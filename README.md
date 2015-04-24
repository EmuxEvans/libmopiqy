# libmopiqy : Qt client library for Mopidy #

[![Travis Status](https://img.shields.io/travis/AlexandrePTJ/libmopiqy/master.svg?style=flat-square)](https://travis-ci.org/AlexandrePTJ/libmopiqy)
[![AppVeyor Status](https://img.shields.io/appveyor/ci/AlexandrePTJ/libmopiqy/master.svg?style=flat-square)](https://ci.appveyor.com/project/AlexandrePTJ/libmopiqy)
[![Coverage Status](https://img.shields.io/coveralls/AlexandrePTJ/libmopiqy/master.svg?style=flat-square)](https://coveralls.io/r/AlexandrePTJ/libmopiqy?branch=master)

[Mopidy](http://www.mopidy.com/) is a music server which can play music both from multiple sources, like your local hard drive, radio streams, and from Spotify and SoundCloud.

This library handle connection to mopidy server through websocket and implement its core API functions.

## Dependencies ##

- [Qt](http://qt-project.org/) >= 5.3
  - `qt5-base`
  - `qt5-websockets`

## Building ##

Libmopiqy is a simple Qt5 project, so it can be build easily using command line :

    $ qmake && make

## Documentation ##

An exampled called [MopidyBasicClient](https://github.com/AlexandrePTJ/libmopiqy/tree/master/demos/mopidybasicclient) is available to show how the library works.

The straight idea is to implement 'as is' [API Models](http://docs.mopidy.com/en/latest/api/models/) and [API Core](http://docs.mopidy.com/en/latest/api/core/)
