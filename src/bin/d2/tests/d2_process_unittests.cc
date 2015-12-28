// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <d2/d2_process.h>
#include <dhcp_ddns/ncr_io.h>
#include <d_test_stubs.h>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::d2;
using namespace boost::posix_time;

namespace {

/// @brief Valid configuration containing an unavailable IP address.
const char* bad_ip_d2_config = "{ "
                        "\"ip-address\" : \"1.1.1.1\" , "
                        "\"port\" : 5031, "
                        "\"tsig-keys\": ["
                        "{ \"name\": \"d2_key.tmark.org\" , "
                        "   \"algorithm\": \"HMAC-MD5\" ,"
                        "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "} ],"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"key-name\": \"d2_key.tmark.org\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.101\" } "
                        "] } ] }, "
                        "\"reverse-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \" 0.168.192.in.addr.arpa.\" , "
                        "  \"key-name\": \"d2_key.tmark.org\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.101\" , "
                        "    \"port\": 100 } ] } "
                        "] } }";

/// @brief D2Process test fixture class
//class D2ProcessTest : public D2Process, public ::testing::Test {
class D2ProcessTest : public D2Process, public ConfigParseTest {
public:

    /// @brief Constructor
    D2ProcessTest() :
        D2Process("d2test",
                  asiolink::IOServicePtr(new isc::asiolink::IOService())) {
    }

    /// @brief Destructor
    virtual ~D2ProcessTest() {
    }

    /// @brief Callback that will invoke shutdown method.
    void genShutdownCallback() {
        shutdown(isc::data::ConstElementPtr());
    }

    /// @brief Callback that throws an exception.
    void genFatalErrorCallback() {
        isc_throw (DProcessBaseError, "simulated fatal error");
    }

    /// @brief Reconfigures and starts the queue manager given a configuration.
    ///
    /// This method emulates the reception of a new configuration and should
    /// conclude with the Queue manager placed in the RUNNING state.
    ///
    /// @param config is the configuration to use
    ///
    /// @return Returns AssertionSuccess if the queue manager was successfully
    /// reconfigured, AssertionFailure otherwise.
    ::testing::AssertionResult runWithConfig(const char* config) {
        int rcode = -1;
        // Convert the string configuration into an Element set.
        ::testing::AssertionResult res = fromJSON(config);
        if (res != ::testing::AssertionSuccess()) {
            return res;
        }

        isc::data::ConstElementPtr answer = configure(config_set_);
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);

        if (rcode) {
            return (::testing::AssertionFailure(::testing::Message() <<
                                                "configure() failed:"
                                                << comment));
        }

        // Must call checkQueueStatus, to cause queue manager to reconfigure
        // and start.
        checkQueueStatus();
        const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

        // If queue manager isn't in the RUNNING state, return failure.
        if (D2QueueMgr::RUNNING !=  queue_mgr->getMgrState()) {
            return (::testing::AssertionFailure(::testing::Message() <<
                                               "queue manager did not start"));
        }

        //  Good to go.
        return (::testing::AssertionSuccess());
    }

    /// @brief Checks if shutdown criteria would be met given a shutdown type.
    ///
    /// This method sets the D2Process shutdown type to the given value, and
    /// calls the canShutdown() method, returning its return value.
    ///
    /// @return Returns the boolean result canShutdown.
    bool checkCanShutdown(ShutdownType shutdown_type) {
        setShutdownType(shutdown_type);
        return (canShutdown());
    }
};

/// @brief Verifies D2Process construction behavior.
/// 1. Verifies that constructor fails with an invalid IOService
/// 2. Verifies that constructor succeeds with a valid IOService
/// 3. Verifies that all managers are accessible
TEST(D2Process, construction) {
    // Verify that the constructor will fail if given an empty
    // io service.
    asiolink::IOServicePtr lcl_io_service;
    EXPECT_THROW (D2Process("TestProcess", lcl_io_service), DProcessBaseError);

    // Verify that the constructor succeeds with a valid io_service
    lcl_io_service.reset(new isc::asiolink::IOService());
    ASSERT_NO_THROW (D2Process("TestProcess", lcl_io_service));

    // Verify that the configuration, queue, and update managers
    // are all accessible after construction.
    D2Process d2process("TestProcess", lcl_io_service);

    D2CfgMgrPtr cfg_mgr = d2process.getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);

    D2QueueMgrPtr queue_mgr = d2process.getD2QueueMgr();
    ASSERT_TRUE(queue_mgr);

    const D2UpdateMgrPtr& update_mgr = d2process.getD2UpdateMgr();
    ASSERT_TRUE(update_mgr);
}

/// @brief Verifies basic configure method behavior.
/// This test primarily verifies that upon receipt of a new configuration,
/// D2Process will reconfigure the queue manager if the configuration is valid,
/// or leave queue manager unaffected if not.  Currently, the queue manager is
/// only D2 component that must adapt to new configurations. Other components,
/// such as Transactions will be unaffected as they are transient and use
/// whatever configuration was in play at the time they were created.
/// If other components need to provide "dynamic" configuration responses,
/// those tests would need to be added.
TEST_F(D2ProcessTest, configure) {
    // Verify the queue manager is not yet initialized.
    D2QueueMgrPtr queue_mgr = getD2QueueMgr();
    ASSERT_TRUE(queue_mgr);
    ASSERT_EQ(D2QueueMgr::NOT_INITTED, queue_mgr->getMgrState());

    // Verify that reconfigure queue manager flag is false.
    ASSERT_FALSE(getReconfQueueFlag());

    // Create a valid configuration set from text config.
    ASSERT_TRUE(fromJSON(valid_d2_config));

    // Invoke configure() with a valid D2 configuration.
    isc::data::ConstElementPtr answer = configure(config_set_);

    // Verify that configure result is success and reconfigure queue manager
    // flag is true.
    ASSERT_TRUE(checkAnswer(answer, 0));
    ASSERT_TRUE(getReconfQueueFlag());

    // Call checkQueueStatus, to cause queue manager to reconfigure and start.
    checkQueueStatus();

    // Verify that queue manager is now in the RUNNING state, and flag is false.
    ASSERT_EQ(D2QueueMgr::RUNNING, queue_mgr->getMgrState());
    ASSERT_FALSE(getReconfQueueFlag());

    //  Create an invalid configuration set from text config.
    ASSERT_TRUE(fromJSON("{ \"bogus\": 1000 } "));

    // Invoke configure() with the invalid configuration.
    answer = configure(config_set_);

    // Verify that configure result is failure, the reconfigure flag is
    // false, and that the queue manager is still running.
    ASSERT_TRUE(checkAnswer(answer, 1));
    EXPECT_FALSE(getReconfQueueFlag());
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr->getMgrState());
}

/// @brief Tests checkQueueStatus() logic for stopping the queue on shutdown
/// This test manually sets shutdown flag and verifies that queue manager
/// stop is initiated.
TEST_F(D2ProcessTest, queueStopOnShutdown) {
    ASSERT_TRUE(runWithConfig(valid_d2_config));
    const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

    setShutdownFlag(true);

    // Calling checkQueueStatus restart queue manager
    checkQueueStatus();

    // Verify that the queue manager is stopping.
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Verify that a subsequent call with no events occurring in between,
    // results in no change to queue manager
    checkQueueStatus();

    // Verify that the queue manager is still stopping.
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Call runIO so the IO cancel event occurs and verify that queue manager
    // has stopped.
    runIO();
    ASSERT_EQ(D2QueueMgr::STOPPED, queue_mgr->getMgrState());
}

/// @brief Tests checkQueueStatus() logic for stopping the queue on reconfigure.
/// This test manually sets queue reconfiguration flag and verifies that queue
/// manager stop is initiated.
TEST_F(D2ProcessTest, queueStopOnReconf) {
    ASSERT_TRUE(runWithConfig(valid_d2_config));
    const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

    // Manually set the reconfigure indicator.
    setReconfQueueFlag(true);

    // Calling checkQueueStatus should initiate stopping the queue manager.
    checkQueueStatus();

    // Verify that the queue manager is stopping.
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Call runIO so the IO cancel event occurs and verify that queue manager
    // has stopped.
    runIO();
    ASSERT_EQ(D2QueueMgr::STOPPED, queue_mgr->getMgrState());
}


/// @brief Tests checkQueueStatus() logic for recovering from queue full
/// This test manually creates a receive queue full condition and then
/// "drains" the queue until the queue manager resumes listening.  This
/// verifies D2Process's ability to recover from a queue full condition.
TEST_F(D2ProcessTest, queueFullRecovery) {
    // Valid test message, contents are unimportant.
    const char* test_msg =
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : false , "
        " \"fqdn\" : \"walah.walah.com\" , "
        " \"ip-address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"010203040A7F8E3D\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

    // Start queue manager with known good config.
    ASSERT_TRUE(runWithConfig(valid_d2_config));
    const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

    // Set the maximum queue size to manageable number.
    size_t max_queue_size = 5;
    queue_mgr->setMaxQueueSize(max_queue_size);

    // Manually enqueue max requests.
    dhcp_ddns::NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr = dhcp_ddns::NameChangeRequest::fromJSON(test_msg));
    for (int i = 0; i < max_queue_size; i++) {
        // Verify that the request can be added to the queue and queue
        // size increments accordingly.
        ASSERT_NO_THROW(queue_mgr->enqueue(ncr));
        ASSERT_EQ(i+1, queue_mgr->getQueueSize());
    }

    // Since we are not really receiving, we will simulate QUEUE FULL
    // detection.
    queue_mgr->stopListening(D2QueueMgr::STOPPED_QUEUE_FULL);
    ASSERT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Call runIO so the IO cancel event occurs and verify that queue manager
    // has stopped.
    runIO();
    ASSERT_EQ(D2QueueMgr::STOPPED_QUEUE_FULL, queue_mgr->getMgrState());

    // Dequeue requests one at a time, calling checkQueueStatus after each
    // dequeue, until we reach the resume threshold.  This simulates update
    // manager consuming jobs.  Queue manager should remain stopped during
    // this loop.
    int resume_threshold = (max_queue_size * QUEUE_RESTART_PERCENT);
    while (queue_mgr->getQueueSize() > resume_threshold) {
        checkQueueStatus();
        ASSERT_EQ(D2QueueMgr::STOPPED_QUEUE_FULL, queue_mgr->getMgrState());
        ASSERT_NO_THROW(queue_mgr->dequeue());
    }

    // Dequeue one more, which brings us under the threshold and call
    // checkQueueStatus.
    // Verify that the queue manager is again running.
    ASSERT_NO_THROW(queue_mgr->dequeue());
    checkQueueStatus();
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr->getMgrState());
}

/// @brief Tests checkQueueStatus() logic for queue receive error recovery
/// This test manually creates a queue receive error condition and tests
/// verifies that checkQueueStatus reacts properly to recover.
TEST_F(D2ProcessTest, queueErrorRecovery) {
    ASSERT_TRUE(runWithConfig(valid_d2_config));
    const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

    // Since we are not really receiving, we have to stage an error.
    queue_mgr->stopListening(D2QueueMgr::STOPPED_RECV_ERROR);
    ASSERT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Call runIO so the IO cancel event occurs and verify that queue manager
    // has stopped.
    runIO();
    ASSERT_EQ(D2QueueMgr::STOPPED_RECV_ERROR, queue_mgr->getMgrState());

    // Calling checkQueueStatus should restart queue manager
    checkQueueStatus();

    // Verify that queue manager is again running.
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr->getMgrState());
}

/// @brief Verifies queue manager recovery from unusable configuration
/// This test checks D2Process's gracefully handle a configuration which
/// while valid is not operationally usable (i.e. IP address is unavailable),
/// and to subsequently recover given a usable configuration.
TEST_F(D2ProcessTest, badConfigureRecovery) {
    D2QueueMgrPtr queue_mgr = getD2QueueMgr();
    ASSERT_TRUE(queue_mgr);

    // Verify the queue manager is not initialized.
    EXPECT_EQ(D2QueueMgr::NOT_INITTED, queue_mgr->getMgrState());

    // Invoke configure() with a valid config that contains an unusable IP
    ASSERT_TRUE(fromJSON(bad_ip_d2_config));
    isc::data::ConstElementPtr answer = configure(config_set_);

    // Verify that configure result is success and reconfigure queue manager
    // flag is true.
    ASSERT_TRUE(checkAnswer(answer, 0));
    ASSERT_TRUE(getReconfQueueFlag());

    // Call checkQueueStatus to cause queue manager to attempt to reconfigure.
    checkQueueStatus();

    // Verify that queue manager  failed to start, (i.e. is in INITTED state),
    // and the the reconfigure flag is false.
    ASSERT_EQ(D2QueueMgr::INITTED, queue_mgr->getMgrState());
    ASSERT_FALSE(getReconfQueueFlag());

    // Verify we can recover given a valid config with an usable IP address.
    ASSERT_TRUE(fromJSON(valid_d2_config));
    answer = configure(config_set_);

    // Verify that configure result is success and reconfigure queue manager
    // flag is true.
    ASSERT_TRUE(checkAnswer(answer, 0));
    ASSERT_TRUE(getReconfQueueFlag());

    // Call checkQueueStatus to cause queue manager to reconfigure and start.
    checkQueueStatus();

    // Verify that queue manager is now in the RUNNING state, and reconfigure
    // flag is false.
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr->getMgrState());
    EXPECT_FALSE(getReconfQueueFlag());
}

/// @brief Verifies basic command method behavior.
/// @TODO IF the D2Process is extended to support extra commands this testing
/// will need to augmented accordingly.
TEST_F(D2ProcessTest, command) {
    // Verify that the process will process unsupported command and
    // return a failure response.
    int rcode = -1;
    string args = "{ \"arg1\": 77 } ";
    isc::data::ElementPtr json = isc::data::Element::fromJSON(args);
    isc::data::ConstElementPtr answer = command("bogus_command", json);
    parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);
}

/// @brief Tests shutdown command argument parsing
/// The shutdown command supports an optional "type" argument. This test
/// checks that for valid values, the shutdown() method: sets the shutdown
/// type to correct value, set the shutdown flag to true, and returns a
/// success response; and for invalid values: sets the shutdown flag to false
/// and returns a failure response.
TEST_F(D2ProcessTest, shutdownArgs) {
    isc::data::ElementPtr args;
    isc::data::ConstElementPtr answer;
    const char* default_args = "{}";
    const char* normal_args =  "{ \"type\" : \"normal\" }";
    const char* drain_args = "{ \"type\" : \"drain_first\" }";
    const char* now_args = "{ \"type\" : \"now\" }";
    const char* bogus_args = "{ \"type\" : \"bogus\" }";

    // Verify defaulting to SD_NORMAL if no argument is given.
    ASSERT_NO_THROW(args = isc::data::Element::fromJSON(default_args));
    EXPECT_NO_THROW(answer = shutdown(args));
    ASSERT_TRUE(checkAnswer(answer, 0));
    EXPECT_EQ(SD_NORMAL, getShutdownType());
    EXPECT_TRUE(shouldShutdown());

    // Verify argument value "normal".
    ASSERT_NO_THROW(args = isc::data::Element::fromJSON(normal_args));
    EXPECT_NO_THROW(answer = shutdown(args));
    ASSERT_TRUE(checkAnswer(answer, 0));
    EXPECT_EQ(SD_NORMAL, getShutdownType());
    EXPECT_TRUE(shouldShutdown());

    // Verify argument value "drain_first".
    ASSERT_NO_THROW(args = isc::data::Element::fromJSON(drain_args));
    EXPECT_NO_THROW(answer = shutdown(args));
    ASSERT_TRUE(checkAnswer(answer, 0));
    EXPECT_EQ(SD_DRAIN_FIRST, getShutdownType());
    EXPECT_TRUE(shouldShutdown());

    // Verify argument value "now".
    ASSERT_NO_THROW(args = isc::data::Element::fromJSON(now_args));
    EXPECT_NO_THROW(answer = shutdown(args));
    ASSERT_TRUE(checkAnswer(answer, 0));
    EXPECT_EQ(SD_NOW, getShutdownType());
    EXPECT_TRUE(shouldShutdown());

    // Verify correct handling of an invalid value.
    ASSERT_NO_THROW(args = isc::data::Element::fromJSON(bogus_args));
    EXPECT_NO_THROW(answer = shutdown(args));
    ASSERT_TRUE(checkAnswer(answer, 1));
    EXPECT_FALSE(shouldShutdown());
}

/// @brief Tests shutdown criteria logic
/// D2Process using the method canShutdown() to determine if a shutdown
/// can be performed given the value of the shutdown flag and the type of
/// shutdown requested.  For each shutdown type certain criteria must be met
/// before the shutdown is permitted.  This method is invoked once each pass
/// through the main event loop.  This test checks the operation of the
/// canShutdown method.  It uses a convenience method, checkCanShutdown(),
/// which sets the shutdown type to the given value and invokes canShutdown(),
/// returning its result.
TEST_F(D2ProcessTest, canShutdown) {
    ASSERT_TRUE(runWithConfig(valid_d2_config));
    const D2QueueMgrPtr& queue_mgr = getD2QueueMgr();

    // Shutdown flag is false.  Method should return false for all types.
    EXPECT_FALSE(checkCanShutdown(SD_NORMAL));
    EXPECT_FALSE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_FALSE(checkCanShutdown(SD_NOW));

    // Set shutdown flag to true.
    setShutdownFlag(true);

    // Queue Manager is running, queue is empty, no transactions.
    // Only SD_NOW should return true.
    EXPECT_FALSE(checkCanShutdown(SD_NORMAL));
    EXPECT_FALSE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_TRUE(checkCanShutdown(SD_NOW));

    // Tell queue manager to stop.
    queue_mgr->stopListening();
    // Verify that the queue manager is stopping.
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr->getMgrState());

    // Queue Manager is stopping, queue is empty, no transactions.
    // Only SD_NOW should return true.
    EXPECT_FALSE(checkCanShutdown(SD_NORMAL));
    EXPECT_FALSE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_TRUE(checkCanShutdown(SD_NOW));

    // Allow cancel event to process.
    ASSERT_NO_THROW(runIO());
    // Verify that queue manager is stopped.
    EXPECT_EQ(D2QueueMgr::STOPPED, queue_mgr->getMgrState());

    // Queue Manager is stopped, queue is empty, no transactions.
    // All types should return true.
    EXPECT_TRUE(checkCanShutdown(SD_NORMAL));
    EXPECT_TRUE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_TRUE(checkCanShutdown(SD_NOW));

    const char* test_msg =
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : false , "
        " \"fqdn\" : \"fish.tmark.org\" , "
        " \"ip-address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"010203040A7F8E3D\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

    // Manually enqueue a request.  This lets us test logic with queue
    // not empty.
    dhcp_ddns::NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr = dhcp_ddns::NameChangeRequest::fromJSON(test_msg));
    ASSERT_NO_THROW(queue_mgr->enqueue(ncr));
    ASSERT_EQ(1, queue_mgr->getQueueSize());

    // Queue Manager is stopped. Queue is not empty, no transactions.
    // SD_DRAIN_FIRST should be false, SD_NORMAL and SD_NOW should be true.
    EXPECT_TRUE(checkCanShutdown(SD_NORMAL));
    EXPECT_FALSE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_TRUE(checkCanShutdown(SD_NOW));

    // Now use update manager to dequeue the request and make a transaction.
    // This lets us verify transaction list not empty logic.
    const D2UpdateMgrPtr& update_mgr = getD2UpdateMgr();
    ASSERT_TRUE(update_mgr);
    ASSERT_NO_THROW(update_mgr->sweep());
    ASSERT_EQ(0, queue_mgr->getQueueSize());
    ASSERT_EQ(1, update_mgr->getTransactionCount());

    // Queue Manager is stopped. Queue is empty, one transaction.
    // Only SD_NOW should be true.
    EXPECT_FALSE(checkCanShutdown(SD_NORMAL));
    EXPECT_FALSE(checkCanShutdown(SD_DRAIN_FIRST));
    EXPECT_TRUE(checkCanShutdown(SD_NOW));
}


/// @brief Verifies that an "external" call to shutdown causes the run method
/// to exit gracefully.
TEST_F(D2ProcessTest, normalShutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*getIoService());
    timer.setup(boost::bind(&D2ProcessTest::genShutdownCallback, this),
                2 * 1000);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_NO_THROW(run());

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2200);
}


/// @brief Verifies that an "uncaught" exception thrown during event loop
/// execution is treated as a fatal error.
TEST_F(D2ProcessTest, fatalErrorShutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // the exception.  (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*getIoService());
    timer.setup(boost::bind(&D2ProcessTest::genFatalErrorCallback, this),
                2 * 1000);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_THROW(run(), DProcessBaseError);

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the anomaly occurred
    // during io callback processing.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2200);
}

/// @brief Used to permit visual inspection of logs to ensure
/// DHCP_DDNS_NOT_ON_LOOPBACK is issued when ip_address is not
/// loopback.
TEST_F(D2ProcessTest, notLoopbackTest) {
    const char* config = "{ "
                        "\"ip-address\" : \"0.0.0.0\" , "
                        "\"port\" : 53001, "
                        "\"tsig-keys\": [],"
                        "\"forward-ddns\" : {},"
                        "\"reverse-ddns\" : {}"
                        "}";

    // Note we don't care nor can we predict if this
    // succeeds or fails. The address and port may or may
    // not be valid on the test host.
    runWithConfig(config);
}


/// @brief Used to permit visual inspection of logs to ensure
/// DHCP_DDNS_NOT_ON_LOOPBACK is not issued.
TEST_F(D2ProcessTest, v4LoopbackTest) {
    const char* config = "{ "
                        "\"ip-address\" : \"127.0.0.1\" , "
                        "\"port\" : 53001, "
                        "\"tsig-keys\": [],"
                        "\"forward-ddns\" : {},"
                        "\"reverse-ddns\" : {}"
                        "}";
    ASSERT_TRUE(runWithConfig(config));
}

/// @brief Used to permit visual inspection of logs to ensure
/// DHCP_DDNS_NOT_ON_LOOPBACK is not issued.
TEST_F(D2ProcessTest, v6LoopbackTest) {
    const char* config = "{ "
                        "\"ip-address\" : \"::1\" , "
                        "\"port\" : 53001, "
                        "\"tsig-keys\": [],"
                        "\"forward-ddns\" : {},"
                        "\"reverse-ddns\" : {}"
                        "}";
    ASSERT_TRUE(runWithConfig(config));
}

} // end of anonymous namespace
