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

#include <cstddef>
#include <vector>

#include <resolve/response_classifier.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrset.h>

using namespace isc::dns;
using namespace std;

namespace isc {
namespace resolve {

// Classify the response in the "message" object.

ResponseClassifier::Category ResponseClassifier::classify(
    const Question& question, const Message& message, 
    Name& cname_target, unsigned int& cname_count, bool tcignore
    )
{
    // Check header bits
    if (!message.getHeaderFlag(Message::HEADERFLAG_QR)) {
        return (NOTRESPONSE);   // Query-response bit not set in the response
    }

    // We only recognise responses to queries here
    if (message.getOpcode() != Opcode::QUERY()) {
        return (OPCODE);
    }

    // Apparently have a response.  There must be a single question in it...
    const vector<QuestionPtr> msgquestion(message.beginQuestion(),
            message.endQuestion());
    if (msgquestion.size() != 1) {
        return (NOTONEQUEST); // Not one question in response question section
    }

    // ... and the question should be equal to the question given.
    // XXX: This means that "question" may not be the question sent by the
    // client.  In the case of a CNAME response, the qname of subsequent
    // questions needs to be altered.
    if (question != *(msgquestion[0])) {
        return (MISMATQUEST);
    }

    // Check for Rcode-related errors.
    const Rcode& rcode = message.getRcode();
    if (rcode != Rcode::NOERROR()) {
        if (rcode == Rcode::NXDOMAIN()) {

            // No such domain.  According to RFC2308, the domain referred to by
            // the QNAME does not exist, although there may be a CNAME in the
            // answer section and there may be an SOA and/or NS RRs in the
            // authority section (ignoring any DNSSEC RRs for now).
            //
            // Note the "may".  There may not be anything.  Also, note that if
            // there is a CNAME in the answer section, the authoritative server
            // has verified that the name given in the CNAME's RDATA field does
            // not exist. And that if a CNAME is returned in the answer, then
            // the QNAME of the RRs in the authority section will refer to the
            // authority for the CNAME's RDATA and not to the original question.
            //
            // Without doing further classification, it is sufficient to say
            // that if an NXDOMAIN is received, there was no translation of the
            // QNAME available.
            return (NXDOMAIN);  // Received NXDOMAIN from parent.

        } else {

            // Not NXDOMAIN but not NOERROR either.  Must be an RCODE-related
            // error.
            return (RCODE);
        }
    }

    // All seems OK and we can start looking at the content.  However, one
    // more header check remains - was the response truncated?  If so, we'll
    // probably want to re-query over TCP.  However, in some circumstances we
    // might want to go with what we have.  So give the caller the option of
    // ignoring the TC bit.
    if (message.getHeaderFlag(Message::HEADERFLAG_TC) && (!tcignore)) {
        return (TRUNCATED);
    }

    // By the time we get here, we're assured that the packet format is correct.
    // We now need to decide as to whether it is an answer, a CNAME, or a
    // referral.  For this, we need to inspect the contents of the answer
    // and authority sections.
    const vector<RRsetPtr> answer(
            message.beginSection(Message::SECTION_ANSWER),
            message.endSection(Message::SECTION_ANSWER)
            );
    const vector<RRsetPtr> authority(
            message.beginSection(Message::SECTION_AUTHORITY),
            message.endSection(Message::SECTION_AUTHORITY)
            );

    // If there is nothing in the answer section, it is a referral - unless
    // there is no NS in the authority section
    if (answer.empty()) {
        if (authority.empty()) {
            return (EMPTY);
        }
        for (vector<RRsetPtr>::size_type i = 0; i < authority.size(); ++i) {
            if (authority[i]->getType() == RRType::NS()) {
                return (REFERRAL);
            }
        }
        return (NXRRSET);
    }

    // Look at two cases - one RRset in the answer and multiple RRsets in
    // the answer.
    if (answer.size() == 1) {

        // Does the name and class of the answer match that of the question?
        if ((answer[0]->getName() == question.getName()) &&
            (answer[0]->getClass() == question.getClass())) {

            // It does.  How about the type of the response?  The response
            // is an answer if the type matches that of the question, or if the
            // question was for type ANY.  It is a CNAME reply if the answer
            // type is CNAME.  And it is an error for anything else.
            if ((answer[0]->getType() == question.getType()) ||
                (question.getType() == RRType::ANY())) {
                return (ANSWER);
            } else if (answer[0]->getType() == RRType::CNAME()) {
                RdataIteratorPtr it = answer[0]->getRdataIterator();
                cname_target = Name(it->getCurrent().toText());
                ++cname_count;
                return (CNAME);
            } else {
                return (INVTYPE);
            }
        }
        else {

            // Either the name and/or class of the reply don't match that of
            // the question.
            return (INVNAMCLASS);
        }
    }

    // There are multiple RRsets in the answer. They should all have the same
    // QCLASS, else there is some error in the response.
    for (vector<RRsetPtr>::size_type i = 1; i < answer.size(); ++i) {
        if (answer[0]->getClass() != answer[i]->getClass()) {
            return (MULTICLASS);
        }
    }

    // If the request type was ANY and they all have the same QNAME, we have
    // an answer.  But if they don't have the same QNAME, we must have an error;
    // the only way we could get different QNAMES in an answer is if one were a
    // CNAME - in which case there should no other record types at that QNAME.
    if (question.getType() == RRType::ANY()) {
        bool all_same = true;
        for (vector<RRsetPtr>::size_type i = 1; (i < answer.size()) && all_same;
             ++i) {
            all_same = (answer[0]->getName() == answer[i]->getName());
        }
        if (all_same) {
            return (ANSWER);
        } else {
            return (EXTRADATA);
        }
    }

    // Multiple RRs in the answer, and not all the same QNAME.  This
    // is either an answer, a CNAME (in either case, there could be multiple
    // CNAMEs in the chain) or an error.
    //
    // So we need to follow the CNAME chain to resolve this.  For this to work:
    //
    // a) There must be one RR that matches the name, class and type of
    //    the question, and this is a CNAME.
    // b) The CNAME chain is followed until the end of the chain does not
    //    exist (answer is a CNAME) or it is not of type CNAME (ANSWER).
    //
    // In the latter case, if there are additional RRs, it must be an error.

    vector<RRsetPtr> ansrrset(answer);
    vector<int> present(ansrrset.size(), 1);
    return cnameChase(question.getName(), question.getType(),
        cname_target, cname_count,
        ansrrset, present, ansrrset.size());
}

// Search the CNAME chain.
ResponseClassifier::Category ResponseClassifier::cnameChase(
    const Name& qname, const RRType& qtype,
    Name& cname_target, unsigned int& cname_count,
    vector<RRsetPtr>& ansrrset, vector<int>& present, size_t size)
{
    // Search through the vector of RRset pointers until we find one with the
    // right QNAME.
    for (vector<RRsetPtr>::size_type i = 0; i < ansrrset.size(); ++i) {
        if (present[i]) {

            // This entry has not been logically removed, so look at it.
            if (ansrrset[i]->getName() == qname) {

                // QNAME match.  If this RRset is a CNAME, remove it from
                // further consideration.  If nothing is left, the end of the
                // chain is a CNAME so this is a CNAME.  Otherwise replace
                // the name with the RDATA of the CNAME and call ourself
                // recursively.
                if (ansrrset[i]->getType() == RRType::CNAME()) {

                    // Don't consider it in the next iteration (although we
                    // can still access it for now).
                    present[i] = 0;
                    --size;
                    if (size == 0) {
                        RdataIteratorPtr it = ansrrset[i]->getRdataIterator();
                        cname_target = Name(it->getCurrent().toText());
                        return (CNAME);
                    } else {
                        if (ansrrset[i]->getRdataCount() != 1) {

                            // Multiple RDATA for a CNAME?  This is invalid.

                            return (NOTSINGLE);
                        }
                        RdataIteratorPtr it = ansrrset[i]->getRdataIterator();
                        Name newname(it->getCurrent().toText());

                        // Increase CNAME count, and continue
                        return cnameChase(newname, qtype, cname_target,
                            ++cname_count, ansrrset, present, size);
                    }

                } else {

                    // We've got here because the element is not a CNAME.  If
                    // this is the last element and the type is the one we are
                    // after, we've found the answer, or it is an error.  If
                    // there is more than one RRset left in the list we are
                    // searching, we have extra data in the answer.
                    if (ansrrset[i]->getType() == qtype) {
                        if (size == 1) {
                            return (ANSWERCNAME);
                        } else {
                            return (EXTRADATA);
                        }
                    }
                    return (INVTYPE);
                }
            }
        }
    }

    // We get here if we've dropped off the end of the list without finding the
    // QNAME we are looking for.  This means that the CNAME chain has ended
    // but there are additional RRsets in the data.

    return (EXTRADATA);
}

} // namespace resolve
} // namespace isc
