// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_MEMORY_RDATA_ENCODER_H
#define DATASRC_MEMORY_RDATA_ENCODER_H 1

#include <dns/labelsequence.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <boost/function.hpp>

#include <vector>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief Attributes of domain name fields of encoded RDATA.
///
/// The enum values define special traits of the name that can affect how
/// it should be handled in rendering or query processing.
enum RdataNameAttributes {
    NAMEATTR_NONE = 0,          ///< No special attributes
    NAMEATTR_COMPRESSIBLE = 1,  ///< Name should be compressed when rendered
    NAMEATTR_ADDITIONAL = (NAMEATTR_COMPRESSIBLE << 1) ///< Name requires
                                                      ///< Additional section
                                                      ///< handling
};

// We use the following quick-hack version of encoder and "foreach"
// operator until we implement the complete versions.  The plan is to
// update the test cases that use these functions with the complete
// functions/classes, and then remove the entire namespace.
namespace testing {
// "Encode" given RDATA of given RR class and type.
//
// Fixed/variable-length data fields are encoded in their wire-format;
// domain names are encoded in the form of:
//  - nlen: name data length (1 byte)
//  - olen: offset data length (1 byte)
//  - name data (nlen bytes)
//  - offset data (olen bytes)
//
// The encoded results are appended to data_result.
// If the RDATA contain variable-length data fields, the lengths of the
// these fields will be appended in len_result, in the order of appearance.
void encodeRdata(const dns::rdata::Rdata& rdata, dns::RRClass rrclass,
                 dns::RRType rrtype, std::vector<uint8_t>& data_result,
                 std::vector<uint16_t>& len_result);

// Callbacks used in foreachRdataField.
typedef boost::function<void(const dns::LabelSequence&,
                             RdataNameAttributes)> NameCallback;
typedef boost::function<void(const uint8_t*, size_t)> DataCallback;

// Iterate over each RDATA field (in terms of the internal encoding) stored
// in encoded_data, and call the given callback for each data (for
// domain name fields, name_callback will be called; for normal data fields
// data_callback will be called).  If the encoded data contain variable-length
// data fields, varlen_list should store a sequence of their lengths, in the
// of the appearance.
void foreachRdataField(dns::RRClass rrclass, dns::RRType rrtype,
                       const std::vector<uint8_t>& encoded_data,
                       const std::vector<uint16_t>& varlen_list,
                       NameCallback name_callback, DataCallback data_callback);
}

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATA_ENCODER_H

// Local Variables:
// mode: c++
// End:
