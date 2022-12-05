// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_H
#define ISC_TRANSLATOR_H 1

#include <cc/data.h>
#include <yang/netconf_error.h>

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>

#include <unordered_map>

namespace isc {
namespace yang {

/// @brief Between YANG and JSON translator class for basic values.
class Translator {
public:
    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name (used and shared by derived classes).
    Translator(sysrepo::Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~Translator() = default;

    /// @brief Calls {translate} for the element found at {xpath} relative to
    /// {data_node} and sets the result in {storage} with the {xpath} key.
    ///
    /// @tparam T typename of the function to be called
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param xpath relative xpath to search by
    /// @param translate function to be called to translate a data node to an element pointer
    template <typename T>
    void checkAndGet(isc::data::ElementPtr const& storage,
                     libyang::DataNode const& data_node,
                     std::string const& xpath,
                     T translate) const {
        libyang::Set<libyang::DataNode> const& nodes(data_node.findXPath(xpath));
        if (!nodes.empty()) {
            isc::data::ElementPtr const& element(translate(nodes.front()));
            if (element && !element->empty()) {
                storage->set(xpath, element);
            }
        }
    }

    /// @brief Calls {translate} for the element found at {xpath} relative to
    /// {data_node} and sets the result in {storage} with the {key} key.
    ///
    /// It's the counterpart for @ref checkAndGet, but when the YANG xpath
    /// and the JSON key diverge.
    ///
    /// @tparam T typename of the function to be called
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param key where to set the result in the {storage} map
    /// @param xpath relative xpath to search by
    /// @param translate function to be called to translate a data node to an element pointer
    template <typename T>
    void checkAndGetDiverging(isc::data::ElementPtr const& storage,
                              libyang::DataNode const& data_node,
                              std::string const& key,
                              std::string const& xpath,
                              T translate) const {
        libyang::Set<libyang::DataNode> const& nodes(data_node.findXPath(xpath));
        if (!nodes.empty()) {
            isc::data::ElementPtr const& element(translate(nodes.front()));
            if (element && !element->empty()) {
                storage->set(key, element);
            }
        }
    }

    /// @brief Retrieves a child YANG data node identified by name from the
    /// given parent YANG container node and stores it in the specified storage.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name the name of the parameter to be set in storage
    void checkAndGetLeaf(isc::data::ElementPtr& storage,
                         libyang::DataNode const& data_node,
                         std::string const& name) const;

    /// @brief Retrieves a child YANG data node identified by name from the
    /// given parent YANG container node and stores it in the specified storage.
    ///
    /// It's the counterpart for @ref checkAndGetLeaf, but when the YANG xpath
    /// and the JSON key diverge.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name the name of the parameter to be set in storage
    /// @param yang_name the name by which to find the parameter in the YANG data node
    void checkAndGetDivergingLeaf(isc::data::ElementPtr& storage,
                                  libyang::DataNode const& data_node,
                                  std::string const& name,
                                  std::string const& yang_name) const;

    /// @brief Retrieves a child YANG data node identified by name from the given parent YANG
    /// container node, converts it from string to JSON and stores it in the specified storage.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name the name of the parameter to be set in storage
    void checkAndGetAndJsonifyLeaf(isc::data::ElementPtr& storage,
                                   libyang::DataNode const& data_node,
                                   const std::string& name) const;

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the name of the YANG node which should also match the key
    /// under which data is set in the MapElement {from}
    /// @param type the YANG node type
    void checkAndSetLeaf(isc::data::ConstElementPtr const& from,
                         std::string const& xpath,
                         std::string const& name,
                         libyang::LeafBaseType const type);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// It's the counterpart for @ref checkAndSetLeaf, but when the YANG xpath
    /// and the JSON key diverge.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the key under which data is set in the MapElement {from}
    /// @param yang_name the name of the YANG node
    /// @param type the YANG node type
    void checkAndSetDivergingLeaf(isc::data::ConstElementPtr const& from,
                                  std::string const& xpath,
                                  std::string const& name,
                                  std::string const& yang_name,
                                  libyang::LeafBaseType const type);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath as a leaf-list.
    ///
    /// @param from the parent configuration node from which to take the values
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the name of the YANG node which should also match the key
    /// under which data is set in the MapElement {from}
    /// @param type the YANG node type of the underlying leaf-list nodes
    void checkAndSetLeafList(isc::data::ConstElementPtr const& from,
                             std::string const& xpath,
                             std::string const& name,
                             libyang::LeafBaseType const type);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    void checkAndSetUserContext(isc::data::ConstElementPtr const& from,
                                std::string const& xpath);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the name of the YANG node which should also match the key
    /// under which data is set in the MapElement {from}
    void checkAndStringifyAndSetLeaf(isc::data::ConstElementPtr const& from,
                                     std::string const& xpath,
                                     std::string const& name);

    /// @brief Delete basic value from YANG.
    ///
    /// @param xpath The xpath of the basic value.
    void deleteItem(const std::string& xpath);

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
    /// @throw NetconfError if no YANG data node was found
    libyang::DataNode findXPath(std::string const& xpath) const;

    /// @brief Run a function for a node and all its children.
    ///
    /// @tparam functor_t typename of the function to be called
    ///
    /// @note This is a computationally expensive operation that makes a lookup
    /// in the sysrepo datastore by calling Session::getData(). It should be
    /// used sparingly in production code. It is primarily meant for unit tests.
    ///
    /// @param xpath the xpath of the root node belonging to the the tree being traversed
    /// @param f the function to be called on the node itself and each descendant
    template <typename functor_t>
    void forAll(std::string const& xpath, functor_t f) const {
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
    /// @throw NetconfError when the used sysrepo API throws an error
    std::optional<libyang::DataNode> getData(std::string const& xpath) const;

    /// @brief Translate a basic value from YANG to JSON for
    /// a given xpath that is relative to the given source node.
    ///
    /// @param data_node the source data node
    /// @param xpath the relative xpath
    ///
    /// @return The Element representing the item at xpath or null
    /// when not found.
    ///
    /// @throw NetconfError when sysrepo raises an error.
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
    /// @throw NetconfError when sysrepo raises an error.
    isc::data::ElementPtr getItemFromAbsoluteXpath(std::string const& xpath) const;

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
                                  isc::data::ElementPtr (T::*f)(libyang::DataNode const&)) const {
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
            isc_throw(NetconfError, "getting item: " << ex.what());
        }
    }

    /// @brief Retrieves a child YANG data node identified by name from the
    /// given parent YANG container node and stores it in the specified storage.
    ///
    /// Unlike @ref checkAndGetLeaf, the leaf is expected to be present.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name the name of the YANG node which should also match the map
    /// key in the JSON configuration
    ///
    /// @throw MissingNode if leaf is not found
    void getMandatoryLeaf(isc::data::ElementPtr& storage,
                          libyang::DataNode const& data_node,
                          std::string const& name) const;

    /// @brief Retrieves a child YANG data node identified by one name from the
    /// given parent YANG container node and stores it in the specified storage
    /// under a different name.
    ///
    /// Unlike @ref checkAndGetLeaf, the leaf is expected to be present.
    ///
    /// @param storage ElementMap where result will be stored
    /// @param data_node parent data node of container type
    /// @param name the map key in the JSON configuration
    /// @param yang_name the name by which to find the parameter in the YANG data node
    ///

    /// @throw MissingNode if leaf is not found
    void getMandatoryDivergingLeaf(isc::data::ElementPtr& storage,
                                   libyang::DataNode const& data_node,
                                   std::string const& name,
                                   std::string const& yang_name) const;

    /// @brief Checks whether a YANG node exists in the schema.
    ///
    /// @param xpath the xpath to be checked
    ///
    /// @return true if the YANG node exists in the schema, false otherwise
    bool schemaNodeExists(std::string const& xpath) const;

    /// @brief Translate and set basic value from JSON to YANG.
    ///
    /// @param xpath The xpath of the basic value.
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    void setItem(const std::string& xpath,
                 isc::data::ConstElementPtr elem,
                 libyang::LeafBaseType type);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the name of the YANG node which should also match the map
    /// key in the JSON configuration
    /// @param type the YANG node type
    void setMandatoryLeaf(isc::data::ConstElementPtr const& from,
                          std::string const& xpath,
                          std::string const& name,
                          libyang::LeafBaseType const type);

    /// @brief Get an element from given ElementPtr node and set it in sysrepo
    /// at given xpath.
    ///
    /// @param from the parent configuration node from which to take the value
    /// @param xpath the xpath to the YANG node without the last node
    /// @param name the map key in the JSON configuration
    /// @param yang_name the name by which to find the parameter in the YANG data node
    /// @param type the YANG node type
    void setMandatoryDivergingLeaf(isc::data::ConstElementPtr const& from,
                                   std::string const& xpath,
                                   std::string const& name,
                                   std::string const& yang_name,
                                   libyang::LeafBaseType const type);

    /// @brief Translate basic value from the given YANG data node to JSON element.
    ///
    /// @param data_node the YANG data node
    ///
    /// @return the translated JSON element
    static isc::data::ElementPtr translateFromYang(std::optional<libyang::DataNode> data_node);

    /// @brief Translate basic value from JSON to YANG.
    ///
    /// @param elem The JSON element.
    /// @param type The sysrepo type.
    ///
    /// @return string representation of {elem}, or nullopt if {elem} is null
    static std::optional<std::string> translateToYang(isc::data::ConstElementPtr const& elem,
                                                      libyang::LeafBaseType const type);

protected:
    /// @brief Decode a YANG element of binary type to a string that
    /// can be stored in an Element::string JSON.
    ///
    /// @param input string to be decoded
    ///
    /// @return the decoded string
    static std::string decode64(std::string const& input);

    /// @brief Encode a string such that it can be stored in a YANG element of binary type.
    ///
    /// @param input string to be encoded
    ///
    /// @return the encoded string
    static std::string encode64(std::string const& input);

    /// @brief Maps YANG types to functions that transform a YANG type into an ElementPtr.
    using Deserializer =
        std::unordered_map<libyang::LeafBaseType,
                           std::function<isc::data::ElementPtr const(std::string const&)>>;

    /// @brief Initializes the deserializer which is used to translate a YANG node to an ElementPtr.
    ///
    /// @return a copy of the deserializer
    static Deserializer initializeDeserializer();

    /// @brief Maps YANG types to functions that transform the string representation of an
    /// Element into a string that can be passed into Session::setItem().
    using Serializer =
        std::unordered_map<libyang::LeafBaseType,
                           std::function<std::string const(std::string const&)>>;

    /// @brief Initializes the serializer which is used to translate the string value of an Element
    /// to a string that can be passed into Session::setItem().
    ///
    /// @return a copy of the serializer
    static Serializer initializeSerializer();

    /// @brief The sysrepo session.
    sysrepo::Session session_;

    /// @brief The model.
    std::string model_;
};  // Translator

}  // namespace yang
}  // namespace isc

#endif  // ISC_TRANSLATOR_H
