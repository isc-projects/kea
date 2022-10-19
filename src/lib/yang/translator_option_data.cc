// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorOptionData::TranslatorOptionData(Session session,
                                           const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorOptionData::~TranslatorOptionData() {
}

ElementPtr
TranslatorOptionData::getOptionData(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option data:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionData not implemented for the model: " << model_);
}

ElementPtr
TranslatorOptionData::getOptionData(string const& xpath) {
    try {
        return getOptionData(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorOptionData::getOptionDataKea(DataNode const& data_node) {
    ConstElementPtr code = getItem(data_node, "code");
    ConstElementPtr space = getItem(data_node, "space");
    if (!code || !space) {
        // Can't happen as code and space are the keys.
        isc_throw(Unexpected, "getOptionDataKea requires code and space");
    }
    ElementPtr result = Element::createMap();
    result->set("code", code);
    result->set("space", space);
    ConstElementPtr name = getItem(data_node, "name");
    if (name) {
        result->set("name", name);
    }
    ConstElementPtr data = getItem(data_node, "data");
    if (data) {
        result->set("data", data);
    }
    ConstElementPtr format = getItem(data_node, "csv-format");
    if (format) {
        result->set("csv-format", format);
    }
    ConstElementPtr send = getItem(data_node, "always-send");
    if (send) {
        result->set("always-send", send);
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorOptionData::setOptionData(string const& xpath,
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
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting option data '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionData::setOptionDataKea(string const& xpath,
                                       ConstElementPtr elem) {
    // Skip keys code and space.
    ConstElementPtr name = elem->get("name");
    if (name) {
        setItem(xpath + "/name", name, LeafBaseType::String);
    }
    ConstElementPtr data = elem->get("data");
    if (data) {
        setItem(xpath + "/data", data, LeafBaseType::String);
    }
    ConstElementPtr format = elem->get("csv-format");
    if (format) {
        setItem(xpath + "/csv-format", format, LeafBaseType::Bool);
    }
    ConstElementPtr send = elem->get("always-send");
    if (send) {
        setItem(xpath + "/always-send", send, LeafBaseType::Bool);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

TranslatorOptionDataList::TranslatorOptionDataList(Session session,
                                                   const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model) {
}

TranslatorOptionDataList::~TranslatorOptionDataList() {
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataList(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataListKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option data list:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDataList not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataList(string const& xpath) {
    try {
        return getOptionDataList(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataListKea(DataNode const& data_node) {
    return getList<TranslatorOptionData>(data_node, "option-data", *this,
                                         &TranslatorOptionData::getOptionData);
}

void
TranslatorOptionDataList::setOptionDataList(string const& xpath,
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
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting option data list '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionDataList::setOptionDataListKea(string const& xpath,
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
