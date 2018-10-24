// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

/// Configuration translation between YANG and JSON
///
/// JSON syntax for kea-dhcp6-server is:
/// @code
/// "Dhcp6": {
///     "preferred-lifetime": <preferred lifetime>,
///     "valid-lifetime": <valid lifetime>,
///     "renew-timer": <renew timer>,
///     "rebind-timer": <rebind timer>,
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
///     <dhcp-ddns>,
///     <user-context>,
///     <comment>
/// },
/// "Logging": <logging>
/// @endcode
///
/// @todo: add kea-dhcp4 syntax and expand logging.
///
/// YANG syntax for kea-dhcp6-server:config is:
/// @code
/// +--rw preferred-lifetime?            uint32
/// +--rw valid-lifetime?                uint32
/// +--rw renew-timer?                   uint32
/// +--rw rebind-timer?                  uint32
/// +--rw decline-probation-period?      uint32
/// +--rw subnet6                        subnet6*
/// +--rw shared-networks                shared-network*
/// +--rw interfaces-config
///    +--rw interfaces*                 string
///    +--rw re-detect?                  boolean
///    +--rw user-context?               string
/// +--rw lease-database!                <database>
/// +--rw hosts-databases                hosts-database*
/// +--rw relay-supplied-options*        string
/// +--rw mac-sources*                   string
/// +--rw host-reservation-identifiers*  enumeration
/// +--rw client-classes                 client-class*
/// +--rw option-def-list                option-def*
/// +--rw option-data-list               option-data*
/// +--rw hook-library*
///    +--rw library                     string
///    +--rw parameters?                 string
/// +--rw expired-leases-processing      <expired-leases-processing>
/// +--rw server-id                      <server-id>
/// +--rw dhcp4o6-port?                  uint16
/// +--rw control-socket!                <control-socket>
/// +--rw dhcp-ddns                      <dhcp-ddns>
/// +--rw echo-client-id?                boolean
/// +--rw user-context?                  string
/// +--rw sanity-checks
///    +--rw lease-checks?               enumeration
/// @endcode
///
/// YANG syntax for kea-dhcp4-server:config is:
/// @code
/// +--rw valid-lifetime?                uint32
/// +--rw renew-timer?                   uint32
/// +--rw rebind-timer?                  uint32
/// +--rw decline-probation-period?      uint32
/// +--rw subnet4                        subnet4*
/// +--rw shared-networks                shared-network*
/// +--rw interfaces-config
///    +--rw interfaces*                 string
///    +--rw dhcp-socket-type?           enumeration
///    +--rw outbound-interface?         enumeration
///    +--rw re-detect?                  boolean
///    +--rw user-context?               string
/// +--rw lease-database!                <database>
/// +--rw hosts-databases                hosts-database*
/// +--rw host-reservation-identifiers*  enumeration
/// +--rw client-classes                 client-class*
/// +--rw option-def-list                option-def*
/// +--rw option-data-list               option-data*
/// +--rw hook-library*
///    +--rw library                     string
///    +--rw parameters?                 string
/// +--rw expired-leases-processing      <expired-leases-processing>
/// +--rw dhcp4o6-port?                  uint16
/// +--rw control-socket!                <control-socket>
/// +--rw dhcp-ddns                      <dhcp-ddns>
/// +--rw echo-client-id?                boolean
/// +--rw match-client-id?               boolean
/// +--rw next-server?                   inet:ipv4-address
/// +--rw server-hostname?               string
/// +--rw boot-file-name?                string
/// +--rw user-context?                  string
/// +--rw sanity-checks
///    +--rw lease-checks?               enumeration
/// @endcode
///
/// YANG syntax for kea-*:logging is:
/// @code
/// +--rw logging
///    +--rw loggers
/// @endcode
///
/// @todo add example
///
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
///
/// @brief A translator class for converting the config between
/// YANG and JSON.
///
/// Currently supports kea-dhcp[46]-server, kea-logging and partially
/// ietf-dhcpv6-server.
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
    TranslatorConfig(S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorConfig();

    /// @brief Get and translate a pool from YANG to JSON.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getConfig();

    /// @brief Translate and set config from JSON to YANG.
    ///
    /// Null elem argument removes the config containers.
    ///
    /// @param elem The JSON element.
    void setConfig(isc::data::ConstElementPtr elem);

protected:
    /// @brief getConfig for ietf-dhcpv6-server.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getConfigIetf6();

    /// @brief delConfig for ietf-dhcpv6-server.
    void delConfigIetf6();

    /// @brief setConfig for ietf-dhcpv6-server.
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

    /// @brief getServer common part for kea-dhcp[46]:config.
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

    /// @brief getServer for kea-*:logging.
    ///
    /// @return JSON representation of the config.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getServerKeaLogging();

    /// @brief delConfig for kea-dhcp[46]-server.
    void delConfigKea();

    /// @brief setConfig for kea-dhcp4-server.
    ///
    /// @param elem The JSON element.
    void setConfigKea4(isc::data::ConstElementPtr elem);

    /// @brief setConfig for kea-dhcp6-server.
    ///
    /// @param elem The JSON element.
    void setConfigKea6(isc::data::ConstElementPtr elem);

    /// @brief setServer common part for kea-dhcp[46]:config.
    ///
    /// @param xpath The xpath of the server.
    /// @param elem The JSON element.
    void setServerKeaDhcpCommon(const std::string& xpath,
                                isc::data::ConstElementPtr elem);

    /// @brief setServer for kea-dhcp4-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp4(isc::data::ConstElementPtr elem);

    /// @brief setServer for kea-dhcp6-server:config.
    ///
    /// @param elem The JSON element.
    void setServerKeaDhcp6(isc::data::ConstElementPtr elem);

    /// @brief setServer for kea-*:logging.
    ///
    /// @param elem The JSON element.
    void setServerKeaLogging(isc::data::ConstElementPtr elem);

    /// @brief The model.
    std::string model_;
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_CONFIG_H
