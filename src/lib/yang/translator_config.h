// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_CONFIG_H
#define ISC_TRANSLATOR_CONFIG_H 1

#include <yang/translator.h>
#include <yang/translator_control_socket.h>
#include <yang/translator_database.h>
#include <yang/translator_class.h>
#include <yang/translator_shared_network.h>
#include <yang/translator_logger.h>
#include <list>

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
///     "reservation-mode": <host reservation mode>,
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
/// +--rw valid-lifetime?                uint32
/// +--rw min-valid-lifetime?            uint32
/// +--rw max-valid-lifetime?            uint32
/// +--rw renew-timer?                   uint32
/// +--rw rebind-timer?                  uint32
/// +--rw calculate-tee-times?           boolean
/// +--rw t1-percent?                    decimal64
/// +--rw t2-percent?                    decimal64
/// +--rw decline-probation-period?      uint32
/// +--rw subnet4*
/// +--rw shared-network*
/// +--rw interfaces-config
///    +--rw interfaces*                 string
///    +--rw dhcp-socket-type?           enumeration
///    +--rw outbound-interface?         enumeration
///    +--rw re-detect?                  boolean
///    +--rw user-context?               string
/// +--rw lease-database!                <database>
/// +--rw hosts-database*
/// +--rw host-reservation-identifiers*  enumeration
/// +--rw client-class*
/// +--rw option-def*
/// +--rw option-data*
/// +--rw hook-library*
///    +--rw library                     string
///    +--rw parameters?                 string
/// +--rw expired-leases-processing      <expired-leases-processing>
/// +--rw dhcp4o6-port?                  uint16
/// +--rw control-socket!                <control-socket>
/// +--rw hostname-char-set?             string
/// +--rw hostname-char-replacement?     string
/// +--rw dhcp-ddns                      <dhcp-ddns>
/// +--rw echo-client-id?                boolean
/// +--rw match-client-id?               boolean
/// +--rw next-server?                   inet:ipv4-address
/// +--rw server-hostname?               string
/// +--rw boot-file-name?                string
/// +--rw authoritative?                 boolean
/// +--rw user-context?                  string
/// +--rw sanity-checks
///    +--rw lease-checks?               enumeration
/// +--rw reservation-mode?              enumeration
/// +--rw host*
/// +--rw config-control
///    +--rw config-fetch-wait-time?     uint32
///    +--rw config-database*
/// +--rw server-tag                     string
/// +--rw dhcp-queue-control             string
/// +--rw logger*
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
///             "socket-name": "/tmp/kea4-sock"
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
///     <socket-name>/tmp/kea4-sock</socket-name>
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
///     "reservation-mode": <host reservation mode>,
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
/// +--rw data-directory?                string
/// +--rw preferred-lifetime?            uint32
/// +--rw min-preferred-lifetime?        uint32
/// +--rw max-preferred-lifetime?        uint32
/// +--rw valid-lifetime?                uint32
/// +--rw min-valid-lifetime?            uint32
/// +--rw max-valid-lifetime?            uint32
/// +--rw renew-timer?                   uint32
/// +--rw rebind-timer?                  uint32
/// +--rw calculate-tee-times?           boolean
/// +--rw t1-percent?                    decimal64
/// +--rw t2-percent?                    decimal64
/// +--rw decline-probation-period?      uint32
/// +--rw subnet6*
/// +--rw shared-network*
/// +--rw interfaces-config
///    +--rw interfaces*                 string
///    +--rw re-detect?                  boolean
///    +--rw user-context?               string
/// +--rw lease-database!                <database>
/// +--rw hosts-database*
/// +--rw relay-supplied-options*        string
/// +--rw mac-sources*                   string
/// +--rw host-reservation-identifiers*  enumeration
/// +--rw client-class*
/// +--rw option-def*
/// +--rw option-data*
/// +--rw hook-library*
///    +--rw library                     string
///    +--rw parameters?                 string
/// +--rw expired-leases-processing      <expired-leases-processing>
/// +--rw server-id                      <server-id>
/// +--rw dhcp4o6-port?                  uint16
/// +--rw control-socket!                <control-socket>
/// +--rw hostname-char-set?             string
/// +--rw hostname-char-replacement?     string
/// +--rw dhcp-ddns                      <dhcp-ddns>
/// +--rw echo-client-id?                boolean
/// +--rw user-context?                  string
/// +--rw sanity-checks
///    +--rw lease-checks?               enumeration
/// +--rw reservation-mode?              enumeration
/// +--rw host*
/// +--rw config-control
///    +--rw config-fetch-wait-time?     uint32
///    +--rw config-database*
/// +--rw server-tag                     string
/// +--rw dhcp-queue-control             string
/// +--rw logger*
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
///             "socket-name": "/tmp/kea6-sock"
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
///     <socket-name>/tmp/kea6-sock</socket-name>
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
    TranslatorConfig(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorConfig();

    /// @brief Get and translate the whole DHCP server configuration
    /// from YANG to JSON.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getConfig();

    /// @brief Translate and sets the DHCP server configuration
    /// from JSON to YANG.
    ///
    /// Null elem argument removes the config containers.
    ///
    /// @param elem The JSON element.
    void setConfig(isc::data::ConstElementPtr elem);

protected:
    /// @brief getConfig for ietf-dhcpv6-server.
    ///
    /// This implementation is very preliminary. It handles network-ranges
    /// only partially and nothing else.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
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
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getConfigKea4();

    /// @brief getConfig for kea-dhcp6-server.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getConfigKea6();

    /// @brief getServer common part for kea-dhcp[46]-server:config.
    ///
    /// @param xpath The xpath of the server.
    /// @return JSON representation of the server.
    isc::data::ElementPtr getServerKeaDhcpCommon(const std::string& xpath);

    /// @brief getServer for kea-dhcp4-server:config.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getServerKeaDhcp4();

    /// @brief getServer for kea-dhcp6-server:config.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
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

    isc::data::ElementPtr getHook(const std::string& xpath);

    /// @brief Retrieves hooks configuration from sysrepo.
    ///
    /// @param xpath path to hooks configuration.
    /// @return ElementList with hooks configuration.
    isc::data::ElementPtr getHooksKea(const std::string& xpath);

    /// @brief Retrieves expired leases processing parameters from sysrepo.
    ///
    /// @param xpath path to expired leases configuration.
    /// @return ElementList with expired leases configuration.
    isc::data::ElementPtr getExpiredKea(const std::string& xpath);

    /// @brief Retrieves DDNS configuration from sysrepo
    ///
    /// @param xpath path to dhcp-ddns configuration.
    /// @return ElementList with dhcp-ddns configuration.
    isc::data::ElementPtr getDdnsKea(const std::string& xpath);

    /// @brief Retrieves configuration control from sysrepo.
    ///
    /// @param xpath path to configuration control.
    /// @return ElementMap with configuration control.
    isc::data::ElementPtr getConfigControlKea(const std::string& xpath);

    /// @brief setServer for kea-dhcp4-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp4(isc::data::ConstElementPtr elem);

    /// @brief setServer for kea-dhcp6-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp6(isc::data::ConstElementPtr elem);

    /// @brief Retrieves an item and stores in the specified storage.
    ///
    /// This will attempt to retrieve an item and, if exists, will
    /// store it in the storage.
    ///
    /// @param storage ElementMap (result will be stored here)
    /// @param xpath xpath location (data will be extracted from sysrepo)
    /// @param name name of the parameter
    void getParam(isc::data::ElementPtr& storage, const std::string& xpath,
                  const std::string& name);
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_CONFIG_H
