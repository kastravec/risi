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
ServerProtocol::ServerProtocol( QTcpSocket * client, QObject *parent  )
    :Protocol( parent, client )
{}

/**
 * \brief
 */
ServerProtocol::~ServerProtocol()
{
}

/**
 * \brief
 * @param msg QString
 */
void ServerProtocol::chatMessageArrived( const Message &msg ) const
{
    qDebug()<<"ServerProtocol chatMessageArrived(): " <<connectionHandler.socket() <<"msg: "<<msg.messageData();
    QMapIterator<QTcpSocket *, Player *> iterator( Server::instance()->players() );
    while (iterator.hasNext())
    {
        iterator.next();
        iterator.value()->sendMessage( msg );
    }
}

/**
 * \brief
 * @param msg const QByteArray &
 */
void ServerProtocol::nickNameMessageArrived( const Message & msg ) const
{
/*
    QString newNick( msg );

    QMapIterator<QTcpSocket *, Player *> iterator( Server::instance()->players() );
    while (iterator.hasNext())
    {
        iterator.next();
        if ( iterator.value()->nickname() == newNick )
            break;
    }

    iterator.toFront();

    while (iterator.hasNext())
    {
        iterator.next();
        iterator.value()->sendUpdatedNick( msg );
    }
    */
}
