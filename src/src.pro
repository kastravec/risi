include(ui/ui.pri)
include(server/server.pri)
include(http/http.pri)
include(core/core.pri)

TEMPLATE = app
TARGET = risi
DEPENDPATH += .
INCLUDEPATH +=.
DESTDIR = ../bin/
MOC_DIR = ../moc/
OBJECTS_DIR = ../builds/

QT += network xml opengl \
 script

HEADERS += core/tcpClient.h \
 core/protocol.h

SOURCES += core/tcpClient.cpp \
 core/protocol.cpp

