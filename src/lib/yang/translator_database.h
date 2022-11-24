// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_DATABASE_H
#define ISC_TRANSLATOR_DATABASE_H 1

#include <yang/translator.h>

namespace isc {
namespace yang {

/// Database access translation between YANG and JSON
///
/// JSON syntax for all Kea servers with database access is:
/// @code
/// {
///     "type": <type>, /// required
///     "user": <user>,
///     "password": <password>,
///     "host": <host>,
///     "name": <name>,
///     "persist": <persist flag>,
///     "port": <port>,
///     "lfc-interval": <lfc interval>,
///     "readonly": <readonly flag>,
///     "trust-anchor": <trust anchor>,
///     "cert-file": <cert file>,
///     "key-file": <key file>,
///     "cipher-list": <cipher list>,
///     "connect-timeout": <connect timeout>,
///     "max-reconnect-tries": <maximum reconnect tries>,
///     "reconnect-wait-time": <reconnect wait time>,
///     "max-row-errors": <maximum row errors>,
///     "user-context": { <json map> },
///     "comment": <comment>
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46] is using database-type as the list key:
/// @code
/// +--rw database
///    +--rw database-type          string
///    +--rw user?                  string
///    +--rw password?              string
///    +--rw host?                  string
///    +--rw name?                  string
///    +--rw persist?               boolean
///    +--rw port?                  uint16
///    +--rw lfc-interval?          uint32
///    +--rw readonly?              boolean
///    +--rw trust-anchor?          string
///    +--rw cert-file?             string
///    +--rw key-file?              string
///    +--rw cipher-list?           string
///    +--rw connect-timeout?       uint32
///    +--rw max-reconnect-tries?   uint32
///    +--rw reconnect-wait-time?   uint32
///    +--rw max-row-errors?        uint32
///    +--rw on-fail?               string
///    +--rw user-context?          user-context
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "type": "mysql",
///         "name": "kea",
///         "user": "kea",
///         "password": "kea",
///         "host": "localhost",
///         "port": 3306
///     }
/// ]
/// @endcode
/// @code
/// /kea-dhcp6-server:config (container)
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql'] (list instance)
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/type = mysql
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/name = kea
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/user = kea
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/password = kea
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/host = localhost
/// /kea-dhcp6-server:config/
///    hosts-database[database-type='mysql']/port = 3306
/// @endcode

/// @brief A translator class for converting a database access parameters
/// between YANG and JSON.
///
/// Supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
class TranslatorDatabase : virtual public Translator {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorDatabase(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorDatabase() = default;

    /// @brief Translate a database access from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the control socket
    ///
    /// @return the JSON representation of the database
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabase(libyang::DataNode const& data_node);

    /// @brief Translate a database access from YANG to JSON.
    ///
    /// @note This is a computationally expensive operation that makes a lookup in the sysrepo
    /// datastore by calling Session::getData(). It should be used sparingly in production code,
    /// mainly to get an initial data node to work with. It may be used at will in unit tests.
    /// Use getDatabase(libyang::DataNode) as a scalable alternative.
    ///
    /// @param xpath The xpath of the database.
    ///
    /// @return JSON representation of the database.
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabaseFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set database access from JSON to YANG.
    ///
    /// Null elem argument removes the database entry.
    ///
    /// @param xpath The xpath of the database access.
    /// @param elem The JSON element.
    /// @param skip The skip type field flag.
    void setDatabase(const std::string& xpath,
                     isc::data::ConstElementPtr elem,
                     bool skip = false);

protected:
    /// @brief getDatabase JSON for kea-dhcp[46]-server models.
    ///
    /// @param data_node the YANG node representing the database configuration
    ///
    /// @return JSON representation of the database
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabaseKea(libyang::DataNode const& data_node);

    /// @brief setDatabase for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the database access.
    /// @param elem The JSON element.
    /// @param skip The skip type field flag.
    /// @throw BadValue on database without type,
    void setDatabaseKea(const std::string& xpath,
                        isc::data::ConstElementPtr elem,
                        bool skip);
};  // TranslatorDatabase

/// @brief A translator class for converting a database access list between
/// YANG and JSON.
///
/// Supports kea-dhcp[46]-server, does not exist in ietf-dhcpv6-server.
class TranslatorDatabases : virtual public TranslatorDatabase {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorDatabases(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorDatabases() = default;

    /// @brief Translate database accesses from YANG to JSON.
    ///
    /// @param data_node the YANG node representing the databases
    /// @param xpath the xpath of databases relative to {data_node}
    ///
    /// @return the JSON representation of the list of databases
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabases(libyang::DataNode const& data_node,
                                       std::string const& xpath);

    /// @brief Translate database accesses from YANG to JSON.
    ///
    /// @note This is a computationally expensive operation that makes a lookup in the sysrepo
    /// datastore by calling Session::getData(). It should be used sparingly in production code,
    /// mainly to get an initial data node to work with. It may be used at will in unit tests.
    /// Use getDatabases(libyang::DataNode, std::string) as a scalable alternative.
    ///
    /// @param xpath The xpath of databases including the list name.
    ///
    /// @return JSON representation of databases.
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabasesFromAbsoluteXpath(std::string const& xpath);

    /// @brief Translate and set database accesses from JSON to YANG.
    ///
    /// Null elem argument removes the database list.
    ///
    /// @param xpath The xpath of databases including the list name.
    /// @param elem The JSON element.
    void setDatabases(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

protected:
    /// @brief getDatabases JSON for kea-dhcp[46]-server models.
    ///
    /// @param data_node the YANG node representing the databases
    /// @param xpath the xpath of databases relative to {data_node}
    ///
    /// @return JSON representation of databases.
    ///
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getDatabasesKea(libyang::DataNode const& data_node,
                                          std::string const& xpath);

    /// @brief setDatabases for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of databases including the list name.
    /// @param elem The JSON element.
    ///
    /// @throw BadValue on database without type,
    void setDatabasesKea(const std::string& xpath,
                         isc::data::ConstElementPtr elem);
};  // TranslatorDatabases

}  // namespace yang
}  // namespace isc

#endif  // ISC_TRANSLATOR_DATABASE_H
