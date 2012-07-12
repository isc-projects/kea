// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <gtest/gtest.h>

#include "../stats_mgr.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

namespace {

typedef StatsMgr<dhcp::Pkt4> StatsMgr4;
typedef StatsMgr<dhcp::Pkt6> StatsMgr6;

const uint32_t common_transid = 123;

class StatsMgrTest : public ::testing::Test {
public:
    StatsMgrTest() {
    }

    Pkt4* createPacket4(const uint8_t msg_type,
                        const uint32_t transid) {
        Pkt4* pkt = new Pkt4(msg_type, transid);
        pkt->updateTimestamp();
        return pkt;
    }
};

TEST_F(StatsMgrTest, Constructor) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
}

TEST_F(StatsMgrTest, Exchanges) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    EXPECT_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet),
        BadValue
    );

    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);
    EXPECT_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_RA, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_RA, rcvd_packet),
        BadValue
    );

    EXPECT_NO_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
    );
    EXPECT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
}

TEST_F(StatsMgrTest, SendReceiveSimple) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);
    ASSERT_NO_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
    );
    EXPECT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
    EXPECT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
}

TEST_F(StatsMgrTest, SendReceiveUnordered) {
    const int packets_num = 10;
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);

    uint32_t transid[packets_num] = { 1, 1024, 2, 1025, 3, 1026, 4, 1027, 5, 1028 };
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                          transid[i]));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
        );
    }

    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPDISCOVER,
                                                          transid[packets_num - 1 - i]));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet);
        );
    }
    EXPECT_EQ(0, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
    EXPECT_EQ(10, stats_mgr->getUnorderedLookups(StatsMgr4::XCHG_DO));
    std::cout << stats_mgr->getAvgUnorderedLookupSetSize(StatsMgr4::XCHG_DO) << std::endl;
}

TEST_F(StatsMgrTest, Orphans) {
    const int packets_num = 6;
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);

    for (int i = 0; i < packets_num; i += 2) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER, i));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
        );
    }
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER, i));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet);
        );
    }
    EXPECT_EQ(packets_num / 2, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
}

}
