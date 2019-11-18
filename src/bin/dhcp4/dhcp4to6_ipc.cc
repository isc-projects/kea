// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/buffer.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt4o6.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4to6_ipc.h>
#include <dhcp4/dhcp4_log.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc::hooks;

namespace isc {
namespace dhcp {

Dhcp4to6Ipc::Dhcp4to6Ipc() : Dhcp4o6IpcBase() {}

Dhcp4to6Ipc& Dhcp4to6Ipc::instance() {
    static Dhcp4to6Ipc dhcp4to6_ipc;
    return (dhcp4to6_ipc);
}

void Dhcp4to6Ipc::open() {
    uint16_t port = CfgMgr::instance().getStagingCfg()->getDhcp4o6Port();
    if (port == 0) {
        Dhcp4o6IpcBase::close();
        return;
    }
    if (port > 65534) {
        isc_throw(OutOfRange, "DHCP4o6 port " << port);
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(port, ENDPOINT_TYPE_V4);
    if ((old_fd == -1) && (socket_fd_ != old_fd)) {
        IfaceMgr::instance().addExternalSocket(socket_fd_,
                                               Dhcp4to6Ipc::handler);
    }
}

void Dhcp4to6Ipc::handler(int /* fd */) {
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    Pkt6Ptr pkt;

    try {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_DHCP4O6_RECEIVING);
        // Receive message from the IPC socket.
        pkt = ipc.receive();

        // from Dhcpv4Srv::run_one() after receivePacket()
        if (pkt) {
            LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_DHCP4O6_PACKET_RECEIVED)
                .arg(static_cast<int>(pkt->getType()))
                .arg(pkt->getRemoteAddr().toText())
                .arg(pkt->getRemotePort())
                .arg(pkt->getIface());
        }
    } catch (const std::exception& e) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_DHCP4O6_RECEIVE_FAIL)
            .arg(e.what());
    }

    if (!pkt) {
        return;
    }

    // Each message must contain option holding DHCPv4 message.
    OptionCollection msgs = pkt->getOptions(D6O_DHCPV4_MSG);
    if (msgs.empty()) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_DHCP4O6_BAD_PACKET)
            .arg("DHCPv4 message option not present");
        return;
    } else if (msgs.size() > 1) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_DHCP4O6_BAD_PACKET)
            .arg("more than one DHCPv4 message option");
        return;
    }

    // Get the DHCPv4 message.
    OptionPtr msg = msgs.begin()->second;
    if (!msg) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_DHCP4O6_BAD_PACKET)
            .arg("null DHCPv4 message option");
        return;
    }

    // Extract the DHCPv4 packet with DHCPv6 packet attached
    Pkt4Ptr query(new Pkt4o6(msg->getData(), pkt));

    // From Dhcpv4Srv::run_one() processing and after
    Pkt4Ptr rsp;

    ControlledDhcpv4Srv::getInstance()->processPacket(query, rsp, false);

    if (!rsp) {
        return;
    }

    try {
        // Now all fields and options are constructed into output wire buffer.
        // Option objects modification does not make sense anymore. Hooks
        // can only manipulate wire buffer at this stage.
        // Let's execute all callouts registered for buffer4_send
      if (HooksManager::calloutsPresent(Dhcpv4Srv::getHookIndexBuffer4Send())) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Enable copying options from the packet within hook library.
            ScopedEnableOptionsCopy<Pkt4> response4_options_copy(rsp);

            // Pass incoming packet as argument
            callout_handle->setArgument("response4", rsp);

            // Call callouts
            HooksManager::callCallouts(Dhcpv4Srv::getHookIndexBuffer4Send(),
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to parse the packet, so skip at this
            // stage means drop.
            if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
                (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                          DHCP4_HOOK_BUFFER_SEND_SKIP)
                    .arg(rsp->getLabel());
                return;
            }

            callout_handle->getArgument("response4", rsp);
        }

        Pkt4o6Ptr rsp6 = boost::dynamic_pointer_cast<Pkt4o6>(rsp);
        // Should not happen
        if (!rsp6) {
            isc_throw(Unexpected, "Dhcp4o6 packet cast fail");
        }

        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_DHCP4O6_PACKET_SEND)
            .arg(rsp6->getLabel())
            .arg(rsp6->getName())
            .arg(static_cast<int>(rsp6->getType()))
            .arg(rsp6->getRemoteAddr())
            .arg(rsp6->getRemotePort())
            .arg(rsp6->getIface())
            .arg(rsp->getLabel())
            .arg(rsp->getName())
            .arg(static_cast<int>(rsp->getType()));

        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA,
                  DHCP4_DHCP4O6_RESPONSE_DATA)
            .arg(rsp6->getLabel())
            .arg(rsp6->getName())
            .arg(static_cast<int>(rsp6->getType()))
            .arg(rsp6->toText());

        ipc.send(rsp6->getPkt6());

        // Update statistics accordingly for sent packet.
        Dhcpv4Srv::processStatsSent(rsp);

    } catch (const std::exception& e) {
        LOG_ERROR(packet4_logger, DHCP4_DHCP4O6_PACKET_SEND_FAIL)
            .arg(rsp->getLabel())
            .arg(e.what());
    }
}

};  // namespace dhcp

};  // namespace isc
