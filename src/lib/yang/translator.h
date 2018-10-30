// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_H
#define ISC_TRANSLATOR_H 1

#include <cc/data.h>
#include <yang/sysrepo_error.h>

#ifndef HAVE_SYSREPO
#error "config.h must be included before translator.h"
#endif

#ifndef HAVE_OLD_SYSREPO
#include <sysrepo-cpp/Session.hpp>
#else
#include <sysrepo-cpp/Session.h>
#endif

namespace isc {
namespace yang {

/// @brief Between YANG and JSON translator class for basic values.
class TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name (used and shared by derived classes).
#ifndef HAVE_OLD_SYSREPO
    TranslatorBasic(sysrepo::S_Session session, const std::string& model);
#else
    TranslatorBasic(S_Session session, const std::string& model);
#endif

    /// @brief Destructor.
    virtual ~TranslatorBasic();

    /// @brief Translate basic value from YANG to JSON.
    ///
    /// @note Please don't use this outside tests.
    ///
    /// @param s_val The value.
    /// @return The Element representing the sysrepo value.
    /// @throw NotImplemented when the value type is not supported.
#ifndef HAVE_OLD_SYSREPO
    static isc::data::ElementPtr value(sysrepo::S_Val s_val);
#else
    static isc::data::ElementPtr value(S_Val s_val);
#endif

    /// @brief Get and translate basic value from YANG to JSON.
    ///
    /// @note Should be const as it is read only...
    ///
    /// @param xpath The xpath of the basic value.
    /// @return The Element representing the item at xpath or null
    /// when not found.
    /// @throw SysrepoError when sysrepo raises an error.
    /// @throw NotImplemented when the value type is not supported.
    isc::data::ElementPtr getItem(const std::string& xpath);

    /// @brief Get and translate a list of basic values from YANG to JSON.
    ///
    /// @param xpath The xpath of the list of basic values.
    /// @return The ListElement representing the leaf-list at xpath or
    /// null when not found.
    isc::data::ElementPtr getItems(const std::string& xpath);

    /// @brief Translate basic value from JSON to YANG.
    ///
    /// @note Please don't use this outside tests.
    ///
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
#ifndef HAVE_OLD_SYSREPO
    static sysrepo::S_Val value(isc::data::ConstElementPtr elem,
                                sr_type_t type);
#else
    static S_Val value(isc::data::ConstElementPtr elem, sr_type_t type);
#endif

    /// @brief Translate and set basic value from JSON to YANG.
    ///
    /// @param xpath The xpath of the basic value.
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    void setItem(const std::string& xpath, isc::data::ConstElementPtr elem,
                 sr_type_t type);

    /// @brief Delete basic value from YANG.
    ///
    /// @param xpath The xpath of the basic value.
    void delItem(const std::string& xpath);

    /// List iterator methods keeping the session private.

    /// @brief Get iterator over a YANG list.
    ///
    /// @param xpath The xpath of the list.
    /// @return An S_Iter_Value pointer. Null is the list does not exist.
#ifndef HAVE_OLD_SYSREPO
    sysrepo::S_Iter_Value getIter(const std::string& xpath);
#else
    S_Iter_Value getIter(const std::string& xpath);
#endif

    /// @brief Get xpath of the next YANG list item.
    ///
    /// @param iter The iterator pointing to the previous element
    /// @return The xpath of the next element. Empty string when at
    /// the end of the list.
#ifndef HAVE_OLD_SYSREPO
    std::string getNext(sysrepo::S_Iter_Value iter);
#else
    std::string getNext(S_Iter_Value iter);
#endif

protected:
    /// @brief The sysrepo session.
#ifndef HAVE_OLD_SYSREPO
    sysrepo::S_Session session_;
#else
    S_Session session_;
#endif

    /// @brief The model.
    std::string model_;
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_H
