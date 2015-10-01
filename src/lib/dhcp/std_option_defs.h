// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>

namespace isc {
namespace dhcp {

namespace {

/// @brief Declare an array holding parameters used to create instance
/// of a definition for option comprising a record of data fields.
///
/// @param name name of the array being declared.
#ifndef RECORD_DECL
#define RECORD_DECL(name, ...) const OptionDataType name[] = { __VA_ARGS__ }
#endif

/// @brief A pair of values: one pointing to the array holding types of
/// data fields belonging to the record, and size of this array.
///
/// @param name name of the array holding data fields' types.
#ifndef RECORD_DEF
#define RECORD_DEF(name) name, sizeof(name) / sizeof(name[0])
#endif

#ifndef NO_RECORD_DEF
#define NO_RECORD_DEF 0, 0
#endif

/// @brief Parameters being used to make up an option definition.
struct OptionDefParams {
    const char* name;              // option name
    uint16_t code;                 // option code
    OptionDataType type;           // data type
    bool array;                    // is array
    const OptionDataType* records; // record fields
    size_t records_size;           // number of fields in a record
    const char* encapsulates;      // option space encapsulated by
                                   // the particular option.
};

// fqdn option record fields.
//
// Note that the flags field indicates the type of domain
// name encoding. There is a choice between deprecated
// ASCII encoding and compressed encoding described in
// RFC 1035, section 3.1. The latter could be handled
// by OPT_FQDN_TYPE but we can't use it here because
// clients may request ASCII encoding.
RECORD_DECL(FQDN_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_UINT8_TYPE,
            OPT_FQDN_TYPE);

// V-I Vendor Class record fields.
//
// Opaque data is represented here by the binary data field.
RECORD_DECL(VIVCO_RECORDS, OPT_UINT32_TYPE, OPT_BINARY_TYPE);

// RFC4578 (PXE) record fields
//
// Three 1 byte fields to describe a network interface: type, major and minor
RECORD_DECL(CLIENT_NDI_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_UINT8_TYPE);
// A client identifer: a 1 byte type field followed by opaque data depending on the type
RECORD_DECL(UUID_GUID_RECORDS, OPT_UINT8_TYPE, OPT_BINARY_TYPE);

/// @brief Definitions of standard DHCPv4 options.
const OptionDefParams OPTION_DEF_PARAMS4[] = {
    { "subnet-mask", DHO_SUBNET_MASK, OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "time-offset", DHO_TIME_OFFSET, OPT_INT32_TYPE, false, NO_RECORD_DEF, "" },
    { "routers", DHO_ROUTERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "time-servers", DHO_TIME_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "name-servers", DHO_NAME_SERVERS, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "domain-name-servers", DHO_DOMAIN_NAME_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "log-servers", DHO_LOG_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "cookie-servers", DHO_COOKIE_SERVERS, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "lpr-servers", DHO_LPR_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "impress-servers", DHO_IMPRESS_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "resource-location-servers", DHO_RESOURCE_LOCATION_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "host-name", DHO_HOST_NAME, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "boot-size", DHO_BOOT_SIZE, OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "merit-dump", DHO_MERIT_DUMP, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "domain-name", DHO_DOMAIN_NAME, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "swap-server", DHO_SWAP_SERVER, OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "root-path", DHO_ROOT_PATH, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "extensions-path", DHO_EXTENSIONS_PATH, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "ip-forwarding", DHO_IP_FORWARDING, OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "non-local-source-routing", DHO_NON_LOCAL_SOURCE_ROUTING,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "policy-filter", DHO_POLICY_FILTER, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "max-dgram-reassembly", DHO_MAX_DGRAM_REASSEMBLY,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "default-ip-ttl", DHO_DEFAULT_IP_TTL, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "path-mtu-aging-timeout", DHO_PATH_MTU_AGING_TIMEOUT,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "path-mtu-plateau-table", DHO_PATH_MTU_PLATEAU_TABLE,
      OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "interface-mtu", DHO_INTERFACE_MTU, OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "all-subnets-local", DHO_ALL_SUBNETS_LOCAL,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "broadcast-address", DHO_BROADCAST_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "perform-mask-discovery", DHO_PERFORM_MASK_DISCOVERY,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "mask-supplier", DHO_MASK_SUPPLIER, OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "router-discovery", DHO_ROUTER_DISCOVERY,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "router-solicitation-address", DHO_ROUTER_SOLICITATION_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "static-routes", DHO_STATIC_ROUTES,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "trailer-encapsulation", DHO_TRAILER_ENCAPSULATION,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "arp-cache-timeout", DHO_ARP_CACHE_TIMEOUT,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "ieee802-3-encapsulation", DHO_IEEE802_3_ENCAPSULATION,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "default-tcp-ttl", DHO_DEFAULT_TCP_TTL, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "tcp-keepalive-interval", DHO_TCP_KEEPALIVE_INTERVAL,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "tcp-keepalive-garbage", DHO_TCP_KEEPALIVE_GARBAGE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "nis-domain", DHO_NIS_DOMAIN, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "nis-servers", DHO_NIS_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "ntp-servers", DHO_NTP_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "vendor-encapsulated-options", DHO_VENDOR_ENCAPSULATED_OPTIONS,
      OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "vendor-encapsulated-options-space" },
    { "netbios-name-servers", DHO_NETBIOS_NAME_SERVERS,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "netbios-dd-server", DHO_NETBIOS_DD_SERVER,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "netbios-node-type", DHO_NETBIOS_NODE_TYPE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "netbios-scope", DHO_NETBIOS_SCOPE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "font-servers", DHO_FONT_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "x-display-manager", DHO_X_DISPLAY_MANAGER,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "dhcp-requested-address", DHO_DHCP_REQUESTED_ADDRESS,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-lease-time", DHO_DHCP_LEASE_TIME, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-option-overload", DHO_DHCP_OPTION_OVERLOAD,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-message-type", DHO_DHCP_MESSAGE_TYPE, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-server-identifier", DHO_DHCP_SERVER_IDENTIFIER,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-parameter-request-list", DHO_DHCP_PARAMETER_REQUEST_LIST,
      OPT_UINT8_TYPE, true, NO_RECORD_DEF, "" },
    { "dhcp-message", DHO_DHCP_MESSAGE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-max-message-size", DHO_DHCP_MAX_MESSAGE_SIZE,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-renewal-time", DHO_DHCP_RENEWAL_TIME, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-rebinding-time", DHO_DHCP_REBINDING_TIME,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "vendor-class-identifier", DHO_VENDOR_CLASS_IDENTIFIER,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-client-identifier", DHO_DHCP_CLIENT_IDENTIFIER,
      OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "nwip-domain-name", DHO_NWIP_DOMAIN_NAME, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "nwip-suboptions", DHO_NWIP_SUBOPTIONS, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "tftp-server-name", DHO_TFTP_SERVER_NAME, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "boot-file-name", DHO_BOOT_FILE_NAME, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "user-class", DHO_USER_CLASS, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "fqdn", DHO_FQDN, OPT_RECORD_TYPE, false, RECORD_DEF(FQDN_RECORDS), "" },
    { "dhcp-agent-options", DHO_DHCP_AGENT_OPTIONS,
      OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "dhcp-agent-options-space" },
    // Unfortunatelly the AUTHENTICATE option contains a 64-bit
    // data field called 'replay-detection' that can't be added
    // as a record field to a custom option. Also, there is no
    // dedicated option class to handle it so we simply return
    // binary option type for now.
    // @todo implement a class to handle AUTH option.
    { "authenticate", DHO_AUTHENTICATE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "client-last-transaction-time", DHO_CLIENT_LAST_TRANSACTION_TIME,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "associated-ip", DHO_ASSOCIATED_IP, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "client-system", DHO_SYSTEM, OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "client-ndi", DHO_NDI, OPT_RECORD_TYPE, false, RECORD_DEF(CLIENT_NDI_RECORDS), "" },
    { "uuid-guid", DHO_UUID_GUID, OPT_RECORD_TYPE, false, RECORD_DEF(UUID_GUID_RECORDS), "" },
    { "subnet-selection", DHO_SUBNET_SELECTION,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    // The following options need a special encoding of data
    // being carried by them. Therefore, there is no way they can
    // be handled by OptionCustom. We may need to implement
    // dedicated classes to handle them. Until that happens
    // let's treat them as 'binary' options.
    { "domain-search", DHO_DOMAIN_SEARCH, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "vivco-suboptions", DHO_VIVCO_SUBOPTIONS, OPT_RECORD_TYPE,
      false, RECORD_DEF(VIVCO_RECORDS), "" },
    { "vivso-suboptions", DHO_VIVSO_SUBOPTIONS, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" }

        // @todo add definitions for all remaning options.
};

/// Number of option definitions defined.
const int OPTION_DEF_PARAMS_SIZE4  =
    sizeof(OPTION_DEF_PARAMS4) / sizeof(OPTION_DEF_PARAMS4[0]);


/// Start Definition of DHCPv6 options

// client-fqdn
RECORD_DECL(CLIENT_FQDN_RECORDS, OPT_UINT8_TYPE, OPT_FQDN_TYPE);
// geoconf-civic
RECORD_DECL(GEOCONF_CIVIC_RECORDS, OPT_UINT8_TYPE, OPT_UINT16_TYPE,
            OPT_BINARY_TYPE);
// iaddr
RECORD_DECL(IAADDR_RECORDS, OPT_IPV6_ADDRESS_TYPE, OPT_UINT32_TYPE,
            OPT_UINT32_TYPE);
// ia-na
RECORD_DECL(IA_NA_RECORDS, OPT_UINT32_TYPE, OPT_UINT32_TYPE, OPT_UINT32_TYPE);
// ia-pd
RECORD_DECL(IA_PD_RECORDS, OPT_UINT32_TYPE, OPT_UINT32_TYPE, OPT_UINT32_TYPE);
// ia-prefix
RECORD_DECL(IA_PREFIX_RECORDS, OPT_UINT32_TYPE, OPT_UINT32_TYPE,
            OPT_UINT8_TYPE, OPT_IPV6_ADDRESS_TYPE);
// lq-query
RECORD_DECL(LQ_QUERY_RECORDS, OPT_UINT8_TYPE, OPT_IPV6_ADDRESS_TYPE);
// lq-relay-data
RECORD_DECL(LQ_RELAY_DATA_RECORDS, OPT_IPV6_ADDRESS_TYPE, OPT_BINARY_TYPE);
// remote-id
RECORD_DECL(REMOTE_ID_RECORDS, OPT_UINT32_TYPE, OPT_BINARY_TYPE);
// status-code
RECORD_DECL(STATUS_CODE_RECORDS, OPT_UINT16_TYPE, OPT_STRING_TYPE);
// vendor-class
RECORD_DECL(VENDOR_CLASS_RECORDS, OPT_UINT32_TYPE, OPT_BINARY_TYPE);
// sedhcpv6 signature
RECORD_DECL(SIGNATURE_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE,
            OPT_BINARY_TYPE);

// RFC5970 (PXE) Class record fields
//
// Three 1 byte fileds to describe a network interface: type, major and minor
RECORD_DECL(CLIENT_NII_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_UINT8_TYPE);

/// Standard DHCPv6 option definitions.
///
/// @warning in this array, the initializers are provided for all
/// OptionDefParams struct's members despite initializers for
/// 'records' and 'record_size' could be ommited for entries for
/// which 'type' does not equal to OPT_RECORD_TYPE. If initializers
/// are ommitted the corresponding values should default to 0.
/// This however does not work on Solaris (GCC) which issues a
/// warning about lack of initializers for some struct members
/// causing build to fail.
const OptionDefParams OPTION_DEF_PARAMS6[] = {
    { "clientid", D6O_CLIENTID, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "serverid", D6O_SERVERID, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "ia-na", D6O_IA_NA, OPT_RECORD_TYPE, false, RECORD_DEF(IA_NA_RECORDS), "" },
    { "ia-ta", D6O_IA_TA, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "iaaddr", D6O_IAADDR, OPT_RECORD_TYPE, false, RECORD_DEF(IAADDR_RECORDS), "" },
    { "oro", D6O_ORO, OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "preference", D6O_PREFERENCE, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "elapsed-time", D6O_ELAPSED_TIME, OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "relay-msg", D6O_RELAY_MSG, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    // Unfortunatelly the AUTH option contains a 64-bit data field
    // called 'replay-detection' that can't be added as a record
    // field to a custom option. Also, there is no dedicated
    // option class to handle it so we simply return binary
    // option type for now.
    // @todo implement a class to handle AUTH option.
    { "auth", D6O_AUTH, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "unicast", D6O_UNICAST, OPT_IPV6_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "status-code", D6O_STATUS_CODE, OPT_RECORD_TYPE, false,
      RECORD_DEF(STATUS_CODE_RECORDS), "" },
    { "rapid-commit", D6O_RAPID_COMMIT, OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "" },
    { "user-class", D6O_USER_CLASS, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "vendor-class", D6O_VENDOR_CLASS, OPT_RECORD_TYPE, false,
      RECORD_DEF(VENDOR_CLASS_RECORDS), "" },
    { "vendor-opts", D6O_VENDOR_OPTS, OPT_UINT32_TYPE, false,
      NO_RECORD_DEF, "vendor-opts-space" },
    { "interface-id", D6O_INTERFACE_ID, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "reconf-msg", D6O_RECONF_MSG, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "reconf-accept", D6O_RECONF_ACCEPT, OPT_EMPTY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "sip-server-dns", D6O_SIP_SERVERS_DNS, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF, "" },
    { "sip-server-addr", D6O_SIP_SERVERS_ADDR, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "dns-servers", D6O_NAME_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "domain-search", D6O_DOMAIN_SEARCH, OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "ia-pd", D6O_IA_PD, OPT_RECORD_TYPE, false, RECORD_DEF(IA_PD_RECORDS), "" },
    { "iaprefix", D6O_IAPREFIX, OPT_RECORD_TYPE, false,
      RECORD_DEF(IA_PREFIX_RECORDS), "" },
    { "nis-servers", D6O_NIS_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "nisp-servers", D6O_NISP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "nis-domain-name", D6O_NIS_DOMAIN_NAME, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF, "" },
    { "nisp-domain-name", D6O_NISP_DOMAIN_NAME, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF, "" },
    { "sntp-servers", D6O_SNTP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "information-refresh-time", D6O_INFORMATION_REFRESH_TIME,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "bcmcs-server-dns", D6O_BCMCS_SERVER_D, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF, "" },
    { "bcmcs-server-addr", D6O_BCMCS_SERVER_A, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "geoconf-civic", D6O_GEOCONF_CIVIC, OPT_RECORD_TYPE, false,
      RECORD_DEF(GEOCONF_CIVIC_RECORDS), "" },
    { "remote-id", D6O_REMOTE_ID, OPT_RECORD_TYPE, false,
      RECORD_DEF(REMOTE_ID_RECORDS), "" },
    { "subscriber-id", D6O_SUBSCRIBER_ID, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "client-fqdn", D6O_CLIENT_FQDN, OPT_RECORD_TYPE, false,
      RECORD_DEF(CLIENT_FQDN_RECORDS), "" },
    { "pana-agent", D6O_PANA_AGENT, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "new-posix-timezone", D6O_NEW_POSIX_TIMEZONE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "new-tzdb-timezone", D6O_NEW_TZDB_TIMEZONE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "ero", D6O_ERO, OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "lq-query", D6O_LQ_QUERY, OPT_RECORD_TYPE, false,
      RECORD_DEF(LQ_QUERY_RECORDS), "" },
    { "client-data", D6O_CLIENT_DATA, OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "" },
    { "clt-time", D6O_CLT_TIME, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "lq-relay-data", D6O_LQ_RELAY_DATA, OPT_RECORD_TYPE, false,
      RECORD_DEF(LQ_RELAY_DATA_RECORDS), "" },
    { "lq-client-link", D6O_LQ_CLIENT_LINK, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "bootfile-url", D6O_BOOTFILE_URL, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "bootfile-param", D6O_BOOTFILE_PARAM, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "client-arch-type", D6O_CLIENT_ARCH_TYPE, OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "nii", D6O_NII, OPT_RECORD_TYPE, false, RECORD_DEF(CLIENT_NII_RECORDS), "" },
    { "erp-local-domain-name", D6O_ERP_LOCAL_DOMAIN_NAME, OPT_FQDN_TYPE, false,
      NO_RECORD_DEF, "" },
    { "rsoo", D6O_RSOO, OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "rsoo-opts" },
    { "client-linklayer-addr", D6O_CLIENT_LINKLAYER_ADDR, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "public-key", D6O_PUBLIC_KEY, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "certificate", D6O_CERTIFICATE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "signature", D6O_SIGNATURE, OPT_RECORD_TYPE, false,
      RECORD_DEF(SIGNATURE_RECORDS), "" },
    { "timestamp", D6O_TIMESTAMP, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" }

    // @todo There is still a bunch of options for which we have to provide
    // definitions but we don't do it because they are not really
    // critical right now.
};

/// Number of option definitions defined.
const int OPTION_DEF_PARAMS_SIZE6  =
    sizeof(OPTION_DEF_PARAMS6) / sizeof(OPTION_DEF_PARAMS6[0]);

} // unnamed namespace

} // namespace dhcp
} // namespace isc

#endif // STD_OPTION_DEFS_H
