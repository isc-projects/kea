// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WIRE_DATA_H
#define WIRE_DATA_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace isc {
namespace tcp {

/// @brief Defines a data structure for storing raw bytes of data on the wire.
typedef std::vector<uint8_t> WireData;
typedef boost::shared_ptr<WireData> WireDataPtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif
