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
#include <QSettings>
#include <QLabel>

//FIXME THIS CLASS WILL BE REDISGNED

SettingsUI::SettingsUI(QWidget *parent )
    :QDialog(parent), portSpin(new QSpinBox(this) )
{
    portSpin->setRange( 0, 9999 );
    setFixedSize( 400, 400 );

    QWidget *page = new QWidget(this);//just an initial page for testing
    QVBoxLayout *l = new QVBoxLayout;
    QLabel *label = new QLabel(tr("This is just for testing. You can however change the port for your server: "), this );
    label->setWordWrap( true );
    l->addWidget( label );
    l->addWidget( portSpin );
    page->setLayout( l );

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

    readSettings();
}

/**
 * creates the left side of the ui form. Basically creates a listview with a several items
 * @return
 */
QWidget * SettingsUI::createListOfSettings()
{
    QListView * listViewSettings = new QListView(this);
    listViewSettings->setEditTriggers( QAbstractItemView::NoEditTriggers );

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
{
    writeSettings();
}

void SettingsUI::okButtonClicked()
{
    writeSettings();
    accept();
}

void SettingsUI::readSettings()
{
    QSettings settings;
    settings.beginGroup( "Server" );
    QVariant v = settings.value( "port", 2222 );
    settings.endGroup();

    bool ok;
    int port = v.toInt( &ok );
    if( ok )
        portSpin->setValue( port );
    else
        portSpin->setValue( 9999 );
}

void SettingsUI::writeSettings()
{
    QSettings settings;

    settings.beginGroup( "Server" );
    settings.setValue( "port", portSpin->value() );
    settings.endGroup();
}
