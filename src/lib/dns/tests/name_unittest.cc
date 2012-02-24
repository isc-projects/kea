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

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include <dns/tests/unittest_util.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;

//
// XXX: these are defined as class static constants, but some compilers
// seemingly cannot find the symbols when used in the EXPECT_xxx macros.
//
const size_t Name::MAX_WIRE;
const size_t Name::MAX_LABELS;

namespace {
class NameTest : public ::testing::Test {
protected:
    NameTest() : example_name("www.example.com"),
                 example_name_upper("WWW.EXAMPLE.COM"),
                 small_name("aaa.example.com"),
                 large_name("zzz.example.com"),
                 buffer_actual(0), buffer_expected(0)
    {}

    const Name example_name;
    Name example_name_upper;    // this will be modified and cannot be const
    const Name small_name;
    const Name large_name;
    OutputBuffer buffer_actual, buffer_expected;

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

const Name downcased_global("\\255.EXAMPLE.COM", true);

Name
NameTest::nameFactoryFromWire(const char* datafile, size_t position,
                              bool downcase)
{
    vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    buffer.setPosition(position);

    return (Name(buffer, downcase));
}

Name
NameTest::nameFactoryLowerCase() {
    string lowercase_namestr;
    lowercase_namestr.reserve(Name::MAX_WIRE);

    unsigned int ch = 0;
    unsigned int labelcount = 0;
    do {
        if (ch < 'A' || ch > 'Z') {
            ostringstream ss;
            ss.setf(ios_base::right, ios_base::adjustfield);
            ss.width(3);
            ss << setfill('0') << ch;
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

TEST_F(NameTest, nonlocalObject) {
    // A previous version of code relied on a non local static object for
    // name construction, so a non local static Name object defined outside
    // the name module might not be initialized correctly.  This test detects
    // that kind of bug.
    EXPECT_EQ("\\255.example.com.", downcased_global.toText());
}

TEST_F(NameTest, fromText) {
    vector<string> strnames;
    strnames.push_back("www.example.com");
    strnames.push_back("www.example.com."); // with a trailing dot
    strnames.push_back("wWw.exAmpLe.com");  // mixed cases
    strnames.push_back("\\wWw.exAmpLe.com"); // escape with a backslash
    // decimal representation for "WWW"
    strnames.push_back("\\087\\087\\087.example.com");

    vector<string>::const_iterator it;
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
    EXPECT_THROW(Name(".a"), EmptyLabel);
    // duplicate period
    EXPECT_THROW(Name("a.."), EmptyLabel);
    // label length must be < 64
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "0123"), TooLongLabel);
    // now-unsupported bitstring labels
    EXPECT_THROW(Name("\\[b11010000011101]"), BadLabelType);
    // label length must be < 64
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "012\\x"), TooLongLabel);
    // but okay as long as resulting len < 64 even if the original string is
    // "too long"
    EXPECT_NO_THROW(Name("012345678901234567890123456789"
                         "012345678901234567890123456789"
                         "01\\x"));
    // incomplete \DDD pattern (exactly 3 D's must appear)
    EXPECT_THROW(Name("\\12abc"), BadEscape);
    // \DDD must not exceed 255
    EXPECT_THROW(Name("\\256"), BadEscape);
    // Same tests for \111 as for \\x above
    EXPECT_THROW(Name("012345678901234567890123456789"
                      "012345678901234567890123456789"
                      "012\\111"), TooLongLabel);
    EXPECT_NO_THROW(Name("012345678901234567890123456789"
                         "012345678901234567890123456789"
                         "01\\111"));
    // A domain name must be 255 octets or less
    EXPECT_THROW(Name("123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "123456789.123456789.123456789.123456789.123456789."
                      "1234"), TooLongName);
    // This is a possible longest name and should be accepted
    EXPECT_NO_THROW(Name("123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123456789.123456789.123456789.123456789.123456789."
                         "123"));
    // \DDD must consist of 3 digits.
    EXPECT_THROW(Name("\\12"), IncompleteName);

    // a name with the max number of labels.  should be constructed without
    // an error, and its length should be the max value.
    Name maxlabels = Name("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 40
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 80
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 120
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 160
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 200
                          "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." // 240
                          "0.1.2.3.4.5.6.");
    EXPECT_EQ(Name::MAX_LABELS, maxlabels.getLabelCount());
}

TEST_F(NameTest, fromWire) {
    //
    // test cases derived from BIND9 tests.
    //
    // normal case with a compression pointer
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName,
                        nameFactoryFromWire("name_fromWire1", 25),
                        Name("vix.com"));
    // bogus label character (looks like a local compression pointer)
    EXPECT_THROW(nameFactoryFromWire("name_fromWire2", 25), DNSMessageFORMERR);
    // a bad compression pointer (too big)
    EXPECT_THROW(nameFactoryFromWire("name_fromWire3_1", 25),
                 DNSMessageFORMERR);
    // forward reference
    EXPECT_THROW(nameFactoryFromWire("name_fromWire3_2", 25),
                 DNSMessageFORMERR);
    // invalid name length
    EXPECT_THROW(nameFactoryFromWire("name_fromWire4", 550), DNSMessageFORMERR);

    // skip test for from Wire5.  It's for disabling decompression, but our
    // implementation always allows it.

    // bad pointer (too big)
    EXPECT_THROW(nameFactoryFromWire("name_fromWire6", 25), DNSMessageFORMERR);
    // input ends unexpectedly
    EXPECT_THROW(nameFactoryFromWire("name_fromWire7", 25), DNSMessageFORMERR);
    // many hops of compression but valid.  should succeed.
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName,
                        nameFactoryFromWire("name_fromWire8", 383),
                        Name("vix.com"));

    //
    // Additional test cases
    //

    // large names, a long but valid one, and invalid (too long) one.
    EXPECT_EQ(Name::MAX_WIRE,
              nameFactoryFromWire("name_fromWire9", 0).getLength());
    EXPECT_THROW(nameFactoryFromWire("name_fromWire10", 0).getLength(),
                 DNSMessageFORMERR);

    // A name with possible maximum number of labels; awkward but valid
    EXPECT_EQ(nameFactoryFromWire("name_fromWire11", 0).getLabelCount(),
              Name::MAX_LABELS);

    // Wire format including an invalid label length
    EXPECT_THROW(nameFactoryFromWire("name_fromWire12", 0), DNSMessageFORMERR);

    // converting upper-case letters to down-case
    EXPECT_EQ("vix.com.",
              nameFactoryFromWire("name_fromWire1", 25, true).toText());
    EXPECT_EQ(3, nameFactoryFromWire("name_fromWire1", 25).getLabelCount());
}

TEST_F(NameTest, copyConstruct) {
    Name copy(example_name);
    EXPECT_EQ(copy, example_name);

    // Check the copied data is valid even after the original is deleted
    Name* copy2 = new Name(example_name);
    Name copy3(*copy2);
    delete copy2;
    EXPECT_EQ(copy3, example_name);
}

TEST_F(NameTest, assignment) {
    Name copy(".");
    copy = example_name;
    EXPECT_EQ(copy, example_name);

    // Check if the copied data is valid even after the original is deleted
    Name* copy2 = new Name(example_name);
    Name copy3(".");
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(copy3, example_name);

    // Self assignment
    copy = copy;
    EXPECT_EQ(example_name, copy);
}

TEST_F(NameTest, toText) {
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

    // test all printable characters to see whether special characters are
    // escaped while the others are intact.  note that the conversion is
    // implementation specific; for example, it's not invalid to escape a
    // "normal" character such as 'a' with regard to the standard.
    string all_printable("!\\\"#\\$%&'\\(\\)*+,-\\./0123456789:\\;<=>?\\@"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "[\\\\]^_.`abcdefghijklmnopqrstuvwxyz{|}~.");
    EXPECT_EQ(all_printable,
              nameFactoryFromWire("name_fromWire13", 0).toText());

    string all_nonprintable(
        "\\000\\001\\002\\003\\004\\005\\006\\007\\008\\009"
        "\\010\\011\\012\\013\\014\\015\\016\\017\\018\\019"
        "\\020\\021\\022\\023\\024\\025\\026\\027\\028\\029"
        "\\030\\031\\032\\127\\128\\129"
        "\\130\\131\\132\\133\\134\\135\\136\\137\\138\\139"
        "\\140\\141\\142\\143\\144\\145\\146\\147\\148\\149"
        "\\150\\151\\152\\153\\154\\155\\156."
        "\\157\\158\\159"
        "\\160\\161\\162\\163\\164\\165\\166\\167\\168\\169"
        "\\170\\171\\172\\173\\174\\175\\176\\177\\178\\179"
        "\\180\\181\\182\\183\\184\\185\\186\\187\\188\\189"
        "\\190\\191\\192\\193\\194\\195\\196\\197\\198\\199"
        "\\200\\201\\202\\203\\204\\205\\206\\207\\208\\209"
        "\\210\\211\\212\\213\\214\\215\\216\\217\\218\\219."
        "\\220\\221\\222\\223\\224\\225\\226\\227\\228\\229"
        "\\230\\231\\232\\233\\234\\235\\236\\237\\238\\239"
        "\\240\\241\\242\\243\\244\\245\\246\\247\\248\\249"
        "\\250\\251\\252\\253\\254\\255.");
    EXPECT_EQ(all_nonprintable,
              nameFactoryFromWire("name_fromWire14", 0).toText());
}

TEST_F(NameTest, toWireBuffer) {
    vector<unsigned char> data;
    OutputBuffer buffer(0);

    UnitTestUtil::readWireData(string("01610376697803636f6d00"), data);
    Name("a.vix.com.").toWire(buffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &data[0], data.size(),
                        buffer.getData(), buffer.getLength());
}

//
// We test various corner cases in Renderer tests, but add this test case
// to fill the code coverage gap.
//
TEST_F(NameTest, toWireRenderer) {
    vector<unsigned char> data;
    MessageRenderer renderer;

    UnitTestUtil::readWireData(string("01610376697803636f6d00"), data);
    Name("a.vix.com.").toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &data[0], data.size(),
                        renderer.getData(), renderer.getLength());
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

TEST_F(NameTest, compare) {
    vector<CompareParameters> params;
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

    vector<CompareParameters>::const_iterator it;
    for (it = params.begin(); it != params.end(); ++it) {
        NameComparisonResult result = (*it).name1.compare((*it).name2);
        EXPECT_EQ((*it).reln, result.getRelation());
        EXPECT_EQ((*it).order,
                  CompareParameters::normalizeOrder(result.getOrder()));
        EXPECT_EQ((*it).labels, result.getCommonLabels());
    }
}

TEST_F(NameTest, equal) {
    EXPECT_TRUE(example_name == Name("WWW.EXAMPLE.COM."));
    EXPECT_TRUE(example_name.equals(Name("WWW.EXAMPLE.COM.")));
    EXPECT_TRUE(example_name != Name("www.example.org."));
    EXPECT_TRUE(example_name.nequals(Name("www.example.org.")));
    // lengths don't match
    EXPECT_TRUE(example_name != Name("www2.example.com."));
    EXPECT_TRUE(example_name.nequals(Name("www2.example.com.")));
    // lengths are equal, but # of labels don't match (first test checks the
    // prerequisite).
    EXPECT_EQ(example_name.getLength(), Name("www\\.example.com.").getLength());
    EXPECT_TRUE(example_name != Name("www\\.example.com."));
    EXPECT_TRUE(example_name.nequals(Name("www\\.example.com.")));
}

TEST_F(NameTest, isWildcard) {
    EXPECT_FALSE(example_name.isWildcard());
    EXPECT_TRUE(Name("*.a.example.com").isWildcard());
    EXPECT_FALSE(Name("a.*.example.com").isWildcard());
}

TEST_F(NameTest, concatenate) {
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
    EXPECT_THROW(n1.concatenate(n2), TooLongName);
}

TEST_F(NameTest, reverse) {
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.reverse(),
                        Name("com.example.www."));
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, Name(".").reverse(),
                        Name("."));
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName,
                        Name("a.b.c.d.e.f.g.h.i.j.k.l.m.n.o.p.q.r.s").reverse(),
                        Name("s.r.q.p.o.n.m.l.k.j.i.h.g.f.e.d.c.b.a"));
}

TEST_F(NameTest, split) {
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
    EXPECT_THROW(example_name.split(1, 0), OutOfRange);
    EXPECT_THROW(example_name.split(2, 3), OutOfRange);

    // invalid range: the following parameters would cause overflow,
    // bypassing naive validation.
    EXPECT_THROW(example_name.split(1, numeric_limits<unsigned int>::max()),
                 OutOfRange);
}

TEST_F(NameTest, split_for_suffix) {
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(1),
                        Name("example.com"));
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(0),
                        example_name);
    EXPECT_PRED_FORMAT2(UnitTestUtil::matchName, example_name.split(3),
                        Name("."));

    // Invalid case: the level must be less than the original label count.
    EXPECT_THROW(example_name.split(4), OutOfRange);
}

TEST_F(NameTest, downcase) {
    // usual case: all-upper case name to all-lower case
    compareInWireFormat(example_name_upper.downcase(), example_name);
    // confirm that non upper-case characters are intact
    compareInWireFormat(nameFactoryLowerCase().downcase(),
                        nameFactoryLowerCase());
    // confirm the calling object is actually modified
    example_name_upper.downcase();
    compareInWireFormat(example_name_upper, example_name);
    
}

TEST_F(NameTest, at) {
    // Confirm at() produces the exact sequence of wire-format name data
    vector<uint8_t> data;

    for (size_t i = 0; i < example_name.getLength(); i++) {
        data.push_back(example_name.at(i));
    }

    example_name.toWire(buffer_expected);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &data[0], data.size(), buffer_expected.getData(),
                        buffer_expected.getLength());

    // Out-of-range access: should trigger an exception.
    EXPECT_THROW(example_name.at(example_name.getLength()), OutOfRange);
}

//
// The following set of tests confirm the result of <=, <, >=, >
// The test logic is simple, and all tests are just straightforward variations
// of the first one.
//
TEST_F(NameTest, leq) {
    // small <= large is true
    EXPECT_TRUE(small_name.leq(large_name));
    EXPECT_TRUE(small_name <= large_name);

    // small <= small is true
    EXPECT_TRUE(small_name.leq(small_name));
    EXPECT_TRUE(small_name <= small_name);

    // large <= small is false
    EXPECT_FALSE(large_name.leq(small_name));
    EXPECT_FALSE(large_name <= small_name);
}

TEST_F(NameTest, geq) {
    EXPECT_TRUE(large_name.geq(small_name));
    EXPECT_TRUE(large_name >= small_name);

    EXPECT_TRUE(large_name.geq(large_name));
    EXPECT_TRUE(large_name >= large_name);

    EXPECT_FALSE(small_name.geq(large_name));
    EXPECT_FALSE(small_name >= large_name);
}

TEST_F(NameTest, lthan) {
    EXPECT_TRUE(small_name.lthan(large_name));
    EXPECT_TRUE(small_name < large_name);

    EXPECT_FALSE(small_name.lthan(small_name));
    EXPECT_FALSE(small_name < small_name);

    EXPECT_FALSE(large_name.lthan(small_name));
    EXPECT_FALSE(large_name < small_name);
}

TEST_F(NameTest, gthan) {
    EXPECT_TRUE(large_name.gthan(small_name));
    EXPECT_TRUE(large_name > small_name);

    EXPECT_FALSE(large_name.gthan(large_name));
    EXPECT_FALSE(large_name > large_name);

    EXPECT_FALSE(small_name.gthan(large_name));
    EXPECT_FALSE(small_name > large_name);
}

TEST_F(NameTest, constants) {
    EXPECT_EQ(Name("."), Name::ROOT_NAME());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(NameTest, LeftShiftOperator) {
    ostringstream oss;
    oss << example_name;
    EXPECT_EQ(example_name.toText(), oss.str());
}
}
