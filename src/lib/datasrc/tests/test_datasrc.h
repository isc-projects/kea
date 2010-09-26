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

#include <datasrc/data_source.h>

namespace isc {

namespace dns {
class Name;
class RRClass;
class RRType;
class RRsetList;
}

namespace datasrc {
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
    TestDataSrc() : initialized(false) {}
    ~TestDataSrc() {}
    //@}

    void findClosestEnclosure(DataSrcMatch& match) const;

    Result findRRset(const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     const isc::dns::RRType& qtype,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findExactRRset(const isc::dns::Name& qname,
                          const isc::dns::RRClass& qclass,
                          const isc::dns::RRType& qtype,
                          isc::dns::RRsetList& target,
                          uint32_t& flags,
                          const isc::dns::Name* zonename) const;

    Result findAddrs(const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findReferral(const isc::dns::Name& qname,
                        const isc::dns::RRClass& qclass,
                        isc::dns::RRsetList& target,
                        uint32_t& flags,
                        const isc::dns::Name* zonename) const;

    Result findPreviousName(const isc::dns::Name& qname,
                            isc::dns::Name& target,
                            const isc::dns::Name* zonename) const;

    Result findCoveringNSEC3(const isc::dns::Name& zonename,
                             std::string& hash,
                             isc::dns::RRsetList& target) const;

    Result init();
    Result init(isc::data::ConstElementPtr config);
    Result close() { return (SUCCESS); }

private:
    bool initialized;
    enum Mode {
        NORMAL,
        ADDRESS,
        DELEGATION
    };
    class RRsetMatch;

    void findRecords(const isc::dns::Name& name, const isc::dns::RRType& rdtype,
                     isc::dns::RRsetList& target,
                     const isc::dns::Name* zonename, const Mode mode,
                     uint32_t& flags) const;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
