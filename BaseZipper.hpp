#pragma once

namespace zlib {

template <typename StreamType>
class BaseZipper
{
public:
    BaseZipper() : stream_is_busy_(false) {}
    bool isBusy() { return stream_is_busy_; }

protected:
    struct StreamMiner;
    static bool const kThreadSafeMode = false;

    StreamType stream_;
    bool stream_is_busy_;
};

template <typename StreamType>
class BaseZipper<StreamType>::StreamMiner
{
public:
    StreamMiner(StreamType *candidate, int level, bool stream_is_busy)
        : mined_stream_(candidate)
        , stream_was_busy_(stream_is_busy || kThreadSafeMode)
    {
        if (stream_was_busy_)
        {
            mined_stream_ = new DeflateStream(level);
        }
    }

    StreamType *get() { return mined_stream_; }

    ~StreamMiner()
    {
        if (stream_was_busy_)
        {
            delete mined_stream_;
        }
    }

private:
    StreamType *mined_stream_;
    bool stream_was_busy_;
};

}  // zlib
