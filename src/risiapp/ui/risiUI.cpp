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
#include <QStatusBar>
#include <QDebug>
#include <QSettings>

#include "core/risiApplication.h"
#include "settingsUI.h"
#include "risiUI.h"
#include "hostGameDialog.h"


class ConnectToIPDialog: public QDialog
{
    public:
        ConnectToIPDialog( QWidget * parent = 0 )
        :QDialog( parent ), IPlineEdit( new QLineEdit( this) ), portSpinBox(new QSpinBox(this) )
        {
            setWindowTitle( tr("Connect to IP: ") );
            portSpinBox->setRange( 0, 9999 );

            QHBoxLayout *hlayout = new QHBoxLayout;
            hlayout->addWidget( new QLabel( tr("IP: ") ) );
            hlayout->addWidget( IPlineEdit );

            QHBoxLayout *hlayout2 = new QHBoxLayout;
            hlayout2->addWidget( new QLabel(tr("Port:")) );
            hlayout2->addWidget( portSpinBox );

            QHBoxLayout *hlayout3 = new QHBoxLayout;
            QPushButton *okButton = new QPushButton( tr("OK" ), this);
            QPushButton *cancelButton = new QPushButton( tr("Cancel"), this );
            hlayout3->addWidget( okButton );
            hlayout3->addWidget( cancelButton );

            QVBoxLayout *vlayout = new QVBoxLayout;
            vlayout->addLayout( hlayout );
            vlayout->addLayout( hlayout2 );
            vlayout->addLayout( hlayout3 );

            setLayout( vlayout );

            connect( okButton, SIGNAL(pressed()), this, SLOT(accept() ) );
            connect( cancelButton, SIGNAL(pressed()), this, SLOT(reject() ) );
        }

        QString ip() const { return IPlineEdit->text(); }
        int port() const { return portSpinBox->value(); }

    private:
        QLineEdit *IPlineEdit;
        QSpinBox *portSpinBox;
};

RISIui::RISIui(QWidget *parent)
    :QMainWindow(parent), nickNameCombobox( new QComboBox ), onlineStatus( false), appStatus( new QLabel( tr("Server not ready! "), this ) ), model( new QStandardItemModel )
{
    resize( 800,600);
    setAnimated(true);

    createCentralWidget();
    createDockWidget(Bottom);
    createDockWidget(Games);
    setupActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();
}

/**
 * creates the toolbars
 */
void RISIui::createToolBars()
{
    QToolBar *gameToolBar = addToolBar( tr("Game toolbar") );
    gameToolBar->addAction( hostGameAction );

    QToolBar *serversToolBar = addToolBar( tr("Server toolbar") );
    serversToolBar->addAction( connectToIPAction );

    QToolBar *goOnlineToolBar = addToolBar ( tr("Internet toolbar") );
    nickNameCombobox->setAutoCompletion( true );
    nickNameCombobox->setEditable( true );
    nickNameCombobox->setMaxVisibleItems( 5 );
    goOnlineToolBar->addWidget( new QLabel( tr("Nickname:"), this ) );
    goOnlineToolBar->addWidget( nickNameCombobox );

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
            break;
        }
        case Logger:
        {
            break;
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
            break;
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

void RISIui::createStatusBar()
{
    QStatusBar *statBar = statusBar();

    QString status = tr("Internet status: ");
    if( onlineStatus )
        status += tr("ONLINE");
    else
        status += tr("OFFLINE");

    onlineStatusLabel = new QLabel( status, this );
    statBar->addPermanentWidget( onlineStatusLabel );
    appStatus->setText( tr("Ready.") );
    statBar->addWidget( appStatus );
}

/**
 * creates and sets up the actions
 */
void RISIui::setupActions()
{
    addRemoveGameAction = new QAction ( tr("Add/Remove games"), this );
    addRemoveGameAction->setStatusTip( tr("Add or remove your games to the application ! ") );
    connect( addRemoveGameAction, SIGNAL(triggered( bool )), this, SLOT(addRemoveGameActTriggered()));

    hostGameAction = new QAction ( tr("Host game"), this );
    hostGameAction->setStatusTip( tr("Host a game for the rest of the network players !") );
    connect( hostGameAction, SIGNAL(triggered( bool )), this, SLOT(hostGameActionTriggered()) );

    settingsAction = new QAction ( tr("Settings"), this );
    settingsAction->setStatusTip( tr("Change settings of RISI !") );
    connect(settingsAction, SIGNAL(triggered( bool )), this, SLOT(settingsActionTriggered()) );

    exitAction = new QAction ( tr("Exit"), this );
    exitAction->setStatusTip( tr(" Exit from RISI !") );
    connect( exitAction, SIGNAL(triggered( bool ) ), this, SLOT(exitActionTriggered()) );

    connectToIPAction = new QAction ( tr("Connect to IP "), this );
    connectToIPAction->setStatusTip( tr("Connect to an IP address !") );
    connect( connectToIPAction, SIGNAL(triggered( bool )), this , SLOT(connectToIPActTriggered()) );

    aboutQtAction = new QAction ( tr("About Qt"), this );
    aboutQtAction->setStatusTip( tr(" About the Qt framework !") );
    connect( aboutQtAction, SIGNAL(triggered( bool )), qApp, SLOT(aboutQt()) );

    serverInfoAction = new QAction( tr("Server info"), this );
    serverInfoAction->setStatusTip( tr("Information about the server running ! ") );
    connect( serverInfoAction, SIGNAL(triggered( bool )), this, SLOT(serverInfoActionTriggered()) );

    QString status;
    if ( onlineStatus )
        status = tr("go offline!");
    else
        status = tr("go online!");
    onlineAction = new QAction ( status, this );
    onlineAction->setCheckable( true );
    onlineAction->setStatusTip( tr("Go online !") );
    onlineAction->setChecked( onlineStatus );
    connect( onlineAction, SIGNAL(triggered( bool ) ), this, SLOT(onlineActionTriggered()) );

    helpAction = new QAction ( tr("Help"), this );
    quitGameAction = new QAction ( tr("Quit game"), this );
    aboutRisiAction = new QAction ( tr("About risi"), this );
}

void RISIui::createMenus()
{
    QMenuBar *mainMenuBar = menuBar();

    QMenu *gameMenu = new QMenu ( tr("&Game"), mainMenuBar);
    gameMenu->addAction( addRemoveGameAction );
    gameMenu->addAction( connectToIPAction );
    gameMenu->addAction( hostGameAction );
    gameMenu->addAction( onlineAction );
    gameMenu->addAction ( settingsAction );
    gameMenu->addAction( serverInfoAction );
    gameMenu->addAction( quitGameAction );
    gameMenu->addAction( exitAction );

    QMenu *viewMenu = createPopupMenu();
    viewMenu->setTitle( tr("View ") );

    QMenu *helpMenu = new QMenu (tr("&Help"), mainMenuBar);
    helpMenu->addAction ( helpAction );
    helpMenu->addAction ( aboutQtAction );
    helpMenu->addAction ( aboutRisiAction );

    mainMenuBar->addMenu(gameMenu);
    mainMenuBar->addMenu( viewMenu );
    mainMenuBar->addMenu(helpMenu);
}
 void RISIui::closeEvent( QCloseEvent *)
{
//     exitActionTriggered();
}

void RISIui::settingsActionTriggered()
{
    SettingsUI settingsDialog(this);
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
        emit chosenGameToHost( hostGameDialog.chosenGame() );
}

void RISIui::onlineActionTriggered()
{
    onlineStatus = onlineAction->isChecked();

    emit goOnlineSignal( nickNameCombobox->currentText(), onlineStatus );

    QString status;
    if( onlineStatus )
        status = tr("go offline!");
    else
        status = tr("go online!");

    onlineAction->setText( status );
    onlineAction->setChecked( onlineStatus );
}

void RISIui::connectToIPActTriggered()
{
    ConnectToIPDialog IPdilaog;
    if( IPdilaog.exec() )
        emit connectToIPSignal( IPdilaog.ip(), IPdilaog.port() );
}

void RISIui::aboutRisiActionTriggered()
{

}

/**
 *
 */
void RISIui::serverInfoActionTriggered()
{
    QDialog dialog;
    dialog.setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );
    dialog.setWindowTitle( tr("Server info: ") );

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget( new QLabel( tr("Info about your server: "), this ), Qt::AlignHCenter);

    QList < QString> addresses = RISIapplication::instance()->broadcastIPaddresses();
    QString ipAddresses;
    for( int i = 0; i < addresses.count(); ++i )
    {
        ipAddresses += addresses.at( i );
        if( i != addresses.count() - 1 )
            ipAddresses += "\n";
    }

    QString port = QString::number( RISIapplication::instance()->serverPort() );
    QString nrOfPlayers = QString::number( RISIapplication::instance()->numberOfConnectedPlayers() );

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget( new QLabel( tr("Server IP: "), &dialog ), 0, 0, Qt::AlignTop );
    gridLayout->addWidget( new QLabel( ipAddresses, this ), 0, 1, Qt::AlignTop );
    gridLayout->addWidget( new QLabel( tr("Port: "), this ), 1, 0 );
    gridLayout->addWidget( new QLabel( port, this ), 1, 1 );
    gridLayout->addWidget( new QLabel( tr("Connected players: "), this ), 2, 0 );
    gridLayout->addWidget( new QLabel( nrOfPlayers, this ), 2, 1 );

    QPushButton *okB = new QPushButton( tr("ok"), this );
    connect( okB, SIGNAL(pressed()), &dialog, SLOT(accept() ) );

    vlayout->addLayout( gridLayout );
    vlayout->addWidget( okB );

    dialog.setLayout( vlayout );
    dialog.setFixedSize( dialog.sizeHint() );
    dialog.exec();
}

void RISIui::updateOnlineStatusSlot( const bool online )
{
    onlineStatus = online;
    onlineAction->setChecked( onlineStatus );

    QString status;
    QString label;
    if( onlineStatus )
    {
        label = tr("Internet status: ONLINE");
        status = tr("go offline!");
    }
    else
    {
        label = tr("Internet status: OFFLINE");
        status = tr("go online!");
    }

    onlineAction->setText( status );
    onlineAction->setChecked( onlineStatus );
    qDebug()<<"label:"<<label;
    onlineStatusLabel->setText( label );
}

void RISIui::playerDisconnectedSlot( const QString reason)
{
    QMessageBox::warning ( this, tr("Player disconnected: "), tr(" Player disconnected due to: ") + reason );
}

void RISIui::readSettings()
{
    QSettings settings;
    settings.beginGroup( "General" );
    nickNameCombobox->addItem( settings.value( "nickname" ).toString() );
    settings.endGroup();
}

void RISIui::writeSettings()
{
}


