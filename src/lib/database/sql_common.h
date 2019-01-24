// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2016-2018 Deutsche Telekom AG.
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace isc {
namespace db {

template <typename T>
using Ptr = boost::shared_ptr<T>;

template <typename T>
using Collection = std::vector<Ptr<T>>;

template <typename T>
using Map = std::unordered_map<std::string, T>;

/// @brief Pair containing major and minor versions
using VersionPair = std::pair<uint32_t, uint32_t>;
using VersionPairPtr = boost::shared_ptr<VersionPair>;

/// @brief Base class for backend exchanges.
struct SqlExchange {
    /// @brief Constructor
    SqlExchange() {
    }

    /// @brief Destructor
    virtual ~SqlExchange() = 0;
};

}  // namespace db
}  // namespace isc

#endif  // SQL_COMMON_H
