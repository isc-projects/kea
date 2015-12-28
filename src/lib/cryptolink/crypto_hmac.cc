// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <boost/scoped_ptr.hpp>

#include <cstring>

namespace isc {
namespace cryptolink {

void
signHMAC(const void* data, const size_t data_len, const void* secret,
         size_t secret_len, const HashAlgorithm hash_algorithm,
         isc::util::OutputBuffer& result, size_t len)
{
    boost::scoped_ptr<HMAC> hmac(
        CryptoLink::getCryptoLink().createHMAC(secret,
                                               secret_len,
                                               hash_algorithm));
    hmac->update(data, data_len);
    if (len == 0) {
        len = hmac->getOutputLength();
    }
    hmac->sign(result, len);
}


bool
verifyHMAC(const void* data, const size_t data_len, const void* secret,
           size_t secret_len, const HashAlgorithm hash_algorithm,
           const void* sig, const size_t sig_len)
{
    boost::scoped_ptr<HMAC> hmac(
        CryptoLink::getCryptoLink().createHMAC(secret,
                                               secret_len,
                                               hash_algorithm));
    hmac->update(data, data_len);
    size_t len = sig_len;
    if (len == 0) {
        len = hmac->getOutputLength();
    }
    return (hmac->verify(sig, len));
}

void
deleteHMAC(HMAC* hmac) {
    delete hmac;
}

} // namespace cryptolink
} // namespace isc
