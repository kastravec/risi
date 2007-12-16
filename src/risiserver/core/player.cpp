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

#include "player.h"
#include "server.h"
#include "game.h"
#include <QTcpSocket>


/**
 * \class Player
 * \brief Constructor
 * @param client This is the socket of the connection for the player
 * @param parent Parent
 */
Player::Player( QTcpSocket *client, QObject *parent )
    :QObject( parent ), games(), nick( "player"+QString::number( client->socketDescriptor()*2 ) ), protocol( client, this )
{
    setupConnections();
}

/**
 *
 */
Player::~Player()
{
}

/**
 * \brief creates SIGNAL-SLOTs connections for Player instances
 * \internal
 */
void Player::setupConnections() const
{
}

/**
 * \brief finds and returns the game with the given id
 * \internal
 * @param iD qint8
 * @return Game *
 */
Game * Player::gameForID( qint8 iD )
{
    if( iD == -1 )
        return 0;

    for( int i = 0; i < games.count(); ++i )
    {
        if( games.at( i )->id() == iD )
            return games.at( i );
    }

    return 0;
}


/**
 * \brief this slot is called when the player is disconnected from the server, check lastError()
 */
void Player::disconnected() //FIXME
{
//     Server::instance()->playerDisconnected( this, connectionHandler.lastError() );
}

/**
 * \brief returns the socket of the connection
 * @return QTcpSocket socket of the connection
 */
QTcpSocket * Player::connectionSocket() const
{
    return protocol.tcpSocket();
}

/**
 * \brief add the game which the player joined
 * @param gm Game
 * @return void
 */
void Player::addGame( Game *gm )
{
    games.append( gm );
}

/**
 * \brief nickname Property: returns the nickname of the player
 * @return QString nickName
 */
QString Player::nickname() const
{
    return nick;
}

/**
 * \brief nickname Property: sets the nickname for the player
 * @param
 */
void Player::setNickname( const QString & name )
{
    nick = name;
}

/**
 * \brief
 * @param msg QByteArray
 * @param msgType qint8
 */
void Player::sendChatMessage( const QByteArray msg )
{
    protocol.sendChatMessage( msg );
}

/**
 * \brief
 */
void Player::sendUpdatedNick( const QByteArray &nick ) const
{

}
