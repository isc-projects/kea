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

#include "dhcp6/addr6.h"
#include "dhcp6/pkt6.h"
#include "dhcp6/iface_mgr.h"

using namespace std;
using namespace isc;

namespace {
class NakedIfaceMgr: public IfaceMgr {
    // "naked" Interface Manager, exposes internal fields 
public:
    NakedIfaceMgr() { }
    IfaceLst & getIfacesLst() { return ifaces_; }
    void setSendSock(int sock) { sendsock_ = sock; }
    void setRecvSock(int sock) { recvsock_ = sock; }
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
    EXPECT_EQ(0, ifacemgr->getIface("wifi0") );

    delete ifacemgr;
}

TEST_F(IfaceMgrTest, detectIfaces) {

    // test detects that interfaces can be detected 
    // there is no code for that now, but interfaces are
    // read from file
    fstream fakeifaces("interfaces.txt", ios::out);
    fakeifaces << "eth0 fe80::1234";
    fakeifaces.close();
    
    // this is not usable on systems that don't have eth0
    // interfaces. Nevertheless, this fake interface should
    // be on list, but if_nametoindex() will fail.
    
    IfaceMgr & ifacemgr = IfaceMgr::instance();
    
    ASSERT_TRUE( ifacemgr.getIface("eth0") != NULL );
    
    IfaceMgr::Iface * eth0 = ifacemgr.getIface("eth0");
    
    // there should be one address
    EXPECT_EQ(1, eth0->addrs_.size());
    
    Addr6 * addr = &(*eth0->addrs_.begin());
    ASSERT_TRUE( addr != NULL );
    
    EXPECT_STREQ( "fe80::1234", addr->getPlain().c_str() );
}

TEST_F(IfaceMgrTest, sockets) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    IfaceMgr & ifacemgr = IfaceMgr::instance();

    Addr6 loAddr("::1", true);

    // bind multicast socket to port 10547
    int socket1 = ifacemgr.openSocket("lo", loAddr, 10547, true);
    EXPECT_GT(socket1, 0); // socket > 0

    // bind unicast socket to port 10548
    int socket2 = ifacemgr.openSocket("lo", loAddr, 10548, false);
    EXPECT_GT(socket2, 0);

    // good to check that both sockets can be opened at once

    close(socket1);
    close(socket2);
}

TEST_F(IfaceMgrTest, sendReceive) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    // let's assume that every supported OS have lo interface
    Addr6 loAddr("::1", true);
    int socket1 = ifacemgr->openSocket("lo", loAddr, 10547, true);
    int socket2 = ifacemgr->openSocket("lo", loAddr, 10546, false);

    ifacemgr->setSendSock(socket2);
    ifacemgr->setRecvSock(socket1);

    Pkt6 sendPkt(128);

    // prepare dummy payload
    for (int i=0;i<128; i++) {
	sendPkt.data_[i] = i;
    }

    sendPkt.remote_port_ = 10547;
    sendPkt.remote_addr_ = Addr6("::1", true);
    sendPkt.ifindex_ = 1;
    sendPkt.iface_ = "lo";
    
    Pkt6 * rcvPkt;

    EXPECT_EQ(true, ifacemgr->send(sendPkt));

    rcvPkt = ifacemgr->receive();

    ASSERT_TRUE( rcvPkt != NULL ); // received our own packet

    // let's check that we received what was sent
    EXPECT_EQ(sendPkt.data_len_, rcvPkt->data_len_);
    EXPECT_EQ(0, memcmp(sendPkt.data_, rcvPkt->data_, rcvPkt->data_len_) );

    EXPECT_EQ(sendPkt.remote_addr_, rcvPkt->remote_addr_);
    EXPECT_EQ(rcvPkt->remote_port_, 10546);

    delete rcvPkt;

    delete ifacemgr;
}

}
