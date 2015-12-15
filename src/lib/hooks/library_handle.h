// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBRARY_HANDLE_H
#define LIBRARY_HANDLE_H

#include <string>

namespace isc {
namespace hooks {

// Forward declarations
class CalloutHandle;
class CalloutManager;

/// Typedef for a callout pointer.  (Callouts must have "C" linkage.)
extern "C" {
    typedef int (*CalloutPtr)(CalloutHandle&);
};

/// @brief Library handle
///
/// This class is accessed by the user library when registering callouts,
/// either by the library's load() function, or by one of the callouts
/// themselves.
///
/// It is really little more than a shell around the CalloutManager.  By
/// presenting this object to the user-library callouts, callouts can manage
/// the callout list for their own library, but cannot affect the callouts
/// registered by other libraries.
///
/// (This restriction is achieved by the CalloutManager maintaining the concept
/// of the "current library".  When a callout is registered - either by the
/// library's load() function, or by a callout in the library - the registration
/// information includes the library active at the time.  When that callout is
/// called, the CalloutManager uses that information to set the "current
/// library": the registration functions only operator on data whose
/// associated library is equal to the "current library".)

class LibraryHandle {
public:

    /// @brief Constructor
    ///
    /// @param manager Back pointer to the containing CalloutManager.
    ///        This pointer is used to access appropriate methods in that
    ///        object.  Note that the "raw" pointer is safe - the only
    ///        instance of the LibraryHandle in the system is as a member of
    ///        the CalloutManager to which it points.
    ///
    /// @param index Index of the library to which the LibraryHandle applies.
    ///        If negative, the library index as set in the CalloutManager is
    ///        used.  Otherwise the current library index is saved, this value
    ///        is set as the current index, the registration call is made, and
    ///        the CalloutManager's library index is reset.  Note: although -1
    ///        is a valid argument value for
    ///        isc::hooks::CalloutManager::setLibraryIndex(), in this class is
    ///        is used as a sentinel to indicate that the library index in
    ///        isc::util::CalloutManager should not be set or reset.
    LibraryHandle(CalloutManager* manager, int index = -1)
        : callout_manager_(manager), index_(index)
    {}

    /// @brief Register a callout on a hook
    ///
    /// Registers a callout function with a given hook.  The callout is added
    /// to the end of the callouts for the current library that are associated
    /// with that hook.
    ///
    /// @param name Name of the hook to which the callout is added.
    /// @param callout Pointer to the callout function to be registered.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    void registerCallout(const std::string& name, CalloutPtr callout);

    /// @brief De-Register a callout on a hook
    ///
    /// Searches through the functions registered by the current library with
    /// the named hook and removes all entries matching the callout.  It does
    /// not affect callouts registered by other libraries.
    ///
    /// @param name Name of the hook from which the callout is removed.
    /// @param callout Pointer to the callout function to be removed.
    ///
    /// @return true if a one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook The hook name is unrecognized.
    /// @throw Unexpected The hook name is valid but an internal data structure
    ///        is of the wrong size.
    bool deregisterCallout(const std::string& name, CalloutPtr callout);

    /// @brief Removes all callouts on a hook
    ///
    /// Removes all callouts associated with a given hook that were registered.
    /// by the current library.  It does not affect callouts that were
    /// registered by other libraries.
    ///
    /// @param name Name of the hook from which the callouts are removed.
    ///
    /// @return true if one or more callouts were deregistered.
    ///
    /// @throw NoSuchHook Thrown if the hook name is unrecognized.
    bool deregisterAllCallouts(const std::string& name);

private:
    /// @brief Copy constructor
    ///
    /// Private (with no implementation) as it makes no sense to copy an object
    /// of this type.  All code receives a reference to an existing handle which
    /// is tied to a particular CalloutManager.  Creating a copy of that handle
    /// runs the risk of a "dangling pointer" to the original handle's callout
    /// manager.
    ///
    /// @param Unused - should be the object to copy.
    LibraryHandle(const LibraryHandle&);

    /// @brief Assignment operator
    ///
    /// Declared private like the copy constructor for the same reasons. It too
    /// has no implementation.
    ///
    /// @param Unused - should be the object to copy.
    LibraryHandle& operator=(const LibraryHandle&);

    /// Back pointer to the collection object for the library
    CalloutManager* callout_manager_;

    /// Library index to which this handle applies.  -1 indicates that it
    /// applies to whatever index is current in the CalloutManager.
    int index_;
};

} // namespace util
} // namespace isc

#endif // LIBRARY_HANDLE_H
