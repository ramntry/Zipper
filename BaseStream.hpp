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

private:
    void increaseBuffer();

    static int const kInitialBufferSize = 2;
    static int const kBufferSizeMultiplier = 2;

    zlib::ZStream stream_;
    std::vector<char> buffer_;
};

}  // zlib
