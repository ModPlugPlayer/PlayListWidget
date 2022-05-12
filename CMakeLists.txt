#Build script of PlayList Widget
#Copyright (C) 2020 Volkan Orhan

#This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

#This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

#You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

cmake_minimum_required(VERSION 3.5)

project(PlayListWidget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB MODPLUGPLAYERAPI_SRC
    "../ModPlugPlayerAPI/src/*.hpp"
    "../ModPlugPlayerAPI/src/*.cpp"
)

file(GLOB PLAYLISTWIDGET_SRC
    "src/*.hpp"
    "src/*.cpp"
    "src/*.ui"
)

file(GLOB PLAYLISTWIDGET_TEST
    "test/*.hpp"
    "test/*.cpp"
    "test/*.ui"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PlayListWidget
        MANUAL_FINALIZATION
        ${PLAYLISTWIDGET_SRC}
        ${PLAYLISTWIDGET_TEST}
        ${MODPLUGPLAYERAPI_SRC}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PlayListWidget APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PlayListWidget SHARED
            ${PLAYLISTWIDGET_SRC}
            ${PLAYLISTWIDGET_TEST}
            ${MODPLUGPLAYERAPI_SRC}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PlayListWidget
            ${PLAYLISTWIDGET_SRC}
            ${PLAYLISTWIDGET_TEST}
            ${MODPLUGPLAYERAPI_SRC}
        )
    endif()
endif()

include_directories(src)
include_directories(test)
include_directories(../ModPlugPlayerAPI/src)

target_link_libraries(PlayListWidget PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PlayListWidget PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PlayListWidget)
endif()
