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

#include <stats/stats_mgr.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <util/boost_time_utils.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::stats;
using namespace boost::posix_time;

namespace {

/// @brief Fixture class for StatsMgr testing
///
/// Very simple class that makes sure that StatsMgr is indeed instantiated
/// before the test and any statistics are wiped out after it.
class StatsMgrTest : public ::testing::Test {
public:
    /// @brief Constructor
    /// Makes sure that the Statistics Manager is instantiated.
    StatsMgrTest() {
        StatsMgr::instance();
    }

    /// @brief Destructor
    /// Removes all statistics.
    ~StatsMgrTest() {
        StatsMgr::instance().removeAll();
    }
};

// Basic test for statistics manager interface.
TEST_F(StatsMgrTest, basic) {

    // Getting an instance
    EXPECT_NO_THROW(StatsMgr::instance());

    // Check that there are no statistics recorded by default.
    EXPECT_EQ(0, StatsMgr::instance().count());
}

// Test checks whether it's possible to record and later report
// an integer statistic.
TEST_F(StatsMgrTest, integerStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("alpha",
                                                  static_cast<int64_t>(1234)));

    ObservationPtr alpha;
    EXPECT_NO_THROW(alpha = StatsMgr::instance().getObservation("alpha"));
    ASSERT_TRUE(alpha);

    std::string exp = "{ \"alpha\": [ [ 1234, \""
        + isc::util::ptimeToText(alpha->getInteger().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("alpha")->str());
}

// Test checks whether it's possible to record and later report
// a floating point statistic.
TEST_F(StatsMgrTest, floatStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("beta", 12.34));

    ObservationPtr beta;
    EXPECT_NO_THROW(beta = StatsMgr::instance().getObservation("beta"));
    ASSERT_TRUE(beta);

    std::string exp = "{ \"beta\": [ [ 12.34, \""
        + isc::util::ptimeToText(beta->getFloat().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("beta")->str());
}

// Test checks whether it's possible to record and later report
// a duration statistic.
TEST_F(StatsMgrTest, durationStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("gamma",
                                                  microsec::time_duration(1,2,3,4)));

    ObservationPtr gamma;
    EXPECT_NO_THROW(gamma = StatsMgr::instance().getObservation("gamma"));
    ASSERT_TRUE(gamma);

    std::string exp = "{ \"gamma\": [ [ \"01:02:03.000004\", \""
        + isc::util::ptimeToText(gamma->getDuration().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("gamma")->str());
}

// Test checks whether it's possible to record and later report
// a string statistic.
TEST_F(StatsMgrTest, stringStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("delta",
                                                  "Lorem ipsum"));

    ObservationPtr delta;
    EXPECT_NO_THROW(delta = StatsMgr::instance().getObservation("delta"));
    ASSERT_TRUE(delta);

    std::string exp = "{ \"delta\": [ [ \"Lorem ipsum\", \""
        + isc::util::ptimeToText(delta->getString().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("delta")->str());
}

// Setting limits is currently not implemented, so those methods should
// throw.
TEST_F(StatsMgrTest, setLimits) {
    EXPECT_THROW(StatsMgr::instance().setMaxSampleAge("foo",
                                                      time_duration(1,0,0,0)),
                 NotImplemented);

    EXPECT_THROW(StatsMgr::instance().setMaxSampleCount("foo", 100),
                 NotImplemented);
}

// This test checks whether a single (get("foo")) and all (getAll())
// statistics are reported properly.
TEST_F(StatsMgrTest, getGetAll) {

    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem");

    // Now add some values to them
    StatsMgr::instance().addValue("alpha", static_cast<int64_t>(5678));
    StatsMgr::instance().addValue("beta", 56.78);
    StatsMgr::instance().addValue("gamma", time_duration(5,6,7,8));
    StatsMgr::instance().addValue("delta", " ipsum");

    // There should be 4 statistics reported
    EXPECT_EQ(4, StatsMgr::instance().count());

    // Now check whether they can be reported back
    ConstElementPtr rep_alpha = StatsMgr::instance().get("alpha");
    ConstElementPtr rep_beta = StatsMgr::instance().get("beta");
    ConstElementPtr rep_gamma = StatsMgr::instance().get("gamma");
    ConstElementPtr rep_delta = StatsMgr::instance().get("delta");

    ASSERT_TRUE(rep_alpha);
    ASSERT_TRUE(rep_beta);
    ASSERT_TRUE(rep_gamma);
    ASSERT_TRUE(rep_delta);

    std::string exp_str_alpha = "[ [ 6912, \""
        + isc::util::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ] ]";
    std::string exp_str_beta = "[ [ 69.12, \""
        + isc::util::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ] ]";
    std::string exp_str_gamma = "[ [ \"06:08:10.000012\", \""
        + isc::util::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ] ]";
    std::string exp_str_delta = "[ [ \"Lorem ipsum\", \""
        + isc::util::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ] ]";

    // Check that individual stats are reported properly
    EXPECT_EQ("{ \"alpha\": " + exp_str_alpha + " }", rep_alpha->str());
    EXPECT_EQ("{ \"beta\": " + exp_str_beta + " }", rep_beta->str());
    EXPECT_EQ("{ \"gamma\": " + exp_str_gamma + " }", rep_gamma->str());
    EXPECT_EQ("{ \"delta\": " + exp_str_delta + " }", rep_delta->str());

    // Check that non-existent metric is not reported.
    EXPECT_EQ("{  }", StatsMgr::instance().get("epsilon")->str());

    // Check that all of them can be reported at once
    ConstElementPtr rep_all = StatsMgr::instance().getAll();
    ASSERT_TRUE(rep_all);

    // Verifying this is a bit more involved, as we don't know whether the
    // order would be preserved or not.
    EXPECT_EQ(4, rep_all->size());
    ASSERT_TRUE(rep_all->get("alpha"));
    ASSERT_TRUE(rep_all->get("beta"));
    ASSERT_TRUE(rep_all->get("delta"));
    ASSERT_TRUE(rep_all->get("gamma"));
    EXPECT_FALSE(rep_all->get("epsilon"));

    EXPECT_EQ(exp_str_alpha, rep_all->get("alpha")->str());
    EXPECT_EQ(exp_str_beta, rep_all->get("beta")->str());
    EXPECT_EQ(exp_str_gamma, rep_all->get("gamma")->str());
    EXPECT_EQ(exp_str_delta, rep_all->get("delta")->str());
}

// This test checks whether existing statistics can be reset.
TEST_F(StatsMgrTest, reset) {

    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().reset("alpha"));
    EXPECT_EQ(0, StatsMgr::instance().getObservation("alpha")->getInteger().first);

    // The other stats should remain untouched
    EXPECT_EQ(12.34,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(1,2,3,4),
              StatsMgr::instance().getObservation("gamma")->getDuration().first);
    EXPECT_EQ("Lorem ipsum",
              StatsMgr::instance().getObservation("delta")->getString().first);

    // Now let's wipe them, too.
    EXPECT_NO_THROW(StatsMgr::instance().reset("beta"));
    EXPECT_NO_THROW(StatsMgr::instance().reset("gamma"));
    EXPECT_NO_THROW(StatsMgr::instance().reset("delta"));
    EXPECT_EQ(0.0,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(0,0,0,0),
              StatsMgr::instance().getObservation("gamma")->getDuration().first);
    EXPECT_EQ("",
              StatsMgr::instance().getObservation("delta")->getString().first);

    // Resetting statistics should not remove them
    EXPECT_EQ(4, StatsMgr::instance().count());
}

// This test checks whether existing statistics can be reset.
TEST_F(StatsMgrTest, resetAll) {

    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().resetAll());
    EXPECT_EQ(0, StatsMgr::instance().getObservation("alpha")->getInteger().first);
    EXPECT_EQ(0.0,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(0,0,0,0),
              StatsMgr::instance().getObservation("gamma")->getDuration().first);
    EXPECT_EQ("",
              StatsMgr::instance().getObservation("delta")->getString().first);

    // Resetting all statistics should not remove them
    EXPECT_EQ(4, StatsMgr::instance().count());
}

// This test checks whether statistics can be removed.
TEST_F(StatsMgrTest, removeAll) {

    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().removeAll());

    // Resetting all statistics should not remove them
    EXPECT_EQ(0, StatsMgr::instance().count());

    // There should be no such statistics anymore
    EXPECT_EQ("{  }", StatsMgr::instance().get("alpha")->str());
    EXPECT_EQ("{  }", StatsMgr::instance().get("beta")->str());
    EXPECT_EQ("{  }", StatsMgr::instance().get("gamma")->str());
    EXPECT_EQ("{  }", StatsMgr::instance().get("delta")->str());

    // There should be no such statistics anymore
    EXPECT_FALSE(StatsMgr::instance().getObservation("alpha"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("beta"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("gamma"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("delta"));
}

// This is a performance benchmark that checks how long does it take
// to increment a single statistic million times.
//
// Data points:
// It took 00:00:00.363709 (363ms) on late 2013 Mac with Mac OS X 10.9.5.
TEST_F(StatsMgrTest, DISABLED_performanceSingleAdd) {
    StatsMgr::instance().removeAll();

    uint32_t cycles = 1000000;

    ptime before = microsec_clock::local_time();
    for (uint32_t i = 0; i < cycles; ++i) {
        StatsMgr::instance().addValue("metric1", 0.1*i);
    }
    ptime after = microsec_clock::local_time();

    time_duration dur = after - before;

    std::cout << "Incrementing a single statistic " << cycles << " times took: "
              << isc::util::durationToText(dur) << std::endl;
}

// This is a performance benchmark that checks how long does it take
// to set absolute value of a single statistic million times.
//
// Data points:
// It took 00:00:00.361003 (361ms) on late 2013 Mac with Mac OS X 10.9.5.
TEST_F(StatsMgrTest, DISABLED_performanceSingleSet) {
    StatsMgr::instance().removeAll();

    uint32_t cycles = 1000000;

    ptime before = microsec_clock::local_time();
    for (uint32_t i = 0; i < cycles; ++i) {
        StatsMgr::instance().setValue("metric1", 0.1*i);
    }
    ptime after = microsec_clock::local_time();

    time_duration dur = after - before;

    std::cout << "Setting a single statistic " << cycles << " times took: "
              << isc::util::durationToText(dur) << std::endl;
}

// This is a performance benchmark that checks how long does it take to
// increment one statistic a million times, when there is 1000 other statistics
// present.
//
// Data points:
// 00:00:00.436943 (436ms) on late 2013 Mac with Mac OS X 10.9.5
TEST_F(StatsMgrTest, DISABLED_performanceMultipleAdd) {
    StatsMgr::instance().removeAll();

    uint32_t cycles = 1000000;
    uint32_t stats = 1000;

    for (uint32_t i = 0; i < stats; ++i) {
        std::stringstream tmp;
        tmp << "statistic" << i;
        StatsMgr::instance().setValue(tmp.str(), static_cast<int64_t>(i));
    }

    ptime before = microsec_clock::local_time();
    for (uint32_t i = 0; i < cycles; ++i) {
        StatsMgr::instance().addValue("metric1", static_cast<int64_t>(i));
    }
    ptime after = microsec_clock::local_time();

    time_duration dur = after - before;

    std::cout << "Incrementing one of " << stats << " statistics " << cycles
              << " times took: " << isc::util::durationToText(dur) << std::endl;
}

// This is a performance benchmark that checks how long does it take to
// set one statistic to a given value a million times, when there is 1000 other
// statistics present.
//
// Data points:
// 00:00:00.424518 (424ms) on late 2013 Mac with Mac OS X 10.9.5
TEST_F(StatsMgrTest, DISABLED_performanceMultipleSet) {
    StatsMgr::instance().removeAll();

    uint32_t cycles = 1000000;
    uint32_t stats = 1000;

    for (uint32_t i = 0; i < stats; ++i) {
        std::stringstream tmp;
        tmp << "statistic" << i;
        StatsMgr::instance().setValue(tmp.str(), static_cast<int64_t>(i));
    }

    ptime before = microsec_clock::local_time();
    for (uint32_t i = 0; i < cycles; ++i) {
        StatsMgr::instance().setValue("metric1", static_cast<int64_t>(i));
    }
    ptime after = microsec_clock::local_time();

    time_duration dur = after - before;

    std::cout << "Setting one of " << stats << " statistics " << cycles
              << " times took: " << isc::util::durationToText(dur) << std::endl;
}

// Test checks whether statistics name can be generated using various
// indexes.
TEST_F(StatsMgrTest, generateName) {
    // generateName is a templated method, so in principle anything printable
    // to stream can be used as index. However, in practice only integers
    // and possibly strings will be used.

    // Let's text integer as index.
    EXPECT_EQ("subnet[123].pkt4-received",
              StatsMgr::generateName("subnet", 123, "pkt4-received"));

    // Lets' test string as index.
    EXPECT_EQ("subnet[foo].pkt4-received",
              StatsMgr::generateName("subnet", "foo", "pkt4-received"));
}

};
