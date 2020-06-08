#include "stu_select.h"
#include "ui_stu_select.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include "info_to_str.h"


Stu_Select::Stu_Select(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Select) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //�������ڷ��ͷ����ź�
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Select::send_select_Slot);

    //��ѯ��ѡ�γ�
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Select::search_section);
    //ѡ��
    connect(ui->selectButton_2,
            &QPushButton::clicked,
            this,&Stu_Select::select_section);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("ѧ��ѡ�ν���"));

}

void Stu_Select::send_select_Slot() {
    emit change_select_win_Signal();

    //�㷵������������������
    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
}

void Stu_Select::search_section() {
    //��������
    ui->tableWidget->setRowCount(20);
    //��������
    //ui->tableWidget->setColumnCount();

    clientRespon respon;
    Get_elective_course(respon);

    //����Qstring����
    QString **q =new QString *[10];//�ٶ����һ����
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//����ռ�

    int input = STU_SELECT;
    int rows = change_info_to_str(respon,q,input);
    ui->tableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][5]));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(q[i][6]));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(q[i][3]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;

}

void Stu_Select::select_section() {
    //��ȡ��Ҫѡ��Ŀγ̺�
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Attend_course(sectionnum, respon);

    if(respon.rp == RECV_ERR) { //���õ�����
        QMessageBox::warning(this,QString::fromLocal8Bit("�γ̺Ŵ���"),respon.data.recv_info);
    } else {
        QMessageBox::information(this,QString::fromLocal8Bit("ѡ�γɹ�"),respon.data.recv_info);
    }
}
