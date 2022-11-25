// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_class.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorClass::TranslatorClass(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model) {
}

ElementPtr
TranslatorClass::getClass(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting client class:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getClass not implemented for the model: " << model_);
}

ElementPtr
TranslatorClass::getClassFromAbsoluteXpath(string const& xpath) {
    try {
        return getClass(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorClass::getClassKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "name");

    checkAndGetLeaf(result, data_node, "max-valid-lifetime");
    checkAndGetLeaf(result, data_node, "min-valid-lifetime");
    checkAndGetLeaf(result, data_node, "only-if-required");
    checkAndGetLeaf(result, data_node, "template-test");
    checkAndGetLeaf(result, data_node, "test");
    checkAndGetLeaf(result, data_node, "valid-lifetime");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    if (model_ == KEA_DHCP4_SERVER) {
        checkAndGetLeaf(result, data_node, "boot-file-name");
        checkAndGetLeaf(result, data_node, "next-server");
        checkAndGetLeaf(result, data_node, "server-hostname");

        ConstElementPtr defs = getOptionDefList(data_node);
        if (defs) {
            result->set("option-def", defs);
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndGetLeaf(result, data_node, "max-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "min-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "preferred-lifetime");
    }

    return (result->empty() ? ElementPtr() : result);
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
        isc_throw(NetconfError,
                  "setting client class '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorClass::setClassKea(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "only-if-required", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "template-test", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "test", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);

    ConstElementPtr options = elem->get("option-data");
    if (options) {
        setOptionDataList(xpath, options);
    }

    if (model_ == KEA_DHCP4_SERVER) {
        checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);

        ConstElementPtr defs = elem->get("option-def");
        if (defs) {
            setOptionDefList(xpath, defs);
        }
    } else if (model_ == KEA_DHCP6_SERVER) {
        checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
    }

    checkAndSetUserContext(elem, xpath);
}

TranslatorClasses::TranslatorClasses(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model),
      TranslatorClass(session, model) {
}

ElementPtr
TranslatorClasses::getClasses(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getClassesKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting client classes:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getClasses not implemented for the model: " << model_);
}

ElementPtr
TranslatorClasses::getClassesFromAbsoluteXpath(string const& xpath) {
    try {
        return getClasses(findXPath(xpath));
    } catch (NetconfError const&) {
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
        isc_throw(NetconfError,
                  "setting client classes '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorClasses::setClassesKea(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr cclass = elem->getNonConst(i);
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
