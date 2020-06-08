#include "tea_change.h"
#include "ui_tea_change.h"
#include "graphic_client_interface.hpp"
#include "info_to_str.h"

Tea_Change::Tea_Change(QWidget *parent) : QWidget(parent),ui(new Ui::Tea_Change) {
    ui->setupUi(this);

    ui->sectiontableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��
    ui->scoretableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�û��޸ı��

    //���ͷ����������ź�
    connect(ui->returnButton,
            &QPushButton::clicked,
            this,&Tea_Change::send_change_Slot);

    //��ѯ���̵ļ����γ̵���Ϣ
    connect(ui->searchsectionButton,
            &QPushButton::clicked,
            this,&Tea_Change::search_section);
    //��ѯָ���γ�������ѧ���ɼ�
    connect(ui->searchButton,
            &QPushButton::clicked,
            this,&Tea_Change::search_score);
    //�ı�ѧ���ɼ�
    connect(ui->confimButton,
            &QPushButton::clicked,
            this,&Tea_Change::change_stu_score);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("��ʦ����ѧ���ɼ�����"));

}

void Tea_Change::send_change_Slot() {
    emit change_changewin_Signal();

    //����������ҳ��������������Ϣ
    ui->sectiontableWidget->clearContents();
    ui->scoretableWidget->clearContents();
    ui->sectionnumEdit->clear();
    ui->stunumEdit->clear();
    ui->stuscorceEdit->clear();
}

void Tea_Change::search_section() {
    clientRespon respon;
    Get_info(INCREASE_BY_SCORE, respon);

    //����Qstring����
    QString **q =new QString *[10];//�ٶ����һ����
    for(int i = 0; i<10; i++)
        q[i] = new QString[8];//����ռ�

    int input = TEA_CHECK;
    int rows = change_info_to_str(respon,q,input);
    ui->sectiontableWidget->setRowCount(rows-1);

    for(int i = 0; i < rows-1; i++) {
        ui->sectiontableWidget->setItem(i,0,new QTableWidgetItem(q[i][0]));
        ui->sectiontableWidget->setItem(i,1,new QTableWidgetItem(q[i][1]));
        ui->sectiontableWidget->setItem(i,2,new QTableWidgetItem(q[i][2]));
        ui->sectiontableWidget->setItem(i,3,new QTableWidgetItem(q[i][3]));
        ui->sectiontableWidget->setItem(i,4,new QTableWidgetItem(q[i][4]));
        ui->sectiontableWidget->setItem(i,5,new QTableWidgetItem(q[i][5]));
    }

    //�ͷſռ�
    for(int i = 0; i < 10; i++)
        delete []q[i];
    delete []q;
}

void Tea_Change::search_score() {
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
        ui->scoretableWidget->setRowCount(rows);


        for(int i = 0; i < rows; i++) {
            ui->scoretableWidget->setItem(i,0,new QTableWidgetItem(q[i][1]));
            ui->scoretableWidget->setItem(i,1,new QTableWidgetItem(q[i][0]));
            ui->scoretableWidget->setItem(i,2,new QTableWidgetItem(q[i][4]));
        }

        //�ͷſռ�
        for(int i = 0; i < 10; i++)
            delete []q[i];
        delete []q;
    }
}

void Tea_Change::change_stu_score() {
    //��ȡ��Ҫ���ĵĿγ̺�,ѧ��ѧ�ųɼ�
    QString sectionnum = ui->sectionnumEdit->text();
    QString stu_no = ui->stunumEdit->text();
    QString stu_score = ui->stuscorceEdit->text();

    clientRespon respon;
    Modify_score(sectionnum, stu_no, stu_score, respon);

    if(respon.rp == RECV_ERR) { //���ó�������
        QMessageBox::warning(this,QString::fromLocal8Bit("�������!"),respon.data.recv_info);
    } else { //�ɹ�
        QMessageBox::information(this,QString::fromLocal8Bit("�޸ĳɹ�!"),QString::fromLocal8Bit("���ĳɼ��ɹ�!"));
    }
}
