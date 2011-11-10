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

#ifndef CLOPTIONS_H
#define CLOPTIONS_H

#include <stdint.h>
#include "procconf.h"

/*
 * Process the options/arguments passed to the program.
 *
 * Input varibles:
 * argc, argv: Command line data.
 *
 * Return value:
 * 0 if the command has been satisfied and the program should exit 0.
 * 2 for usage error, in which case an error message will have been printed.
 * 1 if argument processing was successful and the program should continue.
 */
int procArgs(int argc, const char* argv[]);

/*
 * These functions return values set by command line options
 */
int getv6(void);                // DHCPv6 operation (-6)
int getinitialOnly(void);       // Do only initial exchange (-i)
unsigned getrate(void);         // Request rate (-r)
unsigned getnumRequest(void);   // Number of requests (-n)
double getdropTime(void);       // Response timeout (-d)
double gettestPeriod(void);     // Test period (-p)
const char* getserver(void);    // Server to contact
const char* getlocalName(void); // Local host/interface (-l)
const char* getmaxDrop(void);   // Max dropped responses (-D)

#endif
