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
         * from the iterated zone. The data are not converted yet.
         *
         * \note The order of RRs is not strictly set, but the RRs for single
         * RRset must not be interleaved with any other RRs (eg. RRsets must be
         * "together").
         *
         * \param data The data are to be returned by this parameter. They are
         *     (in order) the name, rrtype, TTL and the rdata.
         * \todo Unify with the interface in #1062 eventually.
         * \todo Do we consider databases where it is stored in binary blob
         *     format?
         */
        virtual bool getNext(std::string data[4]) = 0;
    };

    typedef boost::shared_ptr<IteratorContext> IteratorContextPtr;

    /**
     * \brief Creates an iterator context for given zone.
     *
     * This should create a new iterator context to be used by
     * DatabaseConnection's ZoneIterator. It can be created based on the name
     * or the ID (returned from getZone()), what is more comfortable for the
     * database implementation. Both are provided (and are guaranteed to match,
     * the DatabaseClient first looks up the zone ID and then calls this).
     *
     * The default implementation throws isc::NotImplemented, to allow
     * "minimal" implementations of the connection not supporting optional
     * functionality.
     *
     * \param name The name of the zone.
     * \param id The ID of the zone, returned from getZone().
     * \return Newly created iterator context. Must not be NULL.
     */
    virtual IteratorContextPtr getIteratorContext(const isc::dns::Name& name,
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
     * \brief Starts a new search for records of the given name in the given zone
     *
     * The data searched by this call can be retrieved with subsequent calls to
     * getNextRecord().
     *
     * \exception DataSourceError if there is a problem connecting to the
     *                            backend database
     *
     * \param zone_id The zone to search in, as returned by getZone()
     * \param name The name of the records to find
     */
    virtual void searchForRecords(int zone_id, const std::string& name) = 0;

    /**
     * \brief Retrieves the next record from the search started with searchForRecords()
     *
     * Returns a boolean specifying whether or not there was more data to read.
     * In the case of a database error, a DatasourceError is thrown.
     *
     * The columns passed is an array of std::strings consisting of
     * DatabaseConnection::COLUMN_COUNT elements, the elements of which
     * are defined in DatabaseConnection::RecordColumns, in their basic
     * string representation.
     *
     * If you are implementing a derived database connection class, you
     * should have this method check the column_count value, and fill the
     * array with strings conforming to their description in RecordColumn.
     *
     * \exception DatasourceError if there was an error reading from the database
     *
     * \param columns The elements of this array will be filled with the data
     *                for one record as defined by RecordColumns
     *                If there was no data, the array is untouched.
     * \return true if there was a next record, false if there was not
     */
    virtual bool getNextRecord(std::string columns[], size_t column_count) = 0;

    /**
     * \brief Resets the current search initiated with searchForRecords()
     *
     * This method will be called when the called of searchForRecords() and
     * getNextRecord() finds bad data, and aborts the current search.
     * It should clean up whatever handlers searchForRecords() created, and
     * any other state modified or needed by getNextRecord()
     *
     * Of course, the implementation of getNextRecord may also use it when
     * it is done with a search. If it does, the implementation of this
     * method should make sure it can handle being called multiple times.
     *
     * The implementation for this method should make sure it never throws.
     */
    virtual void resetSearch() = 0;

    /**
     * Definitions of the fields as they are required to be filled in
     * by getNextRecord()
     *
     * When implementing getNextRecord(), the columns array should
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
        RDATA_COLUMN = 3    ///< Full text representation of the record's RDATA
    };

    /// The number of fields the columns array passed to getNextRecord should have
    static const size_t COLUMN_COUNT = 4;

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
         */
        Finder(boost::shared_ptr<DatabaseAccessor> database, int zone_id);
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
         * \param options Unused at this moment
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
         * \brief The database.
         *
         * This function provides the database stored inside as
         * passed to the constructor. This is meant for testing purposes and
         * normal applications shouldn't need it.
         */
        const DatabaseAccessor& database() const {
            return (*database_);
        }
    private:
        boost::shared_ptr<DatabaseAccessor> database_;
        const int zone_id_;
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
    /// \brief Our database.
    const boost::shared_ptr<DatabaseAccessor> database_;
};

}
}

#endif
