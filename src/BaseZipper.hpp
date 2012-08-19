/*
 * File:    BaseZipper.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include "../Options.hpp"
#include <string>
#include "BaseStream.hpp"

namespace zlib {

class BaseZipper
{
public:
    BaseZipper(BaseStream *stream)
        : stream_(stream)
    {
    }
    virtual ~BaseZipper() {}

protected:
    BaseStream *stream_;
};

}  // zlib
