// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
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


#include <datasrc/client_list.h>
#include <datasrc/exceptions.h>
#include <datasrc/client.h>
#include <datasrc/factory.h>
#include <datasrc/cache_config.h>
#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/logger.h>
#include <datasrc/zone_table_accessor_cache.h>
#include <dns/masterload.h>
#include <util/memory_segment_local.h>

#include <memory>
#include <set>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

using namespace isc::data;
using namespace isc::dns;
using namespace std;
using isc::util::MemorySegment;
using boost::lexical_cast;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;
using isc::datasrc::memory::InMemoryClient;
using isc::datasrc::memory::ZoneTableSegment;
using isc::datasrc::memory::ZoneDataUpdater;

namespace isc {
namespace datasrc {

ConfigurableClientList::DataSourceInfo::DataSourceInfo(
    DataSourceClient* data_src_client,
    const DataSourceClientContainerPtr& container,
    boost::shared_ptr<internal::CacheConfig> cache_conf,
    const RRClass& rrclass, const string& name) :
    data_src_client_(data_src_client),
    container_(container),
    name_(name),
    cache_conf_(cache_conf)
{
    if (cache_conf_ && cache_conf_->isEnabled()) {
        ztable_segment_.reset(ZoneTableSegment::create(
                                  rrclass, cache_conf_->getSegmentType()));
        cache_.reset(new InMemoryClient(ztable_segment_, rrclass));
    }
}

const DataSourceClient*
ConfigurableClientList::DataSourceInfo::getCacheClient() const {
    return (cache_.get());
}

ConfigurableClientList::ConfigurableClientList(const RRClass& rrclass) :
    rrclass_(rrclass),
    configuration_(new isc::data::ListElement),
    allow_cache_(false)
{}

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
        set<string> used_names;
        for (; i < config->size(); ++i) {
            // Extract the parameters
            const ConstElementPtr dconf(config->get(i));
            const ConstElementPtr type_elem(dconf->get("type"));
            if (type_elem == ConstElementPtr()) {
                isc_throw(ConfigurationError, "Missing the type option in "
                          "data source no " << i);
            }
            const string type(type_elem->stringValue());
            ConstElementPtr param_conf(dconf->get("params"));
            if (param_conf == ConstElementPtr()) {
                param_conf.reset(new NullElement());
            }
            // Get the name (either explicit, or guess)
            const ConstElementPtr name_elem(dconf->get("name"));
            const string datasrc_name =
                name_elem ? name_elem->stringValue() : type;
            if (!used_names.insert(datasrc_name).second) {
                isc_throw(ConfigurationError, "Duplicate name in client list: "
                          << datasrc_name);
            }

            DataSourcePair dsrc_pair;
            try {
                // Create a client for the underling data source via
                // factory.  If it's our internal type of data source,
                // this is essentially no-op.  In the latter case, it's
                // of no use unless cache is allowed; we simply skip
                // building it in that case.
                dsrc_pair = getDataSourceClient(type, param_conf);
            } catch (const DataSourceLibraryError& ex) {
                LOG_WARN(logger, DATASRC_LIBRARY_FAILURE).
                    arg(datasrc_name).arg(rrclass_).arg(ex.what());
                continue;
            }

            if (!allow_cache && !dsrc_pair.first) {
                LOG_WARN(logger, DATASRC_LIST_NOT_CACHED).
                    arg(datasrc_name).arg(rrclass_);
                continue;
            }

            // Build in-memory cache configuration, and create a set of
            // related objects including the in-memory zone table for the
            // cache.
            boost::shared_ptr<internal::CacheConfig> cache_conf(
                new internal::CacheConfig(type, dsrc_pair.first, *dconf,
                                          allow_cache));
            new_data_sources.push_back(DataSourceInfo(dsrc_pair.first,
                                                      dsrc_pair.second,
                                                      cache_conf, rrclass_,
                                                      datasrc_name));

            // If cache is disabled, or the zone table segment is not (yet)
            // writable,  we are done for this data source.
            // Otherwise load zones into the in-memory cache.
            if (!cache_conf->isEnabled()) {
                continue;
            }
            memory::ZoneTableSegment& zt_segment =
                *new_data_sources.back().ztable_segment_;
            if (!zt_segment.isWritable()) {
                LOG_DEBUG(logger, DBGLVL_TRACE_BASIC,
                          DATASRC_LIST_CACHE_PENDING).arg(datasrc_name);
                continue;
            }

            internal::CacheConfig::ConstZoneIterator end_of_zones =
                cache_conf->end();
            for (internal::CacheConfig::ConstZoneIterator zone_it =
                     cache_conf->begin();
                 zone_it != end_of_zones;
                 ++zone_it)
            {
                const Name& zname = zone_it->first;
                try {
                    const memory::LoadAction load_action =
                        cache_conf->getLoadAction(rrclass_, zname);
                    // in this loop this should be always true
                    assert(load_action);
                    // For the initial load, we'll let the writer handle
                    // loading error and install an empty zone in the table.
                    memory::ZoneWriter writer(zt_segment, load_action, zname,
                                              rrclass_, true);

                    std::string error_msg;
                    writer.load(&error_msg);
                    if (!error_msg.empty()) {
                        LOG_ERROR(logger, DATASRC_LOAD_ZONE_ERROR).arg(zname).
                            arg(rrclass_).arg(datasrc_name).arg(error_msg);
                    }
                    writer.install();
                    writer.cleanup();
                } catch (const NoSuchZone&) {
                    LOG_ERROR(logger, DATASRC_CACHE_ZONE_NOTFOUND).
                        arg(zname).arg(rrclass_).arg(datasrc_name);
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
    } catch (const internal::CacheConfigError& ex) {
        // convert to the "public" exception type.
        isc_throw(ConfigurationError, ex.what());
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

void
ConfigurableClientList::resetMemorySegment
    (const std::string& datasrc_name,
     ZoneTableSegment::MemorySegmentOpenMode mode,
     ConstElementPtr config_params)
{
    BOOST_FOREACH(DataSourceInfo& info, data_sources_) {
        if (info.name_ == datasrc_name) {
            ZoneTableSegment& segment = *info.ztable_segment_;
            segment.reset(mode, config_params);
            break;
        }
    }
}

ConfigurableClientList::ZoneWriterPair
ConfigurableClientList::getCachedZoneWriter(const Name& name,
                                            const std::string& datasrc_name)
{
    if (!allow_cache_) {
        return (ZoneWriterPair(CACHE_DISABLED, ZoneWriterPtr()));
    }

    // Find the data source from which the zone to be loaded into memory.
    // Then get the appropriate load action and create a zone writer.
    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        if (!datasrc_name.empty() && datasrc_name != info.name_) {
            continue;
        }
        // If there's an underlying "real" data source and it doesn't contain
        // the given name, obviously we cannot load it.  If a specific data
        // source is given by the name, search should stop here.
        if (info.data_src_client_ &&
            info.data_src_client_->findZone(name).code != result::SUCCESS) {
            if (!datasrc_name.empty()) {
                return (ZoneWriterPair(ZONE_NOT_FOUND, ZoneWriterPtr()));
            }
            continue;
        }
        // If the corresponding zone table segment is not (yet) writable,
        // we cannot load at this time.
        if (info.ztable_segment_ && !info.ztable_segment_->isWritable()) {
            return (ZoneWriterPair(CACHE_NOT_WRITABLE, ZoneWriterPtr()));
        }
        // Note that getCacheConfig() must return non NULL in this module
        // (only tests could set it to a bogus value).
        const memory::LoadAction load_action =
            info.getCacheConfig()->getLoadAction(rrclass_, name);
        if (!load_action) {
            return (ZoneWriterPair(ZONE_NOT_CACHED, ZoneWriterPtr()));
        }
        return (ZoneWriterPair(ZONE_SUCCESS,
                               ZoneWriterPtr(
                                   new memory::ZoneWriter(
                                       *info.ztable_segment_,
                                       load_action, name, rrclass_, false))));
    }

    // We can't find the specified zone.  If a specific data source was
    // given, this means the given name of data source doesn't exist, so
    // we report it so.
    if (!datasrc_name.empty()) {
        return (ZoneWriterPair(DATASRC_NOT_FOUND, ZoneWriterPtr()));
    }
    return (ZoneWriterPair(ZONE_NOT_FOUND, ZoneWriterPtr()));
}

// NOTE: This function is not tested, it would be complicated. However, the
// purpose of the function is to provide a very thin wrapper to be able to
// replace the call to DataSourceClientContainer constructor in tests.
ConfigurableClientList::DataSourcePair
ConfigurableClientList::getDataSourceClient(const string& type,
                                            const ConstElementPtr&
                                            configuration)
{
    if (type == "MasterFiles") {
        return (DataSourcePair(0, DataSourceClientContainerPtr()));
    }

    DataSourceClientContainerPtr
        container(new DataSourceClientContainer(type, configuration));
    return (DataSourcePair(&container->getInstance(), container));
}

vector<DataSourceStatus>
ConfigurableClientList::getStatus() const {
    vector<DataSourceStatus> result;
    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        if (info.ztable_segment_) {
            result.push_back(DataSourceStatus(
                info.name_,
                (info.ztable_segment_->isUsable() ?
                 SEGMENT_INUSE : SEGMENT_WAITING),
                info.ztable_segment_->getImplType()));
        } else {
            result.push_back(DataSourceStatus(info.name_));
        }
    }
    return (result);
}

ConstZoneTableAccessorPtr
ConfigurableClientList::getZoneTableAccessor(const std::string& datasrc_name,
                                             bool use_cache) const
{
    if (!use_cache) {
        isc_throw(isc::NotImplemented,
              "getZoneTableAccessor only implemented for cache");
    }

    // Find the matching data source
    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        if (!datasrc_name.empty() && datasrc_name != info.name_) {
            continue;
        }

        const internal::CacheConfig* config(info.getCacheConfig());
        // If caching is disabled for the named data source, this will
        // return an accessor to an effectivley empty table.
        return (ConstZoneTableAccessorPtr
                (new internal::ZoneTableAccessorCache(*config)));
    }

    return (ConstZoneTableAccessorPtr());
}

}
}
