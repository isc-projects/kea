// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_COMMAND_CONFIG_H
#define UNIX_COMMAND_CONFIG_H

#include <asiolink/asiolink.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/unix_domain_socket.h>
#include <asiolink/unix_domain_socket_acceptor.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>

namespace isc {
namespace config {

/// @brief UNIX command config aka UNIX control socket info class.
class UnixCommandConfig : public isc::data::UserContext,
                          public isc::data::CfgToElement {
public:
    /// @brief Constructor.
    ///
    /// @param config Pointer to the configuration to parse.
    UnixCommandConfig(isc::data::ConstElementPtr config);

    /// @brief Virtual destructor.
    ~UnixCommandConfig() = default;

    /// @brief Returns socket type.
    ///
    /// @return The socket type ("unix").
    std::string getSocketType() const {
        return (socket_type_);
    }

    /// @brief Sets socket type.
    ///
    /// @param socket_type The new socket type (should be "unix").
    void setSocketType(const std::string& socket_type) {
        socket_type_ = socket_type;
    }

    /// @brief Returns socket name.
    ///
    /// @return The socket name.
    std::string getSocketName() const {
        return (socket_name_);
    }

    /// @brief Sets socket name.
    ///
    /// @param socket_name The new socket name.
    void setSocketName(const std::string& socket_name) {
        socket_name_ = socket_name;
    }

    /// @brief Returns the lock file name
    std::string getLockName() {
        return (std::string(socket_name_ + ".lock"));
    }

    /// @brief Unparse a configuration object.
    ///
    /// @return A pointer to configuration.
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Socket type ("unix").
    std::string socket_type_;

    /// @brief Path to the unix domain socket descriptor.
    ///
    /// This is used to remove the socket file once the connection terminates.
    std::string socket_name_;
};

/// @brief Pointer to a UnixCommandConfig object.
typedef boost::shared_ptr<UnixCommandConfig> UnixCommandConfigPtr;

/// @brief Structure used to store UNIX connection data.
/// (configuration, acceptor, etc.)
struct UnixSocketInfo {
    /// @brief Flag which indicates if socket can be reused.
    bool usable_;

    /// @brief File description to lock name file.
    int lock_fd_;

    /// @brief Pointer to the acceptor service.
    boost::shared_ptr<isc::asiolink::UnixDomainSocketAcceptor> acceptor_;

    /// @brief Pointer to the socket into which the new connection is accepted.
    boost::shared_ptr<isc::asiolink::UnixDomainSocket> socket_;

    /// @brief Pointer to the socket config.
    UnixCommandConfigPtr config_;

    /// @brief Constructor.
    UnixSocketInfo() : usable_(true), lock_fd_(-1) {
    }

    /// @brief Destructor.
    ~UnixSocketInfo() = default;
};

/// @brief Pointer to a UnixSocketInfo object.
typedef boost::shared_ptr<UnixSocketInfo> UnixSocketInfoPtr;

} // end of isc::config namespace
} // end of isc namespace
#endif
