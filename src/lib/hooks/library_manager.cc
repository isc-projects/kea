// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <hooks/hooks.h>
#include <hooks/hooks_log.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager.h>
#include <hooks/server_hooks.h>

#include <string>
#include <vector>

#include <dlfcn.h>

namespace {

// String constants

const char* LOAD_FUNCTION_NAME = "load";
const char* UNLOAD_FUNCTION_NAME = "unload";
const char* VERSION_FUNCTION_NAME = "version";
}

using namespace std;

namespace isc {
namespace hooks {

// Open the library

bool
LibraryManager::openLibrary() {

    // Open the library.  We'll resolve names now, so that if there are any
    // issues we don't bugcheck in the middle of apparently unrelated code.
    dl_handle_ = dlopen(library_name_.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (dl_handle_ == NULL) {
        LOG_ERROR(hooks_logger, HOOKS_OPEN_ERROR).arg(library_name_)
                  .arg(dlerror());
    }

    return (dl_handle_ != NULL);
}

// Close the library if not already open

bool
LibraryManager::closeLibrary() {

    // Close the library if it is open. (If not, this is a no-op.)
    int status = 0;
    if (dl_handle_ != NULL) {
        status = dlclose(dl_handle_);
        dl_handle_ = NULL;
        if (status != 0) {
            LOG_ERROR(hooks_logger, HOOKS_CLOSE_ERROR).arg(library_name_)
                      .arg(dlerror());
        }
    }

    return (status == 0);
}

// Check the version of the library

bool
LibraryManager::checkVersion() const {

    // Look up the "version" string in the library.  This is returned as
    // "void*": without any other information, we must assume that it is of
    // the correct type of version_function_ptr.
    //
    // Note that converting between void* and function pointers in C++ is
    // fraught with difficulty and pitfalls (e.g. see
    // https://groups.google.com/forum/?hl=en&fromgroups#!topic/
    // comp.lang.c++/37o0l8rtEE0)
    // The method given in that article - convert using a union is used here.
    union {
        version_function_ptr    ver_ptr;
        void*                   dlsym_ptr;
    } pointers;

    // Zero the union, whatever the size of the pointers.
    pointers.ver_ptr = NULL;
    pointers.dlsym_ptr = NULL;

    // Get the pointer to the "version" function.
    pointers.dlsym_ptr = dlsym(dl_handle_, VERSION_FUNCTION_NAME);
    if (pointers.ver_ptr != NULL) {
        int version = (*pointers.ver_ptr)();
        if (version == BIND10_HOOKS_VERSION) {
            // All OK, version checks out
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_LIBRARY_VERSION)
                      .arg(library_name_).arg(version);
            return (true);

        } else {
            LOG_ERROR(hooks_logger, HOOKS_INCORRECT_VERSION).arg(library_name_)
                      .arg(version).arg(BIND10_HOOKS_VERSION);
        }
    } else {
        LOG_ERROR(hooks_logger, HOOKS_NO_VERSION).arg(library_name_);
    }

    return (false);
}

// Register the standard callouts

void
LibraryManager::registerStandardCallouts() {
    // Create a library handle for doing the registration.  We also need to
    // set the current library index to indicate the current library.
    manager_->setLibraryIndex(index_);
    LibraryHandle library_handle(manager_.get());

    // Iterate through the list of known hooksv
    vector<string> hook_names = ServerHooks::getServerHooks().getHookNames();
    for (int i = 0; i < hook_names.size(); ++i) {

        // Convert void* to function pointers using the same tricks as
        // described above.
        union {
            CalloutPtr  callout_ptr;
            void*       dlsym_ptr;
        } pointers;
        pointers.callout_ptr = NULL;
        pointers.dlsym_ptr = NULL;

        // Look up the symbol
        pointers.dlsym_ptr = dlsym(dl_handle_, hook_names[i].c_str());
        if (pointers.callout_ptr != NULL) {
            // Found a symbol, so register it.
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_REGISTER_STD_CALLOUT)
                .arg(library_name_).arg(hook_names[i]);
            library_handle.registerCallout(hook_names[i], pointers.callout_ptr);

        }
    }
}

// Run the "load" function if present.

bool
LibraryManager::runLoad() {

    // Look up the "load" function in the library.  The code here is similar
    // to that in "checkVersion".
    union {
        load_function_ptr   load_ptr;
        void*               dlsym_ptr;
    } pointers;

    // Zero the union, whatever the size of the pointers.
    pointers.load_ptr = NULL;
    pointers.dlsym_ptr = NULL;

    // Get the pointer to the "load" function.
    pointers.dlsym_ptr = dlsym(dl_handle_, LOAD_FUNCTION_NAME);
    if (pointers.load_ptr != NULL) {

        // Call the load() function with the library handle.  We need to set
        // the CalloutManager's index appropriately.  We'll invalidate it
        // afterwards.
        manager_->setLibraryIndex(index_);
        int status = (*pointers.load_ptr)(manager_->getLibraryHandle());
        manager_->setLibraryIndex(index_);
        if (status != 0) {
            LOG_ERROR(hooks_logger, HOOKS_LOAD_ERROR).arg(library_name_)
                      .arg(status);
            return (false);
        } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LOAD)
            .arg(library_name_);
        }
    } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_NO_LOAD)
            .arg(library_name_);
    }

    return (true);
}


// Run the "unload" function if present.

bool
LibraryManager::runUnload() {

    // Look up the "load" function in the library.  The code here is similar
    // to that in "checkVersion".
    union {
        unload_function_ptr unload_ptr;
        void*               dlsym_ptr;
    } pointers;

    // Zero the union, whatever the relative size of the pointers.
    pointers.unload_ptr = NULL;
    pointers.dlsym_ptr = NULL;

    // Get the pointer to the "load" function.
    pointers.dlsym_ptr = dlsym(dl_handle_, UNLOAD_FUNCTION_NAME);
    if (pointers.unload_ptr != NULL) {

        // Call the load() function with the library handle.  We need to set
        // the CalloutManager's index appropriately.  We'll invalidate it
        // afterwards.
        int status = (*pointers.unload_ptr)();
        if (status != 0) {
            LOG_ERROR(hooks_logger, HOOKS_UNLOAD_ERROR).arg(library_name_)
                      .arg(status);
            return (false);
        } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_UNLOAD)
            .arg(library_name_);
        }
    } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_NO_UNLOAD)
            .arg(library_name_);
    }

    return (true);
}

// The main library loading function.

bool
LibraryManager::loadLibrary() {
    LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LOAD_LIBRARY)
        .arg(library_name_);

    // In the following, if a method such as openLibrary() fails, it will
    // have issued an error message so there is no need to issue another one
    // here.

    if (openLibrary()) {

        // Library opened OK, see if a version function is present and if so,
        // check it.
        if (checkVersion()) {

            // Version OK, so now register the standard callouts and call the
            // librarie's load() function if present.
            registerStandardCallouts();
            if (runLoad()) {

                // Success - the library has been successfully loaded.
                LOG_INFO(hooks_logger, HOOKS_LIBRARY_LOADED).arg(library_name_);
                return (true);
            } else {

                // The load function failed, so back out.  We can't just close
                // the library as (a) we need to call the library's "unload"
                // function (if present) in case "load" allocated resources that
                // need to be freed and (b) - we need to remove any callouts
                // that have been installed.
                static_cast<void>(unloadLibrary());
            }
        } else {

            // Version check failed so close the library and free up resources.
            // Ignore the status return here - we already have an error
            // consition.
            static_cast<void>(closeLibrary());
        }
    }

    return (false);
}

// The library unloading function.  Call the unload() function (if present),
// remove callouts from the callout manager, then close the library.

bool
LibraryManager::unloadLibrary() {
    LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_UNLOAD_LIBRARY)
        .arg(library_name_);

    // Call the unload() function if present.  Note that this is done first -
    // operations take place in the reverse order to which they were done when
    // the library was loaded.
    bool result = runUnload();

    // Regardless of status, remove all callouts associated with this library
    // on all hooks.
    vector<string> hooks = ServerHooks::getServerHooks().getHookNames();
    manager_->setLibraryIndex(index_);
    for (int i = 0; i < hooks.size(); ++i) {
        bool removed = manager_->deregisterAllCallouts(hooks[i]);
        if (removed) {
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUT_REMOVED)
                .arg(hooks[i]).arg(library_name_);
        }
    }

    // ... and close the library.
    result = result && closeLibrary();
    if (result) {

        // Issue the informational message only if the library was unloaded
        // with no problems.  If there was an issue, an error message would
        // have been issued.
        LOG_INFO(hooks_logger, HOOKS_LIBRARY_UNLOADED).arg(library_name_);
    }

    return (result);
}

} // namespace hooks
} // namespace isc
