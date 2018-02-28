// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_FILE_IO_H
#define LEASE_FILE_IO_H

#include <string>

namespace isc {
namespace dhcp {
namespace test {

/// @brief This class contains functions to perform IO operations on files.
///
/// This class is solely used by unit tests. Some tests often need files
/// as an input. This class allows for easy creation of text files that can
/// be later used by unit tests. It also provides method to read the contents
/// of the existing file and remove existing file (cleanup after unit test).
class LeaseFileIO {
public:
    /// @brief Constructor
    ///
    /// @param filename Absolute path to the file.
    /// @param recreate A boolean flag indicating if the new file should
    /// be created, even if one exists.
    LeaseFileIO(const std::string& filename, const bool recreate = true);

    /// @brief Destructor.
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

    /// @brief Indicates if the file should be recreated during object
    /// construction and removed during destruction.
    bool recreate_;

};

}
}
}

#endif // LEASE_FILE_IO_H
