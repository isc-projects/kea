// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOPTION_H
#define LOPTION_H 1

#include <dhcp/option.h>

namespace isc {
namespace kea {

// Lua option class
class l_option  {
    l_option();

public:
    isc::dhcp::OptionPtr object;
};

#define LUA_KEAOPTION "kea-option"

#define LUA_OPTIONLIBNAME "option"

LUAMOD_API int luaopen_option(lua_State* L);

} // namespace kea
} // namespace isc

#endif // LOPTION_H
