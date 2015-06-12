// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_status_code.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/json_config_parser.h>
#include <util/pointer_util.h>
#include <cc/command_interpreter.h>
#include <string.h>

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

    isc::dhcp::CfgMgr::instance().clear();
    isc::dhcp::CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet_);
    isc::dhcp::CfgMgr::instance().commit();

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
// and is valid when checked against the configured subnet
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

    EXPECT_TRUE(util::nullOrEqualValues(lease_db->hwaddr_, lease.hwaddr_));
    EXPECT_TRUE(util::nullOrEqualValues(lease_db->duid_, lease.duid_));

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
                              const uint8_t prefix_len, bool insert_before_renew) {
    NakedDhcpv6Srv srv(0);

    const IOAddress existing(existing_addr);
    const IOAddress renew(renew_addr);
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(type, existing));

    Lease6Ptr l;
    if (insert_before_renew) {
        // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
        // value on purpose. They should be updated during RENEW.
        Lease6Ptr lease(new Lease6(type, existing, duid_, iaid, 501, 502, 503, 504,
                                   subnet_->getID(), HWAddrPtr(), prefix_len));
        lease->cltt_ = 1234;
        ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

        // Check that the lease is really in the database
        l = LeaseMgrFactory::instance().getLease6(type, existing);
        ASSERT_TRUE(l);

        // Check that T1, T2, preferred, valid and cltt really set and not using
        // previous (500, 501, etc.) values
        EXPECT_NE(l->t1_, subnet_->getT1());
        EXPECT_NE(l->t2_, subnet_->getT2());
        EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
        EXPECT_NE(l->valid_lft_, subnet_->getValid());
        EXPECT_NE(l->cltt_, time(NULL));
    }

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
        l = checkPdLease(duid_, reply->getOption(D6O_IA_PD), prefix_opt);
        ASSERT_TRUE(l);
        break;
    }
    default:
        isc_throw(BadValue, "Invalid lease type");
    }

    // Check that T1, T2, preferred, valid and cltt were really updated
    EXPECT_EQ(subnet_->getT1(), l->t1_);
    EXPECT_EQ(subnet_->getT2(), l->t2_);
    EXPECT_EQ(subnet_->getPreferred(), l->preferred_lft_);
    EXPECT_EQ(subnet_->getValid(), l->valid_lft_);

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(renew_addr));
}

void
Dhcpv6SrvTest::testRenewWrongIAID(Lease::Type type, const IOAddress& addr) {

    NakedDhcpv6Srv srv(0);

    const uint32_t transid = 1234;
    const uint32_t valid_iaid = 234;
    const uint32_t bogus_iaid = 456;

    uint8_t prefix_len = (type == Lease::TYPE_PD) ? 128 : pd_pool_->getLength();

    // Quick sanity check that the address we're about to use is ok
    ASSERT_TRUE(subnet_->inPool(type, addr));

    // Check that the lease is NOT in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), prefix_len));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Pass it to the server and hope for a REPLY
    // Let's create a RENEW
    Pkt6Ptr renew = createMessage(DHCPV6_RENEW, type, IOAddress(addr), prefix_len,
                                  bogus_iaid);
    renew->addOption(clientid);
    renew->addOption(srv.getServerID());

    // The duid and address matches, but the iaid is different. The server could
    // respond with NoBinding. However, according to
    // draft-ietf-dhc-dhcpv6-stateful-issues-10, the server can also assign a
    // new address. And that's what we expect here.
    Pkt6Ptr reply = srv.processRenew(renew);
    checkResponse(reply, DHCPV6_REPLY, transid);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr>
        addr_opt = checkIA_NA(reply, bogus_iaid, subnet_->getT1(), subnet_->getT2());

    ASSERT_TRUE(addr_opt);

    // Check that we've got the an address
    checkIAAddr(addr_opt, addr_opt->getAddress(), Lease::TYPE_NA);

    // Check that we got a different address than was in the database.
    EXPECT_NE(addr_opt->getAddress().toText(), addr.toText());

    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);
}

void
Dhcpv6SrvTest::testRenewSomeoneElsesLease(Lease::Type type, const IOAddress& addr) {

    NakedDhcpv6Srv srv(0);
    const uint32_t valid_iaid = 234;
    const uint32_t transid = 1234;

    uint8_t prefix_len = (type == Lease::TYPE_PD) ? 128 : pd_pool_->getLength();

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Let's create a lease.
    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), prefix_len));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // CASE 3: Lease belongs to a client with different client-id
    Pkt6Ptr renew = createMessage(DHCPV6_RENEW, type, IOAddress(addr), prefix_len,
                                  valid_iaid);
    renew->addOption(generateClientId(13)); // generate different DUID (length 13)
    renew->addOption(srv.getServerID());

    // The iaid and address matches, but the duid is different.
    // The server should not renew it, but assign something else.
    Pkt6Ptr reply = srv.processRenew(renew);
    checkResponse(reply, DHCPV6_REPLY, transid);
    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_?? was returned and that there's proper status code
    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr>
        addr_opt = checkIA_NA(reply, valid_iaid, subnet_->getT1(), subnet_->getT2());

    ASSERT_TRUE(addr_opt);

    // Check that we've got the an address
    checkIAAddr(addr_opt, addr_opt->getAddress(), Lease::TYPE_NA);

    // Check that we got a different address than was in the database.
    EXPECT_NE(addr_opt->getAddress().toText(), addr.toText());

    // Check that the lease is really in the database
    Lease6Ptr l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);
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

    if (type == Lease::TYPE_PD) {
        // For PD, the check is easy. NoBinding and no prefixes
        checkIA_NAStatusCode(ia, STATUS_NoBinding, subnet_->getT1(), subnet_->getT2());
    } else {
        // For IA, it's more involved, as the server will reject the address
        // (and send it with 0 lifetimes), but will also assign a new address.

        // First, check that the requested address is rejected.
        bool found = false;

        dhcp::OptionCollection options = ia->getOptions();
        for (isc::dhcp::OptionCollection::iterator opt = options.begin();
             opt != options.end(); ++opt) {
            if (opt->second->getType() != D6O_IAADDR) {
                continue;
            }

            dhcp::Option6IAAddrPtr opt_addr =
                boost::dynamic_pointer_cast<isc::dhcp::Option6IAAddr>(opt->second);
            ASSERT_TRUE(opt_addr);

            if (opt_addr->getAddress() != addr) {
                // There may be other addresses, e.g. the newly assigned one
                continue;
            }

            found = true;
            EXPECT_NE(0, opt_addr->getPreferred());
            EXPECT_NE(0, opt_addr->getValid());
        }

        EXPECT_TRUE(found) << "Expected address " << addr.toText()
                           << " with zero lifetimes not found.";
    }

    // Check that there is no lease added
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), prefix_len));
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
    checkIA_NAStatusCode(ia, STATUS_NoBinding, subnet_->getT1(), subnet_->getT2());

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
    checkIA_NAStatusCode(ia, STATUS_NoBinding, subnet_->getT1(), subnet_->getT2());

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
    Lease6Ptr lease(new Lease6(type, existing, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), prefix_len));
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
    checkIA_NAStatusCode(ia, STATUS_Success, 0, 0);
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
    checkIA_NAStatusCode(ia, STATUS_NoBinding, 0, 0);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is not there
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID
    SCOPED_TRACE("CASE 2: Lease is known and belongs to this client, but to a different IAID");

    Lease6Ptr lease(new Lease6(type, addr, duid_, valid_iaid, 501, 502, 503,
                               504, subnet_->getID(), HWAddrPtr(), prefix_len));
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
    checkIA_NAStatusCode(ia, STATUS_NoBinding, 0, 0);
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
    checkIA_NAStatusCode(ia, STATUS_NoBinding, 0, 0);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease6(type, addr);
    ASSERT_TRUE(l);

    // Finally, let's cleanup the database
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

void
Dhcpv6SrvTest::configure(const std::string& config) {
    configure(config, srv_);
}

void
Dhcpv6SrvTest::configure(const std::string& config, NakedDhcpv6Srv& srv) {
    ElementPtr json = data::Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(srv, json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = isc::config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode);

    CfgMgr::instance().commit();
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

bool
Dhcpv6SrvTest::compareOptions(const isc::dhcp::OptionPtr& option1,
                              const isc::dhcp::OptionPtr& option2) {
    if ((!option1 && option2) || (option1 && !option2)) {
        return (false);
    }
    if (!option1 && !option2) {
        return (true);
    }

    // We could start by comparing option codes and option lengths
    // here, but it's just a waste of time. These are tests, so they
    // don't have to be super performant. The pack+memcmp approach
    // verifies all in one go.

    isc::util::OutputBuffer buf1(0);
    isc::util::OutputBuffer buf2(0);

    option1->pack(buf1);
    option2->pack(buf2);

    if (buf1.getLength() != buf2.getLength()) {
        return (false);
    }

    // memcmp returns 0 when equal.
    return (!memcmp(buf1.getData(), buf2.getData(), buf1.getLength()));
}

void
NakedDhcpv6SrvTest::checkIA_NAStatusCode(
    const boost::shared_ptr<isc::dhcp::Option6IA>& ia,
    uint16_t expected_status_code, uint32_t expected_t1, uint32_t expected_t2,
    bool check_addr)
{
    // Make sure there is no address assigned. Depending on the situation,
    // the server will either not return the address at all and sometimes
    // it will return it with zeroed lifetimes.
    if (check_addr) {
        dhcp::OptionCollection options = ia->getOptions();
        for (isc::dhcp::OptionCollection::iterator opt = options.begin();
             opt != options.end(); ++opt) {
            if (opt->second->getType() != D6O_IAADDR) {
                continue;
            }

            dhcp::Option6IAAddrPtr addr =
                boost::dynamic_pointer_cast<isc::dhcp::Option6IAAddr>(opt->second);
            ASSERT_TRUE(addr);

            EXPECT_EQ(0, addr->getPreferred());
            EXPECT_EQ(0, addr->getValid());
        }
    }

    // T1, T2 should NOT be zeroed. draft-ietf-dhc-dhcpv6-stateful-issues-10,
    // section 4.4.6 says says that T1,T2 should be consistent along all
    // provided IA options.
    EXPECT_EQ(expected_t1, ia->getT1());
    EXPECT_EQ(expected_t2, ia->getT2());

    isc::dhcp::Option6StatusCodePtr status =
        boost::dynamic_pointer_cast<isc::dhcp::Option6StatusCode>
        (ia->getOption(D6O_STATUS_CODE));

    // It is ok to not include status success as this is the default
    // behavior
    if (expected_status_code == STATUS_Success && !status) {
        return;
    }

    EXPECT_TRUE(status);

    if (status) {
        // We don't have dedicated class for status code, so let's
        // just interpret first 2 bytes as status. Remainder of the
        // status code option content is just a text explanation
        // what went wrong.
        EXPECT_EQ(static_cast<uint16_t>(expected_status_code),
                  status->getStatusCode());
    }
}

}; // end of isc::test namespace
}; // end of isc namespace
