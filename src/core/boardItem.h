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


#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QGraphicsItem>

class BoardItem : public QGraphicsItem
{
    public:
        BoardItem ( QGraphicsItem * parent = 0 );
        ~BoardItem();
        void advance( int phase );
        QRectF boundingRect () const = 0;
        bool collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape ) const;
        bool collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape ) const;
        bool contains ( const QPointF & point ) const;
        bool isObscuredBy ( const QGraphicsItem * item ) const;
        QPainterPath opaqueArea () const;
        void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) = 0;
        QPainterPath shape () const;
        int type () const;

    protected:
        void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
        void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
        void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
        void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
        void dropEvent ( QGraphicsSceneDragDropEvent * event );
        void focusInEvent ( QFocusEvent * event );
        void focusOutEvent ( QFocusEvent * event );
        void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
        void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
        void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
        void inputMethodEvent ( QInputMethodEvent * event );
        QVariant inputMethodQuery ( Qt::InputMethodQuery query ) const;
        QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
        void keyPressEvent ( QKeyEvent * event );
        void keyReleaseEvent ( QKeyEvent * event );
        void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
        void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
        void mousePressEvent ( QGraphicsSceneMouseEvent * event );
        void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
        bool sceneEvent ( QEvent * event );
        bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event );
        void wheelEvent ( QGraphicsSceneWheelEvent * event );
};
#endif
