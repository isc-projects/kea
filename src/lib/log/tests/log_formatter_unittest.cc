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

#include <gtest/gtest.h>
#include <log/log_formatter.h>

#include <vector>
#include <string>

using namespace std;

namespace {

class FormatterTest : public ::testing::Test {
protected:
    typedef pair<const char*, string> Output;
    typedef isc::log::Formatter<FormatterTest> Formatter;
    vector<Output> outputs;
public:
    void output(const char* prefix, const string& message) {
        outputs.push_back(Output(prefix, message));
    }
};

// Create an inactive formatter and check it doesn't produce any output
TEST_F(FormatterTest, inactive) {
    Formatter();
    EXPECT_EQ(0, outputs.size());
}

// Create an active formatter and check it produces output. Does no arg
// substitution yet
TEST_F(FormatterTest, active) {
    Formatter("TEST", "Text of message", 1, *this);
    ASSERT_LE(1, outputs.size());
    EXPECT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("Text of message", outputs[0].second);
}

}
