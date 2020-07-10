// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBRARY_HANDLE_H
#define LIBRARY_HANDLE_H

#include <string>
#include <cc/data.h>

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
///
/// As of Kea 1.3.0 release, the @ref LibraryHandle can be used by the hook
/// libraries to install control command handlers and dynamically register
/// hook points with which the handlers are associated. For example, if the
/// hook library supports control-command 'foo-bar' it should register its
/// handler similarly to this:
/// @code
/// int load(LibraryHandle& libhandle) {
///     libhandle.registerCommandCallout("foo-bar", foo_bar_handler);
///     return (0);
/// }
/// @endcode
///
/// which will result in automatic creation of the hook point for the command
/// (if one doesn't exist) and associating the callout 'foo_bar_handler' with
/// this hook point as a handler for the command.

class LibraryHandle {
public:

    /// @brief Constructor
    ///
    /// @param manager Back reference to the containing CalloutManager.
    ///        This reference is used to access appropriate methods in that
    ///        object.  Note that the reference is safe - the only instance
    ///        of the LibraryHandle in the system is as a member of the
    ///        CalloutManager to which it points.
    ///
    /// @param index Index of the library to which the LibraryHandle applies.
    ///        If negative, the library index as set in the CalloutManager is
    ///        used.  Note: although -1 is a valid argument value for
    ///        @ref isc::hooks::CalloutManager::setLibraryIndex(), in this class
    ///        it is used as a sentinel to indicate that the library index in
    ///        @ref isc::hooks::CalloutManager should not be set or reset.
    LibraryHandle(CalloutManager& manager, int index = -1)
        : callout_manager_(manager), index_(index) {}

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

    /// @brief Register control command handler
    ///
    /// Registers control command handler by creating a hook point for this
    /// command (if it doesn't exist) and associating the callout as a command
    /// handler. It is possible to register multiple command handlers for the
    /// same control command because command handlers are implemented as callouts.
    ///
    /// @param command_name Command name for which handler should be installed.
    /// @param callout Pointer to the command handler implemented as a callout.
    void registerCommandCallout(const std::string& command_name, CalloutPtr callout);

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


    /// @brief Returns configuration parameter for the library.
    ///
    /// This method returns configuration parameters specified in the
    /// configuration file. Here's the example. Let's assume that there
    /// are two hook libraries configured:
    ///
    /// "hooks-libraries": [
    ///     {
    ///        "library": "/opt/charging.so",
    ///        "parameters": {}
    ///    },
    ///    {
    ///        "library": "/opt/local/notification.so",
    ///        "parameters": {
    ///            "mail": "alarm@example.com",
    ///            "floor": 42,
    ///            "debug": false,
    ///            "users": [ "alice", "bob", "charlie" ],
    ///            "header": {
    ///                "french": "bonjour",
    ///                "klingon": "yl'el"
    ///            }
    ///        }
    ///    }
    ///]
    ///
    /// The first library has no parameters, so regardless of the name
    /// specified, for that library getParameter will always return NULL.
    ///
    /// For the second parameter, depending the following calls will return:
    /// - x = getParameter("mail") will return instance of
    ///   isc::data::StringElement. The content can be accessed with
    ///   x->stringValue() and will return std::string.
    /// - x = getParameter("floor") will return an instance of isc::data::IntElement.
    ///   The content can be accessed with x->intValue() and will return int.
    /// - x = getParameter("debug") will return an instance of isc::data::BoolElement.
    ///   Its value can be accessed with x->boolValue() and will return bool.
    /// - x = getParameter("users") will return an instance of ListElement.
    ///   Its content can be accessed with the following methods:
    ///   x->size(), x->get(index)
    /// - x = getParameter("header") will return an instance of isc::data::MapElement.
    ///   Its content can be accessed with the following methods:
    ///   x->find("klingon"), x->contains("french"), x->size()
    ///
    /// For more examples and complete API, see documentation for
    /// @ref isc::data::Element class and its derivatives:
    /// - @ref isc::data::IntElement
    /// - @ref isc::data::DoubleElement
    /// - @ref isc::data::BoolElement
    /// - @ref isc::data::StringElement
    /// - @ref isc::data::ListElement
    /// - @ref isc::data::MapElement
    ///
    /// Another good way to learn how to use Element interface is to look at the
    /// unittests in data_unittests.cc.
    ///
    /// @param name text name of the parameter.
    /// @return ElementPtr representing requested parameter (may be null, if
    ///         there is no such parameter.)
    isc::data::ConstElementPtr
    getParameter(const std::string& name);

    /// @brief Get configuration parameter common code.
    ///
    /// @return configuration parameters.
    isc::data::ConstElementPtr getParameters();

    /// @brief Returns names of configuration parameters for the library.
    ///
    /// This method returns a vector of strings reflecting names of
    /// configuration parameters specified in the configuration file.
    ///
    /// @note: kept for backward compatibility.
    /// @return a vector with parameter entry names.
    std::vector<std::string> getParameterNames();

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
    CalloutManager& callout_manager_;

    /// Library index to which this handle applies.  -1 indicates that it
    /// applies to whatever index is current in the CalloutManager.
    int index_;
};

} // namespace util
} // namespace isc

#endif // LIBRARY_HANDLE_H
