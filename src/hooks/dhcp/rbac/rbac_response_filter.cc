// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>

#include <rbac/rbac.h>
#include <rbac/rbac_response_filter.h>
#include <rbac_log.h>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::log;
using namespace isc::rbac;
using namespace std;

namespace isc {
namespace rbac {

ResponseFilterTable responseFilterTable;

void
ResponseFilter::initResponseFilterTable() {
    responseFilterTable.clear();
    responseFilterTable["noop"] =
        ResponseFilterPtr(new NoopResponseFilter());
    responseFilterTable["list-commands"] =
        ResponseFilterPtr(new ListCommandsResponseFilter());
}

ResponseFilterList
ResponseFilter::parse(ConstElementPtr cfg) {
    if (!cfg) {
        isc_throw(BadValue, "parse null response filter list");
    }
    if (cfg->getType() != Element::list) {
        isc_throw(BadValue, "response filter list is not a list");
    }
    ResponseFilterList filters;
    for (auto const& elem : cfg->listValue()) {
        if (elem->getType() != Element::string) {
            isc_throw(BadValue, "response filter name is not a string");
        }
        const string& name = elem->stringValue();
        if (name.empty()) {
            isc_throw(BadValue, "response filter name is empty");
        }
        auto it = responseFilterTable.find(name);
        if (it == responseFilterTable.end()) {
            isc_throw(BadValue, "unknown response filter '" << name << "'");
        }
        filters.push_back(it->second);
    }
    return (filters);
}

bool
ListCommandsResponseFilter::filter(const string& command,
                                   const RoleConfig& role_config,
                                   ConstElementPtr body) {
    if (command != "list-commands") {
        return (false);
    }
    if (!body || (body->getType() != Element::map)) {
        return (false);
    }
    ConstElementPtr args = body->get(CONTROL_ARGUMENTS);
    if (!args || (args->getType() != Element::list)) {
        return (false);
    }
    if (args->size() < 1) {
        return (false);
    }
    size_t modified = 0;
    ElementPtr filtered = Element::createList();
    for (auto const& elem : args->listValue()) {
        if (!elem || (elem->getType() != Element::string)) {
            ++modified;
            continue;
        }
        const string& cmd = elem->stringValue();
        if ((cmd == "list-commands") || role_config.match(cmd)) {
            filtered->add(elem);
        } else {
            ++modified;
        }
    }
    if (modified == 0) {
        return (false);
    }
    ElementPtr mutable_body = boost::const_pointer_cast<Element>(body);
    mutable_body->set(CONTROL_ARGUMENTS, filtered);
    return (true);
}

} // end of namespace rbac
} // end of namespace isc
