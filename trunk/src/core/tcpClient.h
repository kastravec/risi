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

#include <QTcpSocket>

class TcpClient: public QObject
{
    Q_OBJECT

    public:
        TcpClient( QObject *parent = 0 );

        void sendMessage(QString msg, qint8 type);

    private slots:
        void connectToServer(const QString server, const int port );
        void readReadyData();
        void disconnected();
        void socketErrors( QAbstractSocket::SocketError errors);
        void socketStateChanged( QAbstractSocket::SocketState state );//FIXME do i need this?

    private:
        enum ProtocolError { InvalidFormat =0, InvalidVersion = 1 };

        void setupConnections();
        void parseMessage( QString msg );
        void protocolError(ProtocolError error);

        QTcpSocket *client;
        QString clientError;
        qint8 messageType;
        qint32 packetSize;
        qint32 protocolFormat;
        qint32 protocolVersion;

};

#endif
