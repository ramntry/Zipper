/*
 * File:    ZStream.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include "../Options.hpp"

#ifndef Z_DEBUG_MODE
#   define NDEBUG
#endif

#include "zlib/zlib.h"

#define Z_P(where) Place(#where, __FILE__, __LINE__)
#define Z_E(error_code) #error_code

namespace zlib {

class Place;

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


#ifndef Z_DEBUG_MODE

inline int ZStream::DeflateInit(int level, Place const &) { return deflateInit(this, level); }
inline int ZStream::Deflate(int flush, Place const &) { return deflate(this, flush); }
inline int ZStream::DeflateEnd(Place const &) { return deflateEnd(this); }

inline int ZStream::InflateInit(Place const &) { return inflateInit(this); }
inline int ZStream::Inflate(int flush, Place const &) { return inflate(this, flush); }
inline int ZStream::InflateEnd(Place const &) { return inflateEnd(this); }

#endif  // Z_DEBUG_MODE

}  // zlib

