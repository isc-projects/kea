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


#ifndef DATASRC_SQLITE3_ACCESSOR_H
#define DATASRC_SQLITE3_ACCESSOR_H

#include <datasrc/database.h>
#include <datasrc/data_source.h>

#include <exceptions/exceptions.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>

#include <cc/data.h>

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
class SQLite3Error : public DataSourceError {
public:
    SQLite3Error(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

class IncompatibleDbVersion : public Exception {
public:
    IncompatibleDbVersion(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/**
 * \brief Too Much Data
 *
 * Thrown if a query expecting a certain number of rows back returned too
 * many rows.
 */
class TooMuchData : public DataSourceError {
public:
    TooMuchData(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

/**
 * \brief Too Little Data
 *
 * Thrown if a query expecting a certain number of rows back returned too
 * few rows (including none).
 */
class TooLittleData : public DataSourceError {
public:
    TooLittleData(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

struct SQLite3Parameters;

/**
 * \brief Concrete implementation of DatabaseAccessor for SQLite3 databases
 *
 * This opens one database file with our schema and serves data from there.
 * According to the design, it doesn't interpret the data in any way, it just
 * provides unified access to the DB.
 */
class SQLite3Accessor : public DatabaseAccessor,
    public boost::enable_shared_from_this<SQLite3Accessor> {
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
     * \param rrclass Textual representation of RR class ("IN", "CH", etc),
     *     specifying which class of data it should serve (while the database
     *     file can contain multiple classes of data, a single accessor can
     *     work with only one class).
     */
    SQLite3Accessor(const std::string& filename, const std::string& rrclass);

    /**
     * \brief Destructor
     *
     * Closes the database.
     */
    ~SQLite3Accessor();

    /// This implementation internally opens a new sqlite3 database for the
    /// same file name specified in the constructor of the original accessor.
    virtual boost::shared_ptr<DatabaseAccessor> clone();

    /**
     * \brief Look up a zone
     *
     * This implements the getZone from DatabaseAccessor and looks up a zone
     * in the data. It looks for a zone with the exact given origin and class
     * passed to the constructor.
     *
     * \exception SQLite3Error if something about the database is broken.
     *
     * \param name The (fully qualified) domain name of zone to look up
     * \return The pair contains if the lookup was successful in the first
     *     element and the zone id in the second if it was.
     */
    virtual std::pair<bool, int> getZone(const std::string& name) const;

    /** \brief Look up all resource records for a name
     *
     * This implements the getRecords() method from DatabaseAccessor
     *
     * \exception SQLite3Error if there is an sqlite3 error when performing
     *                         the query
     *
     * \param name the name to look up
     * \param id the zone id, as returned by getZone()
     * \param subdomains Match subdomains instead of the name.
     * \return Iterator that contains all records with the given name
     */
    virtual IteratorContextPtr getRecords(const std::string& name,
                                          int id,
                                          bool subdomains = false) const;

    /// \brief Look up NSEC3 records for the given hash
    ///
    /// This implements the getNSEC3Records of DatabaseAccessor.
    ///
    /// \todo Actually implement, currently throws NotImplemented.
    virtual IteratorContextPtr getNSEC3Records(const std::string& hash,
                                               int id) const;

    /** \brief Look up all resource records for a zone
     *
     * This implements the getRecords() method from DatabaseAccessor
     *
     * \exception SQLite3Error if there is an sqlite3 error when performing
     *                         the query
     *
     * \param id the zone id, as returned by getZone()
     * \return Iterator that contains all records in the given zone
     */
    virtual IteratorContextPtr getAllRecords(int id) const;

    /** \brief Creates an iterator context for a set of differences.
     *
     * Implements the getDiffs() method from DatabaseAccessor
     *
     * \exception NoSuchSerial if either of the versions do not exist in
     *            the difference table.
     * \exception SQLite3Error if there is an sqlite3 error when performing
     *            the query
     *
     * \param id The ID of the zone, returned from getZone().
     * \param start The SOA serial number of the version of the zone from
     *        which the difference sequence should start.
     * \param end The SOA serial number of the version of the zone at which
     *        the difference sequence should end.
     *
     * \return Iterator containing difference records.
     */
    virtual IteratorContextPtr
    getDiffs(int id, uint32_t start, uint32_t end) const;


    virtual std::pair<bool, int> startUpdateZone(const std::string& zone_name,
                                                 bool replace);

    virtual void startTransaction();

    /// \note we are quite impatient here: it's quite possible that the COMMIT
    /// fails due to other process performing SELECT on the same database
    /// (consider the case where COMMIT is done by xfrin or dynamic update
    /// server while an authoritative server is busy reading the DB).
    /// In a future version we should probably need to introduce some retry
    /// attempt and/or increase timeout before giving up the COMMIT, even
    /// if it still doesn't guarantee 100% success.  Right now this
    /// implementation throws a \c DataSourceError exception in such a case.
    virtual void commit();

    /// \note In SQLite3 rollback can fail if there's another unfinished
    /// statement is performed for the same database structure.
    /// Although it's not expected to happen in our expected usage, it's not
    /// guaranteed to be prevented at the API level.  If it ever happens, this
    /// method throws a \c DataSourceError exception.  It should be
    /// considered a bug of the higher level application program.
    virtual void rollback();

    virtual void addRecordToZone(
        const std::string (&columns)[ADD_COLUMN_COUNT]);

    virtual void addNSEC3RecordToZone(
        const std::string (&columns)[ADD_NSEC3_COLUMN_COUNT]);

    virtual void deleteRecordInZone(
        const std::string (&params)[DEL_PARAM_COUNT]);

    virtual void deleteNSEC3RecordInZone(
        const std::string (&params)[DEL_PARAM_COUNT]);

    /// This derived version of the method prepares an SQLite3 statement
    /// for adding the diff first time it's called, and if it fails throws
    // an \c SQLite3Error exception.
    virtual void addRecordDiff(
        int zone_id, uint32_t serial, DiffOperation operation,
        const std::string (&params)[DIFF_PARAM_COUNT]);

    /// The SQLite3 implementation of this method returns a string starting
    /// with a fixed prefix of "sqlite3_" followed by the DB file name
    /// removing any path name.  For example, for the DB file
    /// /somewhere/in/the/system/bind10.sqlite3, this method will return
    /// "sqlite3_bind10.sqlite3".
    virtual const std::string& getDBName() const { return (database_name_); }

    /// \brief Concrete implementation of the pure virtual method
    virtual std::string findPreviousName(int zone_id, const std::string& rname)
        const;

    /// \brief Conrete implemantion of the pure virtual method of
    /// DatabaseAccessor
    virtual std::string findPreviousNSEC3Hash(int zone_id,
                                              const std::string& hash) const;

private:
    /// \brief Private database data
    boost::scoped_ptr<SQLite3Parameters> dbparameters_;
    /// \brief The filename of the DB (necessary for clone())
    const std::string filename_;
    /// \brief The class for which the queries are done
    const std::string class_;
    /// \brief Database name
    const std::string database_name_;

    /// \brief Opens the database
    void open(const std::string& filename);
    /// \brief Closes the database
    void close();

    /// \brief SQLite3 implementation of IteratorContext for all records
    class Context;
    friend class Context;
    /// \brief SQLite3 implementation of IteratorContext for differences
    class DiffContext;
    friend class DiffContext;
};

/// \brief Creates an instance of the SQlite3 datasource client
///
/// Currently the configuration passed here must be a MapElement, containing
/// one item called "database_file", whose value is a string
///
/// This configuration setup is currently under discussion and will change in
/// the near future.
///
/// \param config The configuration for the datasource instance
/// \param error This string will be set to an error message if an error occurs
///              during initialization
/// \return An instance of the sqlite3 datasource client, or NULL if there was
///         an error
extern "C" DataSourceClient* createInstance(isc::data::ConstElementPtr config,
                                            std::string& error);

/// \brief Destroy the instance created by createInstance()
extern "C" void destroyInstance(DataSourceClient* instance);

}
}

#endif  // DATASRC_SQLITE3_ACCESSOR_H

// Local Variables:
// mode: c++
// End:
