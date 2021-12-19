#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
namespace Ui { class texteditor; }
QT_END_NAMESPACE

class texteditor : public QMainWindow
{
    Q_OBJECT

public:
    texteditor(QWidget *parent = nullptr);
    ~texteditor();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionredo_triggered();

    void on_actionundo_triggered();

    void on_actionabout_TextEditor_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();

    void on_actionunderline_triggered();

    void on_actionstrikeout_triggered();

    void on_actiontext_Background_triggered();

    void on_actiontext_size_triggered();

    void on_actiontext_color_triggered();

protected:
  void  mergeFormatOnWordOrSelection(const QTextCharFormat &format);
  void bgColorChanged(const QColor &c);

private:
    Ui::texteditor *ui;
    QString *filename;
};
#endif // TEXTEDITOR_H
