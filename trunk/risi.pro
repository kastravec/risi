######################################################################
# Automatically generated by qmake (2.01a) Tue Dec 4 00:48:51 2007
######################################################################

TEMPLATE = app
TARGET = risi

DESTDIR = bin/
MOC_DIR = moc/
OBJECTS_DIR = builds/

QT += network xml opengl script

DEPENDPATH += . \
              src/protocols \
              src/risiapp/core \
              src/risiapp/http \
              src/risiapp/ui \
              src/risiserver/core \
              src/risiserver/server
INCLUDEPATH += . \
               src/protocols \
               src/risiserver/server \
               src/risiserver/core \
               src/risiapp/core \
               src/risiapp/ui \
               src/risiapp/http

# Input
HEADERS += src/protocols/networkProtocol.h \
           src/protocols/serverprotocol.h \
		   src/protocols/connectionHandler.h \
		   src/protocols/clientprotocol.h \
		   src/protocols/protocol.h \
		   src/risiapp/http/httpController.h \
           src/risiapp/ui/chatUI.h \
           src/risiapp/ui/editGamesUI.h \
           src/risiapp/ui/gameListUI.h \
           src/risiapp/ui/hostGameDialog.h \
           src/risiapp/ui/initDialog.h \
           src/risiapp/ui/lineedit.h \
           src/risiapp/ui/risiUI.h \
           src/risiapp/ui/boardView.h \
           src/risiapp/ui/settingsUI.h \
		   src/risiapp/ui/connectionProgressDlg.h \
           src/risiapp/core/board.h \
           src/risiapp/core/boardItem.h \
           src/risiapp/core/gameListXML.h \
           src/risiapp/core/risiApplication.h \
           src/risiapp/core/tcpClient.h \
           src/risiapp/core/playcontroller.h \
           src/risiserver/core/game.h \
           src/risiserver/core/player.h \
           src/risiserver/server/server.h 

SOURCES += src/protocols/networkProtocol.cpp \
           src/protocols/serverprotocol.cpp \
		   src/protocols/clientprotocol.cpp \
		   src/protocols/connectionHandler.cpp \
		   src/protocols/protocol.cpp \
           src/risiapp/http/httpController.cpp \
           src/risiapp/ui/chatUI.cpp \
           src/risiapp/ui/editGamesUI.cpp \
           src/risiapp/ui/gameListUI.cpp \
           src/risiapp/ui/hostGameDialog.cpp \
           src/risiapp/ui/initDialog.cpp \
           src/risiapp/ui/lineedit.cpp \
           src/risiapp/ui/risiUI.cpp \
           src/risiapp/ui/boardView.cpp \
           src/risiapp/ui/settingsUI.cpp \
           src/risiapp/ui/connectionPrrogressDlg.cpp \
           src/risiapp/core/board.cpp \
           src/risiapp/core/boardItem.cpp \
           src/risiapp/core/gameListXML.cpp \
           src/risiapp/core/main.cpp \
           src/risiapp/core/risiApplication.cpp \
           src/risiapp/core/tcpClient.cpp \
           src/risiapp/core/playcontroller.cpp \         
           src/risiserver/core/game.cpp \
           src/risiserver/core/player.cpp \
           src/risiserver/server/server.cpp 
 