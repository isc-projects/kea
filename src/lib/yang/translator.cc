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
Translator::checkAndSetLeaf(ConstElementPtr const& from,
                            string const& xpath,
                            string const& name,
                            LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        setItem(xpath + "/" + name, x, type);
    }
}

void
Translator::checkAndSetDivergingLeaf(ConstElementPtr const& from,
                                     string const& xpath,
                                     string const& name,
                                     string const& yang_name,
                                     LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        setItem(xpath + "/" + yang_name, x, type);
    }
}

void
Translator::checkAndSetLeafList(ConstElementPtr const& from,
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

void
Translator::checkAndSetUserContext(ConstElementPtr const& from,
                                   string const& xpath) {
    ConstElementPtr const& user_context(Adaptor::getContext(from));
    if (user_context) {
        setItem(xpath + "/user-context", Element::create(user_context->str()),
                LeafBaseType::String);
    }
}

void
Translator::checkAndStringifyAndSetLeaf(ConstElementPtr const& from,
                                        string const& xpath,
                                        string const& name) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        ElementPtr const& json(Element::create(x->str()));
        setItem(xpath + "/" + name, json, LeafBaseType::String);
    }
}

void
Translator::deleteItem(string const& xpath) {
    try {
        if (session_.getData(xpath)) {
            session_.deleteItem(xpath);
        }
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "deleting item at '" << xpath << "': " << ex.what());
    }
    session_.applyChanges();
}

DataNode
Translator::findXPath(string const& xpath) const {
    optional<DataNode> const& data_node(getData(xpath));
    if (!data_node) {
        isc_throw(NetconfError, "no data at xpath " << xpath);
    }
    Set<DataNode> at_path(data_node->findXPath(xpath));
    if (at_path.empty()) {
        isc_throw(NetconfError, "no data at xpath " << xpath);
    }
    return at_path.front();
}

optional<DataNode>
Translator::getData(string const& xpath) const {
    optional<DataNode> data_node;
    try {
        data_node = session_.getData(xpath);
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "getting item at '" << xpath << "': " << ex.what());
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

        // Leaf
        if (node_type == NodeType::Leaf) {
            return translateFromYang(front);
        } else if (node_type == NodeType::Leaflist) {
            ElementPtr result(Element::createList());
            for (DataNode const& i : nodes) {
                result->add(translateFromYang(i));
            }
            return result;
        } else {
            isc_throw(NotImplemented, "getting node of type "
                                          << int(node_type) << " not supported, xpath is '" << xpath
                                          << "'");
        }

    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "getting item at '" << xpath << "': " << ex.what());
    }
}

ElementPtr
Translator::getItemFromAbsoluteXpath(string const& xpath) const {
    optional<DataNode> const& data_node(getData(xpath));
    if (!data_node) {
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

bool
Translator::schemaNodeExists(string const& xpath) const {
    Context const& context(session_.getContext());
    try {
        context.findPath(xpath);
    } catch (libyang::Error const& ex) {
        return false;
    }
    return true;
}

void
Translator::setItem(const string& xpath, ConstElementPtr elem, LeafBaseType type) {
    optional<string> const value(translateToYang(elem, type));
    try {
        session_.setItem(xpath, value);
    } catch (sysrepo::Error const& ex) {
        isc_throw(NetconfError, "setting item '" << (elem ? elem->str() : "nullopt")
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
        LeafBaseType type;
        if (node_type == NodeType::Leaf) {
            type = leaf.schema().asLeaf().valueType().base();
        } else {
            type = leaf.schema().asLeafList().valueType().base();
        }

        static Deserializer deserializer(initializeDeserializer());
        return deserializer.at(type)(string(leaf.valueStr()));
    }
    return ElementPtr();
}

optional<string>
Translator::translateToYang(ConstElementPtr const& element,
                            libyang::LeafBaseType const type) {
    string string_representation;
    if (!element) {
        // A null ElementPtr is how we signal that this item requires no value.
        // Useful when setting YANG lists which is the only way to set their
        // keys in sysrepo since setting the key itself results in an error.
        return nullopt;
    } else if (element->getType() == Element::map) {
        isc_throw(NotImplemented, "Translator::value(): map element");
    } else if (element->getType() == Element::list) {
        isc_throw(NotImplemented, "Translator::value(): list element");
    } else if (element->getType() == Element::string) {
        // If it's a string, get the variant without quotes.
        string_representation = element->stringValue();
    } else {
        // If it's not a string, also get the variant without quotes, but it's a different method.
        string_representation = element->str();
    }

    static Serializer serializer(initializeSerializer());
    return serializer.at(type)(string_representation);
}

string
Translator::decode64(string const& input) {
    vector<uint8_t> binary;
    decodeBase64(input, binary);
    string result;
    result.resize(binary.size());
    memcpy(&result[0], &binary[0], result.size());
    return (result);
}

string
Translator::encode64(string const& input) {
    vector<uint8_t> binary;
    binary.resize(input.size());
    memcpy(&binary[0], input.c_str(), binary.size());
    return (encodeBase64(binary));
}

Translator::Deserializer
Translator::initializeDeserializer() {
    Deserializer result;

    result.emplace(LeafBaseType::Binary, [](string const& value) -> ElementPtr const {
        return Element::create(decode64(value));
    });

    for (LeafBaseType const& i :
         {LeafBaseType::Bool, LeafBaseType::Dec64, LeafBaseType::Int8, LeafBaseType::Int16,
          LeafBaseType::Int32, LeafBaseType::Int64, LeafBaseType::Uint8, LeafBaseType::Uint16,
          LeafBaseType::Uint32, LeafBaseType::Uint64}) {
        result.emplace(i, [](string const& value) -> ElementPtr const {
            return Element::fromJSON(value);
        });
    }

    // The rest of YANG values can be expressed as strings.
    for (LeafBaseType const& i :
         {LeafBaseType::Bits, LeafBaseType::Empty, LeafBaseType::Enum, LeafBaseType::IdentityRef,
          LeafBaseType::InstanceIdentifier, LeafBaseType::Leafref, LeafBaseType::String,
          LeafBaseType::Union, LeafBaseType::Unknown}) {
        result.emplace(i, [](string const& value) -> ElementPtr const {
            return Element::create(value);
        });
    }

    return result;
}

Translator::Serializer
Translator::initializeSerializer() {
    Serializer result;

    result.emplace(LeafBaseType::Binary, [](string const& value) -> string const {
        return encode64(value);
    });

    // The rest of YANG values can be expressed directly.
    for (LeafBaseType const& i :
         {LeafBaseType::Bits, LeafBaseType::Bool, LeafBaseType::Dec64, LeafBaseType::Empty,
          LeafBaseType::Enum, LeafBaseType::IdentityRef, LeafBaseType::InstanceIdentifier,
          LeafBaseType::Int8, LeafBaseType::Int16, LeafBaseType::Int32, LeafBaseType::Int64,
          LeafBaseType::Leafref, LeafBaseType::String, LeafBaseType::Uint8, LeafBaseType::Uint16,
          LeafBaseType::Uint32, LeafBaseType::Uint64, LeafBaseType::Union, LeafBaseType::Unknown}) {
        result.emplace(i, [](string const& value) -> string const {
            return value;
        });
    }

    return result;
}

}  // namespace yang
}  // namespace isc
