// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Do not include this header directly: use crypto_tls.h instead.

#ifndef BOTAN_WRAPPER_H
#define BOTAN_WRAPPER_H

/// @file botan_wrapper.h Botan ASIO wrapper.

#ifdef WITH_BOTAN

/// The error classes do not define virtual destructors.
/// This workaround is taken from the boost header.

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

#include <botan/asio_error.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif // WITH_BOTAN

#endif // BOTAN_WRAPPER_H
