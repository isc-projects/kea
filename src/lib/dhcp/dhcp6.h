// Copyright (C) 2006-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP6_H
#define DHCP6_H

#include <stdint.h>

/// @note Code points in comments are those assigned by IANA
/// but not yet implemented in Kea.
/// To implement a standard option, remove the comment characters,
/// add an entry in std_option_defs.h, add a stdOptionDefs6 unit test
/// in tests/libdhcp++_unittest.cc and update dhcp6-std-options-list in
/// the dhcp6-srv.xml source file of the user guide.

/* DHCPv6 Option codes: */
enum DHCPv6OptionType {
   D6O_CLIENTID                            = 1, /* RFC8415 */
   D6O_SERVERID                            = 2, /* RFC8415 */
   D6O_IA_NA                               = 3, /* RFC8415 */
   D6O_IA_TA                               = 4, /* RFC8415 */
   D6O_IAADDR                              = 5, /* RFC8415 */
   D6O_ORO                                 = 6, /* RFC8415 */
   D6O_PREFERENCE                          = 7, /* RFC8415 */
   D6O_ELAPSED_TIME                        = 8, /* RFC8415 */
   D6O_RELAY_MSG                           = 9, /* RFC8415 */
   // Option code 10 is unassigned.
   D6O_AUTH                                = 11, /* RFC8415 */
   D6O_UNICAST                             = 12, /* RFC8415 */
   D6O_STATUS_CODE                         = 13, /* RFC8415 */
   D6O_RAPID_COMMIT                        = 14, /* RFC8415 */
   D6O_USER_CLASS                          = 15, /* RFC8415 */
   D6O_VENDOR_CLASS                        = 16, /* RFC8415 */
   D6O_VENDOR_OPTS                         = 17, /* RFC8415 */
   D6O_INTERFACE_ID                        = 18, /* RFC8415 */
   D6O_RECONF_MSG                          = 19, /* RFC8415 */
   D6O_RECONF_ACCEPT                       = 20, /* RFC8415 */
   D6O_SIP_SERVERS_DNS                     = 21, /* RFC3319 */
   D6O_SIP_SERVERS_ADDR                    = 22, /* RFC3319 */
   D6O_NAME_SERVERS                        = 23, /* RFC3646 */
   D6O_DOMAIN_SEARCH                       = 24, /* RFC3646 */
   D6O_IA_PD                               = 25, /* RFC8415, RFC3633 */
   D6O_IAPREFIX                            = 26, /* RFC8415, RFC3633 */
   D6O_NIS_SERVERS                         = 27, /* RFC3898 */
   D6O_NISP_SERVERS                        = 28, /* RFC3898 */
   D6O_NIS_DOMAIN_NAME                     = 29, /* RFC3898 */
   D6O_NISP_DOMAIN_NAME                    = 30, /* RFC3898 */
   D6O_SNTP_SERVERS                        = 31, /* RFC4075 */
   D6O_INFORMATION_REFRESH_TIME            = 32, /* RFC8415, RFC4242 */
   D6O_BCMCS_SERVER_D                      = 33, /* RFC4280 */
   D6O_BCMCS_SERVER_A                      = 34, /* RFC4280 */
   // Option code 35 is unassigned.
   D6O_GEOCONF_CIVIC                       = 36, /* RFC4776 */
   D6O_REMOTE_ID                           = 37, /* RFC4649 */
   D6O_SUBSCRIBER_ID                       = 38, /* RFC4580 */
   D6O_CLIENT_FQDN                         = 39, /* RFC4704 */
   D6O_PANA_AGENT                          = 40, /* RFC5192 */
   D6O_NEW_POSIX_TIMEZONE                  = 41, /* RFC4833 */
   D6O_NEW_TZDB_TIMEZONE                   = 42, /* RFC4833 */
   D6O_ERO                                 = 43, /* RFC4994 */
   D6O_LQ_QUERY                            = 44, /* RFC5007 */
   D6O_CLIENT_DATA                         = 45, /* RFC5007 */
   D6O_CLT_TIME                            = 46, /* RFC5007 */
   D6O_LQ_RELAY_DATA                       = 47, /* RFC5007 */
   D6O_LQ_CLIENT_LINK                      = 48, /* RFC5007 */
// D6O_MIP6_HNIDF                          = 49, /* RFC6610 */
// D6O_MIP6_VDINF                          = 50, /* RFC6610 */
   D6O_V6_LOST                             = 51, /* RFC5223 */
   D6O_CAPWAP_AC_V6                        = 52, /* RFC5417 */
   D6O_RELAY_ID                            = 53, /* RFC5460 */
// D6O_IPV6_ADDRESS_MOS                    = 54, /* RFC5678 */
// D6O_IPV6_FQDN_MOS                       = 55, /* RFC5678 */
// D6O_NTP_SERVER                          = 56, /* RFC5908 */
   D6O_V6_ACCESS_DOMAIN                    = 57, /* RFC5986 */
   D6O_SIP_UA_CS_LIST                      = 58, /* RFC6011 */
   D6O_BOOTFILE_URL                        = 59, /* RFC5970 */
   D6O_BOOTFILE_PARAM                      = 60, /* RFC5970 */
   D6O_CLIENT_ARCH_TYPE                    = 61, /* RFC5970 */
   D6O_NII                                 = 62, /* RFC5970 */
// D6O_GEOLOCATION                         = 63, /* RFC6225 */
   D6O_AFTR_NAME                           = 64, /* RFC6334 */
   D6O_ERP_LOCAL_DOMAIN_NAME               = 65, /* RFC6440 */
   D6O_RSOO                                = 66, /* RFC6422 */
   D6O_PD_EXCLUDE                          = 67, /* RFC6603 */
// D6O_VSS                                 = 68, /* RFC6607 */
// D6O_MIP6_IDINF                          = 69, /* RFC6610 */
// D6O_MIP6_UDINF                          = 70, /* RFC6610 */
// D6O_MIP6_HNP                            = 71, /* RFC6610 */
// D6O_MIP6_HAA                            = 72, /* RFC6610 */
// D6O_MIP6_HAF                            = 73, /* RFC6610 */
   D6O_RDNSS_SELECTION                     = 74, /* RFC6731 */
// D6O_KRB_PRINCIPAL_NAME                  = 75, /* RFC6784 */
// D6O_KRB_REALM_NAME                      = 76, /* RFC6784 */
// D6O_KRB_DEFAULT_REALM_NAME              = 77, /* RFC6784 */
// D6O_KRB_KDC                             = 78, /* RFC6784 */
   D6O_CLIENT_LINKLAYER_ADDR               = 79, /* RFC6939 */
   D6O_LINK_ADDRESS                        = 80, /* RFC6977 */
// D6O_RADIUS                              = 81, /* RFC7037 */
   D6O_SOL_MAX_RT                          = 82, /* RFC8415, RFC7083 */
   D6O_INF_MAX_RT                          = 83, /* RFC8415, RFC7083 */
// D6O_ADDRSEL                             = 84, /* RFC7078 */
// D6O_ADDRSEL_TABLE                       = 85, /* RFC7078 */
// D6O_V6_PCP_SERVER                       = 86, /* RFC7291 */
   D6O_DHCPV4_MSG                          = 87, /* RFC7341 */
   D6O_DHCPV4_O_DHCPV6_SERVER              = 88, /* RFC7341 */
   D6O_S46_RULE                            = 89, /* RFC7598 */
   D6O_S46_BR                              = 90, /* RFC7598, RFC8539 */
   D6O_S46_DMR                             = 91, /* RFC7598 */
   D6O_S46_V4V6BIND                        = 92, /* RFC7598 */
   D6O_S46_PORTPARAMS                      = 93, /* RFC7598 */
   D6O_S46_CONT_MAPE                       = 94, /* RFC7598 */
   D6O_S46_CONT_MAPT                       = 95, /* RFC7598 */
   D6O_S46_CONT_LW                         = 96, /* RFC7598 */
// D6O_4RD                                 = 97, /* RFC7600 */
// D6O_4RD_MAP_RULE                        = 98, /* RFC7600 */
// D6O_4RD_NON_MAP_RULE                    = 99, /* RFC7600 */
// D6O_LQ_BASE_TIME                       = 100, /* RFC7653 */
// D6O_LQ_START_TIME                      = 101, /* RFC7653 */
// D6O_LQ_END_TIME                        = 102, /* RFC7653 */
   D6O_V6_CAPTIVE_PORTAL                  = 103, /* RFC8910 */
// D6O_MPL_PARAMETERS                     = 104, /* RFC7774 */
// D6O_ANI_ATT                            = 105, /* RFC7839 */
// D6O_ANI_NETWORK_NAME                   = 106, /* RFC7839 */
// D6O_ANI_AP_NAME                        = 107, /* RFC7839 */
// D6O_ANI_AP_BSSID                       = 108, /* RFC7839 */
// D6O_ANI_OPERATOR_ID                    = 109, /* RFC7839 */
// D6O_ANI_OPERATOR_REALM                 = 110, /* RFC7839 */
// D6O_S46_PRIORITY                       = 111, /* RFC8026 */
   // Option code 112 is unassigned.
// D6O_V6_PREFIX64                        = 113, /* RFC8115 */
// D6O_F_BINDING_STATUS                   = 114, /* RFC8156 */
// D6O_F_CONNECT_FLAGS                    = 115, /* RFC8156 */
// D6O_F_DNS_REMOVAL_INFO                 = 116, /* RFC8156 */
// D6O_F_DNS_HOST_NAME                    = 117, /* RFC8156 */
// D6O_F_DNS_ZONE_NAME                    = 118, /* RFC8156 */
// D6O_F_DNS_FLAGS                        = 119, /* RFC8156 */
// D6O_F_EXPIRATION_TIME                  = 120, /* RFC8156 */
// D6O_F_MAX_UNACKED_BNDUPD               = 121, /* RFC8156 */
// D6O_F_MCLT                             = 122, /* RFC8156 */
// D6O_F_PARTNER_LIFETIME                 = 123, /* RFC8156 */
// D6O_F_PARTNER_LIFETIME_SENT            = 124, /* RFC8156 */
// D6O_F_PARTNER_DOWN_TIME                = 125, /* RFC8156 */
// D6O_F_PARTNER_RAW_CLT_TIME             = 126, /* RFC8156 */
// D6O_F_PROTOCOL_VERSION                 = 127, /* RFC8156 */
// D6O_F_KEEPALIVE_TIME                   = 128, /* RFC8156 */
// D6O_F_RECONFIGURE_DATA                 = 129, /* RFC8156 */
// D6O_F_RELATIONSHIP_NAME                = 130, /* RFC8156 */
// D6O_F_SERVER_FLAGS                     = 131, /* RFC8156 */
// D6O_F_SERVER_STATE                     = 132, /* RFC8156 */
// D6O_F_START_TIME_OF_STATE              = 133, /* RFC8156 */
// D6O_F_STATE_EXPIRATION_TIME            = 134, /* RFC8156 */
   D6O_RELAY_SOURCE_PORT                  = 135, /* RFC8357 */
   D60_V6_SZTP_REDIRECT                   = 136, /* RFC8572 */
   // Option codes 137-142 are unassigned.
   D6O_IPV6_ADDRESS_ANDSF                 = 143, /* RFC6153 */
   D6O_V6_DNR                             = 144 /* RFC-ietf-add-dnr */
};

/*
 * Status Codes, from RFC 8415 section 21.13, 5007, 5460.
 */
enum DHCPv6StatusCode {
   STATUS_Success                    = 0,
   STATUS_UnspecFail                 = 1,
   STATUS_NoAddrsAvail               = 2,
   STATUS_NoBinding                  = 3,
   STATUS_NotOnLink                  = 4,
   STATUS_UseMulticast               = 5,
   STATUS_NoPrefixAvail              = 6,
   STATUS_UnknownQueryType           = 7,
   STATUS_MalformedQuery             = 8,
   STATUS_NotConfigured              = 9,
   STATUS_NotAllowed                 = 10,
   STATUS_QueryTerminated            = 11,
/* RFC7653 */
// STATUS_DataMissing                = 12,
// STATUS_CatchUpComplete            = 13,
// STATUS_NotSupported               = 14,
// STATUS_TLSConnectionRefused       = 15,
/* RFC8156 */
// STATUS_AddressInUse               = 16,
// STATUS_ConfigurationConflict      = 17,
// STATUS_MissingBindingInformation  = 18,
// STATUS_OutdatedBindingInformation = 19,
// STATUS_ServerShuttingDown         = 20,
// STATUS_DNSUpdateNotSupported      = 21,
// STATUS_ExcessiveTimeSkew          = 22
};

/*
 * DHCPv6 message types, defined in section 7.3 of RFC 8415
 */
enum DHCPv6MessageType {
   DHCPV6_NOTYPE               = 0,
   DHCPV6_SOLICIT              = 1,
   DHCPV6_ADVERTISE            = 2,
   DHCPV6_REQUEST              = 3,
   DHCPV6_CONFIRM              = 4,
   DHCPV6_RENEW                = 5,
   DHCPV6_REBIND               = 6,
   DHCPV6_REPLY                = 7,
   DHCPV6_RELEASE              = 8,
   DHCPV6_DECLINE              = 9,
   DHCPV6_RECONFIGURE          = 10,
   DHCPV6_INFORMATION_REQUEST  = 11,
   DHCPV6_RELAY_FORW           = 12,
   DHCPV6_RELAY_REPL           = 13,
   /* RFC 5007 */
   DHCPV6_LEASEQUERY           = 14,
   DHCPV6_LEASEQUERY_REPLY     = 15,
   /* RFC 5460 */
   DHCPV6_LEASEQUERY_DONE      = 16,
   DHCPV6_LEASEQUERY_DATA      = 17,
   /* RFC 6977 */
   DHCPV6_RECONFIGURE_REQUEST  = 18,
    DHCPV6_RECONFIGURE_REPLY   = 19,
   /* RFC 7341 */
   DHCPV6_DHCPV4_QUERY         = 20,
   DHCPV6_DHCPV4_RESPONSE      = 21,
   /* RFC 7653 */
   DHCPV6_ACTIVELEASEQUERY     = 22,
   DHCPV6_STARTTLS             = 23,
   /* RFC 8156 */
   DHCPV6_BNDUPD               = 24,
   DHCPV6_BNDREPLY             = 25,
   DHCPV6_POOLREQ              = 26,
   DHCPV6_POOLRESP             = 27,
   DHCPV6_UPDREQ               = 28,
   DHCPV6_UPDREQALL            = 29,
   DHCPV6_UPDDONE              = 30,
   DHCPV6_CONNECT              = 31,
   DHCPV6_CONNECTREPLY         = 32,
   DHCPV6_DISCONNECT           = 33,
   DHCPV6_STATE                = 34,
   DHCPV6_CONTACT              = 35,
   DHCPV6_TYPES_EOF
};

extern const char *dhcpv6_type_names[];
extern const int dhcpv6_type_name_max;

// DUID type definitions (RFC 8415 section 11).
// see isc::dhcp::DUID::DUIDType enum in dhcp/duid.h

// Define hardware types
// Taken from http://www.iana.org/assignments/arp-parameters/
static const uint16_t HWTYPE_ETHERNET = 0x0001;
static const uint16_t HWTYPE_INFINIBAND = 0x0020;

// Taken from https://www.iana.org/assignments/enterprise-numbers/enterprise-numbers
static const uint32_t ENTERPRISE_ID_ISC = 2495;

/* DHCPv4-over-DHCPv6 (RFC 7341) inter-process communication. These are option
   codes for the ISC vendor specific options used in 4o6 */
static const uint16_t ISC_V6_4O6_INTERFACE = 60000;
static const uint16_t ISC_V6_4O6_SRC_ADDRESS = 60001;
static const uint16_t ISC_V6_4O6_SRC_PORT = 60002;

/* Offsets into IA_*'s where Option spaces commence.  */
static const uint16_t IA_NA_OFFSET = 12; /* IAID, T1, T2, all 4 octets each */
static const uint16_t IA_TA_OFFSET = 4; /* IAID only, 4 octets */
static const uint16_t IA_PD_OFFSET = 12; /* IAID, T1, T2, all 4 octets each */

/* Offset into IAADDR's where Option spaces commence. */
static const uint16_t IAADDR_OFFSET = 24;

/* Offset into IAPREFIX's where Option spaces commence. */
static const uint16_t IAPREFIX_OFFSET = 25;

/* Offset into LQ_QUERY's where Option spaces commence. */
static const uint16_t LQ_QUERY_OFFSET = 17;

/*
 * DHCPv6 well-known multicast addresses, from section 7.1 of RFC 8415
 */
// TODO
#define ALL_DHCP_RELAY_AGENTS_AND_SERVERS "ff02::1:2"
#define ALL_DHCP_SERVERS "ff05::1:3"

static const uint16_t DHCP6_CLIENT_PORT = 546;
static const uint16_t DHCP6_SERVER_PORT = 547;

/*
 * DHCPv6 Retransmission Constants (RFC 8415 section 7.6, RFC 5007)
 */

// TODO
#define SOL_MAX_DELAY     1
#define SOL_TIMEOUT       1
#define SOL_MAX_RT      120
#define REQ_TIMEOUT       1
#define REQ_MAX_RT       30
#define REQ_MAX_RC       10
#define CNF_MAX_DELAY     1
#define CNF_TIMEOUT       1
#define CNF_MAX_RT        4
#define CNF_MAX_RD       10
#define REN_TIMEOUT      10
#define REN_MAX_RT      600
#define REB_TIMEOUT      10
#define REB_MAX_RT      600
#define INF_MAX_DELAY     1
#define INF_TIMEOUT       1
#define INF_MAX_RT      120
#define REL_TIMEOUT       1
#define REL_MAX_RC        5
#define DEC_TIMEOUT       1
#define DEC_MAX_RC        5
#define REC_TIMEOUT       2
#define REC_MAX_RC        8
#define HOP_COUNT_LIMIT  32
#define LQ6_TIMEOUT       1
#define LQ6_MAX_RT       10
#define LQ6_MAX_RC        5

/* Leasequery query-types (RFC 5007, RFC 5460) */

#define LQ6QT_BY_ADDRESS        1
#define LQ6QT_BY_CLIENTID       2
#define LQ6QT_BY_RELAY_ID       3
#define LQ6QT_BY_LINK_ADDRESS   4
#define LQ6QT_BY_REMOTE_ID      5

/*
 * DUID time starts 2000-01-01.
 * This constant is the number of seconds since 1970-01-01,
 * when the Unix epoch began.
 */
#define DUID_TIME_EPOCH 946684800

/* Information-Request Time option (RFC 8415) */

#define IRT_DEFAULT     86400
#define IRT_MINIMUM     600

/* DHCPv4-query message flags (see RFC7341) */
#define DHCPV4_QUERY_FLAGS_UNICAST (1 << 23)

#endif /* DHCP6_H */
