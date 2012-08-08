// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <cstddef>
#include <stdint.h>
#include <string>
#include <gtest/gtest.h>

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

#include "../command_options.h"

using namespace std;
using namespace isc;
using namespace isc::perfdhcp;

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
    /// \param cmdline Command line to parse
    /// \throws std::bad allocation if tokenization failed
    void process(const std::string& cmdline) {
        CommandOptions& opt = CommandOptions::instance();
        int argc = 0;
        char** argv = tokenizeString(cmdline, &argc);
        opt.reset();
        opt.parse(argc, argv);
        for(int i = 0; i < argc; ++i) {
            free(argv[i]);
            argv[i] = NULL;
        }
        free(argv);
    }

    /// \brief Check default initialized values
    ///
    /// Check if initialized values are correct
    void checkDefaults() {
        CommandOptions& opt = CommandOptions::instance();
        process("perfdhcp 192.168.0.1");
        EXPECT_EQ(4, opt.getIpVersion());
        EXPECT_EQ(CommandOptions::DORA_SARR, opt.getExchangeMode());
        EXPECT_EQ(0, opt.getRate());
        EXPECT_EQ(0, opt.getReportDelay());
        EXPECT_EQ(0, opt.getClientsNum());

        // default mac
        const uint8_t mac[6] = { 0x00, 0x0C, 0x01, 0x02, 0x03, 0x04 };
        std::vector<uint8_t> v1 = opt.getMacPrefix();
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
        std::vector<uint8_t> v2 = opt.getDuidPrefix();
        ASSERT_EQ(duid_llt_size, opt.getDuidPrefix().size());
        EXPECT_TRUE(std::equal(v2.begin(), v2.begin() + 4,
                               duid_llt_and_hw));

        EXPECT_EQ(0, opt.getBase().size());
        EXPECT_EQ(0, opt.getNumRequests().size());
        EXPECT_EQ(0, opt.getPeriod());
        for (int i = 0; i < opt.getDropTime().size(); ++i) {
            EXPECT_DOUBLE_EQ(1, opt.getDropTime()[i]);
        }
        ASSERT_EQ(opt.getMaxDrop().size(), opt.getMaxDropPercentage().size());
        for (int i = 0; i < opt.getMaxDrop().size(); ++i) {
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

    /// \brief Split string to array of C-strings
    ///
    /// \param s String to split (tokenize)
    /// \param num Number of tokens returned
    /// \return array of C-strings (tokens)
    char** tokenizeString(const std::string& text_to_split, int* num) const {
        char** results = NULL;
        // Tokenization with std streams
        std::stringstream text_stream(text_to_split);
        // Iterators to be used for tokenization
        std::istream_iterator<std::string> text_iterator(text_stream);
        std::istream_iterator<std::string> text_end;
        // Tokenize string (space is a separator) using begin and end iteratos
        std::vector<std::string> tokens(text_iterator, text_end);

        if (tokens.size() > 0) {
            // Allocate array of C-strings where we will store tokens
            results = static_cast<char**>(malloc(tokens.size() * sizeof(char*)));
            if (results == NULL) {
                throw std::bad_alloc();
            }
            // Store tokens in C-strings array
            for (int i = 0; i < tokens.size(); ++i) {
                char* cs = static_cast<char*>(malloc(tokens[i].length() + 1));
                strcpy(cs, tokens[i].c_str());
                results[i] = cs;
            }
            // Return number of tokens to calling function
            if (num != NULL) {
                *num = tokens.size();
            }
        }
        return results;
    }

};

TEST_F(CommandOptionsTest, Defaults) {
    process("perfdhcp all");
    checkDefaults();
}

TEST_F(CommandOptionsTest, UseFirst) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -1 -B -l ethx all");
    EXPECT_TRUE(opt.isUseFirst());
}
TEST_F(CommandOptionsTest, IpVersion) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -6 -l ethx -c -i all");
    EXPECT_EQ(6, opt.getIpVersion());
    EXPECT_EQ("ethx", opt.getLocalName());
    EXPECT_TRUE(opt.isRapidCommit());
    EXPECT_FALSE(opt.isBroadcast());
    process("perfdhcp -4 -B -l ethx all");
    EXPECT_EQ(4, opt.getIpVersion());
    EXPECT_TRUE(opt.isBroadcast());
    EXPECT_FALSE(opt.isRapidCommit());

    // Negative test cases
    // -4 and -6 must not coexist
    EXPECT_THROW(process("perfdhcp -4 -6 -l ethx all"), isc::InvalidParameter);
    // -6 and -B must not coexist
    EXPECT_THROW(process("perfdhcp -6 -B -l ethx all"), isc::InvalidParameter);
    // -c and -4 (default) must not coexist
    EXPECT_THROW(process("perfdhcp -c -l ethx all"), isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Rate) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -4 -r 10 -l ethx all");
    EXPECT_EQ(10, opt.getRate());

    // Negative test cases
    // Rate must not be 0
    EXPECT_THROW(process("perfdhcp -4 -r 0 -l ethx all"),
                 isc::InvalidParameter);
    // -r must be specified to use -n, -p and -D
    EXPECT_THROW(process("perfdhcp -6 -t 5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -4 -n 150 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -6 -p 120 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -4 -D 1400 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ReportDelay) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -r 100 -t 17 -l ethx all");
    EXPECT_EQ(17, opt.getReportDelay());

    // Negative test cases
    // -t must be positive integer
    EXPECT_THROW(process("perfdhcp -r 10 -t -8 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -r 10 -t 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -r 10 -t s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ClientsNum) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -R 200 -l ethx all");
    EXPECT_EQ(200, opt.getClientsNum());
    process("perfdhcp -R 0 -l ethx all");
    EXPECT_EQ(0, opt.getClientsNum());

    // Negative test cases
    // Number of clients must be non-negative integer
    EXPECT_THROW(process("perfdhcp -R -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -R gs -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Base) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -6 -b MAC=10::20::30::40::50::60 "
            "-l ethx -b duiD=1AB7F5670901FF all");
    uint8_t mac[6] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60 };
    uint8_t duid[7] = { 0x1A, 0xB7, 0xF5, 0x67, 0x09, 0x01, 0xFF };

    // Test Mac
    std::vector<uint8_t> v1 = opt.getMacPrefix();
    ASSERT_EQ(6, v1.size());
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), mac));
    // "3x" is invalid value in MAC address
    EXPECT_THROW(process("perfdhcp -b mac=10::2::3x::4::5::6 -l ethx all"),
                 isc::InvalidParameter);

    // Test DUID
    std::vector<uint8_t> v2 = opt.getDuidPrefix();
    ASSERT_EQ(sizeof(duid) / sizeof(uint8_t), v2.size());
    EXPECT_TRUE(std::equal(v2.begin(), v2.end(), duid));
    // "t" is invalid digit in DUID
    EXPECT_THROW(process("perfdhcp -6 -l ethx -b duiD=1AB7Ft670901FF all"),
                 isc::InvalidParameter);

    // Some more negative test cases
    // Base is not specified
    EXPECT_THROW(process("perfdhcp -b -l ethx all"),
                 isc::InvalidParameter);
    // Typo: should be mac= instead of mc=
    EXPECT_THROW(process("perfdhcp -l ethx -b mc=00:01:02:03::04:05 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, DropTime) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -l ethx -d 12 all");
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(12, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(1, opt.getDropTime()[1]);

    process("perfdhcp -l ethx -d 2 -d 4.7 all");
    ASSERT_EQ(2, opt.getDropTime().size());
    EXPECT_DOUBLE_EQ(2, opt.getDropTime()[0]);
    EXPECT_DOUBLE_EQ(4.7, opt.getDropTime()[1]);

    // Negative test cases
    // Drop time must not be negative
    EXPECT_THROW(process("perfdhcp -l ethx -d -2 -d 4.7 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -l ethx -d -9.1 -d 0 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TimeOffset) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -l ethx -T file1.x -T file2.x -E 4 all");
    EXPECT_EQ(4, opt.getElapsedTimeOffset());

    // Negative test cases
    // Argument -E must be used with -T
    EXPECT_THROW(process("perfdhcp -l ethx -E 3 -i all"),
                 isc::InvalidParameter);
    // Value in -E not specified
    EXPECT_THROW(process("perfdhcp -l ethx -T file.x -E -i all"),
                 isc::InvalidParameter);
    // Value for -E must not be negative
    EXPECT_THROW(process("perfdhcp -l ethx -E -3 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, ExchangeMode) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -l ethx -i all");
    EXPECT_EQ(CommandOptions::DO_SA, opt.getExchangeMode());

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process("perfdhcp -i -l ethx -X 3 all"),
                 isc::InvalidParameter);
    // Offsets can't be used in simple exchanges (-i)
    EXPECT_THROW(process("perfdhcp -i -l ethx -O 2 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -i -l ethx -E 3 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -i -l ethx -S 1 -T file.x all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -i -l ethx -I 2 -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Offsets) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -E5 -4 -I 2 -S3 -O 30 -X7 -l ethx "
            "-X3 -T file1.x -T file2.x all");
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
    EXPECT_THROW(process("perfdhcp -6 -I 0 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -6 -I -4 -l ethx all"),
                 isc::InvalidParameter);

    // TODO - other negative cases
}

TEST_F(CommandOptionsTest, LocalPort) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -l ethx -L 2000 all");
    EXPECT_EQ(2000, opt.getLocalPort());

    // Negative test cases
    // Local port must be between 0..65535
    EXPECT_THROW(process("perfdhcp -l ethx -L -2 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -l ethx -L all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -l ethx -L 65540 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Preload) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -1 -P 3 -l ethx all");
    EXPECT_EQ(3, opt.getPreload());

    // Negative test cases
    // Number of preload packages must not be negative integer
    EXPECT_THROW(process("perfdhcp -P -1 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -P -3 -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Seed) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -6 -P 2 -s 23 -l ethx all");
    EXPECT_EQ(23, opt.getSeed());
    EXPECT_TRUE(opt.isSeeded());

    process("perfdhcp -6 -P 2 -s 0 -l ethx all");
    EXPECT_EQ(0, opt.getSeed());
    EXPECT_FALSE(opt.isSeeded());

    // Negtaive test cases
    // Seed must be non-negative integer
    EXPECT_THROW(process("perfdhcp -6 -P 2 -s -5 -l ethx all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -6 -P 2 -s -l ethx all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, TemplateFiles) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -T file1.x -l ethx all");
    ASSERT_EQ(1, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);

    process("perfdhcp -T file1.x -s 12 -w start -T file2.x -4 -l ethx all");
    ASSERT_EQ(2, opt.getTemplateFiles().size());
    EXPECT_EQ("file1.x", opt.getTemplateFiles()[0]);
    EXPECT_EQ("file2.x", opt.getTemplateFiles()[1]);

    // Negative test cases
    // No template file specified
    EXPECT_THROW(process("perfdhcp -s 12 -T -l ethx all"),
                 isc::InvalidParameter);
    // Too many template files specified
    EXPECT_THROW(process("perfdhcp -s 12 -l ethx -T file.x "
                         "-T file.x -T file.x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Wrapped) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -B -w start -i -l ethx all");
    EXPECT_EQ("start", opt.getWrapped());

    // Negative test cases
    // Missing command after -w, expected start/stop
    EXPECT_THROW(process("perfdhcp -B -i -l ethx -w all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Diagnostics) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -l ethx -i -x asTe all");
    EXPECT_EQ("asTe", opt.getDiags());

    // Negative test cases
    // No diagnostics string specified
    EXPECT_THROW(process("perfdhcp -l ethx -i -x all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Aggressivity) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -a 10 -l 192.168.0.1 all");
    EXPECT_EQ(10, opt.getAggressivity());

    // Negative test cases
    // Aggressivity must be non negative integer
    EXPECT_THROW(process("perfdhcp -l ethx -a 0 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -l ethx -a all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -a -2 -l ethx -a 3 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, MaxDrop) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -D 25 -l ethx -r 10 all");
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    process("perfdhcp -D 25 -l ethx -D 15 -r 10 all");
    EXPECT_EQ(25, opt.getMaxDrop()[0]);
    EXPECT_EQ(15, opt.getMaxDrop()[1]);

    process("perfdhcp -D 15% -l ethx -r 10 all");
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    process("perfdhcp -D 15% -D25% -l ethx -r 10 all");
    EXPECT_EQ(15, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(25, opt.getMaxDropPercentage()[1]);
    process("perfdhcp -D 1% -D 99% -l ethx -r 10 all");
    EXPECT_EQ(1, opt.getMaxDropPercentage()[0]);
    EXPECT_EQ(99, opt.getMaxDropPercentage()[1]);

    // Negative test cases
    // Too many -D<value> options
    EXPECT_THROW(process("perfdhcp -D 0% -D 1 -l ethx -r20 -D 3 all"),
                 isc::InvalidParameter);
    // Too many -D<value%> options
    EXPECT_THROW(process("perfdhcp -D 99% -D 13% -l ethx -r20 -D 10% all"),
                 isc::InvalidParameter);
    // Percentage is out of bounds
    EXPECT_THROW(process("perfdhcp -D101% -D 13% -l ethx -r20 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -D0% -D 13% -l ethx -r20 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, NumRequest) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -n 1000 -r 10 -l ethx all");
    EXPECT_EQ(1000, opt.getNumRequests()[0]);
    process("perfdhcp -n 5 -r 10 -n 500 -l ethx all");
    EXPECT_EQ(5, opt.getNumRequests()[0]);
    EXPECT_EQ(500, opt.getNumRequests()[1]);

    // Negative test cases
    // Too many -n<value> parameters, expected maximum 2
    EXPECT_THROW(process("perfdhcp -n 1 -n 2 -l ethx -n3 -r 20 all"),
                 isc::InvalidParameter);
    // Num request must be positive integer
    EXPECT_THROW(process("perfdhcp -n 1 -n -22 -l ethx -r 10 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -n 0 -l ethx -r 10 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Period) {
    CommandOptions& opt = CommandOptions::instance();
    process("perfdhcp -p 120 -l ethx -r 100 all");
    EXPECT_EQ(120, opt.getPeriod());

    // Negative test cases
    // Test period must be positive integer
    EXPECT_THROW(process("perfdhcp -p 0 -l ethx -r 50 all"),
                 isc::InvalidParameter);
    EXPECT_THROW(process("perfdhcp -p -3 -l ethx -r 50 all"),
                 isc::InvalidParameter);
}

TEST_F(CommandOptionsTest, Interface) {
    // In order to make this test portable we need to know
    // at least one interface name on OS where test is run.
    // Interface Manager has ability to detect interfaces.
    dhcp::IfaceMgr& iface_mgr = dhcp::IfaceMgr::instance();
    const dhcp::IfaceMgr::IfaceCollection& ifaces = iface_mgr.getIfaces();
    std::string iface_name;
    CommandOptions& opt = CommandOptions::instance();
    // The local loopback interface should be available. 
    // If no interface have been found for any reason we should
    // not fail this test.
    if (ifaces.size() > 0) {
        // Get the name of the interface we detected.
        iface_name = ifaces.begin()->getName();
        // Use the name in the command parser.
        ASSERT_NO_THROW(process("perfdhcp -4 -l " + iface_name + " abc"));
        // We expect that command parser will detect that argument
        // specified along with '-l' is the interface name.
        EXPECT_TRUE(opt.isInterface());

        // If neither interface nor server is specified then
        // exception is expected to be thrown.
        EXPECT_THROW(process("perfdhcp -4"), isc::InvalidParameter);
    }
}    

TEST_F(CommandOptionsTest, Server) {
    CommandOptions& opt = CommandOptions::instance();
    // There is at least server parameter needed. If server is not
    // specified the local interface must be specified.
    // The server value equal to 'all' means use broadcast.
    ASSERT_NO_THROW(process("perfdhcp all"));
    // Once command line is parsed we expect that server name is
    // set to broadcast address because 'all' was specified.
    EXPECT_TRUE(opt.isBroadcast());
    // The broadcast address is 255.255.255.255.
    EXPECT_EQ("255.255.255.255", opt.getServerName());

    // When all is specified for DHCPv6 mode we expect
    // FF02::1:2 as a server name which means All DHCP
    // servers and relay agents in local network segment
    ASSERT_NO_THROW(process("perfdhcp -6 all"));
    EXPECT_EQ("FF02::1:2", opt.getServerName());

    // When server='servers' in DHCPv6 mode we expect
    // FF05::1:3 as server name which means All DHCP
    // servers in local network.
    ASSERT_NO_THROW(process("perfdhcp -6 servers"));
    EXPECT_EQ("FF05::1:3", opt.getServerName());

    // If server name is neither 'all' nor 'servers'
    // the given argument value is expected to be
    // returned.
    ASSERT_NO_THROW(process("perfdhcp -6 abc"));
    EXPECT_EQ("abc", opt.getServerName());
}
