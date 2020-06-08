#include "stu_cancel.h"
#include "ui_stu_cancal.h"
#include "graphic_client_interface.hpp"
#include <QDebug>
#include "info_to_str.h"

Stu_Cancel::Stu_Cancel(QWidget *parent) : QWidget(parent),ui(new Ui::Stu_Cancel) {
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //�������ڷ��ͷ����ź�
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::send_cancel_Slot);

    //��ѯ���е���ѡ�γ�
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::search_section);

    //������ȡ���Ŀγ̺Ų��˳�
    connect(ui->cancelButton,
            &QPushButton::clicked,
            this,&Stu_Cancel::cancel_section);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("ѧ��ȡ��ѡ�ν���"));


}

void Stu_Cancel::send_cancel_Slot() {
    emit change_to_cancel_Signal();

    ui->tableWidget->clearContents();
    ui->sectionnumEdit->clear();
}

void Stu_Cancel::search_section() {
    //��������
    ui->tableWidget->setRowCount(20);

    clientRespon respon;

    //TODO: ��������ģʽ
    Get_info(INCREASE_BY_SCORE, respon);
    qDebug() << respon.data.recv_info;

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
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(q[i][4]));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(q[i][6]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;

}

void Stu_Cancel::cancel_section() {
    //��ȡ��Ҫȡ���Ŀγ̺�
    QString sectionnum = ui->sectionnumEdit->text();

    clientRespon respon;
    Cancel_course(sectionnum, respon);

    if(respon.rp == RECV_ERR) { //���õ�����
        QMessageBox::warning(this,QString::fromLocal8Bit("�γ̺Ŵ���"),respon.data.recv_info);
    } else {
        QMessageBox::information(this,QString::fromLocal8Bit("�ɹ�"),respon.data.recv_info);
    }
}







