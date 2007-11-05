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

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

#include "core/risiApplication.h"
#include "hostGameDialog.h"

/**
 *
 * @param parent
 */
HostGameDialog::HostGameDialog( QStandardItemModel *m, QWidget *parent)
    :QDialog( parent )
{
    setupUI( m );
    setupConnections();
}

void HostGameDialog::setupUI( QStandardItemModel *m )
{
    gameListView = new QListView ( this );
    gameListView->setEditTriggers( QAbstractItemView::SelectedClicked );
    gameListView->setModel( m );
    hostButton = new QPushButton ( tr("Host "), this );
    cancelButton = new QPushButton ( tr("Cancel"), this );
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;

    hlayout->addWidget( hostButton );
    hlayout->addWidget( cancelButton );
    vlayout->addWidget( gameListView );
    vlayout->addLayout( hlayout );

    setLayout( vlayout );
}

void HostGameDialog::itemChosen( const QModelIndex &item)
{
    if(item.isValid())
        accept();
    else
    {
        QModelIndex index = gameListView->currentIndex();
        if ( gameListView->selectionModel()->isSelected(index) )
            accept();
        else
            QMessageBox::warning(this, tr("WARNING!"), tr("No game selected to host. Please select a game.") );
    }
}

void HostGameDialog::hostButtonClicked()
{
    itemChosen( QModelIndex() );
}

void HostGameDialog::setupConnections()
{
    connect( hostButton, SIGNAL(released()), this, SLOT(hostButtonClicked() ) );
    connect( gameListView, SIGNAL(doubleClicked( const QModelIndex& )), this, SLOT(itemChosen(const QModelIndex&)) );
    connect( cancelButton, SIGNAL(released()), this, SLOT(reject()) );
}

QString HostGameDialog::chosenGame() const
{
    QItemSelectionModel *selModel = gameListView->selectionModel();
    QModelIndexList selectedItems = selModel->selectedIndexes();

    if( selectedItems.count() != 0 )
        return selectedItems.at(0).data( Qt::DisplayRole ).toString();

    return QString();
}

