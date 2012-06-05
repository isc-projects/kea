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

#include <memory>
#include <boost/foreach.hpp>

using namespace isc::data;
using namespace std;

namespace isc {
namespace datasrc {

ConfigurableContainer::ConfigurableContainer(const ConstElementPtr&, bool,
                                             const ConstContainerPtr&)
{
    // TODO: Implement
}

Container::SearchResult
ConfigurableContainer::search(const dns::Name& name, bool want_exact_match,
                              bool ) const
{
    // Nothing yet.
    auto_ptr<SearchResult> candidate(new SearchResult());
    BOOST_FOREACH(const DataSourceInfo& info, data_sources_) {
        DataSourceClient::FindResult result(info.data_src_->findZone(name));
        switch (result.code) {
            case result::SUCCESS: {
                // If we found an exact match, we have no hope to getting
                // a better one. Stop right here.
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
    // Return the partial match we have.
    return (*candidate);
}

}
}
