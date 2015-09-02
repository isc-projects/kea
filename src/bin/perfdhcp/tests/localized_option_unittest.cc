// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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
