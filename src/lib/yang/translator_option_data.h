// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

// @brief Between Yang and JSON translator class for the option data.
class TranslatorOptionData : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionData(S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionData();

    /// @brief Get and translate an option data from Yang to JSON.
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
    /// @param xpath The xpath of the option data.
    /// @return JSON representation of the option data.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOptionData(const std::string& xpath);

    /// @brief Translate and set option data from JSON to Yang.
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
    /// Yang syntax for kea-dhcp[46] with code and space as keys is:
    /// @code
    ///    +--rw name?          string
    ///    +--rw data?          string
    ///    +--rw code           uint8 / uint16
    ///    +--rw space          string
    ///    +--rw csv-format?    string
    ///    +--rw always-send?   boolean
    ///    +--rw user-context?  string
    /// @endcode
    ///
    /// @param xpath The xpath of the option data.
    /// @param elem The JSON element.
    void setOptionDataKea(const std::string& xpath,
                          isc::data::ConstElementPtr elem);

    /// @brief The model.
    std::string model_;
};

// @brief Between Yang and JSON translator class for option data list.
class TranslatorOptionDataList : virtual public TranslatorOptionData {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorOptionDataList(S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorOptionDataList();

    /// @brief Get and translate option data list from Yang to JSON.
    ///
    /// @param xpath The xpath of the option data list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getOptionDataList(const std::string& xpath);

    /// @brief Translate and set option data list from JSON to Yang.
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
    /// Yang syntax is a option-data list keyed by code and space.
    ///
    /// @param xpath The xpath of the option data list.
    /// @param elem The JSON element.
    void setOptionDataListKea(const std::string& xpath,
                              isc::data::ConstElementPtr elem);

    /// @brief The model.
    std::string model_;
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_OPTION_DATA_H
