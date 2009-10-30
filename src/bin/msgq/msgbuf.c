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

/* $Id: msgbuf.c,v 1.2 2002/12/06 21:06:27 lidl Exp $ */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <isc/mem.h>
#include <isc/util.h>

#include "msgbuf.h"
#include "cc.h"

msgbuf_t *
msgbuf_create(isc_mem_t *mctx, unsigned int length)
{
	msgbuf_t *mb;
	unsigned int len;

	len = sizeof(msgbuf_t);
	len += length;

	mb = isc_mem_get(mctx, len);
	RUNTIME_CHECK(mb != NULL);

	mb->ref = 1;
	mb->r.base = (unsigned char *)(mb + 1);
	mb->r.length = length;

	return (mb);
}

void
msgbuf_detach(isc_mem_t *mctx, msgbuf_t **mbp)
{
	msgbuf_t *mb = *mbp;
	unsigned int len;

	*mbp = NULL;

	INSIST(mb->ref > 0);
	mb->ref--;
	if (mb->ref == 0) {
		len = sizeof(msgbuf_t);
		len += mb->r.length;

		isc_mem_put(mctx, mb, len);
	}
}

msgbuf_t *
msgbuf_attach(msgbuf_t *mb)
{
	INSIST(mb->ref > 0);
	mb->ref++;

	return (mb);
}
