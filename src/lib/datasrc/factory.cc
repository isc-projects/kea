// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "factory.h"

#include "data_source.h"
#include "database.h"
#include "sqlite3_accessor.h"
#include "memory_datasrc.h"

namespace isc {
namespace datasrc {

boost::shared_ptr<DataSourceClient>
createDataSourceClient(const std::string& type,
                       const isc::dns::RRClass& rrclass,
                       isc::data::ConstElementPtr config) {
    // For now, mapping hardcoded
    // config is assumed to be ok
    if (type == "sqlite3") {
        boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
            new SQLite3Accessor(config->get("dbfile")->stringValue(), rrclass));
        return boost::shared_ptr<DataSourceClient>(
            new DatabaseClient(rrclass, sqlite3_accessor));
    } else if (type == "memory") {
        return boost::shared_ptr<DataSourceClient>(new InMemoryClient());
    } else {
        isc_throw(DataSourceError, "Unknown datasource type: " << type);
    }
}

} // end namespace datasrc
} // end namespace isc

