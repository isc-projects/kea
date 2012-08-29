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

#include <util/buffer.h>
#include <util/memory_segment_local.h>

#include <datasrc/memory/treenode_rrset.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/rdata_serialization.h>

#include <util/unittests/wiredata.h>
#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::testutils;
using isc::util::unittests::matchWireData;
using isc::util::OutputBuffer;

namespace {

class TreeNodeRRsetTest : public ::testing::Test {
protected:
    TreeNodeRRsetTest() :
        rrclass_(RRClass::IN()),
        origin_name_("example.com"), www_name_("www.example.com"),
        ns_rrset_(textToRRset("example.com. 3600 IN NS ns.example.com.")),
        a_rrset_(textToRRset("www.example.com. 3600 IN A 192.0.2.1")),
        dname_rrset_(textToRRset("example.com. 3600 IN DNAME d.example.org.")),
        rrsig_rrset_(textToRRset("www.example.com. 3600 IN RRSIG "
                                 "A 5 2 3600 20120814220826 20120715220826 "
                                 "1234 example.com. FAKE")),
        tree_(NULL)
    {}
    void SetUp() {
        // We create some common test data here in SetUp() so it will be
        // as exception safe as possible.

        tree_ = ZoneTree::create(mem_sgmt_, true);

        tree_->insert(mem_sgmt_, origin_name_, &origin_node_);
        ns_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, ns_rrset_,
                                        ConstRRsetPtr());
        origin_node_->setData(mem_sgmt_, ns_rdataset_);
        dname_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, dname_rrset_,
                                           ConstRRsetPtr());
        ns_rdataset_->next = dname_rdataset_;

        tree_->insert(mem_sgmt_, www_name_, &www_node_);
        a_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                       rrsig_rrset_);
        www_node_->setData(mem_sgmt_, a_rdataset_);
    }
    void TearDown() {
        ZoneTree::destroy(mem_sgmt_, tree_);
        // detect any memory leak
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    const RRClass rrclass_;
    const Name origin_name_, www_name_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;
    MessageRenderer renderer_, renderer_expected_;
    ConstRRsetPtr ns_rrset_, a_rrset_, dname_rrset_, rrsig_rrset_;
    ZoneTree* tree_;
    ZoneNode* origin_node_;
    ZoneNode* www_node_;
    RdataSet* ns_rdataset_;
    RdataSet* dname_rdataset_;
    RdataSet* a_rdataset_;
};

TEST_F(TreeNodeRRsetTest, create) {
    const TreeNodeRRset rrset1(RRClass::IN(), www_node_, a_rdataset_, true);
    EXPECT_EQ(RRClass::IN(), rrset1.getClass());
    EXPECT_EQ(RRType::A(), rrset1.getType());
    EXPECT_EQ(www_name_, rrset1.getName());
    EXPECT_EQ(1, rrset1.getRdataCount());
    EXPECT_EQ(1, rrset1.getRRsigDataCount());

    const TreeNodeRRset rrset2(RRClass::IN(), www_node_, a_rdataset_, false);
    EXPECT_EQ(RRClass::IN(), rrset2.getClass());
    EXPECT_EQ(RRType::A(), rrset2.getType());
    EXPECT_EQ(www_name_, rrset2.getName());
    EXPECT_EQ(1, rrset2.getRdataCount());
    EXPECT_EQ(0, rrset2.getRRsigDataCount());
}

template <typename OutputType>
void
checkToWireResult(OutputType& expected_output, OutputType& actual_output,
                  const TreeNodeRRset& actual_rrset,
                  const Name& prepended_name,
                  ConstRRsetPtr rrset, ConstRRsetPtr rrsig_rrset,
                  bool dnssec_ok)
{
    expected_output.clear();
    actual_output.clear();

    // Prepare "actual" rendered data.  We prepend a name to confirm the
    // owner name should be compressed in both cases.
    prepended_name.toWire(actual_output);
    const int expected_ret = (dnssec_ok && rrsig_rrset) ?
        rrset->getRdataCount() + rrsig_rrset->getRdataCount() :
        rrset->getRdataCount();
    EXPECT_EQ(expected_ret, actual_rrset.toWire(actual_output));

    // Prepare "expected" data.
    prepended_name.toWire(expected_output);
    rrset->toWire(expected_output);
    if (dnssec_ok && rrsig_rrset) {
        rrsig_rrset->toWire(expected_output);
    }

    // Compare the two.
    matchWireData(expected_output.getData(), expected_output.getLength(),
                  actual_output.getData(), actual_output.getLength());
}

TEST_F(TreeNodeRRsetTest, toWire) {
    MessageRenderer expected_renderer, actual_renderer;
    //OutputBuffer expected_buffer(0), actual_buffer(0);

    // 1. with RRSIG, DNSSEC OK
    const TreeNodeRRset rrset1(RRClass::IN(), www_node_, a_rdataset_, true);
    checkToWireResult(expected_renderer, actual_renderer, rrset1, www_name_,
                      a_rrset_, rrsig_rrset_, true);
#ifdef notyet
    checkToWireResult(expected_buffer, actual_buffer, rrset1,  www_name_,
                      a_rrset_, rrsig_rrset_, true);
#endif

    // 2. with RRSIG, DNSSEC not OK
    const TreeNodeRRset rrset2(rrclass_, www_node_, a_rdataset_, false);
    checkToWireResult(expected_renderer, actual_renderer, rrset2, www_name_,
                      a_rrset_, rrsig_rrset_, false);

    // 3. without RRSIG, DNSSEC OK
    const TreeNodeRRset rrset3(rrclass_, origin_node_, ns_rdataset_, true);
    checkToWireResult(expected_renderer, actual_renderer, rrset3, origin_name_,
                      ns_rrset_, ConstRRsetPtr(), true);

    // 4. without RRSIG, DNSSEC not OK
    const TreeNodeRRset rrset4(rrclass_, origin_node_, ns_rdataset_, false);
    checkToWireResult(expected_renderer, actual_renderer, rrset4, origin_name_,
                      ns_rrset_, ConstRRsetPtr(), false);

    // RDATA of DNAME RR shouldn't be compressed.  Prepending "example.org"
    // will check that.
    const TreeNodeRRset rrset5(rrclass_, origin_node_, dname_rdataset_, false);
    checkToWireResult(expected_renderer, actual_renderer, rrset5,
                      Name("example.org"), dname_rrset_, ConstRRsetPtr(),
                      false);
}
}
