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

#include "connectionHandler.h"
#include "networkProtocol.h"
#include "protocol.h"
#include "message.h"
#include <QTcpSocket>

/**
 * \class ConnectionHandler
 *
 * \brief Default public constructor
 * initializes protocol format and protocol version
 * @param socket
 * @param parent
 */
ConnectionHandler::ConnectionHandler( QObject *parent, QTcpSocket *sock )
    :QObject( parent ), clientError(), client( sock ), networkProtocol( this, sock )
{
    protocol = qobject_cast< Protocol *> ( parent );
    if( client )
        setupConnections();
}

/**
 * \brief Destructor
 */
ConnectionHandler::~ConnectionHandler()
{}

/**
 * \brief this private functions helps in creating signal-slots connections
 * \internal
 */
void ConnectionHandler::setupConnections()
{
    qDebug()<<connect( client, SIGNAL( readyRead() ), &networkProtocol, SLOT(readData()) );

//     qDebug()<<connect( &networkProtocol, SIGNAL(messageReady(const QByteArray, const qint8, const qint8 )), this, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8 )));

    qDebug()<<connect( &networkProtocol, SIGNAL(messageReady(const Message&) ), this, SLOT(message(const Message&) ) );

    qDebug()<<connect( &networkProtocol, SIGNAL(networkProtocolError() ), this, SLOT(networkProtocolErrorSlot()) );

//TODO QAbstractSocket::SocketError is not a registered metatype, so for queued connections, you will have to register it with Q_REGISTER_METATYPE
    qDebug()<<connect( client, SIGNAL(error( QAbstractSocket::SocketError )), this,SLOT(socketErrors( QAbstractSocket::SocketError )) ) ;

    qDebug()<<connect( client, SIGNAL(stateChanged( QAbstractSocket::SocketState ) ), this, SLOT( socketStateChanged(QAbstractSocket::SocketState) ) );

    qDebug()<<connect( client, SIGNAL(disconnected()), this, SIGNAL(disconnectedFromServer()) );
    qDebug()<<connect( client, SIGNAL(connected()), this, SIGNAL(connectedToServer()) );
}

/**
 * \brief sends message to the other peer
 * @param msg the message
 * @param type type of message
 * @param gameID id of the game which the player is on
 */
qint64 ConnectionHandler::sendMessage( const Message &msg )
{
    QByteArray packet = networkProtocol.createPacket( msg );
    qint32 size = networkProtocol.sizeOfPacket( packet );

    //sending the packet size first
    client->write(reinterpret_cast<char*>(&size), sizeof(qint32));

    qDebug()<<"ConnectionHandler sendMessage(): " <<msg.messageData() <<msg.type() <<"packet: " <<packet;
    //sendind the packet itself
    qint64 ret = client->write(packet);

    return ret;
}

/**
 * \brief this slot is called everytime there is a network protocol error
 * @param err ServerNetworkProtocol::ProtocolError
 */
void ConnectionHandler::networkProtocolErrorSlot()//FIXME handle the error!
{
    qDebug()<<networkProtocol.lastError();
}

/**
 * \brief this slot is called everytime a socket error has occurred
 * @param errors QAbstractSocket::SocketError
 */
void ConnectionHandler::socketErrors( QAbstractSocket::SocketError errors)
{
    switch( errors )
    {
        case QAbstractSocket::ConnectionRefusedError:
        {
            qDebug()<<"QAbstractSocket::ConnectionRefusedError ";
            clientError = tr( "The connection was refused by the peer (or timed out) !" ) ;
            break;
        }
        case QAbstractSocket::RemoteHostClosedError:
        {
            qDebug()<<"QAbstractSocket::RemoteHostClosedError";
            clientError = tr( "connection was closed by remote host/client!" );
            break;
        }
        case QAbstractSocket::HostNotFoundError:
        {
            qDebug()<<"QAbstractSocket::HostNotFoundError";
            clientError = tr( " The host address was not found !" );
            break;
        }
        case QAbstractSocket::SocketAccessError:
        {
            qDebug()<<"QAbstractSocket::SocketAccessError";
            clientError = tr( "The socket operation failed because the application lacked the required privileges for accesing sockets !" );
            break;
        }
        case QAbstractSocket::SocketResourceError:
        {
            qDebug()<<"QAbstractSocket::SocketResourceError";
            clientError = tr( "The local system ran out of resources (e.g., too many sockets) !" );
            break;
        }
        case QAbstractSocket::SocketTimeoutError:
        {
            qDebug()<<"QAbstractSocket::SocketTimeoutError";
            clientError = tr( "The socket operation timed out !" );
            break;
        }
        case QAbstractSocket::DatagramTooLargeError:
        {
            qDebug()<<"QAbstractSocket::DatagramTooLargeError";
            clientError = tr( "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes) !" );
            break;
        }
        case QAbstractSocket::NetworkError:
        {
            qDebug()<<"QAbstractSocket::NetworkError";
            clientError = tr( "An error occurred with the network (e.g., the network cable was accidentally plugged out?)" );
            break;
        }
        case QAbstractSocket::AddressInUseError:
        {
            qDebug()<<"QAbstractSocket::AddressInUseError";
            clientError = tr("The address specified to QUdpSocket::bind() is already in use and was set to be exclusive !");
            break;
        }
        case QAbstractSocket::SocketAddressNotAvailableError:
        {
            qDebug()<<"QAbstractSocket::SocketAddressNotAvailableError";
            clientError = tr( "The address specified to QUdpSocket::bind() does not belong to the host ! " );
            break;
        }
        case QAbstractSocket::UnsupportedSocketOperationError:
        {
            qDebug()<<"QAbstractSocket::UnsupportedSocketOperationError";
            clientError = tr( "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support) ! " );
            break;
        }
        case QAbstractSocket::ProxyAuthenticationRequiredError:
        {
            qDebug()<<"QAbstractSocket::ProxyAuthenticationRequiredError";
            clientError = tr( "The socket is using a proxy, and the proxy requires authentication" );
            break;
        }
        case QAbstractSocket::UnknownSocketError:
        {
            qDebug()<<"QAbstractSocket::UnknownSocketError";
            clientError = tr("An unidentified error occurred !");
            break;
        }
        case QAbstractSocket::UnfinishedSocketOperationError:
        {
            qDebug()<<"QAbstractSocket::UnfinishedSocketOperationError";
            clientError = tr( "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background) !" );
            break;
        }
        default:
            qDebug()<<"some sort of error";
    }

}

/**
 * \brief this slot is called everytime the state of the socket changes
 * @param state QAbstractSocket::SocketState
 */
void ConnectionHandler::socketStateChanged( QAbstractSocket::SocketState state )
{
    switch( state )
    {
        case QAbstractSocket::UnconnectedState:
        {
            qDebug()<<"QAbstractSocket::UnconnectedState " <<client;
            break;
        }
        case QAbstractSocket::HostLookupState:
        {
            qDebug()<<"QAbstractSocket::HostLookupState" <<client;
            break;
        }
        case QAbstractSocket::ConnectingState:
        {
            qDebug()<<"QAbstractSocket::ConnectingState"<<client;
            break;
        }
        case QAbstractSocket::ConnectedState:
        {
            qDebug()<<"QAbstractSocket::ConnectedState"<<client;
            break;
        }
        case QAbstractSocket::BoundState:
        {
            qDebug()<<"QAbstractSocket::BoundState"<<client;
            break;
        }
        case QAbstractSocket::ClosingState:
        {
            qDebug()<<"QAbstractSocket::ClosingState" <<client;
            break;
        }
        case QAbstractSocket::ListeningState:
        {
            qDebug()<<"QAbstractSocket::ListeningState" <<client;
            break;
        }
        default:
            qDebug()<<"some sort of socket state" <<client;
    }

}

/**
 * \brief retuns the socket of the connection
 * @return const QTcpSocket *
 */
QTcpSocket * ConnectionHandler::socket() const
{
    return client;
}

/**
 * \brief
 * @param sock QTcpSocket *
 */
void ConnectionHandler::setSocket( QTcpSocket *sock )
{
    client = sock;
//     setupConnections();
}

/**
 * \brief retuns the last error of the connection
 * @return QString
 */
QString ConnectionHandler::lastError() const
{
    return clientError;
}

/**
 * \brief
 * @param msg
 * @param msgType
 * @param gameID
 */
void ConnectionHandler::message( const Message &msg )//FIXME this is just a workaround, has to be removed
{
    qDebug()<<"ConnectionHandler message(): " <<msg.messageData() <<msg.type();
    protocol->messageArrived( msg );
}
