// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/basic_auth_config.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace http {

BasicHttpAuthClient::BasicHttpAuthClient(const std::string& user,
                                         const std::string& password,
                                         const isc::data::ConstElementPtr& user_context)
    : user_(user), password_(password) {
    if (user_context) {
        setContext(user_context);
    }
}

ElementPtr
BasicHttpAuthClient::toElement() const {
    ElementPtr result = Element::createMap();

    // Set user-context
    contextToElement(result);

    // Set user
    result->set("user", Element::create(user_));

    // Set password
    result->set("password", Element::create(password_));

    return (result);
}

void
BasicHttpAuthConfig::add(const std::string& user,
                         const std::string& password,
                         const ConstElementPtr& user_context) {
    BasicHttpAuth basic_auth(user, password);
    list_.push_back(BasicHttpAuthClient(user, password, user_context));
    map_[basic_auth.getCredential()] = user;
}

void
BasicHttpAuthConfig::clear() {
    list_.clear();
    map_.clear();
}

ElementPtr
BasicHttpAuthConfig::toElement() const {
    ElementPtr result = Element::createList();

    for (auto client : list_) {
        result->add(client.toElement());
    }

    return (result);
}

void
BasicHttpAuthConfig::parse(const ConstElementPtr& config) {
    if (!config) {
        return;
    }
    if (config->getType() != Element::list) {
        isc_throw(DhcpConfigError, "basic-authentications must be a list ("
                  << config->getPosition() << ")");
    }
    for (auto client : config->listValue()) {
        if (client->getType() != Element::map) {
            isc_throw(DhcpConfigError, "basic-authentications items must be "
                      << "maps (" << client->getPosition() << ")");
        }

        // user
        ConstElementPtr user_cfg = client->get("user");
        if (!user_cfg) {
            isc_throw(DhcpConfigError, "user is required in "
                      << "basic-authentications items ("
                      << client->getPosition() << ")");
        }
        if (user_cfg->getType() != Element::string) {
            isc_throw(DhcpConfigError, "user must be a string ("
                      << user_cfg->getPosition() << ")");
        }
        string user = user_cfg->stringValue();
        if (user.empty()) {
            isc_throw(DhcpConfigError, "user must be not be empty ("
                      << user_cfg->getPosition() << ")");
        }
        if (user.find(':') != string::npos) {
            isc_throw(DhcpConfigError, "user must not contain a ':': '"
                      << user << "' (" << user_cfg->getPosition() << ")");
        }

        // password
        string password;
        ConstElementPtr password_cfg = client->get("password");
        if (password_cfg) {
            if (password_cfg->getType() != Element::string) {
                isc_throw(DhcpConfigError, "password must be a string ("
                          << password_cfg->getPosition() << ")");
            }
            password = password_cfg->stringValue();
        }

        // user context
        ConstElementPtr user_context = client->get("user-context");
        if (user_context) {
            if (user_context->getType() != Element::map) {
                isc_throw(DhcpConfigError, "user-context must be a map ("
                          << user_context->getPosition() << ")");
            }
        }

        // add it.
        try {
            add(user, password, user_context);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << client->getPosition() << ")");
        }
    }
}

} // end of namespace isc::http
} // end of namespace isc
