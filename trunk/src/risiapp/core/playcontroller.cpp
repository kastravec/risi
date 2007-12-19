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

#include "playcontroller.h"
#include "risiUI.h"
#include "risiApplication.h"
#include "message.h"

/**
 * \class PlayController
 * \brief Constructor
 * @param parent QObject
 * @param ip const QString &
 * @param port int
 */
PlayController::PlayController( QObject *parent, RISIui *ui, const QString &ip, int pt )
    :QObject( parent ), board( this ), risiUI( ui ), protocol( this ), gameID( -1 ), connectedToServer( false ), ipAddress( ip ), port( pt )
{
    setupConnections();
    protocol.connectToServer( ip, port );
}

/**
 * \brief
 */
PlayController::~PlayController()
{
}

bool PlayController::isConnected() const
{
    return connectedToServer;
}

/**
 * \brief
 * \internal
 */
void PlayController::setupConnections()
{
}

/**
 * \brief returns the last error occured on PlayController
 * @return QString
 */
QString PlayController::lastTcpError() const
{
    return protocol.lastError();
}

/**
 * \brief
 * @return QString
 */
QString PlayController::serverIP() const
{
    return ipAddress;
}

/**
 * \brief
 * @return qint16
 */
qint16 PlayController::serverPort() const
{
    return port;
}

/**
 * \brief
 * \internal
 */
void PlayController::tcpClientConnected()
{
    connectedToServer = true;
}

/**
 * \brief
 * \internal
 */
void PlayController::tcpClientDisconnected()
{
    connectedToServer = false;
}

/**
 * \brief
 * @param msg const Message &
 */
void PlayController::sendMessage( const Message &msg )
{
    qDebug()<<"PlayController sendMessage(): "<<msg.messageData();
    protocol.sendMessage( msg );
}

/**
 * \brief
 * @param msg QString
 */
void PlayController::displayChatMessage( const QString &msg )
{
    risiUI->displayChatMessage( msg );
}
