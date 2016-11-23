/*
 * Copyright (C) 2016  Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef KEA_FUZZ_H
#define KEA_FUZZ_H

extern "C" {

void kea_fuzz_notify(void);

/// @brief Sets up Kea fuzzing
///
/// @param shutdown pointer to boolean flag that will be set to true to
///        trigger shutdown procedure
///
/// This takes one parameter, which is a pointer to shutdown flag,
/// which should point to instance of Dhcp6Srv::shutdown_. Kea runs
/// until something sets this flag to true, which is an indication to
/// start shutdown procedure.
void kea_fuzz_setup(volatile bool * shutdown);

};

#endif /* KEA_FUZZ_H */
