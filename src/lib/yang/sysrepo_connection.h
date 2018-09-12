// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_CONNECTION_H
#define NETCONF_CONNECTION_H

#include <exceptions/exceptions.h>
#include <sysrepo-cpp/Session.h>

namespace isc {
namespace yang {

/// @brief Exception from the sysrepo library for connection.
class SysrepoConnectionError : public Exception {
public:
    SysrepoConnectionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Connection to the sysrepo library. Provision, i.e. currently unused.
class SysrepoConnection {
public:
    // @brief Constructor.
    SysrepoConnection();

    // @brief Destructor (closing connection).
    virtual ~SysrepoConnection();

    // @brief Get a connection and a session.
    void connect();

    // @brief Commit a session.
    void commit();

 private:
    // @brief The session.
    S_Session session_;
};

}  // sysrepo
}  // isc

#endif /* NETCONF_CONNECTION_H_ */
