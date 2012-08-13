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
#include "message_utility.h"
#include "rrset_cache.h"
#include "logger.h"

using namespace isc::dns;
using namespace std;

// Put file scope functions in unnamed namespace.
namespace {

// Get the shortest existing ancestor which is the owner name of
// one DNAME record for the given query name.
// Note: there may be multiple DNAME records(DNAME chain) in answer
// section. In most cases they are in order, but the code can't depend
// on that, it has to find the starter by iterating the DNAME chain.
Name
getDNAMEChainStarter(const Message& message, const Name& query_name) {
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

    return (dname);
}

} // End of unnamed namespace

namespace isc {
namespace cache {

static uint32_t MAX_UINT32 = numeric_limits<uint32_t>::max();

// As with caching positive responses it is sensible for a resolver to
// limit for how long it will cache a negative response as the protocol
// supports caching for up to 68 years.  Such a limit should not be
// greater than that applied to positive answers and preferably be
// tunable.  Values of one to three hours have been found to work well
// and would make sensible a default.  Values exceeding one day have
// been found to be problematic. (sec 5, RFC2308)
// The default value is 3 hours (10800 seconds)
// TODO:Give an option to let user configure
static uint32_t MAX_NEGATIVE_CACHE_TTL = 10800;

// Sets the maximum time for which the server will cache ordinary (positive) answers. The
// default is one week (7 days = 604800 seconds)
// TODO:Give an option to let user configure
static uint32_t MAX_NORMAL_CACHE_TTL = 604800;

MessageEntry::MessageEntry(const isc::dns::Message& msg,
                           const RRsetCachePtr& rrset_cache,
                           const RRsetCachePtr& negative_soa_cache):
    rrset_cache_(rrset_cache),
    negative_soa_cache_(negative_soa_cache),
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
        RRsetCache* rrset_cache = rrsets_[index].cache_;
        RRsetEntryPtr rrset_entry = rrset_cache->lookup(rrsets_[index].name_,
                                                        rrsets_[index].type_);
        if (rrset_entry && time_now < rrset_entry->getExpireTime()) {
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
                       const isc::dns::Message::Section& section)
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

    for (uint16_t index = start_index; index < end_index; ++index) {
        message.addRRset(section, rrset_entry_vec[index]->getRRset());
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
            LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_ENTRY_MISSING_RRSET).
                arg(entry_name_);
            return (false);
        }

        // Begin message generation. We don't need to add question
        // section, since it has been included in the message.
        // Set cached header flags.
        // The AA flag bit should be cleared because this is a response from
        // resolver cache
        msg.setHeaderFlag(Message::HEADERFLAG_AA, false);
        msg.setHeaderFlag(Message::HEADERFLAG_TC, headerflag_tc_);

        addRRset(msg, rrset_entry_vec, Message::SECTION_ANSWER);
        addRRset(msg, rrset_entry_vec, Message::SECTION_AUTHORITY);
        addRRset(msg, rrset_entry_vec, Message::SECTION_ADDITIONAL);

        return (true);
    }
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
                // Make sure question section is not empty.
                assert( quest_iter != message.endQuestion());

                const Name& query_name = (*quest_iter)->getName();
                const RRType& type = rrset->getType();
                const Name& name = rrset->getName();
                if ((type == RRType::CNAME() && name == query_name) ||
                    (type == RRType::DNAME() &&
                     name == getDNAMEChainStarter(message, query_name))) {
                    return (RRSET_TRUST_ANSWER_AA);
                } else {
                    // If there is a CNAME record whose ower name is the same as
                    // the query name in answer section, the other records in answer
                    // section are non-authoritative, except the starter of DNAME
                    // chain (only checking CNAME is enough, because if the CNAME
                    // record is synthesized from a DNAME record, that DNAME
                    // record must be the starter of the DNAME chain).
                    RRsetIterator iter = message.beginSection(Message::SECTION_ANSWER);
                    while(iter != message.endSection(Message::SECTION_ANSWER)) {
                        if ((*iter)->getType() == RRType::CNAME() &&
                             (*iter)->getName() == query_name) {
                            return (RRSET_TRUST_ANSWER_NONAA);
                        }
                        ++iter;
                    }
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
        rrsets_.push_back(RRsetRef(rrset_ptr->getName(), rrset_ptr->getType(),
                          rrset_cache_.get()));

        uint32_t rrset_ttl = rrset_entry->getTTL();
        if (smaller_ttl > rrset_ttl) {
            smaller_ttl = rrset_ttl;
        }

        count++;
    }

    rrset_count = count;
}

void
MessageEntry::parseNegativeResponseAuthoritySection(const isc::dns::Message& msg,
        uint32_t& min_ttl,
        uint16_t& rrset_count)
{
    uint16_t count = 0;
    for (RRsetIterator iter = msg.beginSection(Message::SECTION_AUTHORITY);
            iter != msg.endSection(Message::SECTION_AUTHORITY);
            ++iter) {
        RRsetPtr rrset_ptr = *iter;
        RRsetTrustLevel level = getRRsetTrustLevel(msg, rrset_ptr,
                                                   Message::SECTION_AUTHORITY);
        boost::shared_ptr<RRsetCache> rrset_cache_ptr = rrset_cache_;
        if (rrset_ptr->getType() == RRType::SOA()) {
            rrset_cache_ptr = negative_soa_cache_;
        }

        RRsetEntryPtr rrset_entry = rrset_cache_ptr->update(*rrset_ptr, level);
        rrsets_.push_back(RRsetRef(rrset_ptr->getName(),
                                   rrset_ptr->getType(),
                                   rrset_cache_ptr.get()));
        uint32_t rrset_ttl = rrset_entry->getTTL();
        if (min_ttl > rrset_ttl) {
            min_ttl = rrset_ttl;
        }
        ++count;
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

    bool isNegativeResponse = MessageUtility::isNegativeResponse(msg);

    parseSection(msg, Message::SECTION_ANSWER, min_ttl, answer_count_);
    if (!isNegativeResponse) {
        parseSection(msg, Message::SECTION_AUTHORITY, min_ttl, authority_count_);
    } else {
        parseNegativeResponseAuthoritySection(msg, min_ttl, authority_count_);
    }
    parseSection(msg, Message::SECTION_ADDITIONAL, min_ttl, additional_count_);

    // Limit the ttl to a prset max-value
    if (!isNegativeResponse) {
        if (min_ttl > MAX_NORMAL_CACHE_TTL) {
            min_ttl = MAX_NORMAL_CACHE_TTL;
        }
    } else {
        if (min_ttl > MAX_NEGATIVE_CACHE_TTL) {
            min_ttl = MAX_NEGATIVE_CACHE_TTL;
        }
    }

    expire_time_ = time(NULL) + min_ttl;
}

} // namespace cache
} // namespace isc
