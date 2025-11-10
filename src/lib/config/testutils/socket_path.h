// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_CONFIG_TESTUTILS_SOCKET_TEST_H
#define ISC_CONFIG_TESTUTILS_SOCKET_TEST_H

#include <asiolink/asio_wrapper.h>
#include <asiolink/unix_domain_socket_endpoint.h>
#include <cc/data.h>
#include <config/unix_command_config.h>
#include <exceptions/exceptions.h>

#include <exception>
#include <string>

namespace isc {
namespace config {
namespace test {

/// @brief Struct exists only to avoid ODR violation of inline functions.
struct SocketPath {
    /// @brief Checks if socket name is too long.
    ///
    /// @param socket_name Socket name
    ///
    /// @return whether the socket name is too long
    static bool isTooLong(std::string const& socket_name) {
        try {
            std::string const validated_socket_name(UnixCommandConfig::validatePath(socket_name));
            isc::asiolink::UnixDomainSocketEndpoint endpoint(validated_socket_name);
        } catch (std::exception const& e) {
            // Check if it starts with it.
            std::string const search_for("name too long");
            if (std::string::npos != std::string(e.what()).find(search_for)) {
                return true;
            }
            // Alternative:
            // std::unordered_set<std::string> expected_errors {
            //     "File name too long",  // on some Linuxes: Debian, RHEL, Ubuntu
            //     "File name too long [system:36]",  // on some Linuxes: Arch, Fedora
            //     "File name too long [system:63]",  // on BSD
            //     "Filename too long [system:36]",  // on some Linuxes: Alpine
            // };
            // return (expected_errors.count(e.what()));
        }
        return false;
    }

    /// @brief Takes socket information from config and checks if its name is too long.
    ///
    /// @param config config without the top level entry
    ///
    /// @return whether the socket name is too long
    static bool isTooLongFromConfig(isc::data::ConstElementPtr const& config) {
        using isc::data::ConstElementPtr;
        using isc::data::Element;

        // Socket name too long?
        ConstElementPtr control_sockets(config->get("control-sockets"));
        bool too_long(false);
        if (control_sockets) {
            for (ConstElementPtr control_socket : control_sockets->listValue()) {
                ConstElementPtr socket_name(control_socket->get("socket-name"));
                ConstElementPtr socket_type(control_socket->get("socket-type"));
                if (socket_name && socket_name->getType() == Element::string && socket_type &&
                    socket_type->getType() == Element::string &&
                    socket_type->stringValue() == "unix") {
                    std::string const name(socket_name->stringValue());
                    too_long |= isTooLong(name);
                }
            }
        }
        return too_long;
    }

    /// @brief Returns socket file path to be used for tests.
    static std::string unixSocketFilePath() {
        return (UnixCommandConfig::getSocketPath() + "/test-socket");
    }

    /// @brief Removes unix socket descriptor.
    static void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
    }
};

}  // namespace test
}  // namespace config
}  // namespace isc

#endif  // ISC_CONFIG_TESTUTILS_SOCKET_TEST_H
