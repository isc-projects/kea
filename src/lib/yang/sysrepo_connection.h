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

class SysrepoConnectionError : public Exception {
public:
    SysrepoConnectionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class SysrepoConnection {
public:
    SysrepoConnection();
    virtual ~SysrepoConnection();
    void connect();

    void commit();

 private:
    S_Session session_;
};

}  // sysrepo
}  // isc

#endif /* NETCONF_CONNECTION_H_ */
