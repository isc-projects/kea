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

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrcollator.h>
#include <dns/rdata.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>

#include <vector>

using std::vector;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

typedef RRCollator::AddRRsetCallback AddRRsetCallback;

void
addRRset(const RRsetPtr& rrset, vector<ConstRRsetPtr>* to_append) {
    to_append->push_back(rrset);
}

class RRCollatorTest : public ::testing::Test {
protected:
    RRCollatorTest() :
        origin_("example.com"), rrclass_(RRClass::IN()), rrttl_(3600),
        collator_(boost::bind(addRRset, _1, &rrsets_)),
        rr_callback_(collator_.getCallback())
    {
        RRsetPtr rrset(new RRset(origin_, rrclass_, RRType::A(), rrttl_));
        a_rdata1_ = createRdata(RRType::A(), rrclass_, "192.0.2.1");
        a_rdata2_ = createRdata(RRType::A(), rrclass_, "192.0.2.2");
        rrset->addRdata(a_rdata1_);
        rrset->addRdata(a_rdata2_);
        a_rrset_ = rrset;

        rrset = RRsetPtr(new RRset(origin_, rrclass_, RRType::AAAA(), rrttl_));
        aaaa_rdata_ = createRdata(RRType::AAAA(), rrclass_, "2001:db8::1");
        aaaa_rrset_ = rrset;
    }

    void checkRRset(const Name& expected_name, const RRClass& expected_class,
                    const RRType& expected_type, const RRTTL& expected_ttl,
                    const vector<ConstRdataPtr>& expected_rdatas) {
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

    const Name origin_;
    const RRClass rrclass_;
    const RRTTL rrttl_;
    vector<ConstRRsetPtr> rrsets_;
    RdataPtr a_rdata1_, a_rdata2_, aaaa_rdata_;
    ConstRRsetPtr a_rrset_, aaaa_rrset_;
    RRCollator collator_;
    AddRRCallback rr_callback_;
};

TEST_F(RRCollatorTest, add) {
    vector<ConstRdataPtr> rdatas;

    // Add two RRs belonging to the same RRset.  These will be buffered.
    rr_callback_(origin_, rrclass_, RRType::A(), rrttl_, a_rdata1_);
    EXPECT_TRUE(rrsets_.empty()); // not yet given as an RRset
    rr_callback_(origin_, rrclass_, RRType::A(), rrttl_, a_rdata2_);
    EXPECT_TRUE(rrsets_.empty()); // still not given

    // Add another type of RR.  This completes the construction of the A RRset,
    // which will be given via the callback.
    rr_callback_(origin_, rrclass_, RRType::AAAA(), rrttl_, aaaa_rdata_);
    rdatas.push_back(a_rdata1_);
    rdatas.push_back(a_rdata2_);
    checkRRset(origin_, rrclass_, RRType::A(), rrttl_, rdatas);

    // Let the collator we are done, then we'll see the AAAA RR as an RRset.
    collator_.finish();
    rdatas.clear();
    rdatas.push_back(aaaa_rdata_);
    checkRRset(origin_, rrclass_, RRType::AAAA(), rrttl_, rdatas);
}

}
