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

#ifndef CHATUI_H
#define CHATUI_H

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QHBoxLayout>

class ChatUI: public QWidget
{
    public:
        ChatUI(QWidget *parent = 0);
    private:
        QTextEdit *mainChatWindow;
        QLineEdit *chatInputWindow;
        QListView *playerListWindow;
        QPushButton * sendButton;
        QPushButton * clearButton;

        void initUI();

};

#endif
