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

#define KEA_CC_EXPORT

#include <cc/proto_defs.h>

namespace isc {
namespace cc {

// Aside from defining the values for the C++ library, this file is also
// used as direct input of the generator of the python counterpart. Please,
// keep the syntax here simple and check the generated file
// (lib/python/isc/cc/proto_defs.py) is correct and sane.

// The constants used in the CC protocol
// First the header names
const KEA_CC_DATA_API char* const CC_HEADER_TYPE = "type";
const KEA_CC_DATA_API char* const CC_HEADER_FROM = "from";
const KEA_CC_DATA_API char* const CC_HEADER_TO = "to";
const KEA_CC_DATA_API char* const CC_HEADER_GROUP = "group";
const KEA_CC_DATA_API char* const CC_HEADER_INSTANCE = "instance";
const KEA_CC_DATA_API char* const CC_HEADER_SEQ = "seq";
const KEA_CC_DATA_API char* const CC_HEADER_WANT_ANSWER = "want_answer";
const KEA_CC_DATA_API char* const CC_HEADER_REPLY = "reply";
// The commands in the "type" header
const KEA_CC_DATA_API char* const CC_COMMAND_SEND = "send";
const KEA_CC_DATA_API char* const CC_COMMAND_SUBSCRIBE = "subscribe";
const KEA_CC_DATA_API char* const CC_COMMAND_UNSUBSCRIBE = "unsubscribe";
const KEA_CC_DATA_API char* const CC_COMMAND_GET_LNAME = "getlname";
const KEA_CC_DATA_API char* const CC_COMMAND_PING = "ping";
const KEA_CC_DATA_API char* const CC_COMMAND_PONG = "pong";
const KEA_CC_DATA_API char* const CC_COMMAND_STOP = "stop";
// The wildcards of some headers
const KEA_CC_DATA_API char* const CC_TO_WILDCARD = "*";
const KEA_CC_DATA_API char* const CC_INSTANCE_WILDCARD = "*";
// Prefixes for groups
const KEA_CC_DATA_API char* const CC_GROUP_NOTIFICATION_PREFIX = "notifications/";
// Reply codes
const KEA_CC_DATA_API int CC_REPLY_NO_RECPT = -1;
const KEA_CC_DATA_API int CC_REPLY_SUCCESS = 0;
// Payload in the message
const KEA_CC_DATA_API char *const CC_PAYLOAD_LNAME = "lname";
const KEA_CC_DATA_API char *const CC_PAYLOAD_RESULT = "result";
const KEA_CC_DATA_API char *const CC_PAYLOAD_COMMAND = "command";
const KEA_CC_DATA_API char *const CC_PAYLOAD_NOTIFICATION = "notification";

}
}
