// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <config.h>

#include <gtest/gtest.h>

#include <cc/data.h>
#include <cc/session.h>

#include <auth/statistics.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;

namespace {

class QueryCountersTest : public ::testing::Test {
private:
    class MockSession : public AbstractSession {
    public:
        MockSession() :
            // by default we return a simple "success" message.
            msg_(Element::fromJSON("{\"result\": [0, \"SUCCESS\"]}")),
            throw_session_error_(false), throw_session_timeout_(false)
        {}
        virtual void establish(const char* socket_file);
        virtual void disconnect();
        virtual int group_sendmsg(ConstElementPtr msg, string group,
                                  string instance, string to);
        virtual bool group_recvmsg(ConstElementPtr& envelope,
                                   ConstElementPtr& msg,
                                   bool nonblock, int seq);
        virtual void subscribe(string group, string instance);
        virtual void unsubscribe(string group, string instance);
        virtual void startRead(boost::function<void()> read_callback);
        virtual int reply(ConstElementPtr envelope, ConstElementPtr newmsg);
        virtual bool hasQueuedMsgs() const;
        virtual void setTimeout(size_t) {}
        virtual size_t getTimeout() const { return (0); };

        void setThrowSessionError(bool flag);
        void setThrowSessionTimeout(bool flag);

        void setMessage(ConstElementPtr msg) { msg_ = msg; }

        ConstElementPtr sent_msg;
        string msg_destination;
    private:
        ConstElementPtr msg_;
        bool throw_session_error_;
        bool throw_session_timeout_;
    };

protected:
    QueryCountersTest() : counters(verbose_mode_) {
        counters.setStatsSession(&stats_session_);
    }
    ~QueryCountersTest() {
    }
    MockSession stats_session_;
    QueryCounters counters;
    bool verbose_mode_;
};

void
QueryCountersTest::MockSession::establish(const char*) {}

void
QueryCountersTest::MockSession::disconnect() {}

void
QueryCountersTest::MockSession::subscribe(string, string)
{}

void
QueryCountersTest::MockSession::unsubscribe(string, string)
{}

void
QueryCountersTest::MockSession::startRead(boost::function<void()>)
{}

int
QueryCountersTest::MockSession::reply(ConstElementPtr, ConstElementPtr) {
    return (-1);
}

bool
QueryCountersTest::MockSession::hasQueuedMsgs() const {
    return (false);
}

int
QueryCountersTest::MockSession::group_sendmsg(ConstElementPtr msg,
                                              string group, string, string)
{
    if (throw_session_error_) {
        isc_throw(SessionError, "Session Error");
    }
    sent_msg = msg;
    msg_destination = group;
    return (0);
}

bool
QueryCountersTest::MockSession::group_recvmsg(ConstElementPtr&,
                                              ConstElementPtr& msg, bool, int)
{
    if (throw_session_timeout_) {
        isc_throw(SessionTimeout, "Session Timeout");
    }
    msg = msg_;
    return (true);
}

void
QueryCountersTest::MockSession::setThrowSessionError(bool flag) {
    throw_session_error_ = flag;
}

void
QueryCountersTest::MockSession::setThrowSessionTimeout(bool flag) {
    throw_session_timeout_ = flag;
}

TEST_F(QueryCountersTest, incrementUDPCounter) {
    EXPECT_NO_THROW(counters.inc(QueryCounters::COUNTER_UDP));
}

TEST_F(QueryCountersTest, incrementTCPCounter) {
    EXPECT_NO_THROW(counters.inc(QueryCounters::COUNTER_TCP));
}

TEST_F(QueryCountersTest, incrementInvalidCounter) {
    EXPECT_THROW(counters.inc(QueryCounters::COUNTER_TYPES),
                 isc::InvalidParameter);
}

TEST_F(QueryCountersTest, submitStatisticsWithoutSession) {
    // Set stats_session to NULL and call submitStatistics().
    // Expect to return false.
    counters.setStatsSession(NULL);
    EXPECT_FALSE(counters.submitStatistics());
}

TEST_F(QueryCountersTest, submitStatisticsWithException) {
    // Exception SessionError and SessionTimeout will be thrown
    // while sending statistics data.
    // Both expect to return false.
    stats_session_.setThrowSessionError(true);
    EXPECT_FALSE(counters.submitStatistics());
    stats_session_.setThrowSessionError(false);
    stats_session_.setThrowSessionTimeout(true);
    EXPECT_FALSE(counters.submitStatistics());
    stats_session_.setThrowSessionTimeout(false);
}

TEST_F(QueryCountersTest, submitStatistics) {
    // Submit statistics data.
    // Validate if it submits correct data.

    // UDP query counter is set to 2.
    counters.inc(QueryCounters::COUNTER_UDP);
    counters.inc(QueryCounters::COUNTER_UDP);
    // TCP query counter is set to 1.
    counters.inc(QueryCounters::COUNTER_TCP);
    counters.submitStatistics();

    // Destination is "Stats".
    EXPECT_EQ("Stats", stats_session_.msg_destination);
    // Command is "set".
    EXPECT_EQ("set", stats_session_.sent_msg->get("command")
                         ->get(0)->stringValue());
    ConstElementPtr stats_data = stats_session_.sent_msg ->get("command")
                                     ->get(1)->get("stats_data");
    // UDP query counter is 2 and TCP query counter is 1.
    EXPECT_EQ(2, stats_data->get("auth.queries.udp")->intValue());
    EXPECT_EQ(1, stats_data->get("auth.queries.tcp")->intValue());
}

}
