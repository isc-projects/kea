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

