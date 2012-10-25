// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <cc/data.h>

#ifndef COMMAND_H
#define COMMAND_H 1

class AuthSrv;

/// Execute a control command on \c AuthSrv
///
/// It executes the operation identified by \c command_id with arguments
/// \c args on \c server, and returns the result in the form of the standard
/// command/config answer message (see \c isc::config::createAnswer()).
///
/// This method internally performs minimal validation on \c command_id and
/// \c args to not cause a surprising result such as a crash, but it is
/// generally expected that the caller has performed syntax level validation
/// based on the command specification for the authoritative server.
/// For example, the caller is responsible \c command_id is a valid command
/// name for the authoritative server.
///
/// The execution of the command may internally trigger an exception; for
/// instance, if a string that is expected to be a valid domain name is bogus,
/// the underlying DNS library will throw an exception.  These internal
/// exceptions will be caught inside this function, and will be converted
/// to a return value with a non 0 error code.
/// However, exceptions thrown outside of BIND 10 modules (including standard
/// exceptions) are expected to be handled at a higher layer, and will be
/// propagated to the caller.  In particular if memory allocation fails and
/// \c std::bad_alloc is thrown it will be propagated.
///
/// \param server The \c AuthSrv object on which the command is executed.
/// \param command_id The identifier of the command (such as "shutdown")
/// \param args Command specific argument in a map type of
/// \c isc::data::Element, or a \c NULL \c ElementPtr if the argument isn't
/// specified.
/// \return The result of the command operation.
isc::data::ConstElementPtr
execAuthServerCommand(AuthSrv& server, const std::string& command_id,
                      isc::data::ConstElementPtr args);

#endif // COMMAND_H

// Local Variables:
// mode: c++
// End:
