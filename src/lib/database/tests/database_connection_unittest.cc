// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <database/database_connection.h>
#include <database/dbaccess_parser.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>

#include <functional>

using namespace isc::data;
using namespace isc::db;
namespace ph = std::placeholders;

/// @brief Test fixture for exercising DbLostCallback invocation
class DatabaseConnectionCallbackTest : public ::testing::Test {
public:
    /// Constructor
    DatabaseConnectionCallbackTest()
        : db_reconnect_ctl_(0) {
        DatabaseConnection::db_lost_callback_ = 0;
        DatabaseConnection::db_recovered_callback_ = 0;
        DatabaseConnection::db_failed_callback_ = 0;
    }

    /// Destructor
    ~DatabaseConnectionCallbackTest() {
        DatabaseConnection::db_lost_callback_ = 0;
        DatabaseConnection::db_recovered_callback_ = 0;
        DatabaseConnection::db_failed_callback_ = 0;
    }

    /// @brief Callback to register with a DatabaseConnection
    ///
    /// @param db_reconnect_ctl ReconnectCtl containing reconnect
    /// parameters
    bool dbLostCallback(ReconnectCtlPtr db_reconnect_ctl) {
        if (!db_reconnect_ctl) {
            isc_throw(isc::BadValue, "db_reconnect_ctl should not be null");
        }

        db_reconnect_ctl_ = db_reconnect_ctl;
        return (true);
    }

    /// @brief Callback to register with a DatabaseConnection
    ///
    /// @param db_reconnect_ctl ReconnectCtl containing reconnect
    /// parameters
    bool dbRecoveredCallback(ReconnectCtlPtr db_reconnect_ctl) {
        if (!db_reconnect_ctl) {
            isc_throw(isc::BadValue, "db_reconnect_ctl should not be null");
        }

        db_reconnect_ctl_ = db_reconnect_ctl;
        db_reconnect_ctl_->resetRetries();
        return (true);
    }

    /// @brief Callback to register with a DatabaseConnection
    ///
    /// @param db_reconnect_ctl ReconnectCtl containing reconnect
    /// parameters
    bool dbFailedCallback(ReconnectCtlPtr db_reconnect_ctl) {
        if (!db_reconnect_ctl) {
            isc_throw(isc::BadValue, "db_reconnect_ctl should not be null");
        }

        db_reconnect_ctl_ = db_reconnect_ctl;
        db_reconnect_ctl_->resetRetries();
        return (false);
    }

    /// @brief Retainer for the control passed into the callback
    ReconnectCtlPtr db_reconnect_ctl_;
};

/// @brief getParameter test
///
/// This test checks if the LeaseMgr can be instantiated and that it
/// parses parameters string properly.
TEST(DatabaseConnectionTest, getParameter) {

    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("param1")] = std::string("value1");
    pmap[std::string("param2")] = std::string("value2");
    DatabaseConnection datasrc(pmap);

    EXPECT_EQ("value1", datasrc.getParameter("param1"));
    EXPECT_EQ("value2", datasrc.getParameter("param2"));
    EXPECT_THROW(datasrc.getParameter("param3"), isc::BadValue);
}

/// @brief NoDbLostCallback
///
/// This test verifies that DatabaseConnection::invokeDbLostCallback
/// returns false if the connection has no registered DbLostCallback.
TEST_F(DatabaseConnectionCallbackTest, NoDbLostCallback) {
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");

    bool ret = false;
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbLostCallback(datasrc.reconnectCtl()));
    EXPECT_FALSE(ret);
    EXPECT_FALSE(db_reconnect_ctl_);
}

/// @brief NoDbRecoveredCallback
///
/// This test verifies that DatabaseConnection::invokeDbRecoveredCallback
/// returns false if the connection has no registered DbRecoveredCallback.
TEST_F(DatabaseConnectionCallbackTest, NoDbRecoveredCallback) {
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");

    bool ret = false;
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbRecoveredCallback(datasrc.reconnectCtl()));
    EXPECT_FALSE(ret);
    EXPECT_FALSE(db_reconnect_ctl_);
}

/// @brief NoDbFailedCallback
///
/// This test verifies that DatabaseConnection::invokeDbFailedCallback
/// returns false if the connection has no registered DbFailedCallback.
TEST_F(DatabaseConnectionCallbackTest, NoDbFailedCallback) {
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");

    bool ret = false;
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbFailedCallback(datasrc.reconnectCtl()));
    EXPECT_FALSE(ret);
    EXPECT_FALSE(db_reconnect_ctl_);
}

/// @brief dbLostCallback
///
/// This test verifies that DatabaseConnection::invokeDbLostCallback
/// safely invokes the registered DbCallback.  It also tests
/// operation of DbReconnectCtl retry accounting methods.
TEST_F(DatabaseConnectionCallbackTest, dbLostCallback) {
    /// Create a Database configuration that includes the reconnect
    /// control parameters.
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");

    /// Install the callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&DatabaseConnectionCallbackTest::dbLostCallback, this, ph::_1);
    /// Create the connection..
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");
    bool ret = false;

    /// We should be able to invoke the callback and get
    /// the correct reconnect control parameters from it.
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbLostCallback(datasrc.reconnectCtl()));
    EXPECT_TRUE(ret);
    ASSERT_TRUE(db_reconnect_ctl_);
    ASSERT_EQ("test", db_reconnect_ctl_->backendType());
    ASSERT_EQ("timer", db_reconnect_ctl_->timerName());
    ASSERT_EQ(3, db_reconnect_ctl_->maxRetries());
    ASSERT_EQ(3, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(60000, db_reconnect_ctl_->retryInterval());

    /// Verify that checkRetries() correctly decrements
    /// down to zero, and that retriesLeft() returns
    /// the correct value.
    for (int i = 3; i > 1 ; --i) {
        ASSERT_EQ(i, db_reconnect_ctl_->retriesLeft());
        ASSERT_TRUE(db_reconnect_ctl_->checkRetries());
    }

    /// Retries are exhausted, verify that's reflected.
    EXPECT_FALSE(db_reconnect_ctl_->checkRetries());
    EXPECT_EQ(0, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(3, db_reconnect_ctl_->maxRetries());
}

/// @brief dbRecoveredCallback
///
/// This test verifies that DatabaseConnection::invokeDbRecoveredCallback
/// safely invokes the registered DbRecoveredCallback.  It also tests
/// operation of DbReconnectCtl retry reset method.
TEST_F(DatabaseConnectionCallbackTest, dbRecoveredCallback) {
    /// Create a Database configuration that includes the reconnect
    /// control parameters.
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");

    /// Install the callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&DatabaseConnectionCallbackTest::dbLostCallback, this, ph::_1);
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&DatabaseConnectionCallbackTest::dbRecoveredCallback, this, ph::_1);
    /// Create the connection..
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");
    bool ret = false;

    /// We should be able to invoke the callback and get
    /// the correct reconnect control parameters from it.
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbLostCallback(datasrc.reconnectCtl()));
    EXPECT_TRUE(ret);
    ASSERT_TRUE(db_reconnect_ctl_);
    ASSERT_EQ("test", db_reconnect_ctl_->backendType());
    ASSERT_EQ("timer", db_reconnect_ctl_->timerName());
    ASSERT_EQ(3, db_reconnect_ctl_->maxRetries());
    ASSERT_EQ(3, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(60000, db_reconnect_ctl_->retryInterval());

    /// Verify that checkRetries() correctly decrements
    /// down to zero, and that retriesLeft() returns
    /// the correct value.
    for (int i = 3; i > 1 ; --i) {
        ASSERT_EQ(i, db_reconnect_ctl_->retriesLeft());
        ASSERT_TRUE(db_reconnect_ctl_->checkRetries());
    }

    /// Retries are exhausted, verify that's reflected.
    EXPECT_FALSE(db_reconnect_ctl_->checkRetries());
    EXPECT_EQ(0, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(3, db_reconnect_ctl_->maxRetries());

    /// Reset the reconnect ctl object to verify that it is set again.
    db_reconnect_ctl_.reset();

    /// We should be able to invoke the callback and get
    /// the correct reconnect control parameters from it.
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbRecoveredCallback(datasrc.reconnectCtl()));
    EXPECT_TRUE(ret);
    ASSERT_TRUE(db_reconnect_ctl_);
    ASSERT_EQ("test", db_reconnect_ctl_->backendType());
    ASSERT_EQ("timer", db_reconnect_ctl_->timerName());
    EXPECT_EQ(60000, db_reconnect_ctl_->retryInterval());

    /// Retries are reset, verify that's reflected.
    EXPECT_EQ(3, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(3, db_reconnect_ctl_->maxRetries());
}

/// @brief dbFailedCallback
///
/// This test verifies that DatabaseConnection::invokeDbFailedCallback
/// safely invokes the registered DbFailedCallback.
TEST_F(DatabaseConnectionCallbackTest, dbFailedCallback) {
    /// Create a Database configuration that includes the reconnect
    /// control parameters.
    DatabaseConnection::ParameterMap pmap;
    pmap[std::string("type")] = std::string("test");
    pmap[std::string("max-reconnect-tries")] = std::string("3");
    pmap[std::string("reconnect-wait-time")] = std::string("60000");

    /// Install the callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&DatabaseConnectionCallbackTest::dbLostCallback, this, ph::_1);
    DatabaseConnection::db_failed_callback_ =
        std::bind(&DatabaseConnectionCallbackTest::dbFailedCallback, this, ph::_1);
    /// Create the connection..
    DatabaseConnection datasrc(pmap);
    datasrc.makeReconnectCtl("timer");
    bool ret = false;

    /// We should be able to invoke the callback and get
    /// the correct reconnect control parameters from it.
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbLostCallback(datasrc.reconnectCtl()));
    EXPECT_TRUE(ret);
    ASSERT_TRUE(db_reconnect_ctl_);
    ASSERT_EQ("test", db_reconnect_ctl_->backendType());
    ASSERT_EQ("timer", db_reconnect_ctl_->timerName());
    ASSERT_EQ(3, db_reconnect_ctl_->maxRetries());
    ASSERT_EQ(3, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(60000, db_reconnect_ctl_->retryInterval());

    /// Verify that checkRetries() correctly decrements
    /// down to zero, and that retriesLeft() returns
    /// the correct value.
    for (int i = 3; i > 1 ; --i) {
        ASSERT_EQ(i, db_reconnect_ctl_->retriesLeft());
        ASSERT_TRUE(db_reconnect_ctl_->checkRetries());
    }

    /// Retries are exhausted, verify that's reflected.
    EXPECT_FALSE(db_reconnect_ctl_->checkRetries());
    EXPECT_EQ(0, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(3, db_reconnect_ctl_->maxRetries());

    /// Reset the reconnect ctl object to verify that it is set again.
    db_reconnect_ctl_.reset();

    /// We should be able to invoke the callback and get
    /// the correct reconnect control parameters from it.
    ASSERT_NO_THROW(ret = DatabaseConnection::invokeDbFailedCallback(datasrc.reconnectCtl()));
    EXPECT_FALSE(ret);
    ASSERT_TRUE(db_reconnect_ctl_);
    ASSERT_EQ("test", db_reconnect_ctl_->backendType());
    ASSERT_EQ("timer", db_reconnect_ctl_->timerName());
    EXPECT_EQ(60000, db_reconnect_ctl_->retryInterval());

    /// Retries are reset, verify that's reflected.
    EXPECT_EQ(3, db_reconnect_ctl_->retriesLeft());
    EXPECT_EQ(3, db_reconnect_ctl_->maxRetries());
}

// This test checks that a database access string can be parsed correctly.
TEST(DatabaseConnectionTest, parse) {

    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(
        "user=me password='forbidden' name=kea somethingelse= type=mysql");

    EXPECT_EQ(5, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
    EXPECT_EQ("", parameters["somethingelse"]);
}

// This test checks that it is allowed to specify password including whitespaces
// assuming that the password is enclosed in ''.
TEST(DatabaseConnectionTest, parsePasswordWithWhitespace) {

    // Case 1: password in the middle.
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(
        "user=me password='forbidden with space' name=kea type=mysql");

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden with space", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Case 2: password at the end.
    parameters = DatabaseConnection::parse("user=me name=kea type=mysql password='forbidden with space'");

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden with space", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Case 3: Empty password at the end.
    parameters = DatabaseConnection::parse("user=me name=kea type=mysql password=''");

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Case 4: password at the beginning.
    parameters = DatabaseConnection::parse("password='forbidden with space' user=me name=kea type=mysql");

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden with space", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Case 5: Empty password at the beginning.
    parameters = DatabaseConnection::parse("password='' user=me name=kea type=mysql");

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);


    // Case 6: Password is a sole parameter.
    parameters = DatabaseConnection::parse("password='forbidden with spaces'");

    EXPECT_EQ(1, parameters.size());
    EXPECT_EQ("forbidden with spaces", parameters["password"]);
}

// This test checks that an invalid database access string behaves as expected.
TEST(DatabaseConnectionTest, parseInvalid) {

    // No tokens in the string, so we expect no parameters
    std::string invalid = "";
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(invalid);
    EXPECT_EQ(0, parameters.size());

    // With spaces, there are some tokens so we expect invalid parameter
    // as there are no equals signs.
    invalid = "   \t  ";
    EXPECT_THROW(DatabaseConnection::parse(invalid), isc::InvalidParameter);

    invalid = "   noequalshere  ";
    EXPECT_THROW(DatabaseConnection::parse(invalid), isc::InvalidParameter);

    // Mismatched single quote.
    invalid = "password='xyz";
    EXPECT_THROW(DatabaseConnection::parse(invalid), isc::InvalidParameter);

    // A single "=" is valid string, but is placed here as the result is
    // expected to be nothing.
    invalid = "=";
    parameters = DatabaseConnection::parse(invalid);
    EXPECT_EQ(1, parameters.size());
    EXPECT_EQ("", parameters[""]);
}

/// @brief redactedAccessString test
///
/// Checks that the redacted configuration string includes the password only
/// as a set of asterisks.
TEST(DatabaseConnectionTest, redactAccessString) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me password=forbidden name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("forbidden", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

/// @brief redactedAccessString test - empty password
///
/// Checks that the redacted configuration string includes the password only
/// as a set of asterisks, even if the password is null.
TEST(DatabaseConnectionTest, redactAccessStringEmptyPassword) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me name=kea type=mysql password=");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // ... and again to check that the position of the empty password in the
    // string does not matter.
    parameters = DatabaseConnection::parse("user=me password= name=kea type=mysql");
    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(4, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("*****", parameters["password"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

/// @brief redactedAccessString test - no password
///
/// Checks that the redacted configuration string excludes the password if there
/// was no password to begin with.
TEST(DatabaseConnectionTest, redactAccessStringNoPassword) {

    DatabaseConnection::ParameterMap parameters =
        DatabaseConnection::parse("user=me name=kea type=mysql");
    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);

    // Redact the result.  To check, break the redacted string down into its
    // components.
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);
    parameters = DatabaseConnection::parse(redacted);

    EXPECT_EQ(3, parameters.size());
    EXPECT_EQ("me", parameters["user"]);
    EXPECT_EQ("kea", parameters["name"]);
    EXPECT_EQ("mysql", parameters["type"]);
}

// Check that the toElementDbAccessString() handles all valid parameters
// Note that because toElementDbAccessString() utilizes
// toElement() this tests both.
TEST(DatabaseConnection, toElementDbAccessStringValid) {
    const char* configs[] = {
        "{\n"
        "\"connect-timeout\" : 200, \n"
        "\"contact-points\": \"contact_str\", \n"
        "\"consistency\": \"quorum\", \n"
        "\"on-fail\": \"stop-retry-exit\", \n"
        "\"serial-consistency\": \"serial\", \n"
        "\"keyspace\": \"keyspace_str\", \n"
        "\"lfc-interval\" : 100, \n"
        "\"host\": \"whatevah\", \n"
        "\"max-reconnect-tries\": 5, \n"
        "\"name\": \"name_str\", \n"
        "\"password\": \"password_str\", \n"
        "\"persist\" : true, \n"
        "\"port\" : 300, \n"
        "\"readonly\" : false, \n"
        "\"reconnect-wait-time\": 99, \n"
        "\"request-timeout\" : 100, \n"
        "\"tcp-keepalive\": 101, \n"
        "\"tcp-nodelay\": false, \n"
        "\"type\": \"memfile\", \n"
        "\"user\": \"user_str\", \n"
        "\"max-row-errors\": 50, \n"
        "\"trust-anchor\": \"my-ca\", \n"
        "\"cert-file\": \"my-cert.crt\", \n"
        "\"key-file\": \"my-key.key\", \n"
        "\"cipher-list\": \"AES\" \n"
        "}\n"
    };

    DbAccessParser parser;
    std::string access_str;
    ConstElementPtr json_elements;

    ASSERT_NO_THROW(json_elements = Element::fromJSON(configs[0]));
    ASSERT_NO_THROW(parser.parse(access_str, json_elements));

    ElementPtr round_trip = DatabaseConnection::toElementDbAccessString(access_str);

    ASSERT_TRUE(json_elements->equals(*round_trip));
}

// Check that toElementDbAccessString() catches invalid parameters.
// Note that because toElementDbAccessString() utilizes
// toElement() this tests both.
//
// Test has been disabled. The recent change turned handling of unknown connection
// string params. Instead of throwing, it logs an error and continues. This gives
// us better resiliency. However, we don't have any means implemented to
// test whether it was printed or not. It's reasonably easy to implement such a
// check, but we don't have time for this.
TEST(DatabaseConnection, DISABLED_toElementDbAccessStringInvalid) {
    std::vector<std::string> access_strs = {
        "bogus-param=memfile",
        "lfc-interval=not-an-integer",
        "connect-timeout=not-an-integer",
        "port=not-an-integer",
        "persist=not-boolean",
        "readonly=not-boolean"
    };

    for (auto access_str : access_strs) {
        /// @todo: verify that an ERROR is logged.
        ASSERT_NO_THROW(DatabaseConnection::toElementDbAccessString(access_str));
    }
}

// Check that toElementDbAccessString() handles empty access string
// Note that because toElementDbAccessString() utilizes
// toElement() this tests both.
TEST(DatabaseConnection, toElementDbAccessStringEmpty) {
    ConstElementPtr elements;
    ASSERT_NO_THROW(elements = DatabaseConnection::toElementDbAccessString(""));
    ASSERT_TRUE(elements);
    ASSERT_EQ(0, elements->size());
}
