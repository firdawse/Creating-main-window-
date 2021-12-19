#ifndef MYSPREADSHEET_H
#define MYSPREADSHEET_H

#include <QMainWindow>
#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>

class mySpreadSheet : public QMainWindow
{
    Q_OBJECT

public:
    mySpreadSheet(QWidget *parent = nullptr);
    ~mySpreadSheet();


protected:
    void setupMainWidget();
    void createActions();
    void createMenus();

    void createToolBars();
    void makeConnexions();
    void saveContent(QString filename) const;
    void loadContent(QString filename) const;


private slots:
    void close();
    void updateStatusBar(int, int); //Respond for the call changed
    void goCellSlot();
    void findCell();
    void saveSlot(); //pour répondre a l'appell de sauvegarde
    void saveAsSlot();
    void loadSlot();
    void updateLineEdit();
    void recentFilesSlot();
    void backgroundColorSlot();

    void selectFont();
    void copySlot();
    void selectcol();
     void selectrow();
     void newSlot();
    void deleteSlot();



 //Pointers
private:
    // --------------- Central Widget -------------//
    QTableWidget *spreadsheet;
    // --------------- Actions       --------------//
    QAction * newFile;
    QAction * open;
    QAction * save;
    QAction * saveAs;
    QAction * exit;
    QAction *cut;
    QAction *copy;
    QAction *paste;
    QAction *deleteAction;
    QAction *find;
    QAction *row;
    QAction *Column;
    QAction *all;
    QAction *goCell;
    QAction *recalculate;
    QAction *sort;
    QAction *showGrid;
    QAction *auto_recalculate;
    QAction *about;
    QAction *aboutQt;
    QAction *load;
    QAction *recentFiles;
    QAction *backgroundColor;
    QAction *fontAction;


    // ---------- Menus ----------
    QMenu *FileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;


    //  ----- - Widget pouyr la bare d'etat
    QLabel *cellLocation;  //position de la cellule active
    QLabel *cellFormula;   // Formuel de la cellue active

    //nom de fichier
    QString *currentFile;

     QLineEdit *formulaInput;
     QLabel *cellLabel;
     QString files[5];

      int count=0;

};

#endif // MYSPREADSHEET_H
