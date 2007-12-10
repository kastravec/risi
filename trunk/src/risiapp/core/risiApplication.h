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

#ifndef RISIAPPLICATION_H
#define RISIAPPLICATION_H

class RISIui;
class HttpController;
class Server;
class PlayController;
class QStandardItemModel;
class QIODevice;

#include <QObject>

class RISIapplication: public QObject
{
    Q_OBJECT
    Q_ENUMS( AppState )
    Q_PROPERTY( QString nickname READ nickname WRITE setNickname SCRIPTABLE true USER true )
    Q_PROPERTY( AppState state READ state WRITE setState SCRIPTABLE true USER true )

    public:
        ~RISIapplication();

        enum AppState { Ready = 1, Busy = 2, Idle = 3, Problem = 4 };

        QString nickname() const;
        void setNickname( const QString & nm );
        AppState state() const;
        void setState( AppState st );

        void initUI();
        bool initServer();
        static RISIapplication* instance();
        void gameListXMLrequest( QStandardItemModel *m );
        void saveGameListXML( QStandardItemModel *m );
        void playerDisconnected( PlayController *playController );
        QList <QString> broadcastIPaddresses() const;
        qint16 serverPort() const;
        int numberOfConnectedPlayers() const;

    public slots:
        void connectToServer( const QString &ip, int port );
        void goOnlineSlot( const QString nickName, const bool onlineStatus );

    signals:
        void onlineStatusUpdate( bool onlineStatus );
        void serverStatusUpdate( bool serverStatus );

    private:
        RISIapplication( QObject *parent = 0 );
        void setupConnections();
        bool isConnectedTo(const QString &ip, int port );

        RISIui *risiUI;
        Server *server;
        HttpController *http;
        QList<PlayController *> playControllers;
        QString serverErrors;
        QIODevice *xmlFile;
        QString name;
        AppState appstate;

        static RISIapplication* inst;
};

#endif
