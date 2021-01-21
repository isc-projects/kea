// Copyright (C) 2018,2021 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CQL_EXCHANGE_H
#define CQL_EXCHANGE_H

#include <cql/cql_connection.h>
#include <cql/sql_common.h>

#include <boost/any.hpp>  // for boost::any

#include <string>
#include <typeinfo>       // for std::type_info
#include <unordered_map>  // for std::unordered_map
#include <utility>
#include <vector>

namespace isc {
namespace db {

/// @brief Host identifier converted to Cassandra data type
typedef std::vector<cass_byte_t> CassBlob;

/// @brief Forward declaration to @ref CqlExchange
class CqlExchange;

/// @brief Structure used to bind C++ input values to dynamic CQL parameters
///
/// The structure contains a vector which stores the input values. The vector is
/// passed directly into the CQL execute call. Note that the data values are
/// stored as pointers. These pointers need to be valid for the duration of the
/// CQL statement execution. In other words, populating them with pointers that
/// go out of scope before the statement is executed results in undefined
/// behaviour.
class AnyArray : public std::vector<boost::any> {
public:
    /// @brief Add a value at the end of the vector.
    void add(const boost::any& value);

    /// @brief Remove the void pointer to the data value from a specified
    ///     position inside the vector.
    void remove(const size_t& index);
};

// @brief Representation of a Cassandra User Defined Type
class Udt : public AnyArray {
public:
    /// @brief Parameterized constructor
    Udt(const CqlConnection& connection, const std::string& name);

    /// @brief Destructor
    ~Udt();

    /// @brief Frees the underlying container.
    void freeUserType();

    /// @brief Creates the underlying container.
    void newUserType();

    /// @brief Connection to the Cassandra database
    const CqlConnection& connection_;

    /// @brief Name of the UDT in the schema: CREATE TYPE ___ { ... }
    const std::string name_;

    /// @brief Internal Cassandra driver object representing a Cassandra data
    ///     type
    const CassDataType* cass_data_type_;

    /// @brief Internal Cassandra driver object representing a user defined type
    CassUserType* cass_user_type_;
};

/// @brief Defines an array of arbitrary objects (used by Cassandra backend)
typedef AnyArray AnyCollection;

/// @brief Binds a C++ object to a Cassandra statement's parameter. Used in all
///     statements.
/// @param value the value to be set or retrieved
/// @param index offset of the value being processed
/// @param statement pointer to the parent statement being used
typedef CassError (*CqlBindFunction)(const boost::any& value,
                                     const size_t& index,
                                     CassStatement* statement);

/// @brief Sets a member in a UDT. Used in INSERT & UPDATE statements.
/// @param value the value to be set or retrieved
/// @param index offset of the value being processed
/// @param cass_user_type pointer to the user type that uses this member
typedef CassError (*CqlUdtSetFunction)(const boost::any& value,
                                       const size_t& index,
                                       CassUserType* cass_user_type);

/// @brief Sets an item in a collection. Used in INSERT & UPDATE statements.
/// @param value pointer to a value to be inserted or updated
/// @param collection pointer to collection to be inserted or updated
typedef CassError (*CqlCollectionAppendFunction)(const boost::any& value,
                                                 CassCollection* collection);

/// @brief Converts a single Cassandra column value to a C++ object. Used in
///     SELECT statements.
///
/// @param data the result will be stored here (this pointer will be updated)
/// @param value this value will be converted
typedef CassError (*CqlGetFunction)(const boost::any& data,
                                    const CassValue* value);

/// @brief Wrapper over the bind and get functions that interface with Cassandra
struct CqlFunction {
    /// @brief Binds a C++ object to a Cassandra statement's parameter. Used in
    ///     all statements.
    CqlBindFunction cqlBindFunction_;
    /// @brief Sets a member in a UDT. Used in INSERT & UPDATE statements.
    CqlUdtSetFunction cqlUdtSetFunction_;
    /// @brief Sets an item in a collection. Used in INSERT & UPDATE statements.
    CqlCollectionAppendFunction cqlCollectionAppendFunction_;
    /// @brief Converts a single Cassandra column value to a C++ object. Used in
    ///     SELECT statements.
    CqlGetFunction cqlGetFunction_;
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
    /// @brief Converts time to Cassandra format
    ///
    /// @param cltt timestamp of last client transmission time to be converted
    /// @param valid_lifetime lifetime of a lease
    /// @param expire expiration time (result will be stored here)
    static void convertToDatabaseTime(const time_t& cltt,
                                      const uint32_t& valid_lifetime,
                                      cass_int64_t& expire);

    /// @brief Converts time from Cassandra format
    /// @param expire expiration time in Cassandra format
    /// @param valid_lifetime lifetime of a lease
    /// @param cltt client last transmission time (result will be stored here)
    static void convertFromDatabaseTime(const cass_int64_t& expire,
                                        const cass_int64_t& valid_lifetime,
                                        time_t& cltt);
    /// @}

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    virtual void createBindForSelect(AnyArray& data,
                                     StatementTag statement_tag = NULL) = 0;

    /// @brief Executes SELECT statements.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param where_values array of bound objects used to filter the results
    /// @param statement_tag prepared statement being executed
    /// @param single true if a single row should be returned; by default,
    /// multiple rows are allowed
    ///
    /// @return collection of boost::any objects
    ///
    /// @throw DbOperationError
    /// @throw MultipleRecords
    AnyArray executeSelect(const CqlConnection& connection,
                           const AnyArray& where_values,
                           StatementTag statement_tag,
                           const bool& single = false);

    /// @brief Executes INSERT, UPDATE or DELETE statements.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param assigned_values array of bound objects to be used when inserting
    ///     values
    /// @param statement_tag prepared statement being executed
    ///     applied, could be different for commit than it is for rollback
    void executeMutation(const CqlConnection& connection,
                         const AnyArray& assigned_values,
                         StatementTag statement_tag);

    /// @brief Check if CQL statement has been applied.
    ///
    /// @param future structure used to wait on statement executions
    /// @param row_count number of rows returned
    /// @param column_count number of columns queried
    ///
    /// On insert, a false [applied] means there is a duplicate entry with the
    ///     same primary key.
    ///
    /// @return true if statement has been successfully applied, false otherwise
    bool statementApplied(CassFuture* future, size_t* row_count = NULL,
                          size_t* column_count = NULL);

    /// @brief Copy received data into the derived class' object.
    ///
    /// Copies information about the entity to be retrieved into a holistic
    /// object. Called in @ref executeSelect(). Not implemented for base class
    /// CqlExchange. To be implemented in derived classes.
    ///
    /// @return a pointer to the object retrieved.
    virtual boost::any retrieve() = 0;
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
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    virtual void
    createBindForSelect(AnyArray& data,
                        StatementTag statement_tag = NULL) override;

    /// @brief Standalone method used to retrieve schema version
    ///
    /// @param connection array of bound objects representing data to be
    /// retrieved
    ///
    /// @return version of schema specified in the prepared statement in the
    /// @ref CqlConnection parameter
    virtual VersionPair retrieveVersion(const CqlConnection& connection);

    /// @brief Copy received data into the <version,minor> pair.
    ///
    /// Copies information about the version to be retrieved into a pair. Called
    /// in executeSelect().
    ///
    /// @return a pointer to the object retrieved.
    virtual boost::any retrieve() override;

    /// @brief Statement tags definitions
    /// @{
    static constexpr StatementTag GET_VERSION = "GET_VERSION";
    /// @}

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

private:
    /// @brief Major version
    cass_int32_t version_;
    /// @brief Minor version
    cass_int32_t minor_;
    /// @brief Pair containing major and minor version
    VersionPair pair_;
};

/// @brief Common operations in Cassandra exchanges
class CqlCommon {
public:
    /// @brief Assigns values to every column of an INSERT or an UPDATE statement.
    ///
    /// Calls cqlBindFunction_() for every column with its respective type.
    ///
    /// @param data array containing column values to be passed to the statement
    ///     being executed
    /// @param statement internal Cassandra object representing the statement
    ///     being executed
    static void bindData(const AnyArray& data, CassStatement* statement);

    /// @brief Retrieves data returned by Cassandra.
    ///
    /// Calls cqlGetFunction_() for every column with its respective type.
    ///
    /// @param row internal Cassandra object containing data returned by
    ///     Cassandra
    /// @param data array containing objects to be populated with results
    static void getData(const CassRow* row, AnyArray& data);
};

/// @brief Determine exchange type based on boost::any type.
ExchangeDataType
exchangeType(const boost::any& object);

/// @brief Determine exchange type based on CassValueType.
ExchangeDataType
exchangeType(const CassValueType& type);

}  // namespace db
}  // namespace isc

#endif  // CQL_EXCHANGE_H
