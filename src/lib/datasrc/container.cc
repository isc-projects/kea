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

#include "container.h"
#include "client.h"
#include "factory.h"

#include <memory>
#include <boost/foreach.hpp>

using namespace isc::data;
using namespace std;

namespace isc {
namespace datasrc {

void
ConfigurableContainer::configure(const ConstElementPtr& config, bool) {
    // TODO: Implement the cache
    // TODO: Implement recyclation from the old configuration.
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
            // TODO: Special-case the master files type.
            // Ask the factory to create the data source for us
            const DataSourcePair ds(this->getDataSource(type, paramConf));
            // And put it into the vector
            DataSourceInfo info;
            info.data_src_ = ds.first;
            info.container_ = ds.second;
            new_data_sources.push_back(info);
        }
        // If everything is OK up until now, we have the new configuration
        // ready. So just put it there and let the old one die when we exit
        // the scope.
        data_sources_.swap(new_data_sources);
    }
    catch (const TypeError& te) {
        isc_throw(ConfigurationError, "Malformed configuration at data source "
                  "no. " << i << ": " << te.what());
    }
}

Container::SearchResult
ConfigurableContainer::search(const dns::Name& name, bool want_exact_match,
                              bool ) const
{
    // Nothing found yet.
    // Pointer is used as the SearchResult can't be assigned.
    auto_ptr<SearchResult> candidate(new SearchResult());

    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        // TODO: Once we have support for the caches, consider them too here
        // somehow. This would probably get replaced by a function, that
        // checks if there's a cache available, if it is, checks the loaded
        // zones and zones expected to be in the real data source. If it is
        // the cached one, provide the cached one. If it is in the external
        // data source, use the datasource and don't provide the finder yet.
        DataSourceClient::FindResult result(info.data_src_->findZone(name));
        switch (result.code) {
            case result::SUCCESS: {
                // If we found an exact match, we have no hope to getting
                // a better one. Stop right here.

                // TODO: In case we have only the datasource and not the finder
                // and the need_updater parameter is true, get the zone there.
                return (SearchResult(info.data_src_, result.zone_finder,
                                     name.getLabelCount(), true));
            }
            case result::PARTIALMATCH: {
                if (!want_exact_match) {
                    // In case we have a partial match, check if it is better
                    // than what we have. If so, replace it.
                    uint8_t labels(
                        result.zone_finder->getOrigin().getLabelCount());
                    if (labels > candidate->matched_labels_) {
                        // This one is strictly better. Replace it.
                        candidate.reset(new SearchResult(info.data_src_,
                                                         result.zone_finder,
                                                         labels, false));
                    }
                }
                break;
            }
            default: {
                // Nothing found, nothing to do.
                ;
            }
        }
    }

    // TODO: In case we have only the datasource and not the finder
    // and the need_updater parameter is true, get the zone there.

    // Return the partial match we have. In case we didn't want a partial
    // match, this surely contains the original empty result.
    return (*candidate);
}

// NOTE: This function is not tested, it would be complicated. However, the
// purpose of the function is to provide a very thin wrapper to be able to
// replace the call to DataSourceClientContainer constructor in tests.
ConfigurableContainer::DataSourcePair
ConfigurableContainer::getDataSource(const string& type,
                                     const ::ConstElementPtr& configuration)
{
    DataSourceClientContainerPtr
        container(new DataSourceClientContainer(type, configuration));
    return (DataSourcePair(&container->getInstance(), container));
}

}
}
