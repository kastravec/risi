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

#include "chatUI.h"
#include "lineedit.h"
#include "message.h"
#include "risiApplication.h"
#include <QSplitter>
#include <QTextEdit>
#include <QLineEdit>
#include <QListView>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QStringListModel>

/**
 * \brief Constructor
 * @param parent QWidget
 */
ChatUI::ChatUI(QWidget *parent)
    :QWidget(parent)
{
    initUI();
    inputLineEdit->installEventFilter( this );
}

/**
 * \brief Initializes the UI components
 */
void ChatUI::initUI()
{
    chatWindow = new QTextEdit (this);
    chatWindow->setReadOnly( true );

    playerListWindow = new QListView (this);
    playerListModel = new QStringListModel( playerListWindow );
    inputLineEdit = new LineEdit(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget( chatWindow );
    splitter->addWidget( playerListWindow );
    splitter->setStretchFactor( 0, 5 );
    splitter->setStretchFactor( 1, 1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget( inputLineEdit );

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget( splitter);
    vlayout->addLayout( hlayout );

    setLayout(vlayout);
}

/**
 * \brief This event filter is installed on inputLineEdit- the line edit used to enter chat messages
 * @param watched QObject
 * @param event QEvent
 * @return bool
 */
bool ChatUI::eventFilter ( QObject * watched, QEvent * event )
{
    if( watched )
    {
        LineEdit *lineEdit = qobject_cast<LineEdit *>( watched );
        if( lineEdit )
            inputLineEditEvents( event );
    }

    return false;
}

/**
 * \brief This function processes all the events for inputLineEdit -the line edit used to enter chat messages
 * @param event QEvent
 */
bool ChatUI::inputLineEditEvents( QEvent *event )
{
    switch ( event->type() )
    {
        case QEvent::KeyPress:
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *> ( event );
            if( keyEvent->key() == Qt::Key_Return )
            {
                Message message( this, Message::Chat, 2, Message::Manual );
                qDebug()<<"ChatUI : " <<RISIapplication::instance()->nickname();
                message.addPart( RISIapplication::instance()->nickname() );
                message.addPart( inputLineEdit->text() );
                message.prepareMessage();
                emit messageRequest( message );
                inputLineEdit->clear();
            }

            return true;
        }
        default:
            return true;
    }

    return false;
}

void ChatUI::displayChatMessage( const QString &msg, const QString &nickName )
{
    chatWindow->append(msg);
}

void ChatUI::setListOfPlayers( const QStringList &list )
{
    playerListModel->setStringList( list );
}
