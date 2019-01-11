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

#ifndef CQL_EXCHANGE_H
#define CQL_EXCHANGE_H

#include <cql/cql_connection.h>

#include <database/db_exceptions.h>
#include <database/sql_common.h>

#include <boost/any.hpp>  // for boost::any

#include <string>
#include <vector>

namespace isc {
namespace db {

/// @brief function type to check if transaction action has been applied
typedef bool has_transaction_action_been_applied_t(CassFuturePtr&, uint32_t&);

/// @brief Host identifier converted to Cassandra data type
typedef std::vector<cass_byte_t> CassBlob;

/// @brief Structure used to bind C++ input values to dynamic CQL parameters
///
/// The structure contains a vector which stores the input values. The vector is
/// passed directly into the CQL execute call. Note that the data values are
/// stored as pointers. These pointers need to be valid for the duration of the
/// CQL statement execution. In other words, populating them with pointers that
/// go out of scope before the statement is executed results in undefined
/// behaviour.
struct AnyArray : public std::vector<boost::any> {
    /// @brief Constructors
    /// @{
    AnyArray() {
        // 32: the atomic number of germanium
        std::vector<boost::any>::reserve(32);
    }
    AnyArray(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type())
        : std::vector<boost::any>(il, alloc) {
    }
    /// @}

    /// @brief Add a value at the end of the vector.
    void add(const boost::any& value) {
        std::vector<boost::any>::push_back(value);
    }

    /// @brief Remove the void pointer to the data value from a specified
    ///     position inside the vector.
    void remove(const size_t& index) {
        if (std::vector<boost::any>::size() <= index) {
            isc_throw(BadValue, "AnyArray::remove(): index "
                                    << index << " out of bounds: [0, "
                                    << (std::vector<boost::any>::size() - 1) << "]");
        }
        std::vector<boost::any>::erase(std::vector<boost::any>::begin() + index);
    }
};

/// @brief Binds a C++ object to a Cassandra statement's parameter. Used in all
///     statements.
/// @param value the value to be set or retreived
/// @param index offset of the value being processed
/// @param statement pointer to the parent statement being used
typedef CassError (*CqlBindFunction)(const boost::any& value,
                                     const size_t& index,
                                     CassStatementPtr& statement);

/// @brief Converts a single Cassandra column value to a C++ object. Used in
///     SELECT statements.
///
/// @param data the result will be stored here (this pointer will be updated)
/// @param value this value will be converted
typedef CassError (*CqlGetFunction)(const boost::any& data, const CassValue* value);

/// @brief Wrapper over the bind and get functions that interface with Cassandra
struct CqlFunction {
    /// @brief Binds a C++ object to a Cassandra statement's parameter. Used in
    ///     all statements.
    CqlBindFunction cqlBindFunction_;
    /// @brief Converts a single Cassandra column value to a C++ object. Used in
    ///     SELECT statements.
    CqlGetFunction cqlGetFunction_;
    /// @brief name of type used in errors
    std::string name_;
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
    static void bindData(const AnyArray& data, CassStatementPtr& statement);

    /// @brief Retrieves data returned by Cassandra.
    ///
    /// Calls cqlGetFunction_() for every column with its respective type.
    ///
    /// @param row internal Cassandra object containing data returned by
    ///     Cassandra
    /// @param data array containing objects to be populated with results
    static void getData(const CassRow* row, AnyArray& data);
};

/// @brief Cassandra Exchange
///
/// Used to convert between Cassandra CQL and C++ data types. A different
/// exchange is made for every distinct set of columns. Multiple tables may use
/// the same exchange if they have the same columns.
template <typename T>
class CqlExchange : public SqlExchange {
public:
    /// @brief Constructor
    ///
    /// Empty body. Derived constructors specify table columns.
    CqlExchange() {
    }

    /// @brief Destructor
    virtual ~CqlExchange() = 0;

    /// @name Time conversion:
    /// @{
    /// @brief Converts time to Cassandra format
    ///
    /// @param cltt timestamp of last client transmission time to be converted
    /// @param valid_lifetime lifetime of a lease
    /// @param expire expiration time (result will be stored here)
    static void convertToDatabaseTime(const time_t& cltt,
                                      const uint32_t& valid_lifetime,
                                      cass_int64_t& expire) {
        // Calculate expire time. Store it in the 64-bit value so as we can
        // detect overflows.
        cass_int64_t expire_time =
            static_cast<cass_int64_t>(cltt) + static_cast<cass_int64_t>(valid_lifetime);

        if (expire_time > DatabaseConnection::MAX_DB_TIME) {
            isc_throw(BadValue, "CqlExchange(): convertToDatabaseTime(): time value "
                                    << expire_time << " is too large");
        }

        expire = expire_time;
    }

    /// @brief Converts time from Cassandra format
    /// @param expire expiration time in Cassandra format
    /// @param valid_lifetime lifetime of a lease
    /// @param cltt client last transmission time (result will be stored here)
    static void convertFromDatabaseTime(const cass_int64_t& expire,
                                        const cass_int64_t& valid_lifetime,
                                        time_t& cltt) {
        /// @todo: Although 2037 is still far away, there are people who use infinite
        /// lifetimes. Cassandra doesn't have to support it right now, but at least
        /// we should be able to detect a problem.

        // Convert to local time
        cltt = static_cast<time_t>(expire - valid_lifetime);
    }
    /// @}

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    virtual void createBindForSelect(AnyArray& data, StatementTag const& statement_tag = "") = 0;

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
    Collection<T> executeSelect(const CqlConnection& connection,
                                const AnyArray& where_values,
                                StatementTag statement_tag,
                                const bool& single = false) {
        CassError rc;
        AnyArray local_where_values = where_values;

        // Bind the data before the query is executed.
        CqlTaggedStatement tagged_statement = connection.statements_.at(statement_tag);
        CassStatement* rawStatement;
        if (tagged_statement.is_raw_) {
            // The entire query is the first element in data.
            std::string* query = boost::any_cast<std::string*>(local_where_values.back());
            local_where_values.pop_back();
            rawStatement = cass_statement_new(query->c_str(), local_where_values.size());
        } else {
            rawStatement = cass_prepared_bind(tagged_statement.prepared_statement_.get());
            if (!rawStatement) {
                isc_throw(DbOperationError,
                          "CqlExchange::executeSelect(): unable to bind statement "
                              << tagged_statement.name_);
            }
        }
        auto statement = MakePtr(rawStatement);

        // Set specific level of consistency if we're told to do so.
        if (connection.force_consistency_) {
            rc = cass_statement_set_consistency(statement.get(), connection.consistency_);
            if (rc != CASS_OK) {
                isc_throw(DbOperationError,
                          "CqlExchange::executeSelect(): unable to set statement "
                          "consistency for statement "
                              << tagged_statement.name_
                              << ", Cassandra error code: " << cass_error_desc(rc));
            }
        }

        try {
            CqlCommon::bindData(local_where_values, statement);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, ex.what());
        }


        // Everything's ready. Call the actual statement.
        Collection<T> collection;
        {
            auto future = MakePtr(cass_session_execute(connection.session_.get(), statement.get()));
            if (!future) {
                isc_throw(DbOperationError,
                          "CqlExchange::executeSelect(): no CassFuture for statement "
                              << tagged_statement.name_);
            }

            // Wait for the statement execution to complete.
            cass_future_wait(future.get());
            auto const error = connection.checkFutureError(
                "CqlExchange::executeSelect(): cass_session_execute() != CASS_OK", future,
                statement_tag);
            rc = cass_future_error_code(future.get());

            if (rc != CASS_OK) {
                isc_throw(DbOperationError, error);
            }

            // Get column values.
            auto result_collection = MakePtr(cass_future_get_result(future.get()));
            if (single) {
                size_t const result_count = cass_result_row_count(result_collection.get());
                if (result_count < 1) {
                    isc_throw(ZeroRecords, "CqlExchange::executeSelect(): no entry found in the "
                                           "database where only one was expected for statement "
                                               << tagged_statement.name_);
                } else if (result_count > 1) {
                    isc_throw(MultipleRecords,
                              "CqlExchange::executeSelect(): multiple records were found in "
                              "the database where only one was expected for statement "
                                  << tagged_statement.name_);
                }
            }

            // Get results.
            AnyArray return_values;
            auto rows = MakePtr(cass_iterator_from_result(result_collection.get()));
            while (cass_iterator_next(rows.get())) {
                const CassRow* row = cass_iterator_get_row(rows.get());
                createBindForSelect(return_values, statement_tag);
                CqlCommon::getData(row, return_values);
                collection.push_back(retrieve());
            }
            break;
        }
        return collection;
    }

    /// @brief Executes INSERT, UPDATE or DELETE statements.
    ///
    /// @param connection connection used to communicate with the Cassandra
    ///     database
    /// @param assigned_values array of bound objects to be used when inserting
    ///     values
    /// @param statement_tag prepared statement being executed
    /// @param function function that checks if a certain transaction has been
    ///     applied, could be different for commit than it is for rollback
    void executeMutation(const CqlConnection& connection,
                         const AnyArray& assigned_values,
                         StatementTag statement_tag,
                         has_transaction_action_been_applied_t function = NULL) {
        CassError rc;

        // Bind the statement.
        CqlTaggedStatement tagged_statement = connection.statements_.at(statement_tag);
        auto statement = MakePtr(cass_prepared_bind(tagged_statement.prepared_statement_.get()));
        if (!statement) {
            isc_throw(DbOperationError, "CqlExchange::executeMutation(): unable to bind statement "
                                            << tagged_statement.name_);
        }

        // Set specific level of consistency, if told to do so.
        if (connection.force_consistency_) {
            rc = cass_statement_set_consistency(statement.get(), connection.consistency_);
            if (rc != CASS_OK) {
                isc_throw(DbOperationError,
                          "CqlExchange::executeMutation(): unable to set"
                          " statement consistency for statement "
                              << tagged_statement.name_
                              << ", Cassandra error code: " << cass_error_desc(rc));
            }
        }

        try {
            CqlCommon::bindData(assigned_values, statement);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, ex.what());
        }


        {
            auto future = MakePtr(cass_session_execute(connection.session_.get(), statement.get()));
            if (!future) {
                isc_throw(DbOperationError,
                          "CqlExchange::executeMutation(): unable to execute statement "
                              << tagged_statement.name_);
            }
            cass_future_wait(future.get());
            auto const error = connection.checkFutureError(
                "CqlExchange::executeMutation(): cass_session_execute() != CASS_OK", future,
                statement_tag);
            rc = cass_future_error_code(future.get());

            if (rc != CASS_OK) {
                isc_throw(DbOperationError, error);
            }

            // Check if statement has been applied.
            bool applied = statementApplied(future);

            if (function) {
                uint32_t result;
                bool txn_applied = function(future, result);
                applied = applied && txn_applied;
            }

            if (!applied) {
                isc_throw(StatementNotApplied,
                          "CqlExchange::executeMutation(): [applied] is false for statement "
                              << tagged_statement.name_);
            }
            break;
        }
    }

    /// @brief Check if CQL statement has been applied.
    ///
    /// @param future structure used to wait on statement executions
    /// @param row_count number of rows returned
    /// @param column_count number of columns queried
    ///
    /// On insert, a false [applied] means there is a duplicate entry with the
    ///     same priumary key.
    ///
    /// @return true if statement has been successfully applied, false otherwise
    bool
    statementApplied(CassFuturePtr& future, size_t* row_count = NULL, size_t* column_count = NULL) {
        auto result_collection = MakePtr(cass_future_get_result(future.get()));
        if (!result_collection) {
            isc_throw(DbOperationError, "CqlExchange::statementApplied(): unable to get"
                                        " results collection");
        }
        if (row_count) {
            *row_count = cass_result_row_count(result_collection.get());
        }
        if (column_count) {
            *column_count = cass_result_column_count(result_collection.get());
        }
        auto rows = MakePtr(cass_iterator_from_result(result_collection.get()));
        AnyArray data;
        cass_bool_t applied = cass_true;
        while (cass_iterator_next(rows.get())) {
            const CassRow* row = cass_iterator_get_row(rows.get());
            // [applied]: bool
            data.add(&applied);
            CqlCommon::getData(row, data);
        }
        return applied == cass_true;
    }

    /// @brief Copy received data into the derived class' object.
    ///
    /// Copies information about the entity to be retrieved into a holistic
    /// object. Called in @ref executeSelect(). Not implemented for base class
    /// CqlExchange. To be implemented in derived classes.
    ///
    /// @return a pointer to the object retrieved.
    virtual Ptr<T> retrieve() = 0;
};

template <typename T>
CqlExchange<T>::~CqlExchange() {
}

/// @brief Exchange used to retrieve schema version from the keyspace.
class CqlVersionExchange : public CqlExchange<VersionPair> {
public:
    /// @brief Constructor
    ///
    /// Specifies table columns.
    CqlVersionExchange();

    /// @brief Destructor
    ~CqlVersionExchange();

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    void createBindForSelect(AnyArray& data, StatementTag const& statement_tag = "") override final;

    /// @brief Standalone method used to retrieve schema version
    ///
    /// @param connection array of bound objects representing data to be
    /// retrieved
    ///
    /// @return version of schema specified in the prepared statement in the
    /// @ref CqlConnection parameter
    VersionPairPtr retrieveVersion(const CqlConnection& connection);

    /// @brief Copy received data into the <version,minor> pair.
    ///
    /// Copies information about the version to be retrieved into a pair. Called
    /// in executeSelect().
    ///
    /// @return a pointer to the object retrieved.
    VersionPairPtr retrieve() override final;

    /// @brief Statement tags
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
using CqlVersionExchangePtr = std::unique_ptr<CqlVersionExchange>;

struct CqlConfigVersionExchange : public CqlVersionExchange {
    /// @brief Cassandra statements
    static StatementMap tagged_statements_;
};
using CqlConfigVersionExchangePtr = std::unique_ptr<CqlConfigVersionExchange>;

}  // namespace db
}  // namespace isc

#endif  // CQL_EXCHANGE_H
