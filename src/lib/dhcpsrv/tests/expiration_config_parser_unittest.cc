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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <gtest/gtest.h>
#include <sstream>
#include <stdint.h>
#include <string>

using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c ExpirationConfigParser.
class ExpirationConfigParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

    /// @brief Include a specified parameter in the configuration.
    ///
    /// If the specified parameter already exists, its value is replaced.
    ///
    /// @param param_name Parameter name.
    /// @param value Parameter value.
    void addParam(const std::string& param_name, const int64_t value);

    /// @brief Creates configuration and parses it with the parser under test.
    ///
    /// This method creates the JSON configuration form the parameters
    /// specified using the @c ExpirationConfigParserTest::addParam method.
    /// It then uses the parser to parse this configuration. Any exceptions
    /// emitted by the parser are propagated to the caller (they aren't
    /// caught by this method).
    ///
    /// @return Pointer to the parsed configuration.
    CfgExpirationPtr renderConfig() const;

    /// @brief Tests that the out of range parameter value is not accepted.
    ///
    /// This test checks that the negative value and the value which is
    /// greater than the maximum for the given parameter is not accepted.
    ///
    /// @param param Parameter name.
    /// @param max_value Maximum value allowed for the parameter.
    void testOutOfRange(const std::string& param, const uint64_t max_value);

private:

    /// @brief Holds configuration parameters specified for a test.
    std::map<std::string, int64_t> config_params_;

};

void
ExpirationConfigParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
ExpirationConfigParserTest::TearDown() {
    CfgMgr::instance().clear();
}

void
ExpirationConfigParserTest::addParam(const std::string& param_name,
                                     const int64_t value) {
    config_params_[param_name] = value;
}

CfgExpirationPtr
ExpirationConfigParserTest::renderConfig() const {
    std::ostringstream s;
    // Create JSON configuration from the parameters in the map.
    s << "{";
    for (std::map<std::string, int64_t>::const_iterator param =
             config_params_.begin(); param != config_params_.end();
         ++param) {
        // Include comma sign if we're at the subsequent parameter.
        if (std::distance(config_params_.begin(), param) > 0) {
            s << ",";
        }
        s << "\"" << param->first << "\": " << param->second;
    }
    s << "}";

    ElementPtr config_element = Element::fromJSON(s.str());

    // Parse the configuration. This may emit exceptions.
    ExpirationConfigParser parser;
    parser.build(config_element);

    // No exception so return configuration.
    return (CfgMgr::instance().getStagingCfg()->getCfgExpiration());
}

void
ExpirationConfigParserTest::testOutOfRange(const std::string& param,
                                           const uint64_t max_value) {
    // Remove any existing parameters which would influence the
    // behavior of the test.
    config_params_.clear();

    // Negative value is not allowed.
    addParam(param, -3);
    EXPECT_THROW(renderConfig(), DhcpConfigError)
        << "test for negative value of '" << param << "' failed";

    // Value greater than maximum is not allowed.
    addParam(param, max_value + 1);
    EXPECT_THROW(renderConfig(), DhcpConfigError)
        << "test for out of range value of '" << param << "' failed";

    // Value in range should be accepted.
    addParam(param, max_value);
    EXPECT_NO_THROW(renderConfig())
        << "test for in range value of '" << param << "' failed";
}


// This test verifies that all parameters for the expiration may be configured.
TEST_F(ExpirationConfigParserTest, allParameters) {
    // Create configuration which overrides default values of all parameters.
    addParam("reclaim-timer-wait-time", 20);
    addParam("flush-reclaimed-timer-wait-time", 35);
    addParam("hold-reclaimed-time", 1800);
    addParam("max-reclaim-leases", 50);
    addParam("max-reclaim-time", 100);
    addParam("unwarned-reclaim-cycles", 10);

    CfgExpirationPtr cfg;
    ASSERT_NO_THROW(cfg = renderConfig());
    EXPECT_EQ(20, cfg->getReclaimTimerWaitTime());
    EXPECT_EQ(35, cfg->getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(1800, cfg->getHoldReclaimedTime());
    EXPECT_EQ(50, cfg->getMaxReclaimLeases());
    EXPECT_EQ(100, cfg->getMaxReclaimTime());
    EXPECT_EQ(10, cfg->getUnwarnedReclaimCycles());
}

// This test verifies that default values are used if no parameter is
// specified.
TEST_F(ExpirationConfigParserTest, noParameters) {
    CfgExpirationPtr cfg;
    ASSERT_NO_THROW(cfg = renderConfig());
    EXPECT_EQ(CfgExpiration::DEFAULT_RECLAIM_TIMER_WAIT_TIME,
              cfg->getReclaimTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME,
              cfg->getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_HOLD_RECLAIMED_TIME,
              cfg->getHoldReclaimedTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_LEASES,
              cfg->getMaxReclaimLeases());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_TIME,
              cfg->getMaxReclaimTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_UNWARNED_RECLAIM_CYCLES,
              cfg->getUnwarnedReclaimCycles());
}

// This test verifies that a subset of parameters may be specified and
// that default values are used for those that aren't specified.
TEST_F(ExpirationConfigParserTest, someParameters) {
    addParam("reclaim-timer-wait-time", 15);
    addParam("hold-reclaimed-time", 2000);
    addParam("max-reclaim-time", 200);

    CfgExpirationPtr cfg;
    ASSERT_NO_THROW(cfg = renderConfig());
    EXPECT_EQ(15, cfg->getReclaimTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME,
              cfg->getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(2000, cfg->getHoldReclaimedTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_LEASES,
              cfg->getMaxReclaimLeases());
    EXPECT_EQ(200, cfg->getMaxReclaimTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_UNWARNED_RECLAIM_CYCLES,
              cfg->getUnwarnedReclaimCycles());
}

// This test verifies that another subset of parameters may be specified
// and that default values are used for those that aren't specified.
TEST_F(ExpirationConfigParserTest, otherParameters) {
    addParam("flush-reclaimed-timer-wait-time", 50);
    addParam("max-reclaim-leases", 60);
    addParam("unwarned-reclaim-cycles", 20);

    CfgExpirationPtr cfg;
    ASSERT_NO_THROW(cfg = renderConfig());

    EXPECT_EQ(CfgExpiration::DEFAULT_RECLAIM_TIMER_WAIT_TIME,
              cfg->getReclaimTimerWaitTime());
    EXPECT_EQ(50, cfg->getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(CfgExpiration::DEFAULT_HOLD_RECLAIMED_TIME,
              cfg->getHoldReclaimedTime());
    EXPECT_EQ(60, cfg->getMaxReclaimLeases());
    EXPECT_EQ(CfgExpiration::DEFAULT_MAX_RECLAIM_TIME,
              cfg->getMaxReclaimTime());
    EXPECT_EQ(20, cfg->getUnwarnedReclaimCycles());
}

// This test verifies that the exception is thrown if unsupported
// parameter is specified.
TEST_F(ExpirationConfigParserTest, invalidParameter) {
   addParam("reclaim-timer-wait-time", 20);
   addParam("invalid-parameter", 20);

   EXPECT_THROW(renderConfig(), DhcpConfigError);
}

// This test verifies that negative parameter values are not allowed.
TEST_F(ExpirationConfigParserTest, outOfRangeValues) {
    testOutOfRange("reclaim-timer-wait-time",
                   CfgExpiration::LIMIT_RECLAIM_TIMER_WAIT_TIME);
    testOutOfRange("flush-reclaimed-timer-wait-time",
                   CfgExpiration::LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME);
    testOutOfRange("hold-reclaimed-time",
                   CfgExpiration::LIMIT_HOLD_RECLAIMED_TIME);
    testOutOfRange("max-reclaim-leases",
                   CfgExpiration::LIMIT_MAX_RECLAIM_LEASES);
    testOutOfRange("max-reclaim-time",
                   CfgExpiration::LIMIT_MAX_RECLAIM_TIME);
    testOutOfRange("unwarned-reclaim-cycles",
                   CfgExpiration::LIMIT_UNWARNED_RECLAIM_CYCLES);
}

// This test verifies that it is not allowed to specify a value as
// a text.
TEST_F(ExpirationConfigParserTest, notNumberValue) {
    // The value should not be in quotes.
    std::string config = "{ \"reclaim-timer-wait-time\": \"10\" }";
    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration. It should throw exception.
    ExpirationConfigParser parser;
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

} // end of anonymous namespace
