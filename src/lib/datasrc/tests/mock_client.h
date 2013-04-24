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

#include <datasrc/client.h>

#include <dns/dns_fwd.h>
#include <dns/rrset.h>

#include <cc/data.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <vector>

namespace isc {
namespace datasrc {
namespace unittest {

// A test data source. It pretends it has some zones.
class MockDataSourceClient : public DataSourceClient {
public:
    // Constructor from a list of zones.
    MockDataSourceClient(const char* zone_names[]);

    // Constructor from configuration. The list of zones will be empty, but
    // it will keep the configuration inside for further inspection.
    MockDataSourceClient(const std::string& type,
                         const data::ConstElementPtr& configuration);

    virtual FindResult findZone(const dns::Name& name) const;
    // These methods are not used. They just need to be there to have
    // complete vtable.
    virtual ZoneUpdaterPtr getUpdater(const dns::Name&, bool, bool) const {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
    getJournalReader(const dns::Name&, uint32_t, uint32_t) const
    {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    virtual ZoneIteratorPtr getIterator(const dns::Name& name, bool) const;
    void disableA() { have_a_ = false; }
    void enableA() { have_a_ = true; }
    void disableBadIterator() { use_baditerator_ = false; }
    void enableBadIterator() { use_baditerator_ = true; }
    void eraseZone(const dns::Name& zone_name) {
        zones.erase(zone_name);
    }
    const std::string type_;
    const data::ConstElementPtr configuration_;

private:
    std::set<dns::Name> zones;
    bool have_a_; // control the iterator behavior whether to include A record
    bool use_baditerator_; // whether to use bogus zone iterators for tests
};

} // end of unittest
} // end of datasrc
} // end of isc

// Local Variables:
// mode: c++
// End:
