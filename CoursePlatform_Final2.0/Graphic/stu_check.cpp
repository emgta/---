#include "stu_check.h"
#include "ui_stu_check.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include <QString>
#include "info_to_str.h"


Stu_Check::Stu_Check(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Check) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //�������ڷ��ͷ����ź�
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Check::send_check_Slot);

    //���Ӳ�ѯ��ť���¼�
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Check::check_information);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("ѧ���鿴ѡ����Ϣ����"));

}

void Stu_Check::send_check_Slot() {
    emit change_check_win_Signal();

    //�㷵������������
    ui->tableWidget->clearContents();
}

void Stu_Check::check_information() {
    //��������
    //ui->tableWidget->setRowCount(20);
    //��������
    //ui->tableWidget->setColumnCount();

    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //����Qstring����
    QString **q =new QString *[10];//�ٶ����һ����
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//����ռ�

    int input = STU_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->tableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][5]));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(q[i][6]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;




}
