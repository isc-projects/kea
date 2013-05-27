// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <util/hooks/server_hooks.h>

#include <utility>

using namespace std;
using namespace isc;

namespace isc {
namespace util {

// Constructor - register the pre-defined hooks and check that the indexes
// assigned to them are as expected.

ServerHooks::ServerHooks() {
    int create = registerHook("context_create");
    int destroy = registerHook("context_destroy");

    if ((create != CONTEXT_CREATE) || (destroy != CONTEXT_DESTROY)) {
        isc_throw(Unexpected, "pre-defined hook indexes are not as expected. "
                  "context_create: expected = " << CONTEXT_CREATE <<
                  ", actual = " << create <<
                  ". context_destroy: expected = " << CONTEXT_DESTROY <<
                  ", actual = " << destroy);
    }
}

// Register a hook.  The index assigned to the hook is the current number
// of entries in the collection.

int
ServerHooks::registerHook(const string& name) {

    // Determine index for the new element and insert.
    int index = hooks_.size();
    pair<HookCollection::iterator, bool> result =
        hooks_.insert(make_pair(name, index));

    if (!result.second) {
        // New element was not inserted because an element with the same name
        // already existed.
        isc_throw(DuplicateHook, "hook with name " << name <<
                  " is already registered");
    }

    // New element inserted, return numeric index.
    return (index);
}

// Find the index associated with a hook name or return -1 if not found

int
ServerHooks::getIndex(const string& name) const {

    // Return pair of <hook name, index>.
    HookCollection::const_iterator i = hooks_.find(name);
    if (i == hooks_.end()) {
        return (-1);
    }

    return (i->second);
}

// Return list of hooks

vector<string>
ServerHooks::getHookNames() const {

    vector<string> names;
    HookCollection::const_iterator i;
    for (i = hooks_.begin(); i != hooks_.end(); ++i) {
        names.push_back(i->first);
    }

    return (names);
}


} // namespace util
} // namespace isc
