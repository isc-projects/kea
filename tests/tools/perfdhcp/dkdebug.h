/*
 * Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This module implements a mask-style diagnostic printing/selection system.
 * Each diagnostic is enabled by including an associated keyletter in a
 * selector string given at initialization time (typically as a command-line
 * option).
 */

#ifndef DKDEBUG_H
#define DKDEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

/* Use as the mask in a dkdesc structure to enable all diagnostics */
#define DK_ALL (~0)

/*
 * Elements of this type are used to map the available diagnostic keyletters to
 * mask bits.
 */
struct dkdesc {
    char keyletter;
    unsigned mask;
};

/*
 * Initialize diagnostic mask.
 *
 * Input variables:
 *
 * diag_str is a string giving the keyletters for diagnostics to enable.
 *
 * diags describes the available diagnostics, mapping each keyletter to any
 * number of mask bits.  It should be terminated with an element with keyletter
 * set to the null character.
 *
 * Return value:
 * If an invalid character is given in diag_str, that character; otherwise a
 * null character.
 */
char dk_setup(const char* diag_str, const struct dkdesc* diags);

/*
 * The remaining functions test the mask bitset diag_req against the currently
 * enabled diagnostics, as set by dk_setup().  If any bits set in diag_req are
 * among the enabled diagnostics, the diagnostic operation is enabled.
 */

/*
 * If diagnostic operation is enabled, use the remaining arguments to print
 * like fprintf(stderr, )
 */
void dkprintf(unsigned diag_req, const char format[], ...);

/*
 * If diagnostic operation is enabled, use the remaining arguments to print
 * like vfprintf(stderr, )
 */
void vdkprintf(unsigned diag_req, const char format[], va_list ap);

/*
 * If diagnostic operation is enabled, return 1; else return false.
 */
int dk_set(unsigned diag_req);

#ifdef __cplusplus
}
#endif

#endif
