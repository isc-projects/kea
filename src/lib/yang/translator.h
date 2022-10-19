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

    /// @brief Retrieves a child YANG data node identified by name from the
    /// given parent YANG container node and stores it in the specified storage.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name name of the parameter
    void checkAndGetLeaf(isc::data::ElementPtr& storage,
                         libyang::DataNode const& data_node,
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

    /// @brief Retrieves a YANG data node by xpath.
    ///
    /// @note This is a computationally expensive operation that makes a lookup in the sysrepo
    /// datastore by calling Session::getData(). It should be used sparingly in production code,
    /// mainly to get an initial data node to work with. It may be used at will in unit tests.
    ///
    /// @param xpath the xpath of the requested node
    ///
    /// @return the requested YANG data node
    ///
    /// @throw SysrepoError if no YANG data node was found
    libyang::DataNode findXPath(std::string const& xpath);

    /// @brief Run a function for a node and all its children.
    ///
    /// @tparam functor_t typename of the function to be called
    ///
    /// @note This is a computationally expensive operation that makes a lookup
    /// in the sysrepo datastore by calling Session::getData(). It should be
    /// used sparingly in production code. It is primarily meant for unit tests.
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

    /// @brief Translate a basic value from YANG to JSON for
    /// a given xpath that is relative to the given source node.
    ///
    /// @param data_node the source data node
    /// @param xpath the relative xpath
    ///
    /// @return The Element representing the item at xpath or null
    /// when not found.
    ///
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getItem(libyang::DataNode const& data_node,
                                  std::string const& xpath) const;

    /// @brief Translate a basic value from YANG to JSON for a given absolute xpath.
    ///
    /// @note This is a computationally expensive operation that makes a lookup in the sysrepo
    /// datastore by calling Session::getData(). It should be used sparingly in production code,
    /// mainly to get an initial data node to work with. It may be used at will in unit tests.
    ///
    /// @param xpath The xpath of the basic value.
    /// @return The Element representing the item at xpath or null
    /// when not found.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getItem(std::string const& xpath) const;

    /// @brief Retrieve a list as ElementPtr from sysrepo from a certain xpath.
    ///
    /// @tparam T typename of the translator that holds the function that will
    /// be called on the xpath of each child from the list
    ///
    /// @param data_node the YANG data node to retrieve data from
    /// @param xpath the xpath to the element to be retrieved from, relative to {data_node}
    /// @param t address of a translator instance that holds the function that
    /// will be called on the xpath of each child from the list
    /// @param f the function that will be called on the xpath of each child
    /// from the list
    template <typename T>
    isc::data::ElementPtr getList(libyang::DataNode const& data_node,
                                  std::string const& xpath,
                                  T& t,
                                  isc::data::ElementPtr (T::*f)(libyang::DataNode const&)) {
        try {
            libyang::Set<libyang::DataNode> const& nodes(data_node.findXPath(xpath));
            if (nodes.empty()) {
                return (isc::data::ElementPtr());
            }
            isc::data::ElementPtr const result(isc::data::Element::createList());
            for (libyang::DataNode const& i : nodes) {
                result->add((t.*f)(i));
            }
            return result;
        } catch (libyang::Error const& ex) {
            isc_throw(SysrepoError, "sysrepo error getting item: " << ex.what());
        }
    }

    /// @brief Get a YANG data node found at the given absolute xpath.
    ///
    /// @note This is a computationally expensive operation that makes a lookup in the sysrepo
    /// datastore by calling Session::getData(). It should be used sparingly in production code,
    /// mainly to get an initial data node to work with. It may be used at will in unit tests.
    ///
    /// @param xpath the xpath at which the YANG data node is to be found
    ///
    /// @return a DataNode if found, or nullopt otherwise
    ///
    /// @throw SysrepoError when the used sysrepo API throws an error
    std::optional<libyang::DataNode> getNode(std::string const& xpath) const;

    /// @brief Translate and set basic value from JSON to YANG.
    ///
    /// @param xpath The xpath of the basic value.
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    void setItem(const std::string& xpath,
                 isc::data::ConstElementPtr elem,
                 libyang::LeafBaseType type);

    /// @brief Translate basic value from the given YANG data node to JSON element.
    ///
    /// @param data_node the YANG data node
    ///
    /// @return the translated JSON element
    static isc::data::ElementPtr value(std::optional<libyang::DataNode> data_node);

    /// @brief Translate basic value from JSON to YANG.
    ///
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    ///
    /// @return string representation of {elem}, or nullopt if {elem} is null
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
