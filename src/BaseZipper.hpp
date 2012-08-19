/*
 * File:    BaseZipper.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include <string>
#include "BaseStream.hpp"

namespace zlib {

template <typename StreamType, typename T>
class BaseZipper
{
protected:
    typedef void (*Manipulator)(BaseZipper<StreamType, T> *);

public:
    BaseZipper(T option)
        : stream_(option)
        , stream_is_busy_(false)
    {
    }
    virtual ~BaseZipper() {}
    virtual void operator <<(Manipulator manip) = 0;
    virtual void flush() = 0;

    bool isBusy() { return stream_is_busy_; }
    void push(const char *src, int size);
    void push(std::string const &src) { push(src.c_str(), src.size()); }

    std::string evacuateResult()
    {
        stream_is_busy_ = false;
        return stream_.evacuateResult();
    }
    void operator >>(std::string &dest) { dest = evacuateResult(); }

protected:
    struct StreamMiner;
    static bool const kThreadSafeMode = false;

    StreamType stream_;
    bool stream_is_busy_;

template <typename StreamType_, typename T_>
friend void flush(BaseZipper<StreamType_, T_> *zip);
};

template <typename StreamType, typename T>
void BaseZipper<StreamType, T>::push(const char *src, int size)
{
    stream_.setSource(src, size);
    if (stream_is_busy_ || true)
    {
        stream_.processAvailable(Z_SYNC_FLUSH);
    }
    stream_is_busy_ = true;
}

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

template <typename StreamType_, typename T_>
void flush(BaseZipper<StreamType_, T_> *zip)
{
    zip->flush();
    zip->stream_is_busy_ = false;
}

}  // zlib
