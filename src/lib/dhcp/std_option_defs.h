// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STD_OPTION_DEFS_H
#define STD_OPTION_DEFS_H

#include <dhcp/option_data_types.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_space.h>

/// @brief global std option spaces
#define DHCP4_OPTION_SPACE               "dhcp4"
#define DHCP6_OPTION_SPACE               "dhcp6"
#define ISC_V6_OPTION_SPACE              "4o6"
#define MAPE_V6_OPTION_SPACE             "s46-cont-mape-options"
#define MAPT_V6_OPTION_SPACE             "s46-cont-mapt-options"
#define LW_V6_OPTION_SPACE               "s46-cont-lw-options"
#define V4V6_RULE_OPTION_SPACE           "s46-rule-options"
#define V4V6_BIND_OPTION_SPACE           "s46-v4v6bind-options"
#define LAST_RESORT_V4_OPTION_SPACE      "last-resort-v4"

/// @brief encapsulated option spaces
#define DHCP_AGENT_OPTION_SPACE          "dhcp-agent-options-space"
#define VENDOR_ENCAPSULATED_OPTION_SPACE "vendor-encapsulated-options-space"

// NOTE:
// When adding a new space, make sure you also update
// src/lib/yang/adaptor_option.cc

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

// SLP Directory Agent option.
RECORD_DECL(DIRECTORY_AGENT_RECORDS, OPT_BOOLEAN_TYPE, OPT_IPV4_ADDRESS_TYPE);

// SLP Service Scope option.
//
// The scope list is optional.
RECORD_DECL(SERVICE_SCOPE_RECORDS, OPT_BOOLEAN_TYPE, OPT_STRING_TYPE);

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
// A client identifier: a 1 byte type field followed by opaque data depending on the type
RECORD_DECL(UUID_GUID_RECORDS, OPT_UINT8_TYPE, OPT_BINARY_TYPE);

// RFC6731 DHCPv4 Recursive DNS Server Selection option.
//
// Flag, two addresses and domain list
RECORD_DECL(V4_RDNSS_SELECT_RECORDS, OPT_UINT8_TYPE, OPT_IPV4_ADDRESS_TYPE,
            OPT_IPV4_ADDRESS_TYPE, OPT_FQDN_TYPE);

// RFC6926 DHCPv4 Bulk Leasequery Status Code option.
RECORD_DECL(V4_STATUS_CODE_RECORDS, OPT_UINT8_TYPE, OPT_STRING_TYPE);

// RFC7618 DHCPv4 Port Parameter option.
//
// PSID offset, PSID-len and PSID
RECORD_DECL(V4_PORTPARAMS_RECORDS, OPT_UINT8_TYPE, OPT_PSID_TYPE);

// RFC5969 DHCPv6 6RD option.
//
// two 8 bit lengthes, an IPv6 address and one or more IPv4 addresses
RECORD_DECL(OPT_6RD_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE,
            OPT_IPV6_ADDRESS_TYPE, OPT_IPV4_ADDRESS_TYPE);

// RFC-draft-ietf-add-dnr DHCPv4 DNR option.
//
// DNR Instance Data Length (2 octets), Service Priority (2 octets),
// ADN Length (1 octet), ADN FQDN.
// Opaque data is represented here by the binary data field.
// It may contain Addr Length (1 octet), IPv4 address(es), SvcParams,
// and next DNR instances as binary data.
RECORD_DECL(V4_DNR_RECORDS, OPT_UINT16_TYPE, OPT_UINT16_TYPE, OPT_UINT8_TYPE,
            OPT_FQDN_TYPE, OPT_BINARY_TYPE);

/// @brief Definitions of standard DHCPv4 options.
const OptionDefParams STANDARD_V4_OPTION_DEFINITIONS[] = {
    { "subnet-mask", DHO_SUBNET_MASK, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "time-offset", DHO_TIME_OFFSET, DHCP4_OPTION_SPACE, OPT_INT32_TYPE,
      false, NO_RECORD_DEF, "" },
    { "routers", DHO_ROUTERS, DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, true,
      NO_RECORD_DEF, "" },
    { "time-servers", DHO_TIME_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "name-servers", DHO_NAME_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "domain-name-servers", DHO_DOMAIN_NAME_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "log-servers", DHO_LOG_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "cookie-servers", DHO_COOKIE_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "lpr-servers", DHO_LPR_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "impress-servers", DHO_IMPRESS_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "resource-location-servers", DHO_RESOURCE_LOCATION_SERVERS,
      DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "host-name", DHO_HOST_NAME, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "boot-size", DHO_BOOT_SIZE, DHCP4_OPTION_SPACE, OPT_UINT16_TYPE, false,
      NO_RECORD_DEF, "" },
    { "merit-dump", DHO_MERIT_DUMP, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "domain-name", DHO_DOMAIN_NAME, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "swap-server", DHO_SWAP_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "root-path", DHO_ROOT_PATH, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "extensions-path", DHO_EXTENSIONS_PATH, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "ip-forwarding", DHO_IP_FORWARDING, DHCP4_OPTION_SPACE, OPT_BOOLEAN_TYPE,
      false, NO_RECORD_DEF, "" },
    { "non-local-source-routing", DHO_NON_LOCAL_SOURCE_ROUTING,
      DHCP4_OPTION_SPACE, OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "policy-filter", DHO_POLICY_FILTER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "max-dgram-reassembly", DHO_MAX_DGRAM_REASSEMBLY, DHCP4_OPTION_SPACE,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "default-ip-ttl", DHO_DEFAULT_IP_TTL, DHCP4_OPTION_SPACE, OPT_UINT8_TYPE,
      false, NO_RECORD_DEF, "" },
    { "path-mtu-aging-timeout", DHO_PATH_MTU_AGING_TIMEOUT, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "path-mtu-plateau-table", DHO_PATH_MTU_PLATEAU_TABLE, DHCP4_OPTION_SPACE,
      OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "interface-mtu", DHO_INTERFACE_MTU, DHCP4_OPTION_SPACE, OPT_UINT16_TYPE,
      false, NO_RECORD_DEF, "" },
    { "all-subnets-local", DHO_ALL_SUBNETS_LOCAL, DHCP4_OPTION_SPACE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "broadcast-address", DHO_BROADCAST_ADDRESS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "perform-mask-discovery", DHO_PERFORM_MASK_DISCOVERY, DHCP4_OPTION_SPACE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "mask-supplier", DHO_MASK_SUPPLIER, DHCP4_OPTION_SPACE, OPT_BOOLEAN_TYPE,
      false, NO_RECORD_DEF, "" },
    { "router-discovery", DHO_ROUTER_DISCOVERY, DHCP4_OPTION_SPACE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "router-solicitation-address", DHO_ROUTER_SOLICITATION_ADDRESS,
      DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "static-routes", DHO_STATIC_ROUTES, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "trailer-encapsulation", DHO_TRAILER_ENCAPSULATION, DHCP4_OPTION_SPACE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "arp-cache-timeout", DHO_ARP_CACHE_TIMEOUT, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "ieee802-3-encapsulation", DHO_IEEE802_3_ENCAPSULATION,
      DHCP4_OPTION_SPACE, OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "default-tcp-ttl", DHO_DEFAULT_TCP_TTL, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "tcp-keepalive-interval", DHO_TCP_KEEPALIVE_INTERVAL, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "tcp-keepalive-garbage", DHO_TCP_KEEPALIVE_GARBAGE, DHCP4_OPTION_SPACE,
      OPT_BOOLEAN_TYPE, false, NO_RECORD_DEF, "" },
    { "nis-domain", DHO_NIS_DOMAIN, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "nis-servers", DHO_NIS_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "ntp-servers", DHO_NTP_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    /// vendor-encapsulated-options (43) is deferred
    { "netbios-name-servers", DHO_NETBIOS_NAME_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "netbios-dd-server", DHO_NETBIOS_DD_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "netbios-node-type", DHO_NETBIOS_NODE_TYPE, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "netbios-scope", DHO_NETBIOS_SCOPE, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "font-servers", DHO_FONT_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "x-display-manager", DHO_X_DISPLAY_MANAGER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "dhcp-requested-address", DHO_DHCP_REQUESTED_ADDRESS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-lease-time", DHO_DHCP_LEASE_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-option-overload", DHO_DHCP_OPTION_OVERLOAD, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-message-type", DHO_DHCP_MESSAGE_TYPE, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-server-identifier", DHO_DHCP_SERVER_IDENTIFIER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-parameter-request-list", DHO_DHCP_PARAMETER_REQUEST_LIST,
      DHCP4_OPTION_SPACE, OPT_UINT8_TYPE, true, NO_RECORD_DEF, "" },
    { "dhcp-message", DHO_DHCP_MESSAGE, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "dhcp-max-message-size", DHO_DHCP_MAX_MESSAGE_SIZE, DHCP4_OPTION_SPACE,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-renewal-time", DHO_DHCP_RENEWAL_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-rebinding-time", DHO_DHCP_REBINDING_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "vendor-class-identifier", DHO_VENDOR_CLASS_IDENTIFIER,
      DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-client-identifier", DHO_DHCP_CLIENT_IDENTIFIER, DHCP4_OPTION_SPACE,
      OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "nwip-domain-name", DHO_NWIP_DOMAIN_NAME, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "nwip-suboptions", DHO_NWIP_SUBOPTIONS, DHCP4_OPTION_SPACE,
      OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "nisplus-domain-name", DHO_NISP_DOMAIN_NAME, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "nisplus-servers", DHO_NISP_SERVER_ADDR, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "tftp-server-name", DHO_TFTP_SERVER_NAME, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "boot-file-name", DHO_BOOT_FILE_NAME, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "mobile-ip-home-agent", DHO_HOME_AGENT_ADDRS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "smtp-server", DHO_SMTP_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "pop-server", DHO_POP3_SERVER, DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "nntp-server", DHO_NNTP_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "www-server", DHO_WWW_SERVER, DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "finger-server", DHO_FINGER_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "irc-server", DHO_IRC_SERVER, DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "streettalk-server", DHO_STREETTALK_SERVER, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "streettalk-directory-assistance-server", DHO_STDASERVER,
      DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "user-class", DHO_USER_CLASS, DHCP4_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "slp-directory-agent", DHO_DIRECTORY_AGENT, DHCP4_OPTION_SPACE,
      OPT_RECORD_TYPE, true, RECORD_DEF(DIRECTORY_AGENT_RECORDS), "" },
    { "slp-service-scope", DHO_SERVICE_SCOPE, DHCP4_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(SERVICE_SCOPE_RECORDS), "" },
    { "fqdn", DHO_FQDN, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(FQDN_RECORDS), "" },
    { "dhcp-agent-options", DHO_DHCP_AGENT_OPTIONS, DHCP4_OPTION_SPACE,
      OPT_EMPTY_TYPE, false, NO_RECORD_DEF, DHCP_AGENT_OPTION_SPACE },
    { "nds-servers", DHO_NDS_SERVERS, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "nds-tree-name", DHO_NDS_TREE_NAME, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "nds-context", DHO_NDS_CONTEXT, DHCP4_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "bcms-controller-names", DHO_BCMCS_DOMAIN_NAME_LIST, DHCP4_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "bcms-controller-address", DHO_BCMCS_IPV4_ADDR, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    // Unfortunately the AUTHENTICATE option contains a 64-bit
    // data field called 'replay-detection' that can't be added
    // as a record field to a custom option. Also, there is no
    // dedicated option class to handle it so we simply return
    // binary option type for now.
    // @todo implement a class to handle AUTH option.
    { "authenticate", DHO_AUTHENTICATE, DHCP4_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "client-last-transaction-time", DHO_CLIENT_LAST_TRANSACTION_TIME,
      DHCP4_OPTION_SPACE, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "associated-ip", DHO_ASSOCIATED_IP, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "client-system", DHO_SYSTEM, DHCP4_OPTION_SPACE, OPT_UINT16_TYPE, true,
      NO_RECORD_DEF, "" },
    { "client-ndi", DHO_NDI, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(CLIENT_NDI_RECORDS), "" },
    { "uuid-guid", DHO_UUID_GUID, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(UUID_GUID_RECORDS), "" },
    { "uap-servers", DHO_USER_AUTH, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "geoconf-civic", DHO_GEOCONF_CIVIC, DHCP4_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "pcode", DHO_PCODE, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "tcode", DHO_TCODE, DHCP4_OPTION_SPACE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF, "" },
    { "v6-only-preferred", DHO_V6_ONLY_PREFERRED, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "netinfo-server-address", DHO_NETINFO_ADDR, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "netinfo-server-tag", DHO_NETINFO_TAG, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "v4-captive-portal", DHO_V4_CAPTIVE_PORTAL, DHCP4_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "auto-config", DHO_AUTO_CONFIG, DHCP4_OPTION_SPACE, OPT_UINT8_TYPE,
      false, NO_RECORD_DEF, "" },
    { "name-service-search", DHO_NAME_SERVICE_SEARCH, DHCP4_OPTION_SPACE,
      OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "subnet-selection", DHO_SUBNET_SELECTION, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "domain-search", DHO_DOMAIN_SEARCH, DHCP4_OPTION_SPACE, OPT_FQDN_TYPE,
      true, NO_RECORD_DEF, "" },
    { "vivco-suboptions", DHO_VIVCO_SUBOPTIONS, DHCP4_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(VIVCO_RECORDS), "" },
    // Vendor-Identifying Vendor Specific Information option payload begins with a
    // 32-bit log enterprise number, followed by a tuple of data-len/option-data.
    // The format defined here includes 32-bit field holding enterprise number.
    // This allows for specifying option-data information where the enterprise-id
    // is represented by a uint32_t value. Previously we represented this option
    // as a binary, but that would imply that enterprise number would have to be
    // represented in binary format in the server configuration. That would be
    // inconvenient and non-intuitive.
    /// @todo We need to extend support for vendor options with ability to specify
    /// multiple enterprise numbers for a single option. Perhaps it would be
    /// ok to specify multiple instances of the "vivso-suboptions" which will be
    /// combined in a single option by the server before responding to a client.
    { "vivso-suboptions", DHO_VIVSO_SUBOPTIONS, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "pana-agent", DHO_PANA_AGENT, DHCP4_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "v4-lost", DHO_V4_LOST, DHCP4_OPTION_SPACE, OPT_FQDN_TYPE, false,
      NO_RECORD_DEF, "" },
    { "capwap-ac-v4", DHO_CAPWAP_AC_V4, DHCP4_OPTION_SPACE,
      OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "sip-ua-cs-domains", DHO_SIP_UA_CONF_SERVICE_DOMAINS, DHCP4_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "v4-sztp-redirect", DHO_V4_SZTP_REDIRECT, DHCP4_OPTION_SPACE, OPT_TUPLE_TYPE,
     true, NO_RECORD_DEF, ""},
    { "rdnss-selection", DHO_RDNSS_SELECT, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE,
      true, RECORD_DEF(V4_RDNSS_SELECT_RECORDS), "" },
    { "status-code", DHO_STATUS_CODE, DHCP4_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(V4_STATUS_CODE_RECORDS), "" },
    { "base-time", DHO_BASE_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "start-time-of-state", DHO_START_TIME_OF_STATE, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "query-start-time", DHO_QUERY_START_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "query-end-time", DHO_QUERY_END_TIME, DHCP4_OPTION_SPACE,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "dhcp-state", DHO_DHCP_STATE, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "data-source", DHO_DATA_SOURCE, DHCP4_OPTION_SPACE,
      OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "v4-portparams", DHO_V4_PORTPARAMS, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(V4_PORTPARAMS_RECORDS), "" },
    { "v4-dnr", DHO_V4_DNR, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE,
     false, RECORD_DEF(V4_DNR_RECORDS), "" },
    { "option-6rd", DHO_6RD, DHCP4_OPTION_SPACE, OPT_RECORD_TYPE, true,
      RECORD_DEF(OPT_6RD_RECORDS), "" },
    { "v4-access-domain", DHO_V4_ACCESS_DOMAIN, DHCP4_OPTION_SPACE,
      OPT_FQDN_TYPE, false, NO_RECORD_DEF, "" }

        // @todo add definitions for all remaining options.
};

/// Number of option definitions defined.
const int STANDARD_V4_OPTION_DEFINITIONS_SIZE =
    sizeof(STANDARD_V4_OPTION_DEFINITIONS) /
    sizeof(STANDARD_V4_OPTION_DEFINITIONS[0]);

/// Definitions of DHCPv4 agent options.
const OptionDefParams DHCP_AGENT_OPTION_DEFINITIONS[] = {
    { "circuit-id", RAI_OPTION_AGENT_CIRCUIT_ID,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "remote-id", RAI_OPTION_REMOTE_ID,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "docsis-device-class", RAI_OPTION_DOCSIS_DEVICE_CLASS,
      DHCP_AGENT_OPTION_SPACE, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "link-selection", RAI_OPTION_LINK_SELECTION,
      DHCP_AGENT_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, false,
      NO_RECORD_DEF, "" },
    { "subscriber-id", RAI_OPTION_SUBSCRIBER_ID,
      DHCP_AGENT_OPTION_SPACE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "radius", RAI_OPTION_RADIUS,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "auth", RAI_OPTION_AUTH,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "vendor-specific-info", RAI_OPTION_VSI,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "relay-flags", RAI_OPTION_RELAY_FLAGS,
      DHCP_AGENT_OPTION_SPACE, OPT_UINT8_TYPE, false, NO_RECORD_DEF, "" },
    { "server-id-override", RAI_OPTION_SERVER_ID_OVERRIDE,
      DHCP_AGENT_OPTION_SPACE, OPT_IPV4_ADDRESS_TYPE, false,
      NO_RECORD_DEF, "" },
    { "relay-id", RAI_OPTION_RELAY_ID,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "access-techno-type", RAI_OPTION_ACCESS_TECHNO_TYPE,
      DHCP_AGENT_OPTION_SPACE, OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "access-network-name", RAI_OPTION_ACCESS_NETWORK_NAME,
      DHCP_AGENT_OPTION_SPACE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "access-point-name", RAI_OPTION_ACCESS_POINT_NAME,
      DHCP_AGENT_OPTION_SPACE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "access-point-bssid", RAI_OPTION_ACCESS_POINT_BSSID,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "operator-id", RAI_OPTION_OPERATOR_ID,
      DHCP_AGENT_OPTION_SPACE, OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "operator-realm", RAI_OPTION_OPERATOR_REALM,
      DHCP_AGENT_OPTION_SPACE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "relay-port", RAI_OPTION_RELAY_PORT,
      DHCP_AGENT_OPTION_SPACE, OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "virtual-subnet-select", RAI_OPTION_VIRTUAL_SUBNET_SELECT,
      DHCP_AGENT_OPTION_SPACE, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "virtual-subnet-select-ctrl", RAI_OPTION_VIRTUAL_SUBNET_SELECT_CTRL,
      DHCP_AGENT_OPTION_SPACE, OPT_EMPTY_TYPE, false, NO_RECORD_DEF, "" }
};

const int DHCP_AGENT_OPTION_DEFINITIONS_SIZE =
    sizeof(DHCP_AGENT_OPTION_DEFINITIONS) /
    sizeof(DHCP_AGENT_OPTION_DEFINITIONS[0]);

/// Last resort definitions (only option 43 for now, these definitions
/// are applied in deferred unpacking when none is found).
const OptionDefParams LAST_RESORT_V4_OPTION_DEFINITIONS[] = {
    { "vendor-encapsulated-options", DHO_VENDOR_ENCAPSULATED_OPTIONS,
      DHCP4_OPTION_SPACE, OPT_EMPTY_TYPE, false, NO_RECORD_DEF,
      VENDOR_ENCAPSULATED_OPTION_SPACE }
};

const int LAST_RESORT_V4_OPTION_DEFINITIONS_SIZE =
    sizeof(LAST_RESORT_V4_OPTION_DEFINITIONS) /
    sizeof(LAST_RESORT_V4_OPTION_DEFINITIONS[0]);

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
// s46-rule
RECORD_DECL(S46_RULE, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_UINT8_TYPE,
            OPT_IPV4_ADDRESS_TYPE, OPT_IPV6_PREFIX_TYPE);
// s46-v4v6bind
RECORD_DECL(S46_V4V6BIND, OPT_IPV4_ADDRESS_TYPE, OPT_IPV6_PREFIX_TYPE);
// s46-portparams
RECORD_DECL(S46_PORTPARAMS, OPT_UINT8_TYPE, OPT_PSID_TYPE);
// status-code
RECORD_DECL(V6_STATUS_CODE_RECORDS, OPT_UINT16_TYPE, OPT_STRING_TYPE);
// vendor-class
RECORD_DECL(VENDOR_CLASS_RECORDS, OPT_UINT32_TYPE, OPT_BINARY_TYPE);
// rdnss-selection
RECORD_DECL(V6_RDNSS_SELECT_RECORDS, OPT_IPV6_ADDRESS_TYPE, OPT_UINT8_TYPE,
            OPT_FQDN_TYPE);
// sedhcpv6 signature
RECORD_DECL(SIGNATURE_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE,
            OPT_BINARY_TYPE);

// RFC5970 (PXE) Class record fields
//
// Three 1 byte fileds to describe a network interface: type, major and minor
RECORD_DECL(CLIENT_NII_RECORDS, OPT_UINT8_TYPE, OPT_UINT8_TYPE, OPT_UINT8_TYPE);

// RFC-draft-ietf-add-dnr DHCPv6 DNR option.
//
// Service Priority (2 octets), ADN Length (2 octets), ADN FQDN.
// Opaque data is represented here by the binary data field.
// It may contain Addr Length (2 octets), IPv6 address(es), SvcParams.
RECORD_DECL(V6_DNR_RECORDS, OPT_UINT16_TYPE, OPT_UINT16_TYPE, OPT_FQDN_TYPE, OPT_BINARY_TYPE);

/// Standard DHCPv6 option definitions.
///
/// @warning in this array, the initializers are provided for all
/// OptionDefParams struct's members despite initializers for
/// 'records' and 'record_size' could be omitted for entries for
/// which 'type' does not equal to OPT_RECORD_TYPE. If initializers
/// are omitted the corresponding values should default to 0.
/// This however does not work on Solaris (GCC) which issues a
/// warning about lack of initializers for some struct members
/// causing build to fail.
const OptionDefParams STANDARD_V6_OPTION_DEFINITIONS[] = {
    { "clientid", D6O_CLIENTID, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "serverid", D6O_SERVERID, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "ia-na", D6O_IA_NA, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(IA_NA_RECORDS), "" },
    { "ia-ta", D6O_IA_TA, DHCP6_OPTION_SPACE, OPT_UINT32_TYPE, false,
      NO_RECORD_DEF, "" },
    { "iaaddr", D6O_IAADDR, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(IAADDR_RECORDS), "" },
    { "oro", D6O_ORO, DHCP6_OPTION_SPACE, OPT_UINT16_TYPE, true, NO_RECORD_DEF,
      "" },
    { "preference", D6O_PREFERENCE, DHCP6_OPTION_SPACE, OPT_UINT8_TYPE, false,
      NO_RECORD_DEF, "" },
    { "elapsed-time", D6O_ELAPSED_TIME, DHCP6_OPTION_SPACE, OPT_UINT16_TYPE,
      false, NO_RECORD_DEF, "" },
    { "relay-msg", D6O_RELAY_MSG, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    // Unfortunately the AUTH option contains a 64-bit data field
    // called 'replay-detection' that can't be added as a record
    // field to a custom option. Also, there is no dedicated
    // option class to handle it so we simply return binary
    // option type for now.
    // @todo implement a class to handle AUTH option.
    { "auth", D6O_AUTH, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "unicast", D6O_UNICAST, DHCP6_OPTION_SPACE, OPT_IPV6_ADDRESS_TYPE,
      false, NO_RECORD_DEF, "" },
    { "status-code", D6O_STATUS_CODE, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(V6_STATUS_CODE_RECORDS), "" },
    { "rapid-commit", D6O_RAPID_COMMIT, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "user-class", D6O_USER_CLASS, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "vendor-class", D6O_VENDOR_CLASS, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(VENDOR_CLASS_RECORDS), "" },
    { "vendor-opts", D6O_VENDOR_OPTS, DHCP6_OPTION_SPACE, OPT_UINT32_TYPE,
      false, NO_RECORD_DEF, "" },
    { "interface-id", D6O_INTERFACE_ID, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "reconf-msg", D6O_RECONF_MSG, DHCP6_OPTION_SPACE, OPT_UINT8_TYPE, false,
      NO_RECORD_DEF, "" },
    { "reconf-accept", D6O_RECONF_ACCEPT, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "sip-server-dns", D6O_SIP_SERVERS_DNS, DHCP6_OPTION_SPACE, OPT_FQDN_TYPE,
      true, NO_RECORD_DEF, "" },
    { "sip-server-addr", D6O_SIP_SERVERS_ADDR, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "dns-servers", D6O_NAME_SERVERS, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "domain-search", D6O_DOMAIN_SEARCH, DHCP6_OPTION_SPACE, OPT_FQDN_TYPE,
      true, NO_RECORD_DEF, "" },
    { "ia-pd", D6O_IA_PD, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(IA_PD_RECORDS), "" },
    { "iaprefix", D6O_IAPREFIX, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(IA_PREFIX_RECORDS), "" },
    { "nis-servers", D6O_NIS_SERVERS, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "nisp-servers", D6O_NISP_SERVERS, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "nis-domain-name", D6O_NIS_DOMAIN_NAME, DHCP6_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "nisp-domain-name", D6O_NISP_DOMAIN_NAME, DHCP6_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "sntp-servers", D6O_SNTP_SERVERS, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "information-refresh-time", D6O_INFORMATION_REFRESH_TIME,
      DHCP6_OPTION_SPACE,       OPT_UINT32_TYPE, false, NO_RECORD_DEF, "" },
    { "bcmcs-server-dns", D6O_BCMCS_SERVER_D, DHCP6_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "bcmcs-server-addr", D6O_BCMCS_SERVER_A, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "geoconf-civic", D6O_GEOCONF_CIVIC, DHCP6_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(GEOCONF_CIVIC_RECORDS), "" },
    { "remote-id", D6O_REMOTE_ID, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(REMOTE_ID_RECORDS), "" },
    { "subscriber-id", D6O_SUBSCRIBER_ID, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "client-fqdn", D6O_CLIENT_FQDN, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(CLIENT_FQDN_RECORDS), "" },
    { "pana-agent", D6O_PANA_AGENT, DHCP6_OPTION_SPACE, OPT_IPV6_ADDRESS_TYPE,
      true, NO_RECORD_DEF, "" },
    { "new-posix-timezone", D6O_NEW_POSIX_TIMEZONE, DHCP6_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "new-tzdb-timezone", D6O_NEW_TZDB_TIMEZONE, DHCP6_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "ero", D6O_ERO, DHCP6_OPTION_SPACE, OPT_UINT16_TYPE, true,
      NO_RECORD_DEF, "" },
    { "lq-query", D6O_LQ_QUERY, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(LQ_QUERY_RECORDS), DHCP6_OPTION_SPACE },
    { "client-data", D6O_CLIENT_DATA, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, DHCP6_OPTION_SPACE },
    { "clt-time", D6O_CLT_TIME, DHCP6_OPTION_SPACE, OPT_UINT32_TYPE, false,
      NO_RECORD_DEF, "" },
    { "lq-relay-data", D6O_LQ_RELAY_DATA, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(LQ_RELAY_DATA_RECORDS), "" },
    { "lq-client-link", D6O_LQ_CLIENT_LINK, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "v6-lost", D6O_V6_LOST, DHCP6_OPTION_SPACE, OPT_FQDN_TYPE, false,
      NO_RECORD_DEF, "" },
    { "capwap-ac-v6", D6O_CAPWAP_AC_V6, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "relay-id", D6O_RELAY_ID, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF, "" },
    { "v6-access-domain", D6O_V6_ACCESS_DOMAIN, DHCP6_OPTION_SPACE,
      OPT_FQDN_TYPE, false, NO_RECORD_DEF, "" },
    { "sip-ua-cs-list", D6O_SIP_UA_CS_LIST, DHCP6_OPTION_SPACE,
      OPT_FQDN_TYPE, true, NO_RECORD_DEF, "" },
    { "bootfile-url", D6O_BOOTFILE_URL, DHCP6_OPTION_SPACE, OPT_STRING_TYPE,
      false, NO_RECORD_DEF, "" },
    { "bootfile-param", D6O_BOOTFILE_PARAM, DHCP6_OPTION_SPACE, OPT_TUPLE_TYPE,
      true, NO_RECORD_DEF, "" },
    { "client-arch-type", D6O_CLIENT_ARCH_TYPE, DHCP6_OPTION_SPACE,
      OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "nii", D6O_NII, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(CLIENT_NII_RECORDS), "" },
    { "aftr-name", D6O_AFTR_NAME, DHCP6_OPTION_SPACE, OPT_FQDN_TYPE, false,
      NO_RECORD_DEF, "" },
    { "erp-local-domain-name", D6O_ERP_LOCAL_DOMAIN_NAME, DHCP6_OPTION_SPACE
      , OPT_FQDN_TYPE, false, NO_RECORD_DEF, "" },
    { "rsoo", D6O_RSOO, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE, false,
      NO_RECORD_DEF, "rsoo-opts" },
    { "pd-exclude", D6O_PD_EXCLUDE, DHCP6_OPTION_SPACE, OPT_IPV6_PREFIX_TYPE,
      false, NO_RECORD_DEF, "" },
    { "rdnss-selection", D6O_RDNSS_SELECTION, DHCP6_OPTION_SPACE,
      OPT_RECORD_TYPE, true, RECORD_DEF(V6_RDNSS_SELECT_RECORDS), "" },
    { "client-linklayer-addr", D6O_CLIENT_LINKLAYER_ADDR, DHCP6_OPTION_SPACE,
      OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "link-address", D6O_LINK_ADDRESS, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "solmax-rt", D6O_SOL_MAX_RT, DHCP6_OPTION_SPACE, OPT_UINT32_TYPE, false,
      NO_RECORD_DEF, "" },
    { "inf-max-rt", D6O_INF_MAX_RT, DHCP6_OPTION_SPACE, OPT_UINT32_TYPE, false,
      NO_RECORD_DEF, "" },
    { "dhcpv4-message", D6O_DHCPV4_MSG, DHCP6_OPTION_SPACE, OPT_BINARY_TYPE,
      false, NO_RECORD_DEF, "" },
    { "dhcp4o6-server-addr", D6O_DHCPV4_O_DHCPV6_SERVER, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "v6-captive-portal", D6O_V6_CAPTIVE_PORTAL, DHCP6_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "relay-source-port", D6O_RELAY_SOURCE_PORT, DHCP6_OPTION_SPACE,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" },
    { "v6-sztp-redirect", D60_V6_SZTP_REDIRECT, DHCP6_OPTION_SPACE,
      OPT_TUPLE_TYPE, true, NO_RECORD_DEF, "" },
    { "ipv6-address-andsf", D6O_IPV6_ADDRESS_ANDSF, DHCP6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "s46-cont-mape", D6O_S46_CONT_MAPE, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, MAPE_V6_OPTION_SPACE },
    { "s46-cont-mapt", D6O_S46_CONT_MAPT, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, MAPT_V6_OPTION_SPACE },
    { "s46-cont-lw", D6O_S46_CONT_LW, DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE,
      false, NO_RECORD_DEF, LW_V6_OPTION_SPACE },
    { "v6-dnr", D6O_V6_DNR, DHCP6_OPTION_SPACE, OPT_RECORD_TYPE,
     false, RECORD_DEF(V6_DNR_RECORDS), "" }

    // @todo There is still a bunch of options for which we have to provide
    // definitions but we don't do it because they are not really
    // critical right now.
};

/// Number of option definitions defined.
const int STANDARD_V6_OPTION_DEFINITIONS_SIZE =
    sizeof(STANDARD_V6_OPTION_DEFINITIONS) /
    sizeof(STANDARD_V6_OPTION_DEFINITIONS[0]);

/// @brief Definitions of vendor-specific DHCPv6 options, defined by ISC.
/// 4o6-* options are used for inter-process communication. For details, see
/// https://gitlab.isc.org/isc-projects/kea/wikis/designs/dhcpv4o6-design
///
/// @todo: As those options are defined by ISC, they do not belong in std_option_defs.h.
///        We need to move them to a separate file, e.g. isc_option_defs.h
const OptionDefParams ISC_V6_OPTION_DEFINITIONS[] = {
    { "4o6-interface", ISC_V6_4O6_INTERFACE, ISC_V6_OPTION_SPACE,
      OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "4o6-source-address", ISC_V6_4O6_SRC_ADDRESS, ISC_V6_OPTION_SPACE,
      OPT_IPV6_ADDRESS_TYPE, false, NO_RECORD_DEF, "" },
    { "4o6-source-port", ISC_V6_4O6_SRC_PORT, ISC_V6_OPTION_SPACE,
      OPT_UINT16_TYPE, false, NO_RECORD_DEF, "" }
};

const int ISC_V6_OPTION_DEFINITIONS_SIZE =
    sizeof(ISC_V6_OPTION_DEFINITIONS) /
    sizeof(ISC_V6_OPTION_DEFINITIONS[0]);

/// @brief MAPE option definitions
const OptionDefParams MAPE_V6_OPTION_DEFINITIONS[] = {
    { "s46-br", D6O_S46_BR, MAPE_V6_OPTION_SPACE, OPT_IPV6_ADDRESS_TYPE, false,
      NO_RECORD_DEF, "" },
    { "s46-rule", D6O_S46_RULE, MAPE_V6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(S46_RULE), V4V6_RULE_OPTION_SPACE }
};

const int MAPE_V6_OPTION_DEFINITIONS_SIZE =
    sizeof(MAPE_V6_OPTION_DEFINITIONS) /
    sizeof(MAPE_V6_OPTION_DEFINITIONS[0]);

/// @brief MAPT option definitions
const OptionDefParams MAPT_V6_OPTION_DEFINITIONS[] = {
    { "s46-rule", D6O_S46_RULE, MAPT_V6_OPTION_SPACE, OPT_RECORD_TYPE, false,
      RECORD_DEF(S46_RULE), V4V6_RULE_OPTION_SPACE },
    { "s46-dmr", D6O_S46_DMR, MAPT_V6_OPTION_SPACE, OPT_IPV6_PREFIX_TYPE,
      false, NO_RECORD_DEF, "" }
};

const int MAPT_V6_OPTION_DEFINITIONS_SIZE =
    sizeof(MAPT_V6_OPTION_DEFINITIONS) /
    sizeof(MAPT_V6_OPTION_DEFINITIONS[0]);

/// @brief LW option definitions
const OptionDefParams LW_V6_OPTION_DEFINITIONS[] = {
    { "s46-br", D6O_S46_BR, LW_V6_OPTION_SPACE, OPT_IPV6_ADDRESS_TYPE, false,
      NO_RECORD_DEF, "" },
    { "s46-v4v6bind", D6O_S46_V4V6BIND, LW_V6_OPTION_SPACE, OPT_RECORD_TYPE,
      false, RECORD_DEF(S46_V4V6BIND), V4V6_BIND_OPTION_SPACE }
};

const int LW_V6_OPTION_DEFINITIONS_SIZE =
    sizeof(LW_V6_OPTION_DEFINITIONS) /
    sizeof(LW_V6_OPTION_DEFINITIONS[0]);

/// @brief Rule option definitions
const OptionDefParams V4V6_RULE_OPTION_DEFINITIONS[] = {
    { "s46-portparams", D6O_S46_PORTPARAMS, V4V6_RULE_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(S46_PORTPARAMS), "" }
};

const int V4V6_RULE_OPTION_DEFINITIONS_SIZE =
    sizeof(V4V6_RULE_OPTION_DEFINITIONS) /
    sizeof(V4V6_RULE_OPTION_DEFINITIONS[0]);

/// @brief Bind option definitions
const OptionDefParams V4V6_BIND_OPTION_DEFINITIONS[] = {
    { "s46-portparams", D6O_S46_PORTPARAMS, V4V6_BIND_OPTION_SPACE,
      OPT_RECORD_TYPE, false, RECORD_DEF(S46_PORTPARAMS), "" }
};

const int V4V6_BIND_OPTION_DEFINITIONS_SIZE =
    sizeof(V4V6_BIND_OPTION_DEFINITIONS) /
    sizeof(V4V6_BIND_OPTION_DEFINITIONS[0]);

}  // namespace

}  // namespace dhcp
}  // namespace isc

#endif // STD_OPTION_DEFS_H
