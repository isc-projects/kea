// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <string>

#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>

// BEGIN_HEADER_GUARD

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct RRSIGImpl;

/// \brief \c rdata::RRSIG class represents the RRSIG RDATA as defined %in
/// RFC4034.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// RRSIG RDATA.
class RRSIG : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS
    RRSIG& operator=(const RRSIG& source);
    ~RRSIG();

    // specialized methods
    const RRType& typeCovered() const;
private:
    // helper function for string and lexer constructors
    RRSIGImpl* constructFromLexer(MasterLexer& lexer, const Name* origin);

    RRSIGImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
