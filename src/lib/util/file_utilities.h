// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
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

} // namespace file
} // namespace util
} // namespace isc

#endif // FILE_UTILITIES_H
