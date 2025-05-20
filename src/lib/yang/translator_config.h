// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_CONFIG_H
#define ISC_TRANSLATOR_CONFIG_H 1

#include <yang/translator.h>
#include <yang/translator_class.h>
#include <yang/translator_control_socket.h>
#include <yang/translator_database.h>
#include <yang/translator_logger.h>
#include <yang/translator_shared_network.h>

namespace isc {
namespace yang {

/// @brief DHCP configuration translation between YANG and JSON
///
/// This translator supports kea-dhcp4-server, kea-dhcp6-server and
/// partially ietf-dhcpv6-server.

/// JSON syntax for kea-dhcp4 is:
/// @code
/// "Dhcp4": {
///     "valid-lifetime": <valid lifetime>,
///     "min-valid-lifetime": <minimum valid lifetime>,
///     "max-valid-lifetime": <maximum valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
///     "calculate-tee-times": <calculate T1/T2 times>,
///     "t1-percent": <T1 percent>,
///     "t2-percent": <T2 percent>,
///     "decline-probation-period": <decline probation period>,
///     "subnet4": [ <list of subnet4> ],
///     <shared-networks>,
///     "interfaces-config": {
///         "interfaces" [ <list of interface names / specs> ],
///         ...
///     },
///     <databases>,
///     <host-reservation-identifiers>,
///     <client-classes>,
///     <option-def>,
///     <option-data>,
///     <hooks-libraries>,
///     <expired-leases-processing>,
///     <dhcp4o6-port>,
///     <control-socket>,
///     <hostname-char-set": <hostname character set>,
///     <hostname-char-replacement": <hostname character replacement>,
///     <dhcp-ddns>,
///     "echo-client-id": <echo client id flag>,
///     "match-client-id": <match client id flag>,
///     "next-server": <next server address>,
///     "server-hostname": <server hostname>,
///     "boot-file-name": <boot file name>,
///     "authoritative": <authoritative flag>,
///     <user-context>,
///     <comment>,
///     "sanity-checks": { <sanity checks> },
///     "reservations": [ <list of host reservations> ],
///     <config-control>,
///     "server-tag": <server tag>,
///     "dhcp-queue-control": { <DHCP queue control> },
///     "loggers": [ <list of loggers> ]
/// },
/// @endcode
///
/// YANG syntax for kea-dhcp4-server:config is:
/// @code
/// +--rw valid-lifetime?                   uint32
/// +--rw min-valid-lifetime?               uint32
/// +--rw max-valid-lifetime?               uint32
/// +--rw renew-timer?                      uint32
/// +--rw rebind-timer?                     uint32
/// +--rw calculate-tee-times?              boolean
/// +--rw t1-percent?                       decimal64
/// +--rw t2-percent?                       decimal64
/// +--rw decline-probation-period?         uint32
/// +--rw subnet4* [id]
/// +--rw shared-network* [name]
/// +--rw interfaces-config
/// +--rw lease-database!
/// +--rw hosts-database* [database-type]
/// +--rw host-reservation-identifiers*     host-identifier-type
/// +--rw client-class* [name]
/// +--rw option-def* [code space]
/// +--rw option-data* [code space]
/// +--rw hook-library* [library]
/// +--rw expired-leases-processing
/// +--rw dhcp4o6-port?                     uint16
/// +--rw control-socket!
/// +--rw hostname-char-set?                string
/// +--rw hostname-char-replacement?        string
/// +--rw dhcp-ddns
/// +--rw echo-client-id?                   boolean
/// +--rw match-client-id?                  boolean
/// +--rw next-server?                      inet:ipv4-address
/// +--rw server-hostname?                  string
/// +--rw boot-file-name?                   string
/// +--rw authoritative?                    boolean
/// +--rw user-context?                     user-context
/// +--rw sanity-checks
/// +--rw host* [identifier-type identifier]
/// +--rw config-control
/// +--rw server-tag?                       string
/// +--rw dhcp-queue-control?               string
/// +--rw logger* [name]
/// +--rw cache-max-age?                    uint32
/// +--rw cache-threshold?                  decimal64
/// +--rw compatibility
/// +--rw ddns-generated-prefix?            string
/// +--rw ddns-override-client-update?      boolean
/// +--rw ddns-override-no-update?          boolean
/// +--rw ddns-qualifying-suffix?           string
/// +--rw ddns-replace-client-name?         string
/// +--rw ddns-send-updates?                boolean
/// +--rw ddns-update-on-renew?             boolean
/// +--rw ddns-use-conflict-resolution?     boolean
/// +--rw ddns-conflict-resolution-mode?    conflict-resolution-mode
/// +--rw ip-reservations-unique?           boolean
/// +--rw early-global-reservations-lookup? boolean
/// +--rw reservations-lookup-first?        boolean
/// +--rw multi-threading
/// +--rw parked-packet-limit?              uint32
/// +--rw reservations-global?              boolean
/// +--rw reservations-in-subnet?           boolean
/// +--rw reservations-out-of-pool?         boolean
/// +--rw statistic-default-sample-age?     uint32
/// +--rw statistic-default-sample-count?   uint32
/// +--rw store-extended-info?              boolean
/// @endcode
///
/// Example of kea-dhcp6 simple configuration:
/// @code
/// {
///     "Dhcp4": {
///         "interfaces-config":
///     {
///         "interfaces": [ "eth1" ]
///     },
///         "control-socket": {
///             "socket-type": "unix",
///             "socket-name": "kea4-sock"
///         },
///     "subnet4":
///     [
///         {
///             "subnet": "10.0.35.0/24",
///             "pools":
///             [
///                 {
///                     "pool": "10.0.35.64/27"
///                 }
///             ]
///         }
///     ]
///     }
/// }
///
/// @endcode
///
/// The same configuration wrote into YANG datastore using @c setConfig()
/// with the kea-dhcp4-model and exported to XML format:
/// @code
/// <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp4-server">
///   <subnet4>
///     <id>1</id>
///     <pool>
///       <start-address>10.0.35.64</start-address>
///       <end-address>10.0.35.95</end-address>
///       <prefix>10.0.35.64/27</prefix>
///     </pool>
///     <subnet>10.0.35.0/24</subnet>
///   </subnet4>
///   <interfaces-config>
///     <interfaces>eth1</interfaces>
///   </interfaces-config>
///   <control-socket>
///     <socket-name>kea4-sock</socket-name>
///     <socket-type>unix</socket-type>
///   </control-socket>
/// </config>
/// @endcode

/// JSON syntax for kea-dhcp6 is:
/// @code
/// "Dhcp6": {
///     "data-directory": <data directory>,
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
///     "decline-probation-period": <decline probation period>,
///     "subnet6": [ <list of subnet6> ],
///     <shared-networks>,
///     "interfaces-config": {
///         "interfaces" [ <list of interface names / specs> ],
///         ...
///     },
///     <databases>,
///     <mac-sources>,
///     <relay-supplied-options>,
///     <host-reservation-identifiers>,
///     <client-classes>,
///     <option-def>,
///     <option-data>,
///     <hooks-libraries>,
///     <expired-leases-processing>,
///     <server-id>,
///     <dhcp4o6-port>,
///     <control-socket>,
///     <hostname-char-set": <hostname character set>,
///     <hostname-char-replacement": <hostname character replacement>,
///     <dhcp-ddns>,
///     <user-context>,
///     <comment>
///     "sanity-checks": { <sanity checks> },
///     "reservations": [ <list of host reservations> ],
///     <config-control>,
///     "server-tag": <server tag>,
///     "dhcp-queue-control": { <DHCP queue control> },
///     "loggers": [ <list of loggers> ]
/// },
/// @endcode
///
/// YANG syntax for kea-dhcp6-server:config is:
/// @code
/// +--rw data-directory?                   string
/// +--rw preferred-lifetime?               uint32
/// +--rw min-preferred-lifetime?           uint32
/// +--rw max-preferred-lifetime?           uint32
/// +--rw valid-lifetime?                   uint32
/// +--rw min-valid-lifetime?               uint32
/// +--rw max-valid-lifetime?               uint32
/// +--rw renew-timer?                      uint32
/// +--rw rebind-timer?                     uint32
/// +--rw calculate-tee-times?              boolean
/// +--rw t1-percent?                       decimal64
/// +--rw t2-percent?                       decimal64
/// +--rw decline-probation-period?         uint32
/// +--rw subnet6* [id]
/// +--rw shared-network* [name]
/// +--rw interfaces-config
/// +--rw lease-database!
/// +--rw hosts-database* [database-type]
/// +--rw relay-supplied-options*           string
/// +--rw mac-sources*                      string
/// +--rw host-reservation-identifiers*     host-identifier-type
/// +--rw client-class* [name]
/// +--rw option-def* [code space]
/// +--rw option-data* [code space]
/// +--rw hook-library* [library]
/// +--rw expired-leases-processing
/// +--rw server-id!
/// +--rw dhcp4o6-port?                     uint16
/// +--rw control-socket!
/// +--rw hostname-char-set?                string
/// +--rw hostname-char-replacement?        string
/// +--rw dhcp-ddns
/// +--rw user-context?                     user-context
/// +--rw sanity-checks
/// +--rw host* [identifier-type identifier]
/// +--rw config-control
/// +--rw server-tag?                       string
/// +--rw dhcp-queue-control?               string
/// +--rw logger* [name]
/// +--rw cache-max-age?                    uint32
/// +--rw cache-threshold?                  decimal64
/// +--rw compatibility
/// +--rw ddns-generated-prefix?            string
/// +--rw ddns-override-client-update?      boolean
/// +--rw ddns-override-no-update?          boolean
/// +--rw ddns-qualifying-suffix?           string
/// +--rw ddns-replace-client-name?         string
/// +--rw ddns-send-updates?                boolean
/// +--rw ddns-update-on-renew?             boolean
/// +--rw ddns-use-conflict-resolution?     boolean
/// +--rw ddns-conflict-resolution-mode?    conflict-resolution-mode
/// +--rw ip-reservations-unique?           boolean
/// +--rw early-global-reservations-lookup? boolean
/// +--rw reservations-lookup-first?        boolean
/// +--rw multi-threading
/// +--rw parked-packet-limit?              uint32
/// +--rw reservations-global?              boolean
/// +--rw reservations-in-subnet?           boolean
/// +--rw reservations-out-of-pool?         boolean
/// +--rw statistic-default-sample-age?     uint32
/// +--rw statistic-default-sample-count?   uint32
/// +--rw store-extended-info?              boolean
/// @endcode
///
/// Example of kea-dhcp6 simple configuration:
/// @code
/// {
///     "Dhcp6": {
///         "interfaces-config":
///     {
///         "interfaces": [ "eth1" ]
///     },
///         "control-socket": {
///             "socket-type": "unix",
///             "socket-name": "kea6-sock"
///         },
///     "subnet6":
///     [
///         {
///             "subnet": "2001:db8::/64",
///             "pools":
///             [
///                 {
///                     "pool": "2001:db8::1:0/112"
///                 }
///             ]
///         }
///     ]
///     }
/// }
/// @endcode
///
/// The same configuration wrote into YANG datastore using @c setConfig()
/// with the kea-dhcp6-model and exported to XML format:
/// @code
/// <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
///   <subnet6>
///     <id>1</id>
///     <pool>
///       <start-address>2001:db8::1:0</start-address>
///       <end-address>2001:db8::1:ffff</end-address>
///       <prefix>2001:db8::1:0/112</prefix>
///     </pool>
///     <subnet>2001:db8::/64</subnet>
///   </subnet6>
///   <interfaces-config>
///     <interfaces>eth1</interfaces>
///   </interfaces-config>
///   <control-socket>
///     <socket-name>kea6-sock</socket-name>
///     <socket-type>unix</socket-type>
///   </control-socket>
/// </config>
/// @endcode

/// Inheritance graph between translators is:
///
///        +-----------------------------------------+
///        |                                         |
///        +------------------------------+          |
///        |                              |          |
///        +----------+-------------------+----------+
///        |          |                   |          |
///        |          |         +---------+----------+
///        |          |         |         |          |
/// config +- shared  +- subnet +- pool --+- option -+ basic
///        |  network    (list) |  (list) |  data    |
///        |  (list)            |         |  (list)  |
///        |                    |         |          |
///        |                    +- pd ----+          |
///        |                    |  pool   |          |
///        |                    |  (list) |          |
///        |                    |         |          |
///        +--------------------+- host --+          |
///        |                       (liat) |          |
///        |                              |          |
///        |         +--------------------+----------+
///        |         |                               |
///        +- class -+- option ----------------------+
///        |  (list) |  def                          |
///        |         |  (list)                       |
///        +---------+                               |
///        |                                         |
///        + control --------------------------------+
///        | socket                                  |
///        |                                         |
///        +------------+                            |
///        |            |                            |
///        +- database -+- database -----------------+
///        |  list                                   |
///        |                                         |
///        +- logger --------------------------------+
///           (list)
///
///  'XXX (list)' stands for 'XXX list --- XXX' which is a common motif
///  (only database shows direct dependencies on both the list and the element)

/// @brief A translator class for converting the config between YANG and JSON.
///
/// Currently supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
/// - ietf-dhcpv6-server (partial)
class TranslatorConfig : virtual public TranslatorControlSocket,
    virtual public TranslatorDatabases,
    virtual public TranslatorClasses,
    virtual public TranslatorSharedNetworks,
    virtual public TranslatorLoggers {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorConfig(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorConfig() = default;

    /// @brief Translate the whole DHCP server configuration from YANG to JSON.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getConfig();

    /// @brief Translate and set the DHCP server configuration from JSON to YANG.
    ///
    /// Null elem argument removes the config containers.
    ///
    /// @param elem The JSON element.
    void setConfig(isc::data::ElementPtr elem);

protected:
    /// @brief getConfig for ietf-dhcpv6-server.
    ///
    /// This implementation is very preliminary. It handles network-ranges
    /// only partially and nothing else.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getConfigIetf6();

    /// @brief delConfig for ietf-dhcpv6-server.
    void delConfigIetf6();

    /// @brief setConfig for ietf-dhcpv6-server.
    ///
    /// This implementation is very preliminary. It handles network-ranges
    /// only partially and nothing else.
    ///
    /// @param elem The JSON element.
    /// @throw BadValue on config without Dhcp6.
    void setConfigIetf6(isc::data::ConstElementPtr elem);

    /// @brief getConfig for kea-dhcp4-server.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getConfigKea4();

    /// @brief getConfig for kea-dhcp6-server.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getConfigKea6();

    /// @brief getServer common part for kea-dhcp[46]-server:config.
    ///
    /// @param data_node the YANG node representing the server configuration
    ///
    /// @return JSON representation of the server.
    isc::data::ElementPtr getServerKeaDhcpCommon(libyang::DataNode const& data_node);

    /// @brief getServer for kea-dhcp4-server:config.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getServerKeaDhcp4();

    /// @brief getServer for kea-dhcp6-server:config.
    ///
    /// @return JSON representation of the config.
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getServerKeaDhcp6();

    /// @brief delConfig for kea-dhcp[46]-server.
    void delConfigKea();

    /// @brief setConfig for kea-dhcp[46]-server.
    ///
    /// @param elem The JSON element.
    void setConfigKea4(isc::data::ConstElementPtr elem);

    /// @brief setConfig for kea-dhcp6-server.
    ///
    /// @param elem The JSON element.
    void setConfigKea6(isc::data::ConstElementPtr elem);

    /// @brief setServer common part for kea-dhcp[46]-server:config.
    ///
    /// @param xpath The xpath of the server.
    /// @param elem The JSON element.
    void setServerKeaDhcpCommon(const std::string& xpath,
                                isc::data::ConstElementPtr elem);

    isc::data::ElementPtr getHook(libyang::DataNode const& data_node);

    /// @brief Retrieves hooks configuration from sysrepo.
    ///
    /// @param data_node the YANG node representing the hook libraries
    ///
    /// @return ElementList with hooks configuration.
    isc::data::ElementPtr getHooksKea(libyang::DataNode const& data_node);

    /// @brief Retrieves expired leases processing parameters from sysrepo.
    ///
    /// @param data_node the YANG node representing the configuration for expired lease processing
    ///
    /// @return ElementList with expired leases configuration.
    isc::data::ElementPtr getExpiredKea(libyang::DataNode const& data_node);

    /// @brief Retrieves DDNS configuration from sysrepo
    ///
    /// @param data_node the YANG node representing dhcp-ddns configuration
    ///
    /// @return ElementList with dhcp-ddns configuration.
    isc::data::ElementPtr getDdnsKea(libyang::DataNode const& data_node);

    /// @brief Retrieves configuration control from sysrepo.
    ///
    /// @param data_node the YANG node representing configuration control
    ///
    /// @return ElementMap with configuration control.
    isc::data::ElementPtr getConfigControlKea(libyang::DataNode const& data_node);

    /// @brief Retrieves interfaces configuration from sysrepo.
    ///
    /// @param data_node the YANG node representing the interfaces configuration
    ///
    /// @return ElementMap with configuration control.
    isc::data::ElementPtr getInterfacesKea(libyang::DataNode const& data_node);

    /// @brief setServer for kea-dhcp4-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp4(isc::data::ConstElementPtr elem);

    /// @brief setServer for kea-dhcp6-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp6(isc::data::ConstElementPtr elem);
};  // TranslatorConfig

}  // namespace yang
}  // namespace isc

#endif  // ISC_TRANSLATOR_CONFIG_H
