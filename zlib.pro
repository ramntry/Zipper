TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -L./zlib -lz
DESTDIR = build
OBJECTS_DIR = build/obj

SOURCES += main.cpp \
    ZStream.cpp \
    Zipper.cpp \
    Unzipper.cpp

HEADERS += \
    ZStream.hpp \
    Zipper.hpp \
    Unzipper.hpp

