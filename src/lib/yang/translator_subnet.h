// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_SUBNET_H
#define ISC_TRANSLATOR_SUBNET_H 1

#include <yang/translator.h>
#include <yang/translator_pool.h>
#include <yang/translator_pd_pool.h>
#include <yang/translator_host.h>
#include <list>

namespace isc {
namespace yang {

/// Subnet (aka network range) translation between YANG and JSON
///
/// JSON syntax for kea-dhcp4 is:
/// @code
/// {
///     "valid-lifetime": <valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "option-data": [ <list of option data> ],
///     "pools": [ <list of pools> ],
///     "subnet": "<subnet prefix>",
///     "interface": "<interface>",
///     "id": <id>,
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "reservations": [ <list of host reservations> ],
///     "reservation-mode": <host reservation mode>,
///     "relay": <relay ip address(es)>,
///     "match-client-id": <match client id flag>,
///     "next-server": "<next server>",
///     "server-hostname": "<server hostname>",
///     "boot-file-name": "<boot file name>",
///     "4o6-interface": "<dhpv4-over-dhcpv6 interface>",
///     "4o6-interface-id": "<dhpv4-over-dhcpv6 interface id>",
///     "4o6-subnet": "<dhpv4-over-dhcpv6 subnet>",
///     "authoritative": <authoritative flag>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// JSON syntax for kea-dhcp6 is:
/// @code
/// {
///     "preferred-lifetime": <preferred lifetime>,
///     "valid-lifetime": <valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "option-data": [ <list of option data> ],
///     "pools": [ <list of pools> ],
///     "pd-pools": [ <list of prefix delegation pools> ],
///     "subnet": "<subnet prefix>",
///     "interface": "<interface>",
///     "interface-id": "<interface id>",
///     "id": <id>,
///     "rapid-commit": <rapid commit flag>,
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "reservations": [ <list of host reservations> ],
///     "reservation-mode": <host reservation mode>,
///     "relay": <relay ip address(es)>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for ietf-dhcpv6-server is with network-range-id as the key:
/// @code
///  +--rw network-range-id      uint32
///  +--rw network-description   string
///  +--rw network-prefix        inet:ipv4-prefix
///  +--rw option-set-id?
///     /server/server-config/option-sets/option-set/option-set-id
///  +--rw address-pool*         [pool-id]
///  +--rw pd-pool*              [pool-id]
///  +--rw host-reservations     host-reservation* [cli-id]
/// @endcode
///
/// YANG syntax for kea-dhcp[46]-server is with id as the key:
/// @code
///  +--rw valid-lifetime?           uint32
///  +--rw renew-timer?              uint32
///  +--rw rebind-timer?             uint32
///  +--rw option-data*
///  +--rw pool*
///  +--rw subnet                    inet:ip-prefix
///  +--rw interface?                string
///  +--rw id                        uint32
///  +--rw client-class?             string
///  +--rw require-client-classes*   string
///  +--rw host*
///  +--rw reservation-mode?         enumeration
///  +--rw relay                     ip-addresses*
///  +--rw user-context?             string
///  (DHCPv4 only)
///  +--rw match-client-id?          boolean
///  +--rw next-server?              inet:ipv4-address
///  +--rw server-hostname?          string
///  +--rw boot-file-name?           string
///  +--rw subnet-4o6-interface?     string
///  +--rw subnet-4o6-interface-id?  string
///  +--rw subnet-4o6-subnet?        inet:ipv6-prefix
///  +--rw authoritative?            boolean
///  (DHCPv6 only)
///  +--rw preferred-lifetime?       uint32
///  +--rw pd-pool*
///  +--rw interface-id?             string
///  +--rw rapid-commit?             boolean
/// @endcode
///
/// An example in JSON and YANG formats for the IETF model:
/// @code
/// [
///     {
///         "subnet": "2001:db8::/48",
///         "id": 123,
///         "pools":
///             [
///                 {
///                     "pool": "2001:db8::1:0/112"
///                 },
///                 {
///                     "pool": "2001:db8::2:0/112"
///                 }
///             ]
///     }
/// ]
/// @endcode
/// @code
///  /ietf-dhcpv6-server:server (container)
///  /ietf-dhcpv6-server:server/server-config (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/network-range-id = 123
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/network-prefix = 2001:db8::/48
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0']/pool-id = 0
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0']/pool-prefix = 2001:db8::1:0/112
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0']/start-address = 2001:db8::1:0
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0']/end-address = 2001:db8::1:ffff
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='0']/max-address-count = disabled
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1']/pool-id = 1
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1']/pool-prefix = 2001:db8::2:0/112
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1']/start-address = 2001:db8::2:0
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1']/end-address = 2001:db8::2:ffff
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='123']/address-pools/
///     address-pool[pool-id='1']/max-address-count = disabled
/// @endcode
///
/// An example in JSON and YANG formats for the Kea model:
/// @code
/// [
///     {
///         "subnet": "10.0.1.0/24",
///         "id": 123,
///         "pools":
///             [
///                 {
///                     "pool": "10.0.1.0/28",
///                 },
///                 {
///                     "pool": "10.0.1.200 - 10.0.1.222"
///                 }
///             ]
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp4-server:config (container)
///  /kea-dhcp4-server:config/subnet4[id='123'] (list instance)
///  /kea-dhcp4-server:config/subnet4[id='123']/id = 123
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.0'][end-address='10.0.1.15'] (list instance)
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.0'][end-address='10.0.1.15']/
///     start-address = 10.0.1.0
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.0'][end-address='10.0.1.15']/
///     end-address = 10.0.1.15
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.0'][end-address='10.0.1.15']/
///     prefix = 10.0.1.0/28
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.200'][end-address='10.0.1.222']
///     (list instance)
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.200'][end-address='10.0.1.222']/
///     start-address = 10.0.1.200
///  /kea-dhcp4-server:config/subnet4[id='123']/
///     pool[start-address='10.0.1.200'][end-address='10.0.1.222']/
///     end-address = 10.0.1.222
///  /kea-dhcp4-server:config/subnet4[id='123']/subnet = 10.0.1.0/24
/// @endcode

/// @brief A translator class for converting a subnet between YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server and partially ietf-dhcpv6-server.
class TranslatorSubnet : virtual public TranslatorPools,
    virtual public TranslatorPdPools, virtual public TranslatorHosts {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    TranslatorSubnet(sysrepo::S_Session session, const std::string& model);
#else
    TranslatorSubnet(S_Session session, const std::string& model);
#endif

    /// @brief Destructor.
    virtual ~TranslatorSubnet();

    /// @brief Get and translate a subnet from YANG to JSON.
    ///
    /// @param xpath The xpath of the subnet.
    /// @return JSON representation of the subnet.
    /// @throw SysrepoError when sysrepo raises an error.
    /// @throw BadValue on a subnet without prefix or id.
    isc::data::ElementPtr getSubnet(const std::string& xpath);

    /// @brief Translate and set subnet from JSON to YANG.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    /// @throw BadValue on a subnet without prefix.
    void setSubnet(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getSubnet for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @return JSON representation of the subnet.
    isc::data::ElementPtr getSubnetIetf6(const std::string& xpath);

    /// @brief setSubnet for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    void setSubnetIetf6(const std::string& xpath,
                        isc::data::ConstElementPtr elem);

    /// @brief getSubnet for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @return JSON representation of the subnet.
    isc::data::ElementPtr getSubnetKea(const std::string& xpath);

    /// @brief setSubnet for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    void setSubnetKea(const std::string& xpath,
                      isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting a subnet list between
/// YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server and partially ietf-dhcpv6-server.
class TranslatorSubnets : virtual public TranslatorSubnet {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    TranslatorSubnets(sysrepo::S_Session session, const std::string& model);
#else
    TranslatorSubnets(S_Session session, const std::string& model);
#endif

    /// @brief Destructor.
    virtual ~TranslatorSubnets();

    /// @brief Get and translate subnets from YANG to JSON.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getSubnets(const std::string& xpath);

    /// @brief Translate and set subnets from JSON to YANG.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @param elem The JSON element.
    /// @throw BadValue on a subnet without id.
    void setSubnets(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getSubnets common part.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @param subsel The subnet list name.
    isc::data::ElementPtr getSubnetsCommon(const std::string& xpath,
                                           const std::string& subsel);

    /// @brief setSubnets for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @param elem The JSON element.
    void setSubnetsIetf6(const std::string& xpath,
                         isc::data::ConstElementPtr elem);

    /// @brief setSubnets for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @param elem The JSON element.
    /// @param subsel The subnet list name.
    void setSubnetsKea(const std::string& xpath,
                       isc::data::ConstElementPtr elem,
                       const std::string& subsel);
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_SUBNET_H
