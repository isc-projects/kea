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

using namespace std;

namespace isc {
namespace hooks {

/// @brief Local class for conversion of void pointers to function pointers
///
/// Converting between void* and function pointers in C++ is fraught with
/// difficulty and pitfalls, e.g. see
/// https://groups.google.com/forum/?hl=en&fromgroups#!topic/comp.lang.c++/37o0l8rtEE0
///
/// The method given in that article - convert using a union is used here.  A
/// union is declared (and zeroed) and the appropriate member extracted when
/// needed.

class PointerConverter {
public:
    /// @brief Constructor
    ///
    /// Zeroes the union and stores the void* pointer we wish to convert (the
    /// one returned by dlsym).
    ///
    /// @param dlsym_ptr void* pointer returned by call to dlsym()
    PointerConverter(void* dlsym_ptr) {
        memset(&pointers_, 0, sizeof(pointers_));
        pointers_.dlsym_ptr = dlsym_ptr;
    }

    /// @name Pointer accessor functions
    ///
    /// It is up to the caller to ensure that the correct member is called so
    /// that the correct trype of pointer is returned.
    ///
    ///@{

    /// @brief Return pointer to callout function
    ///
    /// @return Pointer to the callout function
    CalloutPtr calloutPtr() const {
        return (pointers_.callout_ptr);
    }

    /// @brief Return pointer to load function
    ///
    /// @return Pointer to the load function
    load_function_ptr loadPtr() const {
        return (pointers_.load_ptr);
    }

    /// @brief Return pointer to unload function
    ///
    /// @return Pointer to the unload function
    unload_function_ptr unloadPtr() const {
        return (pointers_.unload_ptr);
    }

    /// @brief Return pointer to version function
    ///
    /// @return Pointer to the version function
    version_function_ptr versionPtr() const {
        return (pointers_.version_ptr);
    }

    ///@}

private:

    /// @brief Union linking void* and pointers to functions.
    union {
        void*                   dlsym_ptr;      // void* returned by dlsym
        CalloutPtr              callout_ptr;    // Pointer to callout
        load_function_ptr       load_ptr;       // Pointer to load function
        unload_function_ptr     unload_ptr;     // Pointer to unload function
        version_function_ptr    version_ptr;    // Pointer to version function
    } pointers_;
};


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

    // Get the pointer to the "version" function.
    PointerConverter pc(dlsym(dl_handle_, VERSION_FUNCTION_NAME));
    if (pc.versionPtr() != NULL) {
        int version = BIND10_HOOKS_VERSION - 1; // This is an invalid value
        try {
            version = (*pc.versionPtr())();
        } catch (...) {
            LOG_ERROR(hooks_logger, HOOKS_VERSION_EXCEPTION).arg(library_name_);
            return (false);
        }

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
    // Set the library index for doing the registration.  This is picked up
    // when the library handle is created.
    manager_->setLibraryIndex(index_);

    // Iterate through the list of known hooks
    vector<string> hook_names = ServerHooks::getServerHooks().getHookNames();
    for (int i = 0; i < hook_names.size(); ++i) {

        // Look up the symbol
        void* dlsym_ptr = dlsym(dl_handle_, hook_names[i].c_str());
        PointerConverter pc(dlsym_ptr);
        if (pc.calloutPtr() != NULL) {
            // Found a symbol, so register it.
            manager_->getLibraryHandle().registerCallout(hook_names[i],
                                                         pc.calloutPtr());
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_STD_CALLOUT_REGISTERED)
                .arg(library_name_).arg(hook_names[i]).arg(dlsym_ptr);

        }
    }
}

// Run the "load" function if present.

bool
LibraryManager::runLoad() {

    // Get the pointer to the "load" function.
    PointerConverter pc(dlsym(dl_handle_, LOAD_FUNCTION_NAME));
    if (pc.loadPtr() != NULL) {

        // Call the load() function with the library handle.  We need to set
        // the CalloutManager's index appropriately.  We'll invalidate it
        // afterwards.

        int status = -1;
        try {
            manager_->setLibraryIndex(index_);
            status = (*pc.loadPtr())(manager_->getLibraryHandle());
        } catch (...) {
            LOG_ERROR(hooks_logger, HOOKS_LOAD_EXCEPTION).arg(library_name_);
            return (false);
        }

        if (status != 0) {
            LOG_ERROR(hooks_logger, HOOKS_LOAD_ERROR).arg(library_name_)
                      .arg(status);
            return (false);
        } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LOAD_SUCCESS)
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

    // Get the pointer to the "load" function.
    PointerConverter pc(dlsym(dl_handle_, UNLOAD_FUNCTION_NAME));
    if (pc.unloadPtr() != NULL) {

        // Call the load() function with the library handle.  We need to set
        // the CalloutManager's index appropriately.  We'll invalidate it
        // afterwards.
        int status = -1;
        try {
            status = (*pc.unloadPtr())();
        } catch (...) {
            // Exception generated.  Note a warning as the unload will occur
            // anyway.
            LOG_WARN(hooks_logger, HOOKS_UNLOAD_EXCEPTION).arg(library_name_);
            return (false);
        }

        if (status != 0) {
            LOG_ERROR(hooks_logger, HOOKS_UNLOAD_ERROR).arg(library_name_)
                      .arg(status);
            return (false);
        } else {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_UNLOAD_SUCCESS)
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
    LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LIBRARY_LOADING)
        .arg(library_name_);

    // In the following, if a method such as openLibrary() fails, it will
    // have issued an error message so there is no need to issue another one
    // here.

    // Open the library (which is a check that it exists and is accessible).
    if (openLibrary()) {

        // Library opened OK, see if a version function is present and if so,
        // check what value it returns.
        if (checkVersion()) {

            // Version OK, so now register the standard callouts and call the
            // library's load() function if present.
            registerStandardCallouts();
            if (runLoad()) {

                // Success - the library has been successfully loaded.
                LOG_INFO(hooks_logger, HOOKS_LIBRARY_LOADED).arg(library_name_);
                return (true);

            } else {

                // The load function failed, so back out.  We can't just close
                // the library as (a) we need to call the library's "unload"
                // function (if present) in case "load" allocated resources that
                // need to be freed and (b) we need to remove any callouts that
                // have been installed.
                static_cast<void>(unloadLibrary());
            }
        }

        // Either the version check or call to load() failed, so close the
        // library and free up resources.  Ignore the status return here - we
        // already know there's an error and will have output a message.
        static_cast<void>(closeLibrary());
    }

    return (false);
}

// The library unloading function.  Call the unload() function (if present),
// remove callouts from the callout manager, then close the library.

bool
LibraryManager::unloadLibrary() {
    LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LIBRARY_UNLOADING)
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
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_CALLOUTS_REMOVED)
                .arg(hooks[i]).arg(library_name_);
        }
    }

    // ... and close the library.
    result = closeLibrary() && result;
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
