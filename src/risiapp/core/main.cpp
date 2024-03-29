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

#include <QApplication>
#include <QDebug>
#include "risiApplication.h"
#include "initDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int returnCode;

    app.setApplicationName( "RISI script your game" );
    app.setOrganizationName( "RISI script your game" );

    InitDialog initDialog;
    returnCode = initDialog.exec();

    if( returnCode == QDialog::Accepted )
    {
        RISIapplication::instance()->setNickname( initDialog.nickName() );
        RISIapplication::instance()->initUI();

        if( !RISIapplication::instance()->initServer() )
        {
            qDebug()<<"Server could not be started!!";
            return 42;
        }

        returnCode = app.exec();
        RISIapplication::instance()->deleteLater();
    }
    return returnCode;
}
