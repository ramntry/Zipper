/*
 * File:    ZStream.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include "zlib/zlib.h"

#define Z_P(where) Place(#where, __FILE__, __LINE__)
#define Z_E(error_code) #error_code

namespace zlib {

class Place
{
public:
    Place(const char *w = undefined, const char *f = undefined, int l = unknown_line) : where(w), file(f), line(l) {}

protected:
    static const char *undefined;
    static const int unknown_line;

    const char *where;
    const char *file;
    int line;

friend class ZStream;
};

class ZStream : public z_stream
{
public:
    enum StreamType { UndefinedStream = 0, DeflateStream, InflateStream };

    ZStream();
    ~ZStream();

    int DeflateInit(int level, Place const &p);
    int Deflate(int flush, Place const &p);
    int DeflateEnd(Place const &p);

    int InflateInit(Place const &p);
    int Inflate(int flush, Place const &p);
    int InflateEnd(Place const &p);

    bool availInIsZero() { return avail_in == 0; }
    bool availOutIsZero() { return avail_out == 0; }

protected:
    int check(int error_code, const char *where, const char *who, const char *file, int line, ...);

    StreamType stream_type;
};

}  // zlib

