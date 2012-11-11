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

// $Id$

#ifndef RESPONSE_CLASSIFIER_H
#define RESPONSE_CLASSIFIER_H

#include <cstddef>

#include <dns/question.h>
#include <dns/message.h>
#include <dns/question.h>

#define RESOLVER_MAX_CNAME_CHAIN    16

namespace isc {
namespace resolve {

/// \brief Classify Server Response
///
/// This class is used in the recursive server.  It is passed an answer received
/// from an upstream server and categorises it.
///
/// TODO: The code here does not take into account any EDNS0 fields.

class ResponseClassifier {
public:

    /// \brief Category of Answer
    ///
    /// In the valid answers, not the distinction between REFERRAL and CNAME.
    /// A REFERRAL answer means that the answer section of the message is
    /// empty, but there is something in the authority section.  A CNAME means
    /// that the answer section contains one or more CNAMES in a chain that
    /// do not end with a non-CNAME RRset.
    enum Category {

        // Codes indicating that a message is valid.

        ANSWER,             ///< Response contains the answer
        ANSWERCNAME,        ///< Response was a CNAME chain ending in an answer
        CNAME,              ///< Response was a CNAME
        NXDOMAIN,           ///< Response was an NXDOMAIN
        NXRRSET,            ///< Response was name exists, but type does not
        REFERRAL,           ///< Response contains a referral

        // Codes indicating that a message is invalid.  Note that the error()
        // method relies on these appearing after the "message valid" codes.

        EMPTY,              ///< No answer or authority sections
        EXTRADATA,          ///< Answer section contains more RRsets than needed
        INVNAMCLASS,        ///< Invalid name or class in answer
        INVTYPE,            ///< Name/class of answer correct, type is wrong
        MISMATQUEST,        ///< Response question section != question
        MULTICLASS,         ///< Multiple classes in multi-RR answer
        NOTONEQUEST,        ///< Not one question in response question section
        NOTRESPONSE,        ///< Response has the Query/Response bit clear
        NOTSINGLE,          ///< CNAME has multiple RDATA elements.
        OPCODE,             ///< Opcode field does not indicate a query
        RCODE,              ///< RCODE indicated an error
        TRUNCATED           ///< Response was truncated
    };

    /// \brief Check Error
    ///
    /// An inline routine to quickly classify whether the return category is
    /// an error or not.  This makes use of internal knowledge of the order of
    /// codes in the Category enum.
    ///
    /// \param code Return category from classify()
    ///
    /// \return true if the category is an error, false if not.
    static bool error(Category code) {
        return (code > REFERRAL);
    }

    /// \brief Classify
    ///
    /// Classify the response in the "message" object.
    ///
    /// \param question Question that was sent to the server
    /// \param message Pointer to the associated response from the server.
    /// \param cname_target If the message contains an (unfinished) CNAME
    /// chain, this Name will be replaced by the target of the last CNAME
    /// in the chain
    /// \param cname_count This unsigned int will be incremented with
    /// the number of CNAMEs followed
    /// \param tcignore If set, the TC bit in a response packet is
    /// ignored.  Otherwise the error code TRUNCATED will be returned.  The
    /// only time this is likely to be used is in development where we are not
    /// going to fail over to TCP and will want to use what is returned, even
    /// if some of the response was lost.
    static Category classify(const isc::dns::Question& question,
            const isc::dns::Message& message, 
            isc::dns::Name& cname_target, unsigned int& cname_count,
            bool tcignore = false);

private:
    /// \brief Follow CNAMEs
    ///
    /// Given a QNAME and an answer section that contains CNAMEs, assume that
    /// they form a CNAME chain and search through them.  Possible outcomes
    /// are:
    ///
    /// a) All CNAMES and they form a chain.  The result is a referral.
    /// b) All but one are CNAMES and they form a chain.  The other is pointed
    ///    to by the last element of the chain and is the correct QTYPE.  The
    ///    result is an answer.
    /// c) Having followed the CNAME chain as far as we can, there is one
    ///    remaining RRset that is of the wrong type, or there are multiple
    ///    RRsets remaining.  return the EXTRADATA code.
    ///
    /// \param qname Question name we are searching for
    /// \param qtype Question type we are search for.  (This is assumed not
    /// to be "ANY".)
    /// \param ansrrset Vector of RRsetPtr pointing to the RRsets we are
    /// considering.
    /// \param present Array of "int" the same size of ansrrset, with each
    /// element set to "1" to allow the corresponding element of ansrrset to
    /// be checked, and "0" to skip it.  This might be premature optimisation,
    /// but the algorithm would otherwise involve duplicating the RRset
    /// vector then removing elements from random positions one by one.  As
    /// each removal involves the destruction of an "xxxPtr" element (which
    /// presently is implemented by boost::shared_ptr), the overhad of memory
    /// management seemed high.  This solution imposes some additional loop
    /// cycles, but that should be minimal compared with the overhead of the
    /// memory management.
    /// \param cname_target If the message contains an (unfinished) CNAME
    /// chain, this Name will be replaced by the target of the last CNAME
    /// in the chain
    /// \param cname_count This unsigned int will be incremented with
    /// the number of CNAMEs followed
    /// \param size Number of elements to check.  See description of \c present
    /// for details.
    static Category cnameChase(const isc::dns::Name& qname,
        const isc::dns::RRType& qtype,
        isc::dns::Name& cname_target, unsigned int& cname_count,
        std::vector<isc::dns::RRsetPtr>& ansrrset, std::vector<int>& present,
        size_t size);
};

} // namespace resolve
} // namespace isc

#endif // RESPONSE_CLASSIFIER_H
