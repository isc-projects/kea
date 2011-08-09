// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

DLV::DLV(const std::string& type_str) :
    DS_LIKE(type_str)
{}

DLV::DLV(isc::util::InputBuffer& buffer, size_t rdata_len) :
    DS_LIKE(buffer, rdata_len)
{}

DLV::DLV(const DLV& other) :
    DS_LIKE(other)
{}

std::string DLV::toText() const
{
    return DS_LIKE::toText();
}

void DLV::toWire(isc::util::OutputBuffer& buffer) const
{
    DS_LIKE::toWire(buffer);
}

void DLV::toWire(AbstractMessageRenderer& renderer) const
{
    DS_LIKE::toWire(renderer);
}

int DLV::compare(const Rdata& other) const
{
    return DS_LIKE::compare(other);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
