/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci                                   *
 *   psaraci@gmail.com                                                     *
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

#include "connectionProgressDlg.h"
#include "playcontroller.h"
#include <QApplication>

/**
 * \class ConnectionProgressDlg
 * \internal This class is used to handle the progress when a player attemts to connect to a server
 * \brief Constructor
 * @param parent
 * @param currentPlay
 */
ConnectionProgressDlg::ConnectionProgressDlg( QObject *parent, PlayController *currentPlay )
:QObject( parent ), countSecs( 0 ), maxTime( 10 ), timer( this ), dlg( 0 ), currentPl( currentPlay )
{
    timer.setInterval( 500 );
    timer.setSingleShot( true );
    timer.start();
    dlg.setMinimumDuration( 0 );
    dlg.setRange( 0, maxTime );
    dlg.setCancelButtonText(tr("&Cancel"));
    dlg.setValue( countSecs );
    QApplication::processEvents();//FIXME it should not be neccessary to call this ??
    connect( &timer, SIGNAL(timeout() ), this, SLOT(updateStatus() ) );
}

/**
 * \brief called every 500 msec to check if the attempt to connect has succeeded
 */
void ConnectionProgressDlg::updateStatus()
{
    dlg.setValue( ++countSecs );
    if( currentPl->isConnected() || countSecs ==  2 * maxTime)
    {
        timer.stop();
        return;
    }

     timer.start();
}
