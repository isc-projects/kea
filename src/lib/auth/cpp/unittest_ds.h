// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __TEST_DATA_SOURCE_H
#define __TEST_DATA_SOURCE_H

#include <dns/name.h>
#include <dns/rrset.h>

#include <gtest/gtest.h>

#include "data_source.h"

namespace isc {

namespace dns {
class RRClass;
class RRType;
class RRsetList;
}

namespace auth {
class Query;

class TestDataSrc : public DataSrc {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
private:
    TestDataSrc(const TestDataSrc& source);
    TestDataSrc operator=(const TestDataSrc& source); 
public:
    TestDataSrc();
    ~TestDataSrc() {}
    //@}

    void findClosestEnclosure(NameMatch& match) const;

    Result findRRset(const Query& q,
                     const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     const isc::dns::RRType& qtype,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findExactRRset(const Query& q,
                          const isc::dns::Name& qname,
                          const isc::dns::RRClass& qclass,
                          const isc::dns::RRType& qtype,
                          isc::dns::RRsetList& target,
                          uint32_t& flags,
                          const isc::dns::Name* zonename) const;

    Result findAddrs(const Query& q,
                     const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findReferral(const Query& q,
                        const isc::dns::Name& qname,
                        const isc::dns::RRClass& qclass,
                        isc::dns::RRsetList& target,
                        uint32_t& flags,
                        const isc::dns::Name* zonename) const;

    Result findPreviousName(const Query& q,
                            const isc::dns::Name& qname,
                            isc::dns::Name& target,
                            const isc::dns::Name* zonename) const;

    Result init() { return (SUCCESS); }
    Result close() { return (SUCCESS); }

private:
    enum Mode {
        NORMAL,
        ADDRESS,
        DELEGATION
    };

    void findRecords(const isc::dns::Name& name, const isc::dns::RRType& rdtype,
                     isc::dns::RRsetList& target,
                     const isc::dns::Name* zonename, const Mode mode,
                     uint32_t& flags) const;

    const isc::dns::Name example;
    const isc::dns::Name sql1;
    const isc::dns::Name www_sql1;
    const isc::dns::Name www;
    const isc::dns::Name foo;
    const isc::dns::Name dns01;
    const isc::dns::Name dns02;
    const isc::dns::Name dns03;
    const isc::dns::Name cnameint;
    const isc::dns::Name cnameext;
    const isc::dns::Name dname;
    const isc::dns::Name wild;
    const isc::dns::Name subzone;
    isc::dns::RRsetPtr example_ns;
    isc::dns::RRsetPtr example_soa;
    isc::dns::RRsetPtr example_nsec;
    isc::dns::RRsetPtr www_a;
    isc::dns::RRsetPtr www_nsec;
    isc::dns::RRsetPtr foo_cname;
    isc::dns::RRsetPtr foo_nsec;
    isc::dns::RRsetPtr cnameint_cname;
    isc::dns::RRsetPtr cnameint_nsec;
    isc::dns::RRsetPtr cnameext_cname;
    isc::dns::RRsetPtr cnameext_nsec;
    isc::dns::RRsetPtr dns01_a;
    isc::dns::RRsetPtr dns01_nsec;
    isc::dns::RRsetPtr dns02_a;
    isc::dns::RRsetPtr dns02_nsec;
    isc::dns::RRsetPtr dns03_a;
    isc::dns::RRsetPtr dns03_nsec;
    isc::dns::RRsetPtr wild_a;
    isc::dns::RRsetPtr wild_nsec;
    isc::dns::RRsetPtr dname_dname;
    isc::dns::RRsetPtr dname_nsec;
    isc::dns::RRsetPtr sql1_ns;
    isc::dns::RRsetPtr sql1_soa;
    isc::dns::RRsetPtr sql1_nsec;
    isc::dns::RRsetPtr sql1_ds;
    isc::dns::RRsetPtr sql1_ds_nsec;
    isc::dns::RRsetPtr www_sql1_a;
    isc::dns::RRsetPtr www_sql1_nsec;
    isc::dns::RRsetPtr subzone_ns;
    isc::dns::RRsetPtr subzone_nsec;
    isc::dns::RRsetPtr subzone_glue1;
    isc::dns::RRsetPtr subzone_glue2;
    isc::dns::RRsetPtr subzone_ds;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
