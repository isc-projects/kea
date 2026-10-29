// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_ROLE_H
#define RBAC_ROLE_H

#include <exceptions/exceptions.h>
#include <http/request.h>

namespace isc {
namespace rbac {

/// @brief Forward declaration of Role.
class Role;

/// @brief Type of shared pointers to Role.
typedef boost::shared_ptr<Role> RolePtr;

/// @brief Role assignment base class.
class Role {
public:

    /// @brief Constructor.
    ///
    /// @param name Name of the role assignment class.
    /// @throw Unexpected when name is empty.
    Role(const std::string& name) : name_(name) {
        if (name.empty()) {
            isc_throw(Unexpected, "empty role name");
        }
    }

    /// @brief Destructor.
    virtual ~Role() = default;

    /// @brief Returns the name.
    ///
    /// @return the name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Assign the role.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) = 0;

    /// @brief Setup HTTP library.
    ///
    /// @param load True if at load, false at unload.
    virtual void setup(bool load) = 0;

    /// @brief Require TLS.
    ///
    /// @param request The HTTP request.
    /// @return whether TLS is used.
    static bool requireTls(const http::HttpRequestPtr& request) {
        return (request && request->getTls());
    }

    /// @brief Parse a role assignment value.
    ///
    /// @param cfg Configuration of a role assignment.
    /// @return The role as specified by the configuration.
    static RolePtr parse(data::ConstElementPtr cfg);

protected:
    /// @brief The class name.
    std::string name_;
};

/// @brief Role assignment using the remote address.
class RemoteRole : public Role {
public:

    /// @brief Constructor.
    RemoteRole() : Role("remote") {
    }

    /// @brief Assign the role from the remote address.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (request->getRemote());
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    virtual void setup(bool) final {
    }
};

/// @brief Role assignment using the subject.
class SubjectRole : public Role {
public:

    /// @brief Constructor.
    SubjectRole() : Role("subject") {
    }

    /// @brief Assign the role from the remote subject.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (request->getSubject());
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    ///
    /// @param load True if at load, false at unload.
    virtual void setup(bool load) final {
        http::HttpRequest::recordSubject_ = load;
    }
};

/// @brief Role assignment using the issuer.
class IssuerRole : public Role {
public:

    /// @brief Constructor.
    IssuerRole() : Role("issuer") {
    }

    /// @brief Assign the role from the remote issuer.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (request->getIssuer());
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    ///
    /// @param load True if at load, false at unload.
    virtual void setup(bool load) final {
        http::HttpRequest::recordIssuer_ = load;
    }
};

/// @brief Role assignment using the basic HTTP authentication.
class BasicAuthRole : public Role {
public:

    /// @brief Constructor.
    BasicAuthRole() : Role("basic-auth") {
    }

    /// @brief Assign the role from the basic HTTP authentication.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (request->getBasicAuth());
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    ///
    /// @param load True if at load, false at unload.
    virtual void setup(bool load) final {
        http::HttpRequest::recordBasicAuth_ = load;
    }
};

/// @brief Role assignment using the custom value.
class CustomRole : public Role {
public:

    /// @brief Constructor.
    CustomRole() : Role("custom") {
    }

    /// @brief Assign the role from the remote custom value.
    ///
    /// @param request The HTTP request.
    /// @return the assigned role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (request->getCustom());
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    virtual void setup(bool) final {
    }
};

/// @brief Static role assignment.
class StaticRole : public Role {
public:

    /// @brief Constructor.
    ///
    /// @param role The static role.
    StaticRole(const std::string& role) : Role("static"), role_(role) {
    }

    /// @brief Assign the static role.
    ///
    /// @param request The HTTP request (unused).
    /// @return the assigned / static role.
    virtual std::string assign(const http::HttpRequestPtr& request) final {
        if (request) {
            return (role_);
        } else {
            return ("");
        }
    }

    /// @brief Setup HTTP library.
    virtual void setup(bool) final {
    }

    /// @brief Return the static role.
    ///
    /// @return the static role.
    std::string getRole() const {
        return (role_);
    }

private:
    /// @brief The static role.
    std::string role_;
};

} // end of namespace rbac
} // end of namespace isc
#endif
