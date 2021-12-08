// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_TSIG_KEY_H
#define D2_TSIG_KEY_H

#include <dns/name.h>
#include <dns/tsig.h>
#include <boost/shared_ptr.hpp>

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
    /// @param key_spec Specification of the key
    /// (name:secret[:algorithm][:digestbits])
    explicit D2TsigKey(const std::string& key_spec);

    /// @brief Constructor.
    ///
    /// Initialize the key statistics.
    ///
    /// @param key_name The name of the key as a domain name.
    /// @param algorithm_name The hash algorithm used for this key in the
    /// form of domain name.
    /// @param secret Point to a binary sequence of the shared secret to be
    /// used for this key.
    /// @param secret_len The size of the binary %data (@c secret) in bytes.
    /// @param digestbits The number of bits to include in the digest
    /// (0 means to include all)
    D2TsigKey(const dns::Name& key_name, const dns::Name& algorithm_name,
              const void* secret, size_t secret_len, size_t digestbits = 0);

    /// @brief Destructor.
    ///
    /// Remove the key statistics.
    virtual ~D2TsigKey();

    /// @brief Reset statistics.
    ///
    virtual void resetStats();

    /// @brief Create TSIG context.
    ///
    /// @note Derived classes can implement their own specific context.
    ///
    /// @return The specific @ref dns::TSIGContext of the @ref dns::TSIGKey.
    virtual dns::TSIGContextPtr createContext();

private:
    /// @brief Initialize key statistics.
    void initStats();

    /// @brief Remove key statistics.
    void removeStats();
};

/// @brief Type of pointer to a D2 TSIG key.
typedef boost::shared_ptr<D2TsigKey> D2TsigKeyPtr;

} // namespace d2
} // namespace isc

#endif // D2_TSIG_KEY_H
