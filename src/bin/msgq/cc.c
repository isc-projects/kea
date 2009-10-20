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

/* $Id: cc.c,v 1.6 2002/12/06 21:06:26 lidl Exp $ */

#include <stdlib.h>
#include <string.h>

#include <isc/buffer.h>
#include <isc/util.h>

#include "cc.h"

#define MSG_MAGIC 0x536b616e

int
cc_matchdata(ccsearch_t *c, u_int32_t type, void *data, u_int32_t dlen)
{
	if (c->type == type
	    && c->dlen == dlen
	    && memcmp(c->data, data, dlen) == 0)
		return 1;

	return 0;
}

ccsearch_t *
cc_findtag(ccsearch_t *cc, char *tag, u_int32_t tlen)
{
	ccsearch_t *c;

	c = cc;
	while (c->tag != NULL) {
		if (c->tlen == tlen
		    && memcmp(c->tag, tag, tlen) == 0)
			return c;
		c++;
	}

	return NULL;
}

int
cc_search(logfunc_t lf, void *lfarg, ccsearch_t *cc,
	  void *msg, unsigned int msglen)
{
	isc_buffer_t b;
	u_int32_t magic;
	ccsearch_t *c;
	u_int32_t item_type, item_code, item_lencode;
	u_int32_t item_len, tag_len;
	char *tag_name, *item_ptr;
	int total, n;

	n = 0;
	c = cc;
	while (c->tag != NULL) {
		c->type = ITEM_UNDEFINED;
		c->dlen = 0;
		c->data = 0;

		c++;
		n++;
	}

	if (n == 0)
		return 0;
	total = n;

	isc_buffer_init(&b, msg, msglen);
	isc_buffer_add(&b, msglen);

	if (isc_buffer_remaininglength(&b) < 4)
		return -1;

	magic = isc_buffer_getuint32(&b);
	if (magic != MSG_MAGIC) {
		if (lf != NULL)
			lf(lfarg, "BAD PACKET: MAGIC == %x", magic);
		return -1;
	}

	/*
	 * Walk the buffer, remembering when we find important tags.
	 * We'll set pointers and remember the lengths of:
	 *    to from type group instance
	 *
	 * We assume all of these are at the top level (it's our protocol,
	 * so this is pretty safe) and we only decode the bits we need.
	 * This is by no means a general purpose decoder.
	 */
	while (n != 0 && isc_buffer_remaininglength(&b) > 0) {
		if (isc_buffer_remaininglength(&b) < 1) {
			if (lf != NULL)
				lf(lfarg, "PKTFMT tag len");
			return -1;
		}
		tag_len = isc_buffer_getuint8(&b);

		if (isc_buffer_remaininglength(&b) < tag_len) {
			if (lf != NULL)
				lf(lfarg, "PKTFMT tag (len %d)");
			return -1;
		}
		tag_name = isc_buffer_current(&b);
		isc_buffer_forward(&b, tag_len);

		if (isc_buffer_remaininglength(&b) < 1) {
			if (lf != NULL)
				lf(lfarg, "PKTFMT len/type");
			return -1;
		}
		item_type = isc_buffer_getuint8(&b);

		item_code = item_type & ITEM_MASK;
		item_lencode = item_type & LENGTH_MASK;

		/*
		 * Crack out the message length.
		 */
		item_len = 0;
		item_ptr = NULL;
		if (item_code != ITEM_NULL) {
			switch (item_lencode) {
			case LENGTH_8:
				if (isc_buffer_remaininglength(&b) < 1) {
					if (lf != NULL)
						lf(lfarg, "PKTFMT (len8)");
					return -1;
				}
				item_len = isc_buffer_getuint8(&b);
				break;
			case LENGTH_16:
				if (isc_buffer_remaininglength(&b) < 2) {
					if (lf != NULL)
						lf(lfarg, "PKTFMT (len16)");
					return -1;
				}
				item_len = isc_buffer_getuint16(&b);
				break;
			case LENGTH_32:
				if (isc_buffer_remaininglength(&b) < 4) {
					if (lf != NULL)
						lf(lfarg, "PKTFMT (len32)");
					return -1;
				}
				item_len = isc_buffer_getuint32(&b);
				break;
			default:
				if (lf != NULL)
					lf(lfarg, "PKTFMT (len code 0x%02x)",
				   item_lencode);
				return -1;
			}

			if (isc_buffer_remaininglength(&b) < item_len) {
				if (lf != NULL)
					lf(lfarg, "PKTFMT (item length %d, remaining %d)",
					   item_len,
					   isc_buffer_remaininglength(&b));
				return -1;
			}
			item_ptr = isc_buffer_current(&b);
			isc_buffer_forward(&b, item_len);
		}

		c = cc;
		while (c->tag != NULL) {
			if (c->tlen == tag_len
			    && memcmp(c->tag, tag_name, tag_len) == 0) {
				    if (c->type != ITEM_UNDEFINED)
					    break;
				    c->type = item_code;
				    c->data = item_ptr;
				    c->dlen = item_len;
				    n--;
				    break;
			}
			c++;
		}
	}

	return (total - n);
}

void
ccmsg_init(ccmsg_t *msg, void *buf, unsigned int buflen)
{
	isc_buffer_init(&msg->b, buf, buflen);

	isc_buffer_putuint32(&msg->b, MSG_MAGIC);
}

void
ccmsg_add(ccmsg_t *msg, u_int32_t type, char *tag, u_int32_t tlen,
	  char *data, u_int32_t dlen)
{
	isc_buffer_putuint8(&msg->b, tlen);
	isc_buffer_putmem(&msg->b, tag, tlen);

	if (dlen < 0x000000ff) {
		type |= LENGTH_8;
		isc_buffer_putuint8(&msg->b, type);
		isc_buffer_putuint8(&msg->b, dlen);
		isc_buffer_putmem(&msg->b, data, dlen);
	} else if (dlen < 0x0000ffff) {
		type |= LENGTH_16;
		isc_buffer_putuint8(&msg->b, type);
		isc_buffer_putuint16(&msg->b, dlen);
		isc_buffer_putmem(&msg->b, data, dlen);
	} else {
		type |= LENGTH_32;
		isc_buffer_putuint8(&msg->b, type);
		isc_buffer_putuint32(&msg->b, dlen);
		isc_buffer_putmem(&msg->b, data, dlen);
	}
}

u_int32_t
ccmsg_render(ccmsg_t *msg)
{
	return isc_buffer_usedlength(&msg->b);
}
