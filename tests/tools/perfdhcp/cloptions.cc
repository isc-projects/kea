/*
 * Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include "procconf.h"
#include "perfdhcp.h"
#include "cloptions.h"

static void printHelp(const char *progName, const char *usage);

/*
 * Return value:
 * 0 if the command has been satisfied and the program should exit 0.
 * 2 for usage error, in which case an error message will have been printed.
 * 1 if argument processing was successful and the program should continue.
 */
int
procArgs(int argc, char **argv)
{
    char usage[] =
"Usage:\n\
perfdhcp [-hv] [-4|-6] [-r<rate>] [-n<num-request>] [-p<test-period>]\n\
         [-d<drop-time>] [-D<max-drop>] [-l<local-addr|interface>] [-i]\n\
         [-x<diagnostic-selector>] [server]\n";
    int v4 = 0;
    char *maxDropOpt;
    double dropTime;
    double testPeriod;

    /* Names of configuration variables, for defaults file processor */
    confvar_t optConf[] = {
	{ 'h', NULL,		CF_SWITCH,	NULL,		0 },
	{ 'v', NULL,		CF_SWITCH,	NULL,		0 },
	{ '4', NULL,		CF_SWITCH,	&v4,		1 },
	{ '6', NULL,		CF_SWITCH,	&v6,		1 },
	{ 'i', NULL,		CF_SWITCH,	&initialOnly,	1 },
	{ 'l', NULL,		CF_NE_STRING,	&localName,	0 },
	{ 'r', NULL,		CF_POS_INT,	&rate,		0 },
	{ 'x', NULL,		CF_STRING,	&diagSelector,	0 },
	{ 'd', NULL,		CF_POS_FLOAT,	&dropTime,	0 },
	{ 'D', NULL,		CF_STRING,	&maxDropOpt,	0 },
	{ 'n', NULL,		CF_POS_INT,	&numRequest,	0 },
	{ 'p', NULL,		CF_POS_FLOAT,	&testPeriod,	0 },
        { '\0', NULL,           CF_ENDLIST,	NULL,		0 }
    };

    confdata_t confdata;

    /* Process command line options and config file */
    procOpts(&argc, &argv, optConf, &confdata, NULL, progName, usage);

    if (confdata.map['h']->num > 0) {
        printHelp(progName, usage);
        return 0;
    }
    if (confdata.map['v']->num > 0) {
        printf("dhcpperf v1.0 2011-10-30\n");
        return 0;
    }

    if (v4 && v6) {
	fprintf(stderr, "Must not give -4 and -6 together.\n");
	return 2;
    }
    switch (argc) {
    case 0:
	if (v6 && localName != NULL)
	    server = "all";
	else {
	    if (v6)
		fprintf(stderr, "Use -l to specify an interface name.\n\%s\n", usage);
	    else
		fprintf(stderr, "Must specify a DHCP server.\n\%s\n", usage);
	    return 2;
	}
	break;
    case 1:
	server = argv[0];
	break;
    default:
	fprintf(stderr, "Too many arguments.\n\%s\n", usage);
	return 2;
    }
    return 1;
}

static void
printHelp(const char *progName, const char *usage)
{
    printf(
"%s: Execute a performance test against a DHCP server.\n\
%s\n\
The [server] argument is the name/address of the DHCP server to contact.  For\n\
DHCPv4 operation, exchanges are initiated by transmitting a DHCP DISCOVER to\n\
this address.  For DHCPv6 operation, exchanges are initiated by transmitting a\n\
DHCP SOLICIT to this address.  In the DHCPv6 case, the special name \"all\" can\n\
be used to refer to All_DHCP_Relay_Agents_and_Servers (the multicast address\n\
FF02::1:2), or the special name \"servers\" to refer to All_DHCP_Servers (the\n\
multicast address FF05::1:3).  The [server] argument is optional only in the\n\
case that -l is used to specify an interface, in which case [server] defaults\n\
to \"all\".\n\
\n\
Exchanges are initiated by transmitting a DHCP SOLICIT to\n\
All_DHCP_Relay_Agents_and_Servers (the multicast address FF02::1:2) via this\n\
interface.\n\
\n\
The default is to perform a single 4-way exchange, effectively pinging the\n\
server.  The -r option is used to set up a performance test.\n\
\n\
Options:\n\
-4: DHCPv4 operation (default). This is incompatible with the -6 option.\n\
-6: DHCPv6 operation. This is incompatible with the -4 option.\n\
-h: Print this help.\n\
-i: Do only the initial part of an exchange: DO or SA, depending on whether -6\n\
    is given.\n\
-l<local-addr|interface>: For DHCPv4 operation, specify the local\n\
    hostname/address to use when communicating with the server.  By default,\n\
    the interface address through which traffic would normally be routed to the\n\
    server is used.\n\
    For DHCPv6 operation, specify the name of the network interface via which\n\
    exchanges are initiated.  This must be specified unless a server name is\n\
    given, in which case the interface through which traffic would normally be\n\
    routed to the server is used.\n\
-r<rate>: Initiate <rate> DORA/SARR (or if -i is given, DO/SA) exchanges per\n\
    second.  A periodic report is generated showing the number of exchanges\n\
    which were not completed, as well as the average response latency.  The\n\
    program continues until interrupted, at which point a final report is\n\
    generated.\n\
-v: Report the version number of this program.\n\
-x<diagnostic-selector>: Include extended diagnostics in the output.\n\
    <diagnostic-selector> is a string of single-keywords specifying the\n\
    operations for which verbose output is desired.  The selector keyletters\n\
    are:\n\
    [TO BE ADDED]\n\
\n\
The remaining options are used only in conjunction with -r:\n\
\n\
-d<drop-time>: Specify the time after which a request is treated as having been\n\
    lost.  The value is given in seconds and may contain a fractional\n\
    component.  The default is 1 second.\n\
-D<max-drop>: Abort the test if more than <max-drop> requests have been\n\
    dropped.  Use -D0 to abort if even a single request has been dropped.  If\n\
    <max-drop> includes the suffix \"%%\", it specifies a maximum percentage of\n\
    requests that may be dropped before abort.  In this case, testing of the\n\
    threshold begins after 10 requests have been expected to be received.\n\
-n<num-request>: Initiate <num-request> transactions.  No report is generated\n\
    until all transactions have been initiated/waited-for, after which a report\n\
    is generated and the program terminates.\n\
-p<test-period>: Send requests for the given test period, which is specified in\n\
    the same manner as -d.  This can be used as an alternative to -n, or both\n\
    options can be given, in which case the testing is completed when either\n\
    limit is reached.\n\
\n\
Exit status:\n\
The exit status is:\n\
0 on complete success.\n\
1 for a general error.\n\
2 if an error is found in the command line arguments.\n\
3 if there are no general failures in operation, but one or more exchanges are\n\
  not successfully completed.\n",
		    progName, usage);
}
