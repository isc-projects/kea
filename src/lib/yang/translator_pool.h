// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_POOL_H
#define ISC_TRANSLATOR_POOL_H 1

#include <yang/translator_option_data.h>
#include <list>

namespace isc {
namespace yang {

/// @brief A translator class for converting a pool between YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server and partially ietf-dhcpv6-server.
///
/// JSON syntax for both kea-dhcp4 and kea-dhcp6 is:
/// @code
/// {
///     "pool": "<pool prefix or start - end addresses>",
///     "option-data": [ <list of option data> ],
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax is for ietf-dhcpv6-server is with pool-id as the key:
/// @code
///  +--rw pool-id               uint32
///  +--rw pool-prefix           inet:ipv6-prefix
///  +--rw start-address         inet:ipv6-address-no-zone
///  +--rw end-address           inet:ipv6-address-no-zone
///  +--rw valid-lifetime        yang:timeticks
///  +--rw renew-time            yang:timeticks
///  +--rw rebind-time           yang:timeticks
///  +--rw preferred-lifetime    yang:timeticks
///  +--rw rapid-commit?         boolean
///  +--rw client-class?         string
///  +--rw max-address-count     threshold
///  +--rw option-set-id
///     /server/server-config/option-sets/option-set/option-set-id
/// @endcode
///
/// YANG syntax for kea-dhcp[46] is with start-address and end-address
/// as the keys:
/// @code
/// +--rw prefix?                  inet:ipv[46]-prefix
/// +--rw start-address            inet:ipv[46]-address
/// +--rw end-address              inet:ipv[46]-address
/// +--rw option-data*
/// +--rw client-class?            string
/// +--rw require-client-classes*  string
/// +--rw user-context?            string
/// @endcode
///
/// An example in JSON and YANG formats for the IETF model:
/// @code
/// [
///     {
///         "pool": "2001:db8::/112"
///     }
/// ]
/// @endcode
/// @code
///  /ietf-dhcpv6-server:server (container)
///  /ietf-dhcpv6-server:server/server-config (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/network-range-id = 111
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/network-prefix = 2001:db8::/48
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0']/pool-id = 0
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0']/pool-prefix = 2001:db8::1:0/112
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0']/start-address = 2001:db8::1:0
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0']/end-address = 2001:db8::1:ffff
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     network-range[network-range-id='111']/address-pools/
///     address-pool[pool-id='0']/max-address-count = disabled
/// @endcode
///
/// An example in JSON and YANG formats for the Kea model:
/// @code
/// [
///     {
///         "pool": "2001:db8::1 - 2001:db8::100"
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/subnet6[id='111'] (list instance)
///  /kea-dhcp6-server:config/subnet6[id='111']/id = 111
///  /kea-dhcp6-server:config/subnet6[id='111']/subnet = 2001:db8::/48
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pool[start-address='2001:db8::1'][end-address='2001:db8::100']
///     (list instance)
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pool[start-address='2001:db8::1'][end-address='2001:db8::100']/
///     start-address = 2001:db8::1
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pool[start-address='2001:db8::1'][end-address='2001:db8::100']/
///     end-address = 2001:db8::100
/// @endcode
class TranslatorPool : virtual public TranslatorOptionDataList {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorPool(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorPool();

    /// @brief Get and translate a pool from YANG to JSON.
    ///
    /// @param xpath The xpath of the pool.
    /// @return JSON representation of the pool.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPool(const std::string& xpath);

    /// @brief Translate and set (address) pool from JSON to YANG.
    ///
    /// @param xpath The xpath of the pool.
    /// @param elem The JSON element.
    void setPool(const std::string& xpath, isc::data::ConstElementPtr elem);

    /// @brief Get start and end addresses from prefix.
    ///
    /// @param prefix The prefix string.
    /// @param start_address The reference to the start_address.
    /// @param end_address The reference to the end_address.
    /// @throw BadValue when the prefix is not correctly formed.
    static void getAddresses(const std::string& prefix,
                             std::string& start_address,
                             std::string& end_address);

protected:
    /// @brief getPool for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the pool.
    /// @return JSON representation of the pool.
    /// @throw BadValue on pool without prefix.
    isc::data::ElementPtr getPoolIetf6(const std::string& xpath);

    /// @brief setPool for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the pool.
    /// @param elem The JSON element.
    /// @throw BadValue on pool without prefix and with a range which is
    /// not a prefix.
    void setPoolIetf6(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

    /// @brief getPool for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the pool.
    /// @return JSON representation of the pool.
    /// @throw BadValue on a pool without prefix and start or end address.
    isc::data::ElementPtr getPoolKea(const std::string& xpath);

    /// @brief setPool for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the pool.
    /// @param elem The JSON element.
    /// @throw BadValue on a pool without a well formed prefix.
    void setPoolKea(const std::string& xpath, isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting pools between YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server and partially ietf-dhcpv6-server.
class TranslatorPools : virtual public TranslatorPool {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorPools(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorPools();

    /// @brief Get and translate pools from YANG to JSON.
    ///
    /// @param xpath The xpath of the pool list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPools(const std::string& xpath);

    /// @brief Translate and set (address) pools from JSON to YANG.
    ///
    /// @param xpath The xpath of the pool list.
    /// @param elem The JSON element.
    void setPools(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getPools for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the pool list.
    isc::data::ElementPtr getPoolsIetf(const std::string& xpath);

    /// @brief getPools for kea-dhcp[46]-server.
    ///
    /// @param xpath The xpath of the pool list.
    isc::data::ElementPtr getPoolsKea(const std::string& xpath);

    /// @brief setPools using pool-id.
    ///
    /// @param xpath The xpath of the pool list.
    /// @param elem The JSON element.
    void setPoolsById(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

    /// @brief setPools using address pair.
    ///
    /// @param xpath The xpath of the pool list.
    /// @param elem The JSON element.
    /// @throw BadValue on a pool without a prefix.
    void setPoolsByAddresses(const std::string& xpath,
                             isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_POOL_H
