#include "dialogconnect.h"
#include "ui_dialogconnect.h"

DialogConnect::DialogConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnect)
{
    ui->setupUi(this);
}

DialogConnect::~DialogConnect()
{
    delete ui;
}

QString DialogConnect::getId()
{
    return ui->lineEditID->text();
}

QString DialogConnect::getMdp()
{
    return ui->lineEditMDP->text();
}

void DialogConnect::setMessage()
{
    ui->label->setText(tr("Login or password is incorrect,try again!"));
}


void DialogConnect::on_checkBox_clicked(bool checked)
{
    if(checked==true) {
        ui->lineEditIp->setEnabled(true);
    }else {
        ui->lineEditIp->setEnabled(false);
    }
}

QString DialogConnect::getIp()
{
    return ui->lineEditIp->text();
}
