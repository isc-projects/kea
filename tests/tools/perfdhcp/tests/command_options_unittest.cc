// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "../command_options.h"

#include "exceptions/exceptions.h"

using namespace std;
using namespace isc;
using namespace isc::perfdhcp;

/// \brief Test Fixture Class
class CommandOptionsTest : public virtual ::testing::Test,
                           public virtual CommandOptions
{
public:
    /// \brief Default Constructor
    CommandOptionsTest() : CommandOptions() { }

protected:

    /// \brief Parse command line and cleanup
    ///
    /// Tokenizes command line to array of C-strings,
    /// parses arguments and de-allocates C-strings
    ///
    /// \param s Command line to parse
    /// \return non-zero if parsing failed
    int process(const std::string& s) {
        int argc = 0;
        char** argv = tokenizeString(s, &argc);
        int r = parse(argc, argv, true);
        for(int i = 0; i < argc; ++i) {
            free(argv[i]);
            argv[i] = NULL;
        }
        free(argv);
        return (r);
    }

    /// \brief Check initialized values
    ///
    /// Check if initialized values are correct
    void checkDefaults() {
        EXPECT_EQ(4, getIpVersion());
        EXPECT_EQ(DORR_SARR, getExchangeMode());
        EXPECT_EQ(0, getRate());
        EXPECT_EQ(0, getReportDelay());
        EXPECT_EQ(0, getRandomRange());
        //    EXPECT_EQ(0, max_random_);
        // TODO MAC and DUID checks
        EXPECT_EQ(0, getBase().size());
        EXPECT_EQ(0, getNumRequests().size());
        EXPECT_EQ(0, getPeriod());
        for (int i = 0; i < getLostTime().size(); ++i) {
            EXPECT_DOUBLE_EQ(1, getLostTime()[i]);
        }
        ASSERT_EQ(getMaxDrop().size(), getMaxDropPercentage().size());
        for (int i = 0; i < getMaxDrop().size(); ++i) {
            EXPECT_EQ(0, getMaxDrop()[i]);
            EXPECT_EQ(0, getMaxDropPercentage()[i]);
        }
        EXPECT_EQ("", getLocalName());
        EXPECT_FALSE(isInterface());
        EXPECT_EQ(0, getPreload());
        EXPECT_EQ(1, getAggressivity());
        EXPECT_EQ(0, getLocalPort());
        EXPECT_FALSE(isSeeded());
        EXPECT_EQ(0, getSeed());
        EXPECT_FALSE(isBroadcast());
        EXPECT_FALSE(isRapidCommit());
        EXPECT_FALSE(isUseFirst());
        EXPECT_EQ(0, getTemplateFiles().size());
        EXPECT_EQ(0, getXidOffset().size());
        EXPECT_EQ(0, getRndOffset().size());
        EXPECT_GT(0, getElpOffset());
        EXPECT_GT(0, getSidOffset());
        EXPECT_GT(0, getRipOffset());
        EXPECT_EQ("", getDiags());
        EXPECT_EQ("", getWrapped());
        EXPECT_EQ("", getServerName());
    }

    /// \brief Split string to array of C-strings
    ///
    /// \param s String to split (tokenize)
    /// \param num Number of tokens returned
    /// \return array of C-strings (tokens)
    char** tokenizeString(const std::string& s, int* num) const {
        char** results = NULL;
        std::stringstream ss(s);
        std::istream_iterator<std::string> sit(ss);
        std::istream_iterator<std::string> send;
        std::vector<std::string> tokens(sit, send);

        if (tokens.size() > 0) {
            results = static_cast<char**>(malloc(tokens.size() * sizeof(char*)));
            if (results == NULL) {
                throw std::bad_alloc();
            }
            for (int i = 0; i < tokens.size(); ++i) {
                char* cs = static_cast<char*>(malloc(tokens[i].length() + 1));
                strcpy(cs, tokens[i].c_str());
                results[i] = cs;
            }
            if (num != NULL) {
                *num = tokens.size();
            }
        }

        return results;
    }

};

TEST_F(CommandOptionsTest, Defaults) {
    process("perfdhcp");
    checkDefaults();
}

TEST_F(CommandOptionsTest, UseFirst) {
    process("perfdhcp -l ethx -1 -O 3");
    EXPECT_TRUE(isUseFirst());
}

TEST_F(CommandOptionsTest, IpVersion) {
    process("perfdhcp -6 -l ethx -c");
    EXPECT_EQ(6, getIpVersion());
    EXPECT_EQ("ethx", getLocalName());
    EXPECT_TRUE(isRapidCommit());
    EXPECT_FALSE(isBroadcast());
    process("perfdhcp -4 -B -l ethx");
    EXPECT_EQ(4, getIpVersion());
    EXPECT_TRUE(isBroadcast());
    EXPECT_FALSE(isRapidCommit());
    EXPECT_NE(0, process("perfdhcp -6 -B -l ethx"));
    EXPECT_NE(0, process("perfdhcp -c -l ethx"));
}

TEST_F(CommandOptionsTest, Rate) {
    process("perfdhcp -4 -r 10 -l ethx");
    EXPECT_EQ(10, getRate());
    EXPECT_NE(0, process("perfdhcp -4 -r 0 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -6 -t 5 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -4 -n 150 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -6 -p 120 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -4 -D 1400 -l ethx"));
}

TEST_F(CommandOptionsTest, ReportDelay) {
    process("perfdhcp -r 100 -t 17 -l ethx");
    EXPECT_EQ(17, getReportDelay());
}

TEST_F(CommandOptionsTest, RandomRange) {
    process("perfdhcp -R 200 -l ethx");
    EXPECT_EQ(200, getRandomRange());
}

TEST_F(CommandOptionsTest, Base) {
    process("perfdhcp -6 -b MAC=10:20:30:40:50:60 -l ethx");
    uint8_t mac[6] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60 };
    std::vector<uint8_t> v(mac, mac+6);
    EXPECT_EQ(v, getMacPrefix());
    // TODO - test for DUID
}

TEST_F(CommandOptionsTest, DropTime) {
    process("perfdhcp -l ethx -d 12");
    ASSERT_EQ(2, getLostTime().size());
    EXPECT_DOUBLE_EQ(12, getLostTime()[0]);
    EXPECT_DOUBLE_EQ(1, getLostTime()[1]);

    process("perfdhcp -l ethx -d 2 -d 4.7");
    ASSERT_EQ(2, getLostTime().size());
    EXPECT_DOUBLE_EQ(2, getLostTime()[0]);
    EXPECT_DOUBLE_EQ(4.7, getLostTime()[1]);
}

TEST_F(CommandOptionsTest, TimeOffset) {
    process("perfdhcp -l ethx -E 4");
    EXPECT_EQ(5, getElpOffset());
    EXPECT_NE(0, process("perfdhcp -l ethx -E 3 -i"));
}

TEST_F(CommandOptionsTest, ExchangeMode) {
    process("perfdhcp -i -l ethx");
    EXPECT_EQ(DO_SA, getExchangeMode());
    EXPECT_NE(0, process("perfdhcp -i -l ethx -X 3"));
    EXPECT_NE(0, process("perfdhcp -i -l ethx -O 2"));
    EXPECT_NE(0, process("perfdhcp -i -l ethx -E 3"));
    EXPECT_NE(0, process("perfdhcp -i -l ethx -S 1"));
    EXPECT_NE(0, process("perfdhcp -i -l ethx -I 2"));
}

TEST_F(CommandOptionsTest, Offsets) {
    process("perfdhcp -E5 -4 -I 2 -S3 -O 30 -X7 -l ethx -X3");
    EXPECT_EQ(2, getRipOffset());
    EXPECT_EQ(5, getElpOffset());
    EXPECT_EQ(3, getSidOffset());
    ASSERT_EQ(1, getRndOffset().size());
    EXPECT_EQ(30, getRndOffset()[0]);
    ASSERT_EQ(2, getXidOffset().size());
    EXPECT_EQ(7, getXidOffset()[0]);
    EXPECT_EQ(3, getXidOffset()[1]);
    EXPECT_NE(0, process("perfdhcp -6 -I 0 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -6 -I -4 -l ethx"));

    // TODO - other negative cases
}

TEST_F(CommandOptionsTest, LocalPort) {
    process("perfdhcp -l ethx -L 2000");
    EXPECT_EQ(2000, getLocalPort());
    EXPECT_NE(0, process("perfdhcp -l ethx -L 0"));
}

TEST_F(CommandOptionsTest, Preload) {
    process("perfdhcp -1 -P 3 -l ethx");
    EXPECT_EQ(3, getPreload());
    EXPECT_NE(0, process("perfdhcp -P 0 -1 -l ethx"));
    EXPECT_NE(0, process("perfdhcp -P -1 -l ethx"));
}

TEST_F(CommandOptionsTest, Seed) {
    process("perfdhcp -6 -P 2 -s 23 -l ethx");
    EXPECT_EQ(23, getSeed());
    EXPECT_TRUE(isSeeded());
}

TEST_F(CommandOptionsTest, TemplateFiles) {
    process("perfdhcp -T file1.x -l ethx");
    ASSERT_EQ(1, getTemplateFiles().size());
    EXPECT_EQ("file1.x", getTemplateFiles()[0]);
    process("perfdhcp -T file1.x -s 12 -w start -T file2.x -4 -l ethx");
    ASSERT_EQ(2, getTemplateFiles().size());
    EXPECT_EQ("file1.x", getTemplateFiles()[0]);
    EXPECT_EQ("file2.x", getTemplateFiles()[1]);
    EXPECT_NE(0, process("perfdhcp -T file1.x -s 12 -w start -l ethx -T file2.x -4"));
}

TEST_F(CommandOptionsTest, Wrapped) {
    process("perfdhcp -B -w start -i -l ethx");
    EXPECT_EQ("start", getWrapped());
}

TEST_F(CommandOptionsTest, Diagnostics) {
    process("perfdhcp -l ethx -i -x asTe");
    EXPECT_EQ("asTe", getDiags());
}

