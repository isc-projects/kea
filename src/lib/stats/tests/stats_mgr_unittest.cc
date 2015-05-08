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
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/shared_ptr.hpp>
#include <cc/data.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::stats;
using namespace boost::posix_time;

namespace {

class StatsMgrTest : public ::testing::Test {
public:
    StatsMgrTest() {
        StatsMgr::instance();
    }

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
                                                  static_cast<uint64_t>(1234)));

    ObservationPtr alpha;
    EXPECT_NO_THROW(alpha = StatsMgr::instance().getObservation("alpha"));
    EXPECT_TRUE(alpha);

    std::string exp = "\"alpha\": [ [ 1234, \""
        + Observation::ptimeToText(alpha->getInteger().second) + "\" ] ]";

    EXPECT_EQ(exp, StatsMgr::instance().get("alpha")->str());
}

// Test checks whether it's possible to record and later report
// a floating point statistic.
TEST_F(StatsMgrTest, floatStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("beta", 12.34));

    ObservationPtr beta;
    EXPECT_NO_THROW(beta = StatsMgr::instance().getObservation("beta"));
    EXPECT_TRUE(beta);

    std::string exp = "\"beta\": [ [ 12.34, \""
        + Observation::ptimeToText(beta->getFloat().second) + "\" ] ]";

    EXPECT_EQ(exp, StatsMgr::instance().get("beta")->str());
}

// Test checks whether it's possible to record and later report
// a duration statistic.
TEST_F(StatsMgrTest, durationStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("gamma",
                                                  microsec::time_duration(1,2,3,4)));

    ObservationPtr gamma;
    EXPECT_NO_THROW(gamma = StatsMgr::instance().getObservation("beta"));
    EXPECT_TRUE(gamma);

    std::string exp = "\"gamma\": [ [ \"01:02:03.000004\", \""
        + Observation::ptimeToText(gamma->getDuration().second) + "\" ] ]";

    EXPECT_EQ(exp, StatsMgr::instance().get("gamma")->str());
}

// Test checks whether it's possible to record and later report
// a string statistic.
TEST_F(StatsMgrTest, stringStat) {
    EXPECT_NO_THROW(StatsMgr::instance().setValue("delta",
                                                  "Lorem ipsum"));

    ObservationPtr delta;
    EXPECT_NO_THROW(delta = StatsMgr::instance().getObservation("delta"));
    EXPECT_TRUE(delta);

    std::string exp = "\"delta\": [ [ \"Lorem impsum\", \""
        + Observation::ptimeToText(delta->getString().second) + "\" ] ]";

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
    StatsMgr::instance().setValue("alpha", static_cast<uint64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem");

    // Now add some values to them
    StatsMgr::instance().addValue("alpha", static_cast<uint64_t>(5678));
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

    std::string exp_str_alpha = "\"alpha\": [ [ 1234, \""
        + Observation::ptimeToText(StatsMgr::instance().getObservation("alpha")
                                   ->getInteger().second) + "\" ] ]";
    std::string exp_str_beta = "\"beta\": [ [ 12.34, \""
        + Observation::ptimeToText(StatsMgr::instance().getObservation("beta")
                                   ->getFloat().second) + "\" ] ]";
    std::string exp_str_gamma = "\"gamma\": [ [ \"01:02:03.000004\", \""
        + Observation::ptimeToText(StatsMgr::instance().getObservation("gamma")
                                   ->getDuration().second) + "\" ] ]";
    std::string exp_str_delta = "\"delta\": [ [ \"Lorem impsum\", \""
        + Observation::ptimeToText(StatsMgr::instance().getObservation("delta")
                                   ->getString().second) + "\" ] ]";

    // Check that individual stats are reported properly
    EXPECT_EQ(exp_str_alpha, rep_alpha->str());
    EXPECT_EQ(exp_str_beta, rep_beta->str());
    EXPECT_EQ(exp_str_gamma, rep_gamma->str());
    EXPECT_EQ(exp_str_delta, rep_delta->str());

    // Check that non-existent metric is not reported.
    EXPECT_FALSE(StatsMgr::instance().get("epsilon"));

    // Check that all of them can be reported at once
    ConstElementPtr rep_all = StatsMgr::instance().getAll();
    ASSERT_TRUE(rep_all);

    // This may not be the best verification. There's no guarantee that the
    // statistics will be reported in this specific order.
    std::string exp_all = exp_str_alpha + ", " + exp_str_beta + ", "
        + exp_str_gamma + ", " + exp_str_delta;
    EXPECT_EQ(exp_all, rep_all->str());
}

// This test checks whether existing statistics can be reset.
TEST_F(StatsMgrTest, reset) {

    // Set a couple of statistics
    StatsMgr::instance().setValue("alpha", static_cast<uint64_t>(1234));
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
    StatsMgr::instance().setValue("alpha", static_cast<uint64_t>(1234));
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
    StatsMgr::instance().setValue("alpha", static_cast<uint64_t>(1234));
    StatsMgr::instance().setValue("beta", 12.34);
    StatsMgr::instance().setValue("gamma", time_duration(1,2,3,4));
    StatsMgr::instance().setValue("delta", "Lorem ipsum");

    // This should reset alpha to 0
    EXPECT_NO_THROW(StatsMgr::instance().removeAll());

    // Resetting all statistics should not remove them
    EXPECT_EQ(0, StatsMgr::instance().count());

    // There should be no such statistics anymore
    EXPECT_FALSE(StatsMgr::instance().get("alpha"));
    EXPECT_FALSE(StatsMgr::instance().get("beta"));
    EXPECT_FALSE(StatsMgr::instance().get("gamma"));
    EXPECT_FALSE(StatsMgr::instance().get("delta"));

    // There should be no such statistics anymore
    EXPECT_FALSE(StatsMgr::instance().getObservation("alpha"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("beta"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("gamma"));
    EXPECT_FALSE(StatsMgr::instance().getObservation("delta"));
}

};
