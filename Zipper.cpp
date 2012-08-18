#include "Zipper.hpp"

using namespace zlib;

Zipper::Zipper(int level)
{
	stream.DeflateInit(level, Z_P(Zipper::Zipper(int level)));
}

Zipper::~Zipper()
{
	stream.DeflateEnd(Z_P(Zipper::~Zipper()));
}

