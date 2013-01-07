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

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

// This is a concrete implementation of a Lease database.  It does not do
// anything useful and is used for abstract LeaseMgr class testing.
class ConcreteLeaseMgr : public LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ConcreteLeaseMgr(const LeaseMgr::ParameterMap& parameters)
        : LeaseMgr(parameters)
    {}

    /// @brief Destructor
    virtual ~ConcreteLeaseMgr()
    {}

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease4Ptr&) {
        return (false);
    }

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(const Lease6Ptr&) {
        return (false);
    }

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress&) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv4 leases for specified hardware address.
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const HWAddr&) const {
        return (Lease4Collection());
    }

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr&, SubnetID) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId&) const {
        return (Lease4Collection());
    }

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId&, SubnetID) const {
        return (Lease4Ptr());
    }

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const isc::asiolink::IOAddress&) const {
        return (Lease6Ptr());
    }

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return collection of IPv6 leases
    virtual Lease6Collection getLease6(const DUID&, uint32_t) const {
        return (Lease6Collection());
    }

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id identifier of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const DUID&, uint32_t, SubnetID) const {
        return (Lease6Ptr());
    }

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr&) {}

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr&) {}

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted. (This can be either
    ///        a V4 address or a V6 address.)
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease(const isc::asiolink::IOAddress&) {
        return (false);
    }

    /// @brief Returns backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("concrete"));
    }

    /// @brief Returns backend name.
    ///
    /// If the backend is a database, this is the name of the database or the
    /// file.  Otherwise it is just the same as the type.
    ///
    /// @return Name of the backend.
    virtual std::string getName() const {
        return (std::string("concrete"));
    }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const {
        return (std::string("This is a dummy concrete backend implementation."));
    }

    /// @brief Returns backend version.
    virtual std::pair<uint32_t, uint32_t> getVersion() const {
        return (make_pair(uint32_t(0), uint32_t(0)));
    }

    /// @brief Commit transactions
    virtual void commit() {
    }

    /// @brief Rollback transactions
    virtual void rollback() {
    }
};

namespace {

/// @brief getParameter test
///
/// This test checks if the LeaseMgr can be instantiated and that it
/// parses parameters string properly.
TEST(LeaseMgr, getParameter) {

    LeaseMgr::ParameterMap pmap;
    pmap[std::string("param1")] = std::string("value1");
    pmap[std::string("param2")] = std::string("value2");
    ConcreteLeaseMgr leasemgr(pmap);

    EXPECT_EQ("value1", leasemgr.getParameter("param1"));
    EXPECT_EQ("value2", leasemgr.getParameter("param2"));
    EXPECT_THROW(leasemgr.getParameter("param3"), BadValue);
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call ConcreteLeaseMgr methods.
// Those methods are just stubs that do not return anything.

/// @brief Lease4 Constructor Test
///
/// Lease4 is also defined in lease_mgr.h, so is tested in this file as well.
// This test checks if the Lease4 structure can be instantiated correctly
TEST(Lease4, Lease4Constructor) {

    // Random values for the tests
    const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
    std::vector<uint8_t> hwaddr(HWADDR, HWADDR + sizeof(HWADDR));

    const uint8_t CLIENTID[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};
    std::vector<uint8_t> clientid_vec(CLIENTID, CLIENTID + sizeof(CLIENTID));
    ClientId clientid(clientid_vec);

    // ...and a time
    const time_t current_time = time(NULL);

    // Other random constants.
    const uint32_t SUBNET_ID = 42;
    const uint32_t VALID_LIFETIME = 500;

    // We want to check that various addresses work, so let's iterate over
    // these.
    const uint32_t ADDRESS[] = {
        0x00000000, 0x01020304, 0x7fffffff, 0x80000000, 0x80000001, 0xffffffff
    };

    for (int i = 0; i < sizeof(ADDRESS) / sizeof(ADDRESS[0]); ++i) {

        // Create the lease
        Lease4 lease(ADDRESS[i], HWADDR, sizeof(HWADDR),
                     CLIENTID, sizeof(CLIENTID), VALID_LIFETIME, current_time,
                     SUBNET_ID);

        EXPECT_EQ(ADDRESS[i], static_cast<uint32_t>(lease.addr_));
        EXPECT_EQ(0, lease.ext_);
        EXPECT_TRUE(hwaddr == lease.hwaddr_);
        EXPECT_TRUE(clientid == *lease.client_id_);
        EXPECT_EQ(0, lease.t1_);
        EXPECT_EQ(0, lease.t2_);
        EXPECT_EQ(VALID_LIFETIME, lease.valid_lft_);
        EXPECT_EQ(current_time, lease.cltt_);
        EXPECT_EQ(SUBNET_ID, lease.subnet_id_);
        EXPECT_FALSE(lease.fixed_);
        EXPECT_TRUE(lease.hostname_.empty());
        EXPECT_FALSE(lease.fqdn_fwd_);
        EXPECT_FALSE(lease.fqdn_rev_);
        EXPECT_TRUE(lease.comments_.empty());
    }
}

/// @brief Lease4 Equality Test
///
/// Checks that the operator==() correctly compares two leases for equality.
/// As operator!=() is also defined for this class, every check on operator==()
/// is followed by the reverse check on operator!=().
TEST(Lease4, OperatorEquals) {

    // Random values for the tests
    const uint32_t ADDRESS = 0x01020304;
    const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
    std::vector<uint8_t> hwaddr(HWADDR, HWADDR + sizeof(HWADDR));
    const uint8_t CLIENTID[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};
    std::vector<uint8_t> clientid_vec(CLIENTID, CLIENTID + sizeof(CLIENTID));
    ClientId clientid(clientid_vec);
    const time_t current_time = time(NULL);
    const uint32_t SUBNET_ID = 42;
    const uint32_t VALID_LIFETIME = 500;

    // Check when the leases are equal.
    Lease4 lease1(ADDRESS, HWADDR, sizeof(HWADDR),
                  CLIENTID, sizeof(CLIENTID), VALID_LIFETIME, current_time,
                  SUBNET_ID);
    Lease4 lease2(ADDRESS, HWADDR, sizeof(HWADDR),
                  CLIENTID, sizeof(CLIENTID), VALID_LIFETIME, current_time,
                  SUBNET_ID);
    EXPECT_TRUE(lease1 == lease2);
    EXPECT_FALSE(lease1 != lease2);

    // Now vary individual fields in a lease and check that the leases compare
    // not equal in every case.
    lease1.addr_ = IOAddress(ADDRESS + 1);
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.addr_ = lease2.addr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.ext_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.ext_ = lease2.ext_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.hwaddr_[0];
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hwaddr_ = lease2.hwaddr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++clientid_vec[0];
    lease1.client_id_.reset(new ClientId(clientid_vec));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    --clientid_vec[0];
    lease1.client_id_.reset(new ClientId(clientid_vec));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.t1_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.t1_ = lease2.t1_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.t2_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.t2_ = lease2.t2_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.valid_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.valid_lft_ = lease2.valid_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.cltt_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.cltt_ = lease2.cltt_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.subnet_id_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.subnet_id_ = lease2.subnet_id_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fixed_ = !lease1.fixed_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fixed_ = lease2.fixed_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.hostname_ += string("Something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hostname_ = lease2.hostname_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_fwd_ = !lease1.fqdn_fwd_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_fwd_ = lease2.fqdn_fwd_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_rev_ = !lease1.fqdn_rev_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_rev_ = lease2.fqdn_rev_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.comments_ += string("Something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.comments_ = lease2.comments_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal
}



// Lease6 is also defined in lease_mgr.h, so is tested in this file as well.
// This test checks if the Lease6 structure can be instantiated correctly
TEST(Lease6, Lease6Constructor) {

    // check a variety of addresses with different bits set.
    const char* ADDRESS[] = {
        "::", "::1", "2001:db8:1::456",
        "7fff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
        "8000::", "8000::1",
        "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"
    };

    // Other values
    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));
    uint32_t iaid = 7; // just a number
    SubnetID subnet_id = 8; // just another number

    for (int i = 0; i < sizeof(ADDRESS) / sizeof(ADDRESS[0]); ++i) {
        IOAddress addr(ADDRESS[i]);
        Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr,
                               duid, iaid, 100, 200, 50, 80,
                               subnet_id));

        EXPECT_TRUE(lease->addr_ == addr);
        EXPECT_TRUE(*lease->duid_ == *duid);
        EXPECT_TRUE(lease->iaid_ == iaid);
        EXPECT_TRUE(lease->subnet_id_ == subnet_id);
        EXPECT_TRUE(lease->type_ == Lease6::LEASE_IA_NA);
        EXPECT_TRUE(lease->preferred_lft_ == 100);
        EXPECT_TRUE(lease->valid_lft_ == 200);
        EXPECT_TRUE(lease->t1_ == 50);
        EXPECT_TRUE(lease->t2_ == 80);
    }

    // Lease6 must be instantiated with a DUID, not with NULL pointer
    IOAddress addr(ADDRESS[0]);
    EXPECT_THROW(new Lease6(Lease6::LEASE_IA_NA, addr,
                            DuidPtr(), iaid, 100, 200, 50, 80,
                            subnet_id), InvalidOperation);
}

/// @brief Lease6 Equality Test
///
/// Checks that the operator==() correctly compares two leases for equality.
/// As operator!=() is also defined for this class, every check on operator==()
/// is followed by the reverse check on operator!=().
TEST(Lease6, OperatorEquals) {

    // check a variety of addressemas with different bits set.
    const IOAddress addr("2001:db8:1::456");
    uint8_t duid_array[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(duid_array, sizeof(duid_array)));
    uint32_t iaid = 7; // just a number
    SubnetID subnet_id = 8; // just another number

    // Check for equality.
    Lease6 lease1(Lease6::LEASE_IA_NA, addr, duid, iaid, 100, 200, 50, 80,
                               subnet_id);
    Lease6 lease2(Lease6::LEASE_IA_NA, addr, duid, iaid, 100, 200, 50, 80,
                               subnet_id);
    EXPECT_TRUE(lease1 == lease2);
    EXPECT_FALSE(lease1 != lease2);

    // Go through and alter all the fields one by one

    lease1.addr_ = IOAddress("::1");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.addr_ = lease2.addr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.type_ = Lease6::LEASE_IA_PD;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.type_ = lease2.type_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.prefixlen_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.prefixlen_ = lease2.prefixlen_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.iaid_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.iaid_ = lease2.iaid_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++duid_array[0];
    lease1.duid_.reset(new DUID(duid_array, sizeof(duid_array)));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    --duid_array[0];
    lease1.duid_.reset(new DUID(duid_array, sizeof(duid_array)));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.preferred_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.preferred_lft_ = lease2.preferred_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.valid_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.valid_lft_ = lease2.valid_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.t1_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.t1_ = lease2.t1_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.t2_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.t2_ = lease2.t2_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.cltt_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.cltt_ = lease2.cltt_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.subnet_id_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.subnet_id_ = lease2.subnet_id_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fixed_ = !lease1.fixed_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fixed_ = lease2.fixed_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.hostname_ += string("Something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hostname_ = lease2.hostname_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_fwd_ = !lease1.fqdn_fwd_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_fwd_ = lease2.fqdn_fwd_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_rev_ = !lease1.fqdn_rev_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_rev_ = lease2.fqdn_rev_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.comments_ += string("Something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.comments_ = lease2.comments_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal
}

// Checks if lease expiration is calculated properly
TEST(Lease6, Lease6Expired) {
    const IOAddress addr("2001:db8:1::456");
    const uint8_t duid_array[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    const DuidPtr duid(new DUID(duid_array, sizeof(duid_array)));
    const uint32_t iaid = 7; // just a number
    const SubnetID subnet_id = 8; // just another number
    Lease6 lease(Lease6::LEASE_IA_NA, addr, duid, iaid, 100, 200, 50, 80,
                               subnet_id);

    // case 1: a second before expiration
    lease.cltt_ = time(NULL) - 100;
    lease.valid_lft_ = 101;
    EXPECT_FALSE(lease.expired());

    // case 2: the lease will expire after this second is concluded
    lease.cltt_ = time(NULL) - 101;
    EXPECT_FALSE(lease.expired());

    // case 3: the lease is expired
    lease.cltt_ = time(NULL) - 102;
    EXPECT_TRUE(lease.expired());
}

}; // end of anonymous namespace
