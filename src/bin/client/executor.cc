// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <client/executor.h>
#include <client/clnt_process.h>
#include <cc/command_interpreter.h>

using namespace isc::process;

namespace isc {
namespace client {

const char* Executor::name_("kea-client");

Executor::Executor()
    : DControllerBase(name_, name_) {
}

DControllerBasePtr&
Executor::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new Executor());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase* Executor::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new ClntProcess(getAppName().c_str(), getIOService()));
}


isc::data::ConstElementPtr
Executor::parseFile(const std::string& file_name) {
    return (config::createAnswer(3, "sorry, not implemented"));
}

};
};
