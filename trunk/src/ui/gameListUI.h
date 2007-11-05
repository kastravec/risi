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

#ifndef SERVERLISTUI_H
#define SERVERLISTUI_H

#include <QStandardItemModel>
#include <QComboBox>
#include <QLabel>
#include <QListView>
#include <QLineEdit>

class ServerListUI
{
    public:
        ServerListUI();
    private:
//         QComboBox gameTypeComboBox;
};

class GameListUI: public QWidget
{
        Q_OBJECT

    public:
        GameListUI ( QWidget *parent = 0 );

    private slots:
        void applyFilter ( int filter );

    private:
        enum GameFilter {All = 0, Mine = 1, Internet = 2, LAN = 3};
        QListView *listView;
        QLineEdit *quickFilterInput;
        QStandardItemModel *gameListModel;
        QComboBox *gameTypeComboBox;
        void setupComboBox();
};

#endif
