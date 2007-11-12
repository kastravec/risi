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
#include <QDataStream>

#include "networkProtocol.h"

NetworkProtocol::NetworkProtocol( QObject *parent, QTcpSocket *sock )
    :QObject( parent ), client( sock ), clientError(), messageType(0), packetSize(-1), protocolFormat(10), protocolVersion(11)
{
}

NetworkProtocol::~NetworkProtocol()
{
    delete client;
}

/**
 * this slot is called when data are available for reading
 */
void NetworkProtocol::readData()
{
    //read until there are no bytes available basically
    while (client->bytesAvailable() > 0)
    {
        qDebug()<<"1";

        if (packetSize == -1)
        {
            //make sure that there are available data to read; at this stage, is expected more than 4 bytes
            if( client->bytesAvailable() < sizeof(qint32) )
                return;

            qDebug()<<"2";
            //read the packet size first
            client->read(reinterpret_cast<char*>(&packetSize), sizeof(qint32));
            //changing the byte order for the network to host
            packetSize = ntohl(packetSize);
        }

        qDebug()<<"3";

        //make sure that there are the whole packet is available; basically check if the entire packet is available
        if (client->bytesAvailable() < packetSize)
            return;

        qDebug()<<"4";

        //reseting the packet size since it ensured that there a whole packet is available
        packetSize = -1;

        //init the stream with the socket of the connection
        QDataStream inStream( client );//FIXME datastream version?check qt-docs

        //read and check the protocol format
        qint32 format;
        inStream >> format;
        if( format != protocolFormat )
        {
            qDebug()<<"5";
            emit networkProtocolError( InvalidFormat );
            return;
        }
        qDebug()<<"6";
        //read and check the protocol version
        qint32 version;
        inStream >> version;

        if( version != protocolVersion )
        {
            qDebug()<<"7";
            emit networkProtocolError( InvalidVersion );
            return;
        }
        qDebug()<<"8";
        //read protocol header: the type of message
        inStream >> messageType;//TODO consider message types

        //read message
        QString message;
        inStream >> message;

        emit messageReady( message );
    }
}

QByteArray NetworkProtocol::createPacket( const QString &msg, qint8 type ) const
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly );

    //inserting the protocol format and version in the packet`
    out<<protocolFormat;
    out<<protocolVersion;

    //inserting the message type and message itself in the packet
    out << type;
    out << msg;

    return packet;
}
