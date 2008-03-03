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
#include "risiApplication.h"

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

/**
 * \internal
 */
void ClientProtocol::setupConnections()
{
    connect( &tcpClient, SIGNAL(connectedToServer()), player, SLOT(tcpClientConnected()) );
    connect( &tcpClient, SIGNAL(disconnectedFromServer()), player, SLOT(tcpClientDisconnected()) );
}

/**
 * \brief connects to server with ip and port
 * @param ip const QString &
 * @param port int
 */
void ClientProtocol::connectToServer( const QString &ip, int port )
{
    if( ip.isEmpty() || port == 0 )
        return;
    tcpClient.connectToServer( ip, port );
}

void ClientProtocol::messageArrived( const Message &msg )
{
    if( msg.gameID() == NOGAME )
        parseServerTypeMessages( msg );
    else
        parseGameTypeMessages( msg );
}

void ClientProtocol::parseServerTypeMessages( const Message &msg )
{
    switch( msg.type() )
    {
        case Message::Chat:
        {
            player->displayChatMessage( msg.messageData() );
            return;
        }
        case Message::NickName:
        {
            if( msg.parts() == 1 )
                player->setNickConfirmation( msg.messagePartAt(0) );
            else
                player->setNickConfirmation( msg.messagePartAt(1) );

            break;
        }
        case Message::NickNameUpdateOther:
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

void ClientProtocol::parseGameTypeMessages( const Message &msg )
{
}

void ClientProtocol::updateNickOtherPlayer( const Message & msg )
{

}

