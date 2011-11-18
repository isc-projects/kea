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

#include <stdio.h>
#include <stdarg.h>
#include "dkdebug.h"

/*
 * The set of diagnostic bits set by dk_setup(), and used by the other
 * functions to test offered diagnostics against.
 */
static unsigned dk_diag_mask = 0;

char
dk_setup(const char* diag_str, const struct dkdesc* diags) {
    dk_diag_mask = 0;
    int i;

    for (; *diag_str != '\0'; diag_str++) {
        for (i = 0; diags[i].keyletter != '\0'; i++) {
            if (diags[i].keyletter == *diag_str) {
                dk_diag_mask |= diags[i].mask;
                break;
            }
        }
        if (diags[i].keyletter == '\0') {
            return(*diag_str);
        }
    }
    return('\0');
}

void
dkprintf(unsigned diag_req, const char format[], ...) {
    va_list ap;

    va_start(ap,format);
    vdkprintf(diag_req, format, ap);
    va_end(ap);
}

void
vdkprintf(unsigned diag_req, const char format[], va_list ap) {
    if (diag_req & dk_diag_mask) {
        vfprintf(stderr, format, ap);
    }
}

int
dk_set(unsigned diag_req) {
    return((diag_req & dk_diag_mask) != 0);
}
