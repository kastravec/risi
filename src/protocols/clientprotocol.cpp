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
 */
void ClientProtocol::sendNickName( const QString &name )
{
    tcpClient.sendMessage( name.toUtf8(), NickName, NOGAME );
}

/**
 * \brief
 * @param msg QByteArray &
 */
void ClientProtocol::chatMessageArrived( const QByteArray &msg ) const
{
    QString message( msg );

/*    QString nickSize = message.left(2);

    if( nickSize.contains( ESCAPECHATCHARACTER ) )
    {
        nickSize.remove( 0,1 );
        message.remove( 0, 2 );
        message =
    }*/

    player->displayChatMessage( message.remove( 0, 2) );
}

/**
 * \brief
 * @param msg const QByteArray &
 */
void ClientProtocol::nickNameMessageArrived( const QByteArray & msg ) const
{
}

