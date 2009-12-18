// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"

#include "unittest_util.h"

#include <gtest/gtest.h>

using isc::UnitTestUtil;
using isc::dns::InputBuffer;
using isc::dns::OutputBuffer;
using isc::dns::Name;
using isc::dns::NameComparisonResult;

namespace {
class NameTest : public ::testing::Test {
protected:
    NameTest() : example_name("www.example.com"),
                 example_name_upper("WWW.EXAMPLE.COM"),
                 buffer_actual(0), buffer_expected(0)
    {}

    Name example_name;
    Name example_name_upper;
    OutputBuffer buffer_actual, buffer_expected;

    static const size_t MAX_WIRE = Name::MAX_WIRE;
    static const size_t MAX_LABELS = Name::MAX_LABELS;
    //
    // helper methods
    //
    static Name nameFactoryFromWire(const char* datafile, size_t position,
                                    bool downcase = false);
    // construct a name including all non-upper-case-alphabet characters.
    static Name nameFactoryLowerCase();
    void compareInWireFormat(const Name& name_actual,
                             const Name& name_expected);
};

Name
NameTest::nameFactoryFromWire(const char* datafile, size_t position,
                              bool downcase)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    buffer.setPosition(position);

    return (Name(buffer, downcase));
}

Name
NameTest::nameFactoryLowerCase()
{
    std::string lowercase_namestr;
    lowercase_namestr.reserve(Name::MAX_WIRE);

    unsigned int ch = 0;
    unsigned int labelcount = 0;
    do {
        if (ch < 'A' || ch > 'Z') {
            std::ostringstream ss;
            ss.setf(std::ios_base::right, std::ios_base::adjustfield);
            ss.width(3);
            ss << std::setfill('0') << ch;
            lowercase_namestr += '\\' + ss.str();

            if (++labelcount == Name::MAX_LABELLEN) {
                lowercase_namestr.push_back('.');
                labelcount = 0;
            }
        }
    } while (++ch <= Name::MAX_WIRE);

    return (Name(lowercase_namestr));
}

void
NameTest::compareInWireFormat(const Name& name_actual,
                              const Name& name_expected)
{
    buffer_actual.clear();
    buffer_expected.clear();

    name_actual.toWire(buffer_actual);
    name_expected.toWire(buffer_expected);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        buffer_actual.getData(), buffer_actual.getLength(),
                        buffer_expected.getData(), buffer_expected.getLength());
}

TEST_F(NameTest, fromText)
{
    std::vector<std::string> strnames;
    strnames.push_back("www.example.com");
    strnames.push_back("www.example.com."); // with a trailing dot
    strnames.push_back("wWw.exAmpLe.com");  // mixed cases
    strnames.push_back("\\wWw.exAmpLe.com"); // escape with a backslash
    // decimal representation for "WWW"
    strnames.push_back("\\087\\087\\087.example.com");

    std::vector<std::string>::const_iterator it;
    for (it = strnames.begin(); it != strnames.end(); ++it) {
        EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name, Name(*it));
    }

    // root names
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, Name("@"), Name("."));

    // downcase
    EXPECT_EQ(Name("Www.eXample.coM", true).toText(), example_name.toText());

    //
    // Tests for bogus names.  These should trigger an exception.
    //
    // empty label cannot be followed by another label
    EXPECT_THROW(Name(".a"), isc::dns::EmptyLabel);
    // duplicate period
    EXPECT_THROW(Name("a.."), isc::dns::EmptyLabel);
    // label length must be < 64
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "0123"), isc::dns::TooLongLabel);
    // now-unsupported bitstring labels
    EXPECT_THROW(Name("\\[b11010000011101]"), isc::dns::BadLabelType);
    // label length must be < 64
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "012\\x"), isc::dns::TooLongLabel);
    // but okay as long as resulting len < 64 even if the original string is
    // "too long"
    EXPECT_NO_THROW(Name("012345678901234567890123456789"
                         "012345678901234567890123456789"
                         "01\\x"));
    // incomplete \DDD pattern (exactly 3 D's must appear)
    EXPECT_THROW(Name("\\12abc"), isc::dns::BadEscape);
    // \DDD must not exceed 255
    EXPECT_THROW(Name("\\256"), isc::dns::BadEscape);
    // Same tests for \111 as for \\x above
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "012\\111"), isc::dns::TooLongLabel);
    EXPECT_NO_THROW(Name("012345678901234567890123456789"
                         "012345678901234567890123456789"
                         "01\\111"));
    // A domain name must be 255 octets or less
    EXPECT_THROW(Name("123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "1234"), isc::dns::TooLongName);
    // This is a possible longest name and should be accepted
    EXPECT_NO_THROW(Name("123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123"));
    // \DDD must consist of 3 digits.
    EXPECT_THROW(Name("\\12"), isc::dns::BadLabelType);

    // a name with the max number of labels.  should be constructed without
    // an error, and its length should be the max value.
    Name maxlabels = Name("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 40
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 80
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 120
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 160
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 200
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 240
                          "0.1.2.3.4.5.6.");
    EXPECT_EQ(MAX_LABELS, maxlabels.getLabels());
}

TEST_F(NameTest, fromWire)
{
    //
    // test cases derived from BIND9 tests.
    //
    // normal case with a compression pointer
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName,
                        nameFactoryFromWire("testdata/name_fromWire1", 25),
                        Name("vix.com"));
    // bogus label character (looks like a local compression pointer)
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire2", 25),
                 isc::dns::BadLabelType);
    // a bad compression pointer (too big)
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire3_1", 25),
                 isc::dns::BadPointer);
    // forward reference
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire3_2", 25),
                 isc::dns::BadPointer);
    // invalid name length
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire4", 550),
                 isc::dns::TooLongName);

    // skip test for from Wire5.  It's for disabling decompression, but our
    // implementation always allows it.

    // bad pointer (too big)
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire6", 25),
                 isc::dns::BadPointer);
    // input ends unexpectedly
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire7", 25),
                 isc::dns::IncompleteName);
    // many hops of compression but valid.  should succeed.
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName,
                        nameFactoryFromWire("testdata/name_fromWire8", 383),
                        Name("vix.com"));

    //
    // Additional test cases
    //

    // large names, a long but valid one, and invalid (too long) one.
    EXPECT_EQ(MAX_WIRE,
              nameFactoryFromWire("testdata/name_fromWire9", 0).getLength());
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire10", 0).getLength(),
                 isc::dns::TooLongName);

    // A name with possible maximum number of labels; awkward but valid
    EXPECT_EQ(nameFactoryFromWire("testdata/name_fromWire11", 0).getLabels(),
              MAX_LABELS);

    // Wire format including an invalid label length
    EXPECT_THROW(nameFactoryFromWire("testdata/name_fromWire12", 0),
                 isc::dns::BadLabelType);

    // converting upper-case letters to down-case
    EXPECT_EQ("vix.com.", nameFactoryFromWire("testdata/name_fromWire1",
                                              25, true).toText());
    EXPECT_EQ(3,
              nameFactoryFromWire("testdata/name_fromWire1", 25).getLabels());
}

TEST_F(NameTest, toText)
{
    // tests derived from BIND9
    EXPECT_EQ("a.b.c.d", Name("a.b.c.d").toText(true));
    EXPECT_EQ("a.\\\\[[.c.d", Name("a.\\\\[\\[.c.d").toText(true));
    EXPECT_EQ("a.b.C.d.", Name("a.b.C.d").toText(false));
    EXPECT_EQ("a.b.", Name("a.b.").toText(false));

    // test omit_final_dot.  It's false by default.
    EXPECT_EQ("a.b.c.d", Name("a.b.c.d.").toText(true));
    EXPECT_EQ(Name("a.b.").toText(false), Name("a.b.").toText());

    // the root name is a special case: omit_final_dot will be ignored.
    EXPECT_EQ(".", Name(".").toText(true));
}

TEST_F(NameTest, toWireBuffer)
{
    std::vector<unsigned char> data;
    OutputBuffer buffer(0);

    UnitTestUtil::readWireData(std::string("01610376697803636f6d00"), data);
    Name("a.vix.com.").toWire(buffer);
    EXPECT_EQ(true, buffer.getLength() == data.size() &&
              memcmp(buffer.getData(), &data[0], data.size()) == 0);
}

//
// Helper class to hold comparison test parameters.
//
struct CompareParameters {
    CompareParameters(const Name& n1, const Name&  n2,
                      NameComparisonResult::NameRelation r, int o,
                      unsigned int l) :
        name1(n1), name2(n2), reln(r), order(o), labels(l) {}
    static int normalizeOrder(int o)
    {
        if (o > 0) {
            return (1);
        } else if (o < 0) {
            return (-1);
        }
        return (0);
    }
    Name name1;
    Name name2;
    NameComparisonResult::NameRelation reln;
    int order;
    unsigned int labels;
};

TEST_F(NameTest, compare)
{
    std::vector<CompareParameters> params;
    params.push_back(CompareParameters(Name("c.d"), Name("a.b.c.d"),
                                       NameComparisonResult::SUPERDOMAIN,
                                       -1, 3));
    params.push_back(CompareParameters(Name("a.b.c.d"), Name("c.d"),
                                       NameComparisonResult::SUBDOMAIN, 1, 3));
    params.push_back(CompareParameters(Name("a.b.c.d"), Name("c.d.e.f"),
                                       NameComparisonResult::COMMONANCESTOR,
                                       -1, 1));
    params.push_back(CompareParameters(Name("a.b.c.d"), Name("f.g.c.d"),
                                       NameComparisonResult::COMMONANCESTOR,
                                       -1, 3));
    params.push_back(CompareParameters(Name("a.b.c.d"), Name("A.b.C.d."),
                                       NameComparisonResult::EQUAL,
                                       0, 5));

    std::vector<CompareParameters>::const_iterator it;
    for (it = params.begin(); it != params.end(); ++it) {
        NameComparisonResult result = (*it).name1.compare((*it).name2);
        EXPECT_EQ((*it).reln, result.getRelation());
        EXPECT_EQ((*it).order,
                  CompareParameters::normalizeOrder(result.getOrder()));
        EXPECT_EQ((*it).labels, result.getCommonLabels());
    }
}

TEST_F(NameTest, equal)
{
    EXPECT_TRUE(example_name == Name("WWW.EXAMPLE.COM."));
    EXPECT_TRUE(example_name.equals(Name("WWW.EXAMPLE.COM.")));
    EXPECT_TRUE(example_name != Name("www.example.org."));
    EXPECT_TRUE(example_name.nequals(Name("www.example.org.")));
}

TEST_F(NameTest, isWildcard)
{
    EXPECT_EQ(false, example_name.isWildcard());
    EXPECT_EQ(true, Name("*.a.example.com").isWildcard());
    EXPECT_EQ(false, Name("a.*.example.com").isWildcard());
}

TEST_F(NameTest, concatenate)
{
    NameComparisonResult result =
        Name("aaa.www.example.com.").compare(Name("aaa").concatenate(example_name));
    EXPECT_EQ(NameComparisonResult::EQUAL, result.getRelation());

    result = example_name.compare(Name(".").concatenate(example_name));
    EXPECT_EQ(NameComparisonResult::EQUAL, result.getRelation());

    result = example_name.compare(example_name.concatenate(Name(".")));
    EXPECT_EQ(NameComparisonResult::EQUAL, result.getRelation());

    // concatenating two valid names would result in too long a name.
    Name n1("123456789.123456789.123456789.123456789.123456789."
            "123456789.123456789.123456789.123456789.123456789."
            "123456789.123456789.123456789.123456789.123456789.");
    Name n2("123456789.123456789.123456789.123456789.123456789."
            "123456789.123456789.123456789.123456789.123456789."
            "1234.");
    EXPECT_THROW(n1.concatenate(n2), isc::dns::TooLongName);
}

TEST_F(NameTest, split)
{
    // normal cases with or without explicitly specifying the trailing dot.
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(1, 2),
                        Name("example.com."));
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(1, 3),
                        Name("example.com."));
    // edge cases: only the first or last label.
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(0, 1),
                        Name("www."));
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(3, 1),
                        Name("."));
    // invalid range: an exception should be thrown.
    EXPECT_THROW(example_name.split(1, 0), isc::dns::OutOfRange);
    EXPECT_THROW(example_name.split(2, 3), isc::dns::OutOfRange);
}

TEST_F(NameTest, downcase)
{
    compareInWireFormat(example_name_upper.downcase(), example_name);
    compareInWireFormat(nameFactoryLowerCase().downcase(),
                        nameFactoryLowerCase());
}
}
