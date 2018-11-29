// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT4O6_H
#define PKT4O6_H

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <boost/shared_ptr.hpp>

namespace isc {

namespace dhcp {

/// @brief Represents DHCPv4-over-DHCPv6 packet
///
/// This class derives from @c Pkt4 in order to be handled by
/// the DHCPv4 server code. It includes a shared pointer to the
/// DHCPv6 message too.
///
/// This is an implementation of the DHCPv4-query/response DHCPv6 messages
/// defined in RFC 7341 (http://ietf.org/rfc/rfc7341.txt).
/// See also
/// https://gitlab.isc.org/isc-projects/kea/wikis/designs/dhcpv4o6-design
/// for design discussions.
class Pkt4o6 : public Pkt4 {
public:

    /// @brief Constructor, used in message reception.
    ///
    /// @param pkt4 Content of the DHCPv4-message option
    /// @param pkt6 encapsulating unpacked DHCPv6 message
    /// the DHCPv4 message option will be removed
    Pkt4o6(const OptionBuffer& pkt4, const Pkt6Ptr& pkt6);

    /// @brief Constructor, used in replying to a message
    ///
    /// @param pkt4 DHCPv4 message
    /// @param pkt6 DHCPv6 message
    Pkt4o6(const Pkt4Ptr& pkt4, const Pkt6Ptr& pkt6);

    /// @brief Returns encapsulating DHCPv6 message
    Pkt6Ptr getPkt6() const { return (pkt6_); }

    /// @brief Prepares on-wire format of DHCPv4-over-DHCPv6 packet.
    ///
    /// Calls pack() on both DHCPv4 and DHCPv6 parts
    /// Inserts the DHCPv4-message option
    /// @ref Pkt4::pack and @ref Pkt6::pack
    virtual void pack();

    /// @brief Checks if a DHCPv4 message has been transported over DHCPv6
    ///
    /// @return Boolean value which indicates whether the message is
    /// transported over DHCPv6 (true) or native DHCPv4 (false)
    virtual bool isDhcp4o6() const {
        return (true);
    }

    /// @brief Overrides the @ref Pkt::setCopyRetrievedOptions to also
    /// set the flag for encapsulated @ref Pkt6 instance.
    ///
    /// When the flag is set for the instance of the @ref Pkt4o6 the
    /// encapsulated Pkt6, retrieved with @ref Pkt4o6::getPkt6, will
    /// inherit this setting.
    ///
    /// @param copy Indicates if the options should be copied when
    /// retrieved (if true), or not copied (if false).
    virtual void setCopyRetrievedOptions(const bool copy);

private:
    /// Encapsulating DHCPv6 message
    Pkt6Ptr pkt6_;

}; // Pkt4o6 class

/// @brief A pointer to Pkt4o6 object.
typedef boost::shared_ptr<Pkt4o6> Pkt4o6Ptr;

} // isc::dhcp namespace

} // isc namespace

#endif
