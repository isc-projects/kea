// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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
        const string& xpath0 = "/" + model_ + ":*//.";
        TranslatorBasic tb(session, model_);
        S_Iter_Value iter = tb.getIter(xpath0);
        for (;;) {
            const string& xpath = tb.getNext(iter);
            if (xpath.empty()) {
                break;
            }
            result.push_back(YangReprItem::get(xpath, session));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error in  YangRepr::getTree: " << ex.what());
    }
    return (result);
}

bool
YangRepr::verify(const Tree& expected, S_Session session,
                 ostream& errs) const {
    const Tree& got = get(session);
    for (size_t i = 0; (i < expected.size()) && (i < got.size()); ++i) {
        if (expected[i] == got[i]) {
            continue;
        }
        errs << "expected[" << i << "]: " << expected[i] << endl;
        errs << "got[" << i << "]: " << got[i] << endl;
        return (false);
    }
    if (expected.size() == got.size()) {
        return (true);
    }
    if (expected.size() > got.size()) {
        errs << "missings " << (expected.size() - got.size());
        errs << " beginning by:" << endl << expected[got.size()] << endl;
    } else {
        errs << "extras " << (got.size() - expected.size());
        errs << " beginning by:" << endl << got[expected.size()] << endl;
    }
    return (false);
}

void
YangRepr::set(const Tree& tree, S_Session session) const {
    for (auto item : tree) {
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
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(u8));
#else
                    s_val.reset(new Val(u8, SR_UINT8_T));
#endif
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint8");
                }
                break;

            case SR_UINT16_T:
                try {
                    uint16_t u16 = boost::lexical_cast<uint16_t>(item.value_);
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(u16));
#else
                    s_val.reset(new Val(u16, SR_UINT16_T));
#endif
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint16");
                }
                break;

            case SR_UINT32_T:
                try {
                    uint32_t u32 = boost::lexical_cast<uint32_t>(item.value_);
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(u32));
#else
                    s_val.reset(new Val(u32, SR_UINT32_T));
#endif
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an uint32");
                }
                break;

            case SR_INT8_T:
                try {
                    int8_t i8 = boost::lexical_cast<int>(item.value_);
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(i8));
#else
                    s_val.reset(new Val(i8, SR_INT8_T));
#endif
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an int8");
                }
                break;

            case SR_INT16_T:
                try {
                    int16_t i16 = boost::lexical_cast<int16_t>(item.value_);
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(i16));
#else
                    s_val.reset(new Val(i16, SR_INT16_T));
#endif
                } catch (const boost::bad_lexical_cast&) {
                    isc_throw(BadValue,
                              "'" << item.value_ << "' not an int16");
                }
                break;

            case SR_INT32_T:
                try {
                    int32_t i32 = boost::lexical_cast<int32_t>(item.value_);
#ifdef HAVE_POST_0_7_7_SYSREPO
                    s_val.reset(new Val(i32));
#else
                    s_val.reset(new Val(i32, SR_INT32_T));
#endif
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
                          "YangRepr::set called with unupported type: "
                          << item.type_);
            }
            session->set_item(item.xpath_.c_str(), s_val);
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError,
                      "sysrepo error in YangRepr::set for " << item
                      << ", error: " << ex.what());
        }
    }
}

bool
YangRepr::validate(S_Session session, std::ostream& errs) const {
    try {
        // Try to validate. If it succeeds, then we're done here.
        session->validate();
        return (true);
    } catch (const std::exception& ex) {
        errs << "validate fails with " << ex.what() << endl;
    }
    try {
        // If we get here, it means the validate() threw exceptions.
        S_Errors s_errors = session->get_last_errors();
        if (!s_errors) {

            // This is really weird. An exception was thrown, but
            // get_last_errors() didn't return anything. Maybe we're out of
            // memory or something?
            errs << "no errors" << endl;
            return (false);
        }
        size_t cnt = s_errors->error_cnt();
        errs << "got " << cnt << " errors" << endl;
        for (size_t i = 0; i < cnt; ++i) {
            S_Error s_error = s_errors->error(i);
            if (!s_error) {
                continue;
            }
            const char* xpath = s_error->xpath();
            const char* message = s_error->message();
            if (!xpath || !message) {
                continue;
            }
            // Bug in sysrepo returning message for xpath().
            if (xpath == message) {
                errs << message << endl;
            } else {
                errs << message << endl
                     << "At " << xpath << endl;
            }
        }
    } catch (const std::exception& ex) {
        // Bug in sysrepo rethrowing the last error when trying to get it.
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
    for (auto item : tree) {
        os << item << endl;
    }
    return (os);
}

}; // end of namespace isc::yang::test
}; // end of namespace isc::yang
}; // end of namespace isc
