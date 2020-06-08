#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstring>

#include "../Shared/csapp.h"
#include "../Shared/global.hpp"
#include "../Shared/network.hpp"
#include "../Library/person.hpp"
#include "../Library/system.hpp"
#include "server.hpp"
#include "../Library/course.hpp"

Server::Server(int argc, const char *argv[]) {
    unsigned short port;

    /* Check arguments */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[1]);
    listenSock = Open_listenfd(port);
    start_time = time(NULL);
    log_file.open("server.log");
    std::cout << "Server have started..." << std::endl;
    std::cout << "If you want exit/stop the server, just press the ctrl+c" << std::endl;

    sock_fd.insert(listenSock);
    FD_ZERO(&fds);
    FD_SET(listenSock, &fds);
}

Server::~Server() {
    sock_fd.clear();
    client.clear();
    log_file.close();
    Result_system &system = Result_system::get_instance();
    delete &system;
}

/******************************************
 * Wrappers for the server basic routines
 ******************************************/

void Server::run() {
    while (1) {
        memcpy(&rfds, &fds, sizeof(fds));
        if (Select(&rfds, 0, 0, NULL) <= 0) break;

        // A new client
        if (FD_ISSET(listenSock, &rfds)) {
            dataSock = Accept(listenSock, 0, 0);
            printf("Accept socket %d\n", dataSock);

            FD_SET(dataSock, &fds);
            if (sock_fd.find(dataSock) == sock_fd.end())
                sock_fd.insert(dataSock);
            client[dataSock].status = NO_LOGIN;
        }
        for (auto fd : sock_fd) {
            if (fd !=listenSock && FD_ISSET(fd, &rfds)) {
                if (IsSocketClosed(fd)) {
                    printf("Socket closed!\n");
                    closesocket(fd);
                    FD_CLR(fd, &fds);
                    client[fd].status = NO_LOGIN;
                } else
                    receive_data(fd);
            }
        }
    }
    closesocket(listenSock);
    closesocket(dataSock);
}

int Server::receive_data(int sock) {
    Request_info req;
    recv_request(sock, &req);

    try {
        /* Check the authenrization */
        if (!authenrize(sock, req))
            throw std::invalid_argument("You have no right to do this.");

        /* Process the requirement */
        switch (req) {
        case LOGIN:
            do_login(sock);
            break;
        case PRINT_SCORE_TABLE:
            do_check_score(sock);
            break;
        case ATTEND_COURSE:
            do_attend_course(sock);
            break;
        case CANCEL_COURSE:
            do_cancel_course(sock);
            break;
        case PRINT_ELECTIVE_COURSE:
            do_print_elective_course(sock);
            break;
        case MODIFY_SCORE:
            do_modify_score(sock);
            break;
        case GET_INFO:
            do_get_info(sock);
            break;
        case MODIFY_PASSWD:
            do_modify_password(sock);
            break;
        }
    } catch (std::invalid_argument err) {
        printf("catch err\n");
        std::cout << err.what();
        send_error(sock, err.what());
    }

    return 1;
}

void Server::log_event(std::ostream &os, Request_info req, sockaddr_in peer, socklen_t name_len) {
    std::string s;
    switch (req) {
    case LOGIN:
        s = "LOGIN";
        break;
    case GET_INFO:
        s = "GET_INFO";
        break;
    case PRINT_ELECTIVE_COURSE:
        s = "PRINT_ELECTIVE_COURSE";
        break;
    case ATTEND_COURSE:
        s = "ATTEND_COURSE";
        break;
    case CANCEL_COURSE:
        s = "CANCEL_COURSE";
        break;
    case PRINT_SCORE_TABLE:
        s = "PRINT_SCORE_TABLE";
        break;
    case MODIFY_SCORE:
        s = "MODIFY_SCORE";
        break;
    case MODIFY_PASSWD:
        s = "MODIFY_PASSWD";
        break;
    default:
        s = "BAD_REQUEST";
        break;
    }
    os << (int)(time(NULL) - start_time) << " server Recv a request form " << inet_ntoa(peer.sin_addr) << ":" << ntohs(peer.sin_port) << "\nRequest for: " << s.c_str() << std::endl << std::endl ;
}

/*
 receive the "request" packet
 */
void Server::recv_request(int fd, Request_info *req) {
    sockaddr_in peer;
    socklen_t name_len = sizeof(peer);

    /* Recv the request */
    printf("Recv: %d\n", recvfrom(fd, (char *)req, sizeof(Request_info), 0, (sockaddr *)&peer, &name_len));

    /* log the request */
    log_event(std::cout, *req, peer, name_len);
    log_event(log_file, *req, peer, name_len);
}

/******************************************
 * Wrappers for the request processing routines
 ******************************************/

bool Server::authenrize(int userID, Request_info type) {
    int clientType = client[userID].status;

    if (type == MODIFY_PASSWD) {
        return true;
    }

    /* For un-register user, they can only login*/
    if (clientType == NO_LOGIN) {
        if (type == LOGIN) return true;
        else return false;
    }

    /* get info is ok for both teacher and student */
    if (type <= GET_INFO) return true;

    if (clientType == isStudent && (type <= CANCEL_COURSE))
        return true;
    if (clientType == isTeacher && (type >= PRINT_SCORE_TABLE))
        return true;

    return false;
}

void Server::do_login(int fd) {
    Result_system &system = Result_system::get_instance();
    size_t id;
    clientType type;
    std::string password;
    char passwd_recv[MAX_PASSWORD_LENGTH];

    Recv(fd, &type, sizeof(type));
    Recv(fd, &id, sizeof(id));
    Recv(fd, passwd_recv, MAX_PASSWORD_LENGTH);
    password = passwd_recv;

    Person_ptr user_ptr = system.get_person(id);

    if (!user_ptr->authorize(password) || type != user_ptr->get_user_type()) {
        throw std::invalid_argument("Your id/password is incorrect.");
    }

    client[fd].status = type;
    client[fd].data = user_ptr;

    Message mes;
    send_message(fd, "Login OK!");
}

void Server::do_get_info(int userID) {
    Score_mode mode;
    Recv(userID, &mode, sizeof(mode));

    std::stringstream ss;
    (client[userID].data)->display_info(ss, mode);

    /*  Send the info message */
    send_message(userID, ss);
}

void Server::do_print_elective_course(int userID) {
    Result_system &system = Result_system::get_instance();
    Student_ptr stu_ptr = std::dynamic_pointer_cast<Student>(client[userID].data);
    std::stringstream ss;

    system.print_available_course(*stu_ptr, ss);
    send_message(userID, ss);
}

void Server::do_attend_course(int userID) {
    Course::seq courseID;
    Student_ptr stu_ptr = std::dynamic_pointer_cast<Student>(client[userID].data);
    Recv(userID, &courseID, sizeof(courseID));

    std::stringstream ss;
    ss << "You attend the " << stu_ptr->enroll_course(courseID) << " course successfully." << std::endl;
    send_message(userID, ss);
}

void Server::do_cancel_course(int userID) {
    Course::seq courseID;
    Student_ptr stu_ptr = std::dynamic_pointer_cast<Student>(client[userID].data);

    /* Recv the request info */
    Recv(userID, &courseID, sizeof(courseID));

    /* Send the result */
    std::stringstream ss;
    ss << "You cancel the " << stu_ptr->cancel_course(courseID) << " course successfully." << std::endl;
    send_message(userID, ss);
}

void Server::do_check_score(int userID) {
    Course::seq courseID;
    Teacher_ptr tea_ptr = std::dynamic_pointer_cast<Teacher>(client[userID].data);
    unsigned short int order;

    /* Recv the request info */
    Recv(userID, &courseID, sizeof(courseID));
    Recv(userID, &order, sizeof(order));

    /* Send the result */
    std::stringstream ss;
    tea_ptr->check_score(courseID, ss, order);

    send_message(userID, ss);
}

void Server::do_modify_score(int userID) {
    Course::seq courseID;
    Person::seq student = 0;
    Course::score newScore = 0;
    Teacher_ptr tea_ptr = std::dynamic_pointer_cast<Teacher>(client[userID].data);

    /* Recv the request info */
    Recv(userID, &courseID, sizeof(courseID));
    Recv(userID, &student, sizeof(student));
    Recv(userID, &newScore, sizeof(newScore));

    /* Send the result */
    std::stringstream ss;
    tea_ptr->modify_score(ss, courseID, student, newScore);

    send_message(userID, ss);
}

void Server::do_modify_password(int fd) {
    Result_system &system = Result_system::get_instance();
    clientType type;
    size_t id;
    std::string cur_passwd;
    std::string new_passwd;
    char cur_passwd_recv[MAX_PASSWORD_LENGTH];
    char new_passwd_recv[MAX_PASSWORD_LENGTH];

    Recv(fd, &type, sizeof(type));
    Recv(fd, &id, sizeof(id));
    Recv(fd, cur_passwd_recv, MAX_PASSWORD_LENGTH);
    Recv(fd, new_passwd_recv, MAX_PASSWORD_LENGTH);
    cur_passwd = cur_passwd_recv;
    new_passwd = new_passwd_recv;

    Person_ptr user_ptr = system.get_person(id);
    if (!user_ptr->change_passwd(cur_passwd, new_passwd)) {
        throw std::invalid_argument("Your current id/password is incorrect.");
    }

    Message mes;
    send_message(fd, "Change password OK!");
}


