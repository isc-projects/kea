// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef LEASE_FILE_IO_H
#define LEASE_FILE_IO_H

#include <string>

namespace isc {
namespace dhcp {
namespace test {

class LeaseFileIO {
public:
    LeaseFileIO(const std::string& filename);

    ~LeaseFileIO();

    /// @brief Check if test file exists on disk.
    bool exists() const;

    /// @brief Reads whole lease file.
    ///
    /// @return Contents of the file.
    std::string readFile() const;

    /// @brief Removes existing file (if any).
    void removeFile() const;

    /// @brief Creates file with contents.
    ///
    /// @param contents Contents of the file.
    void writeFile(const std::string& contents) const;

    /// @brief Absolute path to the file used in the tests.
    std::string testfile_;

};

}
}
}

#endif // LEASE_FILE_IO_H
