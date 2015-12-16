// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>
#include <vector>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct SSHFPImpl;

class SSHFP : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    SSHFP(uint8_t algorithm, uint8_t fingerprint_type,
          const std::string& fingerprint);
    SSHFP& operator=(const SSHFP& source);
    ~SSHFP();

    ///
    /// Specialized methods
    ///
    uint8_t getAlgorithmNumber() const;
    uint8_t getFingerprintType() const;
    const std::vector<uint8_t>& getFingerprint() const;
    size_t getFingerprintLength() const;

private:
    SSHFPImpl* constructFromLexer(MasterLexer& lexer);

    SSHFPImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
