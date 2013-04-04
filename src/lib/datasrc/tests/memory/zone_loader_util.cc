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

#include <datasrc/tests/memory/zone_loader_util.h>

#include <datasrc/zone_iterator.h>
#include <datasrc/cache_config.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/zone_writer.h>

#include <dns/dns_fwd.h>

#include <cc/data.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>

namespace isc {
namespace datasrc {
namespace memory {
namespace test {

void
loadZoneIntoTable(ZoneTableSegment& zt_sgmt, const dns::Name& zname,
                  const dns::RRClass& zclass, const std::string& zone_file)
{
    const isc::datasrc::internal::CacheConfig cache_conf(
        "MasterFiles", NULL, *data::Element::fromJSON(
            "{\"cache-enable\": true,"
            " \"params\": {\"" + zname.toText() + "\": \"" + zone_file +
            "\"}}"), true);
    boost::scoped_ptr<memory::ZoneWriter> writer(
        zt_sgmt.getZoneWriter(cache_conf.getLoadAction(zclass, zname),
                              zname, zclass));
    writer->load();
    writer->install();
    writer->cleanup();
}

namespace {
// borrowed from CacheConfig's internal
class IteratorLoader {
public:
    IteratorLoader(const dns::RRClass& rrclass, const dns::Name& name,
                   ZoneIterator& iterator) :
        rrclass_(rrclass),
        name_(name),
        iterator_(iterator)
    {}
    memory::ZoneData* operator()(util::MemorySegment& segment) {
        return (memory::loadZoneData(segment, rrclass_, name_, iterator_));
    }
private:
    const dns::RRClass rrclass_;
    const dns::Name name_;
    ZoneIterator& iterator_;
};
}

void
loadZoneIntoTable(ZoneTableSegment& zt_sgmt, const dns::Name& zname,
                  const dns::RRClass& zclass, ZoneIterator& iterator)
{
    boost::scoped_ptr<memory::ZoneWriter> writer(
        zt_sgmt.getZoneWriter(IteratorLoader(zclass, zname, iterator),
                              zname, zclass));
    writer->load();
    writer->install();
    writer->cleanup();
}

} // namespace test
} // namespace memory
} // namespace datasrc
} // namespace isc

// Local Variables:
// mode: c++
// End:
