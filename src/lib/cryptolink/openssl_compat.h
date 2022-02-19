// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is included by hash and hmac codes so KEA_H* macros
// avoid to define unused inlines.

#ifdef KEA_HASH

#ifndef HAVE_EVP_MD_CTX_NEW
#ifdef HAVE_EVP_MD_CTX_CREATE

// EVP_MD_CTX_new() is EVP_MD_CTX_create() in old OpenSSL

inline EVP_MD_CTX* EVP_MD_CTX_new() {
    return (EVP_MD_CTX_create());
}

#else
#error have no EVP_MD_CTX_new() nor EVP_MD_CTX_create()
#endif
#endif

#ifndef HAVE_EVP_MD_CTX_FREE
#ifdef HAVE_EVP_MD_CTX_DESTROY

// EVP_MD_CTX_free(ctx) is EVP_MD_CTX_destroy(ctx) in old OpenSSL

inline void EVP_MD_CTX_free(EVP_MD_CTX* ctx) {
    EVP_MD_CTX_destroy(ctx);
}

#else
#error have no EVP_MD_CTX_free() nor EVP_MD_CTX_destroy()
#endif
#endif

#endif

#ifdef KEA_HMAC

#ifndef HAVE_EVP_PKEY_NEW_RAW_PRIVATE_KEY
#ifdef HAVE_EVP_PKEY_NEW_MAC_KEY

// EVP_PKEY_new_raw_private_key(type, e, key, keylen) is
// EVP_PKEY_new_mac_key(type, e, key, (int)keylen) in old OpenSSL

inline EVP_PKEY* EVP_PKEY_new_raw_private_key(int type, ENGINE* e,
                                              const unsigned char *key,
                                              size_t keylen) {
    return (EVP_PKEY_new_mac_key(type, e, key, static_cast<int>(keylen)));
}

#else
#error have no EVP_PKEY_new_raw_private_key() nor EVP_PKEY_new_mac_key()
#endif
#endif

#endif
