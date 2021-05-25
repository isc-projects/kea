// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"

#include <perfdhcp/stats_mgr.h>

#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

namespace {

const uint32_t common_transid = 123;

/// @brief Number of packets to be used for testing packets collecting.
const size_t TEST_COLLECTED_PKT_NUM = 10;

/// @brief DHCPv4 packet with modifiable internal values.
///
/// Currently the only additional modifiable value is a packet
/// timestamp.
class Pkt4Modifiable : public Pkt4 {
public:

    /// @brief Constructor.
    ///
    /// @param msg_type DHCPv4 message type.
    /// @param transid Transaction id.
    Pkt4Modifiable(const uint8_t msg_type, const uint32_t transid)
        : Pkt4(msg_type, transid) {
    }

    /// @brief Modifies packet timestamp.
    ///
    /// @param delta Number of seconds to be added to the current
    /// packet time. If this number is negative, the new timestamp
    /// will point to earlier time than the original timestamp.
    void modifyTimestamp(const long delta) {
        timestamp_ += boost::posix_time::seconds(delta);
    }
};

/// @brief Pointer to the Pkt4Modifiable.
typedef boost::shared_ptr<Pkt4Modifiable> Pkt4ModifiablePtr;

class StatsMgrTest : public ::testing::Test {
public:
    StatsMgrTest() {
    }

    /// \brief Create DHCPv4 packet.
    ///
    /// Method creates DHCPv4 packet and updates its timestamp.
    ///
    /// \param msg_type DHCPv4 message type.
    /// \param transid transaction id for the packet.
    /// \return DHCPv4 packet.
    Pkt4Modifiable* createPacket4(const uint8_t msg_type,
                                  const uint32_t transid) {
        Pkt4Modifiable* pkt = new Pkt4Modifiable(msg_type, transid);
        // Packet timestamp is normally updated by interface
        // manager on packets reception or send. Unit tests
        // do not use interface manager so we need to do it
        // ourselves.
        pkt->updateTimestamp();
        return (pkt);
    }

    /// \brief Create DHCPv6 packet.
    ///
    /// Method creates DHCPv6 packet and updates its timestamp.
    ///
    /// \param msg_type DHCPv6 message type.
    /// \param transid transaction id.
    /// \return DHCPv6 packet.
    Pkt6* createPacket6(const uint8_t msg_type,
                        const uint32_t transid) {
        Pkt6* pkt = new Pkt6(msg_type, transid);
        // Packet timestamp is normally updated by interface
        // manager on packets reception or send. Unit tests
        // do not use interface manager so we need to do it
        // ourselves.
        pkt->updateTimestamp();
        return pkt;
    }

    /// \brief Pass multiple DHCPv6 packets to Statistics Manager.
    ///
    /// Method simulates sending or receiving  multiple DHCPv6 packets.
    ///
    /// \note The xchg_type parameter is passed as non-const value to avoid
    /// false cppcheck errors which expect enum value being passed by reference.
    /// This error is not reported when non-const enum is passed by value.
    ///
    /// \param stats_mgr Statistics Manager instance to be used.
    /// \param xchg_type packet exchange types.
    /// \param packet_type DHCPv6 packet type.
    /// \param num_packets packets to be passed to Statistics Manager.
    /// \param receive simulated packets are received (if true)
    /// or sent (if false)
    void passMultiplePackets6(const boost::shared_ptr<StatsMgr> stats_mgr,
                              ExchangeType xchg_type,
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

    /// \brief Simulate DHCPv4 DISCOVER-OFFER with delay.
    ///
    /// Method simulates DHCPv4 DISCOVER-OFFER exchange. The OFFER packet
    /// creation is delayed by the specified number of seconds. This imposes
    /// different packet timestamps and affects delay counters in Statistics
    /// Manager.
    ///
    /// \param stats_mgr Statistics Manager instance.
    /// \param delay delay in seconds between DISCOVER and OFFER packets.
    void passDOPacketsWithDelay(const boost::shared_ptr<StatsMgr> stats_mgr,
                                unsigned int delay,
                                uint32_t transid) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      transid));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
        );

        // Simulate time difference by changing time of sent packet
        auto ts = sent_packet->getTimestamp() - boost::posix_time::seconds(delay);
        sent_packet->setTimestamp(ts);

        boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      transid));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet);
        );

        // Calculate period between packets.
        boost::posix_time::ptime sent_time = sent_packet->getTimestamp();
        boost::posix_time::ptime rcvd_time = rcvd_packet->getTimestamp();

        ASSERT_FALSE(sent_time.is_not_a_date_time());
        ASSERT_FALSE(rcvd_time.is_not_a_date_time());
    }

    /// @brief This test verifies that timed out packets are collected.
    ///
    /// @param transid_index Index in the table of transaction ids which
    /// points to the transaction id to be selected for the DHCPOFFER.
    void testSendReceiveCollected(const size_t transid_index) {
        CommandOptions opt;
        boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
        // The second parameter indicates that transactions older than
        // 2 seconds should be removed and respective packets collected.
        stats_mgr->addExchangeStats(ExchangeType::DO, 2);

        // Transaction ids of packets to be sent. All transaction ids
        // belong to the same bucket (match the transid & 1023 hashing
        // function).
        uint32_t transid[TEST_COLLECTED_PKT_NUM] =
            { 1, 1025, 2049, 3073, 4097, 5121, 6145, 7169, 8193, 9217 };

        // Simulate sending a number of packets.
        for (unsigned int i = 0; i < TEST_COLLECTED_PKT_NUM; ++i) {
            Pkt4ModifiablePtr sent_packet(createPacket4(DHCPDISCOVER,
                                                    transid[i]));
            // For packets with low indexes we set the timestamps to
            // 10s in the past. When DHCPOFFER is processed, the
            // packets with timestamps older than 2s should be collected.
            if (i < TEST_COLLECTED_PKT_NUM / 2) {
                sent_packet->modifyTimestamp(-10);
            }
            ASSERT_NO_THROW(
                stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
            )  << "failure for transaction id " << transid[i];
        }

        // Create a server response for one of the packets sent.
        Pkt4ModifiablePtr rcvd_packet(createPacket4(DHCPOFFER,
                                                    transid[transid_index]));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet);
        );

        // There is exactly one case (transaction id) for which perfdhcp
        // will find a packet using ordered lookup. In this case, no
        // packets will be collected. Otherwise, for any unordered lookup
        // all packets from a bucket should be collected.
        if (stats_mgr->getUnorderedLookups(ExchangeType::DO) > 0) {
            // All packets in the bucket having transaction id
            // index below TEST_COLLECTED_PKT_NUM / 2 should be removed.
            EXPECT_EQ(TEST_COLLECTED_PKT_NUM / 2,
                      stats_mgr->getCollectedNum(ExchangeType::DO));
        }

        // Make sure that we can still use the StatsMgr. It is possible
        // that the pointer to 'next sent' packet was invalidated
        // during packet removal.
        for (unsigned int i = 0; i < TEST_COLLECTED_PKT_NUM; ++i) {
            // Increase transaction ids by 1 so as they don't duplicate
            // with transaction ids of already sent packets.
            Pkt4ModifiablePtr sent_packet(createPacket4(DHCPDISCOVER,
                                                    transid[i] + 1));
            Pkt4ModifiablePtr rcvd_packet(createPacket4(DHCPOFFER,
                                                        transid[i] + 1));
            ASSERT_NO_THROW(
                stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
            ) << "failure for transaction id " << transid[i];

            ASSERT_NO_THROW(
                stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet);
            ) << "failure for transaction id " << transid[i];
        }

        // We should have processed TEST_COLLECTED_PKT_NUM but it is possible
        // that one of them we couldn't match (orphan packet), because
        // the matched packet had to be collected because of the transaction
        // timeout. Therefore, we have to count both received packets and
        // orphans.
        EXPECT_EQ(TEST_COLLECTED_PKT_NUM + 1,
                  stats_mgr->getRcvdPacketsNum(ExchangeType::DO) +
                  stats_mgr->getOrphans(ExchangeType::DO));
    }
};

TEST_F(StatsMgrTest, Constructor) {
    CommandOptions opt;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::DO);
    EXPECT_DOUBLE_EQ(
        std::numeric_limits<double>::max(),
        stats_mgr->getMinDelay(ExchangeType::DO)
    );
    EXPECT_DOUBLE_EQ(0, stats_mgr->getMaxDelay(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getOrphans(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getOrderedLookups(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getUnorderedLookups(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getSentPacketsNum(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getRcvdPacketsNum(ExchangeType::DO));
    EXPECT_EQ(0, stats_mgr->getCollectedNum(ExchangeType::DO));

    EXPECT_THROW(stats_mgr->getAvgDelay(ExchangeType::DO), InvalidOperation);
    EXPECT_THROW(stats_mgr->getStdDevDelay(ExchangeType::DO),
                 InvalidOperation);
    EXPECT_THROW(stats_mgr->getAvgUnorderedLookupSetSize(ExchangeType::DO),
                 InvalidOperation);
}

TEST_F(StatsMgrTest, Exchange) {
    CommandOptions opt;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    // This is expected to throw because XCHG_DO was not yet
    // added to Stats Manager for tracking.
    ASSERT_FALSE(stats_mgr->hasExchangeStats(ExchangeType::DO));
    ASSERT_FALSE(stats_mgr->hasExchangeStats(ExchangeType::RA));
    EXPECT_THROW(
        stats_mgr->passSentPacket(ExchangeType::DO, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet),
        BadValue
    );


    // Adding DISCOVER-OFFER exchanges to be tracked by Stats Manager.
    stats_mgr->addExchangeStats(ExchangeType::DO);
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::DO));
    ASSERT_FALSE(stats_mgr->hasExchangeStats(ExchangeType::RA));
    // The following two attempts are expected to throw because
    // invalid exchange types are passed (XCHG_RA instead of XCHG_DO)
    EXPECT_THROW(
        stats_mgr->passSentPacket(ExchangeType::RA, sent_packet),
        BadValue
    );
    EXPECT_THROW(
        stats_mgr->passRcvdPacket(ExchangeType::RA, rcvd_packet),
        BadValue
    );

    // The following two attempts are expected to run fine because
    // right exchange type is specified.
    EXPECT_NO_THROW(
        stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
    );
    EXPECT_NO_THROW(
        stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet)
    );
}

TEST_F(StatsMgrTest, MultipleExchanges) {
    CommandOptions opt;
    boost::shared_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::SA);
    stats_mgr->addExchangeStats(ExchangeType::RR);

    // Simulate sending number of solicit packets.
    const int solicit_packets_num = 10;
    passMultiplePackets6(stats_mgr, ExchangeType::SA, DHCPV6_SOLICIT,
                         solicit_packets_num);

    // Simulate sending number of request packets. It is important that
    // number of request packets is different then number of solicit
    // packets. We can now check if right number packets went to
    // the right exchange type group.
    const int request_packets_num = 5;
    passMultiplePackets6(stats_mgr, ExchangeType::RR, DHCPV6_REQUEST,
                         request_packets_num);

    // Check if all packets are successfully passed to packet lists.
    EXPECT_EQ(solicit_packets_num,
              stats_mgr->getSentPacketsNum(ExchangeType::SA));
    EXPECT_EQ(request_packets_num,
              stats_mgr->getSentPacketsNum(ExchangeType::RR));

    // Simulate reception of multiple packets for both SOLICIT-ADVERTISE
    // and REQUEST-REPLY exchanges. Assume no packet drops.
    const bool receive_packets = true;
    passMultiplePackets6(stats_mgr, ExchangeType::SA, DHCPV6_ADVERTISE,
                         solicit_packets_num, receive_packets);

    passMultiplePackets6(stats_mgr, ExchangeType::RR, DHCPV6_REPLY,
                         request_packets_num, receive_packets);

    // Verify that all received packets are counted.
    EXPECT_EQ(solicit_packets_num,
              stats_mgr->getRcvdPacketsNum(ExchangeType::SA));
    EXPECT_EQ(request_packets_num,
              stats_mgr->getRcvdPacketsNum(ExchangeType::RR));
}

TEST_F(StatsMgrTest, SendReceiveSimple) {
    CommandOptions opt;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                      common_transid));
    boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER,
                                                      common_transid));
    stats_mgr->addExchangeStats(ExchangeType::DO);
    // The following attempt is expected to pass because the right
    // exchange type is used.
    ASSERT_NO_THROW(
        stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
    );
    // It is ok, to pass to received packets here. First one will
    // be matched with sent packet. The latter one will not be
    // matched with sent packet but orphans counter will simply
    // increase.
    ASSERT_NO_THROW(
        stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet)
    );
    ASSERT_NO_THROW(
        stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet)
    );
    EXPECT_EQ(1, stats_mgr->getOrphans(ExchangeType::DO));
}

TEST_F(StatsMgrTest, SendReceiveUnordered) {
    CommandOptions opt;
    const int packets_num = 10;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::DO);

    // Transaction ids of 10 packets to be sent and received.
    uint32_t transid[packets_num] =
        { 1, 1024, 2, 1025, 3, 1026, 4, 1027, 5, 1028 };
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER,
                                                          transid[i]));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
        );
    }

    // We are simulating that received packets are coming in reverse order:
    // 1028, 5, 1027 ....
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4>
            rcvd_packet(createPacket4(DHCPDISCOVER,
                                      transid[packets_num - 1 - i]));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet);
        );
    }
    // All packets are expected to match (we did not drop any)
    EXPECT_EQ(0, stats_mgr->getOrphans(ExchangeType::DO));
    // Most of the time we have to do unordered lookups except for the last
    // one. Packets are removed from the sent list every time we have a match
    // so eventually we come up with the single packet that caching iterator
    // is pointing to. This is counted as ordered lookup.
    EXPECT_EQ(1, stats_mgr->getOrderedLookups(ExchangeType::DO));
    EXPECT_EQ(9, stats_mgr->getUnorderedLookups(ExchangeType::DO));
}

TEST_F(StatsMgrTest, SendReceiveCollected) {
    // Check that the packet collection mechanism works fine
    // for any packet returned by the server.
    for (unsigned int i = 0; i < TEST_COLLECTED_PKT_NUM; ++i) {
        testSendReceiveCollected(i);
    }
}

TEST_F(StatsMgrTest, Orphans) {
    CommandOptions opt;
    const int packets_num = 6;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::DO);

    // We skip every second packet to simulate drops.
    for (int i = 0; i < packets_num; i += 2) {
        boost::shared_ptr<Pkt4> sent_packet(createPacket4(DHCPDISCOVER, i));
        ASSERT_NO_THROW(
            stats_mgr->passSentPacket(ExchangeType::DO, sent_packet)
        );
    }
    // We pass all received packets.
    for (int i = 0; i < packets_num; ++i) {
        boost::shared_ptr<Pkt4> rcvd_packet(createPacket4(DHCPOFFER, i));
        ASSERT_NO_THROW(
            stats_mgr->passRcvdPacket(ExchangeType::DO, rcvd_packet);
        );
    }
    // The half of received packets are expected not to have matching
    // sent packet.
    EXPECT_EQ(packets_num / 2, stats_mgr->getOrphans(ExchangeType::DO));
}

TEST_F(StatsMgrTest, Delays) {
    CommandOptions opt;
    boost::shared_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::DO, 5);

    // Send DISCOVER, wait 2s and receive OFFER. This will affect
    // counters in Stats Manager.
    passDOPacketsWithDelay(stats_mgr, 2, common_transid);

    // Initially min delay is equal to MAX_DOUBLE. After first packets
    // are passed, it is expected to set to actual value.
    EXPECT_LT(stats_mgr->getMinDelay(ExchangeType::DO),
              std::numeric_limits<double>::max());
    EXPECT_GT(stats_mgr->getMinDelay(ExchangeType::DO), 1);

    // Max delay is supposed to the same value as minimum
    // or maximum delay.
    EXPECT_GT(stats_mgr->getMaxDelay(ExchangeType::DO), 1);

    // Delay sums are now the same as minimum or maximum delay.
    EXPECT_GT(stats_mgr->getAvgDelay(ExchangeType::DO), 1);

    // Simulate another DISCOVER-OFFER exchange with delay between
    // sent and received packets. Delay is now shorter than earlier
    // so standard deviation of delay will now increase.
    const unsigned int delay2 = 1;
    passDOPacketsWithDelay(stats_mgr, delay2, common_transid + 1);
    // Standard deviation is expected to be non-zero.
    EXPECT_GT(stats_mgr->getStdDevDelay(ExchangeType::DO), 0);
}

TEST_F(StatsMgrTest, CustomCounters) {
    CommandOptions opt;
    boost::scoped_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));

    // Specify counter keys and names.
    const std::string too_short_key("tooshort");
    const std::string too_short_name("Too short packets");
    const std::string too_late_key("toolate");
    const std::string too_late_name("Packets sent too late");

    // Add two custom counters.
    stats_mgr->addCustomCounter(too_short_key, too_short_name);
    stats_mgr->addCustomCounter(too_late_key, too_late_name);

    // Increment one of the counters 10 times.
    const uint64_t tooshort_num = 10;
    for (uint64_t i = 0; i < tooshort_num; ++i) {
        stats_mgr->incrementCounter(too_short_key);
    }

    // Increment another counter by 5 times.
    const uint64_t toolate_num = 5;
    for (uint64_t i = 0; i < toolate_num; ++i) {
        stats_mgr->incrementCounter(too_late_key);
    }

    // Check counter's current value and name.
    CustomCounterPtr tooshort_counter =
        stats_mgr->getCounter(too_short_key);
    EXPECT_EQ(too_short_name, tooshort_counter->getName());
    EXPECT_EQ(tooshort_num, tooshort_counter->getValue());

    // Check counter's current value and name.
    CustomCounterPtr toolate_counter =
        stats_mgr->getCounter(too_late_key);
    EXPECT_EQ(too_late_name, toolate_counter->getName());
    EXPECT_EQ(toolate_num, toolate_counter->getValue());

}

TEST_F(StatsMgrTest, PrintStats) {
    std::cout << "This unit test is checking statistics printing "
              << "capabilities. It is expected that some counters "
              << "will be printed during this test. It may also "
              << "cause spurious errors." << std::endl;
    CommandOptions opt;
    boost::shared_ptr<StatsMgr> stats_mgr(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::SA);

    // Simulate sending and receiving one packet. Otherwise printing
    // functions will complain about lack of packets.
    const int packets_num = 1;
    passMultiplePackets6(stats_mgr, ExchangeType::SA, DHCPV6_SOLICIT,
                         packets_num);
    passMultiplePackets6(stats_mgr, ExchangeType::SA, DHCPV6_ADVERTISE,
                         packets_num, true);

    // This function will print statistics even if packets are not
    // archived because it relies on counters. There is at least one
    // exchange needed to count the average delay and std deviation.
    EXPECT_NO_THROW(stats_mgr->printStats());

    // Printing timestamps is expected to fail because by default we
    // disable packets archiving mode. Without packets we can't get
    // timestamps.
    EXPECT_THROW(stats_mgr->printTimestamps(), isc::InvalidOperation);

    // Now, we create another statistics manager instance and enable timestamp
    // printing, thus also enabling packets archiving mode.
    CommandOptionsHelper::process(opt, "perfdhcp -x t 127.0.0.1");
    stats_mgr.reset(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::SA);

    // Timestamps should now get printed because packets have been preserved.
    EXPECT_NO_THROW(stats_mgr->printTimestamps());

    // Create another statistics manager instance and enable lease printing for
    // v4, thus also enabling packets archiving mode.
    CommandOptionsHelper::process(opt, "perfdhcp -4 -x l 127.0.0.1");
    stats_mgr.reset(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::RNA);
    stats_mgr->addExchangeStats(ExchangeType::RLA);
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::DO));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RA));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RNA));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RLA));

    // Leases should now get printed because packets have been preserved.
    EXPECT_NO_THROW(stats_mgr->printLeases());

    // For v6 this time.
    CommandOptionsHelper::process(opt, "perfdhcp -6 -x l 127.0.0.1");
    stats_mgr.reset(new StatsMgr(opt));
    stats_mgr->addExchangeStats(ExchangeType::RN);
    stats_mgr->addExchangeStats(ExchangeType::RL);
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::SA));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RR));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RN));
    ASSERT_TRUE(stats_mgr->hasExchangeStats(ExchangeType::RL));

    // Leases should now get printed because packets have been preserved.
    EXPECT_NO_THROW(stats_mgr->printLeases());
}

}  // namespace
