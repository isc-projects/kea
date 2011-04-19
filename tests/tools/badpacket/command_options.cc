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
#include "util/strutil.h"

#include "command_options.h"
#include "option_info.h"
#include "version.h"

using namespace std;
using namespace isc;

namespace isc {
namespace badpacket {

// Reset stored values to the defaults.
void
CommandOptions::reset() {
    address_ = "127.0.0.1";
    port_ = 53;
    timeout_ = 500;
    qname_ = "www.example.com";

    for (int i = 0; i < OptionInfo::SIZE; ++i) {
        options_[i].minimum = OptionInfo::defval(i);
        options_[i].maximum = OptionInfo::defval(i);
        options_[i].present = false;
    }
}

/// Parses the command-line options and records the results.
void
CommandOptions::parse(int argc, char* const argv[]) {

    // Set up options for processing.  The declaration of the string constants
    // as mutable arrays and putting the string variable into the "longopts"
    // structure (as opposed to just putting a string literal there) is
    // occasioned by a version of solaris which declares the first field as
    // "char*" (instead of the correct "const char*").

    // General options.
    char HELP[] = {"help"};
    char VERSION[] = {"version"};
    char ADDRESS[] = {"address"};
    char PORT[] = {"port"};
    char TIMEOUT[] = {"timeout"};

    // Settings for options in the flags field.
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

    // Settings for the count fields
    char QC[] = {"qc"};
    char AC[] = {"ac"};
    char UC[] = {"uc"};
    char DC[] = {"dc"};

    // Message size
    char MS[] = {"ms"};

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
        {QC,      1, NULL, 'Y'},  // querY section count
        {AC,      1, NULL, 'W'},  // ansWer section count
        {UC,      1, NULL, 'H'},  // autHority section count
        {DC,      1, NULL, 'I'},  // addItional section count
        {MS,      1, NULL, 'M'},  // Message size
        {NULL,    0, NULL, 0  }
    };
    const char* shortopts = "hva:p:t:Q:O:A:T:D:R:Z:U:C:E:Y:W:H:I:M:";


    // Set record of options to defaults before parsing
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
            case 'Y':   // --qc (query count)
            case 'W':   // --ac (answer count)
            case 'H':   // --uc (authority count)
            case 'I':   // --dc (additional count)
            case 'M':   // --ms (message size)
                processOptionValue(c, optarg);
                break;

            default:
                isc_throw(isc::InvalidParameter,
                          "unknown option given on the command line");
        }
    }

    // Pick up a parameter if there is one (and report excess).
    if (optind < argc) {
        qname_ = argv[optind++];
    }

    if (optind < argc) {
        isc_throw(isc::InvalidParameter,
                  "only a single (optional) parameter may be specified on the command line");
    }
}

// Print usage information.
void
CommandOptions::usage() {
    cout << "Usage: badpacket [options] query\n"
             "\n"
            "Sends a sequence of DNS messages to the specified nameserver and prints the\n"
            " results.  The packets are valid query packets but certain aspects of the\n"
            " packets (such as the flags fields, section count fields and message size) can\n"
            "be set to arbitrary values using the command-line switches.\n"
            "\n"
            "In the following list of command-line switches, '<range>' indicates a range of\n"
            "values specified as either <integer> or <integer1>-<integer2> (e.g. both '42'\n"
            "and '0-1' would be valid values for range).  The program sends a sequence of\n"
            "messages that contain all combinations of the flag values.  For example,\n"
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
            "General options are:\n"
            "\n"
            "--help              [-h] Prints this message and exits.\n"
            "--version           [-v] Prints the program version number.\n"
            "--address <address> [-a] Address of nameserver, which defaults to 127.0.0.1\n"
            "--port <port>       [-p] Port to which to send query.  Defaults to 53.\n"
            "--timeout <value>   [-t] Timeout value for the query.  Specified in ms, it\n"
            "                         defaults to 500ms.\n"
            "\n"
            "The following options set fields in the outgoing DNS message flags word:\n"
            "\n"
            "--qr <range>        [-Q] Set query/response bit.  Valid <range> is 0-1.\n"
            "--op <range>        [-O] Set opcode.  Valid <range> is 0-15.\n"
            "--aa <range>        [-A] Set authoritative answer bit.  Valid <range> is 0-1.\n"
            "--tc <range>        [-T] Set truncated bit.  Valid <range> is 0-1.\n"
            "--rd <range>        [-D] Set recursion desired bit.  Valid <range> is 0-1.\n"
            "--ra <range>        [-D] Set recursion available bit.  Valid <range> is 0-1.\n"
            "--z <range>         [-Z] Set zero (reserved) bit.  Valid <range> is 0-1.\n"
            "--ad <range>        [-U] Set authenticated data bit.  Valid <range> is 0-1.\n"
            "--cd <range>        [-C] Set checking disabled bit.  Valid <range> is 0-1.\n"
            "--rc <range>        [-E] Set rcode value.  Valid <range> is 0-15\n"
            "\n"
            "The following options set the various section counts (independent of what is\n"
            "actually in the section):\n"
            "\n"
            "--qc <range>        [-Y] Set the query count.  Valid range is 0-65535.\n"
            "--ac <range>        [-W] Set the answer count.  Valid range is 0-65535.\n"
            "--uc <range>        [-H] Set the authority count.  Valid range is 0-65535.\n"
            "--dc <range>        [-I] Set the additional count.  Valid range is 0-65535.\n"
            "\n"
            "Other options are:\n"
            "\n"
            "--ms <range>        [-M] Set the size of the message.  If the specified size\n"
            "                         smaller than the natural message size, it is truncated.\n"
            "                         If longer, the packet is extended with random values.\n"
            "                         Valid range is 2 to 65536\n"
            "\n"
            "query               Name to query for.  The query is for an 'IN' A record.  If\n"
            "                    not given, the name 'www.example.com' is used.\n"
            "\n"
            "The output is a single (very long) line containing the settings of the various\n"
            "fields.  The settings for the outgoing packet are reported in uppercase letters\n"
            "and that of the returned packet in lowercase.\n"
            ;
}

// Print version information,
void
CommandOptions::version() {
    cout << BADPACKET_VERSION << "\n";
}

// Process single flag that can be stored in the options_ member.
void
CommandOptions::processOptionValue(int c, const char* value) {

    // Get values for this option.
    int index = OptionInfo::getIndex(c);
    const char* name = OptionInfo::name(index);
    uint32_t minval = OptionInfo::minval(index);
    uint32_t maxval = OptionInfo::maxval(index);

    // Split the string up into one or two tokens.
    vector<string> tokens = isc::util::str::tokens(string(value), "-");
    if ((tokens.size() < 1) || (tokens.size() > 2)) {
        isc_throw(isc::BadValue, "value given for " << name << " is '" << value <<
                  "': it must be in the form 'int' or 'int1-int2'");
    }

    // Convert to uint32.
    try {
        options_[index].minimum = boost::lexical_cast<uint32_t>(tokens[0]);
        if (tokens.size() == 2) {
            options_[index].maximum = boost::lexical_cast<uint32_t>(tokens[1]);
        } else {
            options_[index].maximum = options_[index].minimum;
        }
    } catch (boost::bad_lexical_cast) {
        isc_throw(isc::BadValue, "value given for " << name << " is '" << value <<
                  "': it must be in the form 'int' or 'int1-int2'");
    }

    // Set the limits in the correct order.
    if (options_[index].minimum > options_[index].maximum) {
        swap(options_[index].minimum, options_[index].maximum);
    }

    // Check that tokens lie inside the allowed ranges.
    if ((tokens.size() == 1) &&
        ((options_[index].minimum < OptionInfo::minval(index)) || (options_[index].maximum > maxval))) {
        isc_throw(isc::BadValue, "the value of " << options_[index].minimum <<
                  " given for " << name << " is outside the range of " <<
                  minval << " to " << maxval);
    } else if (options_[index].minimum < minval) {
        isc_throw(isc::BadValue, "the lower limit of " << options_[index].minimum <<
                  " given for " << name << " is below the minimum permitted"
                  " value of " << minval);
    } else if (options_[index].maximum > maxval) {
        isc_throw(isc::BadValue, "the upper limit of " << options_[index].maximum <<
                  " given for " << name << " is above the maximum permitted"
                  " value of " << maxval);
    }

    // And finally note that the option was specified on the command line
    options_[index].present = true;
}

// Return information about the option - minimum and maximum values and whether
// it was actually specified. (Note that if it wasn't, the maximum and minimum
// values will have been set to the default recorded in the OptionInfo class.)
uint32_t
CommandOptions::minimum(int index) const {
    OptionInfo::checkIndex(index);
    return (options_[index].minimum);
}

uint32_t
CommandOptions::maximum(int index) const {
    OptionInfo::checkIndex(index);
    return (options_[index].maximum);
}

bool
CommandOptions::present(int index) const {
    OptionInfo::checkIndex(index);
    return (options_[index].present);
}

} // namespace badpacket
} // namespace isc
