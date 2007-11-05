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

#include "gameListUI.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

GameListUI::GameListUI(QWidget *parent )
    :QWidget (parent)
{
    listView = new QListView(this);
    quickFilterInput = new QLineEdit(this);
    gameTypeComboBox = new QComboBox(this);
    gameListModel = new QStandardItemModel(5, 3, listView);

    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;

    hlayout->addWidget( new QLabel( tr("Choose server: ") ) );
    hlayout->addWidget( gameTypeComboBox );

    vlayout->addLayout( hlayout );

    hlayout = new QHBoxLayout;

    hlayout->addWidget(new QLabel( tr("Quickfilter: ") ) );
    hlayout->addWidget(quickFilterInput);

    vlayout->addLayout( hlayout );
    vlayout->addWidget( listView );

    listView->setModel( gameListModel );

    setLayout( vlayout );

    gameTypeComboBox->addItems( QStringList() <<"Sever 1"<<"Sever 2"<<"Sever 3"<<"Sever 4" );
    connect(gameTypeComboBox, SIGNAL(currentIndexChanged( int )), this, SLOT( applyFilter(int) ) );

}

void GameListUI::applyFilter ( int filter)
{
    switch ( filter )
    {
        case All:
        {
            break;
        }
        case Mine:
        {
            break;
        }
        case Internet:
        {
            break;
        }
        case LAN:
        {
            break;
        }
    }
}

ServerListUI::ServerListUI()
{

}
