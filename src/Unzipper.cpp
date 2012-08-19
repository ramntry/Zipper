/*
 * File:    Unzipper.cpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#include <cassert>
#include "Unzipper.hpp"

using namespace zlib;

InflateStream::InflateStream(int)
{
    stream_.InflateInit(Z_P(InflateStream::InflateStream(int)));
}

InflateStream::~InflateStream()
{
    stream_.InflateEnd(Z_P(InflateStream::~InflateStream()));
}

void InflateStream::processAvailable(int flush)
{
    for (;;)
    {
        stream_.Inflate(flush, Z_P(InflateStream::processAvailable(int flush)));
        if (stream_.availOutIsZero() && !stream_.availInIsZero())
        {
            increaseBuffer();
            continue;
        }
        return;
    }
}

Unzipper::Unzipper()
    : BaseZipper(0)
{
}

std::string Unzipper::inflateAtOnce(const char *source, int size)
{
    stream_.setSource(source, size);
    stream_.processAvailable(Z_FULL_FLUSH);
    return stream_.evacuateResult();
}

std::string Unzipper::inflateAtOnce(const std::string &source)
{
    return inflateAtOnce(source.c_str(), source.size());
}
