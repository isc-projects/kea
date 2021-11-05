// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_OPTION_DATA_H
#define ISC_TRANSLATOR_OPTION_DATA_H 1

#include <yang/translator.h>
#include <list>

namespace isc {
namespace yang {

/// Option data translation between YANG and JSON
///
/// JSON syntax for Kea DHCP with command channel is:
/// @code
/// {
///     "code": <code>,
///     "name": <name>,
///     "space": <space>,
///     "csv-format": <csv format flag>,
///     "data": <value>,
///     "always-send": <always send flag>,
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46] with code and space as keys is:
/// @code
/// +--rw option-data* [code space]
///    +--rw code            uint8
///    +--rw space           string
///    +--rw name?           string
///    +--rw data?           string
///    +--rw csv-format?     boolean
///    +--rw always-send?    boolean
///    +--rw user-context?   user-context
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "code": 100,
///         "space": "dns",
///         "csv-format": false,
///         "data": "12121212",
///         "always-send": false
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp6-server:config (container)
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns'] (list instance)
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns']/code = 100
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns']/space = dns
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns']/data = 12121212
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns']/csv-format = false
///  /kea-dhcp6-server:config/
///     option-data[code='100'][space='dns']/always-send = false
/// @endcode

/// @brief A translator class for converting an option data between
/// YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server, not yet ietf-dhcpv6-server.
class TranslatorOptionData : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionData(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionData();

    /// @brief Get and translate an option data from YANG to JSON.
    ///
    ///
    /// @param xpath The xpath of the option data.
    /// @return JSON representation of the option data.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOptionData(const std::string& xpath);

    /// @brief Translate and set option data from JSON to YANG.
    ///
    /// @param xpath The xpath of the option data.
    /// @param elem The JSON element.
    void setOptionData(const std::string& xpath,
                       isc::data::ConstElementPtr elem);

protected:
    /// @brief getOptionData JSON for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the option data.
    /// @return JSON representation of the option data.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOptionDataKea(const std::string& xpath);

    /// @brief setOptionData for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the option data.
    /// @param elem The JSON element.
    void setOptionDataKea(const std::string& xpath,
                          isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting an option data list between
/// YANG and JSON.
///
/// Currently supports on kea-dhcp[46]-server, not yet ietf-dhcpv6-server.
class TranslatorOptionDataList : virtual public TranslatorOptionData {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionDataList(sysrepo::S_Session session,
                             const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionDataList();

    /// @brief Get and translate option data list from YANG to JSON.
    ///
    /// @param xpath The xpath of the option data list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getOptionDataList(const std::string& xpath);

    /// @brief Translate and set option data list from JSON to YANG.
    ///
    /// @param xpath The xpath of the option data list.
    /// @param elem The JSON element.
    void setOptionDataList(const std::string& xpath,
                           isc::data::ConstElementPtr elem);

protected:
    /// @brief getOptionDataList for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the option data list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getOptionDataListKea(const std::string& xpath);

    /// @brief setOptionDataList for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the option data list.
    /// @param elem The JSON element.
    /// @throw BadValue on option data without code or space.
    void setOptionDataListKea(const std::string& xpath,
                              isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_OPTION_DATA_H
