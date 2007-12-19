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
#include <QAbstractSocket>
#include <qendian.h>
#include "message.h"
#include "networkProtocol.h"

/**
 * \class NetworkProtocol
 * \brief Constructor
 * @param parent  QObject
 */
NetworkProtocol::NetworkProtocol( QObject *parent, QAbstractSocket *socket )
    :QObject( parent ), packetSize(-1), format(10), version(11), error(), client( socket )
{}

/**
 * \brief Destructor
 */
NetworkProtocol::~NetworkProtocol()
{
//     delete client;
}

/**
 * \brief this slot is called when data are available for reading
 * @param client QTcpSocket
 */
void NetworkProtocol::readData()
{
    //read until there are no bytes available basically
    while (client->bytesAvailable() > 0)
    {
        if (packetSize == -1)
        {
            //make sure that there are available data to read; at this stage, is expected more than 4 bytes
            if( client->bytesAvailable() < sizeof(qint32) )
                return;

            //read the packet size first
            client->read(reinterpret_cast<char*>(&packetSize), sizeof(qint32));
            //changing the byte order for the network to host
            packetSize = qFromBigEndian( packetSize );
        }
        //make sure that there are the whole packet is available; basically check if the entire packet is available
        if (client->bytesAvailable() < packetSize)
            return;

        //reseting the packet size since it ensured that there a whole packet is available
        packetSize = -1;

        //init the stream with the socket of the connection
        QDataStream inStream( client );//FIXME datastream version?check qt-docs

        //read and check the protocol format
        qint32 format;
        inStream >> format;
        if( format != format )
        {
            error = tr(" Invalid protocol format ");
            emit networkProtocolError();
            return;
        }

        //read and check the protocol version
        qint32 vers;
        inStream >> vers;

        if( vers != version )
        {
            error = tr(" Invalid protocol version ");
            emit networkProtocolError();
            return;
        }

        //read protocol header:
        // read type of message
        qint8 messageType;
        inStream >> messageType;

        //read game id
        qint8 gmid;
        inStream >> gmid;

        //read message
        QByteArray msg;
        inStream >> msg;

        Message message( this, messageType, 0, Message::Automatic );
        message.setMessage( msg );

        qDebug()<<"NetworkProtocol readData(): "<<message.messageData()<<msg <<message.type() <<message.gameID();
        emit messageReady( message );
    }
}

/**
 * \brief Creates and retuns a network packet ready to be sent
 * @param msg the message inside the packet
 * @param type the type of message
 * @param gameID the id of the game which the player is connected
 * @return QByteArray
 */
QByteArray NetworkProtocol::createPacket( const Message &msg ) const
{
    qDebug()<<"NetworkProtocol createPacket(): before creating: "<<msg.messageData();
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly );

    //inserting the protocol format and version in the packet`
    out<<format;
    out<<version;

    //inserting the message type and message itself in the packet
    out << msg.type();
    out << msg.gameID();
    out << msg.messageData();

    qDebug()<<"NetworkProtocol createPacket(): " <<packet /*<<"msg.messageData(): " <<msg.messageData()*/;
    qDebug()<<"NetworkProtocol createPacket(): " <<msg.messageData();
    return packet;
}

/**
 * \brief retuns the size of the packet in big-endian order which is the network order
 * @param packet const QByteArray
 * @return qint32
*/
qint32 NetworkProtocol::sizeOfPacket( const QByteArray &packet ) const
{
    return qToBigEndian( packet.size() );
}

/**
 * \brief retuns the value of the network protocol format
 * @return qint32
 */
qint32 NetworkProtocol::protocolFormat() const
{
    return format;
}

/**
 * \brief sets the protocol format
 * @param  qint32
 */
void NetworkProtocol::setProtocolFormat( qint32 fm )
{
    format = fm;
}

/**
 * \brief protocolVersion Property: sets the protocol version
 * @param vers qint32
 */
void NetworkProtocol::setProtocolVersion ( qint32 vers )
{
    version = vers;
}

/**
 * \brief protocolVersion Property: retuns the protocol version
 * @return qint32
 */
qint32 NetworkProtocol::protocolVersion() const
{
    return version;
}
QString NetworkProtocol::lastError() const
{
    return error;
}

