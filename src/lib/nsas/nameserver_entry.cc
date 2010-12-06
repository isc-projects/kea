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

// $Id$

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
#include <dns/question.h>

#include "address_entry.h"
#include "nameserver_entry.h"
#include "resolver_interface.h"

using namespace asiolink;
using namespace isc::nsas;
using namespace isc::dns;
using namespace std;
using namespace boost;

namespace isc {
namespace nsas {

namespace {

/// Returns false if the address family of a given entry matches the address
/// familyi given. This curious logic is needed for use in the remove_copy_if
/// algorithm, which copies all values apart from those for which the
/// criteria is met.
bool
addressSelection(short family, const AddressEntry& entry) {
    return (entry.getAddress().getFamily() != family);
};

typedef mutex::scoped_lock Lock;

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
    if (getState() != NOT_ASKED && expiration_ <= now && expiration_) {
        setState(EXPIRED);
    }

    if (getState() == EXPIRED && !expired_ok) {
        return EXPIRED;
    }

    switch (getState()) {
        case IN_PROGRESS:
            // Did we receive the address already?
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

    // If any address is OK, just pass everything we have
    if (family == ANY_OK) {
        addresses.insert(addresses.end(), address_.begin(), address_.end());
    } else {
        // Filter the addresses
        short s_family(0);
        switch (family) {
            case V4_ONLY: s_family = AF_INET; break;
            case V6_ONLY: s_family = AF_INET6; break;
            default: assert(0); // This should never happen
        }
        // Now copy all entries that meet the criteria.  Since remove_copy_if
        // does the inverse (copies all entries that do not meet the criteria),
        // the predicate for address selection is negated.
        remove_copy_if(address_.begin(), address_.end(),
            back_inserter(addresses), boost::bind(addressSelection, s_family,
            _1));
    }
    if (getState() == EXPIRED && expired_ok) {
        return READY;
    }
    return getState();
}

asiolink::IOAddress
NameserverEntry::getAddressAtIndex(uint32_t index) const {
    Lock lock(mutex_);

    assert(index < address_.size());

    return address_[index].getAddress();
}

// Set the address RTT to a specific value
void
NameserverEntry::setAddressRTT(const IOAddress& address, uint32_t rtt) {
    Lock lock(mutex_);

    // Search through the list of addresses for a match
    for (AddressVectorIterator i = address_.begin(); i != address_.end(); ++i) {
        if (i->getAddress().equal(address)) {
            i->setRTT(rtt);
        }
    }
}

// Update the address's rtt 
void
NameserverEntry::updateAddressRTTAtIndex(uint32_t rtt, uint32_t index) {
    Lock lock(mutex_);

    //make sure it is a valid index
    if(index >= address_.size()) return;

    //update the rtt
    address_[index].setRTT(rtt);
}

// Sets the address to be unreachable
void
NameserverEntry::setAddressUnreachable(const IOAddress& address) {
    setAddressRTT(address, AddressEntry::UNREACHABLE);
}

/*
 * A callback class into the resolver. Whenever we ask the resolver something,
 * this is created and the answer is fed back trough this. It holds a shared
 * pointer to the entry so it is not destroyed too soon.
 */
class NameserverEntry::ResolverCallback : public ResolverInterface::Callback {
    public:
        ResolverCallback(shared_ptr<NameserverEntry> entry,
            AddressFamily family, const RRType& type) :
            entry_(entry),
            rtt_(0),
            family_(family),
            type_(type)
        { }
        virtual void success(const shared_ptr<AbstractRRset>& response) {
            time_t now = time(NULL);

            Lock lock(entry_->mutex_);

            vector<AddressEntry> entries;

            if (response->getType() != type_ ||
                response->getClass() != RRClass(entry_->getClass()))
            {
                // TODO Log we got answer of different type
                failureInternal(lock);
                return;
            }

            RdataIteratorPtr i(response->getRdataIterator());
            // TODO Remove at merge with trunk
            i->first();
            while (! i->isLast()) {
                entries.push_back(AddressEntry(IOAddress(
                    i->getCurrent().toText()), ++ rtt_));
                i->next();
            }

            if (entries.empty()) {
                // No data there, count it as a failure
                failureInternal(lock);
            } else {
                entry_->expect_address_[family_] = false;
                entry_->expect_address_[ANY_OK] =
                    entry_->expect_address_[V4_ONLY] ||
                    entry_->expect_address_[V6_ONLY];
                // Everything is here
                if (!entry_->expect_address_[ANY_OK]) {
                    entry_->setState(READY);
                }
                // We have some address
                entry_->has_address_[ANY_OK] =
                    entry_->has_address_[family_] = true;
                // Put the addresses there
                entry_->address_.insert(entry_->address_.end(),
                    entries.begin(), entries.end());
                // Update the expiration time. If it is 0, it means we
                // did not set it yet, so reset
                time_t expiration(now + response->getTTL().getValue());
                if (entry_->expiration_) {
                    entry_->expiration_ = min(entry_->expiration_, expiration);
                } else {
                    entry_->expiration_ = expiration;
                }
                // Run the right callbacks
                dispatchCallbacks(lock);
            }
        }
        virtual void failure() {
            Lock lock(entry_->mutex_);
            failureInternal(lock);
        }
    private:
        shared_ptr<NameserverEntry> entry_;
        int rtt_;
        AddressFamily family_;
        RRType type_;

        // Dispatches all relevant callbacks. Keeps lock unlocked afterwards.
        void dispatchCallbacks(Lock& lock)
        {
            // We dispatch ANY addresses if there is at last one address or
            // there's no chance we'll get some in future
            bool dispatch_any = entry_->has_address_[ANY_OK] ||
                !entry_->expect_address_[ANY_OK];
            // Sort out the callbacks we want
            vector<CallbackPair> keep;
            vector<shared_ptr<NameserverEntry::Callback> > dispatch;
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
            BOOST_FOREACH(const shared_ptr<NameserverEntry::Callback>&
                callback, dispatch)
            {
                (*callback)(entry_);
            }
        }

        // Handle a failure to optain data. Dispatches callbacks and leaves
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
            // Dispatch any relevant callbacks
            dispatchCallbacks(lock);
        }
};

void
NameserverEntry::askIP(shared_ptr<ResolverInterface> resolver,
    const RRType& type, AddressFamily family)
{
    QuestionPtr question(new Question(Name(getName()), RRClass(getClass()),
        type));
    shared_ptr<ResolverCallback> callback(new ResolverCallback(
        shared_from_this(), family, type));
    resolver->resolve(question, callback);
}

void
NameserverEntry::askIP(shared_ptr<ResolverInterface> resolver,
    shared_ptr<Callback> callback, AddressFamily family)
{
    Lock lock(mutex_);

    if (getState() == EXPIRED || getState() == NOT_ASKED) {
        // We will request the addresses

        // Set internal state first
        // TODO: We might want to save the addresses somewhere so we do not
        // lose RTT. This might get tricky. Would the trick with map as in
        // ZoneEntry work as well?
        address_.clear();
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
