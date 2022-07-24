// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IFACE_MGR_ERROR_HANDLER_H
#define IFACE_MGR_ERROR_HANDLER_H

/// @brief A macro which handles an error in IfaceMgr.
///
/// There are certain cases when IfaceMgr may hit an error which shouldn't
/// result in interruption of the function processing. A typical case is
/// the function which opens sockets on available interfaces for a DHCP
/// server. If this function fails to open a socket on a specific interface
/// (for example, there is another socket already open on this interface
/// and bound to the same address and port), it is desired that the server
/// logs a warning but will try to open sockets on other interfaces. In order
/// to log an error, the IfaceMgr will use the error handler function provided
/// by the server and pass an error string to it. When the handler function
/// returns, the IfaceMgr will proceed to open other sockets. It is allowed
/// that the error handler function is not installed (is NULL). In these
/// cases it is expected that the exception is thrown instead. A possible
/// solution would be to enclose this conditional behavior in a function.
/// However, despite the hate for macros, the macro seems to be a bit
/// better solution in this case as it allows to conveniently pass an
/// error string in a stream (not as a string).
///
/// @param ex_type Exception to be thrown if error_handler is NULL.
/// @param handler Error handler function to be called or NULL to indicate
/// that exception should be thrown instead.
/// @param iface Pointer to the interface for which the error is logged. Can be null.
/// @param stream stream object holding an error string.
#define IFACEMGR_ERROR(ex_type, handler, iface, stream) \
{ \
    std::ostringstream ieoss__; \
    ieoss__ << stream; \
    std::string const error(ieoss__.str()); \
    if (iface) { \
        iface->addError(error); \
    } \
    if (handler) { \
        handler(error); \
    } else { \
        isc_throw(ex_type, error); \
    } \
} \

#endif // IFACE_MGR_ERROR_HANDLER_H
