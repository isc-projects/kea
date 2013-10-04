// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>
#include <dhcp6/tests/dhcp6_test_utils.h>

namespace isc {
namespace test {

// Checks that server response (ADVERTISE or REPLY) contains proper IA_NA option
// It returns IAADDR option for each chaining with checkIAAddr method.
boost::shared_ptr<Option6IAAddr>
Dhcpv6SrvTest::checkIA_NA(const Pkt6Ptr& rsp, uint32_t expected_iaid,
                          uint32_t expected_t1, uint32_t expected_t2) {
    OptionPtr tmp = rsp->getOption(D6O_IA_NA);
    // Can't use ASSERT_TRUE() in method that returns something
    if (!tmp) {
        ADD_FAILURE() << "IA_NA option not present in response";
        return (boost::shared_ptr<Option6IAAddr>());
    }

    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    if (!ia) {
        ADD_FAILURE() << "IA_NA cannot convert option ptr to Option6";
        return (boost::shared_ptr<Option6IAAddr>());
    }

    EXPECT_EQ(expected_iaid, ia->getIAID());
    EXPECT_EQ(expected_t1, ia->getT1());
    EXPECT_EQ(expected_t2, ia->getT2());

    tmp = ia->getOption(D6O_IAADDR);
    boost::shared_ptr<Option6IAAddr> addr = boost::dynamic_pointer_cast<Option6IAAddr>(tmp);
    return (addr);
}

boost::shared_ptr<Option6IAPrefix>
Dhcpv6SrvTest::checkIA_PD(const Pkt6Ptr& rsp, uint32_t expected_iaid,
                          uint32_t expected_t1, uint32_t expected_t2) {
    OptionPtr tmp = rsp->getOption(D6O_IA_PD);
    // Can't use ASSERT_TRUE() in method that returns something
    if (!tmp) {
        ADD_FAILURE() << "IA_PD option not present in response";
        return (boost::shared_ptr<Option6IAPrefix>());
    }

    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    if (!ia) {
        ADD_FAILURE() << "IA_PD cannot convert option ptr to Option6";
        return (boost::shared_ptr<Option6IAPrefix>());
    }

    EXPECT_EQ(expected_iaid, ia->getIAID());
    EXPECT_EQ(expected_t1, ia->getT1());
    EXPECT_EQ(expected_t2, ia->getT2());

    tmp = ia->getOption(D6O_IAPREFIX);
    boost::shared_ptr<Option6IAPrefix> addr = boost::dynamic_pointer_cast<Option6IAPrefix>(tmp);
    return (addr);
}

// Checks if the lease sent to client is present in the database
// and is valid when checked agasint the configured subnet
Lease6Ptr
Dhcpv6SrvTest::checkLease(const DuidPtr& duid, const OptionPtr& ia_na,
                          boost::shared_ptr<Option6IAAddr> addr) {
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(ia_na);

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            addr->getAddress());
    if (!lease) {
        std::cout << "Lease for " << addr->getAddress().toText()
                  << " not found in the database backend.";
        return (Lease6Ptr());
    }

    EXPECT_EQ(addr->getAddress().toText(), lease->addr_.toText());
    EXPECT_TRUE(*lease->duid_ == *duid);
    EXPECT_EQ(ia->getIAID(), lease->iaid_);
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}

Lease6Ptr
Dhcpv6SrvTest::checkPdLease(const DuidPtr& duid, const OptionPtr& ia_pd,
                            boost::shared_ptr<Option6IAPrefix> prefix){
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(ia_pd);

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                            prefix->getAddress());
    if (!lease) {
        std::cout << "PD lease for " << prefix->getAddress().toText()
                  << " not found in the database backend.";
        return (Lease6Ptr());
    }

    EXPECT_EQ(prefix->getAddress().toText(), lease->addr_.toText());
    EXPECT_TRUE(*lease->duid_ == *duid);
    EXPECT_EQ(ia->getIAID(), lease->iaid_);
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}


void
Dhcpv6SrvTest::testRenewBasic(Lease::Type type, const std::string& existing_addr,
                              const std::string& renew_addr) {
    NakedDhcpv6Srv srv(0);

    const IOAddress existing(existing_addr);
    const IOAddress renew(renew_addr);
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(type, existing));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(type, existing, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(), 128));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(type, existing);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));

    uint16_t code = D6O_IA_NA;
    OptionPtr subopt;
    switch (type) {
    case Lease::TYPE_NA:
        code = D6O_IA_NA;
        subopt.reset(new Option6IAAddr(D6O_IAADDR, renew, 300, 500));
        break;
    case Lease::TYPE_PD:
        code = D6O_IA_PD;
        subopt.reset(new Option6IAPrefix(D6O_IAPREFIX, renew, 32u, 300, 500));
    default:
        isc_throw(BadValue, "Invalid lease type specified");
    }

    boost::shared_ptr<Option6IA> ia = generateIA(code, iaid, 1500, 3000);

    ia->addOption(subopt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    switch (type) {
    case Lease::TYPE_NA: {
        // Check that IA_NA was returned and that there's an address included
        boost::shared_ptr<Option6IAAddr> addr_opt = checkIA_NA(reply, 234, subnet_->getT1(),
                                                           subnet_->getT2());

        ASSERT_TRUE(addr_opt);

        // Check that we've got the address we requested
        checkIAAddr(addr_opt, renew, Lease::TYPE_NA);

        // Check that the lease is really in the database
        l = checkLease(duid_, reply->getOption(code), addr_opt);
        ASSERT_TRUE(l);
        break;
    }

    case Lease::TYPE_PD: {
        // Check that IA_NA was returned and that there's an address included
        boost::shared_ptr<Option6IAPrefix> prefix_opt
            = checkIA_PD(reply, 234, subnet_->getT1(), subnet_->getT2());

        ASSERT_TRUE(prefix_opt);

        // Check that we've got the address we requested
        checkIAAddr(prefix_opt, renew, Lease::TYPE_PD);
        EXPECT_EQ(pd_pool_->getLength(), prefix_opt->getLength());

        // Check that the lease is really in the database
        l = checkLease(duid_, reply->getOption(code), prefix_opt);
        ASSERT_TRUE(l);
        break;
    }
    default:
        isc_throw(BadValue, "Invalid lease type");
    }

    // Check that T1, T2, preferred, valid and cltt were really updated
    EXPECT_EQ(l->t1_, subnet_->getT1());
    EXPECT_EQ(l->t2_, subnet_->getT2());
    EXPECT_EQ(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(renew_addr));
}

// Generate IA_NA option with specified parameters
boost::shared_ptr<Option6IA>
NakedDhcpv6SrvTest::generateIA(uint16_t type, uint32_t iaid, uint32_t t1,
                               uint32_t t2) {
    boost::shared_ptr<Option6IA> ia =
        boost::shared_ptr<Option6IA>(new Option6IA(type, iaid));
    ia->setT1(t1);
    ia->setT2(t2);
    return (ia);
}

}; // end of isc::test namespace
}; // end of isc namespace
