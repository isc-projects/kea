// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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

namespace isc {
namespace yang {

/// Subnet (aka network range) translation between YANG and JSON
///
/// JSON syntax for kea-dhcp4 is:
/// @code
/// {
///     "valid-lifetime": <valid lifetime>,
///     "min-valid-lifetime": <minimum valid lifetime>,
///     "max-valid-lifetime": <maximum valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "calculate-tee-times": <calculate T1/T2 times>,
///     "t1-percent": <T1 percent>,
///     "t2-percent": <T2 percent>,
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
///     "4o6-interface": "<dhcpv4-over-dhcpv6 interface>",
///     "4o6-interface-id": "<dhcpv4-over-dhcpv6 interface id>",
///     "4o6-subnet": "<dhcpv4-over-dhcpv6 subnet>",
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
///     "min-preferred-lifetime": <minimum preferred lifetime>,
///     "max-preferred-lifetime": <maximum preferred lifetime>,
///     "valid-lifetime": <valid lifetime>,
///     "min-valid-lifetime": <minimum valid lifetime>,
///     "max-valid-lifetime": <maximum valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "calculate-tee-times": <calculate T1/T2 times>,
///     "t1-percent": <T1 percent>,
///     "t2-percent": <T2 percent>,
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
///  +--rw subnet[46]* [id]
///     +--rw valid-lifetime?                 uint32
///     +--rw min-valid-lifetime?             uint32
///     +--rw max-valid-lifetime?             uint32
///     +--rw renew-timer?                    uint32
///     +--rw rebind-timer?                   uint32
///     +--rw calculate-tee-times?            boolean
///     +--rw t1-percent?                     decimal64
///     +--rw t2-percent?                     decimal64
///     +--rw option-data* [code space]
///     +--rw pool* [start-address end-address]
///     +--rw subnet                          inet:ipv4-prefix
///     +--rw interface?                      string
///     +--rw id                              uint32
///     +--rw client-class?                   string
///     +--rw require-client-classes*         string
///     +--rw host* [identifier-type identifier]
///     +--rw reservation-mode?               host-reservation-mode
///     +--rw relay
///     +--rw cache-max-age?                  uint32
///     +--rw cache-threshold?                decimal64
///     +--rw ddns-generated-prefix?          string
///     +--rw ddns-override-client-update?    boolean
///     +--rw ddns-override-no-update?        boolean
///     +--rw ddns-qualifying-suffix?         string
///     +--rw ddns-replace-client-name?       string
///     +--rw ddns-send-updates?              boolean
///     +--rw ddns-update-on-renew?           boolean
///     +--rw ddns-use-conflict-resolution?   boolean
///     +--rw hostname-char-replacement?      string
///     +--rw hostname-char-set?              string
///     +--rw reservations-global?            boolean
///     +--rw reservations-in-subnet?         boolean
///     +--rw reservations-out-of-pool?       boolean
///     +--rw store-extended-info?            boolean
///     +--rw user-context?                   user-context
///
///  DHCPv4 only:
///  +--rw match-client-id?          boolean
///  +--rw next-server?              inet:ipv4-address
///  +--rw server-hostname?          string
///  +--rw boot-file-name?           string
///  +--rw subnet-4o6-interface?     string
///  +--rw subnet-4o6-interface-id?  string
///  +--rw subnet-4o6-subnet?        inet:ipv6-prefix
///  +--rw authoritative?            boolean
///
///  DHCPv6 only:
///  +--rw preferred-lifetime?       uint32
///  +--rw min-preferred-lifetime?   uint32
///  +--rw max-preferred-lifetime?   uint32
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
    TranslatorSubnet(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorSubnet() = default;

    /// @brief Get and translate a subnet from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the subnet configuration
    ///
    /// @return the JSON representation of the subnet
    ///
    /// @throw NetconfError when sysrepo raises an error.
    /// @throw BadValue on a subnet without prefix or id.
    isc::data::ElementPtr getSubnet(libyang::DataNode const& data_node);

    /// @brief Get and translate a subnet from YANG to JSON.
    ///
    /// @param xpath The xpath of the subnet.
    ///
    /// @return JSON representation of the subnet.
    ///
    /// @throw NetconfError when sysrepo raises an error.
    /// @throw BadValue on a subnet without prefix or id.
    isc::data::ElementPtr getSubnetFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set subnet from JSON to YANG.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    /// @throw BadValue on a subnet without prefix.
    void setSubnet(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getSubnet for ietf-dhcpv6-server.
    ///
    /// @param data_node the YANG node representing the subnet configuration
    ///
    /// @return JSON representation of the subnet.
    isc::data::ElementPtr getSubnetIetf6(libyang::DataNode const& data_node);

    /// @brief setSubnet for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    void setSubnetIetf6(const std::string& xpath,
                        isc::data::ConstElementPtr elem);

    /// @brief getSubnet for kea-dhcp[46]-server.
    ///
    /// @param data_node the YANG node representing the subnet configuration
    ///
    /// @return JSON representation of the subnet.
    isc::data::ElementPtr getSubnetKea(libyang::DataNode const& data_node);

    /// @brief setSubnet for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the subnet.
    /// @param elem The JSON element.
    void setSubnetKea(const std::string& xpath,
                      isc::data::ConstElementPtr elem);
};  // TranslatorSubnets

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
    TranslatorSubnets(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorSubnets() = default;

    /// @brief Get and translate subnets from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the list of subnets
    ///
    /// @return the JSON representation of the list of subnets
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSubnets(libyang::DataNode const& data_node);

    /// @brief Get and translate subnets from YANG to JSON.
    ///
    /// @param xpath The xpath of the subnet list.
    ///
    /// @return the JSON representation of the list of subnets
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSubnetsFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set subnets from JSON to YANG.
    ///
    /// @param xpath The xpath of the subnet list.
    /// @param elem The JSON element.
    /// @throw BadValue on a subnet without id.
    void setSubnets(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getSubnets common part.
    ///
    /// @param data_node the YANG node representing the list of subnets
    /// @param subsel The subnet list name.
    ///
    /// @return the JSON representation of the list of subnets
    isc::data::ElementPtr getSubnetsCommon(libyang::DataNode const& data_node,
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
};  // TranslatorSubnets

}  // namespace yang
}  // namespace isc

#endif  // ISC_TRANSLATOR_SUBNET_H
