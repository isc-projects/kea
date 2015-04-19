// This file is generated from ./proto_defs.cc
// by the const2hdr.py script.
// Do not edit, all changes will be lost.

// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef KEA_COMMON_DEFS_H
#define KEA_COMMON_DEFS_H

#include <cc/api.h>

// \file proto_defs.h
// \brief Common shared constants

// This file contains common definitions of constasts used across the sources.
// It includes, but is not limited to the definitions of messages sent from
// one process to another. Since the names should be self-explanatory and
// the variables here are used mostly to synchronize the same values across
// multiple programs, separate documentation for each variable is not provided.

namespace isc {
namespace cc {

// Aside from defining the values for the C++ library, this file is also
// used as direct input of the generator of the python counterpart. Please,
// keep the syntax here simple and check the generated file
// (lib/python/isc/cc/proto_defs.py) is correct and sane.

// The constants used in the CC protocol
// First the header names
extern const KEA_CC_API char* const CC_HEADER_TYPE;
extern const KEA_CC_API char* const CC_HEADER_FROM;
extern const KEA_CC_API char* const CC_HEADER_TO;
extern const KEA_CC_API char* const CC_HEADER_GROUP;
extern const KEA_CC_API char* const CC_HEADER_INSTANCE;
extern const KEA_CC_API char* const CC_HEADER_SEQ;
extern const KEA_CC_API char* const CC_HEADER_WANT_ANSWER;
extern const KEA_CC_API char* const CC_HEADER_REPLY;
// The commands in the "type" header
extern const KEA_CC_API char* const CC_COMMAND_SEND;
extern const KEA_CC_API char* const CC_COMMAND_SUBSCRIBE;
extern const KEA_CC_API char* const CC_COMMAND_UNSUBSCRIBE;
extern const KEA_CC_API char* const CC_COMMAND_GET_LNAME;
extern const KEA_CC_API char* const CC_COMMAND_PING;
extern const KEA_CC_API char* const CC_COMMAND_PONG;
extern const KEA_CC_API char* const CC_COMMAND_STOP;
// The wildcards of some headers
extern const KEA_CC_API char* const CC_TO_WILDCARD;
extern const KEA_CC_API char* const CC_INSTANCE_WILDCARD;
// Prefixes for groups
extern const KEA_CC_API char* const CC_GROUP_NOTIFICATION_PREFIX;
// Reply codes
extern const KEA_CC_API int CC_REPLY_NO_RECPT;
extern const KEA_CC_API int CC_REPLY_SUCCESS;
// Payload in the message
extern const KEA_CC_API char *const CC_PAYLOAD_LNAME;
extern const KEA_CC_API char *const CC_PAYLOAD_RESULT;
extern const KEA_CC_API char *const CC_PAYLOAD_COMMAND;
extern const KEA_CC_API char *const CC_PAYLOAD_NOTIFICATION;

}
}
#endif
