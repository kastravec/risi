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

#ifndef PLAYCONTROLER_H
#define PLAYCONTROLER_H

#include <QObject>
#include "tcpClient.h"
#include "board.h"
#include "clientprotocol.h"

class RISIui;
class Message;

class PlayController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool connected READ isConnected )

    public:
        PlayController( QObject *parent = 0, RISIui *ui = 0, const QString &ip = QString(), int pt = 0 );
        ~PlayController();

        bool isConnected() const;
        void displayChatMessage( const QString &msg );
        void setNickConfirmation( const QString &nick );
        QString lastTcpError() const;
        QString serverIP() const;
        qint16 serverPort() const;
        QStringList players() const;
        void setNickName( const QString &oldNick, const QString &newNick );

    public slots:
        void sendMessage( const Message &msg );
        void tcpClientConnected();
        void tcpClientDisconnected();

    signals:
        void nickNameChanged( const QString &oldNick, const QString &newNick );

    private:
        void setupConnections();

        Board board;
        RISIui *risiUI;
        ClientProtocol protocol;
        int gameID;
        bool connectedToServer;
        QString ipAddress;
        qint16 port;
        QStringList playersOnServer;
};

#endif
