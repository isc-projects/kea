// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager_collection.h>
#include <hooks/hooks_manager.h>
#include <hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <string>
#include <vector>

using namespace std;

namespace isc {
namespace hooks {

// Constructor

HooksManager::HooksManager() : test_mode_(false) {
    // Nothing present, so create the collection with any empty set of
    // libraries, and get the CalloutManager.
    HookLibsCollection libraries;
    lm_collection_.reset(new LibraryManagerCollection(libraries));
    lm_collection_->loadLibraries();
    callout_manager_ = lm_collection_->getCalloutManager();
}

// Return reference to singleton hooks manager.

HooksManager&
HooksManager::getHooksManager() {
    static HooksManager manager;
    return (manager);
}

// Are callouts present?

bool
HooksManager::calloutsPresentInternal(int index) {
    return (callout_manager_->calloutsPresent(index));
}

bool
HooksManager::calloutsPresent(int index) {
    return (getHooksManager().calloutsPresentInternal(index));
}

bool
HooksManager::commandHandlersPresentInternal(const std::string& command_name) {
    return (callout_manager_->commandHandlersPresent(command_name));
}

bool
HooksManager::commandHandlersPresent(const std::string& command_name) {
    return (getHooksManager().commandHandlersPresentInternal(command_name));
}

// Call the callouts

void
HooksManager::callCalloutsInternal(int index, CalloutHandle& handle) {
    callout_manager_->callCallouts(index, handle);
}

void
HooksManager::callCallouts(int index, CalloutHandle& handle) {
    getHooksManager().callCalloutsInternal(index, handle);
}

void
HooksManager::callCommandHandlersInternal(const std::string& command_name,
                                          CalloutHandle& handle) {
    callout_manager_->callCommandHandlers(command_name, handle);
}

void
HooksManager::callCommandHandlers(const std::string& command_name,
                                  CalloutHandle& handle) {
    getHooksManager().callCommandHandlersInternal(command_name, handle);
}

// Load the libraries.  This will delete the previously-loaded libraries
// (if present) and load new ones. If loading libraries fails, initialize with
// empty list.

bool
HooksManager::loadLibrariesInternal(const HookLibsCollection& libraries) {
    if (test_mode_) {
        return (true);
    }

    ServerHooks::getServerHooks().getParkingLotsPtr()->clear();

    // Keep a weak pointer on the existing library manager collection.
    boost::weak_ptr<LibraryManagerCollection> weak_lmc(lm_collection_);

    // Create the library manager collection.
    lm_collection_.reset(new LibraryManagerCollection(libraries));

    // If there was another owner the previous library manager collection
    // was not destroyed and libraries not closed.
    if (!weak_lmc.expired()) {
        isc_throw(LibrariesStillOpened, "some libraries are still opened");
    }

    // Load the libraries.
    bool status = lm_collection_->loadLibraries();

    if (status) {
        // ... and obtain the callout manager for them if successful.
        callout_manager_ = lm_collection_->getCalloutManager();
    } else {
        // Unable to load libraries, reset to state before this function was
        // called.
        static_cast<void>(unloadLibrariesInternal());
    }

    return (status);
}

bool
HooksManager::loadLibraries(const HookLibsCollection& libraries) {
    return (getHooksManager().loadLibrariesInternal(libraries));
}

// Unload the libraries.  This just deletes all internal objects (which will
// cause the libraries to be unloaded) and initializes them with empty list if
// requested.

bool
HooksManager::unloadLibrariesInternal() {
    if (test_mode_) {
        return (true);
    }

    ServerHooks::getServerHooks().getParkingLotsPtr()->clear();

    // Keep a weak pointer on the existing library manager collection.
    boost::weak_ptr<LibraryManagerCollection> weak_lmc(lm_collection_);

    // Create the collection with any empty set of libraries.
    HookLibsCollection libraries;
    lm_collection_.reset(new LibraryManagerCollection(libraries));

    // If there was another owner the previous library manager collection
    // was not destroyed and libraries not closed.
    boost::shared_ptr<LibraryManagerCollection> still_here = weak_lmc.lock();
    if (still_here) {
        // Restore the library manager collection.
        lm_collection_ = still_here;
        return (false);
    }

    // Load the empty set of libraries.
    lm_collection_->loadLibraries();

    // Get the CalloutManager.
    callout_manager_ = lm_collection_->getCalloutManager();

    return (true);
}

bool
HooksManager::unloadLibraries() {
    return (getHooksManager().unloadLibrariesInternal());
}

void
HooksManager::prepareUnloadLibrariesInternal() {
    if (test_mode_) {
        return;
    }

    static_cast<void>(lm_collection_->prepareUnloadLibraries());
}

void
HooksManager::prepareUnloadLibraries() {
    getHooksManager().prepareUnloadLibrariesInternal();
}

// Create a callout handle

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandleInternal() {
    return (boost::make_shared<CalloutHandle>(callout_manager_, lm_collection_));
}

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandle() {
    return (getHooksManager().createCalloutHandleInternal());
}

// Get the list of the names of loaded libraries.

std::vector<std::string>
HooksManager::getLibraryNamesInternal() const {
    return (lm_collection_->getLibraryNames());
}

HookLibsCollection
HooksManager::getLibraryInfoInternal() const {
    return (lm_collection_->getLibraryInfo());
}

std::vector<std::string>
HooksManager::getLibraryNames() {
    return (getHooksManager().getLibraryNamesInternal());
}

HookLibsCollection
HooksManager::getLibraryInfo() {
    return (getHooksManager().getLibraryInfoInternal());
}

// Shell around ServerHooks::registerHook()

int
HooksManager::registerHook(const std::string& name) {
    return (ServerHooks::getServerHooks().registerHook(name));
}

// Return pre- and post- library handles.

isc::hooks::LibraryHandle&
HooksManager::preCalloutsLibraryHandleInternal() {
    return (callout_manager_->getPreLibraryHandle());
}

isc::hooks::LibraryHandle&
HooksManager::preCalloutsLibraryHandle() {
    return (getHooksManager().preCalloutsLibraryHandleInternal());
}

isc::hooks::LibraryHandle&
HooksManager::postCalloutsLibraryHandleInternal() {
    return (callout_manager_->getPostLibraryHandle());
}

isc::hooks::LibraryHandle&
HooksManager::postCalloutsLibraryHandle() {
    return (getHooksManager().postCalloutsLibraryHandleInternal());
}

// Validate libraries

std::vector<std::string>
HooksManager::validateLibraries(const std::vector<std::string>& libraries) {
    return (LibraryManagerCollection::validateLibraries(libraries));
}

// Test mode

void
HooksManager::setTestMode(bool mode) {
    getHooksManager().test_mode_ = mode;
}

bool
HooksManager::getTestMode() {
    return (getHooksManager().test_mode_);
}

} // namespace util
} // namespace isc
