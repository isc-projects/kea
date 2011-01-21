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

#include <algorithm>
#include <functional>
#include <vector>

#include <dns/message.h>
#include <dns/name.h>
#include <dns/masterload.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

#include <gtest/gtest.h>

namespace isc {
namespace testutils {
// These are flags to indicate whether the corresponding flag bit of the
// DNS header is to be set in the test cases.  (The flag values
// is irrelevant to their wire-format values)
extern const unsigned int QR_FLAG;
extern const unsigned int AA_FLAG;
extern const unsigned int TC_FLAG;
extern const unsigned int RD_FLAG;
extern const unsigned int RA_FLAG;
extern const unsigned int AD_FLAG;
extern const unsigned int CD_FLAG;

void
headerCheck(const isc::dns::Message& message, const isc::dns::qid_t qid,
            const isc::dns::Rcode& rcode,
            const uint16_t opcodeval, const unsigned int flags,
            const unsigned int qdcount,
            const unsigned int ancount, const unsigned int nscount,
            const unsigned int arcount);

void rrsetCheck(isc::dns::ConstRRsetPtr expected_rrset,
                isc::dns::ConstRRsetPtr rrset);

namespace detail {
// Helper matching class
struct RRsetMatch : public std::unary_function<isc::dns::ConstRRsetPtr, bool> {
    RRsetMatch(isc::dns::ConstRRsetPtr target) : target_(target) {}
    bool operator()(isc::dns::ConstRRsetPtr rrset) const {
        return (rrset->getType() == target_->getType() &&
                rrset->getClass() == target_->getClass() &&
                rrset->getName() == target_->getName());
    }
    const isc::dns::ConstRRsetPtr target_;
};

class RRsetInserter {
public:
    RRsetInserter(std::vector<isc::dns::ConstRRsetPtr>& rrsets) :
        rrsets_(rrsets)
    {}
    void operator()(isc::dns::ConstRRsetPtr rrset) const {
        rrsets_.push_back(rrset);
    }
private:
    std::vector<isc::dns::ConstRRsetPtr>& rrsets_;
};
}

template<typename EXPECTED_ITERATOR, typename ACTUAL_ITERATOR>
void
rrsetsCheck(EXPECTED_ITERATOR expected_begin, EXPECTED_ITERATOR expected_end,
            ACTUAL_ITERATOR actual_begin, ACTUAL_ITERATOR actual_end)
{
    unsigned int rrset_matched = 0;
    unsigned int rrset_count = 0;
    ACTUAL_ITERATOR it;
    for (it = actual_begin; it != actual_end; ++it) {
        std::vector<isc::dns::ConstRRsetPtr>::const_iterator found_rrset_it =
            find_if(expected_begin, expected_end, detail::RRsetMatch(*it));
        if (found_rrset_it != expected_end) {
            rrsetCheck(*found_rrset_it, *it);
            ++rrset_matched;
        }
        ++rrset_count;
    }

    // make sure all expected RRsets are in rrsets
    EXPECT_EQ(distance(expected_begin, expected_end), rrset_matched);
    // make sure rrsets only contains expected RRsets
    EXPECT_EQ(distance(expected_begin, expected_end), rrset_count);
}

template <typename EXPECTED_CONTAINER, typename ACTUAL_CONTAINER>
void
rrsetsCheck(EXPECTED_CONTAINER& expected_rrsets,
            ACTUAL_CONTAINER& actual_rrsets)
{
    rrsetsCheck(expected_rrsets.begin(), expected_rrsets.end(),
                actual_rrsets.begin(), actual_rrsets.end());
}

template<typename ACTUAL_ITERATOR>
void
rrsetsCheck(std::istream& expected_stream,
            ACTUAL_ITERATOR actual_begin, ACTUAL_ITERATOR actual_end,
            const isc::dns::Name& origin = isc::dns::Name::ROOT_NAME(),
            const isc::dns::RRClass& rrclass = isc::dns::RRClass::IN())
{
    std::vector<isc::dns::ConstRRsetPtr> expected;
    isc::dns::masterLoad(expected_stream, origin, rrclass,
                         detail::RRsetInserter(expected));
    rrsetsCheck(expected.begin(), expected.end(), actual_begin, actual_end);
}
} // end of namespace testutils
} // end of namespace isc

// Local Variables:
// mode: c++
// End:
