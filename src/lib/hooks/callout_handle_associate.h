// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CALLOUT_HANDLE_ASSOCIATE_H
#define CALLOUT_HANDLE_ASSOCIATE_H

#include <hooks/callout_handle.h>

namespace isc {
namespace hooks {

/// @brief Base class for classes which need to be associated with
/// a @c CalloutHandle object.
///
/// The @c CalloutHandle is an object used to pass various parameters
/// between Kea and the callouts. The Kea servers usually invoke
/// multiple different callouts for a single packet such as DHCP
/// packet, control command etc. Therefore, it is required to
/// associate this packet with an instance of the callout handle, so
/// this instance can be used for all callouts invoked for this
/// packet.
///
/// Previously this association was made by the @c CalloutHandleStore
/// class. However, with the introduction of parallel processing
/// of packets (DHCP packets parking) it became awkward to use.
/// Attempts to extend this class to hold a map of associations
/// failed because of no easy way to garbage collect unused handles.
///
/// The easiest way to deal with this is to provide ownership of the
/// @c CalloutHandle to the object with which it is associated. The
/// class of this object needs to derive from this class. When the
/// object (e.g. DHCP packet) goes out of scope and is destroyed
/// this instance is destroyed as well.
class CalloutHandleAssociate {
public:

    /// @brief Constructor.
    CalloutHandleAssociate();

    /// @brief Returns callout handle.
    ///
    /// The callout handle is created if it doesn't exist. Subsequent
    /// calls to this method always return the same handle.
    ///
    /// @return Pointer to the callout handle.
    CalloutHandlePtr getCalloutHandle();

    /// @brief Reset callout handle.
    void resetCalloutHandle();

protected:

    /// @brief Callout handle stored.
    CalloutHandlePtr callout_handle_;
};

} // end of isc::hooks
} // end of isc

#endif
