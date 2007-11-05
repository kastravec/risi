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
#include <QDockWidget>

#include "chatUI.h"
#include "gameListUI.h"
#include "settingsUI.h"
#include "editGamesUI.h"

class RISIui: public QMainWindow
{
    Q_OBJECT
    public:
        RISIui(QWidget *parent = 0);

    private slots:
        void settingsActionTriggered();
        void exitActionTriggered();
        void addRemoveGameActTriggered();
        void hostGameActionTriggered();

    signals:
        void chosenGameToHost( const QString &gameName );
        void saveGameListXMLRequest( QStandardItemModel *m );
        void gameListXMLrequest( QStandardItemModel *m );

    protected:
        void closeEvent( QCloseEvent *);

    private:
        enum DockWidgetType { Bottom=0, Logger=1, Games=2 };
        void createToolBars();
        void createMenus();
        void setupActions();
        void createDockWidget(DockWidgetType type) ;
        void createCentralWidget();

        SettingsUI settingsDialog;
        ChatUI *chatUI;
        GameListUI *gameListUI;
        QTabWidget *gameWidgetContainer;

        QAction *hostGameAction;
        QAction *settingsAction;
        QAction *addRemoveGameAction;
        QAction *quitGameAction;
        QAction *exitAction;

        QAction *useProfileAction;
        QAction *createProfileAction;

        QAction *addServerAction;

        QAction *helpAction;
        QAction *aboutQtAction;
        QAction *aboutRisiAction;

        QString choseGame; //TODO do i need this here??
        QStandardItemModel *model;//FIXME this should be QAbstractItemModel
};

#endif
