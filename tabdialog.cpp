/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "tabdialog.h"
#include <QListWidget>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QAction>
#include <QMenuBar>
#include <QSpacerItem>
#include  "pages.h"
#include "commondata.h"
//! [0]
//!
//!
//!

TabDialog::TabDialog(QWidget *parent)
{

    //}
    /*TabDialog::TabDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent)
{*/
    //   QFileInfo fileInfo(fileName);

    //menuBar()->add
    tabWidget = new QTabWidget(this);

    cData=new commonData();

    cData->langCombo = new QComboBox;
    cData->langCombo->addItem(("English"));
    cData->langCombo->addItem(("Russian"));

    tabWidget->addTab(new ValidateTab(tabWidget,cData), tr("Validate Forms"));
    tabWidget->addTab(new SettingsTab(tabWidget,cData), tr("Settings"));

    tabWidget->setCurrentIndex(1);
    /*
//! [1] //! [2]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//! [1] //! [3]
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));*/

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(tabWidget);
    //mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Form Generator UI"));
    createActions();
    createMenus();


    setCentralWidget(tabWidget);
}
//! [5]


TabDialog::~TabDialog()
{
    // delete ui;
}


void TabDialog::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    // connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    // connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    // connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);


}

void TabDialog::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    //helpMenu->addAction(aboutAct);
    //helpMenu->addAction(aboutQtAct);


    // myCoolButton* button= new myCoolButton(this);

    // button->setText("sssss");


    QGroupBox* langGroup = new QGroupBox(tr(""));

    // langGroup->setFlat(true);
    // langGroup->setStyleSheet( "border: none" );

    langGroup->setContentsMargins(0,0,0,0);
    QLabel* langLabelpic = new QLabel("");
    langLabelpic->setPixmap(QPixmap(":/images/lang_verysmall.png"));

    QLabel* langLabel = new QLabel(tr("UI Language:"));



    QHBoxLayout *langLayout = new QHBoxLayout;
    langLayout->addWidget(langLabelpic);
    langLayout->addWidget(langLabel);
    langLayout->addWidget(cData->langCombo);

    langLayout->setContentsMargins(0, 0, 0, 0);
    langGroup->setLayout(langLayout);


    menuBar()->setCornerWidget(langGroup);


}
//! [7]
ValidateTab::ValidateTab(QWidget *parent, commonData *Data)
    : QWidget(parent)
{
    cData=Data;
}
//! [7]

//! [8]
SettingsTab::SettingsTab(QWidget *parent,commonData *Data)
    : QWidget(parent)
{

    cData=Data;

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::ListMode);//QListView::IconMode);
    contentsWidget->setIconSize(QSize(96/2, 84/2));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(160);
    contentsWidget->setMinimumWidth(160);
    contentsWidget->setSpacing(0);

    // commonData* Data=new commonData(this);

    pagesWidget = new QStackedWidget;
    genpage =new GenerateFormsPage(this,cData);
    tablepage= new EditTablesPage(this,cData);


    pagesWidget->addWidget(tablepage);
    pagesWidget->addWidget(genpage);
    genpage->update_view_sing();


    // pagesWidget->addWidget(new SetLanguagePage(this,cData));

    // pagesWidget->addWidget(new PrintAndPreviewPage(this,cData));


    createIcons();
    contentsWidget->setCurrentRow(0);

    //  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    edittab= new QPushButton(tr("Edit Database"));edittab->setObjectName("menuButton");
    edittab->setIcon(QIcon(":/images/table-edit-icon.png"));
    genf= new QPushButton(tr("Generate Forms"));genf->setObjectName("menuButton");
    genf->setIcon(QIcon(":/images/gen.png"));
    QSize a;
    a.setHeight(40);
    a.setWidth(40);
    edittab->setIconSize(a);
    genf->setIconSize(a);

    //tab1= new QPushButton("Form type and answer");tab1->setObjectName("tabButton");

   cData->edit1= new myCoolButton("Edit"); cData->edit1->setObjectName("editButton");
    cData->add1= new myCoolButton("Add new"); cData->add1->setObjectName("addButton");
    cData->rem1= new myCoolButton("Remove"); cData->rem1->setObjectName("remButton");
   // cData->tab2= new QPushButton("Location and area"); ctab2->setObjectName("tabButton");

    cData->edit2= new myCoolButton("Edit"); cData->edit2->setObjectName("editButton");
    cData->rem_area2= new myCoolButton("Eemove area"); cData->rem_area2->setObjectName("remButton");
    cData->rem_loc2= new myCoolButton("Remove location"); cData->rem_loc2->setObjectName("remButton");
    cData->add_area2= new myCoolButton("Add new area"); cData->add_area2->setObjectName("addButton");
    cData->add_loc2= new myCoolButton("Add new location"); cData->add_loc2->setObjectName("addButton");



    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    //verticalLayout->addWidget(contentsWidget);
    verticalLayout->addWidget(edittab);
   // verticalLayout->addWidget(tab1);
    verticalLayout->addWidget(cData->edit1);
    verticalLayout->addWidget(cData->add1);
    verticalLayout->addWidget(cData->rem1);
   // verticalLayout->addWidget(tab2);
    verticalLayout->addWidget(cData->edit2);
    verticalLayout->addWidget(cData->add_area2);
    verticalLayout->addWidget(cData->add_loc2);
    verticalLayout->addWidget(cData->rem_area2);
    verticalLayout->addWidget(cData->rem_loc2);
    verticalLayout->addWidget(genf);


     //tab1->setVisible(true);
     // tab2->setVisible(true);
     cData-> edit1->setVisible(true);
      cData->add1->setVisible(true);
      cData->rem1->setVisible(true);
      cData->edit2->setVisible(false);
      cData->rem_area2->setVisible(false);
      cData->rem_loc2->setVisible(false);
      cData->add_area2->setVisible(false);
      cData->add_loc2->setVisible(false);

    verticalLayout->addStretch();

    horizontalLayout->addLayout(verticalLayout);
    horizontalLayout->addWidget(pagesWidget, 1);

    //QHBoxLayout *buttonsLayout = new QHBoxLayout;
    //buttonsLayout->addStretch(1);
    //buttonsLayout->addWidget(closeButton);

    /* QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);*/
    setLayout(horizontalLayout);
    connect(edittab,
            SIGNAL(clicked(bool)),
            this, SLOT(changePage1()));
    connect(genf,
            SIGNAL(clicked(bool)),
            this, SLOT(changePage2()));
    /*connect(tab1,
            SIGNAL(clicked(bool)),
            this, SLOT(changeTab1()));
    connect(tab2,
            SIGNAL(clicked(bool)),
            this, SLOT(changeTab2()));*/
    connect(cData->add1, SIGNAL(clicked()), tablepage, SLOT(open_win1()));
    connect(cData->edit1, SIGNAL(clicked()),  tablepage, SLOT(open_win11()));
    connect(cData->rem1, SIGNAL(clicked()),  tablepage, SLOT(remove_selected1()));
    connect(cData->add_area2, SIGNAL(clicked()), tablepage, SLOT(open_win3()));
    connect(cData->rem_area2, SIGNAL(clicked()),  tablepage, SLOT(remove_selected3()));
    connect(cData->add_loc2, SIGNAL(clicked()), tablepage, SLOT(open_win4()));
    connect(cData->edit2, SIGNAL(clicked()), tablepage, SLOT(open_win44()));
    connect(cData->rem_loc2, SIGNAL(clicked()),  tablepage, SLOT(remove_selected4()));



}

void SettingsTab::createIcons()
{

    QFont font;
    font.setBold(true);


    /*QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/lang_small.png"));
    configButton->setFont(font);
    configButton->setText(tr("Set Language"));
    configButton->setTextAlignment(Qt::AlignCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/
    /* QTreeWidget *tree=new QTreeWidget;
   tree->setColumnCount(1);


QTreeWidgetItem *item1=new QTreeWidgetItem;
QTreeWidgetItem *item2=new QTreeWidgetItem;
item1->setText(0,"Edit Database");
item1->setIcon(0,QIcon(":/images/table-edit-icon.png"));
item2->setText(0,"Generate forms");
item2->setIcon(0,QIcon(":/images/gen.png"));
tree->addTopLevelItem(item1);
tree->addTopLevelItem(item2);*/


    /* QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/table-edit-icon.png"));
    updateButton->setText(tr("Edit Database"));
    updateButton->setFont(font);
    updateButton->setTextAlignment(Qt::AlignCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



    QListWidgetItem *genb = new QListWidgetItem(contentsWidget);
    genb->setIcon(QIcon(":/images/gen.png"));
    genb->setText(tr("Generate Forms"));
    genb->setFont(font);
    genb->setTextAlignment(Qt::AlignCenter);
    genb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/

    /*  QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/preview.png"));
    queryButton->setText(tr("Preview & Print"));
    queryButton->setFont(font);
    queryButton->setTextAlignment(Qt::AlignCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/



    /* connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));*/

}

void SettingsTab::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));


}
void SettingsTab::changePage1()
{

    pagesWidget->setCurrentIndex(0);
    //tab1->setVisible(true);
    //tab2->setVisible(true);
    cData->edit1->setVisible(true);
   cData->add1->setVisible(true);
    cData->rem1->setVisible(true);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);


}
void SettingsTab::changePage2()
{

    pagesWidget->setCurrentIndex(1);
    //tab1->setVisible(false);
    //tab2->setVisible(false);
    cData->edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);


}
void SettingsTab::changeTab1()
{


    /*edit1->setVisible(true);
    add1->setVisible(true);
    rem1->setVisible(true);
    edit2->setVisible(false);
    rem_area2->setVisible(false);
    rem_loc2->setVisible(false);
    add_area2->setVisible(false);
    add_loc2->setVisible(false);*/


}
void SettingsTab::changeTab2()
{


   /* edit1->setVisible(false);
    add1->setVisible(false);
    rem1->setVisible(false);
    edit2->setVisible(true);
    rem_area2->setVisible(true);
    rem_loc2->setVisible(true);
    add_area2->setVisible(true);
    add_loc2->setVisible(true);*/

}

//! [8]


