# Mopiqy Core : Core Qt client for Mopidy #

This library handle connection to mopidy server through websocket and implement its core API functions.

It is intended to be use directly inside GUI project sources.


## Dependencies ##

- [Qt](http://qt-project.org/) >= 5.0
- [websocketpp](http://www.zaphoyd.com/websocketpp)
 - [boost](http://www.boost.org/) [ modules: system, thread, random ]

## Building ##

Be sure to have `websocketpp` in your includes path.
Or as it is included as a git sub-module, it can be fetched with :

    $ git submodule init
    $ git submodule update

Libmopiqy is a simple Qt5 project, so it can be build easily using command line :

    $ qmake && make
