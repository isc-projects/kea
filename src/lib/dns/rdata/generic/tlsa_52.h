// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <dns/name.h>
#include <dns/rdata.h>

#include <string>
#include <vector>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct TLSAImpl;

class TLSA : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    TLSA(uint8_t certificate_usage, uint8_t selector,
         uint8_t matching_type, const std::string& certificate_assoc_data);
    TLSA& operator=(const TLSA& source);
    ~TLSA();

    ///
    /// Specialized methods
    ///
    uint8_t getCertificateUsage() const;
    uint8_t getSelector() const;
    uint8_t getMatchingType() const;
    const std::vector<uint8_t>& getData() const;
    size_t getDataLength() const;

private:
    TLSAImpl* constructFromLexer(MasterLexer& lexer);

    TLSAImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
