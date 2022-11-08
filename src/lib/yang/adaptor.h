// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_H
#define ISC_ADAPTOR_H 1

#include <cc/data.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace yang {

/// @brief JSON adaptor between canonical Kea and YANG models.
///
/// An adaptor slightly modifies a JSON configuration between canonical Kea
/// what required or rendered by a YANG model, e.g. moving a parameter
/// to/from a parent.
/// The basic adaptor provides a set of tools.
class Adaptor {
public:
    /// @brief Destructor.
    virtual ~Adaptor() = default;

    /// @brief Get user context.
    ///
    /// Get user-context and/or comment and return it with the comment
    /// if exists moved inside the user-context (without checking if
    /// there is already a comment as it should never be the case).
    ///
    /// This behavior is used to handle comments. For historical purposes
    /// Kea allows to define comments in some scopes. Once the user-context
    /// has been introduced, the comment (as a separate text field)
    /// disappeared and was moved to comment key within user-context.
    /// Nevertheless, the old syntax is still supported.
    static isc::data::ConstElementPtr
    getContext(isc::data::ConstElementPtr parent);

    /// @brief Moves a parameter from parent to a list of children.
    ///
    /// Move a parameter from the parent to each item in a list.
    /// If the parameter exists in a child, it is skipped for this
    /// particular child, not overridden.
    ///
    /// @param name The parameter name.
    /// @param parent The parent element.
    /// @param list The children list.
    static void fromParent(const std::string& name,
                           isc::data::ConstElementPtr parent,
                           isc::data::ConstElementPtr list);

    /// @brief Moves a parameter to a parent.
    ///
    /// Move a parameter from children to the parent. All children
    /// on the list must have the parameter specified and it has to have
    /// the same value.
    ///
    /// @param name The parameter name.
    /// @param parent The parent element.
    /// @param list The children list.
    static void toParent(const std::string& name,
                         isc::data::ElementPtr parent,
                         isc::data::ConstElementPtr list);

    /// @brief Modify a configuration in its JSON element format.
    ///
    /// Smart merging tool, e.g. completing an ElementPtr received from YANG.
    ///
    /// A modification is a path and actions:
    ///  - path item can be:
    ///   * a string: current scope is a map, go down following the string
    ///     as a key.
    ///   * a number: current scope is a list, go down the number as an index.
    ///   * special value -1: current scope is a list, apply to all items.
    ///   * map { "<key>": <value> }: current scope is a list, go down to
    ///     the item using the key / value pair.
    ///  - an action can be: insert, replace or delete:
    ///   * insert adds a value at a key:
    ///     . in a map the key is the new entry key
    ///     . in a list an integer key is the new element index
    ///     . in a list a map key is the key / value pair the to-be-modified
    ///       element contains
    ///   * replace adds or replaces if it already exists a value at
    ///     an entry key in a map.
    ///   * delete removes a value designed by a key
    ///
    /// For instance to add a control-socket entry in a configuration
    /// from a generic (vs Kea) model:
    /// @code
    ///   path := [ ]
    ///   actions := [ {
    ///     "action": "insert",
    ///     "key": "Dhcp4",
    ///     "value":
    ///       {
    ///         "control-socket":
    ///           {
    ///              "socket-type": "unix",
    ///              "socket-name": "/tmp/kea4-ctrl-socket"
    ///           }
    ///       }
    ///    }
    /// @endcode
    ///
    /// @param path The search list to follow down to the place to
    ///             apply the action list.
    /// @param actions The action list
    /// @param config The configuration (JSON map) to modify.
    /// @note modify does not throw but returns on unexpected conditions.
    static void modify(isc::data::ConstElementPtr path,
                       isc::data::ConstElementPtr actions,
                       isc::data::ElementPtr config);

};  // Adaptor

}  // namespace yang
}  // namespace isc

#endif  // ISC_ADAPTOR_H
