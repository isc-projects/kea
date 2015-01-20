// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LFC_H
#define LFC_H

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

namespace isc {
namespace lfc {

/// @brief Exception thrown when the command line is invalid.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

//class lfcBase;
//typedef boost::shared_ptr<lfcBase> lfcBasePtr;

class lfc {
public:
    /// @brief Defines the application name, it may be used to locate
    /// configuration data and appears in log statements.
    static const char* lfc_app_name_;

    /// @brief Defines the executable name, by convention this should match
    /// the executable name.
    static const char* lfc_bin_name_;

    /// @brief Constructor
    lfc();

    /// @brief Destructor
    ~lfc();

    /// @brief Acts as the primary entry point to start execution
    /// of the process.  Provides the control logic:
    ///
    /// 1. parse command line arguments
    /// 2. verifies that it is the only instance
    /// 3. creates pid file
    /// .... TBD
    /// 4. remove pid file
    /// 5. exit to the caller
    void launch(int argc, char* argv[], const bool test_mode);

    /// @brief Process the command line arguments.  It is the first
    /// step taken after the process has been launched.
    void parseArgs(int argc, char* argv[]);

    /// @brief Use the pid to determine if there is another instance
    /// and create a pid file if we are alone.
    void pidCheck();

    /// @brief Get rid of the pid file we created earlier
    void pidDelete();

    /// #brief prints the program usage text to std error.
    ///
    /// @param text is a string message which will preceded the usage text.
    /// This is intended to be used for specific usage violation messages.
    void usage(const std::string& text);

private:
    int dhcp_version_;
    bool verbose_;
    std::string config_file_;
    std::string previous_file_;
    std::string copy_file_;
    std::string output_file_;
};

}; // namespace isc:lfc
}; // namespace isc

#endif

