// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp_ddns/ncr_msg.h>
#include <dns/name.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <boost/algorithm/string/predicate.hpp>

#include <sstream>
#include <limits>


namespace isc {
namespace dhcp_ddns {


NameChangeFormat stringToNcrFormat(const std::string& fmt_str) {
    if (boost::iequals(fmt_str, "JSON")) {
        return FMT_JSON;
    }

    isc_throw(BadValue, "Invalid NameChangeRequest format: " << fmt_str);
}


std::string ncrFormatToString(NameChangeFormat format) {
    if (format == FMT_JSON) {
        return ("JSON");
    }

    std::ostringstream stream;
    stream  << "UNKNOWN(" << format << ")";
    return (stream.str());
}

/********************************* D2Dhcid ************************************/

namespace {

///
/// @name Constants which define DHCID identifier-type
//@{
/// DHCID created from client's HW address.
const uint8_t DHCID_ID_HWADDR   = 0x0;
/// DHCID created from client identifier.
const uint8_t DHCID_ID_CLIENTID = 0x1;
/// DHCID created from DUID.
const uint8_t DHCID_ID_DUID     = 0x2;

}

D2Dhcid::D2Dhcid() {
}

D2Dhcid::D2Dhcid(const std::string& data) {
    fromStr(data);
}

D2Dhcid::D2Dhcid(const isc::dhcp::HWAddrPtr& hwaddr,
                 const std::vector<uint8_t>& wire_fqdn) {
    fromHWAddr(hwaddr, wire_fqdn);
}

D2Dhcid::D2Dhcid(const std::vector<uint8_t>& clientid_data,
                 const std::vector<uint8_t>& wire_fqdn) {
    fromClientId(clientid_data, wire_fqdn);
}

D2Dhcid::D2Dhcid(const isc::dhcp::DUID& duid,
                 const std::vector<uint8_t>& wire_fqdn) {
    fromDUID(duid, wire_fqdn);
}


void
D2Dhcid::fromStr(const std::string& data) {
    bytes_.clear();
    try {
        isc::util::encode::decodeHex(data, bytes_);
    } catch (const isc::Exception& ex) {
        isc_throw(NcrMessageError, "Invalid data in Dhcid: " << ex.what());
    }
}

std::string
D2Dhcid::toStr() const {
    return (isc::util::encode::encodeHex(bytes_));
}

void
D2Dhcid::fromClientId(const std::vector<uint8_t>& clientid_data,
                      const std::vector<uint8_t>& wire_fqdn) {
    createDigest(DHCID_ID_CLIENTID, clientid_data, wire_fqdn);
}

void
D2Dhcid::fromHWAddr(const isc::dhcp::HWAddrPtr& hwaddr,
                    const std::vector<uint8_t>& wire_fqdn) {
    if (!hwaddr) {
        isc_throw(isc::dhcp_ddns::DhcidRdataComputeError,
                  "unable to compute DHCID from the HW address, "
                  "NULL pointer has been specified");
    } else if (hwaddr->hwaddr_.empty()) {
        isc_throw(isc::dhcp_ddns::DhcidRdataComputeError,
                  "unable to compute DHCID from the HW address, "
                  "HW address is empty");
    }
    std::vector<uint8_t> hwaddr_data;
    hwaddr_data.push_back(hwaddr->htype_);
    hwaddr_data.insert(hwaddr_data.end(), hwaddr->hwaddr_.begin(),
                       hwaddr->hwaddr_.end());
    createDigest(DHCID_ID_HWADDR, hwaddr_data, wire_fqdn);
}


void
D2Dhcid::fromDUID(const isc::dhcp::DUID& duid,
                  const std::vector<uint8_t>& wire_fqdn) {

    createDigest(DHCID_ID_DUID, duid.getDuid(), wire_fqdn);
}

void
D2Dhcid::createDigest(const uint8_t identifier_type,
                      const std::vector<uint8_t>& identifier_data,
                      const std::vector<uint8_t>& wire_fqdn) {
    // We get FQDN in the wire format, so we don't know if it is
    // valid. It is caller's responsibility to make sure it is in
    // the valid format. Here we just make sure it is not empty.
    if (wire_fqdn.empty()) {
        isc_throw(isc::dhcp_ddns::DhcidRdataComputeError,
                  "empty FQDN used to create DHCID");
    }

    // It is a responsibility of the classes which encapsulate client
    // identifiers, e.g. DUID, to validate the client identifier data.
    // But let's be on the safe side and at least check that it is not
    // empty.
    if (identifier_data.empty()) {
        isc_throw(isc::dhcp_ddns::DhcidRdataComputeError,
                  "empty DUID used to create DHCID");
    }

    // A data buffer will be used to compute the digest.
    std::vector<uint8_t> data = identifier_data;

    // Append FQDN in the wire format.
    data.insert(data.end(), wire_fqdn.begin(), wire_fqdn.end());

    // Use the DUID and FQDN to compute the digest (see RFC4701, section 3).

    isc::util::OutputBuffer hash(0);
    try {
        // We have checked already that the DUID and FQDN aren't empty
        // so it is safe to assume that the data buffer is not empty.
        cryptolink::digest(&data[0], data.size(), cryptolink::SHA256, hash);
    } catch (const std::exception& ex) {
        isc_throw(isc::dhcp_ddns::DhcidRdataComputeError,
                  "error while generating DHCID from DUID: "
                  << ex.what());
    }

    // The DHCID RDATA has the following structure:
    //
    //    < identifier-type > < digest-type > < digest >
    //
    // where identifier type

    // Let's allocate the space for the identifier-type (2 bytes) and
    // digest-type (1 byte). This is 3 bytes all together.
    bytes_.resize(3 + hash.getLength());
    // Leave first byte 0 and set the second byte. Those two bytes
    // form the identifier-type.
    bytes_[1] = identifier_type;
    // Third byte is always equal to 1, which specifies SHA-256 digest type.
    bytes_[2] = 1;
    // Now let's append the digest.
    std::memcpy(&bytes_[3], hash.getData(), hash.getLength());
}

std::ostream&
operator<<(std::ostream& os, const D2Dhcid& dhcid) {
    os << dhcid.toStr();
    return (os);
}



/**************************** NameChangeRequest ******************************/

NameChangeRequest::NameChangeRequest()
    : change_type_(CHG_ADD), forward_change_(false),
    reverse_change_(false), fqdn_(""), ip_io_address_("0.0.0.0"),
    dhcid_(), lease_expires_on_(), lease_length_(0), status_(ST_NEW) {
}

NameChangeRequest::NameChangeRequest(const NameChangeType change_type,
            const bool forward_change, const bool reverse_change,
            const std::string& fqdn, const std::string& ip_address,
            const D2Dhcid& dhcid,
            const uint64_t lease_expires_on,
            const uint32_t lease_length)
    : change_type_(change_type), forward_change_(forward_change),
    reverse_change_(reverse_change), fqdn_(fqdn), ip_io_address_("0.0.0.0"),
    dhcid_(dhcid), lease_expires_on_(lease_expires_on),
    lease_length_(lease_length), status_(ST_NEW) {

    // User setter to validate fqdn.
    setFqdn(fqdn);

    // User setter to validate address.
    setIpAddress(ip_address);

    // Validate the contents. This will throw a NcrMessageError if anything
    // is invalid.
    validateContent();
}

NameChangeRequestPtr
NameChangeRequest::fromFormat(const NameChangeFormat format,
                              isc::util::InputBuffer& buffer) {
    // Based on the format requested, pull the marshalled request from
    // InputBuffer and pass it into the appropriate format-specific factory.
    NameChangeRequestPtr ncr;
    switch (format) {
    case FMT_JSON: {
        try {
            // Get the length of the JSON text.
            size_t len = buffer.readUint16();

            // Read the text from the buffer into a vector.
            std::vector<uint8_t> vec;
            buffer.readVector(vec, len);

            // Turn the vector into a string.
            std::string string_data(vec.begin(), vec.end());

            // Pass the string of JSON text into JSON factory to create the
            // NameChangeRequest instance.  Note the factory may throw
            // NcrMessageError.
            ncr = NameChangeRequest::fromJSON(string_data);
        } catch (isc::util::InvalidBufferPosition& ex) {
            // Read error accessing data in InputBuffer.
            isc_throw(NcrMessageError, "fromFormat: buffer read error: "
                      << ex.what());
        }

        break;
        }
    default:
        // Programmatic error, shouldn't happen.
        isc_throw(NcrMessageError, "fromFormat - invalid format");
        break;
    }

    return (ncr);
}

void
NameChangeRequest::toFormat(const NameChangeFormat format,
                            isc::util::OutputBuffer& buffer) const {
    // Based on the format requested, invoke the appropriate format handler
    // which will marshal this request's contents into the OutputBuffer.
    switch (format) {
    case FMT_JSON: {
        // Invoke toJSON to create a JSON text of this request's contents.
        std::string json = toJSON();
        uint16_t length = json.size();

        // Write the length of the JSON text to the OutputBuffer first, then
        // write the JSON text itself.
        buffer.writeUint16(length);
        buffer.writeData(json.c_str(), length);
        break;
        }
    default:
        // Programmatic error, shouldn't happen.
        isc_throw(NcrMessageError, "toFormat - invalid format");
        break;
    }
}

NameChangeRequestPtr
NameChangeRequest::fromJSON(const std::string& json) {
    // This method leverages the existing JSON parsing provided by isc::data
    // library.  Should this prove to be a performance issue, it may be that
    // lighter weight solution would be appropriate.

    // Turn the string of JSON text into an Element set.
    isc::data::ElementPtr elements;
    try {
        elements = isc::data::Element::fromJSON(json);
    } catch (isc::data::JSONError& ex) {
        isc_throw(NcrMessageError,
                  "Malformed NameChangeRequest JSON: " << ex.what());
    }

    // Get a map of the Elements, keyed by element name.
    ElementMap element_map = elements->mapValue();
    isc::data::ConstElementPtr element;

    // Use default constructor to create a "blank" NameChangeRequest.
    NameChangeRequestPtr ncr(new NameChangeRequest());

    // For each member of NameChangeRequest, find its element in the map and
    // call the appropriate Element-based setter.  These setters may throw
    // NcrMessageError if the given Element is the wrong type or its data
    // content is lexically invalid.   If the element is NOT found in the
    // map, getElement will throw NcrMessageError indicating the missing
    // member. Currently there are no optional values.
    element = ncr->getElement("change-type", element_map);
    ncr->setChangeType(element);

    element = ncr->getElement("forward-change", element_map);
    ncr->setForwardChange(element);

    element = ncr->getElement("reverse-change", element_map);
    ncr->setReverseChange(element);

    element = ncr->getElement("fqdn", element_map);
    ncr->setFqdn(element);

    element = ncr->getElement("ip-address", element_map);
    ncr->setIpAddress(element);

    element = ncr->getElement("dhcid", element_map);
    ncr->setDhcid(element);

    element = ncr->getElement("lease-expires-on", element_map);
    ncr->setLeaseExpiresOn(element);

    element = ncr->getElement("lease-length", element_map);
    ncr->setLeaseLength(element);

    // All members were in the Element set and were correct lexically. Now
    // validate the overall content semantically.  This will throw an
    // NcrMessageError if anything is amiss.
    ncr->validateContent();

    // Everything is valid, return the new instance.
    return (ncr);
}

std::string
NameChangeRequest::toJSON() const  {
    // Create a JSON string of this request's contents.  Note that this method
    // does NOT use the isc::data library as generating the output is straight
    // forward.
    std::ostringstream stream;

    stream << "{\"change-type\":" << getChangeType() << ","
        << "\"forward-change\":"
        << (isForwardChange() ? "true" : "false") << ","
        << "\"reverse-change\":"
        << (isReverseChange() ? "true" : "false") << ","
        << "\"fqdn\":\"" << getFqdn() << "\","
        << "\"ip-address\":\"" << getIpAddress() << "\","
        << "\"dhcid\":\"" << getDhcid().toStr() << "\","
        << "\"lease-expires-on\":\""  << getLeaseExpiresOnStr() << "\","
        << "\"lease-length\":" << getLeaseLength() << "}";

    return (stream.str());
}


void
NameChangeRequest::validateContent() {
    //@todo This is an initial implementation which provides a minimal amount
    // of validation.  FQDN and DHCID members are all currently
    // strings, these may be replaced with richer classes.
    if (fqdn_ == "") {
        isc_throw(NcrMessageError, "FQDN cannot be blank");
    }

    // Validate the DHCID.
    if (dhcid_.getBytes().size()  == 0) {
        isc_throw(NcrMessageError, "DHCID cannot be blank");
    }

    // Ensure the request specifies at least one direction to update.
    if (!forward_change_ && !reverse_change_) {
        isc_throw(NcrMessageError,
                  "Invalid Request, forward and reverse flags are both false");
    }
}

isc::data::ConstElementPtr
NameChangeRequest::getElement(const std::string& name,
                              const ElementMap& element_map) const {
    // Look for "name" in the element map.
    ElementMap::const_iterator it = element_map.find(name);
    if (it == element_map.end()) {
        // Didn't find the element, so throw.
        isc_throw(NcrMessageError,
                  "NameChangeRequest value missing for: " << name );
    }

    // Found the element, return it.
    return (it->second);
}

void
NameChangeRequest::setChangeType(const NameChangeType value) {
    change_type_ = value;
}


void
NameChangeRequest::setChangeType(isc::data::ConstElementPtr element) {
    long raw_value = -1;
    try {
        // Get the element's integer value.
        raw_value = element->intValue();
    } catch (isc::data::TypeError& ex) {
        // We expect a integer Element type, don't have one.
        isc_throw(NcrMessageError,
                  "Wrong data type for change_type: " << ex.what());
    }

    if ((raw_value != CHG_ADD) && (raw_value != CHG_REMOVE)) {
        // Value is not a valid change type.
        isc_throw(NcrMessageError,
                  "Invalid data value for change_type: " << raw_value);
    }

    // Good to go, make the assignment.
    setChangeType(static_cast<NameChangeType>(raw_value));
}

void
NameChangeRequest::setForwardChange(const bool value) {
    forward_change_ = value;
}

void
NameChangeRequest::setForwardChange(isc::data::ConstElementPtr element) {
    bool value;
    try {
        // Get the element's boolean value.
        value = element->boolValue();
    } catch (isc::data::TypeError& ex) {
        // We expect a boolean Element type, don't have one.
        isc_throw(NcrMessageError,
                  "Wrong data type for forward-change: " << ex.what());
    }

    // Good to go, make the assignment.
    setForwardChange(value);
}

void
NameChangeRequest::setReverseChange(const bool value) {
    reverse_change_ = value;
}

void
NameChangeRequest::setReverseChange(isc::data::ConstElementPtr element) {
    bool value;
    try {
        // Get the element's boolean value.
        value = element->boolValue();
    } catch (isc::data::TypeError& ex) {
        // We expect a boolean Element type, don't have one.
        isc_throw(NcrMessageError,
                  "Wrong data type for reverse_change: " << ex.what());
    }

    // Good to go, make the assignment.
    setReverseChange(value);
}


void
NameChangeRequest::setFqdn(isc::data::ConstElementPtr element) {
    setFqdn(element->stringValue());
}

void
NameChangeRequest::setFqdn(const std::string& value) {
    try {
        dns::Name tmp(value);
        fqdn_ = tmp.toText();
    } catch (const std::exception& ex) {
        isc_throw(NcrMessageError,
                  "Invalid FQDN value: " << value << ", reason: "
                  << ex.what());
    }
}

void
NameChangeRequest::setIpAddress(const std::string& value) {
    // Validate IP Address.
    try {
        ip_io_address_ = isc::asiolink::IOAddress(value);
    } catch (const isc::asiolink::IOError&) {
        isc_throw(NcrMessageError,
                  "Invalid ip address string for ip_address: " << value);
    }
}

void
NameChangeRequest::setIpAddress(isc::data::ConstElementPtr element) {
    setIpAddress(element->stringValue());
}


void
NameChangeRequest::setDhcid(const std::string& value) {
    dhcid_.fromStr(value);
}

void
NameChangeRequest::setDhcid(isc::data::ConstElementPtr element) {
    setDhcid(element->stringValue());
}

std::string
NameChangeRequest::getLeaseExpiresOnStr() const {
    return (isc::util::timeToText64(lease_expires_on_));
}

void
NameChangeRequest::setLeaseExpiresOn(const std::string&  value) {
    try {
        lease_expires_on_ = isc::util::timeFromText64(value);
    } catch(...) {
        // We were given an invalid string, so throw.
        isc_throw(NcrMessageError,
            "Invalid date-time string: [" << value << "]");
    }

}

void NameChangeRequest::setLeaseExpiresOn(isc::data::ConstElementPtr element) {
    // Pull out the string value and pass it into the string setter.
    setLeaseExpiresOn(element->stringValue());
}

void
NameChangeRequest::setLeaseLength(const uint32_t value) {
    lease_length_ = value;
}

void
NameChangeRequest::setLeaseLength(isc::data::ConstElementPtr element) {
    long value = -1;
    try {
        // Get the element's integer value.
        value = element->intValue();
    } catch (isc::data::TypeError& ex) {
        // We expect a integer Element type, don't have one.
        isc_throw(NcrMessageError,
                  "Wrong data type for lease_length: " << ex.what());
    }

    // Make sure we the range is correct and value is positive.
    if (value > std::numeric_limits<uint32_t>::max()) {
        isc_throw(NcrMessageError, "lease_length value " << value <<
                "is too large for unsigned 32-bit integer.");
    }
    if (value < 0) {
        isc_throw(NcrMessageError, "lease_length value " << value <<
             "is negative.  It must greater than or equal to zero ");
    }

    // Good to go, make the assignment.
    setLeaseLength(static_cast<uint32_t>(value));
}

void
NameChangeRequest::setStatus(const NameChangeStatus value) {
    status_ = value;
}

std::string
NameChangeRequest::toText() const {
    std::ostringstream stream;

    stream << "Type: " << static_cast<int>(change_type_) << " (";
    switch (change_type_) {
    case CHG_ADD:
        stream << "CHG_ADD)\n";
        break;
    case CHG_REMOVE:
        stream << "CHG_REMOVE)\n";
        break;
    default:
        // Shouldn't be possible.
        stream << "Invalid Value\n";
    }

    stream << "Forward Change: " << (forward_change_ ? "yes" : "no")
           << std::endl
           << "Reverse Change: " << (reverse_change_ ? "yes" : "no")
           << std::endl
           << "FQDN: [" << fqdn_ << "]" << std::endl
           << "IP Address: [" << ip_io_address_ << "]" << std::endl
           << "DHCID: [" << dhcid_.toStr() << "]" << std::endl
           << "Lease Expires On: " << getLeaseExpiresOnStr() << std::endl
           << "Lease Length: " << lease_length_ << std::endl;

    return (stream.str());
}

bool
NameChangeRequest::operator == (const NameChangeRequest& other) {
    return ((change_type_ == other.change_type_) &&
            (forward_change_ == other.forward_change_) &&
            (reverse_change_ == other.reverse_change_) &&
            (fqdn_ == other.fqdn_) &&
            (ip_io_address_ == other.ip_io_address_) &&
            (dhcid_ == other.dhcid_) &&
            (lease_expires_on_ == other.lease_expires_on_) &&
            (lease_length_ == other.lease_length_));
}

bool
NameChangeRequest::operator != (const NameChangeRequest& other) {
    return (!(*this == other));
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
