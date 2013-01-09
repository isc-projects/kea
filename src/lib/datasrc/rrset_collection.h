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
    ///
    /// A reference to the \c updater (via \c shared_ptr) is taken when
    /// the collection is constructed. As long as the collection object
    /// is alive, the reference to the updater is kept and it cannot be
    /// destroyed by the client.
    ///
    /// \param updater The ZoneUpdater to wrap around.
    /// \param rrclass The RRClass of the records in the zone.
    RRsetCollection(ZoneUpdaterPtr updater, const isc::dns::RRClass& rrclass) :
        updater_(updater),
        rrclass_(rrclass)
    {}

    /// \brief Destructor
    virtual ~RRsetCollection() {}

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// \throw FindError if find() results in some underlying datasrc error.
    /// \param name The name of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \returns The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                         const isc::dns::RRClass& rrclass,
                                         const isc::dns::RRType& rrtype) const;

private:
    ZoneUpdaterPtr updater_;
    isc::dns::RRClass rrclass_;

protected:
    // TODO: RRsetCollectionBase::Iter is not implemented and the
    // following two methods just throw.

    virtual RRsetCollectionBase::IterPtr getBeginning();
    virtual RRsetCollectionBase::IterPtr getEnd();
};

} // end of namespace datasrc
} // end of namespace isc

#endif  // RRSET_COLLECTION_DATASRC_H

// Local Variables:
// mode: c++
// End:
