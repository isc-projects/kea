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

namespace isc {
namespace datasrc {

DataSourceClientContainer::DataSourceClientContainer(const std::string& type,
                                                     ConstElementPtr config)
{
    // The name of the loadable module is type + _ds.so
    // config is assumed to be ok
    std::string dl_name = type + "_ds.so";

    ds_lib = dlopen(dl_name.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (ds_lib == NULL) {
        isc_throw(DataSourceError, "Unable to load " << type <<
                  ": " << dlerror());
    }
    dlerror();
    ds_creator* ds_create = (ds_creator*)dlsym(ds_lib, "createInstance");
    const char* dlsym_error = dlerror();
    if (dlsym_error != NULL) {
        dlclose(ds_lib);
        isc_throw(DataSourceError, "Error in library " << type <<
                  ": " << dlsym_error);
    }
    try {
        instance = ds_create(config);
    } catch (...) {
        dlclose(ds_lib);
        throw;
    }

    dlerror();
    destructor = (ds_destructor*)dlsym(ds_lib, "destroyInstance");
    dlsym_error = dlerror();
    if (dlsym_error != NULL) {
        dlclose(ds_lib);
        isc_throw(DataSourceError, "Error in library " << type <<
                  ": " << dlsym_error);
    }
}

DataSourceClientContainer::~DataSourceClientContainer() {
    destructor(instance);
    dlclose(ds_lib);
}

} // end namespace datasrc
} // end namespace isc

