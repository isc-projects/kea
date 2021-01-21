// Copyright (C) 2013-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CALLOUT_HANDLE_STORE_H
#define CALLOUT_HANDLE_STORE_H

#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>
#include <map>
#include <set>

namespace isc {
namespace dhcp {

/// @brief CalloutHandle Store
///
/// When using the Hooks Framework, there is a need to associate an
/// isc::hooks::CalloutHandle object with each request passing through the
/// server.  For the DHCP servers, the association was provided by this function.
///
/// After introduction of "packets parking" feature this function was extended
/// to keep association of packets with the callout handles in a map.
/// However, it was later found that "garbage collection" of the unused
/// handles is very hard. Trying to garbage collect handles at each invocation
/// was highly inefficient and caused server's performance degradation.
///
/// The new approach is using on @c isc::hooks::CalloutHandleAssociate to
/// associate objects with callout handles. This has a major benefit that
/// callout handle instances are removed together with the packets associated
/// with them.
///
/// This function uses this new approach and is kept for the compatibility with
/// existing code.
///
/// @tparam T Pkt4Ptr or Pkt6Ptr object.
/// @param pktptr Pointer to the packet being processed.  This is typically a
///        Pkt4Ptr or Pkt6Ptr object.
///
/// @return Shared pointer to a CalloutHandle. This is the previously-stored
///         CalloutHandle if pktptr points to a packet that has been seen
///         before or a new CalloutHandle if it points to a new one. An empty
///         pointer is returned if pktptr is itself an empty pointer.
template <typename T>
isc::hooks::CalloutHandlePtr getCalloutHandle(const T& pktptr) {

    if (pktptr) {
        return (pktptr->getCalloutHandle());

    }

    return (isc::hooks::CalloutHandlePtr());
}

} // namespace dhcp
} // namespace isc

#endif // CALLOUT_HANDLE_STORE_H
