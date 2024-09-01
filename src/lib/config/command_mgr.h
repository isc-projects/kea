// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_MGR_H
#define COMMAND_MGR_H

#include <config/hooked_command_mgr.h>
#include <boost/noncopyable.hpp>

namespace isc {
namespace config {

/// @brief Commands Manager implementation for the Kea servers.
///
/// This class extends @ref BaseCommandMgr with the ability to receive and
/// respond to commands over unix domain sockets.
class CommandMgr : public HookedCommandMgr, public boost::noncopyable {
public:

    /// @brief CommandMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of the manager.
    static CommandMgr& instance();

private:

    /// @brief Private constructor.
    CommandMgr();
};

} // end of isc::config namespace
} // end of isc namespace
#endif
