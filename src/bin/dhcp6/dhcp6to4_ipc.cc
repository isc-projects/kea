// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/buffer.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/dhcp6to4_ipc.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_srv.h>
#include <exceptions/exceptions.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>

using namespace std;
using namespace isc::hooks;

namespace isc {
namespace dhcp {

uint16_t Dhcp6to4Ipc::client_port = 0;

Dhcp6to4Ipc::Dhcp6to4Ipc() : Dhcp4o6IpcBase() {}

Dhcp6to4Ipc& Dhcp6to4Ipc::instance() {
    static Dhcp6to4Ipc dhcp6to4_ipc;
    return (dhcp6to4_ipc);
}

void Dhcp6to4Ipc::open() {
    uint16_t port = CfgMgr::instance().getStagingCfg()->getDhcp4o6Port();
    if (port == 0) {
        Dhcp4o6IpcBase::close();
        return;
    }
    if (port > 65534) {
        isc_throw(OutOfRange, "DHCP4o6 port " << port);
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(port, ENDPOINT_TYPE_V6);
    if ((old_fd == -1) && (socket_fd_ != old_fd)) {
        IfaceMgr::instance().addExternalSocket(socket_fd_,
                                               Dhcp6to4Ipc::handler);
    }
}

void Dhcp6to4Ipc::handler(int /* fd */) {
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    Pkt6Ptr pkt;

    try {
        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL, DHCP6_DHCP4O6_RECEIVING);
        // Receive message from IPC.
        pkt = ipc.receive();

        if (pkt) {
            LOG_DEBUG(packet6_logger, DBG_DHCP6_BASIC, DHCP6_DHCP4O6_PACKET_RECEIVED)
                .arg(static_cast<int>(pkt->getType()))
                .arg(pkt->getRemoteAddr().toText())
                .arg(pkt->getRemotePort())
                .arg(pkt->getIface());
        }
    } catch (const std::exception& e) {
        LOG_DEBUG(packet6_logger,DBG_DHCP6_DETAIL, DHCP6_DHCP4O6_RECEIVE_FAIL)
            .arg(e.what());
    }

    if (!pkt) {
        return;
    }

    // Should we check it is a DHCPV6_DHCPV4_RESPONSE?

    // Handle relay port
    uint16_t relay_port = Dhcpv6Srv::checkRelaySourcePort(pkt);

    // The received message has been unpacked by the receive() function. This
    // method could have modified the message so it's better to pack() it
    // again because we'll be forwarding it to a client.
    isc::util::OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    // Don't use getType(): get the message type from the buffer as we
    // want to know if it is a relayed message (vs. internal message type).
    // getType() always returns the type of internal message.
    uint8_t msg_type = buf[0];
    if (client_port) {
        pkt->setRemotePort(client_port);
    } else if ((msg_type == DHCPV6_RELAY_FORW) ||
               (msg_type == DHCPV6_RELAY_REPL)) {
        pkt->setRemotePort(relay_port ? relay_port : DHCP6_SERVER_PORT);
    } else {
        pkt->setRemotePort(DHCP6_CLIENT_PORT);
    }

    // Can't call the pkt6_send callout because we don't have the query
    // From Dhcpv6Srv::processPacketBufferSend

    try {
        // Let's execute all callouts registered for buffer6_send
        if (HooksManager::calloutsPresent(Dhcpv6Srv::getHookIndexBuffer6Send())) {
            CalloutHandlePtr callout_handle = getCalloutHandle(pkt);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Use the RAII wrapper to make sure that the callout handle state is
            // reset when this object goes out of scope. All hook points must do
            // it to prevent possible circular dependency between the callout
            // handle and its arguments.
            ScopedCalloutHandleState callout_handle_state(callout_handle);

            // Enable copying options from the packet within hook library.
            ScopedEnableOptionsCopy<Pkt6> response6_options_copy(pkt);

            // Pass incoming packet as argument
            callout_handle->setArgument("response6", pkt);

            // Call callouts
            HooksManager::callCallouts(Dhcpv6Srv::getHookIndexBuffer6Send(),
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would be to parse the packet, so skip at this
            // stage means drop.
            if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
                (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
                LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS,
                          DHCP6_HOOK_BUFFER_SEND_SKIP)
                    .arg(pkt->getLabel());
                return;
            }

            callout_handle->getArgument("response6", pkt);
        }

        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_RESPONSE_DATA)
            .arg(static_cast<int>(pkt->getType())).arg(pkt->toText());

        // Forward packet to the client.
        IfaceMgr::instance().send(pkt);

        // Update statistics accordingly for sent packet.
        Dhcpv6Srv::processStatsSent(pkt);

    } catch (const std::exception& e) {
        LOG_ERROR(packet6_logger, DHCP6_DHCP4O6_SEND_FAIL).arg(e.what());
    }
}

} // namespace dhcp

} // namespace isc

