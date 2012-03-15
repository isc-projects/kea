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

#include <datasrc/sqlite3_accessor.h>
#include <datasrc/database.h>

#include <string>

using namespace std;
using namespace isc::dns;
using namespace isc::data;

namespace isc {
namespace datasrc {

namespace {

const char* const CONFIG_ITEM_DATABASE_FILE = "database_file";

void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}

bool
checkConfig(ConstElementPtr config, ElementPtr errors) {
    /* Specific configuration is under discussion, right now this accepts
     * the 'old' configuration, see header file
     */
    bool result = true;

    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for SQlite3 backend must be a map");
        result = false;
    } else {
        if (!config->contains(CONFIG_ITEM_DATABASE_FILE)) {
            addError(errors,
                     "Config for SQlite3 backend does not contain a '" +
                     string(CONFIG_ITEM_DATABASE_FILE) +
                     "' value");
            result = false;
        } else if (!config->get(CONFIG_ITEM_DATABASE_FILE) ||
                   config->get(CONFIG_ITEM_DATABASE_FILE)->getType() !=
                   Element::string) {
            addError(errors, "value of " + string(CONFIG_ITEM_DATABASE_FILE) +
                     " in SQLite3 backend is not a string");
            result = false;
        } else if (config->get(CONFIG_ITEM_DATABASE_FILE)->stringValue() ==
                   "") {
            addError(errors, "value of " + string(CONFIG_ITEM_DATABASE_FILE) +
                     " in SQLite3 backend is empty");
            result = false;
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
    std::string dbfile = config->get(CONFIG_ITEM_DATABASE_FILE)->stringValue();
    try {
        boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
            new SQLite3Accessor(dbfile, "IN")); // XXX: avoid hardcode RR class
        return (new DatabaseClient(isc::dns::RRClass::IN(), sqlite3_accessor));
    } catch (const std::exception& exc) {
        error = std::string("Error creating sqlite3 datasource: ") + exc.what();
        return (NULL);
    } catch (...) {
        error = std::string("Error creating sqlite3 datasource, "
                            "unknown exception");
        return (NULL);
    }
}

void destroyInstance(DataSourceClient* instance) {
    delete instance;
}

} // end of namespace datasrc
} // end of namespace isc
