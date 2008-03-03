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
#include <QDebug>

/**
 * \class Message
 * \brief Default constructor
 * @param parent QObject *
 */
Message::Message( QObject *parent, int flag )
:QObject( parent ), messageType( NoType ), msgData(), msgParts( 0 ), partList(), gameid( NOGAME ), ready( false ), partFlag( static_cast<ContextPartFlag>(flag) )
{}

/**
 * \brief constructor
 * @param parent QObject *
 */
Message::Message( QObject *parent, char tp, int messageParts, int flag )
    :QObject( parent ), messageType( static_cast<MessageType>(tp) ), msgData(), msgParts( messageParts ), partList(), gameid( NOGAME ), ready( false ), partFlag( static_cast<ContextPartFlag> (flag) )
{
}

/**
 * \brief type property: Setter
 * @param tp MessageType
 */
void Message::setType( char tp )
{
    messageType = static_cast<MessageType> (tp);
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
    ready = false;
}

/**
 * \brief Appends the context part to the end of the context part list
 * @param part const QByteArray &
 */
void Message::addPart( const QByteArray &part )
{
    partList.append( QString( part ) );
    ready = false;
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
    switch( messageType )
    {
        case Chat: // 2|nickname:chatmsg
        {
            if( partFlag == Manual )
            {
                msgData.clear();
                msgData.append( partList.first() );
                msgData.append( PARTSEPARATOR );
                msgData.append( partList.last() );
                partList.clear();
            }
            break;
        }
        case NickName: // 1|nickname  ##  2|oldNick:newNick
        {
            prepareNickMessage();
            break;
        }
        case NickNameUpdateOther:// 2|oldNick:newNick oldNick can be empty which means that new player connected or new nick was not accepted
        {
            if( partFlag == Automatic )
            {
                int msgseparatorIndex = msgData.indexOf( MESSAGESEPARATOR );
                msgParts = 2;//TODO has to be 2 always !
                QByteArray msg1 = msgData.right( (msgData.count() - msgseparatorIndex) - 1 );
                int partseparatorIndex = msg1.indexOf( PARTSEPARATOR );
                partList.append( msg1.left( partseparatorIndex ) );
                partList.append( msg1.right( 1 ) );
            }
            else if( partFlag == Manual )
            {
                msgData.clear();
                msgData.append( msgParts );
                msgData.append( MESSAGESEPARATOR );
                msgData.append( partList.at( 0 ) );
                msgData.append( PARTSEPARATOR );
                msgData.append( partList.at( 1 ) );
            }
            break;
        }
    }

    ready = true;
}

/**
 * \brief Prepares messages of type NickName
 * \internal
 */
void Message::prepareNickMessage()
{
    if( partFlag == Manual )
    {
        msgData.clear();
        msgData.append( QString::number( msgParts ) );
        msgData.append( MESSAGESEPARATOR );
        for( int i = 0; i < msgParts; ++i )
        {
            if( i == 1 )
                msgData.append( PARTSEPARATOR );
            else
                msgData.append( partList.at( i ) );
        }
        partList.clear();//TODO do i have to clear the partlist?
    }
    else if( partFlag == Automatic )
    {
        int separatorIndex = msgData.indexOf( MESSAGESEPARATOR );
        msgParts = msgData.left( separatorIndex ).toInt();

        if( msgParts == 1 )
            partList.append( msgData.right( (msgData.count()-separatorIndex) - 1 ) );
        else if( msgParts == 2 )
        {
            int partseparatorIndex = msgData.indexOf( PARTSEPARATOR );
            QByteArray msg1 = msgData.right( (msgData.count() - separatorIndex) - 1 );
            int partIndex = (partseparatorIndex - separatorIndex) - 1;
            partList.append( msg1.left( partIndex ) );
            partList.append( msg1.right( partIndex ) );
        }
    }
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
void Message::setPartFlag( ContextPartFlag flag )
{
    partFlag = flag;
}

/**
 * \brief
 * @param msg const QByteArray &
 */
void Message::setMessage( const QByteArray &msg )
{
    msgData = msg;
}

/**
 * \brief
 * @param index int
 * @return QString
 */
QString Message::messagePartAt( int index ) const
{
    return partList.at( index );
}
