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

#include "server.h"
#include "protocol.h"
#include "game.h"

Protocol *Protocol::inst = 0;

/**
 * \class Protocol
 * The class responsible for the game protocol
 * \brief Constructor
 */
Protocol::Protocol()
    :server( Server::instance() )
{}

/**
 * \brief returns the instance of Protocol
 * @return Protocol *
 */
Protocol *Protocol::instance()
{
    if( inst == 0 )
        inst = new Protocol;

    return inst;
}

/**
 *\brief  parses the message arrived, typically this message is targeted for the Game. Hence, the parsing is limitted only for the Game
 * @param msg const QByteArray
 * @param msgType const qint8
 */
void Protocol::parseMessageForGame( const QByteArray msg, const qint8 msgType, Game *game )//TODO protocol
{
    switch( msgType )
    {
        case 'g': //GameMsg
        {
            break;
        }
        case 'c': //chat
        {
            break;
        }
        case 'a': //Leave game
        {
            break;
        }
    }

}

/**
 * \brief parses the message arrived, typically this message is target for the Server. Hence, the parsing is limitted only for the Server
 * @param msg const QByteArray
 * @param msgType const qint8
 */
void Protocol::parseMessageForServer( const QByteArray msg, const qint8 msgType )
{
    switch( msgType )
    {
        case 'c'://chat message
        {
            qDebug()<<"looks fine ";
            server->setMessageToPlayers( msg, 'c' );
            break;
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
