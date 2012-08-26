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

#ifndef __ISC_TESTUTILS_DNSMESSAGETEST_H
#define __ISC_TESTUTILS_DNSMESSAGETEST_H 1

#include <algorithm>
#include <functional>
#include <iosfwd>
#include <string>
#include <vector>

#include <dns/message.h>
#include <dns/name.h>
#include <dns/masterload.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

#include <gtest/gtest.h>

namespace isc {
namespace testutils {
///
/// \name Header flags
///
/// These are flags to indicate whether the corresponding flag bit of the
/// DNS header is to be set in the test cases using \c headerCheck().
/// (The flag values is irrelevant to their wire-format values).
/// The meaning of the flags should be obvious from the variable names.
//@{
extern const unsigned int QR_FLAG;
extern const unsigned int AA_FLAG;
extern const unsigned int TC_FLAG;
extern const unsigned int RD_FLAG;
extern const unsigned int RA_FLAG;
extern const unsigned int AD_FLAG;
extern const unsigned int CD_FLAG;
//@}

/// Set of unit tests to examine a DNS message header.
///
/// This function takes a dns::Message object and performs various tests
/// to confirm if the header fields of the message have the given specified
/// value.  The \c message parameter is the Message object to be tested,
/// and the remaining parameters specify the expected values of the fields.
///
/// If all fields have the expected values the test will be considered
/// successful.  Otherwise, some of the tests will indicate a failure, which
/// will make the test case that calls this function fail.
///
/// The meaning of the parameters should be obvious, but here are some notes
/// that may not be so trivial:
/// - \c opcode is an integer, not an \c dns::Opcode object.  This is because
///   we can easily iterate over all possible OPCODEs in a test.
/// - \c flags is a bitmask so that we can specify a set of header flags
///   via a single parameter.  For example, when we expect the message has
///   QR and AA flags are on and others are off, we'd set this parameter to
///   <code>(QR_FLAG | AA_FLAG)</code>.
///
/// \param message The DNS message to be tested.
/// \param qid The expected QID
/// \param rcode The expected RCODE
/// \param opcodeval The code value of the expected OPCODE
/// \param flags Bit flags specifying header flags that are expected to be set
/// \param qdcount The expected value of QDCOUNT
/// \param ancount The expected value of ANCOUNT
/// \param nscount The expected value of NSCOUNT
/// \param arcount The expected value of ARCOUNT
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
// Helper matching class used in rrsetsCheck().  Basically we only have to
// check the equality of name, RR type and RR class, but for RRSIGs we need
// special additional checks because they are essentially different if their
// 'type covered' are different.  For simplicity, we only compare the types
// of the first RRSIG RDATAs (and only check when they exist); if there's
// further difference in the RDATA, the main comparison checks will detect it.
struct RRsetMatch : public std::unary_function<isc::dns::ConstRRsetPtr, bool> {
    RRsetMatch(isc::dns::ConstRRsetPtr target) : target_(target) {}
    bool operator()(isc::dns::ConstRRsetPtr rrset) const {
        if (rrset->getType() != target_->getType() ||
            rrset->getClass() != target_->getClass() ||
            rrset->getName() != target_->getName()) {
            return (false);
        }
        if (rrset->getType() != isc::dns::RRType::RRSIG()) {
            return (true);
        }
        if (rrset->getRdataCount() == 0 || target_->getRdataCount() == 0) {
            return (true);
        }
        isc::dns::RdataIteratorPtr rdit = rrset->getRdataIterator();
        isc::dns::RdataIteratorPtr targetit = target_->getRdataIterator();
        return (dynamic_cast<const isc::dns::rdata::generic::RRSIG&>(
                    rdit->getCurrent()).typeCovered() ==
                dynamic_cast<const isc::dns::rdata::generic::RRSIG&>(
                    targetit->getCurrent()).typeCovered());
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

class RRsetDumper {
public:
    RRsetDumper(std::string& output) :
        output_(output)
    {}
    void operator()(isc::dns::ConstRRsetPtr rrset) {
        output_ += "  " + rrset->toText();

        if (rrset->getRRsig()) {
            output_ += "  " + rrset->getRRsig()->toText();
        }
    }
private:
    std::string& output_;
};
}

/// \brief A converter from a string to RRset.
///
/// This is a convenient shortcut for tests that need to create an RRset
/// from textual representation with a single call to a function.
///
/// An RRset consisting of multiple RRs can be constructed, but only one
/// RRset is allowed.  If the given string contains mixed types of RRs
/// it throws an \c isc::Unexpected exception.
///
/// \param text_rrset A complete textual representation of an RRset.
///  It must meets the assumption of the \c dns::masterLoad() function.
/// \param rrclass The RR class of the RRset.  Note that \c text_rrset should
/// contain the RR class, but it's needed for \c dns::masterLoad().
/// \param origin The zone origin where the RR is expected to belong.  This
/// parameter normally doesn't have to be specified, but for an SOA RR it
/// must be set to its owner name, due to the internal check of
/// \c dns::masterLoad().
isc::dns::RRsetPtr textToRRset(const std::string& text_rrset,
                               const isc::dns::RRClass& rrclass =
                               isc::dns::RRClass::IN(),
                               const isc::dns::Name& origin =
                               isc::dns::Name::ROOT_NAME());

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
///
/// The entire tests will pass if the two sets are identical.  Otherwise
/// some of the tests will indicate a failure.
///
/// \note
/// - There is one known restriction: each set of RRsets must not have more
///   than one RRsets for the same name, RR type and RR class.  If this
///   condition isn't met, some of the tests will fail either against an
///   explicit duplication check or as a result of counter mismatch.
/// - This function uses linear searches on the expected and actual sequences,
///   and won't be scalable for large input.  For the purpose of testing it
///   should be acceptable, but be aware of the size of test data.
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
    std::vector<isc::dns::ConstRRsetPtr> checked_rrsets; // for duplicate check
    std::string expected_text, actual_text;
    std::for_each(expected_begin, expected_end,
                  detail::RRsetDumper(expected_text));
    std::for_each(actual_begin, actual_end, detail::RRsetDumper(actual_text));
    unsigned int rrset_matched = 0;
    ACTUAL_ITERATOR it;
    for (it = actual_begin; it != actual_end; ++it) {
        // Make sure there's no duplicate RRset in actual (using a naive
        // search).  Since the actual set is guaranteed to be unique, we can
        // detect it if the expected data has a duplicate by the match/size
        // checks at the end of the function.
        // Note: we cannot use EXPECT_EQ for iterators
        EXPECT_TRUE(checked_rrsets.end() ==
                    std::find_if(checked_rrsets.begin(), checked_rrsets.end(),
                                 detail::RRsetMatch(*it)));
        checked_rrsets.push_back(*it);

        EXPECTED_ITERATOR found_rrset_it =
            std::find_if(expected_begin, expected_end,
                         detail::RRsetMatch(*it));
        if (found_rrset_it != expected_end) {
            rrsetCheck(*found_rrset_it, *it);
            ++rrset_matched;
            rrset_matched += (*it)->getRRsigDataCount();
        }
    }

    {
        SCOPED_TRACE(std::string("Comparing two RRsets:\n") +
                     "Actual:\n" + actual_text +
                     "Expected:\n" + expected_text);
        // make sure all expected RRsets are in actual sets
        EXPECT_EQ(std::distance(expected_begin, expected_end), rrset_matched);

#if (0)
        // TODO: see bug #2223. The following code was
        // disabled by #2165. The RRSIG RRsets are no longer directly
        // stored in the Message's rrsets, so the iterator will not find
        // them. The expected text used in many tests are flattened,
        // where the RRSIGs are inline. In other words, RRSIGs may occur
        // between (expected_begin, expected_end) but not between
        // (actual_begin, actual_end).

        // make sure rrsets only contains expected RRsets
        EXPECT_EQ(std::distance(expected_begin, expected_end),
                  std::distance(actual_begin, actual_end));
#endif
    }
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

/// Set of unit tests to check if two sets of RRsets are identical using
/// expected data as string.
///
/// This function is a wrapper for the input stream version:
/// \c rrsetsCheck(std::istream&, ACTUAL_ITERATOR, ACTUAL_ITERATOR, const isc::dns::Name&, const isc::dns::RRClass&)(),
/// and takes a string object instead of a stream.
/// While the stream version is more generic, this version would be more
/// convenient for tests using hardcoded expected data.  Using this version,
/// the example test case shown for the stream version would look as follows:
/// \code
/// rrsetsCheck("foo.example.com. 3600 IN A 192.0.2.1\n"
///             "foo.example.com. 3600 IN A 192.0.2.2\n"
///             "foo.example.com. 7200 IN AAAA 2001:db8::1\n",
///             message.beginSection(Message::SECTION_ADDITIONAL),
///             message.endSection(Message::SECTION_ADDITIONAL));
/// \endcode
///
/// The semantics of parameters is the same as that of the stream version
/// except that \c expected is a string of expected sets of RRsets.
template<typename ACTUAL_ITERATOR>
void
rrsetsCheck(const std::string& expected,
            ACTUAL_ITERATOR actual_begin, ACTUAL_ITERATOR actual_end,
            const isc::dns::Name& origin = isc::dns::Name::ROOT_NAME(),
            const isc::dns::RRClass& rrclass = isc::dns::RRClass::IN())
{
    std::stringstream expected_stream(expected);
    rrsetsCheck(expected_stream, actual_begin, actual_end, origin,
                rrclass);
}

} // end of namespace testutils
} // end of namespace isc
#endif  // __ISC_TESTUTILS_DNSMESSAGETEST_H

// Local Variables:
// mode: c++
// End:
