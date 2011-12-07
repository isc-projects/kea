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
#include <fstream>
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
const char* const INTERFACE_FILE = "interfaces.txt";

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedDhcpv4Srv() { }

    boost::shared_ptr<Pkt4> processDiscover(boost::shared_ptr<Pkt4>& discover) {
        return Dhcpv4Srv::processDiscover(discover);
    }
    boost::shared_ptr<Pkt4> processRequest(boost::shared_ptr<Pkt4>& request) {
        return Dhcpv4Srv::processRequest(request);
    }
    void processRelease(boost::shared_ptr<Pkt4>& release) {
        return Dhcpv4Srv::processRelease(release);
    }
    void processDecline(boost::shared_ptr<Pkt4>& decline) {
        Dhcpv4Srv::processDecline(decline);
    }
    boost::shared_ptr<Pkt4> processInform(boost::shared_ptr<Pkt4>& inform) {
        return Dhcpv4Srv::processInform(inform);
    }
};

class Dhcpv4SrvTest : public ::testing::Test {
public:
    Dhcpv4SrvTest() {
        unlink(INTERFACE_FILE);
        fstream fakeifaces(INTERFACE_FILE, ios::out|ios::trunc);
        fakeifaces << "lo ::1";
        fakeifaces.close();
    }

    ~Dhcpv4SrvTest() {
        unlink(INTERFACE_FILE);
    };
};

TEST_F(Dhcpv4SrvTest, basic) {
    // nothing to test. DHCPv4_srv instance is created
    // in test fixture. It is destroyed in destructor

    Dhcpv4Srv* srv = 0;
    ASSERT_NO_THROW({
        srv = new Dhcpv4Srv();
    });

    if (srv) {
        ASSERT_NO_THROW({
            delete srv;
        });
    }
}

TEST_F(Dhcpv4SrvTest, processDiscover) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDISCOVER, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processDiscover(pkt);
    );

    // should return something
    EXPECT_TRUE(srv->processDiscover(pkt));

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processRequest) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPREQUEST, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processRequest(pkt);
    );

    // should return something
    EXPECT_TRUE(srv->processRequest(pkt));

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processRelease) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPRELEASE, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processRelease(pkt);
    );

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processDecline) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDECLINE, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processDecline(pkt);
    );

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processInform) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPINFORM, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processInform(pkt);
    );

    // should return something
    EXPECT_TRUE(srv->processInform(pkt));

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

} // end of anonymous namespace
