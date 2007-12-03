TEMPLATE = app
TARGET = risi

DEPENDPATH += . risiserver/server \
				risiserver/core \
				risiapp/core \
				risiapp/ui \
				risiapp/http \
				protocols
				
INCLUDEPATH = . risiserver/server \
				risiserver/core \
				risiapp/core \
				risiapp/ui \
				risiapp/http \
				protocols 

DESTDIR = ../bin/
MOC_DIR = ../moc/
OBJECTS_DIR = ../builds/

QT += network xml opengl script

HEADERS += chatUI.h \
           editGamesUI.h \
           gameListUI.h \
           hostGameDialog.h \
           risiUI.h \
           settingsUI.h \
		   initDialog.h \
           networkProtocol.h \
		   server.h \
           connectionHandler.h \
           board.h \
           boardItem.h \
           boardView.h \
           game.h \
           gameListXML.h \
           tcpClient.h \
           protocol.h \
           risiApplication.h \
           player.h \
           httpControler.h

SOURCES += chatUI.cpp \
           editGamesUI.cpp \
           gameListUI.cpp \
           hostGameDialog.cpp \
           risiUI.cpp \
           settingsUI.cpp \
		   initDialog.cpp \
           networkProtocol.cpp \
		   server.cpp \
           connectionHandler.cpp \
           board.cpp \
           boardItem.cpp \
           boardView.cpp \
           game.cpp \
           gameListXML.cpp \
           tcpClient.cpp \
           protocol.cpp \
           risiApplication.cpp \
           player.cpp \
           httpControler.cpp \
           main.cpp
