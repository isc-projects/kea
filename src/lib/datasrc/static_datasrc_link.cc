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

#include "client.h"
#include "memory_datasrc.h"
#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/zone_table_segment.h>

#include <cc/data.h>
#include <dns/rrclass.h>

#include <memory>
#include <exception>

using namespace isc::data;
using namespace isc::dns;
using namespace boost;
using namespace std;

namespace isc {
namespace datasrc {

DataSourceClient*
createInstance(ConstElementPtr config, string& error) {
    try {
        shared_ptr<memory::ZoneTableSegment> ztable_segment(
            memory::ZoneTableSegment::create(*config, RRClass::CH()));
        // Create the data source
        auto_ptr<memory::InMemoryClient> client
            (new memory::InMemoryClient(ztable_segment, RRClass::CH()));

        // Fill it with data
        const string path(config->stringValue());
        client->load(Name("BIND"), path);

        return (client.release());
    }
    catch (const std::exception& e) {
        error = e.what();
    }
    catch (...) {
        error = "Unknown exception";
    }
    return (NULL);
}

void
destroyInstance(DataSourceClient* instance) {
    delete instance;
}

}
}
