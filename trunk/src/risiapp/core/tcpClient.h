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

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QAbstractSocket>
#include "networkProtocol.h"

class QTcpSocket;

class TcpClient: public QObject
{
    Q_OBJECT

    public:
        TcpClient( QObject *parent = 0 );

        void connectToServer( const QString &ip, qint16 port );
        void sendMessage( const QByteArray msg, qint8 type, qint8 gameID );
        QString serverIP() const;
        qint16 serverPort() const;
        QString lastError() const;
        QString lastNetworkProtocolError() const;

    signals:
        void messageArrived( const QByteArray msg, const qint8 msgType, const qint8 gameID );
        void connectedToServer();
        void disconnectedFromServer();

    private slots:
        void dataArrived();
        void networkProtocolErrorSlot();
        void socketErrors( QAbstractSocket::SocketError errors);
        void socketStateChanged( QAbstractSocket::SocketState state );//FIXME do i need this?

    private:
        void setupConnections();
        NetworkProtocol networkProtocol;
        QTcpSocket *client;
        QString clientError;
};

#endif
