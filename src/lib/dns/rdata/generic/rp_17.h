// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c rdata::generic::RP class represents the RP RDATA as defined in
/// RFC1183.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// RP RDATA.
class RP : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// We use the default copy constructor and assignment operator.

    /// \brief Constructor from RDATA field parameters.
    ///
    /// The parameters are a straightforward mapping of %RP RDATA
    /// fields as defined in RFC1183.
    RP(const Name& mailbox, const Name& text) :
        mailbox_(mailbox), text_(text)
    {}

    /// \brief Return the value of the mailbox field.
    ///
    /// \throw std::bad_alloc If resource allocation for the returned
    /// \c Name fails.
    ///
    /// \note
    /// Unlike the case of some other RDATA classes (such as
    /// \c NS::getNSName()), this method constructs a new \c Name object
    /// and returns it, instead of returning a reference to a \c Name object
    /// internally maintained in the class (which is a private member).
    /// This is based on the observation that this method will be rarely used
    /// and even when it's used it will not be in a performance context
    /// (for example, a recursive resolver won't need this field in its
    /// resolution process).  By returning a new object we have flexibility of
    /// changing the internal representation without the risk of changing
    /// the interface or method property.
    /// The same note applies to the \c getText() method.
    Name getMailbox() const { return (mailbox_); }

    /// \brief Return the value of the text field.
    ///
    /// \throw std::bad_alloc If resource allocation for the returned
    /// \c Name fails.
    Name getText() const { return (text_); }

private:
    Name mailbox_;
    Name text_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
