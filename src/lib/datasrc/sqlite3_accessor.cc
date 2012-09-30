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
#include <utility>
#include <vector>

#include <exceptions/exceptions.h>

#include <datasrc/sqlite3_accessor.h>
#include <datasrc/logger.h>
#include <datasrc/data_source.h>
#include <datasrc/factory.h>
#include <datasrc/database.h>
#include <util/filename.h>

using namespace std;
using namespace isc::data;

namespace {
// Expected schema.  The major version must match else there is an error.  If
// the minor version of the database is less than this, a warning is output.
//
// It is assumed that a program written to run on m.n of the database will run
// with a database version m.p, where p is any number.  However, if p < n,
// we assume that the database structure was upgraded for some reason, and that
// some advantage may result if the database is upgraded. Conversely, if p > n,
// The database is at a later version than the program was written for and the
// program may not be taking advantage of features (possibly performance
// improvements) added to the database.
const int SQLITE_SCHEMA_MAJOR_VERSION = 2;
const int SQLITE_SCHEMA_MINOR_VERSION = 1;
}

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
    LOW_DIFF_ID = 12,
    HIGH_DIFF_ID = 13,
    DIFF_RECS = 14,
    NSEC3 = 15,
    NSEC3_PREVIOUS = 16,
    NSEC3_LAST = 17,
    ADD_NSEC3_RECORD = 18,
    DEL_ZONE_NSEC3_RECORDS = 19,
    DEL_NSEC3_RECORD = 20,
    NUM_STATEMENTS = 21
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
    // The following iterates the whole zone. As the NSEC3 records
    // (and corresponding RRSIGs) live in separate table, we need to
    // take both of them. As the RRSIGs are for NSEC3s in the other
    // table, we can easily hardcode the sigtype.
    //
    // The extra column is so we can order it by rname. This is to
    // preserve the previous order, mostly for tests.
    // TODO: Is it possible to get rid of the ordering?
    "SELECT rdtype, ttl, sigtype, rdata, name, rname FROM records " // ITERATE
        "WHERE zone_id = ?1 "
        "UNION "
        "SELECT rdtype, ttl, \"NSEC3\", rdata, owner, owner FROM nsec3 "
        "WHERE zone_id = ?1 ORDER by rname, rdtype",
    /*
     * This one looks for previous name with NSEC record. It is done by
     * using the reversed name. The NSEC is checked because we need to
     * skip glue data, which don't have the NSEC.
     */
    "SELECT name FROM records " // FIND_PREVIOUS
        "WHERE zone_id=?1 AND rdtype = 'NSEC' AND "
        "rname < ?2 ORDER BY rname DESC LIMIT 1",
    "INSERT INTO diffs "        // ADD_RECORD_DIFF
        "(zone_id, version, operation, name, rrtype, ttl, rdata) "
        "VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7)",

    // Two statements to select the lowest ID and highest ID in a set of
    // differences.
    "SELECT id FROM diffs "     // LOW_DIFF_ID
        "WHERE zone_id=?1 AND version=?2 and OPERATION=?3 "
        "ORDER BY id ASC LIMIT 1",
    "SELECT id FROM diffs "     // HIGH_DIFF_ID
        "WHERE zone_id=?1 AND version=?2 and OPERATION=?3 "
        "ORDER BY id DESC LIMIT 1",

    // In the next statement, note the redundant ID.  This is to ensure
    // that the columns match the column IDs passed to the iterator
    "SELECT rrtype, ttl, id, rdata, name FROM diffs "   // DIFF_RECS
        "WHERE zone_id=?1 AND id>=?2 and id<=?3 "
        "ORDER BY id ASC",

    // NSEC3: Query to get the NSEC3 records
    //
    // The "1" in SELECT is for positioning the rdata column to the
    // expected position, so we can reuse the same code as for other
    // lookups.
    "SELECT rdtype, ttl, 1, rdata FROM nsec3 WHERE zone_id=?1 AND "
        "hash=?2",
    // NSEC3_PREVIOUS: For getting the previous NSEC3 hash
    "SELECT DISTINCT hash FROM nsec3 WHERE zone_id=?1 AND hash < ?2 "
        "ORDER BY hash DESC LIMIT 1",
    // NSEC3_LAST: And for wrap-around
    "SELECT DISTINCT hash FROM nsec3 WHERE zone_id=?1 "
        "ORDER BY hash DESC LIMIT 1",
    // ADD_NSEC3_RECORD: Add NSEC3-related (NSEC3 or NSEC3-covering RRSIG) RR
    "INSERT INTO nsec3 (zone_id, hash, owner, ttl, rdtype, rdata) "
    "VALUES (?1, ?2, ?3, ?4, ?5, ?6)",
    // DEL_ZONE_NSEC3_RECORDS: delete all NSEC3-related records from the zone
    "DELETE FROM nsec3 WHERE zone_id=?1",
    // DEL_NSEC3_RECORD: delete specified NSEC3-related records
    "DELETE FROM nsec3 WHERE zone_id=?1 AND hash=?2 "
    "AND rdtype=?3 AND rdata=?4"
};

struct SQLite3Parameters {
    SQLite3Parameters() :
        db_(NULL), major_version_(-1), minor_version_(-1),
        in_transaction(false), updating_zone(false), updated_zone_id(-1)
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
    int major_version_;
    int minor_version_;
    bool in_transaction; // whether or not a transaction has been started
    bool updating_zone;          // whether or not updating the zone
    int updated_zone_id;        // valid only when in_transaction is true
    string updated_zone_origin_; // ditto, and only needed to handle NSEC3s
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
//
// The bindXXX methods are straightforward wrappers for the corresponding
// sqlite3_bind_xxx functions that make bindings with the given parameters
// on the statement maintained in this class.
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

    void bindInt(int index, int val) {
        if (sqlite3_bind_int(stmt_, index, val) != SQLITE_OK) {
            isc_throw(DataSourceError,
                      "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparameters_.db_));
        }
    }

    void bindInt64(int index, sqlite3_int64 val) {
        if (sqlite3_bind_int64(stmt_, index, val) != SQLITE_OK) {
            isc_throw(DataSourceError,
                      "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparameters_.db_));
        }
    }

    // For simplicity, we assume val is a NULL-terminated string, and the
    // entire non NUL characters are to be bound.  The destructor parameter
    // is normally either SQLITE_TRANSIENT or SQLITE_STATIC.
    void bindText(int index, const char* val, void(*destructor)(void*)) {
        if (sqlite3_bind_text(stmt_, index, val, -1, destructor)
            != SQLITE_OK) {
            isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparameters_.db_));
        }
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
    "CREATE TABLE schema_version (version INTEGER NOT NULL, "
        "minor INTEGER NOT NULL DEFAULT 0)",
    "INSERT INTO schema_version VALUES (2, 1)",
    "CREATE TABLE zones (id INTEGER PRIMARY KEY, "
    "name TEXT NOT NULL COLLATE NOCASE, "
    "rdclass TEXT NOT NULL COLLATE NOCASE DEFAULT 'IN', "
    "dnssec BOOLEAN NOT NULL DEFAULT 0)",
    "CREATE INDEX zones_byname ON zones (name)",
    "CREATE TABLE records (id INTEGER PRIMARY KEY, "
        "zone_id INTEGER NOT NULL, name TEXT NOT NULL COLLATE NOCASE, "
        "rname TEXT NOT NULL COLLATE NOCASE, ttl INTEGER NOT NULL, "
        "rdtype TEXT NOT NULL COLLATE NOCASE, sigtype TEXT COLLATE NOCASE, "
        "rdata TEXT NOT NULL)",
    "CREATE INDEX records_byname ON records (name)",
    "CREATE INDEX records_byrname ON records (rname)",
    // The next index is a tricky one.  It's necessary for
    // FIND_PREVIOUS to use the index efficiently; since there's an
    // "inequality", the rname column must be placed later.  records_byrname
    // may not be sufficient especially when the zone is not signed (and
    // defining a separate index for rdtype only doesn't work either; SQLite3
    // would then create a temporary B-tree for "ORDER BY").
    "CREATE INDEX records_bytype_and_rname ON records (rdtype, rname)",
    "CREATE TABLE nsec3 (id INTEGER PRIMARY KEY, zone_id INTEGER NOT NULL, "
        "hash TEXT NOT NULL COLLATE NOCASE, "
        "owner TEXT NOT NULL COLLATE NOCASE, "
        "ttl INTEGER NOT NULL, rdtype TEXT NOT NULL COLLATE NOCASE, "
        "rdata TEXT NOT NULL)",
    "CREATE INDEX nsec3_byhash ON nsec3 (hash)",
    // Enforce that only one NSEC3 RR exists for an owner name in the zone.
    "CREATE UNIQUE INDEX nsec3_by_zoneid_and_owner ON nsec3 (zone_id, owner)",
    "CREATE TABLE diffs (id INTEGER PRIMARY KEY, "
        "zone_id INTEGER NOT NULL, "
        "version INTEGER NOT NULL, "
        "operation INTEGER NOT NULL, "
        "name TEXT NOT NULL COLLATE NOCASE, "
        "rrtype TEXT NOT NULL COLLATE NOCASE, "
        "ttl INTEGER NOT NULL, "
        "rdata TEXT NOT NULL)",
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
int checkSchemaVersionElement(sqlite3* db, const char* const query) {
    sqlite3_stmt* prepared = NULL;
    // At this point in time, the database might be exclusively locked, in
    // which case even prepare() will return BUSY, so we may need to try a
    // few times
    for (size_t i = 0; i < 50; ++i) {
        int rc = sqlite3_prepare_v2(db, query, -1, &prepared, NULL);
        if (rc == SQLITE_ERROR) {
            // this is the error that is returned when the table does not
            // exist
            sqlite3_finalize(prepared);
            return (-1);
        } else if (rc == SQLITE_OK) {
            break;
        } else if (rc != SQLITE_BUSY || i == 50) {
            sqlite3_finalize(prepared);
            isc_throw(SQLite3Error, "Unable to prepare version query: "
                        << rc << " " << sqlite3_errmsg(db));
        }
        doSleep();
    }
    if (sqlite3_step(prepared) != SQLITE_ROW) {
        sqlite3_finalize(prepared);
        isc_throw(SQLite3Error,
                    "Unable to query version: " << sqlite3_errmsg(db));
    }
    int version = sqlite3_column_int(prepared, 0);
    sqlite3_finalize(prepared);
    return (version);
}

// Returns the schema major and minor version numbers in a pair.
// Returns (-1, -1) if the table does not exist, (1, 0) for a V1
// database, and (n, m) for any other.
pair<int, int> checkSchemaVersion(sqlite3* db) {
    int major = checkSchemaVersionElement(db,
        "SELECT version FROM schema_version");
    if (major == -1) {
        return (make_pair(-1, -1));
    } else if (major == 1) {
        return (make_pair(1, 0));
    } else {
        int minor = checkSchemaVersionElement(db,
            "SELECT minor FROM schema_version");
        return (make_pair(major, minor));
    }
}

// A helper class used in createDatabase() below so we manage the one shot
// transaction safely.
class ScopedTransaction {
public:
    ScopedTransaction(sqlite3* db) : db_(NULL) {
        // try for 5 secs (50*0.1)
        for (size_t i = 0; i < 50; ++i) {
            const int rc = sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION",
                                        NULL, NULL, NULL);
            if (rc == SQLITE_OK) {
                break;
            } else if (rc != SQLITE_BUSY || i == 50) {
                isc_throw(SQLite3Error, "Unable to acquire exclusive lock "
                          "for database creation: " << sqlite3_errmsg(db));
            }
            doSleep();
        }
        // Hold the DB pointer once we have successfully acquired the lock.
        db_ = db;
    }
    ~ScopedTransaction() {
        if (db_ != NULL) {
            // Note: even rollback could fail in theory, but in that case
            // we cannot do much for safe recovery anyway.  We could at least
            // log the event, but for now don't even bother to do that, with
            // the expectation that we'll soon stop creating the schema in this
            // module.
            sqlite3_exec(db_, "ROLLBACK", NULL, NULL, NULL);
        }
    }
    void commit() {
        if (sqlite3_exec(db_, "COMMIT TRANSACTION", NULL, NULL, NULL) !=
            SQLITE_OK) {
            isc_throw(SQLite3Error, "Unable to commit newly created database "
                      "schema: " << sqlite3_errmsg(db_));
        }
        db_ = NULL;
    }

private:
    sqlite3* db_;
};

// return db version
pair<int, int>
createDatabase(sqlite3* db, const std::string& name) {
    logger.warn(DATASRC_SQLITE_SETUP).arg(name);

    // try to get an exclusive lock. Once that is obtained, do the version
    // check *again*, just in case this process was racing another
    ScopedTransaction trasaction(db);
    pair<int, int> schema_version = checkSchemaVersion(db);
    if (schema_version.first == -1) {
        for (int i = 0; SCHEMA_LIST[i] != NULL; ++i) {
            if (sqlite3_exec(db, SCHEMA_LIST[i], NULL, NULL, NULL) !=
                SQLITE_OK) {
                isc_throw(SQLite3Error,
                          "Failed to set up schema " << SCHEMA_LIST[i]);
            }
        }
        trasaction.commit();

        // Return the version.  We query again to ensure that the only point
        // in which the current schema version is defined is in the create
        // statements.
        schema_version = checkSchemaVersion(db);
    }

    return (schema_version);
}

void
checkAndSetupSchema(Initializer* initializer, const std::string& name) {
    sqlite3* const db = initializer->params_.db_;

    pair<int, int> schema_version = checkSchemaVersion(db);
    if (schema_version.first == -1) {
        schema_version = createDatabase(db, name);
    } else if (schema_version.first != SQLITE_SCHEMA_MAJOR_VERSION) {
        LOG_ERROR(logger, DATASRC_SQLITE_INCOMPATIBLE_VERSION)
            .arg(schema_version.first).arg(schema_version.second)
            .arg(SQLITE_SCHEMA_MAJOR_VERSION).arg(SQLITE_SCHEMA_MINOR_VERSION);
        isc_throw(IncompatibleDbVersion,
                  "incompatible SQLite3 database version: " <<
                  schema_version.first << "." << schema_version.second);
    } else if (schema_version.second < SQLITE_SCHEMA_MINOR_VERSION) {
        LOG_WARN(logger, DATASRC_SQLITE_COMPATIBLE_VERSION)
            .arg(schema_version.first).arg(schema_version.second)
            .arg(SQLITE_SCHEMA_MAJOR_VERSION).arg(SQLITE_SCHEMA_MINOR_VERSION);
    }

    initializer->params_.major_version_ = schema_version.first;
    initializer->params_.minor_version_ = schema_version.second;
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

    checkAndSetupSchema(&initializer, name);
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

    // What kind of query it is - selection of the statement for DB
    enum QueryType {
        QT_ANY, // Directly for a domain
        QT_SUBDOMAINS, // Subdomains of a given domain
        QT_NSEC3 // Domain in the NSEC3 namespace (the name is is the hash,
                 // not the whole name)
    };

    // Construct an iterator for records with a specific name. When constructed
    // this way, the getNext() call will copy all fields except name
    Context(const boost::shared_ptr<const SQLite3Accessor>& accessor, int id,
            const std::string& name, QueryType qtype) :
        iterator_type_(qtype == QT_NSEC3 ? ITT_NSEC3 : ITT_NAME),
        accessor_(accessor),
        statement_(NULL),
        name_(name)
    {
        // Choose the statement text depending on the query type
        const char* statement(NULL);
        switch (qtype) {
            case QT_ANY:
                statement = text_statements[ANY];
                break;
            case QT_SUBDOMAINS:
                statement = text_statements[ANY_SUB];
                break;
            case QT_NSEC3:
                statement = text_statements[NSEC3];
                break;
            default:
                // Can Not Happen - there isn't any other type of query
                // and all the calls to the constructor are from this
                // file. Therefore no way to test it throws :-(.
                isc_throw(Unexpected,
                          "Invalid qtype passed - unreachable code branch "
                          "reached");
        }

        // We create the statement now and then just keep getting data from it
        statement_ = prepare(accessor->dbparameters_->db_, statement);
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
            // The NSEC3 lookup does not provide the SIGTYPE, it is not
            // necessary and not contained in the table.
            if (iterator_type_ != ITT_NSEC3) {
                copyColumn(data, SIGTYPE_COLUMN);
            }
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
        ITT_NAME,
        ITT_NSEC3
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
                                           subdomains ?
                                           Context::QT_SUBDOMAINS :
                                           Context::QT_ANY)));
}

DatabaseAccessor::IteratorContextPtr
SQLite3Accessor::getNSEC3Records(const std::string& hash, int id) const {
    return (IteratorContextPtr(new Context(shared_from_this(), id, hash,
                                           Context::QT_NSEC3)));
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
            int low_id = findIndex(LOW_DIFF_ID, zone_id, start, DIFF_DELETE);
            int high_id = findIndex(HIGH_DIFF_ID, zone_id, end, DIFF_ADD);

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
    /// \exception any Varied
    bool getNext(std::string (&data)[COLUMN_COUNT]) {

        if (last_status_ != SQLITE_DONE) {
            // Last call (if any) didn't reach end of result set, so we
            // can read another row from it.
            //
            // Get a pointer to the statement for brevity (this does not
            // transfer ownership of the statement to this class, so there is
            // no need to tidy up after we have finished using it).
            sqlite3_stmt* stmt =
                accessor_->dbparameters_->getStatement(DIFF_RECS);

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
        if ((sqlite3_reset(stmt) != SQLITE_OK) ||
            (sqlite3_clear_bindings(stmt) != SQLITE_OK)) {
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
            rc = sqlite3_step(stmt);
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
    /// \param diff Code to delete record additions or deletions
    ///
    /// \return int ID of the row in the difss table corresponding to the
    ///         statement.
    ///
    /// \exception TooLittleData Internal error, no result returned when one
    ///            was expected.
    /// \exception NoSuchSerial Serial number not found.
    /// \exception NoDiffsData No data for this zone found in diffs table
    int findIndex(StatementID stindex, int zone_id, uint32_t serial, int diff) {

        // Set up the statement
        reset(stindex);
        bindInt(stindex, 1, zone_id);
        bindInt(stindex, 2, serial);
        bindInt(stindex, 3, diff);

        // Execute the statement
        int result = -1;
        try {
            result = getSingleValue(stindex);

        } catch (const TooLittleData&) {

            // No data returned but the SQL query succeeded.  Only possibility
            // is that there is no entry in the differences table for the given
            // zone and version.
            isc_throw(NoSuchSerial, "No entry in differences table for" <<
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
        // First, clear all current data from tables.
        typedef pair<StatementID, const char* const> StatementSpec;
        const StatementSpec delzone_stmts[] =
            { StatementSpec(DEL_ZONE_RECORDS, "delete zone records"),
              StatementSpec(DEL_ZONE_NSEC3_RECORDS,
                            "delete zone NSEC3 records") };
        try {
            for (size_t i = 0;
                 i < sizeof(delzone_stmts) / sizeof(delzone_stmts[0]);
                 ++i) {
                StatementProcessor delzone_proc(*dbparameters_,
                                                delzone_stmts[i].first,
                                                delzone_stmts[i].second);
                delzone_proc.bindInt(1, zone_info.second);
                delzone_proc.exec();
            }
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
    dbparameters_->updated_zone_origin_ = zone_name;

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
    dbparameters_->updating_zone = false;
    dbparameters_->updated_zone_id = -1;
    dbparameters_->updated_zone_origin_.clear();
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
    dbparameters_->updating_zone = false;
    dbparameters_->updated_zone_id = -1;
    dbparameters_->updated_zone_origin_.clear();
}

namespace {
// Commonly used code sequence for adding/deleting record
template <typename COLUMNS_TYPE>
void
doUpdate(SQLite3Parameters& dbparams, StatementID stmt_id,
         COLUMNS_TYPE update_params, const char* exec_desc)
{
    StatementProcessor proc(dbparams, stmt_id, exec_desc);

    int param_id = 0;
    proc.bindInt(++param_id, dbparams.updated_zone_id);
    const size_t column_count =
        sizeof(update_params) / sizeof(update_params[0]);
    for (int i = 0; i < column_count; ++i) {
        // The old sqlite3 data source API assumes NULL for an empty column.
        // We need to provide compatibility at least for now.
        proc.bindText(++param_id, update_params[i].empty() ? NULL :
                      update_params[i].c_str(), SQLITE_TRANSIENT);
    }
    proc.exec();
}
}

void
SQLite3Accessor::addRecordToZone(const string (&columns)[ADD_COLUMN_COUNT]) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "adding record to SQLite3 "
                  "data source without transaction");
    }
    doUpdate<const string (&)[ADD_COLUMN_COUNT]>(
        *dbparameters_, ADD_RECORD, columns, "add record to zone");
}

void
SQLite3Accessor::addNSEC3RecordToZone(
    const string (&columns)[ADD_NSEC3_COLUMN_COUNT])
{
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "adding NSEC3-related record to SQLite3 "
                  "data source without transaction");
    }

    // XXX: the current implementation of SQLite3 schema requires the 'owner'
    // column, and the current implementation of getAllRecords() relies on it,
    // while the addNSEC3RecordToZone interface doesn't provide it explicitly.
    // We should revisit it at the design level, but for now we internally
    // convert the given parameter to satisfy the internal requirements.
    const string sqlite3_columns[ADD_NSEC3_COLUMN_COUNT + 1] =
        { columns[ADD_NSEC3_HASH],
          columns[ADD_NSEC3_HASH] + "." + dbparameters_->updated_zone_origin_,
          columns[ADD_NSEC3_TTL],
          columns[ADD_NSEC3_TYPE], columns[ADD_NSEC3_RDATA] };
    doUpdate<const string (&)[ADD_NSEC3_COLUMN_COUNT + 1]>(
        *dbparameters_, ADD_NSEC3_RECORD, sqlite3_columns,
        "add NSEC3 record to zone");
}

void
SQLite3Accessor::deleteRecordInZone(const string (&params)[DEL_PARAM_COUNT]) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "deleting record in SQLite3 "
                  "data source without transaction");
    }
    doUpdate<const string (&)[DEL_PARAM_COUNT]>(
        *dbparameters_, DEL_RECORD, params, "delete record from zone");
}

void
SQLite3Accessor::deleteNSEC3RecordInZone(
    const string (&params)[DEL_PARAM_COUNT])
{
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "deleting NSEC3-related record in SQLite3 "
                  "data source without transaction");
    }
    doUpdate<const string (&)[DEL_PARAM_COUNT]>(
        *dbparameters_, DEL_NSEC3_RECORD, params,
        "delete NSEC3 record from zone");
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

    StatementProcessor proc(*dbparameters_, ADD_RECORD_DIFF,
                            "add record diff");
    int param_id = 0;
    proc.bindInt(++param_id, zone_id);
    proc.bindInt64(++param_id, serial);
    proc.bindInt(++param_id, operation);
    for (int i = 0; i < DIFF_PARAM_COUNT; ++i) {
        proc.bindText(++param_id, params[i].c_str(), SQLITE_TRANSIENT);
    }
    proc.exec();
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

std::string
SQLite3Accessor::findPreviousNSEC3Hash(int zone_id, const std::string& hash)
    const
{
    sqlite3_stmt* const stmt = dbparameters_->getStatement(NSEC3_PREVIOUS);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    if (sqlite3_bind_int(stmt, 1, zone_id) != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind zone ID " << zone_id <<
                  " to SQL statement (find previous NSEC3): " <<
                  sqlite3_errmsg(dbparameters_->db_));
    }
    if (sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_STATIC) !=
        SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not bind hash " << hash <<
                  " to SQL statement (find previous NSEC3): " <<
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

    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        // Some kind of error
        isc_throw(SQLite3Error, "Could not get data for previous hash");
    }

    if (rc == SQLITE_DONE) {
        // No NSEC3 records before this hash. This means we should wrap
        // around and take the last one.
        sqlite3_stmt* const stmt = dbparameters_->getStatement(NSEC3_LAST);
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

        if (sqlite3_bind_int(stmt, 1, zone_id) != SQLITE_OK) {
            isc_throw(SQLite3Error, "Could not bind zone ID " << zone_id <<
                      " to SQL statement (find last NSEC3): " <<
                      sqlite3_errmsg(dbparameters_->db_));
        }

        const int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            // We found it
            result = convertToPlainChar(sqlite3_column_text(stmt, 0),
                                        dbparameters_->db_);
        }
        sqlite3_reset(stmt);

        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            // Some kind of error
            isc_throw(SQLite3Error, "Could not get data for last hash");
        }

        if (rc == SQLITE_DONE) {
            // No NSEC3 at all in the zone. Well, bad luck, but you should not
            // have asked in the first place.
            isc_throw(DataSourceError, "No NSEC3 in this zone");
        }
    }

    return (result);
}

} // end of namespace datasrc
} // end of namespace isc
