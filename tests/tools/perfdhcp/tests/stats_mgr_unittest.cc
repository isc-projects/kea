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
#include <dhcp/dhcp6.h>
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
        // Packet timestamp is normally updated by interface
        // manager on packets reception or send. Unit tests
        // do not use interface manager so we need to do it
        // ourselfs.
        pkt->updateTimestamp();
        return pkt;
    }

    Pkt6* createPacket6(const uint8_t msg_type,
                        const uint32_t transid) {
        Pkt6* pkt = new Pkt6(msg_type, transid);
        // Packet timestamp is normally updated by interface
        // manager on packets reception or send. Unit tests
        // do not use interface manager so we need to do it
        // ourselfs.
        pkt->updateTimestamp();
        return pkt;
    }

    void passMultiplePackets6(const boost::shared_ptr<StatsMgr6> stats_mgr,
                              const StatsMgr6::ExchangeType xchg_type,
                              const uint8_t packet_type,
                              const int num_packets,
                              const bool receive = false) {
        for (int i = 0; i < num_packets; ++i) {
            boost::shared_ptr<Pkt6>
                packet(createPacket6(packet_type, i));

            if (receive) {
                ASSERT_NO_THROW(
                    stats_mgr->passRcvdPacket(xchg_type, packet);
                );
            } else {
                ASSERT_NO_THROW(
                    stats_mgr->passSentPacket(xchg_type, packet)
                );
            }
        }
    }

};

TEST_F(StatsMgrTest, Constructor) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);
    EXPECT_EQ(
        std::numeric_limits<double>::max(),
        stats_mgr->getMinDelay(StatsMgr4::XCHG_DO)
    );
    EXPECT_EQ(0, stats_mgr->getMaxDelay(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getSumDelay(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getSquareSumDelay(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getOrderedLookups(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getUnorderedLookups(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getSentPacketsNum(StatsMgr4::XCHG_DO));
    EXPECT_EQ(0, stats_mgr->getRcvdPacketsNum(StatsMgr4::XCHG_DO));

    double avg_size = 0.;
    ASSERT_NO_THROW(
        avg_size = stats_mgr->getAvgUnorderedLookupSetSize(StatsMgr4::XCHG_DO);
    );
    EXPECT_EQ(0., avg_size);
}

TEST_F(StatsMgrTest, Exchange) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    // This is expected to throw because XCHG_DO was not yet
    // added to Stats Manager for tracking.
    EXPECT_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet),
        BadValue
    );

    // Adding DISCOVER-OFFER exchanges to be tracked by Stats Manager.
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);
    // The following two attempts are expected to throw because
    // invalid exchange types are passed (XCHG_RA instead of XCHG_DO)
    EXPECT_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_RA, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_RA, rcvd_packet),
        BadValue
    );

    // The following two attempts are expected to run fine because
    // right exchange type is specified.
    EXPECT_NO_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
    );
    EXPECT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
}

TEST_F(StatsMgrTest, MultipleExchanges) {
    boost::shared_ptr<StatsMgr6> stats_mgr(new StatsMgr6());
    stats_mgr->addExchangeStats(StatsMgr6::XCHG_SA);
    stats_mgr->addExchangeStats(StatsMgr6::XCHG_RR);

    // Simulate sending number of solicit packets.
    const int solicit_packets_num = 10;
    passMultiplePackets6(stats_mgr, StatsMgr6::XCHG_SA, DHCPV6_SOLICIT,
                         solicit_packets_num);

    // Simulate sending number of request packets. It is important that
    // number of request packets is different then number of solicit
    // packets. We can now check if right number packets went to
    // the right exchange type group.
    const int request_packets_num = 5;
    passMultiplePackets6(stats_mgr, StatsMgr6::XCHG_RR, DHCPV6_REQUEST,
                         request_packets_num);

    // Check if all packets are successfuly passed to packet lists.
    EXPECT_EQ(solicit_packets_num,
              stats_mgr->getSentPacketsNum(StatsMgr6::XCHG_SA));
    EXPECT_EQ(request_packets_num,
              stats_mgr->getSentPacketsNum(StatsMgr6::XCHG_RR));

    // Simulate reception of multiple packets for both SOLICIT-ADVERTISE
    // and REQUEST-REPLY exchanges. Assume no packet drops.
    const bool receive_packets = true;
    passMultiplePackets6(stats_mgr, StatsMgr6::XCHG_SA, DHCPV6_ADVERTISE,
                         solicit_packets_num, receive_packets);

    passMultiplePackets6(stats_mgr, StatsMgr6::XCHG_RR, DHCPV6_REPLY,
                         request_packets_num, receive_packets);

    // Verify that all received packets are counted.
    EXPECT_EQ(solicit_packets_num,
              stats_mgr->getRcvdPacketsNum(StatsMgr6::XCHG_SA));
    EXPECT_EQ(request_packets_num,
              stats_mgr->getRcvdPacketsNum(StatsMgr6::XCHG_RR));
}

TEST_F(StatsMgrTest, SendReceiveSimple) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);
    // The following attempt is expected to pass becase the right
    // exchange type is used.
    ASSERT_NO_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
    );
    // It is ok, to pass to received packets here. First one will
    // be matched with sent packet. The latter one will not be
    // matched with sent packet but orphans counter will simply
    // increase.
    ASSERT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
    ASSERT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet)
    );
    EXPECT_EQ(1, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
}

TEST_F(StatsMgrTest, SendReceiveUnordered) {
    const int packets_num = 10;
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);

    // Transaction ids of 10 packets to be sent and received.
    uint32_t transid[packets_num] =
        { 1, 1024, 2, 1025, 3, 1026, 4, 1027, 5, 1028 };
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                          transid[i]));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
        );
    }

    // We are simulating that received packets are coming in reverse order:
    // 1028, 5, 1027 ....
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4>
            rcvd_packet(createPacket4(DHCPDISCOVER,
                                      transid[packets_num - 1 - i]));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet);
        );
    }
    // All packets are expected to match (we did not drop any)
    EXPECT_EQ(0, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
    // Most of the time we have to do unordered lookups except for the last
    // one. Packets are removed from the sent list every time we have a match
    // so eventually we come up with the single packet that caching iterator
    // is pointing to. This is counted as ordered lookup.
    EXPECT_EQ(1, stats_mgr->getOrderedLookups(StatsMgr4::XCHG_DO));
    EXPECT_EQ(9, stats_mgr->getUnorderedLookups(StatsMgr4::XCHG_DO));
}

TEST_F(StatsMgrTest, Orphans) {
    const int packets_num = 6;
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);

    // We skip every second packet to simulate drops.
    for (int i = 0; i < packets_num; i += 2) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER, i));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
        );
    }
    // We pass all received packets.
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER, i));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet);
        );
    }
    // The half of received packets are expected not to have matching
    // sent packet.
    EXPECT_EQ(packets_num / 2, stats_mgr->getOrphans(StatsMgr4::XCHG_DO));
}

TEST_F(StatsMgrTest, Delays) {
    boost::scoped_ptr<StatsMgr4> stats_mgr(new StatsMgr4());
    stats_mgr->addExchangeStats(StatsMgr4::XCHG_DO);

    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    ASSERT_NO_THROW(
        stats_mgr->passSentPacket(StatsMgr4::XCHG_DO, sent_packet)
    );

    // There is way to differentiate timstamps of two packets other than
    // sleep for before we create another packet. Packet is using current
    // time to update its timestamp.
    // Sleeping for two seconds will guarantee that delay between packets
    // will be greater than 1 second. Note that posix time value is
    // transformed to double value and it makes it hard to determine
    // actual value to expect.
    std::cout << "Sleeping for 2 seconds to test packet delays" << std::endl;
    sleep(2);

    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    ASSERT_NO_THROW(
        stats_mgr->passRcvdPacket(StatsMgr4::XCHG_DO, rcvd_packet);
    );

    // Calculate period between packets.
    boost::posix_time::ptime sent_time = sent_packet->getTimestamp();
    boost::posix_time::ptime rcvd_time = rcvd_packet->getTimestamp();

    ASSERT_FALSE(sent_time.is_not_a_date_time());
    ASSERT_FALSE(rcvd_time.is_not_a_date_time());

    boost::posix_time::time_period period(sent_time, rcvd_time);

    // Initially min delay is equal to MAX_DOUBLE. After first packets
    // are passed, it is expected to set to actual value.
    EXPECT_LT(stats_mgr->getMinDelay(StatsMgr4::XCHG_DO),
              std::numeric_limits<double>::max());
    EXPECT_GT(stats_mgr->getMinDelay(StatsMgr4::XCHG_DO), 1);

    // Max delay is supposed to the same value as mininimum
    // or maximum delay.
    EXPECT_GT(stats_mgr->getMaxDelay(StatsMgr4::XCHG_DO), 1);

    // Delay sums are now the same as minimum or maximum delay.
    EXPECT_GT(stats_mgr->getSumDelay(StatsMgr4::XCHG_DO), 1);
    EXPECT_GT(stats_mgr->getSquareSumDelay(StatsMgr4::XCHG_DO), 1);
}

}
