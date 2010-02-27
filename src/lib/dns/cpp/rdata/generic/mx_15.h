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

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>

#include "name.h"
#include "rdata.h"

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

class MX : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    explicit MX(uint16_t preference, const Name& mxname);

    ///
    /// Specialized methods
    ///
    const Name& getMXName() const;
    uint16_t getMXPref() const;

private:
    /// Note: this is a prototype version; we may reconsider
    /// this representation later.
    uint16_t preference_;
    Name mxname_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
