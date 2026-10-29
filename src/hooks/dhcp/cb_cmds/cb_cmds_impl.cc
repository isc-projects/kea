// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/stamped_value.h>
#include <database/server_selector.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <hooks/hooks.h>

#include <set>

#include <cb_cmds/cb_cmds_impl.h>
#include <cb_cmds/cb_parsers.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;
using namespace isc::hooks;

namespace isc {
namespace cb {

BackendSelector
ConfigCmdsParser::getBackendSelector(const ConstElementPtr& args) const {
    auto remote = args->get("remote");
    if (!remote) {
        return (BackendSelector());
    }

    return (BackendSelector(remote));
}

ServerSelector
ConfigCmdsParser::getServerSelector(const ConstElementPtr& args,
                                    ServerTagsParse tags_parse) const {
    auto server_tags = args->get("server-tags");
    if (server_tags) {
        if (tags_parse == ServerTagsParse::TAGS_FORBIDDEN) {
            isc_throw(BadValue, "'server-tags' parameter is forbidden");
        }

        if (server_tags->getType() != Element::list) {
            isc_throw(BadValue, "'server-tags' parameter must be a list");
        }

        auto server_tags_list = server_tags->listValue();

        // Always expecting at least one server tag.
        if (server_tags_list.empty()) {
            isc_throw(BadValue, "'server-tags' list must not be empty");
        }

        // Special [ null ] value for UNASSIGNED.
        if ((server_tags_list[0]->getType() == Element::null) &&
            (server_tags_list.size() == 1)) {
            return (ServerSelector::UNASSIGNED());
        }

        std::set<std::string> server_tags_set;
        for (auto const& tag : server_tags_list) {
            if (tag->getType() != Element::string) {
                isc_throw(BadValue, "when the 'server-tags' list contains "
                          "multiple elements all these elements must "
                          "have the string type");
            }
            ServerTag server_tag(tag->stringValue());
            server_tags_set.insert(server_tag.get());
        }

        if (server_tags_set.size() == 1) {
            return (ServerSelector::ONE(*server_tags_set.begin()));

        } else {
            return (ServerSelector::MULTIPLE(server_tags_set));
        }
    } else if (tags_parse == ServerTagsParse::TAGS_REQUIRED) {
        isc_throw(BadValue, "'server-tags' parameter is mandatory");
    }
    return (ServerSelector::ANY());
}

ConfigCmdsParser::SubnetsAction
ConfigCmdsParser:: getSubnetsAction(const ConstElementPtr& args) const {
    auto action = args->get("subnets-action");
    if (!action) {
        return (SubnetsAction::ACTION_KEEP);
    }
    if (action->getType() != Element::string) {
        isc_throw(BadValue, "'subnets-action' parameter must be a string");
    }
    std::string action_txt = action->stringValue();
    if (action_txt == "keep") {
        return (SubnetsAction::ACTION_KEEP);
    } else if (action_txt == "delete") {
        return (SubnetsAction::ACTION_DELETE);
    } else {
        isc_throw(BadValue, "unknown 'subnets-action' parameter value: '"
                  << action_txt << "', possible vales are 'keep' (default)"
                  << " and 'delete'");
    }
}

ConfigCmdsParser::SubnetsInclude
ConfigCmdsParser::getSubnetsInclude(const ConstElementPtr& args) const {
    auto do_include = args->get("subnets-include");
    if (!do_include) {
        return (SubnetsInclude::INCLUDE_NO);
    }
    if (do_include->getType() != Element::string) {
        isc_throw(BadValue, "'subnets-include' parameter must be a string");
    }
    std::string include_txt = do_include->stringValue();
    if (include_txt == "no") {
        return (SubnetsInclude::INCLUDE_NO);
    } else if (include_txt == "full") {
        return (SubnetsInclude::INCLUDE_FULL);
    } else {
        isc_throw(BadValue, "unknown 'subnets-include' parameter value: '"
                  << include_txt << "', possible values are 'no' (default)"
                  << " and 'full'");
    }
}

ConfigCmdsImpl::ConfigCmdsImpl() : parser_(new ConfigCmdsParser()) {
}

} // end of namespace isc::cb
} // end of namespace isc
