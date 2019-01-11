// Copyright (C) 2018 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
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

#ifndef CQL_MEMORY_MGR_H
#define CQL_MEMORY_MGR_H

#include <cassandra.h>

#include <memory>

namespace isc {
namespace db {

/// @{
typedef std::unique_ptr<CassCluster, void (*)(CassCluster*)> CassClusterPtr;
CassClusterPtr MakePtr(CassCluster*);
/// @}

/// @{
typedef std::unique_ptr<CassFuture, void (*)(CassFuture*)> CassFuturePtr;
CassFuturePtr MakePtr(CassFuture*);
/// @}

/// @{
typedef std::unique_ptr<CassIterator, void (*)(CassIterator*)> CassIteratorPtr;
CassIteratorPtr MakePtr(CassIterator*);
/// @}

/// @{
typedef std::shared_ptr<CassPrepared const> CassPreparedPtr;
CassPreparedPtr MakePtr(CassPrepared const*);
/// @}

/// @{
typedef std::unique_ptr<CassResult const, void (*)(CassResult const*)> CassResultPtr;
CassResultPtr MakePtr(CassResult const*);
/// @}

/// @{
typedef std::unique_ptr<CassStatement, void (*)(CassStatement*)> CassStatementPtr;
CassStatementPtr MakePtr(CassStatement*);
/// @}

/// @{
typedef std::unique_ptr<CassSession, void (*)(CassSession*)> CassSessionPtr;
CassSessionPtr MakePtr(CassSession*);
/// @}

/// @{
typedef std::unique_ptr<CassSsl, void (*)(CassSsl*)> CassSslPtr;
CassSslPtr MakePtr(CassSsl*);
/// @}

/// @{
typedef std::unique_ptr<CassUuidGen, void (*)(CassUuidGen*)> CassUuidGenPtr;
CassUuidGenPtr MakePtr(CassUuidGen*);
/// @}

}  // namespace db
}  // namespace isc

#endif  // CQL_MEMORY_MGR_H
