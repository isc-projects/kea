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

namespace isc {
namespace nsas {

namespace {
// Shorter aliases for frequently used types
typedef boost::mutex::scoped_lock Lock;
typedef boost::shared_ptr<AddressRequestCallback> CallbackPtr;
}

void
ZoneEntry::addCallback(CallbackPtr callback) {
    Lock lock(mutex_);
    callbacks_.push_back(callback);
}

bool
ZoneEntry::hasCallbacks() const {
    Lock lock(mutex_);
    return (!callbacks_.empty());
}

CallbackPtr
ZoneEntry::popCallback() {
    Lock lock(mutex_);
    CallbackPtr result(callbacks_.front());
    callbacks_.pop_front();
    return (result);
}

}; // namespace nsas
}; // namespace isc
