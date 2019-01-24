// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2017-2018 Deutsche Telekom AG.
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <cql/cql_connection.h>
#include <cql/cql_exchange.h>

#include <cstring>

#include <boost/any.hpp>

#include <gtest/gtest.h>

using namespace isc::db;

namespace {

struct CqlConnectionTest {};

/// @brief Check that the key is properly hashed for StatementMap.
TEST(CqlConnectionTest, statementMapHash) {
    // Build std::strings to prevent optimizations on underlying C string.
    std::string tag1_s = "same";
    std::string tag2_s = "same";
    char const* const tag1 = tag1_s.c_str();
    char const* const tag2 = tag2_s.c_str();

    // Make sure addresses are different.
    EXPECT_NE(tag1, tag2);

    // Insert two entries with the same key value.
    StatementMap map;
    map.insert({tag1, {tag1, "your fancy select here"}});
    map.insert({tag2, {tag2, "DELETE FROM world.evil}"}});

    // Make sure the first one was overwritten.
    std::string const tag1_text = map.at(tag1).text_;
    std::string const tag2_text = map.at(tag2).text_;
    EXPECT_NE(tag1_text.size(), 0);
    EXPECT_NE(tag2_text.size(), 0);
    ASSERT_EQ(tag1_text, tag2_text);
    ASSERT_EQ(map.size(), 1u);
}

}  // namespace
