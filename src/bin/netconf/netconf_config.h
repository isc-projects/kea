// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_CONFIG_H
#define NETCONF_CONFIG_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <cc/simple_parser.h>
#include <http/url.h>
#include <exceptions/exceptions.h>

#include <boost/foreach.hpp>

#include <stdint.h>
#include <string>

namespace isc {
namespace netconf {

/// @file netconf_config.h
/// @brief A collection of classes for housing and parsing the application
/// configuration necessary for the Netconf application.
///
/// @note NetconfConfig is not here: this file contains component of
/// this class but not the class itself.
///
/// This file contains the class declarations for the class hierarchy created
/// from the Netconf configuration and the parser classes used to create it.
/// The application configuration consists of a list of managed server.
///
/// The parsing class hierarchy reflects this same scheme.  Working top down:
///
/// A ServerMapParser handles the managed servers map invoking a
/// ServerConfigParser to parse each server.
///
/// A ServerConfigParser handles the scalars which belong to the server as well
/// as creating and invoking a CtrlSocketParser to parse its control socket.
///
/// A CtrlSocketParser handles the scalars which belong to the control socket.
///
/// The following is sample configuration in JSON form with extra spacing
/// for clarity:
///
/// @code
/// {
///  "managed-servers" :
///  {
///    "dhcp4":
///    {
///      "model": "kea-dhcp4-server",
///      "control-socket":
///      {
///        "socket-type": "unix",
///        "socket-name": "/tmp/server-v4.sock"
///      }
///    }
///  }
/// }
/// @endcode

/// @brief Represents a Control Socket.
///
/// Acts as a storage class containing the basic attributes which
/// describe a Control Socket.
class CfgControlSocket : public isc::data::UserContext,
    public isc::data::CfgToElement {
public:
    /// @brief Defines the list of possible control socket types.
    enum Type {
        UNIX,    //< Unix socket.
        HTTP,    //< HTTP socket.
        STDOUT   //< standard output.
    };

    /// @brief Constructor.
    ///
    /// @param type The socket type.
    /// @param name The Unix socket name.
    /// @param url The HTTP server URL.
    CfgControlSocket(Type type, const std::string& name,
                     const isc::http::Url& url);

    /// @brief Destructor (doing nothing).
    virtual ~CfgControlSocket() = default;

    /// @brief Getter which returns the socket type.
    ///
    /// @return returns the socket type as a CfgControlSocket::Type.
    Type getType() const {
        return (type_);
    }

    /// @brief Getter which returns the Unix socket name.
    ///
    /// @return returns the Unix socket name as a std::string.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Getter which returns the HTTP server URL.
    ///
    /// @return returns the HTTP server URL as an isc::http::Url.
    const isc::http::Url getUrl() const {
        return (url_);
    }

    /// @brief Converts socket type name to CfgControlSocket::Type.
    ///
    /// @param type The type name.
    /// Currently supported values are "unix", "http" and "stdout".
    ///
    /// @return The CfgControlSocket::Type corresponding to the type name.
    /// @throw BadValue if the type name isn't recognized.
    static Type stringToType(const std::string& type);

    /// @brief Converts CfgControlSocket::Type to string.
    ///
    /// @param type The CfgControlSocket::Type type.
    /// @return The type name corresponding to the enumeration element.
    static const std::string typeToString(CfgControlSocket::Type type);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

private:
    /// @brief The socket type.
    Type type_;

    /// @brief The UNIX socket name.
    const std::string name_;

    /// @brief The HTTP server URL.
    const isc::http::Url url_;
};

/// @brief Defines a pointer for CfgControlSocket instances.
typedef boost::shared_ptr<CfgControlSocket> CfgControlSocketPtr;

/// @brief Represents a Managed CfgServer.
///
/// Acts as a storage class containing the basic attributes and
/// the Control Socket which describe a Managed CfgServer.
class CfgServer : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Constructor.
    ///
    /// @param model The model name.
    /// @param ctrl_sock The control socket.
    CfgServer(const std::string& model, CfgControlSocketPtr ctrl_sock);

    /// @brief Destructor (doing nothing).
    virtual ~CfgServer() = default;

    /// @brief Getter which returns the model name.
    ///
    /// @return returns the model name as a std::string
    const std::string getModel() const {
        return (model_);
    }

    /// @brief Getter which returns the control socket.
    ///
    /// @return returns the control socket as a CfgControlSocketPtr.
    const CfgControlSocketPtr& getCfgControlSocket() const {
        return (control_socket_);
    }

    /// @brief Getter which returns the boot-update flag.
    ///
    /// @return returns the boot-update flag as a bool.
    bool getBootUpdate() const {
        return (boot_update_);
    }

    /// @brief Set the boot-update flag.
    ///
    /// @param boot_update The boot-update flag.
    void setBootUpdate(bool boot_update) {
        boot_update_ = boot_update;
    }

    /// @brief Getter which returns the subscribe-changes flag.
    ///
    /// @return returns the subscribe-changes flag as a bool.
    bool getSubscribeChanges() const {
        return (subscribe_changes_);
    }

    /// @brief Getter which returns the subscribe-changes flag.
    ///
    /// @return returns the subscribe-changes flag as a bool.
    bool getSubscribeNotifications() const {
        return (subscribe_notifications_);
    }

    /// @brief Set the subscribe-changes flag.
    ///
    /// @param subscribe_changes The subscribe-changes flag.
    void setSubscribeChanges(bool subscribe_changes) {
        subscribe_changes_ = subscribe_changes;
    }

    /// @brief Set the subscribe-notifications flag.
    ///
    /// @param subscribe_notifications the subscribe-notifications flag
    void setSubscribeNotifications(bool subscribe_notifications) {
        subscribe_notifications_ = subscribe_notifications;
    }

    /// @brief Getter which returns the validate-changes flag.
    ///
    /// @return returns the validate-changes flag as a bool.
    bool getValidateChanges() const {
        return (validate_changes_);
    }

    /// @brief Set the validate-changes flag.
    ///
    /// @param validate_changes The validate-changes flag.
    void setValidateChanges(bool validate_changes) {
        validate_changes_ = validate_changes;
    }

    /// @brief Returns a text representation for the server.
    std::string toText() const;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

private:
    /// @brief The model name.
    const std::string model_;

    /// @brief The boot-update flag.
    ///
    /// If true (the default) Kea server configuration is updated at (netconf
    /// agent) boot time.
    bool boot_update_;

    /// @brief The subscribe-changes flag.
    ///
    /// If true (the default) the netconf agent subscribes module changes
    /// so will be notified when the YANG running configuration is changed.
    bool subscribe_changes_;

    /// @brief The subscribe-notifications flag.
    ///
    /// If true (the default) the netconf agent subscribes to the notifications
    /// API so it will be notified on various events like module installations
    /// and uninstallations.
    bool subscribe_notifications_;

    /// @brief The validate-changes flag.
    ///
    /// If true (the default) the netconf agent validates module changes
    /// and can reject bad configurations.
    bool validate_changes_;

    /// @brief The control socket.
    CfgControlSocketPtr control_socket_;
};

/// @brief Defines a pointer for CfgServer instances.
typedef boost::shared_ptr<CfgServer> CfgServerPtr;

/// @brief Defines a map of CfgServers, keyed by the name.
typedef std::map<std::string, CfgServerPtr> CfgServersMap;

/// @brief Defines a iterator pairing of name and CfgServer
typedef std::pair<std::string, CfgServerPtr> CfgServersMapPair;

/// @brief Defines a pointer to map of CfgServers.
typedef boost::shared_ptr<CfgServersMap> CfgServersMapPtr;

/// @brief Dumps the contents of a CfgServer as text to a output stream.
///
/// @param os The output stream to which text should be sent.
/// @param server The CfgServer instance to dump.
std::ostream& operator<<(std::ostream& os, const CfgServer& server);

/// @brief Parser for CfgControlSocket.
///
/// This class parses the configuration element "control-socket"
/// and creates an instance of a CfgControlSocket.
class ControlSocketConfigParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given "control-socket" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// CfgControlSocket, validates those entries, creates a CfgControlSocket
    /// instance.
    ///
    /// @param ctrl_sock_config is the "control-socket" configuration to parse.
    ///
    /// @return pointer to the new CfgControlSocket instance.
    CfgControlSocketPtr parse(data::ConstElementPtr ctrl_sock_config);
};

/// @brief Parser for CfgServer.
///
/// This class parses the configuration value from the "managed-servers" map
/// and creates an instance of a CfgServer.
class ServerConfigParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given value from
    /// the "managed-servers" map.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// CfgServer, validates those entries, creates a CfgServer instance.
    ///
    /// @param server_config is the value from the "managed-servers" map to parse.
    /// @return pointer to the new CfgServer instance.
    CfgServerPtr parse(data::ConstElementPtr server_config);
};

}  // namespace netconf
}  // namespace isc

#endif // NETCONF_CONFIG_H
