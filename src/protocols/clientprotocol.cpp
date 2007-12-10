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

#include "clientprotocol.h"
#include "playcontroller.h"

/**
 * \class Constructor
 * \brief Constructor
 * \internal private
 */
ClientProtocol::ClientProtocol( PlayController *pl )
    :player( pl ), tcpClient( player )
{
    setupConnections();
}

/**
 * \brief
 */
ClientProtocol::~ClientProtocol()
{
}

void ClientProtocol::setupConnections()
{
    connect( &tcpClient, SIGNAL(connectedToServer()), player, SLOT(tcpClientConnected()) );
    connect( &tcpClient, SIGNAL(disconnectedFromServer()), player, SLOT(tcpClientDisconnected()) );
    connect( &tcpClient, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8)), this, SLOT(parseMessage(const QByteArray, const qint8, const qint8)) );
}

void ClientProtocol::connectToServer( const QString &ip, int port )
{
    if( ip.isEmpty() || port == 0 )
        return;
    tcpClient.connectToServer( ip, port );
}

/**
 * \brief
 */
void ClientProtocol::sendNickName( const QString &name )
{
    tcpClient.sendMessage( name.toUtf8(), 'n', '-1' );
}

void ClientProtocol::sendChatMessage( const QString &msg, const QString &nick )
{
    QString message = msg;
    message.prepend(nick);
    int nickSize = nick.size();
    message.prepend( QString::number( nickSize ) );
    if( QString::number( nickSize ).size() != 2 )
        message.prepend( "/" );

    tcpClient.sendMessage( message.toUtf8(), 'c', -1 );
}

/**
 * \brief
 * \internal
 * @param msg QByteArray
 * @param msgType qint8
 */
void ClientProtocol::parseServerMessage( const QByteArray msg, const qint8 msgType )
{
    switch( msgType )
    {
        case 'c'://chat message
        {
            player->displayChatMessage( msg );
            return;
        }
        case 'n': //HostRequest
        {
            break;
        }
        case 'h': //HostRequest
        {
            break;
        }
        case 'l': //HostCancel
        {
            break;
        }
        case 'j': //JoinGame
        {
            break;
        }
        default:
            break;
    }
}

/**
 * \brief
 * @param msg QString
 * @param msgType qint8
 * @param gameID qint8
 */
void ClientProtocol::parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
    qDebug()<<"message from server recieved: " <<msg <<gameID;
    if( gameID == -1 )
        parseServerMessage( msg, msgType );
    else
        parseGameMessage( msg, msgType, gameID );
}

/**
 * \brief
 * \internal
 * @param msg QByteArray
 * @param msgType qint8
 * @param gameID qint8
 */
void ClientProtocol::parseGameMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
}

QString ClientProtocol::lastError() const
{
    return tcpClient.lastError();
}
