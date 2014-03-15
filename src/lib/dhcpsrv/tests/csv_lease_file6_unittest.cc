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
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/tests/lease_file_io.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

const uint8_t DUID0[] = { 0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
const uint8_t DUID1[] = { 1, 1, 1, 1, 0xa, 1, 2, 3, 4, 5 };

class CSVLeaseFile6Test : public ::testing::Test {
public:

    CSVLeaseFile6Test();

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    DuidPtr makeDUID(const uint8_t* duid, const unsigned int size) const {
        return (DuidPtr(new DUID(duid, size)));
    }

    std::string filename_;
    LeaseFileIO io_;

};

CSVLeaseFile6Test::CSVLeaseFile6Test()
    : filename_(absolutePath("leases6.csv")), io_(filename_) {
}

std::string
CSVLeaseFile6Test::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;
    return (s.str());
}


TEST_F(CSVLeaseFile6Test, recreate) {
    boost::scoped_ptr<CSVLeaseFile6> lf(new CSVLeaseFile6(filename_));
    ASSERT_NO_THROW(lf->recreate());
    ASSERT_TRUE(io_.exists());

    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                               makeDUID(DUID0, sizeof(DUID0)),
                               7, 100, 200, 50, 80, 8, true, true,
                               "host.example.com"));
    lease->cltt_ = 0;
    ASSERT_NO_THROW(lf->append(*lease));

    lease.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:2::10"),
                           makeDUID(DUID1, sizeof(DUID1)),
                           8, 150, 300, 40, 70, 6, false, false,
                           "", 128));
    lease->cltt_ = 0;
    ASSERT_NO_THROW(lf->append(*lease));

    lease.reset(new Lease6(Lease::TYPE_PD, IOAddress("3000:1:1::"),
                           makeDUID(DUID0, sizeof(DUID0)),
                           7, 150, 300, 40, 70, 10, false, false,
                           "", 64));
    lease->cltt_ = 0;
    ASSERT_NO_THROW(lf->append(*lease));

    EXPECT_EQ("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
              "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname\n"
              "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
              "200,200,8,100,0,7,0,1,1,host.example.com\n"
              "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05"
              ",300,300,6,150,0,8,128,0,0,\n"
              "3000:1:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
              "300,300,10,150,2,7,64,0,0,\n",
              io_.readFile());
}

} // end of anonymous namespace
