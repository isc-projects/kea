// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify lease query connections.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <testutils/log_utils.h>
#include <lease_query_connection.h>
#include <lease_query_log.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::lease_query;
using namespace isc::tcp;
using namespace isc::util;

namespace {

/// @brief Test timeout (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Test derivation of LeaseQueryConnection.
class TestLeaseQueryConnection : public LeaseQueryConnection {
public:

    /// @brief Constructor.
    TestLeaseQueryConnection(const IOServicePtr& io_service,
                             TcpConnectionPool& connection_pool,
                             const long idle_timeout,
                             const uint16_t family,
                             const size_t max_concurrent_queries = 20,
                             const size_t read_max = 32768)
        : LeaseQueryConnection(io_service,
                               TcpConnectionAcceptorPtr(),
                               TlsContextPtr(),
                               connection_pool,
                               0,
                               0,
                               idle_timeout,
                               family,
                               max_concurrent_queries,
                               read_max) {
    }

    /// @brief Destructor.
    virtual ~TestLeaseQueryConnection() {
    }

    /// @brief Redefine sendNextResponse to do nothing.
    virtual void sendNextResponse() {
    }

    /// @brief Make the list of in-process queries visible.
    using LeaseQueryConnection::running_queries_;

    /// @brief Make the queue of queries waiting to enter processing visible.
    using LeaseQueryConnection::pending_queries_;

    /// @brief Make the list of responses waiting to be sent visible.
    using LeaseQueryConnection::responses_;

    /// @brief Make the mutex used to lock during responses access visible.
    using LeaseQueryConnection::responses_mutex_;
};

/// @brief Type of pointers to TestLeaseQueryConnection.
typedef boost::shared_ptr<TestLeaseQueryConnection> TestLeaseQueryConnectionPtr;

/// @brief Type of weak pointers to TestLeaseQueryConnection.
typedef boost::weak_ptr<TestLeaseQueryConnection> TestLeaseQueryConnectionWPtr;

/// @brief Test fixture class for lease query connections.
class LeaseQueryConnectionTest : public test::LogContentTest {
public:
    /// @brief Path name of server's duid file.
    static const string duid_file_;

    /// @brief Constructor.
    LeaseQueryConnectionTest() {
        CfgMgr::instance().clear();
        io_service_.reset(new IOService());
    }

    /// @brief Destructor.
    ~LeaseQueryConnectionTest() {
        // Check logs.
        EXPECT_TRUE(checkFile());

        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        io_service_.reset();
        static_cast<void>(remove(duid_file_.c_str()));
    }

    /// @brief I/O service.
    IOServicePtr io_service_;

    /// @brief Lease query connection pool.
    TcpConnectionPool connection_pool_;
};

/// @brief Path name for server-id generation.
const string LeaseQueryConnectionTest::duid_file_ =
    string(TEST_DATA_BUILDDIR) + string("/lq6-duid");

/// @brief Verify construction (v4).
TEST_F(LeaseQueryConnectionTest, constructor4) {
    TestLeaseQueryConnectionPtr conn;
    ASSERT_NO_THROW(conn.reset(new TestLeaseQueryConnection(io_service_,
                                                            connection_pool_,
                                                            IDLE_TIMEOUT,
                                                            AF_INET)));
    ASSERT_TRUE(conn);
    string log1 = "DHCPSRV_CFGMGR_CFG_DHCP_DDNS Setting DHCP-DDNS";
    log1 += " configuration to: DHCP-DDNS updates disabled";
    addString(log1);
}

/// @brief Verify construction (v6).
TEST_F(LeaseQueryConnectionTest, constructor6) {
    TestLeaseQueryConnectionPtr conn;
    ASSERT_NO_THROW(conn.reset(new TestLeaseQueryConnection(io_service_,
                                                            connection_pool_,
                                                            IDLE_TIMEOUT,
                                                            AF_INET6)));
    ASSERT_TRUE(conn);
    string log1 = "DHCPSRV_CFGMGR_CFG_DHCP_DDNS Setting DHCP-DDNS";
    log1 += " configuration to: DHCP-DDNS updates disabled";
    addString(log1);
}

} // end of anonymous namespace
