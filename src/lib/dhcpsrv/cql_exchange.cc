// Copyright (C) 2016-2017 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
//          Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_exchange.h>
#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/sql_common.h>

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief a helper structure with a function call operator that returns
///        key value in a format expected by std::hash.
struct ExchangeDataTypeHash {
public:
    size_t operator()(const ExchangeDataType& key) const {
        return std::hash<size_t>{}(static_cast<size_t>(key));
    }
};

/// @brief Defines a type for storing aux. Cassandra functions
typedef std::unordered_map<ExchangeDataType, CqlFunction, ExchangeDataTypeHash>
    CqlFunctionMap;
extern CqlFunctionMap CQL_FUNCTIONS;

/// @brief hash function for CassTypeMap
///
/// Required by g++ versions 5 and below.
///
/// @param key being hashed
///
/// @return hash value
std::size_t
hash_value(const CassValueType& key) {
    return key;
}

/// @brief Map types used to determine exchange type
/// @{

/// @brief Defines type that maps specific type to an enum
typedef std::unordered_map<std::type_index, ExchangeDataType> AnyTypeMap;

// Declare uint8_t as key here for compatibility with g++ version 5. Ideally,
// it would be CassValueType
typedef std::unordered_map<uint8_t, ExchangeDataType> CassTypeMap;
/// @}

/// @brief Maps C++ type to exchange type
static AnyTypeMap ANY_TYPE_MAP = {
    {typeid(NULL), EXCHANGE_DATA_TYPE_NONE},
    {typeid(cass_bool_t*), EXCHANGE_DATA_TYPE_BOOL},
    {typeid(cass_int8_t*), EXCHANGE_DATA_TYPE_INT8},
    {typeid(cass_int16_t*), EXCHANGE_DATA_TYPE_INT16},
    {typeid(cass_int32_t*), EXCHANGE_DATA_TYPE_INT32},
    {typeid(cass_int64_t*), EXCHANGE_DATA_TYPE_INT64},
    {typeid(std::string*), EXCHANGE_DATA_TYPE_STRING},
    {typeid(CassBlob*), EXCHANGE_DATA_TYPE_BYTES},
    {typeid(CassUuid*), EXCHANGE_DATA_TYPE_UUID}};
/// @}

/// @brief AnyArray method implementations
/// @{
void
AnyArray::add(const boost::any& value) {
    push_back(value);
}

void
AnyArray::remove(const size_t& index) {
    if (size() <= index) {
        isc_throw(BadValue,
                  "AnyArray::remove(): index "
                      << index << " out of bounds: [0, " << (size() - 1)
                      << "]");
    }
    erase(begin() + index);
}
/// @}

/// @name CqlBind functions for binding data into Cassandra format for
///     insertion:
/// @{
static CassError
CqlBindNone(const boost::any& /* value */,
            const size_t& index,
            CassStatement* statement) {
    return cass_statement_bind_null(statement, index);
}

static CassError
CqlBindBool(const boost::any& value,
            const size_t& index,
            CassStatement* statement) {
    return cass_statement_bind_bool(statement, index,
                                    *boost::any_cast<cass_bool_t*>(value));
}

static CassError
CqlBindInt8(const boost::any& value,
            const size_t& index,
            CassStatement* statement) {
    return cass_statement_bind_int8(statement, index,
                                    *boost::any_cast<cass_int8_t*>(value));
}

static CassError
CqlBindInt16(const boost::any& value,
             const size_t& index,
             CassStatement* statement) {
    return cass_statement_bind_int16(statement, index,
                                     *boost::any_cast<cass_int16_t*>(value));
}

static CassError
CqlBindInt32(const boost::any& value,
             const size_t& index,
             CassStatement* statement) {
    return cass_statement_bind_int32(statement, index,
                                     *boost::any_cast<cass_int32_t*>(value));
}

static CassError
CqlBindInt64(const boost::any& value,
             const size_t& index,
             CassStatement* statement) {
    return cass_statement_bind_int64(statement, index,
                                     *boost::any_cast<cass_int64_t*>(value));
}

static CassError
CqlBindString(const boost::any& value,
              const size_t& index,
              CassStatement* statement) {
    return cass_statement_bind_string(
        statement, index, boost::any_cast<std::string*>(value)->c_str());
}

static CassError
CqlBindBytes(const boost::any& value,
             const size_t& index,
             CassStatement* statement) {
    CassBlob* blob_value = boost::any_cast<CassBlob*>(value);
    return cass_statement_bind_bytes(statement, index, blob_value->data(),
                                     blob_value->size());
}

static CassError
CqlBindUuid(const boost::any& value,
            const size_t& index,
            CassStatement* statement) {
    return cass_statement_bind_uuid(statement, index,
                                    *boost::any_cast<CassUuid*>(value));
}
/// @}

/// @name CqlGet functions for retrieving data of the proper Cassandra format:
/// @{
static CassError
CqlGetNone(const boost::any& /* data */, const CassValue* /* value */) {
    return CASS_OK;
}

static CassError
CqlGetBool(const boost::any& data, const CassValue* value) {
    return cass_value_get_bool(value, boost::any_cast<cass_bool_t*>(data));
}

static CassError
CqlGetInt8(const boost::any& data, const CassValue* value) {
    return cass_value_get_int8(value, boost::any_cast<cass_int8_t*>(data));
}

static CassError
CqlGetInt16(const boost::any& data, const CassValue* value) {
    return cass_value_get_int16(value, boost::any_cast<cass_int16_t*>(data));
}

static CassError
CqlGetInt32(const boost::any& data, const CassValue* value) {
    return cass_value_get_int32(value, boost::any_cast<cass_int32_t*>(data));
}

static CassError
CqlGetInt64(const boost::any& data, const CassValue* value) {
    return cass_value_get_int64(value, boost::any_cast<cass_int64_t*>(data));
}

static CassError
CqlGetString(const boost::any& data, const CassValue* value) {
    char const* data_value;
    size_t size_value;
    CassError cass_error = cass_value_get_string(
        value, static_cast<char const**>(&data_value), &size_value);
    boost::any_cast<std::string*>(data)->assign(data_value,
                                                data_value + size_value);
    return cass_error;
}

static CassError
CqlGetBytes(const boost::any& data, const CassValue* value) {
    const cass_byte_t* data_value;
    size_t size_value;
    CassError cass_error = cass_value_get_bytes(
        value, static_cast<const cass_byte_t**>(&data_value), &size_value);
    boost::any_cast<CassBlob*>(data)->assign(data_value,
                                             data_value + size_value);
    return cass_error;
}

static CassError
CqlGetUuid(const boost::any& data, const CassValue* value) {
    return cass_value_get_uuid(value, boost::any_cast<CassUuid*>(data));
}
/// @}

/// @brief Functions used to interface with the Cassandra C++ driver
CqlFunctionMap CQL_FUNCTIONS =  //
    {{EXCHANGE_DATA_TYPE_NONE,
      {CqlBindNone, CqlGetNone}},
     {EXCHANGE_DATA_TYPE_BOOL,
      {CqlBindBool, CqlGetBool}},
     {EXCHANGE_DATA_TYPE_INT8,
      {CqlBindInt8, CqlGetInt8}},
     {EXCHANGE_DATA_TYPE_INT16,
      {CqlBindInt16, CqlGetInt16}},
     {EXCHANGE_DATA_TYPE_INT32,
      {CqlBindInt32, CqlGetInt32}},
     {EXCHANGE_DATA_TYPE_INT64,
      {CqlBindInt64, CqlGetInt64}},
     {EXCHANGE_DATA_TYPE_TIMESTAMP,
      {CqlBindInt64, CqlGetInt64}},
     {EXCHANGE_DATA_TYPE_STRING,
      {CqlBindString, CqlGetString}},
     {EXCHANGE_DATA_TYPE_BYTES,
      {CqlBindBytes, CqlGetBytes}},
     {EXCHANGE_DATA_TYPE_UUID,
      {CqlBindUuid, CqlGetUuid}}};

ExchangeDataType
exchangeType(const boost::any& object) {
    const std::type_index type = object.type();
    AnyTypeMap::const_iterator exchange_type_it = ANY_TYPE_MAP.find(type);
    if (exchange_type_it == ANY_TYPE_MAP.end()) {
        isc_throw(DbOperationError,
                  "exchangeType(): boost::any type "
                      << type.name() << " does not map to any exchange type");
    }
    const ExchangeDataType exchange_type = exchange_type_it->second;
    if (exchange_type >= CQL_FUNCTIONS.size()) {
        isc_throw(BadValue,
                  "exchangeType(): index " << exchange_type << " out of bounds "
                                           << 0 << " - "
                                           << (CQL_FUNCTIONS.size() - 1));
    }
    return exchange_type;
}

void
CqlCommon::bindData(const AnyArray& data, CassStatement* statement) {
    size_t i = 0u;
    for (const boost::any& element : data) {
        CassError cass_error;
        try {
            cass_error = CQL_FUNCTIONS[exchangeType(element)].cqlBindFunction_(
                element, i, statement);
        } catch (const boost::bad_any_cast& exception) {
            isc_throw(DbOperationError,
                      "CqlCommon::bindData(): "
                          << exception.what() << " when binding parameter " << i
                          << " which is of type " << element.type().name()
                          << " with function CQL_FUNCTIONS["
                          << exchangeType(element) << "].cqlBindFunction_()");
        }
        if (cass_error != CASS_OK) {
            isc_throw(DbOperationError,
                      "CqlCommon::bindData(): unable to bind parameter "
                          << i << " which is of type " << element.type().name()
                          << " with function CQL_FUNCTIONS["
                          << exchangeType(element)
                          << "].cqlBindFunction_(), Cassandra error code: "
                          << cass_error_desc(cass_error));
        }
        ++i;
    }
}

void
CqlCommon::getData(const CassRow* row, AnyArray& data) {
    size_t i = 0u;
    for (boost::any& element : data) {
        const CassValue* value = cass_row_get_column(row, i);
        CassError cass_error;
        try {
            cass_error = CQL_FUNCTIONS[exchangeType(element)].cqlGetFunction_(
                element, value);
        } catch (const boost::bad_any_cast& exception) {
            isc_throw(DbOperationError,
                      "CqlCommon::getData(): "
                          << exception.what() << " when retrieving parameter "
                          << i << " which is of type " << element.type().name()
                          << " with function CQL_FUNCTIONS["
                          << exchangeType(element) << "].cqlGetFunction_()");
        }
        if (cass_error != CASS_OK) {
            isc_throw(
                DbOperationError,
                "CqlCommon::getData(): Cassandra error when retrieving column "
                    << i << ", Cassandra error code: "
                    << cass_error_desc(cass_error));
        }
        ++i;
    }
}

CqlExchange::CqlExchange() {
}

CqlExchange::~CqlExchange() {
}

void
CqlExchange::convertToDatabaseTime(const time_t& cltt,
                                   const uint32_t& valid_lifetime,
                                   cass_int64_t& expire) {
    // Calculate expire time. Store it in the 64-bit value so as we can
    // detect overflows.
    cass_int64_t expire_time = static_cast<cass_int64_t>(cltt) +
            static_cast<cass_int64_t>(valid_lifetime);

    if (expire_time > DatabaseConnection::MAX_DB_TIME) {
        isc_throw(BadValue,
                  "CqlExchange(): convertToDatabaseTime(): time value "
                      << expire_time << " is too large");
    }

    expire = expire_time;
}

void
CqlExchange::convertFromDatabaseTime(const cass_int64_t& expire,
                                     const cass_int64_t& valid_lifetime,
                                     time_t& cltt) {
    /// @todo: Although 2037 is still far away, there are people who use infinite
    /// lifetimes. Cassandra doesn't have to support it right now, but at least
    /// we should be able to detect a problem.

    // Convert to local time
    cltt = static_cast<time_t>(expire - valid_lifetime);
}

AnyArray
CqlExchange::executeSelect(const CqlConnection& connection, const AnyArray& data,
                           StatementTag statement_tag, const bool& single /* = false */) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;
    AnyArray local_data = data;

    // Find the query statement first.
    StatementMap::const_iterator it = connection.statements_.find(statement_tag);
    if (it == connection.statements_.end()) {
        isc_throw(DbOperationError,
                  "CqlExchange::executeSelect(): Statement "
                      << statement_tag << "has not been prepared.");
    }

    // Bind the data before the query is executed.
    CqlTaggedStatement tagged_statement = it->second;
    if (tagged_statement.is_raw_) {
        // The entire query is the first element in data.
        std::string* query = boost::any_cast<std::string*>(local_data.back());
        local_data.pop_back();
        statement = cass_statement_new(query->c_str(), local_data.size());
    } else {
        statement = cass_prepared_bind(tagged_statement.prepared_statement_);
        if (!statement) {
            isc_throw(DbOperationError,
                      "CqlExchange::executeSelect(): unable to bind statement "
                          << tagged_statement.name_);
        }
    }

    // Set specific level of consistency if we're told to do so.
    if (connection.force_consistency_) {
        rc = cass_statement_set_consistency(statement, connection.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(DbOperationError,
                      "CqlExchange::executeSelect(): unable to set statement "
                      "consistency for statement "
                          << tagged_statement.name_
                          << ", Cassandra error code: " << cass_error_desc(rc));
        }
    }

    try {
        CqlCommon::bindData(local_data, statement);
    } catch (const std::exception& ex) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, ex.what());
    }

    // Everything's ready. Call the actual statement.
    future = cass_session_execute(connection.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "CqlExchange::executeSelect(): no CassFuture for statement "
                      << tagged_statement.name_);
    }

    // Wait for the statement execution to complete.
    cass_future_wait(future);
    const std::string error = connection.checkFutureError(
        "CqlExchange::executeSelect(): cass_session_execute() != CASS_OK",
        future, statement_tag);
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Get column values.
    const CassResult* result_collection = cass_future_get_result(future);
    if (single && cass_result_row_count(result_collection) > 1) {
        cass_result_free(result_collection);
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(
            MultipleRecords,
            "CqlExchange::executeSelect(): multiple records were found in "
            "the database where only one was expected for statement "
                << tagged_statement.name_);
    }

    // Get results.
    AnyArray return_values;
    AnyArray collection;
    CassIterator* rows = cass_iterator_from_result(result_collection);
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        createBindForSelect(return_values, statement_tag);
        CqlCommon::getData(row, return_values);
        collection.add(retrieve());
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(result_collection);
    cass_future_free(future);
    cass_statement_free(statement);

    return collection;
}

void
CqlExchange::executeMutation(const CqlConnection& connection, const AnyArray& data,
                             StatementTag statement_tag) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    // Find the statement on a list of prepared statements.
    StatementMap::const_iterator it =
        connection.statements_.find(statement_tag);
    if (it == connection.statements_.end()) {
        isc_throw(DbOperationError, "CqlExchange::executeSelect(): Statement "
                  << statement_tag << "has not been prepared.");
    }
    // Bind the statement.
    CqlTaggedStatement tagged_statement = it->second;
    statement = cass_prepared_bind(tagged_statement.prepared_statement_);
    if (!statement) {
        isc_throw(DbOperationError,
                  "CqlExchange::executeMutation(): unable to bind statement "
                      << tagged_statement.name_);
    }

    // Set specific level of consistency, if told to do so.
    if (connection.force_consistency_) {
        rc = cass_statement_set_consistency(statement, connection.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(DbOperationError, "CqlExchange::executeMutation(): unable to set"
                      " statement consistency for statement " << tagged_statement.name_
                      << ", Cassandra error code: " << cass_error_desc(rc));
        }
    }

    try {
        CqlCommon::bindData(data, statement);
    } catch (const std::exception& ex) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, ex.what());
    }

    future = cass_session_execute(connection.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "CqlExchange::executeMutation(): unable to execute statement "
                      << tagged_statement.name_);
    }
    cass_future_wait(future);
    const std::string error = connection.checkFutureError("CqlExchange::executeMutation():"
                              "cass_session_execute() != CASS_OK", future, statement_tag);
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Check if statement has been applied.
    bool applied = statementApplied(future);

    // Free resources.
    cass_future_free(future);
    cass_statement_free(statement);

    if (!applied) {
        isc_throw(
            StatementNotApplied,
            "CqlExchange::executeMutation(): [applied] is false for statement "
                << tagged_statement.name_);
    }
}

bool
CqlExchange::statementApplied(CassFuture* future,
                                     size_t* row_count,
                                     size_t* column_count) {
    const CassResult* result_collection = cass_future_get_result(future);
    if (!result_collection) {
        isc_throw(DbOperationError, "CqlExchange::statementApplied(): unable to get"
                      " results collection");
    }
    if (row_count) {
        *row_count = cass_result_row_count(result_collection);
    }
    if (column_count) {
        *column_count = cass_result_column_count(result_collection);
    }
    CassIterator* rows = cass_iterator_from_result(result_collection);
    AnyArray data;
    cass_bool_t applied = cass_true;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // [applied]: bool
        data.add(&applied);
        CqlCommon::getData(row, data);
    }
    cass_iterator_free(rows);
    cass_result_free(result_collection);
    return applied == cass_true;
}

constexpr StatementTag CqlVersionExchange::GET_VERSION;

StatementMap CqlVersionExchange::tagged_statements_ = {
    {GET_VERSION, {GET_VERSION, "SELECT version, minor FROM schema_version "}}
};

CqlVersionExchange::CqlVersionExchange() {
}

CqlVersionExchange::~CqlVersionExchange() {
}

void
CqlVersionExchange::createBindForSelect(AnyArray& data, StatementTag) {
    data.clear(); // Start with a fresh array.
    data.add(&version_); // first column is a major version
    data.add(&minor_); // second column is a minor version
}

boost::any
CqlVersionExchange::retrieve() {
    pair_ = VersionPair(version_, minor_);
    return &pair_;
}

VersionPair
CqlVersionExchange::retrieveVersion(const CqlConnection& connection) {
    // Run statement.
    const AnyArray where_values;
    AnyArray version_collection =
        executeSelect(connection, where_values, GET_VERSION, true);

    if (!version_collection.empty()) {
        return *boost::any_cast<VersionPair*>(*version_collection.begin());
    }

    return VersionPair();
}

}  // namespace dhcp
}  // namespace isc
