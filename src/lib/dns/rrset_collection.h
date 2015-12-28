// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    ///
    /// This constructor creates an empty collection without any data in
    /// it. RRsets can be added to the collection with the \c addRRset()
    /// method.
    RRsetCollection() {}

    /// \brief Constructor.
    ///
    /// The \c origin and \c rrclass arguments are required for the zone
    /// loading, but \c RRsetCollection itself does not do any
    /// validation, and the collection of RRsets does not have to form a
    /// valid zone.
    ///
    /// \throws MasterLoaderError if there is an error during loading.
    /// \param filename Name of a file containing a collection of RRs in
    /// the master file format (which may or may not form a valid zone).
    /// \param origin The zone origin.
    /// \param rrclass The zone class.
    RRsetCollection(const char* filename, const isc::dns::Name& origin,
                    const isc::dns::RRClass& rrclass);

    /// \brief Constructor.
    ///
    /// This constructor is similar to the previous one, but instead of
    /// taking a filename to load a zone from, it takes an input
    /// stream.
    ///
    /// \throws MasterLoaderError if there is an error during loading.
    /// \param input_stream The input stream to load from.
    /// \param origin The zone origin.
    /// \param rrclass The zone class.
    RRsetCollection(std::istream& input_stream, const isc::dns::Name& origin,
                    const isc::dns::RRClass& rrclass);

    /// \brief Destructor
    virtual ~RRsetCollection() {}

    /// \brief Add an RRset to the collection.
    ///
    /// Does not do any validation whether \c rrset belongs to a
    /// particular zone or not. A reference to \c rrset is taken in an
    /// internally managed \c shared_ptr, so even if the caller's
    /// \c RRsetPtr is destroyed, the RRset it wrapped is still alive
    /// and managed by the \c RRsetCollection. It throws an
    /// \c isc::InvalidParameter exception if an rrset with the same
    /// class, type and name already exists.
    ///
    /// Callers must not modify the RRset after adding it to the
    /// collection, as the rrset is indexed internally by the
    /// collection.
    void addRRset(isc::dns::RRsetPtr rrset);

    /// \brief Remove an RRset from the collection.
    ///
    /// RRset(s) matching the \c name, \c rrclass and \c rrtype are
    /// removed from the collection.
    ///
    /// \return \c true if a matching RRset was deleted, \c false if no
    /// such RRset exists.
    bool removeRRset(const isc::dns::Name& name,
                     const isc::dns::RRClass& rrclass,
                     const isc::dns::RRType& rrtype);

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \return The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                         const isc::dns::RRClass& rrclass,
                                         const isc::dns::RRType& rrtype) const;

    /// \brief Find a matching RRset in the collection (non-const
    /// variant).
    ///
    /// See above for a description of the method and arguments.
    isc::dns::RRsetPtr find(const isc::dns::Name& name,
                            const isc::dns::RRClass& rrclass,
                            const isc::dns::RRType& rrtype);

private:
    template<typename T>
    void constructHelper(T source, const isc::dns::Name& origin,
                         const isc::dns::RRClass& rrclass);
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
            ++it;
            return (RRsetCollectionBase::IterPtr(new DnsIter(it)));
        }

        virtual bool equals(Iter& other) {
            const DnsIter* other_real = dynamic_cast<DnsIter*>(&other);
            if (other_real == NULL) {
                return (false);
            }
            return (iter_ == other_real->iter_);
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
