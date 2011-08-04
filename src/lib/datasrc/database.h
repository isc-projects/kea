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

namespace isc {
namespace datasrc {

/**
 * \brief Abstract connection to database with DNS data
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
 *     database. If the database allows having multiple open queries at one
 *     connection, the connection class may share it.
 */
class DatabaseConnection : boost::noncopyable {
public:
    /**
     * \brief Destructor
     *
     * It is empty, but needs a virtual one, since we will use the derived
     * classes in polymorphic way.
     */
    virtual ~DatabaseConnection() { }
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
     *     be returned - the ID is only passed back to the connection as
     *     an opaque handle.
     */
    virtual std::pair<bool, int> getZone(const isc::dns::Name& name) const = 0;
};

/**
 * \brief Concrete data source client oriented at database backends.
 *
 * This class (together with corresponding versions of ZoneFinder,
 * ZoneIterator, etc.) translates high-level data source queries to
 * low-level calls on DatabaseConnection. It calls multiple queries
 * if necessary and validates data from the database, allowing the
 * DatabaseConnection to be just simple translation to SQL/other
 * queries to database.
 *
 * While it is possible to subclass it for specific database in case
 * of special needs, it is not expected to be needed. This should just
 * work as it is with whatever DatabaseConnection.
 */
class DatabaseClient : public DataSourceClient {
public:
    /**
     * \brief Constructor
     *
     * It initializes the client with a connection.
     *
     * \exception isc::InvalidParameter if connection is NULL. It might throw
     * standard allocation exception as well, but doesn't throw anything else.
     *
     * \param connection The connection to use to get data. As the parameter
     *     suggests, the client takes ownership of the connection and will
     *     delete it when itself deleted.
     */
    DatabaseClient(boost::shared_ptr<DatabaseConnection> connection);
    /**
     * \brief Corresponding ZoneFinder implementation
     *
     * The zone finder implementation for database data sources. Similarly
     * to the DatabaseClient, it translates the queries to methods of the
     * connection.
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
         * \param connection The connection (shared with DatabaseClient) to
         *     be used for queries (the one asked for ID before).
         * \param zone_id The zone ID which was returned from
         *     DatabaseConnection::getZone and which will be passed to further
         *     calls to the connection.
         */
        Finder(boost::shared_ptr<DatabaseConnection> connection, int zone_id);
        virtual isc::dns::Name getOrigin() const;
        virtual isc::dns::RRClass getClass() const;
        virtual FindResult find(const isc::dns::Name& name,
                                const isc::dns::RRType& type,
                                isc::dns::RRsetList* target = NULL,
                                const FindOptions options = FIND_DEFAULT)
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
         * \brief The database connection.
         *
         * This function provides the database connection stored inside as
         * passed to the constructor. This is meant for testing purposes and
         * normal applications shouldn't need it.
         */
        const DatabaseConnection& connection() const {
            return (*connection_);
        }
    private:
        boost::shared_ptr<DatabaseConnection> connection_;
        const int zone_id_;
    };
    /**
     * \brief Find a zone in the database
     *
     * This queries connection's getZone to find the best matching zone.
     * It will propagate whatever exceptions are thrown from that method
     * (which is not restricted in any way).
     *
     * \param name Name of the zone or data contained there.
     * \return Result containing the code and instance of Finder, if anything
     *     is found. Applications should not rely on the specific class being
     *     returned, though.
     */
    virtual FindResult findZone(const isc::dns::Name& name) const;
private:
    /// \brief Our connection.
    const boost::shared_ptr<DatabaseConnection> connection_;
};

}
}

#endif
