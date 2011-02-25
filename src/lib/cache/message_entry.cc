// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <limits>
#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include "message_entry.h"
#include "rrset_cache.h"

using namespace isc::dns;
using namespace std;

namespace isc {
namespace cache {

static uint32_t MAX_UINT32 = numeric_limits<uint32_t>::max();

MessageEntry::MessageEntry(const isc::dns::Message& msg,
                           boost::shared_ptr<RRsetCache> rrset_cache):
    rrset_cache_(rrset_cache),
    headerflag_aa_(false),
    headerflag_tc_(false)
{
    initMessageEntry(msg);
    entry_name_ = genCacheEntryName(query_name_, query_type_);
    hash_key_ptr_ = new HashKey(entry_name_, RRClass(query_class_));
}

bool
MessageEntry::getRRsetEntries(vector<RRsetEntryPtr>& rrset_entry_vec,
                              const time_t time_now)
{
    uint16_t entry_count = answer_count_ + authority_count_ + additional_count_;
    rrset_entry_vec.reserve(rrset_entry_vec.size() + entry_count);
    for (int index = 0; index < entry_count; ++index) {
        RRsetEntryPtr rrset_entry = rrset_cache_->lookup(rrsets_[index].name_,
                                                        rrsets_[index].type_);
        if (time_now < rrset_entry->getExpireTime()) {
            rrset_entry_vec.push_back(rrset_entry);
        } else {
            return (false);
        }
    }

    return (true);
}

void
MessageEntry::addRRset(isc::dns::Message& message,
                       const vector<RRsetEntryPtr>& rrset_entry_vec,
                       const isc::dns::Message::Section& section,
                       bool dnssec_need)
{
    uint16_t start_index = 0;
    uint16_t end_index = answer_count_;
    assert(section != Message::SECTION_QUESTION);

    if (section == Message::SECTION_AUTHORITY) {
        start_index = answer_count_;
        end_index = answer_count_ + authority_count_;
    } else if (section == Message::SECTION_ADDITIONAL) {
        start_index = answer_count_ + authority_count_;
        end_index = start_index + additional_count_;
    }

    for(uint16_t index = start_index; index < end_index; ++index) {
        message.addRRset(section, rrset_entry_vec[index]->getRRset(), dnssec_need);
    }
}

bool
MessageEntry::genMessage(const time_t& time_now,
                         isc::dns::Message& msg)
{
    if (time_now >= expire_time_) {
        // The message entry has expired.
        return (false);
    } else {
        // Before do any generation, we should check if some rrset
        // has expired, if it is, return false.
        vector<RRsetEntryPtr> rrset_entry_vec;
        if (false == getRRsetEntries(rrset_entry_vec, time_now)) {
            return (false);
        }

        // Begin message generation. We don't need to add question
        // section, since it has been included in the message.
        // Set cached header flags.
        msg.setHeaderFlag(Message::HEADERFLAG_AA, headerflag_aa_);
        msg.setHeaderFlag(Message::HEADERFLAG_TC, headerflag_tc_);

        bool dnssec_need = msg.getEDNS().get();
        addRRset(msg, rrset_entry_vec, Message::SECTION_ANSWER, dnssec_need);
        addRRset(msg, rrset_entry_vec, Message::SECTION_AUTHORITY, dnssec_need);
        addRRset(msg, rrset_entry_vec, Message::SECTION_ADDITIONAL, dnssec_need);

        return (true);
    }
}

// Get the deepest owner name of DNAME record for the given query name.
static Name
getDeepestDNAMEOwner(const Message& message, const Name& query_name) {
    Name dname = query_name;
    RRsetIterator rrset_iter = message.beginSection(Message::SECTION_ANSWER);
    while(rrset_iter != message.endSection(Message::SECTION_ANSWER)) {
        if ((*rrset_iter)->getType() == RRType::DNAME()) {
            const Name& rrname = (*rrset_iter)->getName();
            if (NameComparisonResult::SUBDOMAIN ==
                dname.compare(rrname).getRelation()) {
                dname = rrname;
            }
        }
        ++rrset_iter;
    }

    return dname;
}

// Check whether answer section in given message has non-authoritative rrsets.
static bool
answerHasNonAuthRecord(const Message& message, const Name& query_name) {
    RRsetIterator rrset_iter = message.beginSection(Message::SECTION_ANSWER);
    while(rrset_iter != message.endSection(Message::SECTION_ANSWER)) {
        // Here, only check CNAME is enough. If there is
        // cname record whose ower name is same with query name, answer
        // section may has non-authoritative rrsets.
        if ((*rrset_iter)->getType() == RRType::CNAME() &&
            (*rrset_iter)->getName() == query_name) {
            return true;
        }
        ++rrset_iter;
    }
    return false;
}

RRsetTrustLevel
MessageEntry::getRRsetTrustLevel(const Message& message,
    const isc::dns::RRsetPtr& rrset,
    const isc::dns::Message::Section& section)
{
    bool aa = message.getHeaderFlag(Message::HEADERFLAG_AA);
    switch(section) {
        case Message::SECTION_ANSWER: {
            if (aa) {
                // According RFC2181 section 5.4.1, only the record
                // describing that ailas is necessarily authoritative.
                // If there are CNAME(Not synchronized from DNAME)
                // records in answer section, only the CNAME record
                // whose owner name is same with qname is assumed as
                // authoritative, all the left records are not authoritative.
                //
                // If there are DNAME records in answer section,
                // Only the start DNAME and the synchronized CNAME record
                // from it are authoritative, any other records in answer
                // section are non-authoritative.
                QuestionIterator quest_iter = message.beginQuestion();
                const Name& query_name = (*quest_iter)->getName();
                const RRType& type = rrset->getType();
                const Name& name = rrset->getName();
                if ((type == RRType::CNAME() && name == query_name) ||
                    (type == RRType::DNAME() &&
                     name == getDeepestDNAMEOwner(message, query_name))) {
                    return RRSET_TRUST_ANSWER_AA;
                } else if (answerHasNonAuthRecord(message, query_name)) {
                    return RRSET_TRUST_ANSWER_NONAA;
                }

                return (RRSET_TRUST_ANSWER_AA);
            } else {
                return (RRSET_TRUST_ANSWER_NONAA);
            }
            break;
        }

        case Message::SECTION_AUTHORITY: {
            if (aa) {
                return (RRSET_TRUST_AUTHORITY_AA);
            } else {
                return (RRSET_TRUST_AUTHORITY_NONAA);
            }
            break;
        }

        case Message::SECTION_ADDITIONAL: {
            if (aa) {
                return (RRSET_TRUST_ADDITIONAL_AA);
            } else {
                return (RRSET_TRUST_ADDITIONAL_NONAA);
            }
            break;
        }

        default:
            return (RRSET_TRUST_DEFAULT);
    }
}

void
MessageEntry::parseSection(const isc::dns::Message& msg,
                         const Message::Section& section,
                         uint32_t& smaller_ttl,
                         uint16_t& rrset_count)
{
    RRsetIterator iter;
    int count = 0;
    for (iter = msg.beginSection(section);
         iter != msg.endSection(section);
         ++iter) {
        // Add the rrset entry to rrset_cache or update the existed
        // rrset entry if the new one is more authoritative.
        //TODO set proper rrset trust level.
        RRsetPtr rrset_ptr = *iter;
        RRsetTrustLevel level = getRRsetTrustLevel(msg, rrset_ptr, section);
        RRsetEntryPtr rrset_entry = rrset_cache_->update(*rrset_ptr, level);
        rrsets_.push_back(RRsetRef(rrset_ptr->getName(), rrset_ptr->getType()));

        uint32_t rrset_ttl = rrset_entry->getTTL();
        if (smaller_ttl > rrset_ttl) {
            smaller_ttl = rrset_ttl;
        }

        count++;
    }

    rrset_count = count;
}

void
MessageEntry::initMessageEntry(const isc::dns::Message& msg) {
    //TODO better way to cache the header flags?
    headerflag_aa_ = msg.getHeaderFlag(Message::HEADERFLAG_AA);
    headerflag_tc_ = msg.getHeaderFlag(Message::HEADERFLAG_TC);

    // We only cache the first question in question section.
    // TODO, do we need to support muptiple questions?
    query_count_ = 1;
    QuestionIterator iter = msg.beginQuestion();
    query_name_ = (*iter)->getName().toText();
    query_type_ = (*iter)->getType().getCode();
    query_class_ = (*iter)->getClass().getCode();

    uint32_t min_ttl = MAX_UINT32;
    parseSection(msg, Message::SECTION_ANSWER, min_ttl, answer_count_);
    parseSection(msg, Message::SECTION_AUTHORITY, min_ttl, authority_count_);
    parseSection(msg, Message::SECTION_ADDITIONAL, min_ttl, additional_count_);

    expire_time_ = time(NULL) + min_ttl;
}

} // namespace cache
} // namespace isc


