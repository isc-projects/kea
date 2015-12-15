// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/serial.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

class SOA : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    SOA(const Name& mname, const Name& rname, uint32_t serial,
        uint32_t refresh, uint32_t retry, uint32_t expire,
        uint32_t minimum);

    /// \brief Returns the serial stored in the SOA.
    Serial getSerial() const;

    /// brief Returns the minimum TTL field value of the SOA.
    uint32_t getMinimum() const;
private:
    /// Note: this is a prototype version; we may reconsider
    /// this representation later.
    Name mname_;
    Name rname_;
    /// serial, refresh, retry, expire, minimum, stored in network byte order
    uint8_t numdata_[20];
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
