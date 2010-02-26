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

#include <gtest/gtest.h>
#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace isc::dns;

#include "data_source.h"

namespace isc {
namespace auth {
class TestDataSrc : public DataSrc {
public:
    TestDataSrc();
    ~TestDataSrc() {}

    void findClosestEnclosure(NameMatch& match) const;

    Result findRRset(const Query& q,
                     const Name& qname,
                     const RRClass& qclass,
                     const RRType& qtype,
                     RRsetList& target,
                     uint32_t& flags,
                     Name* zone = NULL) const;

    Result findExactRRset(const Query& q,
                          const Name& qname,
                          const RRClass& qclass,
                          const RRType& qtype,
                          RRsetList& target,
                          uint32_t& flags,
                          Name* zone = NULL) const;

    Result findAddrs(const Query& q,
                     const Name& qname,
                     const RRClass& qclass,
                     RRsetList& target,
                     uint32_t& flags,
                     Name* zone = NULL) const;

    Result findReferral(const Query& q,
                        const Name& qname,
                        const RRClass& qclass,
                        RRsetList& target,
                        uint32_t& flags,
                        Name* zone = NULL) const;

    Result findPreviousName(const Query& q,
                            const Name& qname,
                            Name& target,
                            Name* zone) const;

    Result init() { return (SUCCESS); }
    Result close() { return (SUCCESS); }

private:
    enum Mode {
        NORMAL,
        ADDRESS,
        DELEGATION
    };

    void findRecords(const Name& name, const RRType& rdtype,
                     RRsetList& target, Name* zone, const Mode mode,
                     uint32_t& flags) const;

    const Name example;
    const Name sql1;
    const Name www_sql1;
    const Name www;
    const Name foo;
    const Name dns01;
    const Name dns02;
    const Name dns03;
    const Name cnameint;
    const Name cnameext;
    const Name dname;
    const Name wild;
    const Name subzone;
    RRsetPtr example_ns;
    RRsetPtr example_soa;
    RRsetPtr example_nsec;
    RRsetPtr www_a;
    RRsetPtr www_nsec;
    RRsetPtr foo_cname;
    RRsetPtr foo_nsec;
    RRsetPtr cnameint_cname;
    RRsetPtr cnameint_nsec;
    RRsetPtr cnameext_cname;
    RRsetPtr cnameext_nsec;
    RRsetPtr dns01_a;
    RRsetPtr dns01_nsec;
    RRsetPtr dns02_a;
    RRsetPtr dns02_nsec;
    RRsetPtr dns03_a;
    RRsetPtr dns03_nsec;
    RRsetPtr wild_a;
    RRsetPtr wild_nsec;
    RRsetPtr dname_dname;
    RRsetPtr dname_nsec;
    RRsetPtr sql1_ns;
    RRsetPtr sql1_soa;
    RRsetPtr sql1_nsec;
    RRsetPtr sql1_ds;
    RRsetPtr sql1_ds_nsec;
    RRsetPtr www_sql1_a;
    RRsetPtr www_sql1_nsec;
    RRsetPtr subzone_ns;
    RRsetPtr subzone_nsec;
    RRsetPtr subzone_glue1;
    RRsetPtr subzone_glue2;
    RRsetPtr subzone_ds;
};

}
}

#endif
