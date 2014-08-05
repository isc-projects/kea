// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

    /// @brief Name of the test lease file.
    std::string filename_;

    /// @brief Object providing access to lease file IO.
    LeaseFileIO io_;

};

CSVLeaseFile4Test::CSVLeaseFile4Test()
    : filename_(absolutePath("leases4.csv")), io_(filename_) {
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
                  "fqdn_fwd,fqdn_rev,hostname\n"
                  "192.0.2.1,06:07:08:09:0a:bc,,200,200,8,1,1,"
                  "host.example.com\n"
                  "192.0.2.1,,a:11:01:04,200,200,8,1,1,host.example.com\n"
                  "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,100,100,7,"
                  "0,0,\n");
}

// This test checks the capability to read and parse leases from the file.
TEST_F(CSVLeaseFile4Test, parse) {
    // Create a file to be parsed.
    writeSampleFile();

    // Open the lease file.
    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->open());

    Lease4Ptr lease;
    // Reading first read should be successful.
    EXPECT_TRUE(lf->next(lease));
    ASSERT_TRUE(lease);

    // Verify that the lease attributes are correct.
    EXPECT_EQ("192.0.2.1", lease->addr_.toText());
    HWAddr hwaddr1(lease->hwaddr_, HTYPE_ETHER);
    EXPECT_EQ("06:07:08:09:0a:bc", hwaddr1.toText(false));
    EXPECT_FALSE(lease->client_id_);
    EXPECT_EQ(200, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(8, lease->subnet_id_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("host.example.com", lease->hostname_);

    // Second lease is malformed - HW address is empty.
    EXPECT_FALSE(lf->next(lease));

    // Even though parsing previous lease failed, reading the next lease should be
    // successful.
    EXPECT_TRUE(lf->next(lease));
    ASSERT_TRUE(lease);
    // Verify that the third lease is correct.
    EXPECT_EQ("192.0.3.15", lease->addr_.toText());
    HWAddr hwaddr3(lease->hwaddr_, HTYPE_ETHER);
    EXPECT_EQ("dd:de:ba:0d:1b:2e:3e:4f", hwaddr3.toText(false));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_EQ("0a:00:01:04", lease->client_id_->toText());
    EXPECT_EQ(100, lease->valid_lft_);
    EXPECT_EQ(0, lease->cltt_);
    EXPECT_EQ(7, lease->subnet_id_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_TRUE(lease->hostname_.empty());

    // There are no more leases. Reading should cause no error, but the returned
    // lease pointer should be NULL.
    EXPECT_TRUE(lf->next(lease));
    EXPECT_FALSE(lease);

    // We should be able to do it again.
    EXPECT_TRUE(lf->next(lease));
    EXPECT_FALSE(lease);

}

// This test checks creation of the lease file and writing leases.
TEST_F(CSVLeaseFile4Test, recreate) {
    boost::scoped_ptr<CSVLeaseFile4> lf(new CSVLeaseFile4(filename_));
    ASSERT_NO_THROW(lf->recreate());
    ASSERT_TRUE(io_.exists());
    // Create first lease, with NULL client id.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.3.2"),
                               HWADDR0, sizeof(HWADDR0),
                               NULL, 0,
                               200, 50, 80, 0, 8, true, true,
                               "host.example.com"));
    ASSERT_NO_THROW(lf->append(*lease));
    // Create second lease, with non-NULL client id.
    lease.reset(new Lease4(IOAddress("192.0.3.10"),
                           HWADDR1, sizeof(HWADDR1),
                           CLIENTID0, sizeof(CLIENTID0),
                           100, 60, 90, 0, 7));
    ASSERT_NO_THROW(lf->append(*lease));
    // Close the lease file.
    lf->close();
    // Check that the contents of the csv file are correct.
    EXPECT_EQ("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
              "fqdn_fwd,fqdn_rev,hostname\n"
              "192.0.3.2,00:01:02:03:04:05,,200,200,8,1,1,host.example.com\n"
              "192.0.3.10,0d:0e:0a:0d:0b:0e:0e:0f,01:02:03:04,100,100,7,0,"
              "0,\n",
              io_.readFile());
}

/// @todo Currently we don't check invalid lease attributes, such as invalid
/// lease type, invalid preferred lifetime vs valid lifetime etc. The Lease6
/// should be extended with the function that validates lease attributes. Once
/// this is implemented we should provide more tests for malformed leases
/// in the CSV file. See http://kea.isc.org/ticket/2405.

} // end of anonymous namespace
