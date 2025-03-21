// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_H
#define RADIUS_CLIENT_H

namespace isc {
namespace radius {

/// @brief Attribute types.
///
/// From freeRADIUS client include and dictionary with fixes when
/// the two sources differed.
enum AttrType : uint8_t {
    PW_USER_NAME                = 1,    //!< string.
    PW_USER_PASSWORD            = 2,    //!< string.
    PW_CHAP_PASSWORD            = 3,    //!< string.
    PW_NAS_IP_ADDRESS           = 4,    //!< ipaddr.
    PW_NAS_PORT                 = 5,    //!< integer.
    PW_SERVICE_TYPE             = 6,    //!< integer.
    PW_FRAMED_PROTOCOL          = 7,    //!< integer.
    PW_FRAMED_IP_ADDRESS        = 8,    //!< ipaddr.
    PW_FRAMED_IP_NETMASK        = 9,    //!< ipaddr.
    PW_FRAMED_ROUTING           = 10,   //!< integer.
    PW_FILTER_ID                = 11,   //!< string.
    PW_FRAMED_MTU               = 12,   //!< integer.
    PW_FRAMED_COMPRESSION       = 13,   //!< integer.
    PW_LOGIN_IP_HOST            = 14,   //!< ipaddr.
    PW_LOGIN_SERVICE            = 15,   //!< integer.
    PW_LOGIN_TCP_PORT           = 16,   //!< integer.
    // PW_OLD_PASSWORD          = 17,   //!< deprecated.
    PW_REPLY_MESSAGE            = 18,   //!< string.
    PW_CALLBACK_NUMBER          = 19,   //!< string.
    PW_CALLBACK_ID              = 20,   //!< string.
    // PW_EXPIRATION            = 21,   //!< deprecated.
    PW_FRAMED_ROUTE             = 22,   //!< string.
    PW_FRAMED_IPX_NETWORK       = 23,   //!< ipaddr.
    PW_STATE                    = 24,   //!< string.
    PW_CLASS                    = 25,   //!< string.
    PW_VENDOR_SPECIFIC          = 26,   //!< string.
    PW_SESSION_TIMEOUT          = 27,   //!< integer.
    PW_IDLE_TIMEOUT             = 28,   //!< integer.
    PW_TERMINATION_ACTION       = 29,   //!< integer.
    PW_CALLED_STATION_ID        = 30,   //!< string.
    PW_CALLING_STATION_ID       = 31,   //!< string.
    PW_NAS_IDENTIFIER           = 32,   //!< string.
    PW_PROXY_STATE              = 33,   //!< string.
    PW_LOGIN_LAT_SERVICE        = 34,   //!< string.
    PW_LOGIN_LAT_NODE           = 35,   //!< string.
    PW_LOGIN_LAT_GROUP          = 36,   //!< string.
    PW_FRAMED_APPLETALK_LINK    = 37,   //!< integer.
    PW_FRAMED_APPLETALK_NETWORK = 38,   //!< integer.
    PW_FRAMED_APPLETALK_ZONE    = 39,   //!< string.
    PW_ACCT_STATUS_TYPE         = 40,   //!< integer.
    PW_ACCT_DELAY_TIME          = 41,   //!< integer.
    PW_ACCT_INPUT_OCTETS        = 42,   //!< integer.
    PW_ACCT_OUTPUT_OCTETS       = 43,   //!< integer.
    PW_ACCT_SESSION_ID          = 44,   //!< string.
    PW_ACCT_AUTHENTIC           = 45,   //!< integer.
    PW_ACCT_SESSION_TIME        = 46,   //!< integer.
    PW_ACCT_INPUT_PACKETS       = 47,   //!< integer.
    PW_ACCT_OUTPUT_PACKETS      = 48,   //!< integer.
    PW_ACCT_TERMINATE_CAUSE     = 49,   //!< integer.
    PW_ACCT_MULTI_SESSION_ID    = 50,   //!< string.
    PW_ACCT_LINK_COUNT          = 51,   //!< integer.
    PW_ACCT_INPUT_GIGAWORDS     = 52,   //!< integer.
    PW_ACCT_OUTPUT_GIGAWORDS    = 53,   //!< integer.
    PW_EVENT_TIMESTAMP          = 55,   //!< integer.
    PW_EGRESS_VLANID            = 56,   //!< string.
    PW_INGRESS_FILTERS          = 57,   //!< integer.
    PW_EGRESS_VLAN_NAME         = 58,   //!< string.
    PW_USER_PRIORITY_TABLE      = 59,   //!< string.
    PW_CHAP_CHALLENGE           = 60,   //!< string.
    PW_NAS_PORT_TYPE            = 61,   //!< integer.
    PW_PORT_LIMIT               = 62,   //!< integer.
    PW_LOGIN_LAT_PORT           = 63,   //!< string.
    PW_TUNNEL_TYPE              = 64,   //!< string.
    PW_TUNNEL_MEDIUM_TYPE       = 65,   //!< integer.
    PW_TUNNEL_CLIENT_ENDPOINT   = 66,   //!< string.
    PW_TUNNEL_SERVER_ENDPOINT   = 67,   //!< string.
    PW_ACCT_TUNNEL_CONNECTION   = 68,   //!< string.
    PW_TUNNEL_PASSWORD          = 69,   //!< string.
    PW_ARAP_PASSWORD            = 70,   //!< string.
    PW_ARAP_FEATURES            = 71,   //!< string.
    PW_ARAP_ZONE_ACCESS         = 72,   //!< integer.
    PW_ARAP_SECURITY            = 73,   //!< integer.
    PW_ARAP_SECURITY_DATA       = 74,   //!< string.
    PW_PASSWORD_RETRY           = 75,   //!< integer.
    PW_PROMPT                   = 76,   //!< integer.
    PW_CONNECT_INFO             = 77,   //!< string.
    PW_CONFIGURATION_TOKEN      = 78,   //!< string.
    PW_EAP_MESSAGE              = 79,   //!< string.
    PW_MESSAGE_AUTHENTICATOR    = 80,   //!< string.
    PW_TUNNEL_PRIVATE_GROUP_ID  = 81,   //!< string.
    PW_TUNNEL_ASSIGNMENT_ID     = 82,   //!< string.
    PW_TUNNEL_PREFERENCE        = 83,   //!< string.
    PW_ARAP_CHALLENGE_RESPONSE  = 84,   //!< string.
    PW_ACCT_INTERIM_INTERVAL    = 85,   //!< integer.
    PW_ACCT_TUNNEL_PACKETS_LOST = 86,   //!< integer.
    PW_NAS_PORT_ID_STRING       = 87,   //!< string.
    PW_FRAMED_POOL              = 88,   //!< string.
    PW_CHARGEABLE_USER_IDENTITY = 89,   //!< string.
    PW_TUNNEL_CLIENT_AUTH_ID    = 90,   //!< string.
    PW_TUNNEL_SERVER_AUTH_ID    = 91,   //!< string.
    PW_NAS_FILTER_RULE          = 92,   //!< string.
    PW_ORIGINATING_LINE_INFO    = 94,   //!< string.
    PW_NAS_IPV6_ADDRESS         = 95,   //!< ipv6addr.
    PW_FRAMED_INTERFACE_ID      = 96,   //!< string.
    PW_FRAMED_IPV6_PREFIX       = 97,   //!< ipv6prefix.
    PW_LOGIN_IPV6_HOST          = 98,   //!< string.
    PW_FRAMED_IPV6_ROUTE        = 99,   //!< string.
    PW_FRAMED_IPV6_POOL         = 100,  //!< string.
    PW_ERROR_CAUSE              = 101,  //!< integer.
    PW_EAP_KEY_NAME             = 102,  //!< string.
    PW_DELEGATED_IPV6_PREFIX    = 123,  //!< ipv6prefix.
    PW_FRAMED_IPV6_ADDRESS      = 168,  //!< ipv6addr.
    PW_DNS_SERVER_IPV6_ADDRESS  = 169,  //!< ipv6addr.
    PW_ROUTE_IPV6_INFORMATION   = 170,  //!< ipv6prefix.
    // 192-223 Experimental Use.
    // 224-240 Private Use.
    // 240-246 Extended Attributes.
    // 247-255 Reserved.
};

/// @brief Accounting Status Type.
enum AcctStatusType : uint32_t {
    PW_STATUS_START         = 1,
    PW_STATUS_STOP          = 2,
    PW_STATUS_ALIVE         = 3,
    PW_STATUS_MODEM_START   = 4,
    PW_STATUS_MODEM_STOP    = 5,
    PW_STATUS_CANCEL        = 6,
    PW_ACCOUNTING_ON        = 7,
    PW_ACCOUNTING_OFF       = 8
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
