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

// $Id$

#include <config.h>

#include <string>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

CNAME::CNAME(const std::string& namestr) :
    cname_(namestr)
{}

CNAME::CNAME(InputBuffer& buffer, size_t rdata_len UNUSED_PARAM) :
    Rdata(), cname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

CNAME::CNAME(const CNAME& other) :
    Rdata(), cname_(other.cname_)
{}

CNAME::CNAME(const Name& cname) :
    cname_(cname)
{}

void
CNAME::toWire(OutputBuffer& buffer) const {
    cname_.toWire(buffer);
}

void
CNAME::toWire(MessageRenderer& renderer) const {
    renderer.writeName(cname_);
}

string
CNAME::toText() const {
    return (cname_.toText());
}

int
CNAME::compare(const Rdata& other) const {
    const CNAME& other_cname = dynamic_cast<const CNAME&>(other);

    return (compareNames(cname_, other_cname.cname_));
}

const Name&
CNAME::getCname() const {
    return (cname_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
