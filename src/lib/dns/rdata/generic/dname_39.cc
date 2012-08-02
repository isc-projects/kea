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

DNAME::DNAME(const std::string& namestr) :
    dname_(namestr)
{}

DNAME::DNAME(InputBuffer& buffer, size_t) :
    dname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

DNAME::DNAME(const DNAME& other) :
    Rdata(), dname_(other.dname_)
{}

DNAME::DNAME(const Name& dname) :
    dname_(dname)
{}

void
DNAME::toWire(OutputBuffer& buffer) const {
    dname_.toWire(buffer);
}

void
DNAME::toWire(AbstractMessageRenderer& renderer) const {
    // Type DNAME is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(dname_, false);
}

string
DNAME::toText() const {
    return (dname_.toText());
}

int
DNAME::compare(const Rdata& other) const {
    const DNAME& other_dname = dynamic_cast<const DNAME&>(other);

    return (compareNames(dname_, other_dname.dname_));
}

const Name&
DNAME::getDname() const {
    return (dname_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
