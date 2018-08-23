// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <boost/noncopyable.hpp>

#include <cryptolink/cryptolink.h>

#ifndef ISC_CRYPTO_RNG_H
#define ISC_CRYPTO_RNG_H

namespace isc {
namespace cryptolink {

/// \brief RNG support
///
/// This class is used to get the RNG.
/// The global instance can be get with CryptoLink::getRNG()
///
class RNG : private boost::noncopyable {
public:
    /// \brief Constructor from a Random Number Generator
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    RNG();

    /// \brief Destructor
    virtual ~RNG();

    /// \brief Generate random value.
    ///
    /// The result will be returned as a std::vector<uint8_t>
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param len The number of bytes from the result to generate.
    /// \return a vector containing random value.
    virtual std::vector<uint8_t> random(size_t len) = 0;

private:
    friend RNGPtr& CryptoLink::getRNG();
};

/// \brief Generate random value. 
///
/// This is a convenience function that generate random data
/// given a fixed amount of data. Internally it does the same as
/// creating an RNG object and generating the resulting value.
///
/// \exception LibraryError if there was any unexpected exception
///                         in the underlying library
///
/// \param len The length of the data
std::vector<uint8_t> random(size_t len);

} // namespace cryptolink
} // namespace isc

#endif // ISC_CRYPTO_RNG_H

