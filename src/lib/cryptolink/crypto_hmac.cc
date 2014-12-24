// Copyright (C) 2011, 2014  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
