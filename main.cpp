/*
 * File:    main.cpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#include <iostream>
#include <algorithm>
#include <sstream>
#include "Zipper.hpp"
#include "Unzipper.hpp"

typedef std::vector<std::string> StrVec;

int main()
{
    zlib::Zipper zipper;
    zlib::Unzipper unzipper;

    std::string source = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis et nulla ipsum, vitae dictum"
            " justo. Etiam suscipit consectetur justo eu ultricies. Fusce vitae augue nunc. Nulla ac massa ante. Sed"
            " nulla lorem, placerat et posuere eget, auctor non ante. Praesent quis condimentum arcu. Aliquam fringilla"
            " dapibus ligula, a placerat nunc tincidunt sed. Nulla facilisi. Nullam ac metus id nisi convallis lacinia."
            " Vivamus vitae sapien diam, eu dictum quam. Maecenas a est eros. Nullam non libero aliquet nulla lobortis"
            " cursus.\n";
    std::string zipped = zipper.deflateAtOnce(source);
    std::string unzipped = unzipper.inflateAtOnce(zipped);

    std::cout << source << "--------------------\n" <<  unzipped << std::endl;
    std::cout << "Native size:   " << source.size()   << "\n"
              << "Zipped size:   " << zipped.size()   << "\n"
              << "Unzipped size: " << unzipped.size() << "\n" << std::endl;

    std::cout << "big test. Please, wait" << std::endl;
    StrVec src;
    std::ostringstream os;
    for (int i = 0; i < 5000; ++i)
    {
        os << " " << i;
        src.push_back(os.str());
    }

    std::cout << "compressing..." << std::endl;
    StrVec pck;
    for (StrVec::iterator it = src.begin(); it != src.end(); ++it)
    {
        pck.push_back(zipper.deflateAtOnce(*it));
    }
    std::reverse(pck.begin(), pck.end());

    std::cout << "decompressing..." << std::endl;
    StrVec unp;
    for (StrVec::iterator it = pck.begin(); it != pck.end(); ++it)
    {
        unp.push_back(unzipper.inflateAtOnce(*it));
    }
    std::reverse(unp.begin(), unp.end());

    std::cout << "verifying of results" << std::endl;
    bool result = true;
    for (size_t i = 0; i < std::max(src.size(), unp.size()); ++i)
    {
        result &= (src[i] == unp[i]);
    }
    std::cout << "\nAll right? " << std::boolalpha << result << "\n" << std::endl;
}
