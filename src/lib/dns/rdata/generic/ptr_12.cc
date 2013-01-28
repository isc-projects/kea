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

#include <config.h>

#include <string>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

PTR::PTR(const std::string& type_str) :
    ptr_name_(type_str)
{}

PTR::PTR(InputBuffer& buffer, size_t) :
    ptr_name_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

PTR::PTR(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    ptr_name_(createNameFromLexer(lexer, origin))
{}

PTR::PTR(const PTR& source) :
    Rdata(), ptr_name_(source.ptr_name_)
{}

std::string
PTR::toText() const {
    return (ptr_name_.toText());
}

void
PTR::toWire(OutputBuffer& buffer) const {
    ptr_name_.toWire(buffer);
}

void
PTR::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(ptr_name_);
}

int
PTR::compare(const Rdata& other) const {
    // The compare method normally begins with this dynamic cast.
    const PTR& other_ptr = dynamic_cast<const PTR&>(other);

    return (compareNames(ptr_name_, other_ptr.ptr_name_));

}

const Name&
PTR::getPTRName() const {
    return (ptr_name_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
