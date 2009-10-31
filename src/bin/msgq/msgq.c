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

/* $Id: msgq.c,v 1.30 2002/12/06 21:06:27 lidl Exp $ */

#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include <ctype.h>	/* for isprint() */
#include <time.h>	/* for time() */
#include <unistd.h>	/* for gethostname() */

#include <isc/app.h>
#include <isc/mem.h>
#include <isc/task.h>
#include <isc/socket.h>
#include <isc/timer.h>
#include <isc/util.h>

#include "msgbuf.h"
#include "cc.h"

#if !defined(MAXHOSTNAMELEN)
#define MAXHOSTNAMELEN 256
#endif

/*
 * Maximum amount of data we'll allow ourselves to receive as a single
 * message.
 */
#define RECV_MAX (1024 * 64)  /* largest single packet receive */

/*
 * Maximum size of an output queue
 */
#define SEND_MAXBUF (1024 * 128)  /* 128 kB maximum output buffer length */

/*
 * Each block of items has this many per allocation block.  This helps
 * reduce the number of allocations we perform.
 */
#define BUNDLE_SIZE 16

/*
 * Size of internal hash tables, and the hash init value.  The former can
 * be changed to any power of two; the latter should not be changed.
 */
#define HASH_LEN 1024
#define HASH_INIT 94760667

/*
 * Default messageq port
 */
#ifndef MSGQ_DEFAULT_PORT
#define MSGQ_DEFAULT_PORT 9912
#endif

typedef struct _lsock lsock_t;
typedef struct _connection connection_t;
typedef struct _sub sub_t;
typedef struct _sublist sublist_t;
typedef struct _msgq msgq_t;

struct _lsock {
	isc_socket_t *sock;
	ISC_LINK(lsock_t) link;
};

struct _connection {
	isc_socket_t *sock;

	char lname[128];
	unsigned int lnamelen;
	u_int32_t lhash;

	u_int32_t recvlen;
	msgbuf_t *inbuf;

	isc_boolean_t writing;
	u_int32_t out_pending;
	u_int32_t sendlen;  /* current send length in network byte order */
	ISC_LIST(msgq_t) outbuf;

	ISC_LINK(connection_t) link;
};

struct _sub {
	unsigned int hash;
	unsigned char glen;
	char *group;
	unsigned char ilen;
	char *instance;

	ISC_LIST(sublist_t) members;
	ISC_LINK(sub_t) link;
};

#define SUBTYPE_NORMAL	1
#define SUBTYPE_MEONLY	2

/*
 * List of clients subscribed to this specific group/instance
 */
struct _sublist {
	int nused;

	connection_t *connection[BUNDLE_SIZE];
	int subtype[BUNDLE_SIZE];

	ISC_LINK(sublist_t) link;
};

/*
 * output buffer queues
 */
struct _msgq {
	int add_idx;
	int del_idx;
	msgbuf_t *outbufs[BUNDLE_SIZE];

	ISC_LINK(msgq_t) link;
};

u_int16_t msgq_port = MSGQ_DEFAULT_PORT;

char hname[MAXHOSTNAMELEN];

ISC_LIST(sub_t) subs[HASH_LEN];
ISC_LIST(connection_t) cons;
ISC_LIST(lsock_t) lsocks;

isc_mem_t *mctx;
isc_taskmgr_t *manager;
isc_task_t *task;
isc_socketmgr_t *socketmgr;
isc_timermgr_t *timermgr;

unsigned int connection_counter = 0;

int con_log_level = LOG_DEBUG;

static void recv_len(isc_task_t *, isc_event_t *);
static void recv_data(isc_task_t *, isc_event_t *);
static void send_data(isc_task_t *, isc_event_t *);
static void sock_accept(isc_task_t *, isc_event_t *);

void sub_add(char *, unsigned int, char *, unsigned int,
	     char *, unsigned int, connection_t *);
void sub_del(char *, unsigned int, char *, unsigned int, connection_t *);
void sub_send(char *, unsigned int, char *, unsigned int,
	      char *, unsigned int, connection_t *, msgbuf_t *);
void sub_unsuball(connection_t *);
sub_t *sub_find(char *, unsigned int, char *, unsigned int,
		u_int32_t *, int *);

void con_add(isc_socket_t *);
void con_del(connection_t *);
void con_closeall(void);

void lsock_open(void);
void lsock_closeall(void);

static msgq_t *msgq_alloc(void);
void con_enqueue(connection_t *, msgbuf_t *);
void con_startwrite(connection_t *);
void process_packet(connection_t *);

static void
hexdump(const unsigned char *c, size_t len)
{
	int count = 0;

	printf("%4d: ", 0);
	while (len) {
		printf("%02x %c ", (*c & 0xff),
		       (isprint((*c & 0xff)) ? (*c & 0xff) : '.'));
		count++;
		c++;
		len--;
		if (count % 16 == 0)
			printf("\n%4d: ", count);
		else if (count % 8 == 0)
			printf(" | ");
	}
	printf("\n");
}

static inline u_int32_t
HASH(const void *data, size_t len, u_int32_t hash)
{
	const unsigned char *c = data;

	while (len-- != 0)
		hash = (hash * 11) + *c++;
	return (hash);
}

static inline u_int32_t
HASH_GROUP(const char *group, unsigned int glen,
	   const char *instance, unsigned int ilen)
{
	u_int32_t hash;

	hash = HASH(group, glen, HASH_INIT);
	if (instance != NULL)
		hash = HASH(instance, ilen, hash);

	return (hash);
}

void
con_log(connection_t *con, int level, const char *fmt, ...)
{
	va_list ap;

	if (level > con_log_level)
		return;

	fprintf(stderr, "con(%p): ", con);

	va_start(ap, fmt);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	fprintf(stderr, "\n");
}

static void
recv_data(isc_task_t *t, isc_event_t *ev)
{
	isc_socketevent_t *sev = (isc_socketevent_t *)ev;
	connection_t *con = sev->ev_arg;
	isc_region_t r;
	unsigned int n;

	if (sev->result != ISC_R_SUCCESS) {
		con_log(con, LOG_NOTICE,
			"recv_data got cancel or error, closing.");
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	if (sev->n != con->recvlen) {
		con_log(con, LOG_NOTICE,
			"Short read (expected %d, got %d)",
			con->recvlen, sev->n);
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	/*
	 * Pull our data, and throw away the event.
	 */
	r = sev->region;
	n = sev->n;
	isc_event_free(&ev);

	con_log(con, LOG_DEBUG, "got %d bytes", n);

	/*
	 * Process it.
	 */
	process_packet(con);
	msgbuf_detach(mctx, &con->inbuf);

	/*
	 * Set up to receive the next packet.
	 */
	r.base = (unsigned char *)&con->recvlen;
	r.length = 4;

	RUNTIME_CHECK(isc_socket_recv(con->sock, &r, 4, task, recv_len, con)
		      == ISC_R_SUCCESS);
}

static void
recv_len(isc_task_t *t, isc_event_t *ev)
{
	isc_socketevent_t *sev = (isc_socketevent_t *)ev;
	connection_t *con = sev->ev_arg;
	isc_region_t r;
	isc_buffer_t b;

	if (sev->result != ISC_R_SUCCESS) {
		con_log(con, LOG_NOTICE,
			"recv_len got cancel or error, closing");
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	if (sev->n != 4) {
		con_log(con, LOG_NOTICE,
			"Short read (expected 4, got %d)", sev->n);
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	/*
	 * Free the event here, since we no longer need anything from it.
	 * We put the data directly into our structure, so there is no
	 * need to use the socket event's data to determine where it went.
	 */
	isc_event_free(&ev);

	/*
	 * Remember network byte order.
	 */
	con->recvlen = ntohl(con->recvlen);

	con_log(con, LOG_DEBUG, "Expecting to receive %d bytes", con->recvlen);

	if (con->recvlen > RECV_MAX) {
		con_log(con, LOG_NOTICE, "Too much data, closing");
		con_del(con);
		return;
	}

	/*
	 * Allocate a receive buffer here.
	 */
	INSIST(con->inbuf == NULL);
	con->inbuf = msgbuf_create(mctx, con->recvlen + 4);

	isc_buffer_init(&b, con->inbuf->r.base, 4);
	isc_buffer_putuint32(&b, con->recvlen);

	r.base = con->inbuf->r.base + 4;
	r.length = con->recvlen;

	/*
	 * Start up a receive to receive that many bytes.
	 */
	RUNTIME_CHECK(isc_socket_recv(con->sock,
				      &r, con->recvlen,
				      task, recv_data, con)
		      == ISC_R_SUCCESS);
}

static void
sock_accept(isc_task_t *t, isc_event_t *ev)
{
	isc_socket_newconnev_t *sev = (isc_socket_newconnev_t *)ev;
	isc_socket_t *lsock = ev->ev_arg;
	isc_socket_t *sock = sev->newsocket;

	if (sev->result == ISC_R_SUCCESS) {
		RUNTIME_CHECK(isc_socket_accept(lsock, task,
						sock_accept, lsock)
			      == ISC_R_SUCCESS);

		con_add(sock);
	} else {
		printf("accept got cancel event\n");
	}

	isc_event_free(&ev);
}

void
handle_subscribe(connection_t *con, msgbuf_t *msgb, ccsearch_t *c)
{
	ccsearch_t *group;
	ccsearch_t *instance;
	ccsearch_t *subtype;

	group = cc_findtag(c, "group", 5);
	instance = cc_findtag(c, "instance", 8);
	subtype = cc_findtag(c, "subtype", 7);

	if (group == NULL || instance == NULL || subtype == NULL) {
		con_log(con, LOG_NOTICE,
			"Bad subscribe message, missing required args");
		return;
	}

	if (group->type != ITEM_DATA
	    || instance->type != ITEM_DATA
	    || subtype->type != ITEM_DATA) {
		con_log(con, LOG_NOTICE,
			"Bad subscribe, incorrect data types");
		return;
	}

	sub_add(group->data, group->dlen,
		instance->data, instance->dlen,
		subtype->data, subtype->dlen,
		con);
}

void
handle_unsubscribe(connection_t *con, msgbuf_t *msgb, ccsearch_t *c)
{
	ccsearch_t *group;
	ccsearch_t *instance;

	group = cc_findtag(c, "group", 5);
	instance = cc_findtag(c, "instance", 8);

	if (group == NULL || instance == NULL) {
		con_log(con, LOG_NOTICE,
			"Bad subscribe message, missing required args");
		return;
	}

	if (group->type != ITEM_DATA
	    || instance->type != ITEM_DATA) {
		con_log(con, LOG_NOTICE,
			"Bad subscribe, incorrect data types");
		return;
	}

	sub_del(group->data, group->dlen,
		instance->data, instance->dlen,
		con);
}

void
handle_send(connection_t *con, msgbuf_t *msgb, ccsearch_t *c)
{
	ccsearch_t *group;
	ccsearch_t *instance;
	ccsearch_t *to;

	group = cc_findtag(c, "group", 5);
	instance = cc_findtag(c, "instance", 8);
	to = cc_findtag(c, "to", 2);

	if (group == NULL || instance == NULL || to == NULL) {
		con_log(con, LOG_NOTICE,
			"Bad send message, missing required args");
		return;
	}

	if (group->type != ITEM_DATA
	    || instance->type != ITEM_DATA) {
		con_log(con, LOG_NOTICE, "Bad send, incorrect data types");
		return;
	}

	if (to->type != ITEM_DATA) {
		con_log(con, LOG_NOTICE, "Bad send, incorrect data types");
		return;
	}

	con_log(con, LOG_DEBUG, "recv group=%.*s instance=%.*s to=%.*s",
		group->dlen, group->data,
		instance->dlen, instance->data,
		to->dlen, to->data);

	sub_send(group->data, group->dlen,
		 instance->data, instance->dlen,
		 to->data, to->dlen,
		 con, msgb);
}

int
send_messages(sub_t *sub, connection_t *con, msgbuf_t *mb,
	      char *to, unsigned int tlen)
{
	sublist_t *sl;
	int sendcnt;
	int slot;
	int nused;
	u_int32_t lhash;

	sendcnt = 0;

	lhash = 0;  /* shut up -Wall warning */
	if (tlen > 0)
		lhash = HASH(to, tlen, HASH_INIT);

	sl = ISC_LIST_HEAD(sub->members);
	while (sl != NULL) {
		nused = sl->nused;
		for (slot = 0 ; slot < BUNDLE_SIZE && nused > 0 ; slot++) {
			connection_t *slcon = sl->connection[slot];
			int sltype = sl->subtype[slot];

			if (slcon == NULL)
				continue;
			nused--;
			if (slcon == con)
				continue;
			if (to == NULL) {
				if (sltype == SUBTYPE_MEONLY)
					continue;
				con_enqueue(slcon, mb);
				sendcnt++;
			} else {
				if (slcon->lnamelen == tlen
				    && slcon->lhash == lhash
				    && memcmp(slcon->lname, to, tlen) == 0) {
					con_enqueue(slcon, mb);
					return (1);
				}
			}
		}
		sl = ISC_LIST_NEXT(sl, link);
	}

	return (sendcnt);
}

void
sub_send(char *group, unsigned int glen, 
	 char *instance, unsigned int ilen,
	 char *to, unsigned int tlen,
	 connection_t *con, msgbuf_t *mb)
{
	sub_t *sub;

	if (ilen == 1 && memcmp(instance, "*", 1) == 0) {
		instance = NULL;
		ilen = 0;
	}

	if (tlen == 1 && memcmp(to, "*", 1) == 0) {
		to = NULL;
		tlen = 0;
	}

	/*
	 * First, send it to those specifically listening on this instance
	 */
	if (ilen > 0) {
		sub = sub_find(group, glen, instance, ilen, NULL, NULL);
		if (sub != NULL)
			send_messages(sub, con, mb, to, tlen);
	}


	/*
	 * And now to wildcard subscribers
	 */
	sub = sub_find(group, glen, NULL, 0, NULL, NULL);
	if (sub != NULL)
		send_messages(sub, con, mb, to, tlen);
}

void
handle_lname(connection_t *con, msgbuf_t *msgb, ccsearch_t *c)
{
	char buf[1024];
	ccmsg_t msg;
	unsigned int len;
	msgbuf_t *mb;
	isc_buffer_t b;

	ccmsg_init(&msg, buf, sizeof(buf));
	ccmsg_add(&msg, ITEM_DATA, "lname", 5, con->lname, con->lnamelen);
	ccmsg_add(&msg, ITEM_DATA, "type", 4, "getlname", 8);
	len = ccmsg_render(&msg);

	mb = msgbuf_create(mctx, len + 4);
	memcpy(mb->r.base + 4, buf, len);

	isc_buffer_init(&b, mb->r.base, 4);
	isc_buffer_putuint32(&b, len);

	con_enqueue(con, mb);
	msgbuf_detach(mctx, &mb);
}

void
process_packet(connection_t *con)
{
	int ret;
	ccsearch_t cc[] = {
		{ "to", 2, },
		{ "from", 4, },
		{ "group", 5, },
		{ "instance", 8, },
		{ "type", 4, },
		{ "subtype", 7, },
		{ NULL, }
	};
	ccsearch_t *c;
	msgbuf_t* mb;

	mb = con->inbuf;

	con_log(con, LOG_DEBUG, "Processing message (%d bytes)", mb->r.length);

	ret = cc_search((logfunc_t)con_log, con, cc,
			mb->r.base + 4, mb->r.length - 4);
	if (ret == 0)
		return;
	if (ret < 0) {
#if 1
		hexdump(mb->r.base, mb->r.length);
#endif
		return;
	}

#if 0
	c = cc;
	while (c->tag != NULL) {
		if (c->type != ITEM_UNDEFINED)
			con_log(con,
				"tag %.*s type 0x%02x len %d data %.*s",
				c->tlen, c->tag, c->type, c->dlen,
				c->dlen, c->data);
		c++;
	}
#endif

	c = cc_findtag(cc, "type", 4);

	if (cc_matchdata(c, ITEM_DATA, "send", 4)) {
		handle_send(con, mb, cc);
	} else if (cc_matchdata(c, ITEM_DATA, "getlname", 8)) {
		handle_lname(con, mb, cc);
	} else if (cc_matchdata(c, ITEM_DATA, "subscribe", 9)) {
		handle_subscribe(con, mb, cc);
	} else if (cc_matchdata(c, ITEM_DATA, "unsubscribe", 9)) {
		handle_unsubscribe(con, mb, cc);
	}
}

static msgq_t *
msgq_alloc(void)
{
	msgq_t *mq;

	mq = isc_mem_get(mctx, sizeof(*mq));
	RUNTIME_CHECK(mq != NULL);

	memset(mq, 0, sizeof(*mq));
	ISC_LINK_INIT(mq, link);

	return (mq);
}

void
con_enqueue(connection_t *con, msgbuf_t *mb)
{
	msgq_t *mq;

	con_log(con, LOG_DEBUG, "sending mb %p (refcnt %d)", mb, mb->ref);

	if (con->out_pending + mb->r.length > SEND_MAXBUF) {
		con_log(con, LOG_DEBUG,
			"Maximum output queue exceeded (%d max, %d hit)",
			SEND_MAXBUF, con->out_pending + mb->r.length);
		return;
	}

	/*
	 * If we need to, allocate a new msgq_t and put it on the end of
	 * the list.
	 */
	mq = ISC_LIST_TAIL(con->outbuf);
	if (mq == NULL) {
		mq = msgq_alloc();
		ISC_LIST_APPEND(con->outbuf, mq, link);
	}

	/*
	 * Pull off the last item on the list.  If there is no room, allocate
	 * another msgq_t and append it.
	 */
	mq = ISC_LIST_TAIL(con->outbuf);
	if (mq->add_idx == BUNDLE_SIZE) {
		mq = msgq_alloc();
		ISC_LIST_APPEND(con->outbuf, mq, link);
	}

	mq->outbufs[mq->add_idx] = msgbuf_attach(mb);
	mq->add_idx++;
	con->out_pending += mb->r.length;

	con_startwrite(con);
}

/*
 * Callback for "sending of the data is complete"
 */
static void
send_data(isc_task_t *task, isc_event_t *ev)
{
	isc_socketevent_t *sev = (isc_socketevent_t *)ev;
	connection_t *con = sev->ev_arg;
	msgq_t *mq;
	msgbuf_t *mb;

	con_log(con, LOG_DEBUG,
		"Send of data complete, result %d", sev->result);

	if (sev->result != ISC_R_SUCCESS) {
		con_log(con, LOG_NOTICE,
			"send_data got cancel or error, closing");
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	/*
	 * Pull the current msgbuf off the top of the list.
	 */
	mq = ISC_LIST_HEAD(con->outbuf);
	mb = mq->outbufs[mq->del_idx];

	if (sev->n != mb->r.length) {
		con_log(con, LOG_ERR, "Short write (expected %d, got %d)",
			mb->r.length, sev->n);
		isc_event_free(&ev);
		con_del(con);
		return;
	}

	/*
	 * Remove the sent msgbuf from the linked list, and free the msgq
	 * part if we've consumed everything.
	 */
	mq->outbufs[mq->del_idx] = NULL;
	mq->del_idx++;
	if (mq->del_idx >= mq->add_idx) {
		con_log(con, LOG_DEBUG,
			"freeing mq %p (add_idx %d, del_idx %d)",
			mq, mq->add_idx, mq->del_idx);
		ISC_LIST_UNLINK(con->outbuf, mq, link);
		isc_mem_put(mctx, mq, sizeof(*mq));
	}
	con->out_pending -= mb->r.length;
	msgbuf_detach(mctx, &mb);

	isc_event_free(&ev);

	con->writing = ISC_FALSE;
	mq = ISC_LIST_HEAD(con->outbuf);
	if (mq == NULL)
		return;
	con_startwrite(con);
}

void
con_startwrite(connection_t *con)
{
	msgq_t *mq;
	msgbuf_t *mb;

	if (con->writing)
		return;

	mq = ISC_LIST_HEAD(con->outbuf);
	if (mq == NULL)
		return;

	con->writing = ISC_TRUE;

	mb = mq->outbufs[mq->del_idx];
	con->sendlen = htonl(mb->r.length);

	RUNTIME_CHECK(isc_socket_send(con->sock, &mb->r, task, send_data, con)
		      == ISC_R_SUCCESS);
}

sub_t *
sub_find(char *group, unsigned int glen, 
	 char *instance, unsigned int ilen,
	 u_int32_t *hashp, int *bucketp)
{
	sub_t *sub;
	u_int32_t hash;
	int bucket;

	hash = HASH_GROUP(group, glen, instance, ilen);
	bucket = hash & (HASH_LEN - 1);

	if (hashp != NULL)
		*hashp = hash;
	if (bucketp != NULL)
		*bucketp = bucket;

	sub = ISC_LIST_HEAD(subs[bucket]);
	while (sub != NULL) {
		if (sub->hash == hash
		    && sub->glen == glen
		    && sub->ilen == ilen
		    && memcmp(sub->group, group, glen) == 0
		    && (instance == NULL ? 1 : memcmp(sub->instance,
						      instance, ilen) == 0))
			break;

		sub = ISC_LIST_NEXT(sub, link);
	}

	return (sub);
}

void
sub_cleanup(void)
{
	sub_t *sub;
	sublist_t *sublist;
	int bucket;
	int slot;

	for (bucket = 0 ; bucket < HASH_LEN ; bucket++) {
		sub = ISC_LIST_HEAD(subs[bucket]);
		while (sub != NULL) {
			sublist = ISC_LIST_HEAD(sub->members);
			while (sublist != NULL) {
				for (slot = 0 ; slot < BUNDLE_SIZE ; slot++) {
					sublist->connection[slot] = NULL;
					sublist->subtype[slot] = 0;
				}
				sublist->nused = 0;
				ISC_LIST_UNLINK(sub->members, sublist, link);

				isc_mem_put(mctx, sublist, sizeof(sublist_t));
				sublist = ISC_LIST_HEAD(sub->members);
			}

			isc_mem_put(mctx, sub->group, sub->glen + sub->ilen);
			ISC_LIST_UNLINK(subs[bucket], sub, link);
			isc_mem_put(mctx, sub, sizeof(sub_t));

			sub = ISC_LIST_HEAD(subs[bucket]);
		}
	}
}

/*
 * Add a new subscription.
 */
void
sub_add(char *group, unsigned int glen, 
	char *instance, unsigned int ilen,
	char *subtype, unsigned int stlen,
	connection_t *con)
{
	sub_t *sub;
	sublist_t *sublist;
	u_int32_t hash;
	int bucket;
	int slot;
	int stype;

	con_log(con, LOG_NOTICE, "sub_add: %.*s.%.*s type %.*s",
		glen, group, ilen, instance, stlen, subtype);

	if (stlen == 6 && memcmp(subtype, "normal", 6) == 0)
		stype = SUBTYPE_NORMAL;
	else if (stlen == 6 && memcmp(subtype, "meonly", 6) == 0)
		stype = SUBTYPE_MEONLY;
	else
		return;

	/*
	 * If the instance is NULL or the instance length is 0,
	 * this is a wildcard subscribe (all messages in the group).
	 * Additionally, handle the case where the instance is "*",
	 * and normalize it so we can treat it as the same thing below.
	 */
	if (ilen == 1 && memcmp(instance, "*", 1) == 0) {
		instance = NULL;
		ilen = 0;
	}

	sub = sub_find(group, glen, instance, ilen, &hash, &bucket);

	if (sub == NULL) {
		sub = isc_mem_get(mctx, sizeof(sub_t));
		RUNTIME_CHECK(sub != NULL);
		memset(sub, 0, sizeof(sub_t));

		sub->hash = hash;
		sub->glen = glen;
		sub->ilen = ilen;

		sub->group = isc_mem_get(mctx, glen + ilen);
		RUNTIME_CHECK(sub->group != NULL);
		memcpy(sub->group, group, glen);
		if (ilen > 0) {
			memcpy(sub->group + glen, instance, ilen);
			sub->instance = sub->group + glen;
		}

		ISC_LINK_INIT(sub, link);
		ISC_LIST_INIT(sub->members);

		ISC_LIST_APPEND(subs[bucket], sub, link);
	}

	sublist = ISC_LIST_HEAD(sub->members);
	while (sublist != NULL) {
		if (sublist->nused < BUNDLE_SIZE)
			break;
		sublist = ISC_LIST_NEXT(sublist, link);
	}

	if (sublist == NULL) {
		sublist = isc_mem_get(mctx, sizeof(sublist_t));
		RUNTIME_CHECK(sublist != NULL);
		memset(sublist, 0, sizeof(sublist_t));

		ISC_LINK_INIT(sublist, link);

		ISC_LIST_PREPEND(sub->members, sublist, link);
	}

	/*
	 * Search for an empty slot to put our connection in.
	 */
	for (slot = 0 ; slot < BUNDLE_SIZE ; slot++) {
		if (sublist->connection[slot] == NULL)
			break;
	}
	sublist->nused++;
	sublist->connection[slot] = con;
	sublist->subtype[slot] = stype;
}

/*
 * Do the low-level delete of a group.
 * SIDE EFFECT:  "sub" may be invalid on return, if it becomes empty.
 */
void
sub_delcon(sub_t *sub, connection_t *con, int bucket)
{
	sublist_t *sl;
	int slot;
	isc_boolean_t found;

	found = ISC_FALSE;
	
	sl = ISC_LIST_HEAD(sub->members);
	while (sl != NULL) {
		for (slot = 0 ; slot < BUNDLE_SIZE ; slot++) {
			if (sl->connection[slot] == con) {
				found = ISC_TRUE;
				break;
			}
		}
		if (found)
			break;
		sl = ISC_LIST_NEXT(sl, link);
	}

	if (sl == NULL)
		return;

	sl->connection[slot] = NULL;
	sl->subtype[slot] = 0;
	sl->nused--;

	if (sl->nused == 0) {
		ISC_LIST_UNLINK(sub->members, sl, link);

		isc_mem_put(mctx, sl, sizeof(sublist_t));
	}

	if (ISC_LIST_EMPTY(sub->members)) {
			isc_mem_put(mctx, sub->group, sub->glen + sub->ilen);
			ISC_LIST_UNLINK(subs[bucket], sub, link);
			isc_mem_put(mctx, sub, sizeof(sub_t));
	}		
}

/*
 * Remove a subscription.  This will clean up unused group structures as
 * needed.
 */
void
sub_del(char *group, unsigned int glen, 
	char *instance, unsigned int ilen,
	connection_t *con)
{
	int bucket;
	sub_t *sub;

	if (ilen == 1 && memcmp(instance, "*", 1) == 0) {
		instance = NULL;
		ilen = 0;
	}

	sub = sub_find(group, glen, instance, ilen, NULL, &bucket);

	sub_delcon(sub, con, bucket);
}

void
sub_unsuball(connection_t *con)
{
	sub_t *sub, *next;
	int bucket;

	for (bucket = 0 ; bucket < HASH_LEN ; bucket++) {
		sub = ISC_LIST_HEAD(subs[bucket]);
		while (sub != NULL) {
			next = ISC_LIST_NEXT(sub, link);
			sub_delcon(sub, con, bucket);
			sub = next;
		}
	}
}

/*
 * Add a connection.
 */
void
con_add(isc_socket_t *sock)
{
	connection_t *con;
	isc_region_t r;

	con = isc_mem_get(mctx, sizeof(*con));
	RUNTIME_CHECK(con != NULL);
	memset(con, 0, sizeof(*con));
	ISC_LIST_INIT(con->outbuf);
	ISC_LINK_INIT(con, link);

	con->sock = sock;

	snprintf(con->lname, sizeof(con->lname),
		 "%x_%x@%s", (unsigned int)time(NULL),
		 connection_counter++, hname);
	con->lnamelen = strlen(con->lname);
	con->lhash = HASH(con->lname, con->lnamelen, HASH_INIT);

	ISC_LIST_APPEND(cons, con, link);

	r.base = (unsigned char *)&con->recvlen;
	r.length = 4;

	RUNTIME_CHECK(isc_socket_recv(con->sock, &r, 4, task, recv_len, con)
		      == ISC_R_SUCCESS);

	con_log(con, LOG_NOTICE, "New connection, lname %s", con->lname);
}

/*
 * delete a connection.  This is called when the socket is being
 * dropped.  It will flush all pending IO, detach from the socket,
 * and remove it from all lists.
 */
void
con_del(connection_t *c)
{
	msgq_t *mq;
	int i;

	if (ISC_LINK_LINKED(c, link))
		ISC_LIST_UNLINK(cons, c, link);

	/*
	 * Cancel any pending socket I/O and release the socket.
	 */
	isc_socket_cancel(c->sock, NULL, ISC_SOCKCANCEL_ALL);
	isc_task_purgerange(task, NULL, ISC_EVENTCLASS_SOCKET,
			    ISC_EVENTCLASS_SOCKET + 0x0000ffff, NULL);
	isc_socket_detach(&c->sock);

	/*
	 * clean up any input buffer
	 */
	if (c->inbuf != NULL)
		msgbuf_detach(mctx, &c->inbuf);

	mq = ISC_LIST_HEAD(c->outbuf);
	while (mq != NULL) {
		for (i = 0 ; i < BUNDLE_SIZE ; i++) {
			if (mq->outbufs[i] != NULL)
				msgbuf_detach(mctx, &(mq->outbufs[i]));
		}

		ISC_LIST_UNLINK(c->outbuf, mq, link);
		isc_mem_put(mctx, mq, sizeof(*mq));

		mq = ISC_LIST_HEAD(c->outbuf);
	}

	/*
	 * Now, run through and do the expensive operation of
	 * cleaning up all our subscriptions.  We don't actually
	 * keep track of which we have, so we'll just walk them
	 * all.  Yick.  Good thing this happens fairly infrequently.
	 *
	 * XXXMLG it would be good to keep a list of what groups we've
	 * subscribed to, but we don't do that yet.
	 */

	sub_unsuball(c);

	isc_mem_put(mctx, c, sizeof *c);
}

/*
 * Close all connections, and clean up their subscriptions.  This is
 * usually called only on shutdown.
 */
void
con_closeall(void)
{
	connection_t *c;

	c = ISC_LIST_HEAD(cons);
	while (c != NULL) {
		con_del(c);
		c = ISC_LIST_HEAD(cons);
	}
}

/*
 * Set up listener sockets.
 */
void
lsock_open(void)
{
	lsock_t *l;
	char *addrs[] = { "127.0.0.1", NULL };
	int i;

	i = 0;
	while (addrs[i] != NULL) {
		isc_socket_t *sock;
		isc_sockaddr_t sa;
		isc_result_t result;
		struct in_addr ina;

		RUNTIME_CHECK(inet_pton(AF_INET, addrs[i], &ina) == 1);
		isc_sockaddr_fromin(&sa, &ina, msgq_port);

		sock = NULL;
		RUNTIME_CHECK(isc_socket_create(socketmgr,
						PF_INET, isc_sockettype_tcp,
						&sock) == ISC_R_SUCCESS);
		RUNTIME_CHECK(sock != NULL);
		result = isc_socket_bind(sock, &sa, ISC_SOCKET_REUSEADDRESS);
		if (result != ISC_R_SUCCESS) {
			fprintf(stderr, "socket bind failed: %s\n",
				isc_result_totext(result));
		}
		RUNTIME_CHECK(result == ISC_R_SUCCESS);

		RUNTIME_CHECK(isc_socket_listen(sock, 0) == ISC_R_SUCCESS);
		RUNTIME_CHECK(isc_socket_accept(sock, task, sock_accept, sock)
			      == ISC_R_SUCCESS);

		l = isc_mem_get(mctx, sizeof(lsock_t));
		RUNTIME_CHECK(l != NULL);
		memset(l, 0, sizeof *l);
		ISC_LINK_INIT(l, link);

		l->sock = sock;

		ISC_LIST_APPEND(lsocks, l, link);

		i++;
	}
}

/*
 * Close all listener sockets.  This is usually called only on close.
 */
void
lsock_closeall(void)
{
	lsock_t *l;

	l = ISC_LIST_HEAD(lsocks);
	while (l != NULL) {
		if (l->sock != NULL) {
			isc_socket_cancel(l->sock, NULL, ISC_SOCKCANCEL_ALL);
			isc_socket_detach(&l->sock);
		}
		ISC_LIST_UNLINK(lsocks, l, link);

		isc_mem_put(mctx, l, sizeof *l);
		
		l = ISC_LIST_HEAD(lsocks);
	}
}

#if 0
static void
my_shutdown(isc_task_t *task, isc_event_t *event) {
        char *name = event->ev_arg;

        printf("shutdown %s (%p)\n", name, task);
        fflush(stdout);
        isc_event_free(&event);
}
#endif

#ifdef TICK
static void
timeout(isc_task_t *task, isc_event_t *event) {
	connection_t *con;
	msgq_t *mq;
	msgbuf_t *mb;
	int i;

	isc_event_free(&event);

	con = ISC_LIST_HEAD(cons);
	if (con != NULL)
		fprintf(stderr, "CONNECTIONS:\n");
	while (con != NULL) {
		fprintf(stderr, "con %p(%p)", con, con->sock);
		if (con->inbuf)
			fprintf(stderr, " inbuf need %d", con->recvlen);
		fprintf(stderr, "\n");

		mq = ISC_LIST_HEAD(con->outbuf);
		while (mq != NULL) {
			fprintf(stderr, "    msgq %p add %d del %d\n",
				mq, mq->add_idx, mq->del_idx);
			for (i = 0 ; i < BUNDLE_SIZE ; i++) {
				mb = mq->outbufs[i];
				fprintf(stderr, "      slot %d: %p", i, mb);
				if (mb != NULL) {
					fprintf(stderr,
						": len %d buf %p ref %d",
						mb->r.length, mb->r.base,
						mb->ref);
				}
				fprintf(stderr, "\n");
			}
			mq = ISC_LIST_NEXT(mq, link);
		}

		con = ISC_LIST_NEXT(con, link);
	}
}
#endif

int
main(int argc, char **argv)
{
	char *port_string;
#ifdef TICK
        isc_time_t expires;
        isc_interval_t interval;
        isc_timer_t *timer;
#endif
	int i;

	gethostname(hname, sizeof(hname));
	hname[sizeof(hname) - 1] = 0;

	connection_counter = time(NULL);

	port_string = getenv("ISC_MSGQ_PORT");
	if (port_string != NULL)
		msgq_port = atoi(port_string);

	RUNTIME_CHECK(isc_app_start() == ISC_R_SUCCESS);

        mctx = NULL;
        RUNTIME_CHECK(isc_mem_create(0, 0, &mctx) == ISC_R_SUCCESS);

        manager = NULL;
        RUNTIME_CHECK(isc_taskmgr_create(mctx, 1, 0, &manager) ==
                      ISC_R_SUCCESS);

        task = NULL;
        RUNTIME_CHECK(isc_task_create(manager, 0, &task) == ISC_R_SUCCESS);

        socketmgr = NULL;
        RUNTIME_CHECK(isc_socketmgr_create(mctx, &socketmgr) == ISC_R_SUCCESS);

#ifdef TICK
        timermgr = NULL;
        RUNTIME_CHECK(isc_timermgr_create(mctx, &timermgr) == ISC_R_SUCCESS);

        isc_time_settoepoch(&expires);
        isc_interval_set(&interval, 10, 0);
        timer = NULL;
        RUNTIME_CHECK(isc_timer_create(timermgr, isc_timertype_ticker,
				       &expires, &interval, task,
				       timeout, NULL, &timer) ==
                      ISC_R_SUCCESS);
#endif

	/*
	 * Do application specific init.
	 */
	for (i = 0 ; i < HASH_LEN ; i++)
		ISC_LIST_INIT(subs[i]);
	ISC_LIST_INIT(lsocks);
	ISC_LIST_INIT(cons);

	lsock_open();

	fprintf(stderr, "Running.\n");

        RUNTIME_CHECK(isc_app_run() == ISC_R_SUCCESS);

	fprintf(stderr, "\nShutting down.\n");

	/*
	 * Application specific shutdown first
	 */
	lsock_closeall();
	con_closeall();
	sub_cleanup();

#ifdef TICK
	isc_timer_detach(&timer);
#endif
	isc_task_detach(&task);
	isc_socketmgr_destroy(&socketmgr);

#ifdef TICK
	isc_timermgr_destroy(&timermgr);
#endif
	isc_taskmgr_destroy(&manager);

	isc_mem_stats(mctx, stderr);
	isc_mem_destroy(&mctx);

	isc_app_finish();

	return (0);
}
