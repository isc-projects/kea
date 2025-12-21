// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_asio_socket.h>
#include <cc/dhcp_config_error.h>
#include <config/command_mgr.h>
#include <config/config_log.h>
#include <config/unix_command_config.h>
#include <util/filesystem.h>
#include <limits>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util::file;
using namespace std;

namespace isc {
namespace config {

namespace {
    // Singleton PathChecker to set and hold valid unix socket path.
    PathCheckerPtr socket_path_checker_;
};

const mode_t UnixCommandConfig::DEFAULT_SOCKET_PATH_PERMS = (S_IRWXU | S_IRGRP | S_IXGRP);

mode_t UnixCommandConfig::socket_path_perms_ = UnixCommandConfig::DEFAULT_SOCKET_PATH_PERMS;

UnixCommandConfig::UnixCommandConfig(ConstElementPtr config)
    : socket_type_("unix"), socket_name_() {
    if (config->getType() != Element::map) {
        isc_throw(DhcpConfigError, "expected map type ("
                  << config->getPosition() << ")");
    }
    // Get socket type.
    ConstElementPtr socket_type = config->get("socket-type");
    if (socket_type) {
        if (socket_type->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket-type' ("
                      << socket_type->getPosition() << ")");
        }
        socket_type_ = socket_type->stringValue();
        if ((socket_type_ != "unix")) {
            isc_throw(DhcpConfigError, "unsupported 'socket-type' '"
                      << socket_type_ << "' not 'unix'");
        }
    }
    // Reject HTTP/HTTPS only socket-address.
    if (config->contains("socket-address")) {
        isc_throw(DhcpConfigError,
                  "parameter 'socket-address' is not supported by UNIX "
                  "control sockets");
    }
    // Get socket name.
    ConstElementPtr socket_name = config->get("socket-name");
    if (!socket_name) {
        isc_throw(DhcpConfigError, "Mandatory 'socket-name' parameter missing");
    }

    if (socket_name->getType() != Element::string) {
        isc_throw(DhcpConfigError,
                  "invalid type specified for parameter 'socket-name' ("
                  << socket_name->getPosition() << ")");
    }

    try {
        socket_name_ = validatePath(socket_name->stringValue());
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, "'socket-name' is invalid: " << ex.what());
    }

    // Get user context.
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        setContext(user_context);
    }
}

ElementPtr
UnixCommandConfig::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context.
    contextToElement(result);
    // Set socket type.
    result->set("socket-type", Element::create(socket_type_));
    // Set socket name.
    result->set("socket-name", Element::create(socket_name_));
    return (result);
}

std::string
UnixCommandConfig::getSocketPath(bool reset /* = false */,
                                 const std::string explicit_path /* = "" */) {
    if (!socket_path_checker_ || reset) {
        socket_path_checker_.reset(new PathChecker(CONTROL_SOCKET_DIR,
                                                   "KEA_CONTROL_SOCKET_DIR"));
        if (!explicit_path.empty()) {
            socket_path_checker_->getPath(true, explicit_path);
        }
    }

    return (socket_path_checker_->getPath());
}

std::string
UnixCommandConfig::validatePath(const std::string socket_path) {
    if (!socket_path_checker_) {
        getSocketPath();
    }

    std::string valid_path;
    try {
        valid_path = socket_path_checker_->validatePath(socket_path);
    } catch (const SecurityWarn& ex) {
        LOG_WARN(command_logger, COMMAND_UNIX_SOCKET_PATH_SECURITY_WARNING)
                .arg(ex.what());
        // Skip checking permissions.
        return(socket_path);
    }

    auto parent_path = socket_path_checker_->getPath();
    auto parent_perms = getPermissions(parent_path);
    if ((parent_perms & ~socket_path_perms_) != 0) {
        std::ostringstream oss;
        oss << "socket path:" << parent_path
            << " does not exist or does not have permssions less than "
            << std::oct << socket_path_perms_;

        if (PathChecker::shouldEnforceSecurity()) {
            isc_throw (DhcpConfigError, oss.str());
        }

        LOG_WARN(command_logger, COMMAND_UNIX_SOCKET_PERMISSIONS_SECURITY_WARNING)
                .arg(oss.str());
    }

    return (valid_path);
}

mode_t
UnixCommandConfig::getSocketPathPerms() {
    return (socket_path_perms_);
}

void
UnixCommandConfig::setSocketPathPerms(mode_t perms
                                      /* = DEFAULT_SOCKET_PATH_PERMS */) {
    socket_path_perms_ = perms;
}

} // end of isc::config
} // end of isc
