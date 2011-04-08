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

#include <boost/program_options.hpp>

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
/// the former case, bost are the same).  The values are stored in a
/// "FlagValues" structure, which can be returned on request.
///
/// For simplicity, the class also takes care of the --help and --version flags,
/// each of which will cause a message to be printed to stdout and the program
/// to terminate.

class CommandOptions {
public:

    /// \brief Flags Word Values
    ///
    /// Structure holding the values for the flag settings.  Each variable in
    /// the structure corresponds to one of the fields in the flags word.  The
    /// variables are two-ewlement arrays: element 0 of the array holds the low
    /// value in the range given, and element 1 the high value.  If only a
    /// single value is given, both elements hold the same value.

    struct FlagValues {
        uint32_t qr[2];         // QR bit
        uint32_t op[2];         // OPCODE field
        uint32_t aa[2];         // AA bit
        uint32_t tc[2];         // TC bit
        uint32_t rd[2];         // RD bit
        uint32_t ra[2];         // RA bit
        uint32_t z[2];          // Z bit (reserved bit)
        uint32_t ad[2];         // AD bit
        uint32_t cd[2];         // CD bit
        uint32_t rc[2];         // RCODE field

        /// \brief Default Constructor
        ///
        /// Sets everything to zero.
        FlagValues() {
            reset();
        }

        /// \brief Reset All Values to Zero
        void reset() {
            qr[0] = qr[1] = 0;
            op[0] = op[1] = 0;
            aa[0] = aa[1] = 0;
            tc[0] = tc[1] = 0;
            rd[0] = rd[1] = 0;
            ra[0] = ra[1] = 0;
            z[0] = z[1] = 0;
            ad[0] = ad[1] = 0;
            cd[0] = cd[1] = 0;
            rc[0] = rc[1] = 0;
        }
    };

    /// \brief CommandOptions Constructor
    ///
    /// Set values to defaults.
    CommandOptions() {
        reset();
    }

    /// \brief Return Flags Word Values
    ///
    /// Returns a copy of the flags word structure for use by the caller.  This
    /// structure holds the flags field settings specified on the command line.
    ///
    /// \return Copy of the values specified on the command line.
    FlagValues getFlagValues() const {
        return values_;
    }

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
        values_.reset();
        address_ = "127.0.0.1";
        port_ = 53;
        timeout_ = 500;
        qname_ = "www.example.com";
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

    /// \brief Print Usage Information
    void usage();

    /// \brief Print Version Information
    void version();

    // The following are protected to aid testing

protected:
    /// \brief Process Option Value
    ///
    /// Processes a specific command-line option, interpreting the value and
    /// placing it in the appropriate location.  On error a BadValue exception
    /// is thrown.
    ///
    /// \param arg flag argument read from the command line
    /// \param where Two-element uint32_t array into which the data is put
    /// \param minval Minimum allowed value
    /// \param maxval Maximum allowed value
    void processOptionValue(const char* arg, uint32_t* where, uint32_t minval,
                     uint32_t maxval);

    // Member variables

private:
    FlagValues      values_;        ///< Values read from command line
    std::string     address_;       ///< Address to where query is sent
    uint16_t        port_;          ///< Target port
    int             timeout_;       ///< Timeout for query
    std::string     qname_;         ///< Query to make
};

} // namespace badpacket
} // namespace isc

#endif // __COMMAND_OPTIONS_H
