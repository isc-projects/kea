// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfg_expiration.h>
#include <exceptions/exceptions.h>
#include <boost/function.hpp>
#include <gtest/gtest.h>
#include <stdint.h>

using namespace isc;
using namespace isc::dhcp;

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

} // end of anonymous namespace
