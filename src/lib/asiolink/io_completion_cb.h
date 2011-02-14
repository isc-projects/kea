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

#ifndef __IO_COMPLETION_CB_H
#define __IO_COMPLETION_CB_H

#include <asio/error_code.hpp>
#include <coroutine.h>


/// \brief Asynchronous I/O Completion Callback
///
/// The stackless coroutine code requires that there be an "entry function"
/// containing the coroutine macros.  When the coroutine yields, its state is
/// stored and when the "entry function" is called again, it jumps to the
/// line when processing left off last time.  In BIND-10, that "entry function"
/// is the Boost asynchronous I/O completion callback - in essence operator().
///
/// This class solves the problem of circularity in class definitions.  In
/// BIND10, classes such as IOFetch contain the coroutine code.  These include
/// objects of classes such as IOSocket, whose signature has to include the
/// callback object - IOFetch.  By abstracting the I/O completion callback into
/// this class, that circularity is broken.
///
/// One more point: the asynchronous I/O functions take the callback object by
/// reference.  But if a derived class object is passed as a reference to its
/// base class, "class slicing" takes place - the derived part of the class is
/// lost and only the base class functionality remains.  By storing a pointer
/// to the true object and having the base class method call the derived class
/// method through that, the behaviour of class inheritance is restored. In
/// other words:
/// \code
/// class derived: public class base {
/// :
/// };
/// derived drv;
///
/// // Call with pointer to base class
/// void f(base* b, asio::error_code& ec, size_t length) {
///    b->operator()(ec, length);
/// }
///
/// // Call with reference to base class
/// void g(base& b, asio::error_code& ec, size_t length) {
///    b.operator()(ec, length);
/// }
///
/// void function xyz(derived *d, asio::error_code& ec, size_t length) {
///    f(d, ec, length);  // Calls derived::operator()
///    g(*d, ec, length); // Also calls derived::operator()
/// }
/// \endcode

class IOCompletionCallback : public coroutine {
public:

    /// \brief Constructor
    IOCompletionCallback() : self_(this)
    {}

    /// \brief Virtual Destructor
    virtual ~IOCompletionCallback()
    {}

    /// \brief Callback Method
    virtual void operator()(asio::error_code ec = asio::error_code(),
        size_t length = 0) {
        (*self_)(ec, length);
    }

private:
    IOCompletionCallback*   self_;      ///< Pointer to real object
};


#endif // __IO_COMPLETION_CB_H
