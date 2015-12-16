// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

class MX : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    MX(uint16_t preference, const Name& mxname);

    ///
    /// Specialized methods
    ///
    const Name& getMXName() const;
    uint16_t getMXPref() const;

private:
    void constructFromLexer(isc::dns::MasterLexer& lexer,
                            const isc::dns::Name* origin);

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
