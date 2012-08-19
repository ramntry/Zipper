/*
 * File:    Zipper.cpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#include <cassert>
#include "Zipper.hpp"

using namespace zlib;

DeflateStream::DeflateStream(int level)
{
    stream_.DeflateInit(level, Z_P(DeflateStream::DeflateStream(int level)));
}

DeflateStream::~DeflateStream()
{
    stream_.DeflateEnd(Z_P(DeflateStream::~DeflateStream()));
}

void DeflateStream::processAvailable(int flush)
{
    for (;;)
    {
        stream_.Deflate(flush, Z_P(DeflateStream::deflateAvailable(int flush)));
        if (stream_.availOutIsZero())
        {
            increaseBuffer();
            continue;
        }
        return;
    }
}

Zipper::Zipper(int level)
    : BaseZipper(level)
{
}

std::string Zipper::deflateAtOnce(std::string const &source)
{
    StreamMiner miner(&stream_, level_, stream_is_busy_);
    DeflateStream *stream = miner.get();
    assert(stream == &stream_);

    stream->setSource(source.c_str(), source.size());
    stream->processAvailable(Z_FULL_FLUSH);
    return stream->evacuateResult();
}

Zipper &Zipper::operator <<(std::string const &src)
{
    push(src);
    return *this;
}

void Zipper::flush()
{
    stream_.processAvailable(Z_FULL_FLUSH);
}
