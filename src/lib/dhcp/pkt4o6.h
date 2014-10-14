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

#ifndef PKT4o6_H
#define PKT4o6_H

#include <dhcp/pkt6.h>
#include <dhcp/pkt4.h>
#include <dhcp/option.h>
#include <dhcp/dhcp6.h>

namespace isc {

namespace dhcp {

/// @brief Pkt4o6 exception thrown when construction fails.
class Pkt4o6ConstructError : public Exception {
public:
    Pkt4o6ConstructError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// Forward declaration for Pkt4o6
class Pkt4o6;

/// Pointer of Pkt4o6
typedef boost::shared_ptr<Pkt4o6> Pkt4o6Ptr;

/// @brief DHCPv4 over DHCPv6 packet (RFC 7341)
///
/// It represents DHCPv4o6 packet by including a Pkt4ptr and a Pkt6ptr 
/// member variables. Generally the Pkt4ptr points to its DHCPv4 message
/// content, and Pkt6ptr gives DHCPv6 information.
class Pkt4o6 : public Pkt4 {
public:
    /// @brief Constructor, used in message reception.
    ///
    /// Creates new 4o6 message. Call Pkt4's constructor.
    ///
    /// @param data pointer to received data
    /// @param len size of buffer to be allocated for this packet.
    Pkt4o6(const uint8_t* data, size_t len)
        : Pkt4(data, len),
          pkt6_local_addr_("::"),
          pkt6_remote_addr_("::") {}

    /// @brief Construct Pkt4o6 from Pkt6
    ///
    /// Creates a new 4o6 message from DHCPv4-query message
    ///
    /// @param pkt6 pointer to a DHCPv4-query message
    static Pkt4o6Ptr fromPkt6(const Pkt6Ptr& pkt6);
    
    /// @brief Construct Pkt6 from Pkt4o6
    ///
    /// Creates a new DHCPv6 DHCPv4-query message from this 4o6 message
    ///
    /// @return pkt6 pointer to a new DHCPv4-query message
    Pkt6Ptr toPkt6();
    
    /// @brief Sets flags field in DHCPv4-query message
    ///
    /// @param flags flags field in DHCPv4-query message
    void setFlags(uint32_t flags) { flags_ = flags; }

    /// @brief Returns flags field in DHCPv4-query message
    ///
    /// @return flags field in DHCPv4-query message    
    uint32_t getFlags() { return flags_; }
    
    /// @brief Prepares on-wire format of DHCPv4o6 packet.
    ///
    /// Prepares on-wire format of DHCPv4 message by calling Pkt4::pack(),
    /// and prepares DHCP4o6 ancillary data to json-format string for transport.
    ///
    /// Method with throw exception if Pkt4::pack() throws
    virtual void pack();
    
    /// @brief Parses on-wire form of DHCPv4o6 packet.
    ///
    /// Parses DHCPv4 packet by calling Pkt4::unpack(), and parses ancillary
    /// data of DHCP4o6 from json-format string
    ///
    /// Method with throw exception if Pkt4::unpack() throws
    virtual void unpack();
    
    /// @brief Returns a string buffer of DHCP4o6 ancillary data
    ///
    /// @return a string of DHCP4o6 ancillary data
    std::string&
    getBufferAncillary() { return (buffer_ancillary_); }
    
    /// @brief Set string buffer of DHCP4o6 ancillary data
    ///
    /// @param buffer_ancillary a string of json-format DHCP4o6 ancillary data
    void
    setBufferAncillary(const std::string& buffer_ancillary)
        { buffer_ancillary_ = buffer_ancillary; }
    
    /// @brief Get a DHCPv4MsgOption that contains pkt4_
    ///
    /// @return A DHCPv4MsgOption
    OptionBuffer getDHCPv4MsgOption();
    
    /// @brief Sets remote address.
    ///
    /// @param remote specifies remote address
    void setPkt6RemoteAddr(const isc::asiolink::IOAddress& remote) { pkt6_remote_addr_ = remote; }

    /// @brief Returns remote address
    ///
    /// @return remote address
    const isc::asiolink::IOAddress& getPkt6RemoteAddr() const {
        return (pkt6_remote_addr_);
    }
    
    /// @brief Sets local address.
    ///
    /// @param local specifies local address
    void setPkt6LocalAddr(const isc::asiolink::IOAddress& local) { pkt6_local_addr_ = local; }

    /// @brief Returns local address.
    ///
    /// @return local address
    const isc::asiolink::IOAddress& getPkt6LocalAddr() const {
        return (pkt6_local_addr_);
    }
    
    /// @brief Sets interface index.
    ///
    /// @param ifindex specifies interface index.
    void setPkt6Index(uint32_t ifindex) { pkt6_ifindex_ = ifindex; };

    /// @brief Returns interface index.
    ///
    /// @return interface index
    uint32_t getPkt6Index() const { return (pkt6_ifindex_); };

    /// @brief Returns interface name.
    ///
    /// Returns interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    std::string getPkt6Iface() const { return pkt6_iface_; };

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    void setPkt6Iface(const std::string& iface ) { pkt6_iface_ = iface; };
   
protected:

    /// @brief DHCP4o6 flags field, the same as transaction-id in DHCPv6
    uint32_t flags_;
    
    /// @brief local address in Pkt6
    isc::asiolink::IOAddress pkt6_local_addr_;

    /// @brief remote address in Pkt6
    isc::asiolink::IOAddress pkt6_remote_addr_;
    
    /// @brief name of the network interface the DHCP6 packet was received/to be sent over
    std::string pkt6_iface_;

    /// @brief interface index of Pkt6
    int pkt6_ifindex_;
    
    /// @brief Set local address in pkt4 according to U flag in pkt6_
    void setPkt4LocalAddr();
    
    /// @brief a json-format string containing ancillary data used by DHCP4o6
    std::string buffer_ancillary_;
};// pkt4o6 class

} // isc::dhcp namespace

} // isc namespace      
    
#endif
   
    
     
       
             
             
      
