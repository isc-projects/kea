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

/// @brief An exception thrown when connection with sysrepo is broken
class SysrepoConnectionError : public Exception {
public:
    SysrepoConnectionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief A class that represents a connection to Sysrepo
class SysrepoConnection {
public:

    /// @brief constructor
    ///
    /// Currently does nothing. You need to explicitly call connect()
    SysrepoConnection();

    /// @brief Destructor
    ///
    /// Discards any pending data, unlocks datastore and stops session.
    virtual ~SysrepoConnection();

    // @brief Get a connection and a session.
    void connect();

    /// @brief Commits any pending data.
    void commit();

 private:

    /// @brief pointer to a session
    ///
    /// May be null if the session is not established.
    S_Session session_;
};

}  // sysrepo
}  // isc

#endif /* NETCONF_CONNECTION_H_ */
