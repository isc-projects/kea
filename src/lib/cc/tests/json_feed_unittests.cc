// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <cc/json_feed.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace isc::config;
using namespace isc::data;

namespace {

/// @brief Test fixture class for @ref JSONFeed class.
class JSONFeedTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Initializes @ref json_map_ and @ref json_list_ which hold reference
    /// JSON structures.
    JSONFeedTest()
        : json_map_(), json_list_() {
        ElementPtr m = Element::fromJSON(createJSON());
        ElementPtr l = Element::createList();
        l->add(m);
        json_map_ = m;
        json_list_ = l;
    }

    /// @brief Creates a JSON map holding 20 elements.
    ///
    /// Each map value is a list of 20 elements.
    std::string createJSON() const {
        // Create a list of 20 elements.
        ElementPtr list_element = Element::createList();
        for (unsigned i = 0; i < 20; ++i) {
            std::ostringstream s;
            s << "list_element" << i;
            list_element->add(Element::create(s.str()));
        }

        // Create a map of 20 elements. Each map element holds a list
        // of 20 elements.
        ElementPtr map_element = Element::createMap();
        for (unsigned i = 0; i < 20; ++i) {
            std::ostringstream s;
            s << "map_element" << i;
            map_element->set(s.str(), list_element);
        }

        return (prettyPrint(map_element));
    }

    /// @brief Test that the JSONFeed correctly recognizes the beginning
    /// and the end of the JSON structure.
    ///
    /// @param input_json A string holding an input JSON structure.
    /// @param expected_output A structure holding expected output from the
    /// @ref JSONFeed::toElement.
    void testRead(const std::string& input_json,
                  const ConstElementPtr& expected_output) {
        JSONFeed feed;
        ASSERT_NO_THROW(feed.initModel());

        // Post the data into the feed in 10 bytes long chunks.
        size_t chunk = 10;

        for (size_t i = 0; i < input_json.size(); i += chunk) {
            bool done = false;
            // When we're near the end of the data stream, the chunk length may
            // vary.
            if (i + chunk >= input_json.size()) {
                chunk = input_json.size() - i;
                done = true;
            }
            // Feed the parser with a data chunk and parse it.
            feed.postBuffer(&input_json[i], chunk);
            feed.poll();
            if (!done) {
                ASSERT_TRUE(feed.needData());
            }
        }

        // Convert parsed/collected data in the feed into the structure of
        // elements.
        ConstElementPtr element_from_feed = feed.toElement();
        EXPECT_TRUE(element_from_feed->equals(*expected_output));
    }

    /// @brief Test that the JSONFeed correctly recognizes the beginning
    /// and the end of the JSON structure.
    ///
    /// @param input_json A string holding an input JSON structure.
    /// @param expected_output A string holding expected output from the
    /// @ref JSONFeed::getProcessedText.
    void testRead(const std::string& input_json,
                  const std::string& expected_output) {
        JSONFeed feed;
        ASSERT_NO_THROW(feed.initModel());

        // Post the data into the feed in 10 bytes long chunks.
        size_t chunk = 10;

        for (size_t i = 0; i < input_json.size(); i += chunk) {
            bool done = false;
            // When we're near the end of the data stream, the chunk length may
            // vary.
            if (i + chunk >= input_json.size()) {
                chunk = input_json.size() - i;
                done = true;
            }
            // Feed the parser with a data chunk and parse it.
            feed.postBuffer(&input_json[i], chunk);
            feed.poll();
            if (!done) {
                ASSERT_TRUE(feed.needData());
            }
        }

        EXPECT_EQ(expected_output, feed.getProcessedText());
    }

    /// @brief Test that the @ref JSONFeed signals an error when the input
    /// string holds invalid data.
    ///
    /// @param input_json A string holding an input JSON structure.
    /// @param err_msg A string holding an expected error message.
    void testInvalidRead(const std::string& input_json,
                         const std::string& err_msg) {
        JSONFeed feed;
        ASSERT_NO_THROW(feed.initModel());

        ASSERT_NO_THROW(feed.postBuffer(&input_json[0], input_json.size()));
        ASSERT_NO_THROW(feed.poll());

        EXPECT_FALSE(feed.needData());
        EXPECT_FALSE(feed.feedOk());

        EXPECT_EQ(err_msg, feed.getErrorMessage());
    }

    /// @brief JSON map holding a number of lists.
    ConstElementPtr json_map_;

    /// @brief JSON list holding a map of lists.
    ConstElementPtr json_list_;

};

// This test verifies that toElement should not be called before
// the feed detects the end of the data stream.
TEST_F(JSONFeedTest, toElementTooSoon) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{\n";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_TRUE(feed.needData());
    EXPECT_THROW(feed.toElement(), JSONFeedError);
}

// This test verifies that toElement checks JSON syntax as a side effect.
TEST_F(JSONFeedTest, badJSON) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{\n]\n";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_THROW(feed.toElement(), JSONFeedError);
}

// This test verifies that a JSON structure starting with '{' is accepted
// and parsed.
TEST_F(JSONFeedTest, startWithBrace) {
    std::string json = createJSON();
    testRead(json, json_map_);
}

// This test verifies that a JSON structure starting with '[' is accepted
// and parsed.
TEST_F(JSONFeedTest, startWithSquareBracket) {
    std::string json = createJSON();
    json = std::string("[") + json + std::string("]");
    testRead(json, json_list_);
}

// This test verifies that input JSON can be preceded with whitespaces.
TEST_F(JSONFeedTest, startWithWhitespace) {
    std::string json = createJSON();
    json = std::string("  \r\r\t  ") + json;
    testRead(json, json_map_);
}

// This test verifies that an empty map is accepted and parsed.
TEST_F(JSONFeedTest, emptyMap) {
    std::string json = "{}";
    testRead(json, Element::createMap());
}

// This test verifies that an empty list is accepted and parsed.
TEST_F(JSONFeedTest, emptyList) {
    std::string json = "[  ]";
    testRead(json, Element::createList());
}

// This test verifies that an error is signalled when a JSON structure
// is preceded by invalid character.
TEST_F(JSONFeedTest, unexpectedFirstCharacter) {
    std::string json = "a {}";
    std::string err_msg = "invalid first character a";
    testInvalidRead(json, err_msg);
}

// This test verifies that an error is signalled when a JSON structure
// is preceded by white spaces and an invalid character.
TEST_F(JSONFeedTest, unexpectedCharacter) {
    std::string json = " a {}";
    std::string err_msg = "invalid character a";
    testInvalidRead(json, err_msg);
}

// This test verifies that an error is signalled when the JSON structure
// begins by a string.
TEST_F(JSONFeedTest, stringFirst) {
    std::string json = "\"foo\"";
    std::string err_msg = "invalid first character \"";
    testInvalidRead(json, err_msg);
}

// This test verifies that an error is signalled when the JSON structure
// begins by white spaces followed by a string.
TEST_F(JSONFeedTest, stringBefore) {
    std::string json = " \"foo\"";
    std::string err_msg = "invalid character \"";
    testInvalidRead(json, err_msg);
}

// This test verifies that an error is signalled when a JSON structure
// lacks an opening brace character.
TEST_F(JSONFeedTest, noOpeningBrace) {
    std::string json = "\"x\": \"y\" }";
    std::string err_msg = "invalid first character \"";
    testInvalidRead(json, err_msg);
}

// This test verifies that an error is signalled when a JSON structure
// lacks an opening square bracket.
TEST_F(JSONFeedTest, noOpeningSquareBracket) {
    std::string json = "1, 2 ]";
    std::string err_msg = "invalid first character 1";
    testInvalidRead(json, err_msg);
}

// This test verifies that a string is correctly handled
TEST_F(JSONFeedTest, string) {
    std::string json = "{ \"braces\": \"}}}}\" }";
    ElementPtr expected = Element::createMap();
    expected->set("braces", Element::create("}}}}"));
    testRead(json, expected);
}

// This test verifies that a string with escapes is correctly handled
TEST_F(JSONFeedTest, escape) {
    std::string json = "{ \"escapes\": \"\\n\\t\\\"\\\\\" }";
    ElementPtr expected = Element::createMap();
    expected->set("escapes", Element::create("\n\t\"\\"));
    testRead(json, expected);
}

// This test verifies that white spaces before JSON are ignored.
TEST_F(JSONFeedTest, whiteSpaceBefore) {
    std::string json = " \n  [ ]\n";
    std::string expected = "[ ]";
    testRead(json, expected);
}

// This test verifies that bash style comments before JSON are ignored.
TEST_F(JSONFeedTest, bashCommentBefore) {
    std::string json = "# ahah\n  # foo\"bar\n{ }\n";
    std::string expected = "{ }";
    testRead(json, expected);
}

// This test verifies that C++ style comments before JSON are ignored.
TEST_F(JSONFeedTest, cppCommentBefore) {
    std::string json = "// ahah\n  // foo\"bar\n[ 12 ]\n";
    std::string expected = "[ 12 ]";
    testRead(json, expected);
}

// This test verifies that multi-line comments before JSON are ignored.
TEST_F(JSONFeedTest, multiLineCommentBefore) {
    std::string json = "/* ahah\n \"// foo*bar**/\n { \"foo\": \"bar\" }\n";
    std::string expected = "{ \"foo\": \"bar\" }";
    testRead(json, expected);
}

// This test verifies that an error is signalled when a slash does not
// begin a C++ or C style comment before JSON.
TEST_F(JSONFeedTest, badCommentBefore) {
    std::string json = "/# foo\n [ ]\n";
    std::string err_msg = "invalid characters /#";
    testInvalidRead(json, err_msg);
}

// This test verifies that bash style comments are ignored.
TEST_F(JSONFeedTest, bashComments) {
    std::string json = "{ # ahah\n \"foo\": # value?\n \"bar\" }";
    std::string expected = "{ \n \"foo\": \n \"bar\" }";
    testRead(json, expected);
}

// This test verifies that C++ style comments are ignored.
TEST_F(JSONFeedTest, cppComments) {
    std::string json = "[ // ahah\n \"foo\", /// value?\n \"bar\" ]";
    std::string expected = "[ \n \"foo\", \n \"bar\" ]";
    testRead(json, expected);
}

// This test verifies that multi-line comments are ignored.
TEST_F(JSONFeedTest, multiLineComments) {
    std::string json = "{ /* ahah\n \"// foo*bar**/\n \"foo\": \"bar\" }\n";
    std::string expected = "{ \n\n \"foo\": \"bar\" }";
    testRead(json, expected);
}

// This test verifies that an error is signalled a slash does not begin
// a C++ or C style comment.
TEST_F(JSONFeedTest, badComment) {
    std::string json = "[ /# foo\n ]\n";
    std::string err_msg = "invalid characters /#";
    testInvalidRead(json, err_msg);
}

// This test verifies that trailing garbage is ignored.
TEST_F(JSONFeedTest, trailing) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "[ 1, 2] 3, 4]";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_TRUE(feed.feedOk());
    std::string expected = "[ 1, 2]";
    EXPECT_EQ(expected, feed.getProcessedText());
}

// Example from DHCPv4 unit tests.
TEST_F(JSONFeedTest, bashComment4) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{ \"Dhcp4\": { \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},\n"
        "# this is a comment\n"
        "\"rebind-timer\": 2000, \n"
        "# lots of comments here\n"
        "# and here\n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 } }";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_TRUE(feed.feedOk());
    EXPECT_NO_THROW(feed.toElement());
}

// Example from DHCPv4 unit tests.
TEST_F(JSONFeedTest, bashCommentsInline4) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{ \"Dhcp4\": { \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},\n"
        "\"rebind-timer\": 2000, # everything after # is ignored\n"
        "\"renew-timer\": 1000, # this will be ignored, too\n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 } }";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_TRUE(feed.feedOk());
    EXPECT_NO_THROW(feed.toElement());
}

// Example from DHCPv6 unit tests.
TEST_F(JSONFeedTest, cppComments6) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{ \"Dhcp6\": { \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},\n"
        "\"preferred-lifetime\": 3000, // this is a comment \n"
        "\"rebind-timer\": 2000, // everything after // is ignored\n"
        "\"renew-timer\": 1000, // this will be ignored, too\n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 } }";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_TRUE(feed.feedOk());
    EXPECT_NO_THROW(feed.toElement());
}

// Example from DHCPv6 unit tests.
TEST_F(JSONFeedTest, multilineComments6) {
    JSONFeed feed;
    ASSERT_NO_THROW(feed.initModel());
    std::string json = "{ \"Dhcp6\": { \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},\n"
        "\"preferred-lifetime\": 3000, /* this is a C style comment\n"
        "that\n can \n span \n multiple \n lines */ \n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000, \n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 } }";
    feed.postBuffer(&json[0], json.size());
    feed.poll();
    EXPECT_FALSE(feed.needData());
    EXPECT_TRUE(feed.feedOk());
    EXPECT_NO_THROW(feed.toElement());
}

} // end of anonymous namespace.
