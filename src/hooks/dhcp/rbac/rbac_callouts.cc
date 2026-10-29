// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks.h>
#include <http/post_request_json.h>
#include <process/daemon.h>

#include <rbac/rbac.h>
#include <rbac/rbac_config.h>
#include <rbac_log.h>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::log;
using namespace isc::process;
using namespace isc::rbac;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle.
/// @return 0 when initialization is successful, 1 otherwise.
int
load(LibraryHandle& handle) {
    try {
        // Make the hook library loadable by DHCP servers.
        const string& proc_name = Daemon::getProcName();
        if ((proc_name != "kea-dhcp4") && (proc_name != "kea-dhcp6") &&
            (proc_name != "kea-dhcp-ddns")) {
            isc_throw(Unexpected, "Bad process name: " << proc_name
                      << ", expected kea-dhcp4, kea-dhcp6 or kea-dhcp-ddns");
        }

        // Load the configuration.
        ConstElementPtr config = handle.getParameters();
        rbacConfig.init();
        Config::parse(config);
    } catch (const std::exception& ex) {
        LOG_ERROR(rbac_logger, RBAC_LOAD_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(rbac_logger, RBAC_LOAD_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int
unload() {
    if (roleAssign) {
        roleAssign->setup(false);
    }
    roleAssign.reset();
    roleConfigTable.clear();
    defaultRoleConfig.reset();
    unknownRoleConfig.reset();
    aclTable.clear();
    apiTable.clear();
    apiAccesses.clear();
    apiHooks.clear();
    responseFilterTable.clear();

    LOG_INFO(rbac_logger, RBAC_UNLOAD_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

/// @brief This callout is called at the "http_auth" callout.
///
/// @param handle CalloutHandle.
/// @return 0 upon success, non-zero otherwise.
int
http_auth(CalloutHandle& handle) {
    auto failwith = [](string msg) {
        LOG_INFO(rbac_logger, RBAC_HTTP_AUTH_FAILED)
            .arg(msg);
    };
    if (!roleAssign) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_AUTH_DISABLED);
        failwith("disabled: no role assigned");
        return (0);
    }

    // Get the parameters.
    HttpRequestPtr request;
    HttpResponseJsonPtr response;
    handle.getArgument("request", request);
    handle.getArgument("response", response);

    if (response) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_AUTH_RESPONSE)
            .arg(response->toBriefString());
        failwith("response already exists");
        return (0);
    }

    auto status_code = HttpStatusCode::FORBIDDEN;
    bool updated = false;
    try {
        // Most errors will be caught later.
        if (!request) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_NO_REQUEST);
            failwith("no request");
            return (0);
        }
        // Check TLS.
        if (rbacConfig.getRequireTls() && !Role::requireTls(request)) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_NO_TLS_REJECT);
            failwith("TLS required but not used");
            status_code = HttpStatusCode::UNAUTHORIZED;
            response = RoleConfig::createReject(request, status_code);
            updated = true;
            isc_throw(Unexpected, "local exit");
        }
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
        if (!request_json) {
            failwith("request is not a JSON one");
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_NO_JSON);
            return (0);
        }
        ConstElementPtr body = request_json->getBodyAsJson();
        if (!body) {
            failwith("request body is empty");
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_EMPTY_BODY);
            return (0);
        }
        if (body->getType() != Element::map) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_BAD_BODY_TYPE);
            failwith("request body is not a map");
            return (0);
        }
        ConstElementPtr elem = body->get(CONTROL_COMMAND);
        if (!elem) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_NO_COMMAND);
            failwith("no command found in request");
            return (0);
        }
        if (elem->getType() != Element::string) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_BAD_COMMAND_TYPE);
            failwith("request command is not a string");
            return (0);
        }
        string command = elem->stringValue();
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_AUTH_COMMAND)
            .arg(command);

        // Assign role.
        const string& role = roleAssign->assign(request);
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC, RBAC_TRACE_HTTP_AUTH_ROLE)
            .arg(role);
        RoleConfigPtr role_config = RoleConfig::getConfig(role);
        if (!role_config) {
            isc_throw(Unexpected, "can't find a role configuration");
        }

        // Filter command.
        if (role_config->match(command)) {
            LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                      RBAC_TRACE_HTTP_AUTH_ACCEPT)
                .arg(role_config->name_)
                .arg(role)
                .arg(command);
            if ((command == "config-set") || (command == "config-reload")) {
                // Ask the handle to be reset so the hook can be unloaded
                // without keeping a pointer to its address space...
                handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
            } else if (!role_config->response_filters_.empty()) {
                // Save values in the context for the response callout.
                handle.setContext("command", command);
                handle.setContext("role_config", role_config);
            }
        } else {
            LOG_INFO(rbac_logger, RBAC_HTTP_AUTH_REJECT)
                .arg(role_config->name_)
                .arg(role)
                .arg(command);
            response = RoleConfig::createReject(request, status_code);
            updated = true;
        }
    } catch (const std::exception& ex) {
        // Not updated means build an error message.
        if (!updated) {
            LOG_ERROR(rbac_logger, RBAC_HTTP_AUTH_ERROR)
                .arg(ex.what());
            status_code = HttpStatusCode::INTERNAL_SERVER_ERROR;
            response = RoleConfig::createReject(request, status_code);
            updated = true;
        }
    }

    // Set parameters.
    if (updated) {
        LOG_INFO(rbac_logger, RBAC_HTTP_AUTH_RESPONSE)
            .arg(response->toBriefString());
        handle.setArgument("response", response);
    }

    return (0);
}

/// @brief This callout is called at the "http_response" hook.
///
/// @param handle CalloutHandle.
/// @return 0 upon success, non-zero otherwise.
int
http_response(CalloutHandle& handle) {
    auto failwith = [](string msg) {
        LOG_INFO(rbac_logger, RBAC_HTTP_RESPONSE_FAILED)
            .arg(msg);
    };
    if (!roleAssign) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_DISABLED);
        failwith("disabled: no role assigned");
        return (0);
    }

    // Get the parameters.
    HttpRequestPtr request;
    HttpResponseJsonPtr response;
    handle.getArgument("request", request);
    handle.getArgument("response", response);

    if (!request || !response) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_NO_ARGUMENTS);
        if (!request && !response) {
            failwith("no request nor response");
        } else if (!request) {
            failwith("no request");
        } else {
            failwith("no response");
        }
        return (0);
    }

    // Decode response.
    ConstElementPtr body = response->getBodyAsJson();
    if (!body) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY);
        failwith("response body is empty");
        return (0);
    }
    if (body->getType() != Element::list) {
        // Should be an error response, anyway nothing to filter.
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_BAD_BODY_TYPE);
        failwith("response body is not a list");
        return (0);
    }
    if (body->size() < 1) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY_LIST);
        failwith("response body is an empty list");
        return (0);
    }

    // Recover command and role config;
    string command;
    RoleConfigPtr role_config;
    handle.getOptionalContext("command", command);
    handle.getOptionalContext("role_config", role_config);
    if (!role_config || (role_config->response_filters_.empty())) {
        return (0);
    }

    LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
              RBAC_TRACE_HTTP_RESPONSE_CONTEXT)
        .arg(command)
        .arg(role_config->name_);

    // Apply filters on each list item.
    bool modified = false;
    for (auto const& answer : body->listValue()) {
        if (role_config->filter(command, answer)) {
            modified = true;
        }
    }
    if (modified) {
        LOG_DEBUG(rbac_logger, DBGLVL_TRACE_BASIC,
                  RBAC_TRACE_HTTP_RESPONSE_MODIFIED);
        response->setBodyAsJson(body);
        response->resetContentLength();
    }

    return (0);
}

}
