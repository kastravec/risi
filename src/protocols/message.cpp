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

#include "message.h"

/**
 * \class Message
 * \brief Default constructor
 * @param parent QObject *
 */
Message::Message( QObject *parent, int flag )
:QObject( parent ), messageType( NoType ), msgData(), msgParts( 0 ), partList(), ready( false ), partFlag( flag )
{}

/**
 * \brief constructor
 * @param parent QObject *
 */
Message::Message( QObject *parent, int tp, int messageParts )
:QObject( parent ), messageType( static_cast<MessageType>(tp) ), msgData(), msgParts( messageParts ), partList(), ready( false ), partFlag( Manual )
{
}

/**
 * \brief type property: Setter
 * @param tp MessageType
 */
void Message::setType( qint tp )
{
    messageType = tp;
}

/**
 * \brief gameID property
 * @return
 */
qint8 Message::gameID() const
{
    return gameid;
}

/**
 * \brief gameID property
 * @param gmid
 */
void Message::setGameID( qint8 gmid )
{
    gameid = gmid;
}

/**
 * \brief type property: Getter
 * @return MessageType
 */
char Message::type() const
{
    return messageType;
}

/**
 * \brief messageData property: This is a ready-to-send data
 * @return QByteArray
 */
QByteArray Message::messageData() const
{
    return msgData;
}

/**
 * \brief parts property: A message contains different context parts. This property specifies how many context parts the message has
 * @return int
 */
int Message::parts() const
{
    return msgParts;
}

/**
 * \brief parts property: A message contains different context parts. This property specifies how many context parts the message has
 * @param p int
 */
void Message::setNumberOfParts( int p )
{
    msgParts = p;
}

/**
 * \brief Appends the context part to the end of the context part list
 * @param part const QString &
 */
void Message::addPart( const QString &part )
{
    partList.append( part );
}

/**
 * \brief Appends the context part to the end of the context part list
 * @param part const QByteArray &
 */
void Message::addPart( const QByteArray &part )
{
    partList.append( QString( part ) );
}

/**
 * \brief Inserts a context part at position 'index' of the list of context parts
 * @param index int
 * @param part const QString &
 */
void Message::insertPart( int index, const QString &part )
{
    partList.insert( index, part );
}

/**
 * \brief
 * @param list const QStringList &
 */
void Message::setPartList( const QStringList &list )
{
    partList = list;
}

/**
 * \brief preparing the message before sending it
 * \internal
 */
void Message::prepareMessage()
{
/*
    QString message = msg;
    message.prepend( ": " );
    message.prepend( nick );
    int nickSize = nick.size();
    message.prepend( QString::number( nickSize ) );
    if( QString::number( nickSize ).size() != 2 )
        message.prepend( ESCAPECHATCHARACTER );*/


    msgData.clear();

    for( int i = 0; i < partList.count(); ++i )
        msgData.append( partList.at( i ) );

    ready = true;
}

/**
 * \brief returns TRUE if message is ready to be sent otherwise returns FALSE
 * @return bool
 */
bool Message::isMessageReady()
{
    return ready;
}

/**
 * \brief
 * @param flag int
 */
void Message::setPartFlag( int flag )
{
    partFlag = flag;
}

