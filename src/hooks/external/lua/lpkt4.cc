// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <lua.hpp>

#include <hooks/external/lua/loption.h>
#include <hooks/external/lua/lpkt4.h>

#include <iostream>

using namespace std;
using namespace isc::dhcp;
using namespace isc::kea;

// Constructor
l_pkt4::l_pkt4() {}

namespace { // anonymous namespace

// __gc
int pkt4__gc(lua_State* L) {
    // This is a critical code to avoid memory leaks
    cout << "pkt4__gc called\n";
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    self->object.reset();
    return (0);
}

// __tostring
int pkt4__tostring(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushstring(L, self->object->toText().c_str());
    return (1);
}

// addOption(const OptionPtr opt) method
int addOption(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    l_option* const sub =
        static_cast<l_option*>(luaL_checkudata(L, 2, LUA_KEAOPTION));
    self->object->addOption(sub->object);
    return (0);
}

// Method table
const luaL_Reg pkt4_method[] = {
    { "__gc", pkt4__gc },
    { "__tostring", pkt4__tostring },
    { "addOption", addOption },
    { NULL, NULL }
};

// Function table
const luaL_Reg pkt4_function[] = {
    { NULL, NULL }
};

// Create the module metadata
void createmeta(lua_State* L) {
    // create metatable
    luaL_newmetatable(L, LUA_KEAPKT4);
    // push metatable
    lua_pushvalue(L, -1);
    // metatable.__index = metatable
    lua_setfield(L, -2, "__index");
    // add methods
    luaL_setfuncs(L, pkt4_method, 0);
    // pop new metatable
    lua_pop(L, 1);
}

} // end of anonymous namespace

namespace isc {
namespace kea {

// Initialize the module
int luaopen_pkt4(lua_State* L) {
    // new module
    luaL_newlib(L, pkt4_function);
    createmeta(L);

    // constants

    return (1);
}

} // namespace lua
} // namespace isc
