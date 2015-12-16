// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SERVER_HOOKS_H
#define SERVER_HOOKS_H

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace hooks {

/// @brief Duplicate hook
///
/// Thrown if an attempt is made to register a hook with the same name as a
/// previously-registered hook.
class DuplicateHook : public Exception {
public:
    DuplicateHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid hook
///
/// Thrown if an attempt is made to get the index for an invalid hook.
class NoSuchHook : public Exception {
public:
    NoSuchHook(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


/// @brief Server hook collection
///
/// This class is used by the server-side code to register hooks - points in the
/// server processing at which libraries can register functions (callouts) that
/// the server will call.  These functions can modify data and so affect the
/// processing of the server.
///
/// The ServerHooks class is little more than a wrapper around the std::map
/// class.  It stores a hook, assigning to it a unique index number.  This
/// number is then used by the server code to identify the hook being called.
/// (Although it would be feasible to use a name as an index, using an integer
/// will speed up the time taken to locate the callouts, which may make a
/// difference in a frequently-executed piece of code.)
///
/// ServerHooks is a singleton object and is only accessible by the static
/// method getServerHooks().

class ServerHooks : public boost::noncopyable {
public:

    /// Index numbers for pre-defined hooks.
    static const int CONTEXT_CREATE = 0;
    static const int CONTEXT_DESTROY = 1;

    /// @brief Reset to Initial State
    ///
    /// Resets the collection of hooks to the initial state, with just the
    /// context_create and context_destroy hooks set.  This used during
    /// testing to reset the global ServerHooks object; it should never be
    /// used in production.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    void reset();

    /// @brief Register a hook
    ///
    /// Registers a hook and returns the hook index.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent hook-related calls.
    ///         This will be greater than or equal to zero (so allowing a
    ///         negative value to indicate an invalid index).
    ///
    /// @throws DuplicateHook A hook with the same name has already been
    ///         registered.
    int registerHook(const std::string& name);

    /// @brief Get hook name
    ///
    /// Returns the name of a hook given the index.  This is most likely to be
    /// used in log messages.
    ///
    /// @param index Index of the hoold
    ///
    /// @return Name of the hook.
    ///
    /// @throw NoSuchHook if the hook index is invalid.
    std::string getName(int index) const;

    /// @brief Get hook index
    ///
    /// Returns the index of a hook.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook, to be used in subsequent calls.
    ///
    /// @throw NoSuchHook if the hook name is unknown to the caller.
    int getIndex(const std::string& name) const;

    /// @brief Return number of hooks
    ///
    /// Returns the total number of hooks registered.
    ///
    /// @return Number of hooks registered.
    int getCount() const {
        return (hooks_.size());
    }

    /// @brief Get hook names
    ///
    /// Return list of hooks registered in the object.
    ///
    /// @return Vector of strings holding hook names.
    std::vector<std::string> getHookNames() const;

    /// @brief Return ServerHooks object
    ///
    /// Returns the global ServerHooks object.
    ///
    /// @return Reference to the global ServerHooks object.
    static ServerHooks& getServerHooks();

private:
    /// @brief Constructor
    ///
    /// This pre-registers two hooks, context_create and context_destroy, which
    /// are called by the server before processing a packet and after processing
    /// for the packet has completed.  They allow the server code to allocate
    /// and destroy per-packet context.
    ///
    /// The constructor is declared private to enforce the singleton nature of
    /// the object.  A reference to the singleton is obtainable through the
    /// getServerHooks() static method.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    ServerHooks();

    /// @brief Initialize hooks
    ///
    /// Sets the collection of hooks to the initial state, with just the
    /// context_create and context_destroy hooks set.  This is used during
    /// construction.
    ///
    /// @throws isc::Unexpected if the registration of the pre-defined hooks
    ///         fails in some way.
    void initialize();

    /// Useful typedefs.
    typedef std::map<std::string, int> HookCollection;
    typedef std::map<int, std::string> InverseHookCollection;

    /// Two maps, one for name->index, the other for index->name.  (This is
    /// simpler than using a multi-indexed container.)
    HookCollection  hooks_;                 ///< Hook name/index collection
    InverseHookCollection inverse_hooks_;   ///< Hook index/name collection
};

} // namespace util
} // namespace isc

#endif  // SERVER_HOOKS_H
