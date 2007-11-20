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

#include <QTcpSocket>
#include "globals/networkProtocol.h"

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
        ConnectionHandler( QTcpSocket *sock = 0, QObject *parent = 0);
        ~ConnectionHandler();

        inline QTcpSocket *socket() const { return client; }

    signals:
        void messageArrived( const QString msg );

    private slots:
        void disconnected();
        void networkProtocolErrorSlot( NetworkProtocol::ProtocolError err );
        void socketErrors( QAbstractSocket::SocketError errors);//FIXME do i need this?
        void socketStateChanged( QAbstractSocket::SocketState state );//FIXME do i need this?

    private:
        void setupConnections();
        void sendMessage(QString msg, qint8 type);

        QTcpSocket *client;
        NetworkProtocol networkProtocol;

        QString clientError;
};

#endif
