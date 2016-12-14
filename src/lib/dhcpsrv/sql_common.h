// Copyright (C) 2016 Deutsche Telekom AG.
//
// Author: Cristian Secăreanu <cristian.secareanu@qualitance.com>
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

#ifndef SQL_COMMON_H
#define SQL_COMMON_H

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

/// @brief Used to map server data types with internal backend storage data
/// types.
enum ExchangeDataType {
    EXCHANGE_DATA_TYPE_NONE,
    EXCHANGE_DATA_TYPE_BOOL,
    EXCHANGE_DATA_TYPE_INT32,
    EXCHANGE_DATA_TYPE_INT64,
    EXCHANGE_DATA_TYPE_TIMESTAMP,
    EXCHANGE_DATA_TYPE_STRING,
    EXCHANGE_DATA_TYPE_BYTES,
    EXCHANGE_DATA_TYPE_UUID
};

/// @brief Used to specify the direction of the data exchange between the
/// database and the server.
enum ExchangeDataTypeIO {
    EXCHANGE_DATA_TYPE_IO_IN,
    EXCHANGE_DATA_TYPE_IO_OUT,
    EXCHANGE_DATA_TYPE_IO_IN_OUT
};

/// @brief Used to map the column name with internal backend storage data types.
struct ExchangeColumnInfo {
    ExchangeColumnInfo()
        : name_(""), index_(0), type_io_(EXCHANGE_DATA_TYPE_IO_IN_OUT),
          type_(EXCHANGE_DATA_TYPE_NONE){};
    ExchangeColumnInfo(const char* name,
                       const uint32_t index,
                       const ExchangeDataTypeIO type_io,
                       const ExchangeDataType type)
        : name_(name), index_(index), type_io_(type_io), type_(type){};
    std::string name_;
    uint32_t index_;
    ExchangeDataTypeIO type_io_;
    ExchangeDataType type_;
};

/// @brief Smart pointer to an @ref ExchangeColumnInfo
typedef boost::shared_ptr<ExchangeColumnInfo> ExchangeColumnInfoPtr;

/// @brief Multimap that allows indexing @ref ExchangeColumnInfoPtr
///     sequentially, by index and by name.
typedef boost::multi_index_container<
    // Container comprises elements of ExchangeColumnInfoPtr type.
    ExchangeColumnInfoPtr,
    // Here we start enumerating various indexes.
    boost::multi_index::indexed_by<
        // Index #0. Sequenced index allows accessing elements in the same way
        // as in std::list.
        boost::multi_index::sequenced<>,
        // Index #1
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                std::string,
                &ExchangeColumnInfo::name_
             >
        >,
        // Index #2
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                uint32_t,
                &ExchangeColumnInfo::index_
            >
        >
    >
> ExchangeColumnInfoContainer;

/// @brief Pointer to the ExchangeColumnInfoContainer object.
typedef boost::shared_ptr<ExchangeColumnInfoContainer>
    ExchangeColumnInfoContainerPtr;

/// @brief Type of the index #1 - name.
typedef ExchangeColumnInfoContainer::nth_index<1>::type
    ExchangeColumnInfoContainerName;

/// @brief Pair of iterators to represent the range of ExchangeColumnInfo having
/// the
/// same name value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerName::const_iterator,
                  ExchangeColumnInfoContainerName::const_iterator>
    ExchangeColumnInfoContainerNameRange;

/// @brief Type of the index #2 - index.
typedef ExchangeColumnInfoContainer::nth_index<2>::type
    ExchangeColumnInfoContainerIndex;

/// @brief Pair of iterators to represent the range of ExchangeColumnInfo having
/// the
/// same index value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerIndex::const_iterator,
                  ExchangeColumnInfoContainerIndex::const_iterator>
    ExchangeColumnInfoContainerIndexRange;

/// @brief Base class for backend exchanges.
class SqlExchange {
public:
    /// @brief Constructor
    SqlExchange() {
    }

    /// @brief Destructor
    virtual ~SqlExchange() {
    }

    /// @brief Column names and types
    ExchangeColumnInfoContainer parameters_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // SQL_COMMON_H
