/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci   *
 *   psaraci@gmail.com   *
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

#include <QSettings>

#include "player.h"
#include "server.h"

Server *Server::inst = 0;

/**
 * \class Server
 * \brief Private default constructor
 * @param parent
 */
Server::Server( QObject *parent )
    :QTcpServer(parent), hostedGames(), games(), connectedPlayers(), upDown( false )
{
    connect( this, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()) );
}

/**
 * \brief returns the instance of Server, singleton pattern
 * @return Server*
 */
Server * Server::instance()
{
    if( inst == 0)
        inst = new Server;

    return inst;
}

/**
 * \brief
 * @param online
 */
void Server::updateOnlineStatus( const bool online )
{

}

/**
 * \brief this slot is called for every new incoming connection
 * \internal
 */
void Server::newConnectionSlot()
{
        while( hasPendingConnections() )
        {
            QTcpSocket *newConnection = nextPendingConnection();
            //add a the socket and the connection handeler for that socket in a map
            connectedPlayers[ newConnection ] = new Player( newConnection, this );
        }
}

/**
 * \brief this function removes a connection which was dropped/disconnected
 * @param handler
 */
void Server::playerDisconnected( Player *player, const QString &err )
{
    connectedPlayers.remove( const_cast<QTcpSocket *>( player->connectionSocket() ) );
    player->deleteLater();
}

/**
 * \brief
 * @return QMap
 */
QMap <QTcpSocket *, Player *> Server::players() const
{
    return connectedPlayers;
}

/**
 * \brief returns the number of connected players
 * @return int
 */
int Server::numberOfConnectedPlayers() const
{
    return connectedPlayers.count();
}

/**
 * \brief
 * @return QString
 */
QString Server::lastError() const
{
    switch( serverError() )
    {
        case QAbstractSocket::ConnectionRefusedError:
        {
            return tr("Server problem: The connection was refused by the peer (or timed out) !" );
        }
        case QAbstractSocket::RemoteHostClosedError:
        {
            return tr("Server problem: connection was closed by remote host/client!" );
        }
        case QAbstractSocket::HostNotFoundError:
        {
            return tr("Server problem: The host address was not found !" );
        }
        case QAbstractSocket::SocketAccessError:
        {
           return tr("Server problem: Server could not be started: Please change the server port in the settings and restart the application. It is recommended to use >1500 ! ");
        }
        case QAbstractSocket::SocketResourceError:
        {
            return tr("Server problem: The local system ran out of resources (e.g., too many sockets) !" );
        }
        case QAbstractSocket::SocketTimeoutError:
        {
            return tr("Server problem: The socket operation timed out !" );
        }
        case QAbstractSocket::DatagramTooLargeError:
        {
            return tr("Server problem: The datagram was larger than the operating system's limit (which can be as low as 8192 bytes) !" );
        }
        case QAbstractSocket::NetworkError:
        {
            return tr("Server problem: An error occurred with the network (e.g., the network cable was accidentally plugged out?)" );
        }
        case QAbstractSocket::AddressInUseError:
        {
            return tr("Server problem: The address specified to QUdpSocket::bind() is already in use and was set to be exclusive !" );
        }
        case QAbstractSocket::SocketAddressNotAvailableError:
        {
            return tr("Server problem: The address specified to QUdpSocket::bind() does not belong to the host ! " );
        }
        case QAbstractSocket::UnsupportedSocketOperationError:
        {
            return tr("Server problem: The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support) ! " );
        }
        case QAbstractSocket::ProxyAuthenticationRequiredError:
        {
            return tr("Server problem: The socket is using a proxy, and the proxy requires authentication" );
        }
        case QAbstractSocket::UnknownSocketError:
        {
            return tr("Server problem: "), tr("An unidentified error occurred !" );
        }
        case QAbstractSocket::UnfinishedSocketOperationError:
        {
            return tr("Server problem: Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background) !" );
        }
        default:
            return tr("Server problem: some sort of error" );
    }
}

/**
 *
 * @param msg
 * @param msgType
 */
void Server::sendMessageToPlayers( const QByteArray msg ) const
{
    QMapIterator<QTcpSocket *, Player *> i(connectedPlayers);
    while (i.hasNext())
    {
        i.next();
        i.value()->sendChatMessage( msg );
    }
}

