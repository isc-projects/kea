// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef NCR_MSG_H
#define NCR_MSG_H

/// @file ncr_msg.h
/// @brief This file provides the classes needed to embody, compose, and
/// decompose DNS update requests that are sent by DHCP-DDNS clients to
/// DHCP-DDNS. These requests are referred to as NameChangeRequests.

#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <util/encode/hex.h>
#include <util/time_utilities.h>

#include <time.h>
#include <string>

namespace isc {
namespace dhcp_ddns {

/// @brief Exception thrown when NameChangeRequest marshalling error occurs.
class NcrMessageError : public isc::Exception {
public:
    NcrMessageError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when there is an error occured during computation
/// of the DHCID.
class DhcidComputeError : public isc::Exception {
public:
    DhcidComputeError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Defines the types of DNS updates that can be requested.
enum NameChangeType {
  CHG_ADD,
  CHG_REMOVE
};

/// @brief Defines the runtime processing status values for requests.
enum NameChangeStatus  {
  ST_NEW,
  ST_PENDING,
  ST_COMPLETED,
  ST_FAILED
};

/// @brief Defines the list of data wire formats supported.
enum NameChangeFormat {
  FMT_JSON
};

/// @brief Container class for handling the DHCID value within a
/// NameChangeRequest. It provides conversion to and from string for JSON
/// formatting, but stores the data internally as unsigned bytes.
class D2Dhcid {
public:
    /// @brief Default constructor
    D2Dhcid();

    /// @brief Constructor - Creates a new instance, populated by converting
    /// a given string of digits into an array of unsigned bytes.
    ///
    /// @param data is a string of hexadecimal digits. The format is simply
    /// a contiguous stream of digits, with no delimiters. For example a string
    /// containing "14A3" converts to a byte array containing:  0x14, 0xA3.
    ///
    /// @throw NcrMessageError if the input data contains non-digits
    /// or there is an odd number of digits.
    D2Dhcid(const std::string& data);

    /// @brief Constructor, creates an instance of the @c D2Dhcid from the
    /// HW address.
    ///
    /// @param A pointer to the object encapsulating HW address.
    /// @param A on-wire canonical representation of the FQDN.
    D2Dhcid(const isc::dhcp::HWAddrPtr& hwaddr,
            const std::vector<uint8_t>& wire_fqdn);

    /// @brief Constructor, creates an instance of the @c D2Dhcid from the
    /// client identifier carried in the Client Identifier option.
    ///
    /// @param clientid_data Holds the raw bytes representing client identifier.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
    D2Dhcid(const std::vector<uint8_t>& clientid_data,
            const std::vector<uint8_t>& wire_fqdn);

    /// @brief Constructor, creates an instance of the @c D2Dhcid from the
    /// @c isc::dhcp::DUID.
    ///
    /// @param duid An object representing DUID.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
    D2Dhcid(const isc::dhcp::DUID& duid,
            const std::vector<uint8_t>& wire_fqdn);

    /// @brief Returns the DHCID value as a string of hexadecimal digits.
    ///
    /// @return a string containing a contiguous stream of digits.
    std::string toStr() const;

    /// @brief Sets the DHCID value based on the given string.
    ///
    /// @param data is a string of hexadecimal digits. The format is simply
    /// a contiguous stream of digits, with no delimiters. For example a string
    /// containing "14A3" converts to a byte array containing:  0x14, 0xA3.
    ///
    /// @throw NcrMessageError if the input data contains non-digits
    /// or there is an odd number of digits.
    void fromStr(const std::string& data);

    /// @brief Sets the DHCID value based on the Client Identifier.
    ///
    /// @param clientid_data Holds the raw bytes representing client identifier.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
    void fromClientId(const std::vector<uint8_t>& clientid_data,
                      const std::vector<uint8_t>& wire_fqdn);

    /// @brief Sets the DHCID value based on the DUID and FQDN.
    ///
    /// This function requires that the FQDN conforms to the section 3.5
    /// of the RFC4701, which says that the FQDN must be in lowercase.
    /// This function doesn't validate if it really converted.
    ///
    /// @param duid A @c isc::dhcp::DUID object encapsulating DUID.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
    void fromDUID(const isc::dhcp::DUID& duid,
                  const std::vector<uint8_t>& wire_fqdn);

    /// @brief Sets the DHCID value based on the HW address and FQDN.
    ///
    /// @param A pointer to the object encapsulating HW address.
    /// @param A on-wire canonical representation of the FQDN.
    void fromHWAddr(const isc::dhcp::HWAddrPtr& hwaddr,
                    const std::vector<uint8_t>& wire_fqdn);

    /// @brief Returns a reference to the DHCID byte vector.
    ///
    /// @return a reference to the vector.
    const std::vector<uint8_t>& getBytes() {
        return (bytes_);
    }

    /// @brief Compares two D2Dhcids for equality
    bool operator==(const D2Dhcid& other) const {
        return (this->bytes_ == other.bytes_);
    }

    /// @brief Compares two D2Dhcids for inequality
    bool operator!=(const D2Dhcid& other) const {
        return (this->bytes_ != other.bytes_);
    }

    /// @brief Compares two D2Dhcids lexcially
    bool operator<(const D2Dhcid& other) const {
        return (this->bytes_ < other.bytes_);
    }

private:

    /// @brief Creates the DHCID using specified indetifier.
    ///
    /// This function creates the DHCID RDATA as specified in RFC4701,
    /// section 3.5.
    ///
    /// @param identifier_type is a less significant byte of the identifier-type
    /// defined in RFC4701.
    /// @param identifier_data A buffer holding client identifier raw data -
    /// e.g. DUID, data carried in the Client Identifier option or client's
    /// HW address.
    /// @param A on-wire canonical representation of the FQDN.
    void createDigest(const uint8_t identifier_type,
                      const std::vector<uint8_t>& identifier_data,
                      const std::vector<uint8_t>& wire_fqdn);

    /// @brief Storage for the DHCID value in unsigned bytes.
    std::vector<uint8_t> bytes_;
};

class NameChangeRequest;
/// @brief Defines a pointer to a NameChangeRequest.
typedef boost::shared_ptr<NameChangeRequest> NameChangeRequestPtr;

/// @brief Defines a map of Elements, keyed by their string name.
typedef std::map<std::string, isc::data::ConstElementPtr> ElementMap;

/// @brief  Represents a DHCP-DDNS client request.
/// This class is used by DHCP-DDNS clients (e.g. DHCP4, DHCP6) to
/// request DNS updates.  Each message contains a single DNS change (either an
/// add/update or a remove) for a single FQDN.  It provides marshalling services
/// for moving instances to and from the wire.  Currently, the only format
/// supported is JSON, however the class provides an interface such that other
/// formats can be readily supported.
class NameChangeRequest {
public:
    /// @brief Default Constructor.
    NameChangeRequest();

    /// @brief Constructor.  Full constructor, which provides parameters for
    /// all of the class members, except status.
    ///
    /// @param change_type the type of change (Add or Update)
    /// @param forward_change indicates if this change should be sent to forward
    /// DNS servers.
    /// @param reverse_change indicates if this change should be sent to reverse
    /// DNS servers.
    /// @param fqdn the domain name whose pointer record(s) should be
    /// updated.
    /// @param ip_address the ip address leased to the given FQDN.
    /// @param dhcid the lease client's unique DHCID.
    /// @param lease_expires_on a timestamp containing the date/time the lease
    /// expires.
    /// @param lease_length the amount of time in seconds for which the
    /// lease is valid (TTL).
    NameChangeRequest(const NameChangeType change_type,
                      const bool forward_change, const bool reverse_change,
                      const std::string& fqdn, const std::string& ip_address,
                      const D2Dhcid& dhcid,
                      const uint64_t lease_expires_on,
                      const uint32_t lease_length);

    /// @brief Static method for creating a NameChangeRequest from a
    /// buffer containing a marshalled request in a given format.
    ///
    /// When the format is:
    ///
    /// JSON: The buffer is expected to contain a two byte unsigned integer
    /// which specified the length of the JSON text; followed by the JSON
    /// text itself.  This method attempts to extract "length" characters
    /// from the buffer. This data is used to create a character string that
    /// is than treated as JSON which is then parsed into the data needed
    /// to create a request instance.
    ///
    /// (NOTE currently only JSON is supported.)
    ///
    /// @param format indicates the data format to use
    /// @param buffer is the input buffer containing the marshalled request
    ///
    /// @return a pointer to the new NameChangeRequest
    ///
    /// @throw NcrMessageError if an error occurs creating new
    /// request.
    static NameChangeRequestPtr fromFormat(const NameChangeFormat format,
                                           isc::util::InputBuffer& buffer);

    /// @brief Instance method for marshalling the contents of the request
    /// into the given buffer in the given format.
    ///
    /// When the format is:
    ///
    /// JSON: Upon completion, the buffer will contain a two byte unsigned
    /// integer which specifies the length of the JSON text; followed by the
    /// JSON text itself. The JSON text contains the names and values for all
    /// the request data needed to reassemble the request on the receiving
    /// end. The JSON text in the buffer is NOT null-terminated.
    ///
    /// (NOTE currently only JSON is supported.)
    ///
    /// @param format indicates the data format to use
    /// @param buffer is the output buffer to which the request should be
    /// marshalled.
    void toFormat(const NameChangeFormat format,
                  isc::util::OutputBuffer& buffer) const;

    /// @brief Static method for creating a NameChangeRequest from a
    /// string containing a JSON rendition of a request.
    ///
    /// @param json is a string containing the JSON text
    ///
    /// @return a pointer to the new NameChangeRequest
    ///
    /// @throw NcrMessageError if an error occurs creating new request.
    static NameChangeRequestPtr fromJSON(const std::string& json);

    /// @brief Instance method for marshalling the contents of the request
    /// into a string of JSON text.
    ///
    /// @return a string containing the JSON rendition of the request
    std::string toJSON() const;

    /// @brief Validates the content of a populated request.  This method is
    /// used by both the full constructor and from-wire marshalling to ensure
    /// that the request is content valid.  Currently it enforces the
    /// following rules:
    ///
    ///  - FQDN must not be blank.
    ///  - The IP address must be a valid address.
    ///  - The DHCID must not be blank.
    ///  - The lease expiration date must be a valid date/time.
    ///  - That at least one of the two direction flags, forward change and
    ///    reverse change is true.
    ///
    /// @todo This is an initial implementation which provides a minimal amount
    /// of validation.  FQDN, DHCID, and IP Address members are all currently
    /// strings, these may be replaced with richer classes.
    ///
    /// @throw NcrMessageError if the request content violates any
    /// of the validation rules.
    void validateContent();

    /// @brief Fetches the request change type.
    ///
    /// @return the change type
    NameChangeType getChangeType() const {
        return (change_type_);
    }

    /// @brief Sets the change type to the given value.
    ///
    /// @param value is the NameChangeType value to assign to the request.
    void setChangeType(const NameChangeType value);

    /// @brief Sets the change type to the value of the given Element.
    ///
    /// @param element is an integer Element containing the change type value.
    ///
    /// @throw NcrMessageError if the element is not an integer
    /// Element or contains an invalid value.
    void setChangeType(isc::data::ConstElementPtr element);

    /// @brief Checks forward change flag.
    ///
    /// @return a true if the forward change flag is true.
    bool isForwardChange() const {
        return (forward_change_);
    }

    /// @brief Sets the forward change flag to the given value.
    ///
    /// @param value contains the new value to assign to the forward change
    /// flag
    void setForwardChange(const bool value);

    /// @brief Sets the forward change flag to the value of the given Element.
    ///
    /// @param element is a boolean Element containing the forward change flag
    /// value.
    ///
    /// @throw NcrMessageError if the element is not a boolean
    /// Element
    void setForwardChange(isc::data::ConstElementPtr element);

    /// @brief Checks reverse change flag.
    ///
    /// @return a true if the reverse change flag is true.
    bool isReverseChange() const {
        return (reverse_change_);
    }

    /// @brief Sets the reverse change flag to the given value.
    ///
    /// @param value contains the new value to assign to the reverse change
    /// flag
    void setReverseChange(const bool value);

    /// @brief Sets the reverse change flag to the value of the given Element.
    ///
    /// @param element is a boolean Element containing the reverse change flag
    /// value.
    ///
    /// @throw NcrMessageError if the element is not a boolean
    /// Element
    void setReverseChange(isc::data::ConstElementPtr element);

    /// @brief Fetches the request FQDN
    ///
    /// @return a string containing the FQDN
    const std::string getFqdn() const {
        return (fqdn_);
    }

    /// @brief Sets the FQDN to the given value.
    ///
    /// @param value contains the new value to assign to the FQDN
    void setFqdn(const std::string& value);

    /// @brief Sets the FQDN to the value of the given Element.
    ///
    /// @param element is a string Element containing the FQDN
    ///
    /// @throw NcrMessageError if the element is not a string
    /// Element
    void setFqdn(isc::data::ConstElementPtr element);

    /// @brief Fetches the request IP address.
    ///
    /// @return a string containing the IP address
    const std::string& getIpAddress() const {
        return (ip_address_);
    }

    /// @brief Sets the IP address to the given value.
    ///
    /// @param value contains the new value to assign to the IP address
    void setIpAddress(const std::string& value);

    /// @brief Sets the IP address to the value of the given Element.
    ///
    /// @param element is a string Element containing the IP address
    ///
    /// @throw NcrMessageError if the element is not a string
    /// Element
    void setIpAddress(isc::data::ConstElementPtr element);

    /// @brief Fetches the request DHCID
    ///
    /// @return a reference to the request's D2Dhcid
    const D2Dhcid& getDhcid() const {
        return (dhcid_);
    }

    /// @brief Sets the DHCID based on the given string value.
    ///
    /// @param value is a string of hexadecimal digits. The format is simply
    /// a contiguous stream of digits, with no delimiters. For example a string
    /// containing "14A3" converts to a byte array containing:  0x14, 0xA3.
    ///
    /// @throw NcrMessageError if the input data contains non-digits
    /// or there is an odd number of digits.
    void setDhcid(const std::string& value);

    /// @brief Sets the DHCID based on the value of the given Element.
    ///
    /// @param element is a string Element containing the string of hexadecimal
    /// digits. (See setDhcid(std::string&) above.)
    ///
    /// @throw NcrMessageError if the input data contains non-digits
    /// or there is an odd number of digits.
    void setDhcid(isc::data::ConstElementPtr element);

    /// @brief Fetches the request lease expiration
    ///
    /// @return the lease expiration as the number of seconds since
    /// the (00:00:00 January 1, 1970)
    uint64_t getLeaseExpiresOn() const {
        return (lease_expires_on_);
    }

    /// @brief Fetches the request lease expiration as string.
    ///
    /// The format of the string returned is:
    ///
    ///    YYYYMMDDHHmmSS
    ///
    /// Example: 18:54:54 June 26, 2013 would be: 20130626185455
    /// NOTE This is always UTC time.
    ///
    /// @return a ISO date-time string of the lease expiration.
    std::string getLeaseExpiresOnStr() const;

    /// @brief Sets the lease expiration based on the given string.
    ///
    /// @param value is an date-time string from which to set the
    /// lease expiration. The format of the input is:
    ///
    ///    YYYYMMDDHHmmSS
    ///
    /// Example: 18:54:54 June 26, 2013 would be: 20130626185455
    /// NOTE This is always UTC time.
    ///
    /// @throw NcrMessageError if the ISO string is invalid.
    void setLeaseExpiresOn(const std::string& value);

    /// @brief Sets the lease expiration based on the given Element.
    ///
    /// @param element is string Element containing a date-time string.
    ///
    /// @throw NcrMessageError if the element is not a string
    /// Element, or if the element value is an invalid date-time string.
    void setLeaseExpiresOn(isc::data::ConstElementPtr element);

    /// @brief Fetches the request lease length.
    ///
    /// @return an integer containing the lease length
    uint32_t getLeaseLength() const {
        return (lease_length_);
    }

    /// @brief Sets the lease length to the given value.
    ///
    /// @param value contains the new value to assign to the lease length
    void setLeaseLength(const uint32_t value);

    /// @brief Sets the lease length to the value of the given Element.
    ///
    /// @param element is a integer Element containing the lease length
    ///
    /// @throw NcrMessageError if the element is not a string
    /// Element
    void setLeaseLength(isc::data::ConstElementPtr element);

    /// @brief Fetches the request status.
    ///
    /// @return the request status as a NameChangeStatus
    NameChangeStatus getStatus() const {
        return (status_);
    }

    /// @brief Sets the request status to the given value.
    ///
    /// @param value contains the new value to assign to request status
    void setStatus(const NameChangeStatus value);

    /// @brief Given a name, finds and returns an element from a map of
    /// elements.
    ///
    /// @param name is the name of the desired element
    /// @param element_map is the map of elements to search
    ///
    /// @return a pointer to the element if located
    /// @throw NcrMessageError if the element cannot be found within
    /// the map
    isc::data::ConstElementPtr getElement(const std::string& name,
                                          const ElementMap& element_map) const;

    /// @brief Returns a text rendition of the contents of the request.
    /// This method is primarily for logging purposes.
    ///
    /// @return a string containing the text.
    std::string toText() const;

    bool operator == (const NameChangeRequest& b);
    bool operator != (const NameChangeRequest& b);

private:
    /// @brief Denotes the type of this change as either an Add or a Remove.
    NameChangeType change_type_;

    /// @brief Indicates if this change should sent to forward DNS servers.
    bool forward_change_;

    /// @brief Indicates if this change should sent to reverse DNS servers.
    bool reverse_change_;

    /// @brief The domain name whose DNS entry(ies) are to be updated.
    /// @todo Currently, this is a std::string but may be replaced with
    /// dns::Name which provides additional validation and domain name
    /// manipulation.
    std::string fqdn_;

    /// @brief The ip address leased to the FQDN.
    std::string ip_address_;

    /// @brief The lease client's unique DHCID.
    /// @todo Currently, this is uses D2Dhcid it but may be replaced with
    /// dns::DHCID which provides additional validation.
    D2Dhcid dhcid_;

    /// @brief The date-time the lease expires.
    uint64_t lease_expires_on_;

    /// @brief The amount of time in seconds for which the lease is valid (TTL).
    uint32_t lease_length_;

    /// @brief The processing status of the request.  Used internally.
    NameChangeStatus status_;
};


}; // end of isc::dhcp_ddns namespace
}; // end of isc namespace

#endif
