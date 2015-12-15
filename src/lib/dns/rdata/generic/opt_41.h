// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/rdata.h>

#include <boost/shared_ptr.hpp>

#include <vector>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct OPTImpl;

class OPT : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    // The default constructor makes sense for OPT as it can be empty.
    OPT();
    OPT& operator=(const OPT& source);
    ~OPT();

    /// \brief A class representing a pseudo RR (or option) within an
    /// OPT RR (see RFC 6891).
    class PseudoRR {
    public:
        /// \brief Constructor.
        /// \param code The OPTION-CODE field of the pseudo RR.
        /// \param data The OPTION-DATA field of the pseudo
        /// RR. OPTION-LENGTH is set to the length of this vector.
        PseudoRR(uint16_t code,
                 boost::shared_ptr<std::vector<uint8_t> >& data);

        /// \brief Return the option code of this pseudo RR.
        uint16_t getCode() const;

        /// \brief Return the option data of this pseudo RR.
        const uint8_t* getData() const;

        /// \brief Return the length of the option data of this
        /// pseudo RR.
        uint16_t getLength() const;

    private:
        uint16_t code_;
        boost::shared_ptr<std::vector<uint8_t> > data_;
    };

    /// \brief Append a pseudo RR (option) in this OPT RR.
    ///
    /// \param code The OPTION-CODE field of the pseudo RR.
    /// \param data The OPTION-DATA field of the pseudo RR.
    /// \param length The size of the \c data argument. OPTION-LENGTH is
    /// set to this size.
    /// \throw \c isc::InvalidParameter if this pseudo RR would cause
    /// the OPT RDATA to overflow its RDLENGTH.
    void appendPseudoRR(uint16_t code, const uint8_t* data, uint16_t length);

    /// \brief Return a vector of the pseudo RRs (options) in this
    /// OPT RR.
    ///
    /// Note: The returned reference is only valid during the lifetime
    /// of this \c generic::OPT object. It should not be used
    /// afterwards.
    const std::vector<PseudoRR>& getPseudoRRs() const;

private:
    OPTImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
