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

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <getopt.h>

#include "exceptions/exceptions.h"
#include "log/strutil.h"

#include "command_options.h"
#include "option_info.h"
#include "version.h"

using namespace std;
using namespace isc;

namespace isc {
namespace badpacket {

/// Parses the command-line options and returns the results in an Options
/// structure.  If the 
void
CommandOptions::parse(int argc, char* const argv[]) {

    // Set up options for processing.  The declaration of the string constants
    // as mutable arrays and putting the string variable into the "option"
    // structure (as opposed to just putting a string literal there) is
    // occasioned by a version of solaris which declares the first field
    // as "char*" (instead of the correct "const char*").
    char HELP[] = {"help"};
    char VERSION[] = {"version"};
    char ADDRESS[] = {"address"};
    char PORT[] = {"port"};
    char TIMEOUT[] = {"timeout"};
    char QR[] = {"qr"};
    char OP[] = {"op"};
    char AA[] = {"aa"};
    char TC[] = {"tc"};
    char RD[] = {"rd"};
    char RA[] = {"ra"};
    char Z[]  = {"z"};
    char AD[] = {"ad"};
    char CD[] = {"cd"};
    char RC[] = {"rc"};

    const struct option longopts[] = {
        {HELP,    0, NULL, 'h'},  // Print usage message and exit
        {VERSION, 0, NULL, 'v'},  // Print program version and exit
        {ADDRESS, 1, NULL, 'a'},  // Specify target server address
        {PORT,    1, NULL, 'p'},  // Specify target port
        {TIMEOUT, 1, NULL, 't'},  // Time to wait before timing out (ms)
        {QR,      1, NULL, 'Q'},  // Query/response flag
        {OP,      1, NULL, 'O'},  // Opcode
        {AA,      1, NULL, 'A'},  // Authoritative answer
        {TC,      1, NULL, 'T'},  // Truncated
        {RD,      1, NULL, 'D'},  // recursion Desired
        {RA,      1, NULL, 'R'},  // Recursion available
        {Z,       1, NULL, 'Z'},  // must be Zero (reserved bit)
        {AD,      1, NULL, 'U'},  // aUthenticated data
        {CD,      1, NULL, 'C'},  // Checking disabled
        {RC,      1, NULL, 'E'},  // rEsult code
        {NULL,    0, NULL, 0  }
    };
    const char* shortopts = "hva:p:t:Q:O:A:T:D:R:Z:U:C:E:";


    // Set variables to defaults before parsing
    reset();

    // Process command line
    int    c;                       // Option being processed
    optind = 0;                     // Reset parsing
    while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
        switch (c) {
            case 'h':   // --help
                usage();
                exit(0);

            case 'v':   // --version
                version();
                exit(0);

            case 'a':   // --address
                address_ = optarg;
                break;

            case 'p':   // --port
                port_ = boost::lexical_cast<uint16_t>(string(optarg));
                break;

            case 't':   // --timeout
                timeout_ = boost::lexical_cast<int>(string(optarg));
                break;

            case 'Q':   // --qr (query/response)
            case 'O':   // --op (operation code)
            case 'A':   // --aa (authoritative answer)
            case 'T':   // --tc (truncated)
            case 'D':   // --rd (recursion desired)
            case 'R':   // --ra (recursion available)
            case 'Z':   // --z (zero: reserved bit)
            case 'U':   // --ad (authenticated data)
            case 'C':   // --cd (checking disabled)
            case 'E':   // --rc (result code)
                processOptionValue(c, optarg);
                break;

            default:
                isc_throw(isc::InvalidParameter,
                          "unknown option '" << argv[optind] << "' given on the command line");
        }
    }

    // Pick up a parameter if there is one (and ignore excess parameters).
    if (optind < argc) {
        qname_ = argv[optind++];
    }
}

/// \brief Print usage information
void
CommandOptions::usage() {
    cout << "Usage: badpacket [options] query\n"
             "\n"
            "Sends a sequence of packets to the specified nameserver and prints the results.\n"
            "The packets are valid query packets but the flags field (third and fourth bytes\n"
            "of the packet) can be set to arbitrary values using the command-line switches.\n"
            "\n"
            "In the following list of command-line switches, '<range>' indicates a range of\n"
            "values specified as either <integer> or <integer1>-<integer2> (e.g. both '42'\n"
            "and '0-1' would be valid values for range).  The program sends a sequence of\n"
            "packets that contain all combinations of the flag values.  For example,\n"
            "specifying:\n"
            "\n"
            "--tc 0-1 --op 1-4 --aa 1 --rd 0-1\n"
            "\n"
            "... would send a total of 16 packets which would have all combinations of the\n"
            "the tc bit set to 0 and 1, the rd bit set to 0 and 1, and the opcode set to all\n"
            "values between 1 and 4.  All other flags fields would be zero except for the aa\n"
            "bit which would always be 1.\n"
            "\n"
            "The long form of the option is given.  It can also be specified as a single-\n"
            "character short-form, which is listed in sqare brackets in the description.\n"
            "\n"
            "--help              [-h] Prints this message and exits.\n"
            "--version           [-v] Prints the program version number.\n"
            "--address <address> [-a] Address of nameserver, which defaults to 127.0.0.1\n"
            "--port <port>       [-p] Port to which to send query.  Defaults to 53.\n"
            "--timeout <value>   [-t] Timeout value for the query.  Specified in ms, it\n"
            "                         defaults to 500ms.\n"
            "--qr <range>        [-Q] Set query/response bit.  Valid <range> is 0-1\n"
            "--op <range>        [-O] Set opcode.  Valid <range> is 0-15\n"
            "--aa <range>        [-A] Set authoritative answer bit.  Valid <range> is 0-1\n"
            "--tc <range>        [-T] Set truncated bit.  Valid <range> is 0-1\n"
            "--z <range>         [-Z] Set zero (reserved) bit.  Valid <range> is 0-1\n"
            "--ad <range>        [-U] Set authentiacted data bit.  Valid <range> is 0-1\n"
            "--cd <range>        [-C] Set checking disabled bit.  Valid <range> is 0-1\n"
            "--rc <range>        [-E] Set rcode value.  Valid <range> is 0-15\n"
            "\n"
            "query               Name to query for.  The query is for an 'IN' A record.\n"
            "                    If not given, the name 'www.example.com' is used.\n"
            ;
}

/// \brief Print version information
void
CommandOptions::version() {
    cout << BADPACKET_VERSION << "\n";
}

// Process single flag
void
CommandOptions::processOptionValue(int c, const char* value) {

    // Get values for this option
    int index = OptionInfo::getIndex(c);
    const char* name = OptionInfo::name(index);
    uint32_t minval = OptionInfo::minval(index);
    uint32_t maxval = OptionInfo::maxval(index);

    // Split the string up into one or two tokens
    vector<string> tokens = isc::strutil::tokens(string(value), "-");
    if ((tokens.size() < 1) || (tokens.size() > 2)) {
        isc_throw(isc::BadValue, "value given for " << name << " is '" << value <<
                  "': it must be in the form 'int' or 'int1-int2'");
    }

    // Convert to uint32.
    int i = 0;
    try {
        do {
            limits_[index][i] = boost::lexical_cast<uint32_t>(tokens[i]);
            ++i;
        } while (i < tokens.size());
    } catch (boost::bad_lexical_cast) {
        isc_throw(isc::BadValue, "value given for " << name << " is '" << value <<
                  "': it must be in the form 'int' or 'int1-int2'");
    }

    // Set the limits in the correct order.
    if (tokens.size() == 1) {
        limits_[index][1] = limits_[index][0];
    } else if (limits_[index][0] > limits_[index][1]) {
        swap(limits_[index][0], limits_[index][1]);
    }

    // Check that tokens lie inside the allowed ranges
    if ((tokens.size() == 1) &&
        ((limits_[index][0] < OptionInfo::minval(index)) || (limits_[index][0] > maxval))) {
        isc_throw(isc::BadValue, "the tokens of " << limits_[index][0] <<
                  " given for " << name << " is outside the range of " <<
                  minval << " to " << maxval);
    } else if (limits_[index][0] < minval) {
        isc_throw(isc::BadValue, "the lower limit of " << limits_[index][0] <<
                  " given for " << name << " is below the minimum permitted"
                  " value of " << minval);
    } else if (limits_[index][1] > maxval) {
        isc_throw(isc::BadValue, "the upper limit of " << limits_[index][1] <<
                  " given for " << name << " is above the maximum permitted"
                  " value of " << maxval);
    }
}

// Minimum and maximum value of the flag
uint32_t
CommandOptions::minimum(int index) const {
    OptionInfo::checkIndex(index);
    return (limits_[index][0]);
}

uint32_t
CommandOptions::maximum(int index) const {
    OptionInfo::checkIndex(index);
    return (limits_[index][1]);
}

} // namespace badpacket
} // namespace isc
