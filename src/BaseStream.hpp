/*
 * File:    BaseStream.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include <vector>
#include <string>
#include "ZStream.hpp"

namespace zlib {

class BaseStream
{
public:
    BaseStream();
    virtual ~BaseStream() {}

    virtual void processAvailable(int flush) = 0;

    void setSource(const char *source, int size);
    const char *resultData() { return &buffer_[0]; }
    int resultSize() { return buffer_.size() - stream_.avail_out; }
    void reinitBuffer();
    std::string evacuateResult();

protected:
    void increaseBuffer();

    static int const kInitialBufferSize = 2;
    static int const kBufferSizeMultiplier = 2;

    zlib::ZStream stream_;
    std::vector<char> buffer_;
};

}  // zlib
