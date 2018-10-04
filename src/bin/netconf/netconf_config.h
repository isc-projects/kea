// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
/// A ServerMapParser handles the managed servers map invoking a ServerParser
/// to parse each server.
///
/// A ServerParser handles the scalars which belong to the server as well as
/// creating and invoking a CtrlSocketParser to parse its control socket.
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

/// @brief Exception thrown when the error during configuration handling
/// occurs.
class NetconfCfgError : public isc::Exception {
public:
    NetconfCfgError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents a Control Socket.
///
/// Acts as a storage class containing the basic attributes which
/// describe a Control Socket.
class ControlSocket : public isc::data::UserContext,
    public isc::data::CfgToElement {
public:
    /// @brief Defines the list of possible constrol socket types.
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
    ControlSocket(Type type, const std::string& name,
                  const isc::http::Url& url);

    /// @brief Destructor (doing nothing).
    virtual ~ControlSocket();

    /// @brief Getter which returns the socket type.
    ///
    /// @return returns the socket type as a ControlSocket::Type.
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

    /// @brief Converts socket type name to ControlSocket::Type.
    ///
    /// @param type The type name.
    /// Currently supported values are "unix", "http" and "stdout".
    ///
    /// @return The ControlSocket::Type corresponding to the type name.
    /// @throw BadValue if the type name isn't recognized.
    static Type stringToType(const std::string& type);

    /// @brief Converts ControlSocket::Type to string.
    ///
    /// @param type The ControlSocket::Type type.
    /// @return The type name corresponding to the enumeration element.
    static const std::string typeToString(ControlSocket::Type type);

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

/// @brief Defines a pointer for ControlSocket instances.
typedef boost::shared_ptr<ControlSocket> ControlSocketPtr;

/// @brief Represents a Managed Server.
///
/// Acts as a storage class containing the basic attributes and
/// the Control Socket which describe a Managed Server.
class Server : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Constructor.
    ///
    /// @param model The model name.
    /// @param ctrl_sock The control socket.
    Server(const std::string& model, ControlSocketPtr ctrl_sock);

    /// @brief Destructor (doing nothing).
    virtual ~Server();

    /// @brief Getter which returns the model name.
    ///
    /// @return returns the model name as a std::string
    const std::string getModel() const {
        return (model_);
    }

    /// @brief Getter which returns the control socket.
    ///
    /// @return returns the control socket as a ControlSocketPtr.
    const ControlSocketPtr& getControlSocket() const {
        return (control_socket_);
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

    /// @brief The control socket.
    ControlSocketPtr control_socket_;
};

/// @brief Defines a pointer for Server instances.
typedef boost::shared_ptr<Server> ServerPtr;

/// @brief Defines a map of Servers, keyed by the name.
typedef std::map<std::string, ServerPtr> ServersMap;

/// @brief Defines a iterator pairing of name and Server
typedef std::pair<std::string, ServerPtr> ServersMapPair;

/// @brief Defines a pointer to map of Servers.
typedef boost::shared_ptr<ServersMap> ServersMapPtr;

/// @brief Dumps the contents of a Server as text to a output stream.
///
/// @param os The output stream to which text should be sent.
/// @param server The Server instance to dump.
std::ostream& operator<<(std::ostream& os, const Server& server);

/// @brief Parser for ControlSocket.
///
/// This class parses the configuration element "control-socket"
/// and creates an instance of a ControlSocket.
class ControlSocketParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given "control-socket" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// ControlSocket, validates those entries, creates a ControlSocket
    /// instance.
    ///
    /// @param ctrl_sock_config is the "control-socket" configuration to parse.
    ///
    /// @return pointer to the new ControlSocket instance.
    ControlSocketPtr parse(data::ConstElementPtr ctrl_sock_config);
};

/// @brief Parser for Server.
///
/// This class parses the configuration value from the "managed-servers" map
/// and creates an instance of a Server.
class ServerParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given value from
    /// the "managed-servers" map.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// Server, validates those entries, creates a Server instance.
    ///
    /// @param server_config is the value from the "managed-servers" map to parse.
    /// @return pointer to the new Server instance.
    ServerPtr parse(data::ConstElementPtr server_config);
};

}; // end of isc::netconf namespace
}; // end of isc namespace

#endif // NETCONF_CONFIG_H
