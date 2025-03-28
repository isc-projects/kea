// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option.h>
#include <dhcp/pkt6.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_filter6_test_utils.h>
#include <dhcp/tests/packet_queue_testutils.h>
#include <testutils/gtest_utils.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <fcntl.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using boost::scoped_ptr;
namespace ph = std::placeholders;

namespace {

// Note this is for the *real* loopback interface, *not* the fake one.
// So in tests using it you have LOOPBACK_NAME, LOOPBACK_INDEX and
// no "eth0" nor "eth1". In tests not using it you can have "lo", LO_INDEX,
// "eth0" or "eth1".
// Name of loopback interface detection.
const size_t BUF_SIZE = 32;
// Can be overwritten to "lo0" for instance on BSD systems.
char LOOPBACK_NAME[BUF_SIZE] = "lo";
// In fact is never 0, 1 is by far the most likely.
uint32_t LOOPBACK_INDEX = 0;

// Ports used during testing
const uint16_t PORT1 = 10547;   // V6 socket
const uint16_t PORT2 = 10548;   // V4 socket

// On some systems measured duration of receive6() and receive4() appears to be
// shorter than select() timeout.  This may be the case if different time
// resolutions are used by these functions.  For such cases we set the
// tolerance to 0.01s.
const uint32_t TIMEOUT_TOLERANCE = 10000;

// Macro for making select wait time arguments for receive functions
#define RECEIVE_WAIT_MS(m) 0,(m*1000)

/// This test verifies that the socket read buffer can be used to
/// receive the data and that the data can be read from it.
TEST(IfaceTest, readBuffer) {
    // Create fake interface object.
    Iface iface("em0", 0);
    // The size of read buffer should initially be 0 and the returned
    // pointer should be NULL.
    ASSERT_EQ(0, iface.getReadBufferSize());
    EXPECT_EQ(NULL, iface.getReadBuffer());

    // Let's resize the buffer.
    iface.resizeReadBuffer(256);
    // Check that the buffer has expected size.
    ASSERT_EQ(256, iface.getReadBufferSize());
    // The returned pointer should now be non-NULL.
    uint8_t* buf_ptr = iface.getReadBuffer();
    ASSERT_FALSE(buf_ptr == NULL);

    // Use the pointer to set some data.
    for (size_t i = 0; i < iface.getReadBufferSize(); ++i) {
        buf_ptr[i] = i;
    }

    // Get the pointer again and validate the data.
    buf_ptr = iface.getReadBuffer();
    ASSERT_EQ(256, iface.getReadBufferSize());
    for (size_t i = 0; i < iface.getReadBufferSize(); ++i) {
        // Use assert so as it fails on the first failure, no need
        // to continue further checks.
        ASSERT_EQ(i, buf_ptr[i]);
    }
}

// Check that counting the number of active addresses on the interface
// works as expected.
TEST(IfaceTest, countActive4) {
    Iface iface("eth0", 0);
    ASSERT_EQ(0, iface.countActive4());

    iface.addAddress(IOAddress("192.168.0.2"));
    ASSERT_EQ(1, iface.countActive4());

    iface.addAddress(IOAddress("2001:db8:1::1"));
    ASSERT_EQ(1, iface.countActive4());

    iface.addAddress(IOAddress("192.168.0.3"));
    ASSERT_EQ(2, iface.countActive4());

    ASSERT_NO_THROW(iface.setActive(IOAddress("192.168.0.2"), false));
    ASSERT_EQ(1, iface.countActive4());

    ASSERT_NO_THROW(iface.setActive(IOAddress("192.168.0.3"), false));
    ASSERT_EQ(0, iface.countActive4());
}

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
/// Berkeley Packet Filtering.
class TestPktFilter : public PktFilter {
public:

    /// Constructor
    TestPktFilter()
        : open_socket_called_(false) {
    }

    virtual bool isDirectResponseSupported() const {
        return (false);
    }

    virtual bool isSocketReceivedTimeSupported() const {
        return (false);
    }

    /// @brief Pretend to open a socket.
    ///
    /// This function doesn't open a real socket. It always returns the
    /// same fake socket descriptor. It also records the fact that it has
    /// been called in the public open_socket_called_ member.
    /// As in the case of opening a real socket, this function will check
    /// if there is another fake socket "bound" to the same address and port.
    /// If there is, it will throw an exception. This allows to simulate the
    /// conditions when one of the sockets can't be open because there is
    /// a socket already open and test how IfaceMgr will handle it.
    ///
    /// @param iface An interface on which the socket is to be opened.
    /// @param addr An address to which the socket is to be bound.
    /// @param port A port to which the socket is to be bound.
    virtual SocketInfo openSocket(Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool join_multicast,
                                  const bool) {
        // Check if there is any other socket bound to the specified address
        // and port on this interface.
        const Iface::SocketCollection& sockets = iface.getSockets();
        for (auto const& socket : sockets) {
            if (((socket.addr_ == addr) ||
                 ((socket.addr_ == IOAddress("::")) && join_multicast)) &&
                socket.port_ == port) {
                isc_throw(SocketConfigError, "test socket bind error");
            }
        }
        open_socket_called_ = true;
        return (SocketInfo(addr, port, 255));
    }

    /// Does nothing
    virtual Pkt4Ptr receive(Iface&, const SocketInfo&) {
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

    /// @brief Constructor.
    NakedIfaceMgr() {
        loDetect();
    }

    /// @brief detects name of the loopback interface
    ///
    /// This method detects name of the loopback interface.
    static void loDetect() {
        // Poor man's interface detection.  It will go away as soon as proper
        // interface detection is implemented
        if (if_nametoindex("lo") > 0) {
            snprintf(LOOPBACK_NAME, BUF_SIZE - 1, "lo");
        } else if (if_nametoindex("lo0") > 0) {
            snprintf(LOOPBACK_NAME, BUF_SIZE - 1, "lo0");
        } else {
            cout << "Failed to detect loopback interface. Neither "
                 << "lo nor lo0 worked. I give up." << endl;
            FAIL();
        }
        LOOPBACK_INDEX = if_nametoindex(LOOPBACK_NAME);
    }

    /// @brief Returns the collection of existing interfaces.
    IfaceCollection& getIfacesLst() { return (ifaces_); }

    /// @brief This function creates fictitious interfaces with fictitious
    /// addresses.
    ///
    /// These interfaces can be used in tests that don't actually try
    /// to open the sockets on these interfaces. Some tests use mock
    /// objects to mimic sockets being open. These interfaces are
    /// suitable for such tests.
    void createIfaces() {

        ifaces_.clear();

        // local loopback
        IfacePtr lo = createIface("lo", LO_INDEX);
        lo->addAddress(IOAddress("127.0.0.1"));
        lo->addAddress(IOAddress("::1"));
        ifaces_.push_back(lo);
        // eth0
        IfacePtr eth0 = createIface("eth0", ETH0_INDEX);
        eth0->addAddress(IOAddress("10.0.0.1"));
        eth0->addAddress(IOAddress("fe80::3a60:77ff:fed5:cdef"));
        eth0->addAddress(IOAddress("2001:db8:1::1"));
        ifaces_.push_back(eth0);
        // eth1
        IfacePtr eth1 = createIface("eth1", ETH1_INDEX);
        eth1->addAddress(IOAddress("192.0.2.3"));
        eth1->addAddress(IOAddress("fe80::3a60:77ff:fed5:abcd"));
        ifaces_.push_back(eth1);
    }

    /// @brief Create an object representing interface.
    ///
    /// Apart from creating an interface, this function also sets the
    /// interface flags:
    /// - loopback flag if interface name is "lo"
    /// - up always true
    /// - running always true
    /// - inactive always to false
    /// - multicast always to true
    /// - broadcast always to false
    ///
    /// If one needs to modify the default flag settings, the setIfaceFlags
    /// function should be used.
    ///
    /// @param name A name of the interface to be created.
    /// @param ifindex An index of the interface to be created.
    ///
    /// @return An object representing interface.
    static IfacePtr createIface(const std::string& name, const unsigned int ifindex) {
        IfacePtr iface(new Iface(name, ifindex));
        if (name == "lo") {
            iface->flag_loopback_ = true;
            // Don't open sockets on loopback interface.
            iface->inactive4_ = true;
            iface->inactive6_ = true;
        } else {
            iface->inactive4_ = false;
            iface->inactive6_ = false;
        }
        iface->flag_multicast_ = true;
        // On BSD systems, the SO_BINDTODEVICE option is not supported.
        // Therefore the IfaceMgr will throw an exception on attempt to
        // open sockets on more than one broadcast-capable interface at
        // the same time. In order to prevent this error, we mark all
        // interfaces broadcast-incapable for unit testing.
        iface->flag_broadcast_ = false;
        iface->flag_up_ = true;
        iface->flag_running_ = true;
        return (iface);
    }

    /// @brief Checks if the specified interface has a socket bound to a
    /// specified address.
    ///
    /// @param iface_name A name of the interface.
    /// @param addr An address to be checked for binding.
    ///
    /// @return true if there is a socket bound to the specified address.
    bool isBound(const std::string& iface_name, const std::string& addr) {
        IfacePtr iface = getIface(iface_name);
        if (!iface) {
            ADD_FAILURE() << "the interface " << iface_name << " doesn't exist";
            return (false);
        }
        const Iface::SocketCollection& sockets = iface->getSockets();
        for (auto const& sock : sockets) {
            if (sock.addr_ == IOAddress(addr)) {
                return (true);

            } else if ((sock.addr_ == IOAddress("::")) &&
                       (IOAddress(addr).isV6LinkLocal())) {
                for (auto const& a : iface->getAddresses()) {
                    if (a.get() == IOAddress(addr)) {
                        return (true);
                    }
                }
            }
        }
        return (false);
    }

    /// @brief Modify flags on the interface.
    ///
    /// @param name A name of the interface.
    /// @param loopback A new value of the loopback flag.
    /// @param up A new value of the up flag.
    /// @param running A new value of the running flag.
    /// @param inactive A new value of the inactive flag.
    void setIfaceFlags(const std::string& name, const bool loopback,
                       const bool up, const bool running,
                       const bool inactive4,
                       const bool inactive6) {
        for (auto const& iface : ifaces_) {
            if (iface->getName() == name) {
                iface->flag_loopback_ = loopback;
                iface->flag_up_ = up;
                iface->flag_running_ = running;
                iface->inactive4_ = inactive4;
                iface->inactive6_ = inactive6;
            }
        }
    }
};

/// @brief A test fixture class for IfaceMgr.
///
/// @todo Sockets being opened by IfaceMgr tests should be managed by
/// the test fixture. In particular, the class should close sockets after
/// each test. Current approach where test cases are responsible for
/// closing sockets is resource leak prone, especially in case of the
/// test failure path.
class IfaceMgrTest : public ::testing::Test {
public:
    /// @brief Constructor.
    IfaceMgrTest()
        : errors_count_(0) {
    }

    ~IfaceMgrTest() {
    }

    /// @brief Tests the number of IPv6 sockets on interface
    ///
    /// This function checks the expected number of open IPv6 sockets on the
    /// specified interface. On non-Linux systems, sockets are bound to a
    /// link-local address and the number of unicast addresses specified.
    /// On Linux systems, there is one more socket bound to a ff02::1:2
    /// multicast address.
    ///
    /// @param iface An interface on which sockets are open.
    /// @param unicast_num A number of unicast addresses bound.
    /// @param link_local_num A number of link local addresses bound.
    void checkSocketsCount6(const Iface& iface, const int unicast_num,
                            const int link_local_num = 1) {
        // On local-loopback interface, there should be no sockets.
        if (iface.flag_loopback_) {
            ASSERT_TRUE(iface.getSockets().empty())
                << "expected empty socket set on loopback interface "
                << iface.getName();
            return;
        }
#if defined OS_LINUX
        // On Linux, for each link-local address there may be an
        // additional socket opened and bound to ff02::1:2. This socket
        // is only opened if the interface is multicast-capable.
        ASSERT_EQ(unicast_num + (iface.flag_multicast_ ? link_local_num : 0)
                  + link_local_num, iface.getSockets().size())
            << "invalid number of sockets on interface "
            << iface.getName();
#else
        // On non-Linux, there is no additional socket.
        ASSERT_EQ(unicast_num + link_local_num, iface.getSockets().size())
            << "invalid number of sockets on interface "
            << iface.getName();

#endif
    }

    // Get the number of IPv4 or IPv6 sockets on the loopback interface
    int getOpenSocketsCount(const Iface& iface, uint16_t family) const {
        // Get all sockets.
        Iface::SocketCollection sockets = iface.getSockets();

        // Loop through sockets and try to find the ones which match the
        // specified type.
        int sockets_count = 0;
        for (auto const& sock : sockets) {
            // Match found, increase the counter.
            if (sock.family_ == family) {
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
        for (auto const& s : sockets) {
            if (s.addr_ == addr) {
                return (&s);
            }
        }
        return (NULL);
    }

    /// @brief Implements an IfaceMgr error handler.
    ///
    /// This function can be installed as an error handler for the
    /// IfaceMgr::openSockets4 function. The error handler is invoked
    /// when an attempt to open a particular socket fails for any reason.
    /// Typically, the error handler will log a warning. When the error
    /// handler returns, the openSockets4 function should continue opening
    /// sockets on other interfaces.
    ///
    /// @param errmsg An error string indicating the reason for failure.
    void ifaceMgrErrorHandler(const std::string&) {
        // Increase the counter of invocations to this function. By checking
        // this number, a test may check if the expected number of errors
        // has occurred.
        ++errors_count_;
    }

    /// @brief Tests the ability to send and receive DHCPv6 packets
    ///
    /// This test calls @r IfaceMgr::configureDHCPPacketQueue, passing in the
    /// given queue configuration.  It then calls IfaceMgr::startDHCPReceiver
    /// and verifies whether or not the receive thread has been started as
    /// expected.  Next it creates a generic DHCPv6 packet and sends it over
    /// the loop back interface.  It invokes IfaceMgr::receive6 to receive the
    /// packet sent, and compares to the packets for equality.
    ///
    /// @param dhcp_queue_control dhcp-queue-control contents to use for the test
    /// @param exp_queue_enabled flag that indicates if packet queuing is expected
    /// to be enabled.
    void sendReceive6Test(data::ConstElementPtr dhcp_queue_control, bool exp_queue_enabled) {
        scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

        // Testing socket operation in a portable way is tricky
        // without interface detection implemented
        // let's assume that every supported OS have lo interface
        IOAddress lo_addr("::1");
        int socket1 = 0, socket2 = 0;
        EXPECT_NO_THROW(
            socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10547);
            socket2 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10546);
        );

        EXPECT_GE(socket1, 0);
        EXPECT_GE(socket2, 0);

        // Configure packet queueing as desired.
        bool queue_enabled = false;
        ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, dhcp_queue_control));

        // Verify that we have a queue only if we expected one.
        ASSERT_EQ(exp_queue_enabled, queue_enabled);

        // Thread should only start when there is a packet queue.
        ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET6));
        ASSERT_TRUE(queue_enabled == ifacemgr->isDHCPReceiverRunning());

        // If the thread is already running, trying to start it again should fail.
        if (queue_enabled) {
            ASSERT_THROW(ifacemgr->startDHCPReceiver(AF_INET6), InvalidOperation);
            // Should still have one running.
            ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());
        }

        // Let's build our DHCPv6 packet.
        // prepare dummy payload
        uint8_t data[128];
        for (uint8_t i = 0; i < 128; i++) {
            data[i] = i;
        }

        Pkt6Ptr sendPkt = Pkt6Ptr(new Pkt6(data, 128));
        sendPkt->repack();
        sendPkt->setRemotePort(10547);
        sendPkt->setRemoteAddr(IOAddress("::1"));
        sendPkt->setIndex(LOOPBACK_INDEX);
        sendPkt->setIface(LOOPBACK_NAME);

        // Send the packet.
        EXPECT_EQ(true, ifacemgr->send(sendPkt));

        // Now, let's try and receive it.
        Pkt6Ptr rcvPkt;
        rcvPkt = ifacemgr->receive6(10);
        ASSERT_TRUE(rcvPkt); // received our own packet

        // let's check that we received what was sent
        ASSERT_EQ(sendPkt->data_.size(), rcvPkt->data_.size());
        EXPECT_EQ(0, memcmp(&sendPkt->data_[0], &rcvPkt->data_[0],
                            rcvPkt->data_.size()));

        EXPECT_EQ(sendPkt->getRemoteAddr(), rcvPkt->getRemoteAddr());

        // since we opened 2 sockets on the same interface and none of them is multicast,
        // none is preferred over the other for sending data, so we really should not
        // assume the one or the other will always be chosen for sending data. Therefore
        // we should accept both values as source ports.
        EXPECT_TRUE((rcvPkt->getRemotePort() == 10546) || (rcvPkt->getRemotePort() == 10547));

        // Stop the thread.  This should be no harm/no foul if we're not
        // queueuing.  Either way, we should not have a thread afterwards.
        ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
        ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    }

    /// @brief Tests the ability to send and receive DHCPv4 packets
    ///
    /// This test calls @r IfaceMgr::configureDHCPPacketQueue, passing in the
    /// given queue configuration.  It then calls IfaceMgr::startDHCPReceiver
    /// and verifies whether or not the receive thread has been started as
    /// expected.  Next it creates a DISCOVER packet and sends it over
    /// the loop back interface.  It invokes IfaceMgr::receive4 to receive the
    /// packet sent, and compares to the packets for equality.
    ///
    /// @param dhcp_queue_control dhcp-queue-control contents to use for the test
    /// @param exp_queue_enabled flag that indicates if packet queuing is expected
    /// to be enabled.
    void sendReceive4Test(data::ConstElementPtr dhcp_queue_control, bool exp_queue_enabled) {
        scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

        // Testing socket operation in a portable way is tricky
        // without interface detection implemented.
        // Let's assume that every supported OS has lo interface
        IOAddress lo_addr("127.0.0.1");
        int socket1 = 0;
        EXPECT_NO_THROW(
            socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr,
                                           DHCP4_SERVER_PORT + 10000);
        );

        EXPECT_GE(socket1, 0);

        // Configure packet queueing as desired.
        bool queue_enabled = false;
        ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, dhcp_queue_control));

        // Verify that we have a queue only if we expected one.
        ASSERT_EQ(exp_queue_enabled, queue_enabled);

        // Thread should only start when there is a packet queue.
        ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));
        ASSERT_TRUE(queue_enabled == ifacemgr->isDHCPReceiverRunning());

        // If the thread is already running, trying to start it again should fail.
        if (queue_enabled) {
            ASSERT_THROW(ifacemgr->startDHCPReceiver(AF_INET), InvalidOperation);
            // Should still have one running.
            ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());
        }

        // Let's construct the packet to send.
        boost::shared_ptr<Pkt4> sendPkt(new Pkt4(DHCPDISCOVER, 1234) );
        sendPkt->setLocalAddr(IOAddress("127.0.0.1"));
        sendPkt->setLocalPort(DHCP4_SERVER_PORT + 10000 + 1);
        sendPkt->setRemotePort(DHCP4_SERVER_PORT + 10000);
        sendPkt->setRemoteAddr(IOAddress("127.0.0.1"));
        sendPkt->setIndex(LOOPBACK_INDEX);
        sendPkt->setIface(string(LOOPBACK_NAME));
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

        // OK, Send the PACKET!
        bool result = false;
        EXPECT_NO_THROW(result = ifacemgr->send(sendPkt));
        EXPECT_TRUE(result);

        // Now let's try and receive it.
        boost::shared_ptr<Pkt4> rcvPkt;
        ASSERT_NO_THROW(rcvPkt = ifacemgr->receive4(10));
        ASSERT_TRUE(rcvPkt); // received our own packet
        ASSERT_NO_THROW(
            rcvPkt->unpack();
        );

        // let's check that we received what was sent
        EXPECT_EQ(sendPkt->len(), rcvPkt->len());
        EXPECT_EQ("127.0.0.1", rcvPkt->getRemoteAddr().toText());
        EXPECT_EQ(sendPkt->getRemotePort(), rcvPkt->getLocalPort());
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
        // properly on attempt to use closed socket.
        close(socket1);

        // @todo Closing the socket does NOT cause a read error out of the
        // receiveDHCP<X>Packets() select.  Apparently this is because the
        // thread is already inside the select when the socket is closed,
        // and (at least under Centos 7.5), this does not interrupt the
        // select.  For now, we'll only test this for direct receive.
        if (!queue_enabled) {
            EXPECT_THROW(ifacemgr->receive4(10), SocketReadError);
        }

        // Verify write fails.
        EXPECT_THROW(ifacemgr->send(sendPkt), SocketWriteError);

        // Stop the thread.  This should be no harm/no foul if we're not
        // queueuing.  Either way, we should not have a thread afterwards.
        ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
        ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    }

    /// @brief Verifies that IfaceMgr DHCPv4 receive calls detect and
    /// purge external sockets that have gone bad without affecting
    /// affecting normal operations.  It can be run with or without
    /// packet queuing.
    ///
    /// @param use_queue determines if packet queuing is used or not.
    void purgeExternalSockets4Test(bool use_queue = false) {
        bool callback_ok = false;
        bool callback2_ok = false;

        scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

        if (use_queue) {
            bool queue_enabled = false;
            data::ConstElementPtr config = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500);
            ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, config));
            ASSERT_TRUE(queue_enabled);

            // Thread should only start when there is a packet queue.
            ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));
            ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());
        }

        // Create first pipe and register it as extra socket
        int pipefd[2];
        EXPECT_TRUE(pipe(pipefd) == 0);
        ASSERT_FALSE(ifacemgr->isExternalSocket(pipefd[0]));
        EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0],
                        [&callback_ok, &pipefd](int fd) {
                            callback_ok = (pipefd[0] == fd);
                        }));
        ASSERT_TRUE(ifacemgr->isExternalSocket(pipefd[0]));

        // Let's create a second pipe and register it as well
        int secondpipe[2];
        EXPECT_TRUE(pipe(secondpipe) == 0);
        ASSERT_FALSE(ifacemgr->isExternalSocket(secondpipe[0]));
        EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0],
                        [&callback2_ok, &secondpipe](int fd) {
                            callback2_ok = (secondpipe[0] == fd);
                        }));
        ASSERT_TRUE(ifacemgr->isExternalSocket(secondpipe[0]));

        // Verify a call with no data and normal external sockets works ok.
        Pkt4Ptr pkt4;
        ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(RECEIVE_WAIT_MS(10)));

        // No callback invocations and no DHCPv4 pkt.
        EXPECT_FALSE(callback_ok);
        EXPECT_FALSE(callback2_ok);
        EXPECT_FALSE(pkt4);

        // Now close the first pipe.  This should make it's external socket invalid.
        close(pipefd[1]);
        close(pipefd[0]);

        // We call receive4() which should detect and remove the invalid socket.
        try {
            pkt4 = ifacemgr->receive4(RECEIVE_WAIT_MS(10));
            ADD_FAILURE() << "receive4 should have failed";
        } catch (const SocketReadError& ex) {
            EXPECT_EQ(std::string("SELECT interrupted by one invalid sockets,"
                                  " purged 1 socket descriptors"),
                      std::string(ex.what()));
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "wrong exception thrown: " << ex.what();
        }

        // No callback invocations and no DHCPv4 pkt.
        EXPECT_FALSE(callback_ok);
        EXPECT_FALSE(callback2_ok);
        EXPECT_FALSE(pkt4);

        // Now check whether the second callback is still functional
        EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

        // Call receive4 again, this should work.
        ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(RECEIVE_WAIT_MS(10)));

        // Should have callback2 data only.
        EXPECT_FALSE(callback_ok);
        EXPECT_TRUE(callback2_ok);
        EXPECT_FALSE(pkt4);

        // Stop the thread.  This should be no harm/no foul if we're not
        // queueuing.  Either way, we should not have a thread afterwards.
        ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
        ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    }

    /// @brief Verifies that IfaceMgr DHCPv6 receive calls detect and
    /// purge external sockets that have gone bad without affecting
    /// affecting normal operations.  It can be run with or without
    /// packet queuing.
    ///
    /// @param use_queue determines if packet queuing is used or not.
    void purgeExternalSockets6Test(bool use_queue = false) {
        bool callback_ok = false;
        bool callback2_ok = false;

        scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

        if (use_queue) {
            bool queue_enabled = false;
            data::ConstElementPtr config = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500);
            ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, config));
            ASSERT_TRUE(queue_enabled);

            // Thread should only start when there is a packet queue.
            ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET6));
            ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());
        }

        // Create first pipe and register it as extra socket
        int pipefd[2];
        EXPECT_TRUE(pipe(pipefd) == 0);
        ASSERT_FALSE(ifacemgr->isExternalSocket(pipefd[0]));
        EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0],
                        [&callback_ok, &pipefd](int fd) {
                            callback_ok = (pipefd[0] == fd);
                        }));
        ASSERT_TRUE(ifacemgr->isExternalSocket(pipefd[0]));

        // Let's create a second pipe and register it as well
        int secondpipe[2];
        EXPECT_TRUE(pipe(secondpipe) == 0);
        ASSERT_FALSE(ifacemgr->isExternalSocket(secondpipe[0]));
        EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0],
                        [&callback2_ok, &secondpipe](int fd) {
                            callback2_ok = (secondpipe[0] == fd);
                        }));
        ASSERT_TRUE(ifacemgr->isExternalSocket(secondpipe[0]));

        // Verify a call with no data and normal external sockets works ok.
        Pkt6Ptr pkt6;
        ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(RECEIVE_WAIT_MS(10)));

        // No callback invocations and no DHCPv6 pkt.
        EXPECT_FALSE(callback_ok);
        EXPECT_FALSE(callback2_ok);
        EXPECT_FALSE(pkt6);

        // Now close the first pipe.  This should make it's external socket invalid.
        close(pipefd[1]);
        close(pipefd[0]);

        // We call receive6() which should detect and remove the invalid socket.
        try {
            pkt6 = ifacemgr->receive6(RECEIVE_WAIT_MS(10));
            ADD_FAILURE() << "receive6 should have failed";
        } catch (const SocketReadError& ex) {
            EXPECT_EQ(std::string("SELECT interrupted by one invalid sockets,"
                                  " purged 1 socket descriptors"),
                      std::string(ex.what()));
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "wrong exception thrown: " << ex.what();
        }

        // No callback invocations and no DHCPv6 pkt.
        EXPECT_FALSE(callback_ok);
        EXPECT_FALSE(callback2_ok);
        EXPECT_FALSE(pkt6);

        // Now check whether the second callback is still functional
        EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

        // Call receive6 again, this should work.
        ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(RECEIVE_WAIT_MS(10)));

        // Should have callback2 data only.
        EXPECT_FALSE(callback_ok);
        EXPECT_TRUE(callback2_ok);
        EXPECT_FALSE(pkt6);

        // Stop the thread.  This should be no harm/no foul if we're not
        // queueuing.  Either way, we should not have a thread afterwards.
        ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
        ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    }

    /// Holds the invocation counter for ifaceMgrErrorHandler.
    int errors_count_;
};

// We need some known interface to work reliably. Loopback interface is named
// lo on Linux and lo0 on BSD boxes. We need to find out which is available.
// This is not a real test, but rather a workaround that will go away when
// interface detection is implemented on all OSes.
TEST_F(IfaceMgrTest, loDetect) {
    NakedIfaceMgr::loDetect();
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

    static_cast<void>(remove("interfaces.txt"));

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
             << pkt->remote_addr_ << "\");" << endl;
        cout << "    pkt->local_port_ = " << pkt-> local_port_ << ";" << endl;
        cout << "    pkt->local_addr_ = IOAddress(\""
             << pkt->local_addr_ << "\");" << endl;
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

// This test verifies that creation of the IfaceMgr instance doesn't
// cause an exception.
TEST_F(IfaceMgrTest, instance) {
    EXPECT_NO_THROW(IfaceMgr::instance());
}

// Basic tests for Iface inner class.
TEST_F(IfaceMgrTest, ifaceClass) {

  IfacePtr iface(new Iface("eth5", 7));
    EXPECT_STREQ("eth5/7", iface->getFullName().c_str());

    EXPECT_THROW_MSG(iface.reset(new Iface("", 10)), BadValue,
                     "Interface name must not be empty");

    EXPECT_NO_THROW(iface.reset(new Iface("big-index", 66666)));
    EXPECT_EQ(66666, iface->getIndex());
}

// This test checks the getIface by index method.
TEST_F(IfaceMgrTest, getIfaceByIndex) {
    NakedIfaceMgr ifacemgr;

    // Create a set of fake interfaces. At the same time, remove the actual
    // interfaces that have been detected by the IfaceMgr.
    ifacemgr.createIfaces();

    // Getting an unset index should throw.
    EXPECT_THROW_MSG(ifacemgr.getIface(UNSET_IFINDEX), BadValue, "interface index was not set");

    // Historically -1 was used as an unset value. Let's also check that it throws in case we didn't
    // migrate all code to UNSET_IFINDEX and in case the values diverge.
    EXPECT_THROW_MSG(ifacemgr.getIface(-1), BadValue, "interface index was not set");

    // Get the first interface defined.
    IfacePtr iface(ifacemgr.getIface(0));
    ASSERT_TRUE(iface);
    EXPECT_EQ("lo", iface->getName());

    // Attemt to get an undefined interface.
    iface = ifacemgr.getIface(3);
    EXPECT_FALSE(iface);

    // Check that we can go past INT_MAX.
    unsigned int int_max(numeric_limits<int>::max());
    iface = ifacemgr.getIface(int_max);
    EXPECT_FALSE(iface);
    iface = ifacemgr.createIface("wlan0", int_max);
    ifacemgr.addInterface(iface);
    iface = ifacemgr.getIface(int_max);
    EXPECT_TRUE(iface);
    iface = ifacemgr.getIface(int_max + 1);
    EXPECT_FALSE(iface);
    iface = ifacemgr.createIface("wlan1", int_max + 1);
    ifacemgr.addInterface(iface);
    iface = ifacemgr.getIface(int_max + 1);
    EXPECT_TRUE(iface);
}

// This test checks the getIface by packet method.
TEST_F(IfaceMgrTest, getIfaceByPkt) {
    NakedIfaceMgr ifacemgr;
    // Create a set of fake interfaces. At the same time, remove the actual
    // interfaces that have been detected by the IfaceMgr.
    ifacemgr.createIfaces();

    // Try IPv4 packet by name.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 1234));
    IfacePtr iface = ifacemgr.getIface(pkt4);
    EXPECT_FALSE(iface);
    pkt4->setIface("eth0");
    iface = ifacemgr.getIface(pkt4);
    EXPECT_TRUE(iface);
    EXPECT_FALSE(pkt4->indexSet());

    // Try IPv6 packet by index.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REPLY, 123456));
    iface = ifacemgr.getIface(pkt6);
    EXPECT_FALSE(iface);
    ASSERT_TRUE(ifacemgr.getIface("eth0"));
    pkt6->setIndex(ifacemgr.getIface("eth0")->getIndex() + 1);
    iface = ifacemgr.getIface(pkt6);
    ASSERT_TRUE(iface);
    EXPECT_TRUE(pkt6->indexSet());

    // Index has precedence when both name and index are available.
    EXPECT_EQ("eth1", iface->getName());
    pkt6->setIface("eth0");
    iface = ifacemgr.getIface(pkt6);
    ASSERT_TRUE(iface);
    EXPECT_EQ("eth1", iface->getName());

    // Not existing name fails.
    pkt4->setIface("eth2");
    iface = ifacemgr.getIface(pkt4);
    EXPECT_FALSE(iface);

    // Not existing index fails.
    pkt6->setIndex(3);
    iface = ifacemgr.getIface(pkt6);
    ASSERT_FALSE(iface);

    // Test that resetting the index is verifiable.
    pkt4->resetIndex();
    EXPECT_FALSE(pkt4->indexSet());
    pkt6->resetIndex();
    EXPECT_FALSE(pkt6->indexSet());

    // Test that you can also reset the index via setIndex().
    pkt4->setIndex(UNSET_IFINDEX);
    EXPECT_FALSE(pkt4->indexSet());
    pkt6->setIndex(UNSET_IFINDEX);
    EXPECT_FALSE(pkt6->indexSet());
}

// Test that the IPv4 address can be retrieved for the interface.
TEST_F(IfaceMgrTest, ifaceGetAddress) {
    Iface iface("eth0", 0);

    IOAddress addr("::1");
    // Initially, the Iface has no addresses assigned.
    EXPECT_FALSE(iface.getAddress4(addr));
    // Add some addresses with IPv4 address in the middle.
    iface.addAddress(IOAddress("fe80::3a60:77ff:fed5:cdef"));
    iface.addAddress(IOAddress("10.1.2.3"));
    iface.addAddress(IOAddress("2001:db8:1::2"));
    // The v4 address should be returned.
    EXPECT_TRUE(iface.getAddress4(addr));
    EXPECT_EQ("10.1.2.3", addr.toText());
    // Delete the IPv4 address and leave only two IPv6 addresses.
    ASSERT_NO_THROW(iface.delAddress(IOAddress("10.1.2.3")));
    // The IPv4 address should not be returned.
    EXPECT_FALSE(iface.getAddress4(addr));
    // Add a different IPv4 address at the end of the list.
    iface.addAddress(IOAddress("192.0.2.3"));
    // This new address should now be returned.
    EXPECT_TRUE(iface.getAddress4(addr));
    EXPECT_EQ("192.0.2.3", addr.toText());
}

// This test checks if it is possible to check that the specific address is
// assigned to the interface.
TEST_F(IfaceMgrTest, ifaceHasAddress) {
    IfaceMgrTestConfig config(true);

    IfacePtr iface = IfaceMgr::instance().getIface("eth0");
    ASSERT_TRUE(iface);
    EXPECT_TRUE(iface->hasAddress(IOAddress("10.0.0.1")));
    EXPECT_FALSE(iface->hasAddress(IOAddress("10.0.0.2")));
    EXPECT_TRUE(iface->hasAddress(IOAddress("fe80::3a60:77ff:fed5:cdef")));
    EXPECT_TRUE(iface->hasAddress(IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(iface->hasAddress(IOAddress("2001:db8:1::2")));
}

// This test checks it is not allowed to add duplicate interfaces.
TEST_F(IfaceMgrTest, addInterface) {
    IfaceMgrTestConfig config(true);

    IfacePtr dup_name(new Iface("eth1", 123));
    EXPECT_THROW_MSG(IfaceMgr::instance().addInterface(dup_name), Unexpected,
                     "Can't add eth1/123 when eth1/2 already exists.");
    IfacePtr dup_index(new Iface("eth2", 2));
    EXPECT_THROW_MSG(IfaceMgr::instance().addInterface(dup_index), Unexpected,
                     "Can't add eth2/2 when eth1/2 already exists.");

    IfacePtr eth2(new Iface("eth2", 3));
    EXPECT_NO_THROW(IfaceMgr::instance().addInterface(eth2));
}

// TODO: Implement getPlainMac() test as soon as interface detection
// is implemented.
TEST_F(IfaceMgrTest, getIface) {

    cout << "Interface checks. Please ignore socket binding errors." << endl;
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Interface name, ifindex
    IfacePtr iface1(new Iface("lo1", 100));
    IfacePtr iface2(new Iface("eth9", 101));
    IfacePtr iface3(new Iface("en99", 102));
    IfacePtr iface4(new Iface("e1000g4", 103));
    cout << "This test assumes that there are less than 100 network interfaces"
         << " in the tested system and there are no lo1, eth9, en99, e1000g4"
         << " or wifi15 interfaces present." << endl;

    // Note: real interfaces may be detected as well
    ifacemgr->getIfacesLst().push_back(iface1);
    ifacemgr->getIfacesLst().push_back(iface2);
    ifacemgr->getIfacesLst().push_back(iface3);
    ifacemgr->getIfacesLst().push_back(iface4);

    cout << "There are " << ifacemgr->getIfacesLst().size()
         << " interfaces." << endl;
    for (auto const& iface : ifacemgr->getIfacesLst()) {
        cout << "  " << iface->getFullName() << endl;
    }

    // Check that interface can be retrieved by ifindex
    IfacePtr tmp = ifacemgr->getIface(102);
    ASSERT_TRUE(tmp);

    EXPECT_EQ("en99", tmp->getName());
    EXPECT_EQ(102, tmp->getIndex());

    // Check that interface can be retrieved by name
    tmp = ifacemgr->getIface("lo1");
    ASSERT_TRUE(tmp);

    EXPECT_EQ("lo1", tmp->getName());
    EXPECT_EQ(100, tmp->getIndex());

    // Check that non-existing interfaces are not returned
    EXPECT_FALSE(ifacemgr->getIface("wifi15") );
}

TEST_F(IfaceMgrTest, clearIfaces) {
    NakedIfaceMgr ifacemgr;
    // Create a set of fake interfaces. At the same time, remove the actual
    // interfaces that have been detected by the IfaceMgr.
    ifacemgr.createIfaces();

    ASSERT_GT(ifacemgr.countIfaces(), 0);

    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    ASSERT_NO_THROW(ifacemgr.openSockets4());

    ifacemgr.clearIfaces();

    EXPECT_EQ(0, ifacemgr.countIfaces());
}

// Verify that we have the expected default DHCPv4 packet queue.
TEST_F(IfaceMgrTest, packetQueue4) {
    NakedIfaceMgr ifacemgr;

    // Should not have a queue at start up.
    ASSERT_FALSE(ifacemgr.getPacketQueue4());

    // Verify that we can create a queue with default factory.
    data::ConstElementPtr config = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 2000);
    ASSERT_NO_THROW(ifacemgr.getPacketQueueMgr4()->createPacketQueue(config));
    CHECK_QUEUE_INFO(ifacemgr.getPacketQueue4(), "{ \"capacity\": 2000, \"queue-type\": \""
                     << PacketQueueMgr4::DEFAULT_QUEUE_TYPE4 << "\", \"size\": 0 }");
}

// Verify that we have the expected default DHCPv6 packet queue.
TEST_F(IfaceMgrTest, packetQueue6) {
    NakedIfaceMgr ifacemgr;

    // Should not have a queue at start up.
    ASSERT_FALSE(ifacemgr.getPacketQueue6());

    // Verify that we can create a queue with default factory.
    data::ConstElementPtr config = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 2000);
    ASSERT_NO_THROW(ifacemgr.getPacketQueueMgr6()->createPacketQueue(config));
    CHECK_QUEUE_INFO(ifacemgr.getPacketQueue6(), "{ \"capacity\": 2000, \"queue-type\": \""
                     << PacketQueueMgr6::DEFAULT_QUEUE_TYPE6 << "\", \"size\": 0 }");
}

TEST_F(IfaceMgrTest, receiveTimeout6) {
    using namespace boost::posix_time;
    std::cout << "Testing DHCPv6 packet reception timeouts."
              << " Test will block for a few seconds when waiting"
              << " for timeout to occur." << std::endl;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    // Open socket on the lo interface.
    IOAddress lo_addr("::1");
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10547)
    );
    // Socket is open if result is non-negative.
    ASSERT_GE(socket1, 0);
    // Start receiver.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET6));

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
    // uncertainty should be low enough to expect that measured
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

    // Stop receiver.
    EXPECT_NO_THROW(ifacemgr->stopDHCPReceiver());
}

TEST_F(IfaceMgrTest, receiveTimeout4) {
    using namespace boost::posix_time;
    std::cout << "Testing DHCPv4 packet reception timeouts."
              << " Test will block for a few seconds when waiting"
              << " for timeout to occur." << std::endl;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    // Open socket on the lo interface.
    IOAddress lo_addr("127.0.0.1");
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10067)
    );
    // Socket is open if returned value is non-negative.
    ASSERT_GE(socket1, 0);

    // Start receiver.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));

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
    // uncertainty should be low enough to expect that measured
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
    EXPECT_THROW(ifacemgr->receive4(0, 1000000), isc::BadValue);
    EXPECT_THROW(ifacemgr->receive4(2, 1000005), isc::BadValue);

    // Stop receiver.
    EXPECT_NO_THROW(ifacemgr->stopDHCPReceiver());
}

TEST_F(IfaceMgrTest, multipleSockets) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Container for initialized socket descriptors
    std::list<uint16_t> init_sockets;

    // Create socket #1
    int socket1 = 0;
    ASSERT_NO_THROW(
        socket1 = ifacemgr->openSocketFromIface(LOOPBACK_NAME, PORT1, AF_INET);
    );
    ASSERT_GE(socket1, 0);
    init_sockets.push_back(socket1);

    // Create socket #2
    IOAddress lo_addr("127.0.0.1");
    int socket2 = 0;
    ASSERT_NO_THROW(
        socket2 = ifacemgr->openSocketFromRemoteAddress(lo_addr, PORT2);
    );
    ASSERT_GE(socket2, 0);
    init_sockets.push_back(socket2);

    // Get loopback interface. If we don't find one we are unable to run
    // this test but we don't want to fail.
    IfacePtr iface_ptr = ifacemgr->getIface(LOOPBACK_NAME);
    if (iface_ptr == NULL) {
        cout << "Local loopback interface not found. Skipping test. " << endl;
        return;
    }
    ASSERT_EQ(LOOPBACK_INDEX, iface_ptr->getIndex());
    // Once sockets have been successfully opened, they are supposed to
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

    // We are still in possession of socket descriptors that we created
    // on the beginning of this test. We can use them to check whether
    // closeSockets() only removed them from the list or they have been
    // really closed.
    for (std::list<uint16_t>::const_iterator init_sockets_it =
             init_sockets.begin();
         init_sockets_it != init_sockets.end(); ++init_sockets_it) {
        // recv() must result in error when using invalid socket.
        char buf;
        static_cast<void>(recv(*init_sockets_it, &buf, 1, MSG_PEEK));
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

    IOAddress lo_addr("::1");

    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, 123));
    pkt6->setIface(LOOPBACK_NAME);

    // Bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10547);
    EXPECT_GE(socket1, 0); // socket >= 0

    EXPECT_EQ(socket1, ifacemgr->getSocket(pkt6));

    // Bind unicast socket to port 10548
    int socket2 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10548);
    EXPECT_GE(socket2, 0);

    // Removed code for binding socket twice to the same address/port
    // as it caused problems on some platforms (e.g. Mac OS X)

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();

    // Use address that is not assigned to LOOPBACK iface.
    IOAddress invalidAddr("::2");
    EXPECT_THROW(
        ifacemgr->openSocket(LOOPBACK_NAME, invalidAddr, 10547),
        SocketConfigError
    );

    // Use non-existing interface name.
    EXPECT_THROW(
        ifacemgr->openSocket("non_existing_interface", lo_addr, 10548),
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
        socket1 = ifacemgr->openSocketFromIface(LOOPBACK_NAME, PORT1, AF_INET6);
    );
    // Socket descriptor must be non-negative integer
    EXPECT_GE(socket1, 0);
    close(socket1);

    // Open v4 socket on loopback interface and bind to different port
    int socket2 = 0;
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromIface(LOOPBACK_NAME, PORT2, AF_INET);
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
    IOAddress lo_addr6("::1");
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocketFromAddress(lo_addr6, PORT1);
    );
    // socket descriptor must be non-negative integer
    EXPECT_GE(socket1, 0);

    // Open v4 socket on loopback interface and bind to different port
    int socket2 = 0;
    IOAddress lo_addr("127.0.0.1");
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromAddress(lo_addr, PORT2);
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
    IOAddress lo_addr6("::1");
    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocketFromRemoteAddress(lo_addr6, PORT1);
    );
    EXPECT_GE(socket1, 0);

    // Open v4 socket to connect to remote address.
    int socket2 = 0;
    IOAddress lo_addr("127.0.0.1");
    EXPECT_NO_THROW(
        socket2 = ifacemgr->openSocketFromRemoteAddress(lo_addr, PORT2);
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

    IOAddress lo_addr("::1");
    IOAddress mcastAddr("ff02::1:2");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK_NAME, mcastAddr, 10547);
    EXPECT_GE(socket1, 0); // socket > 0

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket2 = ifacemgr->openSocket(LOOPBACK_NAME, mcastAddr, 10547);
    EXPECT_GE(socket2, 0);

    // there's no good way to test negative case here.
    // we would need non-multicast interface. We will be able
    // to iterate thru available interfaces and check if there
    // are interfaces without multicast-capable flag.

    close(socket1);
    close(socket2);
}

// Verifies that basic DHCPv6 packet send and receive operates
// in either direct or indirect mode.
TEST_F(IfaceMgrTest, sendReceive6) {
    data::ElementPtr queue_control;

    // Given an empty pointer, queueing should be disabled.
    // This should do direct reception.
    sendReceive6Test(queue_control, false);

    // Now let's populate queue control.
    queue_control = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500, false);
    // With queueing disabled, we should use direct reception.
    sendReceive6Test(queue_control, false);

    // Queuing enabled, indirection reception should work.
    queue_control = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500, true);
    sendReceive6Test(queue_control, true);
}

// Verifies that basic DHCPv4 packet send and receive operates
// in either direct or indirect mode.
TEST_F(IfaceMgrTest, sendReceive4) {
    data::ElementPtr queue_control;

    // Given an empty pointer, queueing should be disabled.
    // This should do direct reception.
    sendReceive4Test(queue_control, false);

    // Now let's populate queue control.
    queue_control = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500, false);
    // With queueing disabled, we should use direct reception.
    sendReceive4Test(queue_control, false);

    // Queuing enabled, indirection reception should work.
    queue_control = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500, true);
    sendReceive4Test(queue_control, true);
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
    IOAddress lo_addr("127.0.0.1");
    int socket1 = 0;
    EXPECT_NO_THROW(
        socket1 = iface_mgr->openSocket(LOOPBACK_NAME, lo_addr,
                                        DHCP4_SERVER_PORT + 10000);
    );

    // Check that openSocket function was called.
    EXPECT_TRUE(custom_packet_filter->open_socket_called_);
    // This function always returns fake socket descriptor equal to 255.
    EXPECT_EQ(255, socket1);

    // Replacing current packet filter object while there are IPv4
    // sockets open is not allowed!
    EXPECT_THROW(iface_mgr->setPacketFilter(custom_packet_filter),
                 PacketFilterChangeDenied);

    // So, let's close the open sockets and retry. Now it should succeed.
    iface_mgr->closeSockets();
    EXPECT_NO_THROW(iface_mgr->setPacketFilter(custom_packet_filter));
}

// This test checks that the default packet filter for DHCPv6 can be replaced
// with the custom one.
TEST_F(IfaceMgrTest, setPacketFilter6) {
    // Create an instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Try to set NULL packet filter object and make sure it is rejected.
    boost::shared_ptr<PktFilter6Stub> custom_packet_filter;
    EXPECT_THROW(iface_mgr->setPacketFilter(custom_packet_filter),
                 isc::dhcp::InvalidPacketFilter);

    // Create valid object and check if it can be set.
    custom_packet_filter.reset(new PktFilter6Stub());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(iface_mgr->setPacketFilter(custom_packet_filter));

    // Try to open socket using IfaceMgr. It should call the openSocket()
    // function on the packet filter object we have set.
    IOAddress lo_addr("::1");
    int socket1 = 0;
    EXPECT_NO_THROW(
        socket1 = iface_mgr->openSocket(LOOPBACK_NAME, lo_addr,
                                        DHCP6_SERVER_PORT + 10000);
    );
    // Check that openSocket function has been actually called on the packet
    // filter object.
    EXPECT_EQ(1, custom_packet_filter->open_socket_count_);
    // Also check that the returned socket descriptor has an expected value.
    EXPECT_EQ(0, socket1);

    // Replacing current packet filter object, while there are sockets open,
    // is not allowed!
    EXPECT_THROW(iface_mgr->setPacketFilter(custom_packet_filter),
                 PacketFilterChangeDenied);

    // So, let's close the sockets and retry. Now it should succeed.
    iface_mgr->closeSockets();
    EXPECT_NO_THROW(iface_mgr->setPacketFilter(custom_packet_filter));
}

#if defined(OS_LINUX) || defined(OS_BSD)

// This test is only supported on Linux and BSD systems. It checks
// if it is possible to use the IfaceMgr to select the packet filter
// object which can be used to send direct responses to the host
// which doesn't have an address yet.
TEST_F(IfaceMgrTest, setMatchingPacketFilter) {

    // Create an instance of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr);

    // Let IfaceMgr figure out which Packet Filter to use when
    // direct response capability is not desired. It should pick
    // PktFilterInet on Linux.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(false));
    // The PktFilterInet is supposed to report lack of direct
    // response capability.
    EXPECT_FALSE(iface_mgr->isDirectResponseSupported());

    // There is working implementation of direct responses on Linux
    // and BSD (using PktFilterLPF and PktFilterBPF. When direct
    // responses are desired the object of this class should be set.
    EXPECT_NO_THROW(iface_mgr->setMatchingPacketFilter(true));
    // This object should report that direct responses are supported.
    EXPECT_TRUE(iface_mgr->isDirectResponseSupported());
}

// This test checks that it is not possible to open two sockets: IP/UDP
// and raw socket and bind to the same address and port. The
// raw socket should be opened together with the fallback IP/UDP socket.
// The fallback socket should fail to open when there is another IP/UDP
// socket bound to the same address and port. Failing to open the fallback
// socket should preclude the raw socket from being open.
TEST_F(IfaceMgrTest, checkPacketFilterRawSocket) {
    IOAddress lo_addr("127.0.0.1");
    int socket1 = -1, socket2 = -1;
    // Create two instances of IfaceMgr.
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr1(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr1);
    boost::scoped_ptr<NakedIfaceMgr> iface_mgr2(new NakedIfaceMgr());
    ASSERT_TRUE(iface_mgr2);

    // Let IfaceMgr figure out which Packet Filter to use when
    // direct response capability is not desired. It should pick
    // PktFilterInet.
    EXPECT_NO_THROW(iface_mgr1->setMatchingPacketFilter(false));
    // Let's open a loopback socket with handy unpriviliged port number
    socket1 = iface_mgr1->openSocket(LOOPBACK_NAME, lo_addr,
                                     DHCP4_SERVER_PORT + 10000);

    EXPECT_GE(socket1, 0);

    // Then the second use PkFilterLPF mode
    EXPECT_NO_THROW(iface_mgr2->setMatchingPacketFilter(true));

    // The socket is open and bound. Another attempt to open socket and
    // bind to the same address and port should result in an exception.
    EXPECT_THROW(
        socket2 = iface_mgr2->openSocket(LOOPBACK_NAME, lo_addr,
                                         DHCP4_SERVER_PORT + 10000),
        isc::dhcp::SocketConfigError
    );
    // Surprisingly we managed to open another socket. We have to close it
    // to prevent resource leak.
    if (socket2 >= 0) {
        close(socket2);
        ADD_FAILURE() << "Two sockets opened and bound to the same IP"
            " address and UDP port";
    }

    if (socket1 >= 0) {
        close(socket1);
    }
}

#else

// Note: This test will only run on non-Linux and non-BSD systems.
// This test checks whether it is possible to use IfaceMgr to figure
// out which Packet Filter object should be used when direct responses
// to hosts, having no address assigned are desired or not desired.
// Since direct responses aren't supported on systems other than Linux
// and BSD the function under test should always set object of
// PktFilterInet type as current Packet Filter. This object does not
//support direct responses. Once implementation is added on systems
// other than BSD and Linux the OS specific version of the test will
// be removed.
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
    IOAddress lo_addr("127.0.0.1");
    // Use unprivileged port (it's convenient for running tests as non-root).
    int socket1 = 0;

    EXPECT_NO_THROW(
        socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr,
                                       DHCP4_SERVER_PORT + 10000);
    );

    EXPECT_GE(socket1, 0);

    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 1234));
    pkt->setIface(LOOPBACK_NAME);
    pkt->setIndex(LOOPBACK_INDEX);

    // Expect that we get the socket that we just opened.
    EXPECT_EQ(socket1, ifacemgr->getSocket(pkt).sockfd_);

    close(socket1);
}

// This test verifies that IPv4 sockets are open on all interfaces (except
// loopback), when interfaces are up, running and active (not disabled from
// the DHCP configuration).
TEST_F(IfaceMgrTest, openSockets4) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    // Use the custom packet filter object. This object mimics the socket
    // opening operation - the real socket is not open.
    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Simulate opening sockets using the dummy packet filter.
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0));

    // Expect that the sockets are open on both eth0 and eth1.
    EXPECT_EQ(1, ifacemgr.getIface("eth0")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(ETH0_INDEX)->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface("eth1")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(ETH1_INDEX)->getSockets().size());
    // Socket shouldn't have been opened on loopback.
    EXPECT_TRUE(ifacemgr.getIface("lo")->getSockets().empty());
    EXPECT_TRUE(ifacemgr.getIface(LO_INDEX)->getSockets().empty());
}

// This test verifies that IPv4 sockets are open on the loopback interface
// when the loopback is active and allowed.
TEST_F(IfaceMgrTest, openSockets4Loopback) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    // Allow the loopback interface.
    ifacemgr.setAllowLoopBack(true);

    // Make the loopback interface active.
    ifacemgr.getIface("lo")->inactive4_ = false;

    // Use the custom packet filter object. This object mimics the socket
    // opening operation - the real socket is not open.
    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Simulate opening sockets using the dummy packet filter.
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0));

    // Expect that the sockets are open on all interfaces.
    EXPECT_EQ(1, ifacemgr.getIface("eth0")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(ETH0_INDEX)->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface("eth1")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(ETH1_INDEX)->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface("lo")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(LO_INDEX)->getSockets().size());
}

// This test verifies that the socket is not open on the interface which is
// down, but sockets are open on all other non-loopback interfaces.
TEST_F(IfaceMgrTest, openSockets4IfaceDown) {
    IfaceMgrTestConfig config(true);

    // Boolean parameters specify that eth0 is:
    // - not a loopback
    // - is "down" (not up)
    // - is not running
    // - is active (is not inactive)
    config.setIfaceFlags("eth0", FlagLoopback(false), FlagUp(false),
                         FlagRunning(false), FlagInactive4(false),
                         FlagInactive6(false));
    ASSERT_FALSE(IfaceMgr::instance().getIface("eth0")->flag_up_);
    ASSERT_FALSE(IfaceMgr::instance().getIface(ETH0_INDEX)->flag_up_);

    // Install an error handler before trying to open sockets. This handler
    // should be called when the IfaceMgr fails to open socket on an interface
    // on which the server is configured to listen.
    isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
        std::bind(&IfaceMgrTest::ifaceMgrErrorHandler, this, ph::_1);

    ASSERT_NO_THROW(IfaceMgr::instance().openSockets4(DHCP4_SERVER_PORT, true,
                                                      error_handler));
    // Since the interface is down, an attempt to open a socket should result
    // in error.
    EXPECT_EQ(1, errors_count_);

    // There should be no socket on eth0 open, because interface was down.
    EXPECT_TRUE(IfaceMgr::instance().getIface("eth0")->getSockets().empty());
    EXPECT_TRUE(IfaceMgr::instance().getIface(ETH0_INDEX)->getSockets().empty());

    // Expecting that the socket is open on eth1 because it was up, running
    // and active.
    EXPECT_EQ(2, IfaceMgr::instance().getIface("eth1")->getSockets().size());
    EXPECT_EQ(2, IfaceMgr::instance().getIface(ETH1_INDEX)->getSockets().size());
    // Same for eth1961.
    EXPECT_EQ(1, IfaceMgr::instance().getIface("eth1961")->getSockets().size());
    EXPECT_EQ(1, IfaceMgr::instance().getIface(ETH1961_INDEX)->getSockets().size());
    // Never open socket on loopback interface.
    EXPECT_TRUE(IfaceMgr::instance().getIface("lo")->getSockets().empty());
    EXPECT_TRUE(IfaceMgr::instance().getIface(LO_INDEX)->getSockets().empty());
}

// This test verifies that the socket is not open on the interface which is
// disabled from the DHCP configuration, but sockets are open on all other
// non-loopback interfaces.
TEST_F(IfaceMgrTest, openSockets4IfaceInactive) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Boolean parameters specify that eth1 is:
    // - not a loopback
    // - is up
    // - is running
    // - is inactive
    ifacemgr.setIfaceFlags("eth1", false, true, true, true, false);
    ASSERT_TRUE(ifacemgr.getIface("eth1")->inactive4_);
    ASSERT_TRUE(ifacemgr.getIface(ETH1_INDEX)->inactive4_);
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0));

    // The socket on eth0 should be open because interface is up, running and
    // active (not disabled through DHCP configuration, for example).
    EXPECT_EQ(1, ifacemgr.getIface("eth0")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(ETH0_INDEX)->getSockets().size());
    // There should be no socket open on eth1 because it was marked inactive.
    EXPECT_TRUE(ifacemgr.getIface("eth1")->getSockets().empty());
    EXPECT_TRUE(ifacemgr.getIface(ETH1_INDEX)->getSockets().empty());
    // Sockets are not open on loopback interfaces too.
    EXPECT_TRUE(ifacemgr.getIface("lo")->getSockets().empty());
    EXPECT_TRUE(ifacemgr.getIface(LO_INDEX)->getSockets().empty());
}

// Test that exception is thrown when trying to bind a new socket to the port
// and address which is already in use by another socket.
TEST_F(IfaceMgrTest, openSockets4NoErrorHandler) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Open socket on eth1. The openSockets4 should detect that this
    // socket has been already open and an attempt to open another socket
    // and bind to this address and port should fail.
    ASSERT_NO_THROW(ifacemgr.openSocket("eth1", IOAddress("192.0.2.3"),
                                        DHCP4_SERVER_PORT));

    // The function throws an exception when it tries to open a socket
    // and bind it to the address in use.
    EXPECT_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0),
                 isc::dhcp::SocketConfigError);
}

// Test that the external error handler is called when trying to bind a new
// socket to the address and port being in use. The sockets on the other
// interfaces should open just fine.
TEST_F(IfaceMgrTest, openSocket4ErrorHandler) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Open socket on eth0.
    ASSERT_NO_THROW(ifacemgr.openSocket("eth0", IOAddress("10.0.0.1"),
                                        DHCP4_SERVER_PORT));

    // Install an error handler before trying to open sockets. This handler
    // should be called when the IfaceMgr fails to open socket on eth0.
    isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
        std::bind(&IfaceMgrTest::ifaceMgrErrorHandler, this, ph::_1);
    // The openSockets4 should detect that there is another socket already
    // open and bound to the same address and port. An attempt to open
    // another socket and bind to this address and port should fail.
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, error_handler));
    // We expect that an error occurred when we tried to open a socket on
    // eth0, but the socket on eth1 should open just fine.
    EXPECT_EQ(1, errors_count_);

    // Reset errors count.
    errors_count_ = 0;

    // Now that we have two sockets open, we can try this again but this time
    // we should get two errors: one when opening a socket on eth0, another one
    // when opening a socket on eth1.
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, error_handler));
    EXPECT_EQ(2, errors_count_);
}

// Test that no exception is thrown when a port is already bound but skip open
// flag is provided.
TEST_F(IfaceMgrTest, openSockets4SkipOpen) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Open socket on eth1. The openSockets4 should detect that this
    // socket has been already open and an attempt to open another socket
    // and bind to this address and port should fail.
    ASSERT_NO_THROW(ifacemgr.openSocket("eth1", IOAddress("192.0.2.3"),
                                        DHCP4_SERVER_PORT));

    // The function doesn't throw an exception when it tries to open a socket
    // and bind it to the address in use but the skip open flag is provided.
    EXPECT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0, true));

    // Check that the other port is bound.
    EXPECT_TRUE(ifacemgr.hasOpenSocket(IOAddress("10.0.0.1")));
}

// This test verifies that the function correctly checks that the v4 socket is
// open and bound to a specific address.
TEST_F(IfaceMgrTest, hasOpenSocketForAddress4) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    // Use the custom packet filter object. This object mimics the socket
    // opening operation - the real socket is not open.
    boost::shared_ptr<TestPktFilter> custom_packet_filter(new TestPktFilter());
    ASSERT_TRUE(custom_packet_filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(custom_packet_filter));

    // Simulate opening sockets using the dummy packet filter.
    ASSERT_NO_THROW(ifacemgr.openSockets4(DHCP4_SERVER_PORT, true, 0));

    // Expect that the sockets are open on both eth0 and eth1.
    ASSERT_EQ(1, ifacemgr.getIface("eth0")->getSockets().size());
    ASSERT_EQ(1, ifacemgr.getIface(ETH0_INDEX)->getSockets().size());
    ASSERT_EQ(1, ifacemgr.getIface("eth1")->getSockets().size());
    ASSERT_EQ(1, ifacemgr.getIface(ETH1_INDEX)->getSockets().size());
    // Socket shouldn't have been opened on loopback.
    ASSERT_TRUE(ifacemgr.getIface("lo")->getSockets().empty());
    ASSERT_TRUE(ifacemgr.getIface(LO_INDEX)->getSockets().empty());

    // Check that there are sockets bound to addresses that we have
    // set for interfaces.
    EXPECT_TRUE(ifacemgr.hasOpenSocket(IOAddress("192.0.2.3")));
    EXPECT_TRUE(ifacemgr.hasOpenSocket(IOAddress("10.0.0.1")));
    // Check that there is no socket for the address which is not
    // configured on any interface.
    EXPECT_FALSE(ifacemgr.hasOpenSocket(IOAddress("10.1.1.1")));

    // Check that v4 sockets are open, but no v6 socket is open.
    EXPECT_TRUE(ifacemgr.hasOpenSocket(AF_INET));
    EXPECT_FALSE(ifacemgr.hasOpenSocket(AF_INET6));
}

// This test checks that the sockets are open and bound to link local addresses
// only, if unicast addresses are not specified.
TEST_F(IfaceMgrTest, openSockets6LinkLocal) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that the number of sockets is correct on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0);

    // Sockets on eth0 should be bound to link-local and should not be bound
    // to global unicast address, even though this address is configured on
    // the eth0.
    EXPECT_TRUE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    // Socket on eth1 should be bound to link local only.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
    EXPECT_TRUE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that the sockets are open on the loopback interface
// when the loopback is active and allowed.
TEST_F(IfaceMgrTest, openSockets6Loopback) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    // Allow the loopback interface.
    ifacemgr.setAllowLoopBack(true);

    // Make the loopback interface active.
    ifacemgr.getIface("lo")->inactive6_ = false;

    // The loopback interface has no link-local (as for Linux but not BSD)
    // so add one.
    ifacemgr.getIface("lo")->addUnicast(IOAddress("::1"));

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that the loopback interface has at least an open socket.
    EXPECT_EQ(1, ifacemgr.getIface("lo")->getSockets().size());
    EXPECT_EQ(1, ifacemgr.getIface(LO_INDEX)->getSockets().size());

    // This socket should be bound to ::1
    EXPECT_TRUE(ifacemgr.isBound("lo", "::1"));
}

// This test checks that socket is not open on the interface which doesn't
// have a link-local address.
TEST_F(IfaceMgrTest, openSockets6NoLinkLocal) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Remove a link local address from eth0. If there is no link-local
    // address, the socket should not open.
    ASSERT_TRUE(ifacemgr.getIface("eth0")->
                delAddress(IOAddress("fe80::3a60:77ff:fed5:cdef")));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that the number of sockets is correct on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    // The third parameter specifies that the number of link-local
    // addresses for eth0 is equal to 0.
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 0, 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 0, 0);
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0, 1);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0, 1);

    // There should be no sockets open on eth0 because it neither has
    // link-local nor global unicast addresses.
    EXPECT_FALSE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    // Socket on eth1 should be bound to link local only.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_FALSE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that socket is open on the non-multicast-capable
// interface. This socket simply doesn't join multicast group.
TEST_F(IfaceMgrTest, openSockets6NotMulticast) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Make eth0 multicast-incapable.
    ifacemgr.getIface("eth0")->flag_multicast_ = false;

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that the number of sockets is correct on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0);

    // Sockets on eth0 should be bound to link-local and should not be bound
    // to global unicast address, even though this address is configured on
    // the eth0.
    EXPECT_TRUE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    // The eth0 is not a multicast-capable interface, so the socket should
    // not be bound to the multicast address.
    EXPECT_FALSE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
    // Socket on eth1 should be bound to link local only.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
    // on eth1.
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that the sockets are opened and bound to link local
// and unicast addresses which have been explicitly specified.
TEST_F(IfaceMgrTest, openSockets6Unicast) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Configure the eth0 to open socket on the unicast address, apart
    // from link-local address.
    ifacemgr.getIface("eth0")->addUnicast(IOAddress("2001:db8:1::1"));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that we have correct number of sockets on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 1); // one unicast address.
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 1);
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0);

    // eth0 should have two sockets, one bound to link-local, another one
    // bound to unicast address.
    EXPECT_TRUE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_TRUE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    // eth1 should have one socket, bound to link-local address.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
    EXPECT_TRUE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that the socket is open and bound to a global unicast
// address if the link-local address does not exist for the particular
// interface.
TEST_F(IfaceMgrTest, openSockets6UnicastOnly) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Configure the eth0 to open socket on the unicast address, apart
    // from link-local address.
    ifacemgr.getIface("eth0")->addUnicast(IOAddress("2001:db8:1::1"));
    // Explicitly remove the link-local address from eth0.
    ASSERT_TRUE(ifacemgr.getIface("eth0")->
                delAddress(IOAddress("fe80::3a60:77ff:fed5:cdef")));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that we have correct number of sockets on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 1, 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 1, 0);
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0);

    // The link-local address is not present on eth0. Therefore, no socket
    // must be bound to this address, nor to multicast address.
    EXPECT_FALSE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
    // There should be one socket bound to unicast address.
    EXPECT_TRUE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    // eth1 should have one socket, bound to link-local address.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that no sockets are open for the interface which is down.
TEST_F(IfaceMgrTest, openSockets6IfaceDown) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Configure the eth0 to open socket on the unicast address, apart
    // from link-local address.
    ifacemgr.getIface("eth0")->addUnicast(IOAddress("2001:db8:1::1"));

    // Boolean parameters specify that eth0 is:
    // - not a loopback
    // - is "down" (not up)
    // - is not running
    // - is active for both v4 and v6
    ifacemgr.setIfaceFlags("eth0", false, false, false, false, false);

    // Install an error handler before trying to open sockets. This handler
    // should be called when the IfaceMgr fails to open socket on eth0.
    isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
        std::bind(&IfaceMgrTest::ifaceMgrErrorHandler, this, ph::_1);

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT,
                                                    error_handler));
    EXPECT_TRUE(success);

    // Opening socket on the interface which is not configured, should
    // result in error.
    EXPECT_EQ(1, errors_count_);

    // Check that we have correct number of sockets on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    // There should be no sockets on eth0 because interface is down.
    ASSERT_TRUE(ifacemgr.getIface("eth0")->getSockets().empty());
    ASSERT_TRUE(ifacemgr.getIface(ETH0_INDEX)->getSockets().empty());
    checkSocketsCount6(*ifacemgr.getIface("eth1"), 0);
    checkSocketsCount6(*ifacemgr.getIface(ETH1_INDEX), 0);

    // eth0 should have no sockets because the interface is down.
    EXPECT_FALSE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", "2001:db8:1::1"));
    EXPECT_FALSE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
    // eth1 should have one socket, bound to link-local address.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// This test checks that no sockets are open for the interface which is
// inactive.
TEST_F(IfaceMgrTest, openSockets6IfaceInactive) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Configure the eth0 to open socket on the unicast address, apart
    // from link-local address.
    ifacemgr.getIface("eth0")->addUnicast(IOAddress("2001:db8:1::1"));

    // Boolean parameters specify that eth1 is:
    // - not a loopback
    // - is up
    // - is running
    // - is active for v4
    // - is inactive for v6
    ifacemgr.setIfaceFlags("eth1", false, true, true, false, true);

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Check that we have correct number of sockets on each interface.
    checkSocketsCount6(*ifacemgr.getIface("lo"), 0);
    checkSocketsCount6(*ifacemgr.getIface(LO_INDEX), 0);
    checkSocketsCount6(*ifacemgr.getIface("eth0"), 1); // one unicast address
    checkSocketsCount6(*ifacemgr.getIface(ETH0_INDEX), 1);
    // There should be no sockets on eth1 because interface is inactive
    ASSERT_TRUE(ifacemgr.getIface("eth1")->getSockets().empty());
    ASSERT_TRUE(ifacemgr.getIface(ETH1_INDEX)->getSockets().empty());

    // eth0 should have one socket bound to a link-local address, another one
    // bound to unicast address.
    EXPECT_TRUE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_TRUE(ifacemgr.isBound("eth0", "2001:db8:1::1"));

    // eth1 shouldn't have a socket bound to link local address because
    // interface is inactive.
    EXPECT_FALSE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));
    EXPECT_FALSE(ifacemgr.isBound("eth1", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));

    // If we are on Linux, there is one more socket bound to ff02::1:2
#if defined OS_LINUX
    EXPECT_TRUE(ifacemgr.isBound("eth0", ALL_DHCP_RELAY_AGENTS_AND_SERVERS));
#endif
}

// Test that the openSockets6 function does not throw if there are no interfaces
// detected. This function is expected to return false.
TEST_F(IfaceMgrTest, openSockets6NoIfaces) {
    NakedIfaceMgr ifacemgr;
    // Remove existing interfaces.
    ifacemgr.getIfacesLst().clear();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // This value indicates if at least one socket opens. There are no
    // interfaces, so it should be set to false.
    bool socket_open = false;
    ASSERT_NO_THROW(socket_open = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_FALSE(socket_open);
}

// Test that the external error handler is called when trying to bind a new
// socket to the address and port being in use. The sockets on the other
// interfaces should open just fine.
TEST_F(IfaceMgrTest, openSockets6ErrorHandler) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Open multicast socket on eth0.
    ASSERT_NO_THROW(ifacemgr.openSocket("eth0",
                                        IOAddress("fe80::3a60:77ff:fed5:cdef"),
                                        DHCP6_SERVER_PORT, true));

    // Install an error handler before trying to open sockets. This handler
    // should be called when the IfaceMgr fails to open socket on eth0.
    isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
        std::bind(&IfaceMgrTest::ifaceMgrErrorHandler, this, ph::_1);
    // The openSockets6 should detect that a socket has been already
    // opened on eth0 and an attempt to open another socket and bind to
    // the same address and port should fail.
    ASSERT_NO_THROW(ifacemgr.openSockets6(DHCP6_SERVER_PORT, error_handler));
    // We expect that an error occurred when we tried to open a socket on
    // eth0, but the socket on eth1 should open just fine.
    EXPECT_EQ(1, errors_count_);

    // Reset errors count.
    errors_count_ = 0;

    // Now that we have two sockets open, we can try this again but this time
    // we should get two errors: one when opening a socket on eth0, another one
    // when opening a socket on eth1.
    ASSERT_NO_THROW(ifacemgr.openSockets6(DHCP6_SERVER_PORT, error_handler));
    EXPECT_EQ(2, errors_count_);
}

// Test that no exception is thrown when a port is already bound but skip open
// flag is provided.
TEST_F(IfaceMgrTest, openSockets6SkipOpen) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Open socket on eth0. The openSockets6 should detect that this
    // socket has been already open and an attempt to open another socket
    // and bind to this address and port should fail.
    ASSERT_NO_THROW(ifacemgr.openSocket("eth0",
                                        IOAddress("fe80::3a60:77ff:fed5:cdef"),
                                        DHCP6_SERVER_PORT, true));

    // The function doesn't throw an exception when it tries to open a socket
    // and bind it to the address in use but the skip open flag is provided.
    EXPECT_NO_THROW(ifacemgr.openSockets6(DHCP6_SERVER_PORT, 0, true));

    // Check that the other port is bound.
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));
}

// This test verifies that the function correctly checks that the v6 socket is
// open and bound to a specific address.
TEST_F(IfaceMgrTest, hasOpenSocketForAddress6) {
    NakedIfaceMgr ifacemgr;

    // Remove all real interfaces and create a set of dummy interfaces.
    ifacemgr.createIfaces();

    boost::shared_ptr<PktFilter6Stub> filter(new PktFilter6Stub());
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(ifacemgr.setPacketFilter(filter));

    // Simulate opening sockets using the dummy packet filter.
    bool success = false;
    ASSERT_NO_THROW(success = ifacemgr.openSockets6(DHCP6_SERVER_PORT));
    EXPECT_TRUE(success);

    // Make sure that the sockets are bound as expected.
    ASSERT_TRUE(ifacemgr.isBound("eth0", "fe80::3a60:77ff:fed5:cdef"));
    EXPECT_TRUE(ifacemgr.isBound("eth1", "fe80::3a60:77ff:fed5:abcd"));

    // There should be v6 sockets only, no v4 sockets.
    EXPECT_TRUE(ifacemgr.hasOpenSocket(AF_INET6));
    EXPECT_FALSE(ifacemgr.hasOpenSocket(AF_INET));

    // Check that there are sockets bound to the addresses we have configured
    // for interfaces.
    EXPECT_TRUE(ifacemgr.hasOpenSocket(IOAddress("fe80::3a60:77ff:fed5:cdef")));
    EXPECT_TRUE(ifacemgr.hasOpenSocket(IOAddress("fe80::3a60:77ff:fed5:abcd")));
    // Check that there is no socket bound to the address which hasn't been
    // configured on any interface.
    EXPECT_FALSE(ifacemgr.hasOpenSocket(IOAddress("fe80::3a60:77ff:feed:1")));
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
    EXPECT_EQ("192.0.2.6", addrs.begin()->get().toText());

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

    ASSERT_LT(Iface::MAX_MAC_LEN + 10, 255);

    uint8_t mac[Iface::MAX_MAC_LEN+10];
    for (uint8_t i = 0; i < Iface::MAX_MAC_LEN + 10; i++) {
        mac[i] = 255 - i;
    }

    EXPECT_EQ("foo", iface.getName());
    EXPECT_EQ(1234, iface.getIndex());

    // MAC is too long. Exception should be thrown and
    // MAC length should not be set.
    EXPECT_THROW(
        iface.setMac(mac, Iface::MAX_MAC_LEN + 1),
        OutOfRange
    );

    // MAC length should stay not set as exception was thrown.
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
    SocketInfo sock1(IOAddress("192.0.2.56"), DHCP4_SERVER_PORT + 7, 7);
    EXPECT_EQ(7, sock1.sockfd_);
    EXPECT_EQ(-1, sock1.fallbackfd_);
    EXPECT_EQ("192.0.2.56", sock1.addr_.toText());
    EXPECT_EQ(AF_INET, sock1.family_);
    EXPECT_EQ(DHCP4_SERVER_PORT + 7, sock1.port_);

    // Check that non-default value of the fallback socket descriptor is set
    SocketInfo sock2(IOAddress("192.0.2.53"), DHCP4_SERVER_PORT + 8, 8, 10);
    EXPECT_EQ(8, sock2.sockfd_);
    EXPECT_EQ(10, sock2.fallbackfd_);
    EXPECT_EQ("192.0.2.53", sock2.addr_.toText());
    EXPECT_EQ(AF_INET, sock2.family_);
    EXPECT_EQ(DHCP4_SERVER_PORT + 8, sock2.port_);

    // Check that socketinfo for IPv6 socket is functional
    SocketInfo sock3(IOAddress("2001:db8:1::56"), DHCP4_SERVER_PORT + 9, 9);
    EXPECT_EQ(9, sock3.sockfd_);
    EXPECT_EQ(-1, sock3.fallbackfd_);
    EXPECT_EQ("2001:db8:1::56", sock3.addr_.toText());
    EXPECT_EQ(AF_INET6, sock3.family_);
    EXPECT_EQ(DHCP4_SERVER_PORT + 9, sock3.port_);

    // Now let's test if IfaceMgr handles socket info properly
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());
    IfacePtr loopback = ifacemgr->getIface(LOOPBACK_NAME);
    ASSERT_TRUE(loopback);
    loopback->addSocket(sock1);
    loopback->addSocket(sock2);
    loopback->addSocket(sock3);

    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REPLY, 123456));

    // pkt6 does not have interface set yet
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        IfaceNotFound
    );

    // Try to send over non-existing interface
    pkt6->setIface("nosuchinterface45");
    pkt6->setIndex(12345);
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        IfaceNotFound
    );

    // Index is now checked first
    pkt6->setIface(LOOPBACK_NAME);
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        IfaceNotFound
    );

    // This will work
    pkt6->setIndex(LOOPBACK_INDEX);
    EXPECT_EQ(9, ifacemgr->getSocket(pkt6));

    bool deleted = false;
    EXPECT_NO_THROW(
        deleted = ifacemgr->getIface(LOOPBACK_NAME)->delSocket(9);
    );
    EXPECT_EQ(true, deleted);

    // It should throw again, there's no usable socket anymore
    EXPECT_THROW(
        ifacemgr->getSocket(pkt6),
        SocketNotFound
    );

    // Repeat for pkt4
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 1));

    // pkt4 does not have interface set yet.
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        IfaceNotFound
    );

    // Try to send over non-existing interface.
    pkt4->setIface("nosuchinterface45");
    pkt4->setIndex(12345);
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        IfaceNotFound
    );

    // Index is now checked first.
    pkt4->setIface(LOOPBACK_NAME);
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        IfaceNotFound
    );

    // Socket info is set, packet has well defined interface. It should work.
    pkt4->setIndex(LOOPBACK_INDEX);
    EXPECT_EQ(7, ifacemgr->getSocket(pkt4).sockfd_);

    // Set the local address to check if the socket for this address will
    // be returned.
    pkt4->setLocalAddr(IOAddress("192.0.2.56"));
    EXPECT_EQ(7, ifacemgr->getSocket(pkt4).sockfd_);

    // Modify the local address and expect that the other socket will be
    // returned.
    pkt4->setLocalAddr(IOAddress("192.0.2.53"));
    EXPECT_EQ(8, ifacemgr->getSocket(pkt4).sockfd_);

    EXPECT_NO_THROW(
        ifacemgr->getIface(LOOPBACK_NAME)->delSocket(7);
        ifacemgr->getIface(LOOPBACK_NAME)->delSocket(8);
    );

    // It should throw again, there's no usable socket anymore.
    EXPECT_THROW(
        ifacemgr->getSocket(pkt4),
        SocketNotFound
    );
}

#if defined(OS_BSD)
#include <net/if_dl.h>
#endif

#include <sys/socket.h>
#include <net/if.h>
#include <ifaddrs.h>

/// @brief Checks the index of this interface
/// @param iface Kea interface structure to be checked
/// @param ifptr original structure returned by getifaddrs
/// @return true if index is returned properly
bool
checkIfIndex(const Iface & iface,
             struct ifaddrs *& ifptr) {
    return (iface.getIndex() == if_nametoindex(ifptr->ifa_name));
}

/// @brief Checks if the interface has proper flags set
/// @param iface Kea interface structure to be checked
/// @param ifptr original structure returned by getifaddrs
/// @return true if flags are set properly
bool
checkIfFlags(const Iface & iface,
             struct ifaddrs *& ifptr) {
        bool flag_loopback_ = ifptr->ifa_flags & IFF_LOOPBACK;
        bool flag_up_ = ifptr->ifa_flags & IFF_UP;
        bool flag_running_ = ifptr->ifa_flags & IFF_RUNNING;
        bool flag_multicast_ = ifptr->ifa_flags & IFF_MULTICAST;

    return ((iface.flag_loopback_ == flag_loopback_) &&
                        (iface.flag_up_ == flag_up_) &&
                        (iface.flag_running_ == flag_running_) &&
                        (iface.flag_multicast_ == flag_multicast_));
}

/// @brief Checks if MAC Address/IP Addresses are properly well formed
/// @param iface Kea interface structure to be checked
/// @param ifptr original structure returned by getifaddrs
/// @return true if addresses are returned properly
bool
checkIfAddrs(const Iface & iface, struct ifaddrs *& ifptr) {
    const unsigned char * p = 0;
#if defined(OS_LINUX)
    // Workaround for Linux ...
    if(ifptr->ifa_data != 0) {
        // We avoid localhost as it has no MAC Address
        if (!strncmp(iface.getName().c_str(), "lo", 2)) {
            return (true);
        }

        struct ifreq ifr;
        memset(& ifr.ifr_name, 0, sizeof ifr.ifr_name);
        strncpy(ifr.ifr_name, iface.getName().c_str(), sizeof(ifr.ifr_name) - 1);

        int s = -1; // Socket descriptor

        if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            isc_throw(Unexpected, "Cannot create AF_INET socket");
        }

        if (ioctl(s, SIOCGIFHWADDR, & ifr) < 0) {
            close(s);
            isc_throw(Unexpected, "Cannot set SIOCGIFHWADDR flag");
        }

        p = reinterpret_cast<uint8_t *>(ifr.ifr_ifru.ifru_hwaddr.sa_data);

        close(s);

        /// @todo: Check MAC address length. For some interfaces it is
        /// different than 6. Some have 0, while some exotic ones (like
        /// infiniband) have 20.
        return (!memcmp(p, iface.getMac(), iface.getMacLen()));
    }
#endif

    if(!ifptr->ifa_addr) {
        return (false);
    }

    switch(ifptr->ifa_addr->sa_family) {
#if defined(OS_BSD)
        case AF_LINK: {
            // We avoid localhost as it has no MAC Address
            if (!strncmp(iface.getName().c_str(), "lo", 2)) {
                return (true);
            }

            struct sockaddr_dl * hwdata =
                   reinterpret_cast<struct sockaddr_dl *>(ifptr->ifa_addr);
            p = reinterpret_cast<uint8_t *>(LLADDR(hwdata));

            // Extract MAC address length
            if (hwdata->sdl_alen != iface.getMacLen()) {
                return (false);
            }

            return (!memcmp(p, iface.getMac(), hwdata->sdl_alen));
        }
#endif
        case AF_INET: {
            struct sockaddr_in * v4data =
                   reinterpret_cast<struct sockaddr_in *>(ifptr->ifa_addr);
            p = reinterpret_cast<uint8_t *>(& v4data->sin_addr);

            IOAddress addrv4 = IOAddress::fromBytes(AF_INET, p);

            for (auto const& a :iface.getAddresses()) {
                if(a.get().isV4() && (a.get()) == addrv4) {
                    return (true);
                }
            }

            return (false);
        }
        case AF_INET6: {
            struct sockaddr_in6 * v6data =
                   reinterpret_cast<struct sockaddr_in6 *>(ifptr->ifa_addr);
            p = reinterpret_cast<uint8_t *>(& v6data->sin6_addr);

            IOAddress addrv6 = IOAddress::fromBytes(AF_INET6, p);

            for (auto const&  a : iface.getAddresses()) {
                if (a.get().isV6() && (a.get() == addrv6)) {
                    return (true);
                }
            }

            return (false);
        }
        default:
            return (true);
    }
}

/// This test checks that the IfaceMgr detects interfaces correctly and
/// that detected interfaces have correct properties.
TEST_F(IfaceMgrTest, detectIfaces) {
    NakedIfaceMgr ifacemgr;

    // We are using struct ifaddrs as it is the only good portable one
    // ifreq and ioctls are far from portable. For BSD ifreq::ifa_flags field
    // is only a short which, nowadays, can be negative
    struct ifaddrs *iflist = 0, *ifptr = 0;
    ASSERT_EQ(0, getifaddrs(&iflist))
        << "Unit test failed to detect interfaces.";

    // Go over all interfaces detected by the unit test and see if they
    // match with the interfaces detected by IfaceMgr.
    for (ifptr = iflist; ifptr != 0; ifptr = ifptr->ifa_next) {
        // When more than one IPv4 address is assigned to the particular
        // physical interface, virtual interfaces may be created for each
        // additional IPv4 address. For example, when multiple addresses
        // are assigned to the eth0 interface, additional virtual interfaces
        // will be eth0:0, eth0:1 etc. This is the case on some Linux
        // distributions. The getifaddrs will return virtual interfaces,
        // with single address each, but the Netlink-based implementation
        // (used by IfaceMgr) will rather hold a list of physical interfaces
        // with multiple IPv4 addresses assigned. This means that the test
        // can't use a name of the interface returned by getifaddrs to match
        // with the interface name held by IfaceMgr. Instead, we use the
        // index of the interface because the virtual interfaces have the
        // same indexes as the physical interfaces.
        IfacePtr i = ifacemgr.getIface(if_nametoindex(ifptr->ifa_name));

        // If the given interface was also detected by the IfaceMgr,
        // check that its properties are correct.
        if (i != NULL) {
            // Check if interface index is reported properly
            EXPECT_TRUE(checkIfIndex(*i, ifptr))
                << "Non-matching index of the detected interface "
                << i->getName();

            // Check if flags are reported properly
            EXPECT_TRUE(checkIfFlags(*i, ifptr))
                << "Non-matching flags of the detected interface "
                << i->getName();

            // Check if addresses are reported properly
            EXPECT_TRUE(checkIfAddrs(*i, ifptr))
                << "Non-matching addresses on the detected interface "
                << i->getName();

        } else {
            // The interface detected here seems to be missing in the
            // IfaceMgr.
            ADD_FAILURE() << "Interface " << ifptr->ifa_name
                          << " not detected by the Interface Manager";
        }
    }

    freeifaddrs(iflist);
    iflist = 0;
}

volatile bool callback_ok;
volatile bool callback2_ok;

void my_callback(int /* fd */) {
    callback_ok = true;
}

void my_callback2(int /* fd */) {
    callback2_ok = true;
}

// Tests if a single external socket and its callback can be passed and
// it is supported properly by receive4() method.
TEST_F(IfaceMgrTest, SingleExternalSocket4) {

    callback_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));

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

    ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
}

// Tests if multiple external sockets and their callbacks can be passed and
// it is supported properly by receive4() method.
TEST_F(IfaceMgrTest, MultipleExternalSockets4) {

    callback_ok = false;
    callback2_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create first pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    // Let's create a second pipe and register it as well
    int secondpipe[2];
    EXPECT_TRUE(pipe(secondpipe) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0], my_callback2));

    Pkt4Ptr pkt4;
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // Our callbacks should not be called this time (there was no data)
    EXPECT_FALSE(callback_ok);
    EXPECT_FALSE(callback2_ok);

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // Now, send some data over the first pipe (38 bytes)
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // There was some data, so this time callback should be called
    EXPECT_TRUE(callback_ok);
    EXPECT_FALSE(callback2_ok);

    // Read the data sent, because our test callbacks are too dumb to actually
    // do it. We don't care about the content read, because we're testing
    // the callbacks, not pipes.
    char buf[80];
    EXPECT_EQ(38, read(pipefd[0], buf, 80));

    // Clear the status...
    callback_ok = false;
    callback2_ok = false;

    // And try again, using the second pipe
    EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // There was some data, so this time callback should be called
    EXPECT_FALSE(callback_ok);
    EXPECT_TRUE(callback2_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);

    close(secondpipe[1]);
    close(secondpipe[0]);
}

// Tests if existing external socket can be deleted and that such deletion does
// not affect any other existing sockets. Tests uses receive4()
TEST_F(IfaceMgrTest, DeleteExternalSockets4) {

    callback_ok = false;
    callback2_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create first pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    // Let's create a second pipe and register it as well
    int secondpipe[2];
    EXPECT_TRUE(pipe(secondpipe) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0], my_callback2));

    // Now delete the first session socket
    EXPECT_NO_THROW(ifacemgr->deleteExternalSocket(pipefd[0]));

    // Now check whether the second callback is still functional
    EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    Pkt4Ptr pkt4;
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt4);

    // There was some data, so this time callback should be called
    EXPECT_FALSE(callback_ok);
    EXPECT_TRUE(callback2_ok);

    // Let's reset the status
    callback_ok = false;
    callback2_ok = false;

    // Now let's send something over the first callback that was unregistered.
    // We should NOT receive any callback.
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // Now check that the first callback is NOT called.
    ASSERT_NO_THROW(pkt4 = ifacemgr->receive4(1));
    EXPECT_FALSE(callback_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);

    close(secondpipe[1]);
    close(secondpipe[0]);
}

// Tests that an existing external socket that becomes invalid
// is detected and purged, without affecting other sockets.
// Tests uses receive4() without queuing.
TEST_F(IfaceMgrTest, purgeExternalSockets4Direct) {
    purgeExternalSockets4Test();
}


// Tests that an existing external socket that becomes invalid
// is detected and purged, without affecting other sockets.
// Tests uses receive4() with queuing.
TEST_F(IfaceMgrTest, purgeExternalSockets4Indirect) {
    purgeExternalSockets4Test(true);
}

// Tests if a single external socket and its callback can be passed and
// it is supported properly by receive6() method.
TEST_F(IfaceMgrTest, SingleExternalSocket6) {

    callback_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    Pkt6Ptr pkt6;
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // Our callback should not be called this time (there was no data)
    EXPECT_FALSE(callback_ok);

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // Now, send some data over pipe (38 bytes)
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // There was some data, so this time callback should be called
    EXPECT_TRUE(callback_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);
}

// Tests if multiple external sockets and their callbacks can be passed and
// it is supported properly by receive6() method.
TEST_F(IfaceMgrTest, MultipleExternalSockets6) {

    callback_ok = false;
    callback2_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create first pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    // Let's create a second pipe and register it as well
    int secondpipe[2];
    EXPECT_TRUE(pipe(secondpipe) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0], my_callback2));

    Pkt6Ptr pkt6;
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // Our callbacks should not be called this time (there was no data)
    EXPECT_FALSE(callback_ok);
    EXPECT_FALSE(callback2_ok);

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // Now, send some data over the first pipe (38 bytes)
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // There was some data, so this time callback should be called
    EXPECT_TRUE(callback_ok);
    EXPECT_FALSE(callback2_ok);

    // Read the data sent, because our test callbacks are too dumb to actually
    // do it. We don't care about the content read, because we're testing
    // the callbacks, not pipes.
    char buf[80];
    EXPECT_EQ(38, read(pipefd[0], buf, 80));

    // Clear the status...
    callback_ok = false;
    callback2_ok = false;

    // And try again, using the second pipe
    EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // There was some data, so this time callback should be called
    EXPECT_FALSE(callback_ok);
    EXPECT_TRUE(callback2_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);

    close(secondpipe[1]);
    close(secondpipe[0]);
}

// Tests if existing external socket can be deleted and that such deletion does
// not affect any other existing sockets. Tests uses receive6()
TEST_F(IfaceMgrTest, DeleteExternalSockets6) {

    callback_ok = false;
    callback2_ok = false;

    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // Create first pipe and register it as extra socket
    int pipefd[2];
    EXPECT_TRUE(pipe(pipefd) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(pipefd[0], my_callback));

    // Let's create a second pipe and register it as well
    int secondpipe[2];
    EXPECT_TRUE(pipe(secondpipe) == 0);
    EXPECT_NO_THROW(ifacemgr->addExternalSocket(secondpipe[0], my_callback2));

    // Now delete the first session socket
    EXPECT_NO_THROW(ifacemgr->deleteExternalSocket(pipefd[0]));

    // Now check whether the second callback is still functional
    EXPECT_EQ(38, write(secondpipe[1], "Hi, this is a message sent over a pipe", 38));

    // ... and repeat
    Pkt6Ptr pkt6;
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));

    // IfaceMgr should not process control socket data as incoming packets
    EXPECT_FALSE(pkt6);

    // There was some data, so this time callback should be called
    EXPECT_FALSE(callback_ok);
    EXPECT_TRUE(callback2_ok);

    // Let's reset the status
    callback_ok = false;
    callback2_ok = false;

    // Now let's send something over the first callback that was unregistered.
    // We should NOT receive any callback.
    EXPECT_EQ(38, write(pipefd[1], "Hi, this is a message sent over a pipe", 38));

    // Now check that the first callback is NOT called.
    ASSERT_NO_THROW(pkt6 = ifacemgr->receive6(1));
    EXPECT_FALSE(callback_ok);

    // close both pipe ends
    close(pipefd[1]);
    close(pipefd[0]);

    close(secondpipe[1]);
    close(secondpipe[0]);
}

// Tests that an existing external socket that becomes invalid
// is detected and purged, without affecting other sockets.
// Tests uses receive6() without queuing.
TEST_F(IfaceMgrTest, purgeExternalSockets6Direct) {
    purgeExternalSockets6Test();
}


// Tests that an existing external socket that becomes invalid
// is detected and purged, without affecting other sockets.
// Tests uses receive6() with queuing.
TEST_F(IfaceMgrTest, purgeExternalSockets6Indirect) {
    purgeExternalSockets6Test(true);
}

// Test checks if the unicast sockets can be opened.
// This test is now disabled, because there is no reliable way to test it. We
// can't even use loopback, because openSockets() skips loopback interface
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
    IfacePtr iface = ifacemgr->getIface("eth0");
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

// Checks if there is a protection against unicast duplicates.
TEST_F(IfaceMgrTest, unicastDuplicates) {
    NakedIfaceMgr ifacemgr;

    IfacePtr iface = ifacemgr.getIface(LOOPBACK_NAME);
    if (!iface) {
        cout << "Local loopback interface not found. Skipping test. " << endl;
        return;
    }

    // Tell the interface that it should bind to this global interface
    // It is the first attempt so it should succeed
    EXPECT_NO_THROW(iface->addUnicast(IOAddress("2001:db8::1")));

    // Tell the interface that it should bind to this global interface
    // It is the second attempt so it should fail
    EXPECT_THROW(iface->addUnicast(IOAddress("2001:db8::1")), BadValue);
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
    int socket1 = ifacemgr->openSocket(LOOPBACK_NAME, lo_addr, 10547);
    EXPECT_GE(socket1, 0); // socket >= 0

    // Bind link-local address
    int socket2 = ifacemgr->openSocket(LOOPBACK_NAME, link_local, 10547);
    EXPECT_GE(socket2, 0);

    int socket3 = ifacemgr->openSocket(LOOPBACK_NAME, global, 10547);
    EXPECT_GE(socket3, 0);

    // Let's make sure those sockets are unique
    EXPECT_NE(socket1, socket2);
    EXPECT_NE(socket2, socket3);
    EXPECT_NE(socket3, socket1);

    // Create a packet
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, 123));
    pkt6->setIface(LOOPBACK_NAME);
    pkt6->setIndex(LOOPBACK_INDEX);

    // Check that packets sent to link-local will get socket bound to link local
    pkt6->setLocalAddr(global);
    pkt6->setRemoteAddr(dst_global);
    EXPECT_EQ(socket3, ifacemgr->getSocket(pkt6));

    // Check that packets sent to link-local will get socket bound to link local
    pkt6->setLocalAddr(link_local);
    pkt6->setRemoteAddr(dst_link_local);
    EXPECT_EQ(socket2, ifacemgr->getSocket(pkt6));

    // Close sockets here because the following tests will want to
    // open sockets on the same ports.
    ifacemgr->closeSockets();
}

// Verifies DHCPv4 behavior of configureDHCPPacketQueue()
TEST_F(IfaceMgrTest, configureDHCPPacketQueueTest4) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // First let's make sure there is no queue and no thread.
    ASSERT_FALSE(ifacemgr->getPacketQueue4());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    bool queue_enabled = false;
    // Given an empty pointer, we should default to no queue.
    data::ConstElementPtr queue_control;
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control));
    EXPECT_FALSE(queue_enabled);
    EXPECT_FALSE(ifacemgr->getPacketQueue4());
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Verify that calling startDHCPReceiver with no queue, does NOT start the thread.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Now let's try with a populated queue control, but with enable-queue = false.
    queue_control = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500, false);
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control));
    EXPECT_FALSE(queue_enabled);
    EXPECT_FALSE(ifacemgr->getPacketQueue4());
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Now let's enable the queue.
    queue_control = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500, true);
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control));
    ASSERT_TRUE(queue_enabled);
    // Verify we have correctly created the queue.
    CHECK_QUEUE_INFO(ifacemgr->getPacketQueue4(), "{ \"capacity\": 500, \"queue-type\": \""
                     << PacketQueueMgr4::DEFAULT_QUEUE_TYPE4 << "\", \"size\": 0 }");
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Calling startDHCPReceiver with a queue, should start the thread.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));
    ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());

    // Verify that calling startDHCPReceiver when the thread is running, throws.
    ASSERT_THROW(ifacemgr->startDHCPReceiver(AF_INET), InvalidOperation);

    // Create a disabled config.
    queue_control = makeQueueConfig(PacketQueueMgr4::DEFAULT_QUEUE_TYPE4, 500, false);

    // Trying to reconfigure with a running thread should throw.
    ASSERT_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control),
                 InvalidOperation);

    // We should still have our queue and the thread should still be running.
    EXPECT_TRUE(ifacemgr->getPacketQueue4());
    ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());

    // Now let's stop stop the thread.
    ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    // Stopping the thread should not destroy the queue.
    ASSERT_TRUE(ifacemgr->getPacketQueue4());

    // Reconfigure with the queue turned off.  We should have neither queue nor thread.
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control));
    EXPECT_FALSE(ifacemgr->getPacketQueue4());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
}

// Verifies DHCPv6 behavior of configureDHCPPacketQueue()
TEST_F(IfaceMgrTest, configureDHCPPacketQueueTest6) {
    scoped_ptr<NakedIfaceMgr> ifacemgr(new NakedIfaceMgr());

    // First let's make sure there is no queue and no thread.
    ASSERT_FALSE(ifacemgr->getPacketQueue6());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    bool queue_enabled = false;
    // Given an empty pointer, we should default to no queue.
    data::ConstElementPtr queue_control;
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET, queue_control));
    EXPECT_FALSE(queue_enabled);
    EXPECT_FALSE(ifacemgr->getPacketQueue6());
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Verify that calling startDHCPReceiver with no queue, does NOT start the thread.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET));
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Now let's try with a populated queue control, but with enable-queue = false.
    queue_control = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500, false);
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, queue_control));
    EXPECT_FALSE(queue_enabled);
    EXPECT_FALSE(ifacemgr->getPacketQueue6());
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Now let's enable the queue.
    queue_control = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500, true);
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, queue_control));
    ASSERT_TRUE(queue_enabled);
    // Verify we have correctly created the queue.
    CHECK_QUEUE_INFO(ifacemgr->getPacketQueue6(), "{ \"capacity\": 500, \"queue-type\": \""
                     << PacketQueueMgr6::DEFAULT_QUEUE_TYPE6 << "\", \"size\": 0 }");
    // configureDHCPPacketQueue() should never start the thread.
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());

    // Calling startDHCPReceiver with a queue, should start the thread.
    ASSERT_NO_THROW(ifacemgr->startDHCPReceiver(AF_INET6));
    ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());

    // Verify that calling startDHCPReceiver when the thread is running, throws.
    ASSERT_THROW(ifacemgr->startDHCPReceiver(AF_INET6), InvalidOperation);

    // Create a disabled config.
    queue_control = makeQueueConfig(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6, 500, false);

    // Trying to reconfigure with a running thread should throw.
    ASSERT_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, queue_control),
                 InvalidOperation);

    // We should still have our queue and the thread should still be running.
    EXPECT_TRUE(ifacemgr->getPacketQueue6());
    ASSERT_TRUE(ifacemgr->isDHCPReceiverRunning());

    // Now let's stop stop the thread.
    ASSERT_NO_THROW(ifacemgr->stopDHCPReceiver());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
    // Stopping the thread should not destroy the queue.
    ASSERT_TRUE(ifacemgr->getPacketQueue6());

    // Reconfigure with the queue turned off.  We should have neither queue nor thread.
    ASSERT_NO_THROW(queue_enabled = ifacemgr->configureDHCPPacketQueue(AF_INET6, queue_control));
    EXPECT_FALSE(ifacemgr->getPacketQueue6());
    ASSERT_FALSE(ifacemgr->isDHCPReceiverRunning());
}

}
