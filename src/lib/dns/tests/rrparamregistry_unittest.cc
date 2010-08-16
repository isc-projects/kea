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

#include <dns/rrclass.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrparamregistry.h>
#include <dns/rrtype.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class RRParamRegistryTest : public ::testing::Test {
protected:
    RRParamRegistryTest()
    {
        ostringstream oss1;
        oss1 << test_class_code;
        test_class_unknown_str = "CLASS" + oss1.str();

        ostringstream oss2;
        oss2 << test_type_code;
        test_type_unknown_str = "TYPE" + oss2.str();
    }
    ~RRParamRegistryTest()
    {
        // cleanup any non well-known parameters that possibly remain
        // as a side effect.
        RRParamRegistry::getRegistry().removeType(test_type_code);
        RRParamRegistry::getRegistry().removeClass(test_class_code);
        RRParamRegistry::getRegistry().removeRdataFactory(
            RRType(test_type_code), RRClass(test_class_code));
        RRParamRegistry::getRegistry().removeRdataFactory(
            RRType(test_type_code));
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
    RRParamRegistry::getRegistry().addType(test_type_str, test_type_code);
    RRParamRegistry::getRegistry().addClass(test_class_str, test_class_code);
    EXPECT_EQ(65533, RRClass("TESTCLASS").getCode());
    EXPECT_EQ(65534, RRType("TESTTYPE").getCode());

    // the first removal attempt should succeed
    EXPECT_TRUE(RRParamRegistry::getRegistry().removeType(test_type_code));
    // then toText() should treat it as an "unknown" 
    EXPECT_EQ(test_type_unknown_str, RRType(test_type_code).toText());
    // attempt of removing non-existent mapping should result in 'false'
    EXPECT_FALSE(RRParamRegistry::getRegistry().removeType(test_type_code));

    // same set of tests for RR class.
    EXPECT_TRUE(RRParamRegistry::getRegistry().removeClass(test_class_code));
    EXPECT_EQ(test_class_unknown_str, RRClass(test_class_code).toText());
    EXPECT_FALSE(RRParamRegistry::getRegistry().removeClass(test_class_code));
}

TEST_F(RRParamRegistryTest, addError)
{
    // An attempt to override a pre-registered class should fail with an
    // exception, and the pre-registered one should remain in the registry.
    EXPECT_THROW(RRParamRegistry::getRegistry().addClass(test_class_str, 1),
                 RRClassExists);
    EXPECT_EQ("IN", RRClass(1).toText());

    // Same for RRType
    EXPECT_THROW(RRParamRegistry::getRegistry().addType(test_type_str, 1),
                 RRTypeExists);
    EXPECT_EQ("A", RRType(1).toText());
}

class TestRdataFactory : public AbstractRdataFactory {
public:
    virtual RdataPtr create(const string& rdata_str) const
    { return (RdataPtr(new in::A(rdata_str))); }
    virtual RdataPtr create(InputBuffer& buffer, size_t rdata_len) const
    { return (RdataPtr(new in::A(buffer, rdata_len))); }
    virtual RdataPtr create(const Rdata& source) const
    { return (RdataPtr(new in::A(dynamic_cast<const in::A&>(source)))); }
};

TEST_F(RRParamRegistryTest, addRemoveFactory)
{
    // By default, the test type/code pair should be considered "unknown",
    // so the following should trigger an exception.
    EXPECT_THROW(createRdata(RRType(test_type_code), RRClass(test_class_code),
                             "192.0.2.1"),
                 InvalidRdataText);
    // Add factories so that we can treat this pair just like in::A.
    RRParamRegistry::getRegistry().add(test_type_str, test_type_code,
                                       test_class_str, test_class_code,
                                       RdataFactoryPtr(new TestRdataFactory));
    // Now it should be accepted, and should be identical to the same data of
    // in::A.
    EXPECT_EQ(0, in::A("192.0.2.1").compare(
                  *createRdata(RRType(test_type_code), RRClass(test_class_code),
                              "192.0.2.1")));
    // It should still fail with other classes as we specified the factories
    // as class-specific.
    EXPECT_THROW(createRdata(RRType(test_type_code), RRClass("IN"),
                             "192.0.2.1"),
                 InvalidRdataText);
    // Add the factories also as a class independent RRtype
    RRParamRegistry::getRegistry().add(test_type_str, test_type_code,
                                       RdataFactoryPtr(new TestRdataFactory));
    // Now it should be okay for other classes than the test class.
    EXPECT_EQ(0, in::A("192.0.2.1").compare(
                  *createRdata(RRType(test_type_code), RRClass("IN"),
                              "192.0.2.1")));

    // Remove the added factories: first attempt should succeed; the second
    // should return false as there's no match
    EXPECT_TRUE(RRParamRegistry::getRegistry().removeRdataFactory(
                    RRType(test_type_code), RRClass(test_class_code)));
    EXPECT_FALSE(RRParamRegistry::getRegistry().removeRdataFactory(
                     RRType(test_type_code), RRClass(test_class_code)));
    EXPECT_TRUE(RRParamRegistry::getRegistry().removeRdataFactory(
                    RRType(test_type_code)));
    EXPECT_FALSE(RRParamRegistry::getRegistry().removeRdataFactory(
                     RRType(test_type_code)));
}

}
