#pragma once

namespace zlib {

template <typename StreamType, typename T>
class BaseZipper
{
public:
    BaseZipper(T option)
        : stream_(option)
        , stream_is_busy_(false)
    {
    }
    bool isBusy() { return stream_is_busy_; }

protected:
    struct StreamMiner;
    static bool const kThreadSafeMode = false;

    StreamType stream_;
    bool stream_is_busy_;
};

template <typename StreamType, typename T>
class BaseZipper<StreamType, T>::StreamMiner
{
public:
    StreamMiner(StreamType *candidate, T option, bool stream_is_busy)
        : mined_stream_(candidate)
        , stream_was_busy_(stream_is_busy || kThreadSafeMode)
    {
        if (stream_was_busy_)
        {
            mined_stream_ = new StreamType(option);
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
