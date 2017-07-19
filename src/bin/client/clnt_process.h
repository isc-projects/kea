// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLNT_PROCESS_H
#define CLNT_PROCESS_H

#include <process/d_process.h>

namespace isc {
namespace client {


class ClntProcess : public process::DProcessBase {

 public:
    ClntProcess(const char* nane, const asiolink::IOServicePtr& io_service);

    virtual void init();

    virtual void run();

    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set,
              bool check_only = false);

    /// @brief Initiates the process's shutdown process. 
    /// 
    /// This is last step in the shutdown event callback chain, that is 
    /// intended to notify the process it is to begin its shutdown process.
    ///
    /// @param args an Element set of shutdown arguments (if any) that are
    /// supported by the process derivation. 
    /// 
    /// @return an Element that contains the results of argument processing,
    /// consisting of an integer status value (0 means successful, 
    /// non-zero means failure), and a string explanation of the outcome. 
    ///  
    /// @throw DProcessBaseError if an operational error is encountered.
    virtual isc::data::ConstElementPtr 
    shutdown(isc::data::ConstElementPtr args);

    virtual ~ClntProcess();
};

};
};

#endif
