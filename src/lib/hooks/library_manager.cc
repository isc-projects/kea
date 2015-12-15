// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks.h>
#include <hooks/hooks_log.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager.h>
#include <hooks/pointer_converter.h>
#include <hooks/server_hooks.h>
#include <log/logger_manager.h>
#include <log/logger_support.h>
#include <log/message_initializer.h>

#include <string>
#include <vector>

#include <dlfcn.h>

using namespace std;

namespace isc {
namespace hooks {


// Constructor (used by external agency)
LibraryManager::LibraryManager(const std::string& name, int index,
                               const boost::shared_ptr<CalloutManager>& manager)
        : dl_handle_(NULL), index_(index), manager_(manager),
          library_name_(name)
{
    if (!manager) {
        isc_throw(NoCalloutManager, "must specify a CalloutManager when "
                  "instantiating a LibraryManager object");
    }
}

// Constructor (used by "validate" for library validation).  Note that this
// sets "manager_" to not point to anything, which means that methods such as
// registerStandardCallout() will fail, probably with a segmentation fault.
// There are no checks for this condition in those methods: this constructor
// is declared "private", so can only be executed by a method in this class.
// The only method to do so is "validateLibrary", which takes care not to call
// methods requiring a non-NULL manager.
LibraryManager::LibraryManager(const std::string& name)
        : dl_handle_(NULL), index_(-1), manager_(), library_name_(name)
{}

// Destructor.  
LibraryManager::~LibraryManager() {
    if (manager_) {
        // LibraryManager instantiated to load a library, so ensure that
        // it is unloaded before exiting.
        static_cast<void>(unloadLibrary());
    } else {
        // LibraryManager instantiated to validate a library, so just ensure
        // that it is closed before exiting.
        static_cast<void>(closeLibrary());
    }
}

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
        int version = KEA_HOOKS_VERSION - 1; // This is an invalid value
        try {
            version = (*pc.versionPtr())();
        } catch (...) {
            LOG_ERROR(hooks_logger, HOOKS_VERSION_EXCEPTION).arg(library_name_);
            return (false);
        }

        if (version == KEA_HOOKS_VERSION) {
            // All OK, version checks out
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS, HOOKS_LIBRARY_VERSION)
                      .arg(library_name_).arg(version);
            return (true);

        } else {
            LOG_ERROR(hooks_logger, HOOKS_INCORRECT_VERSION).arg(library_name_)
                      .arg(version).arg(KEA_HOOKS_VERSION);
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
    for (size_t i = 0; i < hook_names.size(); ++i) {

        // Look up the symbol
        void* dlsym_ptr = dlsym(dl_handle_, hook_names[i].c_str());
        PointerConverter pc(dlsym_ptr);
        if (pc.calloutPtr() != NULL) {
            // Found a symbol, so register it.
            manager_->getLibraryHandle().registerCallout(hook_names[i],
                                                         pc.calloutPtr());
            LOG_DEBUG(hooks_logger, HOOKS_DBG_CALLS,
                      HOOKS_STD_CALLOUT_REGISTERED).arg(library_name_)
                      .arg(hook_names[i]).arg(dlsym_ptr);

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
        } catch (const isc::Exception& ex) {
            LOG_ERROR(hooks_logger, HOOKS_LOAD_FRAMEWORK_EXCEPTION)
                .arg(library_name_).arg(ex.what());
            return (false);
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
        } catch (const isc::Exception& ex) {
            LOG_ERROR(hooks_logger, HOOKS_UNLOAD_FRAMEWORK_EXCEPTION)
                .arg(library_name_).arg(ex.what());
            return (false);
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

        // The hook libraries provide their own log messages and logger
        // instances. This step is required to register log messages for
        // the library being loaded in the global dictionary. Ideally, this
        // should be called after all libraries have been loaded but we're
        // going to call the version() and load() functions here and these
        // functions may already contain logging statements.
        isc::log::MessageInitializer::loadDictionary();

        // The log messages registered by the new hook library may duplicate
        // some of the existing messages. Log warning for each duplicated
        // message now.
        isc::log::LoggerManager::logDuplicatedMessages();

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
// remove callouts from the callout manager, then close the library.  This is
// only run if the library is still loaded and is a no-op if the library is
// not open.

bool
LibraryManager::unloadLibrary() {
    bool result = true;
    if (dl_handle_ != NULL) {
        LOG_DEBUG(hooks_logger, HOOKS_DBG_TRACE, HOOKS_LIBRARY_UNLOADING)
            .arg(library_name_);

        // Call the unload() function if present.  Note that this is done first
        // - operations take place in the reverse order to which they were done
        // when the library was loaded.
        result = runUnload();

        // Regardless of status, remove all callouts associated with this
        // library on all hooks.
        vector<string> hooks = ServerHooks::getServerHooks().getHookNames();
        manager_->setLibraryIndex(index_);
        for (size_t i = 0; i < hooks.size(); ++i) {
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
    }
    return (result);
}

// Validate the library.  We must be able to open it, and the version function
// must both exist and return the right number.  Note that this is a static
// method.

bool
LibraryManager::validateLibrary(const std::string& name) {
    // Instantiate a library manager for the validation.  We use the private
    // constructor as we don't supply a CalloutManager.
    LibraryManager manager(name);

    // Try to open it and, if we succeed, check the version.
    bool validated = manager.openLibrary() && manager.checkVersion();

    // Regardless of whether the version checked out, close the library. (This
    // is a no-op if the library failed to open.)
    static_cast<void>(manager.closeLibrary());

    return (validated);
}

// @note Moved from its own hooks.cc file to avoid undefined reference
// with static link.
void hooksStaticLinkInit() {
    if (!isc::log::isLoggingInitialized()) {
        isc::log::initLogger(std::string("userlib"));
    }
}

} // namespace hooks
} // namespace isc
