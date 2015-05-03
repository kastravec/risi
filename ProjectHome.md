**Grab the source code from svn for the latest changes**
"_svn checkout http://risi.googlecode.com/svn/trunk/ risi_"

**Browse the code online on :**  _http://risi.googlecode.com/svn/_


RISI is a tool that can be used to write your entire game using the QtScript module of the Qt4 platform. For a reference to QtScript please check the following link:
http://doc.trolltech.com/4.3/qtscript.html

How does it work?

The project is still under development.

RISI provides an API for developers to implement several functions. The script files ( the game basically ) after added to the RISI tool can be edited by any editor of your preference.
When you a "host" a game, RISI will read the QtScript files for that game and based on the functions defined on the script it will render the game. The QtScript files that are added for games are monitored by RISI so in this way when writing/editing a game all the changes are applied immediately.
Players need to identify themselfs by registering their profile ( username, password). Once
they are registered they can host games and connect to other hosted games. Registering a profile means that the player is authenticated to a central server and his/her username is how their hosted games are identified later on.
RISI has a server running on the background, which will perform the parsing of the QtScript files and send the parsed functions to be rendered by players/client connected to the hosted game. Hence, when the player registers their profile then the central server ( which is a small http-based python script ) will also store their IP address and port so other players can connect to it when a game is hosted.

**Grab the source code from svn for the latest changes**
"_svn checkout http://risi.googlecode.com/svn/trunk/ risi_"

**Browse the code online on :**  _http://risi.googlecode.com/svn/_

**COMPILE & INSTALL**

i) you need to have the Qt platform installed in your system ( grab it from ftp.trolltech.com ). Note, that you to have the PATH and QTDIR set before compiling RISI.

ii) Unpack, unix/linux (tar xvzf risi-source-snapshot.tar.gz )

iii) run qmake and then just make

iv) bin/risi


