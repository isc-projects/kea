// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <asiolink/io_address.h>
#include <dhcp/lease_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

// This is a concrete implementation of a Lease database.
// It does not do anything useful now, and is used for abstract LeaseMgr
// class testing. It may later evolve into more useful backend if the
// need arises. We can reuse code from memfile benchmark. See code in
// tests/tools/dhcp-ubench/memfile_bench.{cc|h}
class Memfile_LeaseMgr : public LeaseMgr {
public:

    /// @brief The sole lease manager constructor
    ///
    /// dbconfig is a generic way of passing parameters. Parameters
    /// are passed in the "name=value" format, separated by spaces.
    /// Values may be enclosed in double quotes, if needed.
    ///
    /// @param dbconfig database configuration
    Memfile_LeaseMgr(const std::string& dbconfig);

    /// @brief Destructor (closes file)
    virtual ~Memfile_LeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease4Ptr lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    virtual bool addLease(Lease6Ptr lease);

    /// @brief Returns existing IPv4 lease for specified IPv4 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(isc::asiolink::IOAddress addr) const;

    /// @brief Returns existing IPv4 lease for specified hardware address.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// @param clientid client identifier
    virtual Lease4Ptr getLease4(const ClientId& clientid) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getLease6(isc::asiolink::IOAddress addr) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    Lease6Ptr getLease6(const DUID& duid, uint32_t iaid) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    void updateLease4(Lease4Ptr lease4);

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    void updateLease6(Lease6Ptr lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease4(uint32_t addr);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    bool deleteLease6(isc::asiolink::IOAddress addr);

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name, e.g. "mysql" or "sqlite".
    std::string getName() const { return "memfile"; }

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    std::string getDescription() const;

    /// @brief Returns backend version.
    std::string getVersion() const { return "test-version"; }

    using LeaseMgr::getParameter;

protected:


};

Memfile_LeaseMgr::Memfile_LeaseMgr(const std::string& dbconfig)
    : LeaseMgr(dbconfig) {
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
}

bool Memfile_LeaseMgr::addLease(boost::shared_ptr<isc::dhcp::Lease4>) {
    return (false);
}

bool Memfile_LeaseMgr::addLease(boost::shared_ptr<isc::dhcp::Lease6>) {
    return (false);
}

Lease4Ptr Memfile_LeaseMgr::getLease4(isc::asiolink::IOAddress) const {
    return (Lease4Ptr());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const HWAddr& ) const {
    return (Lease4Ptr());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const ClientId& ) const {
    return (Lease4Ptr());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(isc::asiolink::IOAddress) const {
    return (Lease6Ptr());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(const DUID& , uint32_t ) const {
    return (Lease6Ptr());
}

void Memfile_LeaseMgr::updateLease4(Lease4Ptr ) {
}

void Memfile_LeaseMgr::updateLease6(Lease6Ptr ) {

}

bool Memfile_LeaseMgr::deleteLease4(uint32_t ) {
    return (false);
}

bool Memfile_LeaseMgr::deleteLease6(isc::asiolink::IOAddress ) {
    return (false);
}

std::string Memfile_LeaseMgr::getDescription() const {
    return (string("This is a dummy memfile backend implementation.\n"
                   "It does not offer any useful lease management and its only\n"
                   "purpose is to test abstract lease manager API."));
}

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class LeaseMgrTest : public ::testing::Test {
public:
    LeaseMgrTest() {
    }
};

TEST_F(LeaseMgrTest, constructor) {

    // should not throw any exceptions here
    Memfile_LeaseMgr * leaseMgr = new Memfile_LeaseMgr("");
    delete leaseMgr;

    leaseMgr = new Memfile_LeaseMgr("param1=value1 param2=value2");

    EXPECT_EQ("value1", leaseMgr->getParameter("param1"));
    EXPECT_EQ("value2", leaseMgr->getParameter("param2"));
    EXPECT_THROW(leaseMgr->getParameter("param3"), BadValue);

    delete leaseMgr;
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call Memfile_LeaseMgr methods.

}; // end of anonymous namespace
