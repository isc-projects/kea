// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LPKT4_H
#define LPKT4_H 1

#include <dhcp/pkt4.h>

namespace isc {
namespace kea {

// Lua DHCPv4 packet class
class l_pkt4  {
    l_pkt4();

public:
    isc::dhcp::Pkt4Ptr object;
};

#define LUA_KEAPKT4 "kea-pkt4"

#define LUA_PKT4LIBNAME "pkt4"

LUAMOD_API int luaopen_pkt4(lua_State* L);

} // namespace kea
} // namespace isc

#endif // LPKT4_H
