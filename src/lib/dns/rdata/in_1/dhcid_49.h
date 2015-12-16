// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <string>
#include <vector>

#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c rdata::DHCID class represents the DHCID RDATA as defined %in
/// RFC4701.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// DHCID RDATA.
class DHCID : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Return the digest.
    ///
    /// This method never throws an exception.
    const std::vector<uint8_t>& getDigest() const;

private:
    // helper for string and lexer constructors
    void constructFromLexer(MasterLexer& lexer);

    /// \brief Private data representation
    ///
    /// Opaque data at least 3 octets long as per RFC4701.
    ///
    std::vector<uint8_t> digest_;
};
// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
