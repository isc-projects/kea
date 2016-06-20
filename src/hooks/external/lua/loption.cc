// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <lua.hpp>

#include <hooks/external/lua/loption.h>

#include <iostream>

using namespace std;
using namespace isc::dhcp;
using namespace isc::kea;

// Constructor
l_option::l_option() {}

namespace { // anonymous namespace

// factory(universe, type, data)
int factory(lua_State* L) {
    // Require 3 arguments
    if (lua_gettop(L) - 1 != 3) {
        return (luaL_error(L, "option.factory takes 3 arguments"));
    }
    if (lua_type(L, -3) != LUA_TNUMBER) {
        return (luaL_error(L, "universe must be a number"));
    }
    if (lua_type(L, -2) != LUA_TNUMBER) {
        return (luaL_error(L, "type must be a number"));
    }
    if (lua_type(L, -1) != LUA_TSTRING) {
        return (luaL_error(L, "data must be a string"));
    }
    unsigned char u = static_cast<unsigned char>(lua_tonumber(L, -3));
    unsigned short t = static_cast<unsigned short>(lua_tonumber(L, -2));
    Option::Universe universe;
    switch (u) {
    case 4:
        universe = Option::V4;
        if (t > 255) {
            return (luaL_error(L, "out of range type for DHCPv4: %d",
                               static_cast<int>(t)));
        }
        break;
    case 6:
        universe = Option::V6;
        break;
    default:
        return (luaL_error(L, "universe must be 4 or 6 (not %d)",
                           static_cast<int>(u)));
    }

    size_t len = 0;
    const char* d = lua_tolstring(L, -1, &len);
    OptionBuffer data;
    data.resize(len);
    if (len) {
        memmove(&data[0], d, len);
    }

    l_option* const self =
        static_cast<l_option*>(lua_newuserdata(L, sizeof(l_option)));
    memset(self, 0, sizeof(l_option));
    self->object.reset(new Option(universe, t, data));
    luaL_setmetatable(L, LUA_KEAOPTION);
    return (1);
}

// __gc
int option__gc(lua_State* L) {
    // This is a critical code to avoid memory leaks
    cout << "option__gc called\n";
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    self->object.reset();
    return (0);
}

// __tostring
int option__tostring(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    lua_pushstring(L, self->object->toText(0).c_str());
    return (1);
}

// getUniverse() method
int getUniverse(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    switch (self->object->getUniverse()) {
    case Option::V4:
        lua_pushinteger(L, 4);
        return (1);
    case Option::V6:
        lua_pushinteger(L, 6);
        return (1);
    default:
        return (luaL_error(L, "getUniverse"));
    }
}

// Method table
const luaL_Reg option_method[] = {
    { "__gc", option__gc },
    { "__tostring", option__tostring },
    { "getUniverse", getUniverse },
    { NULL, NULL }
};

// Function table
const luaL_Reg option_function[] = {
    { NULL, NULL }
};

// Create the module metadata
void createmeta(lua_State* L) {
    // create metatable
    luaL_newmetatable(L, LUA_KEAOPTION);
    // push metatable
    lua_pushvalue(L, -1);
    // metatable.__index = metatable
    lua_setfield(L, -2, "__index");
    // add methods
    luaL_setfuncs(L, option_method, 0);
    // pop new metatable
    lua_pop(L, 1);
}

} // end of anonymous namespace

namespace isc {
namespace kea {

// Initialize the module
int luaopen_option(lua_State* L) {
    // new module
    luaL_newlib(L, option_function);
    createmeta(L);

    // constants

    return (1);
}

} // namespace lua
} // namespace isc
