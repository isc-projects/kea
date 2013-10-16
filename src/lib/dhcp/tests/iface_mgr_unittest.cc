// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcp/pkt_filter.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using boost::scoped_ptr;

namespace {

// Name of loopback interface detection
const size_t BUF_SIZE = 32;
char LOOPBACK[BUF_SIZE] = "lo";

// Ports used during testing
const uint16_t PORT1 = 10547;   // V6 socket
const uint16_t PORT2 = 10548;   // V4 socket

// On some systems measured duration of receive6() and receive4() appears to be
// shorter than select() timeout.  This may be the case if different time
// resolutions are used by these functions.  For such cases we set the
// tolerance to 0.01s.
const uint32_t TIMEOUT_TOLERANCE = 10000;

/// Mock object implementing PktFilter class.  It is used by
/// IfaceMgrTest::setPacketFilter to verify that IfaceMgr::setPacketFilter
/// sets this object as a handler for opening sockets. This dummy
/// class simply records that openSocket function was called by
/// the IfaceMgr as expected.
///
/// @todo This class currently doesn't verify that send/receive functions
/// were called. In order to test it, there is a need to supply dummy
/// function performing select() on certain sockets. The system select()
/// call will fail when dummy socket descriptor is provided and thus
/// TestPktFilter::receive will never be called. The appropriate extension
/// to IfaceMgr is planned along with implementation of other "Packet
/// Filters" such as these supporting Linux Packet Filtering and
/// Berkley Packet Filtering.
class TestPktFilter : public PktFilter {
public:

    /// Constructor
    TestPktFilter()
        : open_socket_called_(false) {
    }

    virtual bool isDirectResponseSupported() const {
        return (false);
    }

    /// Pretends to open socket. Only records a call to this function.
    /// This function returns fake socket descriptor (always the same).
    /// Note that the returned value has been selected to be unique
    /// (because real values are rather less than 255). Values greater
    /// than 255 are not recommended because they cause warnings to be
    /// reported by Valgrind when invoking close() on them.
    virtual int openSocket(const Iface&,
                           const isc::asiolink::IOAddress&,
                           const uint16_t,
                           const bool,
                           const bool) {
        open_socket_called_ = true;
        return (255);
    }

    /// Does nothing
    virtual Pkt4Ptr receive(const Iface&,
                            const SocketInfo&) {
        return (Pkt4Ptr());
    }

    /// Does nothing
    virtual int send(const Iface&, uint16_t, const Pkt4Ptr&) {
        return (0);
    }

    /// Holds the information whether openSocket was called on this
    /// object after its creation.
    bool open_socket_called_;
};

class NakedIfaceMgr: public IfaceMgr {
    // "Naked" Interface Manager, exposes internal fields
public:
    NakedIfaceMgr() {
    }
    IfaceCollection & getIfacesLst() { return ifaces_; }
};

// Dummy class for now, but this will be expanded when needed
class IfaceMgrTest : public ::testing::Test {
public:
    // These are empty for now, but let's keep them around
    IfaceMgrTest() {
    }

    ~IfaceMgrTest() {
    }

    // Get ther number of IPv4 or IPv6 sockets on the loopback interface
    int getOpenSocketsCount(const Iface& iface, uint16_t family) const {
        // Get all sockets.
        Iface::SocketCollection sockets = iface.getSockets();

        // Loop through sockets and try to find the ones which match the
        // specified type.
        int sockets_count = 0;
        for (Iface::SocketCollection::const_iterator sock = sockets.begin();
             sock != sockets.end(); ++sock) {
            // Match found, increase the counter.
            if (sock->family_ == family) {
                ++sockets_count;
            }
        }
        return (sockets_count);
    }

    /// @brief returns socket bound to a specific address (or NULL)
    ///
    /// A helper function, used to pick a socketinfo that is bound to a given
    /// address.
    ///
    /// @param sockets sockets collection
    /// @param addr address the socket is bound to
    ///
    /// @return socket info structure (or NULL)
    const isc::dhcp::SocketInfo*
    getSocketByAddr(const isc::dhcp::Iface::SocketCollection& sockets,
                    const IOAddress& addr) {
        for (isc::dhcp::Iface::SocketCollection::const_iterator s =
                 sockets.begin(); s != sockets.end(); ++s) {
            if (s->addr_ == addr) {
                return (&(*s));
            }
        }
        return (NULL);
    }

};

// We need some known interface to work reliably. Loopback interface is named
// lo on Linux and lo0 on BSD boxes. We need to find out which is available.
// This is not a real test, but rather a workaround that will go away when
// interface detection is implemented.

// NOTE: At this stage of development, write access to current directory
// during running tests is required.
TEST_F(IfaceMgrTest, loDetect) {

    // Poor man's interface detection.  It will go away as soon as proper
    // interface detection is implemented
    if (if_nametoindex("lo") > 0) {
        snprintf(LOOPBACK, BUF_SIZE - 1, "lo");
    } else if (if_nametoindex("lo0") > 0) {
        snprintf(LOOPBACK, BUF_SIZE - 1, "lo0");
    } else {
        cout << "Failed to detect loopback interface. Neither "
             << "lo nor lo0 worked. I give up." << endl;
        FAIL();
    }
}

// Uncomment this test to create packet writer. It will
// write incoming DHCPv6 packets as C arrays. That is useful
// for generating test sequences based on actual traffic
//
// TODO: this potentially should be moved to a separate tool
//

#if 0
TEST_F(IfaceMgrTest, dhcp6Sniffer) {
    // Testing socket operation in a portable way is tricky
    // without interface detection implemented

    unlink("interfaces.txt");

    ofstream interfaces("interfaces.txt", ios::ate);
    interfaces << "eth0 fe80::21e:8cff:fe9b:7349";
    interfaces.close();

    boost::scoped_ptr<NakedIfaceMgr> ifacemgr = new NakedIfaceMgr();

    Pkt6Ptr pkt;
    int cnt = 0;
    cout << "---8X-----------------------------------------" << endl;
    while (true) {
        pkt.reset(ifacemgr->receive());

        cout << "// this code is autogenerated. Do NOT edit." << endl;
        cout << "// Received " << pkt->data_len_ << " bytes packet:" << endl;
        cout << "Pkt6 *capture" << cnt++ << "() {" << endl;
        cout << "    Pkt6* pkt;" << endl;
        cout << "    pkt = new Pkt6(" << pkt->data_len_ << ");" << endl;
        cout << "    pkt->remote_port_ = " << pkt-> remote_port_ << ";" << endl;
        cout << "    pkt->remote_addr_ = IOAddress(\""
             << pkt->remote_addr_.toText() << "\");" << endl;
        cout << "    pkt->local_port_ = " << pkt-> local_port_ << ";" << endl;
        cout << "    pkt->local_addr_ = IOAddress(\""
             << pkt->local_addr_.toText() << "\");" << endl;
        cout << "    pkt->ifindex_ = " << pkt->ifindex_ << ";" << endl;
        cout << "    pkt->iface_ = \"" << pkt->iface_ << "\";" << endl;

        // TODO it is better to declare statically initialize the array
        // and then memcpy it to packet.
        for (int i=0; i< pkt->data_len_; i++) {
            cout << "    pkt->data_[" << i << "]="
                 << (int)(unsigned char)pkt->data_[i] << "; ";
            if (!(i%4))
                cout << endl;
        }
        cout << endl;
        cout << "    return (pkt);" << endl;
        cout << "}" << endl << endl;

        pkt.reset();
    }
    cout << "---8X-----------------------------------------" << endl;

    // Never happens. Infinite loop is infinite
}
#endif

TEST_F(IfaceMgrTest, basic) {
    // Checks that IfaceManager can be instantiated

    IfaceMgr & ifacemgr = IfaceMgr::instance();
    ASSERT_TRUE(&ifacemgr != 0);
}


// This test verifies that sockets can be closed selectively, i.e. all
// IPv4 sockets can be closed first and all IPv6 sockets remain open.
TEST_F(IfaceMgrTest, closeSockets) {
    // Will be using local loopback addresses for this test.
    IOAddress loaddr("127.0.0.1");
    IOAddress loaddr6("::1");

    // Create instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Out constructor does not detect interfaces by itself. We need
    // to create one and add.
    int ifindex = if_nametoindex(LOOPBACK);
    ASSERT_GT(ifindex, 0);
    Iface lo_iface(LOOPBACK, ifindex);
    iface_mgr->getIfacesLst().push_back(lo_iface);

    // Create set of V4 and V6 sockets on the loopback interface.
    // They must differ by a port they are bound to.
    for (int i = 0; i < 6; ++i) {
        // Every other socket will be IPv4.
        if (i % 2) {
            ASSERT_NO_THROW(
                iface_mgr->openSocket(LOOPBACK, loaddr, 10000 + i)
            );
        } else {
            ASSERT_NO_THROW(
                iface_mgr->openSocket(LOOPBACK, loaddr6, 10000 + i)
            );
        }
    }

    // At the end we should have 3 IPv4 and 3 IPv6 sockets open.
    Iface* iface = iface_mgr->getIface(LOOPBACK);
    ASSERT_TRUE(iface != NULL);

    int v4_sockets_count = getOpenSocketsCount(*iface, AF_INET);
    ASSERT_EQ(3, v4_sockets_count);
    int v6_sockets_count = getOpenSocketsCount(*iface, AF_INET6);
    ASSERT_EQ(3, v6_sockets_count);

    // Let's try to close only IPv4 sockets.
    ASSERT_NO_THROW(iface_mgr->closeSockets(AF_INET));
    v4_sockets_count = getOpenSocketsCount(*iface, AF_INET);
    EXPECT_EQ(0, v4_sockets_count);
    // The IPv6 sockets should remain open.
    v6_sockets_count = getOpenSocketsCount(*iface, AF_INET6);
    EXPECT_EQ(3, v6_sockets_count);

    // Let's try to close IPv6 sockets.
    ASSERT_NO_THROW(iface_mgr->closeSockets(AF_INET6));
    v4_sockets_count = getOpenSocketsCount(*iface, AF_INET);
    EXPECT_EQ(0, v4_sockets_count);
    // They should have been closed now.
    v6_sockets_count = getOpenSocketsCount(*iface, AF_INET6);
    EXPECT_EQ(0, v6_sockets_count);
}

TEST_F(IfaceMgrTest, ifaceClass) {
    // Basic tests for Iface inner class

    Iface iface("eth5", 7);
    EXPECT_STREQ("eth5/7", iface.getFullName().c_str());
}

// TODO: Implement getPlainMac() test as soon as interface detection
// is implemented.
TEST_F(IfaceMgrTest, getIface) {

    cout << "Interface checks. Please ignore socket binding errors." << endl;
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Interface name, ifindex
    Iface iface1("lo1", 100);
    Iface iface2("eth9", 101);
    Iface iface3("en3", 102);
    Iface iface4("e1000g4", 103);
    cout << "This test assumes that there are less than 100 network interfaces"
         << " in the tested system and there are no lo1, eth9, en3, e1000g4"
         << " or wifi15 interfaces present." << endl;

    // Note: real interfaces may be detected as well
    ifacemgr->getIfacesLst().push_back(iface1);
    ifacemgr->getIfacesLst().push_back(iface2);
    ifacemgr->getIfacesLst().push_back(iface3);
    ifacemgr->getIfacesLst().push_back(iface4);

    cout << "There are " << ifacemgr->getIfacesLst().size()
         << " interfaces." << endl;
    for (IfaceMgr::IfaceCollection::iterator iface=ifacemgr->getIfacesLst().begin();
         iface != ifacemgr->getIfacesLst().end();
         ++iface) {
        cout << "  " << iface->getFullName() << endl;
    }


    // Check that interface can be retrieved by ifindex
    Iface* tmp = ifacemgr->getIface(102);
    ASSERT_TRUE(tmp != NULL);

    EXPECT_EQ("en3", tmp->getName());
    EXPECT_EQ(102, tmp->getIndex());

    // Check that interface can be retrieved by name
    tmp = ifacemgr->getIface("lo1");
    ASSERT_TRUE(tmp != NULL);

    EXPECT_EQ("lo1", tmp->getName());
    EXPECT_EQ(100, tmp->getIndex());

    // Check that non-existing interfaces are not returned
    EXPECT_EQ(static_cast<void*>(NULL), ifacemgr->getIface("wifi15") );
}

TEST_F(IfaceMgrTest, receiveTimeout6) {
    using namespace boost::posix_time;
    std::cout << "Testing DHCPv6 packet reception timeouts."
              << " Test will block for a few seconds when waiting"
              << " for timeout to occur." << std::endl;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    // Open socket on the lo interface.
    IOAddress loAddr("::1");
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547)
    );
    // Socket is open if result is non-negative.
    ASSERT_GE(socket1, 0);

    // Remember when we call receive6().
    ptime start_time = microsec_clock::universal_time();
    // Call receive with timeout of 1s + 400000us = 1.4s.
    Pkt6Ptr pkt;
    ASSERT_NO_THROW(pkt = ifacemgr->receive6(1, 400000));
    // Remember when call to receive6() ended.
    ptime stop_time = microsec_clock::universal_time();
    // We did not send a packet to lo interface so we expect that
    // nothing has been received and timeout has been reached.
    ASSERT_FALSE(pkt);
    // Calculate duration of call to receive6().
    time_duration duration = stop_time - start_time;
    // We stop the clock when the call completes so it does not
    // precisely reflect the receive timeout. However the
    // uncertainity should be low enough to expect that measured
    // value is in the range <1.4s; 1.7s>.
    EXPECT_GE(duration.total_microseconds(),
              1400000 - TIMEOUT_TOLERANCE);
    EXPECT_LE(duration.total_microseconds(), 1700000);

    // Test timeout shorter than 1s.
    start_time = microsec_clock::universal_time();
    ASSERT_NO_THROW(pkt = ifacemgr->receive6(0, 500000));
    stop_time = microsec_clock::universal_time();
    ASSERT_FALSE(pkt);
    duration = stop_time - start_time;
    // Check if measured duration is within <0.5s; 0.8s>.
    EXPECT_GE(duration.total_microseconds(),
              500000 - TIMEOUT_TOLERANCE);
    EXPECT_LE(duration.total_microseconds(), 800000);

    // Test with invalid fractional timeout values.
    EXPECT_THROW(ifacemgr->receive6(0, 1000000), isc::BadValue);
    EXPECT_THROW(ifacemgr->receive6(1, 1000010), isc::BadValue);
}

TEST_F(IfaceMgrTest, receiveTimeout4) {
    using namespace boost::posix_time;
    std::cout << "Testing DHCPv6 packet reception timeouts."
              << " Test will block for a few seconds when waiting"
              << " for timeout to occur." << std::endl;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    // Open socket on the lo interface.
    IOAddress loAddr("127.0.0.1");
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10067)
    );
    // Socket is open if returned value is non-negative.
    ASSERT_GE(socket1, 0);

    Pkt4Ptr pkt;
    // Remember when we call receive4().
    ptime start_time = microsec_clock::universal_time();
    // Call receive with timeout of 2s + 300000us = 2.3s.
    ASSERT_NO_THROW(pkt = ifacemgr->receive4(2, 300000));
    // Remember when call to receive4() ended.
    ptime stop_time = microsec_clock::universal_time();
    // We did not send a packet to lo interface so we expect that
    // nothing has been received and timeout has been reached.
    ASSERT_FALSE(pkt);
    // Calculate duration of call to receive4().
    time_duration duration = stop_time - start_time;
    // We stop the clock when the call completes so it does not
    // precisely reflect the receive timeout. However the
    // uncertainity should be low enough to expect that measured
    // value is in the range <2.3s; 2.6s>.
    EXPECT_GE(duration.total_microseconds(),
              2300000 - TIMEOUT_TOLERANCE);
    EXPECT_LE(duration.total_microseconds(), 2600000);

    // Test timeout shorter than 1s.
    start_time = microsec_clock::universal_time();
    ASSERT_NO_THROW(pkt = ifacemgr->receive4(0, 400000));
    stop_time = microsec_clock::universal_time();
    ASSERT_FALSE(pkt);
    duration = stop_time - start_time;
    // Check if measured duration is within <0.4s; 0.7s>.
    EXPECT_GE(duration.total_microseconds(),
              400000 - TIMEOUT_TOLERANCE);
    EXPECT_LE(duration.total_microseconds(), 700000);

    // Test with invalid fractional timeout values.
    EXPECT_THROW(ifacemgr->receive6(0, 1000000), isc::BadValue);
    EXPECT_THROW(ifacemgr->receive6(2, 1000005), isc::BadValue);
}

TEST_F(IfaceMgrTest, multipleSockets) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Container for initialized socket descriptors
    std::list<uint16_t> init_sockets;

    // Create socket #1
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocketFromIface(LOOPBACK, PORT1, AF_INET);
    );
    ASSERT_GE(socket1, 0);
    init_sockets.push_back(socket1);

    // Create socket #2
    IOAddress loAddr("127.0.0.1");
    int socket2 = 0;
    ASSERT_NO_THROW(
        socket2 = ifacemgr->openSocketFromRemoteAddress(loAddr, PORT2);
    );
    ASSERT_GE(socket2, 0);
    init_sockets.push_back(socket2);

    // Get loopback interface. If we don't find one we are unable to run
    // this test but we don't want to fail.
    Iface* iface_ptr = ifacemgr->getIface(LOOPBACK);
    if (iface_ptr == NULL) {
        cout << "Local loopback interface not found. Skipping test. " << endl;
        return;
    }
    // Once sockets have been sucessfully opened, they are supposed to
    // be on the list. Here we start to test if all expected sockets
    // are on the list and no other (unexpected) socket is there.
    Iface::SocketCollection sockets = iface_ptr->getSockets();
    int matched_sockets = 0;
    for (std::list<uint16_t>::iterator init_sockets_it =
             init_sockets.begin();
         init_sockets_it != init_sockets.end(); ++init_sockets_it) {
        // Set socket descriptors non blocking in order to be able
        // to call recv() on them without hang.
        int flags = fcntl(*init_sockets_it, F_GETFL, 0);
        ASSERT_GE(flags, 0);
        ASSERT_GE(fcntl(*init_sockets_it, F_SETFL, flags | O_NONBLOCK), 0);
        // recv() is expected to result in EWOULDBLOCK error on non-blocking
        // socket in case socket is valid but simply no data are coming in.
        char buf;
        recv(*init_sockets_it, &buf, 1, MSG_PEEK);
        EXPECT_EQ(EWOULDBLOCK, errno);
        // Apart from the ability to use the socket we want to make
        // sure that socket on the list is the one that we created.
        for (Iface::SocketCollection::const_iterator socket_it =
                 sockets.begin(); socket_it != sockets.end(); ++socket_it) {
            if (*init_sockets_it == socket_it->sockfd_) {
                // This socket is the one that we created.
                ++matched_sockets;
                break;
            }
        }
    }
    // All created sockets have been matched if this condition works.
    EXPECT_EQ(sockets.size(), matched_sockets);

    // closeSockets() is the other function that we want to test. It
    // is supposed to close all sockets so as we will not be able to use
    // them anymore communication.
    ifacemgr->closeSockets();

    // Closed sockets are supposed to be removed from the list
    sockets = iface_ptr->getSockets();
    ASSERT_EQ(0, sockets.size());

    // We are still in posession of socket descriptors that we created
    // on the beginning of this test. We can use them to check whether
    // closeSockets() only removed them from the list or they have been
    // really closed.
    for (std::list<uint16_t>::const_iterator init_sockets_it =
             init_sockets.begin();
         init_sockets_it != init_sockets.end(); ++init_sockets_it) {
        // recv() must result in error when using invalid socket.
        char buf;
        recv(*init_sockets_it, &buf, 1, MSG_PEEK);
        // EWOULDBLOCK would mean that socket is valid/open but
        // simply no data is received so we have to check for
        // other errors.
        EXPECT_NE(EWOULDBLOCK, errno);
    }
}

TEST_F(IfaceMgrTest, sockets6) {
    // Testing socket operation in a portable way is tricky
    // without interface detection implemented.

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    IOAddress loAddr("::1");

    Pkt6 pkt6(DHCPV6_SOLICIT, 123);
    pkt6.setIface(LOOPBACK);

    // Bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547);
    EXPECT_GE(socket1, 0); // socket >= 0

    EXPECT_EQ(socket1, ifacemgr->getSocket(pkt6));

    // Bind unicast socket to port 10548
    int socket2 = ifacemgr->openSocket(LOOPBACK, loAddr, 10548);
    EXPECT_GE(socket2, 0);

    // Removed code for binding socket twice to the same address/port
    // as it caused problems on some platforms (e.g. Mac OS X)

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();

    // Use address that is not assigned to LOOPBACK iface.
    IOAddress invalidAddr("::2");
    EXPECT_THROW(
        ifacemgr->openSocket(LOOPBACK, invalidAddr, 10547),
        SocketConfigError
    );

    // Use non-existing interface name.
    EXPECT_THROW(
        ifacemgr->openSocket("non_existing_interface", loAddr, 10548),
        BadValue
    );

    // Do not call closeSockets() because it is called by IfaceMgr's
    // virtual destructor.
}

TEST_F(IfaceMgrTest, socketsFromIface) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Open v6 socket on loopback interface and bind to port
    int socket1 = 0;
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocketFromIface(LOOPBACK, PORT1, AF_INET6);
    );
    // Socket descriptor must be non-negative integer
    EXPECT_GE(socket1, 0);
    close(socket1);

    // Open v4 socket on loopback interface and bind to different port
    int socket2 = 0;
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromIface(LOOPBACK, PORT2, AF_INET);
    );
    // socket descriptor must be non-negative integer
    EXPECT_GE(socket2, 0);
    close(socket2);

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();

    // Use invalid interface name.
    EXPECT_THROW(
        ifacemgr->openSocketFromIface("non_existing_interface", PORT1, AF_INET),
        BadValue
    );

    // Do not call closeSockets() because it is called by IfaceMgr's
    // virtual destructor.
}


TEST_F(IfaceMgrTest, socketsFromAddress) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Open v6 socket on loopback interface and bind to port
    int socket1 = 0;
    IOAddress loAddr6("::1");
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocketFromAddress(loAddr6, PORT1);
    );
    // socket descriptor must be non-negative integer
    EXPECT_GE(socket1, 0);

    // Open v4 socket on loopback interface and bind to different port
    int socket2 = 0;
    IOAddress loAddr("127.0.0.1");
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromAddress(loAddr, PORT2);
    );
    // socket descriptor must be positive integer
    EXPECT_GE(socket2, 0);

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();

    // Use non-existing address.
    IOAddress invalidAddr("1.2.3.4");
    EXPECT_THROW(
        ifacemgr->openSocketFromAddress(invalidAddr, PORT1), BadValue
    );

    // Do not call closeSockets() because it is called by IfaceMgr's
    // virtual destructor.
}

TEST_F(IfaceMgrTest, socketsFromRemoteAddress) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Open v6 socket to connect to remote address.
    // Loopback address is the only one that we know
    // so let's treat it as remote address.
    int socket1 = 0;
    IOAddress loAddr6("::1");
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocketFromRemoteAddress(loAddr6, PORT1);
    );
    EXPECT_GE(socket1, 0);

    // Open v4 socket to connect to remote address.
    int socket2 = 0;
    IOAddress loAddr("127.0.0.1");
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromRemoteAddress(loAddr, PORT2);
    );
    EXPECT_GE(socket2, 0);

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();

    // There used to be a check here that verified the ability to open
    // suitable socket for sending broadcast request. However,
    // there is no guarantee for such test to work on all systems
    // because some systems may have no broadcast capable interfaces at all.
    // Thus, this check has been removed.

    // Do not call closeSockets() because it is called by IfaceMgr's
    // virtual destructor.
}

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
TEST_F(IfaceMgrTest, DISABLED_sockets6Mcast) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    IOAddress loAddr("::1");
    IOAddress mcastAddr("ff02::1:2");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK, mcastAddr, 10547);
    EXPECT_GE(socket1, 0); // socket > 0

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket2 = ifacemgr->openSocket(LOOPBACK, mcastAddr, 10547);
    EXPECT_GE(socket2, 0);

    // there's no good way to test negative case here.
    // we would need non-multicast interface. We will be able
    // to iterate thru available interfaces and check if there
    // are interfaces without multicast-capable flag.

    close(socket1);
    close(socket2);
}

TEST_F(IfaceMgrTest, sendReceive6) {

    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // let's assume that every supported OS have lo interface
    IOAddress loAddr("::1");
    int socket1 = 0, socket2 = 0;
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547);
        socket2 = ifacemgr->openSocket(LOOPBACK, loAddr, 10546);
    );

    EXPECT_GE(socket1, 0);
    EXPECT_GE(socket2, 0);


    // prepare dummy payload
    uint8_t data[128];
    for (int i = 0; i < 128; i++) {
        data[i] = i;
    }
    Pkt6Ptr sendPkt = Pkt6Ptr(new Pkt6(data, 128));

    sendPkt->repack();

    sendPkt->setRemotePort(10547);
    sendPkt->setRemoteAddr(IOAddress("::1"));
    sendPkt->setIndex(1);
    sendPkt->setIface(LOOPBACK);

    Pkt6Ptr rcvPkt;

    EXPECT_EQ(true, ifacemgr->send(sendPkt));

    rcvPkt = ifacemgr->receive6(10);

    ASSERT_TRUE(rcvPkt); // received our own packet

    // let's check that we received what was sent
    ASSERT_EQ(sendPkt->data_.size(), rcvPkt->data_.size());
    EXPECT_EQ(0, memcmp(&sendPkt->data_[0], &rcvPkt->data_[0],
                        rcvPkt->data_.size()));

    EXPECT_EQ(sendPkt->getRemoteAddr().toText(), rcvPkt->getRemoteAddr().toText());

    // since we opened 2 sockets on the same interface and none of them is multicast,
    // none is preferred over the other for sending data, so we really should not
    // assume the one or the other will always be chosen for sending data. Therefore
    // we should accept both values as source ports.
    EXPECT_TRUE((rcvPkt->getRemotePort() == 10546) || (rcvPkt->getRemotePort() == 10547));

    // try to send/receive data over the closed socket. Closed socket's descriptor is
    // still being hold by IfaceMgr which will try to use it to receive data.
    close(socket1);
    EXPECT_THROW(ifacemgr->receive6(10), SocketReadError);
    EXPECT_THROW(ifacemgr->send(sendPkt), SocketWriteError);
}

TEST_F(IfaceMgrTest, sendReceive4) {

    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // let's assume that every supported OS have lo interface
    IOAddress loAddr("127.0.0.1");
    int socket1 = 0;
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, DHCP4_SERVER_PORT + 10000);
    );

    EXPECT_GE(socket1, 0);

    boost::shared_ptr<Pkt4> sendPkt(new Pkt4(DHCPDISCOVER, 1234) );

    sendPkt->setLocalAddr(IOAddress("127.0.0.1"));

    sendPkt->setLocalPort(DHCP4_SERVER_PORT + 10000 + 1);
    sendPkt->setRemotePort(DHCP4_SERVER_PORT + 10000);
    sendPkt->setRemoteAddr(IOAddress("127.0.0.1"));
    sendPkt->setIndex(1);
    sendPkt->setIface(string(LOOPBACK));
    sendPkt->setHops(6);
    sendPkt->setSecs(42);
    sendPkt->setCiaddr(IOAddress("192.0.2.1"));
    sendPkt->setSiaddr(IOAddress("192.0.2.2"));
    sendPkt->setYiaddr(IOAddress("192.0.2.3"));
    sendPkt->setGiaddr(IOAddress("192.0.2.4"));

    // Unpack() now checks if mandatory DHCP_MESSAGE_TYPE is present.
    // Workarounds (creating DHCP Message Type Option by hand) are no longer
    // needed as setDhcpType() is called in constructor.

    uint8_t sname[] = "That's just a string that will act as SNAME";
    sendPkt->setSname(sname, strlen((const char*)sname));
    uint8_t file[] = "/another/string/that/acts/as/a/file_name.txt";
    sendPkt->setFile(file, strlen((const char*)file));

    ASSERT_NO_THROW(
        sendPkt->pack();
    );

    boost::shared_ptr<Pkt4> rcvPkt;

    EXPECT_NO_THROW(ifacemgr->send(sendPkt));

    ASSERT_NO_THROW(rcvPkt = ifacemgr->receive4(10));
    ASSERT_TRUE(rcvPkt); // received our own packet

    ASSERT_NO_THROW(
        rcvPkt->unpack();
    );

    // let's check that we received what was sent
    EXPECT_EQ(sendPkt->len(), rcvPkt->len());

    EXPECT_EQ("127.0.0.1", rcvPkt->getRemoteAddr().toText());
    EXPECT_EQ(sendPkt->getRemotePort(), rcvPkt->getLocalPort());

    // now let's check content
    EXPECT_EQ(sendPkt->getHops(), rcvPkt->getHops());
    EXPECT_EQ(sendPkt->getOp(),   rcvPkt->getOp());
    EXPECT_EQ(sendPkt->getSecs(), rcvPkt->getSecs());
    EXPECT_EQ(sendPkt->getFlags(), rcvPkt->getFlags());
    EXPECT_EQ(sendPkt->getCiaddr(), rcvPkt->getCiaddr());
    EXPECT_EQ(sendPkt->getSiaddr(), rcvPkt->getSiaddr());
    EXPECT_EQ(sendPkt->getYiaddr(), rcvPkt->getYiaddr());
    EXPECT_EQ(sendPkt->getGiaddr(), rcvPkt->getGiaddr());
    EXPECT_EQ(sendPkt->getTransid(), rcvPkt->getTransid());
    EXPECT_TRUE(sendPkt->getSname() == rcvPkt->getSname());
    EXPECT_TRUE(sendPkt->getFile() == rcvPkt->getFile());
    EXPECT_EQ(sendPkt->getHtype(), rcvPkt->getHtype());
    EXPECT_EQ(sendPkt->getHlen(), rcvPkt->getHlen());

    // since we opened 2 sockets on the same interface and none of them is multicast,
    // none is preferred over the other for sending data, so we really should not
    // assume the one or the other will always be chosen for sending data. We should
    // skip checking source port of sent address.

    // Close the socket. Further we will test if errors are reported
    // properly on attempt to use closed soscket.
    close(socket1);

// Warning: kernel bug on FreeBSD. The following code checks that attempt to
// read through invalid descriptor will result in exception. The reason why
// this failure is expected is that select() function should result in EBADF
// error when invalid descriptor is passed to it. In particular, closed socket
// descriptor is invalid. On the following OS:
//
// 8.1-RELEASE FreeBSD 8.1-RELEASE #0: Mon Jul 19 02:55:53 UTC 2010
//
// calling select() using invalid descriptor results in timeout and eventually
// value of 0 is returned. This has been identified and reported as a bug in
// FreeBSD: http://www.freebsd.org/cgi/query-pr.cgi?pr=155606
//
// @todo: This part of the test is currently disabled on all BSD systems as it was
// the quick fix. We need a more elegant (config-based) solution to disable
// this check on affected systems only. The ticket has been submited for this
// work: http://bind10.isc.org/ticket/2971
#ifndef OS_BSD
    EXPECT_THROW(ifacemgr->receive4(10), SocketReadError);
#endif

    EXPECT_THROW(ifacemgr->send(sendPkt), SocketWriteError);
}

// Verifies that it is possible to set custom packet filter object
// to handle sockets opening and send/receive operation.
TEST_F(IfaceMgrTest, setPacketFilter) {

    // Create an instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Try to set NULL packet filter object and make sure it is rejected.
    boost::shared_ptr<TestPktFilter> custom_packet_filter;
    EXPECT_THROW(iface_mgr->setPacketFilter(custom_packet_filter),
                 isc::dhcp::InvalidPacketFilter);

    // Create valid object and check if it can be set.
    custom_packet_filter.reset(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(iface_mgr->setPacketFilter(custom_packet_filter));

    // Try to open socket using IfaceMgr. It should call the openSocket() function
    // on the packet filter object we have set.
    IOAddress loAddr("127.0.0.1");
    int socket1 = 0;
    EXPECT_NO_THROW(
        socket1 = iface_mgr->openSocket(LOOPBACK, loAddr, DHCP4_SERVER_PORT + 10000);
    );

    // Check that openSocket function was called.
    EXPECT_TRUE(custom_packet_filter->open_socket_called_);
    // This function always returns fake socket descriptor equal to 255.
    EXPECT_EQ(255, socket1);

    // Replacing current packet filter object while there are IPv4
    // sockets open is not allowed!
    EXPECT_THROW(iface_mgr->setPacketFilter(custom_packet_filter),
                 PacketFilterChangeDenied);

    // So, let's close the open IPv4 sockets and retry. Now it should succeed.
    iface_mgr->closeSockets(AF_INET);
    EXPECT_NO_THROW(iface_mgr->setPacketFilter(custom_packet_filter));
}

#if defined OS_LINUX

// This Linux specific test checks whether it is possible to use
// IfaceMgr to figure out which Pakcket Filter object should be
// used when direct responses to hosts, having no address assigned
// are desired or not desired.
TEST_F(IfaceMgrTest, setMatchingPacketFilter) {

    // Create an instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Let IfaceMgr figure out which Packet Filter to use when
    // direct response capability is not desired. It should pick
    // PktFilterInet.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(false));
    // The PktFilterInet is supposed to report lack of direct
    // response capability.
    EXPECT_FALSE(iface_mgr->isDirectResponseSupported());

    // There is working implementation of direct responses on Linux
    // in PktFilterLPF. It uses Linux Packet Filtering as underlying
    // mechanism. When direct responses are desired the object of
    // this class should be set.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(true));
    // This object should report that direct responses are supported.
    EXPECT_TRUE(iface_mgr->isDirectResponseSupported());
}

#else

// This non-Linux specific test checks whether it is possible to use
// IfaceMgr to figure out which Pakcket Filter object should be
// used when direct responses to hosts, having no address assigned
// are desired or not desired. Since direct responses aren't supported
// on systems other than Linux the function under test should always
// set object of PktFilterInet type as current Packet Filter. This
// object does not support direct responses. Once implementation is
// added on non-Linux systems the OS specific version of the test
// will be removed.
TEST_F(IfaceMgrTest, setMatchingPacketFilter) {

    // Create an instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Let IfaceMgr figure out which Packet Filter to use when
    // direct response capability is not desired. It should pick
    // PktFilterInet.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(false));
    // The PktFilterInet is supposed to report lack of direct
    // response capability.
    EXPECT_FALSE(iface_mgr->isDirectResponseSupported());

    // On non-Linux systems, we are missing the direct traffic
    // implementation. Therefore, we expect that PktFilterInet
    // object will be set.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(true));
    // This object should report lack of direct response capability.
    EXPECT_FALSE(iface_mgr->isDirectResponseSupported());
}

#endif

TEST_F(IfaceMgrTest, socket4) {

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Let's assume that every supported OS have lo interface.
    IOAddress loAddr("127.0.0.1");
    // Use unprivileged port (it's convenient for running tests as non-root).
    int socket1 = 0;

    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, DHCP4_SERVER_PORT + 10000);
    );

    EXPECT_GE(socket1, 0);

    Pkt4 pkt(DHCPDISCOVER, 1234);
    pkt.setIface(LOOPBACK);

    // Expect that we get the socket that we just opened.
    EXPECT_EQ(socket1, ifacemgr->getSocket(pkt));

    close(socket1);
}

// Test the Iface structure itself
TEST_F(IfaceMgrTest, iface) {
    boost::scoped_ptr<Iface> iface;
    EXPECT_NO_THROW(iface.reset(new Iface("eth0",1)));

    EXPECT_EQ("eth0", iface->getName());
    EXPECT_EQ(1, iface->getIndex());
    EXPECT_EQ("eth0/1", iface->getFullName());

    // Let's make a copy of this address collection.
    Iface::AddressCollection addrs = iface->getAddresses();

    EXPECT_EQ(0, addrs.size());

    IOAddress addr1("192.0.2.6");
    iface->addAddress(addr1);

    addrs = iface->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("192.0.2.6", addrs.at(0).toText());

    // No such address, should return false.
    EXPECT_FALSE(iface->delAddress(IOAddress("192.0.8.9")));

    // This address is present, delete it!
    EXPECT_TRUE(iface->delAddress(IOAddress("192.0.2.6")));

    // Not really necessary, previous reference still points to the same
    // collection. Let's do it anyway, as test code may serve as example
    // usage code as well.
    addrs = iface->getAddresses();

    EXPECT_EQ(0, addrs.size());

    EXPECT_NO_THROW(iface.reset());
}

TEST_F(IfaceMgrTest, iface_methods) {
    Iface iface("foo", 1234);

    iface.setHWType(42);
    EXPECT_EQ(42, iface.getHWType());

    uint8_t mac[Iface::MAX_MAC_LEN+10];
    for (int i = 0; i < Iface::MAX_MAC_LEN + 10; i++)
        mac[i] = 255 - i;

    EXPECT_EQ("foo", iface.getName());
    EXPECT_EQ(1234, iface.getIndex());

    // MAC is too long. Exception should be thrown and
    // MAC length should not be set.
    EXPECT_THROW(
        iface.setMac(mac, Iface::MAX_MAC_LEN + 1),
        OutOfRange
    );

    // MAC length should stay not set as excep
    EXPECT_EQ(0, iface.getMacLen());

    // Setting maximum length MAC should be ok.
    iface.setMac(mac, Iface::MAX_MAC_LEN);

    // For some reason constants cannot be used directly in EXPECT_EQ
    // as this produces linking error.
    size_t len = Iface::MAX_MAC_LEN;
    EXPECT_EQ(len, iface.getMacLen());
    EXPECT_EQ(0, memcmp(mac, iface.getMac(), iface.getMacLen()));
}

TEST_F(IfaceMgrTest, socketInfo) {

    // Check that socketinfo for IPv4 socket is functional
    SocketInfo sock1(7, IOAddress("192.0.2.56"), DHCP4_SERVER_PORT + 7);
    EXPECT_EQ(7, sock1.sockfd_);
    EXPECT_EQ("192.0.2.56", sock1.addr_.toText());
    EXPECT_EQ(AF_INET, sock1.family_);
    EXPECT_EQ(DHCP4_SERVER_PORT + 7, sock1.port_);

    // Check that socketinfo for IPv6 socket is functional
    SocketInfo sock2(9, IOAddress("2001:db8:1::56"), DHCP4_SERVER_PORT + 9);
    EXPECT_EQ(9, sock2.sockfd_);
    EXPECT_EQ("2001:db8:1::56", sock2.addr_.toText());
    EXPECT_EQ(AF_INET6, sock2.family_);
    EXPECT_EQ(DHCP4_SERVER_PORT + 9, sock2.port_);

    // Now let's test if IfaceMgr handles socket info properly
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    Iface* loopback = ifacemgr->getIface(LOOPBACK);
    ASSERT_TRUE(loopback);
    loopback->addSocket(sock1);
    loopback->addSocket(sock2);

    Pkt6 pkt6(DHCPV6_REPLY, 123456);

    // pkt6 dos not have interface set yet
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        BadValue
    );

    // Try to send over non-existing interface
    pkt6.setIface("nosuchinterface45");
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        BadValue
    );

    // This will work
    pkt6.setIface(LOOPBACK);
    EXPECT_EQ(9, ifacemgr->getSocket(pkt6));

    bool deleted = false;
    EXPECT_NO_THROW(
        deleted = ifacemgr->getIface(LOOPBACK)->delSocket(9);
    );
    EXPECT_EQ(true, deleted);

    // It should throw again, there's no usable socket anymore
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        Unexpected
    );

    // Repeat for pkt4
    Pkt4 pkt4(DHCPDISCOVER, 1);

    // pkt4 does not have interface set yet.
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        BadValue
    );

    // Try to send over non-existing interface.
    pkt4.setIface("nosuchinterface45");
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        BadValue
    );

    // Socket info is set, packet has well defined interface. It should work.
    pkt4.setIface(LOOPBACK);
    EXPECT_EQ(7, ifacemgr->getSocket(pkt4));

    EXPECT_NO_THROW(
        ifacemgr->getIface(LOOPBACK)->delSocket(7);
    );

    // It should throw again, there's no usable socket anymore.
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        Unexpected
    );
}

#if defined(OS_LINUX)

/// @brief parses text representation of MAC address
///
/// This function parses text representation of a MAC address and stores
/// it in binary format. Text format is expected to be separate with
/// semicolons, e.g. f4:6d:04:96:58:f2
///
/// TODO: Iface::mac_ uses uint8_t* type, should be vector<uint8_t>
///
/// @param textMac string with MAC address to parse
/// @param mac pointer to output buffer
/// @param macLen length of output buffer
///
/// @return number of bytes filled in output buffer
size_t parse_mac(const std::string& textMac, uint8_t* mac, size_t macLen) {
    stringstream tmp(textMac);
    tmp.flags(ios::hex);
    int i = 0;
    uint8_t octet = 0; // output octet
    uint8_t byte;  // parsed character from text representation
    while (!tmp.eof()) {

        tmp >> byte; // hex value
        if (byte == ':') {
            mac[i++] = octet;

            if (i == macLen) {
                // parsing aborted. We hit output buffer size
                return(i);
            }
            octet = 0;
            continue;
        }
        if (isalpha(byte)) {
            byte = toupper(byte) - 'A' + 10;
        } else if (isdigit(byte)) {
            byte -= '0';
        } else {
            // parse error. Let's return what we were able to parse so far
            break;
        }
        octet <<= 4;
        octet += byte;
    }
    mac[i++] = octet;

    return (i);
}

/// @brief Parses 'ifconfig -a' output and creates list of interfaces
///
/// This method tries to parse ifconfig output. Note that there are some
/// oddities in recent versions of ifconfig, like putting extra spaces
/// after MAC address, inconsistent naming and spacing between inet and inet6.
/// This is an attempt to find a balance between tight parsing of every piece
/// of text that ifconfig prints and robustness to handle slight differences
/// in ifconfig output.
///
/// @todo: Consider using isc::util::str::tokens here.
///
/// @param textFile name of a text file that holds output of ifconfig -a
/// @param ifaces empty list of interfaces to be filled
void parse_ifconfig(const std::string& textFile, IfaceMgr::IfaceCollection& ifaces) {
    fstream f(textFile.c_str());

    bool first_line = true;
    IfaceMgr::IfaceCollection::iterator iface;
    while (!f.eof()) {
        string line;
        getline(f, line);

        // interfaces are separated by empty line
        if (line.length() == 0) {
            first_line = true;
            continue;
        }

        // uncomment this for ifconfig output debug
        // cout << "line[" << line << "]" << endl;

        // this is first line of a new interface
        if (first_line) {
            first_line = false;

            size_t offset;
            offset = line.find_first_of(" ");
            if (offset == string::npos) {
                isc_throw(BadValue, "Malformed output of ifconfig");
            }

            // ifconfig in Gentoo prints out eth0: instead of eth0
            if (line[offset - 1] == ':') {
                offset--;
            }
            string name = line.substr(0, offset);

            // sadly, ifconfig does not return ifindex
            ifaces.push_back(Iface(name, 0));
            iface = ifaces.end();
            --iface; // points to the last element

            offset = line.find(string("HWaddr"));

            string mac = "";
            if (offset != string::npos) { // some interfaces don't have MAC (e.g. lo)
                offset += 7;
                mac = line.substr(offset, string::npos);
                mac = mac.substr(0, mac.find_first_of(" "));

                uint8_t buf[Iface::MAX_MAC_LEN];
                int mac_len = parse_mac(mac, buf, Iface::MAX_MAC_LEN);
                iface->setMac(buf, mac_len);
            }
        }

        if (line.find("inet6") != string::npos) {
            // IPv6 address
            string addr;
            if (line.find("addr:", line.find("inet6")) != string::npos) {
                // Ubuntu style format: inet6 addr: ::1/128 Scope:Host
                addr = line.substr(line.find("addr:") + 6, string::npos);
            } else {
                // Gentoo style format: inet6 fe80::6ef0:49ff:fe96:ba17
                // prefixlen 64  scopeid 0x20<link>
                addr = line.substr(line.find("inet6") + 6, string::npos);
            }

            // Handle Ubuntu format: inet6 addr: fe80::f66d:4ff:fe96:58f2/64
            // Scope:Link
            addr = addr.substr(0, addr.find("/"));

            // Handle inet6 fe80::ca3a:35ff:fed4:8f1d  prefixlen 64
            // scopeid 0x20<link>
            addr = addr.substr(0, addr.find(" "));
            IOAddress a(addr);
            iface->addAddress(a);
        } else if(line.find("inet") != string::npos) {
            // IPv4 address
            string addr;
            if (line.find("addr:", line.find("inet")) != string::npos) {
                // Ubuntu style format: inet addr:127.0.0.1  Mask:255.0.0.0
                addr = line.substr(line.find("addr:") + 5, string::npos);
            } else {
                // Gentoo style format: inet 10.53.0.4  netmask 255.255.255.0
                addr = line.substr(line.find("inet") + 5, string::npos);
            }

            addr = addr.substr(0, addr.find_first_of(" "));
            IOAddress a(addr);
            iface->addAddress(a);
        } else if(line.find("Metric") != string::npos) {
            // Flags
            if (line.find("UP") != string::npos) {
                iface->flag_up_ = true;
            }
            if (line.find("LOOPBACK") != string::npos) {
                iface->flag_loopback_ = true;
            }
            if (line.find("RUNNING") != string::npos) {
                iface->flag_running_ = true;
            }
            if (line.find("BROADCAST") != string::npos) {
                iface->flag_broadcast_ = true;
            }
            if (line.find("MULTICAST") != string::npos) {
                iface->flag_multicast_ = true;
            }
        }
    }
}


// This test compares implemented detection routines to output of "ifconfig
// -a" command.  It is far from perfect, but it is able to verify that
// interface names, flags, MAC address, IPv4 and IPv6 addresses are detected
// properly. Interface list completeness (check that each interface is reported,
// i.e. no missing or extra interfaces) and address completeness is verified.
//
// Things that are not tested:
// - ifindex (ifconfig does not print it out)
// - address scopes and lifetimes (we don't need it, so it is not implemented
//   in IfaceMgr)
// TODO: temporarily disabled, see ticket #1529
TEST_F(IfaceMgrTest, DISABLED_detectIfaces_linux) {

    NakedIfaceMgr* ifacemgr = new NakedIfaceMgr();
    IfaceMgr::IfaceCollection& detectedIfaces = ifacemgr->getIfacesLst();

    const std::string textFile = "ifconfig.txt";

    unlink(textFile.c_str());
    int result = system( ("/sbin/ifconfig -a > " + textFile).c_str());

    ASSERT_EQ(0, result);

    // List of interfaces parsed from ifconfig
    IfaceMgr::IfaceCollection parsedIfaces;

    ASSERT_NO_THROW(
        parse_ifconfig(textFile, parsedIfaces);
    );
    unlink(textFile.c_str());

    cout << "------Parsed interfaces---" << endl;
    for (IfaceMgr::IfaceCollection::iterator i = parsedIfaces.begin();
         i != parsedIfaces.end(); ++i) {
        cout << i->getName() << ": ifindex=" << i->getIndex() << ", mac=" << i->getPlainMac();
        cout << ", flags:";
        if (i->flag_up_) {
            cout << " UP";
        }
        if (i->flag_running_) {
            cout << " RUNNING";
        }
        if (i->flag_multicast_) {
            cout << " MULTICAST";
        }
        if (i->flag_broadcast_) {
            cout << " BROADCAST";
        }
        cout << ", addrs:";
        const Iface::AddressCollection& addrs = i->getAddresses();
        for (Iface::AddressCollection::const_iterator a= addrs.begin();
             a != addrs.end(); ++a) {
            cout << a->toText() << " ";
        }
        cout << endl;
    }

    // OK, now we have 2 lists of interfaces. Need to compare them
    ASSERT_EQ(detectedIfaces.size(), parsedIfaces.size());

    // TODO: This could could probably be written simple with find()
    for (IfaceMgr::IfaceCollection::iterator detected = detectedIfaces.begin();
         detected != detectedIfaces.end(); ++detected) {
        // let's find out if this interface is

        bool found = false;
        for (IfaceMgr::IfaceCollection::iterator i = parsedIfaces.begin();
             i != parsedIfaces.end(); ++i) {
            if (detected->getName() != i->getName()) {
                continue;
            }
            found = true;

            cout << "Checking interface " << detected->getName() << endl;

            // Start with checking flags
            EXPECT_EQ(detected->flag_loopback_, i->flag_loopback_);
            EXPECT_EQ(detected->flag_up_, i->flag_up_);
            EXPECT_EQ(detected->flag_running_, i->flag_running_);
            EXPECT_EQ(detected->flag_multicast_, i->flag_multicast_);
            EXPECT_EQ(detected->flag_broadcast_, i->flag_broadcast_);

            // Skip MAC comparison for loopback as netlink returns MAC
            // 00:00:00:00:00:00 for lo
            if (!detected->flag_loopback_) {
                ASSERT_EQ(detected->getMacLen(), i->getMacLen());
                EXPECT_EQ(0, memcmp(detected->getMac(), i->getMac(), i->getMacLen()));
            }

            EXPECT_EQ(detected->getAddresses().size(), i->getAddresses().size());

            // Now compare addresses
            const Iface::AddressCollection& addrs = detected->getAddresses();
            for (Iface::AddressCollection::const_iterator addr = addrs.begin();
                 addr != addrs.end(); ++addr) {
                bool addr_found = false;

                const Iface::AddressCollection& addrs2 = detected->getAddresses();
                for (Iface::AddressCollection::const_iterator a = addrs2.begin();
                     a != addrs2.end(); ++a) {
                    if (*addr != *a) {
                        continue;
                    }
                    addr_found = true;
                }
                if (!addr_found) {
                    cout << "ifconfig does not seem to report " << addr->toText()
                         << " address on " << detected->getFullName() << " interface." << endl;
                    FAIL();
                }
                cout << "Address " << addr->toText() << " on interface " << detected->getFullName()
                     << " matched with 'ifconfig -a' output." << endl;
            }
        }
        if (!found) { // Corresponding interface was not found
            FAIL();
        }
    }

    delete ifacemgr;
}
#endif

volatile bool callback_ok;

void my_callback(void) {
    cout << "Callback triggered." << endl;
    callback_ok = true;
}

TEST_F(IfaceMgrTest, controlSession) {
    // Tests if extra control socket and its callback can be passed and
    // it is supported properly by receive4() method.

    callback_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->set_session_socket(pipefd[0], my_callback));

    Pkt4Ptr pkt4;
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // Our callback should not be called this time (there was no data)
    EXPECT_FALSE(callback_ok);

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // Now, send some data over pipe (38 bytes)
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // There was some data, so this time callback should be called
    EXPECT_TRUE(callback_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);
}

// Test checks if the unicast sockets can be opened.
// This test is now disabled, because there is no reliable way to test it. We
// can't even use loopback, beacuse openSockets() skips loopback interface
// (as it should be, because DHCP server is not supposed to listen on loopback).
TEST_F(IfaceMgrTest, DISABLED_openUnicastSockets) {
    /// @todo Need to implement a test that is able to check whether we can open
    /// unicast sockets. There are 2 problems with it:
    /// 1. We need to have a non-link-local address on an interface that is
    ///    up, running, IPv6 and multicast capable
    /// 2. We need that information on every OS that we run tests on. So far
    ///    we are only supporting interface detection in Linux.
    ///
    /// To achieve this, we will probably need a pre-test setup, similar to what
    /// BIND9 is doing (i.e. configuring well known addresses on loopback).

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Get the interface (todo: which interface)
    Iface* iface = ifacemgr->getIface("eth0");
    ASSERT_TRUE(iface);
    iface->inactive6_ = false;

    // Tell the interface that it should bind to this global interface
    EXPECT_NO_THROW(iface->addUnicast(IOAddress("2001:db8::1")));

    // Tell IfaceMgr to open sockets. This should trigger at least 2 sockets
    // to open on eth0: link-local and global. On some systems (Linux), an
    // additional socket for multicast may be opened.
    EXPECT_TRUE(ifacemgr->openSockets6(PORT1));

    const Iface::SocketCollection& sockets = iface->getSockets();
    ASSERT_GE(2, sockets.size());

    // Global unicast should be first
    EXPECT_TRUE(getSocketByAddr(sockets, IOAddress("2001:db8::1")));
    EXPECT_TRUE(getSocketByAddr(sockets, IOAddress("figure-out-link-local-addr")));
}

// This test requires addresses 2001:db8:15c::1/128 and fe80::1/64 to be
// configured on loopback interface
//
// Useful commands:
// ip a a 2001:db8:15c::1/128 dev lo
// ip a a fe80::1/64 dev lo
//
// If you do not issue those commands before running this test, it will fail.
TEST_F(IfaceMgrTest, DISABLED_getSocket) {
    // Testing socket operation in a portable way is tricky
    // without interface detection implemented.

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    IOAddress lo_addr("::1");
    IOAddress link_local("fe80::1");
    IOAddress global("2001:db8:15c::1");

    IOAddress dst_link_local("fe80::dead:beef");
    IOAddress dst_global("2001:db8:15c::dead:beef");

    // Bind loopback address
    int socket1 = ifacemgr->openSocket(LOOPBACK, lo_addr, 10547);
    EXPECT_GE(socket1, 0); // socket >= 0

    // Bind link-local address
    int socket2 = ifacemgr->openSocket(LOOPBACK, link_local, 10547);
    EXPECT_GE(socket2, 0);

    int socket3 = ifacemgr->openSocket(LOOPBACK, global, 10547);
    EXPECT_GE(socket3, 0);

    // Let's make sure those sockets are unique
    EXPECT_NE(socket1, socket2);
    EXPECT_NE(socket2, socket3);
    EXPECT_NE(socket3, socket1);

    // Create a packet
    Pkt6 pkt6(DHCPV6_SOLICIT, 123);
    pkt6.setIface(LOOPBACK);

    // Check that packets sent to link-local will get socket bound to link local
    pkt6.setLocalAddr(global);
    pkt6.setRemoteAddr(dst_global);
    EXPECT_EQ(socket3, ifacemgr->getSocket(pkt6));

    // Check that packets sent to link-local will get socket bound to link local
    pkt6.setLocalAddr(link_local);
    pkt6.setRemoteAddr(dst_link_local);
    EXPECT_EQ(socket2, ifacemgr->getSocket(pkt6));

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();
}


}
