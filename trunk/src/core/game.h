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

#include "board.h"
#include "boardView.h"

/**
 *
 */

class Game: public QObject
{
    public:
        Game( const QString &nm = 0, QObject *parent = 0);

        QString nameOfGame() const { return name; }
        void setName(const QString &nm ) { name = nm; }
        QStringList scripts() const { return scriptFiles; }
        void setScripts(const QStringList &s) { scriptFiles = s; }

    private:
        QString name;
        Board *board;
        BoardView *boardView;
        QStringList scriptFiles;
};

#endif
