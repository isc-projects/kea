// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/base64.h>
#include <yang/adaptor.h>
#include <yang/translator.h>

#include <sysrepo-cpp/utils/exception.hpp>

#include <cstring>
#include <vector>

using namespace std;
using namespace isc::data;
using namespace isc::util::encode;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

Translator::Translator(Session session, const string& model)
    : session_(session), model_(model) {
}

void
Translator::checkAndGetLeaf(ElementPtr& storage,
                            DataNode const& data_node,
                            string const& name) const {
    ElementPtr const& x(getItem(data_node, name));
    if (x) {
        storage->set(name, x);
    }
}

void
Translator::checkAndGetDivergingLeaf(ElementPtr& storage,
                                     DataNode const& data_node,
                                     string const& name,
                                     string const& yang_name) const {
    ElementPtr const& x(getItem(data_node, yang_name));
    if (x) {
        storage->set(name, x);
    }
}

void
Translator::checkAndGetAndJsonifyLeaf(ElementPtr& storage,
                                      DataNode const& data_node,
                                      string const& name) const {
    ElementPtr const& x(getItem(data_node, name));
    if (x) {
        storage->set(name, Element::fromJSON(x->stringValue()));
    }
}

void
Translator::checkAndJsonifyAndSetLeaf(ConstElementPtr const& from,
                                      string const& xpath,
                                      string const& name) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        ElementPtr const& json(Element::create(x->str()));
        setItem(xpath + "/" + name, json, LeafBaseType::String);
    }
}

void Translator::checkAndSetLeaf(ConstElementPtr const& from,
                                 string const& xpath,
                                 string const& name,
                                 LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        setItem(xpath + "/" + name, x, type);
    }
}

void Translator::checkAndSetDivergingLeaf(ConstElementPtr const& from,
                                          string const& xpath,
                                          string const& name,
                                          string const& yang_name,
                                          LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        setItem(xpath + "/" + yang_name, x, type);
    }
}

void Translator::checkAndSetLeafList(ConstElementPtr const& from,
                                     string const& xpath,
                                     string const& name,
                                     LeafBaseType const type) {
    ConstElementPtr const& leaf_list(from->get(name));
    if (leaf_list && !leaf_list->empty()) {
        for (ElementPtr const& leaf : leaf_list->listValue()) {
            setItem(xpath + "/" + name, leaf, type);
        }
    }
}

void Translator::checkAndSetUserContext(ConstElementPtr const& from,
                                        string const& xpath) {
    ConstElementPtr const& user_context(Adaptor::getContext(from));
    if (user_context) {
        setItem(xpath + "/user-context", Element::create(user_context->str()),
                LeafBaseType::String);
    }
}

string
Translator::decode64(string const& input) {
    vector<uint8_t> binary;
    decodeBase64(input, binary);
    string result;
    result.resize(binary.size());
    memmove(&result[0], &binary[0], result.size());
    return (result);
}

void
Translator::deleteItem(string const& xpath) {
    /// @todo: Remove this if convenient. It is not strictly required and only done to detect
    /// missing schema nodes and throw an exception to keep old behavior.
    try {
        Context const& context(session_.getContext());
        context.findPath(xpath);
    } catch (libyang::Error const& ex) {
        isc_throw(NetconfError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }

    try {
        if (session_.getData(xpath)) {
            session_.deleteItem(xpath);
        }
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError,
                  "sysrepo error deleting item at '"
                  << xpath << "': " << ex.what());
    }
    session_.applyChanges();
}


string
Translator::encode64(string const& input) {
    vector<uint8_t> binary;
    binary.resize(input.size());
    memmove(&binary[0], input.c_str(), binary.size());
    return (encodeBase64(binary));
}

DataNode
Translator::findXPath(string const& xpath) {
    optional<DataNode> const& data_node(getData(xpath));
    if (!data_node) {
        isc_throw(NetconfError, "no data");
    }
    Set<DataNode> at_path(data_node->findXPath(xpath));
    if (at_path.empty()) {
        isc_throw(NetconfError, "no data");
    }
    return at_path.front();
}

optional<DataNode>
Translator::getData(string const& xpath) const {
    /// @todo: Remove this if convenient. It is not strictly required and only done to detect
    /// missing schema nodes and throw an exception to keep old behavior.
    try {
        Context const& context(session_.getContext());
        context.findPath(xpath);
    } catch (libyang::Error const& ex) {
        isc_throw(NetconfError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }

    optional<DataNode> data_node;
    try {
        data_node = session_.getData(xpath);
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }

    return data_node;
}

ElementPtr
Translator::getItem(DataNode const& data_node,
                    string const& xpath) const {
    try {
        Set<DataNode> const& nodes(data_node.findXPath(xpath));
        if (nodes.empty()) {
            return ElementPtr();
        }
        DataNode const& front(nodes.front());
        NodeType const node_type(front.schema().nodeType());

        // Leaf-list
        if (node_type == NodeType::Leaflist) {
            ElementPtr result(Element::createList());
            for (DataNode const& i : nodes) {
                result->add(translateFromYang(i));
            }
            return result;
        } else if (node_type == NodeType::Container) {
            /// @todo:
            /// isc_throw(NetconfError, "getting containers not supported, xpath is '" << xpath << "'");
            return ElementPtr();
        } else if (node_type == NodeType::List) {
            /// @todo:
            /// isc_throw(NetconfError, "getting lists not supported, xpath is '" << xpath << "'");
            return ElementPtr();
        }

        // Leaf
        return translateFromYang(front);
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }
}

ElementPtr
Translator::getItemFromAbsoluteXpath(string const& xpath) const {
    optional<DataNode> const& data_node(getData(xpath));
    if (!data_node) {
        /// @todo:
        /// isc_throw(NetconfError, "no data ");
        return ElementPtr();
    }
    return getItem(*data_node, xpath);
}

void
Translator::getMandatoryLeaf(ElementPtr& storage,
                             DataNode const& data_node,
                             string const& name) const {
    ElementPtr const& x(getItem(data_node, name));
    if (!x) {
        isc_throw(MissingNode, name);
    }
    storage->set(name, x);
}


void
Translator::getMandatoryDivergingLeaf(ElementPtr& storage,
                                      DataNode const& data_node,
                                      string const& name,
                                      string const& yang_name) const {
    ElementPtr const& x(getItem(data_node, yang_name));
    if (!x) {
        isc_throw(MissingNode, yang_name);
    }
    storage->set(name, x);
}

void
Translator::setItem(const string& xpath, ConstElementPtr elem,
                         LeafBaseType type) {
    optional<string> const value(translateToYang(elem, type));
    try {
        session_.setItem(xpath, value);
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "sysrepo error setting item '" << (elem ? elem->str() : "nullopt")
                                << "' at '" << xpath << "': " << ex.what());
    }
    session_.applyChanges();
}

void
Translator::setMandatoryLeaf(ConstElementPtr const& from,
                             string const& xpath,
                             string const& name,
                             LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (!x) {
        isc_throw(MissingNode, "xpath: " << xpath << ", name: " << name);
    }
    setItem(xpath + "/" + name, x, type);
}

void
Translator::setMandatoryDivergingLeaf(ConstElementPtr const& from,
                                      string const& xpath,
                                      string const& name,
                                      string const& yang_name,
                                      LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (!x) {
        isc_throw(MissingNode, "xpath: " << xpath << ", name: " << name);
    }
    setItem(xpath + "/" + yang_name, x, type);
}

ElementPtr
Translator::translateFromYang(optional<DataNode> data_node) {
    NodeType const node_type(data_node->schema().nodeType());
    if (node_type == NodeType::Leaf || node_type == NodeType::Leaflist) {
        DataNodeTerm const& leaf(data_node->asTerm());
        Value const& v(leaf.value());
        if (holds_alternative<string>(v) ||
            holds_alternative<Enum>(v) ||
            holds_alternative<IdentityRef>(v)) {
            // Should be a string. Call create(). Should be slightly faster
            // than wrapping value in double quotes and calling fromJSON().
            return Element::create(string(leaf.valueStr()));
        } else if (holds_alternative<Binary>(v)) {
            return Element::create(decode64(string(leaf.valueStr())));
        } else {
            // This can be various types so defer to fromJSON().
            return Element::fromJSON(string(leaf.valueStr()));
        }
    }
    return ElementPtr();
}

optional<string>
Translator::translateToYang(ConstElementPtr const& element,
                            LeafBaseType const type) {
    if (!element) {
        // A null ElementPtr is how we signal that this item requires no value.
        // Useful when setting YANG lists which is the only way to set their
        // keys in sysrepo since setting the key itself results in an error.
        return nullopt;
    } else if (element->getType() == Element::map) {
        /// @todo: implement
        isc_throw(NotImplemented, "Translator::value(): map element");
    } else if (element->getType() == Element::list) {
        /// @todo: implement
        isc_throw(NotImplemented, "Translator::value(): list element");
    }
    if (type == LeafBaseType::Enum ||
        type == LeafBaseType::String ||
        type == LeafBaseType::Union ||
        type == LeafBaseType::IdentityRef) {
        // These types are usually strings in ElementPtr, but are accepted
        // without the double quotes in sysrepo, so get the stringValue().
        if (element->getType() == Element::string) {
            return element->stringValue();
        } else {
            // Except for some nodes which are maps e.g. user-context. And also Unions and
            // IdentityRefs can very well have underlying types that are different than strings.
            // Use the generic str() for those.
            return element->str();
        }
    } else if (type == LeafBaseType::Binary) {
        return encode64(element->stringValue());
    } else {
        // The rest of YANG values can be expressed using the
        // general string representation of ElementPtr.
        return element->str();
    }
}

}  // namespace yang
}  // namespace isc
