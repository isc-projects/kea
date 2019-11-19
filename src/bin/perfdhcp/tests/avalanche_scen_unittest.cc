// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"
#include "../avalanche_scen.h"

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <cstddef>
#include <stdint.h>
#include <string>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

/// \brief FakeAvalancheScenPerfSocket class that mocks PerfSocket.
///
/// It stubs send and receive operations and collects statistics.
/// Beside that it simulates DHCP server responses for received
/// packets.
class FakeAvalancheScenPerfSocket: public BasePerfSocket {
public:
    /// \brief Default constructor for FakeAvalancheScenPerfSocket.
    FakeAvalancheScenPerfSocket(CommandOptions &opt) :
        opt_(opt),
        iface_(boost::make_shared<Iface>("fake", 0)),
        sent_cnt_(0),
        recv_cnt_(0),
        initial_drops_cnt_(0) {};

    CommandOptions &opt_;

    IfacePtr iface_;  ///< Local fake interface.

    int sent_cnt_;  ///< Counter of sent packets.
    int recv_cnt_;  ///< Counter of received packets.
    int initial_drops_cnt_;

    /// List of pairs <msg_type, trans_id> containing responses
    /// planned to send to perfdhcp.
    std::list<std::tuple<uint8_t, uint32_t>> planned_responses_;

    /// \brief Simulate receiving DHCPv4 packet.
    virtual dhcp::Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;

        if (planned_responses_.empty()) {
            return Pkt4Ptr();
        }

        // simulate initial drops
        if (initial_drops_cnt_ > 0) {
            planned_responses_.pop_front();
            initial_drops_cnt_--;
            return(Pkt4Ptr());
        }

        // prepare received packet
        auto msg = planned_responses_.front();
        planned_responses_.pop_front();
        auto msg_type = std::get<0>(msg);
        Pkt4Ptr pkt(new Pkt4(msg_type, std::get<1>(msg)));
        OptionPtr opt_serverid = Option::factory(Option::V4,
                                                 DHO_DHCP_SERVER_IDENTIFIER,
                                                 OptionBuffer(4, 1));
        pkt->setYiaddr(asiolink::IOAddress("127.0.0.1"));
        pkt->addOption(opt_serverid);
        pkt->updateTimestamp();
        return (pkt);
    };

    /// \brief Simulate receiving DHCPv6 packet.
    virtual dhcp::Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;

        if (planned_responses_.empty()) {
            return Pkt6Ptr();
        }

        // simulate initial drops
        if (initial_drops_cnt_ > 0) {
            planned_responses_.pop_front();
            initial_drops_cnt_--;
            return(Pkt6Ptr());
        }

        // prepare received packet
        auto msg = planned_responses_.front();
        planned_responses_.pop_front();
        auto msg_type = std::get<0>(msg);
        Pkt6Ptr pkt(new Pkt6(msg_type, std::get<1>(msg)));
        // Add IA_NA if requested by the client.
        if (opt_.getLeaseType().includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            OptionPtr iaaddr(new Option6IAAddr(D6O_IAADDR, isc::asiolink::IOAddress("fe80::abcd"), 300, 500));
            opt_ia_na->addOption(iaaddr);
            pkt->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (opt_.getLeaseType().includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            OptionPtr iapref(new Option6IAPrefix(D6O_IAPREFIX, isc::asiolink::IOAddress("fe80::"), 64, 300, 500));
            opt_ia_pd->addOption(iapref);
            pkt->addOption(opt_ia_pd);
        }
        OptionPtr opt_serverid(new Option(Option::V6, D6O_SERVERID));
        std::vector<uint8_t> duid({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        OptionPtr opt_clientid(Option::factory(Option::V6, D6O_CLIENTID, duid));
        pkt->addOption(opt_serverid);
        pkt->addOption(opt_clientid);
        pkt->updateTimestamp();
        return (pkt);
    };

    /// \brief Simulate sending DHCPv4 packet.
    virtual bool send(const dhcp::Pkt4Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        if (pkt->getType() == DHCPDISCOVER) {
            planned_responses_.push_back(std::make_tuple(DHCPOFFER, pkt->getTransid()));
        } else if (pkt->getType() == DHCPREQUEST) {
            planned_responses_.push_back(std::make_tuple(DHCPACK, pkt->getTransid()));
        } else {
            assert(0);
        }
        return true;
    };

    /// \brief Simulate sending DHCPv6 packet.
    virtual bool send(const dhcp::Pkt6Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        if (pkt->getType() == DHCPV6_SOLICIT) {
            planned_responses_.push_back(std::make_tuple(DHCPV6_ADVERTISE, pkt->getTransid()));
        } else if (pkt->getType() == DHCPV6_REQUEST) {
            planned_responses_.push_back(std::make_tuple(DHCPV6_REPLY, pkt->getTransid()));
        } else {
            assert(0);
        }
        return true;
    };

    /// \brief Override getting interface.
    virtual IfacePtr getIface() override { return iface_; }

    void reset() {
        sent_cnt_ = 0;
        recv_cnt_ = 0;
    }
};


/// \brief NakedAvalancheScen class.
///
/// It exposes AvalancheScen internals for UT.
class NakedAvalancheScen: public AvalancheScen {
public:
    using AvalancheScen::tc_;
    using AvalancheScen::total_resent_;

    FakeAvalancheScenPerfSocket fake_sock_;

    NakedAvalancheScen(CommandOptions &opt) : AvalancheScen(opt, fake_sock_), fake_sock_(opt) {};

};


/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp AvalancheScenTest class.
class AvalancheScenTest : public virtual ::testing::Test
{
public:
    AvalancheScenTest() { }

    /// \brief Parse command line string with CommandOptions.
    ///
    /// \param cmdline command line string to be parsed.
    /// \throw isc::Unexpected if unexpected error occurred.
    /// \throw isc::InvalidParameter if command line is invalid.
    void processCmdLine(CommandOptions &opt, const std::string& cmdline) const {
        CommandOptionsHelper::process(opt, cmdline);
    }

    /// \brief Get full path to a file in testdata directory.
    ///
    /// \param filename filename being appended to absolute
    /// path to testdata directory
    ///
    /// \return full path to a file in testdata directory.
    std::string getFullPath(const std::string& filename) const {
        std::ostringstream stream;
        stream << TEST_DATA_DIR << "/" << filename;
        return (stream.str());
    }
};


TEST_F(AvalancheScenTest, Packet4Exchange) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -4 -R 10 --scenario avalanche -g single 127.0.0.1");
    NakedAvalancheScen as(opt);

    as.run();

    // Check if basic exchange of packets happend. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 0);
    EXPECT_EQ(as.fake_sock_.sent_cnt_, 20); // Discovery + Request
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 10);
}


TEST_F(AvalancheScenTest, Packet4ExchangeOnlyDO) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -4 -R 10 -i --scenario avalanche -g single 127.0.0.1");
    NakedAvalancheScen as(opt);

    as.run();

    // Check if DO exchange of packets happend only. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 0);
    EXPECT_EQ(as.fake_sock_.sent_cnt_, 10); // Discovery + Request
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 10);
    EXPECT_THROW(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), isc::BadValue);
}


TEST_F(AvalancheScenTest, Packet4ExchangeWithRetransmissions) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -4 -R 10 --scenario avalanche -g single 127.0.0.1");
    NakedAvalancheScen as(opt);

    as.fake_sock_.initial_drops_cnt_ = 2;
    as.run();

    // Check if basic exchange of packets happend. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 2);
    EXPECT_EQ(as.fake_sock_.sent_cnt_, 22); // Discovery + Request
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 10);
}


TEST_F(AvalancheScenTest, Packet6Exchange) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -R 10 --scenario avalanche -g single ::1");
    NakedAvalancheScen as(opt);

    as.run();

    // Check if basic exchange of packets happend. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 0);
    EXPECT_GE(as.fake_sock_.sent_cnt_, 20); // Solicit + Request
    EXPECT_GE(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 10);
    EXPECT_GE(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 10);
    EXPECT_GE(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), 10);
    EXPECT_GE(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 10);
}


TEST_F(AvalancheScenTest, Packet6ExchangeOnlySA) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -R 10 -i --scenario avalanche -g single ::1");
    NakedAvalancheScen as(opt);

    as.run();

    // Check if SA exchange of packets happend only. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 0);
    EXPECT_GE(as.fake_sock_.sent_cnt_, 10); // Solicit + Request
    EXPECT_GE(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 10);
    EXPECT_GE(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 10);
    EXPECT_THROW(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), isc::BadValue);
}


TEST_F(AvalancheScenTest, Packet6ExchangeWithRetransmissions) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -R 10 --scenario avalanche -g single ::1");
    NakedAvalancheScen as(opt);

    as.fake_sock_.initial_drops_cnt_ = 2;
    as.run();

    // Check if basic exchange of packets happend. No retransmissions expected.
    EXPECT_EQ(as.total_resent_, 2);
    EXPECT_EQ(as.fake_sock_.sent_cnt_, 22); // Discovery + Request
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), 10);
    EXPECT_EQ(as.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 10);
}
