/*
 * File:    BaseStream.cpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#include "../Options.hpp"
#include "BaseStream.hpp"

using namespace zlib;

BaseStream::BaseStream()
    : buffer_(kInitialBufferSize)
{
    reinitBuffer();
}

void BaseStream::setSource(const char *source, int size)
{
    stream_.next_in = (Bytef *)source;
    stream_.avail_in = (uInt)size;
}

void BaseStream::reinitBuffer()
{
    stream_.next_out = (Bytef *)&buffer_[0];
    stream_.avail_out = (uInt)buffer_.size();
}

std::string BaseStream::evacuateResult()
{
    std::string result(resultData(), resultSize());
    reinitBuffer();
    return result;
}

void BaseStream::increaseBuffer()
{
    int result_size = resultSize();
    buffer_.resize(buffer_.size() * kBufferSizeMultiplier);
    stream_.next_out = (Bytef *)(&buffer_[0] + result_size);
    stream_.avail_out = buffer_.size() - result_size;
}
