// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/csv_lease_file4.h>
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

// HWADDR values used by unit tests.
const uint8_t HWADDR0[] = { 0, 1, 2, 3, 4, 5 };
const uint8_t HWADDR1[] = { 0xd, 0xe, 0xa, 0xd, 0xb, 0xe, 0xe, 0xf };

const uint8_t CLIENTID[] = { 1, 2, 3, 4 };

/// @brief Test fixture class for @c CSVLeaseFile4 validation.
class CSVLeaseFile4Test : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Initializes IO for lease file used by unit tests.
    CSVLeaseFile4Test();

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    /// @brief Creates the lease file to be parsed by unit tests.
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
    void checkStats(CSVLeaseFile4& lease_file,
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

    /// @brief hardware address 0 (corresponds to HWADDR0 const)
    HWAddrPtr hwaddr0_;

    /// @brief hardware address 1 (corresponds to HWADDR1 const)
    HWAddrPtr hwaddr1_;

};

CSVLeaseFile4Test::CSVLeaseFile4Test()
    : filename_(absolutePath("leases4.csv")), io_(filename_) {
    hwaddr0_.reset(new HWAddr(HWADDR0, sizeof(HWADDR0), HTYPE_ETHER));
    hwaddr1_.reset(new HWAddr(HWADDR1, sizeof(HWADDR1), HTYPE_ETHER));
}

std::string
CSVLeaseFile4Test::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << DHCP_DATA_DIR << "/" << filename;
    return (s.str());
}

void
CSVLeaseFile4Test::writeSampleFile() const {
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com,0,\n"
                  "192.0.2.2,,,200,200,8,1,1,host.example.com,0,\n"
                  "192.0.2.3,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,100,7,"
                  "0,0,,1,{ \"foobar\": true }\n"
                  "192.0.2.4,,11:22:33:44:55:66,200,200,8,1,1,host.example.com,0,\n"
                  "192.0.2.5,,,200,200,8,1,1,,1,\n");
}

// This test checks the capability to read and parse leases from the file.
TEST_F(CSVLeaseFile4Test, parse) {
    // Create a file to be parsed.
    writeSampleFile();

    // Open the lease file.
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.open());

    // Verify the counters are cleared
    {
    SCOPED_TRACE("Check stats are empty");
    checkStats(lf, 0, 0, 0, 0, 0, 0);
    }

    Lease4Ptr lease;
    // Reading first read should be successful.
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 1, 1, 0, 0, 0, 0);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("192.0.2.1", lease->addr_.toText());
    HWAddr hwaddr1(*lease->hwaddr_);
    EXPECT_EQ("06:07:08:09:0a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("host.example.com", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    // Second lease is malformed - has no HW address or client id and state
    // is not declined.
    {
    SCOPED_TRACE("Second lease malformed");
    EXPECT_FALSE(lf.next(lease));
    EXPECT_FALSE(lease);
    checkStats(lf, 2, 1, 1, 0, 0, 0);
    }

    // Even though parsing previous lease failed, reading the next lease should be
    // successful.
    {
    SCOPED_TRACE("Third lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 3, 2, 1, 0, 0, 0);

    // Verify that the third lease is correct.
    EXPECT_EQ("192.0.2.3", lease->addr_.toText());
    HWAddr hwaddr3(*lease->hwaddr_);
    EXPECT_EQ("dd:de:ba:0d:1b:2e:3e:4f", hwaddr3.toText(false));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_EQ("0a:00:01:04", lease->client_id_->toText());
    EXPECT_EQ(100, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(7, lease->subnet_id_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());
    }

    // Fourth lease has no hardware address but has client id
    {
    SCOPED_TRACE("Fourth lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 4, 3, 1, 0, 0, 0);

    EXPECT_EQ("192.0.2.4", lease->addr_.toText());
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(lease->hwaddr_->hwaddr_.empty());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_EQ("11:22:33:44:55:66", lease->client_id_->toText());
    }

    // Fifth lease has no hardware address or client id but is declined
    {
    SCOPED_TRACE("Fifth lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    checkStats(lf, 5, 4, 1, 0, 0, 0);

    EXPECT_EQ("192.0.2.5", lease->addr_.toText());
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(lease->hwaddr_->hwaddr_.empty());
    ASSERT_FALSE(lease->client_id_);
    EXPECT_EQ(lease->state_, Lease::STATE_DECLINED);
    }

    // There are no more leases. Reading should cause no error, but the returned
    // lease pointer should be NULL.
    {
    SCOPED_TRACE("Sixth read empty");
    EXPECT_TRUE(lf.next(lease));
    EXPECT_FALSE(lease);
    checkStats(lf, 6, 4, 1, 0, 0, 0);
    }

    // We should be able to do it again.
    {
    SCOPED_TRACE("Seventh read empty");
    EXPECT_TRUE(lf.next(lease));
    EXPECT_FALSE(lease);
    checkStats(lf, 7, 4, 1, 0, 0, 0);
    }
}

// This test checks creation of the lease file and writing leases.
TEST_F(CSVLeaseFile4Test, recreate) {
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    // Verify the counters are cleared
    checkStats(lf, 0, 0, 0, 0, 0, 0);

    // Create first lease, with NULL client id.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               200, 0, 8, true, true,
                               "host.example.com"));
    lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    {
    SCOPED_TRACE("First write");
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 1, 1, 0);
    }

    // Create second lease, with non-NULL client id and user context.
    lease.reset(new Lease4(IOAddress("192.0.3.10"),
                           hwaddr1_,
                           CLIENTID, sizeof(CLIENTID),
                           100, 0, 7));
    lease->setContext(Element::fromJSON("{ \"foobar\": true }"));
    {
    SCOPED_TRACE("Second write");
    ASSERT_NO_THROW(lf.append(*lease));
    checkStats(lf, 0, 0, 0, 2, 2, 0);
    }

    // Close the lease file.
    lf.close();
    // Check that the contents of the csv file are correct.
    EXPECT_EQ("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
              "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
              "192.0.3.2,00:01:02:03:04:05,,200,200,8,1,1,host.example.com,"
              "2,\n"
              "192.0.3.10,0d:0e:0a:0d:0b:0e:0e:0f,01:02:03:04,100,100,7,0,"
              "0,,0,{ \"foobar\": true }\n",
              io_.readFile());
}

// Verifies that a schema 1.0 file with records from
// schema 1.0 and 2.0 loads correctly.
TEST_F(CSVLeaseFile4Test, mixedSchemaload) {
    // Create mixed schema file
    io_.writeFile(
                  // schema 1.0 header
                  "address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  // schema 1.0 record
                  "192.0.2.1,06:07:08:09:1a:bc,,200,200,8,1,1,"
                  "one.example.com\n"
                  // schema 2.0 record - has state
                  "192.0.2.2,06:07:08:09:2a:bc,,200,200,8,1,1,"
                  "two.example.com,1\n"
                  // schema 2.1 record - has state and user context
                  "192.0.2.3,06:07:08:09:3a:bc,,200,200,8,1,1,"
                  "three.example.com,2,{ \"foobar\": true }\n"
                   );

    // Open the lease file.
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.open());

    Lease4Ptr lease;

    // Reading first read should be successful.
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("192.0.2.1", lease->addr_.toText());
    HWAddr hwaddr1(*lease->hwaddr_);
    EXPECT_EQ("06:07:08:09:1a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("one.example.com", lease->hostname_);
    // Verify that added state is DEFAULT
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    {
    SCOPED_TRACE("Second lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("192.0.2.2", lease->addr_.toText());
    HWAddr hwaddr1(*lease->hwaddr_);
    EXPECT_EQ("06:07:08:09:2a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("two.example.com", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }

    {
    SCOPED_TRACE("Third lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the third lease is correct.
    EXPECT_EQ("192.0.2.3", lease->addr_.toText());
    HWAddr hwaddr1(*lease->hwaddr_);
    EXPECT_EQ("06:07:08:09:3a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("three.example.com", lease->hostname_);
    EXPECT_EQ(Lease::STATE_EXPIRED_RECLAIMED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": true }", lease->getContext()->str());
    }
}


// Verifies that a lease file with fewer header columns than the
// minimum allowed will not open.
TEST_F(CSVLeaseFile4Test, tooFewHeaderColumns) {
    // Create 1.0 file
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev\n");

    // Open the lease file.
    CSVLeaseFile4 lf(filename_);
    ASSERT_THROW(lf.open(), CSVFileError);
}

// Verifies that a lease file with an unrecognized column header
// will not open.
TEST_F(CSVLeaseFile4Test, invalidHeaderColumn) {
    // Create 1.0 file
    io_.writeFile("address,hwaddr,BOGUS,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n");

    // Open the lease file.
    CSVLeaseFile4 lf(filename_);
    ASSERT_THROW(lf.open(), CSVFileError);
}

// Verifies that a lease file with more header columns than defined
// columns will downgrade.
TEST_F(CSVLeaseFile4Test, downGrade) {
    // Create 2.0 PLUS a column file
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context,FUTURE_COL\n"

                  "192.0.2.3,06:07:08:09:3a:bc,,200,200,8,1,1,"
                  "three.example.com,2,,BOGUS\n");

    // Lease file should open and report as needing downgrade.
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.open());
    EXPECT_TRUE(lf.needsConversion());
    EXPECT_EQ(util::VersionedCSVFile::NEEDS_DOWNGRADE,
              lf.getInputSchemaState());
    Lease4Ptr lease;

    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);

    // Verify that the third lease is correct.
    EXPECT_EQ("192.0.2.3", lease->addr_.toText());
    HWAddr hwaddr1(*lease->hwaddr_);
    EXPECT_EQ("06:07:08:09:3a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("three.example.com", lease->hostname_);
    EXPECT_EQ(Lease::STATE_EXPIRED_RECLAIMED, lease->state_);
    EXPECT_FALSE(lease->getContext());
    }
}

// Verifies that leases with no hardware address are only permitted
// if they are in the declined state.
TEST_F(CSVLeaseFile4Test, declinedLeaseTest) {
    io_.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.1,,,200,200,8,1,1,host.example.com,0,\n"
                  "192.0.2.1,,,200,200,8,1,1,host.example.com,1,\n");

    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.open());
    EXPECT_FALSE(lf.needsConversion());
    EXPECT_EQ(util::VersionedCSVFile::CURRENT, lf.getInputSchemaState());
    Lease4Ptr lease;

    {
    SCOPED_TRACE("No hardware and not declined, invalid");
    EXPECT_FALSE(lf.next(lease));
    ASSERT_FALSE(lease);
    EXPECT_EQ(lf.getReadErrs(),1);
    }

    {
    SCOPED_TRACE("No hardware and declined, valid");
    EXPECT_TRUE(lf.next(lease));
    ASSERT_TRUE(lease);
    EXPECT_EQ(lf.getReadErrs(),1);
    }
}

// Verifies that it is possible to output a lease with very high valid
// lifetime (infinite in RFC2131 terms) and current time, and then read
// back this lease.
TEST_F(CSVLeaseFile4Test, highLeaseLifetime) {
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    // Write lease with very high lease lifetime and current time.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               0xFFFFFFFF, time(0),
                               8, true, true,
                               "host.example.com"));
    // Write this lease out to the lease file.
    ASSERT_NO_THROW(lf.append(*lease));

    // Close the lease file.
    lf.close();

    Lease4Ptr lease_read;

    // Re-open the file for reading.
    ASSERT_NO_THROW(lf.open());

    // Read the lease and make sure it is successful.
    EXPECT_TRUE(lf.next(lease_read));
    ASSERT_TRUE(lease_read);

    // The valid lifetime and the cltt should match with the original lease.
    EXPECT_EQ(lease->valid_lft_, lease_read->valid_lft_);
    EXPECT_EQ(lease->cltt_, lease_read->cltt_);
}

// Verifies that it is not possible to output a lease with empty hwaddr in other
// than the declined state
TEST_F(CSVLeaseFile4Test, emptyHWAddrDefaultStateOnly) {
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    HWAddrPtr hwaddr;

    // Create lease with null hwaddr and default state
    Lease4Ptr lease_null_hwaddr(new Lease4(IOAddress("192.0.3.2"),
                                hwaddr,
                                NULL, 0,
                                0xFFFFFFFF, time(0),
                                8, true, true,
                                "host.example.com"));
    // Try to write this lease out to the lease file.
    ASSERT_THROW(lf.append(*lease_null_hwaddr), BadValue);

    hwaddr.reset(new HWAddr());

    // Create lease with empty hwaddr and default state
    Lease4Ptr lease_empty_hwaddr(new Lease4(IOAddress("192.0.3.2"),
                                 hwaddr,
                                 NULL, 0,
                                 0xFFFFFFFF, time(0),
                                 8, true, true,
                                 "host.example.com"));
    // Try to write this lease out to the lease file.
    ASSERT_THROW(lf.append(*lease_empty_hwaddr), BadValue);

    // Create lease with hwaddr and current time.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               0xFFFFFFFF, time(0),
                               8, true, true,
                               "host.example.com"));

    // Decline the lease
    lease->decline(1000);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ(lease->hwaddr_->toText(false), "");

    // Write this lease out to the lease file.
    ASSERT_NO_THROW(lf.append(*lease));

    // Close the lease file.
    lf.close();

    Lease4Ptr lease_read;

    // Re-open the file for reading.
    ASSERT_NO_THROW(lf.open());

    // Read the lease and make sure it is successful.
    EXPECT_TRUE(lf.next(lease_read));
    ASSERT_TRUE(lease_read);

    // The valid lifetime and the cltt should match with the original lease.
    EXPECT_EQ(lease->valid_lft_, lease_read->valid_lft_);
    EXPECT_EQ(lease->cltt_, lease_read->cltt_);
}

// Verifies that it is possible to write and read a lease with commas
// in hostname and user context.
TEST_F(CSVLeaseFile4Test, embeddedCommas) {
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    std::string hostname("host,example,com");
    std::string context_str("{ \"bar\": true, \"foo\": false, \"x\": \"factor\" }");

    // Create a lease with commas in the hostname.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               0xFFFFFFFF, time(0),
                               8, true, true,
                               hostname));

    // Add the user context with commas.
    lease->setContext(Element::fromJSON(context_str));

    // Write this lease out to the lease file.
    ASSERT_NO_THROW(lf.append(*lease));

    // Close the lease file.
    lf.close();

    Lease4Ptr lease_read;

    // Re-open the file for reading.
    ASSERT_NO_THROW(lf.open());

    // Read the lease and make sure it is successful.
    EXPECT_TRUE(lf.next(lease_read));
    ASSERT_TRUE(lease_read);

    // Expect the hostname and user context to retain the commas
    // they started with.
    EXPECT_EQ(hostname, lease->hostname_);
    EXPECT_EQ(context_str, lease->getContext()->str());
}

// Verifies that it is possible to write and read a lease with
// escape tags and sequences in hostname and user context.
TEST_F(CSVLeaseFile4Test, embeddedEscapes) {
    CSVLeaseFile4 lf(filename_);
    ASSERT_NO_THROW(lf.recreate());
    ASSERT_TRUE(io_.exists());

    std::string hostname("host&#xexample&#x2ccom");
    std::string context_str("{ \"&#xbar\": true, \"foo\": false, \"x\": \"fac&#x2ctor\" }");

    // Create a lease with commas in the hostname.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               0xFFFFFFFF, time(0),
                               8, true, true,
                               hostname));

    // Add the user context with commas.
    lease->setContext(Element::fromJSON(context_str));

    // Write this lease out to the lease file.
    ASSERT_NO_THROW(lf.append(*lease));

    // Close the lease file.
    lf.close();

    Lease4Ptr lease_read;

    // Re-open the file for reading.
    ASSERT_NO_THROW(lf.open());

    // Read the lease and make sure it is successful.
    EXPECT_TRUE(lf.next(lease_read));
    ASSERT_TRUE(lease_read);

    // Expect the hostname and user context to retain the commas
    // they started with.
    EXPECT_EQ(hostname, lease->hostname_);
    EXPECT_EQ(context_str, lease->getContext()->str());
}

/// @todo Currently we don't check invalid lease attributes, such as invalid
/// lease type, invalid preferred lifetime vs valid lifetime etc. The Lease6
/// should be extended with the function that validates lease attributes. Once
/// this is implemented we should provide more tests for malformed leases
/// in the CSV file. See http://oldkea.isc.org/ticket/2405.

} // end of anonymous namespace
