// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/duid.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/tests/lease_file_io.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

// HWADDR values used by unit tests.
const uint8_t HWADDR0[] = { 0, 1, 2, 3, 4, 5 };
const uint8_t HWADDR1[] = { 0xd, 0xe, 0xa, 0xd, 0xb, 0xe, 0xe, 0xf };

const uint8_t CLIENTID0[] = { 1, 2, 3, 4 };
const uint8_t CLIENTID1[] = { 0xa, 0xb, 0xc, 0xd };

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
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com,1\n"
                  "192.0.2.1,,a:11:01:04,200,200,8,1,1,host.example.com,1\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,100,7,"
                  "0,0,,2\n");
}

// This test checks the capability to read and parse leases from the file.
TEST_F(CSVLeaseFile4Test, parse) {
    // Create a file to be parsed.
    writeSampleFile();

    // Open the lease file.
    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    // Verify the counters are cleared
    {
    SCOPED_TRACE("Check stats are empty");
    checkStats(*lf, 0, 0, 0, 0, 0, 0);
    }

    Lease4Ptr lease;
    // Reading first read should be successful.
    {
    SCOPED_TRACE("First lease valid");
    EXPECT_TRUE(lf->next(lease));
    ASSERT_TRUE(lease);
    checkStats(*lf, 1, 1, 0, 0, 0, 0);

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
    }

    // Second lease is malformed - HW address is empty.
    {
    SCOPED_TRACE("Second lease malformed");
    EXPECT_FALSE(lf->next(lease));
    checkStats(*lf, 2, 1, 1, 0, 0, 0);
    }

    // Even though parsing previous lease failed, reading the next lease should be
    // successful.
    {
    SCOPED_TRACE("Third lease valid");
    EXPECT_TRUE(lf->next(lease));
    ASSERT_TRUE(lease);
    checkStats(*lf, 3, 2, 1, 0, 0, 0);

    // Verify that the third lease is correct.
    EXPECT_EQ("192.0.3.15", lease->addr_.toText());
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
    }

    // There are no more leases. Reading should cause no error, but the returned
    // lease pointer should be NULL.
    {
    SCOPED_TRACE("Fifth read empty");
    EXPECT_TRUE(lf->next(lease));
    EXPECT_FALSE(lease);
    checkStats(*lf, 4, 2, 1, 0, 0, 0);
    }

    // We should be able to do it again.
    {
    SCOPED_TRACE("Sixth read empty");
    EXPECT_TRUE(lf->next(lease));
    EXPECT_FALSE(lease);
    checkStats(*lf, 5, 2, 1, 0, 0, 0);
    }
}

// This test checks creation of the lease file and writing leases.
TEST_F(CSVLeaseFile4Test, recreate) {
    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->recreate());
    ASSERT_TRUE(io_.exists());

    // Verify the counters are cleared
    checkStats(*lf, 0, 0, 0, 0, 0, 0);

    // Create first lease, with NULL client id.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               hwaddr0_,
                               NULL, 0,
                               200, 50, 80, 0, 8, true, true,
                               "host.example.com"));
    lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    {
    SCOPED_TRACE("First write");
    ASSERT_NO_THROW(lf->append(*lease));
    checkStats(*lf, 0, 0, 0, 1, 1, 0);
    }

    // Create second lease, with non-NULL client id.
    lease.reset(new Lease4(IOAddress("192.0.3.10"),
                           hwaddr1_,
                           CLIENTID0, sizeof(CLIENTID0),
                           100, 60, 90, 0, 7));
    {
    SCOPED_TRACE("Second write");
    ASSERT_NO_THROW(lf->append(*lease));
    checkStats(*lf, 0, 0, 0, 2, 2, 0);
    }

    // Close the lease file.
    lf->close();
    // Check that the contents of the csv file are correct.
    EXPECT_EQ("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
              "fqdn_fwd,fqdn_rev,hostname,state\n"
              "192.0.3.2,00:01:02:03:04:05,,200,200,8,1,1,host.example.com,4\n"
              "192.0.3.10,0d:0e:0a:0d:0b:0e:0e:0f,01:02:03:04,100,100,7,0,"
              "0,,1\n",
              io_.readFile());
}

/// @todo Currently we don't check invalid lease attributes, such as invalid
/// lease type, invalid preferred lifetime vs valid lifetime etc. The Lease6
/// should be extended with the function that validates lease attributes. Once
/// this is implemented we should provide more tests for malformed leases
/// in the CSV file. See http://kea.isc.org/ticket/2405.

} // end of anonymous namespace
