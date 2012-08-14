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

#include <config.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp/dhcp4.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <config/ccsession.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace {

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(DHCP4_SERVER_PORT + 10000) { }
};

class CtrlDhcpv4SrvTest : public ::testing::Test {
public:
    CtrlDhcpv4SrvTest() {
    }

    ~CtrlDhcpv4SrvTest() {
    };
};

TEST_F(CtrlDhcpv4SrvTest, commands) {

    ControlledDhcpv4Srv* srv = NULL;
    ASSERT_NO_THROW({
        srv = new ControlledDhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });

    // use empty parameters list
    ElementPtr params(new isc::data::MapElement());
    int rcode = -1;

    // case 1: send bogus command
    ConstElementPtr result = ControlledDhcpv4Srv::execDhcpv4ServerCommand("blah", params);
    ConstElementPtr comment = parseAnswer(rcode, result);
    EXPECT_EQ(1, rcode); // expect failure (no such command as blah)

    // case 2: send shutdown command without any parameters
    result = ControlledDhcpv4Srv::execDhcpv4ServerCommand("shutdown", params);
    comment = parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // expect success

    const pid_t pid(getpid());
    ConstElementPtr x(new isc::data::IntElement(pid));
    params->set("pid", x);

    // case 3: send shutdown command with 1 parameter: pid
    result = ControlledDhcpv4Srv::execDhcpv4ServerCommand("shutdown", params);
    comment = parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // expect success


    delete srv;
}

} // end of anonymous namespace
