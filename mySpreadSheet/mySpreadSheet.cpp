#include "mySpreadSheet.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include "dialog.h"
#include "finddialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDebug>
#include <QStandardItem>
#include<QListWidgetItem>
#include <QTabWidget>
#include "recentfiles.h"
#include <QColorDialog>
#include <QPainter>
#include <QFontDialog>
#include "select.h"

mySpreadSheet::mySpreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();

    makeConnexions();

     //creating tool bar
    createToolBars();

    //Creating the labels for the status bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);


    //initier le change currentfile
    currentFile=nullptr;
    setWindowTitle("buffer");
}

mySpreadSheet::~mySpreadSheet()
{ delete spreadsheet;

    // --------------- Actions       --------------//
    delete  newFile;
    delete  open;
    delete  save;
    delete  saveAs;
    delete  exit;
    delete cut;
    delete copy;
    delete paste;
    delete deleteAction;
    delete find;
    delete row;
    delete Column;
    delete all;
    delete goCell;
    delete recalculate;
    delete sort;
    delete showGrid;
    delete auto_recalculate;
    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;

}
void mySpreadSheet::setupMainWidget()
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(100);
    spreadsheet->setColumnCount(10);
    setCentralWidget(spreadsheet);


}
void mySpreadSheet::createActions()
{
    //New File
   QPixmap newIcon(":/new_file.png");
   newFile = new QAction(newIcon, "&New", this);
   newFile->setShortcut(tr("Ctrl+N"));


    // open file
   open = new QAction("&Open", this);
   open->setShortcut(tr("Ctrl+O"));


    //open file
   save = new QAction("&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    // open file
   saveAs = new QAction("save &As", this);


    //open file
   QPixmap cutIcon(":/cut_icon.png");
   cut = new QAction(newIcon, "Cu&t", this);
   cut->setShortcut(tr("Ctrl+X"));

   // Cut menu
   copy = new QAction( "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));


   paste = new QAction( "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));


   deleteAction = new QAction( "&Delete", this);
   deleteAction->setShortcut(tr("Del"));


   row  = new QAction("&Row", this);
   Column = new QAction("&Column", this);
   all = new QAction("&All", this);
   all->setShortcut(tr("Ctrl+A"));



   QPixmap findIcon(":/search_icon.png");
   find= new QAction(newIcon, "&Find", this);
   find->setShortcut(tr("Ctrl+F"));

   QPixmap goCellIcon(":/go_to_icon.png");
   goCell = new QAction( goCellIcon, "&Go to Cell", this);
   deleteAction->setShortcut(tr("f5"));

   about =  new QAction("&About");
   aboutQt = new QAction("About &Qt");

   recalculate = new QAction("&Recalculate",this);
   recalculate->setShortcut(tr("F9"));


   sort = new QAction("&Sort");

   load =new QAction("&Load");
   recentFiles =new QAction("&recentFiles");


   showGrid = new QAction("&Show Grid");
   showGrid->setCheckable(true);
   showGrid->setChecked(spreadsheet->showGrid());

   auto_recalculate = new QAction("&Auto-recalculate");
   auto_recalculate->setCheckable(true);
   auto_recalculate->setChecked(true);
   backgroundColor = new QAction("& backroundColor");
   fontAction = new QAction("&font");
    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"E&xit", this);
   exit->setShortcut(tr("Ctrl+Q"));

}
void mySpreadSheet::createMenus(){
    //filemenu
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(newFile);
    FileMenu->addAction(open);
    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addSeparator();
    FileMenu->addAction(exit);
    FileMenu->addAction(load);
    FileMenu->addSeparator();
    FileMenu->addAction(recentFiles);
    //edit menu
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();

    editMenu->addAction(find);
    editMenu->addAction(goCell);

    auto select = editMenu->addMenu("&Select");
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);


    //help menu
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);

    //Tools menu
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);


    //Optins menus
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(auto_recalculate);
    optionsMenu->addAction(backgroundColor);
    optionsMenu->addAction(backgroundColor);
    optionsMenu->addAction(fontAction);
}
void mySpreadSheet::createToolBars()
{

    //Crer une bare d'outils
    auto toolbar1 = addToolBar("File");


    //Ajouter des actions acette bar
    toolbar1->addAction(newFile);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


    //Creer une autre tool bar
    auto toolbar2  = addToolBar("ToolS");

    toolbar2->addAction(goCell);

    auto toolBar =addToolBar("lineEdit");
    formulaInput= new QLineEdit(this);
    cellLabel=new QLabel(this);
     toolBar->addWidget(cellLabel);
    toolBar->addWidget(formulaInput);

}
void mySpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0, %1)"};
   cellLocation->setText(cell.arg(row+1).arg(col+1));

}

void mySpreadSheet::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void mySpreadSheet::makeConnexions()
{

   // --------- Connexion for the  select all action ----/
   connect(all, &QAction::triggered,
           spreadsheet, &QTableWidget::selectAll);

   // Connection for the  show grid
   connect(showGrid, &QAction::triggered,
           spreadsheet, &QTableWidget::setShowGrid);

   //Connection for the exit button
   connect(exit, &QAction::triggered, this, &mySpreadSheet::close);


   //connectting the chane of any element in the spreadsheet with the update status bar
   connect(spreadsheet, &QTableWidget::cellClicked, this,  &mySpreadSheet::updateStatusBar);

   //connection pour le goDiolog

    connect(goCell ,&QAction::triggered,this,&mySpreadSheet::goCellSlot);

    connect(find,&QAction::triggered,this,&mySpreadSheet::findCell);

    //connecter le save action a saveslot
    connect(save,&QAction::triggered,this,&mySpreadSheet::saveSlot);

     connect(load,&QAction::triggered,this,&mySpreadSheet::loadSlot);

    //connecter le saveas action
    connect(saveAs,&QAction::triggered,this,&mySpreadSheet::saveAsSlot);

    connect(spreadsheet,  &QTableWidget::cellClicked,this, &mySpreadSheet::updateLineEdit);

    connect(recentFiles,&QAction::triggered,this,&mySpreadSheet::recentFilesSlot);

  //backgroundColor connection
    connect(backgroundColor, &QAction::triggered, this, &mySpreadSheet::backgroundColorSlot);

    //font connection
    connect(fontAction, &QAction::triggered, this, &mySpreadSheet::selectFont);
    //copy connection
    connect(copy, &QAction::triggered, this, &mySpreadSheet::copySlot);

    connect(Column, &QAction::triggered, this, &mySpreadSheet::selectcol);
    connect(row, &QAction::triggered, this, &mySpreadSheet::selectrow);

    connect(newFile,&QAction::triggered, this, &mySpreadSheet::newSlot);

    connect(deleteAction,&QAction::triggered, this, &mySpreadSheet::deleteSlot);
}
void mySpreadSheet::goCellSlot(){
    //creer le dialog
    Dialog D;
    //executer le dialog
     auto reply =  D.exec();    //
    //verifier si le dialog a été accepté
     if(reply == Dialog::Accepted)
        {
         //b32
         //extraire le text
         QString cell =D.getCell();

         //extraire la ligne
         int row = cell[0].toLatin1() -'A';

         //extraire la colonne
         cell =cell.remove(0,1);
         int col= cell.toInt()-1;

         //changer de cellule
         statusBar()->showMessage("changing the current cell",2000);
         spreadsheet->setCurrentCell(row,col);

     }
}

void mySpreadSheet::updateLineEdit()
{

   auto location = spreadsheet->currentItem();
               if(location )
formulaInput->setText(location->data(Qt::EditRole).toString());
               else
                   formulaInput->clear();
}

void mySpreadSheet::findCell(){

    findDialog f;

     auto reply =  f.exec();

     //extraire le text
     QString cell =f.getCell();
     int rows = spreadsheet->rowCount();
     int cols = spreadsheet->columnCount();

     for (int i=0;i<rows ;i++){
        for (int j=0;j<cols ;j++){
           auto location = spreadsheet->item(i,j);
           if(location && location->text()==cell){
               spreadsheet->setCurrentCell(i, j);
               return;
        }
     }
   }
}

void mySpreadSheet::saveSlot(){
    if(!currentFile){
        //Creer Factory design
        QFileDialog D; //factory
        auto filename = D.getSaveFileName();
         currentFile = new QString(filename);
        setWindowTitle(*currentFile);
    }
    //sauvegarder le content
    saveContent(*currentFile);
};

void mySpreadSheet::saveAsSlot(){

        //Creer Factory design
        QFileDialog D; //factory
        auto filename = D.getSaveFileName();
         currentFile = new QString(filename);
        setWindowTitle(*currentFile);
        saveContent(*currentFile);
};

void mySpreadSheet::loadSlot(){

    QFileDialog D; //factory
    auto filename = D.getOpenFileName();

    files[count]=filename;
    count++;
    if (filename != ""){
       currentFile = new QString(filename);
       setWindowTitle(filename);
       loadContent(*currentFile);
    }




};
 void mySpreadSheet::loadContent(QString filename)const
 {
    QFile file(filename);
    QFileInfo fi(filename);
    if(fi.suffix()=="csv"){

        if ( !file.open(QIODevice::ReadOnly) ) {
                qDebug() << "File not exists";
            } else {
             int row=0;
             int col=0;

                QTextStream in(&file);
                //Reads the data up to the end of file
                while (!in.atEnd())
                {
                    QString line = in.readLine();

                    // consider that the line separated by semicolons into columns
                    for (QString item : line.split(",")) {

                        spreadsheet->setItem(row,col,new QTableWidgetItem(item));
                        col++;
                    }
                   row++;
                }
                file.close();
            }

 }else{
    if(file.open(QIODevice::ReadOnly)){
        //
        QTextStream in(&file);
        QString line;
        while(!in.atEnd()){
            line= in.readLine();
            auto tokens=line.split(QChar(','));
            auto row = tokens[0].toInt();
            auto col = tokens[1].toInt();
            spreadsheet->setItem(row,col,new QTableWidgetItem(tokens[2]));
        }
       }
     }
 }
 void mySpreadSheet::recentFilesSlot(){
   auto wid = new QWidget();
   wid->show();
   wid->resize(280,250);
   wid->setWindowTitle("recents Files");
   auto recentFile = new recentfiles(wid,files);
   recentFile->show();

}
void mySpreadSheet::saveContent(QString filename)const
{
    //syntaxe c++
    //ofstream out(filname) /out.close();
    //syntaxe c
    //file * fopen(filenam,"w")  fclose(fid);

    //en Qt
    //pointeur sur un fichier
    QFile file(filename);

    //ouvrir le fichier en mode write
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){

    QMessageBox::warning(spreadsheet,"warning","file not open");
        return;
    }
        QTextStream out(&file);
        //Parcourir les cellules et sauvegarder
        int rows = spreadsheet->rowCount();
        int cols = spreadsheet->columnCount();

        for (int i=0;i<rows ;i++){
           for (int j=0;j<cols ;j++){
                auto cell=spreadsheet->item(i,j);
                if(cell){
                    out<< i <<","<<j <<","<<cell->text() <<endl;
                }
           }

    }
    //fermer le fichier
        file.flush();
        file.close();
}

void mySpreadSheet::backgroundColorSlot()
{
    QTableWidgetItem *item = spreadsheet->currentItem();
    QColor col = item ? item->background().color() : spreadsheet->palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    const QList<QTableWidgetItem *> selected = spreadsheet->selectedItems();
    if (selected.isEmpty())
        return;

    for (QTableWidgetItem *i : selected) {
        if (i)
            i->setBackground(col);
    }

}


void mySpreadSheet::selectFont()
{
    const QList<QTableWidgetItem *> selected = spreadsheet->selectedItems();
    if (selected.isEmpty())
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    for (QTableWidgetItem *i : selected) {
        if (i)
            i->setFont(fnt);
    }
}
void mySpreadSheet::copySlot(){
 spreadsheet->currentItem()->clone();
}

void mySpreadSheet::selectcol( )
{

    select f;

     auto reply =  f.exec();

     //extraire le text
     auto col =f.getLoaction();

    if(col <= 0) return;
    spreadsheet->setSelectionMode(QAbstractItemView::SingleSelection);
    spreadsheet->setSelectionBehavior(QAbstractItemView::SelectColumns);
    spreadsheet->selectColumn(col.toInt()-1);
    spreadsheet->setSelectionMode(QAbstractItemView::NoSelection);
}
void mySpreadSheet::selectrow( )
{
     select f;
     auto reply =  f.exec();

     //extraire le text
     auto row =f.getLoaction();

    if(row <= 0) return;
    spreadsheet->setSelectionMode(QAbstractItemView::SingleSelection);
    spreadsheet->setSelectionBehavior(QAbstractItemView::SelectRows);
    spreadsheet->selectRow(row.toInt()-1);
    spreadsheet->setSelectionMode(QAbstractItemView::NoSelection);

}
void mySpreadSheet::newSlot(){
*currentFile="";
spreadsheet->clearContents();
}

void mySpreadSheet::deleteSlot(){

  const QList<QTableWidgetItem *> selected = spreadsheet->selectedItems();
  if (selected.isEmpty())
      return;
  for (QTableWidgetItem *i : selected) {
      if (i)
          i->setText("");
  }


}

