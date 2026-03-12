// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_COMMAND_CONFIG_H
#define UNIX_COMMAND_CONFIG_H

#include <util/filesystem.h>
#include <string>

namespace isc {
namespace config {

/// @brief UNIX command config aka UNIX control socket info class.
class UnixCommandConfig {
public:
    /// @brief Defines the default permissions for unix socket parent directory.
    static const mode_t DEFAULT_SOCKET_PATH_PERMS;

    /// @brief Stores the default permissions for unix socket parent directory.
    static mode_t socket_path_perms_;

    /// @brief Constructor.
    UnixCommandConfig() = default;

    /// @brief Virtual destructor.
    ~UnixCommandConfig() = default;

    /// @brief Fetches the supported control socket path.
    ///
    /// The first call to this function with no arguments will set the default
    /// path to either the value of CONTROL_SOCKET_DIR or the environment
    /// variable KEA_CONTROL_SOCKET_DIR if it is defined. Subsequent calls with
    /// no arguments will simply return this value.
    ///
    /// @param reset recalculate when true, defaults to false.
    /// @param explicit_path set the default socket path to this value. This is
    /// for testing purposes only.
    ///
    /// @return String containing the default socket path.
    static std::string getSocketPath(bool reset = false,
                                     const std::string explicit_path = "");

    /// @brief Validates a path against the supported path for unix control
    /// sockets.
    ///
    /// @param socket_path path to validate.
    /// @param enforce enables validation against the supported path and
    /// permissions.
    /// If false simply returns the input path.
    ///
    /// @return validated path
    static std::string validatePath(const std::string socket_path,
                                    bool enforce = true);

    /// @brief Fetches the required socket path permissions mask
    ///
    /// @return permissions mask
    static mode_t getSocketPathPerms();

    /// @brief Sets the required socket path permissions mask
    ///
    /// This is for testing purposes only.
    /// @param perms permissions mask to use
    static void setSocketPathPerms(mode_t perms = DEFAULT_SOCKET_PATH_PERMS);
};

} // end of isc::config namespace
} // end of isc namespace
#endif
