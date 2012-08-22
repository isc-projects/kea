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

#include "client_list.h"
#include "client.h"
#include "factory.h"
#include "memory_datasrc.h"
#include "logger.h"
#include <dns/masterload.h>

#include <memory>
#include <boost/foreach.hpp>

using namespace isc::data;
using namespace isc::dns;
using namespace std;
using boost::lexical_cast;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;

namespace isc {
namespace datasrc {

ConfigurableClientList::DataSourceInfo::DataSourceInfo(
    DataSourceClient* data_src_client,
    const DataSourceClientContainerPtr& container, bool has_cache) :
    data_src_client_(data_src_client),
    container_(container)
{
    if (has_cache) {
        cache_.reset(new InMemoryClient);
    }
}

ConfigurableClientList::DataSourceInfo::DataSourceInfo(bool has_cache) :
    data_src_client_(NULL)
{
    if (has_cache) {
        cache_.reset(new InMemoryClient);
    }
}

void
ConfigurableClientList::configure(const ConstElementPtr& config,
                                  bool allow_cache)
{
    if (!config) {
        isc_throw(isc::BadValue, "NULL configuration passed");
    }
    // TODO: Implement recycling from the old configuration.
    size_t i(0); // Outside of the try to be able to access it in the catch
    try {
        vector<DataSourceInfo> new_data_sources;
        for (; i < config->size(); ++i) {
            // Extract the parameters
            const ConstElementPtr dconf(config->get(i));
            const ConstElementPtr typeElem(dconf->get("type"));
            if (typeElem == ConstElementPtr()) {
                isc_throw(ConfigurationError, "Missing the type option in "
                          "data source no " << i);
            }
            const string type(typeElem->stringValue());
            ConstElementPtr paramConf(dconf->get("params"));
            if (paramConf == ConstElementPtr()) {
                paramConf.reset(new NullElement());
            }
            const bool want_cache(allow_cache &&
                                  dconf->contains("cache-enable") &&
                                  dconf->get("cache-enable")->boolValue());

            if (type == "MasterFiles") {
                // In case the cache is not allowed, we just skip the master
                // files (at least for now)
                if (!allow_cache) {
                    // We're not going to load these zones. Issue warnings about it.
                    const map<string, ConstElementPtr>
                        zones_files(paramConf->mapValue());
                    for (map<string, ConstElementPtr>::const_iterator
                         it(zones_files.begin()); it != zones_files.end();
                         ++it) {
                        LOG_WARN(logger, DATASRC_LIST_NOT_CACHED).
                            arg(it->first).arg(rrclass_);
                    }
                    continue;
                }
                if (!want_cache) {
                    isc_throw(ConfigurationError, "The cache must be enabled "
                              "for the MasterFiles type");
                }
                new_data_sources.push_back(DataSourceInfo(true));
            } else {
                // Ask the factory to create the data source for us
                const DataSourcePair ds(this->getDataSourceClient(type,
                                                                  paramConf));
                // And put it into the vector
                new_data_sources.push_back(DataSourceInfo(ds.first, ds.second,
                                                          want_cache));
            }

            if (want_cache) {
                if (!dconf->contains("cache-zones") && type != "MasterFiles") {
                    isc_throw(isc::NotImplemented, "Auto-detection of zones "
                              "to cache is not yet implemented, supply "
                              "cache-zones parameter");
                    // TODO: Auto-detect list of all zones in the
                    // data source.
                }

                // List the zones we are loading
                vector<string> zones_origins;
                if (type == "MasterFiles") {
                    const map<string, ConstElementPtr>
                        zones_files(paramConf->mapValue());
                    for (map<string, ConstElementPtr>::const_iterator
                         it(zones_files.begin()); it != zones_files.end();
                         ++it) {
                        zones_origins.push_back(it->first);
                    }
                } else {
                    const ConstElementPtr zones(dconf->get("cache-zones"));
                    for (size_t i(0); i < zones->size(); ++i) {
                        zones_origins.push_back(zones->get(i)->stringValue());
                    }
                }

                const shared_ptr<InMemoryClient>
                    cache(new_data_sources.back().cache_);
                const DataSourceClient* const
                    client(new_data_sources.back().data_src_client_);
                for (vector<string>::const_iterator it(zones_origins.begin());
                     it != zones_origins.end(); ++it) {
                    try {
                        const Name origin(*it);
                        shared_ptr<InMemoryZoneFinder>
                            finder(new
                                InMemoryZoneFinder(rrclass_, origin));
                        if (type == "MasterFiles") {
                            finder->load(paramConf->get(*it)->stringValue());
                        } else {
                            ZoneIteratorPtr iterator;
                            try {
                                iterator = client->getIterator(origin);
                            }
                            catch (const DataSourceError&) {
                                isc_throw(ConfigurationError, "Unable to "
                                          "cache non-existent zone "
                                          << origin);
                            }
                            if (!iterator) {
                                isc_throw(isc::Unexpected, "Got NULL iterator "
                                          "for zone " << origin);
                            }
                            finder->load(*iterator);
                        }
                        cache->addZone(finder);
                    } catch (const isc::dns::MasterLoadError& mle) {
                        LOG_ERROR(logger, DATASRC_MASTERLOAD_ERROR)
                            .arg(mle.what());
                    }
                }
            }
        }
        // If everything is OK up until now, we have the new configuration
        // ready. So just put it there and let the old one die when we exit
        // the scope.
        data_sources_.swap(new_data_sources);
        configuration_ = config;
        allow_cache_ = allow_cache;
    } catch (const TypeError& te) {
        isc_throw(ConfigurationError, "Malformed configuration at data source "
                  "no. " << i << ": " << te.what());
    }
}

namespace {

class CacheKeeper : public ClientList::FindResult::LifeKeeper {
public:
    CacheKeeper(const boost::shared_ptr<InMemoryClient>& cache) :
        cache_(cache)
    {}
private:
    const boost::shared_ptr<InMemoryClient> cache_;
};

class ContainerKeeper : public ClientList::FindResult::LifeKeeper {
public:
    ContainerKeeper(const DataSourceClientContainerPtr& container) :
        container_(container)
    {}
private:
    const DataSourceClientContainerPtr container_;
};

boost::shared_ptr<ClientList::FindResult::LifeKeeper>
genKeeper(const ConfigurableClientList::DataSourceInfo* info) {
    if (info == NULL) {
        return (boost::shared_ptr<ClientList::FindResult::LifeKeeper>());
    }
    if (info->cache_) {
        return (boost::shared_ptr<ClientList::FindResult::LifeKeeper>(
            new CacheKeeper(info->cache_)));
    } else {
        return (boost::shared_ptr<ClientList::FindResult::LifeKeeper>(
            new ContainerKeeper(info->container_)));
    }
}

}

// We have this class as a temporary storage, as the FindResult can't be
// assigned.
struct ConfigurableClientList::MutableResult {
    MutableResult() :
        datasrc_client(NULL),
        matched_labels(0),
        matched(false),
        exact(false),
        info(NULL)
    {}
    DataSourceClient* datasrc_client;
    ZoneFinderPtr finder;
    uint8_t matched_labels;
    bool matched;
    bool exact;
    const DataSourceInfo* info;
    operator FindResult() const {
        // Conversion to the right result.
        return (FindResult(datasrc_client, finder, exact, genKeeper(info)));
    }
};

ClientList::FindResult
ConfigurableClientList::find(const dns::Name& name, bool want_exact_match,
                             bool want_finder) const
{
    MutableResult result;
    findInternal(result, name, want_exact_match, want_finder);
    return (result);
}

void
ConfigurableClientList::findInternal(MutableResult& candidate,
                                     const dns::Name& name,
                                     bool want_exact_match, bool) const
{
    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        DataSourceClient* client(info.cache_ ? info.cache_.get() :
                                 info.data_src_client_);
        const DataSourceClient::FindResult result(client->findZone(name));
        // TODO: Once we mark the zones that are not loaded, but are present
        // in the data source somehow, check them too.
        switch (result.code) {
            case result::SUCCESS:
                // If we found an exact match, we have no hope to getting
                // a better one. Stop right here.

                // TODO: In case we have only the datasource and not the finder
                // and the need_updater parameter is true, get the zone there.
                candidate.datasrc_client = client;
                candidate.finder = result.zone_finder;
                candidate.matched = true;
                candidate.exact = true;
                candidate.info = &info;
                return;
            case result::PARTIALMATCH:
                if (!want_exact_match) {
                    // In case we have a partial match, check if it is better
                    // than what we have. If so, replace it.
                    //
                    // We don't need the labels at the first partial match,
                    // we have nothing to compare with. So we don't get it
                    // (as a performance) and hope we will not need it at all.
                    const uint8_t labels(candidate.matched ?
                        result.zone_finder->getOrigin().getLabelCount() : 0);
                    if (candidate.matched && candidate.matched_labels == 0) {
                        // But if the hope turns out to be false, we need to
                        // compute it for the first match anyway.
                        candidate.matched_labels = candidate.finder->
                            getOrigin().getLabelCount();
                    }
                    if (labels > candidate.matched_labels ||
                        !candidate.matched) {
                        // This one is strictly better. Replace it.
                        candidate.datasrc_client = client;
                        candidate.finder = result.zone_finder;
                        candidate.matched_labels = labels;
                        candidate.matched = true;
                        candidate.info = &info;
                    }
                }
                break;
            default:
                // Nothing found, nothing to do.
                break;
        }
    }

    // TODO: In case we have only the datasource and not the finder
    // and the need_updater parameter is true, get the zone there.
}

ConfigurableClientList::ReloadResult
ConfigurableClientList::reload(const Name& name) {
    if (!allow_cache_) {
        return (CACHE_DISABLED);
    }
    // Try to find the correct zone.
    MutableResult result;
    findInternal(result, name, true, true);
    if (!result.finder) {
        return (ZONE_NOT_FOUND);
    }
    // Try to convert the finder to in-memory one. If it is the cache,
    // it should work.
    shared_ptr<InMemoryZoneFinder>
        finder(dynamic_pointer_cast<InMemoryZoneFinder>(result.finder));
    const DataSourceInfo* info(result.info);
    // It is of a different type or there's no cache.
    if (!info->cache_ || !finder) {
        return (ZONE_NOT_CACHED);
    }
    DataSourceClient* client(info->data_src_client_);
    if (client) {
        // Now do the final reload. If it does not exist in client,
        // DataSourceError is thrown, which is exactly the result what we
        // want, so no need to handle it.
        ZoneIteratorPtr iterator(client->getIterator(name));
        if (!iterator) {
            isc_throw(isc::Unexpected, "Null iterator from " << name);
        }
        finder->load(*iterator);
    } else {
        // The MasterFiles special case
        const string filename(finder->getFileName());
        if (filename.empty()) {
            isc_throw(isc::Unexpected, "Confused about missing both filename "
                      "and data source");
        }
        finder->load(filename);
    }
    return (ZONE_RELOADED);
}

// NOTE: This function is not tested, it would be complicated. However, the
// purpose of the function is to provide a very thin wrapper to be able to
// replace the call to DataSourceClientContainer constructor in tests.
ConfigurableClientList::DataSourcePair
ConfigurableClientList::getDataSourceClient(const string& type,
                                            const ConstElementPtr&
                                            configuration)
{
    DataSourceClientContainerPtr
        container(new DataSourceClientContainer(type, configuration));
    return (DataSourcePair(&container->getInstance(), container));
}

}
}
