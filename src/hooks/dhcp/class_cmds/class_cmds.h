// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLASS_CMDS_H
#define CLASS_CMDS_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <hooks/hooks.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace class_cmds {

/// @brief Thrown upon an attempt to update a class when dependency
/// on KNOWN or UNKNOWN built-in class is removed or added.
///
/// Such modification is not allowed because that may affect other
/// classes which depend on those built-in classes via the
/// modified class.
class DependOnKnownError : public isc::Exception {
public:
    DependOnKnownError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// @brief Thrown upon an attempt to delete a class which would
/// result in leaving dangling dependencies.
class InUseError : public isc::Exception {
public:
    InUseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// @brief Forward declaration of implementation class.
class ClassCmdsImpl;

/// @brief Implements the logic for processing commands pertaining to
/// client classes manipulation.
///
/// This class is used by the callouts implementing command handlers for
/// client classes manipulations.
///
/// Commands which add and update client classes enclose the classes in
/// a JSON list, even though we currently allow only one class to be
/// added or updated per command. In the future we may allow more classes
/// to be added or updated with a single command, but this will
/// require implementation of some sort of transaction mechanism, so as
/// an error in processing one of the classes would cause the rollback
/// of other changes. Allowing partial update could cause inconsistency
/// in the server configuration.
///
/// Meanwhile, we allow only one class to be added or updated but the
/// command structure is already prepared for possible future extension.
class ClassCmds {
public:
    /// @brief Constructor.
    ///
    /// It creates an instance of the @c ClassCmdsImpl.
    ClassCmds();

    /// @brief Returns a response to a 'class-add' command
    ///
    /// This function processes 'class-add' command by adding it to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "class-add",
    ///     "arguments": {
    ///         "client-classes": [
    ///             {
    ///                 "name": "my-class",
    ///                 ...
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before adding the class to the current configuration this method
    /// will check for duplicated class, i.e. having the same name, and
    /// expressions referring to unspecified (i.e. not builtin nor configured)
    /// classes.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "Class 'my-class' added."
    /// }
    /// @endcode
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void addClass(hooks::CalloutHandle& callout_handle);

    /// @brief Returns a response to a 'class-get' command
    ///
    /// This function returns a client class by a name.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "Class 'my-class' definition returned",
    ///     "arguments": {
    ///         "client-classes": [
    ///             {
    ///                 "name": "my-class",
    ///                 ...
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void getClass(hooks::CalloutHandle& callout_handle) const;

    /// @brief Returns a response to a 'class-list' command.
    ///
    /// This method retrieves configured client classes and returns the list
    /// of their names.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "2 classes found",
    ///     "arguments": {
    ///         "client-classes": [
    ///             {
    ///                 "name": "classA"
    ///             },
    ///             {
    ///                 "name": "classB"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///

    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void getClassList(hooks::CalloutHandle& callout_handle) const;

    /// @brief Returns a response to a 'class-update' command
    ///
    /// This function processes 'class-update' command by updating it to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "class-update",
    ///     "arguments": {
    ///         "client-classes": [
    ///             {
    ///                 "name": "my-class",
    ///                 ...
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before updating the class to the current configuration this method
    /// will check for duplicated class, i.e. having the same name, and
    /// expressions referring to unspecified (i.e. not builtin nor configured)
    /// and forward (i.e. configured after) classes. Dependency to KNOWN
    /// and UNKNOWN builtin classes must not change.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "Class 'my-class' updated."
    /// }
    /// @endcode
    ///

    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void updateClass(hooks::CalloutHandle& callout_handle);

    /// @brief Processes and returns a response to 'class-del' command.
    ///
    /// This function processes the 'class-del' command by searching for a
    /// class by specified name and deleting this class from the server
    /// configuration.
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "class-del",
    ///     "arguments": {
    ///         {
    ///             "name": "my-class"
    ///         }
    ///     }
    /// }
    /// @endcode
    ///
    /// If the class exists and is referred by another class an error is
    /// returned with the name of this class.
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void delClass(hooks::CalloutHandle& callout_handle);

private:

    /// Pointer to the actual implementation
    boost::shared_ptr<ClassCmdsImpl> impl_;
};

} // end of namespace class_cmds
} // end of namespace isc

#endif // CLASS_CMDS_H
