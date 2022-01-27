// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/db_exceptions.h>
#include <database/server.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/testutils/generic_cb_recovery_unittest.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <testutils/gtest_utils.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::test;
namespace ph = std::placeholders;

GenericConfigBackendDbLostCallbackTest::GenericConfigBackendDbLostCallbackTest()
        : db_lost_callback_called_(0), db_recovered_callback_called_(0),
          db_failed_callback_called_(0),
          io_service_(boost::make_shared<IOService>()) {
}

GenericConfigBackendDbLostCallbackTest::~GenericConfigBackendDbLostCallbackTest() {
}

void
GenericConfigBackendDbLostCallbackTest::SetUp() {
    DatabaseConnection::db_lost_callback_ = 0;
    DatabaseConnection::db_recovered_callback_ = 0;
    DatabaseConnection::db_failed_callback_ = 0;
    setConfigBackendImplIOService(io_service_);
    isc::dhcp::TimerMgr::instance()->setIOService(io_service_);
    isc::dhcp::CfgMgr::instance().clear();

    // Ensure we have the proper schema with no transient data.
    createSchema();
    isc::dhcp::CfgMgr::instance().clear();
    registerBackendType();
}

void
GenericConfigBackendDbLostCallbackTest::TearDown() {
    // If data wipe enabled, delete transient data otherwise destroy the schema
    destroySchema();
    isc::dhcp::CfgMgr::instance().clear();

    unregisterBackendType();
    DatabaseConnection::db_lost_callback_ = 0;
    DatabaseConnection::db_recovered_callback_ = 0;
    DatabaseConnection::db_failed_callback_ = 0;
    setConfigBackendImplIOService(IOServicePtr());
    isc::dhcp::TimerMgr::instance()->unregisterTimers();
    isc::dhcp::CfgMgr::instance().clear();
}

void
GenericConfigBackendDbLostCallbackTest::testNoCallbackOnOpenFailure() {
    DatabaseConnection::db_lost_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectionString();

    // Connect to the CB backend.
    ASSERT_THROW(addBackend(access), DbOpenError);

    io_service_->poll();

    EXPECT_EQ(0, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
GenericConfigBackendDbLostCallbackTest::testDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectionString();

    ConfigControlInfoPtr config_ctl_info(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the CB backend.
    ASSERT_NO_THROW(addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ServerCollection servers;
    ASSERT_NO_THROW_LOG(servers = getAllServers());

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(servers = getAllServers(), DbConnectionUnusable);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
GenericConfigBackendDbLostCallbackTest::testDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectionString();
    ConfigControlInfoPtr config_ctl_info(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the CB backend.
    ASSERT_NO_THROW(addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ServerCollection servers;
    ASSERT_NO_THROW(servers = getAllServers());

    access = invalidConnectionString();
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    config_ctl_info.reset(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);
    const ConfigDbInfoList& cfg = CfgMgr::instance().getCurrentCfg()->getConfigControlInfo()->getConfigDatabases();
    (const_cast<ConfigDbInfoList&>(cfg))[0].setAccessString(access, true);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(servers = getAllServers(), DbConnectionUnusable);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}

void
GenericConfigBackendDbLostCallbackTest::testDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectionString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    ConfigControlInfoPtr config_ctl_info(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the CB backend.
    ASSERT_NO_THROW(addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ServerCollection servers;
    ASSERT_NO_THROW(servers = getAllServers());

    access = invalidConnectionString();
    access += extra;
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    config_ctl_info.reset(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);
    const ConfigDbInfoList& cfg = CfgMgr::instance().getCurrentCfg()->getConfigControlInfo()->getConfigDatabases();
    (const_cast<ConfigDbInfoList&>(cfg))[0].setAccessString(access, true);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(servers = getAllServers(), DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    access = validConnectionString();
    access += extra;
    CfgMgr::instance().clear();
    config_ctl_info.reset(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
GenericConfigBackendDbLostCallbackTest::testDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&GenericConfigBackendDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectionString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    ConfigControlInfoPtr config_ctl_info(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the CB backend.
    ASSERT_NO_THROW(addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ServerCollection servers;
    ASSERT_NO_THROW(servers = getAllServers());

    access = invalidConnectionString();
    access += extra;
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    config_ctl_info.reset(new ConfigControlInfo());
    config_ctl_info->addConfigDatabase(access);
    CfgMgr::instance().getCurrentCfg()->setConfigControlInfo(config_ctl_info);
    const ConfigDbInfoList& cfg = CfgMgr::instance().getCurrentCfg()->getConfigControlInfo()->getConfigDatabases();
    (const_cast<ConfigDbInfoList&>(cfg))[0].setAccessString(access, true);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(servers = getAllServers(), DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}
