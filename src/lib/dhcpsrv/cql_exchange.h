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

#ifndef CQL_EXCHANGE_H
#define CQL_EXCHANGE_H

#include <cassandra.h>
#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/sql_common.h>
#include <exceptions/exceptions.h>

#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Binds a C++ object to a Cassandra statement's parameter. Used in all
///     statements.
typedef CassError (*CqlBindFunction)(CassStatement* statement,
                                     size_t index,
                                     void* value);

/// @brief Converts a single Cassandra column value to a C++ object. Used in
///     SELECT statements.
typedef CassError (*CqlGetFunction)(const CassValue* value, void* data);

/// @brief Pair containing major and minor versions.
typedef std::pair<uint32_t, uint32_t> VersionPair;

/// @brief Wrapper over the bind and get functions that interface with Cassandra
struct CqlFunctionData {
    /// @brief Binds a C++ object to a Cassandra statement's parameter. Used in
    /// all
    ///     statements.
    CqlBindFunction cqlBindFunction_;
    /// @brief Converts a single Cassandra column value to a C++ object. Used in
    ///     SELECT statements.
    CqlGetFunction cqlGetFunction_;
};

/// @brief Collection of bind and get functions, one pair for each
///     parameter/column
extern struct CqlFunctionData CqlFunctions[];

/// @brief Structure used to bind C++ input values to dynamic CQL parameters
///
/// The structure contains a vector which stores the input values. The vector is
/// passed directly into the CQL execute call. Note that the data values are
/// stored as pointers. These pointers need to be valid for the duration of the
/// CQL statement execution. In other words, populating them with pointers that
/// go out of scope before the statement is executed results in undefined
/// behaviour.
struct CqlDataArray {
    /// @brief Constructor
    CqlDataArray() {
    }

    /// @brief Copy constructor
    CqlDataArray(const CqlDataArray& other) : values_(other.values_) {
    }

    /// @brief Destructor
    virtual ~CqlDataArray() {
    }

    /// @brief Add a at the end of the vector.
    void add(void* value) {
        values_.push_back(value);
    }

    /// @brief Remove the void pointer to the data value from a specified
    ///     position inside the vector.
    void remove(int index) {
        if (values_.size() <= index) {
            isc_throw(BadValue, "Index " << index << " out of bounds: [0, "
                                         << (values_.size() - 1) << "]");
        }
        values_.erase(values_.begin() + index);
    }

    /// @brief Remove all data from the vector.
    void clear() {
        values_.clear();
    }

    /// @brief Get the number of elements inside the vector.
    size_t size() const {
        return values_.size();
    }

    /// @brief Check if the vector is empty.
    bool empty() const {
        return values_.empty();
    }

    /// @brief Square brackets operator overload
    ///
    /// Retrieves void pointer at specified position.
    void* operator[](int i) const {
        return values_[i];
    }

    /// @brief Iterator pointing to the first element
    std::vector<void*>::const_iterator begin() const {
        return values_.begin();
    }

    /// @brief Iterator pointing to the past-the-end element
    std::vector<void*>::const_iterator end() const {
        return values_.end();
    }

    /// @brief Vector of pointers to the data values
    std::vector<void*> values_;
};

/// @brief Cassandra Exchange
///
/// Used to convert between Cassandra CQL and C++ data types. A different
/// exchange is made for every distinct set of columns. Multiple tables may use
/// the same exchange if they have the same columns.
class CqlExchange : public virtual SqlExchange {
public:
    /// @brief Constructor
    ///
    /// Empty body. Derived constructors specify table columns.
    CqlExchange();

    /// @brief Destructor
    virtual ~CqlExchange();

    /// @name Time conversion:
    /// @{
    static void convertToDatabaseTime(const time_t& cltt,
                                      const cass_int64_t& valid_lifetime,
                                      cass_int64_t& expire);
    static void convertFromDatabaseTime(const cass_int64_t& expire,
                                        const cass_int64_t& valid_lifetime,
                                        time_t& cltt);
    /// @}

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeRead() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statementIndex prepared statement to be executed; defaults to an
    ///     invalid index
    virtual void createBindForReceive(CqlDataArray& data,
                                      const int statementIndex = -1);

    /// @brief Executes select statements.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param whereValues array of bound objects used to filter the results
    /// @param statementIndex prepared statement being executed
    /// @param single true if a single row should be returned; by default,
    /// multiple rows are allowed
    /// @param parameters Output parameters of a statement ( used in WHERE
    ///     clause ); optional, needed only if parameters in the statement are
    ///     in a different order than in the schema
    ///
    /// @return collection of void* objects
    ///
    /// @throw DbOperationError
    /// @throw MultipleRecords
    CqlDataArray executeRead(const CqlConnection& connection,
                             const CqlDataArray& whereValues,
                             const int statementIndex,
                             const bool single = false,
                             const std::vector<std::string>& parameters =
                                 std::vector<std::string>());

    /// @brief Executes insert, update, delete or other statements.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param assignedValues array of bound objects to be used when inserting
    ///     values
    /// @param statementIndex prepared statement to be executed
    void executeWrite(const CqlConnection& connection,
                      const CqlDataArray& assignedValues,
                      const int statementIndex);

    /// @brief Check if CQL statement has been applied.
    ///
    /// @param future structure used to wait on statement executions
    /// @param row_count number of rows returned
    /// @param column_count number of columns queried
    ///
    /// @return true if statement has been succesfully applied, false otherwise
    bool hasStatementBeenApplied(CassFuture* future,
                                 size_t* row_count = NULL,
                                 size_t* column_count = NULL);

    /// @brief Copy received data into the derived class' object.
    ///
    /// Copies information about the entity to be retrieved into a holistic
    /// object. Called in @ref executeRead(). Not implemented for base class
    /// CqlExchange. To be implemented in derived classes.
    ///
    /// @return a pointer to the object retrieved.
    virtual void* retrieve();
};

/// @brief Exchange used to retrieve schema version from the keyspace.
class CqlVersionExchange : public virtual CqlExchange {
public:
    /// @brief Constructor
    ///
    /// Specifies table columns.
    CqlVersionExchange();

    /// @brief Destructor
    virtual ~CqlVersionExchange();

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeRead() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statementIndex prepared statement to be executed; defaults to an
    ///     invalid index
    virtual void createBindForReceive(CqlDataArray& data,
                                      const int statementIndex = -1);

    /// @brief Standalone method used to retrieve schema version
    ///
    /// @param connection array of bound objects representing data to be
    /// retrieved
    /// @param statementIndex prepared statement to be executed
    ///
    /// @return version of schema specified in the prepared statement in the
    /// @ref CqlConnection parameter
    virtual VersionPair
    retrieveVersion(const CqlConnection& connection, int statementIndex);

    /// @brief Copy received data into the <version,minor> pair.
    ///
    /// Copies information about the version to be retrieved into a pair. Called
    /// in executeRead().
    ///
    /// @return a pointer to the object retrieved.
    virtual void* retrieve();

private:
    cass_int32_t version_;
    cass_int32_t minor_;
    VersionPair pair_;
};

/// @brief Common operations in Cassandra exchanges
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
    getDataType(const uint32_t stindex,
                int pindex,
                const SqlExchange& exchange,
                const CqlTaggedStatement* tagged_statements);

    /// @brief Binds data specified in data
    ///
    /// Calls one of cass_value_bind_([none|bool|int32|int64|string|bytes]).
    /// It is used to bind C++ data types used by Kea into formats used by
    /// Cassandra.
    ///
    /// @param statement Statement object representing the query
    /// @param stindex Index of statement being executed
    /// @param data array that has been created for the type of lease in
    ///     question.
    /// @param exchange Exchange object to use
    /// @param tagged_statements CqlTaggedStatement array to use
    static void bindData(CassStatement* statement,
                         uint32_t stindex,
                         const CqlDataArray& data,
                         const SqlExchange& exchange,
                         const CqlTaggedStatement* tagged_statements);

    /// @brief Retrieves data returned by Cassandra.
    ///
    /// Calls one of cass_value_bind_([none|bool|int32|int64|string|bytes]).
    /// Used to retrieve data returned by Cassandra into standard C++ types used
    /// by Kea.
    ///
    /// @param row row of data returned by CQL library
    /// @param pindex Index of statement being executed
    /// @param dindex data index (specifies which entry in size array is used)
    /// @param exchange Exchange object to use
    /// @param data array that has been created for the type of lease in
    ///     question.
    static void getData(const CassRow* row,
                        int pindex,
                        int dindex,
                        const SqlExchange& exchange,
                        CqlDataArray& data);
};

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_EXCHANGE_H
