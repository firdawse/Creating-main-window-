#include "select.h"
#include "ui_select.h"

select::select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectCol)
{
    ui->setupUi(this);
}

select::~select()
{
    delete ui;
}
QString select::getLoaction()const
{
return ui->lineEdit->text();
}
