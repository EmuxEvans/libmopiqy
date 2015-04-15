# libmopiqy : Qt client library for Mopidy #

[![Build Status](https://img.shields.io/travis/AlexandrePTJ/mopidy-somafm/develop.svg?style=flat-square)](https://travis-ci.org/AlexandrePTJ/libmopiqy)
[![Coverage Status](https://img.shields.io/coveralls/AlexandrePTJ/libmopiqy/develop.svg?style=flat-square)](https://coveralls.io/r/AlexandrePTJ/libmopiqy?branch=develop)

[Mopidy](http://www.mopidy.com/) is a music server which can play music both from multiple sources, like your local hard drive, radio streams, and from Spotify and SoundCloud.

This library handle connection to mopidy server through websocket and implement its core API functions.

It is used in [Mopiqy Desktop](https://github.com/AlexandrePTJ/mopiqy_desktop) and aims to be used in mobile project.

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
