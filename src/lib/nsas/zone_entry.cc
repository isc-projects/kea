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

#include <map>

#include <config.h>

#include "zone_entry.h"
#include "address_request_callback.h"
#include "nameserver_entry.h"

#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <dns/rrttl.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>

using namespace std;

namespace isc {

using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::random;

namespace nsas {

ZoneEntry::ZoneEntry(
    isc::resolve::ResolverInterface* resolver,
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
typedef isc::util::locks::scoped_lock<isc::util::locks::recursive_mutex> Lock; // Local lock, nameservers not locked
typedef boost::shared_ptr<AddressRequestCallback> CallbackPtr;

/*
 * Create a nameserver.
 * Called inside a mutex so it is filled in atomically.
 */
boost::shared_ptr<NameserverEntry>
newNs(const std::string* name, const RRClass* class_code) {
    return (boost::shared_ptr<NameserverEntry>(new NameserverEntry(*name,
        *class_code)));
}

}

/**
 * \short Callback class that ZoneEntry passes to a resolver.
 *
 * We need to ask for the list of nameservers. So we pass ResolverCallback
 * object to it, when it knows the answer, method of this thing will be
 * called.
 *
 * It is a nested friend class and should be considered as a part of ZoneEntry
 * code. It manipulates directly ZoneEntry's data members, locks it and like
 * that. Mostly eliminates C++ bad design of missing lambda functions.
 */
class ZoneEntry::ResolverCallback :
        public isc::resolve::ResolverInterface::Callback {
    public:
        /// \short Constructor. Pass "this" zone entry
        ResolverCallback(boost::shared_ptr<ZoneEntry> entry) :
            entry_(entry)
        { }
        /**
         * \short It successfully received nameserver list.
         *
         * It fills the nameservers into the ZoneEntry whose callback this is.
         * If there are in the hash table, it is used. If not, they are
         * created. This might still fail, if the list is empty.
         *
         * It then calls process, to go trough the list of nameservers,
         * examining them and seeing if some addresses are already there
         * and to ask for the rest of them.
         */
        virtual void success(MessagePtr response_message) {
            Lock lock(entry_->mutex_);

            // TODO: find the correct RRset, not simply the first
            if (!response_message ||
                response_message->getRcode() != isc::dns::Rcode::NOERROR() ||
                response_message->getRRCount(isc::dns::Message::SECTION_ANSWER) == 0) {
                // todo: define this
                failureInternal(300);
            }

            isc::dns::RRsetIterator rrsi =
                response_message->beginSection(isc::dns::Message::SECTION_ANSWER);
            const isc::dns::RRsetPtr answer = *rrsi;

            RdataIteratorPtr iterator(answer->getRdataIterator());
            // If there are no data
            if (iterator->isLast()) {
                failureInternal(answer->getTTL().getValue());
                return;
            } else {
                /*
                 * We store the nameservers we have currently (we might have
                 * none, at startup, but when we time out and ask again, we
                 * do), so we can just reuse them instead of looking them up in
                 * the table or creating them.
                 */
                std::map<string, NameserverPtr> old;
                BOOST_FOREACH(const NameserverPtr& ptr, entry_->nameservers_) {
                    old[ptr->getName()] = ptr;
                }
                /*
                 * List of original nameservers we did not ask for IP address
                 * yet.
                 */
                set<NameserverPtr> old_not_asked;
                old_not_asked.swap(entry_->nameservers_not_asked_);

                // Once we have them put aside, remove the original set
                // of nameservers from the entry
                entry_->nameservers_.clear();
                // And put the ones from the answer them, reusing if possible
                for (; !iterator->isLast(); iterator->next()) {
                    try {
                        // Get the name from there
                        Name ns_name(dynamic_cast<const rdata::generic::NS&>(
                            iterator->getCurrent()).getNSName());
                        // Try to find it in the old ones
                        std::map<string, NameserverPtr>::iterator old_ns(old.find(
                            ns_name.toText()));
                        /*
                         * We didn't have this nameserver before. So we just
                         * look it up in the hash table or create it.
                         */
                        if (old_ns == old.end()) {
                            // Look it up or create it
                            string ns_name_str(ns_name.toText());
                            pair<bool, NameserverPtr> from_hash(
                                entry_->nameserver_table_->getOrAdd(HashKey(
                                ns_name_str, entry_->class_code_), boost::bind(
                                newNs, &ns_name_str, &entry_->class_code_)));
                            // Make it at the front of the list
                            if (from_hash.first) {
                                entry_->nameserver_lru_->add(from_hash.second);
                            } else {
                                entry_->nameserver_lru_->touch(
                                    from_hash.second);
                            }
                            // And add it at last to the entry
                            entry_->nameservers_.push_back(from_hash.second);
                            entry_->nameservers_not_asked_.insert(
                                from_hash.second);
                        } else {
                            // We had it before, reuse it
                            entry_->nameservers_.push_back(old_ns->second);
                            // Did we ask it already? If not, it is still not
                            // asked (the one designing std interface must
                            // have been mad)
                            if (old_not_asked.find(old_ns->second) !=
                                old_not_asked.end())
                            {
                                entry_->nameservers_not_asked_.insert(
                                    old_ns->second);
                            }
                        }
                    }
                    // OK, we skip this one as it is not NS (log?)
                    catch (bad_cast&) { }
                }

                // It is unbelievable, but we found no nameservers there
                if (entry_->nameservers_.empty()) {
                    // So we fail the same way as if we got empty list
                    failureInternal(answer->getTTL().getValue());
                    return;
                } else {
                    // Ok, we have them. So set us as ready, set our
                    // expiration time and try to answer what we can, ask
                    // if there's still someone to ask.
                    entry_->setState(READY);
                    entry_->expiry_ = answer->getTTL().getValue() + time(NULL);
                    entry_->process(ADDR_REQ_MAX, NameserverPtr());
                    return;
                }
            }
        }
        /// \short Failed to receive answer.
        virtual void failure() {
            failureInternal(300);
        }
    private:
        /**
         * \short Common function called when "it did not work"
         *
         * It marks the ZoneEntry as unreachable and processes callbacks (by
         * calling process).
         */
        void failureInternal(time_t ttl) {
            Lock lock(entry_->mutex_);
            entry_->setState(UNREACHABLE);
            entry_->expiry_ = ttl + time(NULL);
            // Process all three callback lists and tell them KO
            entry_->process(ADDR_REQ_MAX, NameserverPtr());
        }
        /// \short The entry we are callback of
        boost::shared_ptr<ZoneEntry> entry_;
};

void
ZoneEntry::addCallback(CallbackPtr callback, AddressFamily family,
                       const GlueHints& glue_hints) {
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
    bool execute(!ask && getState() != IN_PROGRESS &&
        callbacks_[family].empty());

    // Unless there was glue
    if (ask && glue_hints.hasGlue(family)) {
        callback->success(glue_hints.getGlue(family));
    } else {
        callbacks_[family].push_back(callback);
    }

    if (execute) {
        // Try to process it right away, store if not possible to handle
        process(family, NameserverPtr());
        return;
    }

    if (ask) {
        setState(IN_PROGRESS);
        // Our callback might be directly called from resolve, unlock now
        QuestionPtr question(new Question(Name(name_), class_code_,
            RRType::NS()));
        boost::shared_ptr<ResolverCallback> resolver_callback(
            new ResolverCallback(shared_from_this()));
        resolver_->resolve(question, resolver_callback);
        return;
    }
}

void
ZoneEntry::removeCallback(const CallbackPtr& callback, AddressFamily family) {
    Lock lock(mutex_);
    std::vector<boost::shared_ptr<AddressRequestCallback> >::iterator i = 
        callbacks_[family].begin();
    for (; i != callbacks_[family].end(); ++i) {
        if (*i == callback) {
            callbacks_[family].erase(i);
            // At this point, a callback should only be in the list
            // once (enforced by RunningQuery doing only one at a time)
            // If that changes, we need to revise this (can't delete
            // elements from a list we're looping over)
            return;
        }
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

// Update the address selector according to the RTTs
//
// Each address has a probability to be selected if multiple addresses are available
// The weight factor is equal to 1/(rtt*rtt), then all the weight factors are normalized
// to make the sum equal to 1.0
void
updateAddressSelector(std::vector<NameserverAddress>& addresses,
    WeightedRandomIntegerGenerator& selector)
{
    vector<double> probabilities;
    BOOST_FOREACH(NameserverAddress& address, addresses) {
        uint32_t rtt = address.getAddressEntry().getRTT();
        if(rtt == 0) {
            isc_throw(RTTIsZero, "The RTT is 0");
        }

        if(rtt == AddressEntry::UNREACHABLE) {
            probabilities.push_back(0);
        } else {
            probabilities.push_back(1.0/(rtt*rtt));
        }
    }
    // Calculate the sum
    double sum = accumulate(probabilities.begin(), probabilities.end(), 0.0);

    if(sum != 0) {
        // Normalize the probabilities to make the sum equal to 1.0
        for(vector<double>::iterator it = probabilities.begin();
                it != probabilities.end(); ++it){
            (*it) /= sum;
        }
    } else if(!probabilities.empty()){
        // If all the nameservers are unreachable, the sum will be 0
        // So give each server equal opportunity to be selected.
        for(vector<double>::iterator it = probabilities.begin();
                it != probabilities.end(); ++it){
            (*it) = 1.0/probabilities.size();
        }
    }

    selector.reset(probabilities);
}

}

/**
 * \short Sets given boolean to false when destroyed.
 *
 * This is hack eliminating C++ missing finally. We need to make sure
 * the value gets set to false when we leave the function, so we use
 * a Guard object, that sets it when it gets out of scope.
 */
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

/**
 * \short Callback from NameserverEntry to us.
 *
 * We registre object of this class whenever some ZoneEntry has a need to be
 * notified of a change (received data) inside its NameserverEntry.
 *
 * This is part of the ZoneEntry code (not visible from outside, accessing
 * private functions). It is here just because C++ does not know propper lambda
 * functions.
 */
class ZoneEntry::NameserverCallback : public NameserverEntry::Callback {
    public:
        /**
         * \short Constructor.
         *
         * \param entry The ZoneEntry to be notified.
         * \param family For which address family this change is, so we
         *     do not process all the nameserves and callbacks there.
         */
        NameserverCallback(boost::shared_ptr<ZoneEntry> entry, AddressFamily family) :
            entry_(entry),
            family_(family)
        { }
        /**
         * \short Callback method.
         *
         * This is called by NameserverEntry when the change happens.
         * We just call process to go trough relevant nameservers and call
         * any callbacks we can.
         */
        virtual void operator()(NameserverPtr ns) {
            entry_->process(family_, ns);
        }
    private:
        boost::shared_ptr<ZoneEntry> entry_;
        AddressFamily family_;
};

void
ZoneEntry::dispatchFailures(AddressFamily family) {
    // We extract all the callbacks
    vector<CallbackPtr> callbacks;
    if (family == ADDR_REQ_MAX) {
        move(callbacks_[ANY_OK], callbacks_[V4_ONLY]);
        move(callbacks_[ANY_OK], callbacks_[V6_ONLY]);
        family = ANY_OK;
    }
    callbacks.swap(callbacks_[family]);
    BOOST_FOREACH(const CallbackPtr& callback, callbacks) {
        callback->unreachable();
    }
}

void
ZoneEntry::process(AddressFamily family,
    const boost::shared_ptr<NameserverEntry>& nameserver)
{
    Lock lock(mutex_);
    switch (getState()) {
        // These are not interesting, nothing to return now
        case NOT_ASKED:
        case IN_PROGRESS:
        case EXPIRED:
            break;
        case UNREACHABLE: {
            dispatchFailures(family);
            // And we do nothing more now
            break;
        }
        case READY:
            if (family == ADDR_REQ_MAX) {
                // Just process each one separately
                // TODO Think this over, is it safe, to unlock in the middle?
                process(ANY_OK, nameserver);
                process(V4_ONLY, nameserver);
                process(V6_ONLY, nameserver);
            } else {
                // Nothing to do anyway for this family, be dormant
                if (callbacks_[family].empty()) {
                    return;
                }
                /*
                 * If we have multiple nameservers and more than 1 of them
                 * is in the cache, we want to choose from all their addresses.
                 * So we ensure this instance of process is the only one on
                 * the stack. If not, we terminate and let the outernmost
                 * one handle it when we return to it.
                 *
                 * If we didn't do it, one instance would call "resolve". If it
                 * was from cache, it would imediatelly recurse back to another
                 * process (trough the nameserver callback, etc), which would
                 * take that only one nameserver and trigger all callbacks.
                 * Only then would resolve terminate and we could ask for the
                 * second nameserver. This way, we first receive all the
                 * nameservers that are already in cache and trigger the
                 * callbacks only then.
                 *
                 * However, this does not wait for external fetches of
                 * nameserver addresses, as the callback is called after
                 * process terminates. Therefore this waits only for filling
                 * of the nameservers which we already have in cache.
                 */
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
                            // Someone asked it, but not us, we don't have
                            // callback
                            if (nameservers_not_asked_.find(ns) !=
                                nameservers_not_asked_.end())
                            {
                                to_ask.push_back(ns);
                            }
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
                    // We ask everything that makes sense now
                    nameservers_not_asked_.clear();
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
                        insertCallback(ns, ADDR_REQ_MAX);
                    }
                    // Retry with all the data that might have arrived
                    in_process_[family] = false;
                    // We do not provide the callback again
                    process(family, nameserver);
                    // And be done
                    return;
                // We have some addresses to answer
                } else if (!addresses.empty()) {
                    // Prepare the selector of addresses
                    // TODO: Think of a way how to keep it for a while
                    //   (not update every time)
                    updateAddressSelector(addresses, address_selector);

                    // Extract the callbacks
                    vector<CallbackPtr> to_execute;
                    // FIXME: Think of a solution where we do not lose
                    // any callbacks upon exception
                    to_execute.swap(callbacks_[family]);

                    // Run the callbacks
                    BOOST_FOREACH(const CallbackPtr& callback, to_execute) {
                        callback->success(addresses[address_selector()]);
                    }
                    return;
                } else if (!pending) {
                    dispatchFailures(family);
                    return;
                }
            }
            return;
    }
}

void
ZoneEntry::insertCallback(NameserverPtr ns, AddressFamily family) {
    if (family == ADDR_REQ_MAX) {
        insertCallback(ns, ANY_OK);
        insertCallback(ns, V4_ONLY);
        insertCallback(ns, V6_ONLY);
    } else {
        boost::shared_ptr<NameserverCallback> callback(new NameserverCallback(
            shared_from_this(), family));
        ns->askIP(resolver_, callback, family);
    }
}

}; // namespace nsas
}; // namespace isc
