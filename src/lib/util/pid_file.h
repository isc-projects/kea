// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PID_FILE_H
#define PID_FILE_H

#include <exceptions/exceptions.h>
#include <fstream>
#include <ostream>
#include <string>

namespace isc {
namespace util {

/// @brief Exception thrown when an error occurs during PID file processing.
class PIDFileError : public Exception {
public:
    PIDFileError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when an error occurs trying to read a PID
/// from an opened file.
class PIDCantReadPID : public Exception {
public:
    PIDCantReadPID(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Class to help with processing PID files
///
/// This is a utility class to manipulate PID file. It provides
/// functions for writing and deleting a file containing a PID as
/// well as for extracting a PID from a file and checking if the
/// process is still running.
class PIDFile {
public:
    /// @brief Constructor
    ///
    /// @param filename PID filename.
    PIDFile(const std::string& filename);

    /// @brief Destructor
    ~PIDFile();

    /// @brief Read the PID in from the file and check it.
    ///
    /// Read the PID in from the file then use it to see if
    /// a process with that PID exists. If the file doesn't
    /// exist treat it as the process not being there.
    /// If the file exists but can't be read or it doesn't have
    /// the proper format treat it as the process existing.
    ///
    /// @return true if the PID is in use, false otherwise
    ///
    /// @throw throws PIDCantReadPID if it was able to open the file
    /// but was unable to read the PID from it.
    bool check() const;

    /// @brief Write the PID to the file.
    ///
    /// @param pid the pid to write to the file.
    ///
    /// @throw throws PIDFileError if it can't open or write to the PID file.
    void write(int) const;

    /// @brief Get PID of the current process and write it to the file.
    ///
    /// @throw throws PIDFileError if it can't open or write to the PID file.
    void write() const;

    /// @brief Delete the PID file.
    ///
    /// @throw throws PIDFileError if it can't delete the PID file
    void deleteFile() const;

    /// @brief Returns the path to the PID file.
    std::string getFilename() const {
        return (filename_);
    }

private:
    /// @brief PID filename
    std::string filename_;
};

} // namespace isc::util
} // namespace isc

#endif // PID_FILE_H
