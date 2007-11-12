/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci   *
 *   psaraci@gmail.com   *
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

#include <QSettings>

#include "server.h"

Server *Server::inst = 0;

/**
 * Private default constructor
 * @param parent
 */
Server::Server( QObject *parent )
    :QTcpServer(parent), hostedGames(), connections(), games()
{
    connect( this, SIGNAL(newConnection()), this, SLOT(newPlayerConnection()) );
}

/**
 * returns the instance of Server, singleton pattern
 * @return Server*
 */
Server * Server::instance()
{
    if( inst == 0)
        inst = new Server;

    return inst;
}

void Server::readSettings()
{
    QSettings settings;
}

void Server::writeSettings()
{
    QSettings settings;
}

void Server::hostGame(const QString &gameName)
{
    if( !gameName.isEmpty() )
        qDebug()<<gameName;
}

/**
 * this slot is called for every new incoming connection
 */
void Server::newPlayerConnection()
{
        while( hasPendingConnections() )
        {
            QTcpSocket *newConnection = nextPendingConnection();
            ConnectionHandler *newConnectionHandler = new ConnectionHandler( newConnection, this );

            //add a the socket and the connection handeler for that socket in a map
            connections[ newConnection ] = newConnectionHandler;

            //for every message arrived, the connection handler will emit a signal to notify server to emit its signal
            connect ( newConnectionHandler, SIGNAL(messageArrived(const QString) ), this, SIGNAL(messageArrived(const QString)) );
        }
}

/**
 * this function removes a connection which was dropped/disconnected
 * @param handler
 */
void Server::playerDisconnected( ConnectionHandler *handler, QString err )
{
    connections.remove( handler->socket() );
    handler->deleteLater();

    if( ! err.isNull() )
        emit playerDisconnectedSignal( err );
}
