// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/lease_file_loader.h>
#include <dhcpsrv/testutils/lease_file_io.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_consistency.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
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

    /// @brief Destructor
    ///
    /// Removes any configuration that may have been added in CfgMgr.
    virtual ~LeaseFileLoaderTest();

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

        // Compare to see if we got what we expected.
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

    Lease4Storage storage4_; ///< Storage for IPv4 leases
    Lease6Storage storage6_; ///< Storage for IPv4 leases

    /// @brief Creates IPv4 subnet with specified parameters
    ///
    /// @param subnet_txt subnet in textual form, e.g. 192.0.2.0/24
    /// @param subnet_id id to be used.
    /// @return A pointer to Subnet4 object
    Subnet4Ptr createSubnet4(std::string subnet_txt, SubnetID id) {
        size_t pos = subnet_txt.find("/");
        isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
        size_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        return (Subnet4Ptr(new Subnet4(addr, len, 1000, 2000, 3000, id)));
    }

    /// @brief Creates IPv6 subnet with specified parameters
    ///
    /// @param subnet_txt subnet in textual form, e.g. 2001:db8::/32
    /// @param subnet_id id to be used.
    /// @return A pointer to Subnet4 object
    Subnet6Ptr createSubnet6(std::string subnet_txt, SubnetID id) {
        size_t pos = subnet_txt.find("/");
        isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
        size_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        return (Subnet6Ptr(new Subnet6(addr, len, 1000, 2000, 3000, 4000, id)));
    }

    /// @brief Checks if IPv4 lease loaded from file is sanity checked.
    ///
    /// This method writes a simple lease file with one lease in it,
    /// then sets sanity checks to tested level, then tries to load
    /// the lease file and finally checks whether the lease was loaded
    /// or not.
    ///
    /// @param lease address of the lease in text form
    /// @param lease_id subnet-id to be used in a lease
    /// @param subnet_txt Text representation of the subnet, e.g. 192.0.2.0/24
    /// @param subnet_id Subnet-id of the subnet to be created
    /// @param sanity level of sanity checks
    /// @param exp_present is the lease expected to be loaded (true = yes)
    /// @param exp_id expected subnet-id of the loaded lease
    void sanityChecks4(std::string lease, SubnetID lease_id,
                       std::string subnet_txt, SubnetID subnet_id,
                       CfgConsistency::LeaseSanity sanity,
                       bool exp_present, SubnetID exp_id) {

        // Create the subnet and add it to configuration.
        if (!subnet_txt.empty()) {
            Subnet4Ptr subnet = createSubnet4(subnet_txt, subnet_id);
            ASSERT_NO_THROW(CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet));
        }

        std::stringstream file_content;
        file_content << v4_hdr_ << lease << ",dd:de:ba:0d:1b:2e,"
                     << "0a:00:01:04,100,100," << static_cast<int>(lease_id)
                     << ",0,0,,1,\n";

        ASSERT_NO_THROW(CfgMgr::instance().getStagingCfg()->getConsistency()
                    ->setLeaseSanityCheck(sanity));

        io_.writeFile(file_content.str());

        boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
        ASSERT_NO_THROW(lf->open());

        // Load leases from the file.
        ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage4_, 10));

        {
            SCOPED_TRACE("Read leases");
            checkStats(*lf, 2, 1, 0, 0, 0, 0);
        }

        // Check how many leases were actually loaded.
        ASSERT_EQ( (exp_present ? 1 : 0), storage4_.size());

        Lease4Ptr l = getLease<Lease4Ptr>(lease, storage4_);

        if (exp_present) {
            ASSERT_TRUE(l) << "lease not found, but expected";
            EXPECT_EQ(l->subnet_id_, exp_id);
        } else {
            EXPECT_FALSE(l) << "lease found, but was not expected";
        }
    }

    /// @brief Checks if IPv6 lease loaded from file is sanity checked.
    ///
    /// This method writes a simple lease file with one lease in it,
    /// then sets sanity checks to tested level, then tries to load
    /// the lease file and finally checks whether the lease was loaded
    /// or not.
    ///
    /// @param lease address of the lease in text form
    /// @param lease_id subnet-id to be used in a lease
    /// @param subnet_txt Text representation of the subnet, e.g. 192.0.2.0/24
    /// @param subnet_id Subnet-id of the subnet to be created
    /// @param sanity level of sanity checks
    /// @param exp_present is the lease expected to be loaded (true = yes)
    /// @param exp_id expected subnet-id of the loaded lease
    /// @param prefix_len length of the prefix if the lease created should be
    /// a PD lease. Defaults to 0.
    void sanityChecks6(std::string lease, SubnetID lease_id,
                       std::string subnet_txt, SubnetID subnet_id,
                       CfgConsistency::LeaseSanity sanity,
                       bool exp_present, SubnetID exp_id,
                       unsigned int prefix_len = 0) {

        // Create the subnet and add it to configuration.
        if (!subnet_txt.empty()) {
            Subnet6Ptr subnet = createSubnet6(subnet_txt, subnet_id);
            ASSERT_NO_THROW(CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet));
        }

        std::stringstream file_content;

        file_content << v6_hdr_ << lease << ",dd:de:ba:0d:1b:2e,"
                     << "300,300," << static_cast<int>(lease_id) << ",150,"
                     << (prefix_len > 0 ? Lease::TYPE_PD : Lease::TYPE_NA)
                     << ",8," << prefix_len << ",0,0,,,1,\n";

        ASSERT_NO_THROW(CfgMgr::instance().getStagingCfg()->getConsistency()
                    ->setLeaseSanityCheck(sanity));

        io_.writeFile(file_content.str());

        boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
        ASSERT_NO_THROW(lf->open());

        // Load leases from the file.
        ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage6_, 10));

        {
            SCOPED_TRACE("Read leases");
            checkStats(*lf, 2, 1, 0, 0, 0, 0);
        }

        // Check how many leases were actually loaded.
        ASSERT_EQ( (exp_present ? 1 : 0), storage6_.size());

        Lease6Ptr l = getLease<Lease6Ptr>(lease, storage6_);

        if (exp_present) {
            ASSERT_TRUE(l) << "lease not found, but expected";
            EXPECT_EQ(exp_id, l->subnet_id_);
        } else {
            EXPECT_FALSE(l) << "lease found, but was not expected";
        }
    }

protected:
    /// @brief Sets up the header strings
    virtual void SetUp() {
        v4_hdr_ = "address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n";

        v6_hdr_ = "address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr,state,user_context,"
                  "hwtype,hwaddr_source\n";
    }
};

LeaseFileLoaderTest::LeaseFileLoaderTest()
    : filename_(absolutePath("leases.csv")), io_(filename_) {
    CfgMgr::instance().clear();
}

LeaseFileLoaderTest::~LeaseFileLoaderTest() {
    CfgMgr::instance().clear();
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
                      "200,200,8,1,1,host.example.com,1,"
                      "{ \"foobar\": true }\n";
    std::string a_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "200,500,8,1,1,host.example.com,1,"
                      "{ \"foobar\": true }\n";

    std::string b_1 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,100,7,0,0,,1,\n";
    std::string b_2 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,135,7,0,0,,1,\n";

    std::string c_1 = "192.0.2.3,,,"
                      "200,200,8,1,1,host.example.com,0,\n";

    // Create lease file with leases for 192.0.2.1, 192.0.3.15. The lease
    // entry for the 192.0.2.3 is invalid (lacks HW address and client id)
    // and should be discarded.
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

    // The lease for 192.0.2.1 should have user context.
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());

    // The invalid entry should not be loaded.
    lease = getLease<Lease4Ptr>("192.0.2.3", storage);
    ASSERT_FALSE(lease);

    // The other lease should be present and the cltt time should
    // be set according to the values in the second entry for this
    // lease.
    lease = getLease<Lease4Ptr>("192.0.3.15", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(35, lease->cltt_);
    EXPECT_FALSE(lease->getContext());

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
                      "200,200,8,1,1,host.example.com,1,\n";
    std::string a_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                      "0,500,8,1,1,host.example.com,1,\n";

    std::string b_1 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,100,7,0,0,,1,\n";
    std::string b_2 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                      "100,135,7,0,0,,1,\n";


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

// This test verifies that max-row-errors works correctly for
// DHCPv4 lease files
TEST_F(LeaseFileLoaderTest, maxRowErrors4) {
    // We have 9 rows: 2 that are good, 7 that are flawed (too few fields).
    std::vector<std::string> rows = {
        "192.0.2.100,08:00:27:25:d3:f4,31:31:31:31,3600,1565356064,1,0,0,,0,\n",
        "192.0.2.101,FF:FF:FF:FF:FF:01,32:32:32:31,3600,1565356073,1,0,0\n",
        "192.0.2.102,FF:FF:FF:FF:FF:02,32:32:32:32,3600,1565356073,1,0,0\n",
        "192.0.2.103,FF:FF:FF:FF:FF:03,32:32:32:33,3600,1565356073,1,0,0\n",
        "192.0.2.104,FF:FF:FF:FF:FF:04,32:32:32:34,3600,1565356073,1,0,0\n",
        "192.0.2.105,FF:FF:FF:FF:FF:05,32:32:32:35,3600,1565356073,1,0,0\n",
        "192.0.2.106,FF:FF:FF:FF:FF:06,32:32:32:36,3600,1565356073,1,0,0\n",
        "192.0.2.107,FF:FF:FF:FF:FF:07,32:32:32:37,3600,1565356073,1,0,0\n",
        "192.0.2.108,08:00:27:25:d3:f4,32:32:32:32,3600,1565356073,1,0,0,,0,\n"
    };

    std::ostringstream os;
    os << v4_hdr_;
    for (auto row : rows) {
        os << row;
    }

    io_.writeFile(os.str());

    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Let's limit the number of errors to 5 (we have 7 in the data) and
    // try to load the leases.
    uint32_t max_errors = 5;
    Lease4Storage storage;
    ASSERT_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, max_errors), util::CSVFileError);

    // We should have made 7 reads, with 1 lease read, and 6 errors.
    {
        SCOPED_TRACE("Failed load stats");
        checkStats(*lf, 7, 1, 6, 0, 0, 0);
    }

    // Now let's disable the error limit and try again.
    max_errors = 0;

    // Load leases from the file. Note, we have to reopen the file.
    ASSERT_NO_THROW(lf->open());
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease4>(*lf, storage, max_errors));

    // We should have made 10 reads, with 2 leases read, and 7 errors.
    {
        SCOPED_TRACE("Good load stats");
        checkStats(*lf, 10, 2, 7, 0, 0, 0);
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
                      "200,200,8,100,0,7,0,1,1,host.example.com,,1,"
                      "{ \"foobar\": true },,\n";
    std::string a_2 = "2001:db8:1::1,,"
                      "200,200,8,100,0,7,0,1,1,host.example.com,,1,"
                      "{ \"foobar\": true },,\n";
    std::string a_3 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "200,400,8,100,0,7,0,1,1,host.example.com,,1,"
                      "{ \"foobar\": true },,\n";
    std::string b_1 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,300,6,150,0,8,0,0,0,,,1,,,\n";
    std::string b_2 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,800,6,150,0,8,0,0,0,,,1,,,\n";

    std::string c_1 = "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "100,200,8,0,2,16,64,0,0,,,1,,,\n";


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

    // The 2001:db8:1::1 should have user context.
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());

    // The 3000:1:: lease should be present.
    lease = getLease<Lease6Ptr>("3000:1::", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(100, lease->cltt_);
    EXPECT_FALSE(lease->getContext());

    // The 2001:db8:2::10 should be present and the cltt should be
    // calculated according to the last entry in the lease file.
    lease = getLease<Lease6Ptr>("2001:db8:2::10", storage);
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);
    EXPECT_FALSE(lease->getContext());

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
                      "200,200,8,100,0,7,0,1,1,host.example.com,,1,,,\n";
    std::string a_2 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                      "0,400,8,100,0,7,0,1,1,host.example.com,,1,,,\n";

    std::string b_1 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,300,6,150,0,8,0,0,0,,,1,,,\n";
    std::string b_2 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                      "300,800,6,150,0,8,0,0,0,,,1,,,\n";

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

// This test verifies that max-row-errors works correctly for
// DHCPv6 lease files
TEST_F(LeaseFileLoaderTest, maxRowErrors6) {
    // We have 9 rows: 2 that are good, 7 that are flawed (too few fields).
    std::vector<std::string> rows = {
        "3002::01,00:03:00:01:08:00:27:25:d3:01,30,1565361388,2,20,0,"
        "11189196,128,0,0,,08:00:27:25:d3:f4,0,\n",
        "3002::02,00:03:00:01:08:00:27:25:d3:02,30,1565361388,2,20,0\n",
        "3002::03,00:03:00:01:08:00:27:25:d3:03,30,1565361388,2,20,0\n",
        "3002::04,00:03:00:01:08:00:27:25:d3:04,30,1565361388,2,20,0\n",
        "3002::05,00:03:00:01:08:00:27:25:d3:05,30,1565361388,2,20,0\n",
        "3002::06,00:03:00:01:08:00:27:25:d3:06,30,1565361388,2,20,0\n",
        "3002::07,00:03:00:01:08:00:27:25:d3:07,30,1565361388,2,20,0\n",
        "3002::08,00:03:00:01:08:00:27:25:d3:08,30,1565361388,2,20,0\n",
        "3002::09,00:03:00:01:08:00:27:25:d3:09,30,1565361388,2,20,0,"
        "11189196,128,0,0,,08:00:27:25:d3:f4,0,\n"
    };

    std::ostringstream os;
    os << v6_hdr_;
    for (auto row : rows) {
        os << row;
    }

    io_.writeFile(os.str());

    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->open());

    // Let's limit the number of errors to 5 (we have 7 in the data) and
    // try to load the leases.
    uint32_t max_errors = 5;
    Lease6Storage storage;
    ASSERT_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, max_errors), util::CSVFileError);

    // We should have made 7 reads, with 1 lease read, and 6 errors.
    {
        SCOPED_TRACE("Failed load stats");
        checkStats(*lf, 7, 1, 6, 0, 0, 0);
    }

    // Now let's disable the error limit and try again.
    max_errors = 0;

    // Load leases from the file. Note, we have to reopen the file.
    ASSERT_NO_THROW(lf->open());
    ASSERT_NO_THROW(LeaseFileLoader::load<Lease6>(*lf, storage, max_errors));

    // We should have made 10 reads, with 2 leases read, and 7 errors.
    {
        SCOPED_TRACE("Good load stats");
        checkStats(*lf, 10, 2, 7, 0, 0, 0);
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
    std::string a_1 = "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,,1,\n";
    std::string b_2 = "192.0.2.3,06:07:08:09:0a:bd,,0,200,8,1,1,,1,\n";

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

// This test checks if the lease can be loaded, even though there are no
// subnets configured that it would match.
// Scenario: print a warning, there's no subnet,
// expected outcome: add the lease as is
TEST_F(LeaseFileLoaderTest, sanityChecker4NoSubnetsWarn) {
    sanityChecks4("192.0.2.1", 1, "", 0, CfgConsistency::LEASE_CHECK_WARN, true, 1);
}

// This test checks if the lease can be fixed.
// Scenario: try to fix the lease, there's no subnet,
// expected outcome: add the lease as is
TEST_F(LeaseFileLoaderTest, sanityChecker4NoSubnetsFix) {
    sanityChecks4("192.0.2.1", 1, "", 0, CfgConsistency::LEASE_CHECK_FIX, true, 1);
}

// This test checks if the lease can be discarded if it's impossible to fix.
// Scenario: try to fix the lease, there's no subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker4NoSubnetsFixDel) {
    sanityChecks4("192.0.2.1", 1, "", 0, CfgConsistency::LEASE_CHECK_FIX_DEL, false, 1);
}

// This test checks if the lease can be discarded.
// Scenario: try to fix the lease, there's no subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker4NoSubnetsDel) {
    sanityChecks4("192.0.2.1", 1, "", 0, CfgConsistency::LEASE_CHECK_DEL, false, 1);
}

// This test checks if the lease can be fixed.
// Scenario: try to fix the lease, there's a subnet,
// expected outcome: correct the lease
TEST_F(LeaseFileLoaderTest, sanityChecker4Fix) {
    sanityChecks4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_FIX, true, 2);
}

// This test checks if the lease can be fixed when it's possible.
// Scenario: try to fix the lease, there's a subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker4FixDel1) {
    sanityChecks4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, true, 2);
}

// This test checks if the lease is discarded, when fix is not possible.
// Scenario: try to fix the lease, there's a subnet, but it doesn't match,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker4FixDel2) {
    sanityChecks4("192.0.2.1", 1, "192.0.3.0/24", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, false, 1);
}

// This test checks if the lease is discarded.
// Scenario: delete the lease, there's a subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker4Del) {
    sanityChecks4("192.0.2.1", 1, "192.0.2.0/24", 2, CfgConsistency::LEASE_CHECK_DEL, false, 1);
}

// This test checks if the lease can be loaded, even though there are no
// subnets configured that it would match.
TEST_F(LeaseFileLoaderTest, sanityChecker6NoSubnetsWarn) {
    sanityChecks6("2001::1", 1, "", 0, CfgConsistency::LEASE_CHECK_WARN, true, 1);
}

// This test checks if the lease can be fixed.
// Scenario: try to fix the lease, there's no subnet,
// expected outcome: add the lease as is
TEST_F(LeaseFileLoaderTest, sanityChecker6NoSubnetsFix) {
    sanityChecks6("2001::1", 1, "", 0, CfgConsistency::LEASE_CHECK_FIX, true, 1);
}

// This test checks if the lease can be discarded if it's impossible to fix.
// Scenario: try to fix the lease, there's no subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker6NoSubnetsFixDel) {
    sanityChecks6("2001::1", 1, "", 0, CfgConsistency::LEASE_CHECK_FIX_DEL, false, 1);
}

// This test checks if the lease can be discarded.  Note we are
// verifying whether the checks are conducted at all when loading a file.
// Thorough tests were conducted in sanity_checks_unittest.cc.
TEST_F(LeaseFileLoaderTest, sanityChecker6NoSubnetsDel) {
    sanityChecks6("2001::1", 1, "", 0, CfgConsistency::LEASE_CHECK_DEL, false, 1);
}

// This test checks if the lease can be fixed.
// Scenario: try to fix the lease, there's a subnet,
// expected outcome: correct the lease
TEST_F(LeaseFileLoaderTest, sanityChecker6Fix) {
    sanityChecks6("2001::1", 1, "2001::/16", 2, CfgConsistency::LEASE_CHECK_FIX, true, 2);
}

// This test checks if the lease can be fixed when it's possible.
// Scenario: try to fix the lease, there's a subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker6FixDel1) {
    sanityChecks6("2001::1", 1, "2001::/16", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, true, 2);
}

// This test checks if the lease is discarded, when fix is not possible.
// Scenario: try to fix the lease, there's a subnet, but it doesn't match,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker6FixDel2) {
    sanityChecks6("2001::1", 1, "2002::/16", 2, CfgConsistency::LEASE_CHECK_FIX_DEL, false, 1);
}

// This test checks if the lease is discarded.
// Scenario: delete the lease, there's a subnet,
// expected outcome: the lease is not loaded
TEST_F(LeaseFileLoaderTest, sanityChecker6Del) {
    sanityChecks6("2001::1", 1, "2001::/16", 2, CfgConsistency::LEASE_CHECK_DEL, false, 1);
}

// This test checks to make sure PD leases are not sanity checked,
// and thus not discarded.
TEST_F(LeaseFileLoaderTest, sanityChecker6PD) {
    int prefix_len = 64;

    // We check a prefix lease whose subnet-id does not exist and
    // is clearly outside the only known subnet.
    sanityChecks6("2001:1::", 2,   // create prefix lease in subnet 2
                  "3001::/64", 1,  // create subnet 1
                  CfgConsistency::LEASE_CHECK_DEL,
                  true, 2,         // lease should still exist with subnet id of 2
                  prefix_len);
}

} // end of anonymous namespace
