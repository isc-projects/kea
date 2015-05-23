// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_asym.h>

using namespace std;
using namespace isc::cryptolink;

int main(int argc, char* argv[]) {
    // Take one argument (K file root)
    if (argc != 2) {
        cerr << "usage: from_bind9 K<name>+<algo>+<tag>" << endl;
        return (-1);
    }

    // Get the public key from DNS
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    string keyfile = argv[1];
    keyfile += ".key";
    boost::shared_ptr<Asym> key(crypto.createAsym(keyfile, "",
                                                  RSA_, SHA256,
                                                  PUBLIC, DNS),
                                deleteAsym);
    if (!key) {
        cerr << "createAsym failed" << endl;
        return (-1);
    }

    // Export the public key in SubjectPublicKeyInfo der on stdout
    const std::vector<uint8_t> keybin = key->exportkey(PUBLIC, ASN1);
    const ssize_t cc = write(1, &keybin[0], keybin.size());
    if (cc < 0) {
        cerr << "write failed" << endl;
        return (-1);
    }
    if (static_cast<size_t>(cc) != keybin.size()) {
        cerr << "truncated write" << endl;
        return (-1);
    }
    return (0);
}
