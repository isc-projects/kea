// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_CMDS_H
#define LEASE_CMDS_H

#include <boost/shared_ptr.hpp>

namespace isc {
namespace lease_cmds {

/// @brief Forward declaration of implementation class.
class LeaseCmdsImpl;

/// @brief A wrapper class that provides convenient initialization to the library.
///
/// This is a wrapper class that simply registers extra commands when
/// instantiated and deregisters them when the instance is destroyed.
///
/// For an actual implementation, see @ref LeaseCmdsImpl class in lease_cmds.cc file.
class LeaseCmds {
public:

    /// @brief Initializes additional host reservation commands.
    ///
    /// First, it ensures that either alternate host data source or CfgHosts
    /// (configuration storage) are available. Then it checks that CommandMgr
    /// is available. Then finally, it registers the following commands:
    /// - lease4-add
    /// - lease6-add
    /// - lease4-get
    /// - lease6-get
    /// - lease4-del
    /// - lease6-del
    /// - lease4-update
    /// - lease6-update
    /// - lease4-del-all
    /// - lease6-del-all
    ///
    /// @throw Unexpected If any of the above fails.
    LeaseCmds();

    /// @brief Destructor
    ///
    /// - lease4-add
    /// - lease6-add
    /// - lease4-get
    /// - lease6-get
    /// - lease4-del
    /// - lease6-del
    /// - lease4-update
    /// - lease6-update
    /// - lease4-del-all
    /// - lease6-del-all
    /// Unregisters commands:
    ~LeaseCmds();
private:

    /// Pointer to the actual implementation
    boost::shared_ptr<LeaseCmdsImpl> impl_;
};

};
};

#endif
