#include "teachermain.h"
#include "ui_teachermain.h"

TeacherMain::TeacherMain(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::TeacherMain) {
    ui->setupUi(this);

    //�л�����ʦ������������
    connect(ui->tea_check_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_check);//�л����鿴����

    connect(ui->tea_change_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_change);//�л������ĳɼ�����
    connect(ui->tea_percheck_button,
            &QPushButton::clicked,
            this,&TeacherMain::change_to_tea_percheck);//�л����鿴������Ϣ����

    //�����Ӵ��ڵ��л�������������
    connect(&tea_check_win,&Tea_Check::change_checkwin_Signal,
            this,&TeacherMain::deal_Check);
    connect(&tea_change_win,&Tea_Change::change_changewin_Signal,
            this,&TeacherMain::deal_Change);
    connect(&tea_percheck_win,&Tea_Percheck::change_to_percheck_Signal,
            this,&TeacherMain::deal_Percheck);

    //�������Ͻ�ͼ��
    this->setWindowIcon(QIcon("://image/3.jpg"));
    //�������Ͻ�����
    this->setWindowTitle(QString::fromLocal8Bit("��ʦ������"));


}

void TeacherMain::change_to_tea_check() {
    this->close();
    tea_check_win.show();

}

void TeacherMain::change_to_tea_change() {
    this->hide();
    tea_change_win.show();

}

void TeacherMain::change_to_tea_percheck() {
    this->hide();
    tea_percheck_win.show();
}

void TeacherMain::deal_Check() {
    this->show();
    tea_check_win.close();
}

void TeacherMain::deal_Change() {
    this->show();
    tea_change_win.hide();
}

void TeacherMain::deal_Percheck() {
    this->show();
    tea_percheck_win.hide();
}
