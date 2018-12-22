// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONSTANTS_H
#define MYSQL_CONSTANTS_H

#include <mysql.h>

namespace isc {
namespace db {

/// @name MySQL constants.
///
//@{

#ifdef HAVE_MYSQL_MY_BOOL
/// @brief my_bools type for vectors.
typedef my_bool my_bools;

/// @brief MySQL false value.
const my_bool MLM_FALSE = 0;

/// @brief MySQL true value.
const my_bool MLM_TRUE = 1;

#else
/// @brief my_bool type in MySQL 8.x.
typedef bool my_bool;

/// @brief my_bools type for vectors in MySQL 8.x.
/// @note vector<my_bool> is specialized into a bitset.
typedef char my_bools;

/// @brief MySQL false value.
const my_bool MLM_FALSE = false;

/// @brief MySQL true value.
const my_bool MLM_TRUE = true;
#endif

/// @brief MySQL fetch success code.
const int MLM_MYSQL_FETCH_SUCCESS = 0;

/// @brief MySQL fetch failure code.
const int MLM_MYSQL_FETCH_FAILURE = 0;

//@}

/// @name Current database schema version values.
//@{
const uint32_t MYSQL_SCHEMA_VERSION_MAJOR = 8;
const uint32_t MYSQL_SCHEMA_VERSION_MINOR = 0;

//@}


} // end of namespace isc::db
} // end of namespace isc

#endif
