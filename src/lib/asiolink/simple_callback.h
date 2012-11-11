// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef ASIOLINK_SIMPLE_CALLBACK_H
#define ASIOLINK_SIMPLE_CALLBACK_H 1

#include <asiolink/io_message.h>

namespace isc {
namespace asiolink {

/// \brief The \c SimpleCallback class is an abstract base class for a
/// simple callback function with the signature:
///
/// void simpleCallback(const IOMessage& io_message) const;
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// The \c SimpleCallback is expected to be used for basic, generic
/// tasks such as checking for configuration changes.  It may also be
/// used for testing purposes.
class SimpleCallback {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    SimpleCallback(const SimpleCallback& source);
    SimpleCallback& operator=(const SimpleCallback& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    SimpleCallback() {
        self_ = this;
    }
public:
    /// \brief The destructor
    virtual ~SimpleCallback() {}
    /// \brief The function operator
    //@}
    ///
    /// This makes its call indirectly via the "self" pointer, ensuring
    /// that the function ultimately invoked will be the one in the derived
    /// class.
    ///
    /// \param io_message The event message to handle
    virtual void operator()(const IOMessage& io_message) const {
        (*self_)(io_message);
    }
private:
    SimpleCallback* self_;
};

} // namespace asiolink
} // namespace isc
#endif // ASIOLINK_SIMPLE_CALLBACK_H
