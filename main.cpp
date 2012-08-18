#include <iostream>
#include <sstream>
#include "Zipper.hpp"
#include "Unzipper.hpp"

int main()
{
    zlib::Zipper zipper(Z_NO_COMPRESSION);
    zlib::Unzipper unzipper;

    std::string source = "to be or not to be";
    std::ostringstream os;
    for (int i = 0; i < 20; ++i)
    {
        os << " " << i;
        std::cout << zipper.deflateAtOnce(source + os.str()) << std::endl;
    }
}
