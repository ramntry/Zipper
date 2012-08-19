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
public:
    BaseZipper(T option)
        : stream_(option)
    {
    }
    virtual ~BaseZipper() {}

    std::string evacuateResult()
    {
        return stream_.evacuateResult();
    }

protected:
    StreamType stream_;
};

}  // zlib
