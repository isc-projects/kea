// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_AGENT_H
#define NETCONF_AGENT_H

#include <dhcpsrv/daemon.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/asiolink.h>

namespace isc {
namespace netconf {

    class NetconfAgent : public isc::dhcp::Daemon {
 public:
    NetconfAgent()
        :verbose_(false) {

    };

    bool run();

    void setVerbose(bool verbose) {
        verbose_ = verbose;
    }

    
private:

    bool connectSysrepo();

    bool connectControlSocket();

    /// @brief IOService object, used for all ASIO operations.
    isc::asiolink::IOService io_service_;

};

};
};


#endif

