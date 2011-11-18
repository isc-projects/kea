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
 * This header gives the interface types and prototypes for the procconf
 * module, which processes command line options.
 */

#ifndef PROCCONF_H
#define PROCCONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h> /* for UINT_MAX */

/*
 * These are used to specify the option type expected
 */
typedef enum {
    CF_CHAR,          /* A single character */
    CF_STRING,        /* A string */
    CF_NE_STRING,     /* A non-empty string */
    CF_INT,           /* An integer */
    CF_NON_NEG_INT,   /* A non-negative integer */
    CF_POS_INT,       /* A positive integer */
    CF_FLOAT,         /* A floating-point value */
    CF_NON_NEG_FLOAT, /* A non-negative floating point value */
    CF_POS_FLOAT,     /* A positive floating point value */
    CF_SWITCH,        /* An option that does not take a value */
    CF_ENDLIST        /* End of option list */
} cf_type;

/*
 * This is to be OR'd into a confvar_t outind to indicate that an index
 * number that is given is not to be interpreted as a command line option
 * character.
 */
#define CF_NOTFLAG (UINT_MAX & ~(UINT_MAX >> 1))

/*
 * Structure for passing varname/value pairs.
 * This gives the variable names to search for, and allows variable names to
 * mapped to characters so that the characters may be used as indexes into the
 * results array.
 */
typedef struct {
    unsigned outind;    /* Single-character option, or option output index */
    char* varname;  /* Long name, for config file and long option */
    cf_type type;   /* Option type */
    const void* addr;   /* Address of variable associated with this option */
    int value;      /* Value to assign to switch options */
} confvar_t;

/*
 * Structure for returning assigned values.
 */
typedef struct confval_struct {
    const char* strval; /* String form of value */
    unsigned index; /* Relative position of this instance */
    union {
        int intval;
        unsigned int nnint;
        double floatval;
        const char* string;
        int switchval;
        char charval;
    } value;
    struct confval_struct* next;
} confval;

/* Information about the values assigned to a particular option */
typedef struct {
    int num;        /* number of instances of this option */
    confvar_t* confvar; /* which option descriptor this corresponds to */
    confval** values;   /* Start of pointers to values for this option */
} cf_option;

typedef struct {
    cf_option* optVals; /* All option values */
    cf_option** map;    /* Option values indexed by option-char/option-index */
} confdata_t;

/*
 * Input variables:
 * argc, argv: Command line data.
 * optConf[]: Option description structures.  The array should end with an
 *    element with a type of CF_ENDLIST.
 * name: Name of program, for messages.
 * usage: Usage message.  If non-null, on error a message is printed to stderr
 *    and the program exits.
 *
 * Output variables:
 * The processed option values are stored in confdata.
 * A pointer to the start of the values for each option is stored in
 * confdata->optVals[].values at the same offset as the option appears in
 * confdata[].
 * For any option for option characters/indexes have been used,
 * confdata->map[index] is set to the same data.
 * After processing, argc will have been adjusted to be the number of
 * non-option arguments and argv will have been adjusted to start with the
 * first non-option argument.
 *
 * Return value:
 * On success, NULL.
 * On error, a message describing the problem.
 */
const char*
procOpts(int* argc, const char** argv[], const confvar_t optConf[],
         confdata_t* confdata, const char name[],
         const char usage[]);

/*
 * Free the malloced data stored in confdata elements by ProcOpts()
 */
void confdataFree(confdata_t *confdata);

#ifdef __cplusplus
}
#endif

#endif
