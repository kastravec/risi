/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci   *
 *   psaraci@gmail.com   *
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

#ifndef RISIUI_H
#define RISIUI_H

#include <QMainWindow>

class QStandardItemModel;
class QTabWidget;
class QComboBox;
class QLabel;
class GameListUI;
class ChatUI;
class BoardView;
class PlayController;
class Message;

class RISIui: public QMainWindow
{
    Q_OBJECT

    public:
        RISIui(QWidget *parent = 0);

        PlayController *currentPlayController() const;
        void setCurrentPlayController( PlayController * playController );
        void displayChatMessage( const QString &msg );
        void initConnectionProgressDlg();

    public slots:
        void nickChangedSlot( const QString &oldNick, const QString &newNick );

    private slots:
        void settingsActionTriggered();
        void exitActionTriggered();
        void addRemoveGameActTriggered();
        void hostGameActionTriggered();
        void connectToIPActTriggered();
        void onlineActionTriggered();
        void aboutRisiActionTriggered();
        void serverInfoActionTriggered();
        void playerDisconnectedSlot( const QString reason);
        void updateOnlineStatusSlot( const bool online );
        void updateNickActionTriggered();

    signals:
        void chosenGameToHost( const QString gameName );
        void saveGameListXMLRequest( QStandardItemModel *m );
        void gameListXMLrequest( QStandardItemModel *m );
        void connectToIPSignal( const QString ip, int port );
        void goOnlineSignal( const QString nickName, const bool online );
        void sendMessageRequest( const Message &msg );

    protected:
        void closeEvent( QCloseEvent *);

    private:
        enum DockWidgetType { Bottom=0, Logger=1, Games=2 };
        void createToolBars();
        void createMenus();
        void setupActions();
        void createDockWidget(DockWidgetType type) ;
        void createCentralWidget();
        void createStatusBar();
        void readSettings();
        void writeSettings();
        void setupConnections();

        BoardView *boardView;
        ChatUI *chatUI;
        GameListUI *gameListUI;
        QTabWidget *gameWidgetContainer;
        QComboBox *nickNameCombobox;

        QAction *hostGameAction;
        QAction *settingsAction;
        QAction *addRemoveGameAction;
        QAction *quitGameAction;
        QAction *serverInfoAction;
        QAction *exitAction;
        QAction *onlineAction;
        QAction *connectToIPAction;
        QAction *helpAction;
        QAction *aboutQtAction;
        QAction *aboutRisiAction;
        QAction *updateNickAction;

        bool onlineStatus;
        QLabel *appStatus;
        QLabel *onlineStatusLabel;
        QStandardItemModel *model;//FIXME this should be QAbstractItemModel

        PlayController *currentPlayer;
};

#endif
