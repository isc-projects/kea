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
#include <datasrc/memory/zone_data.h>

#include <util/unittests/wiredata.h>
#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

using std::vector;
using std::string;
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
        wildcard_name_("*.example.com"), match_name_("match.example.com"),
        ns_rrset_(textToRRset("example.com. 3600 IN NS ns.example.com.")),
        a_rrset_(textToRRset("www.example.com. 3600 IN A 192.0.2.1\n"
                             "www.example.com. 3600 IN A 192.0.2.2")),
        aaaa_rrset_(textToRRset("www.example.com. 3600 IN AAAA "
                                "2001:db8::1\n")),
        dname_rrset_(textToRRset("example.com. 3600 IN DNAME d.example.org.")),
        a_rrsig_rrset_(textToRRset("www.example.com. 3600 IN RRSIG "
                                   "A 5 2 3600 20120814220826 20120715220826 "
                                   "1234 example.com. FAKE")),
        aaaa_rrsig_rrset_(textToRRset("www.example.com. 3600 IN RRSIG AAAA 5 2"
                                      " 3600 20120814220826 20120715220826 "
                                      "1234 example.com. FAKE\n"
                                      "www.example.com. 3600 IN RRSIG AAAA 5 2"
                                      " 3600 20120814220826 20120715220826 "
                                      "4321 example.com. FAKE\n")),
        txt_rrsig_rrset_(textToRRset("www.example.com. 3600 IN RRSIG TXT 5 2"
                                     " 3600 20120814220826 20120715220826 "
                                     "1234 example.com. FAKE\n")),
        wildmatch_rrset_(textToRRset(
                             "match.example.com. 3600 IN A 192.0.2.1\n"
                             "match.example.com. 3600 IN A 192.0.2.2")),
        wildmatch_rrsig_rrset_(textToRRset(
                                   "match.example.com. 3600 IN RRSIG "
                                   "A 5 2 3600 20120814220826 20120715220826 "
                                   "1234 example.com. FAKE")),
        zone_data_(NULL), origin_node_(NULL), www_node_(NULL),
        wildcard_node_(NULL), ns_rdataset_(NULL), dname_rdataset_(NULL),
        a_rdataset_(NULL), aaaa_rdataset_(NULL), rrsig_only_rdataset_(NULL),
        wildcard_rdataset_(NULL)
    {}
    void SetUp() {
        // We create some common test data here in SetUp() so it will be
        // as exception safe as possible.

        zone_data_ = ZoneData::create(mem_sgmt_, origin_name_);

        zone_data_->insertName(mem_sgmt_, origin_name_, &origin_node_);
        ns_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, ns_rrset_,
                                        ConstRRsetPtr());
        origin_node_->setData(ns_rdataset_);
        dname_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, dname_rrset_,
                                           ConstRRsetPtr());
        ns_rdataset_->next = dname_rdataset_;

        zone_data_->insertName(mem_sgmt_, www_name_, &www_node_);
        a_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                       a_rrsig_rrset_);
        www_node_->setData(a_rdataset_);

        aaaa_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, aaaa_rrset_,
                                          aaaa_rrsig_rrset_);
        a_rdataset_->next = aaaa_rdataset_;

        // A rare (half broken) case of RRSIG-only set
        rrsig_only_rdataset_ = RdataSet::create(mem_sgmt_, encoder_,
                                                ConstRRsetPtr(),
                                                txt_rrsig_rrset_);
        aaaa_rdataset_->next = rrsig_only_rdataset_;

        zone_data_->insertName(mem_sgmt_, wildcard_name_, &wildcard_node_);
        wildcard_rdataset_ = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                              a_rrsig_rrset_);
        wildcard_node_->setData(wildcard_rdataset_);
    }
    void TearDown() {
        ZoneData::destroy(mem_sgmt_, zone_data_, rrclass_);
        // detect any memory leak
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    const RRClass rrclass_;
    const Name origin_name_, www_name_, wildcard_name_, match_name_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;
    MessageRenderer renderer_, renderer_expected_;
    ConstRRsetPtr ns_rrset_, a_rrset_, aaaa_rrset_, dname_rrset_,
        a_rrsig_rrset_, aaaa_rrsig_rrset_, txt_rrsig_rrset_,
        wildmatch_rrset_, wildmatch_rrsig_rrset_;
    ZoneData* zone_data_;
    ZoneNode* origin_node_;
    ZoneNode* www_node_;
    ZoneNode* wildcard_node_;
    RdataSet* ns_rdataset_;
    RdataSet* dname_rdataset_;
    RdataSet* a_rdataset_;
    RdataSet* aaaa_rdataset_;
    RdataSet* rrsig_only_rdataset_;
    RdataSet* wildcard_rdataset_; // for wildcard (type doesn't matter much)
};

void
compareRRSIGData(RdataIteratorPtr rit, const void* data, size_t data_len) {
    ASSERT_FALSE(rit->isLast());

    OutputBuffer buffer(0);
    rit->getCurrent().toWire(buffer);
    matchWireData(data, data_len, buffer.getData(), buffer.getLength());
    rit->next();
}

// Check some trivial fields of a constructed TreeNodeRRset (passed as
// AbstractRRset as we'd normally use it in polymorphic way).
// Other complicated fields are checked through rendering tests.
void
checkBasicFields(const AbstractRRset& actual_rrset, const RdataSet* rdataset,
                 const Name& expected_name,
                 const RRClass& expected_class, const RRType& expected_type,
                 const uint32_t expected_ttl,
                 size_t expected_rdatacount, size_t expected_sigcount)
{
    EXPECT_EQ(expected_name, actual_rrset.getName());
    EXPECT_EQ(expected_class, actual_rrset.getClass());
    EXPECT_EQ(expected_type, actual_rrset.getType());
    EXPECT_EQ(RRTTL(expected_ttl), actual_rrset.getTTL());
    EXPECT_EQ(expected_rdatacount, actual_rrset.getRdataCount());
    EXPECT_EQ(expected_sigcount, actual_rrset.getRRsigDataCount());

    // getRRsig() should return non NULL iff the RRset is expected to be signed
    if (expected_sigcount == 0) {
        EXPECT_FALSE(actual_rrset.getRRsig());
    } else {
        ConstRRsetPtr actual_sigrrset = actual_rrset.getRRsig();
        ASSERT_TRUE(actual_sigrrset);
        EXPECT_EQ(expected_name, actual_sigrrset->getName());
        EXPECT_EQ(expected_class, actual_sigrrset->getClass());
        EXPECT_EQ(RRType::RRSIG(), actual_sigrrset->getType());
        EXPECT_EQ(RRTTL(expected_ttl), actual_sigrrset->getTTL());
        EXPECT_EQ(expected_sigcount, actual_sigrrset->getRdataCount());

        // Compare each RRSIG RDATA
        RdataIteratorPtr rit = actual_sigrrset->getRdataIterator();
        RdataReader reader(expected_class, expected_type,
                           rdataset->getDataBuf(), expected_rdatacount,
                           expected_sigcount, &RdataReader::emptyNameAction,
                           boost::bind(compareRRSIGData, rit, _1, _2));
        while (reader.nextSig() != RdataReader::RRSET_BOUNDARY) {}
        EXPECT_TRUE(rit->isLast()); // should check all RDATAs
    }
}

// The following two are trivial wrapper to create a shared pointer
// version of TreeNodeRRset object in order to work around dubious
// behavior of some C++ compiler: they reject getting a const reference to
// a temporary non-copyable object.
boost::shared_ptr<TreeNodeRRset>
createRRset(const RRClass& rrclass, const ZoneNode* node,
            const RdataSet* rdataset, bool dnssec_ok,
            const void* ttl_data = NULL)
{
    if (ttl_data) {
        return (boost::shared_ptr<TreeNodeRRset>(
                    new TreeNodeRRset(rrclass, node, rdataset, dnssec_ok,
                                      ttl_data)));
    }
    return (boost::shared_ptr<TreeNodeRRset>(
                new TreeNodeRRset(rrclass, node, rdataset, dnssec_ok)));
}

boost::shared_ptr<TreeNodeRRset>
createRRset(const Name& realname, const RRClass& rrclass, const ZoneNode* node,
            const RdataSet* rdataset, bool dnssec_ok)
{
    return (boost::shared_ptr<TreeNodeRRset>(
                new TreeNodeRRset(realname, rrclass, node, rdataset,
                                  dnssec_ok)));
}

TEST_F(TreeNodeRRsetTest, create) {
    // Constructed with RRSIG, and it should be visible.
    checkBasicFields(*createRRset(rrclass_, www_node_, a_rdataset_, true),
                     a_rdataset_, www_name_, rrclass_, RRType::A(), 3600, 2,
                     1);
    // Constructed with RRSIG, and it should be invisible.
    checkBasicFields(*createRRset(rrclass_, www_node_, a_rdataset_, false),
                     a_rdataset_, www_name_, rrclass_, RRType::A(), 3600, 2,
                     0);
    // Constructed without RRSIG, and it would be visible (but of course won't)
    checkBasicFields(*createRRset(rrclass_, origin_node_, ns_rdataset_, true),
                     ns_rdataset_, origin_name_, rrclass_, RRType::NS(), 3600,
                     1, 0);
    // Constructed without RRSIG, and it should be visible
    checkBasicFields(*createRRset(rrclass_, origin_node_, ns_rdataset_, false),
                     ns_rdataset_, origin_name_, rrclass_, RRType::NS(), 3600,
                     1, 0);
    // RRSIG-only case (note the RRset's type is covered type)
    checkBasicFields(*createRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                                  true),
                     rrsig_only_rdataset_, www_name_, rrclass_, RRType::TXT(),
                     3600, 0, 1);
    // RRSIG-only case (note the RRset's type is covered type), but it's
    // invisible
    checkBasicFields(*createRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                                  false),
                     rrsig_only_rdataset_, www_name_, rrclass_, RRType::TXT(),
                     3600, 0, 0);
    // Wildcard substitution
    checkBasicFields(*createRRset(match_name_, rrclass_,
                                  wildcard_node_, wildcard_rdataset_,
                                  true),
                     wildcard_rdataset_, match_name_, rrclass_, RRType::A(),
                     3600, 2, 1);

    // Constructed with explicit TTL
    const uint32_t ttl = 0;     // use 0 to avoid byte-order conversion
    checkBasicFields(*createRRset(rrclass_, www_node_, a_rdataset_, true,
                                  &ttl),
                     a_rdataset_, www_name_, rrclass_, RRType::A(), 0, 2,
                     1);
}

// The following two templated functions are helper to encapsulate the
// concept truncation and handle MessageRenderer and OutputBuffer transparently
// in templated test cases.
template <typename OutputType>
void
setOutputLengthLimit(OutputType& output, size_t len_limit) {
    output.setLengthLimit(len_limit);
}
template <>
void
setOutputLengthLimit<OutputBuffer>(OutputBuffer&, size_t) {
}

template <typename OutputType>
bool
isOutputTruncated(OutputType& output) {
    return (output.isTruncated());
}
template <>
bool
isOutputTruncated<OutputBuffer>(OutputBuffer&) {
    return (false);
}

// Templated so we so can support OutputBuffer version of toWire().
// We use the above helper templated functions for some renderer only methods.
// We test two sets of cases: normal rendering case and case when truncation
// is expected.  The latter is effectively for MessageRenderer only.
// If len_limit == 0, we consider it the normal case; otherwise it's for
// truncation.  prepended_name isn't used for the truncation case.
template <typename OutputType>
void
checkToWireResult(OutputType& expected_output, OutputType& actual_output,
                  const AbstractRRset& actual_rrset,
                  const Name& prepended_name,
                  ConstRRsetPtr rrset, ConstRRsetPtr rrsig_rrset,
                  bool dnssec_ok,
                  size_t len_limit = 0,
                  size_t expected_result = 0)
{
    expected_output.clear();
    actual_output.clear();

    if (len_limit == 0) {       // normal rendering
        // Prepare "actual" rendered data.  We prepend a name to confirm the
        // owner name should be compressed in both cases.
        prepended_name.toWire(actual_output);
        const size_t rdata_count = rrset ? rrset->getRdataCount() : 0;
        const int expected_ret = (dnssec_ok && rrsig_rrset) ?
            rdata_count + rrsig_rrset->getRdataCount() : rdata_count;
        EXPECT_EQ(expected_ret, actual_rrset.toWire(actual_output));
    } else {                    // truncation
        setOutputLengthLimit(actual_output, len_limit);
        EXPECT_EQ(expected_result, actual_rrset.toWire(actual_output));
        EXPECT_TRUE(isOutputTruncated(actual_output)); // always true here
    }

    // Prepare "expected" data.
    if (len_limit == 0) {       // normal rendering
        prepended_name.toWire(expected_output);
    } else {                    // truncation
        setOutputLengthLimit(expected_output, len_limit);
    }
    if (rrset) {
        rrset->toWire(expected_output);
    }
    if (!isOutputTruncated(expected_output) && dnssec_ok && rrsig_rrset) {
        rrsig_rrset->toWire(expected_output);
    }

    // Compare the two.
    matchWireData(expected_output.getData(), expected_output.getLength(),
                  actual_output.getData(), actual_output.getLength());
}

TEST_F(TreeNodeRRsetTest, getLength) {
    // A RR
    // www.example.com = 1 + 3 + 1 + 7 + 1 + 3 + 1 = 17 octets
    // TYPE field = 2 octets
    // CLASS field = 2 octets
    // TTL field = 2 octets
    // RDLENGTH field = 2 octets
    // A RDATA = 4 octets
    // Total = 17 + 2 + 2 + 2 + 2 + 4 = 29 octets

    // RRSIG RR
    // www.example.com = 1 + 4 + 1 + 7 + 1 + 3 + 1 = 17 octets
    // TYPE field = 2 octets
    // CLASS field = 2 octets
    // TTL field = 2 octets
    // RDLENGTH field = 2 octets
    // RRSIG RDATA = 18 + [1 + 7 + 1 + 3 + 1 (example.com)] + 3 (base64
    //               decode of FAKE) octets
    // Total = 17 + 2 + 2 + 2 + 2 + 34 = 59 octets

    // 1. with RRSIG, DNSSEC not OK
    // ` 2 A RRs + 0 RRSIG RRs
    const TreeNodeRRset rrset1(rrclass_, www_node_, a_rdataset_, false);
    EXPECT_EQ(29 + 29, rrset1.getLength());

    // 2. with RRSIG, DNSSEC OK
    // ` 2 A RRs + 1 RRSIG RR
    const TreeNodeRRset rrset2(rrclass_, www_node_, a_rdataset_, true);
    EXPECT_EQ(29 + 29 + 59, rrset2.getLength());
}

TEST_F(TreeNodeRRsetTest, toWire) {
    MessageRenderer expected_renderer, actual_renderer;
    OutputBuffer expected_buffer(0), actual_buffer(0);

    {
        SCOPED_TRACE("with RRSIG, DNSSEC OK");
        const TreeNodeRRset rrset(rrclass_, www_node_, a_rdataset_, true);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          www_name_, a_rrset_, a_rrsig_rrset_, true);
        // Currently the buffer version throws
        EXPECT_THROW(
            checkToWireResult(expected_buffer, actual_buffer, rrset,
                              www_name_, a_rrset_, a_rrsig_rrset_, true),
            isc::Unexpected);
    }

    {
        SCOPED_TRACE("with RRSIG, DNSSEC OK, explicit TTL");
        const uint32_t ttl = 0;
        const TreeNodeRRset rrset(rrclass_, www_node_, a_rdataset_, true,
                                  &ttl);
        // We need separate variable for the following two: SunStudio cannot
        // automatically promote RRsetPtr to ConstRRsetPtr in the templated
        // function.
        ConstRRsetPtr expected_rrset =
            textToRRset("www.example.com. 0 IN A 192.0.2.1\n"
                        "www.example.com. 0 IN A 192.0.2.2");
        ConstRRsetPtr expected_rrsig_rrset =
            textToRRset("www.example.com. 0 IN RRSIG "
                        "A 5 2 3600 20120814220826 "
                        "20120715220826 1234 example.com. FAKE");
        checkToWireResult(expected_renderer, actual_renderer, rrset, www_name_,
                          expected_rrset, expected_rrsig_rrset, true);
    }

    {
        SCOPED_TRACE("with RRSIG, DNSSEC not OK");
        const TreeNodeRRset rrset(rrclass_, www_node_, a_rdataset_, false);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          www_name_, a_rrset_, a_rrsig_rrset_, false);
    }

    {
        SCOPED_TRACE("without RRSIG, DNSSEC OK");
        const TreeNodeRRset rrset(rrclass_, origin_node_, ns_rdataset_, true);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          origin_name_, ns_rrset_, ConstRRsetPtr(), true);
    }

    {
        SCOPED_TRACE("without RRSIG, DNSSEC not OK");
        const TreeNodeRRset rrset(rrclass_, origin_node_, ns_rdataset_,
                                  false);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          origin_name_, ns_rrset_, ConstRRsetPtr(), false);
    }

    {
        // RDATA of DNAME DR shouldn't be compressed.  Prepending "example.org"
        // will check that.
        SCOPED_TRACE("uncompressed RDATA");
        const TreeNodeRRset rrset(rrclass_, origin_node_, dname_rdataset_,
                                  false);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          Name("example.org"), dname_rrset_, ConstRRsetPtr(),
                          false);
    }

    {
        SCOPED_TRACE("wildcard with RRSIG");
        checkToWireResult(expected_renderer, actual_renderer,
                          *createRRset(match_name_, rrclass_, wildcard_node_,
                                       wildcard_rdataset_, true),
                          origin_name_, wildmatch_rrset_,
                          wildmatch_rrsig_rrset_, true);
    }

    {
        SCOPED_TRACE("wildcard without RRSIG");
        checkToWireResult(expected_renderer, actual_renderer,
                          *createRRset(match_name_, rrclass_, wildcard_node_,
                                       wildcard_rdataset_, false),
                          origin_name_, wildmatch_rrset_,
                          wildmatch_rrsig_rrset_, false);
    }

    {
        // Very unusual case: the set only contains RRSIG (already rare)
        // and it's requested to be dumped to wire (can only happen in
        // ANY or type-RRSIG queries, which are rare also).  But can still
        // happen.
        SCOPED_TRACE("RRSIG only, DNSSEC OK");
        const TreeNodeRRset rrset(rrclass_, www_node_, rrsig_only_rdataset_,
                                  true);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          www_name_, ConstRRsetPtr(), txt_rrsig_rrset_, true);
    }

    {
        // Similar to the previous case, but DNSSEC records aren't requested.
        // In practice this case wouldn't happen, but API-wise possible, so
        // we test it explicitly.
        SCOPED_TRACE("RRSIG only, DNSSEC not OK");
        const TreeNodeRRset rrset(rrclass_, www_node_, rrsig_only_rdataset_,
                                  false);
        checkToWireResult(expected_renderer, actual_renderer, rrset,
                          www_name_, ConstRRsetPtr(), txt_rrsig_rrset_, false);
    }
}

TEST_F(TreeNodeRRsetTest, toWireTruncated) {
    MessageRenderer expected_renderer, actual_renderer;
    // dummy parameter to checkToWireResult (unused for the this test case)
    const Name& name = Name::ROOT_NAME();

    // Set the truncation limit to name len + 14 bytes of fixed data for A RR
    // (type, class, TTL, rdlen, and 4-byte IPv4 address).  Then we can only
    // render just one RR, without any garbage trailing data.
    checkToWireResult(expected_renderer, actual_renderer,
                      *createRRset(rrclass_, www_node_, a_rdataset_, true),
                      name, a_rrset_, a_rrsig_rrset_, true,
                      www_name_.getLength() + 14,
                      1);   // 1 main RR, no RRSIG

    // The first main RRs should fit in the renderer (the name will be
    // fully compressed, so its size is 2 bytes), but the RRSIG doesn't.
    checkToWireResult(expected_renderer, actual_renderer,
                      *createRRset(rrclass_, www_node_, a_rdataset_, true),
                      name, a_rrset_, a_rrsig_rrset_, true,
                      www_name_.getLength() + 14 + 2 + 14,
                      2);   // 2 main RR, no RRSIG

    // This RRset has one main RR and two RRSIGs.  Rendering the second RRSIG
    // causes truncation.
    // First, compute the rendered length for the main RR and a single RRSIG.
    // The length of the RRSIG should be the same if we "accidentally"
    // rendered the RRSIG for the A RR (which only contains one RRSIG).
    expected_renderer.clear();
    aaaa_rrset_->toWire(expected_renderer);
    a_rrsig_rrset_->toWire(expected_renderer);
    const size_t limit_len = expected_renderer.getLength();
    // Then perform the test
    checkToWireResult(expected_renderer, actual_renderer,
                      *createRRset(rrclass_, www_node_, aaaa_rdataset_, true),
                      name, aaaa_rrset_, aaaa_rrsig_rrset_, true, limit_len,
                      2);   // 1 main RR, 1 RRSIG

    // RRSIG only case.  Render length limit being 1, so it won't fit,
    // and will cause truncation.
    checkToWireResult(expected_renderer, actual_renderer,
                      *createRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                                   true),
                      name, ConstRRsetPtr(), txt_rrsig_rrset_, true, 1,
                      0);   // no RR
}

void
checkRdataIterator(const vector<string>& expected, RdataIteratorPtr rit) {
    for (vector<string>::const_iterator it = expected.begin();
         it != expected.end();
         ++it)
    {
        ASSERT_FALSE(rit->isLast());
        EXPECT_EQ(*it, rit->getCurrent().toText());
        rit->next();
    }
    // We should have reached the end of RDATA
    EXPECT_TRUE(rit->isLast());

    // move to the first RDATA again, and check the value.
    rit->first();
    if (!expected.empty()) {
        EXPECT_EQ(expected[0], rit->getCurrent().toText());
    } else {
        EXPECT_TRUE(rit->isLast());
    }
}

TEST_F(TreeNodeRRsetTest, getRdataIterator) {
    // This RRset should have 2 A RDATAs
    vector<string> expected;
    expected.push_back("192.0.2.1");
    expected.push_back("192.0.2.2");
    checkRdataIterator(expected,
                       TreeNodeRRset(rrclass_, www_node_, a_rdataset_, true).
                       getRdataIterator());

    // The iterator shouldn't work different with or without RRSIG
    checkRdataIterator(expected,
                       TreeNodeRRset(rrclass_, www_node_, a_rdataset_, false).
                       getRdataIterator());

    // This RRset should have 1 NS RDATA (containing name field)
    expected.clear();
    expected.push_back("ns.example.com.");
    checkRdataIterator(expected,
                       TreeNodeRRset(rrclass_, origin_node_, ns_rdataset_,
                                     false).getRdataIterator());

    // RRSIG only.  Iterator will be empty and shouldn't cause any disruption.
    expected.clear();
    checkRdataIterator(expected,
                       TreeNodeRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                                     true).getRdataIterator());
}

void
checkToText(const AbstractRRset& actual_rrset,
            ConstRRsetPtr expected_rrset, ConstRRsetPtr expected_sig_rrset)
{
    const string actual_text = actual_rrset.toText();
    const string expected_text =
        (expected_rrset ? expected_rrset->toText() : "") +
        (expected_sig_rrset ? expected_sig_rrset->toText() : "");
    EXPECT_EQ(expected_text, actual_text);
}

TEST_F(TreeNodeRRsetTest, toText) {
    // Constructed with RRSIG, and it should be visible.
    checkToText(*createRRset(rrclass_, www_node_, a_rdataset_, true),
                a_rrset_, a_rrsig_rrset_);
    // Same as the previous, but with explicit TTL.
    const uint32_t ttl = 0;
    checkToText(*createRRset(rrclass_, www_node_, a_rdataset_, true, &ttl),
                textToRRset("www.example.com. 0 IN A 192.0.2.1\n"
                            "www.example.com. 0 IN A 192.0.2.2"),
                textToRRset("www.example.com. 0 IN RRSIG A 5 2 3600 "
                            "20120814220826 20120715220826 1234 example.com. "
                            "FAKE"));
    // Constructed with RRSIG, and it should be invisible.
    checkToText(*createRRset(rrclass_, www_node_, a_rdataset_, false),
                a_rrset_, ConstRRsetPtr());
    // Constructed without RRSIG, and it would be visible (but of course won't)
    checkToText(*createRRset(rrclass_, origin_node_, ns_rdataset_, true),
                ns_rrset_, ConstRRsetPtr());
    // Constructed without RRSIG, and it should be visible
    checkToText(*createRRset(rrclass_, origin_node_, ns_rdataset_, false),
                ns_rrset_, ConstRRsetPtr());
    // Wildcard expanded name with RRSIG
    checkToText(*createRRset(match_name_, rrclass_, wildcard_node_,
                             wildcard_rdataset_, true),
                wildmatch_rrset_, wildmatch_rrsig_rrset_);
    // Wildcard expanded name without RRSIG
    checkToText(*createRRset(match_name_, rrclass_, wildcard_node_,
                             wildcard_rdataset_, false),
                wildmatch_rrset_, ConstRRsetPtr());
    // RRSIG case
    checkToText(*createRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                             true),
                ConstRRsetPtr(), txt_rrsig_rrset_);
    // Similar to the previous case, but completely empty.
    checkToText(*createRRset(rrclass_, www_node_, rrsig_only_rdataset_,
                             false),
                ConstRRsetPtr(), ConstRRsetPtr());
}

TEST_F(TreeNodeRRsetTest, isSameKind) {
    const TreeNodeRRset rrset(rrclass_, www_node_, a_rdataset_, true);

    // Same name (node), same type (rdataset) => same kind
    EXPECT_TRUE(rrset.isSameKind(*createRRset(rrclass_, www_node_,
                                              a_rdataset_, true)));

    // Similar to the previous, but with explicit (different TTL) => still same
    const uint32_t ttl = 0;
    EXPECT_TRUE(rrset.isSameKind(*createRRset(rrclass_, www_node_,
                                              a_rdataset_, true, &ttl)));

    // Same name (node), different type (rdataset) => not same kind
    EXPECT_FALSE(rrset.isSameKind(*createRRset(rrclass_, www_node_,
                                               aaaa_rdataset_, true)));

    // Different name, different type => not same kind
    EXPECT_FALSE(rrset.isSameKind(*createRRset(rrclass_, origin_node_,
                                               ns_rdataset_, true)));

    // Different name, same type => not same kind.
    // Note: this shouldn't happen in our in-memory data source implementation,
    // but API doesn't prohibit it.
    EXPECT_FALSE(rrset.isSameKind(*createRRset(rrclass_, origin_node_,
                                               a_rdataset_, true)));

    // Wildcard and expanded RRset
    const TreeNodeRRset wildcard_rrset(rrclass_, wildcard_node_,
                                       wildcard_rdataset_, true);
    const TreeNodeRRset match_rrset(match_name_, rrclass_, wildcard_node_,
                                    wildcard_rdataset_, true);
    EXPECT_FALSE(wildcard_rrset.isSameKind(match_rrset));
    EXPECT_FALSE(match_rrset.isSameKind(wildcard_rrset));

    // Both are wildcard expanded, and have different names
    const TreeNodeRRset match2_rrset(Name("match2.example.com"), rrclass_,
                                     wildcard_node_, wildcard_rdataset_, true);
    EXPECT_FALSE(match_rrset.isSameKind(match2_rrset));
    EXPECT_FALSE(match2_rrset.isSameKind(match_rrset));

    // Pathological case.  "badwild" is constructed as if expanded due to
    // a wildcard, but has the same owner name of the wildcard itself.
    // Technically, they should be considered of the same kind, but this
    // implementation considers they are not.  But this case shouldn't happen
    // as long as the RRsets are only constructed inside the in-memory
    // zone finder implementation.
    const TreeNodeRRset badwild_rrset(wildcard_name_, rrclass_, wildcard_node_,
                                      wildcard_rdataset_, true);
    EXPECT_FALSE(wildcard_rrset.isSameKind(badwild_rrset));
    EXPECT_EQ(wildcard_rrset.toText(), badwild_rrset.toText());

    // Pathological case:  Same name, same type, but different class.
    // This case should be impossible because if the RRsets share the same
    // tree node, they must belong to the same RR class.  This case is
    // a caller's bug, and the isSameKind() implementation returns the
    // "wrong" (= true) answer.
    EXPECT_TRUE(rrset.isSameKind(*createRRset(RRClass::CH(), www_node_,
                                              a_rdataset_, true)));

    // Same kind of different RRset class
    EXPECT_TRUE(rrset.isSameKind(*a_rrset_));

    // Different kind of different RRset class
    EXPECT_FALSE(rrset.isSameKind(*aaaa_rrset_));
}

TEST_F(TreeNodeRRsetTest, unexpectedMethods) {
    // Note: buffer version of toWire() is checked in the toWire test.

    TreeNodeRRset rrset(rrclass_, www_node_, a_rdataset_, true);

    EXPECT_THROW(rrset.setTTL(RRTTL(0)), isc::Unexpected);
    EXPECT_THROW(rrset.addRdata(createRdata(RRType::A(), rrclass_, "0.0.0.0")),
                 isc::Unexpected);
    RdataPtr sig_rdata = createRdata(
        RRType::RRSIG(), rrclass_,
        "A 5 2 3600 20120814220826 20120715220826 5300 example.com. FAKE");
    EXPECT_THROW(rrset.addRRsig(sig_rdata), isc::Unexpected);
    EXPECT_THROW(rrset.addRRsig(*a_rrsig_rrset_), isc::Unexpected);
    EXPECT_THROW(rrset.addRRsig(a_rrsig_rrset_), isc::Unexpected);
    EXPECT_THROW(rrset.addRRsig(RRsetPtr()), isc::Unexpected);
    EXPECT_THROW(rrset.removeRRsig(), isc::Unexpected);
}
}
