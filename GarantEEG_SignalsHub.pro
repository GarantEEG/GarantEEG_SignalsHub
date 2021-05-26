#-------------------------------------------------
#
# Project created by QtCreator 2019-09-04T15:19:17
#
#-------------------------------------------------

QT       += core gui widgets concurrent
CONFIG += c++11
TEMPLATE = app

DEFINES += _USE_MATH_DEFINES

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

include("$$PWD/../GarantEEG_API/GarantEEG_API.pri")
INCLUDEPATH += $$PWD/../GarantEEG_API/

INCLUDEPATH += $$PWD/include

LIBS += -L"$$PWD/libs/x32/" \
            -lliblsl32

#QMAKE_LFLAGS +=-static-libgcc -static-libstdc++

win32-msvc*: {
    QMAKE_CXXFLAGS += /MP
    QMAKE_CXXFLAGS += /Ob2 /Oi /Ot
    #QMAKE_CXXFLAGS += /MT
    QMAKE_CXXFLAGS += /Zi

    #for MinWG
    #QMAKE_LFLAGS += -Wl,--large-address-aware
    #for MSVC
    QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE
    QMAKE_LFLAGS += /INCREMENTAL:NO /Debug

    #CONFIG += embed_manifest_exe
    #QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"
}

win32-msvc*:contains(QMAKE_TARGET.arch, x86_64): {
    ARCH = x64
	TARGET = GarantEeg_SignalsHub64
} else {
    ARCH = x32
	TARGET = GarantEeg_SignalsHub
}

unix {
    ARCH = x64
	TARGET = GarantEeg_SignalsHub64
}

CONFIG(release, debug|release): {
    BUILD_STATE = release
} else {
    BUILD_STATE = debug
}

DESTDIR     = $$PWD/build/$${BUILD_STATE}_$${ARCH}
OBJECTS_DIR = $$PWD/build/temp/$${BUILD_STATE}_$${ARCH}
MOC_DIR     = $$PWD/build/temp/$${BUILD_STATE}_$${ARCH}
RCC_DIR     = $$PWD/build/temp/$${BUILD_STATE}_$${ARCH}
UI_DIR      = $$PWD/build/temp/$${BUILD_STATE}_$${ARCH}

SOURCES += \
        filtersdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        newfilterdialog.cpp \
        utility.cpp

HEADERS += \
		GarantEeg_SignalsHub.rc \
        filtersdialog.h \
        mainwindow.h \
        newfilterdialog.h \
        resource.h \
        utility.h

FORMS += \
        filtersdialog.ui \
        mainwindow.ui \
        newfilterdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
