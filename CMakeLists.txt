cmake_minimum_required(VERSION 2.8.9)

project(libmopiqy)

#
# Qt 5
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)

#
# Boost
#
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system thread random)

#
# libmopiqy itself
#
set(libmopiqy_SOURCES
    src/mopidyclient.cpp
    src/jsonwebsocket.cpp
    src/jsonrpchandler.cpp
    src/mopidyparser.cpp
    src/corelistener.cpp
    src/controllerinterface.cpp
    src/playbackcontroller.cpp
    src/playlistscontroller.cpp
    src/tracklistcontroller.cpp
    src/librarycontroller.cpp
)

set(libmopiqy_HEADERS
    libmopiqy/controllerinterface.h
    libmopiqy/librarycontroller.h
    libmopiqy/mopidyclient.h
    libmopiqy/mopidymodels.h
    libmopiqy/playbackcontroller.h
    libmopiqy/playlistscontroller.h
    libmopiqy/tracklistcontroller.h
)

qt_wrap_cpp(libmopiqy_HEADERS_MOC ${libmopiqy_HEADERS})

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/libmopiqy
    ${CMAKE_CURRENT_SOURCE_DIR}/websocketpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# OS specifics
if(WIN32)
    add_definitions(-DMOPIQY_CORE_SHARED)
endif(WIN32)

#
# lib version
#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(GetGitRevisionDescription)
git_describe(GIT_DESC "--tags")
add_definitions(-DMOPIQY_CORE_VERSION="${GIT_DESC}")

#
# link everythings
#
add_library(mopiqy SHARED ${libmopiqy_SOURCES} ${libmopiqy_HEADERS_MOC})
target_link_libraries(mopiqy ${Boost_LIBRARIES} ${Qt5Core_LIBRARIES})
