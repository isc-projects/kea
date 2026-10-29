// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <rbac/rbac.h>
#include <rbac/rbac_config.h>
#include <rbac_log.h>

using namespace isc;
using namespace isc::data;
using namespace isc::log;
using namespace isc::rbac;
using namespace std;

namespace isc {
namespace rbac {

Config rbacConfig;

const SimpleKeywords Config::RBAC_PARAMETERS = {
    { "access-control-lists",  Element::list },
    { "assign-role-method",    Element::string },
    { "api-files",             Element::string },
    { "commands",              Element::list },
    { "default-role",          Element::map },
    { "require-tls",           Element::boolean },
    { "roles",                 Element::list },
    { "unknown-role",          Element::map },
    { "comment",               Element::string }
};

const SimpleRequiredKeywords Config::RBAC_REQUIRED_PARAMETERS = {
    "api-files",
    "assign-role-method"
};

void
Config::init() {
    api_files_ = ".../share/kea/api";
    require_tls_ = false;
    Acl::initTable();
    ResponseFilter::initResponseFilterTable();
}

void
Config::parse(ConstElementPtr cfg) {
    if (!cfg) {
        isc_throw(BadValue, "null config");
    }
    if (cfg->getType() != Element::map) {
        isc_throw(BadValue, "config is not a map");
    }

    // Check keywords.
    SimpleParser::checkRequired(Config::RBAC_REQUIRED_PARAMETERS, cfg);
    SimpleParser::checkKeywords(Config::RBAC_PARAMETERS, cfg);

    // Role assignment method.
    roleAssign = Role::parse(cfg->get("assign-role-method"));
    if (!roleAssign) {
        isc_throw(Unexpected, "role assignment parsing failed");
    }
    roleAssign->setup(true);

    // Require TLS flag.
    ConstElementPtr require_tls = cfg->get("require-tls");
    if (require_tls) {
        rbacConfig.setRequireTls(require_tls->boolValue());
    } else if ((roleAssign->getName() == "subject") ||
               (roleAssign->getName() == "issuer")) {
        rbacConfig.setRequireTls(true);
    }

    // API files directory.
    const string& api_files = cfg->get("api-files")->stringValue();
    rbacConfig.setApiFiles(api_files);
    Api::fillApiTable(api_files);

    // Command definitions.
    ConstElementPtr commands = cfg->get("commands");
    if (commands) {
        size_t count(0);
        for (auto const& command : commands->listValue()) {
            Api::parse(command);
            ++count;
        }
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC, RBAC_CONFIGURED_COMMANDS)
            .arg(count);
    }

    // ACL definitions.
    ConstElementPtr acls = cfg->get("access-control-lists");
    if (acls) {
        size_t count(0);
        for (auto const& acl : acls->listValue()) {
            AliasAcl::parse(acl);
            ++count;
        }
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC, RBAC_CONFIGURED_ACLS)
            .arg(count);
    }

    // Roles definitions.
    ConstElementPtr roles = cfg->get("roles");
    if (roles) {
        size_t count(0);
        for (auto const& elem : roles->listValue()) {
            RoleConfigPtr role = RoleConfig::parse(elem);
            if (!role) {
                isc_throw(Unexpected, "role config parsing error for "
                          << elem->str());
            }
            const string& name = role->name_;
            if (roleConfigTable.count(name) != 0) {
                isc_throw(BadValue, "role '" << name
                          << "' is already defined");
            }
            roleConfigTable[name] = role;
            ++count;
        }
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC, RBAC_CONFIGURED_ROLES)
            .arg(count);
    }

    // Default role (use when role assignment returns the empty string).
    ConstElementPtr default_elem = cfg->get("default-role");
    if (default_elem) {
        defaultRoleConfig = RoleConfig::parse(default_elem, "default");
    } else {
        defaultRoleConfig.reset(new RoleConfig("default/reject",
                                               AclPtr(new NoneAcl()),
                                               AclPtr(new AllAcl()),
                                               false, true,
                                               ResponseFilterList()));
    }

    // Unknown role (use when role assignment returns a role not in the table).
    ConstElementPtr unknown_elem = cfg->get("unknown-role");
    if (unknown_elem) {
        unknownRoleConfig = RoleConfig::parse(unknown_elem, "unknown");
    } else {
        unknownRoleConfig.reset(new RoleConfig("unknown/reject",
                                               AclPtr(new NoneAcl()),
                                               AclPtr(new AllAcl()),
                                               false, true,
                                               ResponseFilterList()));
    }
}

} // end of namespace rbac
} // end of namespace isc
