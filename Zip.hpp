/*
 * File:    Options.hpp
 * Project: Zipper: C++-wrap for zlib
 * Author:  Roman Tereshin aka ramntry (ramntry@gmail.com, https://github.com/ramntry)
 *
 * Created on August 19, 2012, 1:10 PM
 */

#pragma once
#include "Options.hpp"
#include "src/Zipper.hpp"
#include "src/Unzipper.hpp"

#ifndef Z_STANDALONE_TEST_MODE
namespace zlib { namespace tests {
void runTests();
}}
#endif
