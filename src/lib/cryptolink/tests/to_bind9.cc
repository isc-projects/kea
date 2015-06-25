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
    // Take one argument (PKCS#8 file and root)
    if (argc != 2) {
        cerr << "usage: to_bind9 <pkcs#8-file>" << endl;
        return (-1);
    }

    // Get the private key from PKCS#8
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    string keyfile = argv[1];
    boost::shared_ptr<Asym> key(crypto.createAsym(keyfile, "",
                                                  RSA_, SHA256,
                                                  PRIVATE, ASN1),
                                deleteAsym);
    if (!key) {
        cerr << "createAsym failed" << endl;
        return (-1);
    }

    // Export the public key in DNSSEC format
    string pubfile = keyfile + ".key";
    key->exportkey(pubfile, "", PUBLIC, DNS);

    // Export the private key in DNSSEC format
    string privfile = keyfile + ".private";
    key->exportkey(privfile, "", PRIVATE, DNS);

    return (0);
}
