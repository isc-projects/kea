// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_CONFIG_BACKEND_RECOVERY_H
#define GENERIC_CONFIG_BACKEND_RECOVERY_H

#include <database/database_connection.h>
#include <database/server_collection.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test fixture for verifying config backend database connection
/// loss-recovery behavior.
class GenericConfigBackendDbLostCallbackTest : public ::testing::Test {
public:
    /// @brief Constructor
    GenericConfigBackendDbLostCallbackTest();

    /// @brief Destructor
    virtual ~GenericConfigBackendDbLostCallbackTest();

    /// @brief Abstract method for destroying the back end specific schema
    virtual void destroySchema() = 0;

    /// @brief Abstract method for creating the back end specific schema
    virtual void createSchema() = 0;

    /// @brief Abstract method which returns a valid back end specific connection
    /// string
    virtual std::string validConnectionString() = 0;

    /// @brief Abstract method which returns an invalid back end specific connection
    /// string
    virtual std::string invalidConnectionString() = 0;

    /// @brief Abstract method which registers a CB backend type.
    virtual void registerBackendType() = 0;

    /// @brief Abstract method which unregisters a CB backend type.
    virtual void unregisterBackendType() = 0;

    /// @brief Abstract method which sets the IOService instance in the CB
    /// implementation object.
    ///
    /// @param io_service pointer to the IOService instance to use. It may be
    /// an empty pointer.
    virtual void setConfigBackendImplIOService(isc::asiolink::IOServicePtr io_service) = 0;

    /// @brief Abstract method which sets the IOService instance in the CB
    virtual void addBackend(const std::string& access) = 0;

    /// @brief Abstract method which sets the IOService instance in the CB
    virtual db::ServerCollection getAllServers() = 0;

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic DB manager to
    /// wipe out any prior instance
    virtual void SetUp();

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown();

    /// @brief Verifies open failures do NOT invoke db lost callback
    ///
    /// The db lost callback should only be invoked after successfully
    /// opening the DB and then subsequently losing it. Failing to
    /// open should be handled directly by the application layer.
    void testNoCallbackOnOpenFailure();

    /// @brief Verifies the CB manager's behavior if DB connection is lost
    ///
    /// This function creates a CB manager with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the CB backend. It then reissues the
    /// query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    void testDbLostAndRecoveredCallback();

    /// @brief Verifies the CB manager's behavior if DB connection is lost
    ///
    /// This function creates a CB manager with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the CB backend. It then reissues the
    /// query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    void testDbLostAndFailedCallback();

    /// @brief Verifies the CB manager's behavior if DB connection is lost
    ///
    /// This function creates a CB manager with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the CB backend. It then reissues the
    /// query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testDbLostAndRecoveredAfterTimeoutCallback();

    /// @brief Verifies the CB manager's behavior if DB connection is lost
    ///
    /// This function creates a CB manager with a back end that supports
    /// connectivity lost callback. It verifies connectivity by issuing a known
    /// valid query. Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the CB backend. It then reissues the
    /// query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testDbLostAndFailedAfterTimeoutCallback();

    /// @brief Callback function registered with the CB manager
    bool db_lost_callback(db::ReconnectCtlPtr /* not_used */) {
        return (++db_lost_callback_called_);
    }

    /// @brief Flag used to detect calls to db_lost_callback function
    uint32_t db_lost_callback_called_;

    /// @brief Callback function registered with the CB manager
    bool db_recovered_callback(db::ReconnectCtlPtr /* not_used */) {
        return (++db_recovered_callback_called_);
    }

    /// @brief Flag used to detect calls to db_recovered_callback function
    uint32_t db_recovered_callback_called_;

    /// @brief Callback function registered with the CB manager
    bool db_failed_callback(db::ReconnectCtlPtr /* not_used */) {
        return (++db_failed_callback_called_);
    }

    /// @brief Flag used to detect calls to db_failed_callback function
    uint32_t db_failed_callback_called_;

    /// The IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_service_;
};

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif // GENERIC_CONFIG_BACKEND_RECOVERY_H
