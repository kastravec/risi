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
#include "server.h"
#include "message.h"
#include <QTcpSocket>

/**
 * \class Protocol
 * \brief
 * @param parent QObject *
 * @param client QTcpSocket *
 */
Protocol::Protocol( QObject *parent, QTcpSocket * client )
    :QObject( parent ), connectionHandler( this, client )
{
//     if( client )
    setupSignalSlots();
}

/**
 * \brief
 */
Protocol::~Protocol()
{
}

/**
 * \brief
 * @param tcpSocket QTcpSocket *
 */
void Protocol::setTcpSocket( QTcpSocket *tcpSocket )
{
    connectionHandler.setSocket( tcpSocket );
    setupSignalSlots();
}

/**
 * \brief
 * @return QString
 */
QString Protocol::lastError() const
{
    return QString();
}

/**
 * \brief
 * @return QTcpSocket *
 */
QTcpSocket *Protocol::tcpSocket() const
{
    return connectionHandler.socket();
}

/**
 * \brief
 * @param msg const Message &
 */
void Protocol::sendMessage( const Message &msg )
{
    qDebug()<<"Protocol sendMessage(): " <<msg.messageData() <<msg.type() <<msg.parts();
    connectionHandler.sendMessage( msg );
}

/**
 * \brief
 * @param msg const QByteArray
 * @param msgType const qint8
 * @param gameID const qint8
 */
void Protocol::messageArrived( const Message &msg )
{
    qDebug()<<"Protocol messageArrived(): " <<msg.messageData() << msg.type() << msg.gameID();
    if( msg.gameID() == NOGAME )
        parseMessageForServer( msg );
    else
        parseMessageForGame( msg );
}

/**
 * \brief
 * \internal
 */
void Protocol::setupSignalSlots()
{
    connect( &connectionHandler, SIGNAL(messageArrived(const Message&) ), this, SLOT(messageArrived(const Message&) ) );
}

/**
 * \brief
 * \internal
 * @param msg
 * @param msgType
 */
void Protocol::parseMessageForServer( const Message &msg )
{
    switch( msg.type() )
    {
        case Message::Chat:
        {
            chatMessageArrived( msg );
            return;
        }
        case Message::NickName:
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

/**
 * \brief
 * \internal
 * @param msg
 * @param msgType
 * @param gameID
 */
void Protocol::parseMessageForGame( const Message &msg )
{
}

