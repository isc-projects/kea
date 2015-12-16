// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

struct CAAImpl;

class CAA : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    CAA(uint8_t flags, const std::string& tag, const std::string& value);
    CAA& operator=(const CAA& source);
    ~CAA();

    ///
    /// Specialized methods
    ///

    /// \brief Return the Flags field of the CAA RDATA.
    uint8_t getFlags() const;

    /// \brief Return the Tag field of the CAA RDATA.
    const std::string& getTag() const;

    /// \brief Return the Value field of the CAA RDATA.
    ///
    /// Note: The const reference which is returned is valid only during
    /// the lifetime of this \c generic::CAA object. It should not be
    /// used afterwards.
    const std::vector<uint8_t>& getValue() const;

private:
    CAAImpl* constructFromLexer(MasterLexer& lexer);

    CAAImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
