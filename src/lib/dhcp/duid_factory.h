// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DUID_FACTORY_H
#define DUID_FACTORY_H

#include <dhcp/duid.h>
#include <boost/noncopyable.hpp>
#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Factory for generating DUIDs (DHCP Unique Identifiers).
///
/// DHCPv6 clients and servers are identified by DUIDs (see RFC3315).
/// DUIDs are unique identifiers carried in the appropriate DHCP
/// options. RFC3315 defines 3 types of DUIDs:
/// -# DUID-LLT
/// -# DUID-EN
/// -# DUID-LL
///
/// of which the DUID-LLT is recommended for all general purpose computing
/// devices. RFC6355 defines new DUID-UUID and any future specifications may
/// define new DUID types. The current implementation of the class only
/// supports DUID types defined in RFC3315.
///
/// In most cases DUIDs can be generated automatically, i.e. no manual
/// configuration is required. For example, DUID-LLT is composed of the
/// current time and link layer address and type of one of the network
/// interfaces. Once the DUID is generated it should be stored in the persistent
/// storage and used by a server or client even when the network interface which
/// address had been used to generate the DUID is removed.
///
/// In some cases administrators may elect to use other types of DUIDs, which
/// are easier to generate (in case of lack of persistent storage or when
/// specifics of the device favors some generation methods), e.g. DUID-EN
/// doesn't rely on the link layer addresses of interfaces present in the
/// system.
///
/// In some cases administrators may want to influence the value of the
/// generated DUID. For example, DUID-EN includes enterprise identifier and
/// the administrator may want to select this identifier.
///
/// This class allows for selecting a type of DUID to be generated. It also
/// allows for setting desired values for the components of the DUIDs
/// being generated, while leaving other components unspecified. For example
/// an administrator may elect to set the enterprise id for the DUID-EN
/// and leave the variable length identifier unspecified. The variable
/// length identifier will be autogenerated.
///
/// This class is also responsible for storing the generated DUID in a
/// file. The location of this file is specified in the class constructor.
/// If this location is not specified the DUID is not persisted, i.e. is
/// lost when the server or client shuts down. However, the DUID may be
/// reconstructed according to the configuration of the client or server
/// when they are back online.
class DUIDFactory : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param storage_location Absolute path to the file where DUID is
    /// stored.
    DUIDFactory(const std::string& storage_location = "");

    /// @brief Checks if generated DUID will be persisted in the file.
    ///
    /// @return true if generated DUIDs are persisted in a file, false
    /// otherwise.
    bool isPersisted() const;

    /// @brief Generates DUID-LLT.
    ///
    /// This method generates DUID-LLT.
    ///
    /// @param htype Hardware type. If this is set to 0 and link layer
    /// address is empty a value from existing DUID or a default value
    /// of @c HTYPE_ETHER is used. Otherwise a link layer type of selected
    /// interface is used.
    /// @param time_in Explicit value of time for the DUID. If this is
    /// set to 0 a value from existing DUOD or current time is used,
    /// otherwise a value specified is used.
    /// @param ll_identifier Data to be used as link layer address. If
    /// this is an empty vector this method will try to use link layer
    /// address from existing DUID. If there is no DUID yet, it will
    /// iterate over all active interfaces and will pick link layer
    /// address of one of them.
    ///
    /// @throw isc::Unexpected if none of the interfaces includes has a
    /// suitable link layer address.
    void createLLT(const uint16_t htype, const uint32_t time_in,
                   const std::vector<uint8_t>& ll_identifier);

    /// @brief Generates DUID-EN.
    ///
    /// @param enterprise_id Enterprise id. If this value is 0, a value
    /// from existing DUID is used or ISC's enterprise id if there is
    /// no DUID yet.
    /// @param identifier Data to be used as variable length identifier.
    /// If this is an empty vector, an identifier from existing DUID is
    /// used. If there is no DUID yet, the 6-bytes long vector with random
    /// values is generated.
    void createEN(const uint32_t enterprise_id,
                  const std::vector<uint8_t>& identifier);

    /// @brief Generates DUID-LL.
    ///
    /// @param htype Hardware type. If this is set to 0 and link layer
    /// address is empty a value from existing DUID or a default value
    /// of @c HTYPE_ETHER is used. Otherwise a link layer type of selected
    /// interface is used.
    /// @param ll_identifier Data to be used as link layer address. If
    /// this is an empty vector this method will try to use link layer
    /// address from existing DUID. If there is no DUID yet, it will
    /// iterate over all active interfaces and will pick link layer
    /// address of one of them.
    ///
    /// @throw isc::Unexpected if none of the interfaces includes has a
    /// suitable link layer address.
    void createLL(const uint16_t htype,
                  const std::vector<uint8_t>& ll_identifier);

    /// @brief Returns current DUID.
    ///
    /// This method first checks if the DUID has been generated, i.e. as a
    /// result of calling DUIDFactory::createLLT. If the DUID hasn't been
    /// generated, this method will try to read the DUID from the persistent
    /// storage. If the DUID is found in persistent storage it is returned.
    /// Otherwise, the DUID-LLT is generated and returned. In some cases the
    /// generation of the DUID-LLT may fail, e.g. when there are no interfaces
    /// with a suitable link layer address. In this case, this method will
    /// generate DUID-EN, with the ISC enterprise id. If this fails, e.g. as a
    /// result of error while persisting the generated DUID-EN, exception
    /// is thrown.
    ///
    /// @return Instance of the DUID read from file, or generated.
    DuidPtr get();

private:

    /// @brief Creates link layer identifier.
    ///
    /// This method iterates over existing network interfaces and finds the
    /// one with a suitable link layer address to generate a DUID-LLT or
    /// DUID-LL. It uses selected link layer address to generate identifier
    /// held in those DUID types.
    ///
    /// @param [out] identifier Link layer address for the DUID.
    /// @param [out] htype Link layer type to be included in the DUID.
    void createLinkLayerId(std::vector<uint8_t>& identifier,
                           uint16_t& htype) const;

    /// @brief Sets a new DUID as current.
    ///
    /// The generated DUID is persisted in the file, if such file is specified.
    /// The new DUID will be returned when @c DUIDFactory::get is called.
    ///
    /// @param duid_vector New DUID represented as vector of bytes.
    void set(const std::vector<uint8_t>& duid_vector);

    /// @brief Reads DUID from file, if file exists.
    void readFromFile();

    /// @brief Location of the file holding generated DUID (if specified).
    std::string storage_location_;

    /// @brief Pointer to generated DUID.
    DuidPtr duid_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif /* DUID_FACTORY_H */
