// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef DHCP4O6_IPC_H
#define DHCP4O6_IPC_H

#include <dhcp/pkt4o6.h>
#include <util/ipc.h>

#include <queue>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when DHCP4o6IPC::send() failed.
class DHCP4o6IPCSendError : public isc::util::IPCSendError {
public:
    DHCP4o6IPCSendError(const char* file, size_t line, const char* what) :
        isc::util::IPCSendError(file, line, what) { };
};

/// @brief IPC class to pass Pkt4o6 between DHCPv4 and DHCPv6 servers
class DHCP4o6IPC : public isc::util::BaseIPC {
public:
    /// @brief Default constructor.
    ///
    /// This function calls BaseIPC::open() to initiate socket directly
    /// Method will throw if BaseIPC::open() method failed
    ///
    /// @param local_filename Filename for receiving socket
    /// @param remote_filename Filename for sending socket
    DHCP4o6IPC(const std::string& local_filename, const std::string& remote_filename);
    
    /// @brief Send a DHCPv4 ove DHCPv6 packet
    ///
    /// This function converts Pkt4o6 into binary data and sends it
    /// through BaseIPC::send().
    /// Method will throw if BaseIPC::send() failed
    ///
    /// @param pkt4o6 Pointer to the packet to be sent
    void sendPkt4o6(const Pkt4o6Ptr& pkt4o6);
    
    /// @brief Receive a DHCPv4 ove DHCPv6 packet
    ///
    /// This function calls BaseIPC::recv() to receive binary data
    /// and converts it into Pkt4o6
    /// It pushes received Pkt4o6 into a queue and does not return immediately.
    /// Method will throw if BaseIPC::recv() failed or Pkt4o6
    /// construction failed
    void recvPkt4o6();
    
    /// @brief Test if Pkt4o6 receiving queue is empty.
    /// 
    /// @return true if the Pkt4o6 receiving queue is empty.
    bool empty() const { return queue_.empty(); }
    
    /// @brief Retrive a Pkt4o6 in the receiving queue and remove it.
    ///
    /// If the receiving queue is not empty, return the one 
    /// in front of the queue and remove it from the queue.
    ///
    /// @return A pointer to the retrived Pkt4o6, or a null pointer if the
    /// queue is empty.
    Pkt4o6Ptr pop();
    
    /// @brief Get the instance of current processing Pkt4o6
    Pkt4o6Ptr currentPkt4o6() { return current_; }

protected:
    
    /// @brief A queue of received DHCPv4 over DHCPv6 packets that has
    /// not been processed
    std::queue<Pkt4o6Ptr> queue_;
      
    /// @brief The current processing DHCPv4 over DHCPv6 packet
    Pkt4o6Ptr current_;
};//DHCP4o6IPC class

typedef boost::shared_ptr<DHCP4o6IPC> DHCP4o6IPCPtr;

} // isc::dhcp namespace
} // isc namespace

#endif //DHCP4O6_IPC_H
