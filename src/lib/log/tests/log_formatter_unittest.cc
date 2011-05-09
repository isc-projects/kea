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
    // Just shortcut for new string
    string* s(const char* text) {
        return (new string(text));
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
    Formatter("TEST", s("Text of message"), this);
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("Text of message", outputs[0].second);
}

// No output even when we have an arg on the inactive formatter
TEST_F(FormatterTest, inactiveArg) {
    Formatter().arg("Hello");
    EXPECT_EQ(0, outputs.size());
}

// Create an active formatter and replace a placeholder with string
TEST_F(FormatterTest, stringArg) {
    {
        SCOPED_TRACE("C++ string");
        Formatter("TEST", s("Hello %1"), this).arg(string("World"));
        ASSERT_EQ(1, outputs.size());
        EXPECT_STREQ("TEST", outputs[0].first);
        EXPECT_EQ("Hello World", outputs[0].second);
    }
    {
        SCOPED_TRACE("C++ string");
        Formatter("TEST", s("Hello %1"), this).arg(string("Internet"));
        ASSERT_EQ(2, outputs.size());
        EXPECT_STREQ("TEST", outputs[1].first);
        EXPECT_EQ("Hello Internet", outputs[1].second);
    }
}

// Can convert to string
TEST_F(FormatterTest, intArg) {
    Formatter("TEST", s("The answer is %1"), this).arg(42);
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("The answer is 42", outputs[0].second);
}

// Can use multiple arguments at different places
TEST_F(FormatterTest, multiArg) {
    Formatter("TEST", s("The %2 are %1"), this).arg("switched").
        arg("arguments");
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("The arguments are switched", outputs[0].second);
}

// Can survive and complains if placeholder is missing
TEST_F(FormatterTest, missingPlace) {
    EXPECT_NO_THROW(Formatter("TEST", s("Missing the first %2"), this).
                    arg("missing").arg("argument"));
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("Missing the first argument "
              "@@Missing placeholder %1 for 'missing'@@", outputs[0].second);
}

// Can replace multiple placeholders
TEST_F(FormatterTest, multiPlaceholder) {
    Formatter("TEST", s("The %1 is the %1"), this).
        arg("first rule of tautology club");
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("The first rule of tautology club is "
              "the first rule of tautology club", outputs[0].second);
}

// Test we can cope with replacement containing the placeholder
TEST_F(FormatterTest, noRecurse) {
    // If we recurse, this will probably eat all the memory and crash
    Formatter("TEST", s("%1"), this).arg("%1 %1");
    ASSERT_EQ(1, outputs.size());
    EXPECT_STREQ("TEST", outputs[0].first);
    EXPECT_EQ("%1 %1", outputs[0].second);
}

}
