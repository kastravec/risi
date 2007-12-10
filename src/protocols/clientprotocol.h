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

#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H


#include "tcpClient.h"
class PlayController;

class ClientProtocol: public QObject
{
    Q_OBJECT

    public:
        ClientProtocol( PlayController *pl );
        ~ClientProtocol();

        enum MessageType {
                            ChatMsg = 'c',
                            NickName = 'n'
                         };

        void sendNickName( const QString &name );
        void sendChatMessage( const QString &msg, const QString &nick );
        void connectToServer( const QString &ip, int port );
        QString lastError() const;

    private slots:
        void parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID );

    private:
        void setupConnections();
        void parseServerMessage( const QByteArray msg, const qint8 msgType );
        void parseGameMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID );

        PlayController *player;
        TcpClient tcpClient;
};

#endif
