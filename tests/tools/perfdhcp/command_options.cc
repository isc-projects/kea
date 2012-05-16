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

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

#include "command_options.h"

using namespace std;
using namespace isc;

namespace isc {
namespace perfdhcp {

// Reset stored values to the defaults.
void
CommandOptions::reset() {
    uint8_t mac[6] = { 0x0, 0xC, 0x1, 0x2, 0x3, 0x4 };
    double lt[2] = { 1., 1. };

    ipversion_ = 4;
    exchange_mode_ = DORR_SARR;
    rate_ = 0;
    report_delay_ = 0;
    random_range_ = 0;
    max_random_ = 0;
    mac_prefix_.assign(mac, mac+6);
    base_.resize(0);
    num_request_.resize(0);
    period_ = 0;
    lost_time_set_ = 0;
    lost_time_.assign(lt, lt+2);
    max_drop_set_ = 0;
    max_drop_.push_back(0);
    max_drop_.push_back(0);
    max_pdrop_.push_back(0.);
    max_pdrop_.push_back(0.);
    localname_.resize(0);
    is_interface_ = false;
    preload_ = 0;
    aggressivity_ = 1;
    local_port_ = 0;
    seeded_ = false;
    seed_ = 0;
    broadcast_ = false;
    rapid_commit_ = false;
    use_first_ = false;
    template_file_.resize(0);
    xid_offset_.resize(0);
    rnd_offset_.resize(0);
    elp_offset_ = -1;
    sid_offset_ = -1;
    rip_offset_ = -1;
    diags_.resize(0);
    wrapped_.resize(0);
    server_name_.resize(0);
}

int
CommandOptions::parse(int argc, char** argv, bool force_reset /*=false */) {
    int ch;
    if (force_reset) {
        reset();
    }
    // Reset internal variable used by getopt to index elements
    optind = 1;
    while((ch = getopt(argc, argv, "hv46r:t:R:b:n:p:d:D:l:P:a:L:s:iBc1T:X:O:E:S:I:x:w:")) != -1) {
        switch (ch) {
        case 'h':
            usage();
            break;
        default:
            ;
        }
    }
    return(0);
}

void
CommandOptions::usage(void)
{
	fprintf(stderr, "%s",
"perfdhcp [-hv] [-4|-6] [-r<rate>] [-t<report>] [-R<range>] [-b<base>]\n"
"    [-n<num-request>] [-p<test-period>] [-d<drop-time>] [-D<max-drop>]\n"
"    [-l<local-addr|interface>] [-P<preload>] [-a<aggressivity>]\n"
"    [-L<local-port>] [-s<seed>] [-i] [-B] [-c] [-1]\n"
"    [-T<template-file>] [-X<xid-offset>] [-O<random-offset]\n"
"    [-E<time-offset>] [-S<srvid-offset>] [-I<ip-offset>]\n"
"    [-x<diagnostic-selector>] [-w<wrapped>] [server]\n"
"\f\n"
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
"-b<base>: The base MAC, DUID, IP, etc, used to simulate different\n"
"    clients.  This can be specified multiple times, each instance is\n"
"    in the <type>=<value> form, for instance:\n"
"    (and default) MAC=00:0c:01:02:03:04.\n"
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

} // namespace perfdhcp
} // namespace isc
