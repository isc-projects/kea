// Copyright (C) 2009-2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef COMMON_H
#define COMMON_H 1

#include <stdexcept>
#include <string>

/// An exception class that is thrown in an unrecoverable error condition.
///
/// This exception should not be caught except at the highest level of
/// the application only for terminating the program gracefully, and so
/// it cannot be a derived class of \c isc::Exception.
class FatalError : public std::runtime_error {
public:
    FatalError(const std::string& what) : std::runtime_error(what)
    {}
};

/// \short Get the path of socket to talk to xfrout
///
/// It takes some environment variables into account (B10_FROM_BUILD,
/// B10_FROM_SOURCE_LOCALSTATEDIR and BIND10_XFROUT_SOCKET_FILE). It
/// also considers the installation prefix.
///
/// The logic should be the same as in b10-xfrout, so they find each other.
std::string getXfroutSocketPath();

/// \brief Get the path of socket to talk to ddns
///
/// It takes some environment variables into account (B10_FROM_BUILD,
/// B10_FROM_SOURCE_LOCALSTATEDIR and BIND10_DDNS_SOCKET_FILE). It
/// also considers the installation prefix.
///
/// The logic should be the same as in b10-ddns, so they find each other.
///
/// Note: eventually we should find a better way so that we don't have to
/// repeat the same magic value (and how to tweak it with some magic
/// environment variable) twice, at which point this function may be able
/// to be deprecated.
std::string getDDNSSocketPath();

/// \brief The name used when identifieng the process
///
/// This is currently b10-auth, but it can be changed easily in one place.
extern const char* const AUTH_NAME;

/// \brief Notification string that is used to inform auth is starting
///
/// This is sent to interested modules (currently only b10-ddns)
extern const char* const AUTH_STARTED_NOTIFICATION;

#endif // COMMON_H

// Local Variables:
// mode: c++
// End:
