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

#include "chatUI.h"
#include <QSplitter>


ChatUI::ChatUI(QWidget *parent)
    :QWidget(parent)
{
    initUI();

}

void ChatUI::initUI()
{
    sendButton = new QPushButton(tr("&Send"), this);
    clearButton = new QPushButton(tr("&Clear"), this);
    mainChatWindow = new QTextEdit (this);
    playerListWindow = new QListView (this);
    chatInputWindow = new QLineEdit(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget( mainChatWindow );
    splitter->addWidget( playerListWindow );
    splitter->setStretchFactor( 0, 5 );
    splitter->setStretchFactor( 1, 1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget( chatInputWindow );
    hlayout->addWidget(sendButton);
    hlayout->addWidget(clearButton);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget( splitter);
    vlayout->addLayout( hlayout );

    setLayout(vlayout);
}
