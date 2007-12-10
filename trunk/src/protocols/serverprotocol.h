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

#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include "connectionHandler.h"
class Game;
class Server;

class ServerProtocol : public QObject
{
    Q_OBJECT

    public:
        ServerProtocol( QTcpSocket * client = 0, QObject *parent = 0 );
        ~ServerProtocol();

        enum MessageType {
                            GameMsg = 'g',
                            Chat = 'c',
                            NickName = 'n',
                            HostRequest = 'h',
                            HostCancel = 'l',
                            JoinGame = 'j',
                            LeaveGame = 'a'
                         };

        void sendChatMessage( const QString &msg, const QString &nickName );

    private slots:
        void parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID );

    private:
        void parseMessageForServer( const QByteArray msg, const qint8 msgType );
        void parseMessageForGame( const QByteArray msg, const qint8 msgType, const qint8 gameID );
        void setupConnections();

        ConnectionHandler connectionHandler;
};

#endif

