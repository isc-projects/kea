// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLNT_EXECUTOR_H
#define CLNT_EXECUTOR_H


// One of the client requirements is to keep its footprint small. We can't use
// the DControllerBase until the mess with its dependencies is sorted out.
// See all the crap in libkea_process_la_LIBADD in src/lib/process/Makefile.am
// and make your own opinion.
#include <process/d_controller.h>

namespace isc {
namespace client {

/// @brief Process Controller for the client process
/// 
/// This class is the client specific derivation of DControllerBase. It
/// creates and manages an instance of the client application process,
/// D2Process.
///
/// @todo Currently, this class provides only the minimum required specialized
/// behavior to run the client service. It may very well expand as the
/// service implementation evolves.  Some thought was given to making
/// DControllerBase a templated class but the labor savings versus the
/// potential number of virtual methods which may be overridden didn't seem
/// worth the clutter at this point.
class Executor : public process::DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton
    /// and sets the base class instance member upon first invocation.
    ///
    /// @return returns the pointer reference to the singleton instance.
    static process::DControllerBasePtr& instance();

    /// @brief Destructor.
    virtual ~Executor() {}

    static const char* name_;

private:
    /// @brief Creates an instance of the DHCP-DDNS specific application
    /// process.  This method is invoked during the process initialization
    /// step of the controller launch.
    ///
    /// @return returns a DProcessBase* to the application process created.
    /// Note the caller is responsible for destructing the process. This
    /// is handled by the base class, which wraps this pointer with a smart
    /// pointer.
    virtual process::DProcessBase* createProcess();

    ///@brief Parse a given file into Elements
    ///
    /// Uses bison parsing to parse a JSON configuration file into an
    /// a element map.
    ///
    /// @param file_name pathname of the file to parse
    ///
    /// @return pointer to the map of elements created
    /// @throw BadValue if the file is empty
    virtual isc::data::ConstElementPtr parseFile(const std::string& file_name);

    /// @brief Constructor is declared private to maintain the integrity of
    /// the singleton instance.
    Executor();
};

}; // namespace isc::d2
}; // namespace isc

#endif
