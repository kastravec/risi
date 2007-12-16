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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include "connectionHandler.h"

static const int NOGAME = 0;
static const char ESCAPECHATCHARACTER = '/';
static const char ESCAPENICKCHARACTER = '|';
class QTcpSocket;

class Protocol: public QObject
{
    Q_OBJECT

    public:
        Protocol( QObject *parent = 0, QTcpSocket * client = 0 );
        virtual ~Protocol();

        enum MessageType{
                            GameMsg = 'g',
                            Chat = 'c',
                            NickName = 'n',
                            HostRequest = 'h',
                            HostCancel = 'l',
                            JoinGame = 'j',
                            LeaveGame = 'a'
                        };

        QTcpSocket *tcpSocket() const;
        QString lastError() const;
        void sendUpdatedNickname( const QString &oldNick, const QString &newNick );
        void sendChatMessage( const QString &msg, const QString &nick = QString() );
        void sendChatMessage( const QByteArray &msg );

    protected:
        virtual QString prepareChatMessage( const QString &msg, const QString &nick ) const;
        virtual void chatMessageArrived( const QByteArray & msg ) const = 0;
        virtual void nickNameMessageArrived( const QByteArray & msg ) const = 0 ;

        void setTcpSocket( QTcpSocket *tcpSocket );
        ConnectionHandler connectionHandler;

    public slots:
        void parseMessage( const QByteArray msg, const qint8 msgType, const qint8 gameID );

    private:
        void parseMessageForServer( const QByteArray msg, const qint8 msgType );
        void parseMessageForGame( const QByteArray msg, const qint8 msgType, const qint8 gameID );
        void setupConnections();
};

#endif
