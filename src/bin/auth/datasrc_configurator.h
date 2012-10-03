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
    typedef boost::shared_ptr<List> ListPtr;
public:
    /// \brief Default constructor.
    DataSourceConfiguratorGeneric() {}

    /// \brief Reads new configuration and replaces the old one.
    ///
    /// It instructs the server to replace the lists with new ones as needed.
    /// You don't need to call it directly (but you could, though the benefit
    /// is unknown and it would be questionable at least). It is called
    /// automatically on normal updates.
    ///
    /// \param server The server for which the data sources are to be
    /// configured.
    /// \param config The configuration value to parse. It is in the form
    ///     as an update from the config manager.
    void reconfigure(Server& server,
                     const isc::data::ConstElementPtr& config)
    {
        // Lock the client lists, we're going to manipulate them.
        isc::util::thread::Mutex::Locker locker(server.getClientListMutex());
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
                activeVector(server.getClientListClasses());
            std::set<isc::dns::RRClass> active(activeVector.begin(),
                                               activeVector.end());
            // Go through the configuration and change everything.
            for (Map::const_iterator it(map.begin()); it != map.end(); ++it) {
                isc::dns::RRClass rrclass(it->first);
                active.erase(rrclass);
                ListPtr list(server.getClientList(rrclass));
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
                    server.setClientList(rrclass, list);
                }
            }
            // Remove the ones that are not in the configuration.
            for (std::set<isc::dns::RRClass>::iterator it(active.begin());
                 it != active.end(); ++it) {
                // There seems to be no way the setClientList could throw.
                // But this is just to make sure in case it did to restore
                // the original.
                rollback_sets.push_back(
                    RollbackPair(*it, server.getClientList(*it)));
                server.setClientList(*it, ListPtr());
            }
        } catch (...) {
            // Perform a rollback of the changes. The old configuration should
            // work.
            for (typename std::vector<RollbackPair>::const_iterator
                 it(rollback_sets.begin()); it != rollback_sets.end(); ++it) {
                server.setClientList(it->first, it->second);
            }
            for (typename std::vector<RollbackConfiguration>::const_iterator
                 it(rollback_configurations.begin());
                 it != rollback_configurations.end(); ++it) {
                server.getClientList(it->first)->configure(it->second, true);
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
