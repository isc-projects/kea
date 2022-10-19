// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorClass::TranslatorClass(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model) {
}

TranslatorClass::~TranslatorClass() {
}

ElementPtr
TranslatorClass::getClass(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting client class:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getClass not implemented for the model: " << model_);
}

ElementPtr
TranslatorClass::getClass(string const& xpath) {
    try {
        return getClass(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorClass::getClassKea(DataNode const& data_node) {
    ConstElementPtr name = getItem(data_node, "name");
    if (!name) {
        // Can't happen as the name is the key.
        isc_throw(Unexpected, "getClassKea requires name");
    }
    ElementPtr result = Element::createMap();
    result->set("name", name);
    ConstElementPtr test = getItem(data_node, "test");
    if (test) {
        result->set("test", test);
    }
    ConstElementPtr required = getItem(data_node, "only-if-required");
    if (required) {
        result->set("only-if-required", required);
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    checkAndGetLeaf(result, data_node, "valid-lifetime");
    checkAndGetLeaf(result, data_node, "min-valid-lifetime");
    checkAndGetLeaf(result, data_node, "max-valid-lifetime");
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr defs = getOptionDefList(data_node);
        if (defs && (defs->size() > 0)) {
            result->set("option-def", defs);
        }
        ConstElementPtr next = getItem(data_node, "next-server");
        if (next) {
            result->set("next-server", next);
        }
        ConstElementPtr hostname = getItem(data_node, "server-hostname");
        if (hostname) {
            result->set("server-hostname", hostname);
        }
        ConstElementPtr boot = getItem(data_node, "boot-file-name");
        if (boot) {
            result->set("boot-file-name", boot);
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndGetLeaf(result, data_node, "preferred-lifetime");
        checkAndGetLeaf(result, data_node, "min-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "max-preferred-lifetime");
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorClass::setClass(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setClassKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setClass not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting client class '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorClass::setClassKea(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    ConstElementPtr test = elem->get("test");
    if (test) {
        setItem(xpath + "/test", test, LeafBaseType::String);
    }
    ConstElementPtr required = elem->get("only-if-required");
    if (required) {
        setItem(xpath + "/only-if-required", required, LeafBaseType::Bool);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options) {
        setOptionDataList(xpath, options);
    }
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", LeafBaseType::Uint32);
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr defs = elem->get("option-def");
        if (defs) {
            setOptionDefList(xpath, defs);
        }
        ConstElementPtr next = elem->get("next-server");
        if (next) {
            setItem(xpath + "/next-server", next, LeafBaseType::String);
        }
        ConstElementPtr hostname = elem->get("server-hostname");
        if (hostname) {
            setItem(xpath + "/server-hostname", hostname, LeafBaseType::String);
        }
        ConstElementPtr boot = elem->get("boot-file-name");
        if (boot) {
            setItem(xpath + "/boot-file-name", boot, LeafBaseType::String);
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

TranslatorClasses::TranslatorClasses(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model),
      TranslatorClass(session, model) {
}

TranslatorClasses::~TranslatorClasses() {
}

ElementPtr
TranslatorClasses::getClasses(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassesKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting client classes:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getClasses not implemented for the model: " << model_);
}

ElementPtr
TranslatorClasses::getClasses(string const& xpath) {
    try {
        return getClasses(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorClasses::getClassesKea(DataNode const& data_node) {
    return getList<TranslatorClass>(data_node, "client-class", *this,
                                    &TranslatorClass::getClass);
}

void
TranslatorClasses::setClasses(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setClassesKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setClasses not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting client classes '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorClasses::setClassesKea(string const& xpath, ConstElementPtr elem) {
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
