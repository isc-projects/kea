// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <cc/command_interpreter.h>
#include <d2/d2_log.h>
#include <dhcp/libdhcp++.h>
#include <d2/d_cfg_mgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
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
namespace d2 {

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
DCfgMgrBase::parseConfig(isc::data::ConstElementPtr config_set) {
    LOG_DEBUG(dctl_logger, DBGLVL_COMMAND,
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
        // Split the configuration into two maps. The first containing only
        // top-level scalar parameters (i.e. globals), the second containing
        // non-scalar or object elements (maps, lists, etc...).  This allows
        // us to parse and validate all of the global values before we do
        // objects which may depend on them.
        ElementMap params_map;
        ElementMap objects_map;

        isc::dhcp::ConfigPair config_pair;
        BOOST_FOREACH(config_pair, config_set->mapValue()) {
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
                               << config_set->getPosition() << ")");
                }
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
        LOG_INFO(dctl_logger, DCTL_CONFIG_COMPLETE).arg(getConfigSummary(0));
        answer = isc::config::createAnswer(0, "Configuration committed.");

    } catch (const std::exception& ex) {
        LOG_ERROR(dctl_logger, DCTL_PARSER_FAIL).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());

        // An error occurred, so make sure that we restore original context.
        context_ = original_context;
        return (answer);
    }

    return (answer);
}

void
DCfgMgrBase::buildParams(isc::data::ConstElementPtr params_config) {
    // Loop through scalars parsing them and committing them to storage.
    BOOST_FOREACH(dhcp::ConfigPair param, params_config->mapValue()) {
        // Call derivation's method to create the proper parser.
        dhcp::ParserPtr parser(createConfigParser(param.first,
                                                  param.second->getPosition()));
        parser->build(param.second);
        parser->commit();
    }
}

void DCfgMgrBase::buildAndCommit(std::string& element_id,
                                 isc::data::ConstElementPtr value) {
    // Call derivation's implementation to create the appropriate parser
    // based on the element id.
    ParserPtr parser = createConfigParser(element_id, value->getPosition());
    if (!parser) {
        isc_throw(DCfgMgrBaseError, "Could not create parser");
    }

    // Invoke the parser's build method passing in the value. This will
    // "convert" the Element form of value into the actual data item(s)
    // and store them in parser's local storage.
    parser->build(value);

    // Invoke the parser's commit method. This "writes" the the data
    // item(s) stored locally by the parser into the context.  (Note that
    // parsers are free to do more than update the context, but that is an
    // nothing something we are concerned with here.)
    parser->commit();
}

}; // end of isc::dhcp namespace
}; // end of isc namespace

