// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <exceptions/exceptions.h>
#include <dhcpsrv/daemon.h>
#include <gtest/gtest.h>
#include <cc/data.h>
#include <fstream>

using namespace isc;
using namespace isc::data;

namespace {

/// @brief Test class for testing Deamon class
class DataFileTest : public ::testing::Test {
public:

    /// @brief writes specified text to a file
    ///
    /// That is an auxilliary funtion used in fileRead() tests.
    ///
    /// @param content text to be written to disk
    void writeFile(const std::string& content) {
        // Write sample content to disk
        static_cast<void>(remove(TEMP_FILE));
        std::ofstream write_me(TEMP_FILE);
        EXPECT_TRUE(write_me.is_open());
        write_me << content;
        write_me.close();
    }

    /// destructor
    ~DataFileTest() {
        static_cast<void>(remove(TEMP_FILE));
    }

    /// Name of the temporary file
    static const char* TEMP_FILE;
};

/// Temporary file name used in some tests
const char* DataFileTest::TEMP_FILE="temp-file.json";

// Test checks whether a text file can be read from disk.
TEST_F(DataFileTest, readFileMultiline) {

    const char* no_endline = "{ \"abc\": 123 }";
    const char* with_endline = "{\n \"abc\":\n 123\n }\n";

    // That's what we expect
    ElementPtr exp = Element::fromJSON(no_endline);

    // Write sample content to disk
    writeFile(no_endline);

    // Check that the read content is correct
    EXPECT_TRUE(exp->equals(*Element::fromJSONFile(TEMP_FILE)));

    // Write sample content to disk
    writeFile(with_endline);

    // Check that the read content is correct
    EXPECT_TRUE(exp->equals(*Element::fromJSONFile(TEMP_FILE)));
}

// Test checks whether comments in file are ignored as expected.
TEST_F(DataFileTest, readFileComments) {
    const char* commented_content = "# This is a comment\n"
        "{ \"abc\":\n"
        "# a comment comment\n"
        "1 }\n";

    // That's what we expect
    ElementPtr exp = Element::fromJSON("{ \"abc\": 1 }");

    // Write sample content to disk
    writeFile(commented_content);

    // Check that the read will fail (without comment elimination)
    EXPECT_THROW(Element::fromJSONFile(TEMP_FILE), JSONError);

    // Check that the read content is correct (with comment elimination)
    EXPECT_NO_THROW(Element::fromJSONFile(TEMP_FILE, true));
    EXPECT_TRUE(exp->equals(*Element::fromJSONFile(TEMP_FILE, true)));
}

// This test checks that missing file will generate an exception.
TEST_F(DataFileTest, readFileError) {

    // Check that the read content is correct
    EXPECT_THROW(Element::fromJSONFile("no-such-file.txt"), isc::InvalidOperation);
}

};
