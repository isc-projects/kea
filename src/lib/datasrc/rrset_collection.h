// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef RRSET_COLLECTION_DATASRC_H
#define RRSET_COLLECTION_DATASRC_H 1

#include <dns/rrset_collection_base.h>
#include <dns/rrclass.h>
#include <datasrc/zone.h>

namespace isc {
namespace datasrc {

/// \brief datasrc implementation of RRsetCollectionBase.
class RRsetCollection : public isc::dns::RRsetCollectionBase {
public:
    /// \brief Constructor.
    /// \param updater The ZoneUpdater to wrap around.
    RRsetCollection(ZoneUpdaterPtr updater) :
        updater_(updater)
    {}

    /// \brief Destructor
    virtual ~RRsetCollection() {}

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \returns The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                         const isc::dns::RRClass& rrclass,
                                         const isc::dns::RRType& rrtype) const;

private:
    ZoneUpdaterPtr updater_;

protected:
    class DsIter : public RRsetCollectionBase::Iter {
    public:
        DsIter()
        {}

        virtual const isc::dns::AbstractRRset& getValue() {
            isc_throw(isc::NotImplemented, "This method is not implemented.");
        }

        virtual IterPtr getNext() {
            isc_throw(isc::NotImplemented, "This method is not implemented.");
        }

        virtual bool equals(Iter& other) {
            const DsIter* other_real = dynamic_cast<DsIter*>(&other);
            if (other_real == NULL) {
                return (false);
            }

            isc_throw(isc::NotImplemented, "This method is not implemented.");
        }
    };

    virtual RRsetCollectionBase::IterPtr getBeginning();
    virtual RRsetCollectionBase::IterPtr getEnd();
};

} // end of namespace datasrc
} // end of namespace isc

#endif  // RRSET_COLLECTION_DATASRC_H

// Local Variables:
// mode: c++
// End:
