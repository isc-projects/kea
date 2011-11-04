/*
 * procopts: process command line options and config file variables.
 * This is still more or less a first cut (despite the rewrite!)
 * 2000-07-22 John H. DuBois III (john@armory.com)
 * 2007-04-28 2.0 Added command line processing.  Largely rewritten.
 * 2011-10-30 Cleaned up.  Added double types and out-of-range checking.
 */

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include "procconf.h"

static char errmsg[256];	/* for returning error descriptions */
static const char *pc_name;
static const char *pc_usage;
static unsigned debugLevel = 0;		/* set by debug option */
static int readConf = 1;		/* should config file be read? */
#define VERBOSE_DEBUG 7

#define INTERNAL_ERROR -1
#define USAGE_ERROR -2

/*
 * error: printf-style interface to print an error message or write it into
 * global errmsg.
 */
static void
error(const int errtype, const char *format, ...)
{
    va_list ap;

    va_start(ap,format);
    if (pc_usage != NULL) {	/* error messages should be printed directly */
	fprintf(stderr, "%s: ", pc_name);
	vfprintf(stderr, format, ap);
	putc('\n', stderr);
	if (errtype == USAGE_ERROR)
	    fputs(pc_usage, stderr);
	exit(errtype == USAGE_ERROR ? 2 : 1);
    }
    else
	vsnprintf(errmsg, sizeof(errmsg), format, ap);
    va_end(ap);
}

static void *
pc_malloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL)
	error(INTERNAL_ERROR, "Out of memory");
    return ret;
}

static void
opterror(const char *expected, const char *value, const confvar_t *varDesc,
	const char filename[], const char *detail)
{
    if (detail == NULL)
	detail = "";
    if (filename == NULL)
	error(USAGE_ERROR,
		"Invalid value given for option -%c: expected %s, got: %s%s",
		varDesc->outind, expected, value, detail);
    else
	error(USAGE_ERROR, "Invalid value given in configuration file \"%s\""
		" for option %s: expected %s, got: %s%s",
		filename, varDesc->varname, expected, value, detail);
}

/*
 * Add an option flag or value assignment to the options database.
 * This does all option-type-specific processing, and generates linked lists
 * of option structures.
 *
 * Input variables:
 * source is the source the option came from (command line, config file, etc.)
 * value is the string value assigned to the option, for options that take
 *     values.
 * varDesc is the description structure for this option.
 * filename is the configuration file name, if this option came from a config
 *     file, else null.
 *
 * Output variables:
 * The option value is stored in the option list pointed to by first.
 * last is used to track the last record in each option list, so option values
 * can be appended easily.
 *
 * Return value:
 * 0 if option was ignored.
 * 1 if option was processed & added to option chain.
 * On error, a string describing the error is stored in the global errmsg and
 * -1 is returned.
 */
static int
addOptVal(const cf_source source, const char *value, const confvar_t *varDesc,
	confval **first, confval **last, const char filename[])
{
    const void *addr;
    confval data, *ret_data;
    int seen = *first != NULL;
    char *ptr;
    int err;

     /* if first instance of this option, store result to given addr */
    addr = seen ? NULL : varDesc->addr;
    switch (varDesc->type) {
    case CF_CHAR:
	if (strlen(value) > 1) {	/* length 0 is OK; gives null char */
	    opterror("a single character", value, varDesc, filename, NULL);
	    return -1;
	}
	data.value.charval = *value;
	if (addr != NULL)
	    *(char *) addr = *value;
	break;
    case CF_STRING:
    case CF_NE_STRING:
	if (varDesc->type == CF_NE_STRING && *value == '\0') {
	    opterror("a non-empty string", value, varDesc, filename, NULL);
	    return -1;
	}
	data.value.string = value;
	if (addr != NULL)
	    *(const char **) addr = value;
	break;
    case CF_INT:
    case CF_NON_NEG_INT:
    case CF_POS_INT:
    case CF_PDEBUG:
	/* todo: check for out-of-range result */
	errno = 0;
	data.value.intval = strtol(value, &ptr, 0);
	if (errno == ERANGE) {
	    opterror("an integer", value, varDesc, filename,
		    " (out of range)");
	    return -1;
	}
	err = *value == '\0' || *ptr != '\0';
	switch (varDesc->type) {
	case CF_INT:
	    if (err) {
		opterror("an integer", value, varDesc, filename, NULL);
		return -1;
	    }
	    break;
	case CF_NON_NEG_INT:
	    if (err || data.value.intval < 0) {
		opterror("a non-negative integer", value, varDesc, filename,
			NULL);
		return -1;
	    }
	    data.value.nnint = data.value.intval;
	    break;
	case CF_POS_INT:
	case CF_PDEBUG:
	    if (err || data.value.intval <= 0) {
		opterror("a positive integer", value, varDesc, filename, NULL);
		return -1;
	    }
	    data.value.nnint = data.value.intval;
	    break;
	default:
	    /* To avoid complaints from -Wall */
	    ;
	}
	if (addr != NULL)
	    *(int *) addr = data.value.intval;
	if (!seen && varDesc->type == CF_PDEBUG)
	    debugLevel = data.value.intval;
	break;
    case CF_FLOAT:
    case CF_NON_NEG_FLOAT:
    case CF_POS_FLOAT:
	/* todo: check for out-of-range result */
	errno = 0;
	data.value.floatval = strtod(value, &ptr);
	if (errno == ERANGE) {
	    opterror("a number", value, varDesc, filename, " (out of range)");
	    return -1;
	}
	err = *value == '\0' || *ptr != '\0';
	switch (varDesc->type) {
	case CF_FLOAT:
	    if (err) {
		opterror("a number", value, varDesc, filename, NULL);
		return -1;
	    }
	    break;
	case CF_NON_NEG_FLOAT:
	    if (err || data.value.floatval < 0) {
		opterror("a non-negative number", value, varDesc, filename,
			NULL);
		return -1;
	    }
	    break;
	case CF_POS_FLOAT:
	    if (err || data.value.floatval <= 0) {
		opterror("a positive number", value, varDesc, filename, NULL);
		return -1;
	    }
	    break;
	default:
	    /* To avoid complaints from -Wall */
	    ;
	}
	if (addr != NULL)
	    *(double *) addr = data.value.floatval;
	break;
    case CF_SWITCH:
    case CF_NOCONF:
    case CF_SDEBUG:
	/* If option not turned on, ignore */
	if (source == CF_FILE && *value != '1')
	    return 0;
	data.value.switchval = varDesc->value;
	value = "1";	/* for debugging */
	if (addr != NULL)
	    *(int *) addr = varDesc->value;
	if (!seen)
	    switch (varDesc->type) {
		case CF_NOCONF:
		    readConf = 0;
		    break;
		case CF_SDEBUG:
		    debugLevel = 9;
		    break;
		default:
		    /* To avoid complaints from -Wall */
		    ;
	    }
	break;
    case CF_ENDLIST:
	/* To avoid complaints from -Wall */
	;
    }
    data.strval = value;
    data.source = source;
    data.next = NULL;
    if ((ret_data = (confval *)pc_malloc(sizeof(confval))) == NULL)
	return -1;
    *ret_data = data;
    if (seen)
	(*last)->next = ret_data;
    else
	*first = ret_data;
    *last = ret_data;
    if (debugLevel >= VERBOSE_DEBUG)
	fprintf(stderr, "Option %c (%s) gets value \"%s\" from %s%s\n",
		0 < varDesc->outind && varDesc->outind < 256 ?
		varDesc->outind : '-',
		varDesc->varname == NULL ? "-" : varDesc->varname, value,
		source == CF_ARGS ? "command line" : "config file", seen ?
			" (already seen)" : "");
    return 1;
}

/*
 * This currently depends on defread().
 * A CDDL version of the def* library exists:
 *http://www.opensource.apple.com/source/autofs/autofs-207/automountlib/deflt.c
 * But, this should really be rewritten to not use defread().
 */
#ifdef DEFREAD
/*
 * Input variables:
 * filename: Name of configuration file.  If it begins with ~/, the ~ is
 *     replaced with the invoking user's home directory.
 * optConf[]: Option description structures.
 *
 * Output variables:
 * See addOptVal().
 *
 * Return value:
 * If the config file does not exist, 0.
 * Otherwise, the number of variable assignments read is returned (which may
 * also result in a 0 return value).
 * On error, a string describing the error is stored in the global errmsg and
 * -1 is returned.
 */
static int
procConfFile(const char filename[], const confvar_t optConf[],
	confval *first[], confval *last[]) {
    int count;
    char *home;
    int ind;

    if (!strncmp(filename, "~/", 2)) {
	char *path;

	if (!(home = getenv("HOME"))) {
	    if (debugLevel > 2)
		fprintf(stderr, "HOME environment variable not set.\n");
	    return 0;
	}
	if ((path = pc_malloc(strlen(home) + strlen(filename))) == NULL)
	    return -1;
	strcpy(path, home);
	strcat(path, filename+1);
	if (defopen(path)) {
	    free(path);
	    return 0;
	}
	free(path);
    }
    else if (defopen((char *)filename)) {
	if (debugLevel > 2)
	    fprintf(stderr, "Config file '%s' not found.\n", filename);
	return 0;
    }
    count = 0;
    for (ind = 0; optConf[ind].type != CF_ENDLIST; ind++) {
	char buf[128];
	char *s;

	if (optConf[ind].varname == NULL)
	    continue;
	strncpy(buf, optConf[ind].varname, 126);
	strcat(buf, "=");
	if ((s = defread(buf)) != NULL) {
	    int ret;

	    if ((s = strdup(s)) == NULL) {
		error(INTERNAL_ERROR, "Out of memory");
		return -1;
	    }
	    switch ((ret = addOptVal(CF_FILE, s, &optConf[ind], &first[ind],
		    &last[ind], filename))) {
	    case 1:
		count++;
		break;
	    case 0:
		break;
	    default:
		return ret;
	    }
	}
    }
    return count;
}
#endif

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
procCmdLineArgs(int *argc, const char **argv[], const confvar_t optConf[],
	confval **first, confval **last)
{
    char *p;
    extern char *optarg;	/* For getopt */
    extern int optind;		/* For getopt */
    extern int optopt;		/* For getopt */
    char optstr[514];
    unsigned optCharToConf[256];
    int optchar;
    unsigned confNum;
    int count = 0;

    optind = 1;
    p = optstr;
    *(p++) = ':';
    for (confNum = 0; optConf[confNum].type != CF_ENDLIST; confNum++) {
	unsigned outind = optConf[confNum].outind;
	if (outind < 256 && isprint(outind)) {
	    *(p++) = (char) outind;
	    switch (optConf[confNum].type) {
	    case CF_SWITCH:
	    case CF_NOCONF:
	    case CF_SDEBUG:
		break;
	    default:
		*(p++) = ':';
		break;
	    }
	    optCharToConf[outind] = confNum;
	}
    }
    *p = '\0';
    while ((optchar = getopt(*argc, const_cast<char **>(*argv), optstr)) != -1) {
	int ind;
	int ret;

	if (optchar == '?') {
	    error(USAGE_ERROR, "Unknown option character '%c'", optopt);
	    return -1;
	}
	else if (optchar == ':') {
	    error(USAGE_ERROR, "No value given for option -%c", optopt);
	    return -1;
	}
	ind = optCharToConf[optchar];
	switch (ret = addOptVal(CF_ARGS, optarg, &optConf[ind], &first[ind],
		&last[ind], NULL)) {
	case 1:
	    count++;
	    break;
	case 0:
	    break;
	default:
	    return ret;
	}
    }
    *argc -= optind;
    *argv += optind;
    return count;
}

/*
 * Input variables:
 * argc, argv: Command line data.
 * optConf[]: Option description structures.
 * confFile[]: Configuration file, or NULL if none provided.
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
const char *
procOpts(int *argc, const char **argv[], const confvar_t optConf[],
	confdata_t *confdata, const char confFile[], const char name[],
	const char usage[])
{
    /* Number of configuration options given in optConf */
    unsigned numConf;
    /* First & last records in the linked list maintained for each option */
    confval **first, **last;
    unsigned maxOptIndex = 0;	/* The highest option index number seen */
    /* number of option instances + assignments given */
    int numOptsFound;
    unsigned optNum;
    unsigned i;
    confval **valuePointers;

    pc_name = name;
    pc_usage = usage;
    for (numConf = 0; optConf[numConf].type != CF_ENDLIST; numConf++) {
	unsigned outind = optConf[numConf].outind;

	if ((outind & ~CF_NOTFLAG) > maxOptIndex)
	    maxOptIndex = outind & ~CF_NOTFLAG;
    }
    if ((first = (confval **)pc_malloc(sizeof(confval *) * numConf)) == NULL ||
	    (last =
	    (confval **)pc_malloc(sizeof(confval *) * numConf)) == NULL)
	return errmsg;
    memset(first, '\0', sizeof(confval *) * numConf);
    memset(last, '\0', sizeof(confval *) * numConf);

    if ((numOptsFound =
	    procCmdLineArgs(argc, argv, optConf, first, last)) < 0)
	return errmsg;
    if (readConf && confFile != NULL) {
#ifdef DEFREAD
	int ret;

	if ((ret = procConfFile(confFile, optConf, first, last)) < 0)
	    return errmsg;
	else
	    nummOptsFound += ret;
#else
	error(INTERNAL_ERROR, "Built without defread!");
	return errmsg;
#endif
    }

    free(last);

    /*
     * All options have been read & initial processing done.
     * An array of pointers is now generated for the options.
     */
    if ((valuePointers =
	    (confval **)pc_malloc(sizeof(confval *) * numOptsFound)) == NULL ||
	    (confdata->optVals =
	    (cf_option *)pc_malloc(sizeof(cf_option) * numConf)) == NULL)
	return errmsg;
    /* If option index numbers are used, allocate a map for them */
    if (maxOptIndex != 0) {
	if ((confdata->map =
		(cf_option **)pc_malloc(sizeof(cf_option) * (maxOptIndex+1)))
		== NULL)
	    return errmsg;
	memset(confdata->map, '\0', sizeof(confval *) * (maxOptIndex+1));
    }

    /*
     * Store the linked lists of option values into arrays.
     * Pointers to all option instances are stored in valuePointers,
     * with the values for each particular option being contiguous.
     */
    i = 0;
    for (optNum = 0; optNum < numConf; optNum++) {
	unsigned outind = optConf[optNum].outind;
	confval *optval;

	confdata->optVals[optNum].num = 0;
	confdata->optVals[optNum].values = &valuePointers[i];
	if (outind != 0)
	    confdata->map[outind & ~CF_NOTFLAG] = &confdata->optVals[optNum];
	for (optval = first[optNum]; optval != NULL; optval = optval->next) {
	    confdata->optVals[optNum].num++;
	    valuePointers[i++] = optval;
	}
	if (debugLevel > 5)
	    fprintf(stderr, "Option %c (%s) got %d values\n",
		    outind == 0 ? '-' : outind,
		    optConf[optNum].varname == NULL ? "-" :
		    optConf[optNum].varname,         
		    confdata->optVals[optNum].num);
    }
    free(first);
    return NULL;
}
