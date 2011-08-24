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

#include <datasrc/client.h>

#include <dns/name.h>
#include <exceptions/exceptions.h>

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
    /// The number of fields the columns array passed to getNext should have
    static const size_t COLUMN_COUNT = 5;

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
        NAME_COLUMN = 4     ///< The domain name of this RR
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
     * \param name The name of the zone's apex to be looked up.
     * \return The first part of the result indicates if a matching zone
     *     was found. In case it was, the second part is internal zone ID.
     *     This one will be passed to methods finding data in the zone.
     *     It is not required to keep them, in which case whatever might
     *     be returned - the ID is only passed back to the database as
     *     an opaque handle.
     */
    virtual std::pair<bool, int> getZone(const isc::dns::Name& name) const = 0;

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
         * getAllRecords(), all 5 elements of the array are overwritten.
         * For a 'name iterator', created with getRecords(), the fifth column
         * (NAME_COLUMN) is untouched, since what would be added here is by
         * definition already known to the caller (it already passes it as
         * an argument to getRecords()).
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
         */
        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) = 0;
    };

    typedef boost::shared_ptr<IteratorContext> IteratorContextPtr;

    /**
     * \brief Creates an iterator context for a specific name.
     *
     * This should create a new iterator context to be used by
     * DatabaseAccessor's ZoneIterator. It can be created based on the name
     * or the ID (returned from getZone()), what is more comfortable for the
     * database implementation. Both are provided (and are guaranteed to match,
     * the DatabaseClient first looks up the zone ID and then calls this).
     *
     * The default implementation throws isc::NotImplemented, to allow
     * "minimal" implementations of the connection not supporting optional
     * functionality.
     *
     * The implementation of the iterator that is returned may leave the
     * fifth column of the array passed to getNext() untouched, as that
     * data is already known (it is the same as the name argument here)
     *
     * \param name The name to search for.
     * \param id The ID of the zone, returned from getZone().
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getRecords(const isc::dns::Name& name,
                                          int id) const
    {
        /*
         * This is a compromise. We need to document the parameters in doxygen,
         * so they need a name, but then it complains about unused parameter.
         * This is a NOP that "uses" the parameters.
         */
        static_cast<void>(name);
        static_cast<void>(id);

        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

    /**
     * \brief Creates an iterator context for the whole zone.
     *
     * This should create a new iterator context to be used by
     * DatabaseAccessor's ZoneIterator. It can be created based on the name
     * or the ID (returned from getZone()), what is more comfortable for the
     * database implementation. Both are provided (and are guaranteed to match,
     * the DatabaseClient first looks up the zone ID and then calls this).
     *
     * The default implementation throws isc::NotImplemented, to allow
     * "minimal" implementations of the connection not supporting optional
     * functionality.
     *
     * \param id The ID of the zone, returned from getZone().
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getAllRecords(int id) const
    {
        /*
         * This is a compromise. We need to document the parameters in doxygen,
         * so they need a name, but then it complains about unused parameter.
         * This is a NOP that "uses" the parameters.
         */
        static_cast<void>(id);

        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

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
    /// A single \c DatabaseAccessor instance can perform at most one update
    /// transaction; a duplicate call to this method before
    /// \c commitUpdateZone() or \c rollbackUpdateZone() will result in
    /// a \c DataSourceError exception.  If multiple update attempts need
    /// to be performed concurrently (and if the underlying database allows
    /// such operation), separate \c DatabaseAccessor instance must be
    /// created.
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
    /// \exception DataSourceError Duplicate call to this method, or some
    /// internal database related error.
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
    /// the columns parameter has an invalid number of elements, or other
    /// internal database error.
    ///
    /// \param columns A vector of strings that defines a record to be added
    /// to the zone.
    virtual void addRecordToZone(const std::vector<std::string>& columns) = 0;

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
    /// the columns parameter has an invalid number of elements, or other
    /// internal database error.
    ///
    /// \param params A vector of strings that defines a record to be deleted
    /// from the zone.
    virtual void deleteRecordInZone(
        const std::vector<std::string>& params) = 0;

    /// Commit updates to the zone.
    ///
    /// This method completes a transaction of making updates to the zone
    /// in the context started by startUpdateZone.
    ///
    /// A successful call to \c startUpdateZone() must have preceded to
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
    virtual void commitUpdateZone() = 0;

    /// Rollback updates to the zone made so far.
    ///
    /// This method rollbacks a transaction of making updates to the zone
    /// in the context started by startUpdateZone.  When it succeeds
    /// (it normally should, but see below), the underlying database should
    /// be reverted to the point before performing the corresponding
    /// \c startUpdateZone().
    ///
    /// A successful call to \c startUpdateZone() must have preceded to
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
    virtual void rollbackUpdateZone() = 0;


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
     * It initializes the client with a database.
     *
     * \exception isc::InvalidParameter if database is NULL. It might throw
     * standard allocation exception as well, but doesn't throw anything else.
     *
     * \param database The database to use to get data. As the parameter
     *     suggests, the client takes ownership of the database and will
     *     delete it when itself deleted.
     */
    DatabaseClient(boost::shared_ptr<DatabaseAccessor> database);
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
        /**
         * \brief Searches database for an RRset
         *
         * This method scans RRs of single domain specified by name and finds
         * RRset with given type or any of redirection RRsets that are
         * requested.
         *
         * This function is used internally by find(), because this part is
         * called multiple times with slightly different parameters.
         *
         * \param name Which domain name should be scanned.
         * \param type The RRType which is requested. This can be NULL, in
         *     which case the method will look for the redirections only.
         * \param want_cname If this is true, CNAME redirection may be returned
         *     instead of the RRset with given type. If there's CNAME and
         *     something else or the CNAME has multiple RRs, it throws
         *     DataSourceError.
         * \param want_dname If this is true, DNAME redirection may be returned
         *     instead. This is with type = NULL only and is not checked in
         *     other circumstances. If the DNAME has multiple RRs, it throws
         *     DataSourceError.
         * \param want_ns This allows redirection by NS to be returned. If
         *     any other data is met as well, DataSourceError is thrown.
         * \note It may happen that some of the above error conditions are not
         *     detected in some circumstances. The goal here is not to validate
         *     the domain in DB, but to avoid bad behaviour resulting from
         *     broken data.
         * \return First part of the result tells if the domain contains any
         *     RRs. This can be used to decide between NXDOMAIN and NXRRSET.
         *     The second part is the RRset found (if any) with any relevant
         *     signatures attached to it.
         * \todo This interface doesn't look very elegant. Any better idea
         *     would be nice.
         */
        std::pair<bool, isc::dns::RRsetPtr> getRRset(const isc::dns::Name&
                                                     name,
                                                     const isc::dns::RRType*
                                                     type,
                                                     bool want_cname,
                                                     bool want_dname,
                                                     bool want_ns);
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

private:
    /// \brief The accessor to our database.
    const boost::shared_ptr<DatabaseAccessor> accessor_;
};

}
}

#endif
