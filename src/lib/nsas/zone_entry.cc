// Copyright (C) 2010  CZ NIC
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

// $id$

#include "zone_entry.h"
#include "address_request_callback.h"
#include "nameserver_entry.h"

#include <algorithm>
#include <boost/foreach.hpp>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace boost;

namespace isc {

using namespace dns;

namespace nsas {

namespace {
// Shorter aliases for frequently used types
typedef mutex::scoped_lock Lock; // Local lock, nameservers not locked
typedef shared_ptr<AddressRequestCallback> CallbackPtr;

/*
 * Create a nameserver.
 * Called inside a mutex so it is filled in atomically.
 */
shared_ptr<NameserverEntry>
newNs(const std::string* name, const RRClass* class_code) {
    return (shared_ptr<NameserverEntry>(new NameserverEntry(*name,
        *class_code)));
}

}

// A struct, the class is unaccessible anyway and is ours
struct ZoneEntry::ResolverCallback : public ResolverInterface::Callback {
    ResolverCallback(shared_ptr<ZoneEntry> entry) :
        entry_(entry)
    { }
    virtual void success(shared_ptr<AbstractRRset> answer) {
        shared_ptr<Lock> lock(new Lock(entry_->mutex_));
        RdataIteratorPtr iterator(answer->getRdataIterator());
        iterator->first();
        // If there are no data
        if (iterator->isLast()) {
            failureInternal(lock, answer->getTTL().getValue());
            return;
        } else {
            // Store the current ones so we can keep them
            map<string, NameserverPtr> old;
            BOOST_FOREACH(const NameserverPtr& ptr, entry_->nameservers_) {
                old[ptr->getName()] = ptr;
            }

            // Now drop the old ones and insert the new ones
            entry_->nameservers_.clear();
            for (; !iterator->isLast(); iterator->next()) {
                try {
                    // Get the name from there
                    Name ns_name(dynamic_cast<const rdata::generic::NS&>(
                        iterator->getCurrent()).getNSName());
                    // Try to find it in the old ones
                    map<string, NameserverPtr>::iterator old_ns(old.find(
                        ns_name.toText()));
                    // It is not there, look it up in the table or create
                    // new one
                    if (old_ns == old.end()) {
                        // Look it up or create it
                        string ns_name_str(ns_name.toText());
                        pair<bool, NameserverPtr> from_hash(
                            entry_->nameserver_table_->getOrAdd(HashKey(
                            ns_name_str, entry_->class_code_), bind(
                            newNs, &ns_name_str, &entry_->class_code_)));
                        // Touch it if it is not newly created
                        if (!from_hash.first) {
                            entry_->nameserver_lru_->touch(from_hash.second);
                        }
                        // And add it at last
                        entry_->nameservers_.push_back(from_hash.second);
                    } else {
                        // We have it, so just use it
                        entry_->nameservers_.push_back(old_ns->second);
                    }
                }
                // OK, we skip this one it is not NS (log?)
                catch (bad_cast&) { }
            }

            // It is unbelievable, but we found no nameservers there
            if (entry_->nameservers_.empty()) {
                failureInternal(lock, answer->getTTL().getValue());
                return;
            } else {
                entry_->setState(READY);
                entry_->expiry_ = answer->getTTL().getValue() + time(NULL);
                entry_->process(CallbackPtr(), ADDR_REQ_MAX, NULL, lock);
                return;
            }
        }
    }
    virtual void failure() {
        shared_ptr<Lock> lock(new Lock(entry_->mutex_));
        /*
         * FIXME: That 5 minutes is just made up and wrong.
         * Where is the correct place to get the correct number?
         */
        failureInternal(lock, 300);
    }
    void failureInternal(shared_ptr<Lock> lock, time_t ttl) {
        entry_->setState(UNREACHABLE);
        entry_->expiry_ = ttl + time(NULL);
        // Process all three callback lists and tell them KO
        entry_->process(CallbackPtr(), ADDR_REQ_MAX, NULL, lock);
    }
    shared_ptr<ZoneEntry> entry_;
};

void
ZoneEntry::addCallback(CallbackPtr callback, AddressFamily family,
    shared_ptr<ZoneEntry> self)
{
    Lock lock(mutex_);

    bool ask(false);

    // Look at expiration time
    if (expiry_ && time(NULL) >= expiry_) {
        setState(EXPIRED);
    }

    // We need to ask (again)
    if (getState() == EXPIRED || getState() == NOT_ASKED) {
        ask = true;
    }

    // We do not have the answer right away, just queue the callback
    if (ask || getState() == IN_PROGRESS || !callbacks_[family].empty()) {
        callbacks_[family].push_back(callback);
    } else {
        // Try to process it right away, store if not possible to handle
        lock.unlock();
        process(callback, family, NULL);
        return;
    }

    if (ask) {
        setState(IN_PROGRESS);
        QuestionPtr question(new Question(Name(name_), class_code_,
            RRType::NS()));
        shared_ptr<ResolverCallback> resolver_callback(
            new ResolverCallback(self));
        resolver_->resolve(question, resolver_callback);
    }
}

namespace {

template<class Container>
void
move(Container& into, Container& from) {
    into.insert(into.end(), from.begin(), from.end());
    from.clear();
}

}

void
ZoneEntry::process(CallbackPtr callback, AddressFamily family,
    NameserverEntry*, shared_ptr<Lock> lock)
{
    // If we were not provided with a lock, get one
    if (!lock) {
        lock.reset(new Lock(mutex_));
    }

    if (callback) {
        assert(family != ADDR_REQ_MAX);
        callbacks_[family].push_back(callback);
    }

    switch (getState()) {
        // These are not interesting, nothing to return now
        case NOT_ASKED:
        case IN_PROGRESS:
        case EXPIRED:
            return;
        case UNREACHABLE: {
            // We extract all the callbacks
            vector<CallbackPtr> callbacks;
            if (family == ADDR_REQ_MAX) {
                move(callbacks_[ANY_OK], callbacks_[V4_ONLY]);
                move(callbacks_[ANY_OK], callbacks_[V6_ONLY]);
                family = ANY_OK;
            }
            callbacks.swap(callbacks_[family]);
            // We want to call them not locked, so we both do not block the
            // lock and allow them to call our functions
            lock->unlock();
            BOOST_FOREACH(const CallbackPtr& callback, callbacks) {
                callback->unreachable();
            }
            // And we do nothing more now
            return;
        }
        case READY:
            // TODO Write
            ;
    }
}

}; // namespace nsas
}; // namespace isc
