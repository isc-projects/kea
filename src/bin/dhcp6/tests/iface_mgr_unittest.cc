// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "io_address.h"
#include "dhcp6/pkt6.h"
#include "dhcp6/iface_mgr.h"

using namespace std;
using namespace isc;
using namespace isc::asiolink;

namespace {
const char* const INTERFACE_FILE = TEST_DATA_BUILDDIR "/interfaces.txt";

class NakedIfaceMgr: public IfaceMgr {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedIfaceMgr() { }
    IfaceLst & getIfacesLst() { return ifaces_; }
    void setSendSock(int sock) { sendsock_ = sock; }
    void setRecvSock(int sock) { recvsock_ = sock; }

    int openSocket(const std::string& ifname,
                   const isc::asiolink::IOAddress& addr,
                   int port) {
        return IfaceMgr::openSocket(ifname, addr, port);
    }

};

// dummy class for now, but this will be expanded when needed
class IfaceMgrTest : public ::testing::Test {
public:
    IfaceMgrTest() {
    }
};

TEST_F(IfaceMgrTest, basic) {
    // checks that IfaceManager can be instantiated

    IfaceMgr & ifacemgr = IfaceMgr::instance();
    ASSERT_TRUE(&ifacemgr != 0);
}

TEST_F(IfaceMgrTest, ifaceClass) {
    // basic tests for Iface inner class

    IfaceMgr::Iface * iface = new IfaceMgr::Iface("eth5", 7);

    EXPECT_STREQ("eth5/7", iface->getFullName().c_str());

    delete iface;

}

// TODO: Implement getPlainMac() test as soon as interface detection is implemented.
TEST_F(IfaceMgrTest, getIface) {

    cout << "Interface checks. Please ignore socket binding errors." << endl;
    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    // interface name, ifindex
    IfaceMgr::Iface iface1("lo", 1);
    IfaceMgr::Iface iface2("eth5", 2);
    IfaceMgr::Iface iface3("en3", 5);
    IfaceMgr::Iface iface4("e1000g0", 3);

    ifacemgr->getIfacesLst().push_back(iface1);
    ifacemgr->getIfacesLst().push_back(iface2);
    ifacemgr->getIfacesLst().push_back(iface3);
    ifacemgr->getIfacesLst().push_back(iface4);

    // check that interface can be retrieved by ifindex
    IfaceMgr::Iface * tmp = ifacemgr->getIface(5);
    // ASSERT_NE(NULL, tmp); is not supported. hmmmm.
    ASSERT_TRUE( tmp != NULL );

    EXPECT_STREQ( "en3", tmp->name_.c_str() );
    EXPECT_EQ(5, tmp->ifindex_);

    // check that interface can be retrieved by name
    tmp = ifacemgr->getIface("lo");
    ASSERT_TRUE( tmp != NULL );

    EXPECT_STREQ( "lo", tmp->name_.c_str() );
    EXPECT_EQ(1, tmp->ifindex_);

    // check that non-existing interfaces are not returned
    EXPECT_EQ(static_cast<void*>(NULL), ifacemgr->getIface("wifi0") );

    delete ifacemgr;
}

TEST_F(IfaceMgrTest, detectIfaces) {

    // test detects that interfaces can be detected
    // there is no code for that now, but interfaces are
    // read from file
    fstream fakeifaces(INTERFACE_FILE, ios::out|ios::trunc);
    fakeifaces << "eth0 fe80::1234";
    fakeifaces.close();

    // this is not usable on systems that don't have eth0
    // interfaces. Nevertheless, this fake interface should
    // be on list, but if_nametoindex() will fail.

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    ASSERT_TRUE( ifacemgr->getIface("eth0") != NULL );

    IfaceMgr::Iface * eth0 = ifacemgr->getIface("eth0");

    // there should be one address
    EXPECT_EQ(1, eth0->addrs_.size());

    IOAddress * addr = &(*eth0->addrs_.begin());
    ASSERT_TRUE( addr != NULL );

    EXPECT_STREQ( "fe80::1234", addr->toText().c_str() );

    delete ifacemgr;
}

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
// Fix for this is available on 1186 branch, will reenable
// this test once 1186 is merged
TEST_F(IfaceMgrTest, DISABLED_sockets) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    IOAddress loAddr("::1");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket("lo", loAddr, 10547);
    EXPECT_GT(socket1, 0); // socket > 0

    // bind unicast socket to port 10548
    int socket2 = ifacemgr->openSocket("lo", loAddr, 10548);
    EXPECT_GT(socket2, 0);

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket3 = ifacemgr->openSocket("lo", loAddr, 10547);
    EXPECT_GT(socket3, 0); // socket > 0

    // we now have 3 sockets open at the same time. Looks good.

    close(socket1);
    close(socket2);
    close(socket3);

    delete ifacemgr;
}

TEST_F(IfaceMgrTest, socketsMcast) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    IOAddress loAddr("::1");
    IOAddress mcastAddr("ff02::1:2");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket("lo", mcastAddr, 10547);
    EXPECT_GT(socket1, 0); // socket > 0

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket2 = ifacemgr->openSocket("lo", mcastAddr, 10547);
    EXPECT_GT(socket2, 0);

    // there's no good way to test negative case here.
    // we would need non-multicast interface. We will be able
    // to iterate thru available interfaces and check if there
    // are interfaces without multicast-capable flag.

    close(socket1);
    close(socket2);

    delete ifacemgr;
}

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
// Fix for this is available on 1186 branch, will reenable
// this test once 1186 is merged
TEST_F(IfaceMgrTest, DISABLED_sendReceive) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    fstream fakeifaces(INTERFACE_FILE, ios::out|ios::trunc);
    fakeifaces << "lo ::1";
    fakeifaces.close();

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    // let's assume that every supported OS have lo interface
    IOAddress loAddr("::1");
    int socket1 = ifacemgr->openSocket("lo", loAddr, 10547);
    int socket2 = ifacemgr->openSocket("lo", loAddr, 10546);

    ifacemgr->setSendSock(socket2);
    ifacemgr->setRecvSock(socket1);

    Pkt6 sendPkt(128);

    // prepare dummy payload
    for (int i=0;i<128; i++) {
        sendPkt.data_[i] = i;
    }

    sendPkt.remote_port_ = 10547;
    sendPkt.remote_addr_ = IOAddress("::1");
    sendPkt.ifindex_ = 1;
    sendPkt.iface_ = "lo";

    Pkt6 * rcvPkt;

    EXPECT_EQ(true, ifacemgr->send(sendPkt));

    rcvPkt = ifacemgr->receive();

    ASSERT_TRUE( rcvPkt != NULL ); // received our own packet

    // let's check that we received what was sent
    EXPECT_EQ(sendPkt.data_len_, rcvPkt->data_len_);
    EXPECT_EQ(0, memcmp(&sendPkt.data_[0], &rcvPkt->data_[0],
                        rcvPkt->data_len_) );

    EXPECT_EQ(sendPkt.remote_addr_.toText(), rcvPkt->remote_addr_.toText());
    EXPECT_EQ(rcvPkt->remote_port_, 10546);

    delete rcvPkt;

    delete ifacemgr;
}

}
