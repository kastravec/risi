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

#ifndef PLAYER_H
#define PLAYER_H

#include "connectionHandler.h"
#include "serverprotocol.h"

class Message;
class Game;
class QTcpSocket;

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString nickname READ nickname WRITE setNickname SCRIPTABLE true USER true )

    public:
        Player( QTcpSocket *client, QObject *parent = 0 );
        ~Player();

        QTcpSocket * connectionSocket() const;

        QString nickname() const;
        void setNickname( const QString & name );
        void addGame( Game *gm );
        void sendMessage( const Message &msg );

    private slots:
        void disconnected();

    private:
        void setupConnections() const;
        Game *gameForID( qint8 iD );

        QList < Game *> games;
        QString nick;
        ServerProtocol protocol;
};

#endif
