// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/lease_file_loader.h>
#include <dhcpsrv/tests/lease_file_io.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for @c LeaseFileLoader class.
class LeaseFileLoaderTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Initializes filename used for unit tests and creates an
    /// IO object to be used to write to this file.
    LeaseFileLoaderTest();

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    /// @brief Retrieves the lease from the storage using an IP address.
    ///
    /// This method returns the pointer to the @c Lease4 or @c Lease6
    /// object representing the lease in the container. This is used to
    /// check if the lease was parsed in the lease file and added to the
    /// container by the @c LeaseFileLoader::load method.
    ///
    /// @param address A string representation of the leased address.
    /// @param storage A reference to the container in which the lease
    /// is to be searched.
    /// @tparam LeasePtrType Type of the returned object: @c Lease4Ptr
    /// @c Lease6Ptr.
    /// @tparam LeaseStorage Type of the container: @c Lease4Container
    /// @c Lease6Container.
    ///
    /// @return A pointer to the lease or NULL if no lease found.
    template<typename LeasePtrType, typename LeaseStorage>
    static LeasePtrType getLease(const std::string& address, const LeaseStorage& storage) {
        typedef typename LeaseStorage::template nth_index<0>::type SearchIndex;
        // Both Lease4Storage and Lease6Storage use index 0 to retrieve the
        // lease using an IP address.
        const SearchIndex& idx = storage.template get<0>();
        typename SearchIndex::iterator lease = idx.find(IOAddress(address));
        // Lease found. Return it.
        if (lease != idx.end()) {
            return (*lease);
        }
        // No lease found.
        return (LeasePtrType());
    }

    /// @brief Name of the test lease file.
    std::string filename_;

    /// @brief Object providing access to lease file IO.
    LeaseFileIO io_;
};

LeaseFileLoaderTest::LeaseFileLoaderTest()
    : filename_("leases4.csv"), io_(absolutePath(filename_)) {
}

std::string
LeaseFileLoaderTest::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << DHCP_DATA_DIR << "/" << filename;
    return (s.str());
}

// This test verifies that the DHCPv4 leases can be loaded from the lease
// file and that only the most recent entry for each lease is loaded and
// the previous entries are discarded.
TEST_F(LeaseFileLoaderTest, load4) {
    // Create lease file with leases for 192.0.2.1, 192.0.3.15. The lease
    // entry for the 192.0.2.3 is invalid (lacks HW address) and should
    // be discarded.
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,100,7,"
                  "0,0,\n"
                  "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,135,7,"
                  "0,0,\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,500,8,1,1,"
                  "host.example.com\n");

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases from the file.
    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 10));

    // There are two unique leases.
    ASSERT_EQ(2, storage.size());

    // The lease for 192.0.2.1 should exist and the cltt should be
    // set to the expire-valid_lifetime for the second entry for
    // this lease, i.e. 500 - 200 = 300.
    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.2.1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(300, lease->cltt_);

    // The invalid entry should not be loaded.
    lease = getLease<Lease4Ptr>("192.0.2.3", storage);
    ASSERT_FALSE(lease);

    // The other lease should be present and the cltt time should
    // be set according to the values in the second entry for this
    // lease.
    lease = getLease<Lease4Ptr>("192.0.3.15", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(35, lease->cltt_);
}

// This test verifies that the lease with a valid lifetime of 0
// is removed from the storage. The valid lifetime of 0 is set
// for the released leases.
TEST_F(LeaseFileLoaderTest, load4LeaseRemove) {
    // Create lease file in which one of the entries for 192.0.2.1
    // has a valid_lifetime of 0 and results in the deletion of the
    // lease.
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,100,7,"
                  "0,0,\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,135,7,"
                  "0,0,\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,0,500,8,1,1,"
                  "host.example.com\n");

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 10));

    // There should only be one lease. The one with the valid_lifetime
    // of 0 should be removed.
    ASSERT_EQ(1, storage.size());

    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.3.15", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(35, lease->cltt_);
}

// This test verifies that the DHCPv6 leases can be loaded from the lease
// file and that only the most recent entry for each lease is loaded and
// the previous entries are discarded.
TEST_F(LeaseFileLoaderTest, load6) {
    // Create a lease file with three valid leases: 2001:db8:1::1,
    // 3000:1:: and 2001:db8:2::10.
    io_.writeFile("address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr\n"
                  "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,\n"
                  "2001:db8:1::1,,200,200,8,100,0,7,0,1,1,host.example.com,\n"
                  "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,300,300,6,150,"
                  "0,8,0,0,0,,\n"
                  "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,100,200,8,0,2,"
                  "16,64,0,0,,\n"
                  "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,300,800,6,150,"
                  "0,8,0,0,0,,\n"
                  "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                  "200,400,8,100,0,7,0,1,1,host.example.com,\n");

    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases from the lease file.
    Lease6Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, 10));

    // There should be 3 unique leases.
    ASSERT_EQ(3, storage.size());

    // The 2001:db8:1::1 should be present and its cltt should be
    // calculated according to the expiration time and the valid
    // lifetime from the last entry for this lease: 400 - 200 = 200.
    Lease6Ptr lease = getLease<Lease6Ptr>("2001:db8:1::1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(200, lease->cltt_);

    // The 3000:1:: lease should be present.
    lease = getLease<Lease6Ptr>("3000:1::", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(100, lease->cltt_);

    // The 2001:db8:2::10 should be present and the cltt should be
    // calculated according to the last entry in the lease file.
    lease = getLease<Lease6Ptr>("2001:db8:2::10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);
}

// This test verifies that the lease with a valid lifetime of 0
// is removed from the storage. The valid lifetime of 0 set set
// for the released leases.
TEST_F(LeaseFileLoaderTest, load6LeaseRemove) {
    // Create lease file in which one of the entries for the 2001:db8:1::1
    // has valid lifetime set to 0, in which case the lease should be
    // deleted.
    io_.writeFile("address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr\n"
                  "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,\n"
                  "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,300,300,6,150,"
                  "0,8,0,0,0,,\n"
                  "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,300,800,6,150,"
                  "0,8,0,0,0,,\n"
                  "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                  "0,400,8,100,0,7,0,1,1,host.example.com,\n");

    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->open());

    // Loaded leases.
    Lease6Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, 10));

    // There should be only one lease for 2001:db8:2::10. The other one
    // should have been deleted (or rather not loaded).
    ASSERT_EQ(1, storage.size());

    Lease6Ptr lease = getLease<Lease6Ptr>("2001:db8:2::10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);
}

// This test verifies that the exception is thrown when the specific
// number of errors in the test data occur during reading of the lease
// file.
TEST_F(LeaseFileLoaderTest, loadMaxErrors) {
    // Create a lease file for which there is a number of invalid
    // entries.
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com\n"
                  "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.2.10,01:02:03:04:05:06,,200,300,8,1,1,,\n"
                  "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,500,8,1,1,"
                  "host.example.com\n");

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases and set the maximum number of errors to 3. This
    // should result in an exception because there are 4 invalid entries.
    Lease4Storage storage;
    ASSERT_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 3),
                 util::CSVFileError);

    lf->close();
    ASSERT_NO_THROW(lf->open());

    // Repeat the test, but this time allow for 4 invalid entries. It
    // should load just fine.
    storage.clear();
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 4));

    ASSERT_EQ(2, storage.size());

    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.2.1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(300, lease->cltt_);

    lease = getLease<Lease4Ptr>("192.0.2.10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(100, lease->cltt_);
}

// This test verifies that the lease with a valid lifetime set to 0 is
// not loaded if there are no previous entries for this lease in the
// lease file.
TEST_F(LeaseFileLoaderTest, loadLeaseWithZeroLifetime) {
    // Create lease file. The second lease has a valid lifetime of 0.
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,,\n"
                  "192.0.2.3,06:07:08:09:0a:bd,,0,200,8,1,1,,\n");

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open()); 

    // Set the error count to 0 to make sure that lease with a zero
    // lifetime doesn't cause an error.
    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 0));

    // The first lease should be present.
    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.2.1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // The lease with a valid lifetime of 0 should not be loaded.
    EXPECT_FALSE(getLease<Lease4Ptr>("192.0.2.3", storage));
}   


} // end of anonymous namespace
