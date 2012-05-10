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

namespace isc {
namespace perfdhcp {

/// \brief Command Options
///
/// This class is responsible for parsing the command-line and storing the
/// specified options.
///
class CommandOptions {
public:

    /// \brief Default Constructor
    ///
    /// Set values to defaults.
    CommandOptions() {
        reset();
    }

    /// \brief Reset to defaults
    ///
    /// Resets the CommandOptions object to default values.
    void reset();

    /// \brief Parse command line
    ///
    /// Parses the command line and stores the selected options.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    void parse(int argc, char* const argv[]);

    /// \brief Returns IP version
    ///
    /// \return IP version to be used
    uint8_t getIpVersion() const { return ipversion_; }

    /// \brief Print usage
    ///
    /// Prints perfdhcp usage
    void usage(void);

private:
    uint8_t ipversion_;

};

} // namespace perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_H
