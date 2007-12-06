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

#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeView>
#include <QAction>

#include "editGamesUI.h"

//TODO keep a QAbstractItemModel instead of QStandardItemModel

class NewGameDialog : public QDialog
{
    public:
        NewGameDialog(QWidget *parent = 0 )
        :QDialog(parent)
        {
            QPushButton *okB = new QPushButton( tr("&Ok"), this );
            QPushButton *cancelB = new QPushButton ( tr("&Cancel"), this );
            descEditor = new QTextEdit (this);
            nameLineEdit = new QLineEdit ( this );
            nameLineEdit->setFocus( Qt::MouseFocusReason );
            setTabOrder( nameLineEdit, descEditor );
            setTabOrder( descEditor, okB );
            setTabOrder( okB, cancelB );
            QVBoxLayout *vlayout = new QVBoxLayout;
            vlayout->addWidget( new QLabel( tr("Name of the game: "), this) );
            vlayout->addWidget( nameLineEdit );
            vlayout->addWidget( new QLabel ( tr("Descripton for the game: "), this ) );
            vlayout->addWidget( descEditor );
            QHBoxLayout *hlayout = new QHBoxLayout;
            hlayout->addWidget( okB );
            hlayout->addWidget( cancelB );
            vlayout->addLayout( hlayout );

            setLayout( vlayout );
            connect( okB, SIGNAL(clicked( bool )), this, SLOT(accept()));
            connect( cancelB, SIGNAL(clicked( bool )), this, SLOT(accept()) );
        }
        QLineEdit *nameLineEdit;
        QTextEdit *descEditor;
};

EditGamesDialog::EditGamesDialog(QStandardItemModel *m, QWidget *parent )
    :QDialog( parent ), maybeSaveXML( false ), model( m )
{
    setupActions();
    setupUI();
    setupConnections();
    model->setHeaderData(0, Qt::Horizontal, "List of installed games", Qt::DisplayRole ); //FIXME this has to be done by the model somewhere else
    gameListView->setModel( model );
}

EditGamesDialog::~EditGamesDialog()
{}

void EditGamesDialog::addGame()
{
    NewGameDialog newGameDialog;
    int result = newGameDialog.exec();
    if(result == QDialog::Accepted )
    {
        QString dataText = newGameDialog.nameLineEdit->text();

        if( !dataText.isEmpty() )
        {
            QString descText = newGameDialog.descEditor->toPlainText();
            QList <QStandardItem*> items = model->findItems( dataText);//TODO maybe its better to use QModelIndexes so no dependecies from QStandardItemMode/item

            if( items.count() == 0 )//check if the name of the game already exists
            {
                QStandardItem *newGameItem = new QStandardItem( dataText );
                if( !descText.isEmpty() )
                    newGameItem->setData( descText, Qt::ToolTipRole );
                else
                    newGameItem->setData( "No info attached so far", Qt::ToolTipRole );

                newGameItem->setData( "game", Qt::UserRole );
                model->appendRow( newGameItem );
            }
            else
                QMessageBox::warning(this, tr("Warning!"), tr("Please choose another name for the game. This name is already in use by another game"));
        }
    }
}

void EditGamesDialog::removeGame()
{
    QItemSelectionModel *selectionModel = gameListView->selectionModel();
    QModelIndexList selectedItems = selectionModel->selectedIndexes();

    if( selectedItems.count() == 1 )//so it is clear now that one item only can be selected
    {
        if( selectedItems.at(0).data(Qt::UserRole).toString() == "game" )
            model->removeRow(selectedItems.at(0).row());
        else
            QMessageBox::warning(this, tr("Warning!"), tr("Please select the game which you want to delete!"));
    }
    else
        QMessageBox::warning(this, tr("Warning!"), tr("Please select the game which you want to delete!"));
}

/**
 *
 */
void EditGamesDialog::addFile() //FIXME add files only for selected items ....stupid
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Add script files for your game"));
    for( int i = 0; i < fileNames.count(); ++i )
    {
        QStandardItem *fileItem = new QStandardItem;
        fileItem->setData( "file", Qt::UserRole );
        fileItem->setData( fileNames.at( i ), Qt::DisplayRole );
        QStandardItem *gameItem = model->itemFromIndex( gameListView->currentIndex() );
        gameItem->appendRow( fileItem );
    }
}

void EditGamesDialog::removeFile()
{
    QItemSelectionModel *selectModel = gameListView->selectionModel();
    QModelIndexList selectedItems = selectModel->selectedIndexes();
    if( selectedItems.count() == 1 ) //one item can be selected
    {
        QStandardItem *fileItem = model->itemFromIndex( selectedItems.at(0) );
        if( fileItem->data(Qt::UserRole).toString() == "file" )
            fileItem->parent()->removeRow( fileItem->row() );
        else
            QMessageBox::warning(this, tr("Warning!"), tr("Please select the file which you want to delete!"));
    }
    else
        QMessageBox::warning(this, tr("Warning!"), tr("Please select the file which you want to delete!"));
}

/**
 * initializes all child widgets
 * lays out the widgets in layouts and splitters
 */
void EditGamesDialog::setupUI()//TODO better UI is needed :)
{
    /*north main layout*/
    QHBoxLayout *mainHlayout = new QHBoxLayout;
    QVBoxLayout *mainVlayout = new QVBoxLayout;

    //north west side
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    gameListView = new QTreeView(this);
    addGameButton = new QPushButton( tr("add game"), this);
    removeGameButton = new QPushButton( tr("remove game"), this);
    addFileButton = new QPushButton( tr("add file"), this);
    removeFileButton = new QPushButton( tr("remove file"), this);
    hlayout->addWidget( addGameButton );
    hlayout->addWidget( removeGameButton );
    hlayout->addWidget( addFileButton );
    hlayout->addWidget( removeFileButton );
    vlayout->addWidget( gameListView );
    vlayout->addLayout( hlayout );

    //south side
    QVBoxLayout *vlayout2 = new QVBoxLayout;
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    editor = new QTextEdit(this);
    QWidget *saveEditorActWidget = new QWidget;
    saveEditorActWidget->addAction( saveEditorAction );
    okButton = new QPushButton( tr("Ok"), this );
    cancelButton = new QPushButton( tr("Cancel"), this );
    hlayout2->addWidget( okButton );
    hlayout2->addWidget( cancelButton );
    vlayout2->addWidget( editor );
    vlayout2->addWidget( saveEditorActWidget );
    vlayout2->addLayout( hlayout2 );

    //setting up all the layouts
    mainHlayout->addLayout( vlayout );
    mainVlayout->addLayout( mainHlayout );
    mainVlayout->addLayout( vlayout2 );

    setLayout( mainVlayout );
}

/**
 * initializes actions and sets them up
 */
void EditGamesDialog::setupActions()
{
    addGameAction = new QAction( tr("add"), this );
    removeGameAction = new QAction( tr("remove"), this);
    addFileAction = new QAction( tr("add"), this);
    removeFileAction = new QAction( tr("remove"), this);
    saveEditorAction = new QAction( tr("Save"), this);
}

void EditGamesDialog::setupConnections()
{
    connect( okButton, SIGNAL(released()), this, SLOT(accept()) );
    connect( cancelButton, SIGNAL(released()), this, SLOT(reject()) );
    connect( addGameButton, SIGNAL(released()), this, SLOT(addGame()) );
    connect( removeGameButton, SIGNAL(released()), this, SLOT(removeGame()) );
    connect( addFileButton, SIGNAL(released()), this, SLOT(addFile()) );
    connect( removeFileButton, SIGNAL(released()), this, SLOT(removeFile()) );
}

