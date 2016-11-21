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

void kea_fuzz_setup(void);

};

#endif /* KEA_FUZZ_H */
