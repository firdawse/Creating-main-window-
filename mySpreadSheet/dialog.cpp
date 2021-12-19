#include "dialog.h"
#include "ui_dialog.h"
#include <QRegExp>
#include <QRegExpValidator>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //expression réguliere
    QRegExp exp {"[A-Z][1-9][0-9]{0,2}"};

    //valider l'expression
    ui->lineEdit->setValidator(new QRegExpValidator(exp));
}

Dialog::~Dialog()
{
    delete ui;
}
QString Dialog::getCell()const
{
return ui->lineEdit->text();
}

