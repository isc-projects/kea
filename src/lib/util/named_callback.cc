// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/named_callback.h>

#include <iostream>
#include <string>

namespace isc {
namespace util {

void
NamedCallbackList::addCallback(const std::string& name, const NamedCallback::Callback& cb) {
    if (!cb) {
        isc_throw(BadValue, "NamedCallbackList - callback: " << name
                  << ", cannot be empty");
    }

    for (auto const& callback : callbacks_) {
        if (callback.name_ == name) {
            isc_throw(BadValue, "NamedCallbackList - callback: " << name
                      << ", already exists");
        }
    }

    callbacks_.push_back(NamedCallback(name, cb));
}

void
NamedCallbackList::removeCallback(const std::string& name) {
    for (auto it = callbacks_.begin(); it != callbacks_.end(); ++it) {
        if ((*it).name_ == name) {
            callbacks_.erase(it);
            break;
        }
    }
}

void
NamedCallbackList::removeAll() {
    callbacks_.clear();
}

const std::list<NamedCallback>&
NamedCallbackList::getCallbacks() {
    return (callbacks_);
}

}  // namespace util
}  // namespace isc
