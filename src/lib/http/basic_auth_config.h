// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_BASIC_AUTH_CONFIG_H
#define HTTP_BASIC_AUTH_CONFIG_H

#include <http/auth_config.h>
#include <http/basic_auth.h>
#include <list>
#include <unordered_map>

namespace isc {
namespace http {

/// @brief Type of basic HTTP authentication credential and user id map,
/// e.g. map["am9obmRvZTpzZWNyZXQx"] = "johndoe".
///
/// The map is used to verify a received credential: if it is not in it
/// the authentication fails, if it is in it the user id is logged.
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

    /// @brief The user id e.g. johndoe.
    std::string user_;

    /// @brief The password e.g. secret1.
    std::string password_;
};

/// @brief Type of basic HTTP authentication client configuration list.
typedef std::list<BasicHttpAuthClient> BasicHttpAuthClientList;

/// @brief Basic HTTP authentication configuration.
class BasicHttpAuthConfig : public HttpAuthConfig {
public:

    /// @brief Destructor.
    virtual ~BasicHttpAuthConfig() { }

    /// @brief Add a client configuration.
    ///
    /// @param user User id
    /// @param password Password
    /// @param user_context Optional user context
    /// @throw BadValue if the user id contains the ':' character.
    void add(const std::string& user,
             const std::string& password,
             const isc::data::ConstElementPtr& user_context = isc::data::ConstElementPtr());

    /// @brief Empty predicate.
    /// @return true if the configuration is empty so authentication
    /// is not required.
    virtual bool empty() const;

    /// @brief Clear configuration.
    virtual void clear();

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

    /// @brief Validate HTTP request.
    ///
    /// @param creator The HTTP response creator.
    /// @param request The HTTP request to validate.
    /// @return Error HTTP response if validation failed, null otherwise.
    virtual isc::http::HttpResponseJsonPtr
    checkAuth(const isc::http::HttpResponseCreator& creator,
              const isc::http::HttpRequestPtr& request) const;

private:

    /// @brief The list of basic HTTP authentication client configuration.
    BasicHttpAuthClientList list_;

    /// @brief The basic HTTP authentication credential and user id map.
    BasicHttpAuthMap map_;
};

/// @brief Type of shared pointers to basic HTTP authentication configuration.
typedef boost::shared_ptr<BasicHttpAuthConfig> BasicHttpAuthConfigPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif // endif HTTP_BASIC_AUTH_CONFIG_H
