// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator.h>
#include <util/encode/base64.h>

#include <sysrepo-cpp/utils/exception.hpp>

#include <cstring>

using namespace std;
using namespace isc::data;
using namespace isc::util::encode;
using namespace libyang;
using namespace sysrepo;

namespace {

string encode64(const string& input) {
    vector<uint8_t> binary;
    binary.resize(input.size());
    memmove(&binary[0], input.c_str(), binary.size());
    return (encodeBase64(binary));
}

string decode64(const string& input) {
    vector<uint8_t> binary;
    decodeBase64(input, binary);
    string result;
    result.resize(binary.size());
    memmove(&result[0], &binary[0], result.size());
    return (result);
}

} // end of anonymous namespace

namespace isc {
namespace yang {

TranslatorBasic::TranslatorBasic(Session session, const string& model)
    : session_(session), model_(model) {
}

TranslatorBasic::~TranslatorBasic() {
}

void
TranslatorBasic::checkAndGetLeaf(ElementPtr& storage,
                                 const std::string& xpath,
                                 const std::string& name) {
    ConstElementPtr x = getItem(xpath + "/" + name);
    if (x) {
        storage->set(name, x);
    }
}

void TranslatorBasic::checkAndSetLeaf(ConstElementPtr const& from,
                                      string const& xpath,
                                      string const& name,
                                      LeafBaseType const type) {
    ConstElementPtr const& x(from->get(name));
    if (x) {
        setItem(xpath + "/" + name, x, type);
    }
}

void
TranslatorBasic::delItem(const std::string& xpath) {
    // TODO: Remove this if convenient. It is not strictly required and only done to detect
    // missing schema nodes and throw an exception to keep old behavior.
    try {
        Context const& context(session_.getContext());
        context.findPath(xpath);
    } catch (libyang::Error const& ex) {
        isc_throw(SysrepoError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }

    try {
        if (session_.getData(xpath)) {
            session_.deleteItem(xpath);
        }
    } catch (sysrepo::Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error deleting item at '"
                  << xpath << "': " << ex.what());
    }
    session_.applyChanges();
}

ElementPtr
TranslatorBasic::getItem(const string& xpath) {
    // TODO: Remove this if convenient. It is not strictly required and only done to detect
    // missing schema nodes and throw an exception to keep old behavior.
    try {
        Context const& context(session_.getContext());
        context.findPath(xpath);
    } catch (libyang::Error const& ex) {
        isc_throw(SysrepoError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }

    try {
        optional<DataNode> const& s_val(session_.getData(xpath));
        if (!s_val) {
            // TODO:
            // isc_throw(SysrepoError, "no data at '" << xpath << "'");
            return ElementPtr();
        }
        Set<DataNode> const& nodes(s_val->findXPath(xpath));
        DataNode const& front(nodes.front());
        NodeType const node_type(front.schema().nodeType());

        // Leaf-list
        if (node_type == NodeType::Leaflist) {
            ElementPtr result(Element::createList());
            for (DataNode const& i : nodes) {
                result->add(value(i));
            }
            return result;
        } else if (node_type == NodeType::Container) {
            // TODO:
            // isc_throw(SysrepoError, "getting containers not supported, xpath is '" << xpath << "'");
            return ElementPtr();
        } else if (node_type == NodeType::List) {
            // TODO:
            // isc_throw(SysrepoError, "getting lists not supported, xpath is '" << xpath << "'");
            return ElementPtr();
        }

        // Leaf
        return value(front);

    } catch (sysrepo::Error const& ex) {
        isc_throw(SysrepoError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }
}

ElementPtr
TranslatorBasic::getItems(const string& xpath) {
    return getItem(xpath);
}

void
TranslatorBasic::setItem(const string& xpath,
                         ConstElementPtr elem,
                         LeafBaseType type) {
    optional<string> const s_val(value(elem, type));
    try {
        session_.setItem(xpath, s_val);
    } catch (sysrepo::Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting item '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
    session_.applyChanges();
}

ElementPtr
TranslatorBasic::value(optional<DataNode> data_node) {
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
TranslatorBasic::value(ConstElementPtr const& element,
                       LeafBaseType const type) {
    if (!element) {
        // A null ElementPtr is how we signal that this item requires no value.
        // Useful when setting YANG lists which is the only way to set their
        // keys in sysrepo since setting the key itself results in an error.
        return std::nullopt;
    } else if (element->getType() == Element::map) {
        // TODO: implement
        isc_throw(NotImplemented, "TranslatorBasic::value(): map element");
    } else if (element->getType() == Element::list) {
        // TODO: implement
        isc_throw(NotImplemented, "TranslatorBasic::value(): list element");
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
