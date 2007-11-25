TEMPLATE = app
TARGET = risi

DEPENDPATH += . ui server http core globals
INCLUDEPATH = . ui server http core globals 

DESTDIR = ../bin/
MOC_DIR = ../moc/
OBJECTS_DIR = ../builds/

QT += network xml opengl script

HEADERS += ui/chatUI.h \
           ui/editGamesUI.h \
           ui/gameListUI.h \
           ui/hostGameDialog.h \
           ui/risiUI.h \
           ui/settingsUI.h \
		   globals/initDialog.h \
           globals/networkProtocol.h \
		   server/server.h \
           server/connectionHandler.h \
           core/board.h \
           core/boardItem.h \
           core/boardView.h \
           core/game.h \
           core/gameListXML.h \
           core/tcpClient.h \
           core/protocol.h \
           core/risiApplication.h \
           core/player.h \
           http/httpControler.h

SOURCES += ui/chatUI.cpp \
           ui/editGamesUI.cpp \
           ui/gameListUI.cpp \
           ui/hostGameDialog.cpp \
           ui/risiUI.cpp \
           ui/settingsUI.cpp \
		   globals/initDialog.cpp \
           globals/networkProtocol.cpp \
		   server/server.cpp \
           server/connectionHandler.cpp \
           core/board.cpp \
           core/boardItem.cpp \
           core/boardView.cpp \
           core/game.cpp \
           core/gameListXML.cpp \
           core/tcpClient.cpp \
           core/protocol.cpp \
           core/risiApplication.cpp \
           core/player.cpp \
           http/httpControler.cpp \
           main.cpp