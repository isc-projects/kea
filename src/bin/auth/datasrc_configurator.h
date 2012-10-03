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
#include <cc/data.h>
#include <util/threads/lock.h>

#include <set>

/// \brief A class to configure the authoritative server's data source lists
///
/// This will hook into the data_sources module configuration and it will
/// keep the local copy of data source clients in the list in the authoritative
/// server.
///
/// Also, the class is a template. This is simply because of easier testing.
/// You don't need to pay attention to it, use the DataSourceConfigurator
/// type alias instead.
template<class Server, class List>
class DataSourceConfiguratorGeneric {
private:
    Server* server_;
    typedef boost::shared_ptr<List> ListPtr;
public:
    /// \brief Constructor.
    ///
    /// \throw isc::InvalidParameter if server is NULL
    /// \param server The server to configure.
    DataSourceConfiguratorGeneric(Server* server) : server_(server) {
        if (server == NULL) {
            isc_throw(isc::InvalidParameter, "The server must not be NULL");
        }
    }

    /// \brief Initializes the class.
    ///
    /// This configures which session and server should be used.
    /// It hooks to the session now and downloads the configuration.
    /// It is synchronous (it may block for some time).
    ///
    /// Note that you need to call cleanup before the server or
    /// session dies, otherwise it might access them after they
    /// are destroyed.
    ///
    /// \param server It is the server to configure.
    /// \throw isc::InvalidOperation if this is called when already
    /// initialized.
    /// \throw isc::InvalidParameter if any of the parameters is NULL
    /// \throw isc::config::ModuleCCError if the remote configuration is not
    ///     available for some reason.
    void init() {
    }

    /// \brief Deinitializes the class.
    ///
    /// This detaches from the session and removes the server from internal
    /// storage. The current configuration in the server is preserved.
    ///
    /// This can be called even if it is not initialized currently. You
    /// can initialize it again after this.
    void cleanup() {
        server_ = NULL;
    }

    /// \brief Reads new configuration and replaces the old one.
    ///
    /// It instructs the server to replace the lists with new ones as needed.
    /// You don't need to call it directly (but you could, though the benefit
    /// is unknown and it would be questionable at least). It is called
    /// automatically on normal updates.
    ///
    /// \param config The configuration value to parse. It is in the form
    ///     as an update from the config manager.
    /// \throw InvalidOperation if it is called when not initialized.
    void reconfigure(const isc::data::ConstElementPtr& config) {
        if (server_ == NULL) {
            isc_throw(isc::InvalidOperation,
                      "Can't reconfigure while not initialized by init()");
        }
        // Lock the client lists, we're going to manipulate them.
        isc::util::thread::Mutex::Locker locker(server_->getClientListMutex());
        typedef std::map<std::string, isc::data::ConstElementPtr> Map;
        typedef std::pair<isc::dns::RRClass, ListPtr> RollbackPair;
        typedef std::pair<isc::dns::RRClass, isc::data::ConstElementPtr>
            RollbackConfiguration;
        // Some structures to be able to perform a rollback
        std::vector<RollbackPair> rollback_sets;
        std::vector<RollbackConfiguration> rollback_configurations;
        try {
            // Get the configuration and current state.
            const Map& map(config->mapValue());
            const std::vector<isc::dns::RRClass>
                activeVector(server_->getClientListClasses());
            std::set<isc::dns::RRClass> active(activeVector.begin(),
                                               activeVector.end());
            // Go through the configuration and change everything.
            for (Map::const_iterator it(map.begin()); it != map.end(); ++it) {
                isc::dns::RRClass rrclass(it->first);
                active.erase(rrclass);
                ListPtr list(server_->getClientList(rrclass));
                bool need_set(false);
                if (list) {
                    rollback_configurations.
                        push_back(RollbackConfiguration(rrclass,
                            list->getConfiguration()));
                } else {
                    list.reset(new List(rrclass));
                    need_set = true;
                    rollback_sets.push_back(RollbackPair(rrclass, ListPtr()));
                }
                list->configure(it->second, true);
                if (need_set) {
                    server_->setClientList(rrclass, list);
                }
            }
            // Remove the ones that are not in the configuration.
            for (std::set<isc::dns::RRClass>::iterator it(active.begin());
                 it != active.end(); ++it) {
                // There seems to be no way the setClientList could throw.
                // But this is just to make sure in case it did to restore
                // the original.
                rollback_sets.push_back(
                    RollbackPair(*it, server_->getClientList(*it)));
                server_->setClientList(*it, ListPtr());
            }
        } catch (...) {
            // Perform a rollback of the changes. The old configuration should
            // work.
            for (typename std::vector<RollbackPair>::const_iterator
                 it(rollback_sets.begin()); it != rollback_sets.end(); ++it) {
                server_->setClientList(it->first, it->second);
            }
            for (typename std::vector<RollbackConfiguration>::const_iterator
                 it(rollback_configurations.begin());
                 it != rollback_configurations.end(); ++it) {
                server_->getClientList(it->first)->configure(it->second, true);
            }
            throw;
        }
    }
};

/// \brief Concrete version of DataSourceConfiguratorGeneric for the
///     use in authoritative server.
typedef DataSourceConfiguratorGeneric<AuthSrv,
        isc::datasrc::ConfigurableClientList>
    DataSourceConfigurator;

#endif

// Local Variables:
// mode: c++
// End:
