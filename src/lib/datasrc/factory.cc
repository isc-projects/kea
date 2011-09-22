// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "factory.h"

#include "data_source.h"
#include "database.h"
#include "sqlite3_accessor.h"
#include "memory_datasrc.h"

#include <dlfcn.h>

using namespace isc::data;
using namespace isc::datasrc;

namespace {
// This initial implementation hard codes specific details. These functions
// should be moved to their corresponding backend libs if we plan on making
// them dynamically loadable

void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}

bool
sqlite3CheckConfig(ConstElementPtr config, ElementPtr errors) {
    bool result = true;
    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for SQlite3 backend must be a map");
        result = false;
    } else {
        if (!config->contains("file")) {
            addError(errors,
                     "Config for SQlite3 backend does not contain a 'file' value");
            result = false;
        } else if (!config->get("file") ||
                   config->get("file")->getType() != Element::string) {
            addError(errors, "file value in SQLite3 backend is not a string");
            result = false;
        } else if (config->get("file")->stringValue() == "") {
            addError(errors, "file value in SQLite3 backend is empty");
            result = false;
        }

        if (!config->contains("class")) {
            addError(errors, "Config for SQlite3 backend does not contain a 'class' value");
            result = false;
        } else if (!config->get("class") ||
                   config->get("class")->getType() != Element::string) {
            addError(errors, "class value in SQLite3 backend is not a string");
            result = false;
        } else {
            try {
                isc::dns::RRClass rrclass(config->get("class")->stringValue());
            } catch (const isc::dns::InvalidRRClass& ivrc) {
                addError(errors, ivrc.what());
                result = false;
            } catch (const isc::dns::IncompleteRRClass& icrc) {
                addError(errors, icrc.what());
                result = false;
            }
        }
    }

    return (result);
}

DataSourceClient *
sqlite3CreateInstance(isc::data::ConstElementPtr config) {
    ElementPtr errors(Element::createList());
    if (!sqlite3CheckConfig(config, errors)) {
        isc_throw(DataSourceConfigError, errors->str());
    }
    isc::dns::RRClass rrclass(config->get("class")->stringValue());
    std::string dbfile = config->get("file")->stringValue();
    boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
        new SQLite3Accessor(dbfile, rrclass));
    return (new DatabaseClient(rrclass, sqlite3_accessor));
}

bool
memoryCheckConfig(ConstElementPtr, ElementPtr) {
    // current inmem has no options (yet)
    return true;
}

DataSourceClient *
memoryCreateInstance(isc::data::ConstElementPtr config) {
    ElementPtr errors(Element::createList());
    if (!memoryCheckConfig(config, errors)) {
        isc_throw(DataSourceConfigError, errors->str());
    }
    return (new InMemoryClient());
}

} // end anonymous namespace

namespace isc {
namespace datasrc {

DataSourceClient *
createDataSourceClient(const std::string& type,
                       isc::data::ConstElementPtr config) {
    // For now, mapping hardcoded
    // config is assumed to be ok
    if (type == "sqlite3") {
        void *ds_lib = dlopen("sqlite3_ds.so", RTLD_LAZY);
        if (ds_lib == NULL) {
            isc_throw(DataSourceError, "Unable to load " << type <<
                      ": " << dlerror());
        }
        dlerror();
        ds_creator* ds_create = (ds_creator*)dlsym(ds_lib, "createInstance");
        const char* dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            isc_throw(DataSourceError, "Error in library " << type <<
                      ": " << dlsym_error);
        }
        return (ds_create(config));
    } else if (type == "memory") {
        return (memoryCreateInstance(config));
    } else {
        isc_throw(DataSourceError, "Unknown datasource type: " << type);
    }
}

} // end namespace datasrc
} // end namespace isc

