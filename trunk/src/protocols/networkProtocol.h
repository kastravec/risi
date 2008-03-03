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

#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>

class Message;
class QAbstractSocket;

class NetworkProtocol: public QObject
{
    Q_OBJECT

    public:
        NetworkProtocol( QObject *parent = 0, QAbstractSocket *socket = 0 );
        virtual ~NetworkProtocol();

        Q_PROPERTY( qint32 protocolFormat READ protocolFormat WRITE setProtocolFormat SCRIPTABLE false )
        Q_PROPERTY( qint32 protocolVersion READ protocolVersion WRITE setProtocolVersion SCRIPTABLE false )

        enum ProtocolError { InvalidFormat =0, InvalidVersion = 1 };

        void setProtocolFormat( qint32 fm );
        qint32 protocolFormat() const;

        void setProtocolVersion ( qint32 vers );
        qint32 protocolVersion() const;

        QByteArray createPacket( const Message &msg ) const;
        qint32 sizeOfPacket( const QByteArray &packet ) const;
        void setClientSocket( QAbstractSocket * socket );
        QString lastError() const;

    public slots:
        void readData();

    signals:
        void messageReady( const Message &msg );
        void networkProtocolError();

    private:
        qint32 packetSize;
        qint32 format;
        qint32 version;
        QString error;
        QAbstractSocket *client;
};

#endif
