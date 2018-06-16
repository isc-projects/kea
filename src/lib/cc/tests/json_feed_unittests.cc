// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
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

    /// @brief Test that the @ref JSONFeed signals an error when the input
    /// string holds invalid data.
    ///
    /// @param input_json A string holding an input JSON structure.
    void testInvalidRead(const std::string& input_json) {
        JSONFeed feed;
        ASSERT_NO_THROW(feed.initModel());

        ASSERT_NO_THROW(feed.postBuffer(&input_json[0], input_json.size()));
        ASSERT_NO_THROW(feed.poll());

        EXPECT_FALSE(feed.needData());
        EXPECT_FALSE(feed.feedOk());
    }

    /// @brief JSON map holding a number of lists.
    ConstElementPtr json_map_;

    /// @brief JSON list holding a map of lists.
    ConstElementPtr json_list_;

};

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
TEST_F(JSONFeedTest, unexpectedCharacter) {
    std::string json = "a {}";
    testInvalidRead(json);
}

// This test verifies that an error is signalled when a JSON structure
// lacks an opening brace character.
TEST_F(JSONFeedTest, noOpeningBrace) {
    std::string json = "\"x\": \"y\" }";
    testInvalidRead(json);
}

// This test verifies that an error is signalled when a JSON structure
// lacks an opening square bracket.
TEST_F(JSONFeedTest, noOpeningSquareBracket) {
    std::string json = "\"x\", \"y\" ]";
    testInvalidRead(json);
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

} // end of anonymous namespace.
