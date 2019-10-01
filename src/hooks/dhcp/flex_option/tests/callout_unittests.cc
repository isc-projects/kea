// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible option callouts.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/host.h>
#include <dhcp/option.h>
#include <dhcp/option_string.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <flex_option.h>
#include <flex_option_log.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::flex_option;

extern "C" {
extern int pkt4_send(CalloutHandle& handle);
extern int pkt6_send(CalloutHandle& handle);
}

namespace {

} // end of anonymous namespace
