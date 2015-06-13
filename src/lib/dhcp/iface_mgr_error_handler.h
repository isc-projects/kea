// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
/// better solution in this case as it allows to convenietly pass an
/// error string in a stream (not as a string).
///
/// @param ex_type Exception to be thrown if error_handler is NULL.
/// @param handler Error handler function to be called or NULL to indicate
/// that exception should be thrown instead.
/// @param stream stream object holding an error string.
#define IFACEMGR_ERROR(ex_type, handler, stream) \
{ \
    std::ostringstream ieoss__; \
    ieoss__ << stream; \
    if (handler) { \
        handler(ieoss__.str()); \
    } else { \
        isc_throw(ex_type, ieoss__.str()); \
    } \
} \

#endif // IFACE_MGR_ERROR_HANDLER_H
