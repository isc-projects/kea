// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

// @brief Between Yang and JSON translator class for the control socket.
class TranslatorControlSocket : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorControlSocket(S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorControlSocket();

    /// @brief Get and translate a control socket from Yang to JSON.
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
    /// @param xpath The xpath of the control socket.
    /// @return JSON representation of the control socket.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getControlSocket(const std::string& xpath);

    /// @brief Translate and set control socket from JSON to Yang.
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
    /// Yang syntax is:
    /// @code
    ///  +--rw control-socket   container
    ///    |
    ///    +--rw socket-name    string
    ///    +--rw socket-type    enumeration
    ///    +--rw user-context?  string
    /// @endcode
    ///
    /// Null elem argument removes the container.
    ///
    /// @param xpath The xpath of the control socket.
    /// @param elem The JSON element.
    void setControlSocketKea(const std::string& xpath,
                             isc::data::ConstElementPtr elem);

    /// @brief The model.
    std::string model_;
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_CONTROL_SOCKET_H
