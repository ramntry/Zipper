#pragma once
#include "ZStream.hpp"

namespace zlib {

class Unzipper
{
public:
	Unzipper();
	~Unzipper();

private:
	ZStream stream;
};

}  // zlib

