// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct SRVImpl;

/// \brief \c rdata::SRV class represents the SRV RDATA as defined %in
/// RFC2782.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// SRV RDATA.
class SRV : public Rdata {
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
    SRV& operator=(const SRV& source);

    /// \brief The destructor.
    ~SRV();

    ///
    /// Specialized methods
    ///

    /// \brief Return the value of the priority field.
    ///
    /// This method never throws an exception.
    uint16_t getPriority() const;

    /// \brief Return the value of the weight field.
    ///
    /// This method never throws an exception.
    uint16_t getWeight() const;

    /// \brief Return the value of the port field.
    ///
    /// This method never throws an exception.
    uint16_t getPort() const;

    /// \brief Return the value of the target field.
    ///
    /// \return A reference to a \c Name class object corresponding to the
    /// internal target name.
    ///
    /// This method never throws an exception.
    const Name& getTarget() const;

private:
    SRVImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
