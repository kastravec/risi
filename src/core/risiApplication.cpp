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

#include <QFile>

#include "gameListXML.h"
#include "risiApplication.h"

RISIapplication* RISIapplication::inst = 0;

RISIapplication::RISIapplication()
{
    server = new Server;
    xmlFile = new QFile("gameList.xml");
}

RISIapplication* RISIapplication::instance()
{
    if (inst == 0)
        inst = new RISIapplication;
    return inst;
}

void RISIapplication::initUI()
{
    risiUI = new RISIui( 0 );
    risiUI->show();

    setupConnections();
}

RISIapplication::~RISIapplication()
{
    delete xmlFile;
}

void RISIapplication::gameListXMLrequest( QStandardItemModel *m )
{
    GameListXML gameListXmlParser( m );
    gameListXmlParser.readXML( xmlFile );
}

void RISIapplication::saveGameListXML( QStandardItemModel *model )
{
    GameListXML gameListXmlParser( model );
    gameListXmlParser.writeXML( xmlFile );
}

void RISIapplication::setupConnections()
{
    connect( risiUI, SIGNAL(chosenGameToHost(const QString&)), server, SLOT( hostGame(const QString &)) );
}
