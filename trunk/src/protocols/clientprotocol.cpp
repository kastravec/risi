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
#include "message.h"

/**
 * \class Constructor
 * \brief Constructor
 * \internal private
 */
ClientProtocol::ClientProtocol( PlayController *pl )
    :Protocol( pl, 0 ), player( pl ), tcpClient( this )
{
    setTcpSocket( tcpClient.socket() );
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
// //     Protocol::setupConnections();
//     connect( &connectionHandler, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8)), this, SLOT(messageArrived(const QByteArray, const qint8, const qint8)) );
    connect( &tcpClient, SIGNAL(connectedToServer()), player, SLOT(tcpClientConnected()) );
    connect( &tcpClient, SIGNAL(disconnectedFromServer()), player, SLOT(tcpClientDisconnected()) );
}

void ClientProtocol::connectToServer( const QString &ip, int port )
{
    if( ip.isEmpty() || port == 0 )
        return;
    tcpClient.connectToServer( ip, port );
}

/**
 * \brief
 * @param msg const Message &
 */
void ClientProtocol::chatMessageArrived( const Message &msg ) const
{
    qDebug()<<"chatMessageArrived at client : "<<msg.messageData();
/*    QString nickSize = message.left(2);

    if( nickSize.contains( ESCAPECHATCHARACTER ) )
    {
        nickSize.remove( 0,1 );
        message.remove( 0, 2 );
        message =
    }*/

    player->displayChatMessage( msg.messageData() );
}

/**
 * \brief
 * @param msg const Message &
 */
void ClientProtocol::nickNameMessageArrived( const Message & msg ) const
{
}

