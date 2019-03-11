// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

#include <cql/cql_connection.h>
#include <cql/cql_exchange.h>
#include <cql/sql_common.h>
#include <database/db_exceptions.h>

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
namespace db {

/// @brief Macro to return directly from caller function
#define KEA_CASS_CHECK(cass_error)   \
    {                                \
        if (cass_error != CASS_OK) { \
            return cass_error;       \
        }                            \
    }

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
    {typeid(CassUuid*), EXCHANGE_DATA_TYPE_UUID},
    {typeid(Udt*), EXCHANGE_DATA_TYPE_UDT}, // user data type
    {typeid(AnyCollection*), EXCHANGE_DATA_TYPE_COLLECTION}};

/// @brief Maps Cassandra type to exchange type
static CassTypeMap CASS_TYPE_MAP = {
    {CASS_VALUE_TYPE_CUSTOM, EXCHANGE_DATA_TYPE_UDT},
    {CASS_VALUE_TYPE_ASCII, EXCHANGE_DATA_TYPE_STRING},
    {CASS_VALUE_TYPE_BIGINT, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_BLOB, EXCHANGE_DATA_TYPE_BYTES},
    {CASS_VALUE_TYPE_BOOLEAN, EXCHANGE_DATA_TYPE_BOOL},
    {CASS_VALUE_TYPE_COUNTER, EXCHANGE_DATA_TYPE_INT32},
    {CASS_VALUE_TYPE_DECIMAL, EXCHANGE_DATA_TYPE_INT32},
    {CASS_VALUE_TYPE_DOUBLE, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_FLOAT, EXCHANGE_DATA_TYPE_INT32},
    {CASS_VALUE_TYPE_INT, EXCHANGE_DATA_TYPE_INT32},
    {CASS_VALUE_TYPE_TEXT, EXCHANGE_DATA_TYPE_STRING},
    {CASS_VALUE_TYPE_TIMESTAMP, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_UUID, EXCHANGE_DATA_TYPE_UUID},
    {CASS_VALUE_TYPE_VARCHAR, EXCHANGE_DATA_TYPE_STRING},
    {CASS_VALUE_TYPE_VARINT, EXCHANGE_DATA_TYPE_INT32},
    {CASS_VALUE_TYPE_TIMEUUID, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_INET, EXCHANGE_DATA_TYPE_NONE},
    {CASS_VALUE_TYPE_DATE, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_TIME, EXCHANGE_DATA_TYPE_INT64},
    {CASS_VALUE_TYPE_SMALL_INT, EXCHANGE_DATA_TYPE_INT16},
    {CASS_VALUE_TYPE_TINY_INT, EXCHANGE_DATA_TYPE_INT8},
    {CASS_VALUE_TYPE_LIST, EXCHANGE_DATA_TYPE_COLLECTION},
    {CASS_VALUE_TYPE_MAP, EXCHANGE_DATA_TYPE_COLLECTION},
    {CASS_VALUE_TYPE_SET, EXCHANGE_DATA_TYPE_COLLECTION},
    {CASS_VALUE_TYPE_UDT, EXCHANGE_DATA_TYPE_UDT},
    {CASS_VALUE_TYPE_TUPLE, EXCHANGE_DATA_TYPE_UDT}};

/// @brief Udt (user data type) method implementations
/// @{
Udt::Udt(const CqlConnection& connection, const std::string& name)
    : AnyArray(), connection_(connection), name_(name) {
    // Create type.
    cass_data_type_ = cass_keyspace_meta_user_type_by_name(
        connection_.keyspace_meta_, name_.c_str());
    if (!cass_data_type_) {
        isc_throw(DbOperationError,
                  "Udt::Udt(): UDT " << name_ << " does not exist ");
    }
    // Create container.
    cass_user_type_ = cass_user_type_new_from_data_type(cass_data_type_);
    if (!cass_user_type_) {
        isc_throw(DbOperationError,
                  "Udt::Udt(): Type " << name_
                                      << " is not a UDT as expected. ");
    }
}

Udt::~Udt() {
    /// @todo: Need to get back to this issue. This is likely a memory leak.
    //
    // Bug: it seems that if there is no call to
    //      cass_user_type_set_*(cass_user_type_), then
    //      cass_user_type_free(cass_user_type_) might SIGSEGV, so we never
    //      free. Udt objects should have application scope though.
    // cass_user_type_free(cass_user_type_);
}
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

static CassError
CqlBindUdt(const boost::any& value,
           const size_t& index,
           CassStatement* statement) {
    Udt* udt = boost::any_cast<Udt*>(value);

    if (!udt) {
        isc_throw(BadValue, "Invalid value specified, not an Udt object");
    }

    size_t i = 0u;

    // Let's iterate over all elements in udt and check that we indeed
    // can assign the set function for each specified type.
    for (boost::any& element : *udt) {
        try {
            KEA_CASS_CHECK(
                CQL_FUNCTIONS[exchangeType(element)].cqlUdtSetFunction_(
                    element, i, udt->cass_user_type_));
        } catch (const boost::bad_any_cast& exception) {
            isc_throw(DbOperationError,
                      "CqlCommon::udtSetData(): "
                          << exception.what() << " when binding parameter "
                          << " of type " << element.type().name()
                          << "in UDT with function CQL_FUNCTIONS["
                          << exchangeType(element) << "].cqlUdtSetFunction_");
        }
        ++i;
    }

    return cass_statement_bind_user_type(statement, index,
                                         udt->cass_user_type_);
}

static CassError
CqlBindCollection(const boost::any& value,
                  const size_t& index,
                  CassStatement* statement) {
    AnyCollection* elements = boost::any_cast<AnyCollection*>(value);

    CassCollection* collection =
        cass_collection_new(CASS_COLLECTION_TYPE_SET, elements->size());

    // Iterate over all elements and assign appropriate append function
    // for each.
    for (boost::any& element : *elements) {
        ExchangeDataType type = exchangeType(element);
        KEA_CASS_CHECK(CQL_FUNCTIONS[type].cqlCollectionAppendFunction_(
            element, collection));
    }

    const CassError cass_error =
        cass_statement_bind_collection(statement, index, collection);
    cass_collection_free(collection);

    return cass_error;
}
/// @}

/// @name CqlUdtSet functions for binding data into Cassandra format for
///     insertion of a UDT:
/// @{
static CassError
CqlUdtSetNone(const boost::any& /* udt_member */,
              const size_t& position,
              CassUserType* cass_user_type) {
    return cass_user_type_set_null(cass_user_type, position);
}

static CassError
CqlUdtSetBool(const boost::any& udt_member,
              const size_t& position,
              CassUserType* cass_user_type) {
    return cass_user_type_set_bool(cass_user_type, position,
                                   *boost::any_cast<cass_bool_t*>(udt_member));
}

static CassError
CqlUdtSetInt8(const boost::any& udt_member,
              const size_t& position,
              CassUserType* cass_user_type) {
    return cass_user_type_set_int8(cass_user_type, position,
                                   *boost::any_cast<cass_int8_t*>(udt_member));
}

static CassError
CqlUdtSetInt16(const boost::any& udt_member,
               const size_t& position,
               CassUserType* cass_user_type) {
    return cass_user_type_set_int16(
        cass_user_type, position, *boost::any_cast<cass_int16_t*>(udt_member));
}

static CassError
CqlUdtSetInt32(const boost::any& udt_member,
               const size_t& position,
               CassUserType* cass_user_type) {
    return cass_user_type_set_int32(
        cass_user_type, position, *boost::any_cast<cass_int32_t*>(udt_member));
}

static CassError
CqlUdtSetInt64(const boost::any& udt_member,
               const size_t& position,
               CassUserType* cass_user_type) {
    return cass_user_type_set_int64(
        cass_user_type, position, *boost::any_cast<cass_int64_t*>(udt_member));
}

static CassError
CqlUdtSetString(const boost::any& udt_member,
                const size_t& position,
                CassUserType* cass_user_type) {
    return cass_user_type_set_string(
        cass_user_type, position,
        boost::any_cast<std::string*>(udt_member)->c_str());
}

static CassError
CqlUdtSetBytes(const boost::any& udt_member,
               const size_t& position,
               CassUserType* cass_user_type) {
    CassBlob* blob_value = boost::any_cast<CassBlob*>(udt_member);
    return cass_user_type_set_bytes(cass_user_type, position,
                                    blob_value->data(), blob_value->size());
}

static CassError
CqlUdtSetUuid(const boost::any& udt_member,
              const size_t& position,
              CassUserType* cass_user_type) {
    return cass_user_type_set_uuid(cass_user_type, position,
                                   *boost::any_cast<CassUuid*>(udt_member));
}

static CassError
CqlUdtSetUdt(const boost::any& udt_member,
             const size_t& position,
             CassUserType* cass_user_type) {
    return cass_user_type_set_user_type(
        cass_user_type, position,
        boost::any_cast<Udt*>(udt_member)->cass_user_type_);
}

static CassError
CqlUdtSetCollection(const boost::any& udt_member,
                    const size_t& position,
                    CassUserType* cass_user_type) {
    return cass_user_type_set_collection(
        cass_user_type, position, boost::any_cast<CassCollection*>(udt_member));
}
/// @}

/// @name CqlCollectionAppend functions for binding data into Cassandra format
///     for insertion of a collection:
/// @{
static CassError
CqlCollectionAppendNone(const boost::any& /* value */,
                        CassCollection* /* collection */) {
    return CASS_OK;
}

static CassError
CqlCollectionAppendBool(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_bool(collection,
                                       *boost::any_cast<cass_bool_t*>(value));
}

static CassError
CqlCollectionAppendInt8(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_int8(collection,
                                       *boost::any_cast<cass_int8_t*>(value));
}

static CassError
CqlCollectionAppendInt16(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_int16(collection,
                                        *boost::any_cast<cass_int16_t*>(value));
}

static CassError
CqlCollectionAppendInt32(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_int32(collection,
                                        *boost::any_cast<cass_int32_t*>(value));
}

static CassError
CqlCollectionAppendInt64(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_int64(collection,
                                        *boost::any_cast<cass_int64_t*>(value));
}

static CassError
CqlCollectionAppendString(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_string(
        collection, boost::any_cast<std::string*>(value)->c_str());
}

static CassError
CqlCollectionAppendBytes(const boost::any& value, CassCollection* collection) {
    CassBlob* blob_value = boost::any_cast<CassBlob*>(value);
    return cass_collection_append_bytes(collection, blob_value->data(),
                                        blob_value->size());
}

static CassError
CqlCollectionAppendUuid(const boost::any& value, CassCollection* collection) {
    return cass_collection_append_uuid(collection,
                                       *boost::any_cast<CassUuid*>(value));
}

static CassError
CqlCollectionAppendUdt(const boost::any& value, CassCollection* collection) {
    Udt* udt = boost::any_cast<Udt*>(value);
    size_t i = 0u;
    for (boost::any& element : *udt) {
        KEA_CASS_CHECK(CQL_FUNCTIONS[exchangeType(element)].cqlUdtSetFunction_(
            element, i, udt->cass_user_type_));
        ++i;
    }
    return cass_collection_append_user_type(collection, udt->cass_user_type_);
}

static CassError
CqlCollectionAppendCollection(const boost::any& value,
                              CassCollection* collection) {
    return cass_collection_append_collection(
        collection, boost::any_cast<CassCollection*>(value));
}
// @}

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

static CassError
CqlGetUdt(const boost::any& data, const CassValue* value) {
    Udt* udt = boost::any_cast<Udt*>(data);

    CassIterator* fields = cass_iterator_fields_from_user_type(value);
    if (!fields) {
        isc_throw(DbOperationError, "CqlGetUdt(): column is not a UDT");
    }
    Udt::const_iterator it = udt->begin();
    while (cass_iterator_next(fields)) {
        const CassValue* field_value =
            cass_iterator_get_user_type_field_value(fields);
        if (cass_value_is_null(field_value)) {
            isc_throw(DbOperationError,
                      "CqlGetUdt(): null value returned in UDT");
        }
        const CassValueType& type = cass_value_type(field_value);
        KEA_CASS_CHECK(CQL_FUNCTIONS[exchangeType(type)].cqlGetFunction_(
            *it, field_value));
        ++it;
        // If cqlGetFunction_() returns != CASS_OK, don't
        // cass_iterator_free(items_iterator) because we're returning from this
        // function and throwing from the callee.
    }
    cass_iterator_free(fields);
    return CASS_OK;
}

static CassError
CqlGetCollection(const boost::any& data, const CassValue* value) {
    AnyCollection* collection = boost::any_cast<AnyCollection*>(data);
    if (!collection) {
        isc_throw(DbOperationError, "CqlGetCollection(): column is not a collection");
    }

    BOOST_ASSERT(collection->size() == 1);

    /// @todo: Create a copy of the underlying object rather than referencing to
    /// it.
    boost::any underlying_object = *collection->begin();

    collection->clear();

    CassIterator* items = cass_iterator_from_collection(value);
    if (!items) {
        isc_throw(DbOperationError,
                  "CqlGetCollection(): column is not a collection");
    }
    while (cass_iterator_next(items)) {
        const CassValue* item_value = cass_iterator_get_value(items);
        if (cass_value_is_null(item_value)) {
            isc_throw(DbOperationError,
                      "CqlGetCollection(): null value returned in collection");
        }
        const CassValueType& type = cass_value_type(item_value);

        collection->push_back(underlying_object);
        KEA_CASS_CHECK(CQL_FUNCTIONS[exchangeType(type)].cqlGetFunction_(
            *collection->rbegin(), item_value));
        // If cqlGetFunction_() returns != CASS_OK, don't call
        // cass_iterator_free(items_iterator) because we're returning from this
        // function and throwing from the callee.
    }
    cass_iterator_free(items);
    return CASS_OK;
}
/// @}

/// @brief Functions used to interface with the Cassandra C++ driver
CqlFunctionMap CQL_FUNCTIONS =  //
    {{EXCHANGE_DATA_TYPE_NONE,
      {CqlBindNone, CqlUdtSetNone, CqlCollectionAppendNone, CqlGetNone}},
     {EXCHANGE_DATA_TYPE_BOOL,
      {CqlBindBool, CqlUdtSetBool, CqlCollectionAppendBool, CqlGetBool}},
     {EXCHANGE_DATA_TYPE_INT8,
      {CqlBindInt8, CqlUdtSetInt8, CqlCollectionAppendInt8, CqlGetInt8}},
     {EXCHANGE_DATA_TYPE_INT16,
      {CqlBindInt16, CqlUdtSetInt16, CqlCollectionAppendInt16, CqlGetInt16}},
     {EXCHANGE_DATA_TYPE_INT32,
      {CqlBindInt32, CqlUdtSetInt32, CqlCollectionAppendInt32, CqlGetInt32}},
     {EXCHANGE_DATA_TYPE_INT64,
      {CqlBindInt64, CqlUdtSetInt64, CqlCollectionAppendInt64, CqlGetInt64}},
     {EXCHANGE_DATA_TYPE_STRING,
      {CqlBindString, CqlUdtSetString, CqlCollectionAppendString,
       CqlGetString}},
     {EXCHANGE_DATA_TYPE_BYTES,
      {CqlBindBytes, CqlUdtSetBytes, CqlCollectionAppendBytes, CqlGetBytes}},
     {EXCHANGE_DATA_TYPE_UUID,
      {CqlBindUuid, CqlUdtSetUuid, CqlCollectionAppendUuid, CqlGetUuid}},
     {EXCHANGE_DATA_TYPE_UDT,
      {CqlBindUdt, CqlUdtSetUdt, CqlCollectionAppendUdt, CqlGetUdt}},
     {EXCHANGE_DATA_TYPE_COLLECTION,
      {CqlBindCollection, CqlUdtSetCollection, CqlCollectionAppendCollection,
       CqlGetCollection}}};

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

ExchangeDataType
exchangeType(const CassValueType& type) {
    CassTypeMap::const_iterator exchange_type_it = CASS_TYPE_MAP.find(type);
    if (exchange_type_it == CASS_TYPE_MAP.end()) {
        isc_throw(DbOperationError,
                  "exchangeType(): Cassandra value type "
                      << type << " does not map to any exchange type");
    }
    const ExchangeDataType exchange_type = exchange_type_it->second;
    if (exchange_type >= CQL_FUNCTIONS.size()) {
        isc_throw(BadValue,
                  "exchangeType(): index " << exchange_type << " out of bounds "
                                           << 0 << " - "
                                           << CQL_FUNCTIONS.size() - 1);
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
        if (connection.serial_consistency_ != CASS_CONSISTENCY_UNKNOWN) {
            rc = cass_statement_set_serial_consistency(statement, connection.serial_consistency_);
            if (rc != CASS_OK) {
                cass_statement_free(statement);
                isc_throw(DbOperationError,
                          "CqlExchange::executeSelect(): unable to set statement "
                          "serial consistency for statement "
                              << tagged_statement.name_
                              << ", Cassandra error code: " << cass_error_desc(rc));
            }
        }
    }

    CqlCommon::bindData(local_data, statement);

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

    CqlCommon::bindData(data, statement);

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

}  // namespace db
}  // namespace isc
