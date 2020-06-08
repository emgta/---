#include "ipaddlogin.h"
#include "ui_ipaddlogin.h"
#include "graphic_client_interface.hpp"

IpaddLogin::IpaddLogin(QWidget *parent) : QWidget(parent),ui(new Ui::IpaddLogin) {
    ui->setupUi(this);

    connect(ui->connectButton,&QPushButton::clicked,
            this,&IpaddLogin::deal_connect_login);//��������

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("���ӵ�����������"));


}

void IpaddLogin::deal_connect_login() {
    QString ipadd = ui->ipaddress->text();
    QString port = ui->portnum->text();

    if(!network_init(ipadd.toStdString(), port.toInt())) {
        QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�����޷�����ʧ�ܣ�"));
        return;
    }

    this->hide();
    loginwin.show();
}
