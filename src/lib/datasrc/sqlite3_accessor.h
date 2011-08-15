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


#ifndef __DATASRC_SQLITE3_ACCESSOR_H
#define __DATASRC_SQLITE3_ACCESSOR_H

#include <datasrc/database.h>

#include <exceptions/exceptions.h>

#include <boost/enable_shared_from_this.hpp>
#include <string>

namespace isc {
namespace dns {
class RRClass;
}

namespace datasrc {

/**
 * \brief Low-level database error
 *
 * This exception is thrown when the SQLite library complains about something.
 * It might mean corrupt database file, invalid request or that something is
 * rotten in the library.
 */
class SQLite3Error : public Exception {
public:
    SQLite3Error(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

struct SQLite3Parameters;

/**
 * \brief Concrete implementation of DatabaseAccessor for SQLite3 databases
 *
 * This opens one database file with our schema and serves data from there.
 * According to the design, it doesn't interpret the data in any way, it just
 * provides unified access to the DB.
 */
class SQLite3Database : public DatabaseAccessor,
    public boost::enable_shared_from_this<SQLite3Database> {
public:
    /**
     * \brief Constructor
     *
     * This opens the database and becomes ready to serve data from there.
     *
     * \exception SQLite3Error will be thrown if the given database file
     * doesn't work (it is broken, doesn't exist and can't be created, etc).
     *
     * \param filename The database file to be used.
     * \param rrclass Which class of data it should serve (while the database
     *     file can contain multiple classes of data, single database can
     *     provide only one class).
     */
    SQLite3Database(const std::string& filename,
                    const isc::dns::RRClass& rrclass);
    /**
     * \brief Destructor
     *
     * Closes the database.
     */
    ~SQLite3Database();
    /**
     * \brief Look up a zone
     *
     * This implements the getZone from DatabaseAccessor and looks up a zone
     * in the data. It looks for a zone with the exact given origin and class
     * passed to the constructor.
     *
     * \exception SQLite3Error if something about the database is broken.
     *
     * \param name The name of zone to look up
     * \return The pair contains if the lookup was successful in the first
     *     element and the zone id in the second if it was.
     */
    virtual std::pair<bool, int> getZone(const isc::dns::Name& name) const;

    /// \brief Implementation of DatabaseAbstraction::getIteratorContext
    virtual IteratorContextPtr getIteratorContext(const isc::dns::Name&,
                                                  int id) const;
    /**
     * \brief Start a new search for the given name in the given zone.
     *
     * This implements the searchForRecords from DatabaseConnection.
     * This particular implementation does not raise DataSourceError.
     *
     * \exception DataSourceError when sqlite3_bind_int() or
     *                            sqlite3_bind_text() fails
     *
     * \param zone_id The zone to seach in, as returned by getZone()
     * \param name The name to find records for
     */
    virtual void searchForRecords(int zone_id, const std::string& name);

    /**
     * \brief Retrieve the next record from the search started with
     *        searchForRecords
     *
     * This implements the getNextRecord from DatabaseConnection.
     * See the documentation there for more information.
     *
     * If this method raises an exception, the contents of columns are undefined.
     *
     * \exception DataSourceError if there is an error returned by sqlite_step()
     *                            When this exception is raised, the current
     *                            search as initialized by searchForRecords() is
     *                            NOT reset, and the caller is expected to take
     *                            care of that.
     * \param columns This vector will be cleared, and the fields of the record will
     *                be appended here as strings (in the order rdtype, ttl, sigtype,
     *                and rdata). If there was no data (i.e. if this call returns
     *                false), the vector is untouched.
     * \return true if there was a next record, false if there was not
     */
    virtual bool getNextRecord(std::string columns[], size_t column_count);

    /**
     * \brief Resets any state created by searchForRecords
     *
     * This implements the resetSearch from DatabaseConnection.
     * See the documentation there for more information.
     *
     * This function never throws.
     */
    virtual void resetSearch();

    /// The SQLite3 implementation of this method returns a string starting
    /// with a fixed prefix of "sqlite3_" followed by the DB file name
    /// removing any path name.  For example, for the DB file
    /// /somewhere/in/the/system/bind10.sqlite3, this method will return
    /// "sqlite3_bind10.sqlite3".
    virtual const std::string& getDBName() const { return (database_name_); }

private:
    /// \brief Private database data
    SQLite3Parameters* dbparameters_;
    /// \brief The class for which the queries are done
    const std::string class_;
    /// \brief Opens the database
    void open(const std::string& filename);
    /// \brief Closes the database
    void close();
    /// \brief SQLite3 implementation of IteratorContext
    class Context;
    friend class Context;
    const std::string database_name_;
};

}
}

#endif
