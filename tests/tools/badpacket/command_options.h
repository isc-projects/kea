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

#ifndef COMMAND_OPTIONS_H
#define COMMAND_OPTIONS_H

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
/// Some of the options perform general control (like setting the address of the
/// nameserver under test, while the rest set values in the DNS message being
/// sent.  Each of the latter options can be specified as either:
///
/// - \c --option value
/// - \c --option value1-value2
///
/// Either way, two values are extracted the low value and the high value (in
/// the former case, both are the same).  The values are stored and can be
/// returned on request.
///
/// For simplicity, the class takes care of the --help and --version flags,
/// each of which will cause a message to be printed to stdout and the program
/// to terminate.

class CommandOptions {
public:

    /// \brief Default Constructor
    ///
    /// Set values to defaults.
    CommandOptions() {
        reset();
    }

    /// \brief Return minimum value for option
    ///
    /// Applicable only to an option affecting a field in the message, this
    /// method returns the minimum value that was given on the command line.
    /// (If only a single value was given, it will be that value returned.)
    /// If the option was not specified on the command line, the default value
    /// set in the OptionsInfo class will be returned.
    ///
    /// \param index Index of the command-line option.
    ///
    /// \return uint32_t holding the minimum value given (or the default if
    ///         the option was not specified on the command line).
    uint32_t minimum(int index) const;

    /// \brief Return maximum value for option
    ///
    /// Applicable only to an option affecting a field in the message, this
    /// method returns the maximum value that was given on the command line.
    /// (If only a single value was given, it will be that value returned.)
    /// If the option was not specified on the command line, the default value
    /// set in the OptionsInfo class will be returned.
    ///
    /// \param index Index of the command-line option.
    ///
    /// \return uint32_t holding the maximum value given (or the default if
    ///         the option was not specified on the command line).
    uint32_t maximum(int index) const;

    /// \brief Reports if option was given on command line
    ///
    /// \param index Index of the command-line option.
    ///
    /// \return true if the option was present, false if not.
    bool present(int index) const;


    /// \brief Return target address
    std::string getAddress() const {
        return address_;
    }

    /// \brief Return target port
    uint16_t getPort() const {
        return port_;
    }

    /// \brief Return timeout
    int getTimeout() const {
        return timeout_;
    }

    /// \brief Return qname
    std::string getQname() const {
        return qname_;
    }

    /// \brief Reset to defaults
    ///
    /// Resets the CommandOptions object to default values.
    void reset();

    /// \brief Parse command line
    ///
    /// Parses the command line and stores the selected options.  The parsing
    /// also handles the --help and --version commands: both of these will cause
    /// some text to be printed to stdout, after which exit() is called to
    /// terminate the program.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    void parse(int argc, char* const argv[]);

    /// \brief Print usage information and exit program
    void usage();

    /// \brief Print version information and exit program
    void version();

private:
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

    struct {
        uint32_t    minimum;        ///< Minimum value specified
        uint32_t    maximum;        ///< Maximum value specified
        bool        present;        ///< true if specified on command line
    } options_[OptionInfo::SIZE];   ///< Information about command options
    std::string     address_;       ///< Address to where query is sent
    uint16_t        port_;          ///< Target port
    int             timeout_;       ///< Timeout for query
    std::string     qname_;         ///< Query to make
};

} // namespace badpacket
} // namespace isc

#endif // COMMAND_OPTIONS_H
