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

#ifndef ZONE_H
#define ZONE_H 1

#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrset_collection_base.h>

#include <datasrc/exceptions.h>
#include <datasrc/result.h>

#include <utility>

namespace isc {
namespace datasrc {

/// \brief A forward declaration
class ZoneFinder;

/// The base class to make updates to a single zone.
///
/// On construction, each derived class object will start a "transaction"
/// for making updates to a specific zone (this means a constructor of
/// a derived class would normally take parameters to identify the zone
/// to be updated).  The underlying realization of a "transaction" will differ
/// for different derived classes; if it uses a general purpose database
/// as a backend, it will involve performing some form of "begin transaction"
/// statement for the database.
///
/// Updates (adding or deleting RRs) are made via \c addRRset() and
/// \c deleteRRset() methods.  Until the \c commit() method is called the
/// changes are local to the updater object.  For example, they won't be
/// visible via a \c ZoneFinder object except the one returned by the
/// updater's own \c getFinder() method.  The \c commit() completes the
/// transaction and makes the changes visible to others.
///
/// This class does not provide an explicit "rollback" interface.  If
/// something wrong or unexpected happens during the updates and the
/// caller wants to cancel the intermediate updates, the caller should
/// simply destruct the updater object without calling \c commit().
/// The destructor is supposed to perform the "rollback" operation,
/// depending on the internal details of the derived class.
///
/// \note This initial implementation provides a quite simple interface of
/// adding and deleting RRs (see the description of the related methods).
/// It may be revisited as we gain more experiences.
class ZoneUpdater {
protected:
    /// The default constructor.
    ///
    /// This is intentionally defined as protected to ensure that this base
    /// class is never instantiated directly.
    ZoneUpdater() {}

public:
    /// The destructor
    ///
    /// Each derived class implementation must ensure that if \c commit()
    /// has not been performed by the time of the call to it, then it
    /// "rollbacks" the updates made via the updater so far.
    virtual ~ZoneUpdater() {}

    /// Return a finder for the zone being updated.
    ///
    /// The returned finder provides the functionalities of \c ZoneFinder
    /// for the zone as updates are made via the updater.  That is, before
    /// making any update, the finder will be able to find all RRsets that
    /// exist in the zone at the time the updater is created.  If RRsets
    /// are added or deleted via \c addRRset() or \c deleteRRset(),
    /// this finder will find the added ones or miss the deleted ones
    /// respectively.
    ///
    /// The finder returned by this method is effective only while the updates
    /// are performed, i.e., from the construction of the corresponding
    /// updater until \c commit() is performed or the updater is destructed
    /// without commit.  The result of a subsequent call to this method (or
    /// the use of the result) after that is undefined.
    ///
    /// \return A reference to a \c ZoneFinder for the updated zone
    virtual ZoneFinder& getFinder() = 0;

    /// Return an RRsetCollection for the updater.
    ///
    /// This method returns an \c RRsetCollection for the updater,
    /// implementing the \c isc::dns::RRsetCollectionBase
    /// interface. Typically, the returned \c RRsetCollection is a
    /// singleton for its \c ZoneUpdater. The returned RRsetCollection
    /// object must not be used after its corresponding \c ZoneUpdater
    /// has been destroyed. The returned RRsetCollection object may be
    /// used to search RRsets from the ZoneUpdater. The actual
    /// \c RRsetCollection returned has a behavior dependent on the
    /// \c ZoneUpdater implementation.
    ///
    /// The behavior of the RRsetCollection is similar to the behavior
    /// of the \c Zonefinder returned by \c getFinder().  In fact, it's
    /// redundant in a sense because one can implement the
    /// \c dns::RRsetCollectionBase interface using an updater and
    /// \c getFinder() interface (unless it's expected to support zone
    /// iteration, and the initial implementation of the \c RRsetCollection
    /// returned by this method doesn't support it).  We still provide it
    /// as an updater's method so it will be easier for an updater
    /// implementation to customize the \c RRsetCollection implementation,
    /// and also for making it easy to impose restrictions described below.
    ///
    /// Specific data sources may have special restrictions.  That's
    /// especially the case for database-based data sources.  Such
    /// restrictions may also result in limiting the usage of the
    /// \c RRsetCollection as described in the following paragraphs.  A
    /// specific updater implementation may provide more flexible
    /// behavior, but applications using this interface must assume
    /// the most restricted case unless it knows it uses a particular
    /// specialized updater implementation that loosens specific restrictions.
    ///
    /// To summarize the restrictions:
    /// - An application must not add or delete RRsets after
    ///   \c getRRsetCollection() is called.
    /// - An application must not use the returned collection from
    ///   \c getRRsetCollection() once \c commit() is called on the updater
    ///   that generates the collection.
    ///
    /// Implementations of \c ZoneUpdater may not allow adding or
    /// deleting RRsets after \c getRRsetCollection() is called. This is
    /// because if an iterator of the collection is being used at that time
    /// the modification to the zone may break an internal assumption of the
    /// iterator and may result in unexpected behavior.  Also, the iterator
    /// may conceptually hold a "reader lock" of the zone (in an implementation
    /// dependent manner), which would prevent the addition or deletion,
    /// surprising the caller (who would normally expect it to succeed).
    ///
    /// Implementations of \c ZoneUpdater may disable a previously returned
    /// \c RRsetCollection after \c commit() is called.  This is because
    /// the returned \c RRsetCollection may internally rely on the conceptual
    /// transaction of the updater that generates the collection (which would
    /// be literally the case for database-based data sources), and once
    /// the transaction is committed anything that relies on it won't be valid.
    /// If an \c RRsetCollection is disabled, using methods such as \c find()
    /// and using its iterator would cause an exception to be thrown. See
    /// \c isc::datasrc::RRsetCollectionBase for details.
    virtual isc::dns::RRsetCollectionBase& getRRsetCollection() = 0;

    /// Add an RRset to a zone via the updater
    ///
    /// This may be revisited in a future version, but right now the intended
    /// behavior of this method is simple: It "naively" adds the specified
    /// RRset to the zone specified on creation of the updater.
    /// It performs minimum level of validation on the specified RRset:
    /// - Whether the RR class is identical to that for the zone to be updated
    /// - Whether the RRset is not empty, i.e., it has at least one RDATA
    /// - Whether the RRset is not associated with an RRSIG, i.e.,
    ///   whether \c getRRsig() on the RRset returns a NULL pointer.
    ///
    /// and otherwise does not check any oddity.  For example, it doesn't
    /// check whether the owner name of the specified RRset is a subdomain
    /// of the zone's origin; it doesn't care whether or not there is already
    /// an RRset of the same name and RR type in the zone, and if there is,
    /// whether any of the existing RRs have duplicate RDATA with the added
    /// ones.  If these conditions matter the calling application must examine
    /// the existing data beforehand using the \c ZoneFinder returned by
    /// \c getFinder().
    ///
    /// The validation requirement on the associated RRSIG is temporary.
    /// If we find it more reasonable and useful to allow adding a pair of
    /// RRset and its RRSIG RRset as we gain experiences with the interface,
    /// we may remove this restriction.  Until then we explicitly check it
    /// to prevent accidental misuse.
    ///
    /// Conceptually, on successful call to this method, the zone will have
    /// the specified RRset, and if there is already an RRset of the same
    /// name and RR type, these two sets will be "merged".  "Merged" means
    /// that a subsequent call to \c ZoneFinder::find() for the name and type
    /// will result in success and the returned RRset will contain all
    /// previously existing and newly added RDATAs with the TTL being the
    /// minimum of the two RRsets.  The underlying representation of the
    /// "merged" RRsets may vary depending on the characteristic of the
    /// underlying data source.  For example, if it uses a general purpose
    /// database that stores each RR of the same RRset separately, it may
    /// simply be a larger sets of RRs based on both the existing and added
    /// RRsets; the TTLs of the RRs may be different within the database, and
    /// there may even be duplicate RRs in different database rows.  As long
    /// as the RRset returned via \c ZoneFinder::find() conforms to the
    /// concept of "merge", the actual internal representation is up to the
    /// implementation.
    ///
    /// This method must not be called once commit() is performed.  If it
    /// calls after \c commit() the implementation must throw a
    /// \c DataSourceError exception.
    ///
    /// Implementations of \c ZoneUpdater may not allow adding or
    /// deleting RRsets after \c getRRsetCollection() is called (see
    /// the description of \c getRRsetCollection()).  In this case,
    /// implementations throw an \c InvalidOperation exception.
    ///
    /// If journaling was requested when getting this updater, it will reject
    /// to add the RRset if the squence doesn't look like and IXFR (see
    /// DataSourceClient::getUpdater). In such case isc::BadValue is thrown.
    ///
    /// \todo As noted above we may have to revisit the design details as we
    /// gain experiences:
    ///
    /// - we may want to check (and maybe reject) if there is already a
    /// duplicate RR (that has the same RDATA).
    /// - we may want to check (and maybe reject) if there is already an
    /// RRset of the same name and RR type with different TTL
    /// - we may even want to check if there is already any RRset of the
    /// same name and RR type.
    /// - we may want to add an "options" parameter that can control the
    /// above points
    /// - we may want to have this method return a value containing the
    /// information on whether there's a duplicate, etc.
    ///
    /// \exception DataSourceError Called after \c commit(), RRset is invalid
    /// (see above), internal data source error
    /// \exception isc::BadValue Journaling is enabled and the current RRset
    ///   doesn't fit into the IXFR sequence (see above).
    /// \exception std::bad_alloc Resource allocation failure
    ///
    /// \param rrset The RRset to be added
    virtual void addRRset(const isc::dns::AbstractRRset& rrset) = 0;

    /// Delete an RRset from a zone via the updater
    ///
    /// Like \c addRRset(), the detailed semantics and behavior of this method
    /// may have to be revisited in a future version.  The following are
    /// based on the initial implementation decisions.
    ///
    /// On successful completion of this method, it will remove from the zone
    /// the RRs of the specified owner name and RR type that match one of
    /// the RDATAs of the specified RRset.  There are several points to be
    /// noted:
    /// - Existing RRs that don't match any of the specified RDATAs will
    ///   remain in the zone.
    /// - Any RRs of the specified RRset that doesn't exist in the zone will
    ///   simply be ignored; the implementation of this method is not supposed
    ///   to check that condition.
    /// - The TTL of the RRset is ignored; matching is only performed by
    ///   the owner name, RR type and RDATA
    ///
    /// Ignoring the TTL may not look sensible, but it's based on the
    /// observation that it will result in more intuitive result, especially
    /// when the underlying data source is a general purpose database.
    /// See also \c DatabaseAccessor::deleteRecordInZone() on this point.
    /// It also matches the dynamic update protocol (RFC2136), where TTLs
    /// are ignored when deleting RRs.
    ///
    /// \note Since the TTL is ignored, this method could take the RRset
    /// to be deleted as a tuple of name, RR type, and a list of RDATAs.
    /// But in practice, it's quite likely that the caller has the RRset
    /// in the form of the \c RRset object (e.g., extracted from a dynamic
    /// update request message), so this interface would rather be more
    /// convenient.  If it turns out not to be true we can change or extend
    /// the method signature.
    ///
    /// This method performs minimum level of validation on the specified
    /// RRset:
    /// - Whether the RR class is identical to that for the zone to be updated
    /// - Whether the RRset is not empty, i.e., it has at least one RDATA
    /// - Whether the RRset is not associated with an RRSIG, i.e.,
    ///   whether \c getRRsig() on the RRset returns a NULL pointer.
    ///
    /// This method must not be called once commit() is performed.  If it
    /// calls after \c commit() the implementation must throw a
    /// \c DataSourceError exception.
    ///
    /// Implementations of \c ZoneUpdater may not allow adding or
    /// deleting RRsets after \c getRRsetCollection() is called (see
    /// the description of \c getRRsetCollection()).  In this case,
    /// implementations throw an \c InvalidOperation exception.
    ///
    /// If journaling was requested when getting this updater, it will reject
    /// to add the RRset if the squence doesn't look like and IXFR (see
    /// DataSourceClient::getUpdater). In such case isc::BadValue is thrown.
    ///
    /// \todo As noted above we may have to revisit the design details as we
    /// gain experiences:
    ///
    /// - we may want to check (and maybe reject) if some or all of the RRs
    ///   for the specified RRset don't exist in the zone
    /// - we may want to allow an option to "delete everything" for specified
    ///   name and/or specified name + RR type.
    /// - as mentioned above, we may want to include the TTL in matching the
    ///   deleted RRs
    /// - we may want to add an "options" parameter that can control the
    ///   above points
    /// - we may want to have this method return a value containing the
    ///   information on whether there's any RRs that are specified but don't
    ///   exit, the number of actually deleted RRs, etc.
    ///
    /// \exception DataSourceError Called after \c commit(), RRset is invalid
    /// (see above), internal data source error
    /// \exception isc::BadValue Journaling is enabled and the current RRset
    ///   doesn't fit into the IXFR sequence (see above).
    /// \exception std::bad_alloc Resource allocation failure
    ///
    /// \param rrset The RRset to be deleted
    virtual void deleteRRset(const isc::dns::AbstractRRset& rrset) = 0;

    /// Commit the updates made in the updater to the zone
    ///
    /// This method completes the "transaction" started at the creation
    /// of the updater.  After successful completion of this method, the
    /// updates will be visible outside the scope of the updater.
    /// The actual internal behavior will defer for different derived classes.
    /// For a derived class with a general purpose database as a backend,
    /// for example, this method would perform a "commit" statement for the
    /// database.
    ///
    /// This operation can only be performed at most once.  A duplicate call
    /// must result in a DatasourceError exception.
    ///
    /// \exception DataSourceError Duplicate call of the method,
    /// internal data source error
    /// \exception isc::BadValue Journaling is enabled and the update is not
    ///    complete IXFR sequence.
    virtual void commit() = 0;
};

/// \brief A pointer-like type pointing to a \c ZoneUpdater object.
typedef boost::shared_ptr<ZoneUpdater> ZoneUpdaterPtr;

/// The base class for retrieving differences between two versions of a zone.
///
/// On construction, each derived class object will internally set up
/// retrieving sequences of differences between two specific version of
/// a specific zone managed in a particular data source.  So the constructor
/// of a derived class would normally take parameters to identify the zone
/// and the two versions for which the differences should be retrieved.
/// See \c DataSourceClient::getJournalReader for more concrete details
/// used in this API.
///
/// Once constructed, an object of this class will act like an iterator
/// over the sequences.  Every time the \c getNextDiff() method is called
/// it returns one element of the differences in the form of an \c RRset
/// until it reaches the end of the entire sequences.
class ZoneJournalReader {
public:
    /// Result codes used by a factory method for \c ZoneJournalReader
    enum Result {
        SUCCESS, ///< A \c ZoneJournalReader object successfully created
        NO_SUCH_ZONE, ///< Specified zone does not exist in the data source
        NO_SUCH_VERSION ///< Specified versions do not exist in the diff storage
    };

protected:
    /// The default constructor.
    ///
    /// This is intentionally defined as protected to ensure that this base
    /// class is never instantiated directly.
    ZoneJournalReader() {}

public:
    /// The destructor
    virtual ~ZoneJournalReader() {}

    /// Return the next difference RR of difference sequences.
    ///
    /// In this API, the difference between two versions of a zone is
    /// conceptually represented as IXFR-style difference sequences:
    /// Each difference sequence is a sequence of RRs: an older version of
    /// SOA (to be deleted), zero or more other deleted RRs, the
    /// post-transaction SOA (to be added), and zero or more other
    /// added RRs.  (Note, however, that the underlying data source
    /// implementation may or may not represent the difference in
    /// straightforward realization of this concept.  The mapping between
    /// the conceptual difference and the actual implementation is hidden
    /// in each derived class).
    ///
    /// This method provides an application with a higher level interface
    /// to retrieve the difference along with the conceptual model: the
    /// \c ZoneJournalReader object iterates over the entire sequences
    /// from the beginning SOA (which is to be deleted) to one of the
    /// added RR of with the ending SOA, and each call to this method returns
    /// one RR in the form of an \c RRset that contains exactly one RDATA
    /// in the order of the sequences.
    ///
    /// Note that the ordering of the sequences specifies the semantics of
    /// each difference: add or delete.  For example, the first RR is to
    /// be deleted, and the last RR is to be added.  So the return value
    /// of this method does not explicitly indicate whether the RR is to be
    /// added or deleted.
    ///
    /// This method ensures the returned \c RRset represents an RR, that is,
    /// it contains exactly one RDATA.  However, it does not necessarily
    /// ensure that the resulting sequences are in the form of IXFR-style.
    /// For example, the first RR is supposed to be an SOA, and it should
    /// normally be the case, but this interface does not necessarily require
    /// the derived class implementation ensure this.  Normally the
    /// differences are expected to be stored using this API (via a
    /// \c ZoneUpdater object), and as long as that is the case and the
    /// underlying implementation follows the requirement of the API, the
    /// result of this method should be a valid IXFR-style sequences.
    /// So this API does not mandate the almost redundant check as part of
    /// the interface.  If the application needs to make it sure 100%, it
    /// must check the resulting sequence itself.
    ///
    /// Once the object reaches the end of the sequences, this method returns
    /// \c Null.  Any subsequent call will result in an exception of
    /// class \c InvalidOperation.
    ///
    /// \exception InvalidOperation The method is called beyond the end of
    /// the difference sequences.
    /// \exception DataSourceError Underlying data is broken and the RR
    /// cannot be created or other low level data source error.
    ///
    /// \return An \c RRset that contains one RDATA corresponding to the
    /// next difference in the sequences.
    virtual isc::dns::ConstRRsetPtr getNextDiff() = 0;
};

/// \brief A pointer-like type pointing to a \c ZoneUpdater object.
typedef boost::shared_ptr<ZoneJournalReader> ZoneJournalReaderPtr;

} // end of datasrc
} // end of isc

#endif  // ZONE_H

// Local Variables:
// mode: c++
// End:
