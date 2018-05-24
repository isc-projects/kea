// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks_log.h>
#include <hooks/server_hooks.h>

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
using namespace isc;

namespace isc {
namespace hooks {

// Constructor - register the pre-defined hooks and check that the indexes
// assigned to them are as expected.
//
// Note that there are no logging messages here or in registerHooks().  The
// recommended way to initialize hook names is to use static initialization.
// Here, a static object is declared in a file outside of any function or
// method.  As a result, it is instantiated and its constructor run before the
// program starts.  By putting calls to ServerHooks::registerHook() in there,
// hooks names are already registered when the program runs.  However, at that
// point, the logging system is not initialized, so messages are unable to
// be output.

ServerHooks::ServerHooks() {
    initialize();
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

    /// @todo: We also need to call CalloutManager::ensureVectorSize(), so it
    /// adjusts its vector. Since CalloutManager is not a singleton, there's
    /// no getInstance() or similar. Also, CalloutManager uses ServerHooks,
    /// so such a call would induce circular dependencies. Ugh.

    if (!result.second) {

        // There's a problem with hook libraries that need to be linked with
        // libdhcpsrv. For example host_cmds hook library requires host
        // parser, so it needs to be linked with libdhcpsrv. However, when
        // unit-tests are started, the hook points are not registered.
        // When the library is loaded new hook points are registered.
        // This causes issues in the hooks framework, especially when
        // LibraryManager::unloadLibrary() iterates through all hooks
        // and then calls deregisterAllCallouts. This method gets
        // hook_index that is greater than number of elements in
        // hook_vector_ and then we have a read past the array boundary.
        /// @todo: See ticket 5251 and 5208 for details.
        return (getIndex(name));

        // New element was not inserted because an element with the same name
        // already existed.
        //isc_throw(DuplicateHook, "hook with name " << name <<
        //         " is already registered");
    }

    // Element was inserted, so add to the inverse hooks collection.
    inverse_hooks_[index] = name;

    // ... and return numeric index.
    return (index);
}

// Set ServerHooks object to initial state.

void
ServerHooks::initialize() {

    // Clear out the name->index and index->name maps.
    hooks_.clear();
    inverse_hooks_.clear();
    parking_lots_.reset(new ParkingLots());

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

// Reset ServerHooks object to initial state.

void
ServerHooks::reset() {

    // Clear all hooks then initialize the pre-defined ones.
    initialize();

    // Log a warning - although this is done during testing, it should never be
    // seen in a production system.
    LOG_WARN(hooks_logger, HOOKS_HOOK_LIST_RESET);
}

// Find the name associated with a hook index.

std::string
ServerHooks::getName(int index) const {

    // Get iterator to matching element.
    InverseHookCollection::const_iterator i = inverse_hooks_.find(index);
    if (i == inverse_hooks_.end()) {
        isc_throw(NoSuchHook, "hook index " << index << " is not recognized");
    }

    return (i->second);
}

// Find the index associated with a hook name.

int
ServerHooks::getIndex(const string& name) const {

    // Get iterator to matching element.
    HookCollection::const_iterator i = hooks_.find(name);
    if (i == hooks_.end()) {
        isc_throw(NoSuchHook, "hook name " << name << " is not recognized");
    }

    return (i->second);
}

int
ServerHooks::findIndex(const std::string& name) const {
    // Get iterator to matching element.
    auto i = hooks_.find(name);
    return ((i == hooks_.end()) ? -1 : i->second);
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
    return (*getServerHooksPtr());
}

ServerHooksPtr
ServerHooks::getServerHooksPtr() {
    static ServerHooksPtr hooks(new ServerHooks());
    return (hooks);
}

ParkingLotsPtr
ServerHooks::getParkingLotsPtr() const {
    return (parking_lots_);
}

ParkingLotPtr
ServerHooks::getParkingLotPtr(const int hook_index) {
    return (parking_lots_->getParkingLotPtr(hook_index));
}

ParkingLotPtr
ServerHooks::getParkingLotPtr(const std::string& hook_name) {
    return (parking_lots_->getParkingLotPtr(getServerHooks().getIndex(hook_name)));
}

std::string
ServerHooks::commandToHookName(const std::string& command_name) {
    // Prefix the command name with a dollar sign.
    std::string hook_name = std::string("$") + command_name;
    // Replace all hyphens with underscores.
    std::replace(hook_name.begin(), hook_name.end(), '-', '_');
    return (hook_name);
}

std::string
ServerHooks::hookToCommandName(const std::string& hook_name) {
    if (!hook_name.empty() && hook_name.front() == '$') {
        std::string command_name = hook_name.substr(1);
        std::replace(command_name.begin(), command_name.end(), '_', '-');
        return (command_name);
    }
    return ("");
}



} // namespace hooks
} // namespace isc
