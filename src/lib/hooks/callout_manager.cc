// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_log.h>
#include <hooks/pointer_converter.h>
#include <util/stopwatch.h>

#include <boost/static_assert.hpp>

#include <algorithm>
#include <climits>
#include <functional>
#include <utility>

using namespace std;

namespace isc {
namespace hooks {

// Constructor
CalloutManager::CalloutManager(int num_libraries)
    : server_hooks_(ServerHooks::getServerHooks()),
      current_hook_(-1), current_library_(-1),
      hook_vector_(ServerHooks::getServerHooks().getCount()),
      library_handle_(this), pre_library_handle_(this, 0),
      post_library_handle_(this, INT_MAX), num_libraries_(num_libraries)
{
    if (num_libraries < 0) {
        isc_throw(isc::BadValue, "number of libraries passed to the "
                  "CalloutManager must be >= 0");
    }
}

// Check that the index of a library is valid.  It can range from 1 - n
// (n is the number of libraries), 0 (pre-user library callouts), or INT_MAX
// (post-user library callouts).  It can also be -1 to indicate an invalid
// value.

void
CalloutManager::checkLibraryIndex(int library_index) const {
    if (((library_index >= -1) && (library_index <= num_libraries_)) ||
        (library_index == INT_MAX)) {
        return;
    }

    isc_throw(NoSuchLibrary, "library index " << library_index <<
              " is not valid for the number of loaded libraries (" <<
              num_libraries_ << ")");
}

// Register a callout for the current library.

void
CalloutManager::registerCallout(const std::string& name, CalloutPtr callout) {
    // Note the registration.
    LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUT_REGISTRATION)
        .arg(current_library_).arg(name);

    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(current_library_);

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

    // Iterate through the callout vector for the hook from start to end,
    // looking for the first entry where the library index is greater than
    // the present index.
    for (CalloutVector::iterator i = hook_vector_[hook_index].begin();
         i != hook_vector_[hook_index].end(); ++i) {
        if (i->first > current_library_) {
            // Found an element whose library index number is greater than the
            // current index, so insert the new element ahead of this one.
            hook_vector_[hook_index].insert(i, make_pair(current_library_,
                                                         callout));
            return;
        }
    }

    // Reached the end of the vector, so there is no element in the (possibly
    // empty) set of callouts with a library index greater than the current
    // library index.  Inset the callout at the end of the list.
    hook_vector_[hook_index].push_back(make_pair(current_library_, callout));
}

// Check if callouts are present for a given hook index.

bool
CalloutManager::calloutsPresent(int hook_index) const {
    // Validate the hook index.
    if ((hook_index < 0) || (hook_index >= hook_vector_.size())) {
        isc_throw(NoSuchHook, "hook index " << hook_index <<
                  " is not valid for the list of registered hooks");
    }

    // Valid, so are there any callouts associated with that hook?
    return (!hook_vector_[hook_index].empty());
}

// Call all the callouts for a given hook.

void
CalloutManager::callCallouts(int hook_index, CalloutHandle& callout_handle) {

    // Clear the "skip" flag so we don't carry state from a previous call.
    // This is done regardless of whether callouts are present to avoid passing
    // any state from the previous call of callCallouts().
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_CONTINUE);

    // Only initialize and iterate if there are callouts present.  This check
    // also catches the case of an invalid index.
    if (calloutsPresent(hook_index)) {

        // Set the current hook index.  This is used should a callout wish to
        // determine to what hook it is attached.
        current_hook_ = hook_index;

        // Duplicate the callout vector for this hook and work through that.
        // This step is needed because we allow dynamic registration and
        // deregistration of callouts.  If a callout attached to a hook modified
        // the list of callouts on that hook, the underlying CalloutVector would
        // change and potentially affect the iteration through that vector.
        CalloutVector callouts(hook_vector_[hook_index]);

        // This object will be used to measure execution time of each callout
        // and the total time spent in callouts for this hook point.
        util::Stopwatch stopwatch;

        // Mark that the callouts begin for the hook.
        LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUTS_BEGIN)
            .arg(server_hooks_.getName(current_hook_));

        // Call all the callouts.
        for (CalloutVector::const_iterator i = callouts.begin();
             i != callouts.end(); ++i) {
            // In case the callout tries to register or deregister a callout,
            // set the current library index to the index associated with the
            // library that registered the callout being called.
            current_library_ = i->first;

            // Call the callout
            try {
                stopwatch.start();
                int status = (*i->second)(callout_handle);
                stopwatch.stop();
                if (status == 0) {
                    LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                              HOOKS_CALLOUT_CALLED).arg(current_library_)
                        .arg(server_hooks_.getName(current_hook_))
                        .arg(PointerConverter(i->second).dlsymPtr())
                        .arg(stopwatch.logFormatLastDuration());
                } else {
                    LOG_ERROR(callouts_logger, HOOKS_CALLOUT_ERROR)
                        .arg(current_library_)
                        .arg(server_hooks_.getName(current_hook_))
                        .arg(PointerConverter(i->second).dlsymPtr())
                        .arg(stopwatch.logFormatLastDuration());
                }
            } catch (const std::exception& e) {
                // If an exception occurred, the stopwatch.stop() hasn't been
                // called, so we have to call it here.
                stopwatch.stop();
                // Any exception, not just ones based on isc::Exception
                LOG_ERROR(callouts_logger, HOOKS_CALLOUT_EXCEPTION)
                    .arg(current_library_)
                    .arg(server_hooks_.getName(current_hook_))
                    .arg(PointerConverter(i->second).dlsymPtr())
                    .arg(e.what())
                    .arg(stopwatch.logFormatLastDuration());
            }

        }

        // Mark end of callout execution. Include the total execution
        // time for callouts.
        LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUTS_COMPLETE)
            .arg(server_hooks_.getName(current_hook_))
            .arg(stopwatch.logFormatTotalDuration());

        // Reset the current hook and library indexs to an invalid value to
        // catch any programming errors.
        current_hook_ = -1;
        current_library_ = -1;
    }
}

// Deregister a callout registered by the current library on a particular hook.

bool
CalloutManager::deregisterCallout(const std::string& name, CalloutPtr callout) {
    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(current_library_);

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

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
    bool removed = initial_size != hook_vector_[hook_index].size();
    if (removed) {
        LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                  HOOKS_CALLOUT_DEREGISTERED).arg(current_library_).arg(name);
    }

    return (removed);
}

// Deregister all callouts on a given hook.

bool
CalloutManager::deregisterAllCallouts(const std::string& name) {

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

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
    bool removed = initial_size != hook_vector_[hook_index].size();
    if (removed) {
        LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                  HOOKS_ALL_CALLOUTS_DEREGISTERED).arg(current_library_)
                                                .arg(name);
    }

    return (removed);
}

} // namespace util
} // namespace isc
