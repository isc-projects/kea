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

#include "rdata_reader.h"

namespace isc {
namespace datasrc {
namespace memory {

void
RdataReader::emptyNameAction(const dns::LabelSequence&, unsigned) {
    // Do nothing here. On purpose, it's not unfinished.
}

void
RdataReader::emptyDataAction(const uint8_t*, size_t) {
    // Do nothing here. On purpose, it's not unfinished.
}

RdataReader::Result::Result(const dns::LabelSequence& label,
                            unsigned attributes) :
    label_(label),
    data_(NULL),
    size_(0),
    type_(NAME),
    compressible_((attributes & NAMEATTR_COMPRESSIBLE) != 0),
    additional_((attributes & NAMEATTR_ADDITIONAL) != 0)
{}

RdataReader::Result::Result(const uint8_t* data, size_t size) :
    label_(dns::Name::ROOT_NAME()),
    data_(data),
    size_(size),
    type_(DATA),
    compressible_(false),
    additional_(false)
{}

}
}
}
