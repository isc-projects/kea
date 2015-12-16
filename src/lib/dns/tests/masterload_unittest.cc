// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <functional>
#include <ios>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

using namespace std;
using namespace isc::dns;

namespace {
// A callback functor for masterLoad() commonly used for the following tests.
class TestCallback : public unary_function<ConstRRsetPtr, void> {
public:
    TestCallback(vector<ConstRRsetPtr>& rrsets) : rrsets_(rrsets) {}
    void operator()(ConstRRsetPtr rrset) {
        rrsets_.push_back(rrset);
    }
private:
    vector<ConstRRsetPtr>& rrsets_;
};

// A function version of TestCallback.
void
testCallback(ConstRRsetPtr rrset, vector<ConstRRsetPtr>* rrsets) {
    rrsets->push_back(rrset);
}

class MasterLoadTest : public ::testing::Test {
protected:
    MasterLoadTest() : origin("example.com"), zclass(RRClass::IN()),
                   callback(results) {}
public:
    void rrsetCallback(ConstRRsetPtr rrset) {
        results.push_back(rrset);
    }
protected:
    Name origin;
    RRClass zclass;
    stringstream rr_stream;
    vector<ConstRRsetPtr> results;
    TestCallback callback;
};

// Commonly used test RRs
const char* const txt_rr = "example.com. 3600 IN TXT \"test data\"\n";
const char* const a_rr1 = "www.example.com. 60 IN A 192.0.2.1\n";
const char* const a_rr2 = "www.example.com. 60 IN A 192.0.2.2\n";
const char* const a_rr3 = "ftp.example.com. 60 IN A 192.0.2.3\n";
// multi-field RR case
const char* const soa_rr = "example.com. 7200 IN SOA . . 0 0 0 0 0\n";
// A couple of RRSIGs, different type covered
const char* const rrsig_rr1 =
    "www.example.com. 60 IN RRSIG A 5 3 3600 20000101000000 20000201000000 "
    "12345 example.com. FAKEFAKEFAKE\n";
const char* const rrsig_rr2 =
    "www.example.com. 60 IN RRSIG AAAA 5 3 3600 20000101000000 20000201000000 "
    "12345 example.com. FAKEFAKEFAKE\n";

// Commonly used for some tests to check the constructed RR content.
const char* const dnskey_rdata =
    "256 3 7 AwEAAaetidLzsKWUt4swWR8yu0wPHPiUi8LUsAD0QPWU+wzt89epO6tH "
    "zkMBVDkC7qphQO2hTY4hHn9npWFRw5BYubE=\n";

TEST_F(MasterLoadTest, loadRRs) {
    // a simple case: loading 3 RRs, each consists of a single RRset.
    rr_stream << txt_rr << a_rr1 << soa_rr;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(3, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(a_rr1, results[1]->toText());
    EXPECT_EQ(soa_rr, results[2]->toText());
}

TEST_F(MasterLoadTest, loadWithFunctionCallback) {
    // The same test as loadRRs but using a normal function (not a functor
    // object)
    rr_stream << txt_rr << a_rr1 << soa_rr;
    masterLoad(rr_stream, origin, zclass,
               bind2nd(ptr_fun(testCallback), &results));
    ASSERT_EQ(3, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(a_rr1, results[1]->toText());
    EXPECT_EQ(soa_rr, results[2]->toText());
}

TEST_F(MasterLoadTest, loadWithMemFunctionCallback) {
    // The same test as loadRRs but using a class member function (with a
    // help of Boost.bind)
    rr_stream << txt_rr << a_rr1 << soa_rr;
    masterLoad(rr_stream, origin, zclass,
               boost::bind(&MasterLoadTest::rrsetCallback, this, _1));
    ASSERT_EQ(3, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(a_rr1, results[1]->toText());
    EXPECT_EQ(soa_rr, results[2]->toText());
}

TEST_F(MasterLoadTest, loadComments) {
    rr_stream << ";; comment line, should be skipped\n"
              << "\n"           // blank line (should be skipped)
              << txt_rr;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
}

TEST_F(MasterLoadTest, loadRRset) {
    // load an RRset containing two RRs
    rr_stream << a_rr1 << a_rr2;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(string(a_rr1) + string(a_rr2), results[0]->toText());
}

TEST_F(MasterLoadTest, loadRRsetsOfSameType) {
    // load two RRsets with the same RR type and different owner names.
    // the loader must distinguish them as separate RRsets.
    rr_stream << a_rr1 << a_rr3;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(2, results.size());
    EXPECT_EQ(a_rr1, results[0]->toText());
    EXPECT_EQ(a_rr3, results[1]->toText());
}

TEST_F(MasterLoadTest, loadRRsetsInterleaved) {
    // two RRs that belongs to the same RRset (rr1 and rr2) are interleaved
    // by another.  This is an unexpected case for this loader, but it's
    // not considered an error.  The loader will simply treat them separate
    // RRsets.
    rr_stream << a_rr1 << a_rr3 << a_rr2;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(3, results.size());
    EXPECT_EQ(a_rr1, results[0]->toText());
    EXPECT_EQ(a_rr3, results[1]->toText());
    EXPECT_EQ(a_rr2, results[2]->toText());
}

TEST_F(MasterLoadTest, loadRRsigs) {
    // RRSIGs of different types covered should be separated
    rr_stream << rrsig_rr1 << rrsig_rr2;
    masterLoad(rr_stream, origin, zclass, callback);
    EXPECT_EQ(2, results.size());
}

// This test was disabled by #2387, because the test data has trailing
// comments and it (eventually) uses the string RDATA constructor which
// doesn't support them. This test should be fixed and re-enabled by
// #2381, or deleted.
TEST_F(MasterLoadTest, DISABLED_loadRRWithComment) {
    // Comment at the end of line should be ignored and the RR should be
    // accepted.
    rr_stream << "example.com. 3600 IN DNSKEY\t256 3 7 "
        "AwEAAaetidLzsKWUt4swWR8yu0wPHPiUi8LUsAD0QPWU+wzt89epO6tH "
        "zkMBVDkC7qphQO2hTY4hHn9npWFRw5BYubE=  ; key id = 40430\n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::DNSKEY(), zclass,
                                      dnskey_rdata)));
}

// This test was disabled by #2387, because the test data has trailing
// comments and it (eventually) uses the string RDATA constructor which
// doesn't support them. This test should be fixed and re-enabled by
// #2381, or deleted.
TEST_F(MasterLoadTest, DISABLED_loadRRWithCommentNoSpace) {
    // Similar to the previous one, but there's no space before comments.
    // It should still work.
    rr_stream << "example.com. 3600 IN DNSKEY\t256 3 7 "
        "AwEAAaetidLzsKWUt4swWR8yu0wPHPiUi8LUsAD0QPWU+wzt89epO6tH "
        "zkMBVDkC7qphQO2hTY4hHn9npWFRw5BYubE=; key id = 40430\n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::DNSKEY(), zclass,
                                      dnskey_rdata)));
}

// This test was disabled by #2387, because the test data has trailing
// comments and it (eventually) uses the string RDATA constructor which
// doesn't support them. This test should be fixed and re-enabled by
// #2381, or deleted.
TEST_F(MasterLoadTest, DISABLED_loadRRWithCommentEmptyComment) {
    // Similar to the previous one, but there's no data after the ;
    // It should still work.
    rr_stream << "example.com. 3600 IN DNSKEY\t256 3 7 "
        "AwEAAaetidLzsKWUt4swWR8yu0wPHPiUi8LUsAD0QPWU+wzt89epO6tH "
        "zkMBVDkC7qphQO2hTY4hHn9npWFRw5BYubE= ;\n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::DNSKEY(), zclass,
                                      dnskey_rdata)));
}

// This test was disabled by #2387, because the test data has trailing
// comments and it (eventually) uses the string RDATA constructor which
// doesn't support them. This test should be fixed and re-enabled by
// #2381, or deleted.
TEST_F(MasterLoadTest, DISABLED_loadRRWithCommentEmptyCommentNoSpace) {
    // Similar to the previous one, but there's no space before or after ;
    // It should still work.
    rr_stream << "example.com. 3600 IN DNSKEY\t256 3 7 "
        "AwEAAaetidLzsKWUt4swWR8yu0wPHPiUi8LUsAD0QPWU+wzt89epO6tH "
        "zkMBVDkC7qphQO2hTY4hHn9npWFRw5BYubE=;\n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::DNSKEY(), zclass,
                                      dnskey_rdata)));
}

TEST_F(MasterLoadTest, loadRRWithEOLWhitespace) {
    // Test with whitespace after rdata
    // It should still work.
    rr_stream << "example.com. 3600 IN NSEC3PARAM 1 0 1 beef \n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::NSEC3PARAM(), zclass,
                                      "1 0 1 beef")));
}

TEST_F(MasterLoadTest, loadRRWithEOLWhitespaceTab) {
    // Similar to the previous one, tab instead of space.
    // It should still work.
    rr_stream << "example.com. 3600 IN NSEC3PARAM 1 0 1 beef\t\n";
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::NSEC3PARAM(), zclass,
                                      "1 0 1 beef")));
}

TEST_F(MasterLoadTest, loadRRNoComment) {
    // A semicolon in a character-string shouldn't confuse the parser.
    rr_stream << "example.com. 3600 IN TXT \"aaa;bbb\"\n";
    masterLoad(rr_stream, origin, zclass, callback);
    EXPECT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::TXT(), zclass,
                                      "\"aaa;bbb\"")));
}

TEST_F(MasterLoadTest, nonAbsoluteOwner) {
    // If the owner name is not absolute, the zone origin is assumed to be
    // its origin.
    rr_stream << "example.com 3600 IN A 192.0.2.1";
    masterLoad(rr_stream, origin, zclass, callback);
    EXPECT_EQ(1, results.size());
    EXPECT_EQ(results[0]->getName(), Name("example.com.example.com"));
}

TEST_F(MasterLoadTest, loadRREmptyAndComment) {
    // There's no RDATA (invalid in this case) but a comment.  This position
    // shouldn't cause any disruption and should be treated as a normal error.
    rr_stream << "example.com. 3600 IN A ;\n";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadWithNoEOF) {
    // the input stream doesn't end with a new line (and the following blank
    // line).  It should be accepted.
    string rr_string(a_rr1);
    rr_string.erase(rr_string.end() - 1);
    rr_stream << rr_string;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(a_rr1, results[0]->toText());
}

TEST_F(MasterLoadTest, loadEmpty) {
    // an unusual case: empty input.  load must succeed with an empty result.
    masterLoad(rr_stream, origin, zclass, callback);
    EXPECT_EQ(0, results.size());   
}

TEST_F(MasterLoadTest, loadWithBeginningSpace) {
    rr_stream << " " << a_rr1;
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadWithBeginningTab) {
    rr_stream << "\t" << a_rr1;
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadInvalidRRClass) {
    rr_stream << "example.com. 3600 CH TXT \"test text\"";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadOutOfZoneData) {
    rr_stream << "example.org. 3600 IN A 192.0.2.255";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadNonAtopSOA) {
    // SOA's owner name must be zone's origin.
    rr_stream << "soa.example.com. 3600 IN SOA . . 0 0 0 0 0";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);
}

// Load TTL with units
TEST_F(MasterLoadTest, loadUnitTTL) {
    stringstream rr_stream2("example.com. 1D IN A 192.0.2.1");
    masterLoad(rr_stream2, origin, zclass, callback);
    EXPECT_EQ(1, results.size());
    EXPECT_EQ(0, results[0]->getRdataIterator()->getCurrent().compare(
                  *rdata::createRdata(RRType::A(), zclass, "192.0.2.1")));
}

TEST_F(MasterLoadTest, loadBadRRText) {
    rr_stream << "example..com. 3600 IN A 192.0.2.1"; // bad owner name
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback),
                 MasterLoadError);

    // bad RR class text
    stringstream rr_stream3("example.com. 3600 BAD A 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream3, origin, zclass, callback),
                 MasterLoadError);

    // bad RR type text
    stringstream rr_stream4("example.com. 3600 IN BAD 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream4, origin, zclass, callback),
                 MasterLoadError);

    // bad RDATA text
    stringstream rr_stream5("example.com. 3600 IN A 2001:db8::1");
    EXPECT_THROW(masterLoad(rr_stream5, origin, zclass, callback),
                 MasterLoadError);

    // incomplete RR text
    stringstream rr_stream6("example.com. 3600 IN A");
    EXPECT_THROW(masterLoad(rr_stream6, origin, zclass, callback),
                 MasterLoadError);
}

// This is a helper callback to test the case the input stream becomes bad
// in the middle of processing.
class StreamInvalidator : public unary_function<ConstRRsetPtr, void> {
public:
    StreamInvalidator(stringstream& ss) : ss_(ss) {}
    void operator()(ConstRRsetPtr) {
        ss_.setstate(ios::badbit);
    }
private:
    stringstream& ss_;
};

TEST_F(MasterLoadTest, loadBadStream) {
    rr_stream << txt_rr << a_rr1;
    StreamInvalidator invalidator(rr_stream);
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, invalidator),
                 MasterLoadError);
}

TEST_F(MasterLoadTest, loadFromFile) {
    // The main parser is shared with the stream version, so we simply test
    // file I/O specific parts.
    masterLoad(TEST_DATA_SRCDIR "/masterload.txt", origin, zclass, callback);
    ASSERT_EQ(2, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(string(a_rr1) + string(a_rr2), results[1]->toText());

    // NULL file name.  Should result in exception.
    EXPECT_THROW(masterLoad(NULL, origin, zclass, callback), MasterLoadError);

    // Non existent file name.  Ditto.
    EXPECT_THROW(masterLoad(TEST_DATA_BUILDDIR "/notexistent.txt", origin,
                            zclass, callback), MasterLoadError);
}
} // end namespace
