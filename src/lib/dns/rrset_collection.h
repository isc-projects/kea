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

#ifndef RRSET_COLLECTION_H
#define RRSET_COLLECTION_H 1

#include <dns/rrset_collection_base.h>
#include <dns/rrclass.h>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <map>

namespace isc {
namespace dns {

/// \brief libdns++ implementation of RRsetCollectionBase using an STL
/// container.
class RRsetCollection : public RRsetCollectionBase {
public:
    /// \brief Constructor.
    RRsetCollection()
    {}

    /// \brief Constructor.
    ///
    /// The \c origin and \c rrclass arguments are required for the zone
    /// loading, but \c RRsetCollection itself does not do any
    /// validation, and the collection of RRsets does not have to form a
    /// valid zone. The constructor throws MasterLoaderError if there is
    /// an error during loading.
    ///
    /// \param filename Name of a file containing a collection of RRs in
    /// the master file format (which may or may not form a valid zone).
    RRsetCollection(const char* filename, const isc::dns::Name& origin,
                    const isc::dns::RRClass& rrclass);

    /// \brief Add an RRset to the collection.
    ///
    /// Does not do any validation whether \c rrset belongs to a
    /// particular zone or not. It throws an \c isc::InvalidParameter
    /// exception if an rrset with the same class, type and name already
    /// exists.
    void addRRset(isc::dns::RRsetPtr rrset);

    /// \brief Remove an RRset from the collection.
    ///
    /// RRset(s) matching the \c name, \c rrclass and \c rrtype are
    /// removed from the collection.
    void removeRRset(const isc::dns::Name& name,
                     const isc::dns::RRClass& rrclass,
                     const isc::dns::RRType& rrtype);

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name and \c rrtype.  If no matching RRset is found,
    /// \c NULL is returned.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \returns A pointer to the RRset if found, \c NULL otherwise.
    virtual const isc::dns::AbstractRRset* find
        (const isc::dns::Name& name, const isc::dns::RRType& rrtype,
	 const isc::dns::RRClass& rrclass)
        const;

    isc::dns::RRsetPtr find(const isc::dns::Name& name,
                            const isc::dns::RRClass& rrclass,
                            const isc::dns::RRType& rrtype);

    isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                 const isc::dns::RRClass& rrclass,
                                 const isc::dns::RRType& rrtype) const;

private:
    void addRRset(const isc::dns::Name& name, const isc::dns::RRClass& rrclass,
                  const isc::dns::RRType& rrtype, const isc::dns::RRTTL& rrttl,
                  const isc::dns::rdata::RdataPtr& data);
    void loaderCallback(const std::string&, size_t, const std::string&);

    typedef boost::tuple<isc::dns::RRClass, isc::dns::RRType, isc::dns::Name>
        CollectionKey;
    typedef std::map<CollectionKey, isc::dns::RRsetPtr> CollectionMap;

    CollectionMap rrsets_;

protected:
    class DnsIter : public RRsetCollectionBase::Iter {
    public:
        DnsIter(CollectionMap::iterator& iter) :
            iter_(iter)
        {}

        virtual const isc::dns::AbstractRRset& getValue() {
            isc::dns::RRsetPtr& rrset = iter_->second;
            return (*rrset);
        }

        virtual IterPtr getNext() {
            CollectionMap::iterator it = iter_;
            it++;
            return (RRsetCollectionBase::IterPtr(new DnsIter(it)));
        }

        virtual bool equals(Iter& other) {
            const DnsIter& other_real = dynamic_cast<DnsIter&>(other);
            return (iter_ == other_real.iter_);
        }

    private:
        CollectionMap::iterator iter_;
    };

    virtual RRsetCollectionBase::IterPtr getBeginning();
    virtual RRsetCollectionBase::IterPtr getEnd();
};

} // end of namespace dns
} // end of namespace isc

#endif  // RRSET_COLLECTION_H

// Local Variables:
// mode: c++
// End:
