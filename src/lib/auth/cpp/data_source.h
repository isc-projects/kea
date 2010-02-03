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

#include <boost/foreach.hpp>
#include <dns/name.h>
#include <dns/rrset.h>
#include <auth/query.h>

namespace isc {
namespace dns {

enum DSResult {
    SUCCESS,
    NOT_IMPLEMENTED,
    ERROR,
    CNAME,
    ZONE_NOT_FOUND,
    NAME_NOT_FOUND,
    TYPE_NOT_FOUND
};

class DataSrc;

class AbstractDataSrc {
public:
    virtual ~AbstractDataSrc() {};

    // 'High-level' methods.  These will be implemented by the
    // general DataSrc class, but MAY be overwritten by subclasses.
    virtual DSResult runQuery(Query query) = 0;

    // Mandatory 'low-level' methods: These will NOT be implemented by
    // the general DataSrc class; subclasses MUST implement them.
    virtual DSResult findRRset(const Name& qname,
                               const RRClass& qclass,
                               const RRType& qtype,
                               RRsetList& target,
                               RRsetList& sigs) const = 0;

    virtual DSResult findRRset(const Name& qname,
                               const RRClass& qclass,
                               const RRType& qtype,
                               RRsetList& target) const = 0;

    virtual const DataSrc* findClosestEnclosure(const Name& qname,
                                                Name& container,
                                                bool& found) const = 0;

    // Optional 'low-level' methods.  These will have stub implementations
    // in the general DataSrc class but MAY be overwritten by subclasses
    virtual DSResult init() = 0;
    virtual DSResult close() = 0;

    //virtual const RRClass& getClass() const = 0;
    //virtual const RRClass& setClass() const = 0;
};

// Base class for a DNS Data Source
class DataSrc : public AbstractDataSrc {
public:
    DataSrc() : rrclass(RRClass::IN()) {}
    DataSrc(const RRClass& c) : rrclass(c) {}
    virtual ~DataSrc() {};

    DSResult runQuery(Query q);

    virtual DSResult findRRset(const Name& qname,
                               const RRClass& qclass,
                               const RRType& qtype,
                               RRsetList& target,
                               RRsetList& sigs) const = 0;

    virtual DSResult findRRset(const Name& qname,
                               const RRClass& qclass,
                               const RRType& qtype,
                               RRsetList& target) const = 0;

    virtual const DataSrc* findClosestEnclosure(const Name& qname,
                                                Name& container,
                                                bool& found) const = 0;

    const RRClass& getClass() const { return rrclass; }
    void setClass(RRClass& c) { rrclass = c; }

    DSResult init() { return NOT_IMPLEMENTED; }
    DSResult close() { return NOT_IMPLEMENTED; }

private:
    RRClass rrclass;
};

class MetaDataSrc : public DataSrc {
public:
    MetaDataSrc() : DataSrc(RRClass::ANY()) {}
    MetaDataSrc(const RRClass& c) : DataSrc(c) {}
    virtual ~MetaDataSrc() {}

    void addDataSrc(DataSrc* ds) {
        if (getClass() != RRClass::ANY() && ds->getClass() != getClass()) {
            dns_throw(Unexpected, "class mismatch");
        }

        data_sources.push_back(ds);
    };

    const DataSrc* findClosestEnclosure(const Name& qname,
                                        Name& container,
                                        bool& found) const
    {
        const DataSrc* best = NULL;
        BOOST_FOREACH (DataSrc* ds, data_sources) {
            const DataSrc* source;

            if (getClass() != RRClass::ANY() && ds->getClass() != getClass()) {
                continue;
            }

            source = ds->findClosestEnclosure(qname, container, found);
            if (source != NULL) {
                best = source;
            }
        }

        return (best);
    };

private:
    std::vector<DataSrc*> data_sources;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
