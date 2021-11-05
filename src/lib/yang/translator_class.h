// Copyright (C) 2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_CLASS_H
#define ISC_TRANSLATOR_CLASS_H 1

#include <yang/translator_option_data.h>
#include <yang/translator_option_def.h>
#include <list>

namespace isc {
namespace yang {

/// Client class translation between YANG and JSON
///
/// JSON syntax for all Kea servers with client class is:
/// @code
/// {
///     "name": <name>,
///     "test": <test expression>,
///     "only-if-required": <only if required flag>,
///     "option-data": <option data list>,
///     (DHCPv4 only)
///     "option-def": <option definition list>,
///     "next-server": <next server address>,
///     "server-hostname": <server hostname>,
///     "boot-file-name": <boot filename>,
///     "user-context": { <json map> },
///     "comment": <comment>
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46] is with the name as the list key:
/// @code
/// +--rw client-class* [name]
///    +--rw name                  string
///    +--rw test?                 string
///    +--rw only-if-required?     boolean
///    +--rw option-def* [code space]
///    +--rw option-data* [code space]
///    +--rw next-server?          inet:ipv4-address
///    +--rw server-hostname?      string
///    +--rw boot-file-name?       string
///    +--rw valid-lifetime?       uint32
///    +--rw min-valid-lifetime?   uint32
///    +--rw max-valid-lifetime?   uint32
///    +--rw user-context?         user-context
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "name": "foo",
///         "test": "''==''",
///         "only-if-required": false
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/client-class[name='foo'] (list instance)
///  /kea-dhcp6-server:config/client-class[name='foo']/name = foo
///  /kea-dhcp6-server:config/client-class[name='foo']/test = ''==''
///  /kea-dhcp6-server:config/client-class[name='foo']/only-if-required = false
/// @endcode

/// @brief A translator class for converting a client class between
/// YANG and JSON.
///
/// Currently supports only kea-dhcp[46]-server. Ietf-dhcpv6-server does
/// not define client class contents.
class TranslatorClass : virtual public TranslatorOptionDataList,
    virtual public TranslatorOptionDefList  {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorClass(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorClass();

    /// @brief Get and translate a client class from YANG to JSON.
    ///
    /// @param xpath The xpath of the class .
    /// @return JSON representation of the class .
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getClass(const std::string& xpath);

    /// @brief Translate and set client class from JSON to YANG.
    ///
    /// @param xpath The xpath of the client class.
    /// @param elem The JSON element.
    void setClass(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getClass JSON for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the class .
    /// @return JSON representation of the class .
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getClassKea(const std::string& xpath);

    /// @brief setClass for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the client class.
    /// @param elem The JSON element.
    void setClassKea(const std::string& xpath,
                     isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting a client class list between
/// YANG and JSON.
///
/// Currently supports only kea-dhcp[46]-server. Ietf-dhcpv6-server does
/// not define client class contents.
class TranslatorClasses : virtual public TranslatorClass {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorClasses(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorClasses();

    /// @brief Get and translate client classes from YANG to JSON.
    ///
    /// @param xpath The xpath of classes.
    /// @return JSON representation of classes.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getClasses(const std::string& xpath);

    /// @brief Translate and set client classes from JSON to YANG.
    ///
    /// @param xpath The xpath of classes.
    /// @param elem The JSON element.
    void setClasses(const std::string& xpath,
                    isc::data::ConstElementPtr elem);

protected:
    /// @brief getClasses JSON for kea-dhcp[46].
    ///
    /// @param xpath The xpath of classes.
    /// @return JSON representation of classes.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getClassesKea(const std::string& xpath);

    /// @brief setClasses for kea-dhcp[46].
    ///
    /// @param xpath The xpath of classes.
    /// @param elem The JSON element.
    /// @throw BadValue on client class without name.
    void setClassesKea(const std::string& xpath,
                       isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_CLASS_H
