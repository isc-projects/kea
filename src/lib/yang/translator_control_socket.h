// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_CONTROL_SOCKET_H
#define ISC_TRANSLATOR_CONTROL_SOCKET_H 1

#include <yang/translator.h>
#include <list>

namespace isc {
namespace yang {

/// Control socket translation between YANG and JSON
///
/// JSON syntax for all Kea servers with command channel is:
/// @code
/// "control-socket": {
///     "socket-type": "<socket type>",
///     "socket-name": "<socket name>",
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax is:
/// @code
///  +--rw control-socket   container
///    |
///    +--rw socket-name    string
///    +--rw socket-type    enumeration
///    +--rw user-context?  string
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// {
///     "socket-name": "/tmp/kea.sock",
///     "socket-type": "unix",
///     "user-context": { "foo": 1 }
/// }
/// @endcode
/// @code
///  /kea-ctrl-agent:config (container)
///  /kea-ctrl-agent:config/control-sockets (container)
///  /kea-ctrl-agent:config/control-sockets/
///     socket[server-type='dhcp4'] (list instance)
///  /kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/
///     server-type = dhcp4
///  /kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/
///     control-socket (container)
///  /kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/
///     control-socket/socket-name = /tmp/kea.sock
///  /kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/
///     control-socket/socket-type = unix
///  /kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/
///     control-socket/user-context = { \"foo\": 1 }
/// @endcode

/// @brief A translator class for converting a control socket between
/// YANG and JSON.
///
/// Supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
/// - kea-dhcp-ddns
/// - kea-ctrl-agent
class TranslatorControlSocket : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorControlSocket(sysrepo::S_Session session,
                            const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorControlSocket();

    /// @brief Get and translate a control socket from YANG to JSON.
    ///
    /// @param xpath The xpath of the control socket.
    /// @return JSON representation of the control socket or null.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getControlSocket(const std::string& xpath);

    /// @brief Translate and set control socket from JSON to YANG.
    ///
    /// @param xpath The xpath of the control socket.
    /// @param elem The JSON element.
    void setControlSocket(const std::string& xpath,
                          isc::data::ConstElementPtr elem);

protected:
    /// @brief getControlSocket JSON for kea models.
    ///
    /// @param xpath The xpath of the control socket.
    /// @return JSON representation of the control socket.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getControlSocketKea(const std::string& xpath);

    /// @brief setControlSocket for kea models.
    ///
    /// Null elem argument removes the container.
    /// Required parameters passed in elem are: socket-name, socket-type.
    /// Optional parameters are: user-context.
    ///
    /// @param xpath The xpath of the control socket.
    /// @param elem The JSON element.
    /// @throw BadValue on control socket without socket type or name.
    void setControlSocketKea(const std::string& xpath,
                             isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_CONTROL_SOCKET_H
