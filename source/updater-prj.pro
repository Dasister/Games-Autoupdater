#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T14:16:30
#
#-------------------------------------------------

QT       += core gui

win32:QMAKE_LFLAGS_RELEASE = /NODEFAULTLIB:msvcprt.lib /NODEFAULTLIB:msvcprtd.lib /NODEFAULTLIB:libcmt.lib
win32:QMAKE_LFLAGS_DEBUG = /NODEFAULTLIB:msvcprtd.lib /NODEFAULTLIB:libcmtd.lib

DEFINES += BOOST_ASIO_SEPARATE_COMPILATION \
        WITH_SHIPPED_GEOIP_H \
        TORRENT_USE_OPENSSL \
        BOOST_ASIO_ENABLE_CANCELIO

TARGET = updater-prj
TEMPLATE = app

INCLUDEPATH += . \
                C:/boost_1_49_0 \
                C:/libtorrent/include \
                C:/openssl/include

CONFIG += static

unix:LIBS += -lssl -ltorrent-rasterbar

win32:LIBS += -L"C:/libtorrent/lib" \
    -L"C:/boost_1_49_0/stage/lib" \
    -L"C:/openssl/lib" \
    -llibtorrent-release -ladvapi32 -lcomctl32 -lssleay32 -llibeay32 -llibboost_system-vc90-mt-s-1_49 -llibboost_date_time-vc90-mt-s-1_49 -llibboost_thread-vc90-mt-s-1_49 -llibboost_filesystem-vc90-mt-1_49

SOURCES += main.cpp\
        mainform.cpp \
    settingswindow.cpp \
    aboutwindow.cpp

HEADERS  += mainform.h \
    settingswindow.h \
    aboutwindow.h


FORMS    += mainform.ui \
    settingswindow.ui \
    aboutwindow.ui

RESOURCES += \
    icons.qrc

TRANSLATIONS += translations/tr_en.ts \
                translations/tr_ru.ts
