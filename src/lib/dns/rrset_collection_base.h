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

#ifndef RRSET_COLLECTION_BASE_H
#define RRSET_COLLECTION_BASE_H 1

#include <dns/rrset.h>
#include <dns/name.h>

#include <boost/shared_ptr.hpp>

#include <iterator>

namespace isc {
namespace dns {

/// \brief Generic class to represent a set of RRsets.
///
/// This is a generic container and the stored set of RRsets does not
/// necessarily form a valid zone (e.g. there doesn't necessarily have
/// to be an SOA at the "origin"). Instead, it will be used to represent
/// a single zone for the purpose of zone loading/checking. It provides
/// a simple find() method to find an RRset for the given name and type
/// (and maybe class) and a way to iterate over all RRsets.
///
/// See \c RRsetCollection for a simple libdns++ implementation using an
/// STL container. libdatasrc will have another implementation.
class RRsetCollectionBase {
public:
    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name and \c rrtype.  If no matching RRset is found,
    /// \c NULL is returned.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \returns A pointer to the RRset if found, \c NULL otherwise.
    virtual const isc::dns::AbstractRRset* find(const isc::dns::Name& name,
                                                const isc::dns::RRType& rrtype)
        const = 0;

protected:
    class Iter; // forward declaration
    typedef boost::shared_ptr<Iter> IterPtr;

    class Iter {
    public:
        virtual const isc::dns::AbstractRRset& getValue() = 0;
        virtual IterPtr getNext() = 0;
        virtual bool equals(Iter& other) = 0;
    };

    virtual IterPtr getBeginning() = 0;
    virtual IterPtr getEnd() = 0;

public:
    class iterator : std::iterator<std::forward_iterator_tag,
                                   const isc::dns::AbstractRRset>
    {
    public:
        explicit iterator(IterPtr iter) :
            iter_(iter)
        {}

        reference operator*() {
            return (iter_->getValue());
        }

        iterator& operator++() {
            iter_ = iter_->getNext();
            return (*this);
        }

        iterator operator++(int) {
            iterator tmp(iter_);
            ++*this;
            return (tmp);
        }

        bool operator==(const iterator& other) const {
            return (iter_->equals(*other.iter_));
        }

        bool operator!=(const iterator& other) const {
            return (!iter_->equals(*other.iter_));
        }

    private:
        IterPtr iter_;
    };

    iterator begin() {
      return iterator(getBeginning());
    }

    iterator end() {
      return iterator(getEnd());
    }
};

} // end of namespace dns
} // end of namespace isc

#endif  // RRSET_COLLECTION_BASE_H

// Local Variables:
// mode: c++
// End:
