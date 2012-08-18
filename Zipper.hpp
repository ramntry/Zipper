#pragma once
#include <string>
#include <vector>
#include "BaseStream.hpp"

namespace zlib {

class DeflateStream : public BaseStream
{
public:
    DeflateStream(int level = Z_DEFAULT_COMPRESSION);
    ~DeflateStream();

    void processAvailable(int flush);
};

class Zipper
{
public:
    Zipper(int level = Z_DEFAULT_COMPRESSION);
    ~Zipper();

    bool isBusy() { return stream_is_busy_; }

    std::string deflateAtOnce(std::string const &source);

private:
    struct StreamMiner;

    static bool const kThreadSafeMode = false;

    DeflateStream stream_;
    int level_;
    bool stream_is_busy_;
};

class Zipper::StreamMiner
{
public:
    StreamMiner(DeflateStream *candidate, int level, bool stream_is_busy)
        : mined_stream_(candidate)
        , stream_was_busy_(stream_is_busy || kThreadSafeMode)
    {
        if (stream_was_busy_)
        {
            mined_stream_ = new DeflateStream(level);
        }
    }

    DeflateStream *get() { return mined_stream_; }

    ~StreamMiner()
    {
        if (stream_was_busy_)
        {
            delete mined_stream_;
        }
    }

private:
    DeflateStream *mined_stream_;
    bool stream_was_busy_;
};

}  // zlib
