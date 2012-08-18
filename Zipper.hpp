#pragma once
#include <string>
#include <vector>
#include "BaseStream.hpp"
#include "BaseZipper.hpp"

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
