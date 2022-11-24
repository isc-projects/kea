// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_database.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorDatabase::TranslatorDatabase(Session session, const string& model)
    : Translator(session, model) {
}

ElementPtr
TranslatorDatabase::getDatabase(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getDatabaseKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting database access: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getDatabase not implemented for the model: " << model_);
}

ElementPtr
TranslatorDatabase::getDatabaseFromAbsoluteXpath(string const& xpath) {
    try {
        return getDatabase(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorDatabase::getDatabaseKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryDivergingLeaf(result, data_node, "type", "database-type");

    checkAndGetLeaf(result, data_node, "cert-file");
    checkAndGetLeaf(result, data_node, "cipher-list");
    checkAndGetLeaf(result, data_node, "connect-timeout");
    checkAndGetLeaf(result, data_node, "host");
    checkAndGetLeaf(result, data_node, "key-file");
    checkAndGetLeaf(result, data_node, "lfc-interval");
    checkAndGetLeaf(result, data_node, "max-reconnect-tries");
    checkAndGetLeaf(result, data_node, "max-row-errors");
    checkAndGetLeaf(result, data_node, "name");
    checkAndGetLeaf(result, data_node, "on-fail");
    checkAndGetLeaf(result, data_node, "password");
    checkAndGetLeaf(result, data_node, "persist");
    checkAndGetLeaf(result, data_node, "port");
    checkAndGetLeaf(result, data_node, "readonly");
    checkAndGetLeaf(result, data_node, "reconnect-wait-time");
    checkAndGetLeaf(result, data_node, "trust-anchor");
    checkAndGetLeaf(result, data_node, "user");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    return (result->empty() ? ElementPtr() : result);
}

void
TranslatorDatabase::setDatabase(string const& xpath,
                                ConstElementPtr elem,
                                bool skip) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setDatabaseKea(xpath, elem, skip);
        } else {
            isc_throw(NotImplemented,
                      "setDatabase not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting database access '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorDatabase::setDatabaseKea(string const& xpath,
                                   ConstElementPtr elem,
                                   bool skip) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }

    checkAndSetLeaf(elem, xpath, "connect-timeout", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "cert-file", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "cipher-list", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "host", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "key-file", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "lfc-interval", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "max-reconnect-tries", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "max-row-errors", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "on-fail", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "password", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "persist", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "port", LeafBaseType::Uint16);
    checkAndSetLeaf(elem, xpath, "readonly", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reconnect-wait-time", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "trust-anchor", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "user", LeafBaseType::String);

    checkAndSetUserContext(elem, xpath);

    if (!skip) {
        setMandatoryDivergingLeaf(elem, xpath, "type", "database-type", LeafBaseType::String);
    }
}

TranslatorDatabases::TranslatorDatabases(Session session,
                                         const string& model)
    : Translator(session, model),
      TranslatorDatabase(session, model) {
}

ElementPtr
TranslatorDatabases::getDatabases(DataNode const& data_node,
                                  string const& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getDatabasesKea(data_node, xpath));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting database accesses: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getDatabases not implemented for the model: " << model_);
}

ElementPtr
TranslatorDatabases::getDatabasesFromAbsoluteXpath(string const& xpath) {
    try {
        return getDatabases(findXPath(xpath), xpath);
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorDatabases::getDatabasesKea(DataNode const& data_node, string const& xpath) {
    return getList<TranslatorDatabase>(data_node, xpath, *this,
                                       &TranslatorDatabase::getDatabase);
}

void
TranslatorDatabases::setDatabases(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setDatabasesKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setDatabases not implemented for the model: "
                      << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting database accesses '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorDatabases::setDatabasesKea(string const& xpath,
                                     ConstElementPtr elem) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr database = elem->getNonConst(i);
        if (!database->contains("type")) {
            isc_throw(BadValue, "database without type: " << database->str());
        }
        string type = database->get("type")->stringValue();
        ostringstream key;
        key << xpath << "[database-type='" << type << "']";
        setDatabase(key.str(), database, true);
    }
}

}  // namespace yang
}  // namespace isc
