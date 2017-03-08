// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_TO_ELEMENT_H
#define TEST_TO_ELEMENT_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <gtest/gtest.h>
#include <string>
#ifdef HAVE_IS_BASE_OF
#include <type_traits>
#endif

#ifndef CONFIG_H_WAS_INCLUDED
#error config.h must be included before test_to_element.h
#endif

namespace isc {
namespace test {

/// @brief Return the difference between two strings
///
/// Use the gtest >= 1.8.0 tool which builds the difference between
/// two vectors of lines.
///
/// @param left left string
/// @param right right string
/// @return the unified diff between left and right
std::string generateDiff(std::string left, std::string right);

/// @brief Run a test using toElement() method with a string
///
/// @tparam Cfg the class implementing the toElement() method
/// @param expected the expected textual value
/// @param cfg an instance of the Cfg class
template<typename Cfg>
void runToElementTest(const std::string& expected, const Cfg& cfg) {
    using namespace isc::data;
#ifdef HAVE_IS_BASE_OF
    static_assert(std::is_base_of<CfgToElement, Cfg>::value,
                  "CfgToElement is not a base of the template parameter");
#endif
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(expected)) << expected;
    ConstElementPtr unparsed;
    ASSERT_NO_THROW(unparsed = cfg.toElement());
    if (!isEquivalent(json, unparsed)) {
        std::string wanted = prettyPrint(json);
        std::string got = prettyPrint(unparsed);
        ADD_FAILURE() << "Expected:\n" << wanted << "\n"
                      << "Actual:\n" << got
#ifdef HAVE_CREATE_UNIFIED_DIFF
                      << "\nDiff:\n" << generateDiff(wanted, got)
#endif
                      << "\n";
    }
}

/// @brief Run a test using toElement() method with an Element
///
/// @tparam Cfg the class implementing the toElement() method
/// @param expected the expected element value
/// @param cfg an instance of the Cfg class
template<typename Cfg>
void runToElementTest(isc::data::ConstElementPtr expected, const Cfg& cfg) {
#ifdef HAVE_IS_BASE_OF
    static_assert(std::is_base_of<isc::data::CfgToElement, Cfg>::value,
                  "CfgToElement is not a base of the template parameter");
#endif
    isc::data::ConstElementPtr unparsed;
    ASSERT_NO_THROW(unparsed = cfg.toElement());
    if (!isEquivalent(expected, unparsed)) {
        std::string wanted = prettyPrint(expected);
        std::string got = prettyPrint(unparsed);
        ADD_FAILURE() << "Expected:\n" << wanted << "\n"
                      << "Actual:\n" << got
#ifdef HAVE_CREATE_UNIFIED_DIFF
                      << "\nDiff:\n" << generateDiff(wanted, got)
#endif
                      << "\n";
    }
}

}; // end of isc::test namespace
}; // end of isc namespace

#endif // TEST_TO_ELEMENT_H
