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

#include <string>

#include "buffer.h"
#include "messagerenderer.h"
#include "rdata.h"
#include "rdataclass.h"

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

// To add RDATA implementation of a new RR type (say "MyType"), copy this
// template into the appropriate subdirectory with the appropriate name
// (see template.h).
// Then define (at least) the following common methods (that are inherited
// from the base abstract class).
// If you added member functions specific to this derived class, you'll need
// to implement them here, of course.

MyType::MyType(const string& type_str)
{
}

MyType::MyType(InputBuffer& buffer, size_t rdata_len)
{
}

MyType::MyType(const MyType& source)
{
}

std::string
MyType::toText() const
{
}

void
MyType::toWire(OutputBuffer& buffer) const
{
}

void
MyType::toWire(MessageRenderer& renderer) const
{
}

int
MyType::compare(const Rdata& other) const
{
    // The compare method normally begins with this dynamic cast.
    const MyType& other_mytype = dynamic_cast<const MyType&>(other);
    // ...
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
