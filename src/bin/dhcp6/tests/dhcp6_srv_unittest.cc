// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>


#include "dhcp6/dhcp6_srv.h"

using namespace std;
using namespace isc;

namespace {
class Dhcpv6SrvTest : public ::testing::Test {
public:
    Dhcpv6SrvTest() {
    }
};

TEST_F(Dhcpv6SrvTest, basic) {
    // there's almost no code now. What's there provides echo capability 
    // that is just a proof of concept and will be removed soon
    // No need to thoroughly test it

    // srv has stubbed interface detection. It will read
    // interfaces.txt instead. It will pretend to have detected
    // fe80::1234 link-local address on eth0 interface. Obviously

    // an attempt to bind this socket will fail.
    EXPECT_NO_THROW( {
        Dhcpv6Srv * srv = new Dhcpv6Srv();

	delete srv;
	});
    
}

}
