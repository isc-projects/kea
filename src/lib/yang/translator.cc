// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator.h>
#include <util/encode/base64.h>
#include <cstring>

using namespace std;
using namespace isc::data;
using namespace isc::util::encode;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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

TranslatorBasic::TranslatorBasic(S_Session session, const string& model)
    : session_(session), model_(model) {
}

TranslatorBasic::~TranslatorBasic() {
}

ElementPtr
TranslatorBasic::value(S_Val s_val) {
    if (!s_val) {
        isc_throw(BadValue, "value called with null");
    }
    switch (s_val->type()) {
    case SR_CONTAINER_T:
    case SR_CONTAINER_PRESENCE_T:
        // Internal node.
        return (ElementPtr());

    case SR_LIST_T:
        return (Element::createList());

    case SR_STRING_T:
        return (Element::create(string(s_val->data()->get_string())));

    case SR_BOOL_T:
        return (Element::create(s_val->data()->get_bool() ? true : false));

    case SR_UINT8_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_uint8())));

    case SR_UINT16_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_uint16())));

    case SR_UINT32_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_uint32())));

    case SR_INT8_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_int8())));

    case SR_INT16_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_int16())));

    case SR_INT32_T:
        return (Element::create(static_cast<long long>(s_val->data()->get_int32())));

    case SR_IDENTITYREF_T:
        return (Element::create(string(s_val->data()->get_identityref())));

    case SR_ENUM_T:
        return (Element::create(string(s_val->data()->get_enum())));

    case SR_BINARY_T:
        return (Element::create(decode64(s_val->data()->get_binary())));

    default:
        isc_throw(NotImplemented,
                  "value called with unupported type: " << s_val->type());
    }
}

ElementPtr
TranslatorBasic::getItem(const string& xpath) {
    S_Val s_val;
    try {
        s_val = session_->get_item(xpath.c_str());
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError, "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }
    if (!s_val) {
        return (ElementPtr());
    }
    return (value(s_val));
}

ElementPtr
TranslatorBasic::getItems(const string& xpath) {
    S_Vals s_vals;
    try {
        s_vals = session_->get_items(xpath.c_str());
        if (!s_vals) {
            return (ElementPtr());
        }
        ElementPtr result = Element::createList();
        for (size_t i = 0; i < s_vals->val_cnt(); ++i) {
            S_Val s_val = s_vals->val(i);
            result->add(value(s_val));
        }
        return (result);
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting item at '" << xpath
                  << "': " << ex.what());
    }
}

S_Val
TranslatorBasic::value(ConstElementPtr elem, sr_type_t type) {
    if (!elem) {
        isc_throw(BadValue, "value called with null");
    }
    S_Val s_val;
    switch (type) {
    case SR_CONTAINER_T:
    case SR_CONTAINER_PRESENCE_T:
        isc_throw(NotImplemented, "value called for a container");

    case SR_LIST_T:
        if (elem->getType() != Element::list) {
            isc_throw(BadValue, "value for a list called with not a list: "
                      << elem->str());
        }
        // Return null.
        break;

    case SR_STRING_T:
    case SR_IDENTITYREF_T:
    case SR_ENUM_T:
        if (elem->getType() != Element::string) {
            isc_throw(BadValue,
                      "value for a string called with not a string: "
                      << elem->str());
        }
        s_val.reset(new Val(elem->stringValue().c_str(), type));
        break;

    case SR_BOOL_T:
        if (elem->getType() != Element::boolean) {
            isc_throw(BadValue,
                      "value for a boolean called with not a boolean: "
                      << elem->str());
        }
        s_val.reset(new Val(elem->boolValue(), type));
        break;

    case SR_UINT8_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<uint8_t>(elem->intValue()), type));
        break;

    case SR_UINT16_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<uint16_t>(elem->intValue()), type));
        break;

    case SR_UINT32_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<uint32_t>(elem->intValue()), type));
        break;

    case SR_INT8_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<int8_t>(elem->intValue()), type));
        break;

    case SR_INT16_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<int16_t>(elem->intValue()), type));
        break;

    case SR_INT32_T:
        if (elem->getType() != Element::integer) {
            isc_throw(BadValue,
                      "value for an integer called with not an integer: "
                      << elem->str());
        }
        s_val.reset(new Val(static_cast<int32_t>(elem->intValue()), type));
        break;

    case SR_BINARY_T:
        if (elem->getType() != Element::string) {
            isc_throw(BadValue,
                      "value for a base64 called with not a string: "
                      << elem->str());
        }
        s_val.reset(new Val(encode64(elem->stringValue()).c_str(), type));
        break;

    default:
        isc_throw(NotImplemented,
                  "value called with unupported type: " << type);
    }

    return (s_val);
}

void
TranslatorBasic::setItem(const string& xpath, ConstElementPtr elem,
                         sr_type_t type) {
    S_Val s_val = value(elem, type);
    if (!s_val && (type != SR_LIST_T)) {
        return;
    }
    try {
        session_->set_item(xpath.c_str(), s_val);
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting item '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorBasic::delItem(const std::string& xpath) {
    try {
        session_->delete_item(xpath.c_str());
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error deleting item at '"
                  << xpath << "': " << ex.what());
    }
}


S_Iter_Value
TranslatorBasic::getIter(const std::string& xpath) {
    return (session_->get_items_iter(xpath.c_str()));
}

string
TranslatorBasic::getNext(S_Iter_Value iter) {
    if (!iter) {
        isc_throw(BadValue, "getNext called with null");
    }
    S_Val s_val;
    try {
        s_val = session_->get_item_next(iter);
    } catch (const sysrepo_exception&) {
        // Should not happen according to the doc but still happen?
        return ("");
    }
    if (!s_val) {
        return ("");
    }
    return (s_val->xpath());
}

}; // end of namespace isc::yang
}; // end of namespace isc
