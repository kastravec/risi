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

#include <QDebug>
#include <QFile>
#include "gameListXML.h"

/**
 * default constructor
 * @param m
 */
GameListXML::GameListXML( QStandardItemModel *m )
{
    if( !m )
        model = new QStandardItemModel;
    else
        model = m;
}

GameListXML::~GameListXML()
{}

/**
 * this function writes the model( QStandardItemModel) to xml (game_list.xml file)
 */
void GameListXML::writeXML( QIODevice *xmlFile )
{
    streamWriter.setDevice( xmlFile );
    xmlFile->open( QIODevice::Truncate | QIODevice::ReadWrite );

    streamWriter.setAutoFormatting( true);
    streamWriter.writeStartDocument();

    streamWriter.writeDTD( "<!DOCTYPE game_list>" );
    streamWriter.writeStartElement( "game_list" );
    streamWriter.writeAttribute( "version", "1.0" );
    for( int i = 0; i<model->rowCount(); ++i)
        writeItem( model->item(i,0) );

    streamWriter.writeEndDocument();

    xmlFile->close();
}

/**
 * helps the writeXML() function by writting an item ( QStandardItem)
 * @param
 */
void GameListXML::writeItem( QStandardItem *item)
{
    QString tagName = item->data( Qt::UserRole ).toString();
    streamWriter.writeStartElement( tagName );

    if( tagName == "game" )
    {
        streamWriter.writeAttribute ( "name", item->data( Qt::DisplayRole ).toString() );
        streamWriter.writeAttribute ( "tooltip", item->data( Qt::ToolTipRole ).toString() );
        for(int i=0; i<item->rowCount(); ++i)
            writeItem( item->child( i, 0) );
    }
    else if ( tagName == "file" )
    {
        streamWriter.writeAttribute( "path", item->data( Qt::DisplayRole ).toString() );//FIXME not the same role ???
        streamWriter.writeAttribute( "name", item->data( Qt::DisplayRole).toString() );
    }

    streamWriter.writeEndElement();
}

/**
 * reads the game_list.xml file and returns a nice standard item model
 * @return
 */
void GameListXML::readXML( QIODevice *xmlFile )
{
    streamReader.setDevice( xmlFile );
    xmlFile->open( QIODevice::ReadOnly );
    model->clear();//to avoid duplicates

    while( !streamReader.atEnd() )
    {
        streamReader.readNext();

        if( streamReader.isStartElement())
        {
            if( streamReader.name() == "game_list" && streamReader.attributes().value("version") == "1.0")
                readGameList();
            else
                streamReader.raiseError("The file is not a game_list version 1.0 file");
        }
    }

    xmlFile->close();
}

/**
 * helps the readXML() function for reading the game_list.xml
 * reads the very start elemement, \<game_list version..>
 */
void GameListXML::readGameList()
{
    //TODO check if really is a start element and its name is game_list and version 1.0
    QStandardItem *gameItem = 0;

    while( !streamReader.atEnd() )
    {
        streamReader.readNext();

        if( streamReader.isStartElement() )
        {
            if( streamReader.name() == "game" )
                readGameElement(&gameItem);
            else if( streamReader.name() == "file" )
                readFileElement(gameItem);
            //TODO what about unknown elements???
        }
    }
}

/**
 * helps the readGameList() function for reading the \<game> element
 * it creates an item ( QStandardItem) for the model
 */
void GameListXML::readGameElement( QStandardItem** gameItem  )
{
    *gameItem = new QStandardItem;
    (*gameItem)->setData( streamReader.attributes().value ("name").toString(), Qt::DisplayRole );
    (*gameItem)->setData( "game", Qt::UserRole );
    (*gameItem)->setData( streamReader.attributes().value("tooltip").toString(), Qt::ToolTipRole );

    model->appendRow( *gameItem );
}

/**
 * helps the readGameList() function for reading the \<file> element
 * it creates an item ( QStandardItem) for the model
 */
void GameListXML::readFileElement( QStandardItem *item )
{
    if (!item)
        return;
    QStandardItem *fileItem = new QStandardItem;
    fileItem->setData( "file", Qt::UserRole );
    item->appendRow( fileItem );
    fileItem->setData( streamReader.attributes().value("path").toString(), Qt::DisplayRole );
}
