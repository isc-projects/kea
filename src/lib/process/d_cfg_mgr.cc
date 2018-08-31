// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <dhcp/libdhcp++.h>
#include <process/d_log.h>
#include <process/d_cfg_mgr.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <limits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace process {

// *********************** DCfgContextBase  *************************

DCfgContextBase::DCfgContextBase():
        boolean_values_(new BooleanStorage()),
        uint32_values_(new Uint32Storage()),
        string_values_(new StringStorage()) {
    }

DCfgContextBase::DCfgContextBase(const DCfgContextBase& rhs):
        boolean_values_(new BooleanStorage(*(rhs.boolean_values_))),
        uint32_values_(new Uint32Storage(*(rhs.uint32_values_))),
        string_values_(new StringStorage(*(rhs.string_values_))) {
}

const data::Element::Position&
DCfgContextBase::getParam(const std::string& name, bool& value, bool optional) {
    try {
        value = boolean_values_->getParam(name);
        return (boolean_values_->getPosition(name));
    } catch (DhcpConfigError& ex) {
        // If the parameter is not optional, re-throw the exception.
        if (!optional) {
            throw;
        }
    }

    return (data::Element::ZERO_POSITION());
}

const data::Element::Position&
DCfgContextBase::getParam(const std::string& name, uint32_t& value,
                          bool optional) {
    try {
        value = uint32_values_->getParam(name);
        return (uint32_values_->getPosition(name));
    } catch (DhcpConfigError& ex) {
        // If the parameter is not optional, re-throw the exception.
        if (!optional) {
            throw;
        }
    }

    return (data::Element::ZERO_POSITION());
}

const data::Element::Position&
DCfgContextBase::getParam(const std::string& name, std::string& value,
                          bool optional) {
    try {
        value = string_values_->getParam(name);
        return (string_values_->getPosition(name));
    } catch (DhcpConfigError& ex) {
        // If the parameter is not optional, re-throw the exception.
        if (!optional) {
            throw;
        }
    }

    return (data::Element::ZERO_POSITION());
}

DCfgContextBase::~DCfgContextBase() {
}

// *********************** DCfgMgrBase  *************************

DCfgMgrBase::DCfgMgrBase(DCfgContextBasePtr context)
    : parse_order_() {
    setContext(context);
}

DCfgMgrBase::~DCfgMgrBase() {
}

void
DCfgMgrBase::resetContext() {
    DCfgContextBasePtr context = createNewContext();
    setContext(context);
}

void
DCfgMgrBase::setContext(DCfgContextBasePtr& context) {
    if (!context) {
        isc_throw(DCfgMgrBaseError, "DCfgMgrBase: context cannot be NULL");
    }

    context_ = context;
}

isc::data::ConstElementPtr
DCfgMgrBase::parseConfig(isc::data::ConstElementPtr config_set,
                         bool check_only) {
    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_COMMAND,
                DCTL_CONFIG_START).arg(config_set->str());

    if (!config_set) {
        return (isc::config::createAnswer(1,
                                    std::string("Can't parse NULL config")));
    }

    // The parsers implement data inheritance by directly accessing
    // configuration context. For this reason the data parsers must store
    // the parsed data into context immediately. This may cause data
    // inconsistency if the parsing operation fails after the context has been
    // modified. We need to preserve the original context here
    // so as we can rollback changes when an error occurs.
    DCfgContextBasePtr original_context = context_;
    resetContext();

    // Answer will hold the result returned to the caller.
    ConstElementPtr answer;

    // Holds the name of the element being parsed.
    std::string element_id;

    try {

        // Make the configuration mutable so we can then insert default values.
        ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(config_set);
        setCfgDefaults(mutable_cfg);

        // Split the configuration into two maps. The first containing only
        // top-level scalar parameters (i.e. globals), the second containing
        // non-scalar or object elements (maps, lists, etc...).  This allows
        // us to parse and validate all of the global values before we do
        // objects which may depend on them.
        ElementMap params_map;
        ElementMap objects_map;

        isc::dhcp::ConfigPair config_pair;
        BOOST_FOREACH(config_pair, mutable_cfg->mapValue()) {
            std::string element_id = config_pair.first;
            isc::data::ConstElementPtr element = config_pair.second;
            switch (element->getType()) {
                case isc::data::Element::integer:
                case isc::data::Element::real:
                case isc::data::Element::boolean:
                case isc::data::Element::string:
                    params_map[element_id] = element;
                    break;
                default:
                    objects_map[element_id] = element;
                    break;
            }
        }

        // Parse the global, scalar parameters. These are "committed" to
        // the context to make them available during object parsing.
        boost::shared_ptr<MapElement> params_config(new MapElement());
        params_config->setValue(params_map);
        buildParams(params_config);

        // Now parse the configuration objects.

        // Use a pre-ordered list of element ids to parse the elements in a
        // specific order if the list (parser_order_) is not empty; otherwise
        // elements are parsed in the order the value_map presents them.
        if (!parse_order_.empty()) {
            // For each element_id in the parse order list, look for it in the
            // value map.  If the element exists in the map, pass it and it's
            // associated data in for parsing.
            // If there is no matching entry in the value map an error is
            // thrown.  Note, that elements tagged as "optional" from the user
            // perspective must still have default or empty entries in the
            // configuration set to be parsed.
            std::map<std::string, ConstElementPtr>::iterator it;
            BOOST_FOREACH(element_id, parse_order_) {
                it = objects_map.find(element_id);
                if (it != objects_map.end()) {
                    buildAndCommit(element_id, it->second);
                    // We parsed it, take it out of the list.
                    objects_map.erase(it);
                }
                else {
                    isc_throw(DCfgMgrBaseError,
                               "Element required by parsing order is missing: "
                               << element_id << " ("
                               << mutable_cfg->getPosition() << ")");
                }
            }

            // Handle user context here as it is really optional.
            std::string user_context_id("user-context");
            it = objects_map.find(user_context_id);
            if (it != objects_map.end()) {
                buildAndCommit(user_context_id, it->second);
                // We parsed it, take it out of the list.
                objects_map.erase(it);
            }

            // NOTE: When using ordered parsing, the parse order list MUST
            // include every possible element id that the value_map may contain.
            // Entries in the map that are not in the parse order, will not be
            // parsed. For now we will flag this as a programmatic error.  One
            // could attempt to adjust for this, by identifying such entries
            // and parsing them either first or last but which would be correct?
            // Better to hold the engineer accountable.  So, if there are any
            // left in the objects_map then they were not in the parse order.
            if (!objects_map.empty()) {
                std::ostringstream stream;
                bool add_comma = false;
                ConfigPair config_pair;
                BOOST_FOREACH(config_pair, objects_map) {
                    stream << ( add_comma ? ", " : "") << config_pair.first
                           << " (" << config_pair.second->getPosition() << ")";
                    add_comma = true;
                }

                isc_throw(DCfgMgrBaseError,
                        "Configuration contains elements not in parse order: "
                        << stream.str());
            }
        } else {
            // Order doesn't matter so iterate over the value map directly.
            // Pass each element and it's associated data in to be parsed.
            ConfigPair config_pair;
            BOOST_FOREACH(config_pair, objects_map) {
                element_id = config_pair.first;
                buildAndCommit(element_id, config_pair.second);
            }
        }

        // Everything was fine. Configuration set processed successfully.
        if (!check_only) {
            LOG_INFO(dctl_logger, DCTL_CONFIG_COMPLETE).arg(getConfigSummary(0));
            answer = isc::config::createAnswer(0, "Configuration committed.");
        } else {
            answer = isc::config::createAnswer(0, "Configuration seems sane.");
            LOG_INFO(dctl_logger, DCTL_CONFIG_CHECK_COMPLETE)
                .arg(getConfigSummary(0))
                .arg(config::answerToText(answer));
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(dctl_logger, DCTL_PARSER_FAIL).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());

        // An error occurred, so make sure that we restore original context.
        context_ = original_context;
        return (answer);
    }

    if (check_only) {
        // If this is a configuration check only, then don't actually apply
        // the configuration and reverse to the previous one.
        context_ = original_context;
    }

    return (answer);
}

isc::data::ConstElementPtr
DCfgMgrBase::simpleParseConfig(isc::data::ConstElementPtr config_set,
                               bool check_only,
                               const std::function<void()>& post_config_cb) {
    if (!config_set) {
        return (isc::config::createAnswer(1,
                                    std::string("Can't parse NULL config")));
    }
    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_COMMAND,
                DCTL_CONFIG_START).arg(config_set->str());

    // The parsers implement data inheritance by directly accessing
    // configuration context. For this reason the data parsers must store
    // the parsed data into context immediately. This may cause data
    // inconsistency if the parsing operation fails after the context has been
    // modified. We need to preserve the original context here
    // so as we can rollback changes when an error occurs.
    DCfgContextBasePtr original_context = context_;
    resetContext();

    // Answer will hold the result returned to the caller.
    ConstElementPtr answer;

    try {
        // Let's call the actual implementation
        answer = parse(config_set, check_only);

        // Everything was fine. Configuration set processed successfully.
        if (!check_only) {
            if (post_config_cb) {
                post_config_cb();
            }

            LOG_INFO(dctl_logger, DCTL_CONFIG_COMPLETE).arg(getConfigSummary(0));
            answer = isc::config::createAnswer(0, "Configuration committed.");
        } else {
            LOG_INFO(dctl_logger, DCTL_CONFIG_CHECK_COMPLETE)
                .arg(getConfigSummary(0))
                .arg(config::answerToText(answer));
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(dctl_logger, DCTL_PARSER_FAIL).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());

        // An error occurred, so make sure that we restore original context.
        context_ = original_context;
        return (answer);
    }

    if (check_only) {
        // If this is a configuration check only, then don't actually apply
        // the configuration and reverse to the previous one.
        context_ = original_context;
    }

    return (answer);
}


void
DCfgMgrBase::setCfgDefaults(isc::data::ElementPtr) {
}

void
DCfgMgrBase::parseElement(const std::string&, isc::data::ConstElementPtr) {
};


void
DCfgMgrBase::buildParams(isc::data::ConstElementPtr params_config) {
    // Loop through scalars parsing them and committing them to storage.
    BOOST_FOREACH(dhcp::ConfigPair param, params_config->mapValue()) {
        // Call derivation's element parser to parse the element.
        parseElement(param.first, param.second);
    }
}

void DCfgMgrBase::buildAndCommit(std::string& element_id,
                                 isc::data::ConstElementPtr value) {
    // Call derivation's element parser to parse the element.
    parseElement(element_id, value);
}

isc::data::ConstElementPtr
DCfgMgrBase::parse(isc::data::ConstElementPtr, bool) {
    isc_throw(DCfgMgrBaseError, "This class does not implement simple parser paradigm yet");
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
