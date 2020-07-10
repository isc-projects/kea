// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/hooks_manager.h>

#include <iostream>

namespace isc {
namespace hooks {

// Callout manipulation - all deferred to the CalloutManager.

void
LibraryHandle::registerCallout(const std::string& name, CalloutPtr callout) {
    int index = index_;

    if (index_ == -1) {
        // -1 means that current index is stored in CalloutManager.
        // So let's get the index from there. See comment for
        // LibraryHandle::index_.
        index = callout_manager_.getLibraryIndex();
    }

    // Register the callout.
    callout_manager_.registerCallout(name, callout, index);
}

void
LibraryHandle::registerCommandCallout(const std::string& command_name,
                                      CalloutPtr callout) {
    // Register hook point for this command, if one doesn't exist.
    callout_manager_.registerCommandHook(command_name);
    // Register the command handler as a callout.
    registerCallout(ServerHooks::commandToHookName(command_name), callout);
}


bool
LibraryHandle::deregisterCallout(const std::string& name, CalloutPtr callout) {
    int index = index_;

    if (index_ == -1) {
        // -1 means that current index is stored in CalloutManager.
        // So let's get the index from there. See comment for
        // LibraryHandle::index_.
        index = callout_manager_.getLibraryIndex();
    }

    return (callout_manager_.deregisterCallout(name, callout, index));
}

bool
LibraryHandle::deregisterAllCallouts(const std::string& name) {
    int index = index_;

    if (index_ == -1) {
        // -1 means that current index is stored in CalloutManager.
        // So let's get the index from there. See comment for
        // LibraryHandle::index_.
        index = callout_manager_.getLibraryIndex();
    }

    return (callout_manager_.deregisterAllCallouts(name, index));
}

isc::data::ConstElementPtr
LibraryHandle::getParameters() {
    HookLibsCollection libinfo = HooksManager::getLibraryInfo();

    int index = index_;

    if (index == -1) {
        // -1 means that current index is stored in CalloutManager.
        // So let's get the index from there. See comment for
        // LibraryHandle::index_.
        index = callout_manager_.getLibraryIndex();
    }

    if ((index > libinfo.size()) || (index <= 0)) {
        // Something is very wrong here. The library index is out of bounds.
        // However, this is user facing interface, so we should not throw here.
        return (isc::data::ConstElementPtr());
    }

    // Some indexes have special meaning:
    // * 0           - pre-user library callout
    // * 1 -> numlib - indexes for actual libraries
    // * INT_MAX     - post-user library callout

    return (libinfo[index - 1].second);
}

isc::data::ConstElementPtr
LibraryHandle::getParameter(const std::string& name) {
    // Try to find appropriate parameter. May return null pointer
    isc::data::ConstElementPtr params = getParameters();
    if (!params || (params->getType() != isc::data::Element::map)) {
        return (isc::data::ConstElementPtr());
    }

    // May return null pointer if there's no parameter.
    return (params->get(name));
}

std::vector<std::string>
LibraryHandle::getParameterNames() {
    std::vector<std::string> names;
    // Find all parameter names.
    isc::data::ConstElementPtr params = getParameters();
    if (!params ||
        (params->getType() != isc::data::Element::map) ||
        (params->size() == 0)) {
        return (names);
    }
    auto map = params->mapValue();
    for (auto elem = map.begin(); elem != map.end(); ++elem) {
        names.push_back(elem->first);
    }
    return (names);
}


} // namespace util
} // namespace isc
