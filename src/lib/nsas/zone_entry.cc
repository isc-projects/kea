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

using namespace std;
using namespace boost;

namespace isc {
namespace nsas {

namespace {
// Shorter aliases for frequently used types
typedef mutex::scoped_lock LLock; // Local lock, nameservers not locked
typedef shared_ptr<LLock> LockPtr;
typedef vector<LockPtr> Locks;
typedef shared_ptr<AddressRequestCallback> CallbackPtr;
}

void
ZoneEntry::addCallback(CallbackPtr callback) {
    LLock lock(mutex_);
    callbacks_.push_back(callback);
}

bool
ZoneEntry::hasCallbacks() const {
    LLock lock(mutex_);
    return (!callbacks_.empty());
}

CallbackPtr
ZoneEntry::popCallback() {
    LLock lock(mutex_);
    CallbackPtr result(callbacks_.front());
    callbacks_.pop_front();
    return (result);
}

// Struct, we are somewhere inside, no need to play the private & public game
struct ZoneEntry::Lock::Impl {
    Locks locks;
};

ZoneEntry::Lock::Lock(shared_ptr<Impl> impl) :
    impl_(impl)
{ }

ZoneEntry::Lock
ZoneEntry::getLock() {
    // First, lock the zone so we can get the nameservers
    LockPtr lock(new LLock(mutex_));
    // Get a sorted copy of the nameservers
    // They are sorted to avoid possible race conditions, they will be locked
    // in increasing order
    NameserverVector nameserverCopy(nameservers_);
    sort(nameserverCopy.begin(), nameserverCopy.end());
    // Construct the list of locks and lock all the nameservers
    shared_ptr<Lock::Impl> impl(new Lock::Impl);
    impl->locks.push_back(lock);
    BOOST_FOREACH(NameserverPtr ns, nameserverCopy) {
        impl->locks.push_back(LockPtr(new LLock(ns->mutex_)));
    }

    return (Lock(impl));
}

}; // namespace nsas
}; // namespace isc
