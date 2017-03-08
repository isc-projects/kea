// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
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

namespace isc {
namespace test {

#ifdef HAVE_CREATE_UNIFIED_DIFF
std::string generateDiff(std::string left, std::string right) {
    std::vector<std::string> left_lines;
    boost::split(left_lines, left, boost::is_any_of("\n"));
    std::vector<std::string> right_lines;
    boost::split(right_lines, right, boost::is_any_of("\n"));
    using namespace testing::internal;
    return (edit_distance::CreateUnifiedDiff(left_lines, right_lines));
}
#else
std::string generateDiff(std::string, std::string) {
    return ("");
}
#endif

}; // end of isc::test namespace
}; // end of isc namespace
