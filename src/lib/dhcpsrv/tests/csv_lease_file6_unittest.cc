// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/testutils/lease_file_io.h>
#include <gtest/gtest.h>
#include <ctime>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

// DUID values used by unit tests.
const uint8_t DUID0[] = { 0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
const uint8_t DUID1[] = { 1, 1, 1, 1, 0xa, 1, 2, 3, 4, 5 };

/// @brief Test fixture class for @c CSVLeaseFile6 validation.
class CSVLeaseFile6Test : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Initializes IO for lease file used by unit tests.
    CSVLeaseFile6Test();

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    /// @brief Create DUID object from the binary.
    ///
    /// @param duid Binary value representing a DUID.
    /// @param size Size of the DUID.
    /// @return Pointer to the @c DUID object.
    DuidPtr makeDUID(const uint8_t* duid, const unsigned int size) const {
        return (DuidPtr(new DUID(duid, size)));
    }

    /// @brief Create lease file that can be parsed by unit tests.
    void writeSampleFile() const;

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
    void checkStats(CSVLeaseFile6& lease_file,
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

};

CSVLeaseFile6Test::CSVLeaseFile6Test()
    : filename_(absolutePath("leases6.csv")), io_(filename_) {
}

std::string
CSVLeaseFile6Test::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << DHCP_DATA_DIR << "/" << filename;
    return (s.str());
}

void
CSVLeaseFile6Test::writeSampleFile() const {
    io_.writeFile("address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr,state,user_context\n"
                  "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,,1,\n"
                  "2001:db8:1::1,,200,200,8,100,0,7,0,1,1,host.example.com,,1,\n"
                  "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,300,300,6,150,"
                  "0,8,0,0,0,,,1,\n"
                  "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,0,200,8,0,2,"
                  "16,64,0,0,,,1,{ \"foobar\": true }\n"
                  "2001:db8:1::2,00,200,200,8,100,0,7,0,1,1,host.example.com,,0,\n"
                  "2001:db8:1::3,00,200,200,8,100,0,7,0,1,1,host.example.com,,1,\n");
}

// This test checks the capability to read and parse leases from the file.
TEST_F(CSVLeaseFile6Test, parse) {
    // Create a file to be parsed.
    writeSampleFile();

    // Open the lease file.
    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.open());

    // Verify the counters are cleared
    {
    SCOPED_TRACE("Check stats are empty");
    checkStats(lf, 0, 0, 0, 0, 0, 0);
    }

    Lease6Ptr lease;
    // Reading first read should be successful.
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 1, 1, 0, 0, 0, 0);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::1", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("host.example.com", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    // Second lease is malformed - DUID is blank (i.e. ",,")
    {
    SCOPED_TRACE("Second lease malformed");
    EXPECT_FALSE(lf.next(lease));
    checkStats(lf, 2, 1, 1, 0, 0, 0);
    }

    // Even, parsing previous lease failed, reading the next lease should be
    // successful.
    {
    SCOPED_TRACE("Third lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 3, 2, 1, 0, 0, 0);

    // Verify that the third lease is correct.
    EXPECT_EQ("2001:db8:2::10", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("01:01:01:01:0a:01:02:03:04:05", lease->duid_->toText());
    EXPECT_EQ(300, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(6, lease->subnet_id_);
    EXPECT_EQ(150, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(8, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    // Reading the fourth lease should be successful.
    {
    SCOPED_TRACE("Fourth lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 4, 3, 1, 0, 0, 0);

    // Verify that the lease is correct.
    EXPECT_EQ("3000:1::", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f", lease->duid_->toText());
    EXPECT_EQ(0, lease->valid_lft_);
    EXPECT_EQ(200, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(0, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_PD, lease->type_);
    EXPECT_EQ(16, lease->iaid_);
    EXPECT_EQ(64, lease->prefixlen_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());
    }


    // Fifth lease is invalid - DUID is empty, state is not DECLINED
    {
    SCOPED_TRACE("Fifth lease invalid");
    EXPECT_FALSE(lf.next(lease));
    checkStats(lf, 5, 3, 2, 0, 0, 0);
    }

    // Reading the sixth lease should be successful.
    {
    SCOPED_TRACE("sixth lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 6, 4, 2, 0, 0, 0);

    // Verify that the lease is correct.
    EXPECT_EQ("2001:db8:1::3", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00", lease->duid_->toText());
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    }

    // There are no more leases. Reading should cause no error, but the returned
    // lease pointer should be NULL.
    {
    SCOPED_TRACE("Sixth read empty");
    EXPECT_TRUE(lf.next(lease));
    EXPECT_FALSE(lease);
    checkStats(lf, 7, 4, 2, 0, 0, 0);
    }

    // We should be able to do it again.
    {
    SCOPED_TRACE("Seventh read empty");
    EXPECT_TRUE(lf.next(lease));
    EXPECT_FALSE(lease);
    checkStats(lf, 8, 4, 2, 0, 0, 0);
    }
}

// This test checks creation of the lease file and writing leases.
TEST_F(CSVLeaseFile6Test, recreate) {
    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    // Verify the counters are cleared
    {
    SCOPED_TRACE("Check stats are empty");
    checkStats(lf, 0, 0, 0, 0, 0, 0);
    }

    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                               makeDUID(DUID0, sizeof(DUID0)),
                               7, 100, 200, 8, true, true,
                               "host.example.com"));
    lease->cltt_ = 0;
    {
    SCOPED_TRACE("First write");
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 1, 1, 0);
    }

    lease.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:2::10"),
                           makeDUID(DUID1, sizeof(DUID1)),
                           8, 150, 300, 6, false, false,
                           "", HWAddrPtr(), 128));
    lease->cltt_ = 0;
    {
    SCOPED_TRACE("Second write");
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 2, 2, 0);
    }

    lease.reset(new Lease6(Lease::TYPE_PD, IOAddress("3000:1:1::"),
                           makeDUID(DUID0, sizeof(DUID0)),
                           7, 150, 300, 10, false, false,
                           "", HWAddrPtr(), 64));
    lease->cltt_ = 0;
    lease->setContext(Element::fromJSON("{ \"foobar\": true }"));
    {
    SCOPED_TRACE("Third write");
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 3, 3, 0);
    }

    DuidPtr empty(new DUID(DUID::EMPTY()));
    lease.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:2::10"),
                           empty, 8, 150, 300, 6, false, false,
                           "", HWAddrPtr(), 128));
    lease->cltt_ = 0;
    {
    SCOPED_TRACE("Fourth write - invalid, no DUID, not declined");
    ASSERT_THROW(lf.append(*lease), BadValue);
    checkStats(lf, 0, 0, 0, 4, 3, 1);
    }

    {
    SCOPED_TRACE("Fifth write - valid, no DUID, declined");
    lease->state_ = Lease::STATE_DECLINED;
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 5, 4, 1);
    }


    EXPECT_EQ("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
              "state,user_context\n"
              "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
              "200,200,8,100,0,7,128,1,1,host.example.com,,0,\n"
              "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05"
              ",300,300,6,150,0,8,128,0,0,,,0,\n"
              "3000:1:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
              "300,300,10,150,2,7,64,0,0,,,0,{ \"foobar\": true }\n"
              "2001:db8:2::10,00,300,300,6,150,0,8,128,0,0,,,1,\n",
              io_.readFile());
}

// Verifies that a 1.0 schema file with records from
// schema 1.0, 2.0, and 3.0 loads correctly.
TEST_F(CSVLeaseFile6Test, mixedSchemaLoad) {
    // Create a mixed schema file
    io_.writeFile(
             // schema 1.0 header
              "address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname\n"
              // schema 1.0 record
              "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:01,"
              "200,200,8,100,0,7,0,1,1,one.example.com\n"

              // schema 2.0 record - has hwaddr
              "2001:db8:1::2,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:02,"
              "200,200,8,100,0,7,0,1,1,two.example.com,01:02:03:04:05\n"

              // schema 3.0 record - has hwaddr and state
              "2001:db8:1::3,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03,"
              "200,200,8,100,0,7,0,1,1,three.example.com,0a:0b:0c:0d:0e,1\n"

              // schema 3.1 record - has hwaddr, state and user context
              "2001:db8:1::4,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03,"
              "200,200,8,100,0,7,0,1,1,three.example.com,0a:0b:0c:0d:0e,1,"
              "{ \"foobar\": true }\n");

    // Open the lease file.
    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.open());

    Lease6Ptr lease;
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::1", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:01", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("one.example.com", lease->hostname_);
    // Verify that added HWaddr is empty
    EXPECT_FALSE(lease->hwaddr_);
    // Verify that added state is STATE_DEFAULT
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    {
    SCOPED_TRACE("Second lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::2", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:02", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("two.example.com", lease->hostname_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("01:02:03:04:05", lease->hwaddr_->toText(false));
    // Verify that added state is STATE_DEFAULT
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    {
    SCOPED_TRACE("Third lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::3", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("three.example.com", lease->hostname_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("0a:0b:0c:0d:0e", lease->hwaddr_->toText(false));
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    {
    SCOPED_TRACE("Forth lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::4", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("three.example.com", lease->hostname_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("0a:0b:0c:0d:0e", lease->hwaddr_->toText(false));
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());
    }

}

// Verifies that a lease file with fewer header columns than the
// minimum allowed will not open.
TEST_F(CSVLeaseFile6Test, tooFewHeaderColumns) {
    io_.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev\n");

    // Open should fail.
    CSVLeaseFile6 lf(filename_);
    ASSERT_THROW(lf.open(), CSVFileError);
}

// Verifies that a lease file with an unrecognized column header
// will not open.
TEST_F(CSVLeaseFile6Test, invalidHeaderColumn) {
    io_.writeFile("address,BOGUS,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
              "hwaddr,state,user_context\n");

    // Open should fail.
    CSVLeaseFile6 lf(filename_);
    ASSERT_THROW(lf.open(), CSVFileError);
}

// Verifies that a lease file with more header columns than defined
// columns will open as needing a downgrade.
TEST_F(CSVLeaseFile6Test, downGrade) {
    // Create a mixed schema file
    io_.writeFile(
             // schema 1.0 header
              "address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
              "hwaddr,state,user_context,FUTURE_COL\n"

              // schema 3.1 record - has hwaddr, state and user context
              "2001:db8:1::3,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03,"
              "200,200,8,100,0,7,0,1,1,three.example.com,0a:0b:0c:0d:0e,1,"
              "{ \"foobar\": true },BOGUS\n");

    // Open should succeed in the event someone is downgrading.
    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.open());
    EXPECT_TRUE(lf.needsConversion());
    EXPECT_EQ(util::VersionedCSVFile::NEEDS_DOWNGRADE,
              lf.getInputSchemaState());


    Lease6Ptr lease;
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("2001:db8:1::3", lease->addr_.toText());
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:03", lease->duid_->toText());
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_EQ(100, lease->preferred_lft_);
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(7, lease->iaid_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("three.example.com", lease->hostname_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("0a:0b:0c:0d:0e", lease->hwaddr_->toText(false));
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());
    }
}

// Verifies that leases with no DUID are invalid, and that leases
// with the "Empty" DUID (1 byte duid = 0x0) are valid only when
// in the declined state.
TEST_F(CSVLeaseFile6Test, declinedLeaseTest) {
    io_.writeFile("address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr,state,user_context\n"
                  "2001:db8:1::1,00,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,,0,\n"
                  "2001:db8:1::1,,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,,0,\n"
                  "2001:db8:1::1,00,"
                  "200,200,8,100,0,7,0,1,1,host.example.com,,1,\n");

    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.open());
    EXPECT_FALSE(lf.needsConversion());
    EXPECT_EQ(util::VersionedCSVFile::CURRENT, lf.getInputSchemaState());
    Lease6Ptr lease;

    {
    SCOPED_TRACE("\"Empty\" DUID and not declined, invalid");
    EXPECT_FALSE(lf.next(lease));
    ASSERT_FALSE(lease);
    EXPECT_EQ(lf.getReadErrs(),1);
    }

    {
    SCOPED_TRACE("Missing (blank) DUID and not declined, invalid");
    EXPECT_FALSE(lf.next(lease));
    ASSERT_FALSE(lease);
    EXPECT_EQ(lf.getReadErrs(),2);
    }

    {
    SCOPED_TRACE("\"Empty\" DUID and declined, valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    EXPECT_EQ(lf.getReadErrs(),2);
    }
}


// Verifies that it is possible to output a lease with very high valid
// lifetime (infinite in RFC2131 terms) and current time, and then read
// back this lease.
TEST_F(CSVLeaseFile6Test, highLeaseLifetime) {
    CSVLeaseFile6 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    // Write lease with very high lease lifetime and current time.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                               makeDUID(DUID0, sizeof(DUID0)),
                               7, 100, 0xFFFFFFFF, 8, true, true,
                               "host.example.com"));

    // Write this lease out to the lease file.
    ASSERT_NO_THROW(lf.append(*lease));

    // Close the lease file.
    lf.close();

    Lease6Ptr lease_read;

    // Re-open the file for reading.
    ASSERT_NO_THROW(lf.open());

    // Read the lease and make sure it is successful.
    EXPECT_TRUE(lf.next(lease_read));
    ASSERT_TRUE(lease_read);

    // The valid lifetime and the cltt should match with the original lease.
    EXPECT_EQ(lease->valid_lft_, lease_read->valid_lft_);
    EXPECT_EQ(lease->cltt_, lease_read->cltt_);
}

/// @todo Currently we don't check invalid lease attributes, such as invalid
/// lease type, invalid preferred lifetime vs valid lifetime etc. The Lease6
/// should be extended with the function that validates lease attributes. Once
/// this is implemented we should provide more tests for malformed leases
/// in the CSV file. See http://oldkea.isc.org/ticket/2405.

} // end of anonymous namespace
