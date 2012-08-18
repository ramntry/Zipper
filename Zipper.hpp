/*
 * File:    Zipper.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include "src/BaseStream.hpp"
#include "src/BaseZipper.hpp"

namespace zlib {

class DeflateStream : public BaseStream
{
public:
    DeflateStream(int level = Z_DEFAULT_COMPRESSION);
    ~DeflateStream();

    void processAvailable(int flush);
};

class Zipper : public BaseZipper<DeflateStream, int>
{
public:
    Zipper(int level = Z_DEFAULT_COMPRESSION);
    std::string deflateAtOnce(std::string const &source);

private:
    int level_;
};

}  // zlib
