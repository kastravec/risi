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

#include "server/server.h"
#include "protocol.h"
#include "game.h"

Protocol *Protocol::inst = 0;

Protocol::Protocol()
{}

Protocol *Protocol::instance()
{
    if( inst == 0 )
        inst = new Protocol;

    return inst;
}

/**
 *
 * @param msg
 * @param msgType
 */
void Protocol::parseMessage( const QByteArray msg, const qint8 msgType/*, Game *game*/ )//TODO protocol
{
    qDebug()<<"message received to be parsed: " <<msg <<"type: " <<msgType;

    switch( msgType )
    {
        case Game:
        {
            break;
        }
        case Chat:
        {
            break;
        }
        case NickName:
        {
            break;
        }
        case HostRequest:
        {
            break;
        }
        case HostCancel:
        {
            break;
        }
        case JoinGame:
        {
            break;
        }
        case LeaveGame:
        {
            break;
        }
    }

}

