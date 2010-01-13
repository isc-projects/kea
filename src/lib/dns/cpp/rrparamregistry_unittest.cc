// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <string>
#include <sstream>

#include <stdint.h>

#include <gtest/gtest.h>

#include "rrclass.h"
#include "rrparamregistry.h"
#include "rrtype.h"

using namespace std;
using namespace isc::dns;

namespace {
class RRParamRegistryTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        ostringstream oss1;
        oss1 << test_class_code;
        test_class_unknown_str = "CLASS" + oss1.str();

        ostringstream oss2;
        oss2 << test_type_code;
        test_type_unknown_str = "TYPE" + oss2.str();
    }

    string test_class_unknown_str;
    string test_type_unknown_str;

    // we assume class/type numbers are officially unassigned.  If not we'll
    // need to update the test cases.
    static const uint16_t test_class_code = 65533; 
    static const uint16_t test_type_code = 65534;
    static const string test_class_str;
    static const string test_type_str;
};

const string RRParamRegistryTest::test_class_str("TESTCLASS");
const string RRParamRegistryTest::test_type_str("TESTTYPE");

TEST_F(RRParamRegistryTest, addRemove)
{
    RRParamRegistry::getRegistry().add(test_class_str, test_class_code,
                                       test_type_str, test_type_code);
    EXPECT_EQ(65533, RRClass("TESTCLASS").getCode());
    EXPECT_EQ(65534, RRType("TESTTYPE").getCode());

    EXPECT_TRUE(RRParamRegistry::getRegistry().removeClass(65533));
    EXPECT_EQ(test_class_unknown_str, RRClass(test_class_code).toText());
    EXPECT_TRUE(RRParamRegistry::getRegistry().removeType(65534));
    EXPECT_EQ(test_type_unknown_str, RRType(test_type_code).toText());
}

TEST_F(RRParamRegistryTest, addError)
{
    // An attempt to override a pre-registered class should fail with an
    // exception, and the pre-registered one should remain in the registry.
    EXPECT_THROW(RRParamRegistry::getRegistry().add(test_class_str, 1,
                                                    test_type_str,
                                                    test_type_code),
                 RRClassExist);
    EXPECT_EQ("IN", RRClass(1).toText());

    // Same for RRType
    EXPECT_THROW(RRParamRegistry::getRegistry().add(test_class_str,
                                                    test_class_code,
                                                    test_type_str, 1),
                 RRTypeExist);
    EXPECT_EQ("A", RRType(1).toText());
}
}
