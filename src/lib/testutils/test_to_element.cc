// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/test_to_element.h>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace isc::data;
using namespace std;

namespace isc {
namespace test {

void expectEqWithDiff(ConstElementPtr const& a, ConstElementPtr const& b) {
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    string const pretty_print_a(prettyPrint(a));
    string const pretty_print_b(prettyPrint(b));
    EXPECT_EQ(pretty_print_a, pretty_print_b)
        << endl
        << "Diff:" << endl
        << generateDiff(pretty_print_a, pretty_print_b) << endl;
}

void expectEqWithDiff(ElementPtr const& a, ElementPtr const& b) {
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    string const pretty_print_a(prettyPrint(a));
    string const pretty_print_b(prettyPrint(b));
    EXPECT_EQ(pretty_print_a, pretty_print_b)
        << endl
        << "Diff:" << endl
        << generateDiff(pretty_print_a, pretty_print_b) << endl;
}

#ifdef HAVE_CREATE_UNIFIED_DIFF
string generateDiff(string left, string right) {
    vector<string> left_lines;
    boost::split(left_lines, left, boost::is_any_of("\n"));
    vector<string> right_lines;
    boost::split(right_lines, right, boost::is_any_of("\n"));
    using namespace testing::internal;
    return (edit_distance::CreateUnifiedDiff(left_lines, right_lines));
}
#else
std::string generateDiff(std::string, std::string) {
    return ("N/A: !HAVE_CREATE_UNIFIED_DIFF");
}
#endif

}  // namespace test
}  // namespace isc
