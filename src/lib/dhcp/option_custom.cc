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

    OptionDataType data_type = definition_.getType();
    if (data_type == OPT_RECORD_TYPE) {
        // An option comprises a record of data fields. We need to
        // get types of these data fields to allocate enough space
        // for each buffer.
        const OptionDefinition::RecordFieldsCollection& fields =
            definition_.getRecordFields();

        // Go over all data fields within a record.
        for (OptionDefinition::RecordFieldsConstIter field = fields.begin();
             field != fields.end(); ++field) {
            // For fixed-size data type such as boolean, integer, even
            // IP address we can use the utility function to get the required
            // buffer size.
            int data_size = OptionDataTypeUtil::getDataTypeLen(*field);

            // For variable size types (such as string) the function above
            // will return 0 so we need to do a runtime check. Since variable
            // length data fields may be laid only at the end of an option we
            // consume the rest of this option. Note that validate() function
            // in OptionDefinition object should have checked whether the
            // data fields layout is correct (that the variable string fields
            // are laid at the end).
            if (data_size == 0) {
                data_size = std::distance(data, data_.end());
                if (data_size == 0) {
                    // If we reached the end of buffer we assume that this option is
                    // truncated because there is no remaining data to initialize
                    // an option field.
                    if (data_size == 0) {
                        isc_throw(OutOfRange, "option buffer truncated");
                    }
                }
            } else {
                // Our data field requires that there is a certain chunk of
                // data left in the buffer. If not, option is truncated.
                if (std::distance(data, data_.end()) < data_size) {
                    isc_throw(OutOfRange, "option buffer truncated");
                }
            }
            // Store the created buffer.
            buffers.push_back(OptionBuffer(data, data + data_size));
            // Proceed to the next data field.
            data += data_size;
        }
    } else {
        // If option definition type is not a 'record' than definition
        // type itself indicates what type of data is being held there.
        int data_size = OptionDataTypeUtil::getDataTypeLen(data_type);
        // The check below will fail if the input buffer is too short
        // for the data size being held by this option.
        // Note that data_size returned by getDataTypeLen may be zero
        // if variable length data is being held by the option but
        // this will not cause this check to throw exception.
        if (std::distance(data, data_.end()) < data_size) {
            isc_throw(OutOfRange, "option buffer truncated");
        }
        // For an array of values we are taking different path because
        // we have to handle multiple buffers.
        if (definition_.getArrayType()) {
            // We don't perform other checks for data types that can't be
            // used together with array indicator such as strings, empty field
            // etc. This is because OptionDefinition::validate function should
            // have checked this already. Thus data_size must be greater than
            // zero.
            assert(data_size > 0);
            // Get equal chunks of data and store as collection of buffers.
            // Truncate any remaining part which length is not divisible by
            // data_size.
            do {
                buffers.push_back(OptionBuffer(data, data + data_size));
                data += data_size;
            } while (std::distance(data, data_.end()) >= data_size);
        } else {
            // For non-arrays the data_size can be zero because
            // getDataTypeLen returns zero for variable size data types
            // such as strings. Simply take whole buffer.
            if (data_size == 0) {
                data_size = std::distance(data, data_.end());
            }
            if (data_size > 0 && data_type != OPT_EMPTY_TYPE) {
                buffers.push_back(OptionBuffer(data, data + data_size));
            } else if (data_type != OPT_EMPTY_TYPE) {
                isc_throw(OutOfRange, "option buffer truncated");
            }
        }
    }
    // If everything went ok we can replace old buffer set with new ones.
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

std::string OptionCustom::toText(int indent /* = 0 */ ) {
    std::stringstream tmp;

    for (int i = 0; i < indent; ++i)
        tmp << " ";

    tmp << "type=" << type_ << ", len=" << len()-getHeaderLen()
        << ", data fields:" << std::endl;

    OptionDataType data_type = definition_.getType();
    for (unsigned int i = 0; i < getDataFieldsNum(); ++i) {
        if (data_type == OPT_RECORD_TYPE) {
            const OptionDefinition::RecordFieldsCollection& fields =
                definition_.getRecordFields();

            for (OptionDefinition::RecordFieldsConstIter field = fields.begin();
                 field != fields.end(); ++field) {
                for (int j = 0; j < indent + 2; ++j) {
                    tmp << " ";
                }
                tmp << OptionDataTypeUtil::getDataTypeName(*field)
                    << ", value = " << "here is a value" << std::endl;
            }
        }
    }

    // print suboptions
    for (OptionCollection::const_iterator opt = options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
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
