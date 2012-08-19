/*
 * File:    Unzipper.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#pragma once
#include "src/BaseStream.hpp"
#include "src/BaseZipper.hpp"

namespace zlib {

class InflateStream : public BaseStream
{
public:
    InflateStream(int);
    ~InflateStream();

    void processAvailable(int flush);
};

class Unzipper : public BaseZipper<InflateStream, int>
{
public:
    Unzipper();
    std::string inflateAtOnce(const char *source, int size);
    std::string inflateAtOnce(std::string const &source);
    void operator <<(Manipulator manip) { manip(this); }
    Unzipper &operator <<(std::string const &src);
    void flush();
};

}  // zlib
