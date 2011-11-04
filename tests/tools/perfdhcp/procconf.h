#ifndef PROCCONF_H
#define PROCCONF_H

#include <limits.h>	/* for UINT_MAX */

typedef enum {
    CF_CHAR,
    CF_STRING,
    CF_NE_STRING,
    CF_INT,
    CF_NON_NEG_INT,
    CF_POS_INT,
    CF_FLOAT,
    CF_NON_NEG_FLOAT,
    CF_POS_FLOAT,
    CF_SWITCH,
    CF_NOCONF,	/* option to specify that config file should not be read */
    CF_PDEBUG,	/* option to turn on debugging, with positive integer value */
    CF_SDEBUG,	/* option to turn on debugging, without a value */
    CF_ENDLIST	/* End of option list */
} cf_type;

typedef enum {
    CF_NONE, CF_ARGS, CF_FILE
} cf_source;

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
    unsigned outind;	/* Single-character option, or option output index */
    char *varname;	/* Long name, for config file and long option */
    cf_type type;	/* Option type */
    const void *addr;	/* Address of variable associated with this option */
    int value;		/* Value to assign to switch options */
} confvar_t;

/*
 * Structure for returning assigned values.
 */
typedef struct confval_struct {
    const char *strval;	/* String form of value */
    cf_source source;	/* Where value was taken from */
    unsigned index;	/* Relative position of this instance */
    union {
	int intval;
	unsigned int nnint;
	double floatval;
	const char *string;
	int switchval;
	char charval;
    } value;
    struct confval_struct *next;
} confval;

/* Information about the values assigned to a particular option */
typedef struct {
    int num;		/* number of instances of this option */
    confvar_t *confvar;	/* which option descriptor this corresponds to */
    confval **values;	/* Start of pointers to values for this option */
} cf_option;

typedef struct {
    cf_option *optVals;	/* All option values */
    cf_option **map;	/* Option values indexed by option-char/option-index */
} confdata_t;

const char *
procOpts(int *argc, const char **argv[], const confvar_t optConf[],
	confdata_t *confdata, const char confFile[], const char name[],
	const char usage[]);

#endif
