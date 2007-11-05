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

#include "settingsUI.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <QListView>

SettingsUI::SettingsUI(QWidget *parent )
    :QDialog(parent)
{
    setFixedSize( 400, 400 );
    QWidget *page = new QWidget(this);
    QWidget *list = createListOfSettings();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    hlayout->addWidget( list );
    hlayout->addWidget( page );
    hlayout->setStretchFactor( page, 5);
    hlayout->setStretchFactor( list, 1);

    mainLayout->addLayout( hlayout );
    mainLayout->addLayout( createButtons() );

    setLayout( mainLayout );
}

QWidget * SettingsUI::createListOfSettings()
{
    QListView * listViewSettings = new QListView(this);
    QStandardItemModel *listViewModel = new QStandardItemModel(this);

    listViewModel->appendRow( new QStandardItem( tr("General") ) );
    listViewModel->appendRow( new QStandardItem ( tr("Appearance") ) );
    listViewModel->appendRow( new QStandardItem ( tr("Game") ) );
    listViewModel->appendRow( new QStandardItem ( tr("Sound") ) );
    listViewModel->appendRow( new QStandardItem ( tr("Stuff") ) );

    listViewSettings->setModel( listViewModel );

    connect ( listViewSettings, SIGNAL(activated( const QModelIndex& ) ), this, SLOT(settingsForItem(const QModelIndex &)));

    return listViewSettings;
}

QLayout * SettingsUI::createButtons()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QPushButton *okButton = new QPushButton( tr("Ok"), this);
    QPushButton *applyButton = new QPushButton ( tr("Apply"), this);
    QPushButton *cancelButton = new QPushButton ( tr("Cancel"), this);

    layout->addWidget(okButton);
    layout->addWidget(applyButton);
    layout->addWidget(cancelButton);

    connect (applyButton, SIGNAL(pressed()), this, SLOT(applyButtonClicked()));
    connect (okButton, SIGNAL(pressed()), this, SLOT(okButtonClicked()) );
    connect (cancelButton, SIGNAL(pressed()), this, SLOT(reject()) );

    return layout;
}

void SettingsUI::settingsForItem( const QModelIndex & /*item*/)
{
}

void SettingsUI::applyButtonClicked()
{}

void SettingsUI::okButtonClicked()
{}
