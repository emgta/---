#ifndef CHANGE_FUNC_H
#define CHANGE_FUNC_H
#include<QString>
#include "graphic_client_interface.hpp"

int change_func(clientRespon &respon,QString *q[]) {
    int i=0,j=0,n=0;
    std::string stuCheck[100][8]= {};                       //����string��ά����
    for(; respon.data.recv_info[i]!='\0'; i++) {            //�ж��ַ������Ƿ����
        while(n<6) {                                        //����ǰn������
            while((respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t')||(respon.data.recv_info[i]=='\n')) {
                i++;
            }                                               //������ͷ�Ŀո��Ʊ�������з�
            while(respon.data.recv_info[i]!='\n') {
                i++;
            }
            n++;                                            //����ÿһ������
        }
        i++;
        for(int k=0; respon.data.recv_info[i]!='\n'; k++) { //��ʼ�����ݷ���

            while((respon.data.recv_info[i]!=' ')&&(respon.data.recv_info[i]=='\t')&&(respon.data.recv_info[i]=='\n')) {
                stuCheck[j][k].push_back(respon.data.recv_info[i]);             //���ַ�ѹ��string
                i++;
            }
            for(; (respon.data.recv_info[i]==' ')||(respon.data.recv_info[i]=='\t'); i++);      //�����ո��Ʊ��
        }
        j++;
    }

    for(int i=0; i<100; i++)
        for(int j=0; j<8; j++)
            q[i][j]=QString::fromStdString(stuCheck[i][j]);             //�����ݴ���QString������

    return j;                                           //��������
}

#endif // CHANGE_FUNC_H

