#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T12:25:58
#
# Cilender (Blender data structure for libcinder)
#
# by Cole D. Ingraham
#
#-------------------------------------------------

QT       -= core gui

TARGET = cilender
TEMPLATE = lib
CONFIG += staticlib

include(QMakeCilender.pri)

QMAKE_LFLAGS += -F/System/Library/Frameworks/Accelerate.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/QTKit.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/CoreAudio.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/CoreVideo.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/AudioUnit.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/OpenGL.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/AudioToolBox.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/ApplicationServices.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/Carbon.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/Cocoa.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/AppKit.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/CoreData.framework
QMAKE_LFLAGS += -F/System/Library/Frameworks/Foundation.framework

INCLUDEPATH += $${CINDER_HOME}/include
INCLUDEPATH += $${CINDER_HOME}/lib
INCLUDEPATH += $${CINDER_HOME}/lib/macosx
INCLUDEPATH += $${CINDER_HOME}/boost
INCLUDEPATH += $${CINDER_HOME}/boost/boost
INCLUDEPATH += $${CINDER_HOME}/blocks/msaFluid/include
INCLUDEPATH += $${CINDER_HOME}/blocks/opencv/include
INCLUDEPATH += $${CINDER_HOME}/blocks/osc/include
INCLUDEPATH += $${CINDER_HOME}/blocks/tuio/include
INCLUDEPATH += $${CINDER_HOME}/blocks/osc/lib/macosx

INCLUDEPATH += $${JSONCPP_HOME}/include

LIBS += -framework Accelerate
LIBS += -framework QTKit
LIBS += -framework CoreAudio
LIBS += -framework CoreVideo
LIBS += -framework AudioUnit
LIBS += -framework OpenGL
LIBS += -framework AudioToolbox
LIBS += -framework ApplicationServices
LIBS += -framework Carbon
LIBS += -framework Cocoa
LIBS += -framework AppKit
LIBS += -framework CoreData
LIBS += -framework Foundation

LIBS += $${CINDER_HOME}/blocks/osc/lib/macosx/osc.a
LIBS += $${CINDER_HOME}/lib/libcinder_d.a
LIBS += $${CINDER_HOME}/lib/libcinder.a
LIBS += $${CINDER_HOME}/lib/macosx/libz.a
LIBS += $${CINDER_HOME}/lib/macosx/libpng14.a
LIBS += $${CINDER_HOME}/lib/macosx/libpixman-1.a
LIBS += $${CINDER_HOME}/lib/macosx/libboost_thread.a
LIBS += $${CINDER_HOME}/lib/macosx/libboost_system.a
LIBS += $${CINDER_HOME}/lib/macosx/libboost_filesystem.a
LIBS += $${CINDER_HOME}/lib/macosx/libboost_date_time.a

LIBS += $${JSONCPP_HOME}/buildscons/linux-gcc-4.2.1/src/lib_json/libjson_linux-gcc-4.2.1_libmt.a

PRE_TARGETDEPS += $${CINDER_HOME}/blocks/osc/lib/macosx/osc.a \
    $${CINDER_HOME}/lib/libcinder_d.a \
    $${CINDER_HOME}/lib/libcinder.a \
    $${CINDER_HOME}/lib/macosx/libz.a \
    $${CINDER_HOME}/lib/macosx/libpng14.a \
    $${CINDER_HOME}/lib/macosx/libpixman-1.a \
    $${CINDER_HOME}/lib/macosx/libboost_thread.a \
    $${CINDER_HOME}/lib/macosx/libboost_system.a \
    $${CINDER_HOME}/lib/macosx/libboost_filesystem.a \
    $${CINDER_HOME}/lib/macosx/libboost_date_time.a \
    $${CINDER_HOME}/blocks/osc/lib/macosx/osc.a

DEPENDPATH += $${CINDER_HOME}/blocks/osc/lib/macosx \
    $${CINDER_HOME}/lib \
    $${CINDER_HOME}/lib/macosx

DEFINES += CILENDER_LIBRARY

HEADERS += include/cilender.h \
    include/texturedata.h \
    include/materialdata.h \
    include/meshdata.h \
    include/objectdata.h \
    include/lampdata.h

SOURCES += cilender.cpp \
    texturedata.cpp \
    materialdata.cpp \
    meshdata.cpp \
    objectdata.cpp \
    lampdata.cpp
