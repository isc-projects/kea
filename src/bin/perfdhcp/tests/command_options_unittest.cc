// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include <stdint.h>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

#include "command_options_helper.h"

using namespace std;
using namespace isc;
using namespace isc::perfdhcp;
using namespace boost::posix_time;

// Verify that default constructor sets lease type to the expected value.
TEST(LeaseTypeTest, defaultConstructor) {
    CommandOptions::LeaseType lease_type;
    EXPECT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));
}

// Verify that the constructor sets the lease type to the specified value.
TEST(LeaseTypeTest, constructor) {
    CommandOptions::LeaseType
        lease_type1(CommandOptions::LeaseType::ADDRESS);
    EXPECT_TRUE(lease_type1.is(CommandOptions::LeaseType::ADDRESS));

    CommandOptions::LeaseType
        lease_type2(CommandOptions::LeaseType::PREFIX);
    EXPECT_TRUE(lease_type2.is(CommandOptions::LeaseType::PREFIX));
}

// Verify that the lease type can be modified using set() function.
TEST(LeaseTypeTest, set) {
    CommandOptions::LeaseType
        lease_type(CommandOptions::LeaseType::ADDRESS);
    EXPECT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));

    lease_type.set(CommandOptions::LeaseType::PREFIX);
    EXPECT_TRUE(lease_type.is(CommandOptions::LeaseType::PREFIX));
}

// Verify that the includes() function returns true when the lease type
// specified with the function argument is the same as the lease type
// encapsulated by the LeaseType object on which include function is called
// or when the lease type value encapsulated by this object is
// ADDRESS_AND_PREFIX.
TEST(LeaseTypeTest, includes) {
    // Lease type: ADDRESS
    CommandOptions::LeaseType lease_type(CommandOptions::LeaseType::ADDRESS);
    // Lease type IS ADDRESS.
    ASSERT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));
    // Lease type includes the ADDRESS.
    EXPECT_TRUE(lease_type.includes(CommandOptions::LeaseType::ADDRESS));
    // Lease type does not include PREFIX.
    EXPECT_FALSE(lease_type.includes(CommandOptions::LeaseType::PREFIX));
    // Lease type does not include ADDRESS_AND_PREFIX.
    EXPECT_FALSE(
        lease_type.includes(CommandOptions::LeaseType::ADDRESS_AND_PREFIX)
    );

    // Do the same check for PREFIX.
    lease_type.set(CommandOptions::LeaseType::PREFIX);
    EXPECT_FALSE(lease_type.includes(CommandOptions::LeaseType::ADDRESS));
    EXPECT_TRUE(lease_type.includes(CommandOptions::LeaseType::PREFIX));
    EXPECT_FALSE(
        lease_type.includes(CommandOptions::LeaseType::ADDRESS_AND_PREFIX)
    );

    // When lease type is set to 'address-and-prefix' it means that client
    // requests both address and prefix (IA_NA and IA_PD). Therefore, the
    // LeaseType::includes() function should return true for both ADDRESS
    // and PREFIX.
    lease_type.set(CommandOptions::LeaseType::ADDRESS_AND_PREFIX);
    EXPECT_TRUE(lease_type.includes(CommandOptions::LeaseType::ADDRESS));
    EXPECT_TRUE(lease_type.includes(CommandOptions::LeaseType::PREFIX));
    EXPECT_TRUE(
        lease_type.includes(CommandOptions::LeaseType::ADDRESS_AND_PREFIX)
    );

}

// Verify that the LeaseType::fromCommandLine() function parses the lease-type
// argument specified as -e<lease-type>.
TEST(LeaseTypeTest, fromCommandLine) {
    CommandOptions::LeaseType
        lease_type(CommandOptions::LeaseType::ADDRESS);
    ASSERT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));

    lease_type.fromCommandLine("prefix-only");
    ASSERT_TRUE(lease_type.is(CommandOptions::LeaseType::PREFIX));

    lease_type.fromCommandLine("address-only");
    EXPECT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));

    lease_type.fromCommandLine("address-and-prefix");
    EXPECT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS_AND_PREFIX));

    EXPECT_THROW(lease_type.fromCommandLine("bogus-parameter"),
                 isc::InvalidParameter);

}

// Verify that the LeaseType::toText() function returns the textual
// representation of the lease type specified.
TEST(LeaseTypeTest, toText) {
    CommandOptions::LeaseType lease_type;
    ASSERT_TRUE(lease_type.is(CommandOptions::LeaseType::ADDRESS));
    EXPECT_EQ("address-only (IA_NA option added to the client's request)",
              lease_type.toText());

    lease_type.set(CommandOptions::LeaseType::PREFIX);
    EXPECT_EQ("prefix-only (IA_PD option added to the client's request)",
              lease_type.toText());

    lease_type.set(CommandOptions::LeaseType::ADDRESS_AND_PREFIX);
    EXPECT_EQ("address-and-prefix (Both IA_NA and IA_PD options added to the"
              " client's request)", lease_type.toText());

}

/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp CommandOptions class.
class CommandOptionsTest : public virtual ::testing::Test
{
public:
    /// \brief Default Constructor
    CommandOptionsTest() { }

protected:
    /// \brief Parse command line and cleanup
    ///
    /// The method tokenizes command line to array of C-strings,
    /// parses arguments using CommandOptions class to set
    /// its data members and de-allocates array of C-strings.
    ///
    /// \param cmdline Command line to parse.
    /// \throws std::bad allocation if tokenization failed.
    /// \return true if program has been run in help or version mode ('h' or 'v' flag).
    bool process(CommandOptions& opt, const std::string& cmdline) {
        return (CommandOptionsHelper::process(opt, cmdline));
    }

    /// \brief Get full path to a file in testdata directory.
    ///
    /// \param filename filename being appended to absolute
    /// path to testdata directory
    ///
    /// \return full path to a file in testdata directory.
    std::string getFullPath(const std::string& filename) const {
        std::ostringstream stream;
        stream << TEST_DATA_DIR << "/" << filename;
        return (stream.str());
    }
};

TEST_F(CommandOptionsTest, Defaults) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp 192.168.0.1"));
    EXPECT_EQ(4, opt.getIpVersion());
    EXPECT_EQ(CommandOptions::DORA_SARR, opt.getExchangeMode());
    EXPECT_TRUE(opt.getLeaseType().is(CommandOptions::LeaseType::ADDRESS));
    EXPECT_EQ(0, opt.getRate());
    EXPECT_EQ(0, opt.getRenewRate());
    EXPECT_EQ(0, opt.getReleaseRate());
    EXPECT_EQ(0, opt.getReportDelay());
    EXPECT_EQ(0, opt.getClientsNum());

    // default mac
    const uint8_t mac[6] = { 0x00, 0x0C, 0x01, 0x02, 0x03, 0x04 };
    std::vector<uint8_t> v1 = opt.getMacTemplate();
    ASSERT_EQ(6, v1.size());
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));

    // Check if DUID is initialized. The DUID-LLT is expected
    // to start with DUID_LLT value of 1 and hardware ethernet
    // type equal to 1 (HWETHER_TYPE).
    const uint8_t duid_llt_and_hw[4] = { 0x0, 0x1, 0x0, 0x1 };
    // We assume DUID-LLT length 14. This includes 4 octets of
    // DUID_LLT value, two octets of hardware type, 4 octets
    // of time value and 6 octets of variable link layer (MAC)
    // address.
    const int duid_llt_size = 14;
    // DUID is not given from the command line but it is supposed
    // to be initialized by the CommandOptions private method
    // generateDuidTemplate().
    std::vector<uint8_t> v2 = opt.getDuidTemplate();
    ASSERT_EQ(duid_llt_size, opt.getDuidTemplate().size());
    EXPECT_TRUE(std::equal(v2.begin(), v2.begin() + 4,
                           duid_llt_and_hw));
    // Check time field contents.
    ptime now = microsec_clock::universal_time();
    ptime duid_epoch(from_iso_string("20000101T000000"));
    time_period period(duid_epoch, now);
    uint32_t duration_sec = period.length().total_seconds();
    // Read time from the template generated.
    uint32_t duration_from_template = 0;
    memcpy(&duration_from_template, &v2[4], 4);
    duration_from_template = htonl(duration_from_template);
    // In special cases, we may have overflow in time field
    // so we give ourselves the margin of 10 seconds here.
    // If time value has been set more then 10 seconds back
    // it is safe to compare it with the time value generated
    // from now.
    if (duration_from_template > 10) {
        EXPECT_GE(duration_sec, duration_from_template);
    }

    EXPECT_EQ(0, opt.getBase().size());
    EXPECT_EQ(0, opt.getNumRequests().size());
    EXPECT_EQ(0, opt.getPeriod());
    for (size_t i = 0; i < opt.getDropTime().size(); ++i) {
        EXPECT_DOUBLE_EQ(1, opt.getDropTime()[i]);
    }
    ASSERT_EQ(opt.getMaxDrop().size(), opt.getMaxDropPercentage().size());
    for (size_t i = 0; i < opt.getMaxDrop().size(); ++i) {
        EXPECT_EQ(0, opt.getMaxDrop()[i]);
        EXPECT_EQ(0, opt.getMaxDropPercentage()[i]);
    }
    EXPECT_EQ("", opt.getLocalName());
    EXPECT_FALSE(opt.isInterface());
    EXPECT_EQ(0, opt.getPreload());
    EXPECT_EQ(0, opt.getLocalPort());
    EXPECT_FALSE(opt.isSeeded());
    EXPECT_EQ(0, opt.getSeed());
    EXPECT_FALSE(opt.isBroadcast());
    EXPECT_FALSE(opt.isRapidCommit());
    EXPECT_FALSE(opt.isUseFirst());
    EXPECT_FALSE(opt.getAddrUnique());
    EXPECT_EQ(-1, opt.getIncreaseElapsedTime());
    EXPECT_EQ(-1, opt.getWaitForElapsedTime());
    EXPECT_EQ(0, opt.getTemplateFiles().size());
    EXPECT_EQ(0, opt.getTransactionIdOffset().size());
    EXPECT_EQ(0, opt.getRandomOffset().size());
    EXPECT_GT(0, opt.getElapsedTimeOffset());
    EXPECT_GT(0, opt.getServerIdOffset());
    EXPECT_GT(0, opt.getRequestedIpOffset());
    EXPECT_EQ("", opt.getDiags());
    EXPECT_EQ("", opt.getWrapped());
    EXPECT_EQ("192.168.0.1", opt.getServerName());
}

TEST_F(CommandOptionsTest, HelpVersion) {
    // The parser is supposed to return true if 'h' or 'v' options
    // are specified.
    CommandOptions opt;
    EXPECT_TRUE(process(opt, "perfdhcp -h"));
    EXPECT_TRUE(process(opt, "perfdhcp -v"));
    EXPECT_TRUE(process(opt, "perfdhcp -h -v"));
    EXPECT_TRUE(process(opt, "perfdhcp -6 -l ethx -h all"));
    EXPECT_TRUE(process(opt, "perfdhcp -l ethx -v all"));
    // No 'h' or 'v' option specified. The false value
    // should be returned.
    EXPECT_FALSE(process(opt, "perfdhcp -l ethx all"));
}

TEST_F(CommandOptionsTest, CheckAddressUniqueness) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -u -l ethx all"));
    EXPECT_TRUE(opt.getAddrUnique());
}

TEST_F(CommandOptionsTest, UseFirst) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -1 -B -l ethx all"));
    EXPECT_TRUE(opt.isUseFirst());
}

TEST_F(CommandOptionsTest, UseCleanOutput) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -C, -l ethx all"));
    EXPECT_TRUE(opt.getCleanReport());
    EXPECT_EQ(",", opt.getCleanReportSeparator());
}

TEST_F(CommandOptionsTest, UseRelayV6) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    // -4 and -A must not coexist
    EXPECT_THROW(process(opt, "perfdhcp -4 -A1 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, IpVersion) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -l ethx -c -i all"));
    EXPECT_EQ(6, opt.getIpVersion());
    EXPECT_EQ("ethx", opt.getLocalName());
    EXPECT_TRUE(opt.isRapidCommit());
    EXPECT_FALSE(opt.isBroadcast());
    process(opt, "perfdhcp -4 -B -l ethx all");
    EXPECT_EQ(4, opt.getIpVersion());
    EXPECT_TRUE(opt.isBroadcast());
    EXPECT_FALSE(opt.isRapidCommit());

    // Negative test cases
    // -4 and -6 must not coexist
    EXPECT_THROW(process(opt, "perfdhcp -4 -6 -l ethx all"), isc::InvalidParameter);
    // -6 and -B must not coexist
    EXPECT_THROW(process(opt, "perfdhcp -6 -B -l ethx all"), isc::InvalidParameter);
    // -c and -4 (default) must not coexist
    EXPECT_THROW(process(opt, "perfdhcp -c -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, LeaseType) {
    CommandOptions opt;
    // Check that the -e address-only works for IPv6.
    ASSERT_NO_THROW(process(opt, "perfdhcp -6 -l etx -e address-only all"));
    EXPECT_EQ(6, opt.getIpVersion());
    EXPECT_EQ("etx", opt.getLocalName());
    EXPECT_TRUE(opt.getLeaseType().is(CommandOptions::LeaseType::ADDRESS));
    // Check that the -e address-only works for IPv4.
    ASSERT_NO_THROW(process(opt, "perfdhcp -4 -l etx -e address-only all"));
    EXPECT_EQ(4, opt.getIpVersion());
    EXPECT_EQ("etx", opt.getLocalName());
    EXPECT_TRUE(opt.getLeaseType().is(CommandOptions::LeaseType::ADDRESS));
    // Check that the -e prefix-only works.
    ASSERT_NO_THROW(process(opt, "perfdhcp -6 -l etx -e prefix-only all"));
    EXPECT_EQ(6, opt.getIpVersion());
    EXPECT_EQ("etx", opt.getLocalName());
    EXPECT_TRUE(opt.getLeaseType().is(CommandOptions::LeaseType::PREFIX));
    // Check that -e prefix-only must not coexist with -4 option.
    EXPECT_THROW(process(opt, "perfdhcp -4 -l ethx -e prefix-only all"),
                 InvalidParameter);
    // Check that -e prefix-only must not coexist with -T options.
    EXPECT_THROW(process(opt, "perfdhcp -6 -l ethx -e prefix-only -T file1.hex"
                         " -T file2.hex -E 4 all"), InvalidParameter);

}

TEST_F(CommandOptionsTest, Rate) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -4 -r 10 -l ethx all"));
    EXPECT_EQ(10, opt.getRate());

    // Negative test cases
    // Rate must not be 0
    EXPECT_THROW(process(opt, "perfdhcp -4 -r 0 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, RenewRate) {
    CommandOptions opt;
    // If -f is specified together with -r the command line should
    // be accepted and the renew rate should be set.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -r 10 -f 10 -l ethx all"));
    EXPECT_EQ(10, opt.getRenewRate());
    // Check that the release rate can be set to different value than
    // rate specified as -r<rate>. Also, swap -f and -r to make sure
    // that order doesn't matter.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -f 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getRenewRate());
    // Renew rate should also be accepted for DHCPv4 case.
    EXPECT_NO_THROW(process(opt, "perfdhcp -4 -f 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getRenewRate());
    // The renew rate should not be greater than the rate.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -f 11 -l ethx all"),
                 isc::InvalidParameter);
    // The renew-rate of 0 is invalid.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -f 0 -l ethx all"),
                 isc::InvalidParameter);
    // The negative renew-rate is invalid.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -f -5 -l ethx all"),
                 isc::InvalidParameter);
    // If -r<rate> is not specified the -f<renew-rate> should not
    // be accepted.
    EXPECT_THROW(process(opt, "perfdhcp -6 -f 10 -l ethx all"),
                 isc::InvalidParameter);
    // Renew rate should be specified.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -f -l ethx all"),
                 isc::InvalidParameter);

    // -f and -i are mutually exclusive
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -f 10 -l ethx -i all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReleaseRate) {
    CommandOptions opt;
    // If -F is specified together with -r the command line should
    // be accepted and the release rate should be set.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -r 10 -F 10 -l ethx all"));
    EXPECT_EQ(10, opt.getReleaseRate());
    // Check that the release rate can be set to different value than
    // rate specified as -r<rate>. Also, swap -F and -r to make sure
    // that order doesn't matter.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -F 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getReleaseRate());
    // The release rate should not be greater than the rate.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -F 11 -l ethx all"),
                 isc::InvalidParameter);
    // The release-rate of 0 is invalid.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -F 0 -l ethx all"),
                 isc::InvalidParameter);
    // The negative release-rate is invalid.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -F -5 -l ethx all"),
                 isc::InvalidParameter);
    // If -r<rate> is not specified the -F<release-rate> should not
    // be accepted.
    EXPECT_THROW(process(opt, "perfdhcp -6 -F 10 -l ethx all"),
                 isc::InvalidParameter);
    // -F<release-rate> should be usable in IPv6 mode.
    EXPECT_NO_THROW(process(opt, "perfdhcp -4 -r 10 -F 10 -l ethx all"));
    // Release rate should be specified.
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -F -l ethx all"),
                 isc::InvalidParameter);
    // -F and -i are mutually exclusive
    EXPECT_THROW(process(opt, "perfdhcp -6 -r 10 -F 10 -l ethx -i all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReleaseRenew) {
    CommandOptions opt;
    // It should be possible to specify the -F, -f and -r options.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -r 10 -F 3 -f 5 -l ethx all"));
    EXPECT_EQ(10, opt.getRate());
    EXPECT_EQ(3, opt.getReleaseRate());
    EXPECT_EQ(5, opt.getRenewRate());
    // It should be possible to specify the -F and -f with the values which
    // sum is equal to the rate specified as -r<rate>.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -r 8 -F 3 -f 5 -l ethx all"));
    EXPECT_EQ(8, opt.getRate());
    EXPECT_EQ(3, opt.getReleaseRate());
    EXPECT_EQ(5, opt.getRenewRate());
    // Check that the sum of the release and renew rate is not greater
    // than the rate specified as -r<rate>.
    EXPECT_THROW(process(opt, "perfdhcp -6 -F 6 -f 5 -r 10 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReportDelay) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -t 17 -l ethx all"));
    EXPECT_EQ(17, opt.getReportDelay());

    // Negative test cases
    // -t must be positive integer
    EXPECT_THROW(process(opt, "perfdhcp -t -8 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -t 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -t s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ClientsNum) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -R 200 -l ethx all"));
    EXPECT_EQ(200, opt.getClientsNum());
    process(opt, "perfdhcp -R 0 -l ethx all");
    EXPECT_EQ(0, opt.getClientsNum());

    // Negative test cases
    // Number of clients must be non-negative integer
    EXPECT_THROW(process(opt, "perfdhcp -R -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -R gs -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Base) {
    CommandOptions opt;
    uint8_t mac[6] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60 };
    uint8_t duid[14] = {  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                          0x01, 0x01, 0x01, 0x10, 0x11, 0x1F, 0x14 };
    // Test DUID and MAC together.
    EXPECT_NO_THROW(process(opt, "perfdhcp -b DUID=0101010101010101010110111F14"
                            " -b MAC=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    std::vector<uint8_t> v1 = opt.getMacTemplate();
    std::vector<uint8_t> v2 = opt.getDuidTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Test valid DUID.
    EXPECT_NO_THROW(
        process(opt, "perfdhcp -b duid=0101010101010101010110111F14 -l 127.0.0.1 all")
    );

    ASSERT_EQ(sizeof(duid) / sizeof(uint8_t), v2.size());
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Test mix of upper/lower case letters.
    EXPECT_NO_THROW(process(opt, "perfdhcp -b DuiD=0101010101010101010110111F14"
                            " -b Mac=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    v2 = opt.getDuidTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Use "ether" instead of "mac".
    EXPECT_NO_THROW(process(opt, "perfdhcp -b ether=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    // Use "ETHER" in upper case.
    EXPECT_NO_THROW(process(opt, "perfdhcp -b ETHER=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    // "t" is invalid character in DUID
    EXPECT_THROW(process(opt, "perfdhcp -6 -l ethx -b "
                         "duid=010101010101010101t110111F14 all"),
                 isc::InvalidParameter);
    // "3x" is invalid value in MAC address
    EXPECT_THROW(process(opt, "perfdhcp -b mac=10::2::3x::4::5::6 -l ethx all"),
                 isc::InvalidParameter);
    // Base is not specified
    EXPECT_THROW(process(opt, "perfdhcp -b -l ethx all"),
                 isc::InvalidParameter);
    // Typo: should be mac= instead of mc=
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -b mc=00:01:02:03::04:05 all"),
                 isc::InvalidParameter);
    // Too short DUID (< 6).
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -b duid=00010203 all"),
                 isc::InvalidParameter);
    // Odd number of digits.
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -b duid=000102030405060 all"),
                 isc::InvalidParameter);
    // Too short MAC (!= 6).
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -b mac=00:01:02:04 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, DropTime) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -l ethx -d 12 all"));
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(12, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(1, opt.getDropTime()[1]);

    EXPECT_NO_THROW(process(opt, "perfdhcp -l ethx -d 2 -d 4.7 all"));
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(2, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(4.7, opt.getDropTime()[1]);

    // Negative test cases
    // Drop time must not be negative
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -d -2 -d 4.7 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -d -9.1 -d 0 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TimeOffset) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -l ethx -T file1.x -T file2.x -E 4 all"));
    EXPECT_EQ(4, opt.getElapsedTimeOffset());

    // Negative test cases
    // Argument -E must be used with -T
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -E 3 -i all"),
                 isc::InvalidParameter);
    // Value in -E not specified
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -T file.x -E -i all"),
                 isc::InvalidParameter);
    // Value for -E must not be negative
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -E -3 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ExchangeMode) {
    CommandOptions opt;
    process(opt, "perfdhcp -l ethx -i all");
    EXPECT_EQ(CommandOptions::DO_SA, opt.getExchangeMode());

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process(opt, "perfdhcp -i -l ethx -X 3 all"),
                 isc::InvalidParameter);
    // Offsets can't be used in simple exchanges (-i)
    EXPECT_THROW(process(opt, "perfdhcp -i -l ethx -O 2 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -i -l ethx -E 3 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -i -l ethx -S 1 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -i -l ethx -I 2 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Offsets) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -E5 -4 -I 2 -S3 -O 30 -X7 -l ethx "
                            "-X3 -T file1.x -T file2.x all"));
    EXPECT_EQ(2, opt.getRequestedIpOffset());
    EXPECT_EQ(5, opt.getElapsedTimeOffset());
    EXPECT_EQ(3, opt.getServerIdOffset());
    ASSERT_EQ(2, opt.getRandomOffset().size());
    EXPECT_EQ(30, opt.getRandomOffset()[0]);
    EXPECT_EQ(30, opt.getRandomOffset()[1]);
    ASSERT_EQ(2, opt.getTransactionIdOffset().size());
    EXPECT_EQ(7, opt.getTransactionIdOffset()[0]);
    EXPECT_EQ(3, opt.getTransactionIdOffset()[1]);

    // Negative test cases
    // IP offset/IA_NA offset must be positive
    EXPECT_THROW(process(opt, "perfdhcp -6 -I 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -6 -I -4 -l ethx all"),
                 isc::InvalidParameter);

    // \todo other negative cases
}

TEST_F(CommandOptionsTest, LocalPort) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -l ethx -L 2000 all"));
    EXPECT_EQ(2000, opt.getLocalPort());

    // Negative test cases
    // Local port must be between 0..65535
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -L -2 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -L all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -L 65540 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Preload) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -1 -P 3 -l ethx all"));
    EXPECT_EQ(3, opt.getPreload());

    // Negative test cases
    // Number of preload packages must not be negative integer
    EXPECT_THROW(process(opt, "perfdhcp -P -1 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -P -3 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Seed) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -P 2 -s 23 -l ethx all"));
    EXPECT_EQ(23, opt.getSeed());
    EXPECT_TRUE(opt.isSeeded());

    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -P 2 -s 0 -l ethx all"));
    EXPECT_EQ(0, opt.getSeed());
    EXPECT_FALSE(opt.isSeeded());

    // Negative test cases
    // Seed must be non-negative integer
    EXPECT_THROW(process(opt, "perfdhcp -6 -P 2 -s -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -6 -P 2 -s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TemplateFiles) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -T file1.x -l ethx all"));
    ASSERT_EQ(1, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);

    EXPECT_NO_THROW(process(opt, "perfdhcp -T file1.x -s 12 -w start -T file2.x -4 -l ethx all"));
    ASSERT_EQ(2, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);
    EXPECT_EQ("file2.x", opt.getTemplateFiles()[1]);

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process(opt, "perfdhcp -s 12 -T -l ethx all"),
                 isc::InvalidParameter);
    // Too many template files specified
    EXPECT_THROW(process(opt, "perfdhcp -s 12 -l ethx -T file.x "
                         "-T file.x -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Wrapped) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -B -w start -i -l ethx all"));
    EXPECT_EQ("start", opt.getWrapped());

    // Negative test cases
    // Missing command after -w, expected start/stop
    EXPECT_THROW(process(opt, "perfdhcp -B -i -l ethx -w all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Diagnostics) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -l ethx -i -x asTe all"));
    EXPECT_EQ("asTe", opt.getDiags());

    // Negative test cases
    // No diagnostics string specified
    EXPECT_THROW(process(opt, "perfdhcp -l ethx -i -x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, MaxDrop) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -D 25 -l ethx all"));
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    EXPECT_NO_THROW(process(opt, "perfdhcp -D 25 -l ethx -D 15 all"));
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    EXPECT_EQ(15, opt.getMaxDrop()[1]);

    EXPECT_NO_THROW(process(opt, "perfdhcp -D 15% -l ethx all"));
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    EXPECT_NO_THROW(process(opt, "perfdhcp -D 15% -D25% -l ethx all"));
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(25, opt.getMaxDropPercentage()[1]);
    EXPECT_NO_THROW(process(opt, "perfdhcp -D 1% -D 99% -l ethx all"));
    EXPECT_EQ(1, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(99, opt.getMaxDropPercentage()[1]);

    // Negative test cases
    // Too many -D<value> options
    EXPECT_THROW(process(opt, "perfdhcp -D 0% -D 1 -l ethx -D 3 all"),
                 isc::InvalidParameter);
    // Too many -D<value%> options
    EXPECT_THROW(process(opt, "perfdhcp -D 99% -D 13% -l ethx -D 10% all"),
                 isc::InvalidParameter);
    // Value is out of bounds
    EXPECT_THROW(process(opt, "perfdhcp -D 0 -l ethx all"),
                 isc::InvalidParameter);
    // Percentage is out of bounds
    EXPECT_THROW(process(opt, "perfdhcp -D101% -D 13% -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -D0% -D 13% -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, NumRequest) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -n 1000 -l ethx all"));
    EXPECT_EQ(1000, opt.getNumRequests()[0]);
    EXPECT_NO_THROW(process(opt, "perfdhcp -n 5 -n 500 -l ethx all"));
    EXPECT_EQ(5, opt.getNumRequests()[0]);
    EXPECT_EQ(500, opt.getNumRequests()[1]);

    // Negative test cases
    // Too many -n<value> parameters, expected maximum 2
    EXPECT_THROW(process(opt, "perfdhcp -n 1 -n 2 -l ethx -n3 all"),
                 isc::InvalidParameter);
    // Num request must be positive integer
    EXPECT_THROW(process(opt, "perfdhcp -n 1 -n -22 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -n 0 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Period) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -p 120 -l ethx all"));
    EXPECT_EQ(120, opt.getPeriod());

    // Negative test cases
    // Test period must be positive integer
    EXPECT_THROW(process(opt, "perfdhcp -p 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process(opt, "perfdhcp -p -3 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Interface) {
    // In order to make this test portable we need to know
    // at least one interface name on OS where test is run.
    // Interface Manager has ability to detect interfaces.
    // Although we don't call initIsInterface explicitly
    // here it is called by CommandOptions object internally
    // so this function is covered by the test.
    dhcp::IfaceMgr& iface_mgr = dhcp::IfaceMgr::instance();
    const dhcp::IfaceCollection& ifaces = iface_mgr.getIfaces();
    std::string iface_name;
    CommandOptions opt;
    // The local loopback interface should be available.
    // If no interface have been found for any reason we should
    // not fail this test.
    if (!ifaces.empty()) {
        // Get the name of the interface we detected.
        iface_name = (*ifaces.begin())->getName();
        // Use the name in the command parser.
        ASSERT_NO_THROW(process(opt, "perfdhcp -4 -l " + iface_name + " abc"));
        // We expect that command parser will detect that argument
        // specified along with '-l' is the interface name.
        EXPECT_TRUE(opt.isInterface());

        // If neither interface nor server is specified then
        // exception is expected to be thrown.
        EXPECT_THROW(process(opt, "perfdhcp -4"), isc::InvalidParameter);
    }
}

TEST_F(CommandOptionsTest, Server) {
    CommandOptions opt;
    // There is at least server parameter needed. If server is not
    // specified the local interface must be specified.
    // The server value equal to 'all' means use broadcast.
    ASSERT_NO_THROW(process(opt, "perfdhcp all"));
    // Once command line is parsed we expect that server name is
    // set to broadcast address because 'all' was specified.
    EXPECT_TRUE(opt.isBroadcast());
    // The broadcast address is 255.255.255.255.
    EXPECT_EQ(DHCP_IPV4_BROADCAST_ADDRESS, opt.getServerName());

    // When all is specified for DHCPv6 mode we expect
    // FF02::1:2 as a server name which means All DHCP
    // servers and relay agents in local network segment
    ASSERT_NO_THROW(process(opt, "perfdhcp -6 all"));
    EXPECT_EQ(ALL_DHCP_RELAY_AGENTS_AND_SERVERS, opt.getServerName());

    // When server='servers' in DHCPv6 mode we expect
    // FF05::1:3 as server name which means All DHCP
    // servers in local network.
    ASSERT_NO_THROW(process(opt, "perfdhcp -6 servers"));
    EXPECT_EQ(ALL_DHCP_SERVERS, opt.getServerName());

    // If server name is neither 'all' nor 'servers'
    // the given argument value is expected to be
    // returned.
    ASSERT_NO_THROW(process(opt, "perfdhcp -6 abc"));
    EXPECT_EQ("abc", opt.getServerName());
}

TEST_F(CommandOptionsTest, LoadMacsFromFile) {
    CommandOptions opt;

    std::string mac_list_full_path = getFullPath("mac-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -M " << mac_list_full_path << " abc";
    EXPECT_NO_THROW(process(opt, cmd.str()));
    EXPECT_EQ(mac_list_full_path, opt.getMacListFile());

    const CommandOptions::MacAddrsVector& m = opt.getMacsFromFile();
    EXPECT_EQ(4, m.size());
}

TEST_F(CommandOptionsTest, LoadRelay4AddrFromFile) {
    CommandOptions opt;
    std::string relay_addr_list_full_path = getFullPath("relay4-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -4 -J " << relay_addr_list_full_path << " abc";
    EXPECT_NO_THROW(process(opt, cmd.str()));
    EXPECT_EQ(relay_addr_list_full_path, opt.getRelayAddrListFile());
    EXPECT_TRUE(opt.checkMultiSubnet());
    EXPECT_EQ(5, opt.getRelayAddrList().size());
}

TEST_F(CommandOptionsTest, LoadRelay6AddrFromFile) {
    CommandOptions opt;
    std::string relay_addr_list_full_path = getFullPath("relay6-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -6 -J " << relay_addr_list_full_path << " abc";
    EXPECT_NO_THROW(process(opt, cmd.str()));
    EXPECT_EQ(relay_addr_list_full_path, opt.getRelayAddrListFile());
    EXPECT_TRUE(opt.checkMultiSubnet());
    EXPECT_EQ(2, opt.getRelayAddrList().size());
}

TEST_F(CommandOptionsTest, RelayAddr6ForVersion4) {
    CommandOptions opt;
    std::string relay_addr_list_full_path = getFullPath("relay6-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -4 -J " << relay_addr_list_full_path << " abc";
    EXPECT_THROW(process(opt, cmd.str()), isc::InvalidParameter);
    EXPECT_FALSE(opt.checkMultiSubnet());
    EXPECT_EQ(0, opt.getRelayAddrList().size());
}

TEST_F(CommandOptionsTest, RelayAddr4ForVersion6) {
    CommandOptions opt;
    std::string relay_addr_list_full_path = getFullPath("relay4-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -6 -J " << relay_addr_list_full_path << " abc";
    EXPECT_THROW(process(opt, cmd.str()), isc::InvalidParameter);
    EXPECT_FALSE(opt.checkMultiSubnet());
    EXPECT_EQ(0, opt.getRelayAddrList().size());
}


TEST_F(CommandOptionsTest, LoadMacsFromFileNegativeCases) {
    CommandOptions opt;
    // Negative test cases
    // Too many -M parameters, expected only 1
    EXPECT_THROW(process(opt, "perfdhcp -M foo -M foo1 all"), isc::InvalidParameter);
    // -M option can't use with -b option
    EXPECT_THROW(process(opt, "perfdhcp -M foo -b mac=1234 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ElapsedTime) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -y 3 -Y 10 192.168.0.1"));

    EXPECT_EQ(3, opt.getIncreaseElapsedTime());
    EXPECT_EQ(10, opt.getWaitForElapsedTime());
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithoutV6) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 --or 32,00000E10 -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    EXPECT_EQ(1, opt.getRelayOpts().size());

    // --or must be used together with -6
    EXPECT_THROW(process(opt, "perfdhcp -A1 --or 32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithoutRelayEncapsulation) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 --or 32,00000E10 -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    EXPECT_EQ(1, opt.getRelayOpts().size());

    // --or must be used together with -A
    EXPECT_THROW(process(opt, "perfdhcp -6 --or 32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseMultipleRelayV6Options) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 --or 32,00000E10 --or "
                                 "23,20010DB800010000000000000000CAFE -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    // 2 options expected at 1st level of encapsulation
    EXPECT_EQ(2, opt.getRelayOpts().size());
    // no options expected at 2nd level of encapsulation
    EXPECT_THROW(opt.getRelayOpts(2), isc::OutOfRange);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithMultiSubnets) {
    CommandOptions opt;
    std::string relay_addr_list_full_path = getFullPath("relay6-list.txt");
    std::ostringstream cmd;
    cmd << "perfdhcp -6 -J " << relay_addr_list_full_path
        << " -A1 --or 32,00000E10 --or 23,20010DB800010000000000000000CAFE -l ethx all";
    EXPECT_NO_THROW(process(opt, cmd.str()));
    EXPECT_EQ(relay_addr_list_full_path, opt.getRelayAddrListFile());
    EXPECT_TRUE(opt.checkMultiSubnet());
    EXPECT_EQ(2, opt.getRelayAddrList().size());
    EXPECT_TRUE(opt.isUseRelayedV6());
    // 2 options expected at 1st level of encapsulation
    EXPECT_EQ(2, opt.getRelayOpts().size());
    // no options expected at 2nd level of encapsulation
    EXPECT_THROW(opt.getRelayOpts(2), isc::OutOfRange);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsNoComma) {
    CommandOptions opt;

    // --or must be followed by encapsulation-level, colon, option code, a comma and hexstring
    // in case encapsulation-level and colon are skipped, encapsulation-level is by default 1
    EXPECT_THROW(process(opt, "perfdhcp -6 --or 3200000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsNegativeOptionCode) {
    CommandOptions opt;

    // --or must be followed by encapsulation-level, colon, positive option code, a comma and hexstring
    // in case encapsulation-level and colon are skipped, encapsulation-level is by default 1
    EXPECT_THROW(process(opt, "perfdhcp -6 --or -32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWrongHexstring) {
    CommandOptions opt;

    // --or hexstring containing char Z which is not correct
    EXPECT_THROW(process(opt, "perfdhcp -6 --or 32,Z0000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithEncapsulationLevel) {
    CommandOptions opt;
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 --or 1:32,00000E10 -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    EXPECT_EQ(1, opt.getRelayOpts().size());
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithNegativeEncapsulationLevel) {
    CommandOptions opt;

    // provided Relayed option encapsulation level must be a positive integer.
    EXPECT_THROW(process(opt, "perfdhcp -6 -A1 --or -1:32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithZeroEncapsulationLevel) {
    CommandOptions opt;

    // provided Relayed option encapsulation level must be a positive integer.
    EXPECT_THROW(process(opt, "perfdhcp -6 -A1 --or 0:32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithWrongEncapsulationLevel) {
    CommandOptions opt;

    // provided Relayed option encapsulation level must be a positive integer.
    EXPECT_THROW(process(opt, "perfdhcp -6 -A1 --or x:32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsWithEncapsulationLevelValueTwo) {
    CommandOptions opt;

    // Relayed option encapsulation level supports only value 1 at the moment.
    EXPECT_THROW(process(opt, "perfdhcp -6 -A1 --or 2:32,00000E10 -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, UseRelayV6OptionsDuplicated) {
    CommandOptions opt;

    // multiple relayed options with the same option code are supported.
    EXPECT_NO_THROW(process(opt, "perfdhcp -6 -A1 --or 1:32,00000E10  --or 32,00000E11 -l ethx all"));
    EXPECT_TRUE(opt.isUseRelayedV6());
    EXPECT_EQ(2, opt.getRelayOpts().size());
}


