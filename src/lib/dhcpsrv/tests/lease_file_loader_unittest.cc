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

    /// @brief Tests the write function.
    ///
    /// This method writes the leases from the storage container to the lease file
    /// then compares the output to the string provided in the arguments to verify
    /// the write was correct.  The order of the leases in the output will depend
    /// on the order in which the container provides the leases.
    ///
    /// @param lease_file A reference to the file to write to
    /// @param storage A reference to the container to be written to the file
    /// @param compare The string to compare to what was read from the file
    ///
    /// @tparam LeaseObjectType A @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType A @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType A @c Lease4Storage or @c Lease6Storage.
    ///
    template<typename LeaseObjectType, typename LeaseFileType,
             typename StorageType>
    void writeLeases(LeaseFileType& lease_file,
                     const StorageType& storage,
                     const std::string& compare) {
        // Prepare for a new file, close and remove the old
        lease_file.close();
        io_.removeFile();

        // Write the current leases to the file
        LeaseFileLoader::write<LeaseObjectType, LeaseFileType, StorageType>
            (lease_file, storage);

        // Compare to see if we got what we exepcted.
        EXPECT_EQ(compare, io_.readFile());
    }

    /// @brief Checks the stats for the file
    ///
    /// This method is passed a leasefile and the values for the statistics it
    /// should have for comparison.
    ///
    /// @param lease_file A reference to the file we are using
    /// @param reads the number of attempted reads
    /// @param read_leases the number of valid leases read
    /// @param read_errs the number of errors while reading leases
    /// @param writes the number of attempted writes
    /// @param write_leases the number of leases successfully written
    /// @param write_errs the number of errors while writing
    ///
    /// @tparam LeaseFileType A @c CSVLeaseFile4 or @c CSVLeaseFile6.
    template<typename LeaseFileType>
    void checkStats(LeaseFileType& lease_file,
                    uint32_t reads, uint32_t read_leases,
                    uint32_t read_errs, uint32_t writes,
                    uint32_t write_leases, uint32_t write_errs) const {
        EXPECT_EQ(reads, lease_file.getReads());
        EXPECT_EQ(read_leases, lease_file.getReadLeases());
        EXPECT_EQ(read_errs, lease_file.getReadErrs());
        EXPECT_EQ(writes, lease_file.getWrites());
        EXPECT_EQ(write_leases, lease_file.getWriteLeases());
        EXPECT_EQ(write_errs, lease_file.getWriteErrs());
    }

    /// @brief Name of the test lease file.
    std::string filename_;

    /// @brief Object providing access to lease file IO.
    LeaseFileIO io_;

    std::string v4_hdr_; ///< String for the header of the v4 csv test file
    std::string v6_hdr_; ///< String for the header of the v6 csv test file

protected:
    /// @brief Sets up the header strings
    virtual void SetUp() {
        v4_hdr_ = "address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n";

        v6_hdr_ = "address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr\n";
    }
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
//
// It also tests the write function by writing the storage to a file
// and comparing that with the expected value.
TEST_F(LeaseFileLoaderTest, loadWrite4) {
    std::string test_str;
    std::string a_1 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,200,8,1,1,host.example.com\n";
    std::string a_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,500,8,1,1,host.example.com\n";

    std::string b_1 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,100,7,0,0,\n";
    std::string b_2 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,135,7,0,0,\n";

    std::string c_1 = "192.0.2.3,,a:11:01:04,"
                      "200,200,8,1,1,host.example.com\n";

    // Create lease file with leases for 192.0.2.1, 192.0.3.15. The lease
    // entry for the 192.0.2.3 is invalid (lacks HW address) and should
    // be discarded.
    test_str = v4_hdr_ + a_1 + b_1 + c_1 + b_2 + a_2;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases from the file.
    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 10));

    // We should have made 6 attempts to read, with 4 leases read and 1 error
    {
    SCOPED_TRACE("Read leases");
    checkStats(*lf, 6, 4, 1, 0, 0, 0);
    }

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

    test_str = v4_hdr_ + a_2 + b_2;
    writeLeases<Lease4, CSVLeaseFile4, Lease4Storage>(*lf, storage, test_str);

    // We should have made 2 attempts to write, with 2 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 2, 2, 0);
    }
}

// This test verifies that the lease with a valid lifetime of 0
// is removed from the storage. The valid lifetime of 0 is set
// for the released leases.
//
// It also tests the write function by writing the storage to a file
// and comparing that with the expected value.
TEST_F(LeaseFileLoaderTest, loadWrite4LeaseRemove) {
    std::string test_str;
    std::string a_1 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,200,8,1,1,host.example.com\n";
    std::string a_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "0,500,8,1,1,host.example.com\n";

    std::string b_1 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,100,7,0,0,\n";
    std::string b_2 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,135,7,0,0,\n";


    // Create lease file in which one of the entries for 192.0.2.1
    // has a valid_lifetime of 0 and results in the deletion of the
    // lease.
    test_str = v4_hdr_ + a_1 + b_1 + b_2 + a_2;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 10));

    // We should have made 5 attempts to read, with 4 leases read and 0 error
    {
    SCOPED_TRACE("Read leases");
    checkStats(*lf, 5, 4, 0, 0, 0, 0);
    }

    // There should only be one lease. The one with the valid_lifetime
    // of 0 should be removed.
    ASSERT_EQ(1, storage.size());

    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.3.15", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(35, lease->cltt_);

    test_str = v4_hdr_ + b_2;
    writeLeases<Lease4, CSVLeaseFile4, Lease4Storage>(*lf, storage, test_str);

    // We should have made 1 attempts to write, with 1 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 1, 1, 0);
    }
}

// This test verifies that the DHCPv6 leases can be loaded from the lease
// file and that only the most recent entry for each lease is loaded and
// the previous entries are discarded.
//
// It also tests the write function by writing the storage to a file
// and comparing that with the expected value.
TEST_F(LeaseFileLoaderTest, loadWrite6) {
    std::string test_str;
    std::string a_1 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "200,200,8,100,0,7,0,1,1,host.example.com,\n";
    std::string a_2 = "2001:db8:1::1,,"
                      "200,200,8,100,0,7,0,1,1,host.example.com,\n";
    std::string a_3 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "200,400,8,100,0,7,0,1,1,host.example.com,\n";

    std::string b_1 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,300,6,150,0,8,0,0,0,,\n";
    std::string b_2 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,800,6,150,0,8,0,0,0,,\n";

    std::string c_1 = "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "100,200,8,0,2,16,64,0,0,,\n";



    // Create a lease file with three valid leases: 2001:db8:1::1,
    // 3000:1:: and 2001:db8:2::10.
    test_str = v6_hdr_ + a_1 + a_2 + b_1 + c_1 + b_2 + a_3;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases from the lease file.
    Lease6Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, 10));

    // We should have made 7 attempts to read, with 5 leases read and 1 error
    {
    SCOPED_TRACE("Read leases");
    checkStats(*lf, 7, 5, 1, 0, 0, 0);
    }

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

    test_str = v6_hdr_ + a_3 + b_2 + c_1;
    writeLeases<Lease6, CSVLeaseFile6, Lease6Storage>(*lf, storage, test_str);

    // We should have made 3 attempts to write, with 3 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 3, 3, 0);
    }
}

// This test verifies that the lease with a valid lifetime of 0
// is removed from the storage. The valid lifetime of 0 set set
// for the released leases.
//
// It also tests the write function by writing the storage to a file
// and comparing that with the expected value.
TEST_F(LeaseFileLoaderTest, loadWrite6LeaseRemove) {
    std::string test_str;
    std::string a_1 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "200,200,8,100,0,7,0,1,1,host.example.com,\n";
    std::string a_2 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "0,400,8,100,0,7,0,1,1,host.example.com,\n";

    std::string b_1 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,300,6,150,0,8,0,0,0,,\n";
    std::string b_2 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,800,6,150,0,8,0,0,0,,\n";

    // Create lease file in which one of the entries for the 2001:db8:1::1
    // has valid lifetime set to 0, in which case the lease should be
    // deleted.
    test_str = v6_hdr_ + a_1 + b_1 + b_2 + a_2;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->open());

    // Loaded leases.
    Lease6Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, 10));

    // We should have made 5 attempts to read, with 4 leases read and 0 error
    {
    SCOPED_TRACE("Read leases");
    checkStats(*lf, 5, 4, 0, 0, 0, 0);
    }

    // There should be only one lease for 2001:db8:2::10. The other one
    // should have been deleted (or rather not loaded).
    ASSERT_EQ(1, storage.size());

    Lease6Ptr lease = getLease<Lease6Ptr>("2001:db8:2::10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);

    test_str = v6_hdr_ + b_2;
    writeLeases<Lease6, CSVLeaseFile6, Lease6Storage>(*lf, storage, test_str);

    // We should have made 1 attempts to write, with 1 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 1, 1, 0);
    }
}

// This test verifies that the exception is thrown when the specific
// number of errors in the test data occur during reading of the lease
// file.
TEST_F(LeaseFileLoaderTest, loadMaxErrors) {
    std::string test_str;
    std::string a_1 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,200,8,1,1,host.example.com\n";
    std::string a_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,500,8,1,1,host.example.com\n";

    std::string b_1 = "192.0.2.3,,a:11:01:04,200,200,8,1,1,host.example.com\n";

    std::string c_1 = "192.0.2.10,01:02:03:04:05:06,,200,300,8,1,1,\n";

    // Create a lease file for which there is a number of invalid
    // entries.  b_1 is invalid and gets used multiple times.
    test_str = v4_hdr_ + a_1 + b_1 + b_1 + c_1 + b_1 + b_1 + a_2;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Load leases and set the maximum number of errors to 3. This
    // should result in an exception because there are 4 invalid entries.
    Lease4Storage storage;
    ASSERT_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 3),
                 util::CSVFileError);

    // We should have made 6 attempts to read, with 2 leases read and 4 error
    {
    SCOPED_TRACE("Read leases 1");
    checkStats(*lf, 6, 2, 4, 0, 0, 0);
    }

    lf->close();
    ASSERT_NO_THROW(lf->open());

    // Repeat the test, but this time allow for 4 invalid entries. It
    // should load just fine.
    storage.clear();
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 4));

    // We should have made 8 attempts to read, with 3 leases read and 4 error
    {
    SCOPED_TRACE("Read leases 2");
    checkStats(*lf, 8, 3, 4, 0, 0, 0);
    }

    ASSERT_EQ(2, storage.size());

    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.2.1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(300, lease->cltt_);

    lease = getLease<Lease4Ptr>("192.0.2.10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(100, lease->cltt_);

    test_str = v4_hdr_ + a_2 + c_1;
    writeLeases<Lease4, CSVLeaseFile4, Lease4Storage>(*lf, storage, test_str);

    // We should have made 1 attempts to write, with 1 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 2, 2, 0);
    }
}

// This test verifies that the lease with a valid lifetime set to 0 is
// not loaded if there are no previous entries for this lease in the
// lease file.
//
// It also tests the write function by writing the storage to a file
// and comparing that with the expected value.
TEST_F(LeaseFileLoaderTest, loadWriteLeaseWithZeroLifetime) {
    std::string test_str;
    std::string a_1 = "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,\n";
    std::string b_2 = "192.0.2.3,06:07:08:09:0a:bd,,0,200,8,1,1,\n";

    // Create lease file. The second lease has a valid lifetime of 0.
    test_str = v4_hdr_ + a_1 + b_2;
    io_.writeFile(test_str);

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Set the error count to 0 to make sure that lease with a zero
    // lifetime doesn't cause an error.
    Lease4Storage storage;
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, 0));

    // We should have made 3 attempts to read, with 2 leases read and 0 error
    {
    SCOPED_TRACE("Read leases");
    checkStats(*lf, 3, 2, 0, 0, 0, 0);
    }

    // The first lease should be present.
    Lease4Ptr lease = getLease<Lease4Ptr>("192.0.2.1", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // The lease with a valid lifetime of 0 should not be loaded.
    EXPECT_FALSE(getLease<Lease4Ptr>("192.0.2.3", storage));

    test_str = v4_hdr_ + a_1;
    writeLeases<Lease4, CSVLeaseFile4, Lease4Storage>(*lf, storage, test_str);

    // We should have made 1 attempts to write, with 1 leases written and 0 errors
    {
    SCOPED_TRACE("Write leases");
    checkStats(*lf, 0, 0, 0, 1, 1, 0);
    }
}
} // end of anonymous namespace
