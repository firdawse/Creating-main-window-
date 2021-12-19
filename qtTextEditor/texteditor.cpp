#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCursor>
#include <QColorDialog>
#include <QFontDialog>

texteditor::texteditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::texteditor)
{
    ui->setupUi(this);
}

texteditor::~texteditor()
{
    delete ui;
}


void texteditor::on_actionNew_triggered()
{
*filename = "";
ui->textEdit->setText("");
}

void texteditor::on_actionOpen_triggered()
{
   QString path = QFileDialog::getOpenFileName(this,"open the file");
   QFile file(path);
   *filename = path;
   if(!file.open(QFile::ReadOnly |QFile::Text)){
       QMessageBox::warning(this,"warning","file not open");
       return;
   }
   QTextStream in (&file);
   QString text =in.readAll();
   ui->textEdit->setText(text);
   file.close();
}

void texteditor::on_actionSave_triggered()
{
    if(!filename){
    QString path = QFileDialog::getSaveFileName(this,"open the file");

    *filename = path;
    }

    QFile file(*filename);
    QTextStream out (&file);
    QString text =ui->textEdit->toPlainText();
    out << text ;
    file.flush();
    file.close();
 }

void texteditor::on_actionSave_as_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,"open the file");
    QFile file(path);
    *filename = path;
    if(!file.open(QFile::WriteOnly |QFile::Text)){
        QMessageBox::warning(this,"warning","file not open");
        return;
    }
    QTextStream out (&file);
    QString text =ui->textEdit->toPlainText();
    out << text ;


 }

void texteditor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void texteditor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void texteditor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void texteditor::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

void texteditor::on_actionundo_triggered()
{
    ui->textEdit->undo();
}

void texteditor::on_actionabout_TextEditor_triggered()
{
    QMessageBox::about(this,"About","...");
}

void texteditor::on_actionItalic_triggered()
{
    QTextCharFormat format;
    format.setFontItalic(1);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void texteditor::on_actionBold_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void texteditor::on_actionunderline_triggered()
{
    QTextCharFormat format;
    format.setFontUnderline(1);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void texteditor::on_actionstrikeout_triggered()
{
    QTextCharFormat format;
    format.setFontStrikeOut(1);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void texteditor::on_actiontext_Background_triggered()
{
    QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
        }
    QTextCharFormat fmt = cursor.charFormat();
    if (col.isValid()) {
        fmt.setBackground(col);
      } else {
        fmt.clearBackground();
        }
    cursor.setCharFormat(fmt);
    ui->textEdit->setCurrentCharFormat(fmt);
}


