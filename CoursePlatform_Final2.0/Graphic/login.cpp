#include "login.h"
#include "ui_login.h"
#include "graphic_client_interface.hpp"
#include <QString>
#include <QDebug>

Login::Login(QWidget *parent) : QDialog(parent)
    ,ui(new Ui::Login) {
    ui->setupUi(this);

    connect(ui->change_to_register_button,
            &QPushButton::clicked,
            this,&Login::change_to_register);

    connect(&subwin,&RegisterDialog::changewinSignal
            ,this,&Login::dealRegister);

    connect(ui->LoginButton,
            &QPushButton::clicked,
            this,&Login::dealLogin);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("��¼����"));

}


void Login::change_to_register() {
    subwin.show();
    this->hide();

    //����������л��������ԭ�����е�������Ϣ
    ui->username->clear();
    ui->password->clear();
}

void Login::dealRegister() {
    subwin.hide();
    this->show();

    //����������л��������ԭ�����е�������Ϣ
    ui->username->clear();
    ui->password->clear();
}

void Login::dealLogin() { //�����¼����Ӧ����
    //��ȡ�б༭�����û���������
    QString username = ui->username->text();
    QString password = ui->password->text();

    clientRespon respon;

    if(ui->Login_type->currentIndex()==0) {
        User_login(isStudent, username, password, respon);
        if(respon.rp == RECV_ERR) { //��¼���ɹ�
            QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�û��������벻��ȷ"));
        } else {
            stu_win.show();
            this->hide();
            QMessageBox::information(this,QString::fromLocal8Bit("�ɹ�"),QString::fromLocal8Bit("��¼�ɹ�"));
        }
    } else {
        User_login(isTeacher, username, password, respon);
        if(respon.rp == RECV_ERR) { //��¼���ɹ�
            QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�û����������벻��ȷ"));
        } else {
            teacher_win.show();
            this->hide();
            QMessageBox::information(this,QString::fromLocal8Bit("�ɹ�"),QString::fromLocal8Bit("��¼�ɹ�"));
        }
    }
}

