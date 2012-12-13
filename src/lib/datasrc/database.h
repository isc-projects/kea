// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATABASE_DATASRC_H
#define DATABASE_DATASRC_H

#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include <datasrc/data_source.h>
#include <datasrc/client.h>
#include <datasrc/zone.h>
#include <datasrc/logger.h>

#include <dns/name.h>
#include <exceptions/exceptions.h>

#include <map>
#include <set>

namespace isc {
namespace datasrc {

/// \brief Abstraction of lowlevel database with DNS data
///
/// This class is defines interface to databases. Each supported database
/// will provide methods for accessing the data stored there in a generic
/// manner. The methods are meant to be low-level, without much or any knowledge
/// about DNS and should be possible to translate directly to queries.
///
/// On the other hand, how the communication with database is done and in what
/// schema (in case of relational/SQL database) is up to the concrete classes.
///
/// This class is non-copyable, as copying connections to database makes little
/// sense and will not be needed.
///
/// \todo Is it true this does not need to be copied? For example the zone
///     iterator might need it's own copy. But a virtual clone() method might
///     be better for that than copy constructor.
///
/// \note The same application may create multiple connections to the same
///     database, having multiple instances of this class. If the database
///     allows having multiple open queries at one connection, the connection
///     class may share it.
class DatabaseAccessor : boost::noncopyable {
public:
    /// \brief Data columns for by IteratorContext::getNext()
    ///
    /// When implementing getNext(), the columns array should be filled with
    /// the values as described in this enumeration, in this order, i.e.
    /// - TYPE_COLUMN should be the first element (index 0) of the array,
    /// - TTL_COLUMN should be the second element (index 1),
    /// - etc.
    enum RecordColumns {
        TYPE_COLUMN = 0,    ///< The RRType of the record (A/NS/TXT etc.)
        TTL_COLUMN = 1,     ///< The TTL of the record (a
        SIGTYPE_COLUMN = 2, ///< For RRSIG records, this contains the RRTYPEs
                            ///< the RRSIG cover. In the current implementation,
                            ///< this field is ignored.
        RDATA_COLUMN = 3,   ///< Full text representation of the record's RDATA
        NAME_COLUMN = 4,    ///< The domain name of this RR
        COLUMN_COUNT = 5    ///< The total number of columns, MUST be value of
                            ///< the largest other element in this enum plus 1.
    };

    /// \brief Definitions of the fields to be passed to addRecordToZone()
    ///
    /// Each derived implementation of addRecordToZone() should expect
    /// the "columns" array to be filled with the values as described in this
    /// enumeration, in this order.
    enum AddRecordColumns {
        ADD_NAME = 0,       ///< The owner name of the record (a domain name)
        ADD_REV_NAME = 1,   ///< Reversed name of NAME (used for DNSSEC)
        ADD_TTL = 2,        ///< The TTL of the record (in numeric form)
        ADD_TYPE = 3,       ///< The RRType of the record (A/NS/TXT etc.)
        ADD_SIGTYPE = 4,    ///< RRSIGs only: RRTYPEs the RRSIG covers.
        ADD_RDATA = 5,      ///< Full text representation of the record's RDATA
        ADD_COLUMN_COUNT = 6 ///< Number of columns
    };

    /// \brief Definitions of the fields to be passed to addNSEC3RecordToZone()
    ///
    /// Each derived implementation of addNSEC3RecordToZone() should expect
    /// the "columns" array to be filled with the values as described in this
    /// enumeration, in this order.
    ///
    /// Note that there is no "reversed name" column.  Since the conceptual
    /// separate namespace for NSEC3 is very simplified and essentially only
    /// consists of a single-label names, there is no need for using reversed
    /// names to identify the "previous hash".
    enum AddNSEC3RecordColumns {
        ADD_NSEC3_HASH = 0, ///< The hash (1st) label of the owner name,
                            ///< excluding the dot character
        ADD_NSEC3_TTL = 1,  ///< The TTL of the record (in numeric form)
        ADD_NSEC3_TYPE = 2, ///< The RRType of the record (either NSEC3 or
                            ///< RRSIG for NSEC3)
        ADD_NSEC3_RDATA = 3, ///< Full text representation of the record's
                             ///< RDATA
        ADD_NSEC3_COLUMN_COUNT = 4 ///< Number of columns
    };

    /// \brief Definitions of the fields to be passed to deleteRecordInZone()
    /// and deleteNSEC3RecordInZone()
    ///
    /// Each derived implementation of deleteRecordInZone() should expect
    /// the "params" array to be filled with the values as described in this
    /// enumeration, in this order.
    enum DeleteRecordParams {
        DEL_NAME = 0, ///< The owner name of the record (a domain name)
                      ///< or the hash label for deleteNSEC3RecordInZone()
        DEL_TYPE = 1, ///< The RRType of the record (A/NS/TXT etc.)
        DEL_RDATA = 2, ///< Full text representation of the record's RDATA
        DEL_PARAM_COUNT = 3 ///< Number of parameters
    };

    /// \brief Operation mode when adding a record diff.
    ///
    /// This is used as the "operation" parameter value of addRecordDiff().
    enum DiffOperation {
        DIFF_ADD = 0,           ///< This diff is for adding an RR
        DIFF_DELETE = 1         ///< This diff is for deleting an RR
    };

    /// \brief Definitions of the fields to be passed to addRecordDiff().
    ///
    /// Each derived implementation of addRecordDiff() should expect
    /// the "params" array to be filled with the values as described in this
    /// enumeration, in this order.
    enum DiffRecordParams {
        DIFF_NAME = 0,          ///< Owner name of the record (a domain name)
        DIFF_TYPE = 1,          ///< The RRType of the record (A/NS/TXT etc.)
        DIFF_TTL = 2,           ///< The TTL of the record (in numeric form)
        DIFF_RDATA = 3,         ///< Full text representation of record's RDATA
        DIFF_PARAM_COUNT = 4    ///< Number of parameters
    };

    /// \brief Destructor
    ///
    /// It is empty, but needs a virtual one, since we will use the derived
    /// classes in polymorphic way.
    virtual ~DatabaseAccessor() { }

    /// \brief Retrieve a zone identifier
    ///
    /// This method looks up a zone for the given name in the database. It
    /// should match only exact zone name (eg. name is equal to the zone's
    /// apex), as the DatabaseClient will loop trough the labels itself and
    /// find the most suitable zone.
    ///
    /// It is not specified if and what implementation of this method may throw,
    /// so code should expect anything.
    ///
    /// \param name The (fully qualified) domain name of the zone's apex to be
    ///             looked up.
    /// \return The first part of the result indicates if a matching zone
    ///     was found. In case it was, the second part is internal zone ID.
    ///     This one will be passed to methods finding data in the zone.
    ///     It is not required to keep them, in which case whatever might
    ///     be returned - the ID is only passed back to the database as
    ///     an opaque handle.
    virtual std::pair<bool, int> getZone(const std::string& name) const = 0;

    /// \brief Add a new zone to the database
    ///
    /// This method creates a new (and empty) zone in the database.
    ///
    /// Like for addRecordToZone, implementations are not required to
    /// check for the existence of the given zone name, it is the
    /// responsibility of the caller to do so.
    ///
    /// Callers must also start a transaction before calling this method,
    /// implementations should throw DataSourceError if this has not been
    /// done. Callers should also expect DataSourceErrors for other potential
    /// problems.
    ///
    /// \param name The (fully qualified) domain name of the zone to add.
    /// \return The internal zone id of the zone (whether is existed already
    ///         or was created by this call).
    virtual int addZone(const std::string& name) = 0;

    /// \brief This holds the internal context of ZoneIterator for databases
    ///
    /// While the ZoneIterator implementation from DatabaseClient does all the
    /// translation from strings to DNS classes and validation, this class
    /// holds the pointer to where the database is at reading the data.
    ///
    /// It can either hold shared pointer to the connection which created it
    /// and have some kind of statement inside (in case single database
    /// connection can handle multiple concurrent SQL statements) or it can
    /// create a new connection (or, if it is more convenient, the connection
    /// itself can inherit both from DatabaseConnection and IteratorContext
    /// and just clone itself).
    class IteratorContext : public boost::noncopyable {
    public:
        /// \brief Destructor
        ///
        /// Virtual destructor, so any descendand class is destroyed correctly.
        virtual ~IteratorContext() { }

        /// \brief Function to provide next resource record
        ///
        /// This function should provide data about the next resource record
        /// from the data that is searched. The data is not converted yet.
        ///
        /// Depending on how the iterator was constructed, there is a difference
        /// in behaviour; for a 'full zone iterator', created with
        /// getAllRecords(), all COLUMN_COUNT elements of the array are
        /// overwritten.
        /// For a 'name iterator', created with getRecords(), the column
        /// NAME_COLUMN is untouched, since what would be added here is by
        /// definition already known to the caller (it already passes it as
        /// an argument to getRecords()).
        ///
        /// Once this function returns false, any subsequent call to it should
        /// result in false.  The implementation of a derived class must ensure
        /// it doesn't cause any disruption due to that such as a crash or
        /// exception.
        ///
        /// \note The order of RRs is not strictly set, but the RRs for single
        /// RRset must not be interleaved with any other RRs (eg. RRsets must be
        /// "together").
        ///
        /// \param columns The data will be returned through here. The order
        ///     is specified by the RecordColumns enum, and the size must be
        ///     COLUMN_COUNT
        /// \todo Do we consider databases where it is stored in binary blob
        ///     format?
        /// \throw DataSourceError if there's database-related error. If the
        ///     exception (or any other in case of derived class) is thrown,
        ///     the iterator can't be safely used any more.
        /// \return true if a record was found, and the columns array was
        ///         updated. false if there was no more data, in which case
        ///         the columns array is untouched.
        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) = 0;
    };

    typedef boost::shared_ptr<IteratorContext> IteratorContextPtr;

    /// \brief Creates an iterator context for a specific name.
    ///
    /// Returns an IteratorContextPtr that contains all records of the
    /// given name from the given zone.
    ///
    /// The implementation of the iterator that is returned may leave the
    /// NAME_COLUMN column of the array passed to getNext() untouched, as that
    /// data is already known (it is the same as the name argument here)
    ///
    /// \exception any Since any implementation can be used, the caller should
    ///            expect any exception to be thrown.
    ///
    /// \param name The name to search for. This should be a FQDN.
    /// \param id The ID of the zone, returned from getZone().
    /// \param subdomains If set to true, match subdomains of name instead
    ///     of name itself. It is used to find empty domains and match
    ///     wildcards.
    /// \return Newly created iterator context. Must not be NULL.
    virtual IteratorContextPtr getRecords(const std::string& name,
                                          int id,
                                          bool subdomains = false) const = 0;

    /// \brief Creates an iterator context for the records of NSEC3 namespace
    ///     for the given hash
    ///
    /// Returns an Iteratorcontextptr that contains all the records of the given
    /// hash in the NSEC3 namespace of the given zone.
    ///
    /// The implementation of the iterator that is returned may leave the
    /// NAME_COLUMN column of the array passed to getNext() untouched,
    /// as that name is easy to construct on the caller side (both the
    /// hash and the name of the zone is known). The SIGTYPE_COLUMN can
    /// be omitted as well, as it would be always empty for NSEC3 RRs or
    /// contained "NSEC3" in case of RRSIG RRs.
    ///
    /// The iterator will contain both the NSEC3 records and the corresponding
    /// RRSIGs, in arbitrary order.
    ///
    /// The iterator might be empty (containing no RRs) in case the zone is not
    /// signed by NSEC3.
    ///
    /// \note In case there are multiple NSEC3 chains and they collide
    ///     (unlikely, but it can happen), this can return multiple NSEC3
    ///     records.
    /// \exception any Since any implementaion can be used, the caller should
    ///     expect any exception to be thrown.
    /// \exception isc::NotImplemented in case the database does not support
    ///     NSEC3
    ///
    /// \param hash The hash part of the NSEC3 name (eg. for a name of NSEC3
    ///     RKBUCQT8T78GV6QBCGBHCHC019LG73SJ.example.com., we the hash would be
    ///     RKBUCQT8T78GV6QBCGBHCHC019LG73SJ).
    /// \param id The id of te zone, as returned from getZone().
    /// \return Newly created iterator context. Must not be NULL.
    virtual IteratorContextPtr getNSEC3Records(const std::string& hash,
                                               int id) const = 0;

    /// \brief Creates an iterator context for the whole zone.
    ///
    /// Returns an IteratorContextPtr that contains all records of the
    /// zone with the given zone id.
    ///
    /// Each call to getNext() on the returned iterator should copy all
    /// column fields of the array that is passed, as defined in the
    /// RecordColumns enum.
    ///
    /// \exception any Since any implementation can be used, the caller should
    ///            expect any exception to be thrown.
    ///
    /// \param id The ID of the zone, returned from getZone().
    /// \return Newly created iterator context. Must not be NULL.
    virtual IteratorContextPtr getAllRecords(int id) const = 0;

    /// \brief Creates an iterator context for a set of differences.
    ///
    /// Returns an IteratorContextPtr that contains all difference records for
    /// the given zone between two versions of a zone.
    ///
    /// The difference records are the set of records that would appear in an
    /// IXFR serving a request for the difference between two versions of a
    /// zone.  The records are returned in the same order as they would be in
    /// the IXFR.  This means that if the the difference between versions of a
    /// zone with SOA serial numbers of "start" and "end" is required, and the
    /// zone contains the differences between serial number "start" to serial
    /// number "intermediate" and from serial number "intermediate" to serial
    /// number "end", the returned records will be (in order):
    ///
    /// \li SOA for serial "start"
    /// \li Records removed from the zone between versions "start" and
    ///     "intermediate" of the zone.  The order of these is not guaranteed.
    /// \li SOA for serial "intermediate"
    /// \li Records added to the zone between versions "start" and
    ///     "intermediate" of the zone.  The order of these is not guaranteed.
    /// \li SOA for serial "intermediate"
    /// \li Records removed from the zone between versions "intermediate" and
    ///     "end" of the zone.  The order of these is not guaranteed.
    /// \li SOA for serial "end"
    /// \li Records added to the zone between versions "intermediate" and "end"
    ///     of the zone. The order of these is not guaranteed.
    ///
    /// Note that there is no requirement that "start" be less than "end".
    /// Owing to serial number arithmetic, it is entirely possible that a later
    /// version of a zone will have a smaller SOA serial number than an earlier
    /// version.
    ///
    /// Each call to getNext() on the returned iterator should copy all column
    /// fields of the array that is passed, as defined in the RecordColumns
    /// enum.
    ///
    /// \exception any Since any implementation can be used, the caller should
    ///                expect any exception to be thrown.
    ///
    /// \param id The ID of the zone, returned from getZone().
    /// \param start The SOA serial number of the version of the zone from
    ///        which the difference sequence should start.
    /// \param end The SOA serial number of the version of the zone at which
    ///        the difference sequence should end.
    ///
    /// \return Newly created iterator context. Must not be NULL.
    virtual IteratorContextPtr
    getDiffs(int id, uint32_t start, uint32_t end) const = 0;

    /// \brief Start a transaction for updating a zone.
    ///
    /// Each derived class version of this method starts a database
    /// transaction to make updates to the given name of zone (whose class was
    /// specified at the construction of the class).
    ///
    /// If \c replace is true, any existing records of the zone will be
    /// deleted on successful completion of updates (after
    /// \c commitUpdateZone()); if it's false, the existing records will be
    /// intact unless explicitly deleted by \c deleteRecordInZone().
    ///
    /// A single \c DatabaseAccessor instance can perform at most one
    /// transaction; a duplicate call to this method before
    /// \c commitUpdateZone() or \c rollbackUpdateZone(), or a call to this
    /// method within another transaction started by \c startTransaction()
    /// will result in a \c DataSourceError exception.
    /// If multiple update attempts need to be performed concurrently (and
    /// if the underlying database allows such operation), separate
    /// \c DatabaseAccessor instance must be created.
    ///
    /// \note The underlying database may not allow concurrent updates to
    /// the same database instance even if different "connections" (or
    /// something similar specific to the database implementation) are used
    /// for different sets of updates.  For example, it doesn't seem to be
    /// possible for SQLite3 unless different databases are used.  MySQL
    /// allows concurrent updates to different tables of the same database,
    /// but a specific operation may block others.  As such, this interface
    /// doesn't require derived classes to allow concurrent updates with
    /// multiple \c DatabaseAccessor instances; however, the implementation
    /// is encouraged to do the best for making it more likely to succeed
    /// as long as the underlying database system allows concurrent updates.
    ///
    /// This method returns a pair of \c bool and \c int.  Its first element
    /// indicates whether the given name of zone is found.  If it's false,
    /// the transaction isn't considered to be started; a subsequent call to
    /// this method with an existing zone name should succeed.  Likewise,
    /// if a call to this method results in an exception, the transaction
    /// isn't considered to be started.  Note also that if the zone is not
    /// found this method doesn't try to create a new one in the database.
    /// It must have been created by some other means beforehand.
    ///
    /// The second element is the internal zone ID used for subsequent
    /// updates.  Depending on implementation details of the actual derived
    /// class method, it may be different from the one returned by
    /// \c getZone(); for example, a specific implementation may use a
    /// completely new zone ID when \c replace is true.
    ///
    /// \exception DataSourceError Duplicate call to this method, call to
    /// this method within another transaction, or some internal database
    /// related error.
    ///
    /// \param zone_name A string representation of the zone name to be updated
    /// \param replace Whether to replace the entire zone (see above)
    ///
    /// \return A pair of bool and int, indicating whether the specified zone
    /// exists and (if so) the zone ID to be used for the update, respectively.
    virtual std::pair<bool, int> startUpdateZone(const std::string& zone_name,
                                                 bool replace) = 0;

    /// \brief Add a single record to the zone to be updated.
    ///
    /// This method provides a simple interface to insert a new record
    /// (a database "row") to the zone in the update context started by
    /// \c startUpdateZone().  The zone to which the record to be added
    /// is the one specified at the time of the \c startUpdateZone() call.
    ///
    /// A successful call to \c startUpdateZone() must have preceded to
    /// this call; otherwise a \c DataSourceError exception will be thrown.
    ///
    /// The row is defined as a vector of strings that has exactly
    /// ADD_COLUMN_COUNT number of elements.  See AddRecordColumns for
    /// the semantics of each element.
    ///
    /// Derived class methods are not required to check whether the given
    /// values in \c columns are valid in terms of the expected semantics;
    /// in general, it's the caller's responsibility.
    /// For example, TTLs would normally be expected to be a textual
    /// representation of decimal numbers, but this interface doesn't require
    /// the implementation to perform this level of validation.  It may check
    /// the values, however, and in that case if it detects an error it
    /// should throw a \c DataSourceError exception.
    ///
    /// Likewise, derived class methods are not required to detect any
    /// duplicate record that is already in the zone.
    ///
    /// \note The underlying database schema may not have a trivial mapping
    /// from this style of definition of rows to actual database records.
    /// It's the implementation's responsibility to implement the mapping
    /// in the actual derived method.
    ///
    /// \exception DataSourceError Invalid call without starting a transaction,
    /// or other internal database error.
    ///
    /// \param columns An array of strings that defines a record to be added
    /// to the zone.
    virtual void addRecordToZone(
        const std::string (&columns)[ADD_COLUMN_COUNT]) = 0;

    /// \brief Add a single NSEC3-related record to the zone to be updated.
    ///
    /// This method is similar to \c addRecordToZone(), but is expected to
    /// be only used for NSEC3 RRs or RRSIG RRs that cover NSEC3.  In terms
    /// of the DNS protocol, these types of RRs reside in a separate space
    /// of the zone.  While this interface does not mandate a specific way
    /// of implementing the separate namespaces in the underlying database,
    /// it would be more convenient for the underlying implementation if the
    /// interfaces are separated; for example, the implementation does not
    /// have to examine the given data to identify the appropriate namespace.
    ///
    /// An implementation may choose to skip providing this interface if the
    /// zones managed by that data source are known to not support NSEC3.
    /// In that case the implementation should throw the
    /// \c isc::NotImplemented exception.
    ///
    /// Note that the \c ADD_NSEC3_HASH column of \c columns is expected to
    /// store only the hash label, not the entire owner name.  This is similar
    /// to the \c hash parameter of \c getNSEC3Records().
    ///
    /// The RRs to be added using this method are expected to be limited to
    /// NSEC3 or RRSIG RRs that cover NSEC3, but it's generally assumed to
    /// be the caller's responsibility to ensure that; the implementation
    /// is not required to check that condition.  The result of adding
    /// unexpected type of RRs (and the result of subsequent lookups) is
    /// undefined.
    ///
    /// Other general notes for \c addRecordToZone() also apply to this
    /// method.
    ///
    /// \exception DataSourceError Invalid call without starting a transaction,
    /// or other internal database error.
    /// \exception isc::NotImplemented in case the database does not support
    ///     NSEC3
    ///
    /// \param columns An array of strings that defines a record to be added
    /// to the NSEC3 namespace of the zone.
    virtual void addNSEC3RecordToZone(
        const std::string (&columns)[ADD_NSEC3_COLUMN_COUNT]) = 0;

    /// \brief Delete a single record from the zone to be updated.
    ///
    /// This method provides a simple interface to delete a record
    /// (a database "row") from the zone in the update context started by
    /// \c startUpdateZone().  The zone from which the record to be deleted
    /// is the one specified at the time of the \c startUpdateZone() call.
    ///
    /// A successful call to \c startUpdateZone() must have preceded to
    /// this call; otherwise a \c DataSourceError exception will be thrown.
    ///
    /// The record to be deleted is specified by a vector of strings that has
    /// exactly DEL_PARAM_COUNT number of elements.  See DeleteRecordParams
    /// for the semantics of each element.
    ///
    /// \note In IXFR, TTL may also be specified, but we intentionally
    /// ignore that in this interface, because it's not guaranteed
    /// that all records have the same TTL (unlike the RRset
    /// assumption) and there can even be multiple records for the
    /// same name, type and rdata with different TTLs.  If we only
    /// delete one of them, subsequent lookup will still return a
    /// positive answer, which would be confusing.  It's a higher
    /// layer's responsibility to check if there is at least one
    /// record in the database that has the given TTL.
    ///
    /// Like \c addRecordToZone, derived class methods are not required to
    /// validate the semantics of the given parameters or to check if there
    /// is a record that matches the specified parameter; if there isn't
    /// it simply ignores the result.
    ///
    /// \exception DataSourceError Invalid call without starting a transaction,
    /// or other internal database error.
    ///
    /// \param params An array of strings that defines a record to be deleted
    /// from the zone.
    virtual void deleteRecordInZone(
        const std::string (&params)[DEL_PARAM_COUNT]) = 0;

    /// \brief Delete a single NSEC3-related record from the zone to be
    /// updated.
    ///
    /// This method is similar to \c deleteRecordInZone(), but is expected to
    /// be only used for NSEC3 RRs or RRSIG RRs that cover NSEC3.  The
    /// relationship between these two methods is similar to that between
    /// \c addRecordToZone() and \c addNSEC3RecordToZone(), and the same
    /// notes apply to this method.
    ///
    /// This method uses the same set of parameters to specify the record
    /// to be deleted as \c deleteRecordInZone(), but the \c DEL_NAME column
    /// is expected to only store the hash label of the owner name.
    /// This is the same as \c ADD_NSEC3_HASH column for
    /// \c addNSEC3RecordToZone().
    ///
    /// \exception DataSourceError Invalid call without starting a transaction,
    /// or other internal database error.
    /// \exception isc::NotImplemented in case the database does not support
    ///     NSEC3
    ///
    /// \param params An array of strings that defines a record to be deleted
    /// from the NSEC3 namespace of the zone.
    virtual void deleteNSEC3RecordInZone(
        const std::string (&params)[DEL_PARAM_COUNT]) = 0;

    /// \brief Start a general transaction.
    ///
    /// Each derived class version of this method starts a database
    /// transaction in a way specific to the database details.  Any subsequent
    /// operations on the accessor are guaranteed to be not susceptible to
    /// any update attempts made during the transaction.  The transaction
    /// must be terminated by either \c commit() or \c rollback().
    ///
    /// In practice, this transaction is intended to be used to perform
    /// a set of atomic reads and work as a read-only lock.  So, in many
    /// cases \c commit() and \c rollback() will have the same effect.
    ///
    /// This transaction cannot coexist with an update transaction started
    /// by \c startUpdateZone().  Such an attempt will result in
    /// \c DataSourceError.
    ///
    /// \exception DataSourceError An attempt of nested transaction, or some
    /// internal database related error.
    virtual void startTransaction() = 0;

    /// \brief Commit a transaction.
    ///
    /// This method completes a transaction started by \c startTransaction
    /// or \c startUpdateZone.
    ///
    /// A successful call to one of the "start" methods must have preceded to
    /// this call; otherwise a \c DataSourceError exception will be thrown.
    /// Once this method successfully completes, the transaction isn't
    /// considered to exist any more.  So a new transaction can now be
    /// started.  On the other hand, a duplicate call to this method after
    /// a successful completion of it is invalid and should result in
    /// a \c DataSourceError exception.
    ///
    /// If some internal database error happens, a \c DataSourceError
    /// exception must be thrown.  In that case the transaction is still
    /// considered to be valid; the caller must explicitly rollback it
    /// or (if it's confident that the error is temporary) try to commit it
    /// again.
    ///
    /// \exception DataSourceError Call without a transaction, duplicate call
    /// to the method or internal database error.
    virtual void commit() = 0;

    /// \brief Rollback any changes in a transaction made so far.
    ///
    /// This method rollbacks a transaction started by \c startTransaction or
    /// \c startUpdateZone.  When it succeeds (it normally should, but see
    /// below), the underlying database should be reverted to the point
    /// before performing the corresponding "start" method.
    ///
    /// A successful call to one of the "start" method must have preceded to
    /// this call; otherwise a \c DataSourceError exception will be thrown.
    /// Once this method successfully completes, the transaction isn't
    /// considered to exist any more.  So a new transaction can now be
    /// started.  On the other hand, a duplicate call to this method after
    /// a successful completion of it is invalid and should result in
    /// a \c DataSourceError exception.
    ///
    /// Normally this method should not fail.  But it may not always be
    /// possible to guarantee it depending on the characteristics of the
    /// underlying database system.  So this interface doesn't require the
    /// actual implementation for the error free property.  But if a specific
    /// implementation of this method can fail, it is encouraged to document
    /// when that can happen with its implication.
    ///
    /// \exception DataSourceError Call without a transaction, duplicate call
    /// to the method or internal database error.
    virtual void rollback() = 0;

    /// \brief Install a single RR diff in difference sequences for zone update.
    ///
    /// This method inserts parameters of an update operation for a single RR
    /// (either adding or deleting one) in the underlying database.
    /// (These parameters would normally be a separate database table, but
    /// actual realization can differ in specific implementations).
    /// The information given via this method generally corresponds to either
    /// a single call to \c addRecordToZone() or \c deleteRecordInZone(),
    /// and this method is expected to be called immediately after (or before)
    /// a call to either of those methods.
    ///
    /// Note, however, that this method passes more detailed information
    /// than those update methods: it passes "serial", even if the diff
    /// is not for the SOA RR; it passes TTL for a diff that deletes an RR
    /// while in \c deleteRecordInZone() it's omitted.  This is because
    /// the stored diffs are expected to be retrieved in the form that
    /// \c getDiffs() is expected to meet.  This means if the caller
    /// wants to use this method with other update operations, it must
    /// ensure the additional information is ready when this method is called.
    ///
    /// The caller of this method must ensure that the added diffs via
    /// this method in a single transaction form an IXFR-style difference
    /// sequences: Each difference sequence is a sequence of RRs:
    /// an older version of SOA (to be deleted), zero or more other deleted
    /// RRs, the post-transaction SOA (to be added), and zero or more other
    /// added RRs.  So, for example, the first call to this method in a
    /// transaction must always be deleting an SOA.  Also, the \c serial
    /// parameter must be equal to the value of the serial field of the
    /// SOA that was last added or deleted (if the call is to add or delete
    /// an SOA RR, \c serial must be identical to the serial of that SOA).
    /// The underlying derived class implementation may or may not check
    /// this condition, but if the caller doesn't meet the condition
    /// a subsequent call to \c getDiffs() will not work as expected.
    ///
    /// Any call to this method must be in a transaction, and, for now,
    /// it must be a transaction triggered by \c startUpdateZone() (that is,
    /// it cannot be a transaction started by \c startTransaction()).
    /// All calls to this method are considered to be part of an atomic
    /// transaction: Until \c commit() is performed, the added diffs are
    /// not visible outside the transaction; if \c rollback() is performed,
    /// all added diffs are canceled; and the added sequences are not
    /// affected by any concurrent attempt of adding diffs (conflict resolution
    /// is up to the database implementation).
    ///
    /// Also for now, all diffs are assumed to be for the zone that is
    /// being updated in the context of \c startUpdateZone().  So the
    /// \c zone_id parameter must be identical to the zone ID returned by
    /// \c startUpdateZone().
    ///
    /// In a future version we may loosen this condition so that diffs can be
    /// added in a generic transaction and may not even have to belong to
    /// a single zone.  For this possible extension \c zone_id parameter is
    /// included even if it's redundant under the current restriction.
    ///
    /// The support for adding (or retrieving) diffs is optional; if it's
    /// not supported in a specific data source, this method for the
    /// corresponding derived class will throw an \c NotImplemented exception.
    ///
    /// \exception DataSourceError Invalid call without starting a transaction,
    /// zone ID doesn't match the zone being updated, or other internal
    /// database error.
    /// \exception NotImplemented Adding diffs is not supported in the
    /// data source.
    /// \exception Other The concrete derived method may throw other
    /// data source specific exceptions.
    ///
    /// \param zone_id The zone for the diff to be added.
    /// \param serial The SOA serial to which the diff belongs.
    /// \param operation Either \c DIFF_ADD or \c DIFF_DELETE.
    /// \param params An array of strings that defines a record for the diff.
    virtual void addRecordDiff(
        int zone_id, uint32_t serial, DiffOperation operation,
        const std::string (&params)[DIFF_PARAM_COUNT]) = 0;

    /// \brief Clone the accessor with the same configuration.
    ///
    /// Each derived class implementation of this method will create a new
    /// accessor of the same derived class with the same configuration
    /// (such as the database server address) as that of the caller object
    /// and return it.
    ///
    /// Note that other internal states won't be copied to the new accessor
    /// even though the name of "clone" may indicate so.  For example, even
    /// if the calling accessor is in the middle of a update transaction,
    /// the new accessor will not start a transaction to trace the same
    /// updates.
    ///
    /// The intended use case of cloning is to create a separate context
    /// where a specific set of database operations can be performed
    /// independently from the original accessor.  The updater will use it
    /// so that multiple updaters can be created concurrently even if the
    /// underlying database system doesn't allow running multiple transactions
    /// in a single database connection.
    ///
    /// The underlying database system may not support the functionality
    /// that would be needed to implement this method.  For example, it
    /// may not allow a single thread (or process) to have more than one
    /// database connections.  In such a case the derived class implementation
    /// should throw a \c DataSourceError exception.
    ///
    /// \return A shared pointer to the cloned accessor.
    virtual boost::shared_ptr<DatabaseAccessor> clone() = 0;

    /// \brief Returns a string identifying this dabase backend
    ///
    /// The returned string is mainly intended to be used for
    /// debugging/logging purposes.
    ///
    /// Any implementation is free to choose the exact string content,
    /// but it is advisable to make it a name that is distinguishable
    /// from the others.
    ///
    /// \return the name of the database
    virtual const std::string& getDBName() const = 0;

    /// \brief It returns the previous name in DNSSEC order.
    ///
    /// Gets the previous name in the DNSSEC order. This can be used
    /// to find the correct NSEC records for proving nonexistence
    /// of domains.
    ///
    /// \param rname The name to ask for previous of, in reversed form.
    ///     We use the reversed form (see isc::dns::Name::reverse),
    ///     because then the case insensitive order of string representation
    ///     and the DNSSEC order correspond (eg. org.example.a is followed
    ///     by org.example.a.b which is followed by org.example.b, etc).
    /// \param zone_id The zone to look through.
    /// \return The previous name.
    /// \note This function must return previous name even in case
    ///     the queried rname does not exist in the zone.
    /// \note This method must skip under-the-zone-cut data (glue data).
    ///     This might be implemented by looking for NSEC records (as glue
    ///     data don't have them) in the zone or in some other way.
    ///
    /// \throw DataSourceError if there's a problem with the database.
    /// \throw NotImplemented if this database doesn't support DNSSEC
    ///     or there's no previous name for the queried one (the NSECs
    ///     might be missing or the queried name is less or equal the
    ///     apex of the zone).
    virtual std::string findPreviousName(int zone_id,
                                         const std::string& rname) const = 0;

    /// \brief It returns the previous hash in the NSEC3 chain.
    ///
    /// This is used to find previous NSEC3 hashes, to find covering NSEC3 in
    /// case none match exactly.
    ///
    /// In case a hash before the lowest or the lowest is provided,
    /// this should return the largest one in the zone (NSEC3 needs a
    /// wrap-around semantics).
    ///
    /// \param zone_id Specifies the zone to look into, as returned by getZone.
    /// \param hash The hash to look before.
    /// \return The nearest smaller hash than the provided one, or the largest
    ///     hash in the zone if something smaller or equal to the lowest one
    ///     is provided.
    /// \note If the zone contains multiple NSEC3 chains, you should check that
    ///     the returned result contains the NSEC3 for correct parameters. If
    ///     not, query again and get something smaller - this will eventually
    ///     get to the correct one. This interface and semantics might change
    ///     in future.
    ///
    /// \throw DataSourceError if there's a problem with the database or if
    ///     this zone is not signed with NSEC3.
    /// \throw NotImplemented if this database doesn't support NSEC3.
    /// \throw anything else, as this might be any implementation.
    virtual std::string findPreviousNSEC3Hash(int zone_id,
                                              const std::string& hash)
        const = 0;
};

/// \brief Concrete data source client oriented at database backends.
///
/// This class (together with corresponding versions of ZoneFinder,
/// ZoneIterator, etc.) translates high-level data source queries to
/// low-level calls on DatabaseAccessor. It calls multiple queries
/// if necessary and validates data from the database, allowing the
/// DatabaseAccessor to be just simple translation to SQL/other
/// queries to database.
///
/// While it is possible to subclass it for specific database in case
/// of special needs, it is not expected to be needed. This should just
/// work as it is with whatever DatabaseAccessor.
class DatabaseClient : public DataSourceClient {
public:
    /// \brief Constructor
    ///
    /// It initializes the client with a database via the given accessor.
    ///
    /// \exception isc::InvalidParameter if accessor is NULL. It might throw
    /// standard allocation exception as well, but doesn't throw anything else.
    ///
    /// \param rrclass The RR class of the zones that this client will handle.
    /// \param accessor The accessor to the database to use to get data.
    ///  As the parameter suggests, the client takes ownership of the accessor
    ///  and will delete it when itself deleted.
    DatabaseClient(isc::dns::RRClass rrclass,
                   boost::shared_ptr<DatabaseAccessor> accessor);


    /// \brief Corresponding ZoneFinder implementation
    ///
    /// The zone finder implementation for database data sources. Similarly
    /// to the DatabaseClient, it translates the queries to methods of the
    /// database.
    ///
    /// Application should not come directly in contact with this class
    /// (it should handle it trough generic ZoneFinder pointer), therefore
    /// it could be completely hidden in the .cc file. But it is provided
    /// to allow testing and for rare cases when a database needs slightly
    /// different handling, so it can be subclassed.
    ///
    /// Methods directly corresponds to the ones in ZoneFinder.
    class Finder : public ZoneFinder {
    public:
        /// \brief Constructor
        ///
        /// \param database The database (shared with DatabaseClient) to
        ///     be used for queries (the one asked for ID before).
        /// \param zone_id The zone ID which was returned from
        ///     DatabaseAccessor::getZone and which will be passed to further
        ///     calls to the database.
        /// \param origin The name of the origin of this zone. It could query
        ///     it from database, but as the DatabaseClient just searched for
        ///     the zone using the name, it should have it.
        Finder(boost::shared_ptr<DatabaseAccessor> database, int zone_id,
               const isc::dns::Name& origin);

        // The following three methods are just implementations of inherited
        // ZoneFinder's pure virtual methods.
        virtual isc::dns::Name getOrigin() const;
        virtual isc::dns::RRClass getClass() const;

        /// \brief Find an RRset in the datasource
        ///
        /// Searches the datasource for an RRset of the given name and
        /// type. If there is a CNAME at the given name, the CNAME rrset
        /// is returned.
        /// (this implementation is not complete, and currently only
        /// does full matches, CNAMES, and the signatures for matches and
        /// CNAMEs)
        ///
        /// \note Maybe counter intuitively, this method is not a const member
        /// function.  This is intentional; some of the underlying
        /// implementations are expected to use a database backend, and would
        /// internally contain some abstraction of "database connection".  In
        /// the most strict sense any (even read only) operation might change
        /// the internal state of such a connection, and in that sense the
        /// operation cannot be considered "const".  In order to avoid giving a
        /// false sense of safety to the caller, we indicate a call to this
        /// method may have a surprising side effect.  That said, this view may
        /// be too strict and it may make sense to say the internal database
        /// connection doesn't affect external behavior in terms of the
        /// interface of this method.  As we gain more experiences with various
        /// kinds of backends we may revisit the constness.
        ///
        /// \exception DataSourceError when there is a problem reading
        ///                            the data from the dabase backend.
        ///                            This can be a connection, code, or
        ///                            data (parse) error.
        ///
        /// \param name The name to find
        /// \param type The RRType to find
        /// \param options Options about how to search.
        ///     See ZoneFinder::FindOptions.
        virtual ZoneFinderContextPtr find(const isc::dns::Name& name,
                                          const isc::dns::RRType& type,
                                          const FindOptions options =
                                          FIND_DEFAULT);
        /// \brief Implementation of the ZoneFinder::findAll method.
        ///
        /// In short, it is mostly the same thing as find, but it returns all
        /// RRsets in the named node through the target parameter in successful
        /// case. It acts the same in the unsuccessful one.
        virtual ZoneFinderContextPtr findAll(
            const isc::dns::Name& name,
            std::vector<isc::dns::ConstRRsetPtr>& target,
            const FindOptions options = FIND_DEFAULT);

        /// Look for NSEC3 for proving (non)existence of given name.
        ///
        /// See documentation in \c Zone.
        virtual FindNSEC3Result
        findNSEC3(const isc::dns::Name& name, bool recursive);

        /// \brief The zone ID
        ///
        /// This function provides the stored zone ID as passed to the
        /// constructor. This is meant for testing purposes and normal
        /// applications shouldn't need it.
        int zone_id() const { return (zone_id_); }

        /// \brief The database accessor.
        ///
        /// This function provides the database accessor stored inside as
        /// passed to the constructor. This is meant for testing purposes and
        /// normal applications shouldn't need it.
        const DatabaseAccessor& getAccessor() const {
            return (*accessor_);
        }

    private:
        boost::shared_ptr<DatabaseAccessor> accessor_;
        const int zone_id_;
        const isc::dns::Name origin_;

        /// \brief Shortcut name for the result of getRRsets
        typedef std::pair<bool, std::map<dns::RRType, dns::RRsetPtr> >
            FoundRRsets;
        /// \brief Just shortcut for set of types
        typedef std::set<dns::RRType> WantedTypes;

        /// \brief Internal logit of find and findAll methods.
        ///
        /// Most of their handling is in the "error" cases and delegations
        /// and so on. So they share the logic here and find and findAll provide
        /// just an interface for it.
        ///
        /// Parameters and behaviour is like of those combined together.
        /// Unexpected parameters, like type != ANY and having the target, are
        /// just that - unexpected and not checked.
        ResultContext findInternal(const isc::dns::Name& name,
                                   const isc::dns::RRType& type,
                                   std::vector<isc::dns::ConstRRsetPtr>*
                                   target,
                                   const FindOptions options = FIND_DEFAULT);

        /// \brief Searches database for RRsets of one domain.
        ///
        /// This method scans RRs of single domain specified by name and
        /// extracts any RRsets found and requested by parameters.
        ///
        /// It is used internally by find(), because it is called multiple
        /// times (usually with different domains).
        ///
        /// \param name Which domain name should be scanned.
        /// \param types List of types the caller is interested in.
        /// \param sigs Return RRSIGs if true is passed. Otherwise, no
        ///     associated RRSIGs are set on the returned RRsets.
        /// \param construct_name If this is NULL, the resulting RRsets have
        ///     their name set to name. If it is not NULL, it overrides the
        ///     name and uses this one (this can be used for wildcard
        ///     synthesized records).
        /// \param any If this is true, it records all the types, not only the
        ///     ones requested by types. It also puts a NULL pointer under the
        ///     ANY type into the result, if it finds any RRs at all, to easy
        ///     the identification of success.
        /// \param srcContext This can be set to non-NULL value to override the
        ///     iterator context used for obtaining the data. This can be used,
        ///     for example, to get data from the NSEC3 namespace.
        /// \return A pair, where the first element indicates if the domain
        ///     contains any RRs at all (not only the requested, it may happen
        ///     this is set to true, but the second part is empty). The second
        ///     part is map from RRtypes to RRsets of the corresponding types.
        ///     If the RRset is not present in DB, the RRtype is not there at
        ///     all (so you'll not find NULL pointer in the result).
        /// \throw DataSourceError If there's a low-level error with the
        ///     database or the database contains bad data.
        FoundRRsets getRRsets(const std::string& name,
                              const WantedTypes& types,
                              bool sigs,
                              const std::string* construct_name = NULL,
                              bool any = false,
                              DatabaseAccessor::IteratorContextPtr srcContext =
                              DatabaseAccessor::IteratorContextPtr());

        /// \brief DNSSEC related context for ZoneFinder::findInternal.
        ///
        /// This class is a helper for the ZoneFinder::findInternal method,
        /// encapsulating DNSSEC related information and processing logic.
        /// Specifically, it tells the finder whether the zone under search
        /// is DNSSEC signed or not, and if it is, whether it's with NSEC or
        /// with NSEC3.  It also provides a RRset DNSSEC proof RRset for some
        /// specific situations (in practice, this means an NSEC RRs for
        /// negative proof when they are needed and expected).
        ///
        /// The purpose of this class is to keep the main finder implementation
        /// unaware of DNSSEC related details.  It's also intended to help
        /// avoid unnecessary lookup for DNSSEC proof RRsets; this class
        /// doesn't look into the DB for these RRsets unless it's known to
        /// be needed.  The same optimization could be implemented in the
        /// main code, but it will result in duplicate similar code logic
        /// and make the code more complicated.  By encapsulating and unifying
        /// the logic in a single separate class, we can keep the main
        /// search logic readable.
        class FindDNSSECContext {
        public:
            /// \brief Constructor for FindDNSSECContext class.
            ///
            /// This constructor doesn't involve any expensive operation such
            /// as database lookups.  It only initializes some internal
            /// states (in a cheap way) and remembers if DNSSEC proof
            /// is requested.
            ///
            /// \param finder The Finder for the findInternal that uses this
            /// context.
            /// \param options Find options given to the finder.
            FindDNSSECContext(Finder& finder, const FindOptions options);

            /// \brief Return DNSSEC related result flags for the context.
            ///
            /// This method returns a FindResultFlags value related to
            /// DNSSEC, based on the context.  If DNSSEC proof is requested
            /// and the zone is signed with NSEC/NSEC3, it returns
            /// RESULT_NSEC_SIGNED/RESULT_NSEC3_SIGNED, respectively;
            /// otherwise it returns RESULT_DEFAULT.  So the caller can simply
            /// take a logical OR for the returned value of this method and
            /// whatever other flags it's going to set, without knowing
            /// DNSSEC specific information.
            ///
            /// If it's not yet identified whether and how the zone is DNSSEC
            /// signed at the time of the call, it now detects that via
            /// database lookups (if necessary).  (And this is because why
            /// this method cannot be a const member function).
            ZoneFinder::FindResultFlags getResultFlags();

            /// \brief Get DNSSEC negative proof for a given name.
            ///
            /// If the zone is considered NSEC-signed and the context
            /// requested DNSSEC proofs, this method tries to find NSEC RRs
            /// for the give name.  If \c covering is true, it means a
            /// "no name" proof is requested, so it calls findPreviousName on
            /// the given name and extracts an NSEC record on the result;
            /// otherwise it tries to get NSEC RRs for the given name.  If
            /// the NSEC is found, this method returns it; otherwise it returns
            /// NULL.
            ///
            /// In all other cases this method simply returns NULL.
            ///
            /// \param name The name which the NSEC RRset belong to.
            /// \param covering true if a covering NSEC is required; false if
            /// a matching NSEC is required.
            /// \return Any found DNSSEC proof RRset or NULL
            isc::dns::ConstRRsetPtr getDNSSECRRset(
                const isc::dns::Name& name, bool covering);

            /// \brief Get DNSSEC negative proof for a given name.
            ///
            /// If the zone is considered NSEC-signed and the context
            /// requested DNSSEC proofs, this method tries to find NSEC RRset
            /// from the given set (\c found_set) and returns it if found;
            /// in other cases this method simply returns NULL.
            ///
            /// \param found_set The RRset which may contain an NSEC RRset.
            /// \return Any found DNSSEC proof RRset or NULL
            isc::dns::ConstRRsetPtr getDNSSECRRset(const FoundRRsets&
                                                   found_set);

        private:
            /// \brief Returns whether the zone is signed with NSEC3.
            ///
            /// This method returns true if the zone for the finder that
            /// uses this context is considered DNSSEC signed with NSEC3;
            /// otherwise it returns false.  If it's not yet detected,
            /// this method now detects that via database lookups (if
            /// necessary).
            bool isNSEC3();

            /// \brief Returns whether the zone is signed with NSEC.
            ///
            /// This is similar to isNSEC3(), but works for NSEC.
            bool isNSEC();

            /// \brief Probe into the database to see if/how the zone is
            /// signed.
            ///
            /// This is a subroutine of isNSEC3() and isNSEC(), and performs
            /// delayed database probe to detect whether the zone used by
            /// the finder is DNSSEC signed, and if it is, with NSEC or NSEC3.
            void probe();

            DatabaseClient::Finder& finder_;
            const bool need_dnssec_;

            bool is_nsec3_;
            bool is_nsec_;
            bool probed_;
        };

        /// \brief A simple wrapper for identifying the previous name
        /// of the given name in the underlying database.
        isc::dns::Name findPreviousName(const isc::dns::Name& name) const;

        /// \brief Search result of \c findDelegationPoint().
        ///
        /// This is a tuple combining the result of the search - a status code
        /// and a pointer to the RRset found - together with additional
        /// information needed for subsequent processing, an indication of
        /// the first NS RRset found in the search and the number of labels
        /// in the last non-empty domain encountered in the search.  It is
        /// used by \c findDelegationPoint().
        ///
        /// The last two items are located naturally in the search and although
        /// not strictly part of the result, they are passed back to avoid
        /// another (duplicate) search later in the processing.
        ///
        /// Note that the code and rrset elements are the same as that in
        /// the \c ZoneFinder::FindResult struct: this structure could be
        /// derived from that one, but as it is used just once in the code and
        /// will never be treated as a \c FindResult, the obscurity involved in
        /// deriving it from a parent class was deemed not worthwhile.
        struct DelegationSearchResult {
            DelegationSearchResult(const ZoneFinder::Result param_code,
                                   const isc::dns::ConstRRsetPtr param_rrset,
                                   const isc::dns::ConstRRsetPtr param_ns,
                                   size_t param_last_known) :
                                   code(param_code), rrset(param_rrset),
                                   first_ns(param_ns),
                                   last_known(param_last_known)
            {}
            const ZoneFinder::Result code;          ///< Result code
            const isc::dns::ConstRRsetPtr rrset;    ///< RRset found
            const isc::dns::ConstRRsetPtr first_ns; ///< First NS found
            const size_t last_known; ///< No. labels in last non-empty domain
        };

        /// \brief Find delegation point
        ///
        /// Given a name, searches through the superdomains from the origin
        /// down, searching for a point that indicates a delegation (i.e. an
        /// NS record or a DNAME).
        ///
        /// The method operates in two modes, non-glue-ok and glue-ok modes:
        ///
        /// In non-glue-ok mode, the search is made purely for the NS or DNAME
        /// RR.  The zone is searched from the origin down looking  for one
        /// of these RRTypes (and ignoring the NS records at the zone origin).
        /// A status is returned indicating what is found: DNAME, DELEGATION
        /// of SUCCESS, the last indicating that nothing was found, together
        /// with a pointer to the relevant RR.
        ///
        /// In glue-ok mode, the first NS encountered in the search (apart from
        /// the NS at the zone apex) is remembered but otherwise NS records are
        /// ignored and the search attempts to find a DNAME.  The result is
        /// returned in the same format, along with a pointer to the first non-
        /// apex NS (if found).
        ///
        /// \param name The name to find
        /// \param options Options about how to search. See the documentation
        ///        for ZoneFinder::FindOptions.
        ///
        /// \return Tuple holding the result of the search - the RRset of the
        ///         delegation point and the type of the point (DELEGATION or
        ///         DNAME) - and associated information.  This latter item
        ///         comprises two pieces of data: a pointer to the highest
        ///         encountered NS, and the number of labels in the last known
        ///         non-empty domain.  The associated information is found as
        ///         a natural part of the search for the delegation point and
        ///         is used later in the find() processing; it is passed back
        ///         to avoid the need to perform a second search to obtain it.
        DelegationSearchResult
        findDelegationPoint(const isc::dns::Name& name,
                            const FindOptions options);

        /// \brief Find wildcard match
        ///
        /// Having found that the name is not an empty non-terminal, this
        /// searches the zone for for wildcards that match the name.
        ///
        /// It searches superdomains of the name from the zone origin down
        /// looking for a wildcard in the zone that matches the name.  There
        /// are several cases to consider:
        ///
        /// - If the previous search for a delegation point has found that
        ///   there is an NS at the superdomain of the point at which the
        ///   wildcard is found, the delegation is returned.
        /// - If there is a match to the name, an appropriate status is
        ///   returned (match on requested type, delegation, cname, or just
        ///   the indication of a match but no RRs relevant to the query).
        /// - If the match is to an non-empty non-terminal wildcard, a
        ///   wildcard NXRRSET is returned.
        ///
        /// Note that if DNSSEC is enabled for the search and the zone uses
        /// NSEC for authenticated denial of existence, the search may
        /// return NSEC records.
        ///
        /// \param name The name to find
        /// \param type The RRType to find
        /// \param options Options about how to search. See the documentation
        ///        for ZoneFinder::FindOptions.
        /// \param dresult Result of the search through the zone for a
        ///        delegation.
        /// \param target If the type happens to be ANY, it will insert all
        ///        the RRsets of the found name (if any is found) here instead
        ///        of being returned by the result.
        /// \param dnssec_ctx The dnssec context, it is a DNSSEC wrapper for
        ///        find function.
        /// \return Tuple holding the result of the search - the RRset of the
        ///         wildcard records matching the name, together with a status
        ///         indicating the match type (e.g. CNAME at the wildcard
        ///         match, no RRs of the requested type at the wildcard,
        ///         success due to an exact match).  Also returned if there
        ///         is no match is an indication as to whether there was an
        ///         NXDOMAIN or an NXRRSET.
        ResultContext findWildcardMatch(const isc::dns::Name& name,
                                        const isc::dns::RRType& type,
                                        const FindOptions options,
                                        const DelegationSearchResult& dresult,
                                        std::vector<isc::dns::ConstRRsetPtr>*
                                        target, FindDNSSECContext& dnssec_ctx);

        /// \brief Handle matching results for name
        ///
        /// This is called when something is found in the underlying database
        /// whose domain name is an exact match of the name to be searched for.
        /// It explores four possible cases to decide the final lookup result:
        /// - The name is a zone cut due to an NS RR.
        /// - CNAME is found (while the requested RR type is not CNAME).
        ///   In this case multiple CNAMEs are checked and rejected with
        ///   a \c DataSourceError exception.
        /// - Requested type is not found at that name.
        /// - A record of the requested type is found, or the query is ANY and
        ///   some records were found.
        /// and returns a corresponding find result.
        ///
        /// This method is commonly used for normal (non wildcard) and wildcard
        /// matches.
        ///
        /// \param name The name to find
        /// \param type The RRType to find
        /// \param options Options about how to search. See the documentation
        ///        for ZoneFinder::FindOptions.
        /// \param is_origin If name is the zone's origin name.
        /// \param found A set of found RRsets in the search for the name
        ///        and type.  It could contain one or more of the requested
        ///        type, CNAME, NS, and NSEC RRsets of the name.
        /// \param wildname If non NULL, the method is called on a wildcard
        ///                 match, and points to a string object representing
        ///                 a textual form of the matched wildcard name;
        ///                 it's NULL in the case of non wildcard match.
        /// \param target When the query is any, this must be set to a vector
        ///    where the result will be stored.
        /// \param dnssec_ctx The dnssec context, it is a DNSSEC wrapper for
        ///        find function.

        /// \return Tuple holding the result of the search - the RRset of the
        ///         wildcard records matching the name, together with a status
        ///         indicating the match type (corresponding to the each of
        ///         the above 4 cases).  The return value is intended to be
        ///         usable as a return value of the caller of this helper
        ///         method.
        ResultContext findOnNameResult(const isc::dns::Name& name,
                                       const isc::dns::RRType& type,
                                       const FindOptions options,
                                       const bool is_origin,
                                       const FoundRRsets& found,
                                       const std::string* wildname,
                                       std::vector<isc::dns::ConstRRsetPtr>*
                                       target, FindDNSSECContext& dnssec_ctx);

        /// \brief Handle no match for name
        ///
        /// This is called when it is known that there is no delegation and
        /// there is no exact match for the name (regardless of RR types
        /// requested).  Before returning NXDOMAIN, we need to check two
        /// cases:
        /// - Empty non-terminal: if the name has subdomains in the database,
        ///   flag the fact.  An NXRRSET will be returned (along with the
        ///   NSEC record covering the requested domain name if DNSSEC data
        ///   is being returned).
        /// - Wildcard: is there a wildcard record in the zone that matches
        ///   requested name? If so, return it.  If not, return the relevant
        ///   NSEC records (if requested).
        ///
        /// \param name The name to find
        /// \param type The RRType to find
        /// \param options Options about how to search. See the documentation
        ///        for ZoneFinder::FindOptions.
        /// \param dresult Result of the search through the zone for a
        ///        delegation.
        /// \param target If the query is for type ANY, the successfull result,
        ///        if there happens to be one, will be returned through the
        ///        parameter, as it doesn't fit into the result.
        /// \param dnssec_ctx The dnssec context, it is a DNSSEC wrapper for
        ///        find function.
        /// \return Tuple holding the result of the search - the RRset of the
        ///         wildcard records matching the name, together with a status
        ///         indicating the match type (e.g. CNAME at the wildcard
        ///         match, no RRs of the requested type at the wildcard,
        ///         success due to an exact match).
        ResultContext findNoNameResult(const isc::dns::Name& name,
                                       const isc::dns::RRType& type,
                                       FindOptions options,
                                       const DelegationSearchResult& dresult,
                                       std::vector<isc::dns::ConstRRsetPtr>*
                                       target, FindDNSSECContext& dnssec_ctx);

        /// Logs condition and creates result
        ///
        /// A convenience function used by findOnNameResult(), it both creates
        /// the FindResult object that find() will return to its caller as well
        /// as logging a debug message for the information being returned.
        ///
        /// \param name Domain name of the RR that was being sought.
        /// \param wildname Domain name string of a matched wildcard name or
        /// NULL for non wildcard match.
        /// \param type Type of RR being sought.
        /// \param code Result of the find operation
        /// \param rrset RRset found as a result of the find (which may be
        ///        null).
        /// \param log_id ID of the message being logged.  Up to five
        ///        parameters are available to the message: data source name,
        ///        requested domain name, requested class, requested type
        ///        and (but only if the search was successful and returned
        ///        an RRset) details of the RRset found.
        ///
        /// \return FindResult object constructed from the code and rrset
        ///         arguments.
        ResultContext logAndCreateResult(const isc::dns::Name& name,
                                         const std::string* wildname,
                                         const isc::dns::RRType& type,
                                         ZoneFinder::Result code,
                                         isc::dns::ConstRRsetPtr rrset,
                                         const isc::log::MessageID& log_id,
                                         FindResultFlags flags) const;

        /// \brief Checks if something lives below this domain.
        ///
        /// This looks if there's any subdomain of the given name. It can be
        /// used to test if domain is empty non-terminal.
        ///
        /// \param name The domain to check.
        ///
        /// \return true if the name has subdomains, false if not.
        bool hasSubdomains(const std::string& name);

        /// \brief Convenience type shortcut.
        ///
        /// To find stuff in the result of getRRsets.
        typedef std::map<dns::RRType, dns::RRsetPtr>::const_iterator
            FoundIterator;
    };

    /// \brief Find a zone in the database
    ///
    /// This queries database's getZone to find the best matching zone.
    /// It will propagate whatever exceptions are thrown from that method
    /// (which is not restricted in any way).
    ///
    /// \param name Name of the zone or data contained there.
    /// \return FindResult containing the code and an instance of Finder, if
    ///     anything is found. However, application should not rely on the
    ///     ZoneFinder being instance of Finder (possible subclass of this class
    ///     may return something else and it may change in future versions), it
    ///     should use it as a ZoneFinder only.
    virtual FindResult findZone(const isc::dns::Name& name) const;

    /// \brief Create a zone in the database
    ///
    /// This method implements \c DataSourceClient::createZone()
    ///
    /// It starts a transaction, checks if the zone exists, and if it
    /// does not, creates it, commits, and returns true. If the zone
    /// does exist already, it does nothing (except abort the transaction)
    /// and returns false.
    virtual bool createZone(const isc::dns::Name& name);

    /// \brief Get the zone iterator
    ///
    /// The iterator allows going through the whole zone content. If the
    /// underlying DatabaseConnection is implemented correctly, it should
    /// be possible to have multiple ZoneIterators at once and query data
    /// at the same time.
    ///
    /// \exception DataSourceError if the zone doesn't exist.
    /// \exception isc::NotImplemented if the underlying DatabaseConnection
    ///     doesn't implement iteration. But in case it is not implemented
    ///     and the zone doesn't exist, DataSourceError is thrown.
    /// \exception Anything else the underlying DatabaseConnection might
    ///     want to throw.
    /// \param name The origin of the zone to iterate.
    /// \param separate_rrs If true, the iterator will return each RR as a
    ///                     new RRset object. If false, the iterator will
    ///                     combine consecutive RRs with the name and type
    ///                     into 1 RRset. The capitalization of the RRset will
    ///                     be that of the first RR read, and TTLs will be
    ///                     adjusted to the lowest one found.
    /// \return Shared pointer to the iterator (it will never be NULL)
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name,
                                        bool separate_rrs = false) const;

    /// This implementation internally clones the accessor from the one
    /// used in the client and starts a separate transaction using the cloned
    /// accessor.  The returned updater will be able to work separately from
    /// the original client.
    virtual ZoneUpdaterPtr getUpdater(const isc::dns::Name& name,
                                      bool replace,
                                      bool journaling = false) const;


    /// This implementation internally clones the accessor from the one
    /// used in the client for retrieving diffs and iterating over them.
    /// The returned reader object will be able to work separately from
    /// the original client.
    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
    getJournalReader(const isc::dns::Name& zone, uint32_t begin_serial,
                     uint32_t end_serial) const;

private:
    /// \brief The RR class that this client handles.
    const isc::dns::RRClass rrclass_;

    /// \brief The accessor to our database.
    const boost::shared_ptr<DatabaseAccessor> accessor_;
};

}
}

#endif  // DATABASE_DATASRC_H

// Local Variables:
// mode: c++
// End:
