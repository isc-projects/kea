// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
        // don't override?
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
/// @param key The key of the modification.
/// @param value The value of the modification.
/// @param scope The place to apply the insert.
void apply_insert(ConstElementPtr key, ConstElementPtr value,
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
/// For maps same than insert but the new value is set even if the key
/// already exists.
///
/// @param key The key of the modification.
/// @param value The value of the modification.
/// @param scope The place to apply the replace.
void apply_replace(ConstElementPtr key, ConstElementPtr value,
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
/// @param last The last item of the path.
/// @param scope The place to apply the delete.
void apply_delete(ConstElementPtr last, ElementPtr scope) {
    if (scope->getType() == Element::map) {
        if (!last || (last->getType() != Element::string)) {
            return;
        }
        string name = last->stringValue();
        if (!name.empty()) {
            scope->remove(name);
        }
    } else if (scope->getType() == Element::list) {
        if (!last) {
            return;
        } else if (last->getType() == Element::integer) {
            int index = last->intValue();
            if ((index >= 0) && (index < scope->size())) {
                scope->remove(index);
            }
        } else if (last->getType() == Element::map) {
            ConstElementPtr key = last->get("key");
            ConstElementPtr value = last->get("value");
            if (!key || !value || (key->getType() != Element::string)) {
                return;
            }
            string name = key->stringValue();
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
/// @param actions The action list.
/// @param scope The current scope.
/// @param next The index of the next action.
void apply_action(ConstElementPtr actions, ElementPtr scope, size_t next) {
    if (next == actions->size()) {
        return;
    }
    ConstElementPtr action = actions->get(next);
    ++next;
    if (!action || (action->getType() != Element::map) ||
        !action->contains("action")) {
        apply_action(actions, scope, next);
        return;
    }
    string name = action->get("action")->stringValue();
    if (name == "insert") {
        apply_insert(action->get("key"), action->get("value"), scope);
    } else if (name == "replace") {
        apply_replace(action->get("key"), action->get("value"), scope);
    } else if (name == "delete") {
        apply_delete(action->get("last"), scope);
    }
    apply_action(actions, scope, next);
}

/// @brief Modify down.
///
/// @param path The search list.
/// @param actions The action list.
/// @param scope The current scope.
/// @param next The index of the next item to use in the path.
void path_down(ConstElementPtr path, ConstElementPtr actions, ElementPtr scope,
               size_t next) {
    if (!scope) {
        return;
    }
    if (next == path->size()) {
        apply_action(actions, scope, 0);
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
            path_down(path, actions, down, next);
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
                    path_down(path, actions, down, next);
                    return;
                }
            }
        } else if (step->getType() != Element::integer) {
            return;
        }
        int index = step->intValue();
        if (index == -1) {
            for (ElementPtr down : downs) {
                path_down(path, actions, down, next);
            }
        } else if ((index >= 0) && (index < scope->size())) {
            path_down(path, actions, scope->getNonConst(index), next);
        }
    }
}

} // end of anonymous namespace

void
Adaptor::modify(ConstElementPtr path, ConstElementPtr actions,
                ElementPtr config) {
    path_down(path, actions, config, 0);
}

}; // end of namespace isc::yang
}; // end of namespace isc
