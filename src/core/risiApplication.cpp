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

#include <QFile>
#include <QMessageBox>
#include <QSettings>

#include "gameListXML.h"
#include "risiApplication.h"

RISIapplication* RISIapplication::inst = 0;

RISIapplication::RISIapplication( QObject *parent )
    :QObject( parent ), xmlFile( new QFile("gameList.xml") ), tcpClient( new TcpClient( this ) ), serverErrors(), protocol( Protocol::instance() )
{
}

RISIapplication* RISIapplication::instance()
{
    if (inst == 0)
        inst = new RISIapplication;
    return inst;
}

void RISIapplication::initServer()
{
    server = Server::instance();

    setupConnections();

    QSettings settings;
    settings.beginGroup( "Server" );
    QVariant v = settings.value( "port", 2222 );
    settings.endGroup();

    bool ok;
    int port = v.toInt( &ok );

    if( ok )
    {
        Server::instance()->listen(QHostAddress::Any, port );
        if( !Server::instance()->isListening() )
            parseServerError();
    }
    else
        QMessageBox::warning(0, tr("Error: "), tr("Internal application error due to conversion from QVariant to integer! Please, try restart the application and submit a bug report ! ") );
}

void RISIapplication::initUI()
{
    risiUI = new RISIui( 0 );
    risiUI->show();
}

RISIapplication::~RISIapplication()
{
    delete xmlFile;
    delete risiUI;

    server->close();
    delete server;
    delete protocol;
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

    connect( server, SIGNAL(playerDisconnectedSignal(const QString)), risiUI, SLOT(playerDisconnectedSlot(const QString) ) );

    connect(server, SIGNAL(messageArrived(const QString)), protocol, SLOT(parseMessage(const QString)) );

    connect( risiUI, SIGNAL(connectToIPSignal(const QString, const int)), tcpClient, SLOT(connectToServer(const QString, const int)) );

}

void RISIapplication::parseServerError()
{
    switch( server->serverError() )
    {
        case QAbstractSocket::ConnectionRefusedError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The connection was refused by the peer (or timed out) !" ) );
            break;
        }
        case QAbstractSocket::RemoteHostClosedError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "connection was closed by remote host/client!" ) );
            break;
        }
        case QAbstractSocket::HostNotFoundError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( " The host address was not found !" ));
            break;
        }
        case QAbstractSocket::SocketAccessError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr("Server could not be started: Please change the server port in the settings and restart the application. It is recommended to use >1500 ! ") );
            break;
        }
        case QAbstractSocket::SocketResourceError:
        {

            QMessageBox::warning(0, tr("Server problem: "), tr( "The local system ran out of resources (e.g., too many sockets) !" ) );
            break;
        }
        case QAbstractSocket::SocketTimeoutError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The socket operation timed out !" ) );
            break;
        }
        case QAbstractSocket::DatagramTooLargeError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes) !" ) );
            break;
        }
        case QAbstractSocket::NetworkError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "An error occurred with the network (e.g., the network cable was accidentally plugged out?)" ) );
            break;
        }
        case QAbstractSocket::AddressInUseError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr("The address specified to QUdpSocket::bind() is already in use and was set to be exclusive !") );
            break;
        }
        case QAbstractSocket::SocketAddressNotAvailableError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The address specified to QUdpSocket::bind() does not belong to the host ! " ));
            break;
        }
        case QAbstractSocket::UnsupportedSocketOperationError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support) ! " ) );
            break;
        }
        case QAbstractSocket::ProxyAuthenticationRequiredError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "The socket is using a proxy, and the proxy requires authentication" ) );
            break;
        }
        case QAbstractSocket::UnknownSocketError:
        {
            qDebug()<<"somethin worng here";
            QMessageBox::warning(0, tr("Server problem: "), tr("An unidentified error occurred !") );
            break;
        }
        case QAbstractSocket::UnfinishedSocketOperationError:
        {
            QMessageBox::warning(0, tr("Server problem: "), tr( "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background) !" ) );
            break;
        }
        default:
            QMessageBox::warning(0, tr("Server problem: "), tr("some sort of error") );
    }

}
