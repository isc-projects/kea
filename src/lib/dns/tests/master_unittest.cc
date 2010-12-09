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

#include <functional>
#include <ios>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <dns/master.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

using namespace std;
using namespace isc::dns;

namespace {
class TestCallback : public unary_function<ConstRRsetPtr, void> {
public:
    TestCallback(vector<ConstRRsetPtr>& rrsets) : rrsets_(rrsets) {}
    void operator()(ConstRRsetPtr rrset) {
        rrsets_.push_back(rrset);
    }
private:
    vector<ConstRRsetPtr>& rrsets_;
};

void
testCallback(ConstRRsetPtr rrset, vector<ConstRRsetPtr>* rrsets) {
    rrsets->push_back(rrset);
}

class MasterTest : public ::testing::Test {
protected:
    MasterTest() : origin("example.com"), zclass(RRClass::IN()),
                   callback(results) {}
    Name origin;
    RRClass zclass;
    vector<ConstRRsetPtr> results;
    stringstream rr_stream;
    TestCallback callback;
};

const char* const txt_rr = "example.com. 3600 IN TXT \"test data\"\n";
const char* const a_rr1 = "www.example.com. 60 IN A 192.0.2.1\n";
const char* const a_rr2 = "www.example.com. 60 IN A 192.0.2.2\n";
const char* const a_rr3 = "ftp.example.com. 60 IN A 192.0.2.3\n";
// multi-field RR case
const char* const soa_rr = "example.com. 7200 IN SOA . . 0 0 0 0 0\n";

TEST_F(MasterTest, loadRRs) {
    // a simple case: loading 3 RRs, each consists of a single RRset.
    rr_stream << txt_rr << a_rr1 << soa_rr;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(3, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(a_rr1, results[1]->toText());
    EXPECT_EQ(soa_rr, results[2]->toText());
}

TEST_F(MasterTest, loadWithFunctionCallback) {
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

TEST_F(MasterTest, loadComments) {
    rr_stream << ";; comment line, should be skipped\n"
              << "\n"           // blank line (should be skipped)
              << txt_rr;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
}

TEST_F(MasterTest, loadRRset) {
    // load an RRset containing two RRs
    rr_stream << a_rr1 << a_rr2;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(string(a_rr1) + string(a_rr2), results[0]->toText());
}

TEST_F(MasterTest, loadRRsetsOfSameType) {
    // load two RRsets with the same RR type and different owner names.
    // the loader must distinguish them as separate RRsets.
    rr_stream << a_rr1 << a_rr3;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(2, results.size());
    EXPECT_EQ(a_rr1, results[0]->toText());
    EXPECT_EQ(a_rr3, results[1]->toText());
}

TEST_F(MasterTest, loadRRsetsInterleaved) {
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

TEST_F(MasterTest, loadWithNoEOF) {
    // the input stream doesn't end with a new line (and the following blank
    // line).  It should be accepted.
    string rr_string(a_rr1);
    rr_string.erase(rr_string.end() - 1);
    rr_stream << rr_string;
    masterLoad(rr_stream, origin, zclass, callback);
    ASSERT_EQ(1, results.size());
    EXPECT_EQ(a_rr1, results[0]->toText());
}

TEST_F(MasterTest, loadEmpty) {
    // an unusual case: empty input.  load must succeed with an empty result.
    masterLoad(rr_stream, origin, zclass, callback);
    EXPECT_EQ(0, results.size());   
}

TEST_F(MasterTest, loadWithBeginningSpace) {
    rr_stream << " " << a_rr1;
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);
}

TEST_F(MasterTest, loadWithBeginningTab) {
    rr_stream << "\t" << a_rr1;
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);
}

TEST_F(MasterTest, loadInvalidRRClass) {
    rr_stream << "example.com. 3600 CH TXT \"test text\"";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);
}

TEST_F(MasterTest, loadOutOfZoneData) {
    rr_stream << "example.org. 3600 IN A 192.0.2.255";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);
}

TEST_F(MasterTest, loadNonAtopSOA) {
    // SOA's owner name must be zone's origin.
    rr_stream << "soa.example.com. 3600 IN SOA . . 0 0 0 0 0";
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);
}

TEST_F(MasterTest, loadBadRRText) {
    rr_stream << "example..com. 3600 IN A 192.0.2.1"; // bad owner name
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, callback), MasterError);

    // currently we only support numeric TTLs
    stringstream rr_stream2("example.com. 1D IN A 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream2, origin, zclass, callback), MasterError);

    // bad RR class text
    stringstream rr_stream3("example.com. 3600 BAD A 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream3, origin, zclass, callback), MasterError);

    // bad RR type text
    stringstream rr_stream4("example.com. 3600 IN BAD 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream4, origin, zclass, callback), MasterError);

    // bad RDATA text
    stringstream rr_stream5("example.com. 3600 IN A 2001:db8::1");
    EXPECT_THROW(masterLoad(rr_stream5, origin, zclass, callback), MasterError);

    // incomplete RR text
    stringstream rr_stream6("example.com. 3600 IN A");
    EXPECT_THROW(masterLoad(rr_stream6, origin, zclass, callback), MasterError);

    // owner name is not absolute
    stringstream rr_stream7("example.com 3600 IN A 192.0.2.1");
    EXPECT_THROW(masterLoad(rr_stream7, origin, zclass, callback), MasterError);
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

TEST_F(MasterTest, loadBadStream) {
    rr_stream << txt_rr << a_rr1;
    StreamInvalidator invalidator(rr_stream);
    EXPECT_THROW(masterLoad(rr_stream, origin, zclass, invalidator),
                 MasterError);
}

TEST_F(MasterTest, loadFromFile) {
    // The main parser is shared with the stream version, so we simply test
    // file I/O specific parts.
    masterLoad(TEST_DATA_BUILDDIR "/masterload.txt", origin, zclass, callback);
    ASSERT_EQ(2, results.size());
    EXPECT_EQ(txt_rr, results[0]->toText());
    EXPECT_EQ(string(a_rr1) + string(a_rr2), results[1]->toText());

    // NULL file name.  Should result in exception.
    EXPECT_THROW(masterLoad(NULL, origin, zclass, callback), MasterError);

    // Non existent file name.  Ditto.
    EXPECT_THROW(masterLoad(TEST_DATA_BUILDDIR "/notexistent.txt", origin,
                            zclass, callback), MasterError);
}
} // end namespace
