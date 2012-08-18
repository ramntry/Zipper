#include <iostream>
#include <memory>
#include "Zipper.hpp"

using namespace zlib;

DeflateStream::DeflateStream(int level)
    : buffer_(kInitialBufferSize)
{
    reinitBuffer();
    stream_.DeflateInit(level, Z_P(DeflateStream::DeflateStream(int level)));
}

DeflateStream::~DeflateStream()
{
    stream_.DeflateEnd(Z_P(DeflateStream::~DeflateStream()));
}

void DeflateStream::setSource(const char *source, int size)
{
    stream_.next_in = (Bytef *)source;
    stream_.avail_in = (uInt)size;
}

void DeflateStream::deflateAvailable(int flush)
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

void DeflateStream::reinitBuffer()
{
    stream_.next_out = (Bytef *)&buffer_[0];
    stream_.avail_out = (uInt)buffer_.size();
}

std::string DeflateStream::evacuateResult()
{
    std::string result(resultData(), resultSize());
    reinitBuffer();
    return result;
}

void DeflateStream::increaseBuffer()
{
    int result_size = resultSize();
    buffer_.resize(buffer_.size() * kBufferSizeMultiplier);
    stream_.next_out = (Bytef *)(&buffer_[0] + result_size);
    stream_.avail_out = buffer_.size() - result_size;
}

Zipper::Zipper(int level)
    : stream_(level)
    , level_(level)
    , stream_is_busy_(false)
{
}

Zipper::~Zipper()
{
}

std::string Zipper::deflateAtOnce(std::string const &source)
{
    StreamMiner miner(&stream_, level_, stream_is_busy_);
    DeflateStream *stream = miner.get();

    stream->setSource(source.c_str(), source.size());
    stream->deflateAvailable(Z_FULL_FLUSH);
    return stream->evacuateResult();
}
