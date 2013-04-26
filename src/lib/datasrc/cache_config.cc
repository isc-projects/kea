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

#include <datasrc/cache_config.h>
#include <datasrc/client.h>
#include <datasrc/memory/load_action.h>
#include <datasrc/memory/zone_data_loader.h>

#include <util/memory_segment.h>

#include <dns/name.h>
#include <dns/rrclass.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <boost/bind.hpp>

#include <cassert>
#include <map>
#include <string>

using namespace isc::data;

namespace isc {
namespace datasrc {
namespace internal {

namespace {
bool
getEnabledFromConf(const Element& conf) {
    return (conf.contains("cache-enable") &&
            conf.get("cache-enable")->boolValue());
}

std::string
getSegmentTypeFromConf(const Element& conf) {
    // If cache-type is not explicitly configured, use the default type.
    // (Ideally we should retrieve the default from the spec).
    if (!conf.contains("cache-type")) {
        return ("local");
    }
    return (conf.get("cache-type")->stringValue());
}
}

CacheConfig::CacheConfig(const std::string& datasrc_type,
                         const DataSourceClient* datasrc_client,
                         const Element& datasrc_conf,
                         bool allowed) :
    enabled_(allowed && getEnabledFromConf(datasrc_conf)),
    segment_type_(getSegmentTypeFromConf(datasrc_conf)),
    datasrc_client_(datasrc_client)
{
    ConstElementPtr params = datasrc_conf.get("params");
    if (!params) {
        params.reset(new NullElement());
    }
    if (datasrc_type == "MasterFiles") {
        if (datasrc_client_) {
            isc_throw(InvalidParameter,
                      "data source client is given for MasterFiles");
        }

        if (!enabled_) {
            isc_throw(CacheConfigError,
                      "The cache must be enabled for the MasterFiles type");
        }

        typedef std::map<std::string, ConstElementPtr> ZoneToFile;
        const ZoneToFile& zone_to_file = params->mapValue();
        ZoneToFile::const_iterator const it_end = zone_to_file.end();
        for (ZoneToFile::const_iterator it = zone_to_file.begin();
             it != it_end;
             ++it)
        {
            zone_config_[dns::Name(it->first)] = it->second->stringValue();
        }
    } else {
        if (!datasrc_client_) {
            isc_throw(InvalidParameter,
                      "data source client is missing for data source type: "
                      << datasrc_type);
        }
        if (!enabled_) {
            return;
        }

        if (!datasrc_conf.contains("cache-zones")) {
            isc_throw(NotImplemented, "Auto-detection of zones "
                      "to cache is not yet implemented, supply "
                      "cache-zones parameter");
            // TODO: Auto-detect list of all zones in the
            // data source.
        }

        const ConstElementPtr zones = datasrc_conf.get("cache-zones");
        for (size_t i = 0; i < zones->size(); ++i) {
            const dns::Name zone_name(zones->get(i)->stringValue());
            if (!zone_config_.insert(Zones::value_type(zone_name,
                                                       "")).second) {
                isc_throw(CacheConfigError, "Duplicate cache zone: " <<
                          zone_name);
            }
        }
    }
}

namespace {

// We would like to use boost::bind for this. However, the loadZoneData takes
// a reference, while we have a shared pointer to the iterator -- and we need
// to keep it alive as long as the ZoneWriter is alive. Therefore we can't
// really just dereference it and pass it, since it would get destroyed once
// the getCachedZoneWriter would end. This class holds the shared pointer
// alive, otherwise is mostly simple.
//
// It might be doable with nested boost::bind, but it would probably look
// more awkward and complicated than this.
class IteratorLoader {
public:
    IteratorLoader(const dns::RRClass& rrclass, const dns::Name& name,
                   const ZoneIteratorPtr& iterator) :
        rrclass_(rrclass),
        name_(name),
        iterator_(iterator)
    {}
    memory::ZoneData* operator()(util::MemorySegment& segment) {
        return (memory::loadZoneData(segment, rrclass_, name_, *iterator_));
    }
private:
    const dns::RRClass rrclass_;
    const dns::Name name_;
    ZoneIteratorPtr iterator_;
};

// We can't use the loadZoneData function directly in boost::bind, since
// it is overloaded and the compiler can't choose the correct version
// reliably and fails. So we simply wrap it into an unique name.
memory::ZoneData*
loadZoneDataFromFile(util::MemorySegment& segment, const dns::RRClass& rrclass,
                     const dns::Name& name, const std::string& filename)
{
    return (memory::loadZoneData(segment, rrclass, name, filename));
}

} // unnamed namespace

memory::LoadAction
CacheConfig::getLoadAction(const dns::RRClass& rrclass,
                           const dns::Name& zone_name) const
{
    // First, check if the specified zone is configured to be cached.
    Zones::const_iterator found = zone_config_.find(zone_name);
    if (found == zone_config_.end()) {
        return (memory::LoadAction());
    }

    if (!found->second.empty()) {
        // This is "MasterFiles" data source.
        return (boost::bind(loadZoneDataFromFile, _1, rrclass, zone_name,
                            found->second));
    }

    // Otherwise there must be a "source" data source (ensured by constructor)
    assert(datasrc_client_);

    // If the specified zone name does not exist in our client of the source,
    // DataSourceError is thrown, which is exactly the result what we
    // want, so no need to handle it.
    ZoneIteratorPtr iterator(datasrc_client_->getIterator(zone_name));
    if (!iterator) {
        // This shouldn't happen for a compliant implementation of
        // DataSourceClient, but we'll protect ourselves from buggy
        // implementations.
        isc_throw(Unexpected, "getting LoadAction for " << zone_name
                  << "/" << rrclass << " resulted in Null zone iterator");
    }

    // Wrap the iterator into the correct functor (which keeps it alive as
    // long as it is needed).
    return (IteratorLoader(rrclass, zone_name, iterator));
}

} // namespace internal
} // namespace datasrc
} // namespace isc
