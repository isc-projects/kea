// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef KEA_THREAD_H
#define KEA_THREAD_H

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

namespace isc {
namespace util {
/// \brief Wrappers for thread related functionality
///
/// We provide our own wrappers, currently around pthreads. We tried using
/// the boost thread support, but it gave us some trouble, so we implemented
/// in-house ones.
namespace thread {

/// \brief A separate thread.
///
/// A thread of execution. When created, starts running in the background.
/// You can wait for it then or just forget it ever existed and leave it
/// live peacefully.
///
/// The interface is minimalist for now. We may need to extend it later.
///
/// \note While the objects of this class represent another thread, they
///     are not thread-safe. You're not supposed to call wait() on the same
///     object from multiple threads or so. They are reentrant (you can
///     wait for different threads from different threads).
class Thread : public boost::noncopyable {
public:
    /// \brief There's an uncaught exception in a thread.
    ///
    /// When a thread terminates because it the main function of the thread
    /// throws, this one is re-thrown out of wait() and contains the what
    /// of the original exception.
    class UncaughtException : public isc::Exception {
    public:
        UncaughtException(const char* file, size_t line, const char* what) :
            Exception(file, line, what)
        {}
    };

    /// \brief Create and start a thread.
    ///
    /// Create a new thread and run body inside it.
    ///
    /// If you need to pass parameters to body, or return some result, you
    /// may just want to use boost::bind or alike to store them within the
    /// body functor.
    ///
    /// \note The main functor will be copied internally. You need to consider
    ///     this when returning the result.
    ///
    /// The body should terminate by exiting the function. If it throws, it
    /// is considered an error. You should generally catch any exceptions form
    /// within there and handle them somehow.
    ///
    /// \param main The code to run inside the thread.
    ///
    /// \throw std::bad_alloc if allocation of the new thread or other
    ///     resources fails.
    /// \throw isc::InvalidOperation for other errors (should not happen).
    Thread(const boost::function<void()>& main);

    /// \brief Destructor.
    ///
    /// It is completely legitimate to destroy the thread without calling
    /// wait() before. In such case, the thread will just live on until it
    /// terminates. However, if the thread dies due to exception, for example,
    /// it's up to you to detect that, no error is reported from this class.
    ///
    /// \throw isc::InvalidOperation in the rare case of OS reporting a
    ///     problem. This should not happen unless you messed up with the raw
    ///     thread by the low-level API.
    ~Thread();

    /// \brief Wait for the thread to terminate.
    ///
    /// Waits until the thread terminates. Must be called at most once.
    ///
    /// \throw isc::InvalidOperation if the OS API returns error. This usually
    ///     mean a programmer error (like two threads trying to wait on each
    ///     other).
    /// \throw isc::InvalidOperation calling wait a second time.
    /// \throw UncaughtException if the thread terminated by throwing an
    ///     exception instead of just returning from the function.
    void wait();
private:
    class Impl;
    Impl* impl_;
};

}
}
}

#endif
