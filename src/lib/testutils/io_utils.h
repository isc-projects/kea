// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_IO_UTILS_H
#define TEST_IO_UTILS_H

#include <string>
#include <sys/stat.h>

namespace isc {
namespace test {

/// @brief Checks if specified file exists.
///
/// @param file_path Path to a file.
/// @return true if the file exists, false otherwise.
bool fileExists(const std::string& file_path);

/// @brief Reads contents of the specified file.
///
/// @param file_path Path to a file.
/// @return File contents.
std::string readFile(const std::string& file_path);

/// @brief Removes comments from a JSON file
///
/// Removes //, # and /* */ comments from the input file and writes its content
/// to another file. The comments are replaced with spaces, so the original
/// token locations should remain unaffected. This is rather naive
/// implementation, but it's probably sufficient for testing. It won't be able
/// to pick any trickier cases, like # or // appearing in strings, nested C++
/// comments etc at the exception of // in URLs.
///
/// @param input_file file to be stripped of comments
/// @return filename of a new file that has comments stripped from it
/// @throw BadValue if the input file cannot be opened
std::string decommentJSONfile(const std::string& input_file);

}; // end of isc::test namespace
}; // end of isc namespace

#endif // TEST_IO_UTILS_H
