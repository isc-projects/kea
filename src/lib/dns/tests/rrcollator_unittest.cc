// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/master_loader.h>
#include <dns/master_loader_callbacks.h>
#include <dns/rrclass.h>
#include <dns/rrcollator.h>
#include <dns/rdata.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using boost::lexical_cast;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

typedef RRCollator::AddRRsetCallback AddRRsetCallback;

void
addRRset(const RRsetPtr& rrset, vector<ConstRRsetPtr>* to_append,
         const bool* do_throw) {
    if (*do_throw) {
        isc_throw(isc::Unexpected, "faked failure");
    }
    to_append->push_back(rrset);
}

class RRCollatorTest : public ::testing::Test {
protected:
    RRCollatorTest() :
        issue_callbacks_(boost::bind(&RRCollatorTest::issueCallback, this,
                                     _1, _2, _3, true),
                         boost::bind(&RRCollatorTest::issueCallback, this,
                                     _1, _2, _3, false)),
        origin_("example.com"), rrclass_(RRClass::IN()), rrttl_(3600),
        throw_from_callback_(false),
        collator_(boost::bind(addRRset, _1, &rrsets_, &throw_from_callback_),
                  issue_callbacks_),
        rr_callback_(collator_.getCallback()),
        a_rdata1_(createRdata(RRType::A(), rrclass_, "192.0.2.1")),
        a_rdata2_(createRdata(RRType::A(), rrclass_, "192.0.2.2")),
        txt_rdata_(createRdata(RRType::TXT(), rrclass_, "test")),
        sig_rdata1_(createRdata(RRType::RRSIG(), rrclass_,
                                "A 5 3 3600 20000101000000 20000201000000 "
                                "12345 example.com. FAKE\n")),
        sig_rdata2_(createRdata(RRType::RRSIG(), rrclass_,
                                "NS 5 3 3600 20000101000000 20000201000000 "
                                "12345 example.com. FAKE\n"))
    {}

    virtual void TearDown() {
        // (The current implementation of) RRCollator should never report an
        // error.
        EXPECT_TRUE(errors_.empty());
    }

    void checkRRset(const Name& expected_name, const RRClass& expected_class,
                    const RRType& expected_type, const RRTTL& expected_ttl,
                    const vector<ConstRdataPtr>& expected_rdatas) {
        SCOPED_TRACE(expected_name.toText(true) + "/" +
                     expected_class.toText() + "/" + expected_type.toText());

        // This test always clears rrsets_ to confirm RRsets are added
        // one-by-one
        ASSERT_EQ(1, rrsets_.size());

        ConstRRsetPtr actual = rrsets_[0];
        EXPECT_EQ(expected_name, actual->getName());
        EXPECT_EQ(expected_class, actual->getClass());
        EXPECT_EQ(expected_type, actual->getType());
        EXPECT_EQ(expected_ttl, actual->getTTL());
        ASSERT_EQ(expected_rdatas.size(), actual->getRdataCount());
        vector<ConstRdataPtr>::const_iterator it = expected_rdatas.begin();
        for (RdataIteratorPtr rit = actual->getRdataIterator();
             !rit->isLast();
             rit->next()) {
            EXPECT_EQ(0, rit->getCurrent().compare(**it));
            ++it;
        }

        rrsets_.clear();
    }

    void issueCallback(const string& src_name, size_t src_line,
                       const string& reason, bool is_error) {
        const string msg(src_name + ":" + lexical_cast<string>(src_line) +
                         ": " + reason);
        if (is_error) {
            errors_.push_back(msg);
        } else {
            warnings_.push_back(msg);
        }
    }

private:
    MasterLoaderCallbacks issue_callbacks_;
protected:
    const Name origin_;
    const RRClass rrclass_;
    const RRTTL rrttl_;
    vector<ConstRRsetPtr> rrsets_;
    bool throw_from_callback_;
    RRCollator collator_;
    AddRRCallback rr_callback_;
    const RdataPtr a_rdata1_, a_rdata2_, txt_rdata_, sig_rdata1_, sig_rdata2_;
    vector<ConstRdataPtr> rdatas_; // placeholder for expected data
    vector<string> warnings_, errors_;
};

TEST_F(RRCollatorTest, basicCases) {
    // Add two RRs belonging to the same RRset.  These will be buffered.
    rr_callback_(origin_, rrclass_, RRType::A(), rrttl_, a_rdata1_);
    EXPECT_TRUE(rrsets_.empty()); // not yet given as an RRset
    rr_callback_(origin_, rrclass_, RRType::A(), rrttl_, a_rdata2_);
    EXPECT_TRUE(rrsets_.empty()); // still not given

    // Add another type of RR.  This completes the construction of the A RRset,
    // which will be given via the callback.
    rr_callback_(origin_, rrclass_, RRType::TXT(), rrttl_, txt_rdata_);
    rdatas_.push_back(a_rdata1_);
    rdatas_.push_back(a_rdata2_);
    checkRRset(origin_, rrclass_, RRType::A(), rrttl_, rdatas_);

    // Add the same type of RR but of different name.  This should make another
    // callback for the previous TXT RR.
    rr_callback_(Name("txt.example.com"), rrclass_, RRType::TXT(), rrttl_,
                 txt_rdata_);
    rdatas_.clear();
    rdatas_.push_back(txt_rdata_);
    checkRRset(origin_, rrclass_, RRType::TXT(), rrttl_, rdatas_);

    // Add the same type and name of RR but of different class (rare case
    // in practice)
    rr_callback_(Name("txt.example.com"), RRClass::CH(), RRType::TXT(), rrttl_,
                 txt_rdata_);
    rdatas_.clear();
    rdatas_.push_back(txt_rdata_);
    checkRRset(Name("txt.example.com"), rrclass_, RRType::TXT(), rrttl_,
               rdatas_);

    // There should have been no warnings.
    EXPECT_EQ(0, warnings_.size());

    // Tell the collator we are done, then we'll see the last RR as an RRset.
    collator_.flush();
    checkRRset(Name("txt.example.com"), RRClass::CH(), RRType::TXT(), rrttl_,
               rdatas_);

    // Redundant flush() will be no-op.
    collator_.flush();
    EXPECT_TRUE(rrsets_.empty());
}

TEST_F(RRCollatorTest, minTTLFirst) {
    // RRs of the same RRset but has different TTLs.  The first RR has
    // the smaller TTL, which should be used for the TTL of the RRset.
    // There should be a warning callback about this.
    rr_callback_(origin_, rrclass_, RRType::A(), RRTTL(10), a_rdata1_);
    rr_callback_(origin_, rrclass_, RRType::A(), RRTTL(20), a_rdata2_);
    rdatas_.push_back(a_rdata1_);
    rdatas_.push_back(a_rdata2_);
    collator_.flush();
    checkRRset(origin_, rrclass_, RRType::A(), RRTTL(10), rdatas_);
    EXPECT_EQ(1, warnings_.size());
    EXPECT_EQ("<unknown source>:0: Different TTLs for the same RRset: "
              "example.com/IN/A, set to 10", warnings_.at(0));
}

TEST_F(RRCollatorTest, maxTTLFirst) {
    // RRs of the same RRset but has different TTLs.  The second RR has
    // the smaller TTL, which should be used for the TTL of the RRset.
    rr_callback_(origin_, rrclass_, RRType::A(), RRTTL(20), a_rdata1_);
    rr_callback_(origin_, rrclass_, RRType::A(), RRTTL(10), a_rdata2_);
    rdatas_.push_back(a_rdata1_);
    rdatas_.push_back(a_rdata2_);
    collator_.flush();
    checkRRset(origin_, rrclass_, RRType::A(), RRTTL(10), rdatas_);
    EXPECT_EQ(1, warnings_.size());
    EXPECT_EQ("<unknown source>:0: Different TTLs for the same RRset: "
              "example.com/IN/A, set to 10", warnings_.at(0));
}

TEST_F(RRCollatorTest, addRRSIGs) {
    // RRSIG is special; they are also distinguished by their covered types.
    rr_callback_(origin_, rrclass_, RRType::RRSIG(), rrttl_, sig_rdata1_);
    rr_callback_(origin_, rrclass_, RRType::RRSIG(), rrttl_, sig_rdata2_);

    rdatas_.push_back(sig_rdata1_);
    checkRRset(origin_, rrclass_, RRType::RRSIG(), rrttl_, rdatas_);
}

TEST_F(RRCollatorTest, emptyFlush) {
    collator_.flush();
    EXPECT_TRUE(rrsets_.empty());
}

TEST_F(RRCollatorTest, throwFromCallback) {
    // Adding an A RR
    rr_callback_(origin_, rrclass_, RRType::A(), rrttl_, a_rdata1_);

    // Adding a TXT RR, which would trigger RRset callback, but in this test
    // it throws.  The added TXT RR will be effectively lost.
    throw_from_callback_ = true;
    EXPECT_THROW(rr_callback_(origin_, rrclass_, RRType::TXT(), rrttl_,
                              txt_rdata_), isc::Unexpected);

    // We'll only see the A RR.
    throw_from_callback_ = false;
    collator_.flush();
    rdatas_.push_back(a_rdata1_);
    checkRRset(origin_, rrclass_, RRType::A(), rrttl_, rdatas_);
}

TEST_F(RRCollatorTest, emptyCallback) {
    const AddRRsetCallback empty_callback;
    EXPECT_THROW(RRCollator collator(empty_callback), isc::InvalidParameter);
}

TEST_F(RRCollatorTest, withMasterLoader) {
    // Test a simple case with MasterLoader.  There shouldn't be anything
    // special, but that's the mainly intended usage of the collator, so we
    // check it explicitly.  Also, this test uses a different local collator,
    // just for checking it works with omitting the issue callback (using
    // the default).
    RRCollator collator(boost::bind(addRRset, _1, &rrsets_,
                                    &throw_from_callback_));
    std::istringstream ss("example.com. 3600 IN A 192.0.2.1\n");
    MasterLoader loader(ss, origin_, rrclass_,
                        MasterLoaderCallbacks::getNullCallbacks(),
                        collator.getCallback());
    loader.load();
    collator.flush();
    rdatas_.push_back(a_rdata1_);
    checkRRset(origin_, rrclass_, RRType::A(), rrttl_, rdatas_);
}

}
