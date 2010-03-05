/*
 *  sha1.h
 *
 *  Description:
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 *
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *
 *      Please read the file sha1.c for more information.
 *
 */

#ifndef _SHA1_H_
#define _SHA1_H_

#include <stdint.h>
/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
 *  int_least16_t    integer of >= 16 bits
 *
 */

enum {
    SHA_SUCCESS = 0,
    SHA_NULL,            /* Null pointer parameter */
    SHA_STATEERROR       /* called Input after Result */
};

enum {
    SHA1_HASHSIZE = 20
};

/*
 *  This structure will hold context information for the SHA-1
 *  hashing operation
 */
typedef struct SHA1Context
{
    uint32_t Intermediate_Hash[SHA1_HASHSIZE/4]; /* Message Digest */
    uint32_t Length_Low;                /* Message length in bits */
    uint32_t Length_High;               /* Message length in bits */
    int_least16_t Message_Block_Index;  /* Index into message block array */
    uint8_t Message_Block[64];          /* 512-bit message blocks */
    int Computed;                       /* Is the digest computed? */
    int Corrupted;                      /* Is the message digest corrupted? */
} SHA1Context;

/*
 *  Function Prototypes
 */
int SHA1Reset(SHA1Context *);
int SHA1Input(SHA1Context *, const uint8_t *, unsigned int);
int SHA1Result(SHA1Context *, uint8_t Message_Digest[SHA1_HASHSIZE]);

#endif
