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
#include <datasrc/factory.h>
#include <datasrc/memory_datasrc.h>

#include <exceptions/exceptions.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>

using namespace isc::dns;
using namespace isc::data;

namespace isc {
namespace datasrc {

/// This exception is raised if there is an error in the configuration
/// that has been passed; missing information, duplicate values, etc.
class InMemoryConfigError : public isc::Exception {
public:
    InMemoryConfigError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

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
        return (false);
    } else if (!config->get(name) ||
               config->get(name)->getType() != Element::string) {
        addError(errors, "value of " + name +
                 " in memory backend config is not a string");
        return (false);
    } else {
        return (true);
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
        if (config->contains("class")) {
            if (!checkConfigElementString(config, "class", errors)) {
                result = false;
            } else {
                try {
                    RRClass(config->get("class")->stringValue());
                } catch (const isc::Exception& rrce) {
                    addError(errors,
                             "Error parsing class config for memory backend: " +
                             std::string(rrce.what()));
                    result = false;
                }
            }
        }
        if (!config->contains("zones")) {
            // Assume empty list of zones
        } else if (!config->get("zones") ||
                   config->get("zones")->getType() != Element::list) {
            addError(errors,
                     "'zones' element in memory backend config is not a list");
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

// Apply the given config to the just-initialized client
// client must be freshly allocated, and config_value should have been
// checked by the caller
void
applyConfig(isc::datasrc::InMemoryClient& client,
            isc::data::ConstElementPtr config_value)
{
    // XXX: We have lost the context to get to the default values here,
    // as a temporary workaround we hardcode the IN class here.
    isc::dns::RRClass rrclass = RRClass::IN();
    if (config_value->contains("class")) {
        rrclass = RRClass(config_value->get("class")->stringValue());
    }
    ConstElementPtr zones_config = config_value->get("zones");
    if (!zones_config) {
        // XXX: Like the RR class, we cannot retrieve the default value here,
        // so we assume an empty zone list in this case.
        return;
    }

    BOOST_FOREACH(ConstElementPtr zone_config, zones_config->listValue()) {
        ConstElementPtr origin = zone_config->get("origin");
        const std::string origin_txt = origin ? origin->stringValue() : "";
        if (origin_txt.empty()) {
            isc_throw(InMemoryConfigError, "Missing zone origin");
        }
        ConstElementPtr file = zone_config->get("file");
        const std::string file_txt = file ? file->stringValue() : "";
        if (file_txt.empty()) {
            isc_throw(InMemoryConfigError, "Missing zone file for zone: "
                      << origin_txt);
        }

        // We support the traditional text type and SQLite3 backend.  For the
        // latter we create a client for the underlying SQLite3 data source,
        // and build the in-memory zone using an iterator of the underlying
        // zone.
        ConstElementPtr filetype = zone_config->get("filetype");
        const std::string filetype_txt = filetype ? filetype->stringValue() :
            "text";
        boost::scoped_ptr<DataSourceClientContainer> container;
        if (filetype_txt == "sqlite3") {
            container.reset(new DataSourceClientContainer(
                                "sqlite3",
                                Element::fromJSON("{\"database_file\": \"" +
                                                  file_txt + "\"}")));
        } else if (filetype_txt != "text") {
            isc_throw(InMemoryConfigError, "Invalid filetype for zone "
                      << origin_txt << ": " << filetype_txt);
        }

        // Note: we don't want to have such small try-catch blocks for each
        // specific error.  We may eventually want to introduce some unified
        // error handling framework as we have more configuration parameters.
        // See bug #1627 for the relevant discussion.
        InMemoryZoneFinder* imzf = NULL;
        try {
            imzf = new InMemoryZoneFinder(rrclass, Name(origin_txt));
        } catch (const isc::dns::NameParserException& ex) {
            isc_throw(InMemoryConfigError, "unable to parse zone's origin: " <<
                      ex.what());
        }

        boost::shared_ptr<InMemoryZoneFinder> zone_finder(imzf);
        const result::Result result = client.addZone(zone_finder);
        if (result == result::EXIST) {
            isc_throw(InMemoryConfigError, "zone "<< origin->str()
                      << " already exists");
        }

        /*
         * TODO: Once we have better reloading of configuration (something
         * else than throwing everything away and loading it again), we will
         * need the load method to be split into some kind of build and
         * commit/abort parts.
         */
        if (filetype_txt == "text") {
            zone_finder->load(file_txt);
        } else {
            zone_finder->load(*container->getInstance().getIterator(
                                  Name(origin_txt)));
        }
    }
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
        std::auto_ptr<InMemoryClient> client(new isc::datasrc::InMemoryClient());
        applyConfig(*client, config);
        return (client.release());
    } catch (const isc::Exception& isce) {
        error = isce.what();
        return (NULL);
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
