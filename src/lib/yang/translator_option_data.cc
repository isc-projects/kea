// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_data.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorOptionData::TranslatorOptionData(S_Session session,
                                           const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorOptionData::~TranslatorOptionData() {
}

ElementPtr
TranslatorOptionData::getOptionData(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option data at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionData not implemented for the model: " << model_);
}

ElementPtr
TranslatorOptionData::getOptionDataKea(const string& xpath) {
    ConstElementPtr code = getItem(xpath + "/code");
    ConstElementPtr space = getItem(xpath + "/space");
    if (!code || !space) {
        // Can't happen as code and space are the keys.
        isc_throw(Unexpected, "getOptionDataKea requires code and space: "
                  << xpath);
    }
    ElementPtr result = Element::createMap();
    result->set("code", code);
    result->set("space", space);
    ConstElementPtr name = getItem(xpath + "/name");
    if (name) {
        result->set("name", name);
    }
    ConstElementPtr data = getItem(xpath + "/data");
    if (data) {
        result->set("data", data);
    }
    ConstElementPtr format = getItem(xpath + "/csv-format");
    if (format) {
        result->set("csv-format", format);
    }
    ConstElementPtr send = getItem(xpath + "/always-send");
    if (send) {
        result->set("always-send", send);
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorOptionData::setOptionData(const string& xpath,
                                    ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setOptionDataKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setOptionData not implemented for the model: "
                      << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting option data '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorOptionData::setOptionDataKea(const string& xpath,
                                       ConstElementPtr elem) {
    // Skip keys code and space.
    ConstElementPtr name = elem->get("name");
    if (name) {
        setItem(xpath + "/name", name, SR_STRING_T);
    }
    ConstElementPtr data = elem->get("data");
    if (data) {
        setItem(xpath + "/data", data, SR_STRING_T);
    }
    ConstElementPtr format = elem->get("csv-format");
    if (format) {
        setItem(xpath + "/csv-format", format, SR_BOOL_T);
    }
    ConstElementPtr send = elem->get("always-send");
    if (send) {
        setItem(xpath + "/always-send", send, SR_BOOL_T);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
    }
}

TranslatorOptionDataList::TranslatorOptionDataList(S_Session session,
                                                   const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model) {
}

TranslatorOptionDataList::~TranslatorOptionDataList() {
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataList(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataListKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option data list at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDataList not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataListKea(const string& xpath) {
    return getList<TranslatorOptionData>(xpath + "/option-data", *this,
                                         &TranslatorOptionData::getOptionData);
}

void
TranslatorOptionDataList::setOptionDataList(const string& xpath,
                                            ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setOptionDataListKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setOptionDataList not implemented for the model: "
                      << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting option data list '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorOptionDataList::setOptionDataListKea(const string& xpath,
                                               ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr option = elem->get(i);
        if (!option->contains("code")) {
            isc_throw(BadValue, "option data without code: " << option->str());
        }
        unsigned code = static_cast<unsigned>(option->get("code")->intValue());
        if (!option->contains("space")) {
            isc_throw(BadValue, "option data without space: " <<option->str());
        }
        string space = option->get("space")->stringValue();
        ostringstream keys;
        keys << xpath << "/option-data[code='" << code
             << "'][space='" << space << "']";
        setOptionData(keys.str(), option);
    }
}

}  // namespace yang
}  // namespace isc
