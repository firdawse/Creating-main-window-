#ifndef RECENTFILES_H
#define RECENTFILES_H

#include <QWidget>
#include <QString>
namespace Ui {
class recentfiles;
}

class recentfiles : public QWidget
{
    Q_OBJECT

public:
    explicit recentfiles(QWidget *parent = nullptr,QString * files = nullptr);
    ~recentfiles();

private:
    Ui::recentfiles *ui;
};

#endif // RECENTFILES_H
