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

#include <datasrc/zone_table_config.h>
#include <datasrc/client.h>
#include <datasrc/memory/load_action.h>
#include <dns/name.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <map>
#include <string>

using namespace isc::data;

namespace isc {
namespace datasrc {
namespace internal {

ZoneTableConfig::ZoneTableConfig(const std::string& datasrc_type,
                                 DataSourceClient* datasrc_client,
                                 const Element& datasrc_conf) :
    datasrc_client_(datasrc_client)
{
    ConstElementPtr params = datasrc_conf.get("params");
    if (!params) {
        params.reset(new NullElement());
    }

    if (datasrc_type == "MasterFiles") {
        if (datasrc_client) {
            isc_throw(isc::InvalidParameter,
                      "data source client is given for MasterFiles");
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
        if (!datasrc_client) {
            isc_throw(isc::InvalidParameter,
                      "data source client is missing for data source type: "
                      << datasrc_type);
        }

        if (!datasrc_conf.contains("cache-zones")) {
            isc_throw(isc::NotImplemented, "Auto-detection of zones "
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
                isc_throw(InvalidParameter, "Duplicate cache zone: " <<
                          zone_name);
            }
        }
    }
}

} // namespace internal
} // namespace datasrc
} // namespace isc
