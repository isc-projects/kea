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

#ifndef __RRSETLIST_H
#define __RRSETLIST_H 1

#include <iostream>
#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

#include "rrset.h"
#include "rrclass.h"
#include "rrtype.h"

namespace isc {
namespace dns {

class DuplicateRRset : public Exception {
public:
    DuplicateRRset(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class RRsetList {
public:
    void addRRset(const RRsetPtr new_rrsetptr);
    const RRsetPtr findRRset(const RRType& rrtype,
                             const RRClass& rrclass = RRClass::IN());
    const RRsetPtr findRRset(const RRsetPtr);

    const RRsetPtr operator[](RRType t) { return (this->findRRset(t)); }

    typedef std::vector<RRsetPtr>::const_iterator const_iterator;
    const_iterator begin() const { return (rrsets_.begin()); }
    const_iterator end() const { return (rrsets_.end)(); }

    typedef std::vector<RRsetPtr>::iterator iterator;
    iterator begin() { return (rrsets_.begin()); }
    iterator end() { return (rrsets_.end)(); }

    size_t size() const { return (rrsets_.size()); }

private:
    std::vector<RRsetPtr> rrsets_;
};

} // end of namespace dns
} // end of namespace isc
#endif  // __RRSETLIST_H

// Local Variables: 
// mode: c++
// End: 
