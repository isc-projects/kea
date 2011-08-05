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


#ifndef __DATASRC_SQLITE3_CONNECTION_H
#define __DATASRC_SQLITE3_CONNECTION_H

#include <datasrc/database.h>

#include <exceptions/exceptions.h>

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
 * \brief Concrete implementation of DatabaseConnection for SQLite3 databases
 *
 * This opens one database file with our schema and serves data from there.
 * According to the design, it doesn't interpret the data in any way, it just
 * provides unified access to the DB.
 */
class SQLite3Connection : public DatabaseConnection {
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
     *     can contain multiple classes of data, single connection can provide
     *     only one class).
     */
    SQLite3Connection(const std::string& filename,
                      const isc::dns::RRClass& rrclass);
    /**
     * \brief Destructor
     *
     * Closes the database.
     */
    ~SQLite3Connection();
    /**
     * \brief Look up a zone
     *
     * This implements the getZone from DatabaseConnection and looks up a zone
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

    /**
     * \brief Start a new search for the given name in the given zone.
     *
     * This implements the searchForRecords from DatabaseConnection.
     * This particular implementation does not raise DataSourceError.
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
     * \param columns This vector will be cleared, and the fields of the record will
     *                be appended here as strings (in the order rdtype, ttl, sigtype,
     *                and rdata). If there was no data, the vector is untouched.
     * \return true if there was a next record, false if there was not
     */
    virtual bool getNextRecord(std::vector<std::string>& columns);
private:
    /// \brief Private database data
    SQLite3Parameters* dbparameters_;
    /// \brief The class for which the queries are done
    const std::string class_;
    /// \brief Opens the database
    void open(const std::string& filename);
    /// \brief Closes the database
    void close();
};

}
}

#endif
