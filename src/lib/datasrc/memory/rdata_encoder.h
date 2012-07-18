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

enum RdataNameAttributes {
    NAMEATTR_COMPRESSIBLE = 1,
    NAMEATTR_ADDITIONAL = (NAMEATTR_COMPRESSIBLE << 1)
};

void encodeRdata(const dns::rdata::Rdata& rdata, dns::RRClass rrclass,
                 dns::RRType rrtype, std::vector<uint8_t>& data_result,
                 std::vector<uint16_t>& len_result);

typedef boost::function<void(const dns::LabelSequence&,
                             RdataNameAttributes)> NameCallback;
typedef boost::function<void(const uint8_t*, size_t)> DataCallback;

void foreachRdataField(dns::RRClass rrclass, dns::RRType rrtype,
                       const std::vector<uint8_t>& encoded_data,
                       const std::vector<uint16_t>& varlen_list,
                       NameCallback name_callback, DataCallback data_callback);

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATA_ENCODER_H

// Local Variables:
// mode: c++
// End:
