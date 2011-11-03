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

#ifndef __DATABASE_DATASRC_H
#define __DATABASE_DATASRC_H

#include <string>

#include <boost/scoped_ptr.hpp>

#include <dns/rrclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

#include <datasrc/client.h>

#include <dns/name.h>
#include <exceptions/exceptions.h>

#include <map>
#include <set>

namespace isc {
namespace datasrc {

/**
 * \brief Abstraction of lowlevel database with DNS data
 *
 * This class is defines interface to databases. Each supported database
 * will provide methods for accessing the data stored there in a generic
 * manner. The methods are meant to be low-level, without much or any knowledge
 * about DNS and should be possible to translate directly to queries.
 *
 * On the other hand, how the communication with database is done and in what
 * schema (in case of relational/SQL database) is up to the concrete classes.
 *
 * This class is non-copyable, as copying connections to database makes little
 * sense and will not be needed.
 *
 * \todo Is it true this does not need to be copied? For example the zone
 *     iterator might need it's own copy. But a virtual clone() method might
 *     be better for that than copy constructor.
 *
 * \note The same application may create multiple connections to the same
 *     database, having multiple instances of this class. If the database
 *     allows having multiple open queries at one connection, the connection
 *     class may share it.
 */
class DatabaseAccessor : boost::noncopyable {
public:
    /**
     * Definitions of the fields as they are required to be filled in
     * by IteratorContext::getNext()
     *
     * When implementing getNext(), the columns array should
     * be filled with the values as described in this enumeration,
     * in this order, i.e. TYPE_COLUMN should be the first element
     * (index 0) of the array, TTL_COLUMN should be the second element
     * (index 1), etc.
     */
    enum RecordColumns {
        TYPE_COLUMN = 0,    ///< The RRType of the record (A/NS/TXT etc.)
        TTL_COLUMN = 1,     ///< The TTL of the record (a
        SIGTYPE_COLUMN = 2, ///< For RRSIG records, this contains the RRTYPE
                            ///< the RRSIG covers. In the current implementation,
                            ///< this field is ignored.
        RDATA_COLUMN = 3,   ///< Full text representation of the record's RDATA
        NAME_COLUMN = 4,    ///< The domain name of this RR
        COLUMN_COUNT = 5    ///< The total number of columns, MUST be value of
                            ///< the largest other element in this enum plus 1.
    };

    /**
     * Definitions of the fields to be passed to addRecordToZone().
     *
     * Each derived implementation of addRecordToZone() should expect
     * the "columns" vector to be filled with the values as described in this
     * enumeration, in this order.
     */
    enum AddRecordColumns {
        ADD_NAME = 0, ///< The owner name of the record (a domain name)
        ADD_REV_NAME = 1, ///< Reversed name of NAME (used for DNSSEC)
        ADD_TTL = 2,     ///< The TTL of the record (in numeric form)
        ADD_TYPE = 3,    ///< The RRType of the record (A/NS/TXT etc.)
        ADD_SIGTYPE = 4, ///< For RRSIG records, this contains the RRTYPE
                            ///< the RRSIG covers.
        ADD_RDATA = 5,    ///< Full text representation of the record's RDATA
        ADD_COLUMN_COUNT = 6 ///< Number of columns
    };

    /**
     * Definitions of the fields to be passed to deleteRecordInZone().
     *
     * Each derived implementation of deleteRecordInZone() should expect
     * the "params" vector to be filled with the values as described in this
     * enumeration, in this order.
     */
    enum DeleteRecordParams {
        DEL_NAME = 0, ///< The owner name of the record (a domain name)
        DEL_TYPE = 1, ///< The RRType of the record (A/NS/TXT etc.)
        DEL_RDATA = 2, ///< Full text representation of the record's RDATA
        DEL_PARAM_COUNT = 3 ///< Number of parameters
    };

    /**
     * \brief Destructor
     *
     * It is empty, but needs a virtual one, since we will use the derived
     * classes in polymorphic way.
     */
    virtual ~DatabaseAccessor() { }

    /**
     * \brief Retrieve a zone identifier
     *
     * This method looks up a zone for the given name in the database. It
     * should match only exact zone name (eg. name is equal to the zone's
     * apex), as the DatabaseClient will loop trough the labels itself and
     * find the most suitable zone.
     *
     * It is not specified if and what implementation of this method may throw,
     * so code should expect anything.
     *
     * \param name The (fully qualified) domain name of the zone's apex to be
     *             looked up.
     * \return The first part of the result indicates if a matching zone
     *     was found. In case it was, the second part is internal zone ID.
     *     This one will be passed to methods finding data in the zone.
     *     It is not required to keep them, in which case whatever might
     *     be returned - the ID is only passed back to the database as
     *     an opaque handle.
     */
    virtual std::pair<bool, int> getZone(const std::string& name) const = 0;

    /**
     * \brief This holds the internal context of ZoneIterator for databases
     *
     * While the ZoneIterator implementation from DatabaseClient does all the
     * translation from strings to DNS classes and validation, this class
     * holds the pointer to where the database is at reading the data.
     *
     * It can either hold shared pointer to the connection which created it
     * and have some kind of statement inside (in case single database
     * connection can handle multiple concurrent SQL statements) or it can
     * create a new connection (or, if it is more convenient, the connection
     * itself can inherit both from DatabaseConnection and IteratorContext
     * and just clone itself).
     */
    class IteratorContext : public boost::noncopyable {
    public:
        /**
         * \brief Destructor
         *
         * Virtual destructor, so any descendand class is destroyed correctly.
         */
        virtual ~IteratorContext() { }

        /**
         * \brief Function to provide next resource record
         *
         * This function should provide data about the next resource record
         * from the data that is searched. The data is not converted yet.
         *
         * Depending on how the iterator was constructed, there is a difference
         * in behaviour; for a 'full zone iterator', created with
         * getAllRecords(), all COLUMN_COUNT elements of the array are
         * overwritten.
         * For a 'name iterator', created with getRecords(), the column
         * NAME_COLUMN is untouched, since what would be added here is by
         * definition already known to the caller (it already passes it as
         * an argument to getRecords()).
         *
         * Once this function returns false, any subsequent call to it should
         * result in false.  The implementation of a derived class must ensure
         * it doesn't cause any disruption due to that such as a crash or
         * exception.
         *
         * \note The order of RRs is not strictly set, but the RRs for single
         * RRset must not be interleaved with any other RRs (eg. RRsets must be
         * "together").
         *
         * \param columns The data will be returned through here. The order
         *     is specified by the RecordColumns enum, and the size must be
         *     COLUMN_COUNT
         * \todo Do we consider databases where it is stored in binary blob
         *     format?
         * \throw DataSourceError if there's database-related error. If the
         *     exception (or any other in case of derived class) is thrown,
         *     the iterator can't be safely used any more.
         * \return true if a record was found, and the columns array was
         *         updated. false if there was no more data, in which case
         *         the columns array is untouched.
         */
        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) = 0;
    };

    typedef boost::shared_ptr<IteratorContext> IteratorContextPtr;

    /**
     * \brief Creates an iterator context for a specific name.
     *
     * Returns an IteratorContextPtr that contains all records of the
     * given name from the given zone.
     *
     * The implementation of the iterator that is returned may leave the
     * NAME_COLUMN column of the array passed to getNext() untouched, as that
     * data is already known (it is the same as the name argument here)
     *
     * \exception any Since any implementation can be used, the caller should
     *            expect any exception to be thrown.
     *
     * \param name The name to search for. This should be a FQDN.
     * \param id The ID of the zone, returned from getZone().
     * \param subdomains If set to true, match subdomains of name instead
     *     of name itself. It is used to find empty domains and match
     *     wildcards.
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getRecords(const std::string& name,
                                          int id,
                                          bool subdomains = false) const = 0;

    /**
     * \brief Creates an iterator context for the whole zone.
     *
     * Returns an IteratorContextPtr that contains all records of the
     * zone with the given zone id.
     *
     * Each call to getNext() on the returned iterator should copy all
     * column fields of the array that is passed, as defined in the
     * RecordColumns enum.
     *
     * \exception any Since any implementation can be used, the caller should
     *            expect any exception to be thrown.
     *
     * \param id The ID of the zone, returned from getZone().
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getAllRecords(int id) const = 0;

    /**
     * \brief Creates an iterator context for a set of differences.
     *
     * Returns an IteratorContextPtr that contains all difference records for
     * the given zone between two versions of a zone.
     *
     * The difference records are the set of records that would appear in an
     * IXFR serving a request for the difference between two versions of a zone.
     * The records are returned in the same order as they would be in the IXFR.
     * This means that if the the difference between versions of a zone with SOA
     * serial numbers of "start" and "end" is required, and the zone contains
     * the differences between serial number "start" to serial number
     * "intermediate" and from serial number "intermediate" to serial number
     * "end", the returned records will be (in order):
     *
     * \li SOA for serial "start"
     * \li Records removed from the zone between versions "start" and
     *     "intermediate" of the zone.  The order of these is not guaranteed.
     * \li SOA for serial "intermediate"
     * \li Records added to the zone between versions "start" and
     *     "intermediate" of the zone.  The order of these is not guaranteed.
     * \li SOA for serial "intermediate"
     * \li Records removed from the zone between versions "intermediate" and
     *     "end" of the zone.  The order of these is not guaranteed.
     * \li SOA for serial "end"
     * \li Records added to the zone between versions "intermediate" and "end"
     *     of the zone. The order of these is not guaranteed.
     *
     * Note that there is no requirement that "start" be less than "end". Owing
     * to serial number arithmetic, it is entirely possible that a later version
     * of a zone will have a smaller SOA serial number than an earlier version.
     *
     * Each call to getNext() on the returned iterator should copy all
     * column fields of the array that is passed, as defined in the
     * RecordColumns enum.
     *
     * \exception any Since any implementation can be used, the caller should
     *                expect any exception to be thrown.
     *
     * \param id The ID of the zone, returned from getZone().
     * \param start The SOA serial number of the version of the zone from
     *        which the difference sequence should start.
     * \param end The SOA serial number of the version of the zone at which
     *        the difference sequence should end.
     *
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getDiffs(int id, uint32_t start, uint32_t end)
                                        const = 0;

    /// Start a transaction for updating a zone.
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

    /// Add a single record to the zone to be updated.
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

    /// Delete a single record from the zone to be updated.
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

    /// Start a general transaction.
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

    /// Commit a transaction.
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

    /// Rollback any changes in a transaction made so far.
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

    /// Clone the accessor with the same configuration.
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

    /**
     * \brief Returns a string identifying this dabase backend
     *
     * The returned string is mainly intended to be used for
     * debugging/logging purposes.
     *
     * Any implementation is free to choose the exact string content,
     * but it is advisable to make it a name that is distinguishable
     * from the others.
     *
     * \return the name of the database
     */
    virtual const std::string& getDBName() const = 0;

    /**
     * \brief It returns the previous name in DNSSEC order.
     *
     * This is used in DatabaseClient::findPreviousName and does more
     * or less the real work, except for working on strings.
     *
     * \param rname The name to ask for previous of, in reversed form.
     *     We use the reversed form (see isc::dns::Name::reverse),
     *     because then the case insensitive order of string representation
     *     and the DNSSEC order correspond (eg. org.example.a is followed
     *     by org.example.a.b which is followed by org.example.b, etc).
     * \param zone_id The zone to look through.
     * \return The previous name.
     * \note This function must return previous name even in case
     *     the queried rname does not exist in the zone.
     * \note This method must skip under-the-zone-cut data (glue data).
     *     This might be implemented by looking for NSEC records (as glue
     *     data don't have them) in the zone or in some other way.
     *
     * \throw DataSourceError if there's a problem with the database.
     * \throw NotImplemented if this database doesn't support DNSSEC
     *     or there's no previous name for the queried one (the NSECs
     *     might be missing or the queried name is less or equal the
     *     apex of the zone).
     */
    virtual std::string findPreviousName(int zone_id,
                                         const std::string& rname) const = 0;
};

/**
 * \brief Concrete data source client oriented at database backends.
 *
 * This class (together with corresponding versions of ZoneFinder,
 * ZoneIterator, etc.) translates high-level data source queries to
 * low-level calls on DatabaseAccessor. It calls multiple queries
 * if necessary and validates data from the database, allowing the
 * DatabaseAccessor to be just simple translation to SQL/other
 * queries to database.
 *
 * While it is possible to subclass it for specific database in case
 * of special needs, it is not expected to be needed. This should just
 * work as it is with whatever DatabaseAccessor.
 */
class DatabaseClient : public DataSourceClient {
public:
    /**
     * \brief Constructor
     *
     * It initializes the client with a database via the given accessor.
     *
     * \exception isc::InvalidParameter if accessor is NULL. It might throw
     * standard allocation exception as well, but doesn't throw anything else.
     *
     * \param rrclass The RR class of the zones that this client will handle.
     * \param accessor The accessor to the database to use to get data.
     *  As the parameter suggests, the client takes ownership of the accessor
     *  and will delete it when itself deleted.
     */
    DatabaseClient(isc::dns::RRClass rrclass,
                   boost::shared_ptr<DatabaseAccessor> accessor);

    /**
     * \brief Corresponding ZoneFinder implementation
     *
     * The zone finder implementation for database data sources. Similarly
     * to the DatabaseClient, it translates the queries to methods of the
     * database.
     *
     * Application should not come directly in contact with this class
     * (it should handle it trough generic ZoneFinder pointer), therefore
     * it could be completely hidden in the .cc file. But it is provided
     * to allow testing and for rare cases when a database needs slightly
     * different handling, so it can be subclassed.
     *
     * Methods directly corresponds to the ones in ZoneFinder.
     */
    class Finder : public ZoneFinder {
    public:
        /**
         * \brief Constructor
         *
         * \param database The database (shared with DatabaseClient) to
         *     be used for queries (the one asked for ID before).
         * \param zone_id The zone ID which was returned from
         *     DatabaseAccessor::getZone and which will be passed to further
         *     calls to the database.
         * \param origin The name of the origin of this zone. It could query
         *     it from database, but as the DatabaseClient just searched for
         *     the zone using the name, it should have it.
         */
        Finder(boost::shared_ptr<DatabaseAccessor> database, int zone_id,
               const isc::dns::Name& origin);
        // The following three methods are just implementations of inherited
        // ZoneFinder's pure virtual methods.
        virtual isc::dns::Name getOrigin() const;
        virtual isc::dns::RRClass getClass() const;

        /**
         * \brief Find an RRset in the datasource
         *
         * Searches the datasource for an RRset of the given name and
         * type. If there is a CNAME at the given name, the CNAME rrset
         * is returned.
         * (this implementation is not complete, and currently only
         * does full matches, CNAMES, and the signatures for matches and
         * CNAMEs)
         * \note target was used in the original design to handle ANY
         *       queries. This is not implemented yet, and may use
         *       target again for that, but it might also use something
         *       different. It is left in for compatibility at the moment.
         * \note options are ignored at this moment
         *
         * \note Maybe counter intuitively, this method is not a const member
         * function.  This is intentional; some of the underlying implementations
         * are expected to use a database backend, and would internally contain
         * some abstraction of "database connection".  In the most strict sense
         * any (even read only) operation might change the internal state of
         * such a connection, and in that sense the operation cannot be considered
         * "const".  In order to avoid giving a false sense of safety to the
         * caller, we indicate a call to this method may have a surprising
         * side effect.  That said, this view may be too strict and it may
         * make sense to say the internal database connection doesn't affect
         * external behavior in terms of the interface of this method.  As
         * we gain more experiences with various kinds of backends we may
         * revisit the constness.
         *
         * \exception DataSourceError when there is a problem reading
         *                            the data from the dabase backend.
         *                            This can be a connection, code, or
         *                            data (parse) error.
         *
         * \param name The name to find
         * \param type The RRType to find
         * \param target Unused at this moment
         * \param options Options about how to search.
         *     See ZoneFinder::FindOptions.
         */
        virtual FindResult find(const isc::dns::Name& name,
                                const isc::dns::RRType& type,
                                isc::dns::RRsetList* target = NULL,
                                const FindOptions options = FIND_DEFAULT);

        /**
         * \brief Implementation of ZoneFinder::findPreviousName method.
         */
        virtual isc::dns::Name findPreviousName(const isc::dns::Name& query)
            const;

        /**
         * \brief The zone ID
         *
         * This function provides the stored zone ID as passed to the
         * constructor. This is meant for testing purposes and normal
         * applications shouldn't need it.
         */
        int zone_id() const { return (zone_id_); }

        /**
         * \brief The database accessor.
         *
         * This function provides the database accessor stored inside as
         * passed to the constructor. This is meant for testing purposes and
         * normal applications shouldn't need it.
         */
        const DatabaseAccessor& getAccessor() const {
            return (*accessor_);
        }
    private:
        boost::shared_ptr<DatabaseAccessor> accessor_;
        const int zone_id_;
        const isc::dns::Name origin_;
        //
        /// \brief Shortcut name for the result of getRRsets
        typedef std::pair<bool, std::map<dns::RRType, dns::RRsetPtr> >
            FoundRRsets;
        /// \brief Just shortcut for set of types
        typedef std::set<dns::RRType> WantedTypes;
        /**
         * \brief Searches database for RRsets of one domain.
         *
         * This method scans RRs of single domain specified by name and
         * extracts any RRsets found and requested by parameters.
         *
         * It is used internally by find(), because it is called multiple
         * times (usually with different domains).
         *
         * \param name Which domain name should be scanned.
         * \param types List of types the caller is interested in.
         * \param check_ns If this is set to true, it checks nothing lives
         *     together with NS record (with few little exceptions, like RRSIG
         *     or NSEC). This check is meant for non-apex NS records.
         * \param construct_name If this is NULL, the resulting RRsets have
         *     their name set to name. If it is not NULL, it overrides the name
         *     and uses this one (this can be used for wildcard synthesized
         *     records).
         * \return A pair, where the first element indicates if the domain
         *     contains any RRs at all (not only the requested, it may happen
         *     this is set to true, but the second part is empty). The second
         *     part is map from RRtypes to RRsets of the corresponding types.
         *     If the RRset is not present in DB, the RRtype is not there at
         *     all (so you'll not find NULL pointer in the result).
         * \throw DataSourceError If there's a low-level error with the
         *     database or the database contains bad data.
         */
        FoundRRsets getRRsets(const std::string& name,
                              const WantedTypes& types, bool check_ns,
                              const std::string* construct_name = NULL);
        /**
         * \brief Checks if something lives below this domain.
         *
         * This looks if there's any subdomain of the given name. It can be
         * used to test if domain is empty non-terminal.
         *
         * \param name The domain to check.
         */
        bool hasSubdomains(const std::string& name);

        /**
         * \brief Get the NSEC covering a name.
         *
         * This one calls findPreviousName on the given name and extracts an NSEC
         * record on the result. It handles various error cases. The method exists
         * to share code present at more than one location.
         */
        dns::RRsetPtr findNSECCover(const dns::Name& name);

        /**
         * \brief Convenience type shortcut.
         *
         * To find stuff in the result of getRRsets.
         */
        typedef std::map<dns::RRType, dns::RRsetPtr>::const_iterator
            FoundIterator;
    };

    /**
     * \brief Find a zone in the database
     *
     * This queries database's getZone to find the best matching zone.
     * It will propagate whatever exceptions are thrown from that method
     * (which is not restricted in any way).
     *
     * \param name Name of the zone or data contained there.
     * \return FindResult containing the code and an instance of Finder, if
     *     anything is found. However, application should not rely on the
     *     ZoneFinder being instance of Finder (possible subclass of this class
     *     may return something else and it may change in future versions), it
     *     should use it as a ZoneFinder only.
     */
    virtual FindResult findZone(const isc::dns::Name& name) const;

    /**
     * \brief Get the zone iterator
     *
     * The iterator allows going through the whole zone content. If the
     * underlying DatabaseConnection is implemented correctly, it should
     * be possible to have multiple ZoneIterators at once and query data
     * at the same time.
     *
     * \exception DataSourceError if the zone doesn't exist.
     * \exception isc::NotImplemented if the underlying DatabaseConnection
     *     doesn't implement iteration. But in case it is not implemented
     *     and the zone doesn't exist, DataSourceError is thrown.
     * \exception Anything else the underlying DatabaseConnection might
     *     want to throw.
     * \param name The origin of the zone to iterate.
     * \return Shared pointer to the iterator (it will never be NULL)
     */
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name) const;

    /// This implementation internally clones the accessor from the one
    /// used in the client and starts a separate transaction using the cloned
    /// accessor.  The returned updater will be able to work separately from
    /// the original client.
    virtual ZoneUpdaterPtr getUpdater(const isc::dns::Name& name,
                                      bool replace) const;

private:
    /// \brief The RR class that this client handles.
    const isc::dns::RRClass rrclass_;

    /// \brief The accessor to our database.
    const boost::shared_ptr<DatabaseAccessor> accessor_;
};

}
}

#endif  // __DATABASE_DATASRC_H

// Local Variables:
// mode: c++
// End:
