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

/// \brief \c rdata::generic::RP class represents the RP RDATA as defined in
/// RFC1183.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// RP RDATA.
class KEA_DNS_API RP : public Rdata {
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
