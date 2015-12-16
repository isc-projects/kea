// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <util/stopwatch.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <stdint.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief Type definition of the @c CfgExpiration modified function.
typedef boost::function<void(CfgExpiration*, const int64_t)> ModifierFun;
/// @brief Type definition of the @c CfgExpiration accessor function
/// returning uint16_t value.
typedef boost::function<uint16_t(CfgExpiration*)> AccessorFunUint16;
/// @brief Type definition of the @c CfgExpiration accessor function
/// returning uint32_t value.
typedef boost::function<uint32_t(CfgExpiration*)> AccessorFunUint32;

/// @brief Tests the accessor and modifier function for a particular
/// configuration parameter held in @c CfgExpiration.
///
/// This is a simple test which tries to set the given parameter to
/// different values:
/// - value greater than maximum allowed for this parameter - expects
///   the exception to be thrown,
/// - value lower than 0 - expects the exception to be thrown,
/// - value equal to the maximum allowed,
/// - value equal to maximum allowed minus 1.
///
/// @param limit Maximum allowed value for the parameter.
/// @param modifier Pointer to the modifier function to be tested.
/// @param accessor Pointer to the accessor function to be tested.
/// @tparam ReturnType Type of the value returned by the accessor,
/// i.e. uint16_t or uint32_t.
template<typename ReturnType>
void
testAccessModify(const int64_t limit, const ModifierFun& modifier,
                 const boost::function<ReturnType(CfgExpiration*)>& accessor) {
    CfgExpiration cfg;

    // Setting the value to maximum allowed + 1 should result in
    // an exception.
    ASSERT_THROW(modifier(&cfg, limit + 1), OutOfRange);

    // Setting to the negative value should result in an exception.
    ASSERT_THROW(modifier(&cfg, -1), OutOfRange);

    // Setting the value to the maximum allowed should pass.
    ASSERT_NO_THROW(modifier(&cfg, limit));
    EXPECT_EQ(limit, accessor(&cfg));

    // Setting the value to the maximum allowed - 1 should pass.
    ASSERT_NO_THROW(modifier(&cfg, limit - 1));
    EXPECT_EQ(limit - 1, accessor(&cfg));

    // Setting the value to 0 should pass.
    ASSERT_NO_THROW(modifier(&cfg, 0));
    EXPECT_EQ(0, accessor(&cfg));
}

/// @brief Tests that modifier and the accessor returning uint16_t value
/// work as expected.
///
/// @param limit Maximum allowed value for the parameter.
/// @param modifier Pointer to the modifier function to be tested.
/// @param accessor Pointer to the accessor function to be tested.
void
testAccessModifyUint16(const int64_t limit, const ModifierFun& modifier,
                       const AccessorFunUint16& accessor) {
    testAccessModify<uint16_t>(limit, modifier, accessor);
}

/// @brief Tests that modifier and the accessor returning uint32_t value
/// work as expected.
///
/// @param limit Maximum allowed value for the parameter.
/// @param modifier Pointer to the modifier function to be tested.
/// @param accessor Pointer to the accessor function to be tested.
void
testAccessModifyUint32(const int64_t limit, const ModifierFun& modifier,
                       const AccessorFunUint32& accessor) {
    testAccessModify<uint32_t>(limit, modifier, accessor);
}

/// Test the default values of CfgExpiration object.
TEST(CfgExpirationTest, defaults) {
    CfgExpiration cfg;
    EXPECT_EQ(CfgExpiration::DEFAULT_RECLAIM_TIMER_WAIT_TIME,
              cfg.getReclaimTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME,
              cfg.getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_HOLD_RECLAIMED_TIME,
              cfg.getHoldReclaimedTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_LEASES,
              cfg.getMaxReclaimLeases());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_TIME,
              cfg.getMaxReclaimTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_UNWARNED_RECLAIM_CYCLES,
              cfg.getUnwarnedReclaimCycles());
}

// Test the {get,set}ReclaimTimerWaitTime.
TEST(CfgExpirationTest, getReclaimTimerWaitTime) {
    testAccessModify<uint16_t>(CfgExpiration::LIMIT_RECLAIM_TIMER_WAIT_TIME,
                               &CfgExpiration::setReclaimTimerWaitTime,
                               &CfgExpiration::getReclaimTimerWaitTime);
}

// Test the {get,set}FlushReclaimedTimerWaitTime.
TEST(CfgExpirationTest, getFlushReclaimedTimerWaitTime) {
    testAccessModifyUint16(CfgExpiration::LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME,
                           &CfgExpiration::setFlushReclaimedTimerWaitTime,
                           &CfgExpiration::getFlushReclaimedTimerWaitTime);
}

// Test the {get,set}HoldReclaimedTime.
TEST(CfgExpirationTest, getHoldReclaimedTime) {
    testAccessModifyUint32(CfgExpiration::LIMIT_HOLD_RECLAIMED_TIME,
                           &CfgExpiration::setHoldReclaimedTime,
                           &CfgExpiration::getHoldReclaimedTime);
}

// Test the {get,set}MaxReclaimLeases.
TEST(CfgExpirationTest, getMaxReclaimLeases) {
    testAccessModifyUint32(CfgExpiration::LIMIT_MAX_RECLAIM_LEASES,
                           &CfgExpiration::setMaxReclaimLeases,
                           &CfgExpiration::getMaxReclaimLeases);
}

// Test the {get,set}MaxReclaimTime.
TEST(CfgExpirationTest, getMaxReclaimTime) {
    testAccessModifyUint16(CfgExpiration::LIMIT_MAX_RECLAIM_TIME,
                           &CfgExpiration::setMaxReclaimTime,
                           &CfgExpiration::getMaxReclaimTime);
}

// Test the {get,set}UnwarnedReclaimCycles.
TEST(CfgExpirationTest, getUnwarnedReclaimCycles) {
    testAccessModifyUint16(CfgExpiration::LIMIT_UNWARNED_RECLAIM_CYCLES,
                           &CfgExpiration::setUnwarnedReclaimCycles,
                           &CfgExpiration::getUnwarnedReclaimCycles);
}

/// @brief Implements test routines for leases reclamation.
///
/// This class implements two routines called by the @c CfgExpiration object
/// instead of the typical routines for leases' reclamation in the
/// @c AllocEngine. These methods do not perform the actual reclamation,
/// but instead they record the number of calls to them and the parameters
/// with which they were executed. This allows for checking if the
/// @c CfgExpiration object calls the leases reclamation routine with the
/// appropriate parameteres.
class LeaseReclamationStub {
public:

    /// @brief Collection of parameters with which the @c reclaimExpiredLeases
    /// method is called.
    ///
    /// Examination of these values allows for assesment if the @c CfgExpiration
    /// calls the routine with the appropriate values.
    struct RecordedParams {
        /// @brief Maximum number of leases to be processed.
        size_t max_leases;

        /// @brief Timeout for processing leases in milliseconds.
        uint16_t timeout;

        /// @brief Boolean flag which indicates if the leases should be removed
        /// when reclaimed.
        bool remove_lease;

        /// @brief Maximum number of reclamation attempts after which all leases
        /// should be reclaimed.
        uint16_t max_unwarned_cycles;

        /// @brief Constructor
        ///
        /// Sets all numeric values to 0xFFFF and the boolean values to false.
        RecordedParams()
            : max_leases(0xFFFF), timeout(0xFFFF), remove_lease(false),
              max_unwarned_cycles(0xFFFF) {
        }
    };

    /// @brief Constructor.
    ///
    /// Resets recorded parameters and obtains the instance of the @c TimerMgr.
    LeaseReclamationStub()
        : reclaim_calls_count_(0), delete_calls_count_(0), reclaim_params_(),
          secs_param_(0), timer_mgr_(TimerMgr::instance()) {
    }

    /// @brief Stub implementation of the leases' reclamation routine.
    ///
    /// @param max_leases Maximum number of leases to be processed.
    /// @param timeout Timeout for processing leases in milliseconds.
    /// @remove_lease Boolean flag which indicates if the leases should be
    /// removed when it is reclaimed.
    /// @param Maximum number of reclamation attempts after which all leases
    /// should be reclaimed.
    void
    reclaimExpiredLeases(const size_t max_leases, const uint16_t timeout,
                         const bool remove_lease,
                         const uint16_t max_unwarned_cycles) {
        // Increase calls counter for this method.
        ++reclaim_calls_count_;
        // Record all parameters with which this method has been called.
        reclaim_params_.max_leases = max_leases;
        reclaim_params_.timeout = timeout;
        reclaim_params_.remove_lease = remove_lease;
        reclaim_params_.max_unwarned_cycles = max_unwarned_cycles;

        // Leases' reclamation routine is responsible for re-scheduling
        // the timer.
        timer_mgr_->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
    }

    /// @brief Stub implementation of the routine which flushes
    /// expired-reclaimed leases.
    ///
    /// @param secs Specifies the minimum amount of time, expressed in
    /// seconds, that must elapse before the expired-reclaime lease is
    /// deleted from the database.
    void
    deleteReclaimedLeases(const uint32_t secs) {
        // Increase calls counter for this method.
        ++delete_calls_count_;
        // Record the value of the parameter.
        secs_param_ = secs;

        // Routine which flushes the reclaimed leases is responsible for
        // re-scheduling the timer.
        timer_mgr_->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
    }

    /// @brief Counter holding the number of calls to @c reclaimExpiredLeases.
    long reclaim_calls_count_;

    /// @brief Counter holding the number of calls to @c deleteReclaimedLeases.
    long delete_calls_count_;

    /// @brief Structure holding values of parameters with which the
    /// @c reclaimExpiredLeases was called.
    ///
    /// These values are overriden on subsequent calls to this method.
    RecordedParams reclaim_params_;

    /// @brief Value of the parameter with which the @c deleteReclaimedLeases
    /// was called.
    uint32_t secs_param_;

private:

    /// @brief Pointer to the @c TimerMgr.
    TimerMgrPtr timer_mgr_;

};

/// @brief Pointer to the @c LeaseReclamationStub.
typedef boost::shared_ptr<LeaseReclamationStub> LeaseReclamationStubPtr;

/// @brief Test fixture class for the @c CfgExpiration.
class CfgExpirationTimersTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the test fixture class. Besides initialization
    /// of the class members, it also stops the @c TimerMgr worker thread
    /// and removes any registered timers.
    CfgExpirationTimersTest()
        : timer_mgr_(TimerMgr::instance()),
          stub_(new LeaseReclamationStub()),
          cfg_(true) {
        cleanupTimerMgr();
    }

    /// @brief Destructor.
    ///
    /// It stops the @c TimerMgr worker thread and removes any registered
    /// timers.
    virtual ~CfgExpirationTimersTest() {
        cleanupTimerMgr();
    }

    /// @brief Stop @c TimerMgr worker thread and remove the timers.
    void cleanupTimerMgr() const {
        timer_mgr_->stopThread();
        timer_mgr_->unregisterTimers();
    }

    /// @brief Runs timers for specified time.
    ///
    /// Internally, this method calls @c IfaceMgr::receive6 to run the
    /// callbacks for the installed timers.
    ///
    /// @param timeout_ms Amount of time after which the method returns.
    void runTimersWithTimeout(const long timeout_ms) {
        Stopwatch stopwatch;
        while (stopwatch.getTotalMilliseconds() < timeout_ms) {
            // Block for up to one millisecond waiting for the timers'
            // callbacks to be executed.
            IfaceMgr::instancePtr()->receive6(0, 1000);
        }
    }

    /// @brief Setup timers according to the configuration and run them
    /// for the specified amount of time.
    ///
    /// @param timeout_ms Timeout in milliseconds.
    void setupAndRun(const long timeout_ms) {
        cfg_.setupTimers(&LeaseReclamationStub::reclaimExpiredLeases,
                         &LeaseReclamationStub::deleteReclaimedLeases,
                         stub_.get());
        // Run timers.
        ASSERT_NO_THROW({
            timer_mgr_->startThread();
            runTimersWithTimeout(timeout_ms);
            timer_mgr_->stopThread();
        });
    }

    /// @brief Pointer to the @c TimerMgr.
    TimerMgrPtr timer_mgr_;

    /// @brief Pointer to the @c LeaseReclamationStub instance.
    LeaseReclamationStubPtr stub_;

    /// @brief Instance of the @c CfgExpiration class used by the tests.
    CfgExpiration cfg_;
};

// Test that the reclamation routines are called with the appropriate parameters.
TEST_F(CfgExpirationTimersTest, reclamationParameters) {
    // Set this value to true, to make sure that the timer callback would
    // modify this value to false.
    stub_->reclaim_params_.remove_lease = true;

    // Set parameters to some non-default values.
    cfg_.setMaxReclaimLeases(1000);
    cfg_.setMaxReclaimTime(1500);
    cfg_.setHoldReclaimedTime(1800);
    cfg_.setUnwarnedReclaimCycles(13);

    // Run timers for 500ms.
    ASSERT_NO_FATAL_FAILURE(setupAndRun(500));

    // Make sure we had more than one call to the reclamation routine.
    ASSERT_GT(stub_->reclaim_calls_count_, 1);
    // Make sure it was called with appropriate arguments.
    EXPECT_EQ(1000, stub_->reclaim_params_.max_leases);
    EXPECT_EQ(1500, stub_->reclaim_params_.timeout);
    EXPECT_FALSE(stub_->reclaim_params_.remove_lease);
    EXPECT_EQ(13, stub_->reclaim_params_.max_unwarned_cycles);

    // Make sure we had more than one call to the routine which flushes
    // expired reclaimed leases.
    ASSERT_GT(stub_->delete_calls_count_, 1);
    // Make sure that the argument was correct.
    EXPECT_EQ(1800, stub_->secs_param_);
}

// This test verifies that if the value of "flush-reclaimed-timer-wait-time"
// configuration parameter is set to 0, the lease reclamation routine would
// delete reclaimed leases from a lease database.
TEST_F(CfgExpirationTimersTest, noLeaseAffinity) {
    // Set the timer for flushing leases to 0. This effectively disables
    // the timer.
    cfg_.setFlushReclaimedTimerWaitTime(0);

    // Run the lease reclamation timer for a while.
    ASSERT_NO_FATAL_FAILURE(setupAndRun(500));

    // Make sure that the lease reclamation routine has been executed a
    // couple of times.
    ASSERT_GT(stub_->reclaim_calls_count_, 1);
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_LEASES,
              stub_->reclaim_params_.max_leases);
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_TIME,
              stub_->reclaim_params_.timeout);
    // When the "flush" timer is disabled, the lease reclamation routine is
    // responsible for removal of reclaimed leases. This is controlled using
    // the "remove_lease" parameter which should be set to true in this case.
    EXPECT_TRUE(stub_->reclaim_params_.remove_lease);

    // The routine flushing reclaimed leases should not be run at all.
    EXPECT_EQ(0, stub_->delete_calls_count_);
}

// This test verfies that lease reclamation may be disabled.
TEST_F(CfgExpirationTimersTest, noLeaseReclamation) {
    // Disable both timers.
    cfg_.setReclaimTimerWaitTime(0);
    cfg_.setFlushReclaimedTimerWaitTime(0);

    // Wait for 500ms.
    ASSERT_NO_FATAL_FAILURE(setupAndRun(500));

    // Make sure that neither leases' reclamation routine nor the routine
    // flushing expired-reclaimed leases was run.
    EXPECT_EQ(0, stub_->reclaim_calls_count_);
    EXPECT_EQ(0, stub_->delete_calls_count_);
}

} // end of anonymous namespace
