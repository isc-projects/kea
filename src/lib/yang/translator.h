// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_H
#define ISC_TRANSLATOR_H 1

#include <cc/data.h>
#include <yang/sysrepo_error.h>

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>

namespace isc {
namespace yang {

/// @brief Between YANG and JSON translator class for basic values.
class TranslatorBasic {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name (used and shared by derived classes).
    TranslatorBasic(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorBasic();

    /// @brief Retrieves an item and stores it in the specified storage.
    ///
    /// This will attempt to retrieve an item and, if exists, will
    /// store it in the storage.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param xpath xpath location of data that will be extracted from sysrepo
    /// @param name name of the parameter
    void checkAndGetLeaf(isc::data::ElementPtr& storage,
                         const std::string& xpath,
                         const std::string& name);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the name of the YANG node which should also match the map
    /// key in the JSON configuration
    /// @param type the sysrepo node type
    void checkAndSetLeaf(isc::data::ConstElementPtr const& from,
                         std::string const& xpath,
                         std::string const& name,
                         libyang::LeafBaseType const type);

    /// @brief Delete basic value from YANG.
    ///
    /// @param xpath The xpath of the basic value.
    void delItem(const std::string& xpath);

    /// @brief Run a function for a node and all its children.
    ///
    /// @tparam functor_t typename of the function to be called
    ///
    /// @param xpath the xpath to be travelled
    /// @param f the function to be called on the node itself and each
    /// descendant
    template <typename functor_t>
    void forAll(std::string const& xpath, functor_t f) {
        std::optional<libyang::DataNode> const& data_node(session_.getData(xpath));
        if (!data_node) {
            return;
        }

        for (libyang::DataNode const& sibling : data_node->siblings()) {
            for (libyang::DataNode const& n : sibling.childrenDfs()) {
                f(n);
            }
        }
    }

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

    /// @brief Retrieve a list as ElementPtr from sysrepo from a certain xpath.
    ///
    /// @tparam T typename of the translator that holds the function that will
    /// be called on the xpath of each child from the list
    ///
    /// @param xpath the xpath to the element to be retrieved from, usually a
    /// list
    /// @param t address of a translator instance that holds the function that
    /// will be called on the xpath of each child from the list
    /// @param f the function that will be called on the xpath of each child
    /// from the list
    template <typename T>
    isc::data::ElementPtr getList(std::string const& xpath,
                                  T& t,
                                  isc::data::ElementPtr (T::*f)(std::string const& xpath)) {
        try {
            std::optional<libyang::DataNode> const& tree(session_.getData(xpath));
            if (!tree) {
                return (isc::data::ElementPtr());
            }
            libyang::Set<libyang::DataNode> const& s_vals(tree->findXPath(xpath));
            if (s_vals.empty()) {
                return (isc::data::ElementPtr());
            }
            isc::data::ElementPtr const result(isc::data::Element::createList());
            for (libyang::DataNode const& i : s_vals) {
                result->add((t.*f)(i.path()));
            }
            return result;
        } catch (libyang::Error const& ex) {
            isc_throw(SysrepoError, "sysrepo error getting item at '"
                                        << xpath << "': " << ex.what());
        }
    }

    /// @brief Translate and set basic value from JSON to YANG.
    ///
    /// @param xpath The xpath of the basic value.
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    void setItem(const std::string& xpath,
                 isc::data::ConstElementPtr elem,
                 libyang::LeafBaseType type);

    /// @brief Translate basic value from YANG to JSON.
    ///
    /// @note Please don't use this outside tests.
    ///
    /// @param s_val The value.
    /// @return The Element representing the sysrepo value.
    /// @throw NotImplemented when the value type is not supported.
    static isc::data::ElementPtr value(std::optional<libyang::DataNode> s_val);

    /// @brief Translate basic value from JSON to YANG.
    ///
    /// @note Please don't use this outside tests.
    ///
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    static std::optional<std::string> value(isc::data::ConstElementPtr const& elem,
                                            libyang::LeafBaseType const type);

protected:
    /// @brief The sysrepo session.
    sysrepo::Session session_;

    /// @brief The model.
    std::string model_;
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_H
