/*
 * Copyright (c) 2004-2011, 2014-2015 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1995-2003 by Internet Software Consortium
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *   Internet Systems Consortium, Inc.
 *   950 Charter Street
 *   Redwood City, CA 94063
 *   <info@isc.org>
 *   https://www.isc.org/
 *
 * This software has been written for Internet Systems Consortium
 * by Ted Lemon in cooperation with Vixie Enterprises.  To learn more
 * about Internet Systems Consortium, see ``https://www.isc.org''.
 * To learn more about Vixie Enterprises, see ``http://www.vix.com''.
 */

/*
 * NOTE: This files is imported from ISC DHCP. It uses C notation.
 *       Format kept for easier merge.
 */

#ifndef DHCP_H
#define DHCP_H

#include <stdint.h>

/// @note Code points in comments are those assigned by IANA
/// but not yet implemented in Kea.
/// To implement a standard option, remove the comment characters,
/// add an entry in std_option_defs.h, add a stdOptionDefs4 unit test
/// in tests/libdhcp++_unittest.cc and update dhcp4-std-options-list-part2
/// in the dhcp4-srv.xml source file of the user guide.

namespace isc {
namespace dhcp {

/* IPv4 Broadcast address */
#define DHCP_IPV4_BROADCAST_ADDRESS "255.255.255.255"

/* BOOTP (rfc951) message types */
enum BOOTPTypes {
    BOOTREQUEST = 1,
    BOOTREPLY = 2
};

/* Possible values for flags field... */
static const uint16_t BOOTP_BROADCAST = 32768L;

/* Possible values for hardware type (htype) field... */
enum HType {
    HTYPE_ETHER = 1,   /* Ethernet 10Mbps */
    HTYPE_DOCSIS = 1,  /* The traffic captures we have from cable modems as well
                          as this list by IANA: http://www.iana.org/assignments/
                          arp-parameters/arp-parameters.xhtml suggest that
                          Ethernet (1) should be used in DOCSIS environment. */
    HTYPE_IEEE802 = 6, /* IEEE 802.2 Token Ring */
    HTYPE_FDDI = 8     /* FDDI */
    /// TODO Add infiniband here
};

/* DHCP Option codes: */
enum DHCPOptionType {
    DHO_PAD                          = 0,
    DHO_SUBNET_MASK                  = 1,
    DHO_TIME_OFFSET                  = 2,
    DHO_ROUTERS                      = 3,
    DHO_TIME_SERVERS                 = 4,
    DHO_NAME_SERVERS                 = 5,
    DHO_DOMAIN_NAME_SERVERS          = 6,
    DHO_LOG_SERVERS                  = 7,
    DHO_COOKIE_SERVERS               = 8,
    DHO_LPR_SERVERS                  = 9,
    DHO_IMPRESS_SERVERS              = 10,
    DHO_RESOURCE_LOCATION_SERVERS    = 11,
    DHO_HOST_NAME                    = 12,
    DHO_BOOT_SIZE                    = 13,
    DHO_MERIT_DUMP                   = 14,
    DHO_DOMAIN_NAME                  = 15,
    DHO_SWAP_SERVER                  = 16,
    DHO_ROOT_PATH                    = 17,
    DHO_EXTENSIONS_PATH              = 18,
    DHO_IP_FORWARDING                = 19,
    DHO_NON_LOCAL_SOURCE_ROUTING     = 20,
    DHO_POLICY_FILTER                = 21,
    DHO_MAX_DGRAM_REASSEMBLY         = 22,
    DHO_DEFAULT_IP_TTL               = 23,
    DHO_PATH_MTU_AGING_TIMEOUT       = 24,
    DHO_PATH_MTU_PLATEAU_TABLE       = 25,
    DHO_INTERFACE_MTU                = 26,
    DHO_ALL_SUBNETS_LOCAL            = 27,
    DHO_BROADCAST_ADDRESS            = 28,
    DHO_PERFORM_MASK_DISCOVERY       = 29,
    DHO_MASK_SUPPLIER                = 30,
    DHO_ROUTER_DISCOVERY             = 31,
    DHO_ROUTER_SOLICITATION_ADDRESS  = 32,
    DHO_STATIC_ROUTES                = 33,
    DHO_TRAILER_ENCAPSULATION        = 34,
    DHO_ARP_CACHE_TIMEOUT            = 35,
    DHO_IEEE802_3_ENCAPSULATION      = 36,
    DHO_DEFAULT_TCP_TTL              = 37,
    DHO_TCP_KEEPALIVE_INTERVAL       = 38,
    DHO_TCP_KEEPALIVE_GARBAGE        = 39,
    DHO_NIS_DOMAIN                   = 40,
    DHO_NIS_SERVERS                  = 41,
    DHO_NTP_SERVERS                  = 42,
    DHO_VENDOR_ENCAPSULATED_OPTIONS  = 43,
    DHO_NETBIOS_NAME_SERVERS         = 44,
    DHO_NETBIOS_DD_SERVER            = 45,
    DHO_NETBIOS_NODE_TYPE            = 46,
    DHO_NETBIOS_SCOPE                = 47,
    DHO_FONT_SERVERS                 = 48,
    DHO_X_DISPLAY_MANAGER            = 49,
    DHO_DHCP_REQUESTED_ADDRESS       = 50,
    DHO_DHCP_LEASE_TIME              = 51,
    DHO_DHCP_OPTION_OVERLOAD         = 52,
    DHO_DHCP_MESSAGE_TYPE            = 53,
    DHO_DHCP_SERVER_IDENTIFIER       = 54,
    DHO_DHCP_PARAMETER_REQUEST_LIST  = 55,
    DHO_DHCP_MESSAGE                 = 56,
    DHO_DHCP_MAX_MESSAGE_SIZE        = 57,
    DHO_DHCP_RENEWAL_TIME            = 58,
    DHO_DHCP_REBINDING_TIME          = 59,
    DHO_VENDOR_CLASS_IDENTIFIER      = 60,
    DHO_DHCP_CLIENT_IDENTIFIER       = 61,
    DHO_NWIP_DOMAIN_NAME             = 62,
    DHO_NWIP_SUBOPTIONS              = 63,
    DHO_TFTP_SERVER_NAME             = 66,
    DHO_BOOT_FILE_NAME               = 67,
    DHO_USER_CLASS                   = 77,
    DHO_FQDN                         = 81,
    DHO_DHCP_AGENT_OPTIONS           = 82,
    DHO_AUTHENTICATE                 = 90,  /* RFC3118, was 210 */
    DHO_CLIENT_LAST_TRANSACTION_TIME = 91,
    DHO_ASSOCIATED_IP                = 92,
    DHO_SUBNET_SELECTION             = 118, /* RFC3011! */
    DHO_DOMAIN_SEARCH                = 119, /* RFC3397 */
    DHO_VIVCO_SUBOPTIONS             = 124,
    DHO_VIVSO_SUBOPTIONS             = 125,

    DHO_END                          = 255
};

/* DHCP message types. */
enum DHCPMessageType {
    DHCPDISCOVER        =  1,
    DHCPOFFER           =  2,
    DHCPREQUEST         =  3,
    DHCPDECLINE         =  4,
    DHCPACK             =  5,
    DHCPNAK             =  6,
    DHCPRELEASE         =  7,
    DHCPINFORM          =  8,
    DHCPLEASEQUERY      =  10,
    DHCPLEASEUNASSIGNED =  11,
    DHCPLEASEUNKNOWN    =  12,
    DHCPLEASEACTIVE     =  13,
    DHCPBULKLEASEQUERY  =  14,
    DHCPLEASEQUERYDONE  =  15
};

static const uint16_t DHCP4_CLIENT_PORT = 68;
static const uint16_t DHCP4_SERVER_PORT = 67;

/// Magic cookie validating dhcp options field (and bootp vendor
/// extensions field).
static const uint32_t DHCP_OPTIONS_COOKIE = 0x63825363;

/* Relay Agent Information option subtypes: */

static const uint16_t RAI_OPTION_AGENT_CIRCUIT_ID = 1; // RFC3046
static const uint16_t RAI_OPTION_REMOTE_ID = 2; // RFC3046
/* option 3 is reserved and will never be assigned */
static const uint16_t RAI_OPTION_DOCSIS_DEVICE_CLASS = 4; // RFC3256
static const uint16_t RAI_OPTION_LINK_SELECTION = 5; // RFC3527
static const uint16_t RAI_OPTION_SUBSCRIBER_ID = 6; //RFC3993
static const uint16_t RAI_OPTION_RADIUS = 7; //RFC4014
static const uint16_t RAI_OPTION_AUTH = 8; //RFC4030
static const uint16_t RAI_OPTION_VSI = 9; // RFC4243
static const uint16_t RAI_OPTION_RELAY_FLAGS = 10; // RFC5010
static const uint16_t RAI_OPTION_SERVER_ID_OVERRIDE = 11; // RFC5107
static const uint16_t RAI_OPTION_RELAY_ID = 12; //RFC6925
static const uint16_t RAI_OPTION_VIRTUAL_SUBNET_SELECT = 151; //RFC6607
static const uint16_t RAI_OPTION_VIRTUAL_SUBNET_SELECT_CTRL = 152; //RFC6607

// TODO: Following are leftovers from dhcp.h import from ISC DHCP
// They will be converted to C++-style defines once they will start
// to be used.
#if 0
/* FQDN suboptions: */
#define FQDN_NO_CLIENT_UPDATE           1
#define FQDN_SERVER_UPDATE              2
#define FQDN_ENCODED                    3
#define FQDN_RCODE1                     4
#define FQDN_RCODE2                     5
#define FQDN_HOSTNAME                   6
#define FQDN_DOMAINNAME                 7
#define FQDN_FQDN                       8
#define FQDN_SUBOPTION_COUNT            8

/* Enterprise Suboptions: */
#define VENDOR_ISC_SUBOPTIONS           2495

#endif

} // end of isc::dhcp namespace
} // end of isc namespace

#endif /* DHCP_H */
