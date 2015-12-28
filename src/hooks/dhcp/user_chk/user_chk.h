// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef USER_CHK_H
#define USER_CHK_H

#include <user_registry.h>
#include <fstream>
#include <string>

// The following constants are used throughout the library.  They are defined
// in load_unload.cc

/// @brief Pointer to the registry instance.
extern user_chk::UserRegistryPtr user_registry;

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
