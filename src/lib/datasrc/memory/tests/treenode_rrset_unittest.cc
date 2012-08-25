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

#include <util/memory_segment_local.h>

#include <datasrc/memory/treenode_rrset.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/rdata_serialization.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::testutils;

namespace {

class TreeNodeRRsetTest : public ::testing::Test {
protected:
    TreeNodeRRsetTest() :
        name_("www.example.com"),
        a_rrset_(textToRRset("www.example.com. 3600 IN A 192.0.2.1")),
        rrsig_rrset_(textToRRset("www.example.com. 3600 IN RRSIG "
                                 "A 5 2 3600 20120814220826 20120715220826 "
                                 "1234 example.com. FAKE"))
    {
        tree_ = ZoneTree::create(mem_sgmt_, true);
        tree_->insert(mem_sgmt_, name_, &zone_node_);
        rdataset_ = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                     rrsig_rrset_);
        zone_node_->setData(mem_sgmt_, rdataset_);
    }
    void TearDown() {
        ZoneTree::destroy(mem_sgmt_, tree_);
        // detect any memory leak
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    const Name name_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;
    ConstRRsetPtr a_rrset_, rrsig_rrset_;
    ZoneTree* tree_;
    ZoneNode* zone_node_;
    RdataSet* rdataset_;
};

TEST_F(TreeNodeRRsetTest, create) {
    const TreeNodeRRset rrset1(RRClass::IN(), zone_node_, rdataset_, true);
    EXPECT_EQ(RRClass::IN(), rrset1.getClass());
    EXPECT_EQ(RRType::A(), rrset1.getType());
    EXPECT_EQ(1, rrset1.getRdataCount());
    EXPECT_EQ(1, rrset1.getRRsigDataCount());

    const TreeNodeRRset rrset2(RRClass::IN(), zone_node_, rdataset_, false);
    EXPECT_EQ(RRClass::IN(), rrset2.getClass());
    EXPECT_EQ(1, rrset2.getRdataCount());
    EXPECT_EQ(0, rrset2.getRRsigDataCount());
}
}
