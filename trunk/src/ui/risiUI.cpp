/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci                                   *
 *   psaraci@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

#include "core/risiApplication.h"
#include "risiUI.h"
#include "hostGameDialog.h"

RISIui::RISIui(QWidget *parent)
    :QMainWindow(parent)
{
    resize( 800,600);
    setAnimated(true);

    createCentralWidget();
    createDockWidget(Bottom);
    createDockWidget(Games);
    setupActions();
    createToolBars();
    createMenus();

    model = new QStandardItemModel;
}

void RISIui::createToolBars()
{
    QToolBar *gameToolBar = addToolBar( tr("Game toolbar") );
    gameToolBar->addAction( hostGameAction );
    gameToolBar->addAction( quitGameAction );

    QToolBar *profileToolBar = addToolBar ( tr("Profile toolbar") );
    profileToolBar->addAction( useProfileAction );
    profileToolBar->addAction( createProfileAction );

    QToolBar *serversToolBar = addToolBar( tr("Server toolbar") );
    serversToolBar->addAction( addServerAction );
}

void RISIui::createDockWidget( DockWidgetType type )
{
    switch (type)
    {
        case Bottom:
        {
            chatUI = new ChatUI(this);
            QDockWidget *bottomDockWidget = new QDockWidget( tr("--Chat-- "), this);
            bottomDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
            bottomDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
            bottomDockWidget->setWidget(chatUI);
            addDockWidget(Qt::BottomDockWidgetArea, bottomDockWidget);
        }
        case Logger:
        {
        }
        case Games:
        {
            gameListUI = new GameListUI(this);
            QDockWidget *gameListDockWidget = new QDockWidget( tr("List of games"), this);
            gameListDockWidget->setWidget( gameListUI );
            gameListDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);//TODO?? :)
            gameListDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
            addDockWidget(Qt::LeftDockWidgetArea, gameListDockWidget);
            //             gameListDockWidget->hide();
        }
    }
}

void RISIui::createCentralWidget()
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout;

    gameWidgetContainer = new QTabWidget(centralWidget);
    gameWidgetContainer->setTabShape(QTabWidget::Triangular);
    gameWidgetContainer->addTab(new QWidget(centralWidget),tr("A Game"));
    hlayout->addWidget(gameWidgetContainer);
    centralWidget->setLayout(hlayout);

    setCentralWidget(centralWidget);
}

void RISIui::setupActions()
{
    addRemoveGameAction = new QAction ( tr("Add/Remove games"), this );
    connect( addRemoveGameAction, SIGNAL(triggered( bool )), this, SLOT(addRemoveGameActTriggered()));

    hostGameAction = new QAction ( tr("Host game"), this );
    connect( hostGameAction, SIGNAL(triggered( bool )), this, SLOT(hostGameActionTriggered()) );

    settingsAction = new QAction ( tr("Settings"), this );
    connect(settingsAction, SIGNAL(triggered( bool )), this, SLOT(settingsActionTriggered()) );

    quitGameAction = new QAction ( tr("Quit game"), this );

    exitAction = new QAction ( tr("Exit"), this );
    connect( exitAction, SIGNAL(triggered( bool ) ), this, SLOT(exitActionTriggered()) );
    useProfileAction = new QAction ( tr("Use/Load profile"), this );
    createProfileAction = new QAction ( tr("Create profile"), this );
    addServerAction = new QAction ( tr("Add server"), this );
    helpAction = new QAction ( tr("Help"), this );

    aboutQtAction = new QAction ( tr("About Qt"), this );
    connect( aboutQtAction, SIGNAL(triggered( bool )), qApp, SLOT(aboutQt()) );

    aboutRisiAction = new QAction ( tr("About risi"), this );
}

void RISIui::createMenus()
{
    QMenuBar *mainMenuBar = menuBar();

    QMenu *gameMenu = new QMenu ( tr("&Game"), mainMenuBar);
    gameMenu->addAction( addRemoveGameAction );
    gameMenu->addAction( hostGameAction );
    gameMenu->addAction ( settingsAction );
    gameMenu->addAction( quitGameAction );
    gameMenu->addAction( exitAction );

    QMenu *profileMenu = new QMenu ( tr("Profile"), mainMenuBar);
    profileMenu->addAction( useProfileAction );
    profileMenu->addAction( createProfileAction );

    QMenu *serversMenu = new QMenu ( tr("Servers") );
    serversMenu->addAction( addServerAction );

    QMenu *viewMenu = createPopupMenu();
    viewMenu->setTitle( tr("View ") );

    QMenu *helpMenu = new QMenu (tr("&Help"), mainMenuBar);
    helpMenu->addAction ( helpAction );
    helpMenu->addAction ( aboutQtAction );
    helpMenu->addAction ( aboutRisiAction );

    mainMenuBar->addMenu(gameMenu);
    mainMenuBar->addMenu( profileMenu );
    mainMenuBar->addMenu( serversMenu );
    mainMenuBar->addMenu( viewMenu );
    mainMenuBar->addMenu(helpMenu);
}
 void RISIui::closeEvent( QCloseEvent *)
{
//     exitActionTriggered();
}

void RISIui::settingsActionTriggered()
{
    settingsDialog.exec();
}
void RISIui::exitActionTriggered()
{

    /*QMessageBox::StandardButton*/int buttonPressed = QMessageBox::question ( this, tr("Quitng??") ,tr("Are you sure?") , QMessageBox::Yes, QMessageBox::No );
    if(  buttonPressed == QMessageBox::Ok )
        close();
}

void RISIui::addRemoveGameActTriggered()
{
    RISIapplication::instance()->gameListXMLrequest( model );

    EditGamesUI editGamesDialog( model , this );
    int result = editGamesDialog.exec();

    if ( result == QDialog::Accepted )
            RISIapplication::instance()->saveGameListXML( model );
}

void RISIui::hostGameActionTriggered()
{
    if( model->rowCount() == 0 )
        RISIapplication::instance()->gameListXMLrequest( model );

    HostGameDialog hostGameDialog( model, this );
    int result = hostGameDialog.exec();
    if( result == QDialog::Accepted )
    {
        choseGame = hostGameDialog.chosenGame();
        emit chosenGameToHost( choseGame );
    }
}
