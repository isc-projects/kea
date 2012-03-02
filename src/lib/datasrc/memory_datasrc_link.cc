// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>

#include <dns/rrclass.h>

#include <datasrc/client.h>
#include <datasrc/memory_datasrc.h>

#include <boost/foreach.hpp>

#include <string>

using namespace isc::dns;
using namespace isc::data;

namespace isc {
namespace datasrc {

namespace {
// convencience function to add an error message to a list of those
// (TODO: move functions like these to some util lib?)
void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}

/// Check if the given element exists in the map, and if it is a string
bool
checkConfigElementString(ConstElementPtr config, const std::string& name,
                         ElementPtr errors)
{
    if (!config->contains(name)) {
        addError(errors,
                 "Config for memory backend does not contain a '"
                 +name+
                 "' value");
        return false;
    } else if (!config->get(name) ||
               config->get(name)->getType() != Element::string) {
        addError(errors, "value of " + name +
                 " in memory backend config is not a string");
        return false;
    } else {
        return true;
    }
}

bool
checkZoneConfig(ConstElementPtr config, ElementPtr errors) {
    bool result = true;
    if (!config || config->getType() != Element::map) {
        addError(errors, "Elements in memory backend's zone list must be maps");
        result = false;
    } else {
        if (!checkConfigElementString(config, "origin", errors)) {
            result = false;
        }
        if (!checkConfigElementString(config, "file", errors)) {
            result = false;
        }
        // we could add some existence/readabilty/parsability checks here
        // if we want
    }
    return result;
}

bool
checkConfig(ConstElementPtr config, ElementPtr errors) {
    /* Specific configuration is under discussion, right now this accepts
     * the 'old' configuration, see [TODO]
     * So for memory datasource, we get a structure like this:
     * { "type": string ("memory"),
     *   "class": string ("IN"/"CH"/etc),
     *   "zones": list
     * }
     * Zones list is a list of maps:
     * { "origin": string,
     *     "file": string
     * }
     *
     * At this moment we cannot be completely sure of the contents of the
     * structure, so we have to do some more extensive tests than should
     * strictly be necessary (e.g. existence and type of elements)
     */
    bool result = true;

    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for memory backend must be a map");
        result = false;
    } else {
        if (!checkConfigElementString(config, "type", errors)) {
            result = false;
        } else {
            if (config->get("type")->stringValue() != "memory") {
                addError(errors,
                         "Config for memory backend is not of type \"memory\"");
                result = false;
            }
        }
        if (!checkConfigElementString(config, "class", errors)) {
            result = false;
        } else {
            try {
                RRClass rrc(config->get("class")->stringValue());
            } catch (const isc::Exception& rrce) {
                addError(errors,
                         "Error parsing class config for memory backend: " +
                         std::string(rrce.what()));
                result = false;
            }
        }
        if (!config->contains("zones")) {
            addError(errors, "No 'zones' element in memory backend config");
            result = false;
        } else if (!config->get("zones") ||
                   config->get("zones")->getType() != Element::list) {
            addError(errors, "'zones' element in memory backend config is not a list");
            result = false;
        } else {
            BOOST_FOREACH(ConstElementPtr zone_config,
                          config->get("zones")->listValue()) {
                if (!checkZoneConfig(zone_config, errors)) {
                    result = false;
                }
            }
        }
    }

    return (result);
}

} // end unnamed namespace

DataSourceClient *
createInstance(isc::data::ConstElementPtr config, std::string& error) {
    ElementPtr errors(Element::createList());
    if (!checkConfig(config, errors)) {
        error = "Configuration error: " + errors->str();
        return (NULL);
    }
    try {
        return (new isc::datasrc::InMemoryClient());
    } catch (const std::exception& exc) {
        error = std::string("Error creating memory datasource: ") + exc.what();
        return (NULL);
    } catch (...) {
        error = std::string("Error creating memory datasource, "
                            "unknown exception");
        return (NULL);
    }
}

void destroyInstance(DataSourceClient* instance) {
    delete instance;
}

} // end of namespace datasrc
} // end of namespace isc
