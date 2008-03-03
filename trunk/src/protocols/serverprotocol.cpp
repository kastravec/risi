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
#include "serverprotocol.h"
#include "player.h"
#include "server.h"
#include "message.h"

/**
 * \class ServerProtocol
 * The class responsible for the game protocol
 * \brief Constructor
 */
ServerProtocol::ServerProtocol( Player *parent, QTcpSocket * client )
    :Protocol( parent, client ), player( parent )
{}

/**
 * \brief
 */
ServerProtocol::~ServerProtocol()
{
}

void ServerProtocol::nickNameMessageArrived( QObject *sender, const Message & msg )
{
    bool keepNewNick = false;
    int msgParts = msg.parts();
    QString newNick;
    QString oldNick = player->nickname();
    QMapIterator<QTcpSocket *, Player *> iterator( Server::instance()->players() );
    Message newMsg( this, Message::NickNameUpdateOther, 2, Message::Manual );
    Message oldNikcMsg( this, Message::NickName, 1, Message::Manual );

    if( msgParts == 1 )
        newNick = msg.messagePartAt( 0 );
    else
        newNick = msg.messagePartAt( 1 );

    while (iterator.hasNext())
    {
        iterator.next();
        if ( iterator.value()->nickname() == newNick )
        {
            keepNewNick = true;
            break;
        }
    }

    if( keepNewNick )
    {
        //if keeping the new nick then just resend the same msg back
        player->setNickname( newNick );
        player->sendMessage( msg );

        if( msgParts == 1 )
        {
            newMsg.addPart( QString("") );
            newMsg.addPart( newNick );
        }
        else
        {
            newMsg.addPart( oldNick );
            newMsg.addPart( newNick );
        }
    }
    else
    {
        oldNikcMsg.addPart( oldNick );
        oldNikcMsg.prepareMessage();
        player->sendMessage( oldNikcMsg );

        newMsg.addPart( QString("") );
        newMsg.addPart( oldNick );
    }

    newMsg.prepareMessage();
    iterator.toFront();
    while (iterator.hasNext() )
    {
        iterator.next();
        if( iterator.value()->nickname() != newNick )
            iterator.value()->sendMessage( newMsg );
    }
}

void ServerProtocol::messageArrived( const Message &msg )
{
    if( msg.gameID() == NOGAME )
        parseServerTypeMessages( msg );
    else
        parseGameTypeMessages( msg );
}

void ServerProtocol::parseServerTypeMessages( const Message &msg )
{
    switch( msg.type() )
    {
        case Message::Chat:
        {
            QMapIterator<QTcpSocket *, Player *> iterator( Server::instance()->players() );
            while (iterator.hasNext())
            {
                iterator.next();
                iterator.value()->sendMessage( msg );
            }
            return;
        }
        case Message::NickName:
        {
            nickNameMessageArrived( parent(), msg );
            break;
        }
        case Message::Connected:
        {
//             playerConnectedMessage( msg );
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

void ServerProtocol::parseGameTypeMessages( const Message &msg )
{
}

