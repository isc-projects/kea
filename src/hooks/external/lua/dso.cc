// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <lua.hpp>

#include <hooks/hooks.h>

#include <hooks/external/lua/loption.h>
#include <hooks/external/lua/lpkt4.h>

#include <iostream>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::kea;

namespace {
    // Lua state
    lua_State* L;
};

extern "C" {

// Framework functions

// version
int version() {
    return (KEA_HOOKS_VERSION);
}

// load
int load(LibraryHandle& handle) {
    // Get a new state
    L = luaL_newstate();
    if (!L) {
        cerr << "can't get new state\n";
        return (1);
    }

    // Check against version mismatch
    luaL_checkversion(L);

    // Add option and pkt4 as to be preloaded modules
    static_cast<void>(luaL_getsubtable(L, LUA_REGISTRYINDEX, "_PRELOAD"));
    lua_pushcfunction(L, luaopen_option);
    lua_setfield(L, -2, "option");
    lua_pushcfunction(L, luaopen_pkt4);
    lua_setfield(L, -2, "pkt4");
    lua_pop(L, 1);
    
    // Load librairies
    luaL_openlibs(L);

    // Load option
    luaL_requiref(L, LUA_OPTIONLIBNAME, luaopen_option, 1);
    lua_pop(L, 1);

    // Load pkt4
    luaL_requiref(L, LUA_PKT4LIBNAME, luaopen_pkt4, 1);
    lua_pop(L, 1);

    // Get the script module name (default "hook.lua" file)
    ConstElementPtr script = handle.getParameter("script");
    string scptname = "hook.lua";
    if (script && script->getType() == Element::string) {
        scptname = script->stringValue();
    } else {
        cout << "no \"script\" parameter: using \"hook.hua\"\n";
    }
    int ret = luaL_loadfile(L, scptname.c_str());
    switch (ret) {
    case LUA_OK:
        break;
    case LUA_ERRSYNTAX:
        cerr << "syntax error in \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (2);
    case LUA_ERRFILE:
        cerr << "bad file \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (2);
    case LUA_ERRMEM:
    case LUA_ERRGCMM:
        cerr << "memory problem loading \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (2);
    default:
        cerr << "unspecified error (" << ret
             << ") loading \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (2);
    }

    // Run the script
    ret = lua_pcall(L, 0, 0, 0);
    switch (ret) {
    case LUA_OK:
        break;
    case LUA_ERRRUN:
        cerr << "runtime error from \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (3);
    case LUA_ERRMEM:
    case LUA_ERRGCMM:
        cerr << "memory problem running \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (3);
    default:
        cerr << "unspecified error (" << ret
             << ") running \"" << scptname << "\": "
             << lua_tostring(L, -1) << "\n";
        return (3);
    }

    // Get pkt4_receive handler
    ret = lua_getglobal(L, "pkt4_receive");
    switch (ret) {
    case LUA_TNIL:
        cerr << "can't find \"pkt4_receive\"\n";
        return (4);
    case LUA_TFUNCTION:
        break;
    default:
        cerr << "\"pkt4_receive\" is not a function, it is a "
             << lua_typename(L, ret) << "\n";
        return (4);
    }
    lua_pop(L, 1);

    return (0);
}

// unload
int unload() {
    // Release the state
    lua_close(L);
    L = NULL;

    return (0);
}

// pkt4_receive hook
int pkt4_receive(CalloutHandle& handle) {
    if (lua_getglobal(L, "pkt4_receive") != LUA_TFUNCTION) {
        return (0);
    }
    cout << "pkt4_receive: enter\n";

    Pkt4Ptr query4;
    handle.getArgument("query4", query4);
    if (!query4) {
        cerr << "pkt4_receive: null query4\n";
        return (0);
    }

    void *query = lua_newuserdata(L, sizeof(l_pkt4));
    if (!query) {
        cerr << "lua_newuserdata failed\n";
        return (0);
    }
    memset(query, 0, sizeof(l_pkt4));
    (static_cast<l_pkt4*>(query))->object = query4;
    if (luaL_getmetatable(L, LUA_KEAPKT4) == LUA_TNIL) {
        cerr << "no metatable for " << LUA_KEAPKT4 << "\n";
    }
    lua_pop(L, 1);
    luaL_setmetatable(L, LUA_KEAPKT4);
    
    int ret = lua_pcall(L, 1, 1, 0);
    switch (ret) {
    case LUA_OK:
        break;
    case LUA_ERRRUN:
        cerr << "runtime error in pkt4_receive: "
             << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
        return (0);
    case LUA_ERRMEM:
    case LUA_ERRGCMM:
        cerr << "memory problem in pkt4_receive: "
             << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
        return (0);
    default:
        cerr << "unspecified error (" << ret
             << ") in pkt4_receive: "
             << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
        return (0);
    }
    if (lua_type(L, -1) != LUA_TNUMBER) {
        cerr << "pkt4_receive didn't return a number\n";
        lua_pop(L, 1);
        return (0);
    }
    ret = static_cast<int>(lua_tonumber(L, -1));
    lua_pop(L, 1);

    cout << "pkt4_receive: return " << ret << "\n";
    return (ret);
}

}
