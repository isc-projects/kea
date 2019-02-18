// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "command_options_helper.h"

#include <exceptions/exceptions.h>
#include "receiver.h"
#include <gtest/gtest.h>


using namespace isc;
using namespace isc::perfdhcp;

TEST(Receiver, singleThreaded) {
    CommandOptions opt;
    CommandOptionsHelper::process(opt, "perfdhcp -g single -l 127.0.0.1 all");
    ASSERT_TRUE(opt.isSingleThreaded());

    PerfSocket socket(opt);
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

    PerfSocket socket(opt);
    Receiver receiver(socket, opt.isSingleThreaded(), opt.getIpVersion());

    ASSERT_NO_THROW(receiver.start());

    auto pkt = receiver.getPkt();
    EXPECT_EQ(pkt, nullptr);

    ASSERT_NO_THROW(receiver.stop());
}
