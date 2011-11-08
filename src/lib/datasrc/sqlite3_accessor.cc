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

#include <sqlite3.h>

#include <string>
#include <vector>

#include <boost/foreach.hpp>

#include <datasrc/sqlite3_accessor.h>
#include <datasrc/logger.h>
#include <datasrc/data_source.h>
#include <datasrc/factory.h>
#include <util/filename.h>

using namespace std;
using namespace isc::data;

#define SQLITE_SCHEMA_VERSION 1

#define CONFIG_ITEM_DATABASE_FILE "database_file"

namespace isc {
namespace datasrc {

// The following enum and char* array define the SQL statements commonly
// used in this implementation.  Corresponding prepared statements (of
// type sqlite3_stmt*) are maintained in the statements_ array of the
// SQLite3Parameters structure.

enum StatementID {
    ZONE = 0,
    ANY = 1,
    ANY_SUB = 2,
    BEGIN = 3,
    COMMIT = 4,
    ROLLBACK = 5,
    DEL_ZONE_RECORDS = 6,
    ADD_RECORD = 7,
    DEL_RECORD = 8,
    ITERATE = 9,
    FIND_PREVIOUS = 10,
    ADD_RECORD_DIFF = 11,
    GET_RECORD_DIFF = 12,       // This is temporary for testing "add diff"
    LOW_DIFF_ID = 13,
    HIGH_DIFF_ID = 14,
    DIFF_RECS = 15,
    NUM_STATEMENTS = 16
};

const char* const text_statements[NUM_STATEMENTS] = {
    // note for ANY and ITERATE: the order of the SELECT values is
    // specifically chosen to match the enum values in RecordColumns
    "SELECT id FROM zones WHERE name=?1 AND rdclass = ?2", // ZONE
    "SELECT rdtype, ttl, sigtype, rdata FROM records "     // ANY
        "WHERE zone_id=?1 AND name=?2",
    "SELECT rdtype, ttl, sigtype, rdata " // ANY_SUB
        "FROM records WHERE zone_id=?1 AND name LIKE (\"%.\" || ?2)",
    "BEGIN",                    // BEGIN
    "COMMIT",                   // COMMIT
    "ROLLBACK",                 // ROLLBACK
    "DELETE FROM records WHERE zone_id=?1", // DEL_ZONE_RECORDS
    "INSERT INTO records "      // ADD_RECORD
        "(zone_id, name, rname, ttl, rdtype, sigtype, rdata) "
        "VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7)",
    "DELETE FROM records WHERE zone_id=?1 AND name=?2 " // DEL_RECORD
        "AND rdtype=?3 AND rdata=?4",
    "SELECT rdtype, ttl, sigtype, rdata, name FROM records " // ITERATE
        "WHERE zone_id = ?1 ORDER BY rname, rdtype",
    /*
     * This one looks for previous name with NSEC record. It is done by
     * using the reversed name. The NSEC is checked because we need to
     * skip glue data, which don't have the NSEC.
     */
    "SELECT name FROM records " // FIND_PREVIOUS
        "WHERE zone_id=?1 AND rdtype = 'NSEC' AND "
        "rname < $2 ORDER BY rname DESC LIMIT 1",
    "INSERT INTO diffs "        // ADD_RECORD_DIFF
        "(zone_id, version, operation, name, rrtype, ttl, rdata) "
        "VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7)",
    "SELECT name, rrtype, ttl, rdata, version, operation " // GET_RECORD_DIFF
        "FROM diffs WHERE zone_id = ?1 ORDER BY id, operation",

    // Two statements to select the lowest ID and highest ID in a set of
    // differences.
    "SELECT id FROM diffs "     // LOW_DIFF_ID
        "WHERE zone_id=?1 AND version=?2 and OPERATION=0 "
        "ORDER BY id ASC LIMIT 1",
    "SELECT id FROM diffs "     // HIGH_DIFF_ID
        "WHERE zone_id=?1 AND version=?2 and OPERATION=1 "
        "ORDER BY id DESC LIMIT 1",

    // In the next statement, note the redundant ID.  This is to ensure
    // that the columns match the column IDs passed to the iterator
    "SELECT rrtype, ttl, id, rdata, name FROM diffs "   // DIFF_RECS
        "WHERE zone_id=?1 AND id>=?2 and id<=?3"
};

struct SQLite3Parameters {
    SQLite3Parameters() :
        db_(NULL), version_(-1), in_transaction(false), updating_zone(false),
        updated_zone_id(-1)
    {
        for (int i = 0; i < NUM_STATEMENTS; ++i) {
            statements_[i] = NULL;
        }
    }

    // This method returns the specified ID of SQLITE3 statement.  If it's
    // not yet prepared it internally creates a new one.  This way we can
    // avoid preparing unnecessary statements and minimize the overhead.
    sqlite3_stmt*
    getStatement(int id) {
        assert(id < NUM_STATEMENTS);
        if (statements_[id] == NULL) {
            assert(db_ != NULL);
            sqlite3_stmt* prepared = NULL;
            if (sqlite3_prepare_v2(db_, text_statements[id], -1, &prepared,
                                   NULL) != SQLITE_OK) {
                isc_throw(SQLite3Error, "Could not prepare SQLite statement: "
                          << text_statements[id] <<
                          ": " << sqlite3_errmsg(db_));
            }
            statements_[id] = prepared;
        }
        return (statements_[id]);
    }

    void
    finalizeStatements() {
        for (int i = 0; i < NUM_STATEMENTS; ++i) {
            if (statements_[i] != NULL) {
                sqlite3_finalize(statements_[i]);
                statements_[i] = NULL;
            }
        }
    }

    sqlite3* db_;
    int version_;
    bool in_transaction; // whether or not a transaction has been started
    bool updating_zone;          // whether or not updating the zone
    int updated_zone_id;        // valid only when in_transaction is true
private:
    // statements_ are private and must be accessed via getStatement() outside
    // of this structure.
    sqlite3_stmt* statements_[NUM_STATEMENTS];
};

// This is a helper class to encapsulate the code logic of executing
// a specific SQLite3 statement, ensuring the corresponding prepared
// statement is always reset whether the execution is completed successfully
// or it results in an exception.
// Note that an object of this class is intended to be used for "ephemeral"
// statement, which is completed with a single "step" (normally within a
// single call to an SQLite3Database method).  In particular, it cannot be
// used for "SELECT" variants, which generally expect multiple matching rows.
class StatementProcessor {
public:
    // desc will be used on failure in the what() message of the resulting
    // DataSourceError exception.
    StatementProcessor(SQLite3Parameters& dbparameters, StatementID stmt_id,
                       const char* desc) :
        dbparameters_(dbparameters), stmt_(dbparameters.getStatement(stmt_id)),
        desc_(desc)
    {
        sqlite3_clear_bindings(stmt_);
    }

    ~StatementProcessor() {
        sqlite3_reset(stmt_);
    }

    void exec() {
        if (sqlite3_step(stmt_) != SQLITE_DONE) {
            sqlite3_reset(stmt_);
            isc_throw(DataSourceError, "failed to " << desc_ << ": " <<
                      sqlite3_errmsg(dbparameters_.db_));
        }
    }

private:
    SQLite3Parameters& dbparameters_;
    sqlite3_stmt* stmt_;
    const char* const desc_;
};

SQLite3Accessor::SQLite3Accessor(const std::string& filename,
                                 const string& rrclass) :
    dbparameters_(new SQLite3Parameters),
    filename_(filename),
    class_(rrclass),
    database_name_("sqlite3_" +
                   isc::util::Filename(filename).nameAndExtension())
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_NEWCONN);

    open(filename);
}

boost::shared_ptr<DatabaseAccessor>
SQLite3Accessor::clone() {
    return (boost::shared_ptr<DatabaseAccessor>(new SQLite3Accessor(filename_,
                                                                    class_)));
}

namespace {

// This is a helper class to initialize a Sqlite3 DB safely.  An object of
// this class encapsulates all temporary resources that are necessary for
// the initialization, and release them in the destructor.  Once everything
// is properly initialized, the move() method moves the allocated resources
// to the main object in an exception free manner.  This way, the main code
// for the initialization can be exception safe, and can provide the strong
// exception guarantee.
class Initializer {
public:
    ~Initializer() {
        if (params_.db_ != NULL) {
            sqlite3_close(params_.db_);
        }
    }
    void move(SQLite3Parameters* dst) {
        *dst = params_;
        params_ = SQLite3Parameters(); // clear everything
    }
    SQLite3Parameters params_;
};

const char* const SCHEMA_LIST[] = {
    "CREATE TABLE schema_version (version INTEGER NOT NULL)",
    "INSERT INTO schema_version VALUES (1)",
    "CREATE TABLE zones (id INTEGER PRIMARY KEY, "
    "name STRING NOT NULL COLLATE NOCASE, "
    "rdclass STRING NOT NULL COLLATE NOCASE DEFAULT 'IN', "
    "dnssec BOOLEAN NOT NULL DEFAULT 0)",
    "CREATE INDEX zones_byname ON zones (name)",
    "CREATE TABLE records (id INTEGER PRIMARY KEY, "
        "zone_id INTEGER NOT NULL, name STRING NOT NULL COLLATE NOCASE, "
        "rname STRING NOT NULL COLLATE NOCASE, ttl INTEGER NOT NULL, "
        "rdtype STRING NOT NULL COLLATE NOCASE, sigtype STRING COLLATE NOCASE, "
        "rdata STRING NOT NULL)",
    "CREATE INDEX records_byname ON records (name)",
    "CREATE INDEX records_byrname ON records (rname)",
    "CREATE TABLE nsec3 (id INTEGER PRIMARY KEY, zone_id INTEGER NOT NULL, "
        "hash STRING NOT NULL COLLATE NOCASE, "
        "owner STRING NOT NULL COLLATE NOCASE, "
        "ttl INTEGER NOT NULL, rdtype STRING NOT NULL COLLATE NOCASE, "
        "rdata STRING NOT NULL)",
    "CREATE INDEX nsec3_byhash ON nsec3 (hash)",
    "CREATE TABLE diffs (id INTEGER PRIMARY KEY, "
        "zone_id INTEGER NOT NULL, "
        "version INTEGER NOT NULL, "
        "operation INTEGER NOT NULL, "
        "name STRING NOT NULL COLLATE NOCASE, "
        "rrtype STRING NOT NULL COLLATE NOCASE, "
        "ttl INTEGER NOT NULL, "
        "rdata STRING NOT NULL)",
    NULL
};

sqlite3_stmt*
prepare(sqlite3* const db, const char* const statement) {
    sqlite3_stmt* prepared = NULL;
    if (sqlite3_prepare_v2(db, statement, -1, &prepared, NULL) != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not prepare SQLite statement: " <<
                  statement << ": " << sqlite3_errmsg(db));
    }
    return (prepared);
}

// small function to sleep for 0.1 seconds, needed when waiting for
// exclusive database locks (which should only occur on startup, and only
// when the database has not been created yet)
void doSleep() {
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 100000000;
    nanosleep(&req, NULL);
}

// returns the schema version if the schema version table exists
// returns -1 if it does not
int checkSchemaVersion(sqlite3* db) {
    sqlite3_stmt* prepared = NULL;
    // At this point in time, the database might be exclusively locked, in
    // which case even prepare() will return BUSY, so we may need to try a
    // few times
    for (size_t i = 0; i < 50; ++i) {
        int rc = sqlite3_prepare_v2(db, "SELECT version FROM schema_version",
                                    -1, &prepared, NULL);
        if (rc == SQLITE_ERROR) {
            // this is the error that is returned when the table does not
            // exist
            return (-1);
        } else if (rc == SQLITE_OK) {
            break;
        } else if (rc != SQLITE_BUSY || i == 50) {
            isc_throw(SQLite3Error, "Unable to prepare version query: "
                        << rc << " " << sqlite3_errmsg(db));
        }
        doSleep();
    }
    if (sqlite3_step(prepared) != SQLITE_ROW) {
        isc_throw(SQLite3Error,
                    "Unable to query version: " << sqlite3_errmsg(db));
    }
    int version = sqlite3_column_int(prepared, 0);
    sqlite3_finalize(prepared);
    return (version);
}

// return db version
int create_database(sqlite3* db) {
    // try to get an exclusive lock. Once that is obtained, do the version
    // check *again*, just in case this process was racing another
    //
    // try for 5 secs (50*0.1)
    int rc;
    logger.info(DATASRC_SQLITE_SETUP);
    for (size_t i = 0; i < 50; ++i) {
        rc = sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL,
                            NULL);
        if (rc == SQLITE_OK) {
            break;
        } else if (rc != SQLITE_BUSY || i == 50) {
            isc_throw(SQLite3Error, "Unable to acquire exclusive lock "
                        "for database creation: " << sqlite3_errmsg(db));
        }
        doSleep();
    }
    int schema_version = checkSchemaVersion(db);
    if (schema_version == -1) {
        for (int i = 0; SCHEMA_LIST[i] != NULL; ++i) {
            if (sqlite3_exec(db, SCHEMA_LIST[i], NULL, NULL, NULL) !=
                SQLITE_OK) {
                isc_throw(SQLite3Error,
                        "Failed to set up schema " << SCHEMA_LIST[i]);
            }
        }
        sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
        return (SQLITE_SCHEMA_VERSION);
    } else {
        return (schema_version);
    }
}

void
checkAndSetupSchema(Initializer* initializer) {
    sqlite3* const db = initializer->params_.db_;

    int schema_version = checkSchemaVersion(db);
    if (schema_version != SQLITE_SCHEMA_VERSION) {
        schema_version = create_database(db);
    }
    initializer->params_.version_ = schema_version;
}

}

void
SQLite3Accessor::open(const std::string& name) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_CONNOPEN).arg(name);
    if (dbparameters_->db_ != NULL) {
        // There shouldn't be a way to trigger this anyway
        isc_throw(DataSourceError, "Duplicate SQLite open with " << name);
    }

    Initializer initializer;

    if (sqlite3_open(name.c_str(), &initializer.params_.db_) != 0) {
        isc_throw(SQLite3Error, "Cannot open SQLite database file: " << name);
    }

    checkAndSetupSchema(&initializer);
    initializer.move(dbparameters_.get());
}

SQLite3Accessor::~SQLite3Accessor() {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_DROPCONN);
    if (dbparameters_->db_ != NULL) {
        close();
    }
}

void
SQLite3Accessor::close(void) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_CONNCLOSE);
    if (dbparameters_->db_ == NULL) {
        isc_throw(DataSourceError,
                  "SQLite data source is being closed before open");
    }

    dbparameters_->finalizeStatements();
    sqlite3_close(dbparameters_->db_);
    dbparameters_->db_ = NULL;
}

std::pair<bool, int>
SQLite3Accessor::getZone(const std::string& name) const {
    int rc;
    sqlite3_stmt* const stmt = dbparameters_->getStatement(ZONE);

    // Take the statement (simple SELECT id FROM zones WHERE...)
    // and prepare it (bind the parameters to it)
    sqlite3_reset(stmt);
    rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind " << name <<
                  " to SQL statement (zone)");
    }
    rc = sqlite3_bind_text(stmt, 2, class_.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind " << class_ <<
                  " to SQL statement (zone)");
    }

    // Get the data there and see if it found anything
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const int zone_id = sqlite3_column_int(stmt, 0);
        sqlite3_reset(stmt);
        return (pair<bool, int>(true, zone_id));
    } else if (rc == SQLITE_DONE) {
        // Free resources
        sqlite3_reset(stmt);
        return (pair<bool, int>(false, 0));
    }

    sqlite3_reset(stmt);
    isc_throw(DataSourceError, "Unexpected failure in sqlite3_step: " <<
              sqlite3_errmsg(dbparameters_->db_));
    // Compilers might not realize isc_throw always throws
    return (std::pair<bool, int>(false, 0));
}

namespace {

// Conversion to plain char
const char*
convertToPlainChar(const unsigned char* ucp, sqlite3 *db) {
    if (ucp == NULL) {
        // The field can really be NULL, in which case we return an
        // empty string, or sqlite may have run out of memory, in
        // which case we raise an error
        if (sqlite3_errcode(db) == SQLITE_NOMEM) {
            isc_throw(DataSourceError,
                      "Sqlite3 backend encountered a memory allocation "
                      "error in sqlite3_column_text()");
        } else {
            return ("");
        }
    }
    const void* p = ucp;
    return (static_cast<const char*>(p));
}

}
class SQLite3Accessor::Context : public DatabaseAccessor::IteratorContext {
public:
    // Construct an iterator for all records. When constructed this
    // way, the getNext() call will copy all fields
    Context(const boost::shared_ptr<const SQLite3Accessor>& accessor, int id) :
        iterator_type_(ITT_ALL),
        accessor_(accessor),
        statement_(NULL),
        name_("")
    {
        // We create the statement now and then just keep getting data from it
        statement_ = prepare(accessor->dbparameters_->db_,
                             text_statements[ITERATE]);
        bindZoneId(id);
    }

    // Construct an iterator for records with a specific name. When constructed
    // this way, the getNext() call will copy all fields except name
    Context(const boost::shared_ptr<const SQLite3Accessor>& accessor, int id,
            const std::string& name, bool subdomains) :
        iterator_type_(ITT_NAME),
        accessor_(accessor),
        statement_(NULL),
        name_(name)

    {
        // We create the statement now and then just keep getting data from it
        statement_ = prepare(accessor->dbparameters_->db_,
                             subdomains ? text_statements[ANY_SUB] :
                             text_statements[ANY]);
        bindZoneId(id);
        bindName(name_);
    }

    bool getNext(std::string (&data)[COLUMN_COUNT]) {
        // If there's another row, get it
        // If finalize has been called (e.g. when previous getNext() got
        // SQLITE_DONE), directly return false
        if (statement_ == NULL) {
            return false;
        }
        const int rc(sqlite3_step(statement_));
        if (rc == SQLITE_ROW) {
            // For both types, we copy the first four columns
            copyColumn(data, TYPE_COLUMN);
            copyColumn(data, TTL_COLUMN);
            copyColumn(data, SIGTYPE_COLUMN);
            copyColumn(data, RDATA_COLUMN);
            // Only copy Name if we are iterating over every record
            if (iterator_type_ == ITT_ALL) {
                copyColumn(data, NAME_COLUMN);
            }
            return (true);
        } else if (rc != SQLITE_DONE) {
            isc_throw(DataSourceError,
                      "Unexpected failure in sqlite3_step: " <<
                      sqlite3_errmsg(accessor_->dbparameters_->db_));
        }
        finalize();
        return (false);
    }

    virtual ~Context() {
        finalize();
    }

private:
    // Depending on which constructor is called, behaviour is slightly
    // different. We keep track of what to do with the iterator type
    // See description of getNext() and the constructors
    enum IteratorType {
        ITT_ALL,
        ITT_NAME
    };

    void copyColumn(std::string (&data)[COLUMN_COUNT], int column) {
        data[column] = convertToPlainChar(sqlite3_column_text(statement_,
                                                              column),
                                          accessor_->dbparameters_->db_);
    }

    void bindZoneId(const int zone_id) {
        if (sqlite3_bind_int(statement_, 1, zone_id) != SQLITE_OK) {
            finalize();
            isc_throw(SQLite3Error, "Could not bind int " << zone_id <<
                      " to SQL statement: " <<
                      sqlite3_errmsg(accessor_->dbparameters_->db_));
        }
    }

    void bindName(const std::string& name) {
        if (sqlite3_bind_text(statement_, 2, name.c_str(), -1,
                              SQLITE_TRANSIENT) != SQLITE_OK) {
            const char* errmsg = sqlite3_errmsg(accessor_->dbparameters_->db_);
            finalize();
            isc_throw(SQLite3Error, "Could not bind text '" << name <<
                      "' to SQL statement: " << errmsg);
        }
    }

    void finalize() {
        sqlite3_finalize(statement_);
        statement_ = NULL;
    }

    const IteratorType iterator_type_;
    boost::shared_ptr<const SQLite3Accessor> accessor_;
    sqlite3_stmt* statement_;
    const std::string name_;
};


// Methods to retrieve the various iterators

DatabaseAccessor::IteratorContextPtr
SQLite3Accessor::getRecords(const std::string& name, int id,
                            bool subdomains) const
{
    return (IteratorContextPtr(new Context(shared_from_this(), id, name,
                                           subdomains)));
}

DatabaseAccessor::IteratorContextPtr
SQLite3Accessor::getAllRecords(int id) const {
    return (IteratorContextPtr(new Context(shared_from_this(), id)));
}


/// \brief Difference Iterator
///
/// This iterator is used to search through the differences table for the
/// resouce records making up an IXFR between two versions of a zone.

class SQLite3Accessor::DiffContext : public DatabaseAccessor::IteratorContext {
public:

    /// \brief Constructor
    ///
    /// Constructs the iterator for the difference sequence.  It is
    /// passed two parameters, the first and last versions in the difference
    /// sequence.  Note that because of serial number rollover, it may well
    /// be that the start serial number is greater than the end one.
    ///
    /// \param zone_id ID of the zone (in the zone table)
    /// \param start Serial number of first version in difference sequence
    /// \param end Serial number of last version in difference sequence
    ///
    /// \exception any A number of exceptions can be expected
    DiffContext(const boost::shared_ptr<const SQLite3Accessor>& accessor,
                int zone_id, uint32_t start, uint32_t end) :
        accessor_(accessor),
        last_status_(SQLITE_ROW)
    {
        try {
            int low_id = findIndex(LOW_DIFF_ID, zone_id, start);
            int high_id = findIndex(HIGH_DIFF_ID, zone_id, end);

            // Prepare the statement that will return data values
            reset(DIFF_RECS);
            bindInt(DIFF_RECS, 1, zone_id);
            bindInt(DIFF_RECS, 2, low_id);
            bindInt(DIFF_RECS, 3, high_id);

        } catch (...) {
            // Something wrong, clear up everything.
            accessor_->dbparameters_->finalizeStatements();
            throw;
        }
    }

    /// \brief Destructor
    virtual ~DiffContext()
    {}

    /// \brief Get Next Diff Record
    ///
    /// Returns the next difference record in the difference sequence.
    ///
    /// \param data Array of std::strings COLUMN_COUNT long.  The results
    ///        are returned in this.
    ///
    /// \return bool true if data is returned, false if not.
    ///
    /// \exceptions any Varied
    bool getNext(std::string (&data)[COLUMN_COUNT]) {

        if (last_status_ != SQLITE_DONE) {
            // Last call (if any) didn't reach end of result set, so we
            // can read another row from it.
            //
            // Get a pointer to the statement for brevity (this does not transfer
            // ownership of the statement to this class, so there is no need to
            // tidy up after we have finished using it).
            sqlite3_stmt* stmt = accessor_->dbparameters_->getStatement(DIFF_RECS);

            const int rc(sqlite3_step(stmt));
            if (rc == SQLITE_ROW) {
                // Copy the data across to the output array
                copyColumn(DIFF_RECS, data, TYPE_COLUMN);
                copyColumn(DIFF_RECS, data, TTL_COLUMN);
                copyColumn(DIFF_RECS, data, NAME_COLUMN);
                copyColumn(DIFF_RECS, data, RDATA_COLUMN);

            } else if (rc != SQLITE_DONE) {
                isc_throw(DataSourceError,
                          "Unexpected failure in sqlite3_step: " <<
                          sqlite3_errmsg(accessor_->dbparameters_->db_));
            }
            last_status_ = rc;
        }
        return (last_status_ == SQLITE_ROW);
    }

private:

    /// \brief Reset prepared statement
    ///
    /// Sets up the statement so that new parameters can be attached to it and
    /// that it can be used to query for another difference sequence.
    ///
    /// \param stindex Index of prepared statement to which to bind
    void reset(int stindex) {
        sqlite3_stmt* stmt = accessor_->dbparameters_->getStatement(stindex);
        if ((sqlite3_reset(stmt) != SQLITE_OK) || (sqlite3_clear_bindings(stmt) != SQLITE_OK)) {
            isc_throw(SQLite3Error, "Could not clear statement bindings in '" <<
                      text_statements[stindex] << "': " << 
                      sqlite3_errmsg(accessor_->dbparameters_->db_));
        }
    }
            
    /// \brief Bind Int
    ///
    /// Binds an integer to a specific variable in a prepared statement.
    ///
    /// \param stindex Index of prepared statement to which to bind
    /// \param varindex Index of variable to which to bind
    /// \param value Value of variable to bind
    /// \exception SQLite3Error on an error
    void bindInt(int stindex, int varindex, sqlite3_int64 value) {
        if (sqlite3_bind_int64(accessor_->dbparameters_->getStatement(stindex),
                             varindex, value) != SQLITE_OK) {
            isc_throw(SQLite3Error, "Could not bind value to parameter " <<
                      varindex << " in statement '" <<
                      text_statements[stindex] << "': " << 
                      sqlite3_errmsg(accessor_->dbparameters_->db_));
        }
    }

    ///\brief Get Single Value
    ///
    /// Executes a prepared statement (which has parameters bound to it)
    /// for which the result of a single value is expected.
    ///
    /// \param stindex Index of prepared statement in statement table.
    ///
    /// \return Value of SELECT.
    ///
    /// \exception TooMuchData Multiple rows returned when one expected
    /// \exception TooLittleData Zero rows returned when one expected
    /// \exception DataSourceError SQLite3-related error
    int getSingleValue(StatementID stindex) {

        // Get a pointer to the statement for brevity (does not transfer
        // resources)
        sqlite3_stmt* stmt = accessor_->dbparameters_->getStatement(stindex);

        // Execute the data.  Should be just one result
        int rc = sqlite3_step(stmt);
        int result = -1;
        if (rc == SQLITE_ROW) {

            // Got some data, extract the value
            result = sqlite3_column_int(stmt, 0);
            int rc = sqlite3_step(stmt);
            if (rc == SQLITE_DONE) {

                // All OK, exit with the value.
                return (result);

            } else if (rc == SQLITE_ROW) {
                isc_throw(TooMuchData, "request to return one value from "
                          "diffs table returned multiple values");
            }
        } else if (rc == SQLITE_DONE) {

            // No data in the table.  A bare exception with no explanation is
            // thrown, as it will be replaced by a more informative one by
            // the caller.
            isc_throw(TooLittleData, "");
        }

        // We get here on an error.
        isc_throw(DataSourceError, "could not get data from diffs table: " <<
                  sqlite3_errmsg(accessor_->dbparameters_->db_));

        // Keep the compiler happy with a return value.
        return (result);
    }

    /// \brief Find index
    ///
    /// Executes the prepared statement locating the high or low index in
    /// the diffs table and returns that index.
    ///
    /// \param stmt_id Index of the prepared statement to execute
    /// \param zone_id ID of the zone for which the index is being sought
    /// \param serial Zone serial number for which an index is being sought.
    ///
    /// \return int ID of the row in the difss table corresponding to the
    ///         statement.
    ///
    /// \exception TooLittleData Internal error, no result returned when one
    ///            was expected.
    /// \exception NoSuchSerial Serial number not found.
    /// \exception NoDiffsData No data for this zone found in diffs table
    int findIndex(StatementID stindex, int zone_id, uint32_t serial) {

        // Set up the statement
        reset(stindex);
        bindInt(stindex, 1, zone_id);
        bindInt(stindex, 2, serial);

        // Execute the statement
        int result = -1;
        try {
            result = getSingleValue(stindex);

        } catch (TooLittleData) {

            // No data returned but the SQL query succeeded.  Only possibility
            // is that there is no entry in the differences table for the given
            // zone and version.
            isc_throw(NoSuchSerial, "No entry in differences table for " <<
                      " zone ID " << zone_id << ", serial number " << serial);
        }

        return (result);
    }

    /// \brief Copy Column to Output
    ///
    /// Copies the textual data in the result set to the specified column
    /// in the output.
    ///
    /// \param stindex Index of prepared statement used to access data
    /// \param data Array of columns passed to getNext
    /// \param column Column of output to copy
    void copyColumn(StatementID stindex, std::string (&data)[COLUMN_COUNT],
                    int column) {

        // Get a pointer to the statement for brevity (does not transfer
        // resources)
        sqlite3_stmt* stmt = accessor_->dbparameters_->getStatement(stindex);
        data[column] = convertToPlainChar(sqlite3_column_text(stmt,
                                                              column),
                                          accessor_->dbparameters_->db_);
    }
    
    // Attributes

    boost::shared_ptr<const SQLite3Accessor> accessor_; // Accessor object
    int last_status_;           // Last status received from sqlite3_step
};

// ... and return the iterator

DatabaseAccessor::IteratorContextPtr
SQLite3Accessor::getDiffs(int id, uint32_t start, uint32_t end) const {
    return (IteratorContextPtr(new DiffContext(shared_from_this(), id, start,
                               end)));
}



pair<bool, int>
SQLite3Accessor::startUpdateZone(const string& zone_name, const bool replace) {
    if (dbparameters_->updating_zone) {
        isc_throw(DataSourceError,
                  "duplicate zone update on SQLite3 data source");
    }
    if (dbparameters_->in_transaction) {
        isc_throw(DataSourceError,
                  "zone update attempt in another SQLite3 transaction");
    }

    const pair<bool, int> zone_info(getZone(zone_name));
    if (!zone_info.first) {
        return (zone_info);
    }

    StatementProcessor(*dbparameters_, BEGIN,
                       "start an SQLite3 update transaction").exec();

    if (replace) {
        try {
            StatementProcessor delzone_exec(*dbparameters_, DEL_ZONE_RECORDS,
                                            "delete zone records");

            sqlite3_stmt* stmt = dbparameters_->getStatement(DEL_ZONE_RECORDS);
            sqlite3_clear_bindings(stmt);
            if (sqlite3_bind_int(stmt, 1, zone_info.second) != SQLITE_OK) {
                isc_throw(DataSourceError,
                          "failed to bind SQLite3 parameter: " <<
                          sqlite3_errmsg(dbparameters_->db_));
            }

            delzone_exec.exec();
        } catch (const DataSourceError&) {
            // Once we start a transaction, if something unexpected happens
            // we need to rollback the transaction so that a subsequent update
            // is still possible with this accessor.
            StatementProcessor(*dbparameters_, ROLLBACK,
                               "rollback an SQLite3 transaction").exec();
            throw;
        }
    }

    dbparameters_->in_transaction = true;
    dbparameters_->updating_zone = true;
    dbparameters_->updated_zone_id = zone_info.second;

    return (zone_info);
}

void
SQLite3Accessor::startTransaction() {
    if (dbparameters_->in_transaction) {
        isc_throw(DataSourceError,
                  "duplicate transaction on SQLite3 data source");
    }

    StatementProcessor(*dbparameters_, BEGIN,
                       "start an SQLite3 transaction").exec();
    dbparameters_->in_transaction = true;
}

void
SQLite3Accessor::commit() {
    if (!dbparameters_->in_transaction) {
        isc_throw(DataSourceError, "performing commit on SQLite3 "
                  "data source without transaction");
    }

    StatementProcessor(*dbparameters_, COMMIT,
                       "commit an SQLite3 transaction").exec();
    dbparameters_->in_transaction = false;
    dbparameters_->updated_zone_id = -1;
}

void
SQLite3Accessor::rollback() {
    if (!dbparameters_->in_transaction) {
        isc_throw(DataSourceError, "performing rollback on SQLite3 "
                  "data source without transaction");
    }

    StatementProcessor(*dbparameters_, ROLLBACK,
                       "rollback an SQLite3 transaction").exec();
    dbparameters_->in_transaction = false;
    dbparameters_->updated_zone_id = -1;
}

namespace {
// Commonly used code sequence for adding/deleting record
template <typename COLUMNS_TYPE>
void
doUpdate(SQLite3Parameters& dbparams, StatementID stmt_id,
         COLUMNS_TYPE update_params, const char* exec_desc)
{
    sqlite3_stmt* const stmt = dbparams.getStatement(stmt_id);
    StatementProcessor executer(dbparams, stmt_id, exec_desc);

    int param_id = 0;
    if (sqlite3_bind_int(stmt, ++param_id, dbparams.updated_zone_id)
        != SQLITE_OK) {
        isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                  sqlite3_errmsg(dbparams.db_));
    }
    const size_t column_count =
        sizeof(update_params) / sizeof(update_params[0]);
    for (int i = 0; i < column_count; ++i) {
        // The old sqlite3 data source API assumes NULL for an empty column.
        // We need to provide compatibility at least for now.
        if (sqlite3_bind_text(stmt, ++param_id,
                              update_params[i].empty() ? NULL :
                              update_params[i].c_str(),
                              -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparams.db_));
        }
    }
    executer.exec();
}
}

void
SQLite3Accessor::addRecordToZone(const string (&columns)[ADD_COLUMN_COUNT]) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "adding record to SQLite3 "
                  "data source without transaction");
    }
    doUpdate<const string (&)[DatabaseAccessor::ADD_COLUMN_COUNT]>(
        *dbparameters_, ADD_RECORD, columns, "add record to zone");
}

void
SQLite3Accessor::deleteRecordInZone(const string (&params)[DEL_PARAM_COUNT]) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "deleting record in SQLite3 "
                  "data source without transaction");
    }
    doUpdate<const string (&)[DatabaseAccessor::DEL_PARAM_COUNT]>(
        *dbparameters_, DEL_RECORD, params, "delete record from zone");
}

void
SQLite3Accessor::addRecordDiff(int zone_id, uint32_t serial,
                               DiffOperation operation,
                               const std::string (&params)[DIFF_PARAM_COUNT])
{
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "adding record diff without update "
                  "transaction on " << getDBName());
    }
    if (zone_id != dbparameters_->updated_zone_id) {
        isc_throw(DataSourceError, "bad zone ID for adding record diff on "
                  << getDBName() << ": " << zone_id << ", must be "
                  << dbparameters_->updated_zone_id);
    }

    sqlite3_stmt* const stmt = dbparameters_->getStatement(ADD_RECORD_DIFF);
    StatementProcessor executer(*dbparameters_, ADD_RECORD_DIFF,
                                "add record diff");
    int param_id = 0;
    if (sqlite3_bind_int(stmt, ++param_id, zone_id)
        != SQLITE_OK) {
        isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }
    if (sqlite3_bind_int64(stmt, ++param_id, serial)
        != SQLITE_OK) {
        isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }
    if (sqlite3_bind_int(stmt, ++param_id, operation)
        != SQLITE_OK) {
        isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }
    for (int i = 0; i < DIFF_PARAM_COUNT; ++i) {
        if (sqlite3_bind_text(stmt, ++param_id, params[i].c_str(),
                              -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparameters_->db_));
        }
    }
    executer.exec();
}

vector<vector<string> >
SQLite3Accessor::getRecordDiff(int zone_id) {
    sqlite3_stmt* const stmt = dbparameters_->getStatement(GET_RECORD_DIFF);
    sqlite3_bind_int(stmt, 1, zone_id);

    vector<vector<string> > result;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        vector<string> row_result;
        for (int i = 0; i < 6; ++i) {
            row_result.push_back(convertToPlainChar(sqlite3_column_text(stmt,
                                                                        i),
                                                    dbparameters_->db_));
        }
        result.push_back(row_result);
    }
    sqlite3_reset(stmt);

    return (result);
}

std::string
SQLite3Accessor::findPreviousName(int zone_id, const std::string& rname)
    const
{
    sqlite3_stmt* const stmt = dbparameters_->getStatement(FIND_PREVIOUS);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    if (sqlite3_bind_int(stmt, 1, zone_id) != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind zone ID " << zone_id <<
                  " to SQL statement (find previous): " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }
    if (sqlite3_bind_text(stmt, 2, rname.c_str(), -1, SQLITE_STATIC) !=
        SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind name " << rname <<
                  " to SQL statement (find previous): " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }

    std::string result;
    const int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // We found it
        result = convertToPlainChar(sqlite3_column_text(stmt, 0),
                                    dbparameters_->db_);
    }
    sqlite3_reset(stmt);

    if (rc == SQLITE_DONE) {
        // No NSEC records here, this DB doesn't support DNSSEC or
        // we asked before the apex
        isc_throw(isc::NotImplemented, "The zone doesn't support DNSSEC or "
                  "query before apex");
    }

    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        // Some kind of error
        isc_throw(SQLite3Error, "Could not get data for previous name");
    }

    return (result);
}

namespace {
void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}

bool
checkConfig(ConstElementPtr config, ElementPtr errors) {
    /* Specific configuration is under discussion, right now this accepts
     * the 'old' configuration, see header file
     */
    bool result = true;

    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for SQlite3 backend must be a map");
        result = false;
    } else {
        if (!config->contains(CONFIG_ITEM_DATABASE_FILE)) {
            addError(errors,
                     "Config for SQlite3 backend does not contain a '"
                     CONFIG_ITEM_DATABASE_FILE
                     "' value");
            result = false;
        } else if (!config->get(CONFIG_ITEM_DATABASE_FILE) ||
                   config->get(CONFIG_ITEM_DATABASE_FILE)->getType() !=
                   Element::string) {
            addError(errors, "value of " CONFIG_ITEM_DATABASE_FILE
                     " in SQLite3 backend is not a string");
            result = false;
        } else if (config->get(CONFIG_ITEM_DATABASE_FILE)->stringValue() ==
                   "") {
            addError(errors, "value of " CONFIG_ITEM_DATABASE_FILE
                     " in SQLite3 backend is empty");
            result = false;
        }
    }

    return (result);
}

} // end anonymous namespace

DataSourceClient *
createInstance(isc::data::ConstElementPtr config, std::string& error) {
    ElementPtr errors(Element::createList());
    if (!checkConfig(config, errors)) {
        error = "Configuration error: " + errors->str();
        return (NULL);
    }
    std::string dbfile = config->get(CONFIG_ITEM_DATABASE_FILE)->stringValue();
    try {
        boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
            new SQLite3Accessor(dbfile, "IN")); // XXX: avoid hardcode RR class
        return (new DatabaseClient(isc::dns::RRClass::IN(), sqlite3_accessor));
    } catch (const std::exception& exc) {
        error = std::string("Error creating sqlite3 datasource: ") + exc.what();
        return (NULL);
    } catch (...) {
        error = std::string("Error creating sqlite3 datasource, "
                            "unknown exception");
        return (NULL);
    }
}

void destroyInstance(DataSourceClient* instance) {
    delete instance;
}

} // end of namespace datasrc
} // end of namespace isc
