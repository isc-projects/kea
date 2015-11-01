// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

const uint16_t TEST_PORT = 12345;

class TestIpc : public  Dhcp4o6IpcBase {
public:

    TestIpc(const uint16_t port, const int side);

    virtual void open();

    Pkt6Ptr getPktReceived() const {
        return (pkt_received_);
    }

private:

    void receiveHandler();

    uint16_t port_;
    int side_;
    Pkt6Ptr pkt_received_;

};

TestIpc::TestIpc(const uint16_t port, const int side)
    : port_(port), side_(side), pkt_received_() {
}

void
TestIpc::open() {
    socket_fd_ = Dhcp4o6IpcBase::open(port_, side_);
    if (socket_fd_ >= 0) {
        IfaceMgr::instance().addExternalSocket(socket_fd_,
                                               boost::bind(&TestIpc::receiveHandler, this));
    }
}

void
TestIpc::receiveHandler() {
    pkt_received_ = receive();
}

class Dhcp4o6IpcBaseTest : public ::testing::Test {
public:

    Dhcp4o6IpcBaseTest();

private:

    IfaceMgrTestConfig iface_mgr_test_config_;

};

Dhcp4o6IpcBaseTest::Dhcp4o6IpcBaseTest()
    : iface_mgr_test_config_(true) {
}

TEST_F(Dhcp4o6IpcBaseTest, basic) {
    TestIpc ipc4(TEST_PORT, 4);
    TestIpc ipc6(TEST_PORT, 6);

    ASSERT_NO_THROW(ipc4.open());
    ASSERT_NO_THROW(ipc6.open());

    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 1234));
    pkt->setIface("eth0");

    ASSERT_NO_THROW(ipc6.send(pkt));

    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));
    
    Pkt6Ptr pkt_received = ipc4.getPktReceived();
    ASSERT_TRUE(pkt_received);
}

} // end of anonymous namespace
