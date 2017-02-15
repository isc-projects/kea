// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <openssl/opensslv.h>

#if defined(LIBRESSL_VERSION_NUMBER) || (OPENSSL_VERSION_NUMBER < 0x10100000L)

// This file is included by hash and hmac codes so KEA_H* macros
// avoid to define unused inlines.

#ifdef KEA_HASH

// EVP_MD_CTX_new() is EVP_MD_CTX_create() in OpenSSL < 1.1

inline EVP_MD_CTX* EVP_MD_CTX_new() {
    return (EVP_MD_CTX_create());
}

// EVP_MD_CTX_free(ctx) is EVP_MD_CTX_destroy(ctx) in OpenSSL < 1.1 

inline void EVP_MD_CTX_free(EVP_MD_CTX* ctx) {
    EVP_MD_CTX_destroy(ctx);
}

#endif

#ifdef KEA_HMAC

// HMAC_CTX_new() implementation for OpenSSL < 1.1

inline HMAC_CTX* HMAC_CTX_new() {
    HMAC_CTX* ctx = static_cast<HMAC_CTX*>(OPENSSL_malloc(sizeof(HMAC_CTX)));
    if (ctx != 0) {
        HMAC_CTX_init(ctx);
    }
    return (ctx);
}

// HMAC_CTX_free() implementation for OpenSSL < 1.1

inline void HMAC_CTX_free(HMAC_CTX* ctx) {
    if (ctx != 0) {
        HMAC_CTX_cleanup(ctx);
        OPENSSL_free(ctx);
    }
}

#endif

#endif
