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
    NUM_STATEMENTS = 10
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
    "WHERE zone_id = ?1 ORDER BY name, rdtype"
};

struct SQLite3Parameters {
    SQLite3Parameters() :
        db_(NULL), version_(-1), updating_zone(false), updated_zone_id(-1)
    {
        for (int i = 0; i < NUM_STATEMENTS; ++i) {
            statements_[i] = NULL;
        }
    }

    sqlite3* db_;
    int version_;
    sqlite3_stmt* statements_[NUM_STATEMENTS];
    bool updating_zone;         // whether or not updating the zone
    int updated_zone_id;        // valid only when updating_zone is true
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
        dbparameters_(dbparameters), stmt_id_(stmt_id), desc_(desc)
    {
        sqlite3_clear_bindings(dbparameters_.statements_[stmt_id_]);
    }

    ~StatementProcessor() {
        sqlite3_reset(dbparameters_.statements_[stmt_id_]);
    }

    void exec() {
        if (sqlite3_step(dbparameters_.statements_[stmt_id_]) != SQLITE_DONE) {
            sqlite3_reset(dbparameters_.statements_[stmt_id_]);
            isc_throw(DataSourceError, "failed to " << desc_ << ": " <<
                      sqlite3_errmsg(dbparameters_.db_));
        }
    }

private:
    SQLite3Parameters& dbparameters_;
    const StatementID stmt_id_;
    const char* const desc_;
};

SQLite3Accessor::SQLite3Accessor(const std::string& filename,
                                 const isc::dns::RRClass& rrclass) :
    dbparameters_(new SQLite3Parameters),
    filename_(filename),
    class_(rrclass.toText()),
    database_name_("sqlite3_" +
                   isc::util::Filename(filename).nameAndExtension())
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_NEWCONN);

    open(filename);
}

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
        for (int i = 0; i < NUM_STATEMENTS; ++i) {
            sqlite3_finalize(params_.statements_[i]);
        }

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
    NULL
};

sqlite3_stmt*
prepare(sqlite3* const db, const char* const statement) {
    sqlite3_stmt* prepared = NULL;
    if (sqlite3_prepare_v2(db, statement, -1, &prepared, NULL) != SQLITE_OK) {
        isc_throw(SQLite3Error, "Could not prepare SQLite statement: " <<
                  statement);
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

    for (int i = 0; i < NUM_STATEMENTS; ++i) {
        initializer->params_.statements_[i] = prepare(db, text_statements[i]);
    }
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

    // XXX: sqlite3_finalize() could fail.  What should we do in that case?
    for (int i = 0; i < NUM_STATEMENTS; ++i) {
        sqlite3_finalize(dbparameters_->statements_[i]);
        dbparameters_->statements_[i] = NULL;
    }

    sqlite3_close(dbparameters_->db_);
    dbparameters_->db_ = NULL;
}

std::pair<bool, int>
SQLite3Accessor::getZone(const std::string& name) const {
    int rc;
    sqlite3_stmt* const stmt = dbparameters_->statements_[ZONE];

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
                                                              column));
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

    // This helper method converts from the unsigned char* type (used by
    // sqlite3) to char* (wanted by std::string). Technically these types
    // might not be directly convertable
    // In case sqlite3_column_text() returns NULL, we just make it an
    // empty string, unless it was caused by a memory error
    const char* convertToPlainChar(const unsigned char* ucp) {
        if (ucp == NULL) {
            // The field can really be NULL, in which case we return an
            // empty string, or sqlite may have run out of memory, in
            // which case we raise an error
            if (sqlite3_errcode(accessor_->dbparameters_->db_)
                                == SQLITE_NOMEM) {
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

    const IteratorType iterator_type_;
    boost::shared_ptr<const SQLite3Accessor> accessor_;
    sqlite3_stmt *statement_;
    const std::string name_;
};

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

pair<bool, int>
SQLite3Accessor::startUpdateZone(const string& zone_name, const bool replace) {
    if (dbparameters_->updating_zone) {
        isc_throw(DataSourceError,
                  "duplicate zone update on SQLite3 data source");
    }

    const pair<bool, int> zone_info(getZone(zone_name));
    if (!zone_info.first) {
        return (zone_info);
    }

    StatementProcessor(*dbparameters_, BEGIN,
                       "start an SQLite3 transaction").exec();

    if (replace) {
        try {
            StatementProcessor delzone_exec(*dbparameters_, DEL_ZONE_RECORDS,
                                            "delete zone records");

            sqlite3_clear_bindings(
                dbparameters_->statements_[DEL_ZONE_RECORDS]);
            if (sqlite3_bind_int(dbparameters_->statements_[DEL_ZONE_RECORDS],
                                 1, zone_info.second) != SQLITE_OK) {
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

    dbparameters_->updating_zone = true;
    dbparameters_->updated_zone_id = zone_info.second;

    return (zone_info);
}

void
SQLite3Accessor::commitUpdateZone() {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "committing zone update on SQLite3 "
                  "data source without transaction");
    }

    StatementProcessor(*dbparameters_, COMMIT,
                       "commit an SQLite3 transaction").exec();
    dbparameters_->updating_zone = false;
    dbparameters_->updated_zone_id = -1;
}

void
SQLite3Accessor::rollbackUpdateZone() {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "rolling back zone update on SQLite3 "
                  "data source without transaction");
    }

    StatementProcessor(*dbparameters_, ROLLBACK,
                       "rollback an SQLite3 transaction").exec();
    dbparameters_->updating_zone = false;
    dbparameters_->updated_zone_id = -1;
}

namespace {
// Commonly used code sequence for adding/deleting record
template <typename COLUMNS_TYPE>
void
doUpdate(SQLite3Parameters& dbparams, StatementID stmt_id,
         COLUMNS_TYPE update_params, const char* exec_desc)
{
    sqlite3_stmt* const stmt = dbparams.statements_[stmt_id];
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
        if (sqlite3_bind_text(stmt, ++param_id, update_params[i].c_str(), -1,
                              SQLITE_TRANSIENT) != SQLITE_OK) {
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

namespace {
void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}
} // end anonymous namespace

bool
checkConfig(ConstElementPtr config, ElementPtr errors) {
    bool result = true;
    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for SQlite3 backend must be a map");
        result = false;
    } else {
        if (!config->contains("file")) {
            addError(errors,
                     "Config for SQlite3 backend does not contain a 'file' value");
            result = false;
        } else if (!config->get("file") ||
                   config->get("file")->getType() != Element::string) {
            addError(errors, "file value in SQLite3 backend is not a string");
            result = false;
        } else if (config->get("file")->stringValue() == "") {
            addError(errors, "file value in SQLite3 backend is empty");
            result = false;
        }

        if (!config->contains("class")) {
            addError(errors, "Config for SQlite3 backend does not contain a 'class' value");
            result = false;
        } else if (!config->get("class") ||
                   config->get("class")->getType() != Element::string) {
            addError(errors, "class value in SQLite3 backend is not a string");
            result = false;
        } else {
            try {
                isc::dns::RRClass rrclass(config->get("class")->stringValue());
            } catch (const isc::dns::InvalidRRClass& ivrc) {
                addError(errors, ivrc.what());
                result = false;
            } catch (const isc::dns::IncompleteRRClass& icrc) {
                addError(errors, icrc.what());
                result = false;
            }
        }
    }

    return (result);
}

DataSourceClient *
createInstance(isc::data::ConstElementPtr config) {
    ElementPtr errors(Element::createList());
    if (!checkConfig(config, errors)) {
        isc_throw(DataSourceConfigError, errors->str());
    }
    isc::dns::RRClass rrclass(config->get("class")->stringValue());
    std::string dbfile = config->get("file")->stringValue();
    boost::shared_ptr<DatabaseAccessor> sqlite3_accessor(
        new SQLite3Accessor(dbfile, rrclass));
    return (new DatabaseClient(rrclass, sqlite3_accessor));
}

void destroyInstance(DataSourceClient* instance) {
    delete instance;
}

} // end of namespace datasrc
} // end of namespace isc
