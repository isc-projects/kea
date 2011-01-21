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

/// Set of unit tests to check equality of two RRsets
///
/// This function takes two RRset objects and performs detailed tests to
/// check if these two are "equal", where equal means:
/// - The owner name, RR class, RR type and TTL are all equal.  Names are
///   compared in case-insensitive manner.
/// - The number of RRs (more accurately RDATAs) is the same.
/// - RDATAs are equal as a sequence.  That is, the first RDATA of
///   \c expected_rrset is equal to the first RDATA of \c actual_rrset,
///   the second RDATA of \c expected_rrset is equal to the second RDATA
///   of \c actual_rrset, and so on.  Two RDATAs are equal iff they have
///   the same DNSSEC sorting order as defined in RFC4034.
///
/// Some of the tests will fail if any of the above isn't met.
///
/// \note In future we may want to allow more flexible matching for RDATAs.
/// For example, we may want to allow comparison as "sets", i.e., comparing
/// RDATAs regardless of the ordering; we may also want to support suppressing
/// duplicate RDATA.  For now, it's caller's responsibility to match the
/// ordering (and any duplicates) between the expected and actual sets.
/// Even if and when we support the flexible behavior, this "strict mode"
/// will still be useful.
///
/// \param expected_rrset The expected RRset
/// \param actual_rrset The RRset to be tested
void rrsetCheck(isc::dns::ConstRRsetPtr expected_rrset,
                isc::dns::ConstRRsetPtr actual_rrset);

/// The definitions in this name space are not supposed to be used publicly,
/// but are given here because they are used in templated functions.
namespace detail {
// Helper matching class used in rrsetsCheck()
struct RRsetMatch : public std::unary_function<isc::dns::ConstRRsetPtr, bool> {
    RRsetMatch(isc::dns::ConstRRsetPtr target) : target_(target) {}
    bool operator()(isc::dns::ConstRRsetPtr rrset) const {
        return (rrset->getType() == target_->getType() &&
                rrset->getClass() == target_->getClass() &&
                rrset->getName() == target_->getName());
    }
    const isc::dns::ConstRRsetPtr target_;
};

// Helper callback functor for masterLoad() used in rrsetsCheck (stream
// version)
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

/// Set of unit tests to check if two sets of RRsets are identical.
///
/// This templated function takes two sets of sequences, each defined by
/// two input iterators pointing to \c ConstRRsetPtr (begin and end).
/// This function compares these two sets of RRsets as "sets", and considers
/// they are equal when:
/// - The number of RRsets are the same.
/// - For any RRset in one set, there is an equivalent RRset in the other set,
///   and vice versa, where the equivalence of two RRsets is tested using
///   \c rrsetCheck().
///
/// Note that the sets of RRsets are compared as "sets", i.e, they don't have
/// to be listed in the same order.
/// There is one known restriction: each set of RRsets must not have more
/// then one RRsets for the same name, RR type and RR class.  If this
/// condition isn't met, this function will be confused and produce
/// meaningless results.
///
/// The entire tests will pass if the two sets are identical.  Otherwise
/// some of the tests will indicate a failure.
///
/// \param expected_begin The beginning of the expected set of RRsets
/// \param expected_end The end of the expected set of RRsets
/// \param actual_begin The beginning of the set of RRsets to be tested
/// \param actual_end The end of the set of RRsets to be tested
template<typename EXPECTED_ITERATOR, typename ACTUAL_ITERATOR>
void
rrsetsCheck(EXPECTED_ITERATOR expected_begin, EXPECTED_ITERATOR expected_end,
            ACTUAL_ITERATOR actual_begin, ACTUAL_ITERATOR actual_end)
{
    unsigned int rrset_matched = 0;
    unsigned int rrset_count = 0;
    ACTUAL_ITERATOR it;
    for (it = actual_begin; it != actual_end; ++it) {
        EXPECTED_ITERATOR found_rrset_it =
            find_if(expected_begin, expected_end, detail::RRsetMatch(*it));
        if (found_rrset_it != expected_end) {
            rrsetCheck(*found_rrset_it, *it);
            ++rrset_matched;
        }
        ++rrset_count;
    }

    // make sure all expected RRsets are in actual sets
    EXPECT_EQ(std::distance(expected_begin, expected_end), rrset_matched);
    // make sure rrsets only contains expected RRsets
    EXPECT_EQ(std::distance(expected_begin, expected_end), rrset_count);
}

/// Set of unit tests to check if two sets of RRsets are identical using
/// streamed expected data.
///
/// This templated function takes a standard input stream that produces
/// a sequence of textural RRs and compares the entire set of RRsets
/// with the range of RRsets specified by two input iterators.
///
/// This function is actually a convenient wrapper for the other version
/// of function; it internally builds a standard vector of RRsets
/// from the input stream and uses iterators of the vector as the expected
/// input iterators for the backend function.
/// Expected data in the form of input stream would be useful for testing
/// as it can be easily hardcoded in test cases using string streams or
/// given from a data source file.
///
/// One common use case of this function is to test whether a particular
/// section of a DNS message contains an expected set of RRsets.
/// For example, when \c message is an \c dns::Message object, the following
/// test code will check if the additional section of \c message contains
/// the hardcoded two RRsets (2 A RRs and 1 AAAA RR) and only contains these
/// RRsets:
/// \code std::stringstream expected;
/// expected << "foo.example.com. 3600 IN A 192.0.2.1\n"
///          << "foo.example.com. 3600 IN A 192.0.2.2\n"
///          << "foo.example.com. 7200 IN AAAA 2001:db8::1\n"
/// rrsetsCheck(expected, message.beginSection(Message::SECTION_ADDITIONAL),
///                       message.endSection(Message::SECTION_ADDITIONAL));
/// \endcode
///
/// The input stream is parsed using the \c dns::masterLoad() function,
/// and notes and restrictions of that function apply.
/// This is also the reason why this function takes \c origin and \c rrclass
/// parameters.  The default values of these parameters should just work
/// in many cases for usual tests, but due to a validity check on the SOA RR
/// in \c dns::masterLoad(), if the input stream contains an SOA RR, the
/// \c origin parameter will have to be set to the owner name of the SOA
/// explicitly.  Likewise, all RRsets must have the same RR class.
/// (We may have to modify \c dns::masterLoad() so that it can
/// have an option to be more generous about these points if it turns out
/// to be too restrictive).
///
/// \param expected_stream An input stream object that is to emit expected set
/// of RRsets
/// \param actual_begin The beginning of the set of RRsets to be tested
/// \param actual_end The end of the set of RRsets to be tested
/// \param origin A domain name that is a super domain of the owner name
/// of all RRsets contained in the stream.
/// \param rrclass The RR class of the RRsets contained in the stream.
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
