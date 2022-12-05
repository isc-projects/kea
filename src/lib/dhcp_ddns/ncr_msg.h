// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NCR_MSG_H
#define NCR_MSG_H

/// @file ncr_msg.h
/// @brief This file provides the classes needed to embody, compose, and
/// decompose DNS update requests that are sent by DHCP-DDNS clients to
/// DHCP-DDNS. These requests are referred to as NameChangeRequests.

#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dns/name.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>
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

/// @brief Exception thrown when there is an error occurred during computation
/// of the DHCID.
class DhcidRdataComputeError : public isc::Exception {
public:
    DhcidRdataComputeError(const char* file, size_t line, const char* what) :
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

/// @brief Function which converts labels to  NameChangeFormat enum values.
///
/// @param fmt_str text to convert to an enum.
/// Valid string values: "JSON"
///
/// @return NameChangeFormat value which maps to the given string.
///
/// @throw isc::BadValue if given a string value which does not map to an
/// enum value.
extern NameChangeFormat stringToNcrFormat(const std::string& fmt_str);

/// @brief Function which converts NameChangeFormat enums to text labels.
///
/// @param format enum value to convert to label
///
/// @return std:string containing the text label if the value is valid, or
/// "UNKNOWN" if not.
extern std::string ncrFormatToString(NameChangeFormat format);

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
    /// @param hwaddr A pointer to the object encapsulating HW address.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
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
    /// @param hwaddr A pointer to the object encapsulating HW address.
    /// @param wire_fqdn A on-wire canonical representation of the FQDN.
    void fromHWAddr(const isc::dhcp::HWAddrPtr& hwaddr,
                    const std::vector<uint8_t>& wire_fqdn);

    /// @brief Returns a reference to the DHCID byte vector.
    ///
    /// @return a reference to the vector.
    const std::vector<uint8_t>& getBytes() const {
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

    /// @brief Compares two D2Dhcids lexically
    bool operator<(const D2Dhcid& other) const {
        return (this->bytes_ < other.bytes_);
    }

private:

    /// @brief Creates the DHCID using specified identifier.
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

std::ostream&
operator<<(std::ostream& os, const D2Dhcid& dhcid);

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
/// supported is JSON detailed here isc::dhcp_ddns::NameChangeRequest::fromJSON
/// The class provides an interface such that other formats can be readily
/// supported.
class NameChangeRequest {
public:
    /// @brief Default Constructor.
    ///
    /// @todo Currently, fromWire makes use of the ability to create an empty
    /// NameChangeRequest and then builds it bit by bit.  This means that it
    /// is technically possible to create one and attempt to use in ways
    /// other than intended and its invalid content may or may not be handled
    /// gracefully by consuming code.  It might be wise to revisit this
    /// structuring such that we do not use a default constructor and only
    /// allow valid instantiations.
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
    /// @param conflict_resolution indicates whether or not conflict resolution
    /// (per RFC 4703) is enabled.
    NameChangeRequest(const NameChangeType change_type,
                      const bool forward_change, const bool reverse_change,
                      const std::string& fqdn, const std::string& ip_address,
                      const D2Dhcid& dhcid,
                      const uint64_t lease_expires_on,
                      const uint32_t lease_length,
                      const bool conflict_resolution = true);

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
    /// end. The JSON text in the buffer is NOT null-terminated.  The format
    /// is identical that described under
    /// isc::dhcp_ddns::NameChangeRequest::fromJSON
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
    /// The JSON expected is described below.  Note that a request must be
    /// enclosed within curly brackets "{..}" and that whitespace is optional
    /// (it is used in the following examples for clarity).
    ///
    /// @code
    ///     {
    ///      "change-type" : <integer>,
    ///      "forward-change" : <boolean>,
    ///      "reverse-change" : <boolean>,
    ///      "fqdn" : "<fqdn>",
    ///      "ip-address" : "<address>",
    ///      "dhcid" : "<hex_string>",
    ///      "lease-expires-on" : "<yyyymmddHHMMSS>",
    ///      "lease-length" : <secs>,
    ///      "use-conflict-resolution": <boolean>
    ///     }
    /// @endcode
    ///
    /// - change-type - indicates whether this request is to add or update
    ///   DNS entries or to remove them.  The value is an integer and is
    ///   0 for add/update and 1 for remove.
    /// - forward-change - indicates whether the forward (name to
    ///   address) DNS zone should be updated.  The value is a string
    ///   representing a boolean.  It is "true" if the zone should be updated
    ///   and "false" if not. (Unlike the keyword, the boolean value is
    ///   case-insensitive.)
    /// - reverse-change - indicates whether the reverse (address to
    ///   name) DNS zone should be updated.  The value is a string
    ///   representing a boolean.  It is "true" if the zone should be updated
    ///   and "false" if not. (Unlike the keyword, the boolean value is
    ///   case-insensitive.)
    /// - fqdn - fully qualified domain name such as "myhost.example.com.".
    ///   (Note that a trailing dot will be appended if not supplied.)
    /// - ip-address - the IPv4 or IPv6 address of the client.  The value
    ///   is a string representing the IP address (e.g. "192.168.0.1" or
    ///   "2001:db8:1::2").
    /// - dhcid - identification of the DHCP client to whom the IP address has
    ///   been leased.  The value is a string containing an even number of
    ///   hexadecimal digits without delimiters such as "2C010203040A7F8E3D"
    ///   (case insensitive).
    /// - lease-expires-on - the date and time on which the lease expires.
    ///   The value is a string of the form "yyyymmddHHMMSS" where:
    ///     - yyyy - four digit year
    ///     - mm - month of year (1-12),
    ///     - dd - day of the month (1-31),
    ///     - HH - hour of the day (0-23)
    ///     - MM - minutes of the hour (0-59)
    ///     - SS - seconds of the minute (0-59)
    /// - lease-length - the length of the lease in seconds.  This is an
    ///   integer and may range between 1 and 4294967295 (2^32 - 1) inclusive.
    /// - use-conflict-resolution - when true, follow RFC 4703 which uses
    ///   DHCID records to prohibit multiple clients from updating an FQDN
    ///
    /// Examples:
    ///
    /// Removal of an IPv4 address from the forward DNS zone only:
    ///
    /// @code
    ///  {
    ///     "change-type" : 1,
    ///     "forward-change" : true,
    ///     "reverse-change" : false,
    ///     "fqdn" : "myhost.example.com.",
    ///     "ip-address" : "192.168.2.1" ,
    ///     "dhcid" : "010203040A7F8E3D" ,
    ///     "lease-expires-on" : "20130121132405",
    ///     "lease-length" : 1300,
    ///     "use-conflict-resolution": true
    ///  }
    /// @endcode
    ///
    /// Addition of an IPv6 address to both forward and reverse DNS zones:
    ///
    /// @code
    ///  {
    ///     "change-type" : 0,
    ///     "forward-change" : true,
    ///     "reverse-change" : true,
    ///     "fqdn" : "someother.example.com.",
    ///     "ip-address" : "2001::db8:1::2",
    ///     "dhcid" : "010203040A7F8E3D" , "
    ///     "lease-expires-on" : "20130121132405",
    ///     "lease-length" : 27400,
    ///     "use-conflict-resolution": true
    ///   }
    /// @endcode
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

    /// @brief Fetches the request IP address string.
    ///
    /// @return a string containing the IP address
    std::string getIpAddress() const {
        return (ip_io_address_.toText());
    }

    /// @brief Fetches the request IP address as an IOAddress.
    ///
    /// @return a asiolink::IOAddress containing the IP address
    const asiolink::IOAddress& getIpIoAddress() const {
        return (ip_io_address_);
    }

    /// @brief Returns true if the lease address is a IPv4 lease.
    ///
    /// @return boolean true if the lease address family is AF_INET.
    bool isV4 () const {
        return (ip_io_address_.isV4());
    }

    /// @brief Returns true if the lease address is a IPv6 lease.
    ///
    /// @return boolean true if the lease address family is AF_INET6.
    bool isV6 () const {
        return (ip_io_address_.isV6());
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

    /// @brief Fetches the request ID.
    ///
    /// @todo Currently this is the DHCID, in the future we may add a unique ID per
    /// request to allow for correlating messages and events between the DHCP servers
    /// and the D2 server.  If we do that we shall also need to add or update other
    /// functions to: set the request ID, add it to the JSON strings, etc.  The
    /// primary purpose of this function is to provide a consistent way to identify
    /// requests for logging purposes.
    ///
    /// @return a string with the request's request ID (currently DHCID)
    std::string getRequestId() const {
        return (dhcid_.toStr());
    }

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

    /// @brief Checks if conflict resolution is enabled
    ///
    /// @return a true if the conflict resolution is enabled.
    bool useConflictResolution() const {
        return (conflict_resolution_);
    }

    /// @brief Sets the conflict resolution flag to the given value.
    ///
    /// @param value contains the new value to assign to the conflict
    /// resolution flag
    void setConflictResolution(const bool value);

    /// @brief Sets the conflict resolution flag to the value of the given Element.
    ///
    /// @param element is a boolean Element containing the conflict resolution flag
    /// value.
    ///
    /// @throw NcrMessageError if the element is not a boolean
    /// Element
    void setConflictResolution(isc::data::ConstElementPtr element);

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

    bool operator == (const NameChangeRequest& b) const;
    bool operator != (const NameChangeRequest& b) const;

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

    /// @brief The ip address leased to the FQDN as an IOAddress.
    ///
    /// The lease address is used in many places, sometimes as a string
    /// and sometimes as an IOAddress.  To avoid converting back and forth
    /// continually over the life span of an NCR, we do it once when the
    /// ip address is actually set.
    asiolink::IOAddress ip_io_address_;

    /// @brief The lease client's unique DHCID.
    /// @todo Currently, this is uses D2Dhcid it but may be replaced with
    /// dns::DHCID which provides additional validation.
    D2Dhcid dhcid_;

    /// @brief The date-time the lease expires.
    uint64_t lease_expires_on_;

    /// @brief The amount of time in seconds for which the lease is valid (TTL).
    uint32_t lease_length_;

    /// @brief Indicates if conflict resolution is enabled.
    bool conflict_resolution_;

    /// @brief The processing status of the request.  Used internally.
    NameChangeStatus status_;
};


}; // end of isc::dhcp_ddns namespace
}; // end of isc namespace

#endif
