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


#include "board.h"
#include <QVariant>

Board::Board(QObject *parent)
    :QGraphicsScene(parent)
{
}

QVariant Board::inputMethodQuery ( Qt::InputMethodQuery query ) const
{
    return QGraphicsScene::inputMethodQuery( query );
}

void Board::contextMenuEvent ( QGraphicsSceneContextMenuEvent * /*contextMenuEvent*/ )
{

}

void Board::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsScene::dragEnterEvent( event );
}

void Board::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsScene::dragLeaveEvent( event );
}

void Board::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsScene::dragMoveEvent( event );
}

void Board::drawBackground ( QPainter * painter, const QRectF & rect )
{
    QGraphicsScene::drawBackground( painter, rect );
}

void Board::drawForeground ( QPainter * painter, const QRectF & rect )
{
    QGraphicsScene::drawForeground( painter, rect );
}
/*
void Board::drawItems ( QPainter * painter, int numItems, QGraphicsItem *[] items, const QStyleOptionGraphicsItem[] options, QWidget * widget )
{
    QGraphicsScene::drawItems( painter, numItems, items, options, widget );
}*/

void Board::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsScene::dropEvent( event );
}

bool Board::event ( QEvent * event )
{
    return QGraphicsScene::event( event );
}

void Board::focusInEvent ( QFocusEvent * focusEvent )
{
    QGraphicsScene::focusInEvent( focusEvent );
}

void Board::focusOutEvent ( QFocusEvent * /*focusEvent*/ )
{
//     QGraphicsScene::focusOutEvent( focusOutEvent );
}

void Board::helpEvent ( QGraphicsSceneHelpEvent * helpEvent )
{
    QGraphicsScene::helpEvent( helpEvent );
}

void Board::inputMethodEvent ( QInputMethodEvent * event )
{
    QGraphicsScene::inputMethodEvent( event );
}

void Board::keyPressEvent ( QKeyEvent * keyEvent )
{
    QGraphicsScene::keyPressEvent( keyEvent );
}

void Board::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    QGraphicsScene::keyReleaseEvent( keyEvent );
}

void Board::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsScene::mouseDoubleClickEvent( mouseEvent );
}

void Board::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsScene::mouseMoveEvent( mouseEvent );
}

void Board::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsScene::mousePressEvent( mouseEvent );
}

void Board::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsScene::mouseReleaseEvent( mouseEvent );
}

void Board::wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent )
{
    QGraphicsScene::wheelEvent( wheelEvent );
}

// void Board::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
// {
//     QGraphicsScene::dragEnterEvent( event );
// }
//
// void Board::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
// {
//     QGraphicsScene::dragLeaveEvent( event );
// }
//
// void Board::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
// {
//     QGraphicsScene::dragMoveEvent( event );
// }
//
// void Board::drawBackground ( QPainter * painter, const QRectF & rect )
// {
//     QGraphicsScene::drawBackground( painter, rect );
// }
//
// void Board::drawForeground ( QPainter * painter, const QRectF & rect )
// {
//     QGraphicsScene::drawForeground( painter, rect );
// }
//
// void Board::drawItems ( QPainter * painter, int numItems, QGraphicsItem *[] items, const QStyleOptionGraphicsItem[] options, QWidget * widget )
// {
//     QGraphicsScene::drawItems( painter, numItems, options, widget );
// }
//         void Board::dropEvent ( QGraphicsSceneDragDropEvent * event )
// {}
//         bool Board::event ( QEvent * event )
// {}
//         void Board::focusInEvent ( QFocusEvent * focusEvent )
// {}
//         void Board::focusOutEvent ( QFocusEvent * focusEvent )
// {}
//         void Board::helpEvent ( QGraphicsSceneHelpEvent * helpEvent )
// {}
//         void Board::inputMethodEvent ( QInputMethodEvent * event )
// {}
//         void Board::keyPressEvent ( QKeyEvent * keyEvent )
// {}
//         void Board::keyReleaseEvent ( QKeyEvent * keyEvent )
// {}
//         void Board::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
// {}
//         void Board::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
// {}
//         void Board::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
// {}
//         void Board::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
// {}
//         void Board::wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent )
// {}
