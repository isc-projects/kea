// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"
#include "../basic_scen.h"

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
#include <mutex>
#include <gtest/gtest.h>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

/// \brief FakeScenPerfSocket class that mocks PerfSocket.
///
/// It stubs send and receive operations and collects statistics.
/// Beside that it simulates DHCP server responses for received
/// packets.
class FakeScenPerfSocket: public BasePerfSocket {
public:
    /// \brief Default constructor for FakeScenPerfSocket.
    FakeScenPerfSocket(CommandOptions &opt) :
        opt_(opt),
        iface_(boost::make_shared<Iface>("fake", 0)),
        sent_cnt_(0),
        recv_cnt_(0),
        start_dropping_after_cnt_(100000) {};

    CommandOptions &opt_;

    IfacePtr iface_;  ///< Local fake interface.

    int sent_cnt_;  ///< Counter of sent packets.
    int recv_cnt_;  ///< Counter of received packets.

    /// List of pairs <msg_type, trans_id> containing responses
    /// planned to send to perfdhcp.
    std::list<std::tuple<uint8_t, uint32_t>> planned_responses_;

    /// Mutex to protect internal state.
    std::mutex mutex_;

    /// Limit for sent packets. After this limit not more packets
    /// are sent. This simulate dropping responses.
    int start_dropping_after_cnt_;

    /// \brief Simulate receiving DHCPv4 packet.
    virtual dhcp::Pkt4Ptr receive4(uint32_t /*timeout_sec*/, uint32_t /*timeout_usec*/) override {
        std::lock_guard<std::mutex> lock(mutex_);
        recv_cnt_++;

        if (planned_responses_.empty() || sent_cnt_ >= start_dropping_after_cnt_) {
            return Pkt4Ptr();
        }
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
    virtual dhcp::Pkt6Ptr receive6(uint32_t /*timeout_sec*/, uint32_t /*timeout_usec*/) override {
        std::lock_guard<std::mutex> lock(mutex_);
        recv_cnt_++;

        if (planned_responses_.empty() || sent_cnt_ >= start_dropping_after_cnt_) {
            return Pkt6Ptr();
        }
        auto msg = planned_responses_.front();
        planned_responses_.pop_front();
        auto msg_type = std::get<0>(msg);
        Pkt6Ptr pkt(new Pkt6(msg_type, std::get<1>(msg)));
        // Add IA_NA if requested by the client.
        if (opt_.getLeaseType().includes(CommandOptions::LeaseType::ADDRESS)) {
            OptionPtr opt_ia_na = Option::factory(Option::V6, D6O_IA_NA);
            OptionPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                             isc::asiolink::IOAddress("fe80::abcd"), 300, 500));
            opt_ia_na->addOption(iaaddr);
            pkt->addOption(opt_ia_na);
        }
        // Add IA_PD if requested by the client.
        if (opt_.getLeaseType().includes(CommandOptions::LeaseType::PREFIX)) {
            OptionPtr opt_ia_pd = Option::factory(Option::V6, D6O_IA_PD);
            OptionPtr iapref(new Option6IAPrefix(D6O_IAPREFIX,
                             isc::asiolink::IOAddress("fe80::"), 64, 300, 500));
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
        std::lock_guard<std::mutex> lock(mutex_);
        sent_cnt_++;
        pkt->updateTimestamp();
        if (sent_cnt_ >= start_dropping_after_cnt_) {
            return true;
        }
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
        std::lock_guard<std::mutex> lock(mutex_);
        sent_cnt_++;
        pkt->updateTimestamp();
        if (sent_cnt_ >= start_dropping_after_cnt_) {
            return true;
        }
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
        std::lock_guard<std::mutex> lock(mutex_);
        sent_cnt_ = 0;
        recv_cnt_ = 0;
    }
};


/// \brief NakedBasicScen class.
///
/// It exposes BasicScen internals for UT.
class NakedBasicScen: public BasicScen {
public:
    using BasicScen::basic_rate_control_;
    using BasicScen::renew_rate_control_;
    using BasicScen::release_rate_control_;
    using BasicScen::tc_;

    FakeScenPerfSocket fake_sock_;

    NakedBasicScen(CommandOptions &opt) : BasicScen(opt, fake_sock_), fake_sock_(opt) {};

};


/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp BasicScenTest class.
class BasicScenTest : public virtual ::testing::Test
{
public:
    BasicScenTest() { }

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


// This test verifies that the class members are reset to expected values.
TEST_F(BasicScenTest, initial_settings) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -6 -l ethx -r 50 -f 30 -F 10 all");
    NakedBasicScen bs(opt);

    EXPECT_EQ(50, bs.basic_rate_control_.getRate());
    EXPECT_EQ(30, bs.renew_rate_control_.getRate());
    EXPECT_EQ(10, bs.release_rate_control_.getRate());
}


TEST_F(BasicScenTest, Packet4Exchange) {
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -r 100 -n 10 -g single 127.0.0.1");
    NakedBasicScen bs(opt);
    bs.run();
    // The command line restricts the number of iterations to 10
    // with -n 10 parameter.
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 20); // Discovery + Request
    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 10);
}

TEST_F(BasicScenTest, Address4Unique) {
    // send more than 1 discover+request but with the same address
    // counter of a unique addresses should be 1
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -u -l fake -r 10 -n 10 -g single 127.0.0.1");
    NakedBasicScen bs(opt);
    bs.run();
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 5); // Discovery + Request
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 1);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 1);
    EXPECT_GE(bs.tc_.getAllUniqueAddrReply().size(), 1);
    EXPECT_GE(bs.tc_.getAllUniqueAddrAdvert().size(), 1);
    EXPECT_EQ(bs.tc_.getStatsMgr().getNonUniqueAddrNum(ExchangeType::DO), 9);
    EXPECT_EQ(bs.tc_.getStatsMgr().getNonUniqueAddrNum(ExchangeType::RA), 9);
}

TEST_F(BasicScenTest, Address6Unique) {
    // send more than 1 solicit+request but with the same address
    // counter of a unique addresses should be 1
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -6 -u -l fake -r 10 -n 10 -g single ::1");
    NakedBasicScen bs(opt);
    bs.run();
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 5); // Solicit + Request
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 1);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 1);
    EXPECT_GE(bs.tc_.getAllUniqueAddrReply().size(), 1);
    EXPECT_GE(bs.tc_.getAllUniqueAddrAdvert().size(), 1);
    EXPECT_EQ(bs.tc_.getStatsMgr().getNonUniqueAddrNum(ExchangeType::SA), 9);
    EXPECT_EQ(bs.tc_.getStatsMgr().getNonUniqueAddrNum(ExchangeType::RR), 9);
}

TEST_F(BasicScenTest, Packet4ExchangeMaxDrop10Proc) {
    CommandOptions opt;

    // With the following command line we restrict the maximum
    // number of dropped packets to 10% of all.
    // Use templates for this test.
    processCmdLine(opt, "perfdhcp -l fake -r 100 -R 20 -n 100"
                   " -D 10% -L 10547  -g single"
                   // \todo seems to be broken as it crashes building pkt
                   // " -T " + getFullPath("discover-example.hex")
                   // + " -T " + getFullPath("request4-example.hex")
                   " 127.0.0.1");
    // The number iterations is restricted by the percentage of
    // dropped packets (-D 10%).
    NakedBasicScen bs(opt);
    bs.fake_sock_.start_dropping_after_cnt_ = 10;
    bs.run();
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 15); // Discovery + Request
    EXPECT_LE(bs.fake_sock_.sent_cnt_, 20); // Discovery + Request

    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::DO), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::DO), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RA), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RA), 15);
}


TEST_F(BasicScenTest, Packet6Exchange) {
    // Set number of iterations to 10.
    CommandOptions opt;
    processCmdLine(opt, "perfdhcp -l fake -6 -r 100 -n 10 -g single -R 20 -L 10547 ::1");
    // Set number of received packets equal to number of iterations.
    // This simulates no packet drops.
    NakedBasicScen bs(opt);
    bs.run();
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 20); // Solicit + Request
    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), 10);
    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 10);
}

TEST_F(BasicScenTest, Packet6ExchangeMaxDrop3Pkt) {
    CommandOptions opt;
    // The maximum number of dropped packets is 3 (because of -D 3).
    processCmdLine(opt, "perfdhcp -l fake"
                   " -6 -r 100 -n 100 -R 20 -D 3 -L 10547"
                   // \todo seems to be broken as it crashes building pkt
                   // " -T " + getFullPath("solicit-example.hex")
                   // + " -T " + getFullPath("request6-example.hex")
                   " ::1");

    // Simulate the number of Solicit-Advertise-Request-Reply (SARR) exchanges.
    // The test function generates server's responses and passes it to the
    // TestControl class methods for processing. The number of exchanges
    // actually performed is controller by 'start_dropping_after_cnt_'.
    // All exchanged packets carry the IA_NA option
    // to simulate the IPv6 address acquisition and to verify that the
    // IA_NA options returned by the server are processed correctly.
    NakedBasicScen bs(opt);
    bs.fake_sock_.start_dropping_after_cnt_ = 10;
    bs.run();
    EXPECT_GE(bs.fake_sock_.sent_cnt_, 10);
    EXPECT_LE(bs.fake_sock_.sent_cnt_, 20);

    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::SA), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::SA), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getSentPacketsNum(ExchangeType::RR), 15);

    EXPECT_GE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 1);
    EXPECT_LE(bs.tc_.getStatsMgr().getRcvdPacketsNum(ExchangeType::RR), 15);
}
