# libmopiqy : Qt client library for Mopidy #

[Mopid](http://www.mopidy.com/) is a music server which can play music both from multiple sources, like your local hard drive, radio streams, and from Spotify and SoundCloud.

This library handle connection to mopidy server through websocket and implement its core API functions.

It is used in [Mopiqy Desktop](https://github.com/AlexandreP2101/mopiqy_desktop) and aims to be used in mobile project.

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
