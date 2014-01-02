// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#ifndef USER_CHK_H
#define USER_CHK_H

#include <user_registry.h>
#include <fstream>
#include <string>

using namespace std;
using namespace user_chk;

// The following constants are used throughout the library.  They are defined
// in load_unload.cc

/// @brief Pointer to the registry instance.
extern UserRegistryPtr user_registry;

/// @brief Output filestream for recording user check outcomes.
extern std::fstream user_chk_output;

/// @brief User registry input file name.
extern const char* registry_fname;

/// @brief User check outcome file name.
extern const char* user_chk_output_fname;

/// @brief Text label of user id in the inbound query in callout context
extern const char* query_user_id_label;

/// @brief Text label of registered user pointer in callout context
extern const char* registered_user_label;

/// @brief Text id used to identify the default IPv4 user in the registry
extern const char* default_user4_id_str;

/// @brief Text id used to identify the default IPv6 user in the registry
extern const char* default_user6_id_str;

#endif
