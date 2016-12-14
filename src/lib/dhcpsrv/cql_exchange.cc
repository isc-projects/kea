// Copyright (C) 2016 Deutsche Telekom AG.
//
// Author: Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <dhcpsrv/cql_exchange.h>

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/db_exceptions.h>

/// @name CqlBind auxiliary functions for binding data into Cassandra format:
/// @{

/// @todo These void* cast are unsafe. See ticket #4525.
static CassError
CqlBindNone(CassStatement* statement, size_t index, void*) {
    return cass_statement_bind_null(statement, index);
}

static CassError
CqlBindBool(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_bool(statement, index,
                                    *(static_cast<cass_bool_t*>(value)));
}

static CassError
CqlBindInt32(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int32(statement, index,
                                     *(static_cast<cass_int32_t*>(value)));
}

static CassError
CqlBindInt64(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int64(statement, index,
                                     *(static_cast<cass_int64_t*>(value)));
}

static CassError
CqlBindTimestamp(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int64(statement, index,
                                     *(static_cast<cass_int64_t*>(value)));
}

static CassError
CqlBindString(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_string(
        statement, index, static_cast<std::string*>(value)->c_str());
}

static CassError
CqlBindBytes(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_bytes(
        statement, index, static_cast<std::vector<cass_byte_t>*>(value)->data(),
        static_cast<std::vector<cass_byte_t>*>(value)->size());
}

static CassError
CqlBindUuid(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_uuid(statement, index,
                                    *static_cast<CassUuid*>(value));
}
/// @}

static CassError
CqlGetNone(const CassValue*, void*) {
    return CASS_OK;
}

static CassError
CqlGetBool(const CassValue* value, void* data) {
    return cass_value_get_bool(value, static_cast<cass_bool_t*>(data));
}

static CassError
CqlGetInt32(const CassValue* value, void* data) {
    return cass_value_get_int32(value, static_cast<cass_int32_t*>(data));
}

static CassError
CqlGetInt64(const CassValue* value, void* data) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError
CqlGetTimestamp(const CassValue* value, void* data) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError
CqlGetString(const CassValue* value, void* data) {
    const char* dataValue;
    size_t sizeValue;
    CassError cassError = cass_value_get_string(
        value, static_cast<const char**>(&dataValue), &sizeValue);
    static_cast<std::string*>(data)->assign(dataValue, dataValue + sizeValue);
    return cassError;
}

static CassError
CqlGetBytes(const CassValue* value, void* data) {
    const cass_byte_t* dataValue;
    size_t sizeValue;
    CassError cassError = cass_value_get_bytes(
        value, static_cast<const cass_byte_t**>(&dataValue), &sizeValue);
    static_cast<std::vector<cass_byte_t>*>(data)->assign(dataValue,
                                                         dataValue + sizeValue);
    return cassError;
}

static CassError
CqlGetUuid(const CassValue* value, void* data) {
    return cass_value_get_uuid(value, static_cast<CassUuid*>(data));
}

namespace isc {
namespace dhcp {

struct CqlFunctionData CqlFunctions[] = {
    {CqlBindNone, CqlGetNone},           {CqlBindBool, CqlGetBool},
    {CqlBindInt32, CqlGetInt32},         {CqlBindInt64, CqlGetInt64},
    {CqlBindTimestamp, CqlGetTimestamp}, {CqlBindString, CqlGetString},
    {CqlBindBytes, CqlGetBytes},         {CqlBindUuid, CqlGetUuid}};

ExchangeDataType
CqlCommon::getDataType(const uint32_t stindex,
                       int pindex,
                       const SqlExchange& exchange,
                       const CqlTaggedStatement* tagged_statements) {
    if (tagged_statements[stindex].params_ &&
        tagged_statements[stindex].params_[pindex]) {
        const ExchangeColumnInfoContainerName& idx =
            exchange.parameters_.get<1>();
        const ExchangeColumnInfoContainerNameRange& range =
            idx.equal_range(tagged_statements[stindex].params_[pindex]);
        if (std::distance(range.first, range.second) > 0) {
            return (*range.first)->type_;
        }
    }
    return EXCHANGE_DATA_TYPE_NONE;
}

void
CqlCommon::bindData(CassStatement* statement,
                    uint32_t stindex,
                    const CqlDataArray& data,
                    const SqlExchange& exchange,
                    const CqlTaggedStatement* tagged_statements) {
    if (!tagged_statements[stindex].params_) {
        return;
    }
    for (int i = 0; tagged_statements[stindex].params_[i]; i++) {
        ExchangeDataType type =
            CqlCommon::getDataType(stindex, i, exchange, tagged_statements);
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << stindex << " out of bounds");
        }
        CqlFunctions[type].cqlBindFunction_(statement, i, data.values_[i]);
    }
}

void
CqlCommon::getData(const CassRow* row,
                   int pindex,
                   int dindex,
                   const SqlExchange& exchange,
                   CqlDataArray& data) {
    if (pindex >= exchange.parameters_.size()) {
        return;
    }
    const ExchangeColumnInfoContainerIndex& idx = exchange.parameters_.get<2>();
    const ExchangeColumnInfoContainerIndexRange& range =
        idx.equal_range(pindex);
    if (std::distance(range.first, range.second) > 0) {
        std::string name = (*range.first)->name_;
        ExchangeDataType type = (*range.first)->type_;
        const CassValue* value = cass_row_get_column_by_name(row, name.c_str());
        if (!value) {
            isc_throw(BadValue, "column name " << name << " doesn't exist");
        }
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << type << " out of bounds");
        }
        CassError cassError =
            CqlFunctions[type].cqlGetFunction_(value, data.values_[dindex]);
        if (cassError != CASS_OK) {
            isc_throw(BadValue, "Cassandra error for column "
                                    << name << " with message: "
                                    << cass_error_desc(cassError));
        }
    }
}

CqlExchange::CqlExchange() {
}

CqlExchange::~CqlExchange() {
}

void
CqlExchange::convertToDatabaseTime(const time_t& cltt,
                                   const cass_int64_t& valid_lifetime,
                                   cass_int64_t& expire) {
    // Calculate expiry time. Store it in the 64-bit value so as we can
    // detect overflows.
    cass_int64_t expire_time = static_cast<cass_int64_t>(cltt) + valid_lifetime;

    if (expire_time > DatabaseConnection::MAX_DB_TIME) {
        isc_throw(BadValue, "Time value is too large: " << expire_time);
    }

    expire = expire_time;
}

void
CqlExchange::convertFromDatabaseTime(const cass_int64_t& expire,
                                     const cass_int64_t& valid_lifetime,
                                     time_t& cltt) {
    // Convert to local time
    cltt = static_cast<time_t>(expire - valid_lifetime);
}

void
CqlExchange::createBindForReceive(CqlDataArray& /* data */,
                                  const int /* statementIndex = -1 */) {
    isc_throw(NotImplemented,
              "CqlExchange::createBindForReceive() not implemented yet.");
}

CqlDataArray
CqlExchange::executeRead(const CqlConnection& connection,
                         const CqlDataArray& data,
                         const int statementIndex,
                         const bool single /* = false */,
                         const std::vector<std::string>&
                             parameters /* = std::vector<std::string>() */) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(connection.statements_[statementIndex]);
    if (!statement) {
        isc_throw(DbOperationError,
                  "unable to bind statement "
                      << connection.tagged_statements_[statementIndex].name_);
    }

    if (connection.force_consistency_) {
        rc = cass_statement_set_consistency(statement, connection.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << connection.tagged_statements_[statementIndex].name_);
        }
    }

    CqlCommon::bindData(statement, statementIndex, data, *this,
                        connection.tagged_statements_);

    future = cass_session_execute(connection.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << connection.tagged_statements_[statementIndex].name_);
    }
    cass_future_wait(future);
    std::string error;
    connection.checkStatementError(error, future, statementIndex,
                                   "unable to execute statement");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Get column values.
    const CassResult* resultCollection = cass_future_get_result(future);
    if (single && cass_result_row_count(resultCollection) > 1) {
        cass_result_free(resultCollection);
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(MultipleRecords,
                  "multiple records were found in the "
                  "database where only one was expected for statement "
                      << connection.tagged_statements_[statementIndex].name_);
    }

    // Get results.
    CqlDataArray returnValues;
    CqlDataArray collection;
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        createBindForReceive(returnValues, statementIndex);
        for (size_t i = 0U; i < returnValues.size(); i++) {
            uint32_t pindex = i;
            if (!parameters.empty()) {
                const ExchangeColumnInfoContainerName& idx =
                    parameters_.get<1>();
                const ExchangeColumnInfoContainerNameRange& range =
                    idx.equal_range(parameters[i]);
                if (std::distance(range.first, range.second) > 0) {
                    pindex = (*range.first)->index_;
                }
            }
            CqlCommon::getData(row, pindex, i, *this, returnValues);
        }
        collection.add(retrieve());
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    return collection;
}

void
CqlExchange::executeWrite(const CqlConnection& connection,
                          const CqlDataArray& data,
                          const int statementIndex) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(connection.statements_[statementIndex]);
    if (!statement) {
        isc_throw(DbOperationError,
                  "unable to bind statement "
                      << connection.tagged_statements_[statementIndex].name_);
    }

    if (connection.force_consistency_) {
        rc = cass_statement_set_consistency(statement, connection.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << connection.tagged_statements_[statementIndex].name_);
        }
    }

    CqlCommon::bindData(statement, statementIndex, data, *this,
                        connection.tagged_statements_);

    future = cass_session_execute(connection.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << connection.tagged_statements_[statementIndex].name_);
    }
    cass_future_wait(future);
    std::string error;
    connection.checkStatementError(error, future, statementIndex,
                                   "unable to execute statement");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Check if statement has been applied.
    bool applied = hasStatementBeenApplied(future);

    // Free resources.
    cass_future_free(future);
    cass_statement_free(statement);

    if (!applied) {
        isc_throw(DuplicateEntry,
                  "[applied] is false. Entry already exists. "
                  "Statement "
                      << connection.tagged_statements_[statementIndex].name_
                      << "has not been applied");
    }
}

bool
CqlExchange::hasStatementBeenApplied(CassFuture* future,
                                     size_t* row_count,
                                     size_t* column_count) {
    const CassResult* resultCollection = cass_future_get_result(future);
    if (row_count) {
        *row_count = cass_result_row_count(resultCollection);
    }
    if (column_count) {
        *column_count = cass_result_column_count(resultCollection);
    }
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    CqlDataArray data;
    cass_bool_t applied = cass_true;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // [applied]: bool
        data.add(reinterpret_cast<void*>(&applied));

        const ExchangeColumnInfoContainerName& idx = parameters_.get<1>();
        const ExchangeColumnInfoContainerNameRange& range =
            idx.equal_range("[applied]");
        if (std::distance(range.first, range.second) > 0) {
            CqlCommon::getData(row, (*range.first)->index_, 0, *this, data);
        }
    }
    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    return applied == cass_true;
}

void*
CqlExchange::retrieve() {
    isc_throw(NotImplemented, "CqlExchange::retrieve() not implemented yet.");
}

CqlVersionExchange::CqlVersionExchange() {
    // Set the column names
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "version", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "minor", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    BOOST_ASSERT(parameters_.size() == 2U);
}

CqlVersionExchange::~CqlVersionExchange() {
}

void
CqlVersionExchange::createBindForReceive(CqlDataArray& data,
                                         const int /* statementIndex = -1 */) {
    // Start with a fresh array.
    data.clear();
    // id: blob
    data.add(reinterpret_cast<void*>(&version_));
    // host_identifier: blob
    data.add(reinterpret_cast<void*>(&minor_));
}

void*
CqlVersionExchange::retrieve() {
    pair_ = VersionPair(version_, minor_);
    return reinterpret_cast<void*>(&pair_);
}

VersionPair
CqlVersionExchange::retrieveVersion(const CqlConnection& connection,
                                    int statementIndex) {
    // Run statement.
    const CqlDataArray whereValues;
    CqlDataArray versionCollection =
        executeRead(connection, whereValues, statementIndex, true);

    VersionPair result;

    if (!versionCollection.empty()) {
        result = *(reinterpret_cast<VersionPair*>(
            *versionCollection.begin()));
    }

    return result;
}

}  // namespace dhcp
}  // namespace isc
