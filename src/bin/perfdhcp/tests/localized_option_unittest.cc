// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>

#include <dhcp/option.h>
#include <dhcp/dhcp6.h>

#include <boost/scoped_ptr.hpp>

#include "../localized_option.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

namespace {

TEST(LocalizedOptionTest, Constructor) {
    OptionBuffer opt_buf;
    // Create option with default offset.
    boost::scoped_ptr<LocalizedOption> opt1(new LocalizedOption(Option::V6,
                                                                D6O_CLIENTID,
                                                                opt_buf));
    EXPECT_EQ(Option::V6, opt1->getUniverse());
    EXPECT_EQ(D6O_CLIENTID, opt1->getType());
    EXPECT_EQ(0, opt1->getOffset());

    // Create option with non-default offset.
    boost::scoped_ptr<LocalizedOption> opt2(new LocalizedOption(Option::V6,
                                                                D6O_CLIENTID,
                                                                opt_buf,
                                                                40));
    EXPECT_EQ(40, opt2->getOffset());
}

}
