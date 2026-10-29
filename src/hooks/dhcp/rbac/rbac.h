// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_H
#define RBAC_H

#include <cc/simple_parser.h>

#include <rbac/rbac_acl.h>
#include <rbac/rbac_response_filter.h>
#include <rbac/rbac_role.h>

namespace isc {
namespace rbac {

/// @brief Forward declaration of RoleConfig.
class RoleConfig;

/// @brief Type of shared pointers to role configurations.
typedef boost::shared_ptr<RoleConfig> RoleConfigPtr;

/// @brief Type of the role configurations table.
typedef std::map<std::string, RoleConfigPtr> RoleConfigTable;

/// @brief Per role configuration class.
///
/// When a command does not match accept and reject ACLs it is an
/// other commands: true is for the accept action, false for the reject one.
/// When a command matches both accept and reject ACLs the preference true
/// follows the accept ACL, false the deny ACL.
class RoleConfig {
public:
    /// @brief Role configuration parameters.
    static const data::SimpleKeywords ROLE_PARAMETERS;

    /// @brief Constructor.
    ///
    /// @param name Role name.
    /// @param accept Accept commands access.
    /// @param reject Reject commands filter.
    /// @param others Action for other commands.
    /// @param preference Action for matching both commands.
    /// @param response_filters Response filters.
    RoleConfig(const std::string& name,
               const AclPtr& accept, const AclPtr& reject,
               bool others, bool preference,
               const ResponseFilterList& response_filters)
        : name_(name), accept_(accept), reject_(reject),
          others_(others), preference_(preference),
          response_filters_(response_filters) {
    }

    /// @brief Destructor.
    virtual ~RoleConfig() = default;

    /// @brief Role name.
    std::string name_;

    /// @brief Accept command access control list.
    AclPtr accept_;

    /// @brief Reject command access control list.
    AclPtr reject_;

    /// @brief Action for other commands.
    bool others_;

    /// @brief Action for both matching.
    bool preference_;

    /// @brief Response filters.
    ResponseFilterList response_filters_;

    /// @brief Match access control list.
    ///
    /// @param command The command.
    /// @return whether accept (true) or reject (false) the command.
    bool match(const std::string& command) const {
        if (preference_) {
            if (accept_ && accept_->match(command)) {
                return (true);
            }
            if (reject_ && reject_->match(command)) {
                return (false);
            }
        } else {
            if (reject_ && reject_->match(command)) {
                return (false);
            }
            if (accept_ && accept_->match(command)) {
                return (true);
            }
        }
        return (others_);
    }

    /// @brief Filter a response.
    ///
    /// @param command The command.
    /// @param body The JSON response body.
    /// @return whether the body was modified.
    bool filter(const std::string& command, data::ConstElementPtr body) const {
        bool modified = false;
        for (auto const& response_filter : response_filters_) {
            if (response_filter) {
                if (response_filter->filter(command, *this, body)) {
                    modified = true;
                }
            }
        }
        return (modified);
    }

    /// @brief Return the role config.
    ///
    /// @param role The role name.
    /// @return the role config, default if empty, unknown if not in table.
    static RoleConfigPtr getConfig(const std::string& role);

    /// @brief Parse a role config.
    ///
    /// @param cfg The role config.
    /// @param name The name (empty when to be get from the config).
    /// @return the parsed role config.
    static RoleConfigPtr parse(data::ConstElementPtr cfg,
                               std::string name = "");

    /// @brief Create a reject response.
    ///
    /// @param request The request.
    /// @param status_code The status code.
    static http::HttpResponseJsonPtr
    createReject(const http::HttpRequestPtr& request,
                 const http::HttpStatusCode& status_code);
};

/// @brief The role assignment.
extern RolePtr roleAssign;

/// @brief The role configurations table.
extern RoleConfigTable roleConfigTable;

/// @brief The default (role is "") role configuration.
extern RoleConfigPtr defaultRoleConfig;

/// @brief The unknown (role is not in the table) role configuration.
extern RoleConfigPtr unknownRoleConfig;

} // end of namespace rbac
} // end of namespace isc
#endif
