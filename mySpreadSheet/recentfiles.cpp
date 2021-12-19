#include "recentfiles.h"
#include "ui_recentfiles.h"
#include "mySpreadSheet.h"

recentfiles::recentfiles(QWidget *parent,QString * files ) :
    QWidget(parent),
    ui(new Ui::recentfiles)
{
    ui->setupUi(this);

    for(int i=0;i<5;i++){
    auto item =new QListWidgetItem(files[i]);
    ui->listWidget->addItem(item);
    }

}

recentfiles::~recentfiles()
{
    delete ui;
}
