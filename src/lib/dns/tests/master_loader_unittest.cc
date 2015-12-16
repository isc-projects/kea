// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_loader_callbacks.h>
#include <dns/master_loader.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/name.h>
#include <dns/rdata.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>
#include <vector>
#include <list>
#include <sstream>

using namespace isc::dns;
using std::vector;
using std::string;
using std::list;
using std::stringstream;
using std::endl;
using boost::lexical_cast;

namespace {
class MasterLoaderTest : public ::testing::Test {
public:
    MasterLoaderTest() :
        callbacks_(boost::bind(&MasterLoaderTest::callback, this,
                               &errors_, _1, _2, _3),
                   boost::bind(&MasterLoaderTest::callback, this,
                               &warnings_, _1, _2, _3))
    {}

    void TearDown() {
        // Check there are no more RRs we didn't expect
        EXPECT_TRUE(rrsets_.empty());
    }

    /// Concatenate file, line, and reason, and add it to either errors
    /// or warnings
    void callback(vector<string>* target, const std::string& file, size_t line,
                  const std::string& reason)
    {
        std::stringstream ss;
        ss << reason << " [" << file << ":" << line << "]";
        target->push_back(ss.str());
    }

    void addRRset(const Name& name, const RRClass& rrclass,
                  const RRType& rrtype, const RRTTL& rrttl,
                  const rdata::RdataPtr& data) {
        const RRsetPtr rrset(new BasicRRset(name, rrclass, rrtype, rrttl));
        rrset->addRdata(data);
        rrsets_.push_back(rrset);
    }

    void setLoader(const char* file, const Name& origin,
                   const RRClass& rrclass, const MasterLoader::Options options)
    {
        loader_.reset(new MasterLoader(file, origin, rrclass, callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    void setLoader(std::istream& stream, const Name& origin,
                   const RRClass& rrclass, const MasterLoader::Options options)
    {
        loader_.reset(new MasterLoader(stream, origin, rrclass, callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    static string prepareZone(const string& line, bool include_last) {
        string result;
        result += "example.org. 3600 IN SOA ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200\n";
        result += line;
        if (include_last) {
            result += "\n";
            result += "correct 3600    IN  A 192.0.2.2\n";
        }
        return (result);
    }

    void clear() {
        warnings_.clear();
        errors_.clear();
        rrsets_.clear();
    }

    // Check the next RR in the ones produced by the loader
    // Other than passed arguments are checked to be the default for the tests
    void checkRR(const string& name, const RRType& type, const string& data,
                 const RRTTL& rrttl = RRTTL(3600)) {
        ASSERT_FALSE(rrsets_.empty());
        RRsetPtr current = rrsets_.front();
        rrsets_.pop_front();

        EXPECT_EQ(Name(name), current->getName());
        EXPECT_EQ(type, current->getType());
        EXPECT_EQ(RRClass::IN(), current->getClass());
        EXPECT_EQ(rrttl, current->getTTL());
        ASSERT_EQ(1, current->getRdataCount());
        EXPECT_EQ(0, isc::dns::rdata::createRdata(type, RRClass::IN(), data)->
                  compare(current->getRdataIterator()->getCurrent()))
            << data << " vs. "
            << current->getRdataIterator()->getCurrent().toText();
    }

    void checkBasicRRs() {
        checkRR("example.org", RRType::SOA(),
                "ns1.example.org. admin.example.org. "
                "1234 3600 1800 2419200 7200");
        checkRR("example.org", RRType::NS(), "ns1.example.org.");
        checkRR("www.example.org", RRType::A(), "192.0.2.1");
        checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
    }

    void checkARR(const string& name) {
        checkRR(name, RRType::A(), "192.0.2.1");
    }

    MasterLoaderCallbacks callbacks_;
    boost::scoped_ptr<MasterLoader> loader_;
    vector<string> errors_;
    vector<string> warnings_;
    list<RRsetPtr> rrsets_;
};

// Test simple loading. The zone file contains no tricky things, and nothing is
// omitted. No RRset contains more than one RR Also no errors or warnings.
TEST_F(MasterLoaderTest, basicLoad) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadedSucessfully());

    // The following three should be set to 0 initially in case the loader
    // is constructed from a file name.
    EXPECT_EQ(0, loader_->getSize());
    EXPECT_EQ(0, loader_->getPosition());

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    // Hardcode expected values taken from the test data file, assuming it
    // won't change too often.
    EXPECT_EQ(550, loader_->getSize());
    EXPECT_EQ(550, loader_->getPosition());

    checkBasicRRs();
}

// Test the $INCLUDE directive
TEST_F(MasterLoaderTest, include) {
    // Test various cases of include
    const char* includes[] = {
        "$include",
        "$INCLUDE",
        "$Include",
        "$InCluDe",
        "\"$INCLUDE\"",
        NULL
    };
    for (const char** include = includes; *include != NULL; ++include) {
        SCOPED_TRACE(*include);

        clear();
        // Prepare input source that has the include and some more data
        // below (to see it returns back to the original source).
        const string include_str = string(*include) + " " +
            TEST_DATA_SRCDIR + "/example.org\nwww 3600 IN AAAA 2001:db8::1\n";
        stringstream ss(include_str);
        setLoader(ss, Name("example.org."), RRClass::IN(),
                  MasterLoader::MANY_ERRORS);

        loader_->load();
        EXPECT_TRUE(loader_->loadedSucessfully());
        EXPECT_TRUE(errors_.empty());
        EXPECT_TRUE(warnings_.empty());

        checkBasicRRs();
        checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
    }
}

TEST_F(MasterLoaderTest, includeAndIncremental) {
    // Check getSize() and getPosition() are adjusted before and after
    // $INCLUDE.
    const string first_rr = "before.example.org. 0 A 192.0.2.1\n";
    const string include_str = "$INCLUDE " TEST_DATA_SRCDIR "/example.org";
    const string zone_data = first_rr + include_str + "\n" +
        "www 3600 IN AAAA 2001:db8::1\n";
    stringstream ss(zone_data);
    setLoader(ss, Name("example.org."), RRClass::IN(), MasterLoader::DEFAULT);

    // On construction, getSize() returns the size of the data (exclude the
    // the file to be included); position is set to 0.
    EXPECT_EQ(zone_data.size(), loader_->getSize());
    EXPECT_EQ(0, loader_->getPosition());

    // Read the first RR.  getSize() doesn't change; position should be
    // at the end of the first line.
    loader_->loadIncremental(1);
    EXPECT_EQ(zone_data.size(), loader_->getSize());
    EXPECT_EQ(first_rr.size(), loader_->getPosition());

    // Read next 4.  It includes $INCLUDE processing.  Magic number of 550
    // is the size of the test zone file (see above); 507 is the position in
    // the file at the end of 4th RR (due to extra comments it's smaller than
    // the file size).
    loader_->loadIncremental(4);
    EXPECT_EQ(zone_data.size() + 550, loader_->getSize());
    EXPECT_EQ(first_rr.size() + include_str.size() + 507,
              loader_->getPosition());

    // Read the last one.  At this point getSize and getPosition return
    // the same value, indicating progress of 100%.
    loader_->loadIncremental(1);
    EXPECT_EQ(zone_data.size() + 550, loader_->getSize());
    EXPECT_EQ(zone_data.size() + 550, loader_->getPosition());

    // we were not interested in checking RRs in this test.  clear them to
    // not confuse TearDown().
    rrsets_.clear();
}

// A commonly used helper to check callback message.
void
checkCallbackMessage(const string& actual_msg, const string& expected_msg,
                     size_t expected_line) {
    // The actual message should begin with the expected message.
    EXPECT_EQ(0, actual_msg.find(expected_msg)) << "actual message: " <<
                                                actual_msg << " expected: " <<
                                                expected_msg;

    // and it should end with "...:<line_num>]"
    const string line_desc = ":" + lexical_cast<string>(expected_line) + "]";
    EXPECT_EQ(actual_msg.size() - line_desc.size(),
              actual_msg.find(line_desc)) << "Expected on line " <<
        expected_line;
}

TEST_F(MasterLoaderTest, origin) {
    // Various forms of the directive
    const char* origins[] = {
        "$origin",
        "$ORIGIN",
        "$Origin",
        "$OrigiN",
        "\"$ORIGIN\"",
        NULL
    };
    for (const char** origin = origins; *origin != NULL; ++origin) {
        SCOPED_TRACE(*origin);

        clear();
        const string directive = *origin;
        const string input =
            "@  1H  IN  A   192.0.2.1\n" +
            directive + " sub.example.org.\n"
            "\"www\"    1H  IN  A   192.0.2.1\n" +
            // Relative name in the origin
            directive + " relative\n"
            "@  1H  IN  A   192.0.2.1\n"
            // Origin is _not_ used here (absolute name)
            "noorigin.example.org.  60M IN  A   192.0.2.1\n";
        stringstream ss(input);
        setLoader(ss, Name("example.org."), RRClass::IN(),
                  MasterLoader::MANY_ERRORS);

        loader_->load();
        EXPECT_TRUE(loader_->loadedSucessfully());
        EXPECT_TRUE(errors_.empty());
        // There's a relative origin in it, we warn about that.
        EXPECT_EQ(1, warnings_.size());
        checkCallbackMessage(warnings_.at(0),
                             "The new origin is relative, did you really mean "
                             "relative.sub.example.org.?", 4);

        checkARR("example.org");
        checkARR("www.sub.example.org");
        checkARR("relative.sub.example.org");
        checkARR("noorigin.example.org");
    }
}

TEST_F(MasterLoaderTest, generate) {
    // Various forms of the directive
    const char* generates[] = {
        "$generate",
        "$GENERATE",
        "$Generate",
        "$GeneratE",
        "\"$GENERATE\"",
        NULL
    };
    for (const char** generate = generates; *generate != NULL; ++generate) {
        SCOPED_TRACE(*generate);

        clear();
        const string directive = *generate;
        const string input =
          "$ORIGIN example.org.\n"
          "before.example.org. 3600 IN A 192.0.2.0\n" +
          directive + " 3-5 host$ A 192.0.2.$\n" +
          "after.example.org. 3600 IN A 192.0.2.255\n";
        stringstream ss(input);
        setLoader(ss, Name("example.org."), RRClass::IN(),
                  MasterLoader::MANY_ERRORS);

        loader_->load();
        EXPECT_TRUE(loader_->loadedSucessfully());
        EXPECT_TRUE(errors_.empty());

        // The "before" and "after" scaffolding below checks that no
        // extra records are added by $GENERATE outside the requested
        // range.
        checkRR("before.example.org", RRType::A(), "192.0.2.0");
        checkRR("host3.example.org", RRType::A(), "192.0.2.3");
        checkRR("host4.example.org", RRType::A(), "192.0.2.4");
        checkRR("host5.example.org", RRType::A(), "192.0.2.5");
        checkRR("after.example.org", RRType::A(), "192.0.2.255");
    }
}

TEST_F(MasterLoaderTest, generateRelativeLHS) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 1-2 @ 3600 NS ns$.example.org.\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("example.org", RRType::NS(), "ns1.example.org.");
    checkRR("example.org", RRType::NS(), "ns2.example.org.");
}

TEST_F(MasterLoaderTest, generateInFront) {
    // $ is in the front
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 9-10 $host 3600 TXT \"$ pomegranate\"\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("9host.example.org", RRType::TXT(), "9 pomegranate");
    checkRR("10host.example.org", RRType::TXT(), "10 pomegranate");
}

TEST_F(MasterLoaderTest, generateInMiddle) {
    // $ is in the middle
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 9-10 num$-host 3600 TXT \"This is $ pomegranate\"\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("num9-host.example.org", RRType::TXT(), "This is 9 pomegranate");
    checkRR("num10-host.example.org", RRType::TXT(), "This is 10 pomegranate");
}

TEST_F(MasterLoaderTest, generateAtEnd) {
    // $ is at the end
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 9-10 num$-host 3600 TXT Pomegranate$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("num9-host.example.org", RRType::TXT(), "Pomegranate9");
    checkRR("num10-host.example.org", RRType::TXT(), "Pomegranate10");
}

TEST_F(MasterLoaderTest, generateStripsQuotes) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 1-2 @ 3600 MX \"$ mx$.example.org.\"\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("example.org", RRType::MX(), "1 mx1.example.org.");
    checkRR("example.org", RRType::MX(), "2 mx2.example.org.");
}

TEST_F(MasterLoaderTest, generateWithDoublePlaceholder) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 9-10 host$ 3600 TXT \"This is $$ pomegranate\"\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("host9.example.org", RRType::TXT(), "This is $ pomegranate");
    checkRR("host10.example.org", RRType::TXT(), "This is $ pomegranate");
}

TEST_F(MasterLoaderTest, generateWithEscape) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 9-10 host$ 3600 TXT \"This is \\$\\pomegranate\"\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("host9.example.org", RRType::TXT(), "This is \\$\\pomegranate");
    checkRR("host10.example.org", RRType::TXT(), "This is \\$\\pomegranate");
}

TEST_F(MasterLoaderTest, generateWithParams) {
    const string input =
        "$ORIGIN example.org.\n"
        "$TTL 3600\n"
        "$GENERATE 2-3 host$ A 192.0.2.$\n"
        "$GENERATE 5-6 host$ 3600 A 192.0.2.$\n"
        "$GENERATE 8-9 host$ IN A 192.0.2.$\n"
        "$GENERATE 11-12 host$ IN 3600 A 192.0.2.$\n"
        "$GENERATE 14-15 host$ 3600 IN A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("host2.example.org", RRType::A(), "192.0.2.2");
    checkRR("host3.example.org", RRType::A(), "192.0.2.3");

    checkRR("host5.example.org", RRType::A(), "192.0.2.5");
    checkRR("host6.example.org", RRType::A(), "192.0.2.6");

    checkRR("host8.example.org", RRType::A(), "192.0.2.8");
    checkRR("host9.example.org", RRType::A(), "192.0.2.9");

    checkRR("host11.example.org", RRType::A(), "192.0.2.11");
    checkRR("host12.example.org", RRType::A(), "192.0.2.12");

    checkRR("host14.example.org", RRType::A(), "192.0.2.14");
    checkRR("host15.example.org", RRType::A(), "192.0.2.15");
}

TEST_F(MasterLoaderTest, generateWithStep) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 2-9/2 host$ 3600 A 192.0.2.$\n"
        "$GENERATE 12-21/3 host$ 3600 A 192.0.2.$\n"
        "$GENERATE 30-31/1 host$ 3600 A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("host2.example.org", RRType::A(), "192.0.2.2");
    checkRR("host4.example.org", RRType::A(), "192.0.2.4");
    checkRR("host6.example.org", RRType::A(), "192.0.2.6");
    checkRR("host8.example.org", RRType::A(), "192.0.2.8");

    checkRR("host12.example.org", RRType::A(), "192.0.2.12");
    checkRR("host15.example.org", RRType::A(), "192.0.2.15");
    checkRR("host18.example.org", RRType::A(), "192.0.2.18");
    checkRR("host21.example.org", RRType::A(), "192.0.2.21");

    checkRR("host30.example.org", RRType::A(), "192.0.2.30");
    checkRR("host31.example.org", RRType::A(), "192.0.2.31");
}

TEST_F(MasterLoaderTest, generateWithModifiers) {
    const string input =
        "$ORIGIN example.org.\n"
        "$TTL 3600\n"

        // Use a positive delta of 1 in the LHS and a negative delta of
        // -1 in the RHS
        "$GENERATE 2-9/2 host${1} A 192.0.2.${-1}\n"

        "$GENERATE 10-12 host${0,4} A 192.0.2.$\n"
        "$GENERATE 14-15 host${0,4,d} A 192.0.2.$\n"

        // Names are case-insensitive, so we use TXT's RDATA to check
        // case with hex representation.
        "$GENERATE 30-31 host$ TXT \"Value ${0,4,x}\"\n"
        "$GENERATE 42-43 host$ TXT \"Value ${0,4,X}\"\n"

        // Octal does not use any alphabets
        "$GENERATE 45-46 host${0,4,o} A 192.0.2.$\n"

        // Here, the LHS has a trailing dot (which would result in an
        // out-of-zone name), but that should be handled as a relative
        // name.
        "$GENERATE 90-92 ${0,8,n} A 192.0.2.$\n"

        // Here, the LHS has no trailing dot, and results in the same
        // number of labels as width=8 above.
        "$GENERATE 94-96 ${0,7,n} A 192.0.2.$\n"

        // Names are case-insensitive, so we use TXT's RDATA to check
        // case with nibble representation.
        "$GENERATE 106-107 host$ TXT \"Value ${0,9,n}\"\n"
        "$GENERATE 109-110 host$ TXT \"Value ${0,9,N}\"\n"

        // Junk type will not parse and 'd' is assumed. No error is
        // generated (this is to match BIND 9 behavior).
        "$GENERATE 200-201 host${0,4,j} A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());

    checkRR("host3.example.org", RRType::A(), "192.0.2.1");
    checkRR("host5.example.org", RRType::A(), "192.0.2.3");
    checkRR("host7.example.org", RRType::A(), "192.0.2.5");
    checkRR("host9.example.org", RRType::A(), "192.0.2.7");

    checkRR("host0010.example.org", RRType::A(), "192.0.2.10");
    checkRR("host0011.example.org", RRType::A(), "192.0.2.11");
    checkRR("host0012.example.org", RRType::A(), "192.0.2.12");

    checkRR("host0014.example.org", RRType::A(), "192.0.2.14");
    checkRR("host0015.example.org", RRType::A(), "192.0.2.15");

    checkRR("host30.example.org", RRType::TXT(), "Value 001e");
    checkRR("host31.example.org", RRType::TXT(), "Value 001f");

    checkRR("host42.example.org", RRType::TXT(), "Value 002A");
    checkRR("host43.example.org", RRType::TXT(), "Value 002B");

    checkRR("host0055.example.org", RRType::A(), "192.0.2.45");
    checkRR("host0056.example.org", RRType::A(), "192.0.2.46");

    checkRR("a.5.0.0.example.org", RRType::A(), "192.0.2.90");
    checkRR("b.5.0.0.example.org", RRType::A(), "192.0.2.91");
    checkRR("c.5.0.0.example.org", RRType::A(), "192.0.2.92");

    checkRR("e.5.0.0.example.org", RRType::A(), "192.0.2.94");
    checkRR("f.5.0.0.example.org", RRType::A(), "192.0.2.95");
    checkRR("0.6.0.0.example.org", RRType::A(), "192.0.2.96");

    checkRR("host106.example.org", RRType::TXT(), "Value a.6.0.0.0");
    checkRR("host107.example.org", RRType::TXT(), "Value b.6.0.0.0");
    checkRR("host109.example.org", RRType::TXT(), "Value D.6.0.0.0");
    checkRR("host110.example.org", RRType::TXT(), "Value E.6.0.0.0");

    checkRR("host0200.example.org", RRType::A(), "192.0.2.200");
    checkRR("host0201.example.org", RRType::A(), "192.0.2.201");
}

TEST_F(MasterLoaderTest, generateWithNoModifiers) {
    const string input =
        "$ORIGIN example.org.\n"
        "$TTL 3600\n"
        "$GENERATE 10-12 host${} A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(2, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "Invalid $GENERATE format modifiers", 3);
    checkCallbackMessage(errors_.at(1),
                         "$GENERATE error", 3);
}

TEST_F(MasterLoaderTest, generateWithBadModifiers) {
    const string input =
        "$ORIGIN example.org.\n"
        "$TTL 3600\n"
        "$GENERATE 10-12 host${GARBAGE} A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(2, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "Invalid $GENERATE format modifiers", 3);
    checkCallbackMessage(errors_.at(1),
                         "$GENERATE error", 3);
}

TEST_F(MasterLoaderTest, generateMissingRange) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "unexpected end of input", 2);
}

TEST_F(MasterLoaderTest, generateMissingLHS) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 2-4\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "unexpected end of input", 2);
}

TEST_F(MasterLoaderTest, generateMissingType) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 2-4 host$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "unexpected end of input", 2);
}

TEST_F(MasterLoaderTest, generateMissingRHS) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 2-4 host$ A\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "unexpected end of input", 2);
}

TEST_F(MasterLoaderTest, generateWithBadRangeSyntax) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE ABCD host$ 3600 A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "$GENERATE: invalid range: ABCD", 2);
}

TEST_F(MasterLoaderTest, generateWithInvalidRange) {
    // start > stop
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 2-1 host$ 3600 A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "$GENERATE: invalid range: 2-1", 2);
}

TEST_F(MasterLoaderTest, generateWithInvalidClass) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 1-2 host$ 3600 CH A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "Class mismatch: CH vs. IN", 2);
}

TEST_F(MasterLoaderTest, generateWithNoAvailableTTL) {
    const string input =
        "$ORIGIN example.org.\n"
        "$GENERATE 1-2 host$ A 192.0.2.$\n";
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken GENERATE
    EXPECT_TRUE(warnings_.empty());

    checkCallbackMessage(errors_.at(0),
                         "no TTL specified; load rejected", 2);
}

// Test the source is correctly popped even after error
TEST_F(MasterLoaderTest, popAfterError) {
    const string include_str = "$include " TEST_DATA_SRCDIR
        "/broken.zone\nwww 3600 IN AAAA 2001:db8::1\n";
    stringstream ss(include_str);
    // We perform the test with MANY_ERRORS, we want to see what happens
    // after the error.
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken RR
    EXPECT_EQ(1, warnings_.size()); // For missing EOLN

    // The included file doesn't contain anything usable, but the
    // line after the include should be there.
    checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
}

// Check it works the same when created based on a stream, not filename
TEST_F(MasterLoaderTest, streamConstructor) {
    const string zone_data(prepareZone("", true));
    stringstream zone_stream(zone_data);
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadedSucessfully());

    // Unlike the basicLoad test, if we construct the loader from a stream
    // getSize() returns the data size in the stream immediately after the
    // construction.
    EXPECT_EQ(zone_data.size(), loader_->getSize());
    EXPECT_EQ(0, loader_->getPosition());

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    checkRR("example.org", RRType::SOA(), "ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200");
    checkRR("correct.example.org", RRType::A(), "192.0.2.2");

    // On completion of the load, both getSize() and getPosition() return the
    // size of the data.
    EXPECT_EQ(zone_data.size(), loader_->getSize());
    EXPECT_EQ(zone_data.size(), loader_->getPosition());
}

// Try loading data incrementally.
TEST_F(MasterLoaderTest, incrementalLoad) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_FALSE(loader_->loadIncremental(2));
    EXPECT_FALSE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("example.org", RRType::SOA(),
            "ns1.example.org. admin.example.org. "
            "1234 3600 1800 2419200 7200");
    checkRR("example.org", RRType::NS(), "ns1.example.org.");

    // The third one is not loaded yet
    EXPECT_TRUE(rrsets_.empty());

    // Load the rest.
    EXPECT_TRUE(loader_->loadIncremental(20));
    EXPECT_TRUE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("www.example.org", RRType::A(), "192.0.2.1");
    checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
}

// Try loading from file that doesn't exist. There should be single error
// saying so.
TEST_F(MasterLoaderTest, invalidFile) {
    setLoader("This file doesn't exist at all",
              Name("exmaple.org."), RRClass::IN(), MasterLoader::MANY_ERRORS);

    // Nothing yet. The loader is dormant until invoked.
    // Is it really what we want?
    EXPECT_TRUE(errors_.empty());

    loader_->load();

    EXPECT_TRUE(warnings_.empty());
    EXPECT_TRUE(rrsets_.empty());
    ASSERT_EQ(1, errors_.size());
    EXPECT_EQ(0, errors_[0].find("Error opening the input source file: ")) <<
        "Different error: " << errors_[0];
}

struct ErrorCase {
    const char* const line;    // The broken line in master file
    const char* const reason;  // If non NULL, the reason string
    const char* const problem; // Description of the problem for SCOPED_TRACE
} const error_cases[] = {
    { "www...   3600    IN  A   192.0.2.1", NULL, "Invalid name" },
    { "www      FORTNIGHT   IN  A   192.0.2.1", NULL, "Invalid TTL" },
    { "www      3600    XX  A   192.0.2.1", NULL, "Invalid class" },
    { "www      3600    IN  A   bad_ip", NULL, "Invalid Rdata" },

    // Parameter ordering errors
    { "www      IN      A   3600 192.168.2.7",
      "createRdata from text failed: Bad IN/A RDATA text: '3600'",
      "Incorrect order of class, TTL and type" },
    { "www      A       IN  3600 192.168.2.8",
      "createRdata from text failed: Bad IN/A RDATA text: 'IN'",
      "Incorrect order of class, TTL and type" },
    { "www      3600    A   IN   192.168.2.7",
      "createRdata from text failed: Bad IN/A RDATA text: 'IN'",
      "Incorrect order of class, TTL and type" },
    { "www      A       3600 IN  192.168.2.8",
      "createRdata from text failed: Bad IN/A RDATA text: '3600'",
      "Incorrect order of class, TTL and type" },

    // Missing type and Rdata
    { "www", "unexpected end of input", "Missing type and Rdata" },
    { "www 3600", "unexpected end of input", "Missing type and Rdata" },
    { "www IN", "unexpected end of input", "Missing type and Rdata" },
    { "www 3600 IN", "unexpected end of input", "Missing type and Rdata" },
    { "www IN 3600", "unexpected end of input", "Missing type and Rdata" },

    // Missing Rdata
    { "www A",
      "createRdata from text failed: unexpected end of input",
      "Missing Rdata" },
    { "www 3600 A",
      "createRdata from text failed: unexpected end of input",
      "Missing Rdata" },
    { "www IN A",
      "createRdata from text failed: unexpected end of input",
      "Missing Rdata" },
    { "www 3600 IN A",
      "createRdata from text failed: unexpected end of input",
      "Missing Rdata" },
    { "www IN 3600 A",
      "createRdata from text failed: unexpected end of input",
      "Missing Rdata" },

    { "www      3600    IN", NULL, "Unexpected EOLN" },
    { "www      3600    CH  TXT nothing", "Class mismatch: CH vs. IN",
      "Class mismatch" },
    { "www      \"3600\"  IN  A   192.0.2.1", NULL, "Quoted TTL" },
    { "www      3600    \"IN\"  A   192.0.2.1", NULL, "Quoted class" },
    { "www      3600    IN  \"A\"   192.0.2.1", NULL, "Quoted type" },
    { "unbalanced)paren 3600    IN  A   192.0.2.1", NULL, "Token error 1" },
    { "www  3600    unbalanced)paren    A   192.0.2.1", NULL,
      "Token error 2" },
    // Check the unknown directive. The rest looks like ordinary RR,
    // so we see the $ is actually special.
    { "$UNKNOWN 3600    IN  A   192.0.2.1", NULL, "Unknown $ directive" },
    { "$INCLUD " TEST_DATA_SRCDIR "/example.org", "Unknown directive 'INCLUD'",
        "Include too short" },
    { "$INCLUDES " TEST_DATA_SRCDIR "/example.org",
        "Unknown directive 'INCLUDES'", "Include too long" },
    { "$INCLUDE", "unexpected end of input", "Missing include path" },
    // The following two error messages are system dependant, omitting
    { "$INCLUDE /file/not/found", NULL, "Include file not found" },
    { "$INCLUDE /file/not/found example.org. and here goes bunch of garbage",
        NULL, "Include file not found and garbage at the end of line" },
    { "$ORIGIN", "unexpected end of input", "Missing origin name" },
    { "$ORIGIN invalid...name", "duplicate period in invalid...name",
        "Invalid name for origin" },
    { "$ORIGIN )brokentoken", "unbalanced parentheses",
        "Broken token in origin" },
    { "$ORIGIN example.org. garbage", "Extra tokens at the end of line",
        "Garbage after origin" },
    { "$ORIGI name.", "Unknown directive 'ORIGI'", "$ORIGIN too short" },
    { "$ORIGINAL name.", "Unknown directive 'ORIGINAL'", "$ORIGIN too long" },
    { "$TTL 100 extra-garbage", "Extra tokens at the end of line",
      "$TTL with extra token" },
    { "$TTL", "unexpected end of input", "missing TTL" },
    { "$TTL No-ttl", "Unknown unit used: N in: No-ttl", "bad TTL" },
    { "$TTL \"100\"", "unexpected quotes", "bad TTL, quoted" },
    { "$TT 100", "Unknown directive 'TT'", "bad directive, too short" },
    { "$TTLLIKE 100", "Unknown directive 'TTLLIKE'", "bad directive, extra" },
    { NULL, NULL, NULL }
};

// Test a broken zone is handled properly. We test several problems,
// both in strict and lenient mode.
TEST_F(MasterLoaderTest, brokenZone) {
    for (const ErrorCase* ec = error_cases; ec->line != NULL; ++ec) {
        SCOPED_TRACE(ec->problem);
        const string zone(prepareZone(ec->line, true));

        {
            SCOPED_TRACE("Strict mode");
            clear();
            stringstream zone_stream(zone);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::DEFAULT);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_THROW(loader_->load(), MasterLoaderError);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_EQ(1, errors_.size());
            if (ec->reason != NULL) {
                checkCallbackMessage(errors_.at(0), ec->reason, 2);
            }
            EXPECT_TRUE(warnings_.empty());

            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            // In the strict mode, it is aborted. The last RR is not
            // even attempted.
            EXPECT_TRUE(rrsets_.empty());
        }

        {
            SCOPED_TRACE("Lenient mode");
            clear();
            stringstream zone_stream(zone);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::MANY_ERRORS);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_NO_THROW(loader_->load());
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_EQ(1, errors_.size());
            EXPECT_TRUE(warnings_.empty());
            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            // This one is below the error one.
            checkRR("correct.example.org", RRType::A(), "192.0.2.2");
            EXPECT_TRUE(rrsets_.empty());
        }

        {
            SCOPED_TRACE("Error at EOF");
            // This case is interesting only in the lenient mode.
            clear();
            const string zoneEOF(prepareZone(ec->line, false));
            stringstream zone_stream(zoneEOF);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::MANY_ERRORS);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_NO_THROW(loader_->load());
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_EQ(1, errors_.size()) << errors_[0] << "\n" << errors_[1];
            // The unexpected EOF warning
            EXPECT_EQ(1, warnings_.size());
            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            EXPECT_TRUE(rrsets_.empty());
        }
    }
}

// Check that a garbage after the include generates an error, but not fatal
// one (in lenient mode) and we can recover.
TEST_F(MasterLoaderTest, includeWithGarbage) {
    // Include an origin (example.org) because we expect it to be handled
    // soon and we don't want it to break here.
    const string include_str("$INCLUDE " TEST_DATA_SRCDIR
                             "/example.org example.org. bunch of other stuff\n"
                             "www 3600 IN AAAA 2001:db8::1\n");
    stringstream zone_stream(include_str);
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    EXPECT_NO_THROW(loader_->load());
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "Extra tokens at the end of line", 1);
    // It says something about extra tokens at the end
    EXPECT_NE(string::npos, errors_[0].find("Extra"));
    EXPECT_TRUE(warnings_.empty());
    checkBasicRRs();
    checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
}

// Check we error about garbage at the end of $ORIGIN line (but the line
// works).
TEST_F(MasterLoaderTest, originWithGarbage) {
    const string origin_str = "$ORIGIN www.example.org. More garbage here\n"
        "@  1H  IN  A   192.0.2.1\n";
    stringstream ss(origin_str);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    EXPECT_NO_THROW(loader_->load());
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "Extra tokens at the end of line", 1);
    EXPECT_TRUE(warnings_.empty());
    checkARR("www.example.org");
}

// Test we can pass both file to include and the origin to switch
TEST_F(MasterLoaderTest, includeAndOrigin) {
    // First, switch origin to something else, so we can check it is
    // switched back.
    const string include_string = "$ORIGIN www.example.org.\n"
        "@  1H  IN  A   192.0.2.1\n"
        // Then include the file with data and switch origin back
        "$INCLUDE " TEST_DATA_SRCDIR "/example.org example.org.\n"
        // Another RR to see we fall back to the previous origin.
        "www    1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    // And check it's the correct data
    checkARR("www.example.org");
    checkBasicRRs();
    checkARR("www.www.example.org");
}

// Like above, but the origin after include is bogus. The whole line should
// be rejected.
TEST_F(MasterLoaderTest, includeAndBadOrigin) {
    const string include_string =
        "$INCLUDE " TEST_DATA_SRCDIR "/example.org example..org.\n"
        // Another RR to see the switch survives after we exit include
        "www    1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "duplicate period in example..org.",
                         1);
    EXPECT_TRUE(warnings_.empty());
    // And check it's the correct data
    checkARR("www.example.org");
}

// Check the origin doesn't get outside of the included file.
TEST_F(MasterLoaderTest, includeOriginRestore) {
    const string include_string =
        "$INCLUDE " TEST_DATA_SRCDIR "/origincheck.txt\n"
        "@  1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    // And check it's the correct data
    checkARR("www.example.org");
    checkARR("example.org");
}

// Check we restore the last name for initial whitespace when returning from
// include. But we do produce a warning if there's one just ofter the include.
TEST_F(MasterLoaderTest, includeAndInitialWS) {
    const string include_string = "xyz  1H  IN  A   192.0.2.1\n"
        "$INCLUDE " TEST_DATA_SRCDIR "/example.org\n"
        "   1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0),
                         "Owner name omitted around $INCLUDE, the result might "
                         "not be as expected", 3);
    checkARR("xyz.example.org");
    checkBasicRRs();
    checkARR("xyz.example.org");
}

// Test for "$TTL"
TEST_F(MasterLoaderTest, ttlDirective) {
    stringstream zone_stream;

    // Set the default TTL with $TTL followed by an RR omitting the TTL
    zone_stream << "$TTL 1800\nexample.org. IN A 192.0.2.1\n";
    // $TTL can be quoted.  Also testing the case of $TTL being changed.
    zone_stream << "\"$TTL\" 100\na.example.org. IN A 192.0.2.2\n";
    // Extended TTL form is accepted.
    zone_stream << "$TTL 1H\nb.example.org. IN A 192.0.2.3\n";
    // Matching is case insensitive.
    zone_stream << "$tTl 360\nc.example.org. IN A 192.0.2.4\n";
    // Maximum allowable TTL
    zone_stream << "$TTL 2147483647\nd.example.org. IN A 192.0.2.5\n";

    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("example.org", RRType::A(), "192.0.2.1", RRTTL(1800));
    checkRR("a.example.org", RRType::A(), "192.0.2.2", RRTTL(100));
    checkRR("b.example.org", RRType::A(), "192.0.2.3", RRTTL(3600));
    checkRR("c.example.org", RRType::A(), "192.0.2.4", RRTTL(360));
    checkRR("d.example.org", RRType::A(), "192.0.2.5", RRTTL(2147483647));
}

TEST_F(MasterLoaderTest, ttlFromSOA) {
    // No $TTL, and the SOA doesn't have an explicit TTL field.  Its minimum
    // TTL field will be used as the RR's TTL, and it'll be used as the
    // default TTL for others.
    stringstream zone_stream("example.org. IN SOA . . 0 0 0 0 1800\n"
                             "a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("example.org", RRType::SOA(), ". . 0 0 0 0 1800", RRTTL(1800));
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(1800));

    // The use of SOA minimum TTL should have caused a warning.
    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0),
                         "no TTL specified; using SOA MINTTL instead", 1);
}

TEST_F(MasterLoaderTest, ttlFromPrevious) {
    // No available default TTL.  2nd and 3rd RR will use the TTL of the
    // 1st RR.  This will result in a warning, but only for the first time.
    stringstream zone_stream("a.example.org. 1800 IN A 192.0.2.1\n"
                             "b.example.org. IN A 192.0.2.2\n"
                             "c.example.org. IN A 192.0.2.3\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(1800));
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(1800));
    checkRR("c.example.org", RRType::A(), "192.0.2.3", RRTTL(1800));

    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "using RFC1035 TTL semantics", 2);
}

TEST_F(MasterLoaderTest, RRParamsOrdering) {
    // We test the order and existence of TTL, class and type. See
    // MasterLoader::MasterLoaderImpl::parseRRParams() for ordering.

    stringstream zone_stream;
    // <TTL> <class> <type> <RDATA>
    zone_stream << "a.example.org. 1800 IN A 192.0.2.1\n";
    // <type> <RDATA>
    zone_stream << "b.example.org. A 192.0.2.2\n";
    // <class> <TTL> <type> <RDATA>
    zone_stream << "c.example.org. IN 3600 A 192.0.2.3\n";
    // <TTL> <type> <RDATA>
    zone_stream << "d.example.org. 7200 A 192.0.2.4\n";
    // <class> <type> <RDATA>
    zone_stream << "e.example.org. IN A 192.0.2.5\n";

    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(1800));
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(1800));
    checkRR("c.example.org", RRType::A(), "192.0.2.3", RRTTL(3600));
    checkRR("d.example.org", RRType::A(), "192.0.2.4", RRTTL(7200));
    checkRR("e.example.org", RRType::A(), "192.0.2.5", RRTTL(7200));

    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "using RFC1035 TTL semantics", 2);
}

TEST_F(MasterLoaderTest, ttlFromPreviousSOA) {
    // Mixture of the previous two cases: SOA has explicit TTL, followed by
    // an RR without an explicit TTL.  In this case the minimum TTL won't be
    // recognized as the "default TTL".
    stringstream zone_stream("example.org. 100 IN SOA . . 0 0 0 0 1800\n"
                             "a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    checkRR("example.org", RRType::SOA(), ". . 0 0 0 0 1800", RRTTL(100));
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(100));

    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "using RFC1035 TTL semantics", 2);
}

TEST_F(MasterLoaderTest, ttlUnknown) {
    // No available TTL is known for the first RR.
    stringstream zone_stream("a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    EXPECT_THROW(loader_->load(), MasterLoaderError);
}

TEST_F(MasterLoaderTest, ttlUnknownAndContinue) {
    stringstream zone_stream("a.example.org. IN A 192.0.2.1\n"
                             "b.example.org. 1800 IN A 192.0.2.2\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(1800));

    EXPECT_TRUE(warnings_.empty());
    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "no TTL specified; load rejected", 1);
}

TEST_F(MasterLoaderTest, ttlUnknownAndEOF) {
    // Similar to the previous case, but the input will be abruptly terminated
    // after the offending RR.  This will cause an additional warning.
    stringstream zone_stream("a.example.org. IN A 192.0.2.1");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_TRUE(rrsets_.empty());

    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "no TTL specified; load rejected", 1);

    // RDATA implementation can complain about it, too.  To be independent of
    // its details, we focus on the very last warning.
    EXPECT_FALSE(warnings_.empty());
    checkCallbackMessage(*warnings_.rbegin(), "File does not end with newline",
                         1);
}

TEST_F(MasterLoaderTest, ttlOverflow) {
    stringstream zone_stream;
    zone_stream << "example.org. IN SOA . . 0 0 0 0 2147483648\n";
    zone_stream << "$TTL 3600\n"; // reset to an in-range value
    zone_stream << "$TTL 2147483649\n" << "a.example.org. IN A 192.0.2.1\n";
    zone_stream << "$TTL 3600\n"; // reset to an in-range value
    zone_stream << "b.example.org. 2147483650 IN A 192.0.2.2\n";
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_EQ(3, rrsets_.size());

    checkRR("example.org", RRType::SOA(), ". . 0 0 0 0 2147483648", RRTTL(0));
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(0));
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(0));

    EXPECT_EQ(4, warnings_.size());
    checkCallbackMessage(warnings_.at(1),
                         "TTL 2147483648 > MAXTTL, setting to 0 per RFC2181",
                         1);
    checkCallbackMessage(warnings_.at(2),
                         "TTL 2147483649 > MAXTTL, setting to 0 per RFC2181",
                         3);
    checkCallbackMessage(warnings_.at(3),
                         "TTL 2147483650 > MAXTTL, setting to 0 per RFC2181",
                         6);
}

// Test the constructor rejects empty add callback.
TEST_F(MasterLoaderTest, emptyCallback) {
    EXPECT_THROW(MasterLoader(TEST_DATA_SRCDIR "/example.org",
                              Name("example.org"), RRClass::IN(), callbacks_,
                              AddRRCallback()), isc::InvalidParameter);
    // And the same with the second constructor
    stringstream ss("");
    EXPECT_THROW(MasterLoader(ss, Name("example.org"), RRClass::IN(),
                              callbacks_, AddRRCallback()),
                 isc::InvalidParameter);
}

// Check it throws when we try to load after loading was complete.
TEST_F(MasterLoaderTest, loadTwice) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_THROW(loader_->load(), isc::InvalidOperation);
    // Don't check them, they are not interesting, so suppress the error
    // at TearDown
    rrsets_.clear();
}

// Load 0 items should be rejected
TEST_F(MasterLoaderTest, loadZero) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);
    EXPECT_THROW(loader_->loadIncremental(0), isc::InvalidParameter);
}

// Test there's a warning when the file terminates without end of
// line.
TEST_F(MasterLoaderTest, noEOLN) {
    // No \n at the end
    const string input("example.org. 3600 IN SOA ns1.example.org. "
                       "admin.example.org. 1234 3600 1800 2419200 7200");
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    // There should be one warning about the EOLN
    EXPECT_EQ(1, warnings_.size());
    checkRR("example.org", RRType::SOA(), "ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200");
}

// Test it rejects when we don't have the previous name to use in place of
// initial whitespace
TEST_F(MasterLoaderTest, noPreviousName) {
    const string input("    1H  IN  A   192.0.2.1\n");
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "No previous name to use in place of "
                         "initial whitespace", 1);
    EXPECT_TRUE(warnings_.empty());
}

// Check we warn if the first RR in an included file has omitted name
TEST_F(MasterLoaderTest, previousInInclude) {
    const string input("www 1H  IN  A   192.0.2.1\n"
                       "$INCLUDE " TEST_DATA_SRCDIR "/omitcheck.txt\n");
    stringstream ss(input);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    // There should be one warning about the EOLN
    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "Owner name omitted around "
                         "$INCLUDE, the result might not be as expected", 1);
    checkARR("www.example.org");
    checkARR("www.example.org");
}

TEST_F(MasterLoaderTest, numericOwnerName) {
    const string input("$ORIGIN example.org.\n"
                       "1 3600 IN A 192.0.2.1\n");
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("1.example.org", RRType::A(), "192.0.2.1");
}

}
