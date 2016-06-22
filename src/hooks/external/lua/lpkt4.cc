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

// Method table
const luaL_Reg pkt4_method[] = {
    { "__gc", pkt4__gc },
    { "__tostring", pkt4__tostring },
    { NULL, NULL }
};

// addOption(const OptionPtr opt) method
int addOption(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    l_option* const sub =
        static_cast<l_option*>(luaL_checkudata(L, 2, LUA_KEAOPTION));
    self->object->addOption(sub->object);
    return (0);
}

// delOption(uint16_t type) method
int delOption(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.delOption takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "type must be an integer"));
    }
    uint16_t t = static_cast<uint16_t>(lua_tointeger(L, 2));
    bool ret = self->object->delOption(t);
    lua_pushboolean(L, ret ? 1 : 0);
    return (1);
}

// len() method
int len(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->len()));
    return (1);
}

// getType() method
int getType(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->getType()));
    return (1);
}

// setType(uint8_t type) method
int setType(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.setType takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "type must be an integer"));
    }
    uint16_t t = static_cast<uint16_t>(lua_tointeger(L, 2));
    self->object->setType(t);
    return (1);
}

// setTransid(uint32_t transid) method
int setTransid(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.setTransid takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "transid must be an integer"));
    }
    uint32_t t = static_cast<uint32_t>(lua_tointeger(L, 2));
    self->object->setTransid(t);
    return (1);
}

// getTransid() method
int getTransid(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->getTransid()));
    return (1);
}

// inClass(const isc::dhcp::ClientClass& client_class) method
int inClass(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.inClass takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isstring(L, 2)) {
        return (luaL_error(L, "client_class must be a string"));
    }
    const ClientClass& cclass(lua_tostring(L, 2));
    bool ret = self->object->inClass(cclass);
    lua_pushboolean(L, ret ? 1 : 0);
    return (1);
}

// addClass(const isc::dhcp::ClientClass& client_class) method
int addClass(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.addClass takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isstring(L, 2)) {
        return (luaL_error(L, "client_class must be a string"));
    }
    const ClientClass& cclass(lua_tostring(L, 2));
    self->object->addClass(cclass);
    return (0);
}

// TODO: getClasses() method

// getOption(uint16_t type) method
int getOption(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.getOption takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
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

// TODO: getTimestamp() method

// TODO: set/getLocal/RemoteAddr/Port methods

// setIndex(uint32_t ifindex) method
int setIndex(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.setIndex takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isinteger(L, 2)) {
        return (luaL_error(L, "ifindex must be an integer"));
    }
    uint32_t t = static_cast<uint32_t>(lua_tointeger(L, 2));
    self->object->setIndex(t);
    return (1);
}

// getIndex() method
int getIndex(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushinteger(L, static_cast<lua_Integer>(self->object->getIndex()));
    return (1);
}

// getIface() method
int getIface(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    lua_pushstring(L, self->object->getIface().c_str());
    return (1);
}

// setIface(const std::string& iface) method
int setIface(lua_State* L) {
    // Requires 2 arguments
    if (lua_gettop(L) != 2) {
        return (luaL_error(L, "pkt4.setIface takes 2 arguments"));
    }
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    if (!lua_isstring(L, 2)) {
        return (luaL_error(L, "iface must be a string"));
    }
    const ClientClass& cclass(lua_tostring(L, 2));
    self->object->setIface(cclass);
    return (0);
}

// TODO many methods

// getHWAddr() method
int getHWAddr(lua_State* L) {
    l_pkt4* const self =
        static_cast<l_pkt4*>(luaL_checkudata(L, 1, LUA_KEAPKT4));
    HWAddrPtr hwaddr = self->object->getHWAddr();
    vector<uint8_t> bin;
    if (hwaddr) {
        bin = hwaddr->hwaddr_;
    }
    lua_pushlstring(L, reinterpret_cast<char*>(&bin[0]), bin.size());
    return (1);
}

// Function table
const luaL_Reg pkt4_function[] = {
    { "addOption", addOption },
    { "delOption", delOption },
    { "len", len },
    { "getType", getType },
    { "setType", setType },
    { "setTransid", setTransid },
    { "getTransid", getTransid },
    { "inClass", inClass },
    { "addClass", addClass },
    { "getOption", getOption },
    { "setIndex", setIndex },
    { "getIndex", getIndex },
    { "getIface", getIface },
    { "setIface", setIface },
    { "getHWAddr", getHWAddr },
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
