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

#include <datasrc/tests/mock_client.h>
#include <datasrc/client.h>
#include <datasrc/result.h>
#include <datasrc/zone_iterator.h>
#include <datasrc/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

#include <cc/data.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include <vector>
#include <set>
#include <string>

using namespace isc::dns;

using boost::shared_ptr;
using std::vector;
using std::string;
using std::set;

namespace isc {
namespace datasrc {
namespace unittest {

namespace {
class Finder : public ZoneFinder {
public:
    Finder(const Name& origin) :
        origin_(origin)
    {}
    Name getOrigin() const { return (origin_); }
    // The rest is not to be called, so just have them
    RRClass getClass() const {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    shared_ptr<Context> find(const Name&, const RRType&,
                             const FindOptions)
    {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    shared_ptr<Context> findAll(const Name&,
                                vector<ConstRRsetPtr>&,
                                const FindOptions)
    {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    FindNSEC3Result findNSEC3(const Name&, bool) {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
private:
    Name origin_;
};

class Iterator : public ZoneIterator {
public:
    Iterator(const Name& origin, bool include_a) :
        origin_(origin),
        soa_(new RRset(origin_, RRClass::IN(), RRType::SOA(),
                       RRTTL(3600)))
    {
        // The RData here is bogus, but it is not used to anything. There
        // just needs to be some.
        soa_->addRdata(rdata::generic::SOA(Name::ROOT_NAME(),
                                           Name::ROOT_NAME(),
                                           0, 0, 0, 0, 0));
        rrsets_.push_back(soa_);

        RRsetPtr rrset(new RRset(origin_, RRClass::IN(), RRType::NS(),
                                 RRTTL(3600)));
        rrset->addRdata(rdata::generic::NS(Name::ROOT_NAME()));
        rrsets_.push_back(rrset);

        if (include_a) {
            // Dummy A rrset. This is used for checking zone data
            // after reload.
            rrset.reset(new RRset(Name("tstzonedata").concatenate(origin_),
                                  RRClass::IN(), RRType::A(),
                                  RRTTL(3600)));
            rrset->addRdata(rdata::in::A("192.0.2.1"));
            rrsets_.push_back(rrset);
        }

        rrsets_.push_back(ConstRRsetPtr());

        it_ = rrsets_.begin();
    }
    virtual isc::dns::ConstRRsetPtr getNextRRset() {
        ConstRRsetPtr result = *it_;
        ++it_;
        return (result);
    }
    virtual isc::dns::ConstRRsetPtr getSOA() const {
        return (soa_);
    }
private:
    const Name origin_;
    const RRsetPtr soa_;
    vector<ConstRRsetPtr> rrsets_;
    vector<ConstRRsetPtr>::const_iterator it_;
};
}

// A test data source. It pretends it has some zones.

MockDataSourceClient::MockDataSourceClient(const char* zone_names[]) :
    have_a_(true), use_baditerator_(true)
{
    for (const char** zone(zone_names); *zone; ++zone) {
        zones.insert(Name(*zone));
    }
}

// Constructor from configuration. The list of zones will be empty, but
// it will keep the configuration inside for further inspection.
MockDataSourceClient::MockDataSourceClient(
    const string& type,
    const data::ConstElementPtr& configuration) :
    type_(type),
    configuration_(configuration),
    have_a_(true), use_baditerator_(true)
{
    EXPECT_NE("MasterFiles", type) << "MasterFiles is a special case "
        "and it never should be created as a data source client";
    if (configuration_->getType() == data::Element::list) {
        for (size_t i(0); i < configuration_->size(); ++i) {
            zones.insert(Name(configuration_->get(i)->stringValue()));
        }
    }
}

DataSourceClient::FindResult
MockDataSourceClient::findZone(const Name& name) const {
    if (zones.empty()) {
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    }
    set<Name>::const_iterator it(zones.upper_bound(name));
    if (it == zones.begin()) {
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    }
    --it;
    NameComparisonResult compar(it->compare(name));
    const ZoneFinderPtr finder(new Finder(*it));
    switch (compar.getRelation()) {
    case NameComparisonResult::EQUAL:
        return (FindResult(result::SUCCESS, finder));
    case NameComparisonResult::SUPERDOMAIN:
        return (FindResult(result::PARTIALMATCH, finder));
    default:
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    }
}

// These methods are not used. They just need to be there to have
// complete vtable.

ZoneIteratorPtr
MockDataSourceClient::getIterator(const Name& name, bool) const {
    if (use_baditerator_ && name == Name("noiter.org")) {
        isc_throw(isc::NotImplemented, "Asked not to be implemented");
    } else if (use_baditerator_ && name == Name("null.org")) {
        return (ZoneIteratorPtr());
    } else {
        FindResult result(findZone(name));
        if (result.code == isc::datasrc::result::SUCCESS) {
            return (ZoneIteratorPtr(new Iterator(name, have_a_)));
        } else {
            isc_throw(DataSourceError, "No such zone");
        }
    }
}

} // end of unittest
} // end of datasrc
} // end of isc
