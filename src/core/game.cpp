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

#include "game.h"

/**
 * \class Game
 *
 * \brief Constructor
 * @param nm QString name for the game
 * @param parent QObject parent
 */
Game::Game( const QString &nm, QObject * parent )
    :QObject( parent ), gameName( nm ), gameID( -1 )
{
}

/**
 * \brief name Property : Sets the name property of the game
 * @param nm QString
 */
void Game::setName( const QString & nm )
{
    gameName = nm;
}

/**
 * \brief name Property: returns the name property
 * @return QString
 */
QString Game::name() const
{
    return gameName;
}

/**
 * \brief id Property: returns the id property
 * @return qint32
 */
qint8 Game::id() const
{
    return gameID;
}

/**
 * \brief id Property: sets the id property
 * @param iD
 */
void Game::setID( qint8 iD )
{
    gameID = iD;
}
