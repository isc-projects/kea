// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/stats_mgr.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <util/boost_time_utils.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::stats;
using namespace isc::config;
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
        StatsMgr::instance().removeAll();
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

    std::string exp = "{ \"alpha\": [ [ 1234, \"" +
        isc::util::ptimeToText(alpha->getInteger().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("alpha")->str());
}

// Test checks whether it's possible to record and later report
// a floating point statistic.
TEST_F(StatsMgrTest, floatStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("beta", 12.34));

    ObservationPtr beta;
    EXPECT_NO_THROW(beta = StatsMgr::instance().getObservation("beta"));
    ASSERT_TRUE(beta);

    std::string exp = "{ \"beta\": [ [ 12.34, \"" +
        isc::util::ptimeToText(beta->getFloat().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("beta")->str());
}

// Test checks whether it's possible to record and later report
// a duration statistic.
TEST_F(StatsMgrTest, durationStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("gamma",
                                                  microsec::time_duration(1, 2, 3, 4)));

    ObservationPtr gamma;
    EXPECT_NO_THROW(gamma = StatsMgr::instance().getObservation("gamma"));
    ASSERT_TRUE(gamma);

    std::string exp = "{ \"gamma\": [ [ \"01:02:03.000004\", \"" +
        isc::util::ptimeToText(gamma->getDuration().second) + "\" ] ] }";

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

    std::string exp = "{ \"delta\": [ [ \"Lorem ipsum\", \"" +
        isc::util::ptimeToText(delta->getString().second) + "\" ] ] }";

    EXPECT_EQ(exp, StatsMgr::instance().get("delta")->str());
}

// Basic test of getSize function.
TEST_F(StatsMgrTest, getSize) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", microsec::time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    EXPECT_NO_THROW(StatsMgr::instance().getSize("alpha"));
    EXPECT_NO_THROW(StatsMgr::instance().getSize("beta"));
    EXPECT_NO_THROW(StatsMgr::instance().getSize("gamma"));
    EXPECT_NO_THROW(StatsMgr::instance().getSize("delta"));

    EXPECT_EQ(StatsMgr::instance().getSize("alpha"), 1);
    EXPECT_EQ(StatsMgr::instance().getSize("beta"), 1);
    EXPECT_EQ(StatsMgr::instance().getSize("gamma"), 1);
    EXPECT_EQ(StatsMgr::instance().getSize("delta"), 1);
}

// Test checks whether setting age limit and count limit works properly.
TEST_F(StatsMgrTest, setLimits) {
    // Initializing of an integer type observation
    StatsMgr::instance().setValue("foo", static_cast<int64_t>(1));

    EXPECT_NO_THROW(StatsMgr::instance().setMaxSampleAge("foo",
                                                         time_duration(0, 0, 1, 0)));

    for (uint32_t i = 0; i < 10; ++i) {
        if (i == 5) {
            sleep(1); // wait one second to force exceeding the time limit
        }
        StatsMgr::instance().setValue("foo", static_cast<int64_t>(i));
    }

    EXPECT_EQ(StatsMgr::instance().getSize("foo"), 5);
    EXPECT_NO_THROW(StatsMgr::instance().setMaxSampleCount("foo", 100));

    for (int64_t i = 0; i < 200; ++i) {
        StatsMgr::instance().setValue("foo", i);
    }

    EXPECT_EQ(StatsMgr::instance().getSize("foo"), 100);
}

// Test checks whether setting age limit and count limit to existing
// statistics works properly.
TEST_F(StatsMgrTest, setLimitsAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // check the setting of time limit to existing statistics
    EXPECT_NO_THROW(StatsMgr::instance().setMaxSampleAgeAll(time_duration(0, 0, 1, 0)));

    // check if time limit was set properly and whether count limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().second,
              time_duration(0, 0, 1, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().second,
              time_duration(0, 0, 1, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().second,
              time_duration(0, 0, 1, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().second,
              time_duration(0, 0, 1, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().first, false);

    // check the setting of count limit to existing statistics
    EXPECT_NO_THROW(StatsMgr::instance().setMaxSampleCountAll(1200));

    // check if count limit was set properly and whether count limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().second, 1200);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().second, 1200);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().second, 1200);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().second, 1200);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().first, false);
}

// This test checks whether a single (get("foo")) and all (getAll())
// statistics are reported properly.
TEST_F(StatsMgrTest, getGetAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem");

    // The string's representation of firstly added statistics
    std::string alpha_first = ", [ 1234, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ] ]";
    std::string beta_first = ", [ 12.34, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ] ]";
    std::string gamma_first = ", [ \"01:02:03.000004\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ] ]";
    std::string delta_first = ", [ \"Lorem\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ] ]";

    // Now add some values to them
    StatsMgr::instance().addValue("alpha", static_cast<int64_t>(5678));
    StatsMgr::instance().addValue("beta", 56.78);
    StatsMgr::instance().addValue("gamma", time_duration(5, 6, 7, 8));
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

    std::string exp_str_alpha = "[ [ 6912, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ]" + alpha_first;
    std::string exp_str_beta = "[ [ 69.12, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ]" + beta_first;
    std::string exp_str_gamma = "[ [ \"06:08:10.000012\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ]" + gamma_first;
    std::string exp_str_delta = "[ [ \"Lorem ipsum\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ]" + delta_first;

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
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().reset("alpha"));
    EXPECT_EQ(0,
              StatsMgr::instance().getObservation("alpha")->getInteger().first);

    // The other stats should remain untouched
    EXPECT_EQ(12.34,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(1, 2, 3, 4),
              StatsMgr::instance().getObservation("gamma")->getDuration().first);
    EXPECT_EQ("Lorem ipsum",
              StatsMgr::instance().getObservation("delta")->getString().first);

    // Now let's wipe them, too.
    EXPECT_NO_THROW(StatsMgr::instance().reset("beta"));
    EXPECT_NO_THROW(StatsMgr::instance().reset("gamma"));
    EXPECT_NO_THROW(StatsMgr::instance().reset("delta"));
    EXPECT_EQ(0.0,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(0, 0, 0, 0),
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
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().resetAll());
    EXPECT_EQ(0,
              StatsMgr::instance().getObservation("alpha")->getInteger().first);
    EXPECT_EQ(0.0,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(0, 0, 0, 0),
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
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
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
        StatsMgr::instance().addValue("metric1", 0.1 * i);
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
        StatsMgr::instance().setValue("metric1", 0.1 * i);
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

// Test checks if statistic-get handler is able to return specified statistic.
TEST_F(StatsMgrTest, commandStatisticGet) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));

    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));

    ConstElementPtr rsp = StatsMgr::instance().statisticGetHandler("statistic-get",
                                                                   params);

    ObservationPtr alpha;
    EXPECT_NO_THROW(alpha = StatsMgr::instance().getObservation("alpha"));
    ASSERT_TRUE(alpha);

    std::string exp = "{ \"alpha\": [ [ 1234, \"" +
        isc::util::ptimeToText(alpha->getInteger().second) + "\" ] ] }";

    EXPECT_EQ("{ \"arguments\": " + exp + ", \"result\": 0 }", rsp->str());
}

// Test checks if statistic-get is able to handle:
// - a request without parameters
// - a request with missing statistic name
// - a request for non-existing statistic.
TEST_F(StatsMgrTest, commandStatisticGetNegative) {
    // Case 1: a request without parameters
    ConstElementPtr rsp = StatsMgr::instance().statisticGetHandler("statistic-get",
                                                                   ElementPtr());
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 2: a request with missing statistic name
    ElementPtr params = Element::createMap();
    rsp = StatsMgr::instance().statisticGetHandler("statistic-get", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 3: a request for non-existing statistic
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticGetHandler("statistic-get", params);
    EXPECT_EQ("{ \"arguments\": {  }, \"result\": 0 }", rsp->str());
}

// This test checks whether statistic-get-all command returns all statistics
// correctly.
TEST_F(StatsMgrTest, commandGetAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // Now get them. They're used to generate expected output
    ConstElementPtr rep_alpha = StatsMgr::instance().get("alpha");
    ConstElementPtr rep_beta = StatsMgr::instance().get("beta");
    ConstElementPtr rep_gamma = StatsMgr::instance().get("gamma");
    ConstElementPtr rep_delta = StatsMgr::instance().get("delta");

    ASSERT_TRUE(rep_alpha);
    ASSERT_TRUE(rep_beta);
    ASSERT_TRUE(rep_gamma);
    ASSERT_TRUE(rep_delta);

    std::string exp_str_alpha = "[ [ 1234, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ] ]";
    std::string exp_str_beta = "[ [ 12.34, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ] ]";
    std::string exp_str_gamma = "[ [ \"01:02:03.000004\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ] ]";
    std::string exp_str_delta = "[ [ \"Lorem ipsum\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ] ]";

    // Check that all of them can be reported at once
    ConstElementPtr rsp = StatsMgr::instance().statisticGetAllHandler(
        "statistic-get-all", ElementPtr());
    ASSERT_TRUE(rsp);
    int status_code;
    ConstElementPtr rep_all = parseAnswer(status_code, rsp);
    ASSERT_EQ(0, status_code);
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

// Test checks if statistic-reset handler is able to reset specified statistic.
TEST_F(StatsMgrTest, commandStatisticReset) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));

    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));

    ConstElementPtr rsp =
        StatsMgr::instance().statisticResetHandler("statistic-reset", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    ObservationPtr alpha;
    EXPECT_NO_THROW(alpha = StatsMgr::instance().getObservation("alpha"));
    ASSERT_TRUE(alpha);

    // Check that it was indeed reset
    EXPECT_EQ(0, alpha->getInteger().first);
}

// Test checks if statistic-reset is able to handle:
// - a request without parameters
// - a request with missing statistic name
// - a request for non-existing statistic.
TEST_F(StatsMgrTest, commandStatisticResetNegative) {
    // Case 1: a request without parameters
    ConstElementPtr rsp =
        StatsMgr::instance().statisticResetHandler("statistic-reset", ElementPtr());
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 2: a request with missing statistic name
    ElementPtr params = Element::createMap();
    rsp = StatsMgr::instance().statisticResetHandler("statistic-reset", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 3: a request for non-existing statistic
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticResetHandler("statistic-reset", params);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'alpha' statistic found\" }",
              rsp->str());
}

// This test checks whether statistic-reset-all command really resets all
// statistics correctly.
TEST_F(StatsMgrTest, commandResetAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // Now get them. They're used to generate expected output
    ConstElementPtr rep_alpha = StatsMgr::instance().get("alpha");
    ConstElementPtr rep_beta = StatsMgr::instance().get("beta");
    ConstElementPtr rep_gamma = StatsMgr::instance().get("gamma");
    ConstElementPtr rep_delta = StatsMgr::instance().get("delta");

    ASSERT_TRUE(rep_alpha);
    ASSERT_TRUE(rep_beta);
    ASSERT_TRUE(rep_gamma);
    ASSERT_TRUE(rep_delta);

    std::string exp_str_alpha = "[ [ 1234, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ] ]";
    std::string exp_str_beta = "[ [ 12.34, \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ] ]";
    std::string exp_str_gamma = "[ [ \"01:02:03.000004\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ] ]";
    std::string exp_str_delta = "[ [ \"Lorem ipsum\", \"" +
        isc::util::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ] ]";

    // Check that all of them can be reset at once
    ConstElementPtr rsp = StatsMgr::instance().statisticResetAllHandler(
        "statistic-reset-all", ElementPtr());
    ASSERT_TRUE(rsp);
    int status_code;
    ConstElementPtr rep_all = parseAnswer(status_code, rsp);
    ASSERT_EQ(0, status_code);
    ASSERT_TRUE(rep_all);

    // Check that they're indeed reset
    EXPECT_EQ(0,
              StatsMgr::instance().getObservation("alpha")->getInteger().first);
    EXPECT_EQ(0.0f,
              StatsMgr::instance().getObservation("beta")->getFloat().first);
    EXPECT_EQ(time_duration(0, 0, 0, 0),
              StatsMgr::instance().getObservation("gamma")->getDuration().first);
    EXPECT_EQ("",
              StatsMgr::instance().getObservation("delta")->getString().first);
}

// Test checks if statistic-remove handler is able to remove a statistic.
TEST_F(StatsMgrTest, commandStatisticRemove) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));

    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));

    ConstElementPtr rsp =
        StatsMgr::instance().statisticRemoveHandler("statistic-remove", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    // It should be gone.
    EXPECT_FALSE(StatsMgr::instance().getObservation("alpha"));
    EXPECT_EQ(0, StatsMgr::instance().count());
}

// Test checks if statistic-remove is able to handle:
// - a request without parameters
// - a request with missing statistic name
// - a request for non-existing statistic.
TEST_F(StatsMgrTest, commandStatisticRemoveNegative) {
    // Case 1: a request without parameters
    ConstElementPtr rsp =
        StatsMgr::instance().statisticRemoveHandler("statistic-remove", ElementPtr());
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 2: a request with missing statistic name
    ElementPtr params = Element::createMap();
    rsp = StatsMgr::instance().statisticRemoveHandler("statistic-remove", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 3: a request for non-existing statistic
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticRemoveHandler("statistic-remove", params);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'alpha' statistic found\" }",
              rsp->str());
}

// This test checks whether statistic-remove-all command really resets all
// statistics correctly.
TEST_F(StatsMgrTest, commandRemoveAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // Check that all of them can be reset at once
    ConstElementPtr rsp = StatsMgr::instance().statisticRemoveAllHandler(
        "statistic-remove-all", ElementPtr());
    ASSERT_TRUE(rsp);
    int status_code;
    ConstElementPtr rep_all = parseAnswer(status_code, rsp);
    ASSERT_EQ(0, status_code);

    EXPECT_FALSE(StatsMgr::instance().getObservation("alpha"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("beta"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("gamma"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("delta"));
    EXPECT_EQ(0, StatsMgr::instance().count());
}

// This test checks whether statistic-sample-age-set command really set
// max_sample_age_ limit correctly.
TEST_F(StatsMgrTest, commandSetMaxSampleAge) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));

    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));
    params->set("duration", Element::create(1245)); // time_duration(0, 20, 45, 0)

    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleAgeHandler("statistic-sample-age-set", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    // check if time limit was set properly and whether count limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().second,
              time_duration(0, 20, 45, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, false);
}

// Test checks if statistic-sample-age-set is able to handle:
// - a request without parameters
// - a request without duration parameter
// - a request with missing statistic name
// - a request for non-existing statistic.
TEST_F(StatsMgrTest, commandSetMaxSampleAgeNegative) {
    // Case 1: a request without parameters
    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleAgeHandler("statistic-sample-age-set", ElementPtr());
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 2: a request without duration parameter
    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticSetMaxSampleAgeHandler("statistic-sample-age-set", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 3: a request with missing statistic name
    params = Element::createMap();
    params->set("duration", Element::create(100));
    rsp = StatsMgr::instance().statisticSetMaxSampleAgeHandler("statistic-sample-age-set", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 4: a request for non-existing statistic
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticSetMaxSampleAgeHandler("statistic-sample-age-set", params);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'alpha' statistic found\" }",
              rsp->str());
}

TEST_F(StatsMgrTest, commandSetMaxSampleAgeAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    ElementPtr params = Element::createMap();
    params->set("duration", Element::create(3765)); // time_duration(1, 2, 45, 0)

    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleAgeAllHandler("statistic-sample-age-set-all", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    // check if time limit was set properly and whether count limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().second,
              time_duration(1, 2, 45, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().second,
              time_duration(1, 2, 45, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().second,
              time_duration(1, 2, 45, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().second,
              time_duration(1, 2, 45, 0));
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().first, false);
}

// This test checks whether statistic-sample-count-set command really set
// max_sample_count_ limit correctly.
TEST_F(StatsMgrTest, commandSetMaxSampleCount) {
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));

    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));
    params->set("max-samples", Element::create(15));

    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleCountHandler("statistic-sample-count-set", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    // check if time limit was set properly and whether duration limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().second, 15);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, false);
}

// Test checks if statistic-sample-count-set is able to handle:
// - a request without parameters
// - a request without max-samples parameter
// - a request with missing statistic name
// - a request for non-existing statistic.
TEST_F(StatsMgrTest, commandSetMaxSampleCountNegative) {
    // Case 1: a request without parameters
    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleCountHandler("statistic-sample-count-set", ElementPtr());
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 2: a request without max-samples parameter
    ElementPtr params = Element::createMap();
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticSetMaxSampleCountHandler("statistic-sample-count-set", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 3: a request with missing statistic name
    params = Element::createMap();
    params->set("max-samples", Element::create(10));
    rsp = StatsMgr::instance().statisticSetMaxSampleCountHandler("statistic-sample-count-set", params);
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(status_code, CONTROL_RESULT_ERROR);

    // Case 4: a request for non-existing statistic
    params->set("name", Element::create("alpha"));
    rsp = StatsMgr::instance().statisticSetMaxSampleCountHandler("statistic-sample-count-set", params);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'alpha' statistic found\" }",
              rsp->str());
}

TEST_F(StatsMgrTest, commandSetMaxSampleCountAll) {
    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<int64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1, 2, 3, 4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    ElementPtr params = Element::createMap();
    params->set("max-samples", Element::create(200));

    ConstElementPtr rsp =
        StatsMgr::instance().statisticSetMaxSampleCountAllHandler("statistic-sample-count-set-all", params);
    int status_code;
    ASSERT_NO_THROW(parseAnswer(status_code, rsp));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);

    // check if count limit was set properly and whether count limit is disabled
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleCount().second, 200);
    EXPECT_EQ(StatsMgr::instance().getObservation("alpha")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleCount().second, 200);
    EXPECT_EQ(StatsMgr::instance().getObservation("beta")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleCount().second, 200);
    EXPECT_EQ(StatsMgr::instance().getObservation("gamma")->getMaxSampleAge().first, false);

    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().first, true);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleCount().second, 200);
    EXPECT_EQ(StatsMgr::instance().getObservation("delta")->getMaxSampleAge().first, false);
}

};
