// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_CONTROLLER_H
#define D2_CONTROLLER_H

#include <d2/d_controller.h>

namespace isc {
namespace d2 {

/// @brief Process Controller for D2 Process
/// This class is the DHCP-DDNS specific derivation of DControllerBase. It
/// creates and manages an instance of the DHCP-DDNS application process,
/// D2Process.
/// @todo Currently, this class provides only the minimum required specialized
/// behavior to run the DHCP-DDNS service. It may very well expand as the
/// service implementation evolves.  Some thought was given to making
/// DControllerBase a templated class but the labor savings versus the
/// potential number of virtual methods which may be overridden didn't seem
/// worth the clutter at this point.
class D2Controller : public DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton
    /// and sets the base class instance member upon first invocation.
    ///
    /// @return returns the pointer reference to the singleton instance.
    static DControllerBasePtr& instance();

    /// @brief Destructor.
    virtual ~D2Controller();

    /// @brief Defines the application name, this is passed into base class
    /// and appears in log statements.
    static const char* d2_app_name_;

    /// @brief Defines the executable name. This is passed into the base class
    /// by convention this should match the executable name.
    static const char* d2_bin_name_;

private:
    /// @brief Creates an instance of the DHCP-DDNS specific application
    /// process.  This method is invoked during the process initialization
    /// step of the controller launch.
    ///
    /// @return returns a DProcessBase* to the application process created.
    /// Note the caller is responsible for destructing the process. This
    /// is handled by the base class, which wraps this pointer with a smart
    /// pointer.
    virtual DProcessBase* createProcess();

    /// @brief Constructor is declared private to maintain the integrity of
    /// the singleton instance.
    D2Controller();
};

}; // namespace isc::d2
}; // namespace isc

#endif
