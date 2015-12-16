// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>
#include <vector>

#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

namespace detail {
template<class Type, uint16_t typeCode> class TXTLikeImpl;
}

/// \brief \c rdata::SPF class represents the SPF RDATA as defined %in
/// RFC4408.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class. The semantics of the class is provided by
/// a copy of instantiated TXTLikeImpl class common to both TXT and SPF.
class SPF : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    SPF& operator=(const SPF& source);

    /// \brief The destructor.
    ~SPF();

    ///
    /// Specialized methods
    ///

    /// \brief Return a reference to the data strings
    ///
    /// This method never throws an exception.
    const std::vector<std::vector<uint8_t> >& getString() const;

private:
    typedef isc::dns::rdata::generic::detail::TXTLikeImpl<SPF, 99> SPFImpl;
    SPFImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
