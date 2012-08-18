#include <iostream>
#include <memory>
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

    stream->setSource(source.c_str(), source.size());
    stream->processAvailable(Z_FULL_FLUSH);
    return stream->evacuateResult();
}
