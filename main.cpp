#include "ZStream.hpp"

int main()
{
	zlib::ZStream stream;
	stream.DeflateInit(Z_DEFAULT_COMPRESSION, zlib::Z_P(main()));
	stream.DeflateEnd(zlib::Z_P(main()));
}

