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
#include <util/hooks/callout_manager.h>

#include <algorithm>
#include <functional>
#include <utility>

using namespace std;
using namespace isc::util;

namespace isc {
namespace util {

// Register a callout for a particular library.

void
CalloutManager::registerCallout(const std::string& name, CalloutPtr callout) {
    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(current_library_);

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = hooks_->getIndex(name);

    // Iterate through the callout vector for the hook from start to end,
    // looking for the first entry where the library index is greater than
    // the present index.
    for (CalloutVector::iterator i = hook_vector_[hook_index].begin();
         i != hook_vector_[hook_index].end(); ++i) {
        if (i->first > current_library_) {
            // Found an element whose library number is greater than ours,
            // so insert the new element ahead of this one.
            hook_vector_[hook_index].insert(i, make_pair(current_library_,
                                                         callout));
            return;
        }
    }

    // Reach the end of the vector, so no element in the (possibly empty)
    // set of callouts with a library index greater that the one related to
    // this callout, insert at the end.
    hook_vector_[hook_index].push_back(make_pair(current_library_, callout));
}

// Check if callouts are present for a given hook index.

bool
CalloutManager::calloutsPresent(int hook_index) const {
    // Validate the hook index.
    checkHookIndex(hook_index);

    // Valid, so are there any callouts associated with that hook?
    return (!hook_vector_[hook_index].empty());
}

// Call all the callouts for a given hook.

int
CalloutManager::callCallouts(int hook_index, CalloutHandle& callout_handle) {
    // Validate the hook index.
    checkHookIndex(hook_index);

    // Clear the "skip" flag so we don't carry state from a previous
    // call.
    callout_handle.setSkip(false);

    // Duplicate the callout vector for this hook and work through that.
    // This step is needed because we allow dynamic registration and
    // deregistration of callouts.  If a callout attached to a hook modified
    // the list of callouts, the underlying CalloutVector would change and
    // potentially affect the iteration through that vector.
    CalloutVector callouts(hook_vector_[hook_index]);

    // Call all the callouts, stopping if a non-zero status is returned.
    int status = 0;

    for (CalloutVector::const_iterator i = callouts.begin();
         i != callouts.end() && (status == 0); ++i) {
        // In case the callout tries to register or deregister a callout, set
        // the current library index to the index associated with the callout
        // being called.
        current_library_ = i->first;

        // Call the callout
        status = (*i->second)(callout_handle);
    }

    // Reset the current library index to an invalid value to catch any
    // programming errors.
    current_library_ = -1;


    return (status);
}

// Deregister a callout registered by a library on a particular hook.

bool
CalloutManager::deregisterCallout(const std::string& name, CalloutPtr callout) {
    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(current_library_);

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = hooks_->getIndex(name);

    /// Construct a CalloutEntry matching the current library and the callout
    /// we want to remove.
    CalloutEntry target(current_library_, callout);

    /// To decide if any entries were removed, we'll record the initial size
    /// of the callout vector for the hook, and compare it with the size after
    /// the removal.
    size_t initial_size = hook_vector_[hook_index].size();

    // The next bit is standard STL (see "Item 33" in "Effective STL" by
    // Scott Meyers).
    //
    // remove_if reorders the hook vector so that all items not matching
    // the predicate are at the start of the vector and returns a pointer
    // to the next element. (In this case, the predicate is that the item
    // is equal to the value of the passed callout.)  The erase() call
    // removes everything from that element to the end of the vector, i.e.
    // all the matching elements.
    hook_vector_[hook_index].erase(remove_if(hook_vector_[hook_index].begin(),
                                             hook_vector_[hook_index].end(),
                                             bind1st(equal_to<CalloutEntry>(),
                                                     target)),
                                   hook_vector_[hook_index].end());

    // Return an indication of whether anything was removed.
    return (initial_size != hook_vector_[hook_index].size());
}

// Deregister all callouts on a given hook.

bool
CalloutManager::deregisterAllCallouts(const std::string& name) {

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = hooks_->getIndex(name);

    /// Construct a CalloutEntry matching the current library (the callout
    /// pointer is NULL as we are not checking that).
    CalloutEntry target(current_library_, NULL);

    /// To decide if any entries were removed, we'll record the initial size
    /// of the callout vector for the hook, and compare it with the size after
    /// the removal.
    size_t initial_size = hook_vector_[hook_index].size();

    // Remove all callouts matching this library.
    hook_vector_[hook_index].erase(remove_if(hook_vector_[hook_index].begin(),
                                             hook_vector_[hook_index].end(),
                                             bind1st(CalloutLibraryEqual(),
                                                     target)),
                                   hook_vector_[hook_index].end());

    // Return an indication of whether anything was removed.
    return (initial_size != hook_vector_[hook_index].size());
}

} // namespace util
} // namespace isc
