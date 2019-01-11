// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2016-2018 Deutsche Telekom AG.
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

#include <cql/cql_connection.h>
#include <cql/cql_exchange.h>

#include <database/db_exceptions.h>
#include <database/sql_common.h>

#include <boost/core/demangle.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>

#include <string>
#include <unordered_map>

namespace isc {
namespace db {

/// @name CqlBind functions for binding data into Cassandra format for
///     insertion:
/// @{
static CassError
CqlBindNone(const boost::any& /* value */, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_null(statement.get(), index);
}

static CassError
CqlBindBool(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_bool(statement.get(), index, *boost::any_cast<cass_bool_t*>(value));
}

static CassError
CqlBindInt8(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int8(statement.get(), index, *boost::any_cast<cass_int8_t*>(value));
}

static CassError
CqlBindInt16(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int16(statement.get(), index,
                                     *boost::any_cast<cass_int16_t*>(value));
}

static CassError
CqlBindInt32(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int32(statement.get(), index,
                                     *boost::any_cast<cass_int32_t*>(value));
}

static CassError
CqlBindInt64(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int64(statement.get(), index,
                                     *boost::any_cast<cass_int64_t*>(value));
}

static CassError
CqlBindUint8(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int8(
        statement.get(), index, static_cast<cass_int8_t>(*boost::any_cast<cass_uint8_t*>(value)));
}

static CassError
CqlBindUint16(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int16(
        statement.get(), index, static_cast<cass_int16_t>(*boost::any_cast<cass_uint16_t*>(value)));
}

static CassError
CqlBindUint32(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int32(
        statement.get(), index, static_cast<cass_int32_t>(*boost::any_cast<cass_uint32_t*>(value)));
}

static CassError
CqlBindUint64(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_int64(
        statement.get(), index, static_cast<cass_int64_t>(*boost::any_cast<cass_uint64_t*>(value)));
}

static CassError
CqlBindString(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_string(statement.get(), index,
                                      boost::any_cast<std::string*>(value)->c_str());
}

static CassError
CqlBindBytes(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    CassBlob* blob_value = boost::any_cast<CassBlob*>(value);
    return cass_statement_bind_bytes(statement.get(), index, blob_value->data(),
                                     blob_value->size());
}

static CassError
CqlBindUuid(const boost::any& value, const size_t& index, CassStatementPtr& statement) {
    return cass_statement_bind_uuid(statement.get(), index, *boost::any_cast<CassUuid*>(value));
}
/// @}

/// @name CqlGet functions for retrieving data of the proper Cassandra format:
/// @{
static CassError CqlGetNone(const boost::any& /* data */, const CassValue* /* value */) {
    return CASS_OK;
}

static CassError CqlGetBool(const boost::any& data, const CassValue* value) {
    return cass_value_get_bool(value, boost::any_cast<cass_bool_t*>(data));
}

static CassError CqlGetInt8(const boost::any& data, const CassValue* value) {
    return cass_value_get_int8(value, boost::any_cast<cass_int8_t*>(data));
}

static CassError CqlGetInt16(const boost::any& data, const CassValue* value) {
    return cass_value_get_int16(value, boost::any_cast<cass_int16_t*>(data));
}

static CassError CqlGetInt32(const boost::any& data, const CassValue* value) {
    return cass_value_get_int32(value, boost::any_cast<cass_int32_t*>(data));
}

static CassError CqlGetInt64(const boost::any& data, const CassValue* value) {
    return cass_value_get_int64(value, boost::any_cast<cass_int64_t*>(data));
}

static CassError CqlGetUint8(const boost::any& data, const CassValue* value) {
    return cass_value_get_int8(
        value, reinterpret_cast<cass_int8_t*>(boost::any_cast<cass_uint8_t*>(data)));
}

static CassError CqlGetUint16(const boost::any& data, const CassValue* value) {
    return cass_value_get_int16(
        value, reinterpret_cast<cass_int16_t*>(boost::any_cast<cass_uint16_t*>(data)));
}

static CassError CqlGetUint32(const boost::any& data, const CassValue* value) {
    return cass_value_get_int32(
        value, reinterpret_cast<cass_int32_t*>(boost::any_cast<cass_uint32_t*>(data)));
}

static CassError CqlGetUint64(const boost::any& data, const CassValue* value) {
    return cass_value_get_int64(
        value, reinterpret_cast<cass_int64_t*>(boost::any_cast<cass_uint64_t*>(data)));
}

static CassError CqlGetString(const boost::any& data, const CassValue* value) {
    char const* data_value;
    size_t size_value;
    CassError cass_error =
        cass_value_get_string(value, static_cast<char const**>(&data_value), &size_value);
    boost::any_cast<std::string*>(data)->assign(data_value, data_value + size_value);
    return cass_error;
}

static CassError CqlGetBytes(const boost::any& data, const CassValue* value) {
    const cass_byte_t* data_value;
    size_t size_value;
    CassError cass_error =
        cass_value_get_bytes(value, static_cast<const cass_byte_t**>(&data_value), &size_value);
    boost::any_cast<CassBlob*>(data)->assign(data_value, data_value + size_value);
    return cass_error;
}

static CassError CqlGetUuid(const boost::any& data, const CassValue* value) {
    return cass_value_get_uuid(value, boost::any_cast<CassUuid*>(data));
}
/// @}

/// @brief Defines a type for storing aux. Cassandra functions
typedef std::unordered_map<std::type_index, CqlFunction> CqlFunctionMap;

/// @brief Maps C++ type to functions.
static CqlFunctionMap CQL_FUNCTIONS{
    {{typeid(NULL), {CqlBindNone, CqlGetNone, "NULL"}},
     {typeid(cass_bool_t*), {CqlBindBool, CqlGetBool, "cass_bool_t*"}},
     {typeid(cass_int8_t*), {CqlBindInt8, CqlGetInt8, "cass_int8_t*"}},
     {typeid(cass_int16_t*), {CqlBindInt16, CqlGetInt16, "cass_int16_t*"}},
     {typeid(cass_int32_t*), {CqlBindInt32, CqlGetInt32, "cass_int32_t*"}},
     {typeid(cass_int64_t*), {CqlBindInt64, CqlGetInt64, "cass_int64_t*"}},
     {typeid(cass_uint8_t*), {CqlBindUint8, CqlGetUint8, "cass_uint8_t*"}},
     {typeid(cass_uint16_t*), {CqlBindUint16, CqlGetUint16, "cass_uint16_t*"}},
     {typeid(cass_uint32_t*), {CqlBindUint32, CqlGetUint32, "cass_uint32_t*"}},
     {typeid(cass_uint64_t*), {CqlBindUint64, CqlGetUint64, "cass_uint64_t*"}},
     {typeid(std::string*), {CqlBindString, CqlGetString, "std::string*"}},
     {typeid(CassBlob*), {CqlBindBytes, CqlGetBytes, "CassBlob*"}},
     {typeid(CassUuid*), {CqlBindUuid, CqlGetUuid, "CassUuid*"}}}};

void CqlCommon::bindData(const AnyArray& data, CassStatementPtr& statement) {
    size_t i = 0u;
    for (const boost::any& element : data) {
        CassError cass_error;
        try {
            cass_error = CQL_FUNCTIONS.at(element.type()).cqlBindFunction_(element, i, statement);
        } catch (std::out_of_range const& exception) {
            isc_throw(BadValue, "CqlCommon::bindData(): "
                                    << exception.what() << " when binding parameter " << i
                                    << " of type " << boost::core::demangle(element.type().name()));
        } catch (boost::bad_any_cast const& exception) {
            isc_throw(DbOperationError,
                      "CqlCommon::bindData(): "
                          << exception.what() << " when binding parameter " << i << " of type "
                          << boost::core::demangle(element.type().name()) << " to type "
                          << CQL_FUNCTIONS.at(element.type()).name_);
        }
        if (cass_error != CASS_OK) {
            isc_throw(DbOperationError,
                      "CqlCommon::bindData(): "
                          << cass_error_desc(cass_error) << " when binding parameter " << i
                          << " of type " << boost::core::demangle(element.type().name())
                          << " to type " << CQL_FUNCTIONS.at(element.type()).name_);
        }
        ++i;
    }
}

void CqlCommon::getData(const CassRow* row, AnyArray& data) {
    size_t i = 0u;
    for (boost::any& element : data) {
        const CassValue* value = cass_row_get_column(row, i);
        CassError cass_error;
        try {
            cass_error = CQL_FUNCTIONS.at(element.type()).cqlGetFunction_(element, value);
        } catch (std::out_of_range const& exception) {
            isc_throw(BadValue, "CqlCommon::bindData(): "
                                    << exception.what() << " when binding parameter " << i
                                    << " of type " << boost::core::demangle(element.type().name()));
        } catch (boost::bad_any_cast& exception) {
            isc_throw(DbOperationError,
                      "CqlCommon::getData(): "
                          << exception.what() << " when retrieving parameter " << i << " of type "
                          << boost::core::demangle(element.type().name()) << " to type "
                          << CQL_FUNCTIONS.at(element.type()).name_);
        }
        if (cass_error != CASS_OK) {
            isc_throw(DbOperationError,
                      "CqlCommon::getData(): "
                          << cass_error_desc(cass_error) << " when retrieving parameter " << i
                          << " of type " << boost::core::demangle(element.type().name())
                          << " to type " << CQL_FUNCTIONS.at(element.type()).name_);
        }
        ++i;
    }
}

constexpr StatementTag CqlVersionExchange::GET_VERSION;

StatementMap CqlVersionExchange::tagged_statements_{
    {GET_VERSION, {GET_VERSION, "SELECT version, minor FROM schema_version "}}};

CqlVersionExchange::CqlVersionExchange() {
}

CqlVersionExchange::~CqlVersionExchange() {
}

void CqlVersionExchange::createBindForSelect(AnyArray& data, StatementTag const&) {
    data.clear();  // Start with a fresh array.
    data.add(&version_);  // first column is a major version
    data.add(&minor_);  // second column is a minor version
}

VersionPairPtr CqlVersionExchange::retrieve() {
    return std::make_shared<VersionPair>(version_, minor_);
}

VersionPairPtr CqlVersionExchange::retrieveVersion(CqlConnection const& connection) {
    // Run statement.
    AnyArray const where_values;
    Collection<VersionPair> const& results =
        executeSelect(connection, where_values, GET_VERSION, true);

    return results.front();
}

StatementMap CqlConfigVersionExchange::tagged_statements_{
    {GET_VERSION, {GET_VERSION, "SELECT version, minor FROM config_schema_version "}}};

}  // namespace db
}  // namespace isc
