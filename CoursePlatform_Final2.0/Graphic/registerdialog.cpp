#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "graphic_client_interface.hpp"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog) {
    ui->setupUi(this);

    connect(ui->change_login_button,
            &QPushButton::clicked,
            this,&RegisterDialog::send_login_Slot);

    //����ע�ᰴť���¼�
    connect(ui->registerButton,
            &QPushButton::clicked,
            this,&RegisterDialog::deal_register);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("�����������"));



}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::send_login_Slot() {
    emit changewinSignal();

    //����������л��������ԭ�����е�������Ϣ
    ui->usernameEdit->clear();
    ui->ordinarypasswordEdit->clear();
    ui->currentpasswordEdit->clear();

}

void RegisterDialog::deal_register() {
    //��ȡ�б༭�����û��������ֺ�����
    QString username = ui->usernameEdit->text();
    QString cur_password = ui->ordinarypasswordEdit->text();
    QString new_password = ui->currentpasswordEdit->text();

    clientRespon respon;

    if(ui->typeBox->currentIndex()==0) {
        Modify_passwd(isStudent, username, cur_password,new_password,respon);
        if(respon.rp == RECV_ERR) { //���ܲ��ɹ�
            QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�û��������벻��ȷ"));
        } else {
            QMessageBox::information(this,QString::fromLocal8Bit("�ɹ�"),QString::fromLocal8Bit("���ܳɹ�"));
        }
    } else {
        Modify_passwd(isTeacher, username,cur_password,new_password,respon);
        if(respon.rp == RECV_ERR) { //���ܲ��ɹ�
            QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�û����������벻��ȷ"));
        } else {
            QMessageBox::information(this,QString::fromLocal8Bit("�ɹ�"),QString::fromLocal8Bit("���ܳɹ�"));
        }
    }


}
