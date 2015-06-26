// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/duid.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <stats/stats_mgr.h>

#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>

#include <hooks/hooks_manager.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;
using namespace isc::stats;

namespace isc {
namespace dhcp {
namespace test {

AllocEngine6Test::AllocEngine6Test() {
    CfgMgr::instance().clear();

    duid_ = DuidPtr(new DUID(std::vector<uint8_t>(8, 0x42)));
    iaid_ = 42;

    // Let's use odd hardware type to check if there is no Ethernet
    // hardcoded anywhere.
    const uint8_t mac[] = { 0, 1, 22, 33, 44, 55};
    hwaddr_ = HWAddrPtr(new HWAddr(mac, sizeof(mac), HTYPE_FDDI));

    // Initialize a subnet and short address pool.
    initSubnet(IOAddress("2001:db8:1::"),
               IOAddress("2001:db8:1::10"),
               IOAddress("2001:db8:1::20"));

    initFqdn("", false, false);

    factory_.create("type=memfile universe=6 persist=false");
}

void
AllocEngine6Test::initSubnet(const asiolink::IOAddress& subnet,
                    const asiolink::IOAddress& pool_start,
                    const asiolink::IOAddress& pool_end) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    subnet_ = Subnet6Ptr(new Subnet6(subnet, 56, 100, 200, 300, 400));
    pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, pool_start, pool_end));

    subnet_->addPool(pool_);

    pd_pool_ = Pool6Ptr(new Pool6(Lease::TYPE_PD, subnet, 56, 64));
    subnet_->addPool(pd_pool_);

    cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet_);
    cfg_mgr.commit();

    // By default we pretend our subnet has 100 addresses and prefixes allocated.
    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas"),
        static_cast<int64_t>(100));
    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_->getID(), "assigned-pds"),
        static_cast<int64_t>(100));
}

void
AllocEngine6Test::findReservation(AllocEngine& engine,
    AllocEngine::ClientContext6& ctx) {
    engine.findReservation(ctx);
    // Let's check whether there's a hostname specified in the reservation
    if (ctx.host_) {
        std::string hostname = ctx.host_->getHostname();
        // If there is, let's use it
        if (!hostname.empty()) {
            ctx.hostname_ = hostname;
        }
    }
}

HostPtr
AllocEngine6Test::createHost6HWAddr(bool add_to_host_mgr, IPv6Resrv::Type type,
                                    HWAddrPtr& hwaddr, const asiolink::IOAddress& addr,
                                    uint8_t prefix_len) {
    HostPtr host(new Host(&hwaddr->hwaddr_[0], hwaddr->hwaddr_.size(),
                          Host::IDENT_HWADDR, SubnetID(0), subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    IPv6Resrv resv(type, addr, prefix_len);
    host->addReservation(resv);

    if (add_to_host_mgr) {
        CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
        CfgMgr::instance().commit();
    }
    return (host);
}

Lease6Collection
AllocEngine6Test::allocateTest(AllocEngine& engine, const Pool6Ptr& pool,
                               const asiolink::IOAddress& hint, bool fake,
                               bool in_pool) {
    Lease::Type type = pool->getType();
    uint8_t expected_len = pool->getLength();

    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type,
                                    false, false, "", fake);
    ctx.query_.reset(new Pkt6(fake ? DHCPV6_SOLICIT : DHCPV6_REQUEST, 1234));

    Lease6Collection leases;

    findReservation(engine, ctx);
    EXPECT_NO_THROW(leases = engine.allocateLeases6(ctx));

    for (Lease6Collection::iterator it = leases.begin(); it != leases.end(); ++it) {

        // Do all checks on the lease
        checkLease6(*it, type, expected_len, in_pool, in_pool);

        // Check that the lease is indeed in LeaseMgr
        Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type,
                                                                   (*it)->addr_);
        if (!fake) {
            // This is a real (REQUEST) allocation, the lease must be in the DB
            EXPECT_TRUE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                                  << " returned by allocateLeases6(), "
                                  << "but was not present in LeaseMgr";
            if (!from_mgr) {
                return (leases);
            }

            // Now check that the lease in LeaseMgr has the same parameters
            detailCompareLease(*it, from_mgr);
        } else {
            // This is a fake (SOLICIT) allocation, the lease must not be in DB
            EXPECT_FALSE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                                   << " returned by allocateLeases6(), "
                                   << "was present in LeaseMgr (expected to be"
                                   << " not present)";
            if (from_mgr) {
                return (leases);
            }
        }
    }

    return (leases);
}

Lease6Ptr
AllocEngine6Test::simpleAlloc6Test(const Pool6Ptr& pool, const IOAddress& hint,
                                   bool fake, bool in_pool) {
    Lease::Type type = pool->getType();
    uint8_t expected_len = pool->getLength();

    boost::scoped_ptr<AllocEngine> engine;
    EXPECT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100)));
    // We can't use ASSERT macros in non-void methods
    EXPECT_TRUE(engine);
    if (!engine) {
        return (Lease6Ptr());
    }

    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type,
                                    false, false, "", fake);
    ctx.hwaddr_ = hwaddr_;
    ctx.query_.reset(new Pkt6(fake ? DHCPV6_SOLICIT : DHCPV6_REQUEST, 1234));

    findReservation(*engine, ctx);
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that we got a lease
    EXPECT_TRUE(lease);
    if (!lease) {
        return (Lease6Ptr());
    }

    // Do all checks on the lease
    checkLease6(lease, type, expected_len, in_pool, in_pool);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type, lease->addr_);
    if (!fake) {
        // This is a real (REQUEST) allocation, the lease must be in the DB
        EXPECT_TRUE(from_mgr);
        if (!from_mgr) {
            return (Lease6Ptr());
        }

        // Now check that the lease in LeaseMgr has the same parameters
        detailCompareLease(lease, from_mgr);
    } else {
        // This is a fake (SOLICIT) allocation, the lease must not be in DB
        EXPECT_FALSE(from_mgr);
        if (from_mgr) {
            return (Lease6Ptr());
        }
    }

    return (lease);
}

Lease6Collection
AllocEngine6Test::renewTest(AllocEngine& engine, const Pool6Ptr& pool,
                            AllocEngine::HintContainer& hints,
                            bool allow_new_leases_in_renewal,
                            bool in_pool) {

    Lease::Type type = pool->getType();
    uint8_t expected_len = pool->getLength();

    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    type, false, false, "", false);
    ctx.hints_ = hints;
    ctx.query_.reset(new Pkt6(DHCPV6_RENEW, 123));
    ctx.allow_new_leases_in_renewals_ = allow_new_leases_in_renewal;
    ctx.query_.reset(new Pkt6(DHCPV6_RENEW, 1234));

    findReservation(engine, ctx);
    Lease6Collection leases = engine.renewLeases6(ctx);

    for (Lease6Collection::iterator it = leases.begin(); it != leases.end(); ++it) {

        // Do all checks on the lease
        checkLease6(*it, type, expected_len, in_pool, in_pool);

        // Check that the lease is indeed in LeaseMgr
        Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type,
                                                                   (*it)->addr_);

        // This is a real (REQUEST) allocation, the lease must be in the DB
        EXPECT_TRUE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                              << " returned by allocateLeases6(), "
                              << "but was not present in LeaseMgr";
        if (!from_mgr) {
            return (leases);
        }

        // Now check that the lease in LeaseMgr has the same parameters
        detailCompareLease(*it, from_mgr);
    }

    return (leases);
}

void
AllocEngine6Test::allocWithUsedHintTest(Lease::Type type, IOAddress used_addr,
                                        IOAddress requested,
                                        uint8_t expected_pd_len) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Let's create a lease and put it in the LeaseMgr
    DuidPtr duid2 = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xff)));
    time_t now = time(NULL);
    Lease6Ptr used(new Lease6(type, used_addr,
                              duid2, 1, 2, 3, 4, now, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, requested, type,
                                    false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Allocated address must be different
    EXPECT_NE(used_addr, lease->addr_);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE(requested, lease->addr_);

    // Do all checks on the lease
    checkLease6(lease, type, expected_pd_len);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

void
AllocEngine6Test::allocBogusHint6(Lease::Type type, asiolink::IOAddress hint,
                                  uint8_t expected_pd_len) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Client would like to get a 3000::abc lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type, false,
                                    false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE(hint, lease->addr_);

    // Do all checks on the lease
    checkLease6(lease, type, expected_pd_len);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

void
AllocEngine4Test::initSubnet(const asiolink::IOAddress& pool_start,
                             const asiolink::IOAddress& pool_end) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(pool_start, pool_end));
    subnet_->addPool(pool_);

    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);
}

AllocEngine4Test::AllocEngine4Test() {
    // Create fresh instance of the HostMgr, and drop any previous HostMgr state.
    HostMgr::instance().create();

    clientid_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x44)));
    clientid2_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x56)));

    uint8_t mac[] = { 0, 1, 22, 33, 44, 55};

    // Let's use odd hardware type to check if there is no Ethernet
    // hardcoded anywhere.
    hwaddr_ = HWAddrPtr(new HWAddr(mac, sizeof(mac), HTYPE_FDDI));

    // Allocate different MAC address for the tests that require two
    // different MAC addresses.
    ++mac[sizeof(mac) - 1];
    hwaddr2_ = HWAddrPtr(new HWAddr(mac, sizeof (mac), HTYPE_FDDI));

    // instantiate cfg_mgr
    CfgMgr& cfg_mgr = CfgMgr::instance();

    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.109"));
    cfg_mgr.commit();

    factory_.create("type=memfile universe=4 persist=false");

    // Create a default context. Note that remaining parameters must be
    // assigned when needed.
    ctx_.subnet_ = subnet_;
    ctx_.clientid_ = clientid_;
    ctx_.hwaddr_ = hwaddr_;
    ctx_.callout_handle_ = HooksManager::createCalloutHandle();
    ctx_.query_.reset(new Pkt4(DHCPREQUEST, 1234));
}

}; // namespace test
}; // namespace dhcp
}; // namespace isc
