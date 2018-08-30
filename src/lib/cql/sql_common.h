// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2016-2017 Deutsche Telekom AG.
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

namespace isc {
namespace db {

/// @brief Used to map server data types with internal backend storage data
/// types.
enum ExchangeDataType {
    EXCHANGE_DATA_TYPE_NONE,
    EXCHANGE_DATA_TYPE_BOOL,
    EXCHANGE_DATA_TYPE_INT8,
    EXCHANGE_DATA_TYPE_INT16,
    EXCHANGE_DATA_TYPE_INT32,
    EXCHANGE_DATA_TYPE_INT64,
    EXCHANGE_DATA_TYPE_TIMESTAMP,
    EXCHANGE_DATA_TYPE_STRING,
    EXCHANGE_DATA_TYPE_BYTES,
    EXCHANGE_DATA_TYPE_UUID,
    EXCHANGE_DATA_TYPE_UDT,       ///< User-Defined Type (used in Cassandra)
    EXCHANGE_DATA_TYPE_COLLECTION ///< Collection (used in Cassandra)
};

/// @brief Base class for backend exchanges.
class SqlExchange {
public:
    /// @brief Constructor
    SqlExchange() {
    }

    /// @brief Destructor
    virtual ~SqlExchange() {
    }
};

}  // namespace db
}  // namespace isc

#endif  // SQL_COMMON_H
