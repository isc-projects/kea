// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __DATA_SOURCE_H
#define __DATA_SOURCE_H

#include <dns/cpp/name.h>
#include <dns/cpp/rrset.h>

namespace isc {
namespace dns {

// do we need to make a template for this?
// i.e. do we want this to be able to hold more types than RRset?
class SearchResult {
public:
    enum status_type { success, error, not_implemented,
                       zone_not_found, name_not_found };

    void addRRset(RRsetPtr rrset) { rrsets.push_back(rrset); }

    status_type getStatus() { return status; }
    void setStatus(status_type s) { status = s; }
    
    /* forward iterator interface */
    typedef std::vector<RRsetPtr>::iterator iterator;
    typedef std::vector<RRsetPtr>::const_iterator const_iterator;
    std::vector<RRsetPtr>::iterator begin() { return rrsets.begin(); }
    std::vector<RRsetPtr>::iterator end() { return rrsets.end(); }
    std::vector<RRsetPtr>::const_iterator begin() const { return rrsets.begin(); }
    std::vector<RRsetPtr>::const_iterator end() const { return rrsets.end(); }
    
private:
    status_type status;
    std::vector<RRsetPtr> rrsets;
};

// Base class for a DNS Data Source
class DataSource {
public:
    //enum result { success, not_implemented, error, zone_not_found,
    //              name_not_found };

    DataSource() {};
    virtual ~DataSource() {};

    //
    // 'high-level' methods, these may or may not be overwritten;
    // depending on the data source the default implementation
    // may not be most efficient, but should at least provide
    // the needed functionality
    //

    // fill in separate lists or simple fill in an answer Message object?
    void getData(const RRsetPtr query, Message& answer);

    // how to provide highlevel update data?
    //result handleUpdate()
    

    //
    // mandatory 'low-level' methods, an implementation must overwrite these
    //
    //
    // for a 'catch-all' datasource, we need to be able to find
    // out if it has a zone for a given name
    //
    // perhaps this should not set a zone Name, but rather a specific
    // ZoneRef option (which could be datasource-specific, as it will
    // only be used to pass along to other calls)
    // Or even more abstract;
    // SomeHandler initFind(name, whatever else);
    virtual bool hasZoneFor(const Name& name, Name& zone_name) = 0;

    // for the zone_name, see getZoneFor, perhaps this needs to be a more
    // general handle
    // And perhaps we need a function that does not have that argument too
    virtual SearchResult findRRsets(const Name& zone_name,
                                    const Name& name,
                                    const RRClass& clas,
                                    const RRType& type) = 0;

    //
    // optional 'low-level' methods, an implementation may overwrite these,
    // by default they return not_implemented
    //
    virtual void init() {};
    virtual void close() {};
    //virtual result addRR(Name name, int clas, int type,
    //                     int ttl, Rdata::RdataPtr data)
    //                    { return not_implemented; };
    //virtual result delRR(isc::dns::Name name, int clas, int type) = 0;
    // on name/class/type again? or use an already constructed object?
    //virtual result getRRSigs(RRsetPtr target, const RRsetPtr rrset)
    //                        { return not_implemented; };
    //virtual result getNSECs(RRsetPtr target, const RRsetPtr rrset)
    //                        { return not_implemented; };

    // check if the zone exists, and if so, return something that could
    // be used as a pointer for the rest of these functions?
    // do we need this? do we want this?
    //virtual int getZone(void* zone, isc::dns::Name name);
    
};

}
}

#endif
