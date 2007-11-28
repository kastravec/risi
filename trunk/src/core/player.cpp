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

#include "core/protocol.h"
#include "player.h"
#include "server/server.h"
// // #include "game.h"

Player::Player( QTcpSocket *client, QObject *parent )
	:QObject( parent ), connectionHandler( client, this ), games(), nick( "player"+QString::number( client->socketDescriptor()*2 ) )
{
    setupConnections();
}

void Player::setupConnections()
{
    connect( &connectionHandler, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8 )), this, SLOT(messageArrivedSlot(const QByteArray, const qint8, const qint8 )) );

    connect( &connectionHandler, SIGNAL(disconnectMe()), this, SLOT(disconnected()) );
}

void Player::disconnected()
{
    qDebug()<<"disconnected slot" <<connectionHandler.lastError();

    Server::instance()->playerDisconnected( this, connectionHandler.lastError() );
}

void Player::messageArrivedSlot( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{

//     Protocol::instance()->parseMessage( msg, msgType, games.at( 0 )  ); //FIXME consider game id
}

