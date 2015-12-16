// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD
#include <stdint.h>

#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <dns/name.h>
#include <dns/rdata.h>
#include <util/buffer.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

class HINFOImpl;

/// \brief \c HINFO class represents the HINFO rdata defined in
/// RFC1034, RFC1035
///
/// This class implements the basic interfaces inherited from the
/// \c rdata::Rdata class, and provides accessors specific to the
/// HINFO rdata.
class HINFO : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    // HINFO specific methods
    ~HINFO();

    HINFO& operator=(const HINFO&);

    const std::string getCPU() const;
    const std::string getOS() const;

private:
    /// Helper template function for toWire()
    ///
    /// \param outputer Where to write data in
    template <typename T>
    void toWireHelper(T& outputer) const;

    boost::scoped_ptr<HINFOImpl> impl_;
};


// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
