#pragma once
#include "ZStream.hpp"

namespace zlib {

class Zipper
{
public:
	Zipper(int level = Z_DEFAULT_COMPRESSION);
	~Zipper();

private:
	ZStream stream;
};

}  // zlib

