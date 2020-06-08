#include "tea_check.h"
#include "ui_tea_check.h"
#include "graphic_client_interface.hpp"
#include "info_to_str.h"

Tea_Check::Tea_Check(QWidget *parent) : QWidget(parent),ui(new Ui::Tea_Check) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��
    ui->sectiontableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //���ͷ����������ź�
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Tea_Check::send_check_Slot);

    //�鿴�ý�ʦ��������ͬѧ�ĳɼ�
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Tea_Check::search_all_info);
    //ɸѡ�ɼ�
    connect(ui->dressButton,
            &QPushButton::clicked,
            this,&Tea_Check::search_dress_info);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("��ʦ�鿴ѧ���ɼ�����"));



}

void Tea_Check::send_check_Slot() {
    emit change_checkwin_Signal();

    //����������ҳ������������Ϣ
    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
    ui->sectiontableWidget->clear();
}

void Tea_Check::search_all_info() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //����Qstring����
    QString **q =new QString *[10];//�ٶ����һ����
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//����ռ�

    int input = TEA_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->sectiontableWidget->setRowCount(rows-1);


    //qDebug()<<q[0][0];


    for(int i = 0; i < rows-1; i++) {
        ui->sectiontableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->sectiontableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;
}

void Tea_Check::search_dress_info() {
    //��ȡ��Ҫ�鿴�Ŀγ̺�
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Check_score(sectionnum, INCREASE_BY_SCORE, respon);

    if(respon.rp == RECV_ERR) { //�������õ�����
        QMessageBox::warning(this,QString::fromLocal8Bit("�γ̺Ŵ���"),respon.data.recv_info);
    } else { //��ѯ�ɹ�
        QMessageBox::information(this,QString::fromLocal8Bit("��ѯ�ɹ�!"),QString::fromLocal8Bit("�γ̺���ȷ!"));

        //����Qstring����
        QString **q =new QString *[10];//�ٶ����һ����
        for(int i = 0; i<10; i++)
            q[i] = new QString[8];//����ռ�

        int input = TEA_SELECT;
        int rows = change_info_to_str(respon,q,input);
        ui->tableWidget->setRowCount(rows);


        for(int i = 0; i < rows; i++) {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(q[i][3]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][0]));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][2]));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][4]));
        }

        //�ͷſռ�
        for(int i = 0; i < 10; i++)
            delete []q[i];
        delete []q;
    }
}




