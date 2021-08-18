// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_TSIG_KEY_H
#define D2_TSIG_KEY_H

#include <dns/name.h>
#include <dns/tsigkey.h>
#include <boost/shared_ptr.hpp>

#include <set>

namespace isc {
namespace d2 {

/// @brief Statistics keeping extension of the DNS TSIGKey class.
///
/// Implements a TSIGKey derived class which can be used as the value
/// of TSIGKeyPtr so with minimal or no update to the DNS++ library.
class D2TsigKey : public dns::TSIGKey {
public:
    /// @brief Constructor.
    ///
    /// Initialize the key statistics.
    ///
    /// @param key_name Domain name of the key.
    D2TsigKey(const std::string& key_name);

    /// @brief Destructor.
    ///
    /// Remove the key statistics.
    virtual ~D2TsigKey();

    /// @brief Reset statistics.
    ///
    virtual void resetStats();

    /// @brief Statistics names (key).
    ///
    /// The list of statistic names for keys.
    static std::set<std::string> keyStats;

    /// @brief Statistics names (global).
    ///
    /// The list of global statistic names.
    static std::set<std::string> globalStats;
};

/// @brief Type of pointer to a D2 TSIG key.
typedef boost::shared_ptr<D2TsigKey> D2TsigKeyPtr;

} // namespace d2
} // namespace isc

#endif // D2_TSIG_KEY_H
