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

#ifndef CFG_SUBNETS4_H
#define CFG_SUBNETS4_H

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/subnet.h>
#include <util/optional_value.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Exception thrown upon attempt to add subnet with an ID that belongs
/// to the subnet that already exists.
class DuplicateSubnet4ID : public Exception {
public:
    DuplicateSubnet4ID(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Holds subnets configured for the DHCPv4 server.
///
/// This class holds a collection of subnets configured for the DHCPv4 server.
/// It allows for retrieving a subnet for the particular client using various
/// parameters extracted from the DHCPv4 message. These parameters must be
/// assigned to the appropriate members of the @c CfgSubnets4::Selector
/// structure.
///
/// See @c CfgSubnets4::get documentation for more details on how the subnet
/// is selected for the client.
class CfgSubnets4 {
public:

    /// @brief Subnet selector used in @c CfgSubnets4::getSubnet4.
    ///
    /// This structure holds various parameters extracted from a packet sent
    /// by a DHCP client used to select the subnet for the client. Note that
    /// data members are optional which means that they may be left unspecified
    /// by the caller, if the caller doesn't have access to the relevant
    /// information.
    struct Selector {
        /// @brief ciaddr from the client's message.
        util::OptionalValue<asiolink::IOAddress> ciaddr_;
        /// @brief giaddr from the client's message.
        util::OptionalValue<asiolink::IOAddress> giaddr_;
        /// @brief Address on which the message was received.
        util::OptionalValue<asiolink::IOAddress> local_address_;
        /// @brief Source address of the message.
        util::OptionalValue<asiolink::IOAddress> remote_address_;
        /// @brief Classes that the client belongs to.
        util::OptionalValue<ClientClasses> client_classes_;
        /// @brief Name of the interface on which the message was received.
        util::OptionalValue<std::string> iface_name_;

        /// @brief Default constructor.
        ///
        ///  Sets the default values for the @c Selector.
        Selector();
    };

    /// @brief Adds new subnet to the configuration.
    ///
    /// @param subnet Pointer to the subnet being added.
    ///
    /// @throw isc::DuplicateSubnet4ID If the subnet id for the new subnet
    /// duplicates id of an existing subnet.
    void add(const Subnet4Ptr& subnet);

    /// @brief Returns pointer to the collection of all IPv4 subnets.
    ///
    /// This is used in a hook (subnet4_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    ///
    /// @return A pointer to const Subnet4 collection
    const Subnet4Collection* getAll() const {
        return (&subnets_);
    }

    /// @brief Returns pointer to the selected subnet.
    ///
    /// This method tries to retrieve the subnet for the client using various
    /// parameters extracted from the client's message using the following
    /// logic.
    ///
    /// If the giaddr value is found it means that the client's message was
    /// relayed. The subnet configuration allows for setting the relay address
    /// for each subnet to indicate that the subnet must be assigned when the
    /// packet was transmitted over the particular relay. This method first
    /// tries to match the giaddr with the relay addresses specified for
    /// all subnets. If the relay address for the subnet is equal to the address
    /// of the relay through which the message was transmitted, the particular
    /// subnet is returned.
    ///
    /// If the giaddr is not matched with any of the relay addresses in any
    /// subnet or the message was not relayed, the method will need to try to
    /// match one of the addresses in the client's message with the prefixes
    /// of the existing subnets. Depending whether it is a relayed message,
    /// message from the renewing client or a new allocation, the server will
    /// pick one of the following addresses for this matching:
    /// - giaddr - for relayed message
    /// - ciaddr - for renewing or rebinding client
    /// - source address - for the renewing client which didn't provide ciaddr
    /// - address on the local server's interface if this is a new allocation
    /// requested by the directly connected client
    ///
    /// If the address matches with a subnet, the subnet is returned.
    ///
    /// @param selector Const reference to the selector structure which holds
    /// various information extracted from the client's packet which are used
    /// to find appropriate subnet.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    /// @throw isc::BadValue if the values in the subnet selector are invalid
    /// or they are insufficient to select a subnet.
    Subnet4Ptr get(const Selector& selector) const;

private:

    /// @brief Checks that the IPv4 subnet with the given id already exists.
    ///
    /// @param subnet Subnet for which this function will check if the other
    /// subnet with equal id already exists.
    ///
    /// @return true if the duplicate subnet exists.
    bool isDuplicate(const Subnet4& subnet) const;

    /// @brief A container for IPv4 subnets.
    Subnet4Collection subnets_;

};

/// @name Pointer to the @c CfgSubnets4 objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgSubnets4> CfgSubnets4Ptr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgSubnets4> ConstCfgSubnets4Ptr;

//@}

}
}

#endif // CFG_SUBNETS4_H
