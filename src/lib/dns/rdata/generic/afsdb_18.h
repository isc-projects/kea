// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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

/// \brief \c rdata::AFSDB class represents the AFSDB RDATA as defined %in
/// RFC1183.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// AFSDB RDATA.
class AFSDB : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Assignment operator.
    ///
    /// This method never throws an exception.
    AFSDB& operator=(const AFSDB& source);
    ///
    /// Specialized methods
    ///

    /// \brief Return the value of the server field.
    ///
    /// \return A reference to a \c Name class object corresponding to the
    /// internal server name.
    ///
    /// This method never throws an exception.
    const Name& getServer() const;

    /// \brief Return the value of the subtype field.
    ///
    /// This method never throws an exception.
    uint16_t getSubtype() const;

private:
    void createFromLexer(MasterLexer& lexer, const Name* origin);

    uint16_t subtype_;
    Name server_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
