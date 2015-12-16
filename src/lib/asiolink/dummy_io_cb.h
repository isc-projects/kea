// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DUMMY_IO_CB_H
#define DUMMY_IO_CB_H

#include <iostream>

#include <exceptions/exceptions.h>

#include <boost/asio/error.hpp>

namespace isc {
namespace asiolink {

/// \brief Asynchronous I/O Completion Callback
///
/// The two socket classes (UDPSocket and TCPSocket) require that the I/O
/// completion callback function have an operator() method with the appropriate
/// signature.  The classes are templates, any class with that method and
/// signature can be passed as the callback object - there is no need for a
/// base class defining the interface.  However, some users of the socket
/// classes do not use the asynchronous I/O operations, yet have to supply a
/// template parameter.  This is the reason for this class - it is the dummy
/// template parameter.

class DummyIOCallback {
public:

    /// \brief Asynchronous I/O callback method
    ///
    /// Should never be called, as this class is a convenience class provided
    /// for instances where a socket is required but it is known that no
    /// asynchronous operations will be carried out.
    void operator()(boost::system::error_code) {
        // If the function is called, there is a serious logic error in
        // the program (this class should not be used as the callback
        // class).  As the asiolink module is too low-level for logging
        // errors, throw an exception.
        isc_throw(isc::Unexpected,
                  "DummyIOCallback::operator() must not be called");
    }

    /// \brief Asynchronous I/O callback method
    ///
    /// Should never be called, as this class is a convenience class provided
    /// for instances where a socket is required but it is known that no
    /// asynchronous operations will be carried out.
    void operator()(boost::system::error_code, size_t) {
        // If the function is called, there is a serious logic error in
        // the program (this class should not be used as the callback
        // class).  As the asiolink module is too low-level for logging
        // errors, throw an exception.
        isc_throw(isc::Unexpected,
                  "DummyIOCallback::operator() must not be called");
    }
};

} // namespace asiolink
} // namespace isc

#endif // DUMMY_IO_CB_H
