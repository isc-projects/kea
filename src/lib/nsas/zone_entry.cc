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
#include <boost/random.hpp>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace boost;

namespace isc {

using namespace dns;

namespace nsas {

ZoneEntry::ZoneEntry(boost::shared_ptr<ResolverInterface> resolver,
    const std::string& name, const isc::dns::RRClass& class_code,
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
    boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru) :
    expiry_(0),
    name_(name), class_code_(class_code), resolver_(resolver),
    nameserver_table_(nameserver_table), nameserver_lru_(nameserver_lru)
{
    in_process_[ANY_OK] = false;
    in_process_[V4_ONLY] = false;
    in_process_[V6_ONLY] = false;
}

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

class ZoneEntry::ResolverCallback : public ResolverInterface::Callback {
    public:
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
                                entry_->nameserver_lru_->touch(
                                    from_hash.second);
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
                    entry_->process(CallbackPtr(), ADDR_REQ_MAX,
                        NameserverPtr(), entry_, lock);
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
    private:
        void failureInternal(shared_ptr<Lock> lock, time_t ttl) {
            entry_->setState(UNREACHABLE);
            entry_->expiry_ = ttl + time(NULL);
            // Process all three callback lists and tell them KO
            entry_->process(CallbackPtr(), ADDR_REQ_MAX, NameserverPtr(),
                entry_, lock);
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
        process(callback, family, NameserverPtr(), self);
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

// This just moves items from one container to another
template<class Container>
void
move(Container& into, Container& from) {
    into.insert(into.end(), from.begin(), from.end());
    from.clear();
}

mutex randMutex;

size_t
randIndex(size_t count) {
    // We need to lock the global generator
    // TODO If there's contention locking, we might want a generator
    // for each thread?
    mutex::scoped_lock lock(randMutex);
    // This seems to be enough to use pseudo-random generator and according
    // to boost docs, this one is fast.
    static rand48 generator;
    return variate_generator<rand48&, uniform_int<size_t> >(generator,
        uniform_int<size_t>(0, count - 1))();
}

asiolink::IOAddress
chooseAddress(const NameserverEntry::AddressVector& addresses) {
    // TODO Something little bit more inteligent than just picking random
    // one
    assert(!addresses.empty()); // Should not be called with empty list
    return (addresses[randIndex(addresses.size())].getAddress());
}

}

// Sets to false on exit of current scope
class ZoneEntry::ProcessGuard {
    public:
        ProcessGuard(bool& guarded) :
            guarded_(guarded)
        { }
        ~ ProcessGuard() {
            guarded_ = false;
        }
    private:
        bool& guarded_;
};

class ZoneEntry::NameserverCallback : public NameserverEntry::Callback {
    public:
        NameserverCallback(shared_ptr<ZoneEntry> entry, AddressFamily family) :
            entry_(entry),
            family_(family)
        { }
        virtual void operator()(NameserverPtr ns) {
            entry_->process(CallbackPtr(), family_, ns, entry_);
        }
    private:
        shared_ptr<ZoneEntry> entry_;
        AddressFamily family_;
};

void
ZoneEntry::process(CallbackPtr callback, AddressFamily family,
    shared_ptr<NameserverEntry> nameserver, shared_ptr<ZoneEntry> self,
    shared_ptr<Lock> lock)
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
            if (family == ADDR_REQ_MAX) {
                // Just process each one separately
                process(CallbackPtr(), ANY_OK, nameserver, self, lock);
                process(CallbackPtr(), V4_ONLY, nameserver, self, lock);
                process(CallbackPtr(), V6_ONLY, nameserver, self, lock);
            } else {
                // Nothing to do anyway for this family, be dormant
                if (callbacks_[family].empty()) {
                    return;
                }
                /*
                 * Check that we are only in one process call on stack.
                 * It eliminates the problem when there are multiple nameserver
                 * IP addresses in the cache, but the first one would trigger
                 * calling all callbacks. We do not want that, we want to wait
                 * for all cached ones to arriwe. Therefore we bail out if
                 * theres a call here in the stack already and let that sort
                 * everything out when it returns.
                 */
                // Check that we are only in one process call on stack
                if (in_process_[family]) {
                    return;
                }
                // Mark we are on the stack 
                ProcessGuard guard(in_process_[family]);
                in_process_[family] = true;
                // Variables to store the data to
                NameserverEntry::AddressVector addresses;
                NameserverVector to_ask;
                bool pending(false);

                // Pick info from the nameservers
                BOOST_FOREACH(const NameserverPtr& ns, nameservers_) {
                    Fetchable::State ns_state(ns->getAddresses(addresses,
                        family, ns == nameserver));
                    switch (ns_state) {
                        case IN_PROGRESS:
                            pending = true;
                            break;
                        case NOT_ASKED:
                        case EXPIRED:
                            to_ask.push_back(ns);
                            break;
                        case UNREACHABLE:
                        case READY:
                            // Not interested, but avoiding warning
                            break;
                    }
                }

                // We have someone to ask, so do it
                if (!to_ask.empty()) {
                    // We should not be locked, because this function can
                    // be called directly from the askIP again
                    lock->unlock();
                    shared_ptr<NameserverCallback> ns_callbacks[ADDR_REQ_MAX];;
                    ns_callbacks[ANY_OK].reset(new NameserverCallback(self,
                        ANY_OK));
                    ns_callbacks[V4_ONLY].reset(new NameserverCallback(self,
                        V4_ONLY));
                    ns_callbacks[V6_ONLY].reset(new NameserverCallback(self,
                        V6_ONLY));
                    /*
                     * TODO: Possible place for an optimisation. We now ask
                     * everything we can. We should limit this to something like
                     * 2 concurrent NS fetches (and fetch cache first, then
                     * fetch the remote ones). But fetching everything right
                     * away is simpler.
                     */
                    BOOST_FOREACH(const NameserverPtr& ns, to_ask) {
                        // Put all 3 callbacks there. If we put just the
                        // current family, it might not work due to missing
                        // callback for different one.
                        // If they recurse back to us (call directly), we kill
                        // it by the in_process_
                        ns->askIP(resolver_, ns_callbacks[V4_ONLY], V4_ONLY,
                            ns);
                        ns->askIP(resolver_, ns_callbacks[V6_ONLY], V6_ONLY,
                            ns);
                        ns->askIP(resolver_, ns_callbacks[ANY_OK], ANY_OK,
                            ns);
                    }
                    // Retry with all the data that might have arrived
                    in_process_[family] = false;
                    process(callback, family, nameserver, self);
                    // And be done
                    return;
                // We have some addresses to answer
                } else if (!addresses.empty()) {
                    // Extract the callbacks
                    vector<CallbackPtr> to_execute;
                    to_execute.swap(callbacks_[family]);

                    // Unlock, the callbacks might want to call us
                    BOOST_FOREACH(const CallbackPtr& callback, to_execute) {
                        callback->success(chooseAddress(addresses));
                    }
                }
            }
            return;
    }
}

}; // namespace nsas
}; // namespace isc
