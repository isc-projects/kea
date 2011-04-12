// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __COMMAND_OPTIONS_H
#define __COMMAND_OPTIONS_H

#include <cstdlib>
#include <stdint.h>
#include <utility>

#include "option_info.h"

namespace isc {
namespace badpacket {

/// \brief Command Options
///
/// This class is responsible for parsing the command-line and storing the
/// specified options.
///
/// Each option setting the state of one of the fields in the flags word in the
/// DNS packet can be specified as either:
///
/// - \c --option value
/// - \c --option value1-value2
///
/// Either way, two values are extracted the low value and the high value (in
/// the former case, both are the same).  The values are stored in an array
/// and can be returned on request.
///
/// For simplicity, the class also takes care of the --help and --version flags,
/// each of which will cause a message to be printed to stdout and the program
/// to terminate.

class CommandOptions {
public:

    /// \brief CommandOptions Constructor
    ///
    /// Set values to defaults.
    CommandOptions() {
        reset();
    }

    /// \brief Return minimum value for option
    ///
    /// \param index Index of the command-line option.
    ///
    /// \return uint32_t holding the minimum value given (or the default if
    ///         the option was not specified on the command line).
    uint32_t minimum(int index) const;

    /// \brief Return maximum value for option
    ///
    /// \param index Index of the command-line option.
    ///
    /// \return uint32_t holding the maximum value given (or the default if
    ///         the option was not specified on the command line).
    uint32_t maximum(int index) const;

    /// \brief Return Target Address
    std::string getAddress() const {
        return address_;
    }

    /// \brief Return Target Port
    uint16_t getPort() const {
        return port_;
    }

    /// \brief Return Timeout
    int getTimeout() const {
        return timeout_;
    }

    /// \brief Return qname
    std::string getQname() const {
        return qname_;
    }

    /// \brief Reset To Defaults
    void reset() {
        address_ = "127.0.0.1";
        port_ = 53;
        timeout_ = 500;
        qname_ = "www.example.com";

        for (int i = 0; i < OptionInfo::SIZE; ++i) {
            limits_[i][0] = limits_[i][1] = OptionInfo::defval(i);
        }
    }

    /// \brief Parse Command Line
    ///
    /// Parses the command line and stores the selected options.  The parsing
    /// also handles the --help and --version commands: both of these will cause
    /// some text to be printed to stdout, after which exit() is called to
    /// terminate the program.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    void parse(int argc, char* const argv[]);

    /// \brief Print Usage Information And Exit Program
    void usage();

    /// \brief Print Version Information And Exit Program
    void version();

    // The following are protected to aid testing

protected:
    /// \brief Process Option Value
    ///
    /// Processes a specific command-line option, interpreting the value and
    /// placing it in the appropriate location.  On error a BadValue exception
    /// is thrown.
    ///
    /// \param c Short form option character from the command line
    /// \param value Value of the option read from the command line
    void processOptionValue(int c, const char* value);

    // Member variables

private:
    uint32_t        limits_[OptionInfo::SIZE][2];
                                    ///< Value of options (minimum and maximum)
    std::string     address_;       ///< Address to where query is sent
    uint16_t        port_;          ///< Target port
    int             timeout_;       ///< Timeout for query
    std::string     qname_;         ///< Query to make
};

} // namespace badpacket
} // namespace isc

#endif // __COMMAND_OPTIONS_H
