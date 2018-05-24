// Copyright (C) 2016 Deutsche Telekom AG.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include "command_options_helper.h"

using namespace isc::config_tool;
/*
/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on kea-config-tool CommandOptions class.
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
    void process(const std::string& cmdline) {
        CommandOptionsHelper::process(cmdline);
    }

    /// \brief Check default initialized values
    ///
    /// Check if initialized values are correct
    void checkDefaults() {
        CommandOptions& opt = CommandOptions::instance();
        EXPECT_NO_THROW(process("kea-config-tool --help"));

        // default mac
        const uint8_t mac[6] = { 0x00, 0x0C, 0x01, 0x02, 0x03, 0x04 };

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
        EXPECT_EQ(1, opt.getAggressivity());
        EXPECT_EQ(0, opt.getLocalPort());
        EXPECT_FALSE(opt.isSeeded());
        EXPECT_EQ(0, opt.getSeed());
        EXPECT_FALSE(opt.isBroadcast());
        EXPECT_FALSE(opt.isRapidCommit());
        EXPECT_FALSE(opt.isUseFirst());
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
};

TEST_F(CommandOptionsTest, Defaults) {
    EXPECT_NO_THROW(process("kea-config-tool all"));
    checkDefaults();
}

TEST_F(CommandOptionsTest, HelpVersion) {
    // The parser is supposed to return true if 'h' or 'v' options
    // are specified.
    EXPECT_NO_THROW(process("kea-config-tool -h"));
    EXPECT_NO_THROW(process("kea-config-tool -v"));
    EXPECT_NO_THROW(process("kea-config-tool -h -v"));
    EXPECT_NO_THROW(process("kea-config-tool -6 -l ethx -h all"));
    EXPECT_NO_THROW(process("kea-config-tool -l ethx -v all"));
    // No 'h' or 'v' option specified. The false value
    // should be returned.
    EXPECT_FALSE(process("kea-config-tool -l ethx all"));
}

TEST_F(CommandOptionsTest, UseFirst) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -1 -B -l ethx all"));
    EXPECT_TRUE(opt.isUseFirst());
}
TEST_F(CommandOptionsTest, IpVersion) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -6 -l ethx -c -i all"));
    EXPECT_EQ(6, opt.getIpVersion());
    EXPECT_EQ("ethx", opt.getLocalName());
    EXPECT_TRUE(opt.isRapidCommit());
    EXPECT_FALSE(opt.isBroadcast());
    process("kea-config-tool -4 -B -l ethx all");
    EXPECT_EQ(4, opt.getIpVersion());
    EXPECT_TRUE(opt.isBroadcast());
    EXPECT_FALSE(opt.isRapidCommit());

    // Negative test cases
    // -4 and -6 must not coexist
    EXPECT_THROW(process("kea-config-tool -4 -6 -l ethx all"), isc::InvalidParameter);
    // -6 and -B must not coexist
    EXPECT_THROW(process("kea-config-tool -6 -B -l ethx all"), isc::InvalidParameter);
    // -c and -4 (default) must not coexist
    EXPECT_THROW(process("kea-config-tool -c -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Rate) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -4 -r 10 -l ethx all"));
    EXPECT_EQ(10, opt.getRate());

    // Negative test cases
    // Rate must not be 0
    EXPECT_THROW(process("kea-config-tool -4 -r 0 -l ethx all"),
                 isc::InvalidParameter);
    // -r must be specified to use -n, -p and -D
    EXPECT_THROW(process("kea-config-tool -6 -t 5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -4 -n 150 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -6 -p 120 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -4 -D 1400 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, RenewRate) {
    CommandOptions& opt = CommandOptions::instance();
    // If -f is specified together with -r the command line should
    // be accepted and the renew rate should be set.
    EXPECT_NO_THROW(process("kea-config-tool -6 -r 10 -f 10 -l ethx all"));
    EXPECT_EQ(10, opt.getRenewRate());
    // Check that the release rate can be set to different value than
    // rate specified as -r<rate>. Also, swap -f and -r to make sure
    // that order doesn't matter.
    EXPECT_NO_THROW(process("kea-config-tool -6 -f 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getRenewRate());
    // Renew rate should also be accepted for DHCPv4 case.
    EXPECT_NO_THROW(process("kea-config-tool -4 -f 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getRenewRate());
    // The renew rate should not be greater than the rate.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -f 11 -l ethx all"),
                 isc::InvalidParameter);
    // The renew-rate of 0 is invalid.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -f 0 -l ethx all"),
                 isc::InvalidParameter);
    // The negative renew-rate is invalid.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -f -5 -l ethx all"),
                 isc::InvalidParameter);
    // If -r<rate> is not specified the -f<renew-rate> should not
    // be accepted.
    EXPECT_THROW(process("kea-config-tool -6 -f 10 -l ethx all"),
                 isc::InvalidParameter);
    // Renew rate should be specified.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -f -l ethx all"),
                 isc::InvalidParameter);

    // -f and -i are mutually exclusive
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -f 10 -l ethx -i all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReleaseRate) {
    CommandOptions& opt = CommandOptions::instance();
    // If -F is specified together with -r the command line should
    // be accepted and the release rate should be set.
    EXPECT_NO_THROW(process("kea-config-tool -6 -r 10 -F 10 -l ethx all"));
    EXPECT_EQ(10, opt.getReleaseRate());
    // Check that the release rate can be set to different value than
    // rate specified as -r<rate>. Also, swap -F and -r to make sure
    // that order doesn't matter.
    EXPECT_NO_THROW(process("kea-config-tool -6 -F 5 -r 10 -l ethx all"));
    EXPECT_EQ(5, opt.getReleaseRate());
    // The release rate should not be greater than the rate.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -F 11 -l ethx all"),
                 isc::InvalidParameter);
    // The release-rate of 0 is invalid.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -F 0 -l ethx all"),
                 isc::InvalidParameter);
    // The negative release-rate is invalid.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -F -5 -l ethx all"),
                 isc::InvalidParameter);
    // If -r<rate> is not specified the -F<release-rate> should not
    // be accepted.
    EXPECT_THROW(process("kea-config-tool -6 -F 10 -l ethx all"),
                 isc::InvalidParameter);
    // Currently the -F<release-rate> can be specified for IPv6 mode
    // only.
    EXPECT_THROW(process("kea-config-tool -4 -r 10 -F 10 -l ethx all"),
                 isc::InvalidParameter);
    // Release rate should be specified.
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -F -l ethx all"),
                 isc::InvalidParameter);

    // -F and -i are mutually exclusive
    EXPECT_THROW(process("kea-config-tool -6 -r 10 -F 10 -l ethx -i all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReleaseRenew) {
    CommandOptions& opt = CommandOptions::instance();
    // It should be possible to specify the -F, -f and -r options.
    EXPECT_NO_THROW(process("kea-config-tool -6 -r 10 -F 3 -f 5 -l ethx all"));
    EXPECT_EQ(10, opt.getRate());
    EXPECT_EQ(3, opt.getReleaseRate());
    EXPECT_EQ(5, opt.getRenewRate());
    // It should be possible to specify the -F and -f with the values which
    // sum is equal to the rate specified as -r<rate>.
    EXPECT_NO_THROW(process("kea-config-tool -6 -r 8 -F 3 -f 5 -l ethx all"));
    EXPECT_EQ(8, opt.getRate());
    EXPECT_EQ(3, opt.getReleaseRate());
    EXPECT_EQ(5, opt.getRenewRate());
    // Check that the sum of the release and renew rate is not greater
    // than the rate specified as -r<rate>.
    EXPECT_THROW(process("kea-config-tool -6 -F 6 -f 5 -r 10 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReportDelay) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -r 100 -t 17 -l ethx all"));
    EXPECT_EQ(17, opt.getReportDelay());

    // Negative test cases
    // -t must be positive integer
    EXPECT_THROW(process("kea-config-tool -r 10 -t -8 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -r 10 -t 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -r 10 -t s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ClientsNum) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -R 200 -l ethx all"));
    EXPECT_EQ(200, opt.getClientsNum());
    process("kea-config-tool -R 0 -l ethx all");
    EXPECT_EQ(0, opt.getClientsNum());

    // Negative test cases
    // Number of clients must be non-negative integer
    EXPECT_THROW(process("kea-config-tool -R -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -R gs -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Base) {
    CommandOptions& opt = CommandOptions::instance();
    uint8_t mac[6] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60 };
    uint8_t duid[14] = {  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                          0x01, 0x01, 0x01, 0x10, 0x11, 0x1F, 0x14 };
    // Test DUID and MAC together.
    EXPECT_NO_THROW(process("kea-config-tool -b DUID=0101010101010101010110111F14"
                            " -b MAC=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    std::vector<uint8_t> v1 = opt.getMacTemplate();
    std::vector<uint8_t> v2 = opt.getDuidTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Test valid DUID.
    EXPECT_NO_THROW(
        process("kea-config-tool -b duid=0101010101010101010110111F14 -l 127.0.0.1 all")
    );

    ASSERT_EQ(sizeof(duid) / sizeof(uint8_t), v2.size());
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Test mix of upper/lower case letters.
    EXPECT_NO_THROW(process("kea-config-tool -b DuiD=0101010101010101010110111F14"
                            " -b Mac=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    v2 = opt.getDuidTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // Use "ether" instead of "mac".
    EXPECT_NO_THROW(process("kea-config-tool -b ether=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    // Use "ETHER" in upper case.
    EXPECT_NO_THROW(process("kea-config-tool -b ETHER=10::20::30::40::50::60"
                            " -l 127.0.0.1 all"));
    v1 = opt.getMacTemplate();
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    // "t" is invalid character in DUID
    EXPECT_THROW(process("kea-config-tool -6 -l ethx -b "
                         "duid=010101010101010101t110111F14 all"),
                 isc::InvalidParameter);
    // "3x" is invalid value in MAC address
    EXPECT_THROW(process("kea-config-tool -b mac=10::2::3x::4::5::6 -l ethx all"),
                 isc::InvalidParameter);
    // Base is not specified
    EXPECT_THROW(process("kea-config-tool -b -l ethx all"),
                 isc::InvalidParameter);
    // Typo: should be mac= instead of mc=
    EXPECT_THROW(process("kea-config-tool -l ethx -b mc=00:01:02:03::04:05 all"),
                 isc::InvalidParameter);
    // Too short DUID (< 6).
    EXPECT_THROW(process("kea-config-tool -l ethx -b duid=00010203 all"),
                 isc::InvalidParameter);
    // Odd number of digits.
    EXPECT_THROW(process("kea-config-tool -l ethx -b duid=000102030405060 all"),
                 isc::InvalidParameter);
    // Too short MAC (!= 6).
    EXPECT_THROW(process("kea-config-tool -l ethx -b mac=00:01:02:04 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, DropTime) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -l ethx -d 12 all"));
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(12, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(1, opt.getDropTime()[1]);

    EXPECT_NO_THROW(process("kea-config-tool -l ethx -d 2 -d 4.7 all"));
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(2, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(4.7, opt.getDropTime()[1]);

    // Negative test cases
    // Drop time must not be negative
    EXPECT_THROW(process("kea-config-tool -l ethx -d -2 -d 4.7 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -l ethx -d -9.1 -d 0 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TimeOffset) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -l ethx -T file1.x -T file2.x -E 4 all"));
    EXPECT_EQ(4, opt.getElapsedTimeOffset());

    // Negative test cases
    // Argument -E must be used with -T
    EXPECT_THROW(process("kea-config-tool -l ethx -E 3 -i all"),
                 isc::InvalidParameter);
    // Value in -E not specified
    EXPECT_THROW(process("kea-config-tool -l ethx -T file.x -E -i all"),
                 isc::InvalidParameter);
    // Value for -E must not be negative
    EXPECT_THROW(process("kea-config-tool -l ethx -E -3 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ExchangeMode) {
    CommandOptions& opt = CommandOptions::instance();
    process("kea-config-tool -l ethx -i all");
    EXPECT_EQ(CommandOptions::DO_SA, opt.getExchangeMode());

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process("kea-config-tool -i -l ethx -X 3 all"),
                 isc::InvalidParameter);
    // Offsets can't be used in simple exchanges (-i)
    EXPECT_THROW(process("kea-config-tool -i -l ethx -O 2 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -i -l ethx -E 3 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -i -l ethx -S 1 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -i -l ethx -I 2 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Offsets) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -E5 -4 -I 2 -S3 -O 30 -X7 -l ethx "
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
    EXPECT_THROW(process("kea-config-tool -6 -I 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -6 -I -4 -l ethx all"),
                 isc::InvalidParameter);

    // TODO - other negative cases
}

TEST_F(CommandOptionsTest, LocalPort) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -l ethx -L 2000 all"));
    EXPECT_EQ(2000, opt.getLocalPort());

    // Negative test cases
    // Local port must be between 0..65535
    EXPECT_THROW(process("kea-config-tool -l ethx -L -2 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -l ethx -L all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -l ethx -L 65540 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Preload) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -1 -P 3 -l ethx all"));
    EXPECT_EQ(3, opt.getPreload());

    // Negative test cases
    // Number of preload packages must not be negative integer
    EXPECT_THROW(process("kea-config-tool -P -1 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -P -3 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Seed) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -6 -P 2 -s 23 -l ethx all"));
    EXPECT_EQ(23, opt.getSeed());
    EXPECT_TRUE(opt.isSeeded());

    EXPECT_NO_THROW(process("kea-config-tool -6 -P 2 -s 0 -l ethx all"));
    EXPECT_EQ(0, opt.getSeed());
    EXPECT_FALSE(opt.isSeeded());

    // Negative test cases
    // Seed must be non-negative integer
    EXPECT_THROW(process("kea-config-tool -6 -P 2 -s -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -6 -P 2 -s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TemplateFiles) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -T file1.x -l ethx all"));
    ASSERT_EQ(1, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);

    EXPECT_NO_THROW(process("kea-config-tool -T file1.x -s 12 -w start -T file2.x -4 -l ethx all"));
    ASSERT_EQ(2, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);
    EXPECT_EQ("file2.x", opt.getTemplateFiles()[1]);

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process("kea-config-tool -s 12 -T -l ethx all"),
                 isc::InvalidParameter);
    // Too many template files specified
    EXPECT_THROW(process("kea-config-tool -s 12 -l ethx -T file.x "
                         "-T file.x -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Wrapped) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -B -w start -i -l ethx all"));
    EXPECT_EQ("start", opt.getWrapped());

    // Negative test cases
    // Missing command after -w, expected start/stop
    EXPECT_THROW(process("kea-config-tool -B -i -l ethx -w all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Diagnostics) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -l ethx -i -x asTe all"));
    EXPECT_EQ("asTe", opt.getDiags());

    // Negative test cases
    // No diagnostics string specified
    EXPECT_THROW(process("kea-config-tool -l ethx -i -x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Aggressivity) {
    CommandOptions& opt = CommandOptions::instance();
    process("kea-config-tool -a 10 -l 192.168.0.1 all");
    EXPECT_EQ(10, opt.getAggressivity());

    // Negative test cases
    // Aggressivity must be non negative integer
    EXPECT_THROW(process("kea-config-tool -l ethx -a 0 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -l ethx -a all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -a -2 -l ethx -a 3 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, MaxDrop) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -D 25 -l ethx -r 10 all"));
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    EXPECT_NO_THROW(process("kea-config-tool -D 25 -l ethx -D 15 -r 10 all"));
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    EXPECT_EQ(15, opt.getMaxDrop()[1]);

    EXPECT_NO_THROW(process("kea-config-tool -D 15% -l ethx -r 10 all"));
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    EXPECT_NO_THROW(process("kea-config-tool -D 15% -D25% -l ethx -r 10 all"));
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(25, opt.getMaxDropPercentage()[1]);
    EXPECT_NO_THROW(process("kea-config-tool -D 1% -D 99% -l ethx -r 10 all"));
    EXPECT_EQ(1, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(99, opt.getMaxDropPercentage()[1]);

    // Negative test cases
    // Too many -D<value> options
    EXPECT_THROW(process("kea-config-tool -D 0% -D 1 -l ethx -r20 -D 3 all"),
                 isc::InvalidParameter);
    // Too many -D<value%> options
    EXPECT_THROW(process("kea-config-tool -D 99% -D 13% -l ethx -r20 -D 10% all"),
                 isc::InvalidParameter);
    // Percentage is out of bounds
    EXPECT_THROW(process("kea-config-tool -D101% -D 13% -l ethx -r20 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -D0% -D 13% -l ethx -r20 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, NumRequest) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -n 1000 -r 10 -l ethx all"));
    EXPECT_EQ(1000, opt.getNumRequests()[0]);
    EXPECT_NO_THROW(process("kea-config-tool -n 5 -r 10 -n 500 -l ethx all"));
    EXPECT_EQ(5, opt.getNumRequests()[0]);
    EXPECT_EQ(500, opt.getNumRequests()[1]);

    // Negative test cases
    // Too many -n<value> parameters, expected maximum 2
    EXPECT_THROW(process("kea-config-tool -n 1 -n 2 -l ethx -n3 -r 20 all"),
                 isc::InvalidParameter);
    // Num request must be positive integer
    EXPECT_THROW(process("kea-config-tool -n 1 -n -22 -l ethx -r 10 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -n 0 -l ethx -r 10 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Period) {
    CommandOptions& opt = CommandOptions::instance();
    EXPECT_NO_THROW(process("kea-config-tool -p 120 -l ethx -r 100 all"));
    EXPECT_EQ(120, opt.getPeriod());

    // Negative test cases
    // Test period must be positive integer
    EXPECT_THROW(process("kea-config-tool -p 0 -l ethx -r 50 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("kea-config-tool -p -3 -l ethx -r 50 all"),
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
    const dhcp::IfaceMgr::IfaceCollection& ifaces = iface_mgr.getIfaces();
    std::string iface_name;
    CommandOptions& opt = CommandOptions::instance();
    // The local loopback interface should be available.
    // If no interface have been found for any reason we should
    // not fail this test.
    if (!ifaces.empty()) {
        // Get the name of the interface we detected.
        iface_name = (*ifaces.begin())->getName();
        // Use the name in the command parser.
        ASSERT_NO_THROW(process("kea-config-tool -4 -l " + iface_name + " abc"));
        // We expect that command parser will detect that argument
        // specified along with '-l' is the interface name.
        EXPECT_TRUE(opt.isInterface());

        // If neither interface nor server is specified then
        // exception is expected to be thrown.
        EXPECT_THROW(process("kea-config-tool -4"), isc::InvalidParameter);
    }
}

TEST_F(CommandOptionsTest, Server) {
    CommandOptions& opt = CommandOptions::instance();
    // There is at least server parameter needed. If server is not
    // specified the local interface must be specified.
    // The server value equal to 'all' means use broadcast.
    ASSERT_NO_THROW(process("kea-config-tool all"));
    // Once command line is parsed we expect that server name is
    // set to broadcast address because 'all' was specified.
    EXPECT_TRUE(opt.isBroadcast());
    // The broadcast address is 255.255.255.255.
    EXPECT_EQ(DHCP_IPV4_BROADCAST_ADDRESS, opt.getServerName());

    // When all is specified for DHCPv6 mode we expect
    // FF02::1:2 as a server name which means All DHCP
    // servers and relay agents in local network segment
    ASSERT_NO_THROW(process("kea-config-tool -6 all"));
    EXPECT_EQ(ALL_DHCP_RELAY_AGENTS_AND_SERVERS, opt.getServerName());

    // When server='servers' in DHCPv6 mode we expect
    // FF05::1:3 as server name which means All DHCP
    // servers in local network.
    ASSERT_NO_THROW(process("kea-config-tool -6 servers"));
    EXPECT_EQ(ALL_DHCP_SERVERS, opt.getServerName());

    // If server name is neither 'all' nor 'servers'
    // the given argument value is expected to be
    // returned.
    ASSERT_NO_THROW(process("kea-config-tool -6 abc"));
    EXPECT_EQ("abc", opt.getServerName());
}
//*/
