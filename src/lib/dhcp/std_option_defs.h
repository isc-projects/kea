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

#ifndef NO_RECORD_DEF
#define NO_RECORD_DEF 0, 0
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
///
/// @warning in this array, the initializers are provided for all
/// OptionDefParams struct's members despite initializers for
/// 'records' and 'record_size' could be ommited for entries for
/// which 'type' does not equal to OPT_RECORD_TYPE. If initializers
/// are ommitted the corresponding values should default to 0.
/// This however does not work on Solaris (GCC) which issues a
/// warning about lack of initializers for some struct members
/// causing build to fail.
static const OptionDefParams OPTION_DEF_PARAMS6[] = {
    { "clientid", D6O_CLIENTID, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    { "serverid", D6O_SERVERID, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    { "ia-na", D6O_IA_NA, OPT_RECORD_TYPE, false, RECORD_DEF(ianaRecords) },
    { "ia-ta", D6O_IA_TA, OPT_UINT32_TYPE, false, NO_RECORD_DEF },
    { "iaaddr", D6O_IAADDR, OPT_RECORD_TYPE, false, RECORD_DEF(iaaddrRecords) },
    { "oro", D6O_ORO, OPT_UINT16_TYPE, true, NO_RECORD_DEF },
    { "preference", D6O_PREFERENCE, OPT_UINT8_TYPE, false, NO_RECORD_DEF },
    { "elapsed-time", D6O_ELAPSED_TIME, OPT_UINT16_TYPE, false, NO_RECORD_DEF },
    { "relay-msg", D6O_RELAY_MSG, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    // Unfortunatelly the AUTH option contains a 64-bit data field
    // called 'replay-detection' that can't be added as a record
    // field to a custom option. Also, there is no dedicated
    // option class to handle it so we simply return binary
    // option type for now.
    // @todo implement a class to handle AUTH option.
    { "auth", D6O_AUTH, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    { "unicast", D6O_UNICAST, OPT_IPV6_ADDRESS_TYPE, false, NO_RECORD_DEF },
    { "status-code", D6O_STATUS_CODE, OPT_RECORD_TYPE, false,
      RECORD_DEF(statusCodeRecords) },
    { "rapid-commit", D6O_RAPID_COMMIT, OPT_EMPTY_TYPE, false, NO_RECORD_DEF },
    { "user-class", D6O_USER_CLASS, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    { "vendor-class", D6O_VENDOR_CLASS, OPT_RECORD_TYPE, false,
      RECORD_DEF(vendorClassRecords) },
    { "vendor-opts", D6O_VENDOR_OPTS, OPT_RECORD_TYPE, false,
      RECORD_DEF(vendorOptsRecords) },
    { "interface-id", D6O_INTERFACE_ID, OPT_BINARY_TYPE, false, NO_RECORD_DEF },
    { "reconf-msg", D6O_RECONF_MSG, OPT_UINT8_TYPE, false, NO_RECORD_DEF },
    { "reconf-accept", D6O_RECONF_ACCEPT, OPT_EMPTY_TYPE, false,
      NO_RECORD_DEF },
    { "sip-server-dns", D6O_SIP_SERVERS_DNS, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF },
    { "sip-server-addr", D6O_SIP_SERVERS_ADDR, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "dns-servers", D6O_NAME_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "domain-search", D6O_DOMAIN_SEARCH, OPT_FQDN_TYPE, true, NO_RECORD_DEF },
    { "ia-pd", D6O_IA_PD, OPT_RECORD_TYPE, false, RECORD_DEF(iapdRecords) },
    { "iaprefix", D6O_IAPREFIX, OPT_RECORD_TYPE, false,
      RECORD_DEF(iaPrefixRecords) },
    { "nis-servers", D6O_NIS_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "nisp-servers", D6O_NISP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "nis-domain-name", D6O_NIS_DOMAIN_NAME, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF },
    { "nisp-domain-name", D6O_NISP_DOMAIN_NAME, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF },
    { "sntp-servers", D6O_SNTP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "information-refresh-time", D6O_INFORMATION_REFRESH_TIME,
      OPT_UINT32_TYPE, false, NO_RECORD_DEF },
    { "bcmcs-server-dns", D6O_BCMCS_SERVER_D, OPT_FQDN_TYPE, true,
      NO_RECORD_DEF },
    { "bcmcs-server-addr", D6O_BCMCS_SERVER_A, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "geoconf-civic", D6O_GEOCONF_CIVIC, OPT_RECORD_TYPE, false,
      RECORD_DEF(geoconfCivicRecords) },
    { "remote-id", D6O_REMOTE_ID, OPT_RECORD_TYPE, false,
      RECORD_DEF(remoteIdRecords) },
    { "subscriber-id", D6O_SUBSCRIBER_ID, OPT_BINARY_TYPE, false,
      NO_RECORD_DEF },
    { "client-fqdn", D6O_CLIENT_FQDN, OPT_RECORD_TYPE, false,
      RECORD_DEF(clientFqdnRecords) },
    { "pana-agent", D6O_PANA_AGENT, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF },
    { "new-posix-timezone", D6O_NEW_POSIX_TIMEZONE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF },
    { "new-tzdb-timezone", D6O_NEW_TZDB_TIMEZONE, OPT_STRING_TYPE, false,
      NO_RECORD_DEF },
    { "ero", D6O_ERO, OPT_UINT16_TYPE, true, NO_RECORD_DEF },
    { "lq-query", D6O_LQ_QUERY, OPT_RECORD_TYPE, false,
      RECORD_DEF(lqQueryRecords) },
    { "client-data", D6O_CLIENT_DATA, OPT_EMPTY_TYPE, false, NO_RECORD_DEF },
    { "clt-time", D6O_CLT_TIME, OPT_UINT32_TYPE, false, NO_RECORD_DEF },
    { "lq-relay-data", D6O_LQ_RELAY_DATA, OPT_RECORD_TYPE, false,
      RECORD_DEF(lqRelayData) },
    { "lq-client-link", D6O_LQ_CLIENT_LINK, OPT_IPV6_ADDRESS_TYPE, true,
      NO_RECORD_DEF }

    // @todo There is still a bunch of options for which we have to provide
    // definitions but we don't do it because they are not really
    // critical right now.
};

/// Number of option definitions defined.
const int OPTION_DEF_PARAMS_SIZE6  =
    sizeof(OPTION_DEF_PARAMS6) / sizeof(OPTION_DEF_PARAMS6[0]);

}; // anonymous namespace

#endif // STD_OPTION_DEFS_H
