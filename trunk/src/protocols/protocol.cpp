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
        setupConnections();
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
    setupConnections();
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
 * @param oldNick QString &
 * @param newNick QString &
 */
void Protocol::sendUpdatedNickname( const QString &oldNick, const QString &newNick )
{
    connectionHandler.sendMessage( QString( oldNick + ESCAPENICKCHARACTER + newNick).toUtf8(), NickName, NOGAME );
}

/**
 * \brief
 * @param msg QByteArray &
 */
void Protocol::sendChatMessage( const QByteArray &msg )
{
    sendChatMessage( QString( msg ) );
}

/**
 * \brief
 * @param msg const QString &
 * @param nick const QString &
 */
void Protocol::sendChatMessage( const QString &msg, const QString &nick )
{
    qDebug()<<"sending message " <<msg <<nick <<"from: " <<connectionHandler.socket();
    qint64 returnValue;

    if( !nick.isEmpty() )
         returnValue = connectionHandler.sendMessage( prepareChatMessage(msg, nick).toUtf8(), Protocol::Chat, NOGAME );
    else
        returnValue = connectionHandler.sendMessage( msg.toUtf8() , Protocol::Chat, NOGAME );

    if( returnValue == -1 )
        qDebug()<<"error while sendind data";
    else
        qDebug()<<returnValue << "bytes of data sent from : "<<connectionHandler.socket() ;
}

/**
 * \brief
 * @param msg const QString &
 * @param nick const QString &
 * @return
 */
QString Protocol::prepareChatMessage( const QString &msg, const QString &nick ) const
{
    QString message = msg;
    message.prepend( ": " );
    message.prepend( nick );
    int nickSize = nick.size();
    message.prepend( QString::number( nickSize ) );
    if( QString::number( nickSize ).size() != 2 )
        message.prepend( ESCAPECHATCHARACTER );

    return message;
}

/**
 * \brief
 * @param msg const QByteArray
 * @param msgType const qint8
 * @param gameID const qint8
 */
void Protocol::parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
    qDebug()<<"parseMessage " <<msg << msgType << gameID ;
    if( gameID == NOGAME )
        parseMessageForServer( msg, msgType );
    else
        parseMessageForGame( msg, msgType, gameID );
}

/**
 * \brief
 * \internal
 */
void Protocol::setupConnections()
{
    connect( &connectionHandler, SIGNAL(messageArrived(const QByteArray, const qint8, const qint8 )), this, SLOT(parseMessage(const QByteArray, const qint8, const qint8 )) );

}

/**
 * \brief
 * \internal
 * @param msg
 * @param msgType
 */
void Protocol::parseMessageForServer( const QByteArray msg, const qint8 msgType )
{
    switch( msgType )
    {
        case Chat:
        {
            chatMessageArrived( msg );
            return;
        }
        case NickName:
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
void Protocol::parseMessageForGame( const QByteArray msg, const qint8 msgType, const qint8 gameID )
{
}

