// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/testutils/translator_test.h>

#include <boost/lexical_cast.hpp>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;
namespace isc {
namespace yang {
namespace test {

YangRepr::YangReprItem
YangRepr::YangReprItem::get(const string& xpath, S_Session session) {
    string val_xpath = xpath;
    string value = "";
    sr_type_t type = SR_UNKNOWN_T;
    bool settable = true;
    try {
        S_Val s_val = session->get_item(xpath.c_str());
        if (!s_val) {
            isc_throw(BadValue, "YangReprItem failed at '" << xpath << "'");
        }
        val_xpath = string(s_val->xpath());
        type = s_val->type();
        ostringstream num_value;
        switch (type) {
        case SR_CONTAINER_T:
        case SR_CONTAINER_PRESENCE_T:
            settable = false;
            break;

        case SR_LIST_T:
            break;

        case SR_STRING_T:
            value = s_val->data()->get_string();
            break;

        case SR_BOOL_T:
            value = s_val->data()->get_bool() ? "true" : "false";
            break;

        case SR_UINT8_T:
            num_value << static_cast<unsigned>(s_val->data()->get_uint8());
            value = num_value.str();
            break;

        case SR_UINT16_T:
            num_value << s_val->data()->get_uint16();
            value = num_value.str();
            break;

        case SR_UINT32_T:
            num_value << s_val->data()->get_uint32();
            value = num_value.str();
            break;

        case SR_INT8_T:
            num_value << static_cast<unsigned>(s_val->data()->get_int8());
            value = num_value.str();
            break;

        case SR_INT16_T:
            num_value << s_val->data()->get_int16();
            value = num_value.str();
            break;

        case SR_INT32_T:
            num_value << s_val->data()->get_int32();
            value = num_value.str();
            break;

        case SR_DECIMAL64_T:
            num_value << s_val->data()->get_decimal64();
            value = num_value.str();
            break;

        case SR_IDENTITYREF_T:
            value = s_val->data()->get_identityref();
            break;

        case SR_ENUM_T:
            value = s_val->data()->get_enum();
            break;

        case SR_BINARY_T:
            value = s_val->data()->get_binary();
            break;

        default:
            isc_throw(NotImplemented,
                      "YangReprItem called with unsupported type: " << type);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error in YangReprItem: " << ex.what());
    }
    return (YangReprItem(val_xpath, value, type, settable));
}

YangRepr::Tree
YangRepr::get(S_Session session) const {
    Tree result;
    try {
        TranslatorBasic tb(session, model_);
        string const xpath0("/" + model_ + ":*//.");
        tb.forAll(xpath0, [&](libyang::S_Data_Node const& node) {
            string const& xpath(node->path());
            result.emplace(xpath, YangReprItem::get(xpath, session));
        });
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error in  YangRepr::getTree: " << ex.what());
    }
    return (result);
}

bool
YangRepr::verify(const Tree& expected, S_Session session,
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
YangRepr::set(const Tree& tree, S_Session session) const {
    for (auto const& kv : tree) {
        YangReprItem const& item(kv.second);
        if (!item.settable_) {
            continue;
        }
        try {
            S_Val s_val;
            switch (item.type_) {
            case SR_CONTAINER_T:
            case SR_CONTAINER_PRESENCE_T:
                isc_throw(NotImplemented,
                          "YangRepr::set called for a container");

            case SR_LIST_T:
                isc_throw(NotImplemented,
                          "YangRepr::set called for a list");
                break;

            case SR_STRING_T:
            case SR_IDENTITYREF_T:
            case SR_ENUM_T:
            case SR_BINARY_T:
                s_val.reset(new Val(item.value_.c_str(), item.type_));
                break;

            case SR_BOOL_T:
                if (item.value_ == "true") {
                    s_val.reset(new Val(true, SR_BOOL_T));
                } else if (item.value_ == "false") {
                    s_val.reset(new Val(false, SR_BOOL_T));
                } else {
                    isc_throw(BadValue, "'" << item.value_ << "' not a bool");
                }
                break;

            case SR_UINT8_T:
                try {
                    uint8_t u8 = boost::lexical_cast<unsigned>(item.value_);
                    s_val.reset(new Val(u8));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint8");
                }
                break;

            case SR_UINT16_T:
                try {
                    uint16_t u16 = boost::lexical_cast<uint16_t>(item.value_);
                    s_val.reset(new Val(u16));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint16");
                }
                break;

            case SR_UINT32_T:
                try {
                    uint32_t u32 = boost::lexical_cast<uint32_t>(item.value_);
                    s_val.reset(new Val(u32));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint32");
                }
                break;

            case SR_INT8_T:
                try {
                    int8_t i8 = boost::lexical_cast<int>(item.value_);
                    s_val.reset(new Val(i8));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an int8");
                }
                break;

            case SR_INT16_T:
                try {
                    int16_t i16 = boost::lexical_cast<int16_t>(item.value_);
                    s_val.reset(new Val(i16));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an int16");
                }
                break;

            case SR_INT32_T:
                try {
                    int32_t i32 = boost::lexical_cast<int32_t>(item.value_);
                    s_val.reset(new Val(i32));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an int32");
                }
                break;

            case SR_DECIMAL64_T:
                try {
                    double d64 = boost::lexical_cast<double>(item.value_);
                    s_val.reset(new Val(d64));
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not a real");
                }
                break;

            default:
                isc_throw(NotImplemented,
                          "YangRepr::set called with unsupported type: "
                          << item.type_);
            }
            session->set_item(item.xpath_.c_str(), s_val);
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError,
                      "sysrepo error in YangRepr::set for " << item
                      << ", error: " << ex.what());
        }
    }
    session->apply_changes();
}

bool
YangRepr::validate(S_Session session, ostream& errs) const {
    try {
        // Try to validate. If it succeeds, then we're done here.
        session->validate();
        return (true);
    } catch (const std::exception& ex) {
        errs << "validate fails with " << ex.what() << endl;
    }
    try {
        // If we get here, it means the validate() threw exceptions.
        S_Errors errors(session->get_error());
        if (!errors) {
            // This is really weird. An exception was thrown, but
            // get_last_errors() didn't return anything. Maybe we're out of
            // memory or something?
            errs << "no errors" << endl;
            return (false);
        }
        size_t const count(errors->error_cnt());
        errs << "got " << count << " errors" << endl;
        for (size_t i = 0; i < count ; ++i) {
            const char* message(errors->message(i));
            const char* xpath(errors->xpath(i));
            if (!message || !xpath) {
                continue;
            }
            errs << message << " at " << xpath << endl;
        }
    } catch (const std::exception& ex) {
        errs << "double error " << ex.what();
    }
    return (false);
}

ostream&
operator<<(ostream& os, sr_type_t type) {
    switch (type) {
    case SR_CONTAINER_T:
        os << "container";
        break;
    case SR_CONTAINER_PRESENCE_T:
        os << "container presence";
        break;
    case SR_LIST_T:
        os << "list";
        break;
    case SR_STRING_T:
        os << "string";
        break;
    case SR_BOOL_T:
        os << "bool";
        break;
    case SR_UINT8_T:
        os << "uint8";
        break;
    case SR_UINT16_T:
        os << "uint16";
        break;
    case SR_UINT32_T:
        os << "uint32";
        break;
    case SR_INT8_T:
        os << "int8";
        break;
    case SR_INT16_T:
        os << "int16";
        break;
    case SR_INT32_T:
        os << "int32";
        break;
    case SR_IDENTITYREF_T:
        os << "identity ref";
        break;
    case SR_ENUM_T:
        os << "enum";
        break;
    case SR_BINARY_T:
        os << "binary";
        break;
    case SR_LEAF_EMPTY_T:
        os << "leaf empty";
        break;
    case SR_BITS_T:
        os << "bits";
        break;
    case SR_DECIMAL64_T:
        os << "decimal64";
        break;
    case SR_INSTANCEID_T:
        os << "instance id";
        break;
    case SR_INT64_T:
        os << "int64";
        break;
    case SR_UINT64_T:
        os << "uint64";
        break;
    case SR_ANYXML_T:
        os << "any xml";
        break;
    case SR_ANYDATA_T:
        os << "any data";
        break;
#ifdef SR_UNION_T
    case SR_UNION_T:
        os << "union";
        break;
#endif
    default:
        os << type;
        break;
    }
    return (os);
}

ostream& operator<<(ostream& os, const YangRepr::YangReprItem& item) {
    os << item.xpath_ << " = (" << item.type_ << ") '" << item.value_ << "'";
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
