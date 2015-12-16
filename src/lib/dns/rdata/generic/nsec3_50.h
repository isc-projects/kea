// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <string>
#include <vector>

#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/master_lexer.h>

// BEGIN_HEADER_GUARD

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct NSEC3Impl;

class NSEC3 : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS
    NSEC3& operator=(const NSEC3& source);
    ~NSEC3();

    uint8_t getHashalg() const;
    uint8_t getFlags() const;
    uint16_t getIterations() const;
    const std::vector<uint8_t>& getSalt() const;
    const std::vector<uint8_t>& getNext() const;

private:
    NSEC3Impl* constructFromLexer(isc::dns::MasterLexer& lexer);

    NSEC3Impl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
