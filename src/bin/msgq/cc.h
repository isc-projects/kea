/*
 * Copyright (C) 2002  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: cc.h,v 1.5 2002/12/06 21:06:27 lidl Exp $ */

#ifndef MSGQ_CC_H
#define MSGQ_CC_H

#include <isc/buffer.h>
#include <isc/types.h>

/*
 * Item types and data lengths.
 */
#define ITEM_UNDEFINED	0x00
#define ITEM_BLOB	0x01
#define ITEM_HASH	0x02
#define ITEM_LIST	0x03
#define ITEM_NULL	0x04
#define ITEM_UTF8   0x08
#define ITEM_MASK	0x0f

#define LENGTH_32	0x00
#define LENGTH_16	0x10
#define LENGTH_8	0x20
#define LENGTH_MASK	0x30

typedef struct {
	/* Set by caller */
	char *tag;	/* the target of our search */
	u_int8_t tlen;	/* length of tag name */

	/* Set by function */
	u_int8_t type;	/* the item type found */
	u_int32_t dlen;  /* the length of the item */
	void *data;	/* a pointer to the data for this item */
} ccsearch_t;

typedef struct {
	isc_buffer_t b;
} ccmsg_t;

typedef int (*logfunc_t)(void *, const char *, ...);

/*
 * Given a NULL-terminated array of ccsearch_t, searches the message
 * and fills it in.  If logging is needed, it will use the logging function
 * to log, or now logging if NULL.
 */
int cc_search(logfunc_t, void *, ccsearch_t *, void *, unsigned int);

/*
 * Returns 1 if the type, dlen, and data matches.
 */
int cc_matchdata(ccsearch_t *, u_int32_t, void *, u_int32_t);

/*
 * Find the tag in the ccsearch structure, or return NULL if not found.
 */
ccsearch_t *cc_findtag(ccsearch_t *, char *, u_int32_t);

/*
 * Initialize a ccmsg_t using the buffer provided.
 */
void ccmsg_init(ccmsg_t *, void *, unsigned int);

/*
 * Add a data item to the buffer.
 */
void ccmsg_add(ccmsg_t *, u_int32_t, char *, u_int32_t, char *, u_int32_t);

/*
 * "render" the message.  This really just returns its length.
 */
u_int32_t ccmsg_render(ccmsg_t *);

#endif /* MSGQ_CC_H */
