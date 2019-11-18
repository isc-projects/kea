// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <client/clnt_process.h>
#include <client/clnt_cfg_mgr.h>
#include <cc/command_interpreter.h>
#include <process/d_cfg_mgr.h>
#include <iostream>

using namespace isc::client;
using namespace isc::config;

ClntProcess::ClntProcess(const char* name,
                         const asiolink::IOServicePtr& io_service)
  :DProcessBase(name, io_service, process::DCfgMgrBasePtr(new ClntCfgMgr())) {

}

void ClntProcess::init() {

}

void ClntProcess::run() {
    std::cout << "Running...." << std::endl;
    while (true) {
        std::cout << ".";
        sleep(1);
    }
}

isc::data::ConstElementPtr
ClntProcess::configure(isc::data::ConstElementPtr config_set,
                       bool check_only) {
    return (createAnswer(3, "not implemented"));
}

isc::data::ConstElementPtr 
ClntProcess::shutdown(isc::data::ConstElementPtr args) {
    return (createAnswer(3, "not implemented"));
}

ClntProcess::~ClntProcess() {
}

