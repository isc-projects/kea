// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FILE_UTILITIES_H
#define FILE_UTILITIES_H

#include <string>

namespace isc {
namespace util {
namespace file {

/// @brief Get the content of a regular file.
///
/// @param file_name The file name.
/// @return The content of the file_name file.
/// @throw BadValue when the file can't be opened or is not a regular one.
std::string getContent(const std::string& file_name);

/// @brief Check if there is a directory at the given path.
///
/// @param name the path being checked.
/// @return True if the name points to a directory, false otherwise including
/// if the pointed location does not exist.
bool isDir(const std::string& name);

/// @brief Check if there is a file at the given path.
///
/// @param name the path being checked.
/// @return True if the name points to a file, false otherwise including
/// if the pointed location does not exist.
bool isFile(const std::string& name);

} // namespace file
} // namespace util
} // namespace isc

#endif // FILE_UTILITIES_H
