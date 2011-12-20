// Copyright (C) 2010-2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <ctype.h>
#include <strings.h>

#include <config.h>

#include <exceptions/exceptions.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rcode.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <resolve/resolver_interface.h>

#include <asiolink/io_address.h>

#include "address_entry.h"
#include "nameserver_address.h"
#include "nameserver_entry.h"
#include "nsas_log.h"

using namespace isc::asiolink;
using namespace isc::nsas;
using namespace isc::dns;
using namespace std;

namespace isc {
namespace nsas {

namespace {

// Just shorter type alias
typedef isc::util::locks::scoped_lock<isc::util::locks::recursive_mutex> Lock;

}

// Returns the list of addresses matching the given family
Fetchable::State
NameserverEntry::getAddresses(AddressVector& addresses,
    AddressFamily family, bool expired_ok)
{
    Lock lock(mutex_);

    // Check TTL
    time_t now(time(NULL));
    // We take = as well, so we catch TTL 0 correctly
    // expiration_ == 0 means not set, the reason is we are UNREACHABLE or
    // NOT_ASKED or IN_PROGRESS
    if (getState() != NOT_ASKED && expiration_ && expiration_ <= now) {
        setState(EXPIRED);
    }

    if (getState() == EXPIRED && !expired_ok) {
        return EXPIRED;
    }

    switch (getState()) {
        case IN_PROGRESS:
            /*
             * Did we receive the address already?
             *
             * We might have already received the addresses for this family
             * and still wait for the other (in which case has_address_[family]
             * will be true). We might already received a negative answer,
             * in which case expect_address_[family] is false and
             * has_address_[family] is false as well.
             */
            if (!has_address_[family] && expect_address_[family]) {
                return IN_PROGRESS;
            }
            // If we do not expect the address, then fall trough to READY
        case EXPIRED: // If expired_ok, we pretend to be ready
        case READY:
            if (!has_address_[family]) {
                return UNREACHABLE;
            }
            break; // OK, we give some answers
        case NOT_ASKED:
        case UNREACHABLE:
            // Reject giving any data
            return (getState());
    }

    boost::shared_ptr<NameserverEntry> self(shared_from_this());
    // If any address is OK, just pass everything we have
    if (family == ANY_OK) {
        BOOST_FOREACH(const AddressEntry& entry, addresses_[V6_ONLY]) {
            addresses.push_back(NameserverAddress(self, entry, V6_ONLY));
        }
        BOOST_FOREACH(const AddressEntry& entry, addresses_[V4_ONLY]) {
            addresses.push_back(NameserverAddress(self, entry, V4_ONLY));
        }
    } else {
        BOOST_FOREACH(const AddressEntry& entry, addresses_[family]) {
            addresses.push_back(NameserverAddress(self, entry, family));
        }
    }
    if (getState() == EXPIRED && expired_ok) {
        return READY;
    }
    return getState();
}

// Return the address corresponding to the family
asiolink::IOAddress
NameserverEntry::getAddressAtIndex(size_t index, AddressFamily family) const {
    Lock lock(mutex_);

    assert(index < addresses_[family].size());

    return (addresses_[family][index].getAddress());
}

// Set the address RTT to a specific value
void
NameserverEntry::setAddressRTT(const IOAddress& address, uint32_t rtt) {
    Lock lock(mutex_);

    // Search through the list of addresses for a match
    AddressFamily family(V4_ONLY);
    for (;;) {
        BOOST_FOREACH(AddressEntry& entry, addresses_[family]) {
            if (entry.getAddress().equals(address)) {
                entry.setRTT(rtt);
                return;
            }
        }

        // Hack. C++ does not allow ++ on enums, enumerating trough them is pain
        switch (family) {
            case V4_ONLY: family = V6_ONLY; break;
            default: return;
        }
    }
}

// Update the address's rtt
#define UPDATE_RTT_ALPHA 0.7
void
NameserverEntry::updateAddressRTTAtIndex(uint32_t rtt, size_t index,
    AddressFamily family)
{
    Lock lock(mutex_);

    //make sure it is a valid index
    if(index >= addresses_[family].size()) return;

    // Smoothly update the rtt
    // The algorithm is as the same as bind8/bind9:
    //    new_rtt = old_rtt * alpha + new_rtt * (1 - alpha), where alpha is a float number in [0, 1.0]
    // The default value for alpha is 0.7
    uint32_t old_rtt = addresses_[family][index].getRTT();
    uint32_t new_rtt = (uint32_t)(old_rtt * UPDATE_RTT_ALPHA + rtt *
        (1 - UPDATE_RTT_ALPHA));
    if (new_rtt == 0) {
        new_rtt = 1;
    }
    addresses_[family][index].setRTT(new_rtt);
    LOG_DEBUG(nsas_logger, NSAS_DBG_RTT, NSAS_UPDATE_RTT)
              .arg(addresses_[family][index].getAddress().toText())
              .arg(old_rtt).arg(new_rtt);
}

void
NameserverEntry::updateAddressRTT(uint32_t rtt,
    const asiolink::IOAddress& address, AddressFamily family)
{
    Lock lock(mutex_);
    for (size_t i(0); i < addresses_[family].size(); ++ i) {
        if (addresses_[family][i].getAddress().equals(address)) {
            updateAddressRTTAtIndex(rtt, i, family);
            return;
        }
    }
}

// Sets the address to be unreachable
void
NameserverEntry::setAddressUnreachable(const IOAddress& address) {
    setAddressRTT(address, AddressEntry::UNREACHABLE);
}

/**
 * \short A callback into the resolver.
 *
 * Whenever we ask the resolver something, this is created and the answer is
 * fed back through this. It holds a shared pointer to the entry so it is not
 * destroyed too soon.
 */
class NameserverEntry::ResolverCallback :
        public isc::resolve::ResolverInterface::Callback {
    public:
        ResolverCallback(boost::shared_ptr<NameserverEntry> entry,
            AddressFamily family, const RRType& type) :
            entry_(entry),
            family_(family),
            type_(type)
        { }
        /**
         * \short We received the address successfully.
         *
         * This extracts the addresses out from the response and puts them
         * inside the entry. It tries to reuse the address entries from before
         * (if there were any), to keep their RTTs.
         */
        virtual void success(MessagePtr response_message) {
            time_t now = time(NULL);

            Lock lock(entry_->mutex_);

            // TODO: find the correct RRset, not simply the first
            if (!response_message) {
                LOG_ERROR(nsas_logger, NSAS_NULL_RESPONSE).arg(entry_->getName());
                failureInternal(lock);
                return;

            } else if (response_message->getRcode() != isc::dns::Rcode::NOERROR()) {
                LOG_DEBUG(nsas_logger, NSAS_DBG_RESULTS, NSAS_ERROR_RESPONSE).
                          arg(response_message->getRcode()).arg(entry_->getName());
                failureInternal(lock);
                return;

            } else if (
                response_message->getRRCount(isc::dns::Message::SECTION_ANSWER) == 0) {
                LOG_DEBUG(nsas_logger, NSAS_DBG_RESULTS, NSAS_EMPTY_RESPONSE).
                          arg(entry_->getName());
                failureInternal(lock);
                return;
            }
            
            isc::dns::RRsetIterator rrsi =
                response_message->beginSection(isc::dns::Message::SECTION_ANSWER);
            const isc::dns::RRsetPtr response = *rrsi;
            
            vector<AddressEntry> entries;

            if (response->getType() != type_ ||
                response->getClass() != RRClass(entry_->getClass()))
            {
                // Invalid response type or class
                LOG_ERROR(nsas_logger, NSAS_WRONG_ANSWER)
                          .arg(entry_->getName()).arg(type_)
                          .arg(entry_->getClass()).arg(response->getType())
                          .arg(response->getClass());

                failureInternal(lock);
                return;
            }

            for (RdataIteratorPtr i(response->getRdataIterator());
                !i->isLast(); i->next())
            {
                // Try to find the original value and reuse it
                string address(i->getCurrent().toText());
                AddressEntry *found(NULL);
                BOOST_FOREACH(AddressEntry& entry,
                    entry_->previous_addresses_[family_])
                {
                    if (entry.getAddress().toText() == address) {
                        // Good, found it.
                        found = &entry;
                        break;
                    }
                }
                // If we found it, use it. If not, create a new one.
                entries.push_back(found ? *found : AddressEntry(
                                                   IOAddress(address), 1));
                LOG_DEBUG(nsas_logger, NSAS_DBG_RESULTS, NSAS_FOUND_ADDRESS)
                          .arg(address).arg(entry_->getName());
            }

            // We no longer need the previous set of addresses, we have
            // the current ones now.
            entry_->previous_addresses_[family_].clear();

            if (entries.empty()) {
                // No data there, count it as a failure
                failureInternal(lock);
            } else {
                // We received the data, so mark it
                entry_->expect_address_[family_] = false;
                entry_->expect_address_[ANY_OK] =
                    entry_->expect_address_[V4_ONLY] ||
                    entry_->expect_address_[V6_ONLY];
                // Everything is here (all address families)
                if (!entry_->expect_address_[ANY_OK]) {
                    entry_->setState(READY);
                }
                // We have some address
                entry_->has_address_[ANY_OK] =
                    entry_->has_address_[family_] = true;
                // Insert the entries inside
                entry_->addresses_[family_].swap(entries);
                // Update the expiration time. If it is 0, it means we
                // did not set it yet, so reset
                time_t expiration(now + response->getTTL().getValue());
                if (entry_->expiration_) {
                    // We expire at the time first address expires
                    entry_->expiration_ = min(entry_->expiration_, expiration);
                } else {
                    // We have no expiration time set, use this one
                    entry_->expiration_ = expiration;
                }
                // Run the right callbacks
                dispatchCallbacks(lock);
            }
        }
        /**
         * \short The resolver failed to retrieve the data.
         *
         * So mark the current address family as unreachable.
         */
        virtual void failure() {
            LOG_DEBUG(nsas_logger, NSAS_DBG_RESULTS, NSAS_NS_LOOKUP_FAIL)
                      .arg(type_).arg(entry_->getName());
            Lock lock(entry_->mutex_);
            failureInternal(lock);
        }
    private:
        boost::shared_ptr<NameserverEntry> entry_;
        AddressFamily family_;
        RRType type_;

        // Dispatches all relevant callbacks. Keeps lock unlocked afterwards.
        // TODO: We might want to use recursive lock and get rid of this
        void dispatchCallbacks(Lock& lock)
        {
            // We dispatch ANY addresses if there is at last one address or
            // there's no chance we'll get some in future
            bool dispatch_any = entry_->has_address_[ANY_OK] ||
                !entry_->expect_address_[ANY_OK];
            // Sort out the callbacks we want
            vector<CallbackPair> keep;
            vector<boost::shared_ptr<NameserverEntry::Callback> > dispatch;
            BOOST_FOREACH(const CallbackPair &callback, entry_->callbacks_)
            {
                if (callback.first == family_ || (dispatch_any &&
                    callback.first == ANY_OK))
                {
                    dispatch.push_back(callback.second);
                } else {
                    keep.push_back(callback);
                }
            }
            // Put there only the ones that we do not want, drop the rest
            keep.swap(entry_->callbacks_);
            keep.clear();

            // We can't keep the lock while we execute callbacks
            lock.unlock();
            // Run all the callbacks
            /*
             * FIXME: This is not completely exception safe. If there's an
             * exception in a callback, we lose the rest of them.
             */
            BOOST_FOREACH(const boost::shared_ptr<NameserverEntry::Callback>&
                callback, dispatch)
            {
                (*callback)(entry_);
            }
        }

        // Handle a failure to obtain data. Dispatches callbacks and leaves
        // lock unlocked
        void failureInternal(Lock &lock) {
            // Set state of the addresses
            entry_->expect_address_[family_] = false;
            entry_->expect_address_[ANY_OK] =
                entry_->expect_address_[V4_ONLY] ||
                entry_->expect_address_[V6_ONLY];
            // When we do not expect any more addresses, decide the state
            if (!entry_->expect_address_[ANY_OK]) {
                if (entry_->has_address_[ANY_OK]) {
                    // We have at last one kind of address, so OK
                    entry_->setState(READY);
                } else {
                    // No addresses :-(
                    entry_->setState(UNREACHABLE);
                }
            }
            // Drop the previous addresses, no use of them now
            entry_->previous_addresses_[family_].clear();
            // Dispatch any relevant callbacks
            dispatchCallbacks(lock);
        }
};

void
NameserverEntry::askIP(isc::resolve::ResolverInterface* resolver,
    const RRType& type, AddressFamily family)
{
    QuestionPtr question(new Question(Name(getName()), RRClass(getClass()),
        type));
    boost::shared_ptr<ResolverCallback> callback(new ResolverCallback(
        shared_from_this(), family, type));
    resolver->resolve(question, callback);
}

void
NameserverEntry::askIP(isc::resolve::ResolverInterface* resolver,
    boost::shared_ptr<Callback> callback, AddressFamily family)
{
    Lock lock(mutex_);

    if (getState() == EXPIRED || getState() == NOT_ASKED) {
        // We will request the addresses

        // Set internal state first
        // We store the old addresses so we can pick their RTT when
        // we get the same addresses again (most probably)
        previous_addresses_[V4_ONLY].clear();
        previous_addresses_[V6_ONLY].clear();
        addresses_[V4_ONLY].swap(previous_addresses_[V4_ONLY]);
        addresses_[V6_ONLY].swap(previous_addresses_[V6_ONLY]);
        setState(IN_PROGRESS);
        has_address_[V4_ONLY] = has_address_[V6_ONLY] = has_address_[ANY_OK] =
            false;
        expect_address_[V4_ONLY] = expect_address_[V6_ONLY] =
            expect_address_[ANY_OK] = true;
        expiration_ = 0;

        // Store the callback
        callbacks_.push_back(CallbackPair(family, callback));

        // Ask for both types of addresses
        // We are unlocked here, as the callback from that might want to lock
        lock.unlock();

        LOG_DEBUG(nsas_logger, NSAS_DBG_TRACE, NSAS_FIND_NS_ADDRESS).arg(getName());
        askIP(resolver, RRType::A(), V4_ONLY);
        askIP(resolver, RRType::AAAA(), V6_ONLY);
        // Make sure we end the routine when we are not locked
        return;
    } else {
        // We already asked. Do we expect this address type still to come?
        if (!expect_address_[family]) {
            // We do not expect it to come, dispatch right away
            lock.unlock();
            (*callback)(shared_from_this());
            return;
        } else {
            // It will come in future, store the callback until then
            callbacks_.push_back(CallbackPair(family, callback));
        }
    }
}

} // namespace dns
} // namespace isc
