// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

// @brief A translator class for converting a database access between
// YANG and JSON.
//
// Supports kea-dhcp[46]-server, not yet ietf-dhcpv6-server.
//
// JSON syntax for all Kea servers with database access is:
// @code
// {
//     "type": <type>, // required
//     "user": <user>,
//     "password": <password>,
//     "host": <host>,
//     "name": <name>,
//     "persist": <persist flag>,
//     "port": <port>,
//     "lfc-interval": <lfc interval>,
//     "readonly": <readonly flag>,
//     "connect-timeout": <connect timeout>,
//     "contact-points": <contact points>,
//     "keyspace": <keyspace>,
//     "max-reconnect-tries": <maximum reconnect tries>,
//     "reconnect-wait-time": <reconnect wait time>,
//     "request-timeout": <request timeout>,
//     "tcp-keepalive": <TCP keepalive>,
//     "tcp-nodelay": <TCP nodelay flag>,
//     "user-context": { <json map> },
//     "comment": <comment>
// }
// @endcode
//
// YANG syntax for kea-dhcp[46] is:
// @code
//  +--rw database                container
//    |
//    +--rw datanase=type?        string
//    +--rw user?                 string
//    +--rw password?             string
//    +--rw host?                 string
//    +--rw name?                 string
//    +--rw persist?              boolean
//    +--rw port?                 uint16
//    +--rw lfc-interval?         uint32
//    +--rw readonly?             boolean
//    +--rw connect-timeout?      uint32
//    +--rw contact-points?       string
//    +--rw keyspace?             string
//    +--rw max-reconnect-tries?  uint32
//    +--rw reconnect-wait-time?  uint32
//    +--rw request-timeout?      uint32
//    +--rw tcp-keepalive?        uint32
//    +--rw tcp-nodelay?          boolean
//    +--rw user-context?         string
// @endcode
//
class TranslatorDatabase : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorDatabase(S_Session session, const std::string& model);

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
    /// @brief getDatabase JSON for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the database.
    /// @return JSON representation of the database.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getDatabaseKea(const std::string& xpath);

    /// @brief setDatabase for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the database access.
    /// @param elem The JSON element.
    /// @param skip The skip type field flag.
    /// @throw BadValue on database without tyoe,
    void setDatabaseKea(const std::string& xpath,
                        isc::data::ConstElementPtr elem,
                        bool skip);

    /// @brief The model.
    std::string model_;
};

// @brief A translator class for converting a database access list between
// YANG and JSON.
//
// Supports kea-dhcp[46]-server, does not exist in ietf-dhcpv6-server.
//
// YANG list key is the database-type.
//
class TranslatorDatabases : virtual public TranslatorDatabase {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorDatabases(S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorDatabases();

    /// @brief Get and translate database accesses from YANG to JSON.
    ///
    /// @param xpath The xpath of databases.
    /// @return JSON representation of databases.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getDatabases(const std::string& xpath);

    /// @brief Translate and set database accesses from JSON to YANG.
    ///
    /// Null elem argument removes the database list.
    ///
    /// @param xpath The xpath of databases.
    /// @param elem The JSON element.
    void setDatabases(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

protected:
    /// @brief getDatabases JSON for kea-dhcp[46].
    ///
    /// @param xpath The xpath of databases.
    /// @return JSON representation of  databases.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getDatabasesKea(const std::string& xpath);

    /// @brief setDatabases for kea-dhcp[46].
    ///
    /// @param xpath The xpath of databases.
    /// @param elem The JSON element.
    /// @throw BadValue on database without tyoe,
    void setDatabasesKea(const std::string& xpath,
                         isc::data::ConstElementPtr elem);

    /// @brief The model.
    std::string model_;
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_DATABASE_H
