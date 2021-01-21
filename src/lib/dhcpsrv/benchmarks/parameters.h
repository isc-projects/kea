// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BENCHMARKS_PARAMETERS_H
#define BENCHMARKS_PARAMETERS_H

#include <benchmark/benchmark.h>

namespace isc {
namespace dhcp {
namespace bench {

/// @defgroup benchmark_params Benchmark parameters that define boundary values
///           for benchmarks.
///
/// The range is defined as 512..65533. Google benchmark will pick a few specific
/// values: 512, 4096, 32768, 65533.

/// @{

/// @brief A minimum number of leases used in a benchmark
constexpr size_t MIN_LEASE_COUNT = 512;
/// @brief A maximum number of leases used in a benchmark
constexpr size_t MAX_LEASE_COUNT = 0xfffd;

/// @brief A minimum number of leases used in a benchmark
constexpr size_t MIN_HOST_COUNT = 512;
/// @brief A maximum number of leases used in a benchmark
constexpr size_t MAX_HOST_COUNT = 0xfffd;

/// @brief A time unit used - all results to be expressed in us (microseconds)
constexpr benchmark::TimeUnit UNIT = benchmark::kMicrosecond;

/// @}

}  // namespace bench
}  // namespace dhcp
}  // namespace isc

#endif
