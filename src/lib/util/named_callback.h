// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NAMED_CALLBACK_H
#define NAMED_CALLBACK_H

#include <exceptions/exceptions.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <functional>
#include <list>

namespace isc {
namespace util {

/// @brief Associates a Callback with a name.
struct NamedCallback {
    /// @brief Defines a callback as a simple void() functor.
    typedef std::function<void()> Callback;

    /// @brief Constructor
    ///
    /// @param name Name by which the callback can be found.
    /// @param cb Callback associated with name.
    NamedCallback(const std::string& name, const Callback& cb)
        : name_(name), callback_(cb) {
    };

    /// @Brief Name by which the callback can be found.
    std::string name_;

    /// @Brief Callback associated with name.
    Callback callback_;
};

/// @brief Maintains list of unique NamedCallbacks.
///
/// The list emphasizes iteration order and speed over
/// retrieval by name. When iterating over the list of
/// callbacks, they are returned in the order they were
/// added, not by name.
class NamedCallbackList {
public:
    /// @brief Constructor.
    NamedCallbackList(){};

    /// @brief Adds a callback to the list.
    ///
    /// @param name Name of the callback to add.
    /// @param cb Callback to add.
    ///
    /// @throw BadValue if the name is already in the list.
    void addCallback(const std::string& name, const NamedCallback::Callback& cb);

    /// @brief Removes a callback from the list.
    ///
    /// @param name Name of the callback to remove.
    /// If no such callback exists, it simply returns.
    void removeCallback(const std::string& name);

    /// @brief Removes all callbacks from the list.
    void removeAll();

    /// @brief Fetches the list of callbacks.
    const std::list<NamedCallback>& getCallbacks();

private:
    /// @brief The list of callbacks.
    std::list<NamedCallback>  callbacks_;
};

}  // namespace util
}  // namespace isc

#endif  // NAMED_CALLBACK_H
