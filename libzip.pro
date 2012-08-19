TARGET = Zipper
TEMPLATE = lib
CONFIG += console staticlib
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L./zlib -lz
DESTDIR = build
OBJECTS_DIR = build/obj

SOURCES += main.cpp \
    src/ZStream.cpp \
    src/Zipper.cpp \
    src/Unzipper.cpp \
    src/BaseStream.cpp

HEADERS += \
    src/Zipper.hpp \
    src/Unzipper.hpp \
    src/ZStream.hpp \
    src/BaseStream.hpp \
    src/BaseZipper.hpp \
    Options.hpp \
    Zip.hpp

