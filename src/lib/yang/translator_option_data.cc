// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_data.h>
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
    : Translator(session, model) {
}

ElementPtr
TranslatorOptionData::getOptionData(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting option data:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionData not implemented for the model: " << model_);
}

ElementPtr
TranslatorOptionData::getOptionDataFromAbsoluteXpath(string const& xpath) {
    try {
        return getOptionData(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorOptionData::getOptionDataKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    // Code and space must exist.
    getMandatoryLeaf(result, data_node, "code");
    getMandatoryLeaf(result, data_node, "space");

    // Data must exist according to the YANG module too, but empty data is considered no data.
    ElementPtr const& x(getItem(data_node, "data"));
    if (x && !x->stringValue().empty()) {
        result->set("data", x);
    }

    checkAndGetLeaf(result, data_node, "always-send");
    checkAndGetLeaf(result, data_node, "csv-format");
    checkAndGetLeaf(result, data_node, "name");
    checkAndGetLeaf(result, data_node, "never-send");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    return (result->empty() ? ElementPtr() : result);
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
        isc_throw(NetconfError,
                  "setting option data '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionData::setOptionDataKea(string const& xpath,
                                       ConstElementPtr elem) {
    // Set the list element. This is important in case we have no other elements except the keys.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    // Skip keys "code", "space", and "data" since they were set with the
    // list element in the call above with the LeafBaseType::Unknown parameter.

    checkAndSetLeaf(elem, xpath, "always-send", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "csv-format", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "never-send", LeafBaseType::Bool);

    checkAndSetUserContext(elem, xpath);
}

TranslatorOptionDataList::TranslatorOptionDataList(Session session,
                                                   const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model) {
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataList(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDataListKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting option data list:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDataList not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorOptionDataList::getOptionDataListFromAbsoluteXpath(string const& xpath) {
    try {
        return getOptionDataList(findXPath(xpath));
    } catch (NetconfError const&) {
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
        isc_throw(NetconfError,
                  "setting option data list '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionDataList::setOptionDataListKea(string const& xpath,
                                               ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr option = elem->getNonConst(i);

        // Code and space must exist in the input.
        if (!option->contains("code")) {
            isc_throw(BadValue, "option data without code: " << option->str());
        }
        unsigned code = static_cast<unsigned>(option->get("code")->intValue());
        if (!option->contains("space")) {
            isc_throw(BadValue, "option data without space: " << option->str());
        }
        string space = option->get("space")->stringValue();

        // Data must exist according to the YANG module too, but no data in the input is allowed and
        // converted to an empty string.
        string data;
        if (option->contains("data")) {
            data = option->get("data")->stringValue();
        }

        ostringstream keys;
        keys << xpath << "/option-data[code='" << code <<
                "'][space='" << space <<
                "'][data='" << data << "']";
        setOptionData(keys.str(), option);
    }
}

}  // namespace yang
}  // namespace isc
