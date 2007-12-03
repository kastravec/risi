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

#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>

class Board: public QGraphicsScene
{
    Q_OBJECT

    public:
        Board(QObject *parent = 0);

        QVariant inputMethodQuery ( Qt::InputMethodQuery query ) const;

    protected:
        void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
        void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
        void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
        void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
        void drawBackground ( QPainter * painter, const QRectF & rect );
        void drawForeground ( QPainter * painter, const QRectF & rect );
//         void drawItems ( QPainter * painter, int numItems, QGraphicsItem *[] items, const QStyleOptionGraphicsItem[] options, QWidget * widget = 0 );
        void dropEvent ( QGraphicsSceneDragDropEvent * event );
        bool event ( QEvent * event );
        void focusInEvent ( QFocusEvent * focusEvent );
        void focusOutEvent ( QFocusEvent * focusEvent );
        void helpEvent ( QGraphicsSceneHelpEvent * helpEvent );
        void inputMethodEvent ( QInputMethodEvent * event );
        void keyPressEvent ( QKeyEvent * keyEvent );
        void keyReleaseEvent ( QKeyEvent * keyEvent );
        void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
        void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
        void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
        void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
        void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent );
};
#endif
