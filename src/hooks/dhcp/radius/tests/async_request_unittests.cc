// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#define RequestTest RequestAsyncTest
#define RequestAuth RadiusAsyncAuth
#define RequestAcct RadiusAsyncAcct
#define RequestAuthPtr RadiusAsyncAuthPtr
#define RequestAcctPtr RadiusAsyncAcctPtr

#include "request_unittests.h"
