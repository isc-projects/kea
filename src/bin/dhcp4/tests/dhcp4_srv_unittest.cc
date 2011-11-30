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

#include <dhcp/dhcp4.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp/option.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedDhcpv4Srv() { }

    boost::shared_ptr<Pkt4>
    processDiscover(boost::shared_ptr<Pkt4>& discover) {
        return Dhcpv4Srv::processDiscover(discover);
    }
    boost::shared_ptr<Pkt4>
    processRequest(boost::shared_ptr<Pkt4>& request) {
        return Dhcpv4Srv::processRequest(request);
    }
};

class Dhcpv4SrvTest : public ::testing::Test {
public:
    Dhcpv4SrvTest() {
    }
};

TEST_F(Dhcpv4SrvTest, basic) {
    // there's almost no code now. What's there provides echo capability
    // that is just a proof of concept and will be removed soon
    // No need to thoroughly test it

    EXPECT_NO_THROW( {
        Dhcpv4Srv * srv = new Dhcpv4Srv();

        delete srv;
        });

}

} // end of anonymous namespace
