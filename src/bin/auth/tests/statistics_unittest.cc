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

#include <config.h>

#include <string>

#include <gtest/gtest.h>

#include <boost/bind.hpp>

#include <dns/opcode.h>
#include <dns/rcode.h>

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

class AuthCountersTest : public ::testing::Test {
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
    AuthCountersTest() : counters() {
        counters.setStatisticsSession(&statistics_session_);
    }
    ~AuthCountersTest() {
    }
    MockSession statistics_session_;
    AuthCounters counters;
    // no need to be inherited from the original class here.
    class MockModuleSpec {
    public:
        bool validateStatistics(ConstElementPtr, const bool valid) const
            { return (valid); }
    };
    MockModuleSpec module_spec_;
};

void
AuthCountersTest::MockSession::establish(const char*) {}

void
AuthCountersTest::MockSession::disconnect() {}

void
AuthCountersTest::MockSession::subscribe(string, string)
{}

void
AuthCountersTest::MockSession::unsubscribe(string, string)
{}

void
AuthCountersTest::MockSession::startRead(boost::function<void()>)
{}

int
AuthCountersTest::MockSession::reply(ConstElementPtr, ConstElementPtr) {
    return (-1);
}

bool
AuthCountersTest::MockSession::hasQueuedMsgs() const {
    return (false);
}

int
AuthCountersTest::MockSession::group_sendmsg(ConstElementPtr msg,
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
AuthCountersTest::MockSession::group_recvmsg(ConstElementPtr&,
                                              ConstElementPtr& msg, bool, int)
{
    if (throw_session_timeout_) {
        isc_throw(SessionTimeout, "Session Timeout");
    }
    msg = msg_;
    return (true);
}

void
AuthCountersTest::MockSession::setThrowSessionError(bool flag) {
    throw_session_error_ = flag;
}

void
AuthCountersTest::MockSession::setThrowSessionTimeout(bool flag) {
    throw_session_timeout_ = flag;
}

TEST_F(AuthCountersTest, incrementUDPCounter) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_UDP_QUERY));
    EXPECT_NO_THROW(counters.inc(AuthCounters::SERVER_UDP_QUERY));
    // After increment, the counter should be 1.
    EXPECT_EQ(1, counters.getCounter(AuthCounters::SERVER_UDP_QUERY));
}

TEST_F(AuthCountersTest, incrementTCPCounter) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_TCP_QUERY));
    EXPECT_NO_THROW(counters.inc(AuthCounters::SERVER_TCP_QUERY));
    // After increment, the counter should be 1.
    EXPECT_EQ(1, counters.getCounter(AuthCounters::SERVER_TCP_QUERY));
}

TEST_F(AuthCountersTest, incrementInvalidCounter) {
    // Expect to throw an isc::OutOfRange
    EXPECT_THROW(counters.inc(AuthCounters::SERVER_COUNTER_TYPES),
                 isc::OutOfRange);
}

TEST_F(AuthCountersTest, incrementOpcodeCounter) {
    // The counter should be initialized to 0.  If we increment it by 1
    // the counter should be 1.
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(0, counters.getCounter(Opcode(i)));
        counters.inc(Opcode(i));
        EXPECT_EQ(1, counters.getCounter(Opcode(i)));
    }
}

TEST_F(AuthCountersTest, incrementRcodeCounter) {
    // The counter should be initialized to 0.  If we increment it by 1
    // the counter should be 1.
    for (int i = 0; i < 17; ++i) {
        EXPECT_EQ(0, counters.getCounter(Rcode(i)));
        counters.inc(Rcode(i));
        EXPECT_EQ(1, counters.getCounter(Rcode(i)));
    }
}

TEST_F(AuthCountersTest, submitStatisticsWithoutSession) {
    // Set statistics_session to NULL and call submitStatistics().
    // Expect to return false.
    counters.setStatisticsSession(NULL);
    EXPECT_FALSE(counters.submitStatistics());
}

TEST_F(AuthCountersTest, submitStatisticsWithException) {
    // Exception SessionError and SessionTimeout will be thrown
    // while sending statistics data.
    // Both expect to return false.
    statistics_session_.setThrowSessionError(true);
    EXPECT_FALSE(counters.submitStatistics());
    statistics_session_.setThrowSessionError(false);
    statistics_session_.setThrowSessionTimeout(true);
    EXPECT_FALSE(counters.submitStatistics());
    statistics_session_.setThrowSessionTimeout(false);
}

void
opcodeDataCheck(ConstElementPtr data, const int expected[16]) {
    const char* item_names[] = {
        "query", "iquery", "status", "reserved3", "notify", "update",
        "reserved6", "reserved7", "reserved8", "reserved9", "reserved10",
        "reserved11", "reserved12", "reserved13", "reserved14", "reserved15",
        NULL
    };
    int i;
    for (i = 0; i < 16; ++i) {
        ASSERT_NE(static_cast<const char*>(NULL), item_names[i]);
        const string item_name = "opcode." + string(item_names[i]);
        if (expected[i] == 0) {
            EXPECT_FALSE(data->get(item_name));
        } else {
            EXPECT_EQ(expected[i], data->get(item_name)->intValue());
        }
    }
    // We should have examined all names
    ASSERT_EQ(static_cast<const char*>(NULL), item_names[i]);
}

void
rcodeDataCheck(ConstElementPtr data, const int expected[17]) {
    const char* item_names[] = {
        "noerror", "formerr", "servfail", "nxdomain", "notimp", "refused",
        "yxdomain", "yxrrset", "nxrrset", "notauth", "notzone", "reserved11",
        "reserved12", "reserved13", "reserved14", "reserved15", "badvers",
        NULL
    };
    int i;
    for (i = 0; i < 17; ++i) {
        ASSERT_NE(static_cast<const char*>(NULL), item_names[i]);
        const string item_name = "rcode." + string(item_names[i]);
        if (expected[i] == 0) {
            EXPECT_FALSE(data->get(item_name));
        } else {
            EXPECT_EQ(expected[i], data->get(item_name)->intValue());
        }
    }
    // We should have examined all names
    ASSERT_EQ(static_cast<const char*>(NULL), item_names[i]);
}


TEST_F(AuthCountersTest, submitStatisticsWithoutValidator) {
    // Submit statistics data.
    // Validate if it submits correct data.

    // Counters should be initialized to 0.
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_UDP_QUERY));
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_TCP_QUERY));

    // UDP query counter is set to 2.
    counters.inc(AuthCounters::SERVER_UDP_QUERY);
    counters.inc(AuthCounters::SERVER_UDP_QUERY);
    // TCP query counter is set to 1.
    counters.inc(AuthCounters::SERVER_TCP_QUERY);
    counters.submitStatistics();

    // Destination is "Stats".
    EXPECT_EQ("Stats", statistics_session_.msg_destination);
    // Command is "set".
    EXPECT_EQ("set", statistics_session_.sent_msg->get("command")
                         ->get(0)->stringValue());
    EXPECT_EQ("Auth", statistics_session_.sent_msg->get("command")
                         ->get(1)->get("owner")->stringValue());
    ConstElementPtr statistics_data = statistics_session_.sent_msg
                                          ->get("command")->get(1)
                                          ->get("data");
    // UDP query counter is 2 and TCP query counter is 1.
    EXPECT_EQ(2, statistics_data->get("queries.udp")->intValue());
    EXPECT_EQ(1, statistics_data->get("queries.tcp")->intValue());

    // By default opcode counters are all 0 and omitted
    const int opcode_results[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0 };
    opcodeDataCheck(statistics_data, opcode_results);
    // By default rcode counters are all 0 and omitted
    const int rcode_results[17] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0 };
    rcodeDataCheck(statistics_data, rcode_results);
}

void
updateOpcodeCounters(AuthCounters &counters, const int expected[16]) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < expected[i]; ++j) {
            counters.inc(Opcode(i));
        }
    }
}

void
updateRcodeCounters(AuthCounters &counters, const int expected[17]) {
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < expected[i]; ++j) {
            counters.inc(Rcode(i));
        }
    }
}

TEST_F(AuthCountersTest, submitStatisticsWithOpcodeCounters) {
    // Increment some of the opcode counters.  Then they should appear in the
    // submitted data; others shouldn't
    const int opcode_results[16] = { 1, 2, 3, 0, 4, 5, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0 };
    updateOpcodeCounters(counters, opcode_results);
    counters.submitStatistics();
    ConstElementPtr statistics_data = statistics_session_.sent_msg
        ->get("command")->get(1)->get("data");
    opcodeDataCheck(statistics_data, opcode_results);
}

TEST_F(AuthCountersTest, submitStatisticsWithAllOpcodeCounters) {
    // Increment all opcode counters.  Then they should appear in the
    // submitted data.
    const int opcode_results[16] = { 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1 };
    updateOpcodeCounters(counters, opcode_results);
    counters.submitStatistics();
    ConstElementPtr statistics_data = statistics_session_.sent_msg
        ->get("command")->get(1)->get("data");
    opcodeDataCheck(statistics_data, opcode_results);
}

TEST_F(AuthCountersTest, submitStatisticsWithRcodeCounters) {
    // Increment some of the opcode counters.  Then they should appear in the
    // submitted data; others shouldn't
    const int rcode_results[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                    10, 0, 0, 0, 0, 0, 0, 11 };
    updateRcodeCounters(counters, rcode_results);
    counters.submitStatistics();
    ConstElementPtr statistics_data = statistics_session_.sent_msg
        ->get("command")->get(1)->get("data");
    rcodeDataCheck(statistics_data, rcode_results);
}

TEST_F(AuthCountersTest, submitStatisticsWithAllRcodeCounters) {
    // Increment all opcode counters.  Then they should appear in the
    // submitted data.
    const int rcode_results[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1 };
    updateOpcodeCounters(counters, rcode_results);
    counters.submitStatistics();
    ConstElementPtr statistics_data = statistics_session_.sent_msg
        ->get("command")->get(1)->get("data");
    opcodeDataCheck(statistics_data, rcode_results);
}

TEST_F(AuthCountersTest, submitStatisticsWithValidator) {

    //a validator for the unittest
    AuthCounters::validator_type validator;
    ConstElementPtr el;

    // Submit statistics data with correct statistics validator.
    validator = boost::bind(
        &AuthCountersTest::MockModuleSpec::validateStatistics,
        &module_spec_, _1, true);

    EXPECT_TRUE(validator(el));

    // register validator to AuthCounters
    counters.registerStatisticsValidator(validator);

    // Counters should be initialized to 0.
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_UDP_QUERY));
    EXPECT_EQ(0, counters.getCounter(AuthCounters::SERVER_TCP_QUERY));

    // UDP query counter is set to 2.
    counters.inc(AuthCounters::SERVER_UDP_QUERY);
    counters.inc(AuthCounters::SERVER_UDP_QUERY);
    // TCP query counter is set to 1.
    counters.inc(AuthCounters::SERVER_TCP_QUERY);

    // checks the value returned by submitStatistics
    EXPECT_TRUE(counters.submitStatistics());

    // Destination is "Stats".
    EXPECT_EQ("Stats", statistics_session_.msg_destination);
    // Command is "set".
    EXPECT_EQ("set", statistics_session_.sent_msg->get("command")
                         ->get(0)->stringValue());
    EXPECT_EQ("Auth", statistics_session_.sent_msg->get("command")
                         ->get(1)->get("owner")->stringValue());
    ConstElementPtr statistics_data = statistics_session_.sent_msg
                                          ->get("command")->get(1)
                                          ->get("data");
    // UDP query counter is 2 and TCP query counter is 1.
    EXPECT_EQ(2, statistics_data->get("queries.udp")->intValue());
    EXPECT_EQ(1, statistics_data->get("queries.tcp")->intValue());

    // Submit statistics data with incorrect statistics validator.
    validator = boost::bind(
        &AuthCountersTest::MockModuleSpec::validateStatistics,
        &module_spec_, _1, false);

    EXPECT_FALSE(validator(el));

    counters.registerStatisticsValidator(validator);

    // checks the value returned by submitStatistics
    EXPECT_FALSE(counters.submitStatistics());
}
}
