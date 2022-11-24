// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/testutils/translator_test.h>

#include <boost/lexical_cast.hpp>

#include <variant>
#include <vector>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {
namespace test {

LeafBaseType
YangRepr::YangReprItem::getUnionType(Value const& value) {
    static_assert(
        std::is_same<
            Value, std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t,
                                uint64_t, bool, Empty, Binary, string, optional<DataNode>,
                                Decimal64, vector<Bit>, Enum, IdentityRef>>::value,
        "Value type has changed. The if statement needs to be adjusted to include all alternatives "
        "of the std::variant.");

    if (holds_alternative<int8_t>(value)) {
        return LeafBaseType::Int8;
    } else if (holds_alternative<int16_t>(value)) {
        return LeafBaseType::Int16;
    } else if (holds_alternative<int32_t>(value)) {
        return LeafBaseType::Int32;
    } else if (holds_alternative<int64_t>(value)) {
        return LeafBaseType::Int64;
    } else if (holds_alternative<uint8_t>(value)) {
        return LeafBaseType::Uint8;
    } else if (holds_alternative<uint16_t>(value)) {
        return LeafBaseType::Uint16;
    } else if (holds_alternative<uint32_t>(value)) {
        return LeafBaseType::Uint32;
    } else if (holds_alternative<uint64_t>(value)) {
        return LeafBaseType::Uint64;
    } else if (holds_alternative<bool>(value)) {
        return LeafBaseType::Bool;
    } else if (holds_alternative<Empty>(value)) {
        return LeafBaseType::Empty;
    } else if (holds_alternative<Binary>(value)) {
        return LeafBaseType::Binary;
    } else if (holds_alternative<string>(value)) {
        return LeafBaseType::String;
    } else if (holds_alternative<optional<DataNode>>(value)) {
        return LeafBaseType::InstanceIdentifier;
    } else if (holds_alternative<Decimal64>(value)) {
        return LeafBaseType::Dec64;
    } else if (holds_alternative<vector<Bit>>(value)) {
        return LeafBaseType::Bits;
    } else if (holds_alternative<Enum>(value)) {
        return LeafBaseType::Enum;
    } else if (holds_alternative<IdentityRef>(value)) {
        return LeafBaseType::IdentityRef;
    }
    return LeafBaseType::Unknown;
}

YangRepr::YangReprItem
YangRepr::YangReprItem::get(const string& xpath, Session session) {
    string val_xpath;
    optional<string> value;
    LeafBaseType type(LeafBaseType::Unknown);
    bool settable = true;
    try {
        optional<DataNode> data_node(session.getData(xpath));
        if (!data_node) {
            isc_throw(BadValue, "YangReprItem failed at '" << xpath << "'");
        }
        data_node = data_node->findPath(xpath);
        SchemaNode const& schema(data_node->schema());
        NodeType const node_type(schema.nodeType());
        if (node_type == NodeType::Leaf) {
            type = schema.asLeaf().valueType().base();
        } else if (node_type == NodeType::Leaflist) {
            type = schema.asLeafList().valueType().base();
        } else {
            settable = false;
        }
        if (type == LeafBaseType::Union) {
            // Get the underlying type.
            type = getUnionType(data_node->asTerm().value());
        }
        if (type == LeafBaseType::Leafref) {
            // Get the underlying type.
            type = data_node->schema().asLeaf().valueType().asLeafRef().resolvedType().base();
        }
        value = Translator::translateToYang(Translator::translateFromYang(data_node), type);
        val_xpath = string(data_node->path());
    } catch (Error const& ex) {
        isc_throw(NetconfError, "in YangReprItem: " << ex.what());
    }
    return (YangReprItem(val_xpath, value, type, settable));
}

YangRepr::Tree
YangRepr::get(Session session) const {
    Tree result;
    try {
        Translator tb(session, model_);
        string const xpath0("/" + model_ + ":*//.");
        tb.forAll(xpath0, [&](libyang::DataNode const& node) {
            string const& xpath(node.path());
            result.emplace(xpath, YangReprItem::get(xpath, session));
        });
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "in YangRepr::getTree: " << ex.what());
    }
    return (result);
}

bool
YangRepr::verify(const Tree& expected, Session session,
                 ostream& errs) const {
    bool result(true);
    const Tree& received = get(session);
    for (auto const& kv : received) {
        string const& xpath(kv.first);
        YangReprItem const& received_node(kv.second);

        auto iterator(expected.find(xpath));
        if (iterator == expected.end()) {
            errs << "received " << received_node << ", but was not expected"
                 << endl;
            result = false;
            continue;
        }

        YangReprItem const expected_node(iterator->second);
        if (expected_node != received_node) {
            errs << "expected " << expected_node << ", but received "
                 << received_node << endl;
            result = false;
        }
    }

    for (auto const& kv : expected) {
        string const& xpath(kv.first);
        YangReprItem const& expected_node(kv.second);

        auto iterator(received.find(xpath));
        if (iterator == received.end()) {
            errs << "expected " << expected_node << ", but was not received"
                 << endl;
            result = false;
        }
    }

    return result;
}

void
YangRepr::set(const Tree& tree, Session session) const {
    for (auto const& kv : tree) {
        YangReprItem const& item(kv.second);
        if (!item.settable_) {
            continue;
        }
        try {
            Context const& context(session.getContext());
            SchemaNode const& schema(context.findPath(item.xpath_));
            NodeType const node_type(schema.nodeType());
            bool is_key(false);
            if (node_type == NodeType::Leaf) {
                is_key = schema.asLeaf().isKey();
            }
            if (!is_key) {
                session.setItem(item.xpath_, item.value_);
            }
        } catch (Error const& ex) {
            isc_throw(NetconfError,
                      "in YangRepr::set for " << item
                      << ", error: " << ex.what());
        }
    }
    session.applyChanges();
}

ostream&
operator<<(ostream& os, LeafBaseType type) {
    switch (type) {
    case LeafBaseType::String:
        os << "string";
        break;
    case LeafBaseType::Bool:
        os << "bool";
        break;
    case LeafBaseType::Uint8:
        os << "uint8";
        break;
    case LeafBaseType::Uint16:
        os << "uint16";
        break;
    case LeafBaseType::Uint32:
        os << "uint32";
        break;
    case LeafBaseType::Int8:
        os << "int8";
        break;
    case LeafBaseType::Int16:
        os << "int16";
        break;
    case LeafBaseType::Int32:
        os << "int32";
        break;
    case LeafBaseType::IdentityRef:
        os << "identity ref";
        break;
    case LeafBaseType::Enum:
        os << "enum";
        break;
    case LeafBaseType::Binary:
        os << "binary";
        break;
    case LeafBaseType::Bits:
        os << "bits";
        break;
    case LeafBaseType::Dec64:
        os << "decimal64";
        break;
    case LeafBaseType::InstanceIdentifier:
        os << "instance id";
        break;
    case LeafBaseType::Int64:
        os << "int64";
        break;
    case LeafBaseType::Uint64:
        os << "uint64";
        break;
    case LeafBaseType::Union:
        os << "union";
        break;
    case LeafBaseType::Leafref:
        os << "leafref";
        break;
    case LeafBaseType::Unknown:
        os << "unknown";
        break;
    default:
        isc_throw(BadValue, "unsupported type " << int(type));
    }
    return (os);
}

ostream& operator<<(ostream& os, const YangRepr::YangReprItem& item) {
    os << item.xpath_ << " = (" << item.type_ << ") '" << (item.value_ ? *item.value_ : "nullopt")
       << "'";
    return (os);
}

ostream& operator<<(ostream& os, const YangRepr::Tree& tree) {
    for (auto const& kv : tree) {
        YangRepr::YangReprItem const& item(kv.second);
        os << item << endl;
    }
    return (os);
}

}  // namespace test
}  // namespace yang
}  // namespace isc
