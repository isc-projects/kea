#ifndef CQL_EXCHANGE_H
#define CQL_EXCHANGE_H

#include <exceptions/exceptions.h>
#include <dhcpsrv/sql_common.h>
#include <vector>
#include <cassandra.h>

namespace isc {
namespace dhcp {

/// @brief  Defines a single query
///
/// @param params_ Bind parameter names
/// @param name_ Short name of the query.
/// @param text_ Text representation of the actual query.
struct CqlTaggedStatement {
    const char** params_;
    const char* name_;
    const char* text_;
};

typedef CassError (*CqlBindFunction)(CassStatement* statement, size_t index,
        void* value);
typedef CassError (*CqlGetFunction)(const CassValue* value, void* data);

struct CqlFunctionData {
    CqlBindFunction sqlBindFunction_;
    CqlGetFunction sqlGetFunction_;
};

extern struct CqlFunctionData CqlFunctions[];

/// @brief Structure used to bind C++ input values to dynamic SQL parameters
/// The structure contains a vector which store the input values,
/// This vector is passed directly into the
/// CQL execute call.
///
/// Note that the data values are stored as pointers. These pointers need
/// to be valid for the duration of the CQL statement execution. In other
/// words populating them with pointers to values that go out of scope
/// before statement is executed is a bad idea.
struct CqlDataArray {
    /// Add void pointer to a vector of pointers to the data values.
    std::vector<void*> values_;
    void add(void* value) {
        values_.push_back(value);
    }
    /// Remove void pointer from a vector of pointers to the data values.
    void remove(int index) {
        if (values_.size() <= index) {
            isc_throw(BadValue, "Index " << index << " out of bounds: [0, " <<
                (values_.size() - 1)  << "]");
        }
        values_.erase(values_.begin() + index);
    }
    /// Get size.
    size_t size() {
        return values_.size();
    }
};

class CqlCommon {
public:
    /// @brief Returns type of data for specific parameter.
    ///
    /// Returns type of a given parameter of a given statement.
    ///
    /// @param stindex Index of statement being executed.
    /// @param pindex Index of the parameter for a given statement.
    /// @param exchange Exchange object to use
    /// @param tagged_statements CqlTaggedStatement array to use
    static ExchangeDataType
    getDataType(const uint32_t stindex, int pindex,
            const SqlExchange& exchange, CqlTaggedStatement* tagged_statements);

    /// @brief Binds data specified in data
    ///
    /// This method calls one of cass_value_bind_{none,bool,int32,int64,string,bytes}.
    /// It is used to bind C++ data types used by Kea into formats used by Cassandra.
    ///
    /// @param statement Statement object representing the query
    /// @param stindex Index of statement being executed
    /// @param data array that has been created for the type of lease in question.
    /// @param exchange Exchange object to use
    /// @param tagged_statements CqlTaggedStatement array to use
    static void
    bindData(CassStatement* statement, const uint32_t stindex,
            CqlDataArray& data, const SqlExchange& exchange, CqlTaggedStatement* tagged_statements);

    /// @brief Retrieves data returned by Cassandra.
    ///
    /// This method calls one of cass_value_get_{none,bool,int32,int64,string,bytes}.
    /// It is used to retrieve data returned by Cassandra into standard C++ types
    /// used by Kea.
    ///
    /// @param row row of data returned by CQL library
    /// @param pindex Index of statement being executed
    /// @param data array that has been created for the type of lease in question.
    /// @param size a structure that holds information about size
    /// @param dindex data index (specifies which entry in size array is used)
    /// @param exchange Exchange object to use
    static void
    getData(const CassRow* row, const int pindex, CqlDataArray& data,
            const int dindex, const SqlExchange& exchange);
};

class CqlVersionExchange : public virtual SqlExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlVersionExchange() {
        // Set the column names
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("version",
            parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("minor",
            parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        BOOST_ASSERT(parameters_.size() == 2U);
    }
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // CQL_EXCHANGE_H
