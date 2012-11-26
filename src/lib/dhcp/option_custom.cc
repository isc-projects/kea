// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/libdhcp++.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_custom.h>

namespace isc {
namespace dhcp {

OptionCustom::OptionCustom(const OptionDefinition& def,
                             Universe u,
                             const OptionBuffer& data)
    : Option(u, def.getCode(), data.begin(), data.end()),
      definition_(def),
      init_passed_(true) {
    try {
        createBuffers();
    } catch (const Exception& ex) {
        init_passed_ = false;
    }
}

OptionCustom::OptionCustom(const OptionDefinition& def,
                             Universe u,
                             OptionBufferConstIter first,
                             OptionBufferConstIter last)
    : Option(u, def.getCode(), first, last),
      definition_(def),
      init_passed_(true) {
    try {
        createBuffers();
    } catch (const Exception& ex) {
        init_passed_ = false;
    }
}

void
OptionCustom::checkIndex(const uint32_t index) const {
    if (index >= buffers_.size()) {
        isc_throw(isc::OutOfRange, "specified data field index " << index
                  << " is out of rangex.");
    }
}

void
OptionCustom::createBuffers() {
    // Check that the option definition is correct as we are going
    // to use it to split the data_ buffer into set of sub buffers.
    definition_.validate();

    // @todo create buffers here
}

void
OptionCustom::pack4(isc::util::OutputBuffer& buf) {
    if (len() > 255) {
        isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big."
                  << " At most 255 bytes are supported.");
    }

    buf.writeUint8(type_);
    buf.writeUint8(len() - getHeaderLen());

    // @todo write option data here

    LibDHCP::packOptions(buf, options_);
    return;
}

void
OptionCustom::pack6(isc::util::OutputBuffer& buf) {
    buf.writeUint16(type_);
    buf.writeUint16(len() - getHeaderLen());

    // @todo write option data here.

    LibDHCP::packOptions(buf, options_);
    return;
}

void
OptionCustom::readAddress(const uint32_t index, asiolink::IOAddress& address) const {
    checkIndex(index);
    if (buffers_[index].size() == asiolink::V4ADDRESS_LEN) {
        OptionDataTypeUtil::readAddress(buffers_[index], AF_INET, address);
    } else if (buffers_[index].size() == asiolink::V6ADDRESS_LEN) {
        OptionDataTypeUtil::readAddress(buffers_[index], AF_INET6, address);
    } else {
        isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                  << " IP address. Invalid buffer length " << buffers_[index].size());
    }
}

bool
OptionCustom::readBoolean(const uint32_t index) const {
    checkIndex(index);
    return (OptionDataTypeUtil::readBool(buffers_[index]));
}

void
OptionCustom::readString(const uint32_t index, std::string& value) const {
    checkIndex(index);
    OptionDataTypeUtil::readString(buffers_[index], value);
}

void
OptionCustom::unpack(OptionBufferConstIter begin,
                           OptionBufferConstIter end) {
    data_ = OptionBuffer(begin, end);
}

uint16_t
OptionCustom::len() {
    // Returns length of the complete option (data length + DHCPv4/DHCPv6
    // option header)

    // length of the whole option is header and data stored in this option...
    int length = getHeaderLen() + data_.size();

    // ... and sum of lengths of all suboptions
    for (OptionCustom::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    // note that this is not equal to lenght field. This value denotes
    // number of bytes required to store this option. length option should
    // contain (len()-getHeaderLen()) value.
    return (length);
}

bool
OptionCustom::valid() {
    if ((universe_ != V4 && universe_ != V6) ||
        !init_passed_) {
        return (false);
    }

    return (true);
}

std::string OptionCustom::toText(int /* =0 */ ) {
    std::stringstream tmp;

    /*    for (int i = 0; i < indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << ", len=" << len()-getHeaderLen() << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            tmp << ":";
        }
        tmp << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    // print suboptions
    for (OptionCollection::const_iterator opt = options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
        } */
    return tmp.str();
}

void OptionCustom::setData(const OptionBufferConstIter first,
                     const OptionBufferConstIter last) {
    // We will copy entire option buffer, so we have to resize data_.
    data_.resize(std::distance(first, last));
    std::copy(first, last, data_.begin());
}

} // end of isc::dhcp namespace
} // end of isc namespace
