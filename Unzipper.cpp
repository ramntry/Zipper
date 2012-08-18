#include "Unzipper.hpp"

using namespace zlib;

Unzipper::Unzipper()
{
	stream.InflateInit(Z_P(Unzipper::Unzipper()));
}

Unzipper::~Unzipper()
{
	stream.InflateEnd(Z_P(Unzipper::~Unzipper()));
}

