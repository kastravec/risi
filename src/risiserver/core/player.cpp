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

#include "protocol.h"
#include "player.h"
#include "server.h"
#include "game.h"


/**
 * \class Player
 * \brief Constructor
 * @param client This is the socket of the connection for the player
 * @param parent Parent
 */
Player::Player( QTcpSocket *client, QObject *parent )
    :QObject( parent ), connectionHandler( client, this ), games(), nick( "player"+QString::number( client->socketDescriptor()*2 ) ), protocol( Protocol::instance() )
{
    setupConnections();
}

/**
 * \brief creates SIGNAL-SLOTs connections for Player instances
 * \internal
 */
void Player::setupConnections() const
{
    connect( &connectionHandler, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8 )), this, SLOT(messageArrivedSlot(const QByteArray, const qint8, const qint8 )) );

    connect( &connectionHandler, SIGNAL(disconnectMe()), this, SLOT(disconnected()) );
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
void Player::disconnected()
{
    qDebug()<<"disconnected slot" <<connectionHandler.lastError();

    Server::instance()->playerDisconnected( this, connectionHandler.lastError() );
}

/**
 *  \brief this slot is called when a message arrives from the player
 * @param msg The arrived message
 * @param msgType the type of the arrived message
 * @param gameID gameID is the id of which game this player is connected
 */

/**
 * \brief this slot is called everytime a message arrives for the player
 * @param msg QByteArray the arrived message
 * @param msgType qint8 type of the message
 * @param gameID qint8
 */
void Player::messageArrivedSlot( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
    Game * game = gameForID( gameID );
    if( game )
        protocol->parseMessageForGame( msg, msgType, game );
    else
        protocol->parseMessageForServer( msg, msgType );
}

/**
 * \brief returns the socket of the connection
 * @return QTcpSocket socket of the connection
 */
const QTcpSocket * Player::connectionSocket()
{
    return connectionHandler.socket();
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

void Player::sendMessage( const QByteArray msg, const qint8 msgType )
{
    connectionHandler.sendMessage( msg, msgType, -1 );
}
