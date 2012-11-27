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
      definition_(def) {
    createBuffers();
}

OptionCustom::OptionCustom(const OptionDefinition& def,
                             Universe u,
                             OptionBufferConstIter first,
                             OptionBufferConstIter last)
    : Option(u, def.getCode(), first, last),
      definition_(def) {
    createBuffers();
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

    std::vector<OptionBuffer> buffers;
    OptionBuffer::iterator data = data_.begin();
    if (definition_.getType() == OPT_RECORD_TYPE) {
        const OptionDefinition::RecordFieldsCollection& fields =
            definition_.getRecordFields();
        for (OptionDefinition::RecordFieldsConstIter field = fields.begin();
             field != fields.end(); ++field) {
            int data_size = OptionDataTypeUtil::getDataTypeLen(*field);
            if (data_size == 0) {
                if (*field == OPT_IPV4_ADDRESS_TYPE) {
                    data_size = asiolink::V4ADDRESS_LEN;
                } else if (*field == OPT_IPV6_ADDRESS_TYPE) {
                    data_size = asiolink::V6ADDRESS_LEN;
                } else {
                    data_size = std::distance(data, data_.end());
                }
            }
            if (data_size == 0) {
                isc_throw(OutOfRange, "option buffer truncated");
            }
            buffers.push_back(OptionBuffer(data, data + data_size));
            data += data_size;
        }
    } else {
        OptionDataType data_type = definition_.getType();
        int data_size = OptionDataTypeUtil::getDataTypeLen(data_type);
        if (data_size == 0) {
            if (data_type == OPT_IPV4_ADDRESS_TYPE) {
                data_size = asiolink::V4ADDRESS_LEN;
            } else if (data_type == OPT_IPV6_ADDRESS_TYPE) {
                data_size = asiolink::V6ADDRESS_LEN;
            }
        }
        if (std::distance(data, data_.end()) < data_size) {
            isc_throw(OutOfRange, "option buffer truncated");
        }
        if (definition_.getArrayType()) {
            // We don't perform other checks for data types that can't be
            // used together with array indicator such as strings, empty field
            // etc. This is because OptionDefinition::validate function should
            // have checked this already.
            assert(data_size > 0);
            do {
                buffers.push_back(OptionBuffer(data, data + data_size));
                data += data_size;
            } while (std::distance(data, data_.end()) >= data_size);
        } else {
            if (data_size == 0) {
                data_size = std::distance(data, data_.end());
            }
            buffers.push_back(OptionBuffer(data, data + data_size));
        }
    }
    std::swap(buffers_, buffers);
}

void
OptionCustom::pack4(isc::util::OutputBuffer& buf) {
    if (len() > 255) {
        isc_throw(OutOfRange, "DHCPv4 Option " << type_
                  << " value is too high. At most 255 is supported.");
    }

    buf.writeUint8(type_);
    buf.writeUint8(len() - getHeaderLen());

    // Write data from buffers.
    for (std::vector<OptionBuffer>::const_iterator it = buffers_.begin();
         it != buffers_.end(); ++it) {
        buf.writeData(&(*it)[0], it->size());
    }

    // Write suboptions.
    LibDHCP::packOptions(buf, options_);
}

void
OptionCustom::pack6(isc::util::OutputBuffer& buf) {
    buf.writeUint16(type_);
    buf.writeUint16(len() - getHeaderLen());

    // Write data from buffers.
    for (std::vector<OptionBuffer>::const_iterator it = buffers_.begin();
         it != buffers_.end(); ++it) {
        buf.writeData(&(*it)[0], it->size());
    }

    LibDHCP::packOptions(buf, options_);
}

void
OptionCustom::readAddress(const uint32_t index, asiolink::IOAddress& address) const {
    checkIndex(index);

    // The address being read can be either IPv4 or IPv6. The decision
    // is made based on the buffer length. If it holds 4 bytes it is IPv4
    // address, if it holds 16 bytes it is IPv6.
    if (buffers_[index].size() == asiolink::V4ADDRESS_LEN) {
        OptionDataTypeUtil::readAddress(buffers_[index], AF_INET, address);
    } else if (buffers_[index].size() == asiolink::V6ADDRESS_LEN) {
        OptionDataTypeUtil::readAddress(buffers_[index], AF_INET6, address);
    } else {
        isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                  << " IP address. Invalid buffer length " << buffers_[index].size());
    }
}

const OptionBuffer&
OptionCustom::readBinary(const uint32_t index) const {
    checkIndex(index);
    return (buffers_[index]);
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
    // Chop the buffer stored in data_ into set of sub buffers.
    createBuffers();
}

uint16_t
OptionCustom::len() {
    // The length of the option is a sum of option header ...
    int length = getHeaderLen();

    // ... lengths of all buffers that hold option data ...
    for (std::vector<OptionBuffer>::const_iterator buf = buffers_.begin();
         buf != buffers_.end(); ++buf) {
        length += buf->size();
    }

    // ... and lengths of all suboptions
    for (OptionCustom::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
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

    // Chop the data_ buffer into set of buffers that represent
    // option fields data.
    createBuffers();
}

} // end of isc::dhcp namespace
} // end of isc namespace
