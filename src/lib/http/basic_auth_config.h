// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_BASIC_AUTH_CONFIG_H
#define HTTP_BASIC_AUTH_CONFIG_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <cc/user_context.h>
#include <http/basic_auth.h>
#include <list>
#include <unordered_map>

namespace isc {
namespace http {

/// @brief Type of basic HTTP authentication credential and user id map.
typedef std::unordered_map<std::string, std::string> BasicHttpAuthMap;

/// @brief Basic HTTP authentication client configuration.
class BasicHttpAuthClient : public isc::data::UserContext,
                            public isc::data::CfgToElement {
public:

    /// @brief Constructor.
    ///
    /// @param user User id
    /// @param password Password
    /// @param user_context Optional user context
    BasicHttpAuthClient(const std::string& user,
                        const std::string& password,
                        const isc::data::ConstElementPtr& user_context);

    /// @brief Returns the user id.
    const std::string& getUser() const {
        return (user_);
    }

    /// @brief Returns the password.
    const std::string& getPassword() const {
        return (password_);
    }

    /// @brief Unparses basic HTTP authentication client configuration.
    ///
    /// @return A pointer to unparsed client configuration.
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief The user id.
    std::string user_;

    /// @brief The password.
    std::string password_;
};

/// @brief Type of basic HTTP authentication client configuration list.
typedef std::list<BasicHttpAuthClient> BasicHttpAuthClientList;

/// @brief Basic HTTP authentication configuration.
class BasicHttpAuthConfig : public isc::data::CfgToElement {
public:

    /// @brief Add a client configuration.
    ///
    /// @param user User id
    /// @param password Password
    /// @param user_context Optional user context
    /// @throw BadValue if the user id contains the ':' character.
    void add(const std::string& user,
             const std::string& password,
             const isc::data::ConstElementPtr& user_context = isc::data::ConstElementPtr());

    /// @brief Clear configuration.
    void clear();

    /// @brief Returns the list of client configuration.
    ///
    /// @return List of basic HTTP authentication client configuration.
    const BasicHttpAuthClientList& getClientList() const {
        return (list_);
    }

    /// @brief Returns the credential and user id map.
    ///
    /// @return The basic HTTP authentication credential and user id map.
    const BasicHttpAuthMap& getCredentialMap() const {
        return (map_);
    }

    /// @brief Parses basic HTTP authentication configuration.
    ///
    /// @param config Element holding the basic HTTP authentication
    /// configuration to be parsed.
    /// @throw DhcpConfigError when the configuration is invalid.
    void parse(const isc::data::ConstElementPtr& config);

    /// @brief Unparses basic HTTP authentication configuration.
    ///
    /// @return A pointer to unparsed basic HTTP authentication configuration.
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief The list of basic HTTP authentication client configuration.
    BasicHttpAuthClientList list_;

    /// @brief The basic HTTP authentication credential and user id map.
    BasicHttpAuthMap map_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif // endif HTTP_BASIC_AUTH_CONFIG_H
