// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_DATABASE_H
#define ISC_TRANSLATOR_DATABASE_H 1

#include <yang/translator.h>
#include <list>

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
///     "connect-timeout": <connect timeout>,
///     "contact-points": <contact points>,
///     "keyspace": <keyspace>,
///     "max-reconnect-tries": <maximum reconnect tries>,
///     "reconnect-wait-time": <reconnect wait time>,
///     "request-timeout": <request timeout>,
///     "tcp-keepalive": <TCP keepalive>,
///     "tcp-nodelay": <TCP nodelay flag>,
///     "consistency": <consistency level>,
///     "serial-consistency": <serial consistency level>,
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
///    +--rw connect-timeout?       uint32
///    +--rw contact-points?        string
///    +--rw keyspace?              string
///    +--rw max-reconnect-tries?   uint32
///    +--rw reconnect-wait-time?   uint32
///    +--rw request-timeout?       uint32
///    +--rw tcp-keepalive?         uint32
///    +--rw tcp-nodelay?           boolean
///    +--rw consistency?           string
///    +--rw serial-consistency?    string
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
class TranslatorDatabase : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorDatabase(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorDatabase();

    /// @brief Get and translate a database access from YANG to JSON.
    ///
    /// @param xpath The xpath of the database.
    /// @return JSON representation of the database.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getDatabase(const std::string& xpath);

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
    /// @param xpath The xpath of the database.
    /// @return JSON representation of the database or null if none.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getDatabaseKea(const std::string& xpath);

    /// @brief setDatabase for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the database access.
    /// @param elem The JSON element.
    /// @param skip The skip type field flag.
    /// @throw BadValue on database without type,
    void setDatabaseKea(const std::string& xpath,
                        isc::data::ConstElementPtr elem,
                        bool skip);
};

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
    TranslatorDatabases(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorDatabases();

    /// @brief Get and translate database accesses from YANG to JSON.
    ///
    /// @param xpath The xpath of databases including the list name.
    /// @return JSON representation of databases.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getDatabases(const std::string& xpath);

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
    /// @param xpath The xpath of databases including the list name.
    /// @return JSON representation of  databases.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getDatabasesKea(const std::string& xpath);

    /// @brief setDatabases for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of databases including the list name.
    /// @param elem The JSON element.
    /// @throw BadValue on database without type,
    void setDatabasesKea(const std::string& xpath,
                         isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_DATABASE_H
