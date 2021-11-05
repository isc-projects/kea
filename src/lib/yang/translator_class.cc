// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_class.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorClass::TranslatorClass(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model) {
}

TranslatorClass::~TranslatorClass() {
}

ElementPtr
TranslatorClass::getClass(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting client class at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getClass not implemented for the model: " << model_);
}

ElementPtr
TranslatorClass::getClassKea(const string& xpath) {
    ConstElementPtr name = getItem(xpath + "/name");
    if (!name) {
        // Can't happen as the name is the key.
        isc_throw(Unexpected, "getClassKea requires name: " << xpath);
    }
    ElementPtr result = Element::createMap();
    result->set("name", name);
    ConstElementPtr test = getItem(xpath + "/test");
    if (test) {
        result->set("test", test);
    }
    ConstElementPtr required = getItem(xpath + "/only-if-required");
    if (required) {
        result->set("only-if-required", required);
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    checkAndGetLeaf(result, xpath, "valid-lifetime");
    checkAndGetLeaf(result, xpath, "min-valid-lifetime");
    checkAndGetLeaf(result, xpath, "max-valid-lifetime");
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr defs = getOptionDefList(xpath);
        if (defs && (defs->size() > 0)) {
            result->set("option-def", defs);
        }
        ConstElementPtr next = getItem(xpath + "/next-server");
        if (next) {
            result->set("next-server", next);
        }
        ConstElementPtr hostname = getItem(xpath + "/server-hostname");
        if (hostname) {
            result->set("server-hostname", hostname);
        }
        ConstElementPtr boot = getItem(xpath + "/boot-file-name");
        if (boot) {
            result->set("boot-file-name", boot);
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndGetLeaf(result, xpath, "preferred-lifetime");
        checkAndGetLeaf(result, xpath, "min-preferred-lifetime");
        checkAndGetLeaf(result, xpath, "max-preferred-lifetime");
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorClass::setClass(const string& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setClassKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setClass not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting client class '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorClass::setClassKea(const string& xpath, ConstElementPtr elem) {
    bool created = false;
    // Skip key name.
    ConstElementPtr test = elem->get("test");
    if (test) {
        setItem(xpath + "/test", test, SR_STRING_T);
        created = true;
    }
    ConstElementPtr required = elem->get("only-if-required");
    if (required) {
        setItem(xpath + "/only-if-required", required, SR_BOOL_T);
        created = true;
    }
    ConstElementPtr options = elem->get("option-data");
    if (options) {
        setOptionDataList(xpath, options);
        created = true;
    }
    checkAndSetLeaf(elem, xpath, "valid-lifetime", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", SR_UINT32_T);
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr defs = elem->get("option-def");
        if (defs) {
            setOptionDefList(xpath, defs);
            created = true;
        }
        ConstElementPtr next = elem->get("next-server");
        if (next) {
            setItem(xpath + "/next-server", next, SR_STRING_T);
            created = true;
        }
        ConstElementPtr hostname = elem->get("server-hostname");
        if (hostname) {
            setItem(xpath + "/server-hostname", hostname, SR_STRING_T);
            created = true;
        }
        ConstElementPtr boot = elem->get("boot-file-name");
        if (boot) {
            setItem(xpath + "/boot-file-name", boot, SR_STRING_T);
            created = true;
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndSetLeaf(elem, xpath, "preferred-lifetime", SR_UINT32_T);
        checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", SR_UINT32_T);
        checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", SR_UINT32_T);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
        created = true;
    }
    // There is no mandatory fields outside the key so force creation.
    if (!created) {
        ConstElementPtr list = Element::createList();
        setItem(xpath, list, SR_LIST_T);
    }
}

TranslatorClasses::TranslatorClasses(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model),
      TranslatorClass(session, model) {
}

TranslatorClasses::~TranslatorClasses() {
}

ConstElementPtr
TranslatorClasses::getClasses(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassesKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting client classes at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getClasses not implemented for the model: " << model_);
}

ElementPtr
TranslatorClasses::getClassesKea(const string& xpath) {
    return getList<TranslatorClass>(xpath + "/client-class", *this,
                                    &TranslatorClass::getClass);
}

void
TranslatorClasses::setClasses(const string& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setClassesKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setClasses not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting client classes '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorClasses::setClassesKea(const string& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr cclass = elem->get(i);
        if (!cclass->contains("name")) {
            isc_throw(BadValue, "client class without name: " << elem->str());
        }
        string name = cclass->get("name")->stringValue();
        ostringstream key;
        key << xpath << "/client-class[name='" << name << "']";
        setClass(key.str(), cclass);
    }
}

}  // namespace yang
}  // namespace isc
