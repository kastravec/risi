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

#ifndef GAME_H
#define GAME_H

class Player;

#include <QStringList>
#include <QObject>

class Game: public QObject
{
    Q_OBJECT

    public:
        Game( const QString &nm = 0, QObject *parent = 0);

        Q_PROPERTY( QString name READ name WRITE setName SCRIPTABLE true USER true )
        Q_PROPERTY( qint8 id READ id WRITE setID SCRIPTABLE true USER true)

        QString name() const;
        void setName( const QString &nm );

        qint8 id() const;
        void setID( qint8 iD );

        QStringList scripts() const;
        void setScripts( const QStringList &s );

//         void sendChatMessage();

    private:
        QString gameName;
        qint8 gameID;

        QList < Player *> players;

        QStringList scriptFiles;
};

#endif
