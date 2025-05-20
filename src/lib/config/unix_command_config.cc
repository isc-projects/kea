// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/unix_command_config.h>
#include <util/filesystem.h>
#include <exceptions/exceptions.h>

using namespace isc;
using namespace isc::config;
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
UnixCommandConfig::validatePath(const std::string socket_path,
                                bool enforce /* = true */) {
    if (!socket_path_checker_) {
        getSocketPath();
    }

    auto valid_path = socket_path_checker_->validatePath(socket_path, enforce);
    if (enforce && !(socket_path_checker_->pathHasPermissions(socket_path_perms_))) {
        isc_throw (BadValue,
                   "socket path:" << socket_path_checker_->getPath()
                   << " does not exist or does not have permssions = "
                   << std::oct << socket_path_perms_);
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
