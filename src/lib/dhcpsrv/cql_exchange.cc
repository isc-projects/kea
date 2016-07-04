#include <dhcpsrv/cql_exchange.h>
/// @name CqlBind auxiliary methods for binding data into Cassandra format:
/// @{

/// @todo These void* cast are unsafe. See ticket #4525.
static CassError CqlBindNone(CassStatement* statement, size_t index,
        void*) {
    return cass_statement_bind_null(statement, index);
}

static CassError CqlBindBool(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_bool(statement, index,
        *(static_cast<cass_bool_t*>(value)));
}

static CassError CqlBindInt32(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int32(statement, index,
        *(static_cast<cass_int32_t*>(value)));
}

static CassError CqlBindInt64(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int64(statement, index,
        *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindTimestamp(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int64(statement, index,
        *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindString(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_string(statement, index,
        static_cast<std::string*>(value)->c_str());
}

static CassError CqlBindBytes(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_bytes(statement, index,
        static_cast<std::vector<cass_byte_t>*>(value)->data(),
        static_cast<std::vector<cass_byte_t>*>(value)->size());
}
/// @}

static CassError CqlGetNone(const CassValue*, void*) {
    return CASS_OK;
}

static CassError CqlGetBool(const CassValue* value, void* data) {
    return cass_value_get_bool(value, static_cast<cass_bool_t*>(data));
}

static CassError CqlGetInt32(const CassValue* value, void* data) {
    return cass_value_get_int32(value, static_cast<cass_int32_t*>(data));
}

static CassError CqlGetInt64(const CassValue* value, void* data) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError CqlGetTimestamp(const CassValue* value, void* data) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError CqlGetString(const CassValue* value, void* data) {
    const char* dataValue;
    size_t sizeValue;
    CassError cassError = cass_value_get_string(value,
        static_cast<const char**>(&dataValue), &sizeValue);
    static_cast<std::string*>(data)->assign(dataValue, dataValue + sizeValue);
    return cassError;
}

static CassError CqlGetBytes(const CassValue* value, void* data) {
    const cass_byte_t* dataValue;
    size_t sizeValue;
    CassError cassError = cass_value_get_bytes(value,
        static_cast<const cass_byte_t**>(&dataValue), &sizeValue);
    static_cast<std::vector<cass_byte_t>*>(data)->assign(dataValue, dataValue +
        sizeValue);
    return cassError;
}

namespace isc {
namespace dhcp {

struct CqlFunctionData CqlFunctions[] = {
    {CqlBindNone, CqlGetNone},
    {CqlBindBool, CqlGetBool},
    {CqlBindInt32, CqlGetInt32},
    {CqlBindInt64, CqlGetInt64},
    {CqlBindTimestamp, CqlGetTimestamp},
    {CqlBindString, CqlGetString},
    {CqlBindBytes, CqlGetBytes}
};

ExchangeDataType
CqlCommon::getDataType(const uint32_t stindex, int pindex,
        const SqlExchange& exchange, CqlTaggedStatement* tagged_statements) {
    if (tagged_statements[stindex].params_ &&
            tagged_statements[stindex].params_[pindex]) {
        const ExchangeColumnInfoContainerName& idx = exchange.parameters_.get<1>();
        const ExchangeColumnInfoContainerNameRange& range =
            idx.equal_range(tagged_statements[stindex].params_[pindex]);
        if (std::distance(range.first, range.second) > 0) {
            return (*range.first)->type_;
        }
    }
    return EXCHANGE_DATA_TYPE_NONE;
}

void
CqlCommon::bindData(CassStatement* statement, const uint32_t stindex,
        CqlDataArray& data, const SqlExchange& exchange, CqlTaggedStatement* tagged_statements) {
    if (tagged_statements[stindex].params_ == NULL) {
        return;
    }
    for (int i = 0; tagged_statements[stindex].params_[i]; i++) {
        ExchangeDataType type = CqlCommon::getDataType(stindex, i, exchange, tagged_statements);
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << stindex << " out of bounds");
        }
        CqlFunctions[type].sqlBindFunction_(statement, i, data.values_[i]);
    }
}

void
CqlCommon::getData(const CassRow* row, const int pindex, CqlDataArray& data,
        const int dindex, const SqlExchange& exchange) {
    const CassValue* value;
    if (pindex >= exchange.parameters_.size()) {
        return;
    }
    const ExchangeColumnInfoContainerIndex& idx = exchange.parameters_.get<2>();
    const ExchangeColumnInfoContainerIndexRange& range = idx.equal_range(pindex);
    if (std::distance(range.first, range.second) > 0) {
        std::string name = (*range.first)->name_;
        ExchangeDataType type = (*range.first)->type_;
        value = cass_row_get_column_by_name(row, name.c_str());
        if (NULL == value) {
            isc_throw(BadValue, "column name " << name << " doesn't exist");
        }
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << type << " out of bounds");
        }
        CqlFunctions[type].sqlGetFunction_(value, data.values_[dindex]);
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
