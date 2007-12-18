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

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "networkProtocol.h"
#include <QAbstractSocket>
class QTcpSocket;
class Protocol;
class Message;

/**
 * list of message types:

   a = Invalid protocolFormat
   b = Invalid protocolVersion
   c = Invalid protocol
 */
class ConnectionHandler: public QObject
{
    Q_OBJECT

    public:
        ConnectionHandler( QObject *parent = 0, QTcpSocket *sock = 0 );
        virtual ~ConnectionHandler();

        QTcpSocket *socket() const;
        void setSocket( QTcpSocket *sock );
        QString lastError() const;
        qint64 sendMessage( const Message &msg );

    signals:
        void messageArrived( const Message &msg );
        void connectedToServer();
        void disconnectedFromServer();

    private slots:
        void message( const Message &msg );
        void networkProtocolErrorSlot();
        void socketErrors( QAbstractSocket::SocketError errors);
        void socketStateChanged( QAbstractSocket::SocketState state );

    protected:
        QString clientError;
        QTcpSocket *client;
        NetworkProtocol networkProtocol;

    private:
        void setupConnections();
        Protocol *protocol;

};
#endif
