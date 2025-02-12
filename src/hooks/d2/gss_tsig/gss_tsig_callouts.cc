// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <gss_tsig_context.h>
#include <gss_tsig_impl.h>
#include <gss_tsig_log.h>
#include <process/daemon.h>
#include <exceptions/exceptions.h>
#include <functional>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::gss_tsig;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::dns;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::process;
using namespace std;

namespace isc {
namespace gss_tsig {

/// @brief The GSS-TSIG hook implementation object.
GssTsigImplPtr impl;

} // end of namespace isc::gss_tsig
} // end of namespace isc

extern "C" {

/// @brief The gss-tsig-get command.
///
/// This command takes an argument id with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int get(CalloutHandle& handle) {
    impl->getHandler(handle);
    return (0);
}

/// @brief The gss-tsig-get-all command.
///
/// @param handle CalloutHandle.
/// @return always 0.
int get_all(CalloutHandle& handle) {
    impl->getAllHandler(handle);
    return (0);
}

/// @brief The gss-tsig-list command.
///
/// @param handle CalloutHandle.
/// @return always 0.
int lists(CalloutHandle& handle) {
    impl->listHandler(handle);
    return (0);
}

/// @brief The gss-tsig-key-get command.
///
/// This command takes an argument name with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int key_get(CalloutHandle& handle) {
    impl->keyGetHandler(handle);
    return (0);
}

/// @brief The gss-tsig-key-expire command.
///
/// This command takes an argument name with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int key_expire(CalloutHandle& handle) {
    impl->keyExpireHandler(handle);
    return (0);
}

/// @brief The gss-tsig-key-del command.
///
/// This command takes an argument name with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int key_del(CalloutHandle& handle) {
    impl->keyDelHandler(handle);
    return (0);
}

/// @brief The gss-tsig-purge command.
///
/// This command takes an argument id with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int purge(CalloutHandle& handle) {
    impl->purgeHandler(handle);
    return (0);
}

/// @brief The gss-tsig-purge-all command.
///
/// @param handle CalloutHandle.
/// @return always 0.
int purge_all(CalloutHandle& handle) {
    impl->purgeAllHandler(handle);
    return (0);
}

/// @brief The gss-tsig-rekey command.
///
/// This command takes an argument id with a string value.
///
/// @param handle CalloutHandle.
/// @return always 0.
int rekey(CalloutHandle& handle) {
    impl->rekeyHandler(handle);
    return (0);
}

/// @brief The gss-tsig-rekey-all command.
///
/// @param handle CalloutHandle.
/// @return always 0.
int rekey_all(CalloutHandle& handle) {
    impl->rekeyAllHandler(handle);
    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @return always 0.
int load(LibraryHandle& handle) {
    try {
        // Create the implementation object.
        impl.reset(new GssTsigImpl());

        // Make the hook library loadable only by d2.
        const std::string& proc_name = Daemon::getProcName();
        if (proc_name != "kea-dhcp-ddns") {
            isc_throw(Unexpected, "Bad process name: " << proc_name
                      << ", expected kea-dhcp-ddns");
        }

        // Load the configuration (syntax check).
        ConstElementPtr config = handle.getParameters();
        impl->configure(config);

        // Register commands.
        handle.registerCommandCallout("gss-tsig-get", get);
        handle.registerCommandCallout("gss-tsig-get-all", get_all);
        handle.registerCommandCallout("gss-tsig-key-del", key_del);
        handle.registerCommandCallout("gss-tsig-key-expire", key_expire);
        handle.registerCommandCallout("gss-tsig-key-get", key_get);
        handle.registerCommandCallout("gss-tsig-list", lists);
        handle.registerCommandCallout("gss-tsig-purge", purge);
        handle.registerCommandCallout("gss-tsig-purge-all", purge_all);
        handle.registerCommandCallout("gss-tsig-rekey", rekey);
        handle.registerCommandCallout("gss-tsig-rekey-all", rekey_all);
    } catch (const std::exception& ex) {
        LOG_ERROR(gss_tsig_logger, GSS_TSIG_LOAD_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(gss_tsig_logger, GSS_TSIG_LOAD_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    if (impl) {
        IOServiceMgr::instance().unregisterIOService(impl->getIOService());
        impl->stop();
        impl.reset();
    }
    LOG_INFO(gss_tsig_logger, GSS_TSIG_UNLOAD_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

/// This function is called when the server finishes (re)configuration.
///
/// The server reverse map is built and an error is returned when a
/// configuration mismatch is detected.
///
/// @param handle CalloutHandle.
/// @return always 0.
/// @throw Unexpected when something went really wrong.
int d2_srv_configured(CalloutHandle& handle) {
    // First check the status.
    if (handle.getStatus() != CalloutHandle::NEXT_STEP_CONTINUE) {
        return (0);
    }
    IOServiceMgr::instance().registerIOService(impl->getIOService());
    D2CfgContextPtr d2_config;
    // Get the parameters.
    handle.getArgument("server_config", d2_config);
    if (!d2_config) {
        const string error("Error: gss_tsig d2_srv_configured: server_config is null");
        handle.setArgument("error", error);
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        return (1);
    }
    try {
        impl->finishConfigure(d2_config);
        impl->getIOService()->post([]() { impl->start(); });
    } catch (const std::exception& ex) {
        ostringstream os;
        os << "gss_tsig config mismatch: " << ex.what();
        string error(os.str());
        handle.setArgument("error", error);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (1);
    }
    return (0);
}

/// This function is called when the server selects a DNS server and
/// optionally a TSIG key.
///
/// An usable GSS-TSIG key for the DNS server is looked for:
///  - if GSS-TSIG is not enabled: just return with CONTINUE
///  - if a key was found: overwrite the selected key with it and
///    return with CONTINUE
///  - if no key was found but GSS-TSIG is enabled: return with SKIP
///    (i.e. implement this as GSS-TSIG is required)
///
/// @param handle CalloutHandle.
/// @return always 0.
int select_key(CalloutHandle& handle) {
    // First check the status.
    if (handle.getStatus() != CalloutHandle::NEXT_STEP_CONTINUE) {
        return (0);
    }
    // Get the parameters.
    DnsServerInfoPtr server_info;
    handle.getArgument("current_server", server_info);
    D2TsigKeyPtr tsig_key;
    handle.getArgument("tsig_key", tsig_key);
    // Get the DNS server.
    D2TsigKeyPtr key;
    bool useGssTsig = false;
    bool fallback = false;
    if (server_info) {
        key = impl->findKey(server_info, useGssTsig, fallback);
    }
    if (useGssTsig) {
        if (key) {
            handle.setArgument("tsig_key", key);
        } else if (!fallback) {
            handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
        }
    }
    return (0);
}

/// @brief This function is called when a command was processed.
///
/// Adds an entry to status-get answer.
///
/// @param handle CalloutHandle.
/// @return always 0.
int command_processed(CalloutHandle& handle) {
    try {
        impl->commandProcessed(handle);
    } catch (const std::exception& ex) {
        LOG_ERROR(gss_tsig_logger, GSS_TSIG_COMMAND_PROCESSED_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

} // end extern "C"
