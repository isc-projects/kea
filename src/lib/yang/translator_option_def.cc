// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_def.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorOptionDef::TranslatorOptionDef(Session session,
                                         const string& model)
    : Translator(session, model) {
}

ElementPtr
TranslatorOptionDef::getOptionDef(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDefKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting option definition:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDef not implemented for the model: " << model_);
}

ElementPtr
TranslatorOptionDef::getOptionDefFromAbsoluteXpath(string const& xpath) {
    try {
        return getOptionDef(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorOptionDef::getOptionDefKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "code");
    getMandatoryLeaf(result, data_node, "name");
    getMandatoryLeaf(result, data_node, "space");
    getMandatoryLeaf(result, data_node, "type");

    checkAndGetLeaf(result, data_node, "array");
    checkAndGetLeaf(result, data_node, "encapsulate");
    checkAndGetLeaf(result, data_node, "record-types");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    return (result->empty() ? ElementPtr() : result);
}

void
TranslatorOptionDef::setOptionDef(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setOptionDefKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setOptionDef not implemented for the model: "
                      << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting option definition '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionDef::setOptionDefKea(string const& xpath,
                                     ConstElementPtr elem) {
    // Skip keys "code" and "space".

    setMandatoryLeaf(elem, xpath, "name", LeafBaseType::String);
    setMandatoryLeaf(elem, xpath, "type", LeafBaseType::String);

    checkAndSetLeaf(elem, xpath, "array", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "encapsulate", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "record-types", LeafBaseType::String);

    checkAndSetUserContext(elem, xpath);
}

TranslatorOptionDefList::TranslatorOptionDefList(Session session,
                                                 const string& model)
    : Translator(session, model),
      TranslatorOptionDef(session, model) {
}

ConstElementPtr
TranslatorOptionDefList::getOptionDefList(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDefListKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting option definition list:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDefList not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorOptionDefList::getOptionDefListFromAbsoluteXpath(string const& xpath) {
    try {
        return getOptionDefList(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ConstElementPtr
TranslatorOptionDefList::getOptionDefListKea(DataNode const& data_node) {
    return getList<TranslatorOptionDef>(data_node, "option-def", *this,
                                        &TranslatorOptionDefList::getOptionDef);
}

void
TranslatorOptionDefList::setOptionDefList(string const& xpath,
                                          ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setOptionDefListKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setOptionDefList not implemented for the model: "
                      << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting option definition list '"
                  << elem->str() << "' : " << ex.what());
    }
}

void
TranslatorOptionDefList::setOptionDefListKea(string const& xpath,
                                             ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr def = elem->getNonConst(i);
        if (!def->contains("code")) {
            isc_throw(BadValue,
                      "option definition without code: " << def->str());
        }
        unsigned code = static_cast<unsigned>(def->get("code")->intValue());
        if (!def->contains("space")) {
            isc_throw(BadValue,
                      "option definition without space: " << def->str());
        }
        string space = def->get("space")->stringValue();
        ostringstream keys;
        keys << xpath << "/option-def[code='" << code
            << "'][space='" << space << "']";
        setOptionDef(keys.str(), def);
    }
}

}  // namespace yang
}  // namespace isc
