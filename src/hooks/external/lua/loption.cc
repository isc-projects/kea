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

// Method table
const luaL_Reg option_method[] = {
    { "__gc", option__gc },
    { "__tostring", option__tostring },
    { NULL, NULL }
};

// factory(universe, type, data)
int factory(lua_State* L) {
    // Requires 3 arguments
    if (lua_gettop(L) != 3) {
        return (luaL_error(L, "option.factory takes 3 arguments"));
    }
    if (!lua_isinteger(L, 1)) {
        return (luaL_error(L, "universe must be an integer"));
    }
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "type must be an integer"));
    }
    if (!lua_isstring(L, 3)) {
        return (luaL_error(L, "data must be a string"));
    }
    uint8_t u = static_cast<uint8_t>(lua_tointeger(L, 1));
    uint16_t t = static_cast<uint16_t>(lua_tointeger(L, 2));
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
    const char* d = lua_tolstring(L, 3, &len);
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

// toBinary(bool include_header = false) method
int toBinary(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    vector<uint8_t> bin = self->object->toBinary(true);
    lua_pushlstring(L, reinterpret_cast<char*>(&bin[0]), bin.size());
    return (1);
}

// getType() method
int getType(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->getType()));
    return (1);
}

// len() method
int len(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->len()));
    return (1);
}

// getHeaderLen() method
int getHeaderLen(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->getHeaderLen()));
    return (1);
}

// getData() method
int getData(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    const OptionBuffer& data = self->object->getData();
    lua_pushlstring(L, reinterpret_cast<const char*>(&data[0]), data.size());
    return (1);
}

// addOption(OptionPtr opt) method
int addOption(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "option.addOption takes 2 arguments"));
    }
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    l_option* const sub =
        static_cast<l_option*>(luaL_checkudata(L, 2, LUA_KEAOPTION));
    self->object->addOption(sub->object);
    return (0);
}

// getOption(uint16_t type) method
int getOption(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "option.getOption takes 2 arguments"));
    }
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "type must be an integer"));
    }
    uint16_t t = static_cast<uint16_t>(lua_tointeger(L, 2));
    OptionPtr sub = self->object->getOption(t);
    if (sub) {
        void* ret =
            static_cast<l_option*>(lua_newuserdata(L, sizeof(l_option)));
        memset(ret, 0, sizeof(l_option));
        (static_cast<l_option*>(ret))->object = sub;
    } else {
        lua_pushnil(L);
    }
    return (1);
}

// TODO: getOptions() method

// delOption(uint16_t type) method
int delOption(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "option.delOption takes 2 arguments"));
    }
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "type must be an integer"));
    }
    uint16_t t = static_cast<uint16_t>(lua_tointeger(L, 2));
    bool ret = self->object->delOption(t);
    lua_pushboolean(L, ret ? 1 : 0);
    return (1);
}

// setData(<byte>) method
int setData(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "option.setData takes 2 arguments"));
    }
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    if (!lua_isstring(L, 2)) {
        return (luaL_error(L, "data must be a string"));
    }
    size_t len = 0;
    const char* d = lua_tolstring(L, 2, &len);
    OptionBuffer data;
    data.resize(len);
    if (len) {
        memmove(&data[0], d, len);
    }
    self->object->setData(data.begin(), data.end());
    return (0);
}

// setEncapsulatedSpace(const string& encapsulated_space) method
int setEncapsulatedSpace(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L,
                    "option.setEncapsulatedSpace takes 2 arguments"));
    }
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    if (!lua_isstring(L, 2)) {
        return (luaL_error(L, "encapsulated_state must be a string"));
    }
    string state(lua_tostring(L, 2));
    self->object->setEncapsulatedSpace(state);
    return (0);
}

// getEncapsulatedSpace() method
int getEncapsulatedSpace(lua_State* L) {
    l_option* const self =
        static_cast<l_option*>(luaL_checkudata(L, 1, LUA_KEAOPTION));
    lua_pushstring(L, self->object->getEncapsulatedSpace().c_str());
    return (1);
}

// Function table
const luaL_Reg option_function[] = {
    { "factory", factory },
    { "getUniverse", getUniverse },
    { "toBinary", toBinary },
    { "getType", getType },
    { "len", len },
    { "getHeaderLen", getHeaderLen },
    { "getData", getData },
    { "addOption", addOption },
    { "getOption", getOption },
    { "delOption", delOption },
    { "setData", setData },
    { "setEncapsulatedSpace", setEncapsulatedSpace },
    { "getEncapsulatedSpace", getEncapsulatedSpace },
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
