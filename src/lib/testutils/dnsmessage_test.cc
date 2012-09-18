// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/message.h>
#include <dns/opcode.h>
#include <dns/rdata.h>
#include <dns/rcode.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <gtest/gtest.h>

#include <testutils/dnsmessage_test.h>

#include <boost/bind.hpp>

#include <string>
#include <sstream>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace testutils {
const unsigned int QR_FLAG = 0x1;
const unsigned int AA_FLAG = 0x2;
const unsigned int TC_FLAG = 0x4;
const unsigned int RD_FLAG = 0x8;
const unsigned int RA_FLAG = 0x10;
const unsigned int AD_FLAG = 0x20;
const unsigned int CD_FLAG = 0x40;

void
headerCheck(const Message& message, const qid_t qid, const Rcode& rcode,
            const uint16_t opcodeval, const unsigned int flags,
            const unsigned int qdcount,
            const unsigned int ancount, const unsigned int nscount,
            const unsigned int arcount)
{
    EXPECT_EQ(qid, message.getQid());
    EXPECT_EQ(rcode, message.getRcode());
    EXPECT_EQ(opcodeval, message.getOpcode().getCode());
    EXPECT_EQ((flags & QR_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_EQ((flags & AA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ((flags & TC_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_EQ((flags & RA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_EQ((flags & RD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_EQ((flags & AD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_EQ((flags & CD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_CD));

    EXPECT_EQ(qdcount, message.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(ancount, message.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(nscount, message.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(arcount, message.getRRCount(Message::SECTION_ADDITIONAL));
}

namespace {
::testing::AssertionResult
matchRdata(const char*, const char*,
           const rdata::Rdata& expected, const rdata::Rdata& actual)
{
    if (expected.compare(actual) != 0) {
        ::testing::Message msg;
        msg << "Two RDATAs are expected to be equal but not:\n"
            << "  Actual: " << actual.toText() << "\n"
            << "Expected: " << expected.toText();
        return (::testing::AssertionFailure(msg));
    }
    return (::testing::AssertionSuccess());
}

// A helper callback of masterLoad() used by textToRRset() below.
void
setRRset(RRsetPtr rrset, RRsetPtr* rrsetp) {
    if (*rrsetp) {
        // may be a sig
        if (rrset->getType() == RRType::RRSIG()) {
            (*rrsetp)->addRRsig(rrset);
        } else {
            isc_throw(isc::Unexpected,
                      "multiple RRsets are given to textToRRset");
        }
    } else {
        *rrsetp = rrset;
    }
}
}

RRsetPtr
textToRRset(const string& text_rrset, const RRClass& rrclass,
            const Name& origin)
{
    stringstream ss(text_rrset);
    RRsetPtr rrset;
    masterLoad(ss, origin, rrclass, boost::bind(setRRset, _1, &rrset));
    return (rrset);
}

void
rrsetCheck(isc::dns::ConstRRsetPtr expected_rrset,
           isc::dns::ConstRRsetPtr actual_rrset)
{
    SCOPED_TRACE("Comparing RRsets\n"
                 "  Actual: " + actual_rrset->toText() +
                 "  Expected: " + expected_rrset->toText());
    EXPECT_EQ(expected_rrset->getName(), actual_rrset->getName());
    EXPECT_EQ(expected_rrset->getClass(), actual_rrset->getClass());
    EXPECT_EQ(expected_rrset->getType(), actual_rrset->getType());
    EXPECT_EQ(expected_rrset->getTTL(), actual_rrset->getTTL());

    isc::dns::RdataIteratorPtr rdata_it = actual_rrset->getRdataIterator();
    isc::dns::RdataIteratorPtr expected_rdata_it =
        expected_rrset->getRdataIterator();
    while (!expected_rdata_it->isLast()) {
        EXPECT_FALSE(rdata_it->isLast());
        if (rdata_it->isLast()) {
            // buggy case, should stop here
            break;
        }

        EXPECT_PRED_FORMAT2(matchRdata, expected_rdata_it->getCurrent(),
                            rdata_it->getCurrent());

        expected_rdata_it->next();
        rdata_it->next();
    }

    // Make sure we have examined all sets of rrset RDATA
    EXPECT_TRUE(rdata_it->isLast());
}
} // end of namespace testutils
} // end of namespace isc
