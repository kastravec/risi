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

#include "server/connectionHandler.h"
#include "server/server.h"

/**
 * Default public constructor
 * @param socket
 * @param parent
 */
ConnectionHandler::ConnectionHandler( QTcpSocket *socket , QObject *parent )
    :QTcpSocket( parent ), messageLength(0), messageType(0)
{
     //the data stream sent/recieved has the following format
    int streamFormat = 10;

    //the protocol version, hence it would be easier for future upgrades to the protocol`
    int protocolVersion = 11;

    client = socket;
}

/**
 * this private functions helps in creating signal-slots connections
 */
void ConnectionHandler::setupConnections()
{
    connect( client, SIGNAL( readyRead() ), this, SLOT( readReadyData() ) );
    connect( client, SIGNAL(disconnected()), this, SLOT(disconnected()) );

//TODO QAbstractSocket::SocketError is not a registered metatype, so for queued connections, you will have to register it with Q_REGISTER_METATYPE
    connect( client, SIGNAL(error( QAbstractSocket::SocketError )), this,SLOT(socketErrors( QAbstractSocket::SocketError )) ) ;

    connect( client, SIGNAL(stateChanged( QAbstractSocket::SocketState ) ), this, SLOT( socketStateChanged(QAbstractSocket::SocketState) ) );
}

/**
 * this slot is called when data are available for reading
 */
void ConnectionHandler::readReadyData()
{
    //init the stream with the socket of the connection
    QDataStream inStream( client );

    //make sure that there are available data to read
    if( client->bytesAvailable() < sizeof(int) )
        return;

    //read and check the protocol format
    int format;
    inStream >> format;
    if( format != protocolFormat )
    {
        protocolError( InvalidFormat );
        return;
    }

    //make sure that there are available data to read
    if( client->bytesAvailable() < sizeof(int) )
        return;

    //read and check the protocol version
    int version;
    inStream >> version;
    if( version != protocolVersion )
    {
        protocolError( InvalidVersion );
        return;
    }

    //make sure that there are available data to read
    if( client->bytesAvailable() < sizeof(char) )
        return;

    //read protocol header: the type of message
    inStream >> messageType;//TODO consider message types

    //make sure that there are available data to read
    if( client->bytesAvailable() < sizeof(qint16) )
        return;

    //read protocol header: the length of message
    inStream >> messageLength;

    //make sure that there are available data to read
    if( client->bytesAvailable() < messageLength )
        return;

    //read message
    QString message;
    inStream >> message;
    parseMessage( message );
}

/**
 * parses the message which is encapsulated in the protocol
 * @param msg
 */
void ConnectionHandler::parseMessage( QString msg )
{
    qDebug()<<"message received: " <<msg;
}

void ConnectionHandler::protocolError(ProtocolError error)
{
    switch( error )
    {
        case InvalidFormat:
        {
            qDebug()<<"invalid protocol format";
            break;
        }
        case InvalidVersion:
        {
            qDebug()<<"invalid protocol version";
            break;
        }
        default:
        {
            qDebug()<<"unkown protocol error";
        }
    }
}

void ConnectionHandler::disconnected()
{
    Server::instance()->playerDisconnected( this );
}

void ConnectionHandler::socketErrors( QAbstractSocket::SocketError errors)
{}

void ConnectionHandler::socketStateChanged( QAbstractSocket::SocketState state )
{}


