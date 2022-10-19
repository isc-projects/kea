// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_def.h>
#include <yang/adaptor.h>
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
    : TranslatorBasic(session, model) {
}

TranslatorOptionDef::~TranslatorOptionDef() {
}

ElementPtr
TranslatorOptionDef::getOptionDef(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDefKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option definition:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDef not implemented for the model: " << model_);
}

ElementPtr
TranslatorOptionDef::getOptionDef(string const& xpath) {
    try {
        return getOptionDef(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorOptionDef::getOptionDefKea(DataNode const& data_node) {
    ConstElementPtr code = getItem(data_node, "code");
    ConstElementPtr name = getItem(data_node, "name");
    ConstElementPtr type = getItem(data_node, "type");
    ConstElementPtr space = getItem(data_node, "space");
    if (!code || !space) {
        // Can't happen as code and space are the keys.
        isc_throw(Unexpected, "getOptionDefKea requires code and space");
    }
    if (!name || !type) {
        isc_throw(BadValue, "getOptionDefKea requires name and type");
    }
    ElementPtr result = Element::createMap();
    result->set("code", code);
    result->set("name", name);
    result->set("type", type);
    result->set("space", getItem(data_node, "space"));
    ConstElementPtr record = getItem(data_node, "record-types");
    if (record) {
        result->set("record-types", record);
    }
    ConstElementPtr array = getItem(data_node, "array");
    if (array) {
        result->set("array", array);
    }
    ConstElementPtr encapsulate = getItem(data_node, "encapsulate");
    if (encapsulate) {
        result->set("encapsulate", encapsulate);
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
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
        isc_throw(SysrepoError,
                  "sysrepo error setting option definition '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorOptionDef::setOptionDefKea(string const& xpath,
                                     ConstElementPtr elem) {
    // Skip code and space as they are the keys.
    ConstElementPtr name = elem->get("name");
    if (!name) {
        isc_throw(BadValue, "option definition with name: " << elem->str());
    }
    setItem(xpath + "/name", name, LeafBaseType::String);
    ConstElementPtr type = elem->get("type");
    if (!type) {
        isc_throw(BadValue, "option definition with type: " << elem->str());
    }
    setItem(xpath + "/type", type, LeafBaseType::String);
    ConstElementPtr record = elem->get("record-types");
    if (record) {
        setItem(xpath + "/record-types", record, LeafBaseType::String);
    }
    ConstElementPtr array = elem->get("array");
    if (array) {
        setItem(xpath + "/array", array, LeafBaseType::Bool);
    }
    ConstElementPtr encapsulate = elem->get("encapsulate");
    if (encapsulate) {
        setItem(xpath + "/encapsulate", encapsulate, LeafBaseType::String);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

TranslatorOptionDefList::TranslatorOptionDefList(Session session,
                                                 const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionDef(session, model) {
}

TranslatorOptionDefList::~TranslatorOptionDefList() {
}

ConstElementPtr
TranslatorOptionDefList::getOptionDefList(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getOptionDefListKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting option definition list:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getOptionDefList not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorOptionDefList::getOptionDefList(string const& xpath) {
    try {
        return getOptionDefList(findXPath(xpath));
    } catch(SysrepoError const&) {
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
        isc_throw(SysrepoError,
                  "sysrepo error setting option definition list '"
                  << elem->str() << "' : " << ex.what());
    }
}

void
TranslatorOptionDefList::setOptionDefListKea(string const& xpath,
                                             ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr def = elem->get(i);
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
