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

/* $Id: msgbuf.h,v 1.2 2002/12/06 21:06:27 lidl Exp $ */

#ifndef MSGQ_MSGBUF_H
#define MSGQ_MSGBUF_H

#include <isc/region.h>

typedef struct _msgbuf msgbuf_t;

/*
 * A buffer.
 */
struct _msgbuf {
	int ref;
	isc_region_t r;
};

msgbuf_t *msgbuf_create(isc_mem_t *mctx, unsigned int);
void msgbuf_detach(isc_mem_t *mctx, msgbuf_t **);
msgbuf_t *msgbuf_attach(msgbuf_t *);

#endif /* MSGQ_MSGBUF_H */
