// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <boost/scoped_ptr.hpp>

#include <cstring>

namespace isc {
namespace cryptolink {

void
digest(const void* data, const size_t data_len,
       const HashAlgorithm hash_algorithm,
       isc::util::OutputBuffer& result, size_t len)
{
    boost::scoped_ptr<Hash> hash(
        CryptoLink::getCryptoLink().createHash(hash_algorithm));
    hash->update(data, data_len);
    if (len == 0) {
        len = hash->getOutputLength();
    }
    hash->final(result, len);
}

void
deleteHash(Hash* hash) {
    delete hash;
}

} // namespace cryptolink
} // namespace isc
