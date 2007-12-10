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

#include <QWidget>

class QTextEdit;
class QListView;
class QPushButton;
class LineEdit;

class ChatUI: public QWidget
{
    Q_OBJECT

    public:
        ChatUI(QWidget *parent = 0);

        void displayChatMessage( const QString &msg, const QString &nickName );

    signals:
        void sendChatMessageRequest( const QString & msg );

    private:
        QTextEdit *chatWindow;
        LineEdit *inputLineEdit;
        QListView *playerListWindow;

        bool eventFilter ( QObject * watched, QEvent * event );
        bool inputLineEditEvents( QEvent *event );
        void initUI();
};

#endif
