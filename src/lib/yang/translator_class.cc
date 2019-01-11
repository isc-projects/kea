// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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
    S_Iter_Value iter = getIter(xpath + "/client-class");
    if (!iter) {
        // Can't happen.
        isc_throw(Unexpected, "getClassesKea: can't get iterator: " << xpath);
    }
    ElementPtr result = Element::createList();
    for (;;) {
        const string& cclass = getNext(iter);
        if (cclass.empty()) {
            break;
        }
        result->add(getClass(cclass));
    }
    if (result->size() > 0) {
        return (result);
    } else {
        return (ElementPtr());
    }
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

}; // end of namespace isc::yang
}; // end of namespace isc
