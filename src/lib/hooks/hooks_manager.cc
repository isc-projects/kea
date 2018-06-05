// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager_collection.h>
#include <hooks/hooks_manager.h>
#include <hooks/server_hooks.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

using namespace std;

namespace isc {
namespace hooks {

// Constructor

HooksManager::HooksManager() {
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
    conditionallyInitialize();
    return (callout_manager_->calloutsPresent(index));
}

bool
HooksManager::calloutsPresent(int index) {
    return (getHooksManager().calloutsPresentInternal(index));
}

bool
HooksManager::commandHandlersPresentInternal(const std::string& command_name) {
    conditionallyInitialize();
    return (callout_manager_->commandHandlersPresent(command_name));
}

bool
HooksManager::commandHandlersPresent(const std::string& command_name) {
    return (getHooksManager().commandHandlersPresentInternal(command_name));
}

// Call the callouts

void
HooksManager::callCalloutsInternal(int index, CalloutHandle& handle) {
    conditionallyInitialize();
    callout_manager_->callCallouts(index, handle);
}

void
HooksManager::callCallouts(int index, CalloutHandle& handle) {
    getHooksManager().callCalloutsInternal(index, handle);
}

void
HooksManager::callCommandHandlersInternal(const std::string& command_name,
                                          CalloutHandle& handle) {
    conditionallyInitialize();
    callout_manager_->callCommandHandlers(command_name, handle);
}

void
HooksManager::callCommandHandlers(const std::string& command_name,
                                  CalloutHandle& handle) {
    getHooksManager().callCommandHandlersInternal(command_name, handle);
}


// Load the libraries.  This will delete the previously-loaded libraries
// (if present) and load new ones.

bool
HooksManager::loadLibrariesInternal(const HookLibsCollection& libraries) {
    // Unload current set of libraries (if any are loaded).
    unloadLibrariesInternal();

    // Create the library manager and load the libraries.
    lm_collection_.reset(new LibraryManagerCollection(libraries));
    bool status = lm_collection_->loadLibraries();

    if (status) {
        // ... and obtain the callout manager for them if successful.
        callout_manager_ = lm_collection_->getCalloutManager();
    } else {
        // Unable to load libraries, reset to state before this function was
        // called.
        lm_collection_.reset();
        callout_manager_.reset();
    }

    return (status);
}

bool
HooksManager::loadLibraries(const HookLibsCollection& libraries) {
    return (getHooksManager().loadLibrariesInternal(libraries));
}

// Unload the libraries.  This just deletes all internal objects which will
// cause the libraries to be unloaded.

void
HooksManager::unloadLibrariesInternal() {
    // The order of deletion does not matter here, as each library manager
    // holds its own pointer to the callout manager.  However, we may as
    // well delete the library managers first: if there are no other references
    // to the callout manager, the second statement will delete it, which may
    // ease debugging.
    lm_collection_.reset();
    callout_manager_.reset();
    ServerHooks::getServerHooks().getParkingLotsPtr()->clear();
}

void HooksManager::unloadLibraries() {
    getHooksManager().unloadLibrariesInternal();
}

// Create a callout handle

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandleInternal() {
    conditionallyInitialize();
    return (boost::shared_ptr<CalloutHandle>(
            new CalloutHandle(callout_manager_, lm_collection_)));
}

boost::shared_ptr<CalloutHandle>
HooksManager::createCalloutHandle() {
    return (getHooksManager().createCalloutHandleInternal());
}

// Get the list of the names of loaded libraries.

std::vector<std::string>
HooksManager::getLibraryNamesInternal() const {
    return (lm_collection_ ? lm_collection_->getLibraryNames()
                           : std::vector<std::string>());
}

HookLibsCollection
HooksManager::getLibraryInfoInternal() const {
    return (lm_collection_ ? lm_collection_->getLibraryInfo()
            : HookLibsCollection());
}

std::vector<std::string>
HooksManager::getLibraryNames() {
    return (getHooksManager().getLibraryNamesInternal());
}

HookLibsCollection
HooksManager::getLibraryInfo() {
    return (getHooksManager().getLibraryInfoInternal());
}

// Perform conditional initialization if nothing is loaded.

void
HooksManager::performConditionalInitialization() {

    // Nothing present, so create the collection with any empty set of
    // libraries, and get the CalloutManager.
    HookLibsCollection libraries;
    lm_collection_.reset(new LibraryManagerCollection(libraries));
    lm_collection_->loadLibraries();

    callout_manager_ = lm_collection_->getCalloutManager();
}

// Shell around ServerHooks::registerHook()

int
HooksManager::registerHook(const std::string& name) {
    return (ServerHooks::getServerHooks().registerHook(name));
}

// Return pre- and post- library handles.

isc::hooks::LibraryHandle&
HooksManager::preCalloutsLibraryHandleInternal() {
    conditionallyInitialize();
    return (callout_manager_->getPreLibraryHandle());
}

isc::hooks::LibraryHandle&
HooksManager::preCalloutsLibraryHandle() {
    return (getHooksManager().preCalloutsLibraryHandleInternal());
}

isc::hooks::LibraryHandle&
HooksManager::postCalloutsLibraryHandleInternal() {
    conditionallyInitialize();
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

// Shared callout manager
boost::shared_ptr<CalloutManager>&
HooksManager::getSharedCalloutManager() {
    return (getHooksManager().shared_callout_manager_);
}

} // namespace util
} // namespace isc
