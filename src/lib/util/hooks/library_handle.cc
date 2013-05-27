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

#include <util/hooks/callout_handle.h>
#include <util/hooks/library_handle.h>

#include <algorithm>
#include <functional>

using namespace std;
using namespace isc::util;

namespace isc {
namespace util {

// Check that an index is valid for the hook vector
void
LibraryHandle::checkHookIndex(int index) const {
    if ((index < 0) || (index >= hook_vector_.size())) {
        isc_throw(NoSuchHook, "hook index " << index << " is invalid for the "
                  " size of the hook vector (" << hook_vector_.size() << ")");
    }
}

// Get index for named hook
int
LibraryHandle::getHookIndex(const std::string& name) const {

    // Get index of hook in the hook vector.
    int index = hooks_->getIndex(name);
    if (index < 0) {
        isc_throw(NoSuchHook, "unknown hook: " << name);
    } else if (index >= hook_vector_.size()) {
        isc_throw(Unexpected, "hook name " << name << " is valid, but the "
                  "index returned (" << index << ") is invalid for the size of "
                  "the LibraryHandle::hook_vector_ (" << hook_vector_.size() <<
                  ")");
    }

    return (index);
}

// Register a callout at the back of the named hook

void
LibraryHandle::registerCallout(const std::string& name, CalloutPtr callout) {

    // Get index of hook in the hook vector, validating the hook name as we
    // do so.
    int index = getHookIndex(name);

    // Index valid, so add the callout to the end of the list.
    hook_vector_[index].push_back(callout);
}

// Check if callouts are present for a given hook index.

bool
LibraryHandle::calloutsPresent(int index) const {

    // Validate the hook index.
    checkHookIndex(index);

    // Valid, so are there any callouts associated with that hook?
    return (!hook_vector_[index].empty());
}

// Call all the callouts for a given hook.

int
LibraryHandle::callCallouts(int index, CalloutHandle& handle) {

    // Validate the hook index.
    checkHookIndex(index);

    // Call all the callouts, stopping if a non-zero status is returned.
    // @todo also need to stop if the callout handle "skip" flag is set.
    int status = 0;
    for (int i = 0;
         (i < hook_vector_[index].size()) && !handle.getSkip() && (status == 0);
          ++i) {
        status = (*hook_vector_[index][i])(handle);
    }

    return (status);
}

// Deregister a callout

void
LibraryHandle::deregisterCallout(const std::string& name, CalloutPtr callout) {

    // Get the index associated with this hook (validating the name in the
    // process).
    int index = getHookIndex(name);

    if (!hook_vector_[index].empty()) {
        // The next bit is standard STL (see "Item 33" in "Effective STL" by
        // Scott Meyters.
        //
        // remove_if reorders the hook vector so that all items not matching
        // the predicate are at the start of the vector, and returns a pointer
        // to the next element. (In this case, the predicate is that the item
        // is equal to the value of the passed callout.)  The erase() call
        // removes everything from that element to the end of the vector, i.e.
        // all the matching elements.
        hook_vector_[index].erase(remove_if(hook_vector_[index].begin(),
                                            hook_vector_[index].end(),
                                            bind1st(equal_to<CalloutPtr>(),
                                                    callout)),
                                  hook_vector_[index].end());
    }
}

// Deregister all callouts

void
LibraryHandle::deregisterAll(const std::string& name) {

    // Get the index associated with this hook (validating the name in the
    // process).
    int index = getHookIndex(name);

    // Get rid of everything.
    hook_vector_[index].clear();
}

// return the name of all context items.

vector<string>
LibraryHandle::getContextNames() const {

    vector<string> names;
    ContextCollection::const_iterator i;
    for (i = context_.begin(); i != context_.end(); ++i) {
        names.push_back(i->first);
    }

    return (names);
}

} // namespace util
} // namespace isc
