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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QByteArray>
#include <QStringList>

static const qint8 NOGAME = 0;
static const char PARTSEPARATOR = ':';
static const char MESSAGESEPARATOR = '|';

class Message: public QObject
{
    Q_ENUMS( MessageType )
    Q_PROPERTY( MessageType type READ type WRITE setType SCRIPTABLE true USER true )
    Q_PROPERTY( qint8 gameID READ gameID WRITE setGameID SCRIPTABLE true USER true )
    Q_PROPERTY( int parts READ parts WRITE setNumberOfParts SCRIPTABLE false USER true )
    Q_PROPERTY( QByteArray messageData READ messageData SCRIPTABLE true USER true )

    public:
        Message( QObject *parent = 0, int flag = Automatic );
        Message( QObject *parent = 0, char tp = NoType, int messageParts = 0, int flag = Automatic );

        enum ContextPartFlag { Automatic = 1, Manual = 0 };
        enum MessageType
            {
                Connected = 'o',
                GameMsg = 'g',
                Chat = 'c',
                NickName = 'n',
                NickNameUpdateOther = 'm',
                HostRequest = 'h',
                HostCancel = 'l',
                JoinGame = 'j',
                LeaveGame = 'a',
                NoType = 'x'
            };

        char type() const;
        void setType( char tp );
        qint8 gameID() const;
        void setGameID( qint8 gmid );
        int parts() const;
        void setNumberOfParts( int p );
        QByteArray messageData() const;
        void addPart( const QString &part );
        void addPart( const QByteArray &part );
        void insertPart( int index, const QString &part );
        void setPartList( const QStringList &list );
        bool isMessageReady();
        void prepareMessage();
        void setPartFlag( ContextPartFlag flag );
        void setMessage( const QByteArray &msg );
        QString messagePartAt( int index ) const;

    private:
        void prepareNickMessage();

        MessageType messageType;
        QByteArray msgData;
        int msgParts;
        QStringList partList;
        qint8 gameid;
        bool ready;
        ContextPartFlag partFlag;
};

// Q_DECLARE_METATYPE( Message )

#endif
