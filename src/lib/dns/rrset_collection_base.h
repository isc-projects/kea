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

/// \brief Error during RRsetCollectionBase find() operation
///
/// This exception is thrown when an calling implementation of
/// \c RRsetCollectionBase::find() results in an error which is not due
/// to unmatched data, but because of some other underlying error
/// condition.
class RRsetCollectionError : public Exception {
public:
    RRsetCollectionError(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

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
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// This method's implementations currently are not specified to
    /// handle \c RRTypes such as RRSIG and NSEC3. RRSIGs are attached
    /// to their corresponding \c RRset and it is not straightforward to
    /// search for them. Searching for RRSIGs will return \c false
    /// always. Support for RRSIGs may be added in the future.
    ///
    /// Non-concrete types such as ANY and AXFR are unsupported and will
    /// return \c false always.
    ///
    /// \throw RRsetCollectionError if find() results in some
    /// implementation-specific error.
    /// \param name The name of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \return The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find
        (const isc::dns::Name& name, const isc::dns::RRClass& rrclass,
         const isc::dns::RRType& rrtype)
        const = 0;

    /// \brief Destructor
    virtual ~RRsetCollectionBase() {}

protected:
    class Iter; // forward declaration

    /// \brief Wraps Iter with a reference count.
    typedef boost::shared_ptr<Iter> IterPtr;

    /// \brief A helper iterator interface for \c RRsetCollectionBase.
    ///
    /// This is a protected iterator class that is a helper interface
    /// used by the public iterator.  Derived classes of
    /// \c RRsetCollectionBase are supposed to implement this class and
    /// the \c getBeginning() and \c getEnd() methods, so that the
    /// public interator interface can be provided. This is a forward
    /// iterator only.
    class Iter {
    public:
        virtual ~Iter() {};

        /// \brief Returns the \c AbstractRRset currently pointed to by
        /// the iterator.
        virtual const isc::dns::AbstractRRset& getValue() = 0;

        /// \brief Returns an \c IterPtr wrapping an Iter pointing to
        /// the next \c AbstractRRset in sequence in the collection.
        virtual IterPtr getNext() = 0;

        /// \brief Check if another iterator is equal to this one.
        ///
        /// Returns \c true if this iterator is equal to \c other,
        /// \c false otherwise. Note that if \c other is not the same
        /// type as \c this, or cannot be compared meaningfully, the
        /// method must return \c false.
        ///
        /// \param other The other iterator to compare against.
        /// \return \c true if equal, \c false otherwise.
        virtual bool equals(Iter& other) = 0;
    };

    /// \brief Returns an \c IterPtr wrapping an Iter pointing to the
    /// beginning of the collection.
    ///
    /// \throw isc::dns::RRsetCollectionError if using the iterator
    /// results in some underlying datasrc error.
    virtual IterPtr getBeginning() = 0;

    /// \brief Returns an \c IterPtr wrapping an Iter pointing past the
    /// end of the collection.
    ///
    /// \throw isc::dns::RRsetCollectionError if using the iterator
    /// results in some underlying datasrc error.
    virtual IterPtr getEnd() = 0;

public:
    /// \brief A forward \c std::iterator for \c RRsetCollectionBase.
    ///
    /// It behaves like a \c std::iterator forward iterator, so please
    /// see its documentation for usage.
    class Iterator : std::iterator<std::forward_iterator_tag,
                                   const isc::dns::AbstractRRset>
    {
    public:
        explicit Iterator(IterPtr iter) :
            iter_(iter)
        {}

        reference operator*() {
            return (iter_->getValue());
        }

        Iterator& operator++() {
            iter_ = iter_->getNext();
            return (*this);
        }

        Iterator operator++(int) {
            Iterator tmp(iter_);
            ++*this;
            return (tmp);
        }

        bool operator==(const Iterator& other) const {
            return (iter_->equals(*other.iter_));
        }

        bool operator!=(const Iterator& other) const {
            return (!iter_->equals(*other.iter_));
        }

    private:
        IterPtr iter_;
    };

    /// \brief Returns an iterator pointing to the beginning of the
    /// collection.
    Iterator begin() {
      return Iterator(getBeginning());
    }

    /// \brief Returns an iterator pointing past the end of the
    /// collection.
    Iterator end() {
      return Iterator(getEnd());
    }
};

} // end of namespace dns
} // end of namespace isc

#endif  // RRSET_COLLECTION_BASE_H

// Local Variables:
// mode: c++
// End:
