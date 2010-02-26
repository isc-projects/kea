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
#include <dns/rrsetlist.h>
#include <auth/query.h>
#include <iostream>

using namespace isc::dns;

namespace isc {
namespace auth {

class DataSrc;
class NameMatch;

class AbstractDataSrc {
public:
    enum Result {
        SUCCESS,
        ERROR,
        NOT_IMPLEMENTED
    };

    // These flags indicate conditions encountered while processing a query.
    //
    // REFERRAL:       The node contains an NS record
    // CNAME_FOUND:    The node contains a CNAME record
    // NAME_NOT_FOUND: The node does not exist in the data source.
    // TYPE_NOT_FOUND: The node does not contain the requested RRType
    // NO_SUCH_ZONE:   The zone does not exist in this data source.
    enum QueryResponseFlags {
        REFERRAL = 0x01,
        CNAME_FOUND = 0x02,
        NAME_NOT_FOUND = 0x04,
        TYPE_NOT_FOUND = 0x08,
        NO_SUCH_ZONE = 0x10
    };

    virtual ~AbstractDataSrc() {};

    // 'High-level' methods.  These will be implemented by the
    // general DataSrc class, and SHOULD NOT be overwritten by subclasses.
    virtual void doQuery(Query query) = 0;

    // XXX: High-level methods to be implemented later:
    // virtual void doUpdate(Update update) = 0;
    // virtual void doXfr(Query query) = 0;

    // 'Medium-level' methods.  This will be implemented by the general
    // DataSrc class but MAY be overwritten by subclasses.
    virtual void findClosestEnclosure(NameMatch& match) const = 0;

    // Optional 'low-level' methods.  These will have stub implementations
    // in the general DataSrc class but MAY be overwritten by subclasses
    virtual Result init() = 0;
    virtual Result close() = 0;

    // Mandatory 'low-level' methods: These will NOT be implemented by
    // the general DataSrc class; subclasses MUST implement them.
    virtual Result findRRset(const Query& q,
                             const Name& qname,
                             const RRClass& qclass,
                             const RRType& qtype,
                             RRsetList& target,
                             uint32_t& flags,
                             Name* zone = NULL) const = 0;

    virtual Result findExactRRset(const Query& q,
                                  const Name& qname,
                                  const RRClass& qclass,
                                  const RRType& qtype,
                                  RRsetList& target,
                                  uint32_t& flags,
                                  Name* zone = NULL) const = 0;

    // These will have dumb implementations in the general DataSrc
    // class, and SHOULD be overwritten by subclasses.
    virtual Result findAddrs(const Query& q,
                             const Name& qname,
                             const RRClass& qclass,
                             RRsetList& target,
                             uint32_t& flags,
                             Name* zone = NULL) const = 0;

     virtual Result findReferral(const Query& q,
                                const Name& qname,
                                const RRClass& qclass,
                                RRsetList& target,
                                uint32_t& flags,
                                Name* zone = NULL) const = 0;

    // This MUST be implemented by concrete data sources which support
    // DNSSEC, but is optional for others (e.g., the static data source).
    virtual Result findPreviousName(const Query& q,
                                    const Name& qname,
                                    Name& target,
                                    Name* zone) const = 0;

};

// Base class for a DNS Data Source
class DataSrc : public AbstractDataSrc {
public:
    DataSrc() : rrclass(RRClass::IN()) {}
    DataSrc(const RRClass& c) : rrclass(c) {}
    virtual ~DataSrc() {};

    void doQuery(Query q);

    virtual void findClosestEnclosure(NameMatch& match) const = 0;

    const RRClass& getClass() const { return rrclass; }
    void setClass(RRClass& c) { rrclass = c; }
    void setClass(const RRClass& c) { rrclass = c; }

    Result init() { return NOT_IMPLEMENTED; }
    Result close() { return NOT_IMPLEMENTED; }

    virtual Result findRRset(const Query& q,
                             const Name& qname,
                             const RRClass& qclass,
                             const RRType& qtype,
                             RRsetList& target,
                             uint32_t& flags,
                             Name* zone = NULL) const = 0;

    virtual Result findExactRRset(const Query& q,
                                  const Name& qname,
                                  const RRClass& qclass,
                                  const RRType& qtype,
                                  RRsetList& target,
                                  uint32_t& flags,
                                  Name* zone = NULL) const = 0;

    virtual Result findAddrs(const Query& q,
                               const Name& qname,
                               const RRClass& qclass,
                               RRsetList& target,
                               uint32_t& flags,
                               Name* zone = NULL) const {
        Result r;
        bool a = false, aaaa = false;

        flags = 0;
        r = findExactRRset(q, qname, qclass, RRType::A(), target, flags, zone);
        if (r == SUCCESS && flags == 0) {
            a = true;
        }

        flags = 0;
        r = findExactRRset(q, qname, qclass, RRType::AAAA(), target,
                           flags, zone);
        if (r == SUCCESS && flags == 0) {
            aaaa = true;
        }

        if (!a && !aaaa) {
            flags = TYPE_NOT_FOUND;
        } else {
            flags = 0;
        }

        return (SUCCESS);
    }

    virtual Result findReferral(const Query& q,
                                const Name& qname,
                                const RRClass& qclass,
                                RRsetList& target,
                                uint32_t& flags,
                                Name* zone = NULL) const {
        Result r;
        bool ns = false, ds = false, dname = false;

        flags = 0;
        r = findExactRRset(q, qname, qclass, RRType::NS(), target, flags, zone);
        if (r == SUCCESS && flags == 0) {
            ns = true;
        } else if ((flags & (NO_SUCH_ZONE|NAME_NOT_FOUND))) {
            return (SUCCESS);
        }

        flags = 0;
        r = findExactRRset(q, qname, qclass, RRType::DS(), target, flags, zone);
        if (r == SUCCESS && flags == 0) {
            ds = true;
        } else if ((flags & (NO_SUCH_ZONE|NAME_NOT_FOUND))) {
            return (SUCCESS);
        }

        flags = 0;
        r = findExactRRset(q, qname, qclass, RRType::DNAME(), target,
                           flags, zone);
        if (r == SUCCESS && flags == 0) {
            dname = true;
        } else if ((flags & (NO_SUCH_ZONE|NAME_NOT_FOUND))) {
            return (SUCCESS);
        }

        if (!ns && !dname && !ds) {
            flags = TYPE_NOT_FOUND;
        } else {
            flags = 0;
        }

        return (SUCCESS);
    }

    virtual Result findPreviousName(const Query& q,
                                    const Name& qname,
                                    Name& target,
                                    Name* zone) const = 0;
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
    }

    void findClosestEnclosure(NameMatch& match) const {
        BOOST_FOREACH (DataSrc* ds, data_sources) {
            if (getClass() != RRClass::ANY() && ds->getClass() != getClass()) {
                continue;
            }

            ds->findClosestEnclosure(match);
        }
    }

    // Actual queries for data should not be sent to a MetaDataSrc object,
    // so we return NOT_IMPLEMENTED if we receive any.
    //
    // The proper way to use the MetaDataSrc is to run findClosestEnclosure()
    // to get a pointer to the best concrete data source for the specified
    // zone, then send all queries directly to that data source.

    Result findRRset(const Query& q, const Name& qname,
                     const RRClass& qclass, const RRType& qtype,
                     RRsetList& target, uint32_t& flags,
                     Name* zone = NULL) const {
        return (NOT_IMPLEMENTED);
    }

    Result findExactRRset(const Query& q, const Name& qname,
                          const RRClass& qclass, const RRType& qtype,
                          RRsetList& target, uint32_t& flags,
                          Name* zone = NULL) const {
        return (NOT_IMPLEMENTED);
    }

    Result findAddrs(const Query& q,
                     const Name& qname, const RRClass& qclass,
                     RRsetList& target, uint32_t& flags,
                     Name* zone = NULL) const {
        return (NOT_IMPLEMENTED);
    }

    Result findReferral(const Query& q,
                        const Name& qname, const RRClass& qclass,
                        RRsetList& target, uint32_t& flags,
                        Name* zone = NULL) const {
        return (NOT_IMPLEMENTED);
    }

    virtual Result findPreviousName(const Query& q,
                                    const Name& qname,
                                    Name& target,
                                    Name* zone) const {
        return (NOT_IMPLEMENTED);
    }

private:
    std::vector<DataSrc*> data_sources;
};

class NameMatch {
public:
    NameMatch(const Name& qname) :
        closest_name_(NULL), best_source_(NULL), qname_(qname) {}

    ~NameMatch() {
        delete closest_name_;
    }

    void update(const DataSrc& new_source, const Name& container) {
        if (closest_name_ == NULL) {
            closest_name_ = new Name(container);
            best_source_ = &new_source;
            return;
        }

        NameComparisonResult::NameRelation cmp = 
            container.compare(*closest_name_).getRelation();

        if (cmp == NameComparisonResult::SUBDOMAIN) {
            Name* newname = new Name(container);
            delete closest_name_;
            closest_name_ = newname;
            best_source_ = &new_source;
        }
    }

    const Name& qname() { return (qname_); }
    const Name* closestName() { return (closest_name_); }
    const DataSrc* bestDataSrc() { return (best_source_); }

private:
    const Name* closest_name_;
    const DataSrc* best_source_;
    const Name& qname_;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
