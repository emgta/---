#include "tea_percheck.h"
#include "ui_tea_percheck.h"
#include "info_to_str.h"

Tea_Percheck::Tea_Percheck(QWidget *parent) : QWidget(parent),ui(new Ui::Tea_Percheck) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //����������
    connect(ui->returnButton,&QPushButton::clicked,
            this,&Tea_Percheck::send_percheck_Slot);

    //�����ѯ�����ɸ�����Ϣ
    connect(ui->searchButton,&QPushButton::clicked,
            this,&Tea_Percheck::check_personalinfo);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("��ʦ�鿴������Ϣ����"));
}

void Tea_Percheck::send_percheck_Slot() {
    emit change_to_percheck_Signal();

    //�㷵������������
    ui->tableWidget->clearContents();
}

void Tea_Percheck::check_personalinfo() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //����Qstring����
    QString **q =new QString *[10];//�ٶ����һ����
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//����ռ�

    int input = TEA_PERCHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->tableWidget->setRowCount(rows);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::fromLocal8Bit("����")));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem(QString::fromLocal8Bit("ְ����")));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem(QString::fromLocal8Bit("Ժϵ")));



    for(int i = 0; i < rows; i++) {
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q[i][0]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;


}
