// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"

#include <dhcp/iface_mgr.h>


#include <exceptions/exceptions.h>
#include "receiver.h"
#include <gtest/gtest.h>


using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;


/// \brief FakeReceiverPerfSocket class that mocks PerfSocket.
///
/// It stubs send and receive operations and collects statistics.
class FakeReceiverPerfSocket: public BasePerfSocket {
public:
    /// \brief Default constructor for FakeReceiverPerfSocket.
    FakeReceiverPerfSocket() :
        iface_(boost::make_shared<Iface>("fake", 0)),
        sent_cnt_(0),
        recv_cnt_(0) {};

    IfacePtr iface_;  ///< Local fake interface.

    int sent_cnt_;  ///< Counter of sent packets
    int recv_cnt_;  ///< Counter of received packets.

    /// \brief Simulate receiving DHCPv4 packet.
    virtual dhcp::Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;
        // slow down receiving as receiver calls it in a loop thousands of time
        // if null is returned
        usleep(50);
        return(dhcp::Pkt4Ptr());
    };

    /// \brief Simulate receiving DHCPv6 packet.
    virtual dhcp::Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec) override {
        (void)timeout_sec; // silence compile 'unused parameter' warning;
        (void)timeout_usec; // silence compile 'unused parameter' warning;
        recv_cnt_++;
        return(dhcp::Pkt6Ptr());
    };

    /// \brief Simulate sending DHCPv4 packet.
    virtual bool send(const dhcp::Pkt4Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        return true;
    };

    /// \brief Simulate sending DHCPv6 packet.
    virtual bool send(const dhcp::Pkt6Ptr& pkt) override {
        sent_cnt_++;
        pkt->updateTimestamp();
        return true;
    };

    /// \brief Override getting interface.
    virtual IfacePtr getIface() override { return iface_; }

    void reset() {
        sent_cnt_ = 0;
        recv_cnt_ = 0;
    }
};


TEST(Receiver, singleThreaded) {
    CommandOptions opt;
    CommandOptionsHelper::process(opt, "perfdhcp -g single -l 127.0.0.1 all");
    ASSERT_TRUE(opt.isSingleThreaded());

    FakeReceiverPerfSocket socket;
    Receiver receiver(socket, opt.isSingleThreaded(), opt.getIpVersion());

    ASSERT_NO_THROW(receiver.start());

    auto pkt = receiver.getPkt();

    EXPECT_EQ(pkt, nullptr);

    ASSERT_NO_THROW(receiver.stop());
}


TEST(Receiver, multiThreaded) {
    CommandOptions opt;
    CommandOptionsHelper::process(opt, "perfdhcp -g multi -l 127.0.0.1 all");
    ASSERT_FALSE(opt.isSingleThreaded());

    FakeReceiverPerfSocket socket;
    Receiver receiver(socket, opt.isSingleThreaded(), opt.getIpVersion());

    ASSERT_NO_THROW(receiver.start());

    auto pkt = receiver.getPkt();

    EXPECT_EQ(pkt, nullptr);

    ASSERT_NO_THROW(receiver.stop());
}
