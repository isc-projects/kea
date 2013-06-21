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

#include "exceptions.h"
#include "database.h"
#include "sqlite3_accessor.h"

#include "datasrc_config.h"

#include <datasrc/logger.h>

#include <exceptions/exceptions.h>

#include <dlfcn.h>
#include <cstdlib>

using namespace std;
using namespace isc::data;
using namespace isc::datasrc;

namespace {
// This helper function takes the 'type' string as passed to
// the DataSourceClient container below, and, unless it
// already specifies a specific loadable .so file, will
// convert the short-name to the full file.
// I.e. it will add '_ds.so' (if necessary), and prepend
// it with an absolute path (if necessary).
// Returns the resulting string to use with LibraryContainer.
const std::string
getDataSourceLibFile(const std::string& type) {
    if (type.empty()) {
        isc_throw(DataSourceLibraryError,
                  "DataSourceClient container called with empty type value");
    }
    if (type == ".so") {
        isc_throw(DataSourceLibraryError, "DataSourceClient container called "
                                          "with bad type or file name");
    }

    // Type can be either a short name, in which case we need to
    // append "_ds.so", or it can be a direct .so library.
    std::string lib_file = type;
    const int ext_pos = lib_file.rfind(".so");
    if (ext_pos == std::string::npos || ext_pos + 3 != lib_file.length()) {
        lib_file.append("_ds.so");
    }
    // And if it is not an absolute path, prepend it with our
    // loadable backend library path
    if (type[0] != '/') {
        // When running from the build tree, we do NOT want
        // to load the installed loadable library
        if (getenv("B10_FROM_BUILD") != NULL) {
            lib_file = std::string(getenv("B10_FROM_BUILD")) +
                       "/src/lib/datasrc/.libs/" + lib_file;
        } else {
            lib_file = isc::datasrc::BACKEND_LIBRARY_PATH + lib_file;
        }
    }
    return (lib_file);
}
} // end anonymous namespace

namespace isc {
namespace datasrc {

LibraryContainer::LibraryContainer(const std::string& name) {
    // use RTLD_GLOBAL so that shared symbols (e.g. exceptions)
    // are recognized as such
    ds_lib_ = dlopen(name.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (ds_lib_ == NULL) {
        // This may cause the filename to appear twice in the actual
        // error, but the output of dlerror is implementation-dependent
        isc_throw(DataSourceLibraryOpenError,
                  "dlopen failed for " << name << ": " << dlerror());
    }
}

LibraryContainer::~LibraryContainer() {
    dlclose(ds_lib_);
}

void*
LibraryContainer::getSym(const char* name) {
    // Since dlsym can return NULL on success, we check for errors by
    // first clearing any existing errors with dlerror(), then calling dlsym,
    // and finally checking for errors with dlerror()
    dlerror();

    void *sym = dlsym(ds_lib_, name);

    const char* dlsym_error = dlerror();
    if (dlsym_error != NULL) {
        isc_throw(DataSourceLibrarySymbolError, dlsym_error);
    }

    return (sym);
}

DataSourceClientContainer::DataSourceClientContainer(const std::string& type,
                                                     ConstElementPtr config)
: ds_lib_(getDataSourceLibFile(type))
{
    // We are casting from a data to a function pointer here
    // Some compilers (rightfully) complain about that, but
    // c-style casts are accepted the most here. If we run
    // into any that also don't like this, we might need to
    // use some form of union cast or memory copy to get
    // from the void* to the function pointer.
    ds_creator* ds_create = (ds_creator*)ds_lib_.getSym("createInstance");
    destructor_ = (ds_destructor*)ds_lib_.getSym("destroyInstance");

    std::string error;
    try {
        instance_ = ds_create(config, error);
        if (instance_ == NULL) {
            isc_throw(DataSourceError, error);
        }
    } catch (const std::exception& exc) {
        isc_throw(DataSourceError, "Unknown uncaught exception from " + type +
                                   " createInstance: " + exc.what());
    } catch (...) {
        isc_throw(DataSourceError, "Unknown uncaught exception from " + type);
    }
}

DataSourceClientContainer::~DataSourceClientContainer() {
    destructor_(instance_);
}

} // end namespace datasrc
} // end namespace isc

