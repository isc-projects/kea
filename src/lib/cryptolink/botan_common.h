// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace isc {
namespace cryptolink {
namespace btn {

/// @brief Decode the HashAlgorithm enum into a name usable by Botan
///
/// @param algorithm algorithm to be converted
/// @return static text representation of the algorithm name
const char*
getHashAlgorithmName(isc::cryptolink::HashAlgorithm algorithm);

} // namespace btn
} // namespace cryptolink
} // namespace isc
