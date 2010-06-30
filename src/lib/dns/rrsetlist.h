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
#include <iterator>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

namespace isc {
namespace dns {

class DuplicateRRset : public Exception {
public:
    DuplicateRRset(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

template <typename T, typename P, typename R>
class RRsetListIterator :
        public std::iterator<std::input_iterator_tag, RRsetPtr> {
public:
    RRsetListIterator() {}
    explicit RRsetListIterator(const T& it) :
        it_(it) {}
    RRsetListIterator& operator++()
    {
        ++it_;
        return (*this);
    }
    RRsetListIterator operator++(int)
    {
        RRsetListIterator tmp(*this);
        ++it_;
        return (tmp);
    }
    R operator*() const
    {
        return (*it_);
    }
    P operator->() const
    {
        return (&(operator*()));
    }
    bool operator==(const RRsetListIterator& other)
    {
        return (it_ == other.it_);
    }
    bool operator!=(const RRsetListIterator& other)
    {
        return (it_ != other.it_);
    }
    
private:
    T it_;
};

class RRsetList {
private:
    RRsetList(const RRsetList& source);
    RRsetList& operator=(const RRsetList& source);
public:
    RRsetList() {}
    void addRRset(RRsetPtr new_rrsetptr);
    RRsetPtr findRRset(const RRType& rrtype, const RRClass& rrclass);

    typedef RRsetListIterator<std::vector<RRsetPtr>::iterator,
                              RRsetPtr*,
                              RRsetPtr&> iterator;
    typedef RRsetListIterator<std::vector<RRsetPtr>::const_iterator,
                              const RRsetPtr*,
                              const RRsetPtr&> const_iterator;

    const_iterator begin() const { return (const_iterator(rrsets_.begin())); }
    const_iterator end() const { return (const_iterator(rrsets_.end())); }

    iterator begin() { return (iterator(rrsets_.begin())); }
    iterator end() { return (iterator(rrsets_.end())); }

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
