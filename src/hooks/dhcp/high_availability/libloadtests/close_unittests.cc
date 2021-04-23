// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the high availability hook library. In order to test
/// the load function, one must be able to pass it hook library
/// parameters. The the only way to populate these parameters is by
/// actually loading the library via HooksManager::loadLibraries().

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/option.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/network_state.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <hooks/callout_manager.h>
#include <process/daemon.h>
#include <util/buffer.h>
#include <util/watched_thread.h>

#include <gtest/gtest.h>

#include <boost/weak_ptr.hpp>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::util;

namespace {

/// @brief Structure that holds registered hook indexes.
struct TestHooks {
    /// @brief Index of dhcp4_srv_configured callout.
    int hook_index_dhcp4_srv_configured_;

    /// @brief Index of buffer4_receive callout.
    int hook_index_buffer4_receive_;

    /// @brief Index of leases4_committed callout.
    int hook_index_leases4_committed_;

    /// @brief Index of dhcp6_srv_configured callout.
    int hook_index_dhcp6_srv_configured_;

    /// @brief Index of buffer6_receive callout.
    int hook_index_buffer6_receive_;

    /// @brief Index of leases6_committed callout.
    int hook_index_leases6_committed_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_dhcp4_srv_configured_ =
            HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_buffer4_receive_ =
            HooksManager::registerHook("buffer4_receive");
        hook_index_leases4_committed_ =
            HooksManager::registerHook("leases4_committed");
        hook_index_dhcp6_srv_configured_ =
            HooksManager::registerHook("dhcp6_srv_configured");
        hook_index_buffer6_receive_ =
            HooksManager::registerHook("buffer6_receive");
        hook_index_leases6_committed_ =
            HooksManager::registerHook("leases6_committed");
    }
};

TestHooks testHooks;

/// @brief Test fixture for testing closing the HA library
class CloseHATest : public ::testing::Test {
public:
    /// @brief Constructor
    CloseHATest() {
    }

    /// @brief Destructor
    virtual ~CloseHATest() {
        HooksManager::prepareUnloadLibraries();
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture dtor) unloadLibraries failed" << endl;
        }
    }

    /// @brief Return HA configuration with three servers in JSON format.
    ///
    /// @param backup Flag to set this server as backup server.
    ConstElementPtr createValidJsonConfiguration(bool backup = false) const;

    /// @brief Run partners.
    ///
    /// Simulate partners by accepting connections. The HA will send
    /// lease updates and waits for answers so will own the query.
    void runPartners();

    /// @brief The watched thread.
    WatchedThreadPtr wthread_;
};

ConstElementPtr
CloseHATest::createValidJsonConfiguration(bool backup) const {
    std::ostringstream config_text;
    config_text <<
        "["
        "     {"
        "         \"this-server-name\": \"" << (!backup ? "server1" : "server2") << "\","
        "         \"mode\": \"passive-backup\","
        "         \"wait-backup-ack\": true,"
        "         \"peers\": ["
        "             {"
        "                 \"name\": \"server1\","
        "                 \"url\": \"http://127.0.0.1:18123/\","
        "                 \"role\": \"primary\""
        "             },"
        "             {"
        "                 \"name\": \"server2\","
        "                 \"url\": \"http://127.0.0.1:18124/\","
        "                 \"role\": \"backup\""
        "             },"
        "             {"
        "                 \"name\": \"server3\","
        "                 \"url\": \"http://127.0.0.1:18125/\","
        "                 \"role\": \"backup\""
        "             }"
        "         ]"
        "     }"
        "]";

    return (Element::fromJSON(config_text.str()));
}

void
CloseHATest::runPartners() {
    int accept_partner1 = -1;
    int accept_partner2 = -1;
    std::map<int, bool> readers;

    try {
        struct sockaddr_in partner;
        memset(&partner, 0, sizeof(partner));
        partner.sin_family =  AF_INET;
#ifdef HAVE_SA_LEN
        partner.sin_len = sizeof(partner);
#endif
        partner.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        socklen_t slen = sizeof(partner);

#define SA(x)   reinterpret_cast<const sockaddr*>(x)
        accept_partner1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (accept_partner1 < 0) {
            isc_throw(Unexpected, "socket1 " << strerror(errno));
        }
        if (fcntl(accept_partner1, F_SETFL, O_NONBLOCK) < 0) {
            isc_throw(Unexpected, "fcntl1 " << strerror(errno));
        }

        int reuse_addr = 1;
        if (setsockopt(accept_partner1, SOL_SOCKET, SO_REUSEADDR,
               (char *)&reuse_addr, sizeof(reuse_addr)) < 0) {
            isc_throw(Unexpected, "partner1 setsocketopt SO_REUSEADDR failed: " << strerror(errno));
        }

        partner.sin_port = htons(18124);
        if (::bind(accept_partner1, SA(&partner), slen) < 0) {
            isc_throw(Unexpected, "bind1 " << strerror(errno));
        }
        if (listen(accept_partner1, 1) < 0) {
            isc_throw(Unexpected, "listen1 " << strerror(errno));
        }

        accept_partner2 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (accept_partner2 < 0) {
            isc_throw(Unexpected, "socket2 " << strerror(errno));
        }
        if (fcntl(accept_partner2, F_SETFL, O_NONBLOCK) < 0) {
            isc_throw(Unexpected, "fcntl2 " << strerror(errno));
        }

        if (setsockopt(accept_partner2, SOL_SOCKET, SO_REUSEADDR,
               (char *)&reuse_addr, sizeof(reuse_addr)) < 0) {
            isc_throw(Unexpected, "partner2 setsocketopt SO_REUSEADDR failed: " << strerror(errno));
        }

        partner.sin_port = htons(18125);
        if (::bind(accept_partner2, SA(&partner), slen) < 0) {
            isc_throw(Unexpected, "bind2 " << strerror(errno));
        }
        if (listen(accept_partner2, 1) < 0) {
            isc_throw(Unexpected, "listen2 " << strerror(errno));
        }

        wthread_->markReady(WatchedThread::READY);

        for (;;) {
            int nfd;
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(wthread_->getWatchFd(WatchedThread::TERMINATE), &fds);
            nfd = wthread_->getWatchFd(WatchedThread::TERMINATE);
            FD_SET(accept_partner1, &fds);
            if (accept_partner1 > nfd) {
                nfd = accept_partner1;
            }
            FD_SET(accept_partner2, &fds);
            if (accept_partner2 > nfd) {
                nfd = accept_partner2;
            }
            for (auto reader : readers) {
                if (!reader.second) {
                    continue;
                }
                int fd = reader.first;
                FD_SET(fd, &fds);
                if (fd > nfd) {
                    nfd = fd;
                }
            }
            struct timeval tm;
            tm.tv_sec = tm.tv_usec = 0;
            int n = select(nfd + 1, &fds, 0, 0, &tm);
            if ((n < 0) && (errno == EINTR)) {
                cerr << "interrupted" << endl;
                continue;
            }
            if (FD_ISSET(wthread_->getWatchFd(WatchedThread::TERMINATE), &fds)) {
                break;
            }
            if (FD_ISSET(accept_partner1, &fds)) {
                int fd = accept(accept_partner1, 0, 0);
                if (fd < 0) {
                    cerr << "accept1 failed " << strerror(errno) << endl;
                } else {
                    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
                        cerr << "fcntl NONBLOCK " << strerror(errno) << endl;
                    }
                    readers[fd] = true;
                }
            }
            if (FD_ISSET(accept_partner2, &fds)) {
                int fd = accept(accept_partner2, 0, 0);
                if (fd < 0) {
                    cerr << "accept2 failed " << strerror(errno) << endl;
                } else {
                    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
                        cerr << "fcntl NONBLOCK " << strerror(errno) << endl;
                    }
                    readers[fd] = true;
                }
            }
            for (auto reader : readers) {
                if (!reader.second) {
                    continue;
                }
                int fd = reader.first;
                if (FD_ISSET(fd, &fds)) {
                    char buf[128];
                    int cc = read(fd, buf, 128);
                    if (cc < 0) {
                        cerr << "read " << strerror(errno) << endl;
                    }
                    if (cc == 0) {
                        readers[fd] = false;
                        close(fd);
                    }
                }
            }
        }
    } catch (const std::exception& ex) {
        wthread_->setError(ex.what());
    }

    wthread_->clearReady(WatchedThread::TERMINATE);
    if (accept_partner1 >= 0) {
        close(accept_partner1);
        accept_partner1 = -1;
    }
    if (accept_partner2 >= 0) {
        close(accept_partner2);
        accept_partner2 = -1;
    }
    for (auto reader : readers) {
        if (!reader.second) {
            continue;
        }
        int fd = reader.first;
        readers[fd] = false;
        close(fd);
    }
}

// Test that checks that the library can be loaded and unloaded from a DHCPv4
// active server.
// 1. Creates one active and 2 backup servers.
// 2. Check that the network state is reset and updated to expected state when
// creating the HAService by calling the dhcp4_srv_configured hook.
// 3. Send ha-heartbeat to make the server transition 'passive-backup' state.
// 4. Call buffer4_receive and leases4_committed hooks to make sure that the
// parked packet is owned strictly by the HA library.
// 5. Verify that releasing the query will release all resources.
// 6. Unload the library which should not have any dangling resources.
// 7. Verify that the network state is reset on unload.
TEST_F(CloseHATest, close4) {
    // Start partners.
    wthread_.reset(new WatchedThread());
    wthread_->start([this] () { runPartners(); });

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    // Load the library.
    HookLibsCollection libraries;
    libraries.push_back(make_pair(LIBDHCP_HA_SO, params));
    ASSERT_TRUE(HooksManager::loadLibraries(libraries));

    // Prepare objects.
    IOServicePtr io_service(new IOService());
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 12345));
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    query->setHWAddr(hwaddr);
    ASSERT_NO_THROW(query->pack());
    const OutputBuffer& buffer = query->getBuffer();
    query.reset(new Pkt4(reinterpret_cast<const uint8_t*>(buffer.getData()),
                         buffer.getLength()));

    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.1"), hwaddr,
                               static_cast<const uint8_t*>(0), 0,
                               60, 0, 1));
    Lease4CollectionPtr leases(new Lease4Collection());
    leases->push_back(lease);
    Lease4CollectionPtr deleted_leases(new Lease4Collection());

    // Check that the disabled state is reset on dhcp4_srv_configured.
    ASSERT_TRUE(network_state->isServiceEnabled());
    network_state->disableService(NetworkState::Origin::HA_COMMAND);
    ASSERT_FALSE(network_state->isServiceEnabled());

    // Start HA service.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_dhcp4_srv_configured_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("io_context", io_service);
        handle->setArgument("network_state", network_state);
        HooksManager::callCallouts(testHooks.hook_index_dhcp4_srv_configured_,
                                   *handle);
    }

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Pretend to be the partner.
    ConstElementPtr command = createCommand("ha-heartbeat", "dhcp4");
    ConstElementPtr response;
    EXPECT_TRUE(HooksManager::commandHandlersPresent("ha-heartbeat"));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("command", command);
        handle->setArgument("response", response);
        HooksManager::callCommandHandlers("ha-heartbeat", *handle);
        handle->getArgument("response", response);
    }
    int code = 0;
    ConstElementPtr arguments = parseAnswer(code, response);
    EXPECT_EQ(0, code);
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());
    ConstElementPtr state = arguments->get("state");
    ASSERT_TRUE(state);
    ASSERT_EQ(Element::string, state->getType());
    EXPECT_EQ("passive-backup", state->stringValue());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Submit packet.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_buffer4_receive_));
    {
        // Use the query callout handle.
        CalloutHandlePtr handle = query->getCalloutHandle();
        ScopedCalloutHandleState handle_state(handle);
        handle->setArgument("query4", query);

        // Park the packet proactively as the server normally would.
        HooksManager::park("leases4_committed", query, []{});

        // Invoke the callouts.
        HooksManager::callCallouts(testHooks.hook_index_buffer4_receive_,
                                   *handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle->getStatus());
    }

    // Wait for the partners.
    while (!wthread_->isReady(WatchedThread::READY) &&
           !wthread_->isReady(WatchedThread::ERROR)) {
        cerr << ".";
        usleep(50000);
    }
    if (wthread_->isReady(WatchedThread::ERROR)) {
        cerr << "partners simulation failed "
             << wthread_->getLastError() << endl;
    }

    // Submit lease.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_leases4_committed_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("query4", query);
        handle->setArgument("leases4", leases);
        handle->setArgument("deleted_leases4", deleted_leases);
        HooksManager::callCallouts(testHooks.hook_index_leases4_committed_,
                                   *handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    // Done: purge I/Os.
    io_service->poll();
    io_service->stop();
    io_service.reset();

    // Verify the HA owns the query.
    boost::weak_ptr<Pkt4> weak_query(query);
    query.reset();
    EXPECT_FALSE(weak_query.expired());

    EXPECT_FALSE(HooksManager::unloadLibraries());

    // Tell the HA to cleanup first.
    EXPECT_NO_THROW(HooksManager::prepareUnloadLibraries());
    EXPECT_TRUE(HooksManager::unloadLibraries());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Stop partners.
    wthread_->stop();
}

// Test that checks that the library can be loaded and unloaded from a DHCPv4
// backup server.
// 1. Creates one active and 2 backup servers.
// 2. Check that the network state is reset and updated to expected state when
// creating the HAService by calling the dhcp4_srv_configured hook.
// 3. Send ha-heartbeat to make the server transition 'backup' state.
// 4. Unload the library which should not have any dangling resources.
// 5. Verify that the network state is reset on unload.
TEST_F(CloseHATest, close4Backup) {
    // Start partners.
    wthread_.reset(new WatchedThread());
    wthread_->start([this] () { runPartners(); });

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration(true));

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    // Load the library.
    HookLibsCollection libraries;
    libraries.push_back(make_pair(LIBDHCP_HA_SO, params));
    ASSERT_TRUE(HooksManager::loadLibraries(libraries));

    // Prepare objects.
    IOServicePtr io_service(new IOService());
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));

    // Check that the state is computed on dhcp4_srv_configured.
    // It is first reset by the constructor and then adjusted by running the
    // state model.
    ASSERT_TRUE(network_state->isServiceEnabled());
    network_state->disableService(NetworkState::Origin::HA_COMMAND);
    ASSERT_FALSE(network_state->isServiceEnabled());

    // Start HA service.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_dhcp4_srv_configured_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("io_context", io_service);
        handle->setArgument("network_state", network_state);
        HooksManager::callCallouts(testHooks.hook_index_dhcp4_srv_configured_,
                                   *handle);
    }

    ASSERT_FALSE(network_state->isServiceEnabled());

    // Transition to backup state.
    ConstElementPtr command = createCommand("ha-heartbeat", "dhcp4");
    ConstElementPtr response;
    EXPECT_TRUE(HooksManager::commandHandlersPresent("ha-heartbeat"));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("command", command);
        handle->setArgument("response", response);
        HooksManager::callCommandHandlers("ha-heartbeat", *handle);
        handle->getArgument("response", response);
    }
    int code = 0;
    ConstElementPtr arguments = parseAnswer(code, response);
    EXPECT_EQ(0, code);
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());
    ConstElementPtr state = arguments->get("state");
    ASSERT_TRUE(state);
    ASSERT_EQ(Element::string, state->getType());
    EXPECT_EQ("backup", state->stringValue());

    ASSERT_FALSE(network_state->isServiceEnabled());

    // Done: purge I/Os.
    io_service->poll();
    io_service->stop();
    io_service.reset();

    EXPECT_TRUE(HooksManager::unloadLibraries());

    // Tell the HA to cleanup first.
    EXPECT_NO_THROW(HooksManager::prepareUnloadLibraries());
    EXPECT_TRUE(HooksManager::unloadLibraries());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Stop partners.
    wthread_->stop();
}

// Test that checks that the library can be loaded and unloaded from a DHCPv6
// active server.
// 1. Creates one active and 2 backup servers.
// 2. Check that the network state is reset and updated to expected state when
// creating the HAService by calling the dhcp6_srv_configured hook.
// 3. Send ha-heartbeat to make the server transition 'passive-backup' state.
// 4. Call buffer6_receive and leases6_committed hooks to make sure that the
// parked packet is owned strictly by the HA library.
// 5. Verify that releasing the query will release all resources.
// 6. Unload the library which should not have any dangling resources.
// 7. Verify that the network state is reset on unload.
TEST_F(CloseHATest, close6) {
    // Start partners.
    wthread_.reset(new WatchedThread());
    wthread_->start([this] () { runPartners(); });

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");

    // Load the library.
    HookLibsCollection libraries;
    libraries.push_back(make_pair(LIBDHCP_HA_SO, params));
    ASSERT_TRUE(HooksManager::loadLibraries(libraries));

    // Prepare objects.
    IOServicePtr io_service(new IOService());
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv6));
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 12345));
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, duid->getDuid()));
    query->addOption(opt_duid);
    ASSERT_NO_THROW(query->pack());
    const OutputBuffer& buffer = query->getBuffer();
    query.reset(new Pkt6(reinterpret_cast<const uint8_t*>(buffer.getData()),
                         buffer.getLength()));

    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"),
                               duid, 1234, 50, 60, 1));
    Lease6CollectionPtr leases(new Lease6Collection());
    leases->push_back(lease);
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    // Check that the disabled state is reset on dhcp6_srv_configured.
    ASSERT_TRUE(network_state->isServiceEnabled());
    network_state->disableService(NetworkState::Origin::HA_COMMAND);
    ASSERT_FALSE(network_state->isServiceEnabled());

    // Start HA service.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_dhcp6_srv_configured_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("io_context", io_service);
        handle->setArgument("network_state", network_state);
        HooksManager::callCallouts(testHooks.hook_index_dhcp6_srv_configured_,
                                   *handle);
    }

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Pretend to be the partner.
    ConstElementPtr command = createCommand("ha-heartbeat", "dhcp6");
    ConstElementPtr response;
    EXPECT_TRUE(HooksManager::commandHandlersPresent("ha-heartbeat"));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("command", command);
        handle->setArgument("response", response);
        HooksManager::callCommandHandlers("ha-heartbeat", *handle);
        handle->getArgument("response", response);
    }
    int code = 0;
    ConstElementPtr arguments = parseAnswer(code, response);
    EXPECT_EQ(0, code);
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());
    ConstElementPtr state = arguments->get("state");
    ASSERT_TRUE(state);
    ASSERT_EQ(Element::string, state->getType());
    EXPECT_EQ("passive-backup", state->stringValue());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Submit packet.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_buffer6_receive_));
    {
        // Use the query callout handle.
        CalloutHandlePtr handle = query->getCalloutHandle();
        ScopedCalloutHandleState handle_state(handle);
        handle->setArgument("query6", query);

        // Park the packet proactively as the server normally would.
        HooksManager::park("leases6_committed", query, []{});

        // Invoke the callouts.
        HooksManager::callCallouts(testHooks.hook_index_buffer6_receive_,
                                   *handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle->getStatus());
    }

    // Wait for the partners.
    while (!wthread_->isReady(WatchedThread::READY) &&
           !wthread_->isReady(WatchedThread::ERROR)) {
        cerr << ".";
        usleep(50000);
    }
    if (wthread_->isReady(WatchedThread::ERROR)) {
        cerr << "partners simulation failed "
             << wthread_->getLastError() << endl;
    }

    // Submit lease.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_leases6_committed_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("query6", query);
        handle->setArgument("leases6", leases);
        handle->setArgument("deleted_leases6", deleted_leases);
        HooksManager::callCallouts(testHooks.hook_index_leases6_committed_,
                                   *handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    // Done: purge I/Os.
    io_service->poll();
    io_service->stop();
    io_service.reset();

    // Verify the HA owns the query.
    boost::weak_ptr<Pkt6> weak_query(query);
    query.reset();
    EXPECT_FALSE(weak_query.expired());

    EXPECT_FALSE(HooksManager::unloadLibraries());

    // Tell the HA to cleanup first.
    EXPECT_NO_THROW(HooksManager::prepareUnloadLibraries());
    EXPECT_TRUE(HooksManager::unloadLibraries());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Stop partners.
    wthread_->stop();
}

// Test that checks that the library can be loaded and unloaded from a DHCPv6
// backup server.
// 1. Creates one active and 2 backup servers.
// 2. Check that the network state is reset and updated to expected state when
// creating the HAService by calling the dhcp6_srv_configured hook.
// 3. Send ha-heartbeat to make the server transition 'backup' state.
// 4. Unload the library which should not have any dangling resources.
// 5. Verify that the network state is reset on unload.
TEST_F(CloseHATest, close6Backup) {
    // Start partners.
    wthread_.reset(new WatchedThread());
    wthread_->start([this] () { runPartners(); });

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration(true));

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");

    // Load the library.
    HookLibsCollection libraries;
    libraries.push_back(make_pair(LIBDHCP_HA_SO, params));
    ASSERT_TRUE(HooksManager::loadLibraries(libraries));

    // Prepare objects.
    IOServicePtr io_service(new IOService());
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv6));

    // Check that the state is computed on dhcp6_srv_configured.
    // It is first reset by the constructor and then adjusted by running the
    // state model.
    ASSERT_TRUE(network_state->isServiceEnabled());
    network_state->disableService(NetworkState::Origin::HA_COMMAND);
    ASSERT_FALSE(network_state->isServiceEnabled());

    // Start HA service.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_dhcp6_srv_configured_));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("io_context", io_service);
        handle->setArgument("network_state", network_state);
        HooksManager::callCallouts(testHooks.hook_index_dhcp6_srv_configured_,
                                   *handle);
    }

    ASSERT_FALSE(network_state->isServiceEnabled());

    // Transition to backup state.
    ConstElementPtr command = createCommand("ha-heartbeat", "dhcp6");
    ConstElementPtr response;
    EXPECT_TRUE(HooksManager::commandHandlersPresent("ha-heartbeat"));
    {
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("command", command);
        handle->setArgument("response", response);
        HooksManager::callCommandHandlers("ha-heartbeat", *handle);
        handle->getArgument("response", response);
    }
    int code = 0;
    ConstElementPtr arguments = parseAnswer(code, response);
    EXPECT_EQ(0, code);
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());
    ConstElementPtr state = arguments->get("state");
    ASSERT_TRUE(state);
    ASSERT_EQ(Element::string, state->getType());
    EXPECT_EQ("backup", state->stringValue());

    ASSERT_FALSE(network_state->isServiceEnabled());

    // Done: purge I/Os.
    io_service->poll();
    io_service->stop();
    io_service.reset();

    EXPECT_TRUE(HooksManager::unloadLibraries());

    // Tell the HA to cleanup first.
    EXPECT_NO_THROW(HooksManager::prepareUnloadLibraries());
    EXPECT_TRUE(HooksManager::unloadLibraries());

    ASSERT_TRUE(network_state->isServiceEnabled());

    // Stop partners.
    wthread_->stop();
}

}
