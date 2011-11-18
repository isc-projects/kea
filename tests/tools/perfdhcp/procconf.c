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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include "procconf.h"

static char errmsg[256];    /* for returning error descriptions */
static const char* pc_name;
static const char* pc_usage;

#define INTERNAL_ERROR -1
#define USAGE_ERROR -2

/*
 * error: printf-style interface to print an error message or write it into
 * global errmsg.  If a usage message has been given (the indicator that errors
 * should be handled internally), the message is printed to stderr and the
 * program is exited.  If not, it is written into errmsg.
 * Input variables:
 * errtype is the error type.  If USAGE_ERROR, the program's usage is included
 *     in error messages, and the exit status is 2; otherwise the exit status
 *     is 1.
 * format and the remaining arguments are as for printf().
 */
static void
error(const int errtype, const char* format, ...) {
    va_list ap;

    va_start(ap,format);
    if (pc_usage != NULL) { /* error messages should be printed directly */
        fprintf(stderr, "%s: ", pc_name);
        vfprintf(stderr, format, ap);
        putc('\n', stderr);
        if (errtype == USAGE_ERROR) {
            fputs(pc_usage, stderr);
        }
        exit(errtype == USAGE_ERROR ? 2 : 1);
    } else {
        vsnprintf(errmsg, sizeof(errmsg), format, ap);
    }
    va_end(ap);
}

/*
 * Allocate memory, with error checking.
 * On allocation failure, error() is called; see its description.
 * The memory is zeroed before being returned.
 */
static void*
pc_malloc(size_t size) {
    void* ret = calloc(1, size);
    if (ret == NULL) {
        error(INTERNAL_ERROR, "Out of memory");
    }
    return(ret);
}

/*
 * Generate an error message describing an error in the value passed with an
 * option.  This is a front end for error(); see its usage for details.
 * Input variables:
 * expected: A description of what was expected for the value.
 * varDesc: The descriptor for the option.
 * value: The value that was given with the option.
 * detail: If non-null, additional detail to append regardign the problem.
 */
static void
opterror(const char* expected, const char* value, const confvar_t* varDesc,
         const char* detail) {
    if (detail == NULL) {
        detail = "";
    }
    error(USAGE_ERROR,
          "Invalid value given for option -%c: expected %s, got: %s%s",
          varDesc->outind, expected, value, detail);
}

/*
 * Add an option flag or value assignment to the options database.
 * This does all option-type-specific processing, and generates linked lists
 * of option structures.
 *
 * Input variables:
 * value is the string value assigned to the option, for options that take
 *     values.
 * varDesc is the description structure for this option.
 *
 * Output variables:
 * The option data is stored in a malloced confval structure, which is appended
 * to the option list.  The first element of the list is pointed to by first.
 * first should be NULL if the list contains no elements; in this case it is
 * set to point to the new structure.  Otherwise the structure is appended to
 * the element pointed to by last (it is updated to point to that structure).
 * The 'next' element of the new structure is set to NULL; this is the list
 * termination indicator when traversing it.
 *
 * Return value:
 * 0 if option was ignored.
 * 1 if option was processed & added to option chain.
 * On error, a string describing the error is stored in the global errmsg and
 * -1 is returned.
 */
static int
addOptVal(const char* value, const confvar_t* varDesc,
          confval** first, confval** last) {
    const void* addr;           /* address, if any at which to store value */
    confval data;               /* data for this option/value */
    confval *ret_data;          /* allocated structure to add to list */
    int seen = *first != NULL;  /* has this option been seen before? */
    char* ptr;        /* character that terminated processing in strtox() */
    int err;                    /* bad numeric value found? */

    /* if first instance of this option, store result to given addr */
    addr = seen ? NULL : varDesc->addr;
    switch (varDesc->type) {
    case CF_CHAR:
        if (strlen(value) > 1) {    /* length 0 is OK; gives null char */
            opterror("a single character", value, varDesc, NULL);
            return(-1);
        }
        data.value.charval = *value;
        if (addr != NULL) {
            *(char*)addr = *value;
        }
        break;
    case CF_STRING:
    case CF_NE_STRING:
        if (varDesc->type == CF_NE_STRING && *value == '\0') {
            opterror("a non-empty string", value, varDesc, NULL);
            return(-1);
        }
        data.value.string = value;
        if (addr != NULL) {
            *(const char**)addr = value;
        }
        break;
    case CF_INT:
    case CF_NON_NEG_INT:
    case CF_POS_INT:
        /* todo: check for out-of-range result */
        errno = 0;
        data.value.intval = strtol(value, &ptr, 0);
        if (errno == ERANGE) {
            opterror("an integer", value, varDesc,
                     " (out of range)");
            return(-1);
        }
        err = *value == '\0' || *ptr != '\0';
        switch (varDesc->type) {
        case CF_INT:
            if (err) {
                opterror("an integer", value, varDesc, NULL);
                return(-1);
            }
            break;
        case CF_NON_NEG_INT:
            if (err || data.value.intval < 0) {
                opterror("a non-negative integer", value, varDesc,
                         NULL);
                return(-1);
            }
            data.value.nnint = data.value.intval;
            break;
        case CF_POS_INT:
            if (err || data.value.intval <= 0) {
                opterror("a positive integer", value, varDesc, NULL);
                return(-1);
            }
            data.value.nnint = data.value.intval;
            break;
        default:
            /* To avoid complaints from -Wall */
            ;
        }
        if (addr != NULL) {
            *(int*)addr = data.value.intval;
        }
        break;
    case CF_FLOAT:
    case CF_NON_NEG_FLOAT:
    case CF_POS_FLOAT:
        /* todo: check for out-of-range result */
        errno = 0;
        data.value.floatval = strtod(value, &ptr);
        if (errno == ERANGE) {
            opterror("a number", value, varDesc, " (out of range)");
            return(-1);
        }
        err = *value == '\0' || *ptr != '\0';
        switch (varDesc->type) {
        case CF_FLOAT:
            if (err) {
                opterror("a number", value, varDesc, NULL);
                return(-1);
            }
            break;
        case CF_NON_NEG_FLOAT:
            if (err || data.value.floatval < 0) {
                opterror("a non-negative number", value, varDesc,
                         NULL);
                return(-1);
            }
            break;
        case CF_POS_FLOAT:
            if (err || data.value.floatval <= 0) {
                opterror("a positive number", value, varDesc, NULL);
                return(-1);
            }
            break;
        default:
            /* To avoid complaints from -Wall */
            ;
        }
        if (addr != NULL) {
            *(double*)addr = data.value.floatval;
        }
        break;
    case CF_SWITCH:
        data.value.switchval = varDesc->value;
        value = "1";    /* for debugging */
        if (addr != NULL) {
            *(int*)addr = varDesc->value;
        }
        break;
    case CF_ENDLIST:
        /* To avoid complaints from -Wall */
        ;
    }
    data.strval = value;
    data.next = NULL;
    if ((ret_data = (confval*)pc_malloc(sizeof(confval))) == NULL) {
        return(-1);
    }
    *ret_data = data;
    if (seen) {
        (*last)->next = ret_data;
    } else {
        *first = ret_data;
    }
    *last = ret_data;
    return(1);
}

/*
 * Input variables:
 * argc, argv: Command line data.
 * optConf[]: Option description structures.
 *
 * Output variables:
 * See addOptVal().
 * After processing, argc will be the number of non-option arguments and argv
 * will start with the first non-option argument.
 *
 * Return value:
 * On success, the number of options processed.
 * On error, a string describing the error is stored in the global errmsg and
 * -1 is returned.
 */
static int
procCmdLineArgs(int* argc, const char** argv[], const confvar_t optConf[],
                confval** perOptRecordsFirst, confval** perOptRecordsLast) {
    char* p;
    extern char* optarg;    /* For getopt */
    extern int optind;      /* For getopt */
    extern int optopt;      /* For getopt */
    char optstr[514];       /* List of option chars, for getopt */
    unsigned optCharToConf[256];        /* Map option char/num to confvar */
    int optchar;            /* value returned by getopt() */
    int confNum;       /* to iterate over confvars */
    int count = 0;          /* number of options processed */

    p = optstr;
    *(p++) = ':';
    for (confNum = 0; optConf[confNum].type != CF_ENDLIST; confNum++) {
        unsigned outind = optConf[confNum].outind;
        if (outind < 256 && isprint(outind)) {
            *(p++) = (char)outind;
            switch (optConf[confNum].type) {
            case CF_SWITCH:
                break;
            default:
                *(p++) = ':';
                break;
            }
            optCharToConf[outind] = confNum;
        }
    }

    *p = '\0';
    optind = 1;
    while ((optchar = getopt(*argc, *argv, optstr)) != -1)
    {
        int ind;
        int ret;

        if (optchar == '?') {
            error(USAGE_ERROR, "Unknown option character '%c'", optopt);
            return(-1);
        } else if (optchar == ':') {
            error(USAGE_ERROR, "No value given for option -%c", optopt);
            return(-1);
        }
        ind = optCharToConf[optchar];
        switch (ret = addOptVal(optarg, &optConf[ind],
                                &perOptRecordsFirst[ind],
                                &perOptRecordsLast[ind])) {
        case 1:
            count++;
            break;
        case 0:
            break;
        default:
            return(ret);
        }
    }
    *argc -= optind;
    *argv += optind;
    return(count);
}

/*
 * Input variables:
 * argc, argv: Command line data.
 * optConf[]: Option description structures.
 * name: Name of program, for messages.
 * usage: Usage message.  If non-null, on error a message is printed to stderr
 *    and the program exits.
 *
 * Output variables:
 * Option values are stored at the value given by any confvar that has a
 * non-null address. 
 * If confdatda is not null, the processed option values are stored in
 * confdata.
 * A pointer to the start of the values for each option is stored in
 * confdata->optVals[].values at the same offset as the option appears in
 * confdata[].
 * For any option for option characters/indexes that have been used,
 * confdata->map[index] is set to the same data.
 * After processing, argc will have been adjusted to be the number of
 * non-option arguments and argv will have been adjusted to start with the
 * first non-option argument.
 * The malloced data structures returned in confdata are:
 *   optVals
 *   optVals[0].values
 *   If any option characters/indexes are used, map.  If not used, this will be
 *     a null pointer.
 *
 * Return value:
 * On success, NULL.
 * On error, a message describing the problem.
 */
const char*
procOpts(int* argc, const char** argv[], const confvar_t optConf[],
         confdata_t* confdata, const char name[],
         const char usage[]) {
    /*
     * First & last records in the linked lists maintained for each option.
     * These will point to arrays indexed by option number, giving one pointer
     * (each) per option, used to maintain/return the list of values seen for
     * that option (see the description of first & last in addOptVal()
     */
    confval** perOptRecordsFirst;
    confval** perOptRecordsLast;

    /* Number of configuration options given in optConf */
    unsigned numConf;
    unsigned maxOptIndex = 0;   /* The highest option index number seen */
    /* number of option instances + assignments given */
    int numOptsFound;
    int optNum;    /* to iterate through the possible options */
    int i;         /* index into the global list of option value structures */
    confval** valuePointers;    /* global list of value structures */

    pc_name = name;
    pc_usage = usage;
    for (numConf = 0; optConf[numConf].type != CF_ENDLIST; numConf++) {
        unsigned outind = optConf[numConf].outind;

        if ((outind & ~CF_NOTFLAG) > maxOptIndex) {
            maxOptIndex = outind & ~CF_NOTFLAG;
        }
    }
    if (numConf == 0) {
        error(INTERNAL_ERROR, "Empty confvar list");
        return(errmsg);
    }
    if ((perOptRecordsFirst = (confval**)pc_malloc(sizeof(confval*) * numConf))
            == NULL || (perOptRecordsLast =
            (confval**)pc_malloc(sizeof(confval*) * numConf)) == NULL) {
        return(errmsg);
    }

    numOptsFound = procCmdLineArgs(argc, argv, optConf, perOptRecordsFirst,
                                   perOptRecordsLast);
    free(perOptRecordsLast);
    perOptRecordsLast = NULL;

    if (numOptsFound < 0)
    {
        free(perOptRecordsFirst);
        return(errmsg);
    }
    if (confdata == NULL) {
        free(perOptRecordsFirst);
        return NULL;
    }

    /*
     * All options have been read & initial processing done.
     * An array of pointers is now generated for the options.
     */
    if ((valuePointers =
            (confval**)pc_malloc(sizeof(confval*) * numOptsFound)) == NULL ||
            (confdata->optVals =
            (cf_option*)pc_malloc(sizeof(cf_option) * numConf)) == NULL) {
        return(errmsg);
    }
    /* If option characters / indexes are used, allocate a map for them */
    if (maxOptIndex == 0) {
	confdata->map = NULL;
    } else {
        if ((confdata->map = (cf_option**)pc_malloc(sizeof(cf_option) *
             (maxOptIndex+1))) == NULL) {
            return(errmsg);
        }
    }

    /*
     * Store the linked lists of option values into arrays.
     * Pointers to all option instances are stored in valuePointers,
     * with the values for each particular option being contiguous.
     */
    i = 0;
    for (optNum = 0; optNum < numConf; optNum++) {
        unsigned outind = optConf[optNum].outind;
        confval* optval;

        confdata->optVals[optNum].num = 0;
        confdata->optVals[optNum].values = &valuePointers[i];
        if (outind != 0) {
            confdata->map[outind & ~CF_NOTFLAG] = &confdata->optVals[optNum];
        }
        for (optval = perOptRecordsFirst[optNum]; optval != NULL;
                 optval = optval->next) {
            confdata->optVals[optNum].num++;
            valuePointers[i++] = optval;
        }
    }
    free(perOptRecordsFirst);
    return(NULL);
}

/*
 * Free the malloced data stored in confdata elements by ProcOpts()
 */
void
confdataFree(confdata_t *confdata) {
    if (confdata->map != NULL) {
        free(confdata->map);
        confdata->map = NULL;
    }
    free(confdata->optVals[0].values);
    free(confdata->optVals);
    confdata->optVals = NULL;
}
