// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    : server_hooks_(ServerHooks::getServerHooks()), current_library_(-1),
      hook_vector_(ServerHooks::getServerHooks().getCount()),
      library_handle_(*this), pre_library_handle_(*this, 0),
      post_library_handle_(*this, INT_MAX), num_libraries_(num_libraries) {
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
CalloutManager::registerCallout(const std::string& name,
                                CalloutPtr callout,
                                int library_index) {
    // Note the registration.
    LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUT_REGISTRATION)
        .arg(library_index).arg(name);

    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(library_index);

    // New hooks could have been registered since the manager was constructed.
    ensureHookLibsVectorSize();

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

    // Iterate through the callout vector for the hook from start to end,
    // looking for the first entry where the library index is greater than
    // the present index.
    for (CalloutVector::iterator i = hook_vector_[hook_index].begin();
         i != hook_vector_[hook_index].end(); ++i) {
        if (i->first > library_index) {
            // Found an element whose library index number is greater than the
            // current index, so insert the new element ahead of this one.
            hook_vector_[hook_index].insert(i, make_pair(library_index,
                                                         callout));
            return;
        }
    }

    // Reached the end of the vector, so there is no element in the (possibly
    // empty) set of callouts with a library index greater than the current
    // library index.  Inset the callout at the end of the list.
    hook_vector_[hook_index].push_back(make_pair(library_index, callout));
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

bool
CalloutManager::commandHandlersPresent(const std::string& command_name) const {
    // Check if the hook point for the specified command exists.
    int index = ServerHooks::getServerHooks().findIndex(
                    ServerHooks::commandToHookName(command_name));
    if (index >= 0) {
        // The hook point exits but it is possible that there are no
        // callouts/command handlers. This is possible if there was a
        // hook library supporting this command attached, but it was
        // later unloaded. The hook points are not deregistered in
        // this case. Only callouts are deregistered.
        // Let's check if callouts are present for this hook point.
        return (calloutsPresent(index));
    }

    // Hook point not created, so we don't support this command in
    // any of the hooks libraries.
    return (false);
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
        callout_handle.setCurrentHook(hook_index);

        // This object will be used to measure execution time of each callout
        // and the total time spent in callouts for this hook point.
        util::Stopwatch stopwatch;

        // Mark that the callouts begin for the hook.
        LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUTS_BEGIN)
            .arg(server_hooks_.getName(callout_handle.getCurrentHook()));

        // Call all the callouts.
        for (CalloutVector::const_iterator i = hook_vector_[hook_index].begin();
             i != hook_vector_[hook_index].end(); ++i) {
            // In case the callout requires access to the context associated
            // with the library, set the current library index to the index
            // associated with the library that registered the callout being
            // called.
            callout_handle.setCurrentLibrary(i->first);

            // Call the callout
            try {
                stopwatch.start();
                int status = (*i->second)(callout_handle);
                stopwatch.stop();
                if (status == 0) {
                    LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                              HOOKS_CALLOUT_CALLED)
                        .arg(callout_handle.getCurrentLibrary())
                        .arg(server_hooks_.getName(callout_handle.getCurrentHook()))
                        .arg(PointerConverter(i->second).dlsymPtr())
                        .arg(stopwatch.logFormatLastDuration());
                } else {
                    LOG_ERROR(callouts_logger, HOOKS_CALLOUT_ERROR)
                        .arg(callout_handle.getCurrentLibrary())
                        .arg(server_hooks_.getName(callout_handle.getCurrentHook()))
                        .arg(PointerConverter(i->second).dlsymPtr())
                        .arg(stopwatch.logFormatLastDuration());
                }
            } catch (const std::exception& e) {
                // If an exception occurred, the stopwatch.stop() hasn't been
                // called, so we have to call it here.
                stopwatch.stop();
                // Any exception, not just ones based on isc::Exception
                LOG_ERROR(callouts_logger, HOOKS_CALLOUT_EXCEPTION)
                    .arg(callout_handle.getCurrentLibrary())
                    .arg(server_hooks_.getName(callout_handle.getCurrentHook()))
                    .arg(PointerConverter(i->second).dlsymPtr())
                    .arg(e.what())
                    .arg(stopwatch.logFormatLastDuration());
            }

        }

        // Mark end of callout execution. Include the total execution
        // time for callouts.
        LOG_DEBUG(callouts_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUTS_COMPLETE)
            .arg(server_hooks_.getName(callout_handle.getCurrentHook()))
            .arg(stopwatch.logFormatTotalDuration());

        // Reset the current hook and library indexes to an invalid value to
        // catch any programming errors.
        callout_handle.setCurrentHook(-1);
        callout_handle.setCurrentLibrary(-1);
    }
}

void
CalloutManager::callCommandHandlers(const std::string& command_name,
                                    CalloutHandle& callout_handle) {
    // Get the index of the hook point for the specified command.
    // This will throw an exception if the hook point doesn't exist.
    // The caller should check if the hook point exists by calling
    // commandHandlersPresent.
    int index = ServerHooks::getServerHooks().getIndex(
                    ServerHooks::commandToHookName(command_name));
    // Call the handlers for this command.
    callCallouts(index, callout_handle);
}


// Deregister a callout registered by the current library on a particular hook.

bool
CalloutManager::deregisterCallout(const std::string& name, CalloutPtr callout,
                                  int library_index) {
    // Sanity check that the current library index is set to a valid value.
    checkLibraryIndex(library_index);

    // New hooks could have been registered since the manager was constructed.
    ensureHookLibsVectorSize();

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

    // New hooks can have been registered since the manager was constructed.
    if (hook_index >= hook_vector_.size()) {
        return (false);
    }

    /// Construct a CalloutEntry matching the current library and the callout
    /// we want to remove.
    CalloutEntry target(library_index, callout);

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
                                             [&target] (CalloutEntry x) {
                                                 return (x == target); }),
                                   hook_vector_[hook_index].end());

    // Return an indication of whether anything was removed.
    bool removed = initial_size != hook_vector_[hook_index].size();
    if (removed) {
        LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                  HOOKS_CALLOUT_DEREGISTERED).arg(library_index).arg(name);
    }

    return (removed);
}

// Deregister all callouts on a given hook.

bool
CalloutManager::deregisterAllCallouts(const std::string& name,
                                      int library_index) {
    // New hooks could have been registered since the manager was constructed.
    ensureHookLibsVectorSize();

    // Get the index associated with this hook (validating the name in the
    // process).
    int hook_index = server_hooks_.getIndex(name);

    /// Construct a CalloutEntry matching the current library (the callout
    /// pointer is NULL as we are not checking that).
    CalloutEntry target(library_index, static_cast<CalloutPtr>(0));

    /// To decide if any entries were removed, we'll record the initial size
    /// of the callout vector for the hook, and compare it with the size after
    /// the removal.
    size_t initial_size = hook_vector_[hook_index].size();

    // Remove all callouts matching this library.
    hook_vector_[hook_index].erase(remove_if(hook_vector_[hook_index].begin(),
                                             hook_vector_[hook_index].end(),
                                             [&target] (CalloutEntry x) {
                                                 return (x.first == target.first);
                                             }),
                                   hook_vector_[hook_index].end());

    // Return an indication of whether anything was removed.
    bool removed = initial_size != hook_vector_[hook_index].size();
    if (removed) {
        LOG_DEBUG(callouts_logger, HOOKS_DBG_EXTENDED_CALLS,
                  HOOKS_ALL_CALLOUTS_DEREGISTERED).arg(library_index).arg(name);
    }

    return (removed);
}

void
CalloutManager::registerCommandHook(const std::string& command_name) {
    // New hooks could have been registered since the manager was constructed.
    ensureHookLibsVectorSize();

    ServerHooks& hooks = ServerHooks::getServerHooks();
    int hook_index = hooks.findIndex(ServerHooks::commandToHookName(command_name));
    if (hook_index < 0) {
        // Hook for this command doesn't exist. Let's create one.
        hooks.registerHook(ServerHooks::commandToHookName(command_name));
        // Callout Manager's vector of hooks have to be resized to hold the
        // information about callouts for this new hook point. This should
        // add new element at the end of the hook_vector_. The index of this
        // element will match the index of the hook point in the ServerHooks
        // because ServerHooks allocates indexes incrementally.
        hook_vector_.resize(server_hooks_.getCount());
    }
}

void
CalloutManager::ensureHookLibsVectorSize() {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    if (hooks.getCount() > hook_vector_.size()) {
        // Uh oh, there are more hook points that our vector allows.
        hook_vector_.resize(hooks.getCount());
    }
}

} // namespace util
} // namespace isc
