// Copyright (C) 2011-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c rdata::generic::MINFO class represents the MINFO RDATA as
/// defined in RFC1035.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// MINFO RDATA.
class KEA_DNS_API MINFO : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Define the assignment operator.
    ///
    /// \exception std::bad_alloc Memory allocation fails in copying
    /// internal member variables (this should be very rare).
    MINFO& operator=(const MINFO& source);

    /// \brief Return the value of the rmailbox field.
    ///
    /// \throw std::bad_alloc If resource allocation for the returned
    /// \c Name fails.
    ///
    /// \note
    /// Unlike the case of some other RDATA classes (such as
    /// \c NS::getNSName()), this method constructs a new \c Name object
    /// and returns it, instead of returning a reference to a \c Name object
    /// internally maintained in the class (which is a private member).
    /// This is based on the observation that this method will be rarely
    /// used and even when it's used it will not be in a performance context
    /// (for example, a recursive resolver won't need this field in its
    /// resolution process).  By returning a new object we have flexibility
    /// of changing the internal representation without the risk of changing
    /// the interface or method property.
    /// The same note applies to the \c getEmailbox() method.
    Name getRmailbox() const { return (rmailbox_); }

    /// \brief Return the value of the emailbox field.
    ///
    /// \throw std::bad_alloc If resource allocation for the returned
    /// \c Name fails.
    Name getEmailbox() const { return (emailbox_); }

private:
    Name rmailbox_;
    Name emailbox_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
