// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor.h>
#include <boost/foreach.hpp>

#include <iostream>

using namespace std;
using namespace isc::data;

namespace isc {
namespace yang {

Adaptor::Adaptor() {
}

Adaptor::~Adaptor() {
}

ConstElementPtr
Adaptor::getContext(ConstElementPtr parent)
{
    ConstElementPtr context = parent->get("user-context");
    ConstElementPtr comment = parent->get("comment");
    if (!comment) {
        return (context);
    }
    ElementPtr result;
    if (context) {
        result = copy(context);
    } else {
        result = Element::createMap();
    }
    result->set("comment", comment);
    return (result);
}

void
Adaptor::fromParent(const string& name, ConstElementPtr parent,
                    ConstElementPtr list) {
    ConstElementPtr param = parent->get(name);
    if (!param) {
        return;
    }
    BOOST_FOREACH(ElementPtr item, list->listValue()) {
        // don't override. Skip this entry if it already has the parameter.
        if (item->contains(name)) {
            continue;
        }
        item->set(name, param);
    }
}

void
Adaptor::toParent(const string& name, ElementPtr parent,
                  ConstElementPtr list) {
    ConstElementPtr param;
    bool first = true;
    BOOST_FOREACH(ElementPtr item, list->listValue()) {
        if (first) {
            first = false;
            param = item->get(name);
        } else if ((!param && item->contains(name)) ||
                   (param && !item->contains(name)) ||
                   (param && item->contains(name) &&
                    !param->equals(*item->get(name)))) {
            isc_throw(BadValue,
                      "inconsistent value of " << name
                      << " in " << list->str());
        }
    }
    if (!first && param) {
        BOOST_FOREACH(ElementPtr item, list->listValue()) {
            if (param) {
                item->remove(name);
            }
        }
        parent->set(name, param);
    }
}

namespace {

/// @brief Apply insert.
///
/// This function applies an insert action at the given scope:
///  - in a map it adds the value at the key when the key does not exist
///  - in a list it appends the value
///  - in other scope type it does nothing
/// @note a copy of the value is used to avoid unwanted sharing/side effects.
///
/// @param key The key of the modification.
/// @param value The value of the modification.
/// @param scope The place to apply the insert.
void applyInsert(ConstElementPtr key, ConstElementPtr value,
                 ElementPtr scope) {
    if (scope->getType() == Element::map) {
        if (!key || !value || (key->getType() != Element::string)) {
            return;
        }
        string name = key->stringValue();
        if (!name.empty() && !scope->contains(name)) {
            scope->set(name, copy(value));
        }
    } else if (scope->getType() == Element::list) {
        if (value) {
            scope->add(copy(value));
        }
    }
}

/// @brief Apply replace.
///
/// This function works only on map scopes and acts as insert at the
/// exception the new value is set even if the key already exists.
///
/// @param key The key of the modification.
/// @param value The value of the modification.
/// @param scope The place to apply the replace.
void applyReplace(ConstElementPtr key, ConstElementPtr value,
                   ElementPtr scope) {
    if ((scope->getType() != Element::map) ||
        !key || !value || (key->getType() != Element::string)) {
            return;
    }
    string name = key->stringValue();
    if (!name.empty()) {
        scope->set(name, copy(value));
    }
}

/// @brief Apply delete.
///
/// This function deletes the value designed by the key from the given scope:
///  - in a map the key is the key of the value to remove
///  - in a list the key is:
///     * when it is an integer the index of the value to remove
///     * when it is a map the key / value pair which belongs to the value
///      to remove
///  - in other scope type it does nothing
///
/// @param key The key item of the path.
/// @param scope The place to apply the delete.
void applyDelete(ConstElementPtr key, ElementPtr scope) {
    if (scope->getType() == Element::map) {
        if (!key || (key->getType() != Element::string)) {
            return;
        }
        string name = key->stringValue();
        if (!name.empty()) {
            scope->remove(name);
        }
    } else if (scope->getType() == Element::list) {
        if (!key) {
            return;
        } else if (key->getType() == Element::integer) {
            int index = key->intValue();
            if ((index >= 0) && (index < scope->size())) {
                scope->remove(index);
            }
        } else if (key->getType() == Element::map) {
            ConstElementPtr entry = key->get("key");
            ConstElementPtr value = key->get("value");
            if (!entry || !value || (entry->getType() != Element::string)) {
                return;
            }
            string name = entry->stringValue();
            if (name.empty()) {
                return;
            }
            for (int i = 0; i < scope->size(); ++i) {
                ConstElementPtr item = scope->get(i);
                if (!item || (item->getType() != Element::map)) {
                    continue;
                }
                ConstElementPtr compare = item->get(name);
                if (compare && value->equals(*compare)) {
                    scope->remove(i);
                    return;
                }
            }
        }
    }
}

/// @brief Apply action.
///
/// This function applies one action (insert, replace or delete) using
/// applyInsert, applyReplace or applyDelete.
///
/// @param actions The action list.
/// @param scope The current scope.
/// @param next The index of the next action.
void applyAction(ConstElementPtr actions, ElementPtr scope, size_t next) {
    if (next == actions->size()) {
        return;
    }
    ConstElementPtr action = actions->get(next);
    ++next;
    if (!action || (action->getType() != Element::map) ||
        !action->contains("action")) {
        applyAction(actions, scope, next);
        return;
    }
    string name = action->get("action")->stringValue();
    if (name == "insert") {
        applyInsert(action->get("key"), action->get("value"), scope);
    } else if (name == "replace") {
        applyReplace(action->get("key"), action->get("value"), scope);
    } else if (name == "delete") {
        applyDelete(action->get("key"), scope);
    }
    applyAction(actions, scope, next);
}

/// @brief Apply recursively actions following the path and going down
/// in the to-be-modified structure.
///
/// The recursive call when the end of the path is not reached is done:
///  - in a map on the value at the key
///  - in a list the next path item is:
///     * if it is a positive integer on the value at the index
///     * if it is -1 on all elements of the list
///     * if a map on the element where the key / value pair belongs to
///
/// @param path The search list.
/// @param actions The action list.
/// @param scope The current scope.
/// @param next The index of the next item to use in the path.
void applyDown(ConstElementPtr path, ConstElementPtr actions, ElementPtr scope,
               size_t next) {
    if (!scope) {
        return;
    }
    if (next == path->size()) {
        applyAction(actions, scope, 0);
        return;
    }
    ConstElementPtr step = path->get(next);
    ++next;
    if (scope->getType() == Element::map) {
        if (!step || (step->getType() != Element::string)) {
            return;
        }
        string name = step->stringValue();
        if (name.empty() || !scope->contains(name)) {
            return;
        }
        ElementPtr down = boost::const_pointer_cast<Element>(scope->get(name));
        if (down) {
            applyDown(path, actions, down, next);
        }
    } else if (scope->getType() == Element::list) {
        if (!step) {
            return;
        }
        auto downs = scope->listValue();
        if (step->getType() == Element::map) {
            ConstElementPtr key = step->get("key");
            ConstElementPtr value = step->get("value");
            if (!key || !value || (key->getType() != Element::string)) {
                return;
            }
            string name = key->stringValue();
            if (name.empty()) {
                return;
            }
            for (ElementPtr down : downs) {
                if (!down || (down->getType() != Element::map)) {
                    continue;
                }
                ConstElementPtr compare = down->get(name);
                if (compare && value->equals(*compare)) {
                    applyDown(path, actions, down, next);
                    return;
                }
            }
        } else if (step->getType() != Element::integer) {
            return;
        }
        int index = step->intValue();
        if (index == -1) {
            for (ElementPtr down : downs) {
                applyDown(path, actions, down, next);
            }
        } else if ((index >= 0) && (index < scope->size())) {
            applyDown(path, actions, scope->getNonConst(index), next);
        }
    }
}

} // end of anonymous namespace

/// Apply recursively starting at the beginning of the path.
void
Adaptor::modify(ConstElementPtr path, ConstElementPtr actions,
                ElementPtr config) {
    applyDown(path, actions, config, 0);
}

}; // end of namespace isc::yang
}; // end of namespace isc
