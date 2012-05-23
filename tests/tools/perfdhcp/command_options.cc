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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "exceptions/exceptions.h"

#include "command_options.h"

using namespace std;
using namespace isc;

namespace isc {
namespace perfdhcp {

CommandOptions&
CommandOptions::instance() {
    static CommandOptions options;
    return (options);
}

void
CommandOptions::reset() {
    // default mac address used in DHCP messages
    // if -b mac=<mac-address> was not specified
    uint8_t mac[6] = { 0x0, 0xC, 0x1, 0x2, 0x3, 0x4 };

    // default packet drop time if -D<drop-time> parameter
    // was not specified
    double dt[2] = { 1., 1. };

    // We don't use constructor initialization list because we
    // will need to reset all members many times to perform unit tests
    ipversion_ = 0;
    exchange_mode_ = DORA_SARR;
    rate_ = 0;
    report_delay_ = 0;
    random_range_ = 0;
    max_random_ = 0;
    mac_prefix_.assign(mac, mac + 6);
    base_.resize(0);
    num_request_.resize(0);
    period_ = 0;
    drop_time_set_ = 0;
    drop_time_.assign(dt, dt + 2);
    max_drop_set_ = 0;
    max_drop_.clear();
    max_pdrop_.clear();
    localname_.clear();
    is_interface_ = false;
    preload_ = 0;
    aggressivity_ = 1;
    local_port_ = 0;
    seeded_ = false;
    seed_ = 0;
    broadcast_ = false;
    rapid_commit_ = false;
    use_first_ = false;
    template_file_.clear();
    rnd_offset_.clear();
    xid_offset_.clear();
    elp_offset_ = -1;
    sid_offset_ = -1;
    rip_offset_ = -1;
    diags_.clear();
    wrapped_.clear();
    server_name_.clear();
}

void
CommandOptions::parse(int argc, char** const argv) {
    // Reset internal variables used by getopt
    // to eliminate undefined behavior when
    // parsing different command lines multiple times
    optind = 1;
    opterr = 0;
    initialize(argc, argv);
    validate();
}

void
CommandOptions::initialize(int argc, char** argv) {
    char opt = 0;               // subsequent options returned by getopt()
    std::string dropArg;        // value of -D<value>argument
    size_t percentLoc = 0;      // location of % sign in -D<value>
    double dropPercent = 0;     // % value (1..100) in -D<%value>
    int numDrops = 0;           // max number of drops specified in -D<value>
    int numReq = 0;             // max number of dropped requests in -n<max-drops>
    int offsetArg = 0;          // temp variable holiding offset arguments
    std::string sarg;           // temp variable for string args

    // in this section we collect argument values from command line
    // they will be tuned and validated elsewhere
    while((opt = getopt(argc, argv, "hv46r:t:R:b:n:p:d:D:l:P:a:L:s:iBc1T:X:O:E:S:I:x:w:")) != -1) {
        switch (opt) {
        case 'h':
            usage();
            return;

        case 'v':
            version();
            return;

        case '4':
            check(ipversion_ == 6, "IP version already set to 6");
            ipversion_ = 4;
            break;

        case '6':
            check(ipversion_ == 4, "IP version already set to 4");
            ipversion_ = 6;
            break;

        case 'r':
            rate_ = positiveInteger("rate_ must be a positive integer");
            break;

        case 't':
            report_delay_ = positiveInteger("report_delay_ must be a positive integer");
            break;

        case 'R':
            initRandomRange(optarg);
            break;

        case 'b':
            check(base_.size() > 3, "too many bases");
            base_.push_back(optarg);
            decodeBase(base_.back());
            break;

        case 'n':
            numReq = positiveInteger("num-request must be a positive integer");
            if (num_request_.size() >= 2) {
                isc_throw(isc::InvalidParameter,
                          "too many num-request values");
            }
            num_request_.push_back(numReq);
            break;

        case 'p':
            period_ = positiveInteger("test-period must be a positive integer");
            break;

        case 'd':
            try {
                drop_time_[drop_time_set_] = boost::lexical_cast<double>(optarg);
            } catch (boost::bad_lexical_cast&) {
                isc_throw(isc::InvalidParameter,
                          "value of drop time: -d<value> must be positive number");
            }
            check(drop_time_[drop_time_set_] <= 0., "drop-time must be a positive number");
            drop_time_set_ = 1;
            break;

        case 'D':
            dropArg = std::string(optarg);
            percentLoc = dropArg.find('%');
            if ((percentLoc) != std::string::npos) {
                dropPercent = boost::lexical_cast<double>(dropArg.substr(percentLoc + 1));
                check((dropPercent <= 0) || (dropPercent >= 100),
                  "value of drop percentage: -D<%value> must be 0..100");
                max_pdrop_.push_back(dropPercent);
                break;
            }
            numDrops = positiveInteger("value of max drops number: -d<value> must be a positive integer");
            max_drop_.push_back(numDrops);
            break;

        case 'l':
            localname_ = std::string(optarg);
            break;

        case 'P':
            preload_ = nonNegativeInteger("number of preload packets: -P<value> must not be "
                                          "a negative integer");
            break;

        case 'a':
            aggressivity_ = positiveInteger("value of aggressivity: -a<value> must be a positive integer");
            break;

        case 'L':
             local_port_ = nonNegativeInteger("value of local port: -L<value> must not be a negative integer");
             check(local_port_ > static_cast<int>( std::numeric_limits<uint16_t>::max()),
                  "local-port must be lower than " +
                  boost::lexical_cast<std::string>(std::numeric_limits<uint16_t>::max()));
            break;

        case 's':
            seed_ = static_cast<unsigned int>
                (nonNegativeInteger("value of -s <seed> must be non-negative integer"));
            seeded_ = seed_ > 0 ? true : false;
            break;

        case 'i':
            exchange_mode_ = DO_SA;
            break;

        case 'B':
            broadcast_ = true;
            break;

        case 'c':
            rapid_commit_ = true;
            break;

        case '1':
            use_first_ = true;
            break;

        case 'T':
            switch (template_file_.size()) {
            case 0:
            case 1:
                sarg = nonEmptyString("template file name not specified, expected -T<filename>");
                template_file_.push_back(sarg);
                break;
            default:
                isc_throw(isc::InvalidParameter,
                          "template-files are already set");
            }
            break;

        case 'X':
            offsetArg = positiveInteger("value of transaction id: -X<value> must be a positive integer");
            if (xid_offset_.size() >= 2) {
                xid_offset_.clear();
            }
            xid_offset_.push_back(offsetArg);
            break;

        case 'O':
            try {
                offsetArg = boost::lexical_cast<int>(optarg);
            } catch (boost::bad_lexical_cast&) {
                isc_throw(isc::InvalidParameter, "value of random random-offset: -O<value> "
                          "must be greater than 3");
            }
            check(offsetArg < 3, "value of random random-offset: -O<value> must be greater than 3 ");
            if (rnd_offset_.size() >= 2) {
                rnd_offset_.clear();
            }
            rnd_offset_.push_back(offsetArg);
            break;

        case 'E':
            elp_offset_ = nonNegativeInteger("value of time-offset: -E<value> must not be a negative integer");
            break;

        case 'S':
            sid_offset_ = positiveInteger("value of server id offset: -S<value> must be a positive integer");
            break;

        case 'I':
            rip_offset_ = positiveInteger("value of ip addr offset: -I<value> must be a positive integer");
            break;

        case 'x':
            diags_ = nonEmptyString("value of diagnostics selectors: -x<value> must be specified");
            break;

        case 'w':
            wrapped_ = nonEmptyString("command for wrapped mode: -w<command> must be specified");
            break;

        default:
            isc_throw(isc::InvalidParameter,
                      "unknown command line option");
        }
    }

    // Tune ip version as it still might be zero
    // if not specified in command line was used
    if (ipversion_ == 0) {
        ipversion_ = 4;
    }

    // Tune up template file lists
    if (template_file_.size() > 1) {
        if (xid_offset_.size() == 1) {
            xid_offset_.push_back(xid_offset_[0]);
        }
        if (rnd_offset_.size() == 1) {
            rnd_offset_.push_back(rnd_offset_[0]);
        }
    }

    // Get server argument
    check(optind < argc -1, "extra arguments?");
    if (optind == argc - 1) {
        server_name_ = argv[optind];
        // Decode special cases
        if ((ipversion_ == 4) && (server_name_.compare("all") == 0)) {
            broadcast_ = 1;
            server_name_ = "255.255.255.255";
        } else if ((ipversion_ == 6) && (server_name_.compare("all") == 0)) {
            server_name_ = "FF02::1:2";
        } else if ((ipversion_ == 6) && (server_name_.compare("servers") == 0)) {
            server_name_ = "FF05::1:3";
        }
    }

    // TODO handle -l option with IfaceManager when it is created
}

void
CommandOptions::initRandomRange(const std::string& opt) {
    const std::string errmsg = "value of -R <value> must be non-negative integer";
    long long randomRange = 0;
    try {
        randomRange = boost::lexical_cast<long long>(opt);
    } catch (boost::bad_lexical_cast&) {
        isc_throw(isc::InvalidParameter, errmsg.c_str());
    }
    check(randomRange < 0, errmsg.c_str());
    try {
        random_range_ = boost::lexical_cast<uint32_t>(randomRange);
    } catch (boost::bad_lexical_cast&) {
        isc_throw(isc::InvalidParameter, errmsg);
    }

    if ((random_range_ != 0) && (random_range_ != std::numeric_limits<uint32_t>::max())) {
        // randomization range is restricted by number of clients
        uint32_t maxTargetRand    = random_range_ + 1;
        // randomization with random() function is within uint32_t range
        uint64_t maxRandom        = std::numeric_limits<uint32_t>::max() + 1;
        // restrict max randomized value to
        // multiple of number of clients
        uint64_t restrictedRandom = (maxRandom / maxTargetRand) * maxTargetRand;
        if (restrictedRandom == maxRandom) {
            // no need to restrict max random value
            // uint32_t range is already multiple
            // of number of clients range
            max_random_ = 0;
        } else {
            max_random_ = static_cast<uint32_t> (restrictedRandom);
        }
    }
}

void
CommandOptions::decodeBase(const std::string& base) {
    std::string b(base);
    boost::algorithm::to_lower(b);

    // Currently we only support mac and duid
    if ((b.substr(0, 4) == "mac=") || (b.substr(0, 6) == "ether=")) {
        decodeMac(b);
    } else if (b.substr(0, 5) == "duid=") {
        decodeDuid(b);
    } else {
        isc_throw(isc::InvalidParameter,
                  "base value not provided as -b<value>, expected -b mac=<mac> or -b duid=<duid>");
    }
}

void
CommandOptions::decodeMac(const std::string& base) {
    // Strip string from mac=
    size_t found = base.find('=');
    static const char* errmsg = "expected -b<base> format for mac address is -b mac=00::0C::01::02::03::04";
    check(found == std::string::npos, errmsg);

    // Decode mac address to vector of uint8_t
    std::istringstream s1(base.substr(found + 1));
    std::string token;
    mac_prefix_.clear();
    while (std::getline(s1, token, ':')) {
        unsigned int ui = 0;
        std::istringstream s2(token);
        if (token.length() > 0) {
            try {
                ui = convertHexString(token);
            } catch (isc::InvalidParameter&) {
                isc_throw(isc::InvalidParameter,
                          "invalid characters in MAC provided");

            }
            mac_prefix_.push_back(ui);
        }
    }
    check(mac_prefix_.size() != 6, errmsg);
}

void
CommandOptions::decodeDuid(const std::string& base) {
    // Strip argument from duid=
    size_t found = base.find('=');
    check(found == std::string::npos, "expected -b<base> format for duid is -b duid=<duid>");
    std::string b = base.substr(found + 1);

    // duid must have even number of digits and must not be longer than 64 bytes
    check(b.length() & 1, "odd number of hexadecimal digits in duid");
    check(b.length() > 128, "duid too large");
    check(b.length() == 0, "no duid specified");

    // Turn pairs of hex digits into vector of bytes
    for (int i = 0; i < b.length(); i += 2) {
        unsigned int ui = 0;
        try {
            ui = convertHexString(b.substr(i, 2));
        } catch (isc::InvalidParameter&) {
            isc_throw(isc::InvalidParameter,
                      "invalid characters in DUID provided, exepected hex digits");
        }
        duid_prefix_.push_back(static_cast<uint8_t>(ui));
    }
}

uint8_t
CommandOptions::convertHexString(const std::string& s) {
    unsigned int ui = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (!std::isxdigit(s[i])) {
            isc_throw(isc::InvalidParameter,
                      "The following digit: " << s[i] << " in "
                      << s << "is not hexadecimal");
        }
    }
    std::istringstream ss(s);
    ss >> std::hex >> ui >> std::dec;
    if (ui > 0xFF) {
        isc_throw(isc::InvalidParameter, "Can't convert more than two hex digits to byte");
    }
    return ui;
}

void
CommandOptions::validate() const {
    check((getIpVersion() != 4) && (isBroadcast() != 0),
          "-B is not compatible with IPv6 (-6)");
    check((getIpVersion() != 6) && (isRapidCommit() != 0),
          "-6 (IPv6) must be set to use -c");
    check((getExchangeMode() == DO_SA) && (getNumRequests().size() > 1),
          "second -n<num-request> is not compatible with -i");
    check((getExchangeMode() == DO_SA) && (getDropTime()[1] != 1.),
          "second -d<drop-time> is not compatible with -i");
    check((getExchangeMode() == DO_SA) &&
          ((getMaxDrop().size() > 1) || (getMaxDropPercentage().size() > 1)),
          "second -D<max-drop> is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (isUseFirst()),
          "-1 is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getTemplateFiles().size() > 1),
          "second -T<template-file> is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getTransactionIdOffset().size() > 1),
          "second -X<xid-offset> is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getRandomOffset().size() > 1),
          "second -O<random-offset is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getElapsedTimeOffset() >= 0),
          "-E<time-offset> is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getServerIdOffset() >= 0),
          "-S<srvid-offset> is not compatible with -i\n");
    check((getExchangeMode() == DO_SA) && (getRequestedIpOffset() >= 0),
          "-I<ip-offset> is not compatible with -i\n");
	check((getExchangeMode() != DO_SA) && (isRapidCommit() != 0),
          "-i must be set to use -c\n");
	check((getRate() == 0) && (getReportDelay() != 0),
          "-r<rate> must be set to use -t<report>\n");
	check((getRate() == 0) && (getNumRequests().size() > 0),
          "-r<getRate()> must be set to use -n<num-request>\n");
	check((getRate() == 0) && (getPeriod() != 0),
          "-r<rate> must be set to use -p<test-period>\n");
	check((getRate() == 0) &&
          ((getMaxDrop().size() > 0) || getMaxDropPercentage().size() > 0),
          "-r<rate> must be set to use -D<max-drop>\n");
	check((getTemplateFiles().size() < getTransactionIdOffset().size()),
          "-T<template-file> must be set to use -X<xid-offset>\n");
	check((getTemplateFiles().size() < getRandomOffset().size()),
          "-T<template-file> must be set to use -O<random-offset>\n");
	check((getTemplateFiles().size() < 2) && (getElapsedTimeOffset() >= 0),
          "second/request -T<template-file> must be set to use -E<time-offset>\n");
	check((getTemplateFiles().size() < 2) && (getServerIdOffset() >= 0),
          "second/request -T<template-file> must be set to "
          "use -S<srvid-offset>\n");
	check((getTemplateFiles().size() < 2) && (getRequestedIpOffset() >= 0),
			"second/request -T<template-file> must be set to "
			"use -I<ip-offset>\n");

}

void
CommandOptions::check(bool condition, const std::string& errmsg) const {
    // The same could have been done with macro or just if statement but
    // we prefer functions to macros here
    if (condition) {
        isc_throw(isc::InvalidParameter, errmsg);
    }
}

int
CommandOptions::positiveInteger(const std::string& errmsg) {
    try {
        int value = boost::lexical_cast<int>(optarg);
        check(value <= 0, errmsg);
        return (value);
    } catch (boost::bad_lexical_cast&) {
        isc_throw(InvalidParameter, errmsg);
    }
}

int
CommandOptions::nonNegativeInteger(const std::string& errmsg) {
    try {
        int value = boost::lexical_cast<int>(optarg);
        check(value < 0, errmsg);
        return (value);
    } catch (boost::bad_lexical_cast&) {
        isc_throw(InvalidParameter, errmsg);
    }
}

std::string
CommandOptions::nonEmptyString(const std::string& errmsg) {
    std::string sarg = optarg;
    if (sarg.length() == 0) {
        isc_throw(isc::InvalidParameter, errmsg);
    }
    return sarg;
}

void
CommandOptions::usage() const {
	fprintf(stdout, "%s",
"perfdhcp [-hv] [-4|-6] [-r<rate>] [-t<report>] [-R<range>] [-b<base>]\n"
"    [-n<num-request>] [-p<test-period>] [-d<drop-time>] [-D<max-drop>]\n"
"    [-l<local-addr|interface>] [-P<preload>] [-a<aggressivity>]\n"
"    [-L<local-port>] [-s<seed>] [-i] [-B] [-c] [-1]\n"
"    [-T<template-file>] [-X<xid-offset>] [-O<random-offset]\n"
"    [-E<time-offset>] [-S<srvid-offset>] [-I<ip-offset>]\n"
"    [-x<diagnostic-selector>] [-w<wrapped>] [server]\n"
"\n"
"The [server] argument is the name/address of the DHCP server to\n"
"contact.  For DHCPv4 operation, exchanges are initiated by\n"
"transmitting a DHCP DISCOVER to this address.\n"
"\n"
"For DHCPv6 operation, exchanges are initiated by transmitting a DHCP\n"
"SOLICIT to this address.  In the DHCPv6 case, the special name 'all'\n"
"can be used to refer to All_DHCP_Relay_Agents_and_Servers (the\n"
"multicast address FF02::1:2), or the special name 'servers' to refer\n"
"to All_DHCP_Servers (the multicast address FF05::1:3).  The [server]\n"
"argument is optional only in the case that -l is used to specify an\n"
"interface, in which case [server] defaults to 'all'.\n"
"\n"
"The default is to perform a single 4-way exchange, effectively pinging\n"
"the server.\n"
"The -r option is used to set up a performance test, without\n"
"it exchanges are initiated as fast as possible.\n"
"\n"
"Options:\n"
"-1: Take the server-ID option from the first received message.\n"
"-4: DHCPv4 operation (default). This is incompatible with the -6 option.\n"
"-6: DHCPv6 operation. This is incompatible with the -4 option.\n"
"-a<aggressivity>: When the target sending rate is not yet reached,\n"
"    control how many exchanges are initiated before the next pause.\n"
"-b<base>: The base mac, duid, IP, etc, used to simulate different\n"
"    clients.  This can be specified multiple times, each instance is\n"
"    in the <type>=<value> form, for instance:\n"
"    (and default) mac=00:0c:01:02:03:04.\n"
"-d<drop-time>: Specify the time after which a request is treated as\n"
"    having been lost.  The value is given in seconds and may contain a\n"
"    fractional component.  The default is 1 second.\n"
"-E<time-offset>: Offset of the (DHCPv4) secs field / (DHCPv6)\n"
"    elapsed-time option in the (second/request) template.\n"
"    The value 0 disables it.\n"
"-h: Print this help.\n"
"-i: Do only the initial part of an exchange: DO or SA, depending on\n"
"    whether -6 is given.\n"
"-I<ip-offset>: Offset of the (DHCPv4) IP address in the requested-IP\n"
"    option / (DHCPv6) IA_NA option in the (second/request) template.\n"
"-l<local-addr|interface>: For DHCPv4 operation, specify the local\n"
"    hostname/address to use when communicating with the server.  By\n"
"    default, the interface address through which traffic would\n"
"    normally be routed to the server is used.\n"
"    For DHCPv6 operation, specify the name of the network interface\n"
"    via which exchanges are initiated.\n"
"-L<local-port>: Specify the local port to use\n"
"    (the value 0 means to use the default).\n"
"-O<random-offset>: Offset of the last octet to randomize in the template.\n"
"-P<preload>: Initiate first <preload> exchanges back to back at startup.\n"
"-r<rate>: Initiate <rate> DORA/SARR (or if -i is given, DO/SA)\n"
"    exchanges per second.  A periodic report is generated showing the\n"
"    number of exchanges which were not completed, as well as the\n"
"    average response latency.  The program continues until\n"
"    interrupted, at which point a final report is generated.\n"
"-R<range>: Specify how many different clients are used. With 1\n"
"    (the default), all requests seem to come from the same client.\n"
"-s<seed>: Specify the seed for randomization, making it repeatable.\n"
"-S<srvid-offset>: Offset of the server-ID option in the\n"
"    (second/request) template.\n"
"-T<template-file>: The name of a file containing the template to use\n"
"    as a stream of hexadecimal digits.\n"
"-v: Report the version number of this program.\n"
"-w<wrapped>: Command to call with start/stop at the beginning/end of\n"
"    the program.\n"
"-x<diagnostic-selector>: Include extended diagnostics in the output.\n"
"    <diagnostic-selector> is a string of single-keywords specifying\n"
"    the operations for which verbose output is desired.  The selector\n"
"    keyletters are:\n"
"   * 'a': print the decoded command line arguments\n"
"   * 'e': print the exit reason\n"
"   * 'i': print rate processing details\n"
"   * 'r': print randomization details\n"
"   * 's': print first server-id\n"
"   * 't': when finished, print timers of all successful exchanges\n"
"   * 'T': when finished, print templates\n"
"-X<xid-offset>: Transaction ID (aka. xid) offset in the template.\n"
"\n"
"DHCPv4 only options:\n"
"-B: Force broadcast handling.\n"
"\n"
"DHCPv6 only options:\n"
"-c: Add a rapid commit option (exchanges will be SA).\n"
"\n"
"The remaining options are used only in conjunction with -r:\n"
"\n"
"-D<max-drop>: Abort the test if more than <max-drop> requests have\n"
"    been dropped.  Use -D0 to abort if even a single request has been\n"
"    dropped.  If <max-drop> includes the suffix '%', it specifies a\n"
"    maximum percentage of requests that may be dropped before abort.\n"
"    In this case, testing of the threshold begins after 10 requests\n"
"    have been expected to be received.\n"
"-n<num-request>: Initiate <num-request> transactions.  No report is\n"
"    generated until all transactions have been initiated/waited-for,\n"
"    after which a report is generated and the program terminates.\n"
"-p<test-period>: Send requests for the given test period, which is\n"
"    specified in the same manner as -d.  This can be used as an\n"
"    alternative to -n, or both options can be given, in which case the\n"
"    testing is completed when either limit is reached.\n"
"-t<report>: Delay in seconds between two periodic reports.\n"
"\n"
"Errors:\n"
"- tooshort: received a too short message\n"
"- orphans: received a message which doesn't match an exchange\n"
"   (duplicate, late or not related)\n"
"- locallimit: reached to local system limits when sending a message.\n"
"\n"
"Exit status:\n"
"The exit status is:\n"
"0 on complete success.\n"
"1 for a general error.\n"
"2 if an error is found in the command line arguments.\n"
"3 if there are no general failures in operation, but one or more\n"
"  exchanges are not successfully completed.\n");
}

void
CommandOptions::version() const {
	fprintf(stdout, "version 0.01\n");
}


} // namespace perfdhcp
} // namespace isc
