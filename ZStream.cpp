#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cstdio>

#include "ZStream.hpp"

using namespace zlib;

const char *Place::undefined = "undefined";
const int Place::unknown_line = -1;

ZStream::ZStream()
{
    assert(Z_OK == 0);
    bzero(this, sizeof(ZStream));
}

int ZStream::DeflateInit(int level, Place const &p)
{
    assert(stream_type == UndefinedStream);
    stream_type = DeflateStream;
    return check(deflateInit(this, level)
            , p.where, "deflateInit(z_streamp strm, int level)", p.file, p.line
            , Z_MEM_ERROR, Z_E(Z_MEM_ERROR)" not enough memory"
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" level is not a valid compression level"
            , Z_VERSION_ERROR, Z_E(Z_VERSION_ERROR)" the version of zlib.h and"
                     " the version of the library linked do not match"
            , Z_OK);
}

int ZStream::Deflate(int flush, Place const &p)
{
    assert(stream_type == DeflateStream);
    return check(deflate(this, flush)
            , p.where, "deflate(z_streamp strm, int flush)", p.file, p.line
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" the stream state is "
                     "inconsistent (for example if next_in or next_out is NULL)"
            , Z_BUF_ERROR, Z_E(Z_BUF_ERROR)" no progress is possible (for example avail_in or avail_out was zero)"
            , Z_OK);
}

int ZStream::DeflateEnd(Place const &p)
{
    assert(stream_type == DeflateStream);
    stream_type = UndefinedStream;
    return check(deflateEnd(this)
            , p.where, "deflateEnd(z_streamp strm)", p.file, p.line
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" the stream state was inconsistent"
            , Z_DATA_ERROR, Z_E(Z_DATA_ERROR)" the stream was freed prematurely (some input or output was discarded)"
            , Z_OK);
}

int ZStream::InflateInit(Place const &p)
{
    assert(stream_type == UndefinedStream);
    stream_type = InflateStream;
    return check(inflateInit(this)
            , p.where, "inflateInit(z_streamp strm)", p.file, p.line
            , Z_MEM_ERROR, Z_E(Z_MEM_ERROR)" not enough memory"
            , Z_VERSION_ERROR, Z_E(Z_VERSION_ERROR)" the version of zlib.h and"
                     " the version of the library linked do not match"
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" the parameters are invalid (such as a null pointer to the structure)"
            , Z_OK);
}

int ZStream::Inflate(int flush, Place const &p)
{
    assert(stream_type == InflateStream);
    return check(inflate(this, flush)
            , p.where, "inflate(z_streamp strm, int flush)", p.file, p.line
            , Z_NEED_DICT, Z_E(Z_NEED_DICT)" a preset dictionary is needed"
            , Z_DATA_ERROR, Z_E(Z_DATA_ERROR)" input data was corrupted (input"
                     " stream not conforming to the zlib format or incorrect check value)"
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" the stream structure was"
                     " inconsistent (for example if next_in or next_out was NULL)"
            , Z_MEM_ERROR, Z_E(Z_MEM_ERROR)" there was not enough memory"
            , Z_BUF_ERROR, Z_E(Z_BUF_ERROR)" no progress is possible or if there"
                     " was not enough room in the output buffer when Z_FINISH is used"
            , Z_OK);
}

int ZStream::InflateEnd(Place const &p)
{
    assert(stream_type == InflateStream);
    stream_type = UndefinedStream;
    return check(inflateEnd(this)
            , p.where, "inflateEnd(z_streamp strm)", p.file, p.line
            , Z_STREAM_ERROR, Z_E(Z_STREAM_ERROR)" the stream state was inconsistent"
            , Z_OK);
}

ZStream::~ZStream()
{
    assert(stream_type == UndefinedStream);
}

int ZStream::check(int error_code, const char *where, const char *who, const char *file, int line, ...)
{
    if (error_code == Z_OK)
        return error_code;

    fprintf(stderr, "zlib error (code: %d, stream message: %s) in %s, %s -> file \"%s\", line %d"
            , error_code, msg, where, who, file, line);

    va_list args;
    va_start(args, line);
    for (int pattern = va_arg(args, int); pattern != Z_OK; pattern = va_arg(args, int))
    {
        const char *message = va_arg(args, const char *);
        if (pattern == error_code)
        {
            fprintf(stderr, " | %s", message);
        }
    }
    putc('\n', stderr);
    fflush(stderr);
    va_end(args);
    return error_code;
}

