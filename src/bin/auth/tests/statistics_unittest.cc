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

TEST(StatisticsItemsTest, QRItemNamesCheck) {
    // check the number of elements in the array
    EXPECT_EQ(sizeof(QRCounterItemName) / sizeof(QRCounterItemName[0]),
              QR_COUNTER_TYPES);
    // check the name of the first enum element
    EXPECT_EQ(QRCounterItemName[QR_REQUEST_IPV4], "request.v4");
    // check the name of the last enum element
    EXPECT_EQ(QRCounterItemName[QR_RCODE_OTHER], "rcode.other");
}

TEST(StatisticsItemsTest, SocketItemNamesCheck) {
    // check the number of elements in the array
    EXPECT_EQ(sizeof(SocketCounterItemName) / sizeof(SocketCounterItemName[0]),
              SOCKET_COUNTER_TYPES);
    // check the name of the first enum element
    EXPECT_EQ(SocketCounterItemName[SOCKET_IPV4_UDP_BINDFAIL],
              "ipv4.udp.bindfail");
    // check the name of the last enum element
    EXPECT_EQ(SocketCounterItemName[SOCKET_UNIXDOMAIN_SENDERR],
              "unixdomain.senderr");
}

}
