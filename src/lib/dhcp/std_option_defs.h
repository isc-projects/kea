// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef STD_OPTION_DEFS_H
#define STD_OPTION_DEFS_H

#include <dhcp/option_data_types.h>

namespace {

/// @brief Declare an array holding parameters used to create instance
/// of a definition for option comprising a record of data fields.
///
/// @param name name of the array being declared.
/// @param types data types of fields that belong to the record.
#ifndef RECORD_DECL
#define RECORD_DECL(name, types...) static OptionDataType name[] = { types }
#endif

/// @brief A pair of values: one pointing to the array holding types of
/// data fields belonging to the record, and size of this array.
///
/// @param name name of the array holding data fields' types.
#ifndef RECORD_DEF
#define RECORD_DEF(name) name, sizeof(name) / sizeof(name[0])
#endif

using namespace isc::dhcp;

/// @brief Parameters being used to make up an option definition.
struct OptionDefParams {
    const char* name;         // option name
    uint16_t code;            // option code
    OptionDataType type;      // data type
    bool array;               // is array
    OptionDataType* records;  // record fields
    size_t records_size;      // number of fields in a record
};

// fqdn option record fields.
//
// Note that the flags field indicates the type of domain
// name encoding. There is a choice between deprecated
// ASCII encoding and compressed encoding described in
// RFC 1035, section 3.1. The latter could be handled
// by OPT_FQDN_TYPE but we can't use it here because
// clients may request ASCII encoding.
RECORD_DECL(FQDN_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_STRING_TYPE);

/// @brief Definitions of standard DHCPv4 options.
static const OptionDefParams OPTION_DEF_PARAMS4[] = {
    { "subnet-mask", DHO_SUBNET_MASK, OPT_IPV4_ADDRESS_TYPE, false },
    { "time-offset", DHO_TIME_OFFSET, OPT_UINT32_TYPE, false },
    { "routers", DHO_ROUTERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "time-servers", DHO_TIME_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "name-servers", DHO_NAME_SERVERS, OPT_IPV4_ADDRESS_TYPE,
      false },
    { "domain-name-servers", DHO_DOMAIN_NAME_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "log-servers", DHO_LOG_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "cookie-servers", DHO_COOKIE_SERVERS, OPT_IPV4_ADDRESS_TYPE,
      true },
    { "lpr-servers", DHO_LPR_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "impress-servers", DHO_IMPRESS_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "resource-location-servers", DHO_RESOURCE_LOCATION_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "host-name", DHO_HOST_NAME, OPT_STRING_TYPE, false },
    { "boot-size", DHO_BOOT_SIZE, OPT_UINT16_TYPE, false },
    { "merit-dump", DHO_MERIT_DUMP, OPT_STRING_TYPE, false },
    { "domain-name", DHO_DOMAIN_NAME, OPT_FQDN_TYPE, false },
    { "swap-server", DHO_SWAP_SERVER, OPT_IPV4_ADDRESS_TYPE, false },
    { "root-path", DHO_ROOT_PATH, OPT_STRING_TYPE, false },
    { "extensions-path", DHO_EXTENSIONS_PATH, OPT_STRING_TYPE,
      false },
    { "ip-forwarding", DHO_IP_FORWARDING, OPT_BOOLEAN_TYPE, false },
    { "non-local-source-routing", DHO_NON_LOCAL_SOURCE_ROUTING,
      OPT_BOOLEAN_TYPE, false },
    { "policy-filter", DHO_POLICY_FILTER, OPT_IPV4_ADDRESS_TYPE, true },
    { "max-dgram-reassembly", DHO_MAX_DGRAM_REASSEMBLY,
      OPT_UINT16_TYPE, false },
    { "default-ip-ttl", DHO_DEFAULT_IP_TTL, OPT_UINT8_TYPE, false },
    { "path-mtu-aging-timeout", DHO_PATH_MTU_AGING_TIMEOUT,
      OPT_UINT32_TYPE, false },
    { "path-mtu-plateau-table", DHO_PATH_MTU_PLATEAU_TABLE,
      OPT_UINT16_TYPE, true },
    { "interface-mtu", DHO_INTERFACE_MTU, OPT_UINT16_TYPE, false },
    { "all-subnets-local", DHO_ALL_SUBNETS_LOCAL,
      OPT_BOOLEAN_TYPE, false },
    { "broadcast-address", DHO_BROADCAST_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false },
    { "perform-mask-discovery", DHO_PERFORM_MASK_DISCOVERY,
      OPT_BOOLEAN_TYPE, false },
    { "mask-supplier", DHO_MASK_SUPPLIER, OPT_BOOLEAN_TYPE, false },
    { "router-discovery", DHO_ROUTER_DISCOVERY,
      OPT_BOOLEAN_TYPE, false },
    { "router-solicitation-address", DHO_ROUTER_SOLICITATION_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false },
    { "static-routes", DHO_STATIC_ROUTES,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "trailer-encapsulation", DHO_TRAILER_ENCAPSULATION,
      OPT_BOOLEAN_TYPE, false },
    { "arp-cache-timeout", DHO_ARP_CACHE_TIMEOUT,
      OPT_UINT32_TYPE, false },
    { "ieee802-3-encapsulation", DHO_IEEE802_3_ENCAPSULATION,
      OPT_BOOLEAN_TYPE, false },
    { "default-tcp-ttl", DHO_DEFAULT_TCP_TTL, OPT_UINT8_TYPE, false },
    { "tcp-keepalive-internal", DHO_TCP_KEEPALIVE_INTERVAL,
      OPT_UINT32_TYPE, false },
    { "tcp-keepalive-garbage", DHO_TCP_KEEPALIVE_GARBAGE,
      OPT_BOOLEAN_TYPE, false },
    { "nis-domain", DHO_NIS_DOMAIN, OPT_STRING_TYPE, false },
    { "nis-servers", DHO_NIS_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "ntp-servers", DHO_NTP_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "vendor-encapsulated-options", DHO_VENDOR_ENCAPSULATED_OPTIONS,
      OPT_BINARY_TYPE, false },
    { "netbios-name-servers", DHO_NETBIOS_NAME_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "netbios-dd-server", DHO_NETBIOS_DD_SERVER,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "netbios-node-type", DHO_NETBIOS_NODE_TYPE,
      OPT_UINT8_TYPE, false },
    { "netbios-scope", DHO_NETBIOS_SCOPE, OPT_STRING_TYPE, false },
    { "font-servers", DHO_FONT_SERVERS, OPT_IPV4_ADDRESS_TYPE, true },
    { "x-display-manager", DHO_X_DISPLAY_MANAGER,
      OPT_IPV4_ADDRESS_TYPE, true },
    { "dhcp-requested-address", DHO_DHCP_REQUESTED_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false },
    { "dhcp-lease-time", DHO_DHCP_LEASE_TIME, OPT_UINT32_TYPE, false },
    { "dhcp-option-overload", DHO_DHCP_OPTION_OVERLOAD,
      OPT_UINT8_TYPE, false },
    { "dhcp-message-type", DHO_DHCP_MESSAGE_TYPE, OPT_UINT8_TYPE, false },
    { "dhcp-server-identifier", DHO_DHCP_SERVER_IDENTIFIER,
      OPT_IPV4_ADDRESS_TYPE, false },
    { "dhcp-parameter-request-list", DHO_DHCP_PARAMETER_REQUEST_LIST,
      OPT_UINT8_TYPE, true },
    { "dhcp-message", DHO_DHCP_MESSAGE, OPT_STRING_TYPE, false },
    { "dhcp-max-message-size", DHO_DHCP_MAX_MESSAGE_SIZE,
      OPT_UINT16_TYPE, false },
    { "dhcp-renewal-time", DHO_DHCP_RENEWAL_TIME, OPT_UINT32_TYPE, false },
    { "dhcp-rebinding-time", DHO_DHCP_REBINDING_TIME,
      OPT_UINT32_TYPE, false },
    { "vendor-class-identifier", DHO_VENDOR_CLASS_IDENTIFIER,
      OPT_BINARY_TYPE, false },
    { "dhcp-client-identifier", DHO_DHCP_CLIENT_IDENTIFIER,
      OPT_BINARY_TYPE, false },
    { "nwip-domain-name", DHO_NWIP_DOMAIN_NAME, OPT_STRING_TYPE, false },
    { "nwip-suboptions", DHO_NWIP_SUBOPTIONS, OPT_BINARY_TYPE, false },
    { "user-class", DHO_USER_CLASS, OPT_BINARY_TYPE, false },
    { "fqdn", DHO_FQDN, OPT_RECORD_TYPE, false, RECORD_DEF(FQDN_RECORDS) },
    { "dhcp-agent-options", DHO_DHCP_AGENT_OPTIONS,
      OPT_BINARY_TYPE, false },
    // Unfortunatelly the AUTHENTICATE option contains a 64-bit
    // data field called 'replay-detection' that can't be added
    // as a record field to a custom option. Also, there is no
    // dedicated option class to handle it so we simply return
    // binary option type for now.
    // @todo implement a class to handle AUTH option.
    { "authenticate", DHO_AUTHENTICATE, OPT_BINARY_TYPE, false },
    { "client-last-transaction-time", DHO_CLIENT_LAST_TRANSACTION_TIME,
      OPT_UINT32_TYPE, false },
    { "associated-ip", DHO_ASSOCIATED_IP, OPT_IPV4_ADDRESS_TYPE, true },
    { "subnet-selection", DHO_SUBNET_SELECTION,
      OPT_IPV4_ADDRESS_TYPE, false },
    // The following options need a special encoding of data
    // being carried by them. Therefore, there is no way they can
    // be handled by OptionCustom. We may need to implement
    // dedicated classes to handle them. Until that happens
    // let's treat them as 'binary' options.
    { "domain-search", DHO_DOMAIN_SEARCH, OPT_BINARY_TYPE, false },
    { "vivco-suboptions", DHO_VIVCO_SUBOPTIONS,
      OPT_BINARY_TYPE, false },
    { "vivso-suboptions", DHO_VIVSO_SUBOPTIONS, OPT_BINARY_TYPE,
      false }

        // @todo add definitions for all remaning options.
};

/// Number of option definitions defined.
const int OPTION_DEF_PARAMS_SIZE4  =
    sizeof(OPTION_DEF_PARAMS4) / sizeof(OPTION_DEF_PARAMS4[0]);


/// Start Definition of DHCPv6 options

// client-fqdn
RECORD_DECL(clientFqdnRecords, OPT_UINT8_TYPE, OPT_FQDN_TYPE);
// geoconf-civic
RECORD_DECL(geoconfCivicRecords, OPT_UINT8_TYPE, OPT_UINT16_TYPE,
            OPT_BINARY_TYPE);
// iaddr
RECORD_DECL(iaaddrRecords, OPT_IPV6_ADDRESS_TYPE, OPT_UINT32_TYPE,
            OPT_UINT32_TYPE);
// ia-na
RECORD_DECL(ianaRecords, OPT_UINT32_TYPE, OPT_UINT32_TYPE, OPT_UINT32_TYPE);
// ia-pd
RECORD_DECL(iapdRecords, OPT_UINT32_TYPE, OPT_UINT32_TYPE, OPT_UINT32_TYPE);
// ia-prefix
RECORD_DECL(iaPrefixRecords, OPT_UINT32_TYPE, OPT_UINT32_TYPE,
            OPT_UINT8_TYPE, OPT_BINARY_TYPE);
// lq-query
RECORD_DECL(lqQueryRecords, OPT_UINT8_TYPE, OPT_IPV6_ADDRESS_TYPE);
// lq-relay-data
RECORD_DECL(lqRelayData, OPT_IPV6_ADDRESS_TYPE, OPT_BINARY_TYPE);
// remote-id
RECORD_DECL(remoteIdRecords, OPT_UINT32_TYPE, OPT_BINARY_TYPE);
// status-code
RECORD_DECL(statusCodeRecords, OPT_UINT16_TYPE, OPT_STRING_TYPE);
// vendor-class
RECORD_DECL(vendorClassRecords, OPT_UINT32_TYPE, OPT_BINARY_TYPE);
// vendor-opts
RECORD_DECL(vendorOptsRecords, OPT_UINT32_TYPE, OPT_BINARY_TYPE);

/// Standard DHCPv6 option definitions.
static const OptionDefParams OPTION_DEF_PARAMS6[] = {
    { "clientid", D6O_CLIENTID, OPT_BINARY_TYPE, false },
    { "serverid", D6O_SERVERID, OPT_BINARY_TYPE, false },
    { "ia-na", D6O_IA_NA, OPT_RECORD_TYPE, false, RECORD_DEF(ianaRecords) },
    { "ia-ta", D6O_IA_TA, OPT_UINT32_TYPE, false },
    { "iaaddr", D6O_IAADDR, OPT_RECORD_TYPE, false, RECORD_DEF(iaaddrRecords) },
    { "oro", D6O_ORO, OPT_UINT16_TYPE, true },
    { "preference", D6O_PREFERENCE, OPT_UINT8_TYPE, false },
    { "elapsed-time", D6O_ELAPSED_TIME, OPT_UINT16_TYPE, false },
    { "relay-msg", D6O_RELAY_MSG, OPT_BINARY_TYPE, false },
    // Unfortunatelly the AUTH option contains a 64-bit data field
    // called 'replay-detection' that can't be added as a record
    // field to a custom option. Also, there is no dedicated
    // option class to handle it so we simply return binary
    // option type for now.
    // @todo implement a class to handle AUTH option.
    { "auth", D6O_AUTH, OPT_BINARY_TYPE, false },
    { "unicast", D6O_UNICAST, OPT_IPV6_ADDRESS_TYPE, false },
    { "status-code", D6O_STATUS_CODE, OPT_RECORD_TYPE, false,
      RECORD_DEF(statusCodeRecords) },
    { "rapid-commit", D6O_RAPID_COMMIT, OPT_EMPTY_TYPE, false },
    { "user-class", D6O_USER_CLASS, OPT_BINARY_TYPE, false },
    { "vendor-class", D6O_VENDOR_CLASS, OPT_RECORD_TYPE, false,
      RECORD_DEF(vendorClassRecords) },
    { "vendor-opts", D6O_VENDOR_OPTS, OPT_RECORD_TYPE, false,
      RECORD_DEF(vendorOptsRecords) },
    { "interface-id", D6O_INTERFACE_ID, OPT_BINARY_TYPE, false },
    { "reconf-msg", D6O_RECONF_MSG, OPT_UINT8_TYPE, false },
    { "reconf-accept", D6O_RECONF_ACCEPT, OPT_EMPTY_TYPE, false },
    { "sip-server-dns", D6O_SIP_SERVERS_DNS, OPT_FQDN_TYPE, true },
    { "sip-server-addr", D6O_SIP_SERVERS_ADDR, OPT_IPV6_ADDRESS_TYPE, true },
    { "dns-servers", D6O_NAME_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
    { "domain-search", D6O_DOMAIN_SEARCH, OPT_FQDN_TYPE, true },
    { "ia-pd", D6O_IA_PD, OPT_RECORD_TYPE, false, RECORD_DEF(iapdRecords) },
    { "iaprefix", D6O_IAPREFIX, OPT_RECORD_TYPE, false,
      RECORD_DEF(iaPrefixRecords) },
    { "nis-servers", D6O_NIS_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
    { "nisp-servers", D6O_NISP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
    { "nis-domain-name", D6O_NIS_DOMAIN_NAME, OPT_FQDN_TYPE, true },
    { "nisp-domain-name", D6O_NISP_DOMAIN_NAME, OPT_FQDN_TYPE, true },
    { "sntp-servers", D6O_SNTP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
    { "information-refresh-time", D6O_INFORMATION_REFRESH_TIME,
      OPT_UINT32_TYPE, false },
    { "bcmcs-server-dns", D6O_BCMCS_SERVER_D, OPT_FQDN_TYPE, true },
    { "bcmcs-server-addr", D6O_BCMCS_SERVER_A, OPT_IPV6_ADDRESS_TYPE, true },
    { "geoconf-civic", D6O_GEOCONF_CIVIC, OPT_RECORD_TYPE, false,
      RECORD_DEF(geoconfCivicRecords) },
    { "remote-id", D6O_REMOTE_ID, OPT_RECORD_TYPE, false,
      RECORD_DEF(remoteIdRecords) },
    { "subscriber-id", D6O_SUBSCRIBER_ID, OPT_BINARY_TYPE, false },
    { "client-fqdn", D6O_CLIENT_FQDN, OPT_RECORD_TYPE, false,
      RECORD_DEF(clientFqdnRecords) },
    { "pana-agent", D6O_PANA_AGENT, OPT_IPV6_ADDRESS_TYPE, true },
    { "new-posix-timezone", D6O_NEW_POSIX_TIMEZONE, OPT_STRING_TYPE, false },
    { "new-tzdb-timezone", D6O_NEW_TZDB_TIMEZONE, OPT_STRING_TYPE, false },
    { "ero", D6O_ERO, OPT_UINT16_TYPE, true },
    { "lq-query", D6O_LQ_QUERY, OPT_RECORD_TYPE, false,
      RECORD_DEF(lqQueryRecords) },
    { "client-data", D6O_CLIENT_DATA, OPT_EMPTY_TYPE, false },
    { "clt-time", D6O_CLT_TIME, OPT_UINT32_TYPE, false },
    { "lq-relay-data", D6O_LQ_RELAY_DATA, OPT_RECORD_TYPE, false,
      RECORD_DEF(lqRelayData) },
    { "lq-client-link", D6O_LQ_CLIENT_LINK, OPT_IPV6_ADDRESS_TYPE, true }

    // @todo There is still a bunch of options for which we have to provide
    // definitions but we don't do it because they are not really
    // critical right now.
};

/// Number of option definitions defined.
const int OPTION_DEF_PARAMS_SIZE6  =
    sizeof(OPTION_DEF_PARAMS6) / sizeof(OPTION_DEF_PARAMS6[0]);

}; // anonymous namespace

#endif // STD_OPTION_DEFS_H
