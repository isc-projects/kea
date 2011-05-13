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

#include <iostream>
#include <vector>
#include <dns/message.h>
#include <dns/rrset.h>
#include <dns/name.h>
#include "response_scrubber.h"

using namespace isc::dns;
using namespace std;

// Compare addresses etc.

ResponseScrubber::Category ResponseScrubber::addressCheck(
    const isc::asiolink::IOEndpoint& to, const isc::asiolink::IOEndpoint& from)
{
    if (from.getProtocol() == to.getProtocol()) {
        if (from.getAddress() == to.getAddress()) {
            if (from.getPort() == to.getPort()) {
                return (ResponseScrubber::SUCCESS);
            } else {
                return (ResponseScrubber::PORT);
            }
        } else {
            return (ResponseScrubber::ADDRESS);
        }
    }
    return (ResponseScrubber::PROTOCOL);
}

// Do a general scrubbing.  The QNAMES of RRsets in the specified section are
// compared against the list of name given and if they are not equal and not in
// the specified relationship (generally superdomain or subdomain) to at least
// of of the given names, they are removed.

unsigned int
ResponseScrubber::scrubSection(Message& message,
    const vector<const Name*>& names,
    const NameComparisonResult::NameRelation connection,
    const Message::Section section)
{
    unsigned int count = 0;     // Count of RRsets removed
    unsigned int kept = 0;      // Count of RRsets kept
    bool removed = true;        // Set true if RRset removed in a pass

    // Need to go through the section multiple times as when an RRset is
    // removed, all iterators into the section are invalidated.  This condition
    // is flagged by "remove" being set true when an RRset is removed.

    while (removed) {
        RRsetIterator i = message.beginSection(section);

        // Skips the ones that have been checked (and retained) in a previous
        // pass through the "while" loop.  (Although RRset removal invalidates
        // iterators, it does not change the relative order of the retained
        // RRsets in the section.)
        for (int j = 0; j < kept; ++j) {
            ++i;
        }

        // Start looking at the remaining entries in the section.
        removed = false;
        for (; i != message.endSection(section); ++i) {

            // Loop through the list of names given and see if any are in the
            // given relationship with the QNAME of this RRset
            bool match = false;
            for (vector<const Name*>::const_iterator n = names.begin();
                 n != names.end(); ++n) {
                NameComparisonResult result = (*i)->getName().compare(**n);
                NameComparisonResult::NameRelation relationship =
                    result.getRelation();
                if ((relationship == NameComparisonResult::EQUAL) ||
                   (relationship == connection)) {

                    // RRset in the specified relationship, so a match has
                    // been found
                    match = true;
                    break;
                }
            }

            // Remove the RRset if there was no match to one of the given names.
            if (!match) {
                message.removeRRset(section, i);
                ++count;            // One more RRset removed
                removed = true;     // Something was removed
                break; // It invalidated the iterators, start again
             } else {

                // There was a match so this is one more entry we can skip next
                // time.
                ++kept;
             }
        }
    }

    return (count);
}

// Perform the scrubbing of all sections of the message.

unsigned int
ResponseScrubber::scrubAllSections(Message& message, const Name& bailiwick) {

    // Leave the question section alone.  Just go through the RRsets in the
    // answer, authority and additional sections.
    unsigned int count = 0;
    const vector<const Name*> bailiwick_names(1, &bailiwick);
    count += scrubSection(message, bailiwick_names,
            NameComparisonResult::SUBDOMAIN, Message::SECTION_ANSWER);
    count += scrubSection(message, bailiwick_names,
            NameComparisonResult::SUBDOMAIN, Message::SECTION_AUTHORITY);
    count += scrubSection(message, bailiwick_names,
            NameComparisonResult::SUBDOMAIN, Message::SECTION_ADDITIONAL);

    return (count);
}

// Scrub across sections.

unsigned int
ResponseScrubber::scrubCrossSections(isc::dns::Message& message) {

    // Get a list of the names in the answer section or, failing this, the
    // question section.  Note that pointers to the names within "message" are
    // stored; this is OK as the relevant sections in "message" will not change
    // during the lifetime of this method (it only affects the authority
    // section).
    vector<const Name*> source;
    if (message.getRRCount(Message::SECTION_ANSWER) != 0) {
        for (RRsetIterator i = message.beginSection(Message::SECTION_ANSWER);
            i != message.endSection(Message::SECTION_ANSWER); ++i) {
            const Name& qname = (*i)->getName();
            source.push_back(&qname);
        }

    } else {
        for (QuestionIterator i = message.beginQuestion();
            i != message.endQuestion(); ++i) {
            const Name& qname = (*i)->getName();
            source.push_back(&qname);
        }
    }

    if (source.empty()) {
        // TODO: Log the fact - should be at least a question present
        return (0);
    }

    // Could be duplicates, especially in the answer section, so sort the
    // names and remove them.
    sort(source.begin(), source.end(), ResponseScrubber::compareNameLt);
    vector<const Name*>::iterator endunique =
        unique(source.begin(), source.end(), ResponseScrubber::compareNameEq);
    source.erase(endunique, source.end());

    // Now purge the authority section of RRsets that are not equal to or a
    // superdomain of the names in the question/answer section.
    return (scrubSection(message, source,
        NameComparisonResult::SUPERDOMAIN, Message::SECTION_AUTHORITY));
}

// Scrub a message

unsigned int
ResponseScrubber::scrub(const isc::dns::MessagePtr& message,
    const isc::dns::Name& bailiwick)
{
    unsigned int sections_removed = scrubAllSections(*message, bailiwick);
    sections_removed += scrubCrossSections(*message);

    return (sections_removed);
}


