// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_CONFIGURATOR_H
#define DATASRC_CONFIGURATOR_H

#include "auth_srv.h"

#include <datasrc/client_list.h>
#include <config/ccsession.h>

/// \brief A class to configure the authoritative server's data source lists
///
/// This will hook into the data_sources module configuration and it will
/// keep the local copy of data source clients in the list in the authoritative
/// server.
///
/// The class is slightly unusual. Due to some technical limitations, the hook
/// needs to be static method. Therefore it is not possible to create instances
/// of the class.
///
/// Also, the class is a template. This is simply because of easier testing.
/// You don't need to pay attention to it, use the DataSourceConfigurator
/// type alias instead.
template<class Server, class List>
class DataSourceConfiguratorGeneric {
private:
    /// \brief Disallow creation of instances
    DataSourceConfiguratorGeneric();
    /// \brief Internal method to hook into the ModuleCCSession
    ///
    /// It simply calls reconfigure.
    static void reconfigureInternal(const std::string&,
                                    isc::data::ConstElementPtr config,
                                    const isc::config::ConfigData&)
    {
        reconfigure(config);
    }
    static Server* server_;
    static isc::config::ModuleCCSession* session_;
public:
    /// \brief Initializes the class.
    ///
    /// This configures which session and server should be used.
    /// It hooks to the session now and downloads the configuration.
    /// It is synchronous (it may block for some time).
    ///
    /// Note that you need to call deinit before the server or
    /// session dies, otherwise it might access them after they
    /// are destroyed.
    ///
    /// \param session The session to hook into and to access the configuration
    ///     through.
    /// \param server It is the server to configure.
    /// \throw isc::InvalidOperation if this is called when already initialized.
    /// \throw isc::InvalidParameter if any of the parameters is NULL
    /// \throw isc::config::ModuleCCError if the remote configuration is not
    ///     available for some reason.
    static void init(isc::config::ModuleCCSession *session,
                     Server *server)
    {
        if (session == NULL) {
            isc_throw(isc::InvalidParameter, "The session must not be NULL");
        }
        if (server == NULL) {
            isc_throw(isc::InvalidParameter, "The server must not be NULL");
        }
        if (server_ != NULL) {
            isc_throw(isc::InvalidOperation,
                      "The configurator is already initialized");
        }
        server_ = server;
        session_ = session;
        session->addRemoteConfig("data_sources", reconfigureInternal, false);
    }
    /// \brief Deinitializes the class.
    ///
    /// This detaches from the session and removes the server from internal
    /// storage. The current configuration in the server is preserved.
    ///
    /// This can be called even if it is not initialized currently. You
    /// can initialize it again after this.
    static void deinit() {
        if (session_ != NULL) {
            session_->removeRemoteConfig("data_sources");
        }
        session_ = NULL;
        server_ = NULL;
    }
    /// \brief Reads new configuration and replaces the old one.
    ///
    /// It instructs the server to replace the lists with new ones as needed.
    /// You don't need to call it directly (but you could, though the benefit
    /// is unkown and it would be questionable at least). It is called
    /// automatically on normal updates.
    ///
    /// \param config The configuration value to parse. It is in the form
    ///     as an update from the config manager.
    /// \throw InvalidOperation if it is called when not initialized.
    static void reconfigure(const isc::data::ConstElementPtr& ) {

    }
};

template<class Server, class List>
isc::config::ModuleCCSession*
DataSourceConfiguratorGeneric<Server, List>::session_(NULL);

template<class Server, class List>
Server* DataSourceConfiguratorGeneric<Server, List>::server_(NULL);

/// \brief Concrete version of DataSourceConfiguratorGeneric for the
///     use in authoritative server.
typedef DataSourceConfiguratorGeneric<AuthSrv,
        isc::datasrc::ConfigurableClientList>
    DataSourceConfigurator;

#endif
