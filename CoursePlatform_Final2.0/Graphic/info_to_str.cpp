#include "graphic_client_interface.hpp"
#include "info_to_str.h"


int change_info_to_str(clientRespon &respon,QString *q[],int input) {
    int i=0,j=0,n=0;
    std::string stuCheck[10][8]= {};                       //����string��ά����
    if(input==1) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //�ж��ַ������Ƿ����
            while(n<4) {                                        //����ǰn������
                while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                    i++;
                }                                               //������ͷ�Ŀո��Ʊ�������з�
                while(respon.data.recv_info[i]!='\n') {
                    i++;
                }
                n++;                                            //����ÿһ������
            }
            if(j==0)//�ӽ�����
                i++;
            for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //��ʼ�����ݷ���

                while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')&&(respon.data.recv_info[i]!='\n')) {
                    stuCheck[j][k].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                    i++;
                }
                for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //�����ո��Ʊ��
            }
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

        return j;                                           //��������
    } else if(input==2) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //�ж��ַ������Ƿ����

            for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //��ʼ�����ݷ���

                while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')&&(respon.data.recv_info[i]!='\n')) {
                    stuCheck[j][k].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                    i++;
                }
                for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //�����ո��Ʊ��
            }
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

        return j;
    } else if(input==3) {
        for(i=0; respon.data.recv_info[i]!='\0'; i++) {            //�ж��ַ������Ƿ����
            while(n<3) {                                        //����ǰn������
                while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                    i++;
                }                                               //������ͷ�Ŀո��Ʊ�������з�
                while(respon.data.recv_info[i]!='\n') {
                    i++;
                }
                n++;                                            //����ÿһ������
            }
            if(j==0)//�ӽ�����
                i++;
            for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //��ʼ�����ݷ���

                while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]!='\t')&&(respon.data.recv_info[i]!='\n')) {
                    stuCheck[j][k].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                    i++;
                }
                for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //�����ո��Ʊ��
            }
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

        return j;                                           //��������
    } else if(input==5) {
        while(j<4) {                                        //����ǰn������
            while(respon.data.recv_info[i]!='\n') {
                stuCheck[j][0].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                i++;
            }
            i++;
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

        return j;
    }

    else if(input==6) {
        while(j<3) {                                        //����ǰn������
            while(respon.data.recv_info[i]!='\n') {
                stuCheck[j][0].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                i++;
            }
            i++;
            j++;
        }

        for(int i=0; i<10; i++)
            for(int j=0; j<8; j++)
                q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

        return j;
    }

    else
        return 0;
}

