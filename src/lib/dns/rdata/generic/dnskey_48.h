// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <string>

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

struct DNSKEYImpl;

class DNSKEY : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS
    DNSKEY& operator=(const DNSKEY& source);
    ~DNSKEY();

    ///
    /// Specialized methods
    ///

    /// \brief Returns the key tag
    ///
    /// \throw isc::OutOfRange if the key data for RSA/MD5 is too short
    /// to support tag extraction.
    uint16_t getTag() const;

    uint16_t getFlags() const;
    uint8_t getAlgorithm() const;

private:
    DNSKEYImpl* constructFromLexer(isc::dns::MasterLexer& lexer);

    DNSKEYImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
