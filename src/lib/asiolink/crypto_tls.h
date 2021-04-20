// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CRYPTO_TLS_H
#define CRYPTO_TLS_H

/// @file crypto_tls.h TLS API.

// Verify that config.h was included.
#ifndef CONFIG_H_WAS_INCLUDED
#error config.h must be included before crypto_tls.h
#endif

// Include different versions.
#include <asiolink/botan_boost_tls.h>
#include <asiolink/botan_tls.h>
#include <asiolink/openssl_tls.h>

// Verify that one version matched.
#ifndef COMMON_TLS_H
#error no TLS backend was found
#endif

#endif // CRYPTO_TLS_H
