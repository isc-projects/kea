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

#include <d2/ncr_msg.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

#include <sstream>

namespace isc {
namespace d2 {

using namespace boost::posix_time;

/********************************* D2Dhcid ************************************/

D2Dhcid::D2Dhcid() {
}

D2Dhcid::~D2Dhcid() {
}

D2Dhcid::D2Dhcid(const std::string& data) {
    fromStr(data);
}

void
D2Dhcid::fromStr(const std::string& data) {
    const char* buf = data.c_str();
    size_t len = data.size();

    // String can't be empty and must be an even number of characters.
    if (len == 0 || ((len % 2) > 0)) {
        isc_throw(NcrMessageError,
            "String to byte conversion, invalid data length: " << len);
    }

    // Iterate over the string of character "digits", combining each pair
    // into an unsigned byte and then add the byte to our byte vector.
    // This implementation may seem verbose but it is very quick and more
    // importantly provides data validation.
    bytes_.clear();
    for (int i = 0; i < len; i++) {
        char ch = buf[i++];
        if (ch >= 0x30 && ch <= 0x39) {
            // '0' to '9'
            ch -= 0x30;
        } else if (ch >= 0x41 && ch <= 0x46) {
            // 'A' to 'F'
            ch -= 0x37;
        } else {
            // Not a digit, so throw an error.
            isc_throw(NcrMessageError, "Invalid data in Dhcid");
        }

        // Set the upper nibble digit.
        uint8_t byte = ch  << 4;

        ch = buf[i];
        if (ch >= 0x30 && ch <= 0x39) {
            // '0' to '9'
            ch -= 0x30;
        } else if (ch >= 0x41 && ch <= 0x46) {
            // 'A' to 'F'
            ch -= 0x37;
        } else {
            // Not a digit, so throw an error.
            isc_throw(NcrMessageError, "Invalid data in Dhcid");
        }

        // "OR" in the lower nibble digit.
        byte |= ch;

        // Add the new byte to the end of the vector.
        bytes_.push_back(byte);
    }
}

std::string
D2Dhcid::toStr() const {
    int len = bytes_.size();
    char tmp[len+1];
    char* chptr = tmp;
    unsigned char* bptr = const_cast<unsigned char*>(bytes_.data());

    // Iterate over the vector of bytes, converting them into a contiguous
    // string of ASCII hexadecimal digits, '0' - '9' and 'A' to 'F'.
    // Each byte is split into a pair of digits.
    for (int i = 0; i < len; i++) {
        uint8_t byte = *bptr++;
        char ch = (byte >> 4);
        // Turn upper nibble into a digit and append it to char buf.
        ch += (ch < 0x0A ? 0x30 : 0x37);
        *chptr++ = ch;
        // Turn lower nibble into a digit and append it to char buf.
        ch = (byte & 0x0F);
        ch += (ch < 0x0A ? 0x30 : 0x37);
        *chptr++ = ch;
    }

    // Null terminate it.
    *chptr = 0x0;

    return (std::string(tmp));

}


/**************************** NameChangeRequest ******************************/

NameChangeRequest::NameChangeRequest()
    : change_type_(chgAdd), forward_change_(false),
    reverse_change_(false), fqdn_(""), ip_address_(""),
    dhcid_(), lease_expires_on_(), lease_length_(0), status_(stNew) {
}

NameChangeRequest::NameChangeRequest(NameChangeType change_type,
            bool forward_change, bool reverse_change,
            const std::string& fqdn, const std::string & ip_address,
            const D2Dhcid& dhcid, const ptime& lease_expires_on,
            uint32_t lease_length)
    : change_type_(change_type), forward_change_(forward_change),
    reverse_change_(reverse_change), fqdn_(fqdn), ip_address_(ip_address),
    dhcid_(dhcid), lease_expires_on_(new ptime(lease_expires_on)),
    lease_length_(lease_length), status_(stNew) {

    // Validate the contents. This will throw a NcrMessageError if anything
    // is invalid.
    validateContent();
}

NameChangeRequest::~NameChangeRequest() {
}

NameChangeRequestPtr
NameChangeRequest::fromFormat(NameChangeFormat format,
                              isc::util::InputBuffer& buffer) {
    // Based on the format requested, pull the marshalled request from
    // InputBuffer and pass it into the appropriate format-specific factory.
    NameChangeRequestPtr ncr;
    switch (format)
    {
    case fmtJSON: {
        try {
            // Get the length of the JSON text and create a char buf large
            // enough to hold it + 1.
            size_t len = buffer.readUint16();
            char string_data[len+1];

            // Read len bytes of data from the InputBuffer into local char buf
            // and then NULL terminate it.
            buffer.readData(&string_data, len);
            string_data[len] = 0x0;

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
NameChangeRequest::toFormat(NameChangeFormat format,
                            isc::util::OutputBuffer& buffer) {
    // Based on the format requested, invoke the appropriate format handler
    // which will marshal this request's contents into the OutputBuffer.
    switch (format)
    {
    case fmtJSON: {
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
    element = ncr->getElement("change_type", element_map);
    ncr->setChangeType(element);

    element = ncr->getElement("forward_change", element_map);
    ncr->setForwardChange(element);

    element = ncr->getElement("reverse_change", element_map);
    ncr->setReverseChange(element);

    element = ncr->getElement("fqdn", element_map);
    ncr->setFqdn(element);

    element = ncr->getElement("ip_address", element_map);
    ncr->setIpAddress(element);

    element = ncr->getElement("dhcid", element_map);
    ncr->setDhcid(element);

    element = ncr->getElement("lease_expires_on", element_map);
    ncr->setLeaseExpiresOn(element);

    element = ncr->getElement("lease_length", element_map);
    ncr->setLeaseLength(element);

    // All members were in the Element set and were correct lexically. Now
    // validate the overall content semantically.  This will throw an
    // NcrMessageError if anything is amiss.
    ncr->validateContent();

    // Everything is valid, return the new instance.
    return (ncr);
}

std::string
NameChangeRequest::toJSON() {
    // Create a JSON string of this request's contents.  Note that this method
    // does NOT use the isc::data library as generating the output is straight
    // forward.
    std::ostringstream stream;

    stream << "{\"change_type\":" << change_type_ << ","
        << "\"forward_change\":"
        << (forward_change_ ? "true" : "false") << ","
        << "\"reverse_change\":"
        << (reverse_change_ ? "true" : "false") << ","
        << "\"fqdn\":\"" << fqdn_ << "\","
        << "\"ip_address\":\"" << ip_address_ << "\","
        << "\"dhcid\":\"" << dhcid_.toStr() << "\","
        << "\"lease_expires_on\":\""  << getLeaseExpiresOnStr() << "\","
        << "\"lease_length\":" << lease_length_ << "}";

    return (stream.str());
}


void
NameChangeRequest::validateContent() {
    // Validate FQDN.
    if (fqdn_ == "") {
        isc_throw(NcrMessageError, "FQDN cannot be blank");
    }

    // Validate IP Address.
    try {
        isc::asiolink::IOAddress io_addr(ip_address_);
    } catch (const isc::asiolink::IOError& ex) {
        isc_throw(NcrMessageError,
                  "Invalid ip address string for ip_address: " << ip_address_);
    }

    // Validate the DHCID.
    if (dhcid_.getBytes().size()  == 0) {
        isc_throw(NcrMessageError, "DHCID cannot be blank");
    }

    // Validate lease expiration.
    if (lease_expires_on_->is_not_a_date_time()) {
        isc_throw(NcrMessageError, "Invalid value for lease_expires_on");
    }

    // Ensure the request specifies at least one direction to update.
    if (!forward_change_ && !reverse_change_) {
        isc_throw(NcrMessageError,
                  "Invalid Request, forward and reverse flags are both false");
    }
}

isc::data::ConstElementPtr
NameChangeRequest::getElement(const std::string& name,
                              const ElementMap& element_map) {
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
NameChangeRequest::setChangeType(NameChangeType value) {
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

    if (raw_value != chgAdd && raw_value != chgRemove) {
        // Value is not a valid change type.
        isc_throw(NcrMessageError,
                  "Invalid data value for change_type: " << raw_value);
    }

    // Good to go, make the assignment.
    setChangeType(static_cast<NameChangeType>(raw_value));
}

void
NameChangeRequest::setForwardChange(bool value) {
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
                  "Wrong data type for forward_change :" << ex.what());
    }

    // Good to go, make the assignment.
    setForwardChange(value);
}

void
NameChangeRequest::setReverseChange(bool value) {
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
                  "Wrong data type for reverse_change :" << ex.what());
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
    fqdn_ = value;
}

void
NameChangeRequest::setIpAddress(const std::string& value) {
    ip_address_ = value;
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
    if (!lease_expires_on_) {
        // This is a programmatic error, should not happen.
        isc_throw(NcrMessageError,
            "lease_expires_on_ is null, cannot convert to string");
    }

    // Return the ISO date-time string for the value of lease_expires_on_.
    return (to_iso_string(*lease_expires_on_));
}

void NameChangeRequest::setLeaseExpiresOn(const std::string&  value) {
    try {
        // Create a new ptime instance from the ISO date-time string in value
        // add assign it to lease_expires_on_.
        ptime* tptr = new ptime(from_iso_string(value));
        lease_expires_on_.reset(tptr);
    } catch(...) {
        // We were given an invalid string, so throw.
        isc_throw(NcrMessageError,
            "Invalid ISO date-time string: [" << value << "]");
    }

}

void NameChangeRequest::setLeaseExpiresOn(const ptime&  value) {
    if (lease_expires_on_->is_not_a_date_time()) {
        isc_throw(NcrMessageError, "Invalid value for lease_expires_on");
    }

    // Go to go, make the assignment.
    lease_expires_on_.reset(new ptime(value));
}

void NameChangeRequest::setLeaseExpiresOn(isc::data::ConstElementPtr element) {
    // Pull out the string value and pass it into the string setter.
    setLeaseExpiresOn(element->stringValue());
}

void
NameChangeRequest::setLeaseLength(uint32_t value) {
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
NameChangeRequest::setStatus(NameChangeStatus value) {
    status_ = value;
}

std::string
NameChangeRequest::toText() const {
    std::ostringstream stream;

    stream << "Type: " << static_cast<int>(change_type_) << " (";
    switch (change_type_) {
        case chgAdd:
            stream << "chgAdd)\n";
            break;
        case chgRemove:
            stream << "chgRemove)\n";
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
           << "IP Address: [" << ip_address_  << "]" << std::endl
           << "DHCID: [" << dhcid_.toStr() << "]" << std::endl
           << "Lease Expires On: " << getLeaseExpiresOnStr() << std::endl
           << "Lease Length: " << lease_length_ << std::endl;

    return (stream.str());
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
