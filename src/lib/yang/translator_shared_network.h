// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_SHARED_NETWORK_H
#define ISC_TRANSLATOR_SHARED_NETWORK_H 1

#include <yang/translator.h>
#include <yang/translator_subnet.h>

namespace isc {
namespace yang {

/// Shared network translation between YANG and JSON
///
/// JSON syntax for kea-dhcp4 is:
/// @code
/// {
///     "name": <name>,
///     "subnet4": <subnet list>,
///     "valid-lifetime": <valid lifetime>,
///     "min-valid-lifetime": <minimum valid lifetime>,
///     "max-valid-lifetime": <maximum valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "calculate-tee-times": <calculate T1/T2 times>,
///     "t1-percent": <T1 percent>,
///     "t2-percent": <T2 percent>,
///     "option-data": [ <list of option data> ],
///     "interface": "<interface>",
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "reservation-mode": <host reservation mode>,
///     "relay": <relay ip address(es)>,
///     "match-client-id": <match client id flag>,
///     "next-server": "<next server>",
///     "server-hostname": "<server hostname>",
///     "boot-file-name": "<boot file name>",
///     "authoritative": <authoritative flag>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// JSON syntax for kea-dhcp6 is:
/// @code
/// {
///     "name": <name>,
///     "subnet6": <subnet list>,
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
///     "interface": "<interface>",
///     "interface-id": "<interface id>",
///     "rapid-commit": <rapid commit flag>,
///     "client-class": "<guard class name>",
///     "require-client-classes": [ <list of required class names> ],
///     "reservation-mode": <host reservation mode>,
///     "relay": <relay ip address(es)>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46]-server is with name as the list key:
/// @code
/// +--rw shared-network* [name]
///    +--rw name                            string
///    +--rw interface?                      string
///    +--rw renew-timer?                    uint32
///    +--rw rebind-timer?                   uint32
///    +--rw option-data* [code space]
///    +--rw reservation-mode?               host-reservation-mode
///    +--rw client-class?                   string
///    +--rw require-client-classes*         string
///    +--rw valid-lifetime?                 uint32
///    +--rw min-valid-lifetime?             uint32
///    +--rw max-valid-lifetime?             uint32
///    +--rw calculate-tee-times?            boolean
///    +--rw t1-percent?                     decimal64
///    +--rw t2-percent?                     decimal64
///    +--rw cache-max-age?                  uint32
///    +--rw cache-threshold?                decimal64
///    +--rw ddns-generated-prefix?          string
///    +--rw ddns-override-client-update?    boolean
///    +--rw ddns-override-no-update?        boolean
///    +--rw ddns-qualifying-suffix?         string
///    +--rw ddns-replace-client-name?       string
///    +--rw ddns-send-updates?              boolean
///    +--rw ddns-update-on-renew?           boolean
///    +--rw ddns-use-conflict-resolution?   boolean
///    +--rw store-extended-info?            boolean
///    +--rw hostname-char-replacement?      string
///    +--rw hostname-char-set?              string
///    +--rw reservations-global?            boolean
///    +--rw reservations-in-subnet?         boolean
///    +--rw reservations-out-of-pool?       boolean
///    +--rw user-context?                   user-context
///
/// DHCPv4 only:
///    +--rw subnet4*
///    +--rw match-client-id?          boolean
///    +--rw next-server?              inet:ipv4-address
///    +--rw server-hostname?          string
///    +--rw boot-file-name?           string
///    +--rw authoritative?            boolean
///    +--rw relay
///    |  +--rw ip-addresses*   inet:ipv4-address
///
/// DHCPv6 only:
///    +--rw subnet6*
///    +--rw preferred-lifetime?       uint32
///    +--rw min-preferred-lifetime?   uint32
///    +--rw max-preferred-lifetime?   uint32
///    +--rw interface-id?             string
///    +--rw rapid-commit?             boolean
///    +--rw relay
///    |  +--rw ip-addresses*   inet:ipv6-address
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "name": "foo",
///         "subnet6":
///             [
///                 {
///                     "subnet": "2001:db8::/48",
///                     "id": 123
///                 }
///             ]
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/shared-network[name='foo'] (list instance)
///  /kea-dhcp6-server:config/shared-network[name='foo']/name = foo
///  /kea-dhcp6-server:config/shared-network[name='foo']/
///     subnet6[id='123'] (list instance)
///  /kea-dhcp6-server:config/shared-network[name='foo']/
///     subnet6[id='123']/id = 123
///  /kea-dhcp6-server:config/shared-network[name='foo']/
///     subnet6[id='123']/subnet = 2001:db8::/48
/// @endcode

/// @brief A translator class for converting a shared network between
/// YANG and JSON.
///
/// Currently supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
class TranslatorSharedNetwork : virtual public TranslatorSubnets {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorSharedNetwork(sysrepo::Session session,
                            const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorSharedNetwork() = default;

    /// @brief Translate a shared network from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the shared network
    ///
    /// @return the JSON representation of the shared network
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSharedNetwork(libyang::DataNode const& data_node);

    /// @brief Translate a shared network from YANG to JSON.
    ///
    /// @param xpath The xpath of the shared network.
    ///
    /// @return JSON representation of the shared network.
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSharedNetworkFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set shared network from JSON to YANG.
    ///
    /// @param xpath The xpath of the shared network.
    /// @param elem The JSON element.
    void setSharedNetwork(const std::string& xpath,
                          isc::data::ConstElementPtr elem);

protected:
    /// @brief getSharedNetwork for kea-dhcp4-server and
    /// kea-dhcp6-server models
    ///
    /// @param data_node the YANG node representing the shared nework
    /// @param subsel The subnet list name (either "subnet4" or "subnet6").
    ///
    /// @return JSON representation of the shared network.
    isc::data::ElementPtr getSharedNetworkKea(libyang::DataNode const& data_node,
                                              const std::string& subsel);

    /// @brief setSharedNetwork for kea-dhcp4-server and
    /// kea-dhcp6-server models
    ///
    /// @param xpath The xpath of the shared network.
    /// @param elem The JSON element.
    /// @param subsel The subnet list name (either "subnet4" or "subnet6").
    void setSharedNetworkKea(const std::string& xpath,
                             isc::data::ConstElementPtr elem,
                             const std::string& subsel);
};  // TranslatorSharedNetwork

/// @brief A translator class for converting a shared network list between
/// YANG and JSON.
///
/// Currently supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
class TranslatorSharedNetworks : virtual public TranslatorSharedNetwork {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorSharedNetworks(sysrepo::Session session,
                             const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorSharedNetworks() = default;

    /// @brief Translate shared networks from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the list of shared networks
    ///
    /// @return the JSON representation of the list of shared networks
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSharedNetworks(libyang::DataNode const& data_node);

    /// @brief Translate shared networks from YANG to JSON.
    ///
    /// @param xpath The xpath of the shared network list.
    ///
    /// @return the JSON representation of the list of shared networks
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getSharedNetworksFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set shared networks from JSON to YANG.
    ///
    /// @param xpath The xpath of the shared network list.
    /// @param elem The JSON element.
    void setSharedNetworks(const std::string& xpath,
                           isc::data::ConstElementPtr elem);

protected:
    /// @brief setSharedNetworks for kea-dhcp4-server and
    /// kea-dhcp6-server
    ///
    /// @param xpath The xpath of the shared network list.
    /// @param elem The JSON element.
    /// @throw BadValue on a shared network without name.
    void setSharedNetworksKea(const std::string& xpath,
                              isc::data::ConstElementPtr elem);
};  // TranslatorSharedNetworks

}  // namespace yang
}  // namespace isc

#endif  // ISC_TRANSLATOR_SHARED_NETWORK_H
