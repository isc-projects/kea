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
#include <hooks/hooks_log.h>
#include <hooks/server_hooks.h>

#include <utility>
#include <vector>

using namespace std;
using namespace isc;

namespace isc {
namespace hooks {

// Constructor - register the pre-defined hooks and check that the indexes
// assigned to them are as expected.

ServerHooks::ServerHooks() {
    reset();
}

// Register a hook.  The index assigned to the hook is the current number
// of entries in the collection, so ensuring that hook indexes are unique
// and non-negative.

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

    // Element was inserted, so add to the inverse hooks collection.
    inverse_hooks_[index] = name;

    // Log it if debug is enabled
    LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_REGISTER_HOOK).arg(name);

    // ... and return numeric index.
    return (index);
}

// Reset ServerHooks object to initial state.

void
ServerHooks::reset() {
    // Log a warning - although this is done during testing, it should never be
    // seen in a production system.
    LOG_WARN(hooks_logger, HOOKS_RESET_HOOK_LIST);

    // Clear out the name->index and index->name maps.
    hooks_.clear();
    inverse_hooks_.clear();

    // Register the pre-defined hooks.
    int create = registerHook("context_create");
    int destroy = registerHook("context_destroy");

    // Check registration went as expected.
    if ((create != CONTEXT_CREATE) || (destroy != CONTEXT_DESTROY)) {
        isc_throw(Unexpected, "pre-defined hook indexes are not as expected. "
                  "context_create: expected = " << CONTEXT_CREATE <<
                  ", actual = " << create <<
                  ". context_destroy: expected = " << CONTEXT_DESTROY <<
                  ", actual = " << destroy);
    }
}

// Find the name associated with a hook index.

std::string
ServerHooks::getName(int index) const {

    // Get iterator to matching element.
    InverseHookCollection::const_iterator i = inverse_hooks_.find(index);
    if (i == inverse_hooks_.end()) {
        isc_throw(NoSuchHook, "hook index " << index << " is not recognised");
    }

    return (i->second);
}

// Find the index associated with a hook name.

int
ServerHooks::getIndex(const string& name) const {

    // Get iterator to matching element.
    HookCollection::const_iterator i = hooks_.find(name);
    if (i == hooks_.end()) {
        isc_throw(NoSuchHook, "hook name " << name << " is not recognised");
    }

    return (i->second);
}

// Return vector of hook names.  The names are not sorted - it is up to the
// caller to perform sorting if required.

vector<string>
ServerHooks::getHookNames() const {

    vector<string> names;
    HookCollection::const_iterator i;
    for (i = hooks_.begin(); i != hooks_.end(); ++i) {
        names.push_back(i->first);
    }

    return (names);
}

// Return global ServerHooks object

ServerHooks&
ServerHooks::getServerHooks() {
    static ServerHooks hooks;
    return (hooks);
}


} // namespace util
} // namespace isc
