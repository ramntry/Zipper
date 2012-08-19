/*
 * File:    main.cpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 18, 2012, 1:00 PM
 */

#include "Options.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "src/Zipper.hpp"
#include "src/Unzipper.hpp"

namespace zlib {
namespace tests {

typedef std::vector<std::string> StrVec;

int const repeatTimes = 5000;
std::string::difference_type const stepSize = 997;

void test1()
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
}

void test2(StrVec &src)
{
    zlib::Zipper zipper;
    zlib::Unzipper unzipper;

    std::cout << "big test. Please, wait" << std::endl;
    std::cout << "compressing..." << std::endl;
    StrVec pck;
    std::for_each(src.begin(), src.end(), [&pck, &zipper](std::string const &str)
            { pck.push_back(zipper.deflateAtOnce(str)); });
    std::random_shuffle(++pck.begin(), pck.end());

    std::cout << "decompressing..." << std::endl;
    StrVec unp;
    std::for_each(pck.begin(), pck.end(), [&unp, &unzipper](std::string const &str)
            { unp.push_back(unzipper.inflateAtOnce(str)); });
    std::sort(unp.begin(), unp.end());

    std::cout << "verifying of results" << std::endl;
    bool result = true;
    for (size_t i = 0; i < std::max(src.size(), unp.size()); ++i)
    {
        result &= (src[i] == unp[i]);
    }
    std::cout << "\nAll right? " << std::boolalpha << result << "\n" << std::endl;
}

// stable, but with zlib warnings :(
void test4(StrVec &src)
{
    std::cout << "main test #4. Please, wait" << std::endl;

    zlib::Zipper zipper(Z_BEST_COMPRESSION);
    zlib::Unzipper unzipper;

    std::string native_header = "* HEADER\n";
    std::string native_tail = "+ OK\n";
    int native_size = native_header.size() + native_tail.size();

    std::string header = zipper.deflateAtOnce(native_header);
    std::string tail = zipper.deflateAtOnce(native_tail);

    std::cout << "compressing..." << std::endl;
    StrVec pck;
    std::for_each(src.begin(), src.end(), [&pck, &zipper, &native_size](std::string const &str)
    {
        native_size += str.size();
        pck.push_back(zipper.deflateAtOnce(str));
    });
    std::random_shuffle(pck.begin(), pck.end());

    pck.push_back(tail);
    std::string compressed_data = header;
    std::for_each(pck.begin(), pck.end(), [&compressed_data](std::string &str) { compressed_data.append(str); });

    std::cout << "decompressing..." << std::endl;
    const char *buf = compressed_data.c_str();
    const char *end = buf + compressed_data.size();
    const char *cursorFrom = buf;
    const char *cursorTo = cursorFrom + std::min(stepSize, end - cursorFrom);
    std::string result;
    for (;;)
    {
        result.append(unzipper.inflateAtOnce(cursorFrom, cursorTo - cursorFrom));

        std::string::difference_type step = std::min(stepSize, end - cursorFrom);
        cursorFrom += step;
        cursorTo += step;

        if (result.size() >= native_tail.size()
                && result.substr(result.size() - native_tail.size(), native_tail.size()) == native_tail)
        { break; }
    }
    std::cout << "Native size:   " << native_size << "\n"
              << "Zipped size:   " << compressed_data.size() << "\n"
              << "Unzipped size: " << result.size() << "\n" << std::endl;
}

void runTests()
{
    StrVec src;
    std::ostringstream os;
    for (int i = 0; i < repeatTimes; ++i)
    {
        os << " " << i;
        src.push_back(os.str() + "\n");
    }

    test1();
    test2(src);

    // stable, but with zlib warnings :(
    test4(src);
}

}  // tests
}  // zlib

#ifdef Z_STANDALONE_TEST_MODE
int main()
{
    zlib::tests::runTests();
}
#endif
