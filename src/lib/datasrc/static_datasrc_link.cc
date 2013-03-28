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

#include <datasrc/static_datasrc.h>
#include <datasrc/client.h>
#include <datasrc/zone_table_config.h>

#include <datasrc/memory/memory_client.h>
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
namespace {
// XXX: this is a hack: we need to make sure the zone table config is valid
// throughout the zone table segment, but there's no way to keep it alive
// within this factory.  So we use a custom segment that internally creates
// and hold the config.  Actually, we shouldn't need a separate data source
// client implementation for "static"; the generic "MasterFiles" data source
// with pre-generated configuration should suffice.  When it's done, we can
// remove this loadable module with this hack.
class ZoneTableSegmentStatic : public memory::ZoneTableSegment {
public:
    ZoneTableSegmentStatic(const string& zone_file) :
        memory::ZoneTableSegment(RRClass::CH()),
        ztconfig_("MasterFiles", 0, *data::Element::fromJSON(
                      "{\"params\": {\"BIND\": \"" + zone_file + "\"}}")),
        ztsegment_(memory::ZoneTableSegment::create(RRClass::CH(), ztconfig_))
    {}

    virtual ~ZoneTableSegmentStatic() {
        memory::ZoneTableSegment::destroy(ztsegment_);
    }

    virtual memory::ZoneTableHeader& getHeader() {
        return (ztsegment_->getHeader());
    }
    virtual const memory::ZoneTableHeader& getHeader() const {
        return (ztsegment_->getHeader());
    }
    virtual isc::util::MemorySegment& getMemorySegment() {
        return (ztsegment_->getMemorySegment());
    }
    virtual memory::ZoneWriter* getZoneWriter(
        const memory::LoadAction& load_action,
        const dns::Name& origin,
        const dns::RRClass& rrclass)
    {
        return (ztsegment_->getZoneWriter(load_action, origin, rrclass));
    }

private:
    const internal::ZoneTableConfig ztconfig_;
    memory::ZoneTableSegment* ztsegment_; // actual segment
};
}

DataSourceClient*
createInstance(ConstElementPtr config, string& error) {
    try {
        // Set up the zone table.
        const string path(config->stringValue());
        shared_ptr<memory::ZoneTableSegment> ztable_segment(
            new ZoneTableSegmentStatic(path));

        // Create the data source
        auto_ptr<memory::InMemoryClient> client
            (new memory::InMemoryClient(ztable_segment, RRClass::CH()));

        // Fill it with data
        client->load(Name("BIND"), path);

        return (client.release());
    } catch (const std::exception& e) {
        error = e.what();
    } catch (...) {
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
