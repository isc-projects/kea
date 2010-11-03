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

#include <config.h>             // for UNUSED_PARAM

#include <string>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

A::A(const string& addrstr UNUSED_PARAM) {
    // TBD
}

A::A(InputBuffer& buffer UNUSED_PARAM, size_t rdata_len UNUSED_PARAM) {
    // TBD
}

A::A(const A& source UNUSED_PARAM) : Rdata() {
    // TBD
}

void
A::toWire(OutputBuffer& buffer UNUSED_PARAM) const {
    // TBD
}

void
A::toWire(AbstractMessageRenderer& renderer UNUSED_PARAM) const {
    // TBD
}

string
A::toText() const {
    // TBD
    isc_throw(InvalidRdataText, "Not implemented yet");
}

int
A::compare(const Rdata& other UNUSED_PARAM) const {
    return (0);                 // dummy.  TBD
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
