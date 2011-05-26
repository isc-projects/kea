// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __DEBUG_LEVELS_H
#define __DEBUG_LEVELS_H

/// \brief Defines Debug Levels
///
/// Defines the maximum and minimum debug levels and the number of levels.
/// These are defined using #define as they are referenced in the construction
/// of variables declared outside execution units.  (In this way we avoid the
/// "static initialization fiasco" problem.)

#define MIN_DEBUG_LEVEL (0)
#define MAX_DEBUG_LEVEL (99)
#define NUM_DEBUG_LEVEL (MAX_DEBUG_LEVEL - MIN_DEBUG_LEVEL + 1)

#endif // __DEBUG_LEVELS_H
