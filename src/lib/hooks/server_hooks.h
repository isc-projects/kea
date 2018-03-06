// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SERVER_HOOKS_H
#define SERVER_HOOKS_H

#include <exceptions/exceptions.h>
#include <hooks/parking_lots.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

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

class ServerHooks;
typedef boost::shared_ptr<ServerHooks> ServerHooksPtr;

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
    /// @param index Index of the hook
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

    /// @brief Find hook index
    ///
    /// Provides exception safe method of retrieving an index of the
    /// specified hook.
    ///
    /// @param name Name of the hook
    ///
    /// @return Index of the hook if the hook point exists, or -1 if the
    /// hook point doesn't exist.
    int findIndex(const std::string& name) const;

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

    /// @brief Returns pointer to ServerHooks object.
    ///
    /// @return Pointer to the global ServerHooks object.
    static ServerHooksPtr getServerHooksPtr();

    /// @brief Returns pointer to all parking lots.
    ///
    /// @return pointer to all parking lots.
    ParkingLotsPtr getParkingLotsPtr() const;

    /// @brief Returns pointer to the ParkingLot for the specified hook index.
    ///
    /// @param hook_index index of the hook point for which the parking lot
    /// should be returned.
    /// @return Pointer to the ParkingLot object.
    ParkingLotPtr getParkingLotPtr(const int hook_index);

    /// @brief Returns pointer to the ParkingLot for the specified hook name.
    ///
    /// @param hook_name name of the hook point for which the parking lot
    /// should be returned.
    /// @return Pointer to the ParkingLot object.
    ParkingLotPtr getParkingLotPtr(const std::string& hook_name);

    /// @brief Generates hook point name for the given control command name.
    ///
    /// This function is called to generate the name of the hook point
    /// when the hook point is used to install command handlers for the
    /// given control command.
    ///
    /// The name of the hook point is generated as follows:
    /// - command name is prefixed with a dollar sign,
    /// - all hyphens are replaced with underscores.
    ///
    /// For example, if the command_name is 'foo-bar', the resulting hook
    /// point name will be '$foo_bar'.
    ///
    /// @param command_name Command name for which the hook point name is
    ///        to be generated.
    ///
    /// @return Hook point name, or an empty string if the command name
    /// can't be converted to a hook name (e.g. when it lacks dollar sign).
    static std::string commandToHookName(const std::string& command_name);

    /// @brief Returns command name for a specified hook name.
    ///
    /// This function removes leading dollar sign and replaces underscores
    /// with hyphens.
    ///
    /// @param hook_name Hook name for which command name should be returned.
    ///
    /// @return Command name.
    static std::string hookToCommandName(const std::string& hook_name);

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

    ParkingLotsPtr parking_lots_;
};

} // namespace util
} // namespace isc

#endif  // SERVER_HOOKS_H
