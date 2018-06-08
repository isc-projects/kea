// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#include <config.h>
#include <hooks/hooks.h>

extern "C" {

/// @brief returns Kea hooks version.
int version() {
    return (KEA_HOOKS_VERSION);
}

}
