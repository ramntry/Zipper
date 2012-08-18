TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -L./zlib -lz
DESTDIR = build
OBJECTS_DIR = build/obj

SOURCES += main.cpp \
    src/ZStream.cpp \
    src/Zipper.cpp \
    src/Unzipper.cpp \
    src/BaseStream.cpp

HEADERS += \
    Zipper.hpp \
    Unzipper.hpp \
    src/ZStream.hpp \
    src/BaseStream.hpp \
    src/BaseZipper.hpp

