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

#ifndef EDITGAMESUI_H
#define EDITGAMESUI_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeView>
#include <QAction>

class QStandardItemModel;

/**
This is a UI class. This class is responsible for adding,removing and editting
games that are about to be installed locally.
*/

class EditGamesUI : public QDialog
{
    Q_OBJECT

    public:
    /**
     * Default constructor
     * @param parent
     */
        EditGamesUI(QStandardItemModel *m , QWidget *parent = 0 );
        ~EditGamesUI();

    private slots:
        void addGame();
        void removeGame();
        void addFile();
        void removeFile();

    private:
        QTextEdit *editor;
        QTreeView *gameListView;
        QStandardItemModel *model;
        QPushButton * okButton, *cancelButton, *addGameButton, *addFileButton, *removeGameButton, *removeFileButton;

        QAction *addGameAction;
        QAction *removeGameAction;

        QAction *addFileAction;
        QAction *removeFileAction;

        QAction *saveEditorAction;

        void setupUI();
        void setupActions();
        void setupConnections();

        bool maybeSaveXML;//FIXME do i need this here ?
};

#endif
