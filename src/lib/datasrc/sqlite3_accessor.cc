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
#include <util/filename.h>

using namespace std;

namespace isc {
namespace datasrc {

// The following enum and char* array define the SQL statements commonly
// used in this implementation.  Corresponding prepared statements (of
// type sqlite3_stmt*) are maintained in the statements_ array of the
// SQLite3Parameters structure.

enum StatementID {
    ZONE = 0,
    ANY = 1,
    BEGIN = 2,
    COMMIT = 3,
    ROLLBACK = 4,
    DEL_ZONE_RECORDS = 5,
    ADD_RECORD = 6,
    DEL_RECORD = 7,
    NUM_STATEMENTS = 8
};

const char* const text_statements[NUM_STATEMENTS] = {
    "SELECT id FROM zones WHERE name=?1 AND rdclass = ?2", // ZONE
    "SELECT rdtype, ttl, sigtype, rdata FROM records "     // ANY
    "WHERE zone_id=?1 AND name=?2",
    "BEGIN",                    // BEGIN
    "COMMIT",                   // COMMIT
    "ROLLBACK",                 // ROLLBACK
    "DELETE FROM records WHERE zone_id=?1", // DEL_ZONE_RECORDS
    "INSERT INTO records "      // ADD_RECORD
    "(zone_id, name, rname, ttl, rdtype, sigtype, rdata) "
    "VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7)",
    "DELETE FROM records WHERE zone_id=?1 AND name=?2 " // DEL_RECORD
    "AND rdtype=?3 AND rdata=?4"
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
class StatementExecuter {
public:
    // desc will be used on failure in the what() message of the resulting
    // DataSourceError exception.
    StatementExecuter(SQLite3Parameters* dbparameters, StatementID stmt_id,
                      const char* desc) :
        dbparameters_(dbparameters), stmt_id_(stmt_id), desc_(desc)
    {
        sqlite3_clear_bindings(dbparameters_->statements_[stmt_id_]);
    }

    ~StatementExecuter() {
        sqlite3_reset(dbparameters_->statements_[stmt_id_]);
    }

    void exec() {
        if (sqlite3_step(dbparameters_->statements_[stmt_id_]) !=
            SQLITE_DONE) {
            sqlite3_reset(dbparameters_->statements_[stmt_id_]);
            isc_throw(DataSourceError, "failed to " << desc_ << ": " <<
                      sqlite3_errmsg(dbparameters_->db_));
        }
    }

private:
    SQLite3Parameters* dbparameters_;
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

void
checkAndSetupSchema(Initializer* initializer) {
    sqlite3* const db = initializer->params_.db_;

    sqlite3_stmt* prepared = NULL;
    if (sqlite3_prepare_v2(db, "SELECT version FROM schema_version", -1,
                           &prepared, NULL) == SQLITE_OK &&
        sqlite3_step(prepared) == SQLITE_ROW) {
        initializer->params_.version_ = sqlite3_column_int(prepared, 0);
        sqlite3_finalize(prepared);
    } else {
        logger.info(DATASRC_SQLITE_SETUP);
        if (prepared != NULL) {
            sqlite3_finalize(prepared);
        }
        for (int i = 0; SCHEMA_LIST[i] != NULL; ++i) {
            if (sqlite3_exec(db, SCHEMA_LIST[i], NULL, NULL, NULL) !=
                SQLITE_OK) {
                isc_throw(SQLite3Error,
                          "Failed to set up schema " << SCHEMA_LIST[i]);
            }
        }
    }

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
    initializer.move(dbparameters_);
}

SQLite3Accessor::~SQLite3Accessor() {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_SQLITE_DROPCONN);
    if (dbparameters_->db_ != NULL) {
        close();
    }
    delete dbparameters_;
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
SQLite3Accessor::getZone(const isc::dns::Name& name) const {
    return (getZone(name.toText()));
}

std::pair<bool, int>
SQLite3Accessor::getZone(const string& name) const {
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
    std::pair<bool, int> result;
    if (rc == SQLITE_ROW) {
        result = std::pair<bool, int>(true, sqlite3_column_int(stmt, 0));
    } else {
        result = std::pair<bool, int>(false, 0);
    }
    // Free resources
    sqlite3_reset(stmt);

    return (result);
}

void
SQLite3Accessor::searchForRecords(int zone_id, const std::string& name) {
    resetSearch();

    sqlite3_stmt* const stmt = dbparameters_->statements_[ANY];
    if (sqlite3_bind_int(stmt, 1, zone_id) != SQLITE_OK) {
        isc_throw(DataSourceError,
                  "Error in sqlite3_bind_int() for zone_id " <<
                  zone_id << ": " << sqlite3_errmsg(dbparameters_->db_));
    }
    // use transient since name is a ref and may disappear
    if (sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT) !=
        SQLITE_OK) {
        isc_throw(DataSourceError,
                  "Error in sqlite3_bind_text() for name " <<
                  name << ": " << sqlite3_errmsg(dbparameters_->db_));
    }
}

namespace {
// This helper function converts from the unsigned char* type (used by
// sqlite3) to char* (wanted by std::string). Technically these types
// might not be directly convertable
// In case sqlite3_column_text() returns NULL, we just make it an
// empty string.
// The sqlite3parameters value is only used to check the error code if
// ucp == NULL
const char*
convertToPlainChar(const unsigned char* ucp,
                   SQLite3Parameters* dbparameters) {
    if (ucp == NULL) {
        // The field can really be NULL, in which case we return an
        // empty string, or sqlite may have run out of memory, in
        // which case we raise an error
        if (dbparameters != NULL &&
            sqlite3_errcode(dbparameters->db_) == SQLITE_NOMEM) {
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

bool
SQLite3Accessor::getNextRecord(std::string columns[], size_t column_count) {
    if (column_count != COLUMN_COUNT) {
            isc_throw(DataSourceError,
                    "Datasource backend caller did not pass a column array "
                    "of size " << COLUMN_COUNT << " to getNextRecord()");
    }

    sqlite3_stmt* current_stmt = dbparameters_->statements_[ANY];
    const int rc = sqlite3_step(current_stmt);

    if (rc == SQLITE_ROW) {
        for (int column = 0; column < column_count; ++column) {
            try {
                columns[column] = convertToPlainChar(sqlite3_column_text(
                                                     current_stmt, column),
                                                     dbparameters_);
            } catch (const std::bad_alloc&) {
                isc_throw(DataSourceError,
                        "bad_alloc in Sqlite3Connection::getNextRecord");
            }
        }
        return (true);
    } else if (rc == SQLITE_DONE) {
        // reached the end of matching rows
        resetSearch();
        return (false);
    }
    isc_throw(DataSourceError, "Unexpected failure in sqlite3_step: " <<
                               sqlite3_errmsg(dbparameters_->db_));
    // Compilers might not realize isc_throw always throws
    return (false);
}

void
SQLite3Accessor::resetSearch() {
    sqlite3_reset(dbparameters_->statements_[ANY]);
    sqlite3_clear_bindings(dbparameters_->statements_[ANY]);
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

    dbparameters_->updating_zone = true;
    dbparameters_->updated_zone_id = zone_info.second;

    StatementExecuter(dbparameters_, BEGIN,
                      "start an SQLite3 transaction").exec();

    if (replace) {
        StatementExecuter delzone_exec(dbparameters_, DEL_ZONE_RECORDS,
                                       "delete zone records");

        sqlite3_clear_bindings(dbparameters_->statements_[DEL_ZONE_RECORDS]);
        if (sqlite3_bind_int(dbparameters_->statements_[DEL_ZONE_RECORDS],
                             1, zone_info.second) != SQLITE_OK) {
            isc_throw(DataSourceError,
                      "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparameters_->db_));
        }

        delzone_exec.exec();
    }

    return (zone_info);
}

void
SQLite3Accessor::commitUpdateZone() {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "committing zone update on SQLite3 "
                  "data source without transaction");
    }

    StatementExecuter(dbparameters_, COMMIT,
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

    // We expect that ROLLBACK always succeeds.  But could that fail?
    // If so, what should we do?  Is it okay to simply propagate the
    // DataSourceError exception?
    StatementExecuter(dbparameters_, ROLLBACK,
                      "commit an SQLite3 transaction").exec();
    dbparameters_->updating_zone = false;
    dbparameters_->updated_zone_id = -1;
}

namespace {
// Commonly used code sequence for adding/deleting record
void
doUpdate(SQLite3Parameters* dbparams, StatementID stmt_id,
         const vector<string>& update_params, const char* exec_desc)
{
    sqlite3_stmt* const stmt = dbparams->statements_[stmt_id];
    StatementExecuter executer(dbparams, stmt_id, exec_desc);

    int param_id = 0;
    if (sqlite3_bind_int(stmt, ++param_id, dbparams->updated_zone_id)
        != SQLITE_OK) {
        isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                  sqlite3_errmsg(dbparams->db_));
    }
    BOOST_FOREACH(const string& column, update_params) {
        if (sqlite3_bind_text(stmt, ++param_id, column.c_str(), -1,
                              SQLITE_TRANSIENT) != SQLITE_OK) {
            isc_throw(DataSourceError, "failed to bind SQLite3 parameter: " <<
                      sqlite3_errmsg(dbparams->db_));
        }
    }
    executer.exec();
}
}

void
SQLite3Accessor::addRecordToZone(const vector<string>& columns) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "adding record to SQLite3 "
                  "data source without transaction");
    }
    if (columns.size() != ADD_COLUMN_COUNT) {
        isc_throw(DataSourceError, "adding incompatible number of columns "
                  "to SQLite3 data source: " << columns.size());
    }

    doUpdate(dbparameters_, ADD_RECORD, columns, "add record to zone");
}

void
SQLite3Accessor::deleteRecordInZone(const vector<string>& params) {
    if (!dbparameters_->updating_zone) {
        isc_throw(DataSourceError, "deleting record in SQLite3 "
                  "data source without transaction");
    }
    if (params.size() != DEL_PARAM_COUNT) {
        isc_throw(DataSourceError, "incompatible # of parameters for "
                  "deleting in SQLite3 data source: " << params.size());
    }

    doUpdate(dbparameters_, DEL_RECORD, params, "delete record from zone");
}

}
}
