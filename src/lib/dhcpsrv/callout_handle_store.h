// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
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
/// server.  For the DHCP servers, the association is provided by this function.
///
/// The DHCP servers process requests sequentially, but sometimes packets can
/// be "parked" waiting for the completion of asynchronous operations scheduled
/// by hook libraries. While the packets are parked, other packets can be
/// processed. This poses a requirement for the DHCP server to keep
/// multiple associations between the packets and their handles. At points where
/// the CalloutHandle is required, the pointer to the current request (packet)
/// is passed to this function. If the request is a new one, a pointer to the
/// request stored, a new CalloutHandle is allocated (and stored) and a pointer
/// to the latter object returned to the caller. If the request matches one of
/// the stored requests, the CalloutHandle for this request is returned.
///
/// In order to avoid the endless growth of the collection of stored associations
/// this function performs housekeeping of the collection every time it is
/// called with non-null packet pointer. All entries for which the packet
/// pointer's reference count is less than 2 are removed. These are the packet
/// objects which only this function holds reference counts to. Thus, they can
/// be removed because they are not required by the server anymore. They have
/// been either dropped or processed.
///
///
/// A special case is a null pointer being passed to this function. This has
/// the effect of clearing the pointers to stored handles and packets.
///
/// @tparam T Pkt4Ptr or Pkt6Ptr object.
/// @param pktptr Pointer to the packet being processed.  This is typically a
///        Pkt4Ptr or Pkt6Ptr object.  An empty pointer is passed to clear
///        the stored pointers.
///
/// @return Shared pointer to a CalloutHandle.  This is the previously-stored
///         CalloutHandle if pktptr points to a packet that has been seen
///         before or a new CalloutHandle if it points to a new one.  An empty
///         pointer is returned if pktptr is itself an empty pointer.
template <typename T>
isc::hooks::CalloutHandlePtr getCalloutHandle(const T& pktptr) {

    isc::hooks::CalloutHandlePtr stored_handle;
    static std::map<T, isc::hooks::CalloutHandlePtr> store;

    if (pktptr) {

        std::set<T> to_remove;

        // Identify unused handles by checking whether the reference count is
        // less then 2. This indicates that only our local store keeps the
        // pointer to the packet.
        for (auto handle_pair_it = store.begin(); handle_pair_it != store.end();
             ++handle_pair_it) {

            if (!handle_pair_it->first || handle_pair_it->first.use_count() < 2) {
                to_remove.insert(handle_pair_it->first);
            }
        }

        // Actually remove the unused handles.
        for (const auto& pktptr : to_remove) {
            store.erase(pktptr);
        }

        // Pointer given, have we seen it before?
        auto stored_handle_it = store.find(pktptr);
        if (stored_handle_it == store.end()) {

            // Not seen before, so store the pointer passed to us and get a new
            // CalloutHandle.
            stored_handle = isc::hooks::HooksManager::createCalloutHandle();
            store[pktptr] = stored_handle;

        } else {
            // Return existing pointer.
            stored_handle = stored_handle_it->second;
        }
        
    } else {
        // Empty pointer passed, clear stored data
        store.clear();
    }

    return (stored_handle);
}

} // namespace shcp
} // namespace isc

#endif // CALLOUT_HANDLE_STORE_H
