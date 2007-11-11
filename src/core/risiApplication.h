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

#ifndef RISIAPPLICATION_H
#define RISIAPPLICATION_H

#include "ui/risiUI.h"
#include "server/server.h"
#include "tcpClient.h"

class RISIapplication : public QObject
{
    Q_OBJECT

    public:
        ~RISIapplication();

        void initUI();
        void initServer();

        void go();//FIXME remove me

        static RISIapplication* instance();

        void gameListXMLrequest( QStandardItemModel *m );
        void saveGameListXML( QStandardItemModel *m );

    private:
        RISIapplication( QObject *parent = 0 );
        void setupConnections();
        void parseServerError();

        RISIui *risiUI;
        Server *server;
        TcpClient *tcpClient;

        bool isServerRunning;
        QString serverErrors;

        QIODevice *xmlFile;
        static RISIapplication* inst;
};

#endif
