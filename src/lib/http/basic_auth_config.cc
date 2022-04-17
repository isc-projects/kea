// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/auth_log.h>
#include <http/basic_auth_config.h>
#include <util/file_utilities.h>
#include <util/strutil.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace isc {
namespace http {

BasicHttpAuthClient::BasicHttpAuthClient(const std::string& user,
                                         const std::string& password,
                                         const isc::data::ConstElementPtr& user_context)
    : user_(user), user_file_(""), password_(password),
      password_file_(""), password_file_only_(false) {
    if (user_context) {
        setContext(user_context);
    }
}

BasicHttpAuthClient::BasicHttpAuthClient(const std::string& user,
                                         const std::string& user_file,
                                         const std::string& password,
                                         const std::string& password_file,
                                         bool password_file_only,
                                         const isc::data::ConstElementPtr& user_context)
    : user_(user), user_file_(user_file), password_(password),
      password_file_(password_file), password_file_only_(password_file_only) {
    if (user_context) {
        setContext(user_context);
    }
}

ElementPtr
BasicHttpAuthClient::toElement() const {
    ElementPtr result = Element::createMap();

    // Set user-context
    contextToElement(result);

    // Set password file or password.
    if (!password_file_.empty()) {
        result->set("password-file", Element::create(password_file_));
    } else {
        result->set("password", Element::create(password_));
    }

    // Set user-file or user.
    if (!password_file_only_) {
        if (!user_file_.empty()) {
            result->set("user-file", Element::create(user_file_));
        } else {
            result->set("user", Element::create(user_));
        }
    }

    return (result);
}

void
BasicHttpAuthConfig::add(const std::string& user,
                         const std::string& user_file,
                         const std::string& password,
                         const std::string& password_file,
                         bool password_file_only,
                         const ConstElementPtr& user_context) {
    BasicHttpAuth basic_auth(user, password);
    list_.push_back(BasicHttpAuthClient(user, user_file, password,
                                        password_file, password_file_only,
                                        user_context));
    map_[basic_auth.getCredential()] = user;
}

void
BasicHttpAuthConfig::clear() {
    list_.clear();
    map_.clear();
}

bool
BasicHttpAuthConfig::empty() const {
    return (map_.empty());
}

string
BasicHttpAuthConfig::getFileContent(const std::string& file_name) const {
    // Build path.
    string path = getDirectory();
    // Add a trailing '/' if the last character is not already a '/'.
    if (path.empty() || (path[path.size() - 1] != '/')) {
        path += "/";
    }
    // Don't add a second '/'.
    if (file_name.empty() || (file_name[0] != '/')) {
        path += file_name;
    } else {
        path += file_name.substr(1);
    }

    try {
        return (file::getContent(path));
    } catch (const isc::BadValue& ex) {
        isc_throw(DhcpConfigError, ex.what());
    }
}

ElementPtr
BasicHttpAuthConfig::toElement() const {
    ElementPtr result = Element::createMap();

    // Set user-context
    contextToElement(result);

    // Set type
    result->set("type", Element::create(string("basic")));

    // Set realm
    result->set("realm", Element::create(getRealm()));

    // Set directory.
    result->set("directory", Element::create(getDirectory()));

    // Set clients
    ElementPtr clients = Element::createList();
    for (auto client : list_) {
        clients->add(client.toElement());
    }
    result->set("clients", clients);

    return (result);
}

void
BasicHttpAuthConfig::parse(const ConstElementPtr& config) {
    if (!config) {
        return;
    }
    if (config->getType() != Element::map) {
        isc_throw(DhcpConfigError, "authentication must be a map ("
                  << config->getPosition() << ")");
    }

    // Get and verify the type.
    ConstElementPtr type = config->get("type");
    if (!type) {
        isc_throw(DhcpConfigError, "type is required in authentication ("
                  << config->getPosition() << ")");
    }
    if (type->getType() != Element::string) {
        isc_throw(DhcpConfigError, "type must be a string ("
                  << type->getPosition() << ")");
    }
    if (type->stringValue() != "basic") {
        isc_throw(DhcpConfigError, "only basic HTTP authentication is "
                  << "supported: type is '" << type->stringValue()
                  << "' not 'basic' (" << type->getPosition() << ")");
    }

    // Get the realm.
    ConstElementPtr realm = config->get("realm");
    if (realm) {
        if (realm->getType() != Element::string) {
            isc_throw(DhcpConfigError, "realm must be a string ("
                      << realm->getPosition() << ")");
        }
        setRealm(realm->stringValue());
    }

    // Get the directory.
    ConstElementPtr directory = config->get("directory");
    if (directory) {
        if (directory->getType() != Element::string) {
            isc_throw(DhcpConfigError, "directory must be a string ("
                      << directory->getPosition() << ")");
        }
        setDirectory(directory->stringValue());
    }

    // Get user context.
    ConstElementPtr user_context_cfg = config->get("user-context");
    if (user_context_cfg) {
        if (user_context_cfg->getType() != Element::map) {
            isc_throw(DhcpConfigError, "user-context must be a map ("
                      << user_context_cfg->getPosition() << ")");
        }
        setContext(user_context_cfg);
    }

    // Get clients.
    ConstElementPtr clients = config->get("clients");
    if (!clients) {
        return;
    }
    if (clients->getType() != Element::list) {
        isc_throw(DhcpConfigError, "clients must be a list ("
                  << clients->getPosition() << ")");
    }

    // Iterate on clients.
    for (auto client : clients->listValue()) {
        if (client->getType() != Element::map) {
            isc_throw(DhcpConfigError, "clients items must be maps ("
                      << client->getPosition() << ")");
        }

        // password.
        string password;
        ConstElementPtr password_cfg = client->get("password");
        if (password_cfg) {
            if (password_cfg->getType() != Element::string) {
                isc_throw(DhcpConfigError, "password must be a string ("
                          << password_cfg->getPosition() << ")");
            }
            password = password_cfg->stringValue();
        }

        // password file.
        string password_file;
        ConstElementPtr password_file_cfg = client->get("password-file");
        if (password_file_cfg) {
            if (password_cfg) {
                isc_throw(DhcpConfigError, "password ("
                          << password_cfg->getPosition()
                          << ") and password-file ("
                          << password_file_cfg->getPosition()
                          << ") are mutually exclusive");
            }
            if (password_file_cfg->getType() != Element::string) {
                isc_throw(DhcpConfigError, "password-file must be a string ("
                          << password_file_cfg->getPosition() << ")");
            }
            password_file = password_file_cfg->stringValue();
        }

        ConstElementPtr user_cfg = client->get("user");
        ConstElementPtr user_file_cfg = client->get("user-file");
        bool password_file_only = false;
        if (!user_cfg && !user_file_cfg) {
            if (password_file_cfg) {
                password_file_only = true;
            } else {
                isc_throw(DhcpConfigError, "user is required in clients "
                          << "items (" << client->getPosition() << ")");
            }
        }

        // user.
        string user;
        if (user_cfg) {
            if (user_file_cfg) {
                isc_throw(DhcpConfigError, "user (" << user_cfg->getPosition()
                          << ") and user-file ("
                          << user_file_cfg->getPosition()
                          << ") are mutually exclusive");
            }
            if (user_cfg->getType() != Element::string) {
                isc_throw(DhcpConfigError, "user must be a string ("
                          << user_cfg->getPosition() << ")");
            }
            user = user_cfg->stringValue();
            if (user.empty()) {
                isc_throw(DhcpConfigError, "user must not be empty ("
                          << user_cfg->getPosition() << ")");
            }
            if (user.find(':') != string::npos) {
                isc_throw(DhcpConfigError, "user must not contain a ':': '"
                          << user << "' (" << user_cfg->getPosition() << ")");
            }
        }

        // user file.
        string user_file;
        if (user_file_cfg) {
            if (user_file_cfg->getType() != Element::string) {
                isc_throw(DhcpConfigError, "user-file must be a string ("
                          << user_file_cfg->getPosition() << ")");
            }
            user_file = user_file_cfg->stringValue();
            user = getFileContent(user_file);
            if (user.empty()) {
                isc_throw(DhcpConfigError, "user must not be empty "
                          << "from user-file '" << user_file << "' ("
                          << user_file_cfg->getPosition() << ")");
            }
            if (user.find(':') != string::npos) {
                isc_throw(DhcpConfigError, "user must not contain a ':' "
                          << "from user-file '" << user_file << "' ("
                          << user_file_cfg->getPosition() << ")");
            }
        }

        // Solve password file.
        if (password_file_cfg) {
            if (password_file_only) {
                string content = getFileContent(password_file);
                auto pos = content.find(':');
                if (pos == string::npos) {
                    isc_throw(DhcpConfigError, "can't find the user id part "
                              << "in password-file '" << password_file << "' ("
                              << password_file_cfg->getPosition() << ")");
                }
                user = content.substr(0, pos);
                password = content.substr(pos + 1);
            } else {
                password = getFileContent(password_file);
            }
        }

        // user context.
        ConstElementPtr user_context = client->get("user-context");
        if (user_context) {
            if (user_context->getType() != Element::map) {
                isc_throw(DhcpConfigError, "user-context must be a map ("
                          << user_context->getPosition() << ")");
            }
        }

        // add it.
        try {
            add(user, user_file, password, password_file, password_file_only,
                user_context);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << client->getPosition() << ")");
        }
    }
}

HttpResponseJsonPtr
BasicHttpAuthConfig::checkAuth(const HttpResponseCreator& creator,
                               const HttpRequestPtr& request) const {
    const BasicHttpAuthMap& credentials = getCredentialMap();
    bool authentic = false;
    if (credentials.empty()) {
        authentic = true;
    } else try {
        string value = request->getHeaderValue("Authorization");
        // Trim space characters.
        value = str::trim(value);
        if (value.size() < 8) {
            isc_throw(BadValue, "header content is too short");
        }
        // Get the authentication scheme which must be "basic".
        string scheme = value.substr(0, 5);
        str::lowercase(scheme);
        if (scheme != "basic") {
            isc_throw(BadValue, "not basic authentication");
        }
        // Skip the authentication scheme name and space characters.
        value = value.substr(5);
        value = str::trim(value);
        // Verify the credential is in the list.
        const auto it = credentials.find(value);
        if (it != credentials.end()) {
            LOG_INFO(auth_logger, HTTP_CLIENT_REQUEST_AUTHORIZED)
                .arg(it->second);
            if (HttpRequest::recordBasicAuth_) {
                request->setBasicAuth(it->second);
            }
            authentic = true;
        } else {
            LOG_INFO(auth_logger, HTTP_CLIENT_REQUEST_NOT_AUTHORIZED);
            authentic = false;
        }
    } catch (const HttpMessageNonExistingHeader&) {
        LOG_INFO(auth_logger, HTTP_CLIENT_REQUEST_NO_AUTH_HEADER);
    } catch (const BadValue& ex) {
        LOG_INFO(auth_logger, HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER)
            .arg(ex.what());
    }
    if (authentic) {
        return (HttpResponseJsonPtr());
    }
    const string& realm = getRealm();
    const string& scheme = "Basic";
    HttpResponsePtr response =
        creator.createStockHttpResponse(request, HttpStatusCode::UNAUTHORIZED);
    response->reset();
    response->context()->headers_.push_back(
        HttpHeaderContext("WWW-Authenticate",
                          scheme + " realm=\"" + realm + "\""));
    response->finalize();
    return (boost::dynamic_pointer_cast<HttpResponseJson>(response));
}

} // end of namespace isc::http
} // end of namespace isc
