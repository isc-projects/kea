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
#include <auth/statistics_items.h>

#include <dns/tests/unittest_util.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using isc::auth::statistics::Counters;
using isc::auth::statistics::QRAttributes;

namespace {

class CountersTest : public ::testing::Test {
protected:
    CountersTest() : counters() {}
    ~CountersTest() {}
    Counters counters;
};

bool
checkCountersAllZeroExcept(const isc::data::ConstElementPtr counters,
                           const std::set<std::string>& except_for) {
    std::map<std::string, ConstElementPtr> stats_map = counters->mapValue();

    for (std::map<std::string, ConstElementPtr>::const_iterator
            i = stats_map.begin(), e = stats_map.end();
            i != e;
            ++i)
    {
        int expect = 0;
        if (except_for.count(i->first) != 0) {
            expect = 1;
        }
        EXPECT_EQ(expect, i->second->intValue()) << "Expected counter "
            << i->first << " = " << expect << ", actual: "
            << i->second->intValue();
    }

    return false;
}

TEST_F(CountersTest, incrementNormalQuery) {
    Message response(Message::RENDER);
    QRAttributes qrattrs;
    std::set<std::string> expect_nonzero;

    expect_nonzero.clear();
    checkCountersAllZeroExcept(counters.getStatistics(), expect_nonzero);

    qrattrs.setQueryIPVersion(AF_INET6);
    qrattrs.setQueryTransportProtocol(IPPROTO_UDP);
    qrattrs.setQueryOpCode(Opcode::QUERY_CODE);
    qrattrs.setQueryEDNS(true, false);
    qrattrs.setQueryDO(true);
    qrattrs.answerWasSent();

    response.setRcode(Rcode::REFUSED());
    response.addQuestion(Question(Name("example.com"),
                                  RRClass::IN(), RRType::AAAA()));

    counters.inc(qrattrs, response);

    expect_nonzero.clear();
    expect_nonzero.insert("opcode.query");
    expect_nonzero.insert("queries.udp");
    expect_nonzero.insert("rcode.refused");
    checkCountersAllZeroExcept(counters.getStatistics(), expect_nonzero);
}

TEST_F(CountersTest, getStatistics) {
    std::map<std::string, ConstElementPtr> stats_map =
        counters.getStatistics()->mapValue();
    for (std::map<std::string, ConstElementPtr>::const_iterator
            i = stats_map.begin(), e = stats_map.end();
            i != e;
            ++i)
    {
        // item type check
        EXPECT_NO_THROW(i->second->intValue())
            << "Item " << i->first << " is not IntElement";
    }
}

TEST_F(AuthCountersTest, getStatisticsWithOpcodeCounters) {
    // Increment some of the opcode counters.  Then they should appear in the
    // submitted data; others shouldn't
    const int opcode_results[16] = { 1, 2, 3, 0, 4, 5, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0 };
    updateOpcodeCounters(counters, opcode_results);
    ConstElementPtr statistics_data = counters.getStatistics();
    opcodeDataCheck(statistics_data, opcode_results);
}

TEST_F(AuthCountersTest, getStatisticsWithAllOpcodeCounters) {
    // Increment all opcode counters.  Then they should appear in the
    // submitted data.
    const int opcode_results[16] = { 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1 };
    updateOpcodeCounters(counters, opcode_results);
    ConstElementPtr statistics_data = counters.getStatistics();
    opcodeDataCheck(statistics_data, opcode_results);
}

TEST_F(AuthCountersTest, getStatisticsWithRcodeCounters) {
    // Increment some of the rcode counters.  Then they should appear in the
    // submitted data; others shouldn't
    const int rcode_results[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                    10, 0, 0, 0, 0, 0, 0, 11 };
    updateRcodeCounters(counters, rcode_results);
    ConstElementPtr statistics_data = counters.getStatistics();
    rcodeDataCheck(statistics_data, rcode_results);
}

TEST_F(AuthCountersTest, getStatisticsWithAllRcodeCounters) {
    // Increment all rcode counters.  Then they should appear in the
    // submitted data.
    const int rcode_results[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 1, 1, 1, 1, 1, 1, 1 };
    updateOpcodeCounters(counters, rcode_results);
    ConstElementPtr statistics_data = counters.getStatistics();
    opcodeDataCheck(statistics_data, rcode_results);
}

TEST_F(AuthCountersTest, getStatisticsWithValidator) {

    //a validator for the unittest
    AuthCounters::validator_type validator;
    ConstElementPtr el;

    // Get statistics data with correct statistics validator.
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

    // checks the value returned by getStatistics
    ConstElementPtr statistics_data = counters.getStatistics();

    // UDP query counter is 2 and TCP query counter is 1.
    EXPECT_EQ(2, statistics_data->get("queries.udp")->intValue());
    EXPECT_EQ(1, statistics_data->get("queries.tcp")->intValue());

    // Get statistics data with incorrect statistics validator.
    validator = boost::bind(
        &AuthCountersTest::MockModuleSpec::validateStatistics,
        &module_spec_, _1, false);

    EXPECT_FALSE(validator(el));

    counters.registerStatisticsValidator(validator);

    // checks the value returned by getStatistics
    EXPECT_FALSE(counters.getStatistics());
}

int
countTreeElements(const struct CounterTypeTree* tree) {
    int count = 0;
    for (int i = 0; tree[i].name != NULL; ++i) {
        if (tree[i].sub_tree == NULL) {
            ++count;
        } else {
            count += countTreeElements(tree[i].sub_tree);
        }
    }
    return count;
}

TEST(StatisticsItemsTest, QRItemNamesCheck) {
    EXPECT_EQ(QR_COUNTER_TYPES, countTreeElements(QRCounterTree));
}

}
