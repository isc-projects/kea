// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <host_cache.h>
#include <host_cache_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <process/daemon.h>

using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::process;

namespace isc {
namespace host_cache {

/// @brief Pointer to the Host Cache instance.
HostCachePtr hcptr;

/// @brief Host Cache factory.
HostDataSourcePtr
factory(const DatabaseConnection::ParameterMap&) {
    return (hcptr);
}

} // end of namespace isc::host_cache
} // end of namespace isc

using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::host_cache;

extern "C" {

/// @brief This is a command callout for 'cache-size' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_size(CalloutHandle& handle) {
    return (hcptr->cacheSizeHandler(handle));
}

/// @brief This is a command callout for 'cache-clear' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_clear(CalloutHandle& handle) {
    return (hcptr->cacheClearHandler(handle));
}

/// @brief This is a command callout for 'cache-flush' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_flush(CalloutHandle& handle) {
    return (hcptr->cacheFlushHandler(handle));
}

/// @brief This is a command callout for 'cache-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_get(CalloutHandle& handle) {
    return (hcptr->cacheGetHandler(handle));
}

/// @brief This is a command callout for 'cache-get-by-id' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_get_by_id(CalloutHandle& handle) {
    return (hcptr->cacheGetByIdHandler(handle));
}

/// @brief This is a command callout for 'cache-insert' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_insert(CalloutHandle& handle) {
    return (hcptr->cacheInsertHandler(handle));
}

/// @brief This is a command callout for 'cache-write' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_write(CalloutHandle& handle) {
    return (hcptr->cacheWriteHandler(handle));
}

/// @brief This is a command callout for 'cache-load' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_load(CalloutHandle& handle) {
    return (hcptr->cacheLoadHandler(handle));
}

/// @brief This is a command callout for 'cache-remove' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int cache_remove(CalloutHandle& handle) {
    return (hcptr->cacheRemoveHandler(handle));
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        // Make the hook library not loadable by d2 or ca.
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp4");
            }
        } else {
            if (proc_name != "kea-dhcp6") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp6");
            }
        }

        // Get and decode parameters.
        hcptr.reset(new HostCache());
        ConstElementPtr config = handle.getParameter("host-cache");
        hcptr->configure(config);
        HostDataSourceFactory::registerFactory("cache", factory);
        handle.registerCommandCallout("cache-clear", cache_clear);
        handle.registerCommandCallout("cache-flush", cache_flush);
        handle.registerCommandCallout("cache-get", cache_get);
        handle.registerCommandCallout("cache-get-by-id", cache_get_by_id);
        handle.registerCommandCallout("cache-insert", cache_insert);
        handle.registerCommandCallout("cache-load", cache_load);
        handle.registerCommandCallout("cache-remove", cache_remove);
        handle.registerCommandCallout("cache-size", cache_size);
        handle.registerCommandCallout("cache-write", cache_write);
        HostMgr::instance().addBackend("type=cache");
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_CONFIGURATION_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_INIT_OK);
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(host_cache_logger, HOST_CACHE_DEINIT_OK);
    HostMgr::delBackend("cache");
    hcptr.reset();
    HostDataSourceFactory::deregisterFactory("cache");
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
