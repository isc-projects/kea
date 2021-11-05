// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_database.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorDatabase::TranslatorDatabase(S_Session session, const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorDatabase::~TranslatorDatabase() {
}

ElementPtr
TranslatorDatabase::getDatabase(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getDatabaseKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting database access at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getDatabase not implemented for the model: " << model_);
}

ElementPtr
TranslatorDatabase::getDatabaseKea(const string& xpath) {
    ConstElementPtr type = getItem(xpath + "/database-type");
    if (!type) {
        return (ElementPtr());
    }
    ElementPtr result = Element::createMap();
    result->set("type", type);
    ConstElementPtr user = getItem(xpath + "/user");
    if (user) {
        result->set("user", user);
    }
    ConstElementPtr password = getItem(xpath + "/password");
    if (password) {
        result->set("password", password);
    }
    ConstElementPtr host = getItem(xpath + "/host");
    if (host) {
        result->set("host", host);
    }
    ConstElementPtr name = getItem(xpath + "/name");
    if (name) {
        result->set("name", name);
    }
    ConstElementPtr persist = getItem(xpath + "/persist");
    if (persist) {
        result->set("persist", persist);
    }
    ConstElementPtr port = getItem(xpath + "/port");
    if (port) {
        result->set("port", port);
    }
    ConstElementPtr lfc_interval = getItem(xpath + "/lfc-interval");
    if (lfc_interval) {
        result->set("lfc-interval", lfc_interval);
    }
    ConstElementPtr readonly = getItem(xpath + "/readonly");
    if (readonly) {
        result->set("readonly", readonly);
    }
    ConstElementPtr connect_timeout = getItem(xpath + "/connect-timeout");
    if (connect_timeout) {
        result->set("connect-timeout", connect_timeout);
    }
    ConstElementPtr contact_points = getItem(xpath + "/contact-points");
    if (contact_points) {
        result->set("contact-points", contact_points);
    }
    ConstElementPtr keyspace = getItem(xpath + "/keyspace");
    if (keyspace) {
        result->set("keyspace", keyspace);
    }
    ConstElementPtr max_reconnect = getItem(xpath + "/max-reconnect-tries");
    if (max_reconnect) {
        result->set("max-reconnect-tries", max_reconnect);
    }
    ConstElementPtr reconnect_time = getItem(xpath + "/reconnect-wait-time");
    if (reconnect_time) {
        result->set("reconnect-wait-time", reconnect_time);
    }
    ConstElementPtr request_timeout = getItem(xpath + "/request-timeout");
    if (request_timeout) {
        result->set("request-timeout", request_timeout);
    }
    ConstElementPtr keepalive = getItem(xpath + "/tcp-keepalive");
    if (keepalive) {
        result->set("tcp-keepalive", keepalive);
    }
    ConstElementPtr nodelay = getItem(xpath + "/tcp-nodelay");
    if (nodelay) {
        result->set("tcp-nodelay", nodelay);
    }
    ConstElementPtr consistency = getItem(xpath + "/consistency");
    if (consistency) {
        result->set("consistency", consistency);
    }
    ConstElementPtr serial_consistency = getItem(xpath + "/serial-consistency");
    if (serial_consistency) {
        result->set("serial-consistency", serial_consistency);
    }
    ConstElementPtr max_row_errors = getItem(xpath + "/max-row-errors");
    if (max_row_errors) {
        result->set("max-row-errors", max_row_errors);
    }
    checkAndGetLeaf(result, xpath, "on-fail");
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorDatabase::setDatabase(const string& xpath,
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting database access '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorDatabase::setDatabaseKea(const string& xpath,
                                   ConstElementPtr elem,
                                   bool skip) {
    if (!elem) {
        delItem(xpath);
        return;
    }
    if (!skip) {
        ConstElementPtr type = elem->get("type");
        if (!type) {
            isc_throw(BadValue, "setDatabase requires database type: "
                      << elem->str());
        }
        setItem(xpath + "/database-type", type, SR_STRING_T);
    }
    ConstElementPtr user = elem->get("user");
    if (user) {
        setItem(xpath + "/user", user, SR_STRING_T);
    }
    ConstElementPtr password = elem->get("password");
    if (password) {
        setItem(xpath + "/password", password, SR_STRING_T);
    }
    ConstElementPtr host = elem->get("host");
    if (host) {
        setItem(xpath + "/host", host, SR_STRING_T);
    }
    ConstElementPtr name = elem->get("name");
    if (name) {
        setItem(xpath + "/name", name, SR_STRING_T);
    }
    ConstElementPtr persist = elem->get("persist");
    if (persist) {
        setItem(xpath + "/persist", persist, SR_BOOL_T);
    }
    ConstElementPtr port = elem->get("port");
    if (port) {
        setItem(xpath + "/port", port, SR_UINT16_T);
    }
    ConstElementPtr lfc_interval = elem->get("lfc-interval");
    if (lfc_interval) {
        setItem(xpath + "/lfc-interval", lfc_interval, SR_UINT32_T);
    }
    ConstElementPtr readonly = elem->get("readonly");
    if (readonly) {
        setItem(xpath + "/readonly", readonly, SR_BOOL_T);
    }
    ConstElementPtr connect_timeout = elem->get("connect-timeout");
    if (connect_timeout) {
        setItem(xpath + "/connect-timeout", connect_timeout, SR_UINT32_T);
    }
    ConstElementPtr contact_points = elem->get("contact-points");
    if (contact_points) {
        setItem(xpath + "/contact-points", contact_points, SR_STRING_T);
    }
    ConstElementPtr keyspace = elem->get("keyspace");
    if (keyspace) {
        setItem(xpath + "/keyspace", keyspace, SR_STRING_T);
    }
    ConstElementPtr max_reconnect = elem->get("max-reconnect-tries");
    if (max_reconnect) {
        setItem(xpath + "/max-reconnect-tries", max_reconnect, SR_UINT32_T);
    }
    ConstElementPtr reconnect_wait = elem->get("reconnect-wait-time");
    if (reconnect_wait) {
        setItem(xpath + "/reconnect-wait-time", reconnect_wait, SR_UINT32_T);
    }
    ConstElementPtr request_timeout = elem->get("request-timeout");
    if (request_timeout) {
        setItem(xpath + "/request-timeout", request_timeout, SR_UINT32_T);
    }
    ConstElementPtr keepalive = elem->get("tcp-keepalive");
    if (keepalive) {
        setItem(xpath + "/tcp-keepalive", keepalive, SR_UINT32_T);
    }
    ConstElementPtr nodelay = elem->get("tcp-nodelay");
    if (nodelay) {
        setItem(xpath + "/tcp-nodelay", nodelay, SR_BOOL_T);
    }
    ConstElementPtr consistency = elem->get("consistency");
    if (consistency) {
        setItem(xpath + "/consistency", consistency, SR_STRING_T);
    }
    ConstElementPtr serial_consistency = elem->get("serial-consistency");
    if (serial_consistency) {
        setItem(xpath + "/serial-consistency", serial_consistency, SR_STRING_T);
    }
    ConstElementPtr max_row_errors = elem->get("max-row-errors");
    if (max_row_errors) {
        setItem(xpath + "/max-row-errors", max_row_errors, SR_UINT32_T);
    }
    checkAndSetLeaf(elem, xpath, "on-fail", SR_STRING_T);
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
    }
}

TranslatorDatabases::TranslatorDatabases(S_Session session,
                                         const string& model)
    : TranslatorBasic(session, model),
      TranslatorDatabase(session, model) {
}

TranslatorDatabases::~TranslatorDatabases() {
}

ConstElementPtr
TranslatorDatabases::getDatabases(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getDatabasesKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting database accesses at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getDatabases not implemented for the model: " << model_);
}

ElementPtr
TranslatorDatabases::getDatabasesKea(const string& xpath) {
    return getList<TranslatorDatabase>(xpath, *this,
                                       &TranslatorDatabase::getDatabase);
}

void
TranslatorDatabases::setDatabases(const string& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setDatabasesKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setDatabases not implemented for the model: "
                      << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting database accesses '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorDatabases::setDatabasesKea(const string& xpath,
                                     ConstElementPtr elem) {
    if (!elem) {
        delItem(xpath);
        return;
    }
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr database = elem->get(i);
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
