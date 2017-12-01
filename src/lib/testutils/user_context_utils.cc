// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/user_context_utils.h>

using namespace isc::data;

namespace {

/// @brief Exception to handle a unmodified value
/// @tparam EP ElementPtr or ConstElementPtr (compiler can't infer which one)
template<typename EP>
class UnModified {
public:
    /// @brief Constructor
    /// @param value the unmodified value
    UnModified(EP value) : value_(value) { }

    /// @brief Get the value
    /// @return the value
    EP get() const { return (value_); }

protected:
    /// @brief the unmodified value
    EP value_;
};

/// @brief Recursive helper
///
/// Instead of returning a unmodified copy a @ref UnModified exception
/// is raised with the unmodified value
///
/// @tparam EP ElementPtr or ConstElementPtr (compiler will infer which one)
/// @param element the element to traverse
/// @return a modified copy where comment entries were moved to user-context
/// @throw UnModified with the unmodified value
template<typename EP>
EP moveComments1(EP element) {
    bool modified = false;

    // On lists recurse on items
    if (element->getType() == Element::list) {
        ElementPtr result = ElementPtr(new ListElement());
        typedef std::vector<ElementPtr> ListType;
        const ListType& list = element->listValue();
        for (ListType::const_iterator it = list.cbegin();
             it != list.cend(); ++it) {
            try {
                result->add(moveComments1(*it));
                modified = true;
            }
            catch (const UnModified<ElementPtr>& ex) {
                result->add(ex.get());
            }
        }
        if (!modified) {
            throw UnModified<EP>(element);
        }
        return (result);
    } else if (element->getType() != Element::map) {
        throw UnModified<EP>(element);
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
            try {
                result->set(it->first, moveComments1(it->second));
                modified = true;
            }
            catch (const UnModified<ConstElementPtr>& ex) {
                result->set(it->first, ex.get());
            }
        }
    }
    // Check if the value should be not modified
    if (!has_comment && !modified) {
        throw UnModified<EP>(element);
    }

    if (has_comment) {
        // Move the comment entry
        ConstElementPtr comment = element->get("comment");
        ElementPtr moved = Element::createMap();
        moved->set("comment", comment);
        result->combine_set("user-context", moved);
    }

    return (result);
}

} // anonymous namespace

namespace isc {
namespace test {

ElementPtr moveComments(ElementPtr element) {
    ElementPtr result;
    try {
        result = moveComments1(element);
    }
    catch (const UnModified<ElementPtr>& ex) {
        result = ex.get();
    }
    return result;
}

}; // end of isc::test namespace
}; // end of isc namespace

namespace {

/// @brief Recursive helper
///
/// Instead of returning a unmodified copy a @ref UnModified exception
/// is raised with the unmodified value
///
/// @tparam EP ElementPtr or ConstElementPtr (compiler will infer which one)
/// @param element the element to traverse
/// @return a modified copy where comment entries were moved to user-context
/// @throw UnModified with the unmodified value
template<typename EP>
EP extractComments1(EP element) {
    bool modified = false;

    // On lists recurse on items
    if (element->getType() == Element::list) {
        ElementPtr result = ElementPtr(new ListElement());
        typedef std::vector<ElementPtr> ListType;
        const ListType& list = element->listValue();
        for (ListType::const_iterator it = list.cbegin();
             it != list.cend(); ++it) {
            try {
                result->add(extractComments1(*it));
                modified = true;
            }
            catch (const UnModified<ElementPtr>& ex) {
                result->add(ex.get());
            }
        }
        if (!modified) {
            throw UnModified<EP>(element);
        }
        return (result);
    } else if (element->getType() != Element::map) {
        throw UnModified<EP>(element);
    }

    // Process maps: recurse on items
    ElementPtr result = ElementPtr(new MapElement());
    bool has_comment = false;
    typedef std::map<std::string, ConstElementPtr> map_type;
    const map_type& map = element->mapValue();
    for (map_type::const_iterator it = map.cbegin(); it != map.cend(); ++it) {
        if (it->first == "comment") {
            // Do not traverse comment entries
            result->set("comment", it->second);
        } else if (it->first == "user-context") {
            if (it->second->contains("comment")) {
                // Note there is a  entry to move
                has_comment = true;
            } else {
                // Do not traverse user-context entries
                result->set("user-context", it->second);
            }
        } else {
            // Not comment or user-context
            try {
                result->set(it->first, extractComments1(it->second));
                modified = true;
            }
            catch (const UnModified<ConstElementPtr>& ex) {
                result->set(it->first, ex.get());
            }
        }
    }
    // Check if the value should be not modified
    if (!has_comment && !modified) {
        throw UnModified<EP>(element);
    }

    if (has_comment) {
        // Move the comment entry
        const map_type& uc_map = element->get("user-context")->mapValue();
        ElementPtr user_context = Element::createMap();
        ConstElementPtr comment;
        for (map_type::const_iterator it = uc_map.cbegin();
             it != uc_map.cend(); ++it) {
            if  (it->first == "comment") {
                comment = it->second;
            } else {
                user_context->set(it->first, it->second);
            }
        }
        if (user_context->size() > 0) {
            result->set("user-context", user_context);
        }
        result->combine_set("comment", copy(comment, 0));
    }

    return (result);
}

} // anonymous namespace

namespace isc {
namespace test {

ElementPtr extractComments(ElementPtr element) {
    ElementPtr result;
    try {
        result = extractComments1(element);
    }
    catch (const UnModified<ElementPtr>& ex) {
        result = ex.get();
    }
    return result;
}

}; // end of isc::test namespace
}; // end of isc namespace
