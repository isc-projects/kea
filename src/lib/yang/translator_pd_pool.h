// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_PD_POOL_H
#define ISC_TRANSLATOR_PD_POOL_H 1

#include <yang/translator_option_data.h>
#include <list>

namespace isc {
namespace yang {

/// Prefix delegation pool translation between YANG and JSON
///
/// JSON syntax for kea-dhcp6-server is:
/// @code
/// {
///     "prefix": <prefix base>,
///     "prefix-len": <prefix length>,
///     "delegated-len": <delegated length>,
///     "excluded-prefix": <excluded prefix>,
///     "excluded-prefix-len": <excluded prefix length>,
///     "option-data": [ <list of option data> ],
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for ietf-dhcpv6-server is with pool-id as the key.
/// @code
///  +--rw pool-id                     uint32
///  +--rw prefix                      inet:ipv6-prefix
///  +--rw prefix-length               uint8
///  +--rw valid-lifetime              yang:timeticks
///  +--rw renew-time                  yang:timeticks
///  +--rw rebind-time                 yang:timeticks
///  +--rw preferred-lifetime          yang:timeticks
///  +--rw rapid-commit?               boolean
///  +--rw client-class?               string
///  +--rw max-pd-space-utilization?   threshold
///  +--rw option-set-id?
///     /server/server-config/option-sets/option-set/option-set-id
/// @endcode
///
/// YANG syntax for kea-dhcp6-server is with prefix as the key.
/// @code
/// +--rw pd-pool* [prefix]
///    +--rw prefix                    inet:ipv6-prefix
///    +--rw delegated-len?            uint8
///    +--rw option-data* [code space]
///    +--rw client-class?             string
///    +--rw require-client-classes*   string
///    +--rw excluded-prefix?          inet:ipv6-prefix
///    +--rw user-context?             user-context
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "prefix": "2001:db8:0:1000::",
///         "prefix-len": 56,
///         "delegated-len": 64
///     }
/// ]
/// @endcode
/// @code
///  /ietf-dhcpv6-server:server (container)
///  /ietf-dhcpv6-server:server/server-config (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/network-range-id = 111
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/network-prefix = 2001:db8::/48
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/pd-pools (container)
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/pd-pools/
///     pd-pool[pool-id='0'] (list instance)
///  /ietf-dhcpv6-server:server/server-config/network-ranges/
///     pd-pool[pool-id='0']/pool-id = 0
///     network-range[network-range-id='111']/pd-pools/
///     pd-pool[pool-id='0']/prefix = 2001:db8:0:1000::/56
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/pd-pools/
///     pd-pool[pool-id='0']/prefix-length = 56
///  /ietf-dhcpv6-server:server/server-config/network-ranges
///     network-range[network-range-id='111']/pd-pools/
///     pd-pool[pool-id='0']/max-pd-space-utilization = disabled
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/subnet6[id='111'] (list instance)
///  /kea-dhcp6-server:config/subnet6[id='111']/id = 111
///  /kea-dhcp6-server:config/subnet6[id='111']/subnet = 2001:db8::/48
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pd-pool[prefix='2001:db8:0:1000::/56' (list instance)
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pd-pool[prefix='2001:db8:0:1000::/56'/prefix = 2001:db8:0:1000::/56
///  /kea-dhcp6-server:config/subnet6[id='111']/
///     pd-pool[prefix='2001:db8:0:1000::/56'/delegated-len = 64
/// @endcode

/// @brief A translator class for converting a pd-pool between
/// YANG and JSON.
///
/// Currently supported models:
/// - kea-dhcp6-server
/// - ietf-dhcpv6-server (partial support)
class TranslatorPdPool : virtual public TranslatorOptionDataList {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorPdPool(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorPdPool();

    /// @brief Get and translate a pd-pool from YANG to JSON.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @return JSON representation of the pd-pool.
    /// @throw SysrepoError when sysrepo raises an error.
    /// @throw BadValue on pd-pool without well formed prefix.
    isc::data::ElementPtr getPdPool(const std::string& xpath);

    /// @brief Translate and set pd-pool from JSON to YANG.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @param elem The JSON element.
    void setPdPool(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getPdPool for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @return JSON representation of the pd-pool.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPdPoolIetf6(const std::string& xpath);

    /// @brief setPdPool for ietf-dhcpv6-server.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @param elem The JSON element.
    /// @throw BadValue on pd-pool without prefix or prefix length.
    void setPdPoolIetf6(const std::string& xpath,
                        isc::data::ConstElementPtr elem);

    /// @brief getPdPool for kea-dhcp6-server.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @return JSON representation of the pd-pool.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPdPoolKea(const std::string& xpath);

    /// @brief setPdPool for kea-dhcp6-server.
    ///
    /// @param xpath The xpath of the pd-pool.
    /// @param elem The JSON element.
    void setPdPoolKea(const std::string& xpath,
                      isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting a pd-pool list between
/// YANG and JSON.
///
/// Currently supports the following models:
/// - kea-dhcp6-server
/// - ietf-dhcpv6-server (partial support)
class TranslatorPdPools : virtual public TranslatorPdPool {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorPdPools(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorPdPools();

    /// @brief Get and translate pd-pools from YANG to JSON.
    ///
    /// @param xpath The xpath of the pd-pool list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPdPools(const std::string& xpath);

    /// @brief Translate and set pd-pools from JSON to YANG.
    ///
    /// @param xpath The xpath of the pd-pool list.
    /// @param elem The JSON element.
    void setPdPools(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getPdPools common part.
    ///
    /// @param xpath The xpath of the pd-pool list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getPdPoolsCommon(const std::string& xpath);

    /// @brief setPdPools using pool-id.
    ///
    /// @param xpath The xpath of the pd-pool list.
    /// @param elem The JSON element.
    void setPdPoolsId(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

    /// @brief setPdPools using prefix.
    ///
    /// @param xpath The xpath of the pd-pool list.
    /// @param elem The JSON element.
    /// @throw BadValue on pd-pool without prefix or prefix length.
    void setPdPoolsPrefix(const std::string& xpath,
                          isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_PD_POOL_H
