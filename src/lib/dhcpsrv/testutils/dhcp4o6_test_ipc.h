// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP4O6_TEST_IPC_H
#define DHCP4O6_TEST_IPC_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Implements a simple IPC for the test.
class Dhcp4o6TestIpc : public  Dhcp4o6IpcBase {
public:

    /// @brief Constructor.
    ///
    /// @param port Desired port.
    /// @param endpoint_type Type of the IPC endpoint. It should be 4 or 6.
    Dhcp4o6TestIpc(uint16_t port, EndpointType endpoint_type);

    /// @brief Sets new port to be used with @c open.
    ///
    /// @param desired_port New desired port.
    void setDesiredPort(uint16_t desired_port) {
        desired_port_ = desired_port;
    }

    /// @brief Opens the IPC socket and registers it in @c IfaceMgr.
    ///
    /// This method opens the IPC socket and registers it as external
    /// socket in the IfaceMgr. The @c TestIpc::receiveHandler is used as a
    /// callback to be called by the @c IfaceMgr when the data is received
    /// over the socket.
    virtual void open();

    /// @brief Close the IPC socket.
    virtual void close();

    /// @brief Retrieve port which socket is bound to.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Retrieve socket descriptor.
    int getSocketFd() const {
        return (socket_fd_);
    }

    /// @brief Pops and returns a received message.
    ///
    /// @return Pointer to the received message over the IPC.
    Pkt6Ptr popPktReceived() {
        // Copy the received message.
        Pkt6Ptr pkt_copy(pkt_received_);
        // Set the received message to NULL (pop).
        pkt_received_.reset();
        // Return the copy.
        return (pkt_copy);
    }

private:

    /// @brief Callback for the IPC socket.
    ///
    /// This callback is called by the @c IfaceMgr when the data is received
    /// over the IPC socket.
    void receiveHandler();

    /// @brief Port number.
    uint16_t desired_port_;

    /// @brief Endpoint type, i.e. 4 or 6.
    EndpointType endpoint_type_;

    /// @brief Pointer to the last received message.
    Pkt6Ptr pkt_received_;
};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4O6_TEST_IPC_H
