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


#include "boardItem.h"

BoardItem::BoardItem( QGraphicsItem * parent )
    :QGraphicsItem ( parent )
{
}

BoardItem::~BoardItem()
{
}

void BoardItem::advance( int phase )
{
    QGraphicsItem::advance( phase );
}

QRectF BoardItem::boundingRect () const
{
//     return QGraphicsItem::boundingRect();
    return QRectF(0,0,0,0);//TODO??
}

bool BoardItem::collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode) const
{
    return QGraphicsItem::collidesWithItem( other, mode );
}
bool BoardItem::collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode mode ) const
{
    return QGraphicsItem::collidesWithPath( path, mode );
}

bool BoardItem::contains ( const QPointF & point ) const
{
    return QGraphicsItem::contains( point );
}

bool BoardItem::isObscuredBy ( const QGraphicsItem * item ) const
{
    return QGraphicsItem::isObscuredBy( item );
}

QPainterPath BoardItem::opaqueArea () const
{
    return QGraphicsItem::opaqueArea();
}

void BoardItem::paint ( QPainter * /*painter*/, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
//     QGraphicsItem::paint( painter, option, widget );
}

QPainterPath BoardItem::shape () const
{
    return QGraphicsItem::shape();
}
int BoardItem::type () const
{
    return QGraphicsItem::type();
}

void BoardItem::contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
{
    QGraphicsItem::contextMenuEvent( event );
}
void BoardItem::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsItem::dragEnterEvent( event );
}

void BoardItem::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsItem::dragLeaveEvent( event );
}

void BoardItem::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsItem::dragMoveEvent( event );
}

void BoardItem::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
    QGraphicsItem::dropEvent( event );
}

void BoardItem::focusInEvent ( QFocusEvent * event )
{
    QGraphicsItem::focusInEvent( event );
}

void BoardItem::focusOutEvent ( QFocusEvent * event )
{
    QGraphicsItem::focusOutEvent( event );
}

void BoardItem::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    QGraphicsItem::hoverEnterEvent( event );
}

void BoardItem::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    QGraphicsItem::hoverLeaveEvent( event );
}

void BoardItem::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
{
    QGraphicsItem::hoverMoveEvent( event );
}

void BoardItem::inputMethodEvent ( QInputMethodEvent * event )
{
    QGraphicsItem::inputMethodEvent( event );
}

QVariant BoardItem::inputMethodQuery ( Qt::InputMethodQuery query ) const
{
    return QGraphicsItem::inputMethodQuery( query );
}

QVariant BoardItem::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    return QGraphicsItem::itemChange ( change, value );
}

void BoardItem::keyPressEvent ( QKeyEvent * event )
{
    QGraphicsItem::keyPressEvent( event );
}

void BoardItem::keyReleaseEvent ( QKeyEvent * event )
{
    QGraphicsItem::keyReleaseEvent( event );
}

void BoardItem::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )
{
    QGraphicsItem::mouseDoubleClickEvent( event );
}

void BoardItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    QGraphicsItem::mouseMoveEvent( event );
}

void BoardItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    QGraphicsItem::mousePressEvent( event );
}

void BoardItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    QGraphicsItem::mouseReleaseEvent( event );
}

bool BoardItem::sceneEvent ( QEvent * event )
{
    return QGraphicsItem::sceneEvent( event );
}

bool BoardItem::sceneEventFilter ( QGraphicsItem * watched, QEvent * event )
{
    return QGraphicsItem::sceneEventFilter( watched, event );
}

void BoardItem::wheelEvent ( QGraphicsSceneWheelEvent * event )
{
    QGraphicsItem::wheelEvent( event );
}
