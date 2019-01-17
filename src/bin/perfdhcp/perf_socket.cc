// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <perfdhcp/perf_socket.h>

#include <dhcp/iface_mgr.h>

#include <boost/foreach.hpp>


using namespace isc::dhcp;

namespace isc {
namespace perfdhcp {

PerfSocket::PerfSocket(const int socket) :
SocketInfo(asiolink::IOAddress("127.0.0.1"), 0, socket),
    ifindex_(0), valid_(true) {
    try {
        initSocketData();
    } catch (const Exception&) {
        valid_ = false;
    }
}

PerfSocket::~PerfSocket() {
    IfacePtr iface = IfaceMgr::instance().getIface(ifindex_);
    if (iface) {
        iface->delSocket(sockfd_);
    }
}

void
PerfSocket::initSocketData() {
    BOOST_FOREACH(IfacePtr iface, IfaceMgr::instance().getIfaces()) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            if (s.sockfd_ == sockfd_) {
                ifindex_ = iface->getIndex();
                addr_ = s.addr_;
                return;
            }
        }
    }
    isc_throw(BadValue, "interface for specified socket descriptor not found");
}

}
}
