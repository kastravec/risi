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
#include "serverprotocol.h"
#include "game.h"

/**
 * \class ServerProtocol
 * The class responsible for the game protocol
 * \brief Constructor
 */
ServerProtocol::ServerProtocol( QTcpSocket * client, QObject *parent  )
    :QObject( parent ), connectionHandler( parent, client )
{
    setupConnections();
}

/**
 * \brief
 */
ServerProtocol::~ServerProtocol()
{
}

/**
 * \brief
 * @param msg QByteArray
 * @param msgType qint8
 * @param gameID qint8
 */
void ServerProtocol::parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
    if( gameID == -1 )
        parseMessageForServer( msg, msgType );
    else
        parseMessageForGame( msg, msgType, gameID );
}

/**
 *\brief  parses the message arrived, typically this message is targeted for the Game. Hence, the parsing is limitted only for the Game
 * @param msg const QByteArray
 * @param msgType const qint8
 */
void ServerProtocol::parseMessageForGame( const QByteArray msg, const qint8 msgType, const qint8 gameID )//TODO protocol
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
void ServerProtocol::parseMessageForServer( const QByteArray msg, const qint8 msgType )
{
    switch( msgType )
    {
        case 'c'://chat message
        {
            qDebug()<<"message arrived in server: " <<msg <<msgType;
            Server::instance()->sendMessageToPlayers( msg );
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

void ServerProtocol::setupConnections()
{
    connect( &connectionHandler, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8 )), this, SLOT(parseMessage(const QByteArray, const qint8, const qint8 )) );
}

/**
 *
 * @param msg
 * @param nickName
 */
void ServerProtocol::sendChatMessage( const QString &msg, const QString &nick )
{
    QString message = msg;
    message.prepend( nick );
    int nickSize = nick.size();
    message.prepend( QString::number( nickSize ) );
    if( QString::number( nickSize ).size() != 2 )
        message.prepend( "/" );

    connectionHandler.sendMessage( message.toUtf8(), 'c', -1 );
}
