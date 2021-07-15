// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_OPTION_DEF_H
#define ISC_TRANSLATOR_OPTION_DEF_H 1

#include <yang/translator.h>
#include <list>

namespace isc {
namespace yang {

/// @brief Option definition translation between YANG and JSON
///
/// JSON syntax for Kea DHCP servers is:
/// @code
/// {
///     "code": <code>,
///     "name": <name>,
///     "space": <space>,
///     "type": <type>,
///     "array": <array flag>,
///     "encapsulate": <encapsulated space>,
///     "record-types": <record types>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46] with code and space as keys is:
/// @code
///    +--rw name           string
///    +--rw code           uint8 / uint16
///    +--rw type           string
///    +--rw record-types?  string
///    +--rw space          string
///    +--rw encapsulate?   string
///    +--rw array?         boolean
///    +--rw user-context?  string
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "code": 100,
///         "name": "foo",
///         "space": "isc",
///         "type": "string",
///         "array": false
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc'] (list instance)
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc']/code = 100
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc']/space = isc
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc']/name = foo
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc']/type = string
///  /kea-dhcp6-server:config/
///     option-def[code='100'][space='isc']/array = false
/// @endcode

/// @brief A translator class for converting an option definition between
/// YANG and JSON.
///
/// Currently supports kea-dhcp[46]-server models.
/// @todo: Support for ietf-dhcpv6-server model.
class TranslatorOptionDef : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionDef(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionDef();

    /// @brief Get and translate an option definition from YANG to JSON.
    ///
    /// @param xpath The xpath of the option definition.
    /// @return JSON representation of the option definition.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOptionDef(const std::string& xpath);

    /// @brief Translate and set option definition from JSON to YANG.
    ///
    /// @param xpath The xpath of the option definition..
    /// @param elem The JSON element.
    void setOptionDef(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

protected:
    /// @brief getOptionDef implementation specific to kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the option definition.
    /// @return JSON representation of the option definition.
    /// @throw SysrepoError when sysrepo raises an error.
    /// @throw BadValue on option definition without name or type.
    isc::data::ElementPtr getOptionDefKea(const std::string& xpath);

    /// @brief setOptionDef implementation specific to kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the option definition.
    /// @param elem The JSON element.
    /// @throw BadValue on option definition without name or type.
    void setOptionDefKea(const std::string& xpath,
                         isc::data::ConstElementPtr elem);
};

// @brief A translator class for converting an option definition list
// between YANG and JSON.
//
/// Currently supports kea-dhcp[46]-server models.
/// @todo: Support for ietf-dhcpv6-server model.
class TranslatorOptionDefList : virtual public TranslatorOptionDef {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionDefList(sysrepo::S_Session session,
                            const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionDefList();

    /// @brief Get and translate option definition list from YANG to JSON.
    ///
    /// @param xpath The xpath of the option definition list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getOptionDefList(const std::string& xpath);

    /// @brief Translate and set option definition list from JSON to YANG.
    ///
    /// @param xpath The xpath of the option definition list.
    /// @param elem The JSON element.
    void setOptionDefList(const std::string& xpath,
                          isc::data::ConstElementPtr elem);

protected:
    /// @brief getOptionDefList implementation specific to kea-dhcp[46]-server
    ///        models.
    ///
    /// @param xpath The xpath of the option definition list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getOptionDefListKea(const std::string& xpath);

    /// @brief setOptionDefList implementation specific to kea-dhcp[46]-server
    ///        models.
    ///
    /// @param xpath The xpath of the option definition list.
    /// @param elem The JSON element.
    /// @throw BadValue on option definition without code or space.
    void setOptionDefListKea(const std::string& xpath,
                             isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_OPTION_DEF_H
