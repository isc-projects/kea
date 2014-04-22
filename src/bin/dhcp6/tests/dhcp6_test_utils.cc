// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp6/json_config_parser.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace test {

Dhcpv6SrvTest::Dhcpv6SrvTest()
:srv_(0) {
    subnet_ = isc::dhcp::Subnet6Ptr
        (new isc::dhcp::Subnet6(isc::asiolink::IOAddress("2001:db8:1::"),
                                48, 1000, 2000, 3000, 4000));
    subnet_->setIface("eth0");

    pool_ = isc::dhcp::Pool6Ptr
        (new isc::dhcp::Pool6(isc::dhcp::Lease::TYPE_NA,
                              isc::asiolink::IOAddress("2001:db8:1:1::"),
                              64));
    subnet_->addPool(pool_);

    isc::dhcp::CfgMgr::instance().deleteSubnets6();
    isc::dhcp::CfgMgr::instance().addSubnet6(subnet_);

    // configure PD pool
    pd_pool_ = isc::dhcp::Pool6Ptr
        (new isc::dhcp::Pool6(isc::dhcp::Lease::TYPE_PD,
                              isc::asiolink::IOAddress("2001:db8:1:2::"),
                              64, 80));
    subnet_->addPool(pd_pool_);
}

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
        std::cout << "Lease for " << addr->getAddress()
                  << " not found in the database backend.";
        return (Lease6Ptr());
    }

    EXPECT_EQ(addr->getAddress(), lease->addr_);
    EXPECT_TRUE(*lease->duid_ == *duid);
    EXPECT_EQ(ia->getIAID(), lease->iaid_);
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}

isc::dhcp::Lease6Ptr
Dhcpv6SrvTest::checkLease(const isc::dhcp::Lease6& lease) {
    Lease6Ptr lease_db = LeaseMgrFactory::instance().getLease6(lease.type_,
                                                               lease.addr_);
    if (!lease_db) {
        return (Lease6Ptr());
    }

    EXPECT_TRUE(lease_db->matches(lease));
    return (lease_db);
}

Lease6Ptr
Dhcpv6SrvTest::checkPdLease(const DuidPtr& duid, const OptionPtr& ia_pd,
                            boost::shared_ptr<Option6IAPrefix> prefix){
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(ia_pd);

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                            prefix->getAddress());
    if (!lease) {
        std::cout << "PD lease for " << prefix->getAddress()
                  << " not found in the database backend.";
        return (Lease6Ptr());
    }

    EXPECT_EQ(prefix->getAddress(), lease->addr_);
    EXPECT_TRUE(*lease->duid_ == *duid);
    EXPECT_EQ(ia->getIAID(), lease->iaid_);
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}


Pkt6Ptr
Dhcpv6SrvTest::createMessage(uint8_t message_type, Lease::Type lease_type,
                             const IOAddress& addr, const uint8_t prefix_len,
                             const uint32_t iaid) {
    Pkt6Ptr msg = Pkt6Ptr(new Pkt6(message_type, 1234));
    msg->setRemoteAddr(IOAddress("fe80::abcd"));
    msg->setIface("eth0");
    msg->addOption(createIA(lease_type, addr, prefix_len, iaid));
    return (msg);
}

Option6IAPtr
Dhcpv6SrvTest::createIA(isc::dhcp::Lease::Type lease_type,
                        const isc::asiolink::IOAddress& addr,
                        const uint8_t prefix_len, const uint32_t iaid) {
    uint16_t code;
    OptionPtr subopt;
    switch (lease_type) {
    case Lease::TYPE_NA:
        code = D6O_IA_NA;
        subopt.reset(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
        break;
    case Lease::TYPE_PD:
        code = D6O_IA_PD;
        subopt.reset(new Option6IAPrefix(D6O_IAPREFIX, addr, prefix_len,
                                         300, 500));
        break;
    default:
        isc_throw(BadValue, "Invalid lease type specified "
                  << static_cast<int>(lease_type));
    }

    Option6IAPtr ia = generateIA(code, iaid, 1500, 3000);
    ia->addOption(subopt);

    return (ia);
}

void
Dhcpv6SrvTest::testRenewBasic(Lease::Type type, const std::string& existing_addr,
                              const std::string& renew_addr,
                              const uint8_t prefix_len) {
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
    Lease6Ptr lease(new Lease6(type, existing, duid_, iaid, 501, 502, 503, 504,
                               subnet_->getID(), prefix_len));
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

    Pkt6Ptr req = createMessage(DHCPV6_RENEW, type, IOAddress(renew_addr),
                                prefix_len, iaid);
    req->addOption(clientid);
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    // Check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    switch (type) {
    case Lease::TYPE_NA: {
        // Check that IA_NA was returned and that there's an address included
        boost::shared_ptr<Option6IAAddr>
          addr_opt = checkIA_NA(reply, 234, subnet_->getT1(), subnet_->getT2());

        ASSERT_TRUE(addr_opt);

        // Check that we've got the address we requested
        checkIAAddr(addr_opt, renew, Lease::TYPE_NA);

        // Check that the lease is really in the database
        l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
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
        l = checkLease(duid_, reply->getOption(D6O_IA_PD), prefix_opt);
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

void
Dhcpv6SrvTest::testRenewReject(Lease::Type type, const IOAddress& addr) {

    NakedDhcpv6Srv srv(0);

    const uint32_t transid = 1234;
    const uint32_t valid_iaid = 234;
    const uint32_t bogus_iaid = 456;

    uint32_t code;
    uint8_t prefix_len;
    if (type == Lease::TYPE_NA) {
        code = D6O_IA_NA;
        prefix_len = 128;
    } else if (type == Lease::TYPE_PD) {
        code = D6O_IA_PD;
        prefix_len = pd_pool_->getLength();
    } else {
        isc_throw(BadValue, "Invalid lease type");
    }

    // Quick sanity check that the address we're about to use is ok
    ASSERT_TRUE(subnet_->inPool(type, addr));

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Check that the lease is NOT in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // Let's create a RENEW
    Pkt6Ptr req = createMessage(DHCPV6_RENEW, type, IOAddress(addr), prefix_len,
                                bogus_iaid);
    req->addOption(clientid);
    req->addOption(srv.getServerID());

    // Case 1: No lease known to server

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, transid);
    OptionPtr tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    // Check that there is no lease added
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               prefix_len));
    lease->cltt_ = 123; // Let's use it as an indicator that the lease
                        // was NOT updated.
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Pass it to the server and hope for a REPLY
    reply = srv.processRenew(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    // There is a iaid mis-match, so server should respond that there is
    // no such address to renew.

    // CASE 3: Lease belongs to a client with different client-id
    req->delOption(D6O_CLIENTID);
    ia = boost::dynamic_pointer_cast<Option6IA>(req->getOption(code));
    ia->setIAID(valid_iaid); // Now iaid in renew matches that in leasemgr
    req->addOption(generateClientId(13)); // generate different DUID
                                          // (with length 13)

    reply = srv.processRenew(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    lease = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_TRUE(lease);
    // Verify that the lease was not updated.
    EXPECT_EQ(123, lease->cltt_);

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

void
Dhcpv6SrvTest::testReleaseBasic(Lease::Type type, const IOAddress& existing,
                                const IOAddress& release_addr) {
    NakedDhcpv6Srv srv(0);

    const uint32_t iaid = 234;

    uint32_t code; // option code of the container (IA_NA or IA_PD)
    uint8_t prefix_len;
    if (type == Lease::TYPE_NA) {
        code = D6O_IA_NA;
        prefix_len = 128;
    } else if (type == Lease::TYPE_PD) {
        code = D6O_IA_PD;
        prefix_len = pd_pool_->getLength();
    } else {
        isc_throw(BadValue, "Invalid lease type");
    }

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(type, existing));

    // Let's prepopulate the database
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, existing, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               prefix_len));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(type, existing);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr rel = createMessage(DHCPV6_RELEASE, type, release_addr, prefix_len,
                                iaid);
    rel->addOption(clientid);
    rel->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(rel);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    checkIA_NAStatusCode(ia, STATUS_Success);
    checkMsgStatusCode(reply, STATUS_Success);

    // There should be no address returned in RELEASE (see RFC3315, 18.2.6)
    // There should be no prefix
    EXPECT_FALSE(tmp->getOption(D6O_IAADDR));
    EXPECT_FALSE(tmp->getOption(D6O_IAPREFIX));

    // Check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // Check that the lease is really gone in the database
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(type, release_addr);
    ASSERT_FALSE(l);

    // get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(type, *duid_, iaid,
                                              subnet_->getID());
    ASSERT_FALSE(l);
}

void
Dhcpv6SrvTest::testReleaseReject(Lease::Type type, const IOAddress& addr) {
    NakedDhcpv6Srv srv(0);

    const uint32_t transid = 1234;
    const uint32_t valid_iaid = 234;
    const uint32_t bogus_iaid = 456;

    uint32_t code; // option code of the container (IA_NA or IA_PD)
    uint8_t prefix_len;
    if (type == Lease::TYPE_NA) {
        code = D6O_IA_NA;
        prefix_len = 128;
    } else if (type == Lease::TYPE_PD) {
        code = D6O_IA_PD;
        prefix_len = pd_pool_->getLength();
    } else {
        isc_throw(BadValue, "Invalid lease type");
    }

    // Quick sanity check that the address we're about to use is ok
    ASSERT_TRUE(subnet_->inPool(type, addr));

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Check that the lease is NOT in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // Let's create a RELEASE
    Pkt6Ptr rel = createMessage(DHCPV6_RELEASE, type, addr, prefix_len, valid_iaid);
    rel->addOption(clientid);
    rel->addOption(srv.getServerID());

    // Case 1: No lease known to server
    SCOPED_TRACE("CASE 1: No lease known to server");

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(rel);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, transid);
    OptionPtr tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);
    // Check that IA_NA/IA_PD was returned and that there's status code in it
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is not there
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID
    SCOPED_TRACE("CASE 2: Lease is known and belongs to this client, but to a different IAID");

    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid, 501, 502, 503,
                               504, subnet_->getID(), prefix_len));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Let's create a different RELEASE, with a bogus iaid
    rel = createMessage(DHCPV6_RELEASE, type, addr, prefix_len, bogus_iaid);
    rel->addOption(clientid);
    rel->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    reply = srv.processRelease(rel);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_TRUE(l);

    // CASE 3: Lease belongs to a client with different client-id
    SCOPED_TRACE("CASE 3: Lease belongs to a client with different client-id");

    rel->delOption(D6O_CLIENTID);
    ia = boost::dynamic_pointer_cast<Option6IA>(rel->getOption(code));
    ia->setIAID(valid_iaid); // Now iaid in renew matches that in leasemgr
    rel->addOption(generateClientId(13)); // generate different DUID
                                          // (with length 13)

    reply = srv.processRelease(rel);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(code);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_TRUE(l);

    // Finally, let's cleanup the database
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

void
Dhcpv6SrvTest::configure(const std::string& config) {
    ElementPtr json = data::Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode);
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
