// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GSS_TSIG_IMPL_H
#define GSS_TSIG_IMPL_H

#include <asiolink/interval_timer.h>
#include <gss_tsig_cfg.h>
#include <hooks/hooks.h>
#include <managed_key.h>

#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <chrono>
#include <memory>

namespace isc {
namespace gss_tsig {

/// @brief Tag for the name index for searching GSS-TSIG key.
struct GssTsigKeyNameTag { };

/// @brief Tag for the server ID index for searching GSS-TSIG key.
struct GssTsigKeyServerTag { };

/// @brief A multi index container holding GSS-TSIG keys.
typedef boost::multi_index_container<
    // It holds pointers to GSS-TSIG key objects.
    ManagedKeyPtr,
    boost::multi_index::indexed_by<
        // First index is the by DNS name.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<GssTsigKeyNameTag>,
            boost::multi_index::const_mem_fun<ManagedKey, std::string,
                                              &ManagedKey::getKeyNameStr>
        >,

        // Second index is by DNS server (parent) ID with the inception
        // date to sort search results.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<GssTsigKeyServerTag>,
            boost::multi_index::composite_key<
                ManagedKey,
                // The DNS server (parent) ID.
                boost::multi_index::const_mem_fun<ManagedKey, std::string,
                                                  &ManagedKey::getParentID>,
                // The inception date.
                boost::multi_index::const_mem_fun<GssTsigKey,
                                                  std::chrono::system_clock::time_point,
                                                  &GssTsigKey::getInception>
                >
            >
    >
> ManagedKeyList;

/// @brief GSS-TSIG hook implementation.
///
/// @note: currently only the configuration part: the runtime part will be
/// added later.
class GssTsigImpl {
public:
    /// @brief Constructor.
    GssTsigImpl();

    /// @brief Destructor.
    virtual ~GssTsigImpl();

    /// @brief Configure.
    ///
    /// @param config A map element with parameters.
    /// @throw BadValue and similar exceptions on error.
    void configure(isc::data::ConstElementPtr config);

    /// @brief Finish configure.
    ///
    /// @param d2_config D2 server running configuration.
    void finishConfigure(isc::d2::D2CfgContextPtr d2_config);

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    void setIOService(isc::asiolink::IOServicePtr io_service) {
        io_service_ = io_service;
    }

    /// @brief Get the DNS server from its ID.
    ///
    /// @param id The server ID.
    /// @return the DNS server or null if not found.
    DnsServerPtr getServer(const std::string& id) const;

    /// @brief Start method.
    ///
    /// @note This method is called from the I/O context after
    /// the d2_srv_configured callout.
    void start();

    /// @brief Stop method.
    ///
    /// @note This method is called before unloading.
    void stop();

    /// @brief Process GSS-TSIG keys for all servers.
    ///
    /// @param rekey The flag which indicates if unconditionally rekey all
    /// servers.
    void processAllServersKeys(bool rekey = false);

    /// @brief Process GSS-TSIG keys for a specific server.
    ///
    /// @param server The server with keys to be processed.
    /// @param rekey The flag which indicates if unconditionally rekey server.
    void processServerKeys(DnsServerPtr server, bool rekey = false);

    /// @brief Create new GSS-TSIG key.
    ///
    /// @param server The server for which the new key is added.
    /// @param now The current timestamp.
    void createKey(DnsServerPtr server,
                   std::chrono::time_point<std::chrono::system_clock> now);

    /// @brief Find a GSS-TSIG key by server info.
    ///
    /// @param server_info Pointer to a DNS server.
    /// @param[out] useGssTsig Set to true when GSS-TSIG is used.
    /// @param[out] fallback Set to true when GSS-TSIG should be used and
    /// no key is available fallbacks to the no GSS-TSIG behavior (vs.
    /// skips this DNS server).
    /// @return an usable key or null if none was found.
    ManagedKeyPtr findKey(const d2::DnsServerInfoPtr& server_info,
                          bool& useGssTsig, bool& fallback);

    /// @brief Find a GSS-TSIG key by name.
    ///
    /// @param name Name of the key.
    /// @return the key with the name or null if none was found.
    ManagedKeyPtr findKey(const std::string& name) const;

    /// @brief Purge very old GSS-TSIG keys.
    ///
    /// Handler of the purge periodic timer.
    void purgeKeys();

    /// @brief The gss-tsig-get command handler.
    ///
    /// @param handle CalloutHandle.
    void getHandler(isc::hooks::CalloutHandle& handle) const;

    /// @brief The gss-tsig-get-all command handler.
    ///
    /// @param handle CalloutHandle.
    void getAllHandler(isc::hooks::CalloutHandle& handle) const;

    /// @brief The gss-tsig-list command handler.
    ///
    /// @param handle CalloutHandle.
    void listHandler(isc::hooks::CalloutHandle& handle) const;

    /// @brief The gss-tsig-key-get command handler.
    ///
    /// @param handle CalloutHandle.
    void keyGetHandler(isc::hooks::CalloutHandle& handle) const;

    /// @brief The gss-tsig-key-expire command handler.
    ///
    /// @param handle CalloutHandle.
    void keyExpireHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The gss-tsig-key-del command handler.
    ///
    /// @param handle CalloutHandle.
    void keyDelHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The gss-tsig-purge command handler.
    ///
    /// @param handle CalloutHandle.
    void purgeHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The gss-tsig-purge-all command handler.
    ///
    /// @param handle CalloutHandle.
    void purgeAllHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The gss-tsig-rekey command handler.
    ///
    /// @param handle CalloutHandle.
    void rekeyHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The gss-tsig-rekey-all command handler.
    ///
    /// @param handle CalloutHandle.
    void rekeyAllHandler(isc::hooks::CalloutHandle& handle);

    /// @brief The command_processed handler.
    ///
    /// @param handle CalloutHandle.
    void commandProcessed(isc::hooks::CalloutHandle& handle);

protected:
    /// @brief GSS-TSIG hook configuration.
    GssTsigCfg cfg_;

    /// @brief Map of GSS-TSIG keys by name.
    ManagedKeyList keys_;

    /// @brief The hook I/O service.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief The previous value of client key table environment variable.
    std::unique_ptr<std::string> krb5_client_ktname_prev_;

    /// @brief The previous value of credential cache environment variable.
    std::unique_ptr<std::string> krb5ccname_prev_;

    /// @brief The purge periodic timer.
    isc::asiolink::IntervalTimerPtr purge_timer_;
};

/// @brief Type of pointer to a GSS-TSIG hook configuration.
typedef std::unique_ptr<GssTsigImpl> GssTsigImplPtr;

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // GSS_TSIG_IMPL_H
