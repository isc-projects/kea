// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <config/module_spec.h>

#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::config;

namespace {

const char* const SPEC_FILE = AUTH_OBJ_DIR "/auth.spec";

class AuthConfigSyntaxTest : public ::testing::Test {
protected:
    AuthConfigSyntaxTest() : mspec_(moduleSpecFromFile(SPEC_FILE))
    {}
    ModuleSpec mspec_;
};

TEST_F(AuthConfigSyntaxTest, inmemoryDefaultFileType) {
    // filetype is optional
    EXPECT_TRUE(
        mspec_.validateConfig(
            Element::fromJSON(
                "{\"tcp_recv_timeout\": 1000,"
                " \"listen_on\": [], \"datasources\": "
                "  [{\"type\": \"memory\", \"class\": \"IN\", "
                "    \"zones\": [{\"origin\": \"example.com\","
                "                 \"file\": \""
                TEST_DATA_DIR "/example.zone\"}]}]}"), true));
}

TEST_F(AuthConfigSyntaxTest, inmemorySQLite3Backend) {
    // Specifying non-default in-memory filetype
    EXPECT_TRUE(
        mspec_.validateConfig(
            Element::fromJSON(
                "{\"tcp_recv_timeout\": 1000,"
                " \"datasources\": "
                "  [{\"type\": \"memory\","
                "    \"zones\": [{\"origin\": \"example.com\","
                "                 \"file\": \""
                TEST_DATA_DIR "/example.zone\","
                "                 \"filetype\": \"sqlite3\"}]}]}"), false));
}

TEST_F(AuthConfigSyntaxTest, badInmemoryFileType) {
    // filetype must be a string
    ASSERT_FALSE(
        mspec_.validateConfig(
            Element::fromJSON(
                "{\"tcp_recv_timeout\": 1000,"
                " \"datasources\": "
                "  [{\"type\": \"memory\","
                "    \"zones\": [{\"origin\": \"example.com\","
                "                 \"file\": \""
                TEST_DATA_DIR "/example.zone\","
                "                 \"filetype\": 42}]}]}"), false));
}

TEST_F(AuthConfigSyntaxTest, badTCPRecvTimeout) {
    // tcp_recv_timeout must be int
    EXPECT_FALSE(
        mspec_.validateConfig(
            Element::fromJSON(
                "{\"tcp_recv_timeout\": \"foo\","
                " \"datasources\": "
                "  [{\"type\": \"memory\","
                "    \"zones\": [{\"origin\": \"example.com\","
                "                 \"file\": \""
                TEST_DATA_DIR "/example.zone\","
                "                 \"filetype\": \"sqlite3\"}]}]}"), false));
}

}
