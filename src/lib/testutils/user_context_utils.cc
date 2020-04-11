// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/user_context_utils.h>

using namespace isc::data;

namespace {

/// @brief Encapsulate either a modified copy or a unmodified value
/// @tparam EP ElementPtr or ConstElementPtr (compiler can't infer which one)
template<typename EP>
class Value {
public:
    /// @brief Factory for modified copy
    static Value mkCopy(EP value) { return (Value(value, false)); }

    /// @brief Factory for unmodified original
    static Value mkShare(EP value) { return (Value(value, true)); }

    /// @brief Get the value
    /// @return the value
    EP get() const { return (value_); }

    /// @brief Get the shared status
    /// @return true if original, false if copy
    bool isShared() const { return (shared_); }

private:
    /// @brief Constructor
    /// @param value the modified copy or unmodified value
    /// @param shared true if original, false if copy
    Value(EP value, bool shared) : value_(value), shared_(shared) { }

    /// @brief the value
    EP value_;

    /// @brief the shared status
    bool shared_;
};

/// @brief Recursive helper
///
/// @tparam EP ElementPtr or ConstElementPtr (compiler will infer which one)
/// @param element the element to traverse
/// @return a modified copy where comment entries were moved to user-context
/// or the unmodified original argument encapsulated into a Value
template<typename EP>
Value<EP> moveComments1(EP element) {
    bool modified = false;

    // On lists recurse on items
    if (element->getType() == Element::list) {
        ElementPtr result = ElementPtr(new ListElement());
        typedef std::vector<ElementPtr> ListType;
        const ListType& list = element->listValue();
        for (ListType::const_iterator it = list.cbegin();
             it != list.cend(); ++it) {
            Value<ElementPtr> item = moveComments1(*it);
            result->add(item.get());
            if (!item.isShared()) {
                modified = true;
            }
        }
        if (!modified) {
            return (Value<EP>::mkShare(element));
        } else {
            return (Value<EP>::mkCopy(result));
        }
    } else if (element->getType() != Element::map) {
        return (Value<EP>::mkShare(element));
    }

    // Process maps: recurse on items
    ElementPtr result = ElementPtr(new MapElement());
    bool has_comment = false;
    typedef std::map<std::string, ConstElementPtr> map_type;
    const map_type& map = element->mapValue();
    for (map_type::const_iterator it = map.cbegin(); it != map.cend(); ++it) {
        if (it->first == "comment") {
            // Note there is a comment entry to move
            has_comment = true;
        } else if (it->first == "user-context") {
            // Do not traverse user-context entries
            result->set("user-context", it->second);
        } else {
            // Not comment or user-context
            Value<ConstElementPtr> item = moveComments1(it->second);
            result->set(it->first, item.get());
            if (!item.isShared()) {
                modified = true;
            }
        }
    }
    // Check if the value should be not modified
    if (!has_comment && !modified) {
        return (Value<EP>::mkShare(element));
    }

    if (has_comment) {
        // Move the comment entry
        ConstElementPtr comment = element->get("comment");
        ElementPtr moved = Element::createMap();
        moved->set("comment", comment);
        ConstElementPtr previous = element->get("user-context");
        // If there is already a user context merge it
        if (previous) {
                merge(moved, previous);
        }
        result->set("user-context", moved);
    }

    return (Value<EP>::mkCopy(result));
}

} // anonymous namespace

namespace isc {
namespace test {

ElementPtr moveComments(ElementPtr element) {
    Value<ElementPtr> result = moveComments1(element);
    return (result.get());
}

ConstElementPtr moveComments(ConstElementPtr element) {
    Value<ConstElementPtr> result = moveComments1(element);
    return (result.get());
}

} // end of isc::test namespace
} // end of isc namespace
