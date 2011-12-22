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

#ifdef __linux__
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <math.h>
#include <netdb.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* DHCPv4 defines (to be moved/shared) */

#define DHCP_OFF_OPCODE		0
#define DHCP_OFF_HTYPE		1
#define DHCP_OFF_HLEN		2
#define DHCP_OFF_HOPS		3
#define DHCP_OFF_XID		4
#define DHCP_OFF_SECS		8
#define DHCP_OFF_FLAGS		10
#define DHCP_OFF_CIADDR		12
#define DHCP_OFF_YIADDR		16
#define DHCP_OFF_SADDR		20
#define DHCP_OFF_GIADDR		24
#define DHCP_OFF_CHADDR		28
#define DHCP_OFF_SNAME		44
#define DHCP_OFF_FILE		108
#define DHCP_OFF_COOKIE		236
#define DHCP_OFF_OPTIONS	240

#define BOOTP_OP_REQUEST	1
#define BOOTP_OP_REPLY		2
#define BOOTP_MIN_LEN		300

#define DHCP_OP_DISCOVER	1
#define DHCP_OP_OFFER		2
#define DHCP_OP_REQUEST		3
#define DHCP_OP_DECLINE		4
#define DHCP_OP_ACK		5
#define DHCP_OP_NAK		6
#define DHCP_OP_RELEASE		7
#define DHCP_OP_INFORM		8

#define DHCP_HTYPE_ETHER	1

#define DHCP_OPT_PAD		0
#define DHCP_OPT_SUBNET_MASK	1
#define DHCP_OPT_TIME_OFFSET	2
#define DHCP_OPT_ROUTERS	3
#define DHCP_OPT_DNS_SERVERS	6
#define DHCP_OPT_HOST_NAME	12
#define DHCP_OPT_DOMAIN_NAME	15
#define DHCP_OPT_BROADCAST	28
#define DHCP_OPT_DHCP_ADDRESS	50
#define DHCP_OPT_DHCP_LEASE	51
#define DHCP_OPT_DHCP_MSGTYPE	53
#define DHCP_OPT_DHCP_SRVID	54
#define DHCP_OPT_DHCP_PRL	55
#define DHCP_OPT_END		255

#define DHCP_OPTLEN_SRVID	6

/* DHCPv6 defines  (to be moved/shared) */

#define DHCP6_OFF_MSGTYP	0
#define DHCP6_OFF_XID		1
#define DHCP6_OFF_OPTIONS	4

#define DHCP6_OP_SOLICIT	1
#define DHCP6_OP_ADVERTISE	2
#define DHCP6_OP_REQUEST	3
#define DHCP6_OP_REPLY		7

#define DHCP6_OPT_CLIENTID	1
#define DHCP6_OPT_SERVERID	2
#define DHCP6_OPT_IA_NA		3
#define DHCP6_OPT_ORO		6
#define DHCP6_OPT_ELAPSED_TIME	8
#define DHCP6_OPT_STATUS_CODE	13
#define DHCP6_OPT_RAPID_COMMIT	14
#define DHCP6_OPT_NAME_SERVERS	23
#define DHCP6_OPT_DOMAIN_SEARCH	24

#define DHCP6_ST_SUCCESS	0
#define DHCP6_ST_NOADDRSAVAIL	2

#define DHCP6_DUID_LLT		1
#define DHCP6_DUID_EPOCH	946684800

/* tail queue macros (from FreeBSD 8.2 /sys/sys/queue.h, to be moved/shared) */

#define ISC_TAILQ_HEAD(name, type)					\
struct name {								\
	struct type *tqh_first;						\
	struct type **tqh_last;						\
}

#define ISC_TAILQ_ENTRY(type)						\
struct {								\
	struct type *tqe_next;						\
	struct type **tqe_prev;						\
}

#define ISC_TAILQ_EMPTY(head)	((head)->tqh_first == NULL)

#define ISC_TAILQ_FIRST(head)	((head)->tqh_first)

#define ISC_TAILQ_LAST(head, headname)					\
	(*(((struct headname *)((head)->tqh_last))->tqh_last))

#define ISC_TAILQ_NEXT(elm, field)	((elm)->field.tqe_next)

#define ISC_TAILQ_PREV(elm, headname, field)				\
	(*(((struct headname *)((elm)->field.tqe_prev))->tqh_last))

#define ISC_TAILQ_INIT(head)	do {					\
	ISC_TAILQ_FIRST((head)) = NULL;					\
	(head)->tqh_last = &ISC_TAILQ_FIRST((head));			\
} while (0)

#define ISC_TAILQ_INSERT_HEAD(head, elm, field)	do {			\
	ISC_TAILQ_NEXT((elm), field) = ISC_TAILQ_FIRST((head));		\
	if (!ISC_TAILQ_EMPTY((head)))					\
		ISC_TAILQ_FIRST((head))->field.tqe_prev =		\
			&ISC_TAILQ_NEXT((elm), field);			\
	else								\
		(head)->tqh_last = &ISC_TAILQ_NEXT((elm), field);	\
	ISC_TAILQ_FIRST((head)) = (elm);				\
	(elm)->field.tqe_prev = &ISC_TAILQ_FIRST((head));		\
} while (0)

#define ISC_TAILQ_INSERT_TAIL(head, elm, field)	do {			\
	ISC_TAILQ_NEXT((elm), field) = NULL;				\
	(elm)->field.tqe_prev = (head)->tqh_last;			\
	*(head)->tqh_last = (elm);					\
	(head)->tqh_last = &ISC_TAILQ_NEXT((elm), field);		\
} while (0)

#define ISC_TAILQ_REMOVE(head, elm, field)	do {			\
	if ((ISC_TAILQ_NEXT((elm), field)) != NULL)			\
		ISC_TAILQ_NEXT((elm), field)->field.tqe_prev =		\
			(elm)->field.tqe_prev;				\
	else								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = ISC_TAILQ_NEXT((elm), field);		\
} while (0)

#define ISC_TAILQ_FOREACH(var, head, field)				\
	for ((var) = ISC_TAILQ_FIRST((head));				\
	     (var);							\
	     (var) = ISC_TAILQ_NEXT((var), field))

#define ISC_TAILQ_FOREACH_SAFE(var, head, field, tvar)			\
	for ((var) = ISC_TAILQ_FIRST((head));				\
	     (var) && ((tvar) = ISC_TAILQ_NEXT((var), field), 1);	\
	     (var) = (tvar))

/*
 * Data structures
 */

/*
 * exchange:
 *    - per exchange values:
 *	* order (for debugging)
 *	* xid (even/odd for 4 packet exchanges)
 *	* random (for debugging)
 *	* time-stamps
 *	* server ID (for 3rd packet)
 *	* IA_NA (for IPv6 3rd packet)
 *
 * sent/rcvd global chains, "next to be received" on entry cache,
 * and hash table for xid -> data structure fast matching
 * (using the assumption collisions are unlikely, cf birthday problem)
 */

struct exchange {				/* per exchange structure */
	ISC_TAILQ_ENTRY(exchange) gchain;	/* global chaining */
	ISC_TAILQ_ENTRY(exchange) hchain;	/* hash table chaining */
	uint64_t order0, order2;		/* number of this exchange */
	uint32_t xid;				/* transaction ID */
	uint32_t rnd;				/* random part */
	struct timespec ts0, ts1, ts2, ts3;	/* timespecs */
	uint8_t *sid;				/* server ID */
	size_t sidlen;				/* server ID length */
	uint8_t *iana;				/* (IPv6) IA_NA */
	size_t ianalen;				/* (IPv6) IA_NA length */
};
struct exchange *xnext0, *xnext2;		/* next to be received */
ISC_TAILQ_HEAD(xlist, exchange);		/* exchange list */
struct xlist xsent0, xsent2, xrcvd0, xrcvd2;	/* sent and received lists */
uint64_t xscount0, xscount2;			/* sent counters */
uint64_t xrcount0, xrcount2;			/* received counters */
caddr_t exchanges0, exchanges2;			/* hash tables */
uint32_t hashsize0, hashsize2;			/* hash table sizes */

/*
 * statictics counters and accumulators
 */

uint64_t tooshort, orphans, locallimit;		/* error counters */
uint64_t latesent, compsend, latercvd;		/* rate stats */
uint64_t multrcvd, shortwait, collected[2];	/* rate stats (cont) */
double dmin0 = 999999999., dmin2 = 999999999.;	/* minimum delays */
double dmax0 = 0., dmax2 = 0.;			/* maximum delays */
double dsum0 = 0., dsum2 = 0.;			/* delay sums */
double dsumsq0 = 0., dsumsq2 = 0.;		/* square delay sums */

/*
 * command line parameters
 */

int ipversion = 0;			/* IP version */
int simple;				/* DO/SA in place of DORR/SARR */
int rate;				/* rate in exchange per second */
int report;				/* delay between two reports */
uint32_t range;				/* randomization range */
uint32_t maxrandom;			/* maximum random value */
int basecnt;				/* base count */
char *base[4];				/* bases */
int gotnumreq;				/* numreq[0] was set */
int numreq[2];				/* number of exchange */
int period;				/* test period */
int gotlosttime;			/* losttime[0] was set */
double losttime[2] = {1., 1.};		/* time after a request is lost  */
int gotmaxdrop;				/* max{p}drop[0] was set */
int maxdrop[2];				/* maximum number of lost requests */
double maxpdrop[2] = { 0., 0.};		/* maximum percentage */
char *localname;			/* local address or interface */
int isinterface;			/* interface vs local address */
int preload;				/* preload exchanges */
int aggressivity = 1;			/* back to back exchanges */
int localport;				/* local port number (host endian) */
int seeded;				/* is a seed provided */
unsigned int seed;			/* randomization seed */
int isbroadcast;			/* use broadcast */
int rapidcommit;			/* add rapid commit option */
int usefirst;				/* where to take the server-ID */
char *templatefile[2];			/* template file name */
int xidoffset[2] = {-1, -1};		/* template offsets (xid)*/
int rndoffset[2] = {-1, -1};		/* template offsets (random) */
int elpoffset = -1;			/* template offset (elapsed time) */
int sidoffset = -1;			/* template offset (server ID) */
int ripoffset = -1;			/* template offset (requested IP) */
char *diags;				/* diagnostic selectors */
char *wrapped;				/* wrapped command */
char *servername;			/* server */

/*
 * global variables
 */

struct sockaddr_storage localaddr;	/* local socket address */
struct sockaddr_storage serveraddr;	/* server socket address */

int sock;				/* socket descriptor */
int interrupted, fatal;			/* to finish flags */

uint8_t obuf[4096], ibuf[4096];		/* I/O buffers */
char tbuf[8200];			/* template buffer */

struct timespec boot;			/* the date of boot */
struct timespec last;			/* the date of last send */
struct timespec due;			/* the date of next send */
struct timespec dreport;		/* the date of next reporting */
struct timespec finished;		/* the date of finish */

uint8_t *gsrvid;			/* global server id */
size_t gsrvidlen;			/*  and its length */
uint8_t gsrvidbuf[64];			/*  and its storage */

/* MAC address */
uint8_t mac_prefix[6] = { 0x00, 0x0c, 0x01, 0x02, 0x03, 0x04 };

/* DUID prefix */
uint8_t *duid_prefix;
int duid_length;

/* magic cookie for BOOTP/DHCPv4 */
uint8_t dhcp_cookie[4] = { 0x63, 0x82, 0x53, 0x63 };

/*
 * templates
 *
 * note: the only hard point is what are the offsets:
 *   - xid_discover4 and xid_request4: first of the 4 octet long
 *     transaction ID (default DHCP_OFF_XID = 4)
 *   - random_discover4 and random_request4: last of the 6 octet long
 *     MAC address (default DHCP_OFF_CHADDR + 6 = 28 + 6)
 *   - elapsed_request4: first of the 2 octet long secs field
 *     (default DHCP_OFF_SECS = 8, 0 means disabled)
 *   - serverid_request4: first of the 6 octet long server ID option
 *     (no default, required)
 *   - reqaddr_request4: first of the 4 octet long requested IP address
 *     option content (i.e., the address itself, btw OFFER yiaddr)
 *     (no default, required)
 *   - xid_solicit6 and xid_request6: first of the 3 octet long
 *     transaction ID (default DHCP6_OFF_XID = 1)
 *   - random_solicit6 and random_request6: last of the DUID in the
 *     client ID option (no default, required when rate is set)
 *   - elapsed_request6: first of the 2 octet long content of
 *     the option elapsed time option (no default, 0 means disabled)
 *   - serverid_request6: position where the variable length server ID
 *     option is inserted (no default, required, set to length means append)
 *   - reqaddr_request6: position where of the variable length requested
 *     IP address option is inserted (no default, required, set to
 *     length means append)
 */

size_t length_discover4;
uint8_t template_discover4[4096];
size_t xid_discover4;
size_t random_discover4;
size_t length_request4;
uint8_t template_request4[4096];
size_t xid_request4;
size_t elapsed_request4;
size_t random_request4;
size_t serverid_request4;
size_t reqaddr_request4;
size_t length_solicit6;
uint8_t template_solicit6[4096];
size_t xid_solicit6;
size_t random_solicit6;
size_t length_request6;
uint8_t template_request6[4096];
size_t xid_request6;
size_t elapsed_request6;
size_t random_request6;
size_t serverid_request6;
size_t reqaddr_request6;

/*
 * initialize data structures handling exchanges
 */

void
inits(void)
{
	struct xlist *bucket;
	caddr_t p;
	size_t len, i;

	ISC_TAILQ_INIT(&xsent0);
	ISC_TAILQ_INIT(&xsent2);
	ISC_TAILQ_INIT(&xrcvd0);
	ISC_TAILQ_INIT(&xrcvd2);

	/// compute hashsizes
	hashsize0 = 1024;
	len = sizeof(*bucket) * hashsize0;
	exchanges0 = malloc(len);
	if (exchanges0 == NULL) {
		perror("malloc(exchanges0)");
		exit(1);
	}
	for (i = 0, p = exchanges0; i < hashsize0; i++, p += sizeof(*bucket)) {
		bucket = (struct xlist *) p;
		ISC_TAILQ_INIT(bucket);
	}
	if (simple != 0)
		return;
	hashsize2 = 1024;
	len = sizeof(*bucket) * hashsize2;
	exchanges2 = malloc(len);
	if (exchanges2 == NULL) {
		perror("malloc(exchanges2)");
		exit(1);
	}
	for (i = 0, p = exchanges2; i < hashsize2; i++, p += sizeof(*bucket)) {
		bucket = (struct xlist *) p;
		ISC_TAILQ_INIT(bucket);
	}
}

/*
 * randomize the value of the given field:
 *   - offset of the field
 *   - random seed (used as it when suitable)
 *   - returns the random value which was used
 */

uint32_t
randomize(size_t offset, uint32_t r)
{
	uint32_t v;

	if (range == 0)
		return 0;
	if (range == UINT32_MAX)
		return r;
	if (maxrandom != 0)
		while (r >= maxrandom)
			r = (uint32_t) random();
	r %= range + 1;
	v = r;
	v += obuf[offset];
	obuf[offset] = v;
	if (v < 256)
		return r;
	v >>= 8;
	v += obuf[offset - 1];
	obuf[offset - 1] = v;
	if (v < 256)
		return r;
	v >>= 8;
	v += obuf[offset - 2];
	obuf[offset - 2] = v;
	if (v < 256)
		return r;
	v >>= 8;
	v += obuf[offset - 3];
	obuf[offset - 3] = v;
	return r;
}

/*
 * receive a reply (4th packet), shared between IPv4 and IPv6:
 *   - transaction ID xid
 *   - receiving time-stamp now
 * called from receive[46]() when the xid is odd
 */

void
receive_reply(uint32_t xid, struct timespec *now)
{
	struct exchange *x, *t;
	struct xlist *bucket;
	uint32_t hash;
	int checklost;
	double delta;

	/* bucket is needed even when the next cache matches */
	hash = (xid >> 1) & (hashsize2 - 1);
	bucket = (struct xlist *) (exchanges2 + hash * sizeof(*bucket));
	/* try the 'next to be received' cache */
	if ((xnext2 != NULL) && (xnext2->xid == xid)) {
		x = xnext2;
		goto found;
	}
	/* usually the lost probability is low for request/reply */
	checklost = 1;
	/* look for the exchange */
	ISC_TAILQ_FOREACH_SAFE(x, bucket, hchain, t) {
		double waited;

		if (x->xid == xid)
			goto found;
		if (checklost <= 0)
			continue;
		checklost = 0;
		/* check for a timed-out exchange */
		waited = now->tv_sec - x->ts2.tv_sec;
		waited += (now->tv_nsec - x->ts2.tv_nsec) / 1e9;
		if (waited < losttime[1])
			continue;
		/* garbage collect timed-out exchange */
		ISC_TAILQ_REMOVE(bucket, x, hchain);
		ISC_TAILQ_REMOVE(&xsent2, x, gchain);
		free(x);
		collected[1] += 1;
	}
	/* no match? very late or not for us */
	orphans++;
	return;

	/* got it: update stats and move to the received queue */
    found:
	xrcount2++;
	x->ts3 = *now;
	delta = x->ts3.tv_sec - x->ts2.tv_sec;
	delta += (x->ts3.tv_nsec - x->ts2.tv_nsec) / 1e9;
	if (delta < dmin2)
		dmin2 = delta;
	if (delta > dmax2)
		dmax2 = delta;
	dsum2 += delta;
	dsumsq2 += delta * delta;
	xnext2 = ISC_TAILQ_NEXT(x, gchain);
	ISC_TAILQ_REMOVE(bucket, x, hchain);
	ISC_TAILQ_REMOVE(&xsent2, x, gchain);
	ISC_TAILQ_INSERT_TAIL(&xrcvd2, x, gchain);
}

/*
 * get the DHCPv4 socket descriptor
 * (the only complexity is broadcast enabling: there is no easy way to
 *  recognize broadcast addresses, so the command line -B flag)
 */

void
getsock4(void)
{
	int ret;

	/* update local port */
	if (localport != 0) {
		uint16_t lp = htons((uint16_t) localport);

		((struct sockaddr_in *) &localaddr)->sin_port = lp;
	}
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	ret = bind(sock,
		   (struct sockaddr *) &localaddr,
		   sizeof(struct sockaddr_in));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}
	/* enable broadcast if needed or required */
	if (isbroadcast != 0) {
		int on = 1;

		ret = setsockopt(sock,
				 SOL_SOCKET, SO_BROADCAST,
				 &on, sizeof(on));
		if (ret < 0) {
			perror("setsockopt(SO_BROADCAST)");
			exit(1);
		}
	}
}

/*
 * build a DHCPv4 DISCOVER from a relay template
 * (implicit parameters are the local (giaddr) and MAC addresses (chaddr))
 * (assume the link is Ethernet)
 */

void
build_template_discover4(void)
{
	uint8_t *p = template_discover4;

	length_discover4 = BOOTP_MIN_LEN;
	xid_discover4 = DHCP_OFF_XID;
	random_discover4 = DHCP_OFF_CHADDR + 6;
	/* opcode */
	p[DHCP_OFF_OPCODE] = BOOTP_OP_REQUEST;
	/* hardware address type */
	p[DHCP_OFF_HTYPE] = DHCP_HTYPE_ETHER;
	/* hardware address length */
	p[DHCP_OFF_HLEN] = 6;
	/* hops */
	p[DHCP_OFF_HOPS] = 1;
	/* gateway address */
	memcpy(p + DHCP_OFF_GIADDR,
	       &((struct sockaddr_in *) &localaddr)->sin_addr,
	       4);
	/* hardware address */
	memcpy(p + DHCP_OFF_CHADDR, mac_prefix, 6);
	/* cookie */
	memcpy(p + DHCP_OFF_COOKIE, dhcp_cookie, 4);
	/* options */
	p += DHCP_OFF_OPTIONS;
	/* inline DHCP message type */
	*p++ = DHCP_OPT_DHCP_MSGTYPE;
	*p++ = 1;
	*p++ = DHCP_OP_DISCOVER;
	/* inline DHCP parameter request list (default) */
	*p++ = DHCP_OPT_DHCP_PRL;
	*p++ = 7;
	*p++ = DHCP_OPT_SUBNET_MASK;
	*p++ = DHCP_OPT_BROADCAST;
	*p++ = DHCP_OPT_TIME_OFFSET;
	*p++ = DHCP_OPT_ROUTERS;
	*p++ = DHCP_OPT_DOMAIN_NAME;
	*p++ = DHCP_OPT_DNS_SERVERS;
	*p++ = DHCP_OPT_HOST_NAME;
	/* end */
	*p = DHCP_OPT_END;
}

/*
 * get a DHCPv4 client/relay first packet (usually a DISCOVER) template
 * from the file given in the command line (-T<template-file>)
 * and xid/rnd offsets (-X<xid-offset> and -O<random-offset>)
 */

void
get_template_discover4(void)
{
	uint8_t *p = template_discover4;
	int fd, cc, i, j;

	fd = open(templatefile[0], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile[0], strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile[0], strerror(errno));
		exit(1);
	}
	if (cc < 100) {
		fprintf(stderr, "file '%s' too short\n", templatefile[0]);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile[0]);
		exit(2);
	}
	j = 0;
	for (i = 0; i < cc; i++) {
		if (isspace((int) tbuf[i]))
			continue;
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile[0]);
			exit(2);
		}
		tbuf[j] = tbuf[i];
		j++;
	}
	cc = j;
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile[0]);
		exit(2);
	}
	length_discover4 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset[0] >= 0)
		xid_discover4 = (size_t) xidoffset[0];
	else
		xid_discover4 = DHCP_OFF_XID;
	if (xid_discover4 + 4 > length_discover4) {
		fprintf(stderr,
			"xid (at %zu) outside the template (length %zu)?\n",
			xid_discover4, length_discover4);
		exit(2);
	}
	if (rndoffset[0] >= 0)
		random_discover4 = (size_t) rndoffset[0];
	else
		random_discover4 = DHCP_OFF_CHADDR + 6;
	if (random_discover4 > length_discover4) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_discover4, length_discover4);
		exit(2);
	}
}

/*
 * build a DHCPv4 REQUEST from a relay template
 * (implicit parameters are the local (giaddr) and MAC addresses (chaddr))
 * (assume the link is Ethernet)
 */

void
build_template_request4(void)
{
	uint8_t *p = template_request4;

	length_request4 = BOOTP_MIN_LEN;
	xid_request4 = DHCP_OFF_XID;
	elapsed_request4 = DHCP_OFF_SECS;
	random_request4 = DHCP_OFF_CHADDR + 6;
	/* opcode */
	p[DHCP_OFF_OPCODE] = BOOTP_OP_REQUEST;
	/* hardware address type */
	p[DHCP_OFF_HTYPE] = DHCP_HTYPE_ETHER;
	/* hardware address length */
	p[DHCP_OFF_HLEN] = 6;
	/* hops */
	p[DHCP_OFF_HOPS] = 1;
	/* gateway address */
	memcpy(p + DHCP_OFF_GIADDR,
	       &((struct sockaddr_in *) &localaddr)->sin_addr,
	       4);
	/* hardware address */
	memcpy(p + DHCP_OFF_CHADDR, mac_prefix, 6);
	/* cookie */
	memcpy(p + DHCP_OFF_COOKIE, dhcp_cookie, 4);
	/* options */
	p += DHCP_OFF_OPTIONS;
	/* inline DHCP message type */
	*p++ = DHCP_OPT_DHCP_MSGTYPE;
	*p++ = 1;
	*p++ = DHCP_OP_REQUEST;
	/* place for DHCP server id (option) */
	serverid_request4 = p - template_request4;
	p += DHCP_OPTLEN_SRVID;
	/* place for DHCP requested IP address (address) */
	*p++ = DHCP_OPT_DHCP_ADDRESS;
	*p++ = 4;
	reqaddr_request4 = p - template_request4;
	p += 4;
	/* inline DHCP parameter request list (default) */
	*p++ = DHCP_OPT_DHCP_PRL;
	*p++ = 7;
	*p++ = DHCP_OPT_SUBNET_MASK;
	*p++ = DHCP_OPT_BROADCAST;
	*p++ = DHCP_OPT_TIME_OFFSET;
	*p++ = DHCP_OPT_ROUTERS;
	*p++ = DHCP_OPT_DOMAIN_NAME;
	*p++ = DHCP_OPT_DNS_SERVERS;
	*p++ = DHCP_OPT_HOST_NAME;
	/* end */
	*p = DHCP_OPT_END;
}

/*
 * get a DHCPv4 client/relay third packet (usually a REQUEST) template
 * from the file given in the command line (-T<template-file>)
 * and offsets (-X,-O,-E,-S,-I).
 */

void
get_template_request4(void)
{
	uint8_t *p = template_request4;
	int fd, cc, i, j;

	fd = open(templatefile[1], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile[1], strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile[1], strerror(errno));
		exit(1);
	}
	if (cc < 100) {
		fprintf(stderr, "file '%s' too short\n", templatefile[1]);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile[1]);
		exit(2);
	}
	j = 0;
	for (i = 0; i < cc; i++) {
		if (isspace((int) tbuf[i]))
			continue;
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile[1]);
			exit(2);
		}
		tbuf[j] = tbuf[i];
		j++;
	}
	cc = j;
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile[1]);
		exit(2);
	}
	length_request4 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset[1] >= 0)
		xid_request4 = (size_t) xidoffset[1];
	else
		xid_request4 = DHCP_OFF_XID;
	if (xid_request4 + 4 > length_request4) {
		fprintf(stderr,
			"xid (at %zu) outside the template (length %zu)?\n",
			xid_request4, length_request4);
		exit(2);
	}
	if (rndoffset[1] >= 0)
		random_request4 = (size_t) rndoffset[1];
	else
		random_request4 = DHCP_OFF_CHADDR + 6;
	if (random_request4 > length_request4) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_request4, length_request4);
		exit(2);
	}
	if (elpoffset >= 0)
		elapsed_request4 = (size_t) elpoffset;
	else
		elapsed_request4 = DHCP_OFF_SECS;
	if (elapsed_request4 + 2 > length_request4) {
		fprintf(stderr,
			"secs (at %zu) outside the template (length %zu)?\n",
			elapsed_request4, length_request4);
		exit(2);
	}
	serverid_request4 = (size_t) sidoffset;
	if (serverid_request4 + 6 > length_request4) {
		fprintf(stderr,
			"server-id option (at %zu) outside the template "
			"(length %zu)?\n",
			serverid_request4, length_request4);
		exit(2);
	}
	reqaddr_request4 = (size_t) ripoffset;
	if (reqaddr_request4 + 4 > length_request4) {
		fprintf(stderr,
			"requested-ip-address option (at %zu) outside "
			"the template (length %zu)?\n",
			reqaddr_request4, length_request4);
		exit(2);
	}
}

/*
 * send the DHCPv4 REQUEST third packet
 * (the transaction ID is odd)
 * (TODO: check for errors in the OFFER)
 */

void
send_request4(struct exchange *x0)
{
	struct exchange *x;
	struct xlist *bucket;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL) {
		locallimit++;
		perror("send2");
		return;
	}

	memcpy(x, x0, sizeof(*x));
	x->order2 = xscount2++;
	x->xid |= 1;
	hash = x->xid >> 1;

	ISC_TAILQ_INSERT_TAIL(&xsent2, x, gchain);
	hash &= hashsize2 - 1;
	bucket = (struct xlist *) (exchanges2 + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	memcpy(obuf, template_request4, length_request4);
	/* xid */
	memcpy(obuf + xid_request4, &x->xid, 4);
	/* random */
	randomize(random_request4, x->rnd);
	/* secs */
	if (elapsed_request4 > 0) {
		int secs;

		secs = x->ts1.tv_sec - x->ts0.tv_sec;
		if (x->ts1.tv_nsec < x->ts0.tv_nsec)
			secs += 1;
		if (secs > 0) {
			obuf[elapsed_request4] = secs >> 8;
			obuf[elapsed_request4 + 1] = secs & 0xff;
		}
	}
	/* server ID */
	memcpy(obuf + serverid_request4, x->sid, x->sidlen);
	/* requested IP address */
	memcpy(obuf + reqaddr_request4, ibuf + DHCP_OFF_YIADDR, 4);

	/* timestamp */
	ret = clock_gettime(CLOCK_REALTIME, &x->ts2);
	if (ret < 0) {
		perror("clock_gettime(send2)");
		fatal = 1;
		return;
	}
	ret = sendto(sock, obuf, length_request4, 0,
		     (struct sockaddr *) &serveraddr,
		     sizeof(struct sockaddr_in));
	if (ret >= 0)
		return;
	if ((errno == EAGAIN) || (errno == EWOULDBLOCK) ||
	    (errno == ENOBUFS) || (errno == ENOMEM))
		locallimit++;
	perror("send2");
}

/*
 * send the DHCPv4 DISCOVER first packet
 * (for 4-exchange, the transaction ID xid is even)
 */

int
send4(void)
{
	struct exchange *x;
	struct xlist *bucket;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL)
		return -ENOMEM;

	memset(x, 0, sizeof(*x));
	x->order0 = xscount0++;
	hash = x->rnd = (uint32_t) random();
	if (simple == 0)
		x->xid = hash << 1;
	else
		x->xid = hash;

	ISC_TAILQ_INSERT_TAIL(&xsent0, x, gchain);
	hash &= hashsize0 - 1;
	bucket = (struct xlist *) (exchanges0 + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	memcpy(obuf, template_discover4, length_discover4);
	/* xid */
	memcpy(obuf + xid_discover4, &x->xid, 4);
	/* random */
	x->rnd = randomize(random_discover4, x->rnd);
	/* timestamp */
	ret = clock_gettime(CLOCK_REALTIME, &last);
	if (ret < 0) {
		perror("clock_gettime(send)");
		fatal = 1;
		return -errno;
	}
	x->ts0 = last;
	errno = 0;
	ret = sendto(sock, obuf, length_discover4, 0,
		     (struct sockaddr *) &serveraddr,
		     sizeof(struct sockaddr_in));
	if (ret == (ssize_t) length_discover4)
		return 0;
	return -errno;
}	

/*
 * scan a DHCPv4 OFFER to get its server-id option
 */

int
scan_for_srvid4(struct exchange *x, size_t cc)
{
	size_t off = DHCP_OFF_OPTIONS;

	for (;;) {
		if (off + DHCP_OPTLEN_SRVID > cc) {
			fprintf(stderr, "truncated\n");
			return -1;
		}
		if (ibuf[off] == DHCP_OPT_DHCP_SRVID)
			break;
		if (ibuf[off] == DHCP_OPT_END) {
			fprintf(stderr, "server-id not found\n");
			return -1;
		}
		if (ibuf[off] == DHCP_OPT_PAD) {
			off++;
			continue;
		}
		off += 2 + ibuf[off + 1];
	}
	/* check length */
	if (ibuf[off + 1] != DHCP_OPTLEN_SRVID - 2) {
		fprintf(stderr,
			"bad server-id length (%hhu)\n",
			ibuf[off + 1]);
		return -1;
	}
	/* cache it in the global variables when required and not yet done */
	if ((usefirst != 0) && (gsrvid == NULL)) {
		memcpy(gsrvidbuf, ibuf + off, DHCP_OPTLEN_SRVID);
		gsrvid = gsrvidbuf;
		gsrvidlen = DHCP_OPTLEN_SRVID;
	}
	x->sid = ibuf + off;
	x->sidlen = DHCP_OPTLEN_SRVID;
	return 0;
}

/*
 * receive a DHCPv4 packet
 */

void
receive4(void)
{
	struct exchange *x, *t;
	struct xlist *bucket;
	struct timespec now;
	ssize_t cc;
	uint32_t xid, hash;
	int checklost = 0;
	double delta;

	cc = recv(sock, ibuf, sizeof(ibuf), 0);
	if (cc < 0) {
		if ((errno == EAGAIN) ||
		    (errno == EWOULDBLOCK) ||
		    (errno == EINTR))
			return;
		perror("recv");
		fatal = 1;
		return;
	}
	/* enforce a reasonable length */
	if (cc < BOOTP_MIN_LEN) {
		tooshort++;
		return;
	}
	/* must be a BOOTP REPLY */
	if (ibuf[DHCP_OFF_OPCODE] != BOOTP_OP_REPLY)
		return;
	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		perror("clock_gettime(receive)");
		fatal = 1;
		return;
	}
	memcpy(&xid, ibuf + xid_discover4, 4);
	/* 4-packet exchange even/odd xid */
	if (simple == 0) {
		if ((xid & 1) != 0) {
			receive_reply(xid, &now);
			return;
		}
		hash = (xid >> 1) & (hashsize0 - 1);
	} else
		hash = xid & (hashsize0 - 1);
	/* now it is the second packet, get the bucket which is needed */
	bucket = (struct xlist *) (exchanges0 + hash * sizeof(*bucket));
	/* try the 'next to be received' cache */
	if ((xnext0 != NULL) && (xnext0->xid == xid)) {
		x = xnext0;
		goto found;
	}
	/* if the rate is not illimited, garbage collect up to 3
	   timed-out exchanges */
	if (rate != 0)
		checklost = 3;
	/* look for the exchange */
	ISC_TAILQ_FOREACH_SAFE(x, bucket, hchain, t) {
		double waited;

		if (x->xid == xid)
			goto found;
		if (checklost <= 0)
			continue;
		/* check for a timed-out exchange */
		waited = now.tv_sec - x->ts0.tv_sec;
		waited += (now.tv_nsec - x->ts0.tv_nsec) / 1e9;
		if (waited < losttime[0]) {
			checklost = 0;
			continue;
		}
		/* garbage collect timed-out exchange */
		checklost--;
		ISC_TAILQ_REMOVE(bucket, x, hchain);
		ISC_TAILQ_REMOVE(&xsent0, x, gchain);
		free(x);
		collected[0] += 1;
	}
	/* no match? very late or not for us */
	orphans++;
	return;

	/* got it: update stats and move to the received queue */
    found:
	xrcount0++;
	x->ts1 = now;
	delta = x->ts1.tv_sec - x->ts0.tv_sec;
	delta += (x->ts1.tv_nsec - x->ts0.tv_nsec) / 1e9;
	if (delta < dmin0)
		dmin0 = delta;
	if (delta > dmax0)
		dmax0 = delta;
	dsum0 += delta;
	dsumsq0 += delta * delta;
	xnext0 = ISC_TAILQ_NEXT(x, gchain);
	ISC_TAILQ_REMOVE(bucket, x, hchain);
	ISC_TAILQ_REMOVE(&xsent0, x, gchain);
	ISC_TAILQ_INSERT_TAIL(&xrcvd0, x, gchain);
	/* if the exchange is not finished, go to the second part */
	if (simple == 0) {
		int ret = 0;

		/* the server-ID option is needed */
		if ((usefirst != 0) && (gsrvid != NULL)) {
			x->sid = gsrvid;
			x->sidlen = gsrvidlen;
		} else
			ret = scan_for_srvid4(x, cc);
		if (ret >= 0)
			send_request4(x);
	}
}

/*
 * get the DHCPv6 socket descriptor
 */

void
getsock6(void)
{
	struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) &serveraddr;
	int ret;

	/* update local port */
	if (localport != 0) {
		uint16_t lp = htons((uint16_t) localport);

		((struct sockaddr_in6 *) &localaddr)->sin6_port = lp;
	}
	sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	/* perform the multicast stuff when the destination is multicast */
	if (IN6_IS_ADDR_MULTICAST(&s6->sin6_addr)) {
		int hops = 1;

		ret = setsockopt(sock,
				 IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
				 &hops, sizeof(hops));
		if (ret < 0) {
			perror("setsockopt(IPV6_MULTICAST_HOPS)");
			exit(1);
		}
	}
	if (isinterface && IN6_IS_ADDR_MULTICAST(&s6->sin6_addr)) {
		unsigned idx = if_nametoindex(localname);

		if (idx == 0) {
			fprintf(stderr,
				"if_nametoindex(%s) failed\n",
				localname);
			exit(1);
		}
		ret = setsockopt(sock,
				 IPPROTO_IPV6, IPV6_MULTICAST_IF,
				 &idx, sizeof(idx));
		if (ret < 0) {
			perror("setsockopt(IPV6_MULTICAST_IF)");
			exit(1);
		}
	}
}

/*
 * build a DHCPv6 SOLICIT template
 * (implicit parameter is the DUID, don't assume an Ethernet link)
 */

void
build_template_solicit6(void)
{
	uint8_t *p = template_solicit6;

	xid_solicit6 = DHCP6_OFF_XID;
	/* message type */
	p[DHCP6_OFF_MSGTYP] = DHCP6_OP_SOLICIT;
	/* options */
	p += DHCP6_OFF_OPTIONS;
	/* elapsed time */
	p[1] = DHCP6_OPT_ELAPSED_TIME;
	p[3] = 2;
	p += 6;
	/* rapid commit */
	if (rapidcommit != 0) {
		p[1] = DHCP6_OPT_RAPID_COMMIT;
		p += 4;
	}
	/* client ID */
	p[1] = DHCP6_OPT_CLIENTID;
	p[3] = duid_length;
	memcpy(p + 4, duid_prefix, duid_length);
	p += 4 + duid_length;
	random_solicit6 = p - template_solicit6;
	/* option request option */
	p[1] = DHCP6_OPT_ORO;
	p[3] = 4;
	p[5] = DHCP6_OPT_NAME_SERVERS;
	p[7] = DHCP6_OPT_DOMAIN_SEARCH;
	p += 8;
	/* IA_NA (IAID = 1, T1 = 3600, T2 = 5400) */
	p[1] = DHCP6_OPT_IA_NA;
	p[3] = 12;
	p[7] = 1;
	p[10] = 3600 >> 8;
	p[11] = 3600 & 0xff;
	p[14] = 5400 >> 8;
	p[15] = 5400 & 0xff;
	p += 16;
	/* set length */
	length_solicit6 = p - template_solicit6;
}

/*
 * get a DHCPv6 first packet (usually a SOLICIT) template
 * from the file given in the command line (-T<template-file>)
 * and xid/rnd offsets (-X<xid-offset> and -O<random-offset>)
 */

void
get_template_solicit6(void)
{
	uint8_t *p = template_solicit6;
	int fd, cc, i, j;

	fd = open(templatefile[0], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile[0], strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile[0], strerror(errno));
		exit(1);
	}
	if (cc < 10) {
		fprintf(stderr, "file '%s' too short\n", templatefile[0]);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile[0]);
		exit(2);
	}
	j = 0;
	for (i = 0; i < cc; i++) {
		if (isspace((int) tbuf[i]))
			continue;
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile[0]);
			exit(2);
		}
		tbuf[j] = tbuf[i];
		j++;
	}
	cc = j;
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile[0]);
		exit(2);
	}
	length_solicit6 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset[0] >= 0)
		xid_solicit6 = (size_t) xidoffset[0];
	else
		xid_solicit6 = DHCP6_OFF_XID;
	if (xid_solicit6 + 3 > length_solicit6) {
		fprintf(stderr,
			"xid (at %zu) is outside the template (length %zu)?\n",
			xid_solicit6, length_solicit6);
		exit(2);
	}
	if (rndoffset[0] >= 0)
		random_solicit6 = (size_t) rndoffset[0];
	else
		random_solicit6 = 0;
	if (random_solicit6 > length_solicit6) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_solicit6, length_solicit6);
		exit(2);
	}
}

/*
 * build a DHCPv6 REQUEST template
 * (implicit parameter is the DUID, don't assume an Ethernet link)
 */

void
build_template_request6(void)
{
	uint8_t *p = template_request6;

	xid_request6 = DHCP6_OFF_XID;
	/* message type */
	p[DHCP6_OFF_MSGTYP] = DHCP6_OP_REQUEST;
	/* options */
	p += DHCP6_OFF_OPTIONS;
	/* elapsed time */
	p[1] = DHCP6_OPT_ELAPSED_TIME;
	p[3] = 2;
	p += 4;
	elapsed_request6 = p - template_request6;
	p += 2;
	/* client ID */
	p[1] = DHCP6_OPT_CLIENTID;
	p[3] = duid_length;
	memcpy(p + 4, duid_prefix, duid_length);
	p += 4 + duid_length;
	random_request6 = p - template_request6;
	/* option request option */
	p[1] = DHCP6_OPT_ORO;
	p[3] = 4;
	p[5] = DHCP6_OPT_NAME_SERVERS;
	p[7] = DHCP6_OPT_DOMAIN_SEARCH;
	p += 8;
	/* server ID and IA_NA */
	serverid_request6 = p - template_request6;
	reqaddr_request6 = p - template_request6;
	/* set length */
	length_request6 = p - template_request6;
}

/*
 * get a DHCPv6 third packet (usually a REQUEST) template
 * from the file given in the command line (-T<template-file>)
 * and offsets (-X,-O,-E,-S,-I).
 */

void
get_template_request6(void)
{
	uint8_t *p = template_request6;
	int fd, cc, i, j;

	fd = open(templatefile[1], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile[1], strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile[1], strerror(errno));
		exit(1);
	}
	if (cc < 10) {
		fprintf(stderr, "file '%s' too short\n", templatefile[1]);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile[1]);
		exit(2);
	}
	j = 0;
	for (i = 0; i < cc; i++) {
		if (isspace((int) tbuf[i]))
			continue;
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile[1]);
			exit(2);
		}
		tbuf[j] = tbuf[i];
		j++;
	}
	cc = j;
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile[1]);
		exit(2);
	}
	length_request6 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset[1] >= 0)
		xid_request6 = (size_t) xidoffset[1];
	else
		xid_request6 = DHCP6_OFF_XID;
	if (xid_request6 + 3 > length_request6) {
		fprintf(stderr,
			"xid (at %zu) is outside the template (length %zu)?\n",
			xid_request6, length_request6);
		exit(2);
	}
	if (rndoffset[1] >= 0)
		random_request6 = (size_t) rndoffset[1];
	else
		random_request6 = 0;
	if (random_request6 > length_request6) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_request6, length_request6);
		exit(2);
	}
	if (elpoffset >= 0)
		elapsed_request6 = (size_t) elpoffset;
	if (elapsed_request6 + 2 > length_request6) {
		fprintf(stderr,
			"secs (at %zu) outside the template (length %zu)?\n",
			elapsed_request6, length_request6);
		exit(2);
	}
	serverid_request6 = (size_t) sidoffset;
	if (serverid_request6 > length_request6) {
		fprintf(stderr,
			"server-id option (at %zu) outside the template "
			"(length %zu)?\n",
			serverid_request6, length_request6);
		exit(2);
	}
	reqaddr_request6 = (size_t) ripoffset;
	if (reqaddr_request6 > length_request6) {
		fprintf(stderr,
			"requested-ip-address option (at %zu) outside "
			"the template (length %zu)?\n",
			reqaddr_request6, length_request6);
		exit(2);
	}
}

/*
 * send the DHCPv6 REQUEST third packet
 * (the transaction ID is odd)
 * (TODO: check for errors in the ADVERTISE)
 */

void
send_request6(struct exchange *x0)
{
	struct exchange *x;
	struct xlist *bucket;
	size_t len;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL) {
		locallimit++;
		perror("send2");
		return;
	}

	memcpy(x, x0, sizeof(*x));
	x->order2 = xscount2++;
	x->xid |= 1;
	hash = x->xid >> 1;

	ISC_TAILQ_INSERT_TAIL(&xsent2, x, gchain);
	hash &= hashsize2 - 1;
	bucket = (struct xlist *) (exchanges2 + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	len = length_request6;
	memcpy(obuf, template_request6, len);
	/* xid */
	obuf[xid_request6] = x->xid >> 16;
	obuf[xid_request6 + 1] = x->xid >> 8;
	obuf[xid_request6 + 2] = x->xid;
	/* random */
	randomize(random_request6, x->rnd);
	/* elapsed time */
	if (elapsed_request6 > 0) {
		int et;

		et = (x->ts1.tv_sec - x->ts0.tv_sec) * 100;
		et += (x->ts1.tv_nsec - x->ts0.tv_nsec) / 10000000;
		if (et > 65535) {
			obuf[elapsed_request6] = 0xff;
			obuf[elapsed_request6 + 1] = 0xff;
		} else if (et > 0) {
			obuf[elapsed_request6] = et >> 8;
			obuf[elapsed_request6 + 1] = et & 0xff;
		}
	}
	/* server ID */
	if (serverid_request6 < length_request6)
		memmove(obuf + serverid_request6 + x->sidlen,
			obuf + serverid_request6,
			x->sidlen);
	memcpy(obuf + serverid_request6, x->sid, x->sidlen);
	len += x->sidlen;
	/* IA_NA */
	if (reqaddr_request6 < serverid_request6) {
		memmove(obuf + reqaddr_request6 + x->ianalen,
			obuf + reqaddr_request6,
			x->ianalen);
		memcpy(obuf + reqaddr_request6, x->iana, x->ianalen);
	} else if (reqaddr_request6 < length_request6) {
		memmove(obuf + reqaddr_request6 + x->sidlen + x->ianalen,
			obuf + reqaddr_request6 + x->sidlen,
			x->ianalen);
		memcpy(obuf + reqaddr_request6+ x->sidlen,
		       x->iana,
		       x->ianalen);
	} else
		memcpy(obuf + len, x->iana, x->ianalen);
	len += x->ianalen;

	/* timestamp */
	ret = clock_gettime(CLOCK_REALTIME, &x->ts2);
	if (ret < 0) {
		perror("clock_gettime(send2)");
		fatal = 1;
		return;
	}
	ret = sendto(sock, obuf, len, 0,
		     (struct sockaddr *) &serveraddr,
		     sizeof(struct sockaddr_in6));
	if (ret >= 0)
		return;
	if ((errno == EAGAIN) || (errno == EWOULDBLOCK) ||
	    (errno == ENOBUFS) || (errno == ENOMEM))
		locallimit++;
	perror("send2");
}

/*
 * send the DHCPv6 SOLICIT first packet
 * (for 4-exchange, the transaction ID xid is even)
 */

int
send6(void)
{
	struct exchange *x;
	struct xlist *bucket;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL)
		return -ENOMEM;

	memset(x, 0, sizeof(*x));
	x->order0 = xscount0++;
	hash = x->rnd = (uint32_t) random();
	if (simple == 0)
		x->xid = (hash << 1) & 0x00ffffff;
	else
		x->xid = hash & 0x00ffffff;

	ISC_TAILQ_INSERT_TAIL(&xsent0, x, gchain);
	hash &= hashsize0 - 1;
	bucket = (struct xlist *) (exchanges0 + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	memcpy(obuf, template_solicit6, length_solicit6);
	/* xid */
	obuf[xid_solicit6] = x->xid >> 16;
	obuf[xid_solicit6 + 1] = x->xid >> 8;
	obuf[xid_solicit6 + 2] = x->xid;
	/* random */
	x->rnd = randomize(random_solicit6, x->rnd);

	/* timestamp */
	ret = clock_gettime(CLOCK_REALTIME, &last);
	if (ret < 0) {
		perror("clock_gettime(send)");
		fatal = 1;
		return -errno;
	}
	x->ts0 = last;
	errno = 0;
	ret = sendto(sock, obuf, length_solicit6, 0,
		     (struct sockaddr *) &serveraddr,
		     sizeof(struct sockaddr_in6));
	if (ret == (ssize_t) length_solicit6)
		return 0;
	return -errno;
}

/*
 * scan a DHCPv6 ADVERTISE to get its server-id option
 */

int
scan_for_srvid6(struct exchange *x, size_t cc)
{
	size_t off = DHCP6_OFF_OPTIONS, len;

	for (;;) {
		if (off + 4 > cc) {
			fprintf(stderr, "server-id not found\n");
			return -1;
		}
		if ((ibuf[off] == 0) && (ibuf[off + 1] == DHCP6_OPT_SERVERID))
			break;
		off += 4 + (ibuf[off + 2] << 8) + ibuf[off + 3];
	}
	len = 4 + (ibuf[off + 2] << 8) + ibuf[off + 3];
	/* cache it in the global variables when required and not yet done */
	if ((usefirst != 0) && (gsrvid == NULL)) {
		if (len <= sizeof(gsrvidbuf)) {
			memcpy(gsrvidbuf, ibuf + off, len);
			gsrvid = gsrvidbuf;
			gsrvidlen = len;
		} else {
			gsrvid = (uint8_t *) malloc(len);
			if (gsrvid == NULL) {
				perror("malloc(gsrvid");
				return -1;
			}
			memcpy(gsrvid, ibuf + off, len);
			gsrvidlen = len;
		}
	}
	x->sid = ibuf + off;
	x->sidlen = len;
	return 0;
}

/*
 * scan a DHCPv6 ADVERTISE to get its IA_NA option
 * (TODO: check for errors)
 */

int
scan_for_ia_na(struct exchange *x, size_t cc)
{
	size_t off = DHCP6_OFF_OPTIONS, len;

	for (;;) {
		if (off + 4 > cc) {
			fprintf(stderr, "ia-na not found\n");
			return -1;
		}
		if ((ibuf[off] == 0) && (ibuf[off + 1] == DHCP6_OPT_IA_NA))
			break;
		off += 4 + (ibuf[off + 2] << 8) + ibuf[off + 3];
	}
	len = 4 + (ibuf[off + 2] << 8) + ibuf[off + 3];
	x->iana = ibuf + off;
	x->ianalen = len;
	return 0;
}

/*
 * receive a DHCPv6 packet
 */

void
receive6(void)
{
	struct exchange *x, *t;
	struct xlist *bucket;
	struct timespec now;
	ssize_t cc;
	uint32_t xid, hash;
	int checklost = 0;
	double delta;

	cc = recv(sock, ibuf, sizeof(ibuf), 0);
	if (cc < 0) {
		if ((errno == EAGAIN) ||
		    (errno == EWOULDBLOCK) ||
		    (errno == EINTR))
			return;
		perror("recv");
		fatal = 1;
		return;
	}
	/* enforce a reasonable length */
	if (cc < 22) {
		tooshort++;
		return;
	}
	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		perror("clock_gettime(receive)");
		fatal = 1;
		return;
	}
	xid = ibuf[xid_solicit6] << 16;
	xid |= ibuf[xid_solicit6 + 1] << 8;
	xid |= ibuf[xid_solicit6 + 2];
	/* 4-packet exchange even/odd xid */
	if (simple == 0) {
		if ((xid & 1) != 0) {
			receive_reply(xid, &now);
			return;
		}
		hash = (xid >> 1) & (hashsize0 - 1);
	} else
		hash = xid & (hashsize0 - 1);
	/* now it is the second packet, get the bucket which is needed */
	bucket = (struct xlist *) (exchanges0 + hash * sizeof(*bucket));
	/* try the 'next to be received' cache */
	if ((xnext0 != NULL) && (xnext0->xid == xid)) {
		x = xnext0;
		goto found;
	}
	/* if the rate is not illimited, garbage collect up to 3
	   timed-out exchanges */
	if (rate != 0)
		checklost = 3;
	/* look for the exchange */
	ISC_TAILQ_FOREACH_SAFE(x, bucket, hchain, t) {
		double waited;

		if (x->xid == xid)
			goto found;
		if (checklost <= 0)
			continue;
		/* check for a timed-out exchange */
		waited = now.tv_sec - x->ts0.tv_sec;
		waited += (now.tv_nsec - x->ts0.tv_nsec) / 1e9;
		if (waited < losttime[0]) {
			checklost = 0;
			continue;
		}
		/* garbage collect timed-out exchange */
		checklost--;
		ISC_TAILQ_REMOVE(bucket, x, hchain);
		ISC_TAILQ_REMOVE(&xsent0, x, gchain);
		free(x);
		collected[0] += 1;
	}
	/* no match? very late or not for us */
	orphans++;
	return;

	/* got it: update stats and move to the received queue */
    found:
	xrcount0++;
	x->ts1 = now;
	delta = x->ts1.tv_sec - x->ts0.tv_sec;
	delta += (x->ts1.tv_nsec - x->ts0.tv_nsec) / 1e9;
	if (delta < dmin0)
		dmin0 = delta;
	if (delta > dmax0)
		dmax0 = delta;
	dsum0 += delta;
	dsumsq0 += delta * delta;
	xnext0 = ISC_TAILQ_NEXT(x, gchain);
	ISC_TAILQ_REMOVE(bucket, x, hchain);
	ISC_TAILQ_REMOVE(&xsent0, x, gchain);
	ISC_TAILQ_INSERT_TAIL(&xrcvd0, x, gchain);
	/* if the exchange is not finished, go to the second part */
	if (simple == 0) {
		int ret = 0;

		/* the server-ID option is needed */
		if ((usefirst != 0) && (gsrvid != NULL)) {
			x->sid = gsrvid;
			x->sidlen = gsrvidlen;
		} else
			ret = scan_for_srvid6(x, cc);
		/* and the IA_NA option too */
		if (ret >= 0)
			ret = scan_for_ia_na(x, cc);
		if (ret >= 0)
			send_request6(x);
	}
}

/*
 * decode a base command line parameter
 * (currently only MAC address and DUID are supported)
 */

void
decodebase(void)
{
	char *b0 = base[basecnt];

	/* MAC address (alias Ethernet address) */
	if ((strncasecmp(b0, "mac=", 4) == 0) ||
	    (strncasecmp(b0, "ether=", 6) == 0)) {
		char *b;

		b = strchr(b0, '=') + 1;
		if (sscanf(b, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
			   &mac_prefix[0], &mac_prefix[1],
			   &mac_prefix[2], &mac_prefix[3],
			   &mac_prefix[4], &mac_prefix[5]) == 6) {
			if ((diags != NULL) && (strchr(diags, 'a') != NULL))
				printf("set MAC to %s\n", b);
			return;
		}
		fprintf(stderr,
			"expected base in '%*s=xx:xx:xx:xx:xx:xx' format\n",
			(int) (b - b0 - 1), b0);
			exit(2);
	}
	/* DUID */
	if (strncasecmp(b0, "duid=", 5) == 0) {
		char *b;
		size_t i, l;

		if (duid_prefix != NULL) {
			fprintf(stderr, "duid was already set?\n");
			exit(2);
		}
		b = strchr(b0, '=') + 1;
		l = 0;
		while (*b != '\0') {
			if (!isxdigit((int) *b)) {
				fprintf(stderr,
					"illegal char '%c' in duid\n",
					(int) *b);
				exit(2);
			}
			b++;
			l++;
		}
		if ((l & 1) != 0) {
			fprintf(stderr,
				"odd number of hexadecimal digits in duid\n");
			exit(2);
		}
		l /= 2;
		if (l > 64) {
			fprintf(stderr, "duid too large\n");
			exit(2);
		}
		duid_prefix = (uint8_t *) malloc(l);
		if (duid_prefix == NULL) {
			perror("malloc(duid)");
			exit(1);
		}
		b = strchr(b0, '=') + 1;
		for (i = 0; i < l; i++, b += 2)
			(void) sscanf(b, "%02hhx", &duid_prefix[i]);
		duid_length = l;
		if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
			b = strchr(b0, '=') + 1;
			printf("set DUID[%d] to %s\n",
			       duid_length, b);
		}
		return;
	}
	/* other */
	fprintf(stderr, "not yet supported base '%s'\n", b0);
	exit(2);
}
			   
/*
 * get the server socket address from the command line:
 *  - flags: inherited from main, 0 or AI_NUMERICHOST (for literals)
 */

void
getserveraddr(const int flags)
{
	struct addrinfo hints, *res;
	char *service;
	int ret;

	memset(&hints, 0, sizeof(hints));
	if (ipversion == 4) {
		hints.ai_family = AF_INET;
		service = "67";
	} else {
		hints.ai_family = AF_INET6;
		service = "547";
	}
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_ADDRCONFIG | AI_NUMERICSERV | flags;
	hints.ai_protocol = IPPROTO_UDP;
	
	ret = getaddrinfo(servername, service, &hints, &res);
	if (ret != 0) {
		fprintf(stderr, "bad server=%s: %s\n",
			servername, gai_strerror(ret));
		exit(2);
	}
	if (res->ai_next != NULL) {
		fprintf(stderr, "ambiguous server=%s\n", servername);
		exit(2);
	}
	memcpy(&serveraddr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
}

/*
 * get the interface from the command line:
 *   - name of the interface
 *   - socket address to fill
 * (in IPv6, get the first link-local address)
 */

void
getinterface(const char *name, struct sockaddr_storage *ss)
{
	struct ifaddrs *ifaddr, *ifa;
	int ret;
	size_t len;

	ret = getifaddrs(&ifaddr);
	if (ret < 0) {
		perror("getifaddrs");
		exit(1);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_name == NULL)
			continue;
		if (strcmp(ifa->ifa_name, name) != 0)
			continue;
		if ((ifa->ifa_flags & IFF_UP) == 0)
			continue;
		if ((ifa->ifa_flags & IFF_MULTICAST) == 0)
			continue;
		if (ifa->ifa_addr == NULL)
			continue;
		if ((ipversion == 4) &&
		    (ifa->ifa_addr->sa_family != AF_INET))
			continue;
		if (ipversion == 6) {
			struct sockaddr_in6 *a6;

			a6 = (struct sockaddr_in6 *) ifa->ifa_addr;
			if (a6->sin6_family != AF_INET6)
				continue;
			if (!IN6_IS_ADDR_LINKLOCAL(&a6->sin6_addr))
				continue;
		}
		if (ipversion == 4)
			len = sizeof(struct sockaddr_in);
		else
			len = sizeof(struct sockaddr_in6);
		memcpy(ss, ifa->ifa_addr, len);
		/* fill the server port */
		if (ipversion == 4)
			((struct sockaddr_in *) ss)->sin_port = htons(67);
		else
			((struct sockaddr_in6 *) ss)->sin6_port = htons(546);
		return;
	}
	fprintf(stderr, "can't find interface %s\n", name);
	exit(1);
}

/*
 * get the local socket address from the command line
 * (if it doesn't work, try an interface name)
 */

void
getlocaladdr(void)
{
	struct addrinfo hints, *res;
	char *service;
	int ret;

	memset(&hints, 0, sizeof(hints));
	if (ipversion == 4) {
		hints.ai_family = AF_INET;
		service = "67";
	} else {
		hints.ai_family = AF_INET6;
		service = "546";
	}
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_ADDRCONFIG | AI_NUMERICSERV;
	hints.ai_protocol = IPPROTO_UDP;
	
	ret = getaddrinfo(localname, service, &hints, &res);
	if ((ret == EAI_NONAME)
#ifdef EAI_NODATA
	    || (ret == EAI_NODATA)
#endif
	   ) {
		isinterface = 1;
		getinterface(localname, &localaddr);
		return;
	}
	if (ret != 0) {
		fprintf(stderr,
			"bad -l<local-addr=%s>: %s\n",
			localname,
			gai_strerror(ret));
		exit(2);
	}
	/* refuse multiple addresses */
	if (res->ai_next != NULL) {
		fprintf(stderr,
			"ambiguous -l<local-addr=%s>\n",
			localname);
		exit(2);
	}
	memcpy(&localaddr, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	return;
}

/*
 * get the local socket address from the server one
 */

void
getlocal(void)
{
	int ret, s;
	socklen_t l;

	if (ipversion == 4) {
		l = sizeof(struct sockaddr_in);
		s = socket(PF_INET, SOCK_DGRAM, 0);
	} else {
		l = sizeof(struct sockaddr_in6);
		s = socket(PF_INET6, SOCK_DGRAM, 0);
	}
	if (s < 0) {
		perror("socket");
		exit(1);
	}
	if ((ipversion == 4) && (isbroadcast != 0)) {
		int on = 1;

		ret = setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
		if (ret < 0) {
			perror("setsockopt(SO_BROADCAST)");
			exit(1);
		}
	}
	ret = connect(s, (struct sockaddr *) &serveraddr, l);
	if (ret < 0) {
		perror("connect");
		exit(1);
	}
	l = sizeof(localaddr);
	ret = getsockname(s, (struct sockaddr *) &localaddr, &l);
	if (ret < 0) {
		perror("getsockname");
		exit(1);
	}
	(void) close(s);
	/* fill the local port */
	if (ipversion == 4)
		((struct sockaddr_in *) &localaddr)->sin_port = htons(67);
	else
		((struct sockaddr_in6 *) &localaddr)->sin6_port = htons(546);
}

/*
 * intermediate reporting
 * (note: an in-transit packet can be reported as dropped)
 */

void
reporting(void)
{
	dreport.tv_sec += report;

	if (xscount2 == 0) {
		printf("sent: %llu, received: %llu (drops: %lld)",
		       (unsigned long long) xscount0,
		       (unsigned long long) xrcount0,
		       (long long) (xscount0 - xrcount0));
		if (!ISC_TAILQ_EMPTY(&xrcvd0)) {
			double avg;

			avg = dsum0 / xrcount0;
			printf(" average: %.3f ms", avg * 1e3);
		}
	} else {
		printf("sent: %llu/%llu received: %llu/%llu "
		       "(drops: %lld/%lld)",
		       (unsigned long long) xscount0,
		       (unsigned long long) xscount2,
		       (unsigned long long) xrcount0,
		       (unsigned long long) xrcount2,
		       (long long) (xscount0 - xrcount0),
		       (long long) (xscount2 - xrcount2));
		if (!ISC_TAILQ_EMPTY(&xrcvd0)) {
			double avg0, avg2;

			avg0 = dsum0 / xrcount0;
			if (xrcount2 != 0)
				avg2 = dsum2 / xrcount2;
			else
				avg2 = 0.;
			printf(" average: %.3f/%.3f ms",
			       avg0 * 1e3, avg2 * 1e3);
		}
	}
	printf("\n");
}

/*
 * SIGCHLD handler
 */

void
reapchild(int sig)
{
	int status;

	sig = sig;
	while (wait3(&status, WNOHANG, NULL) > 0)
		/* continue */;
}

/*
 * SIGINT handler
 */

void
interrupt(int sig)
{
	sig = sig;
	interrupted = 1;
}

/*
 * '-v' handler
 */

void
version(void)
{
	fprintf(stderr, "version 0.01\n");
}

/*
 * usage (from the wiki)
 */

void
usage(void)
{
	fprintf(stderr, "%s",
"perfdhcp [-hv] [-4|-6] [-r<rate>] [-t<report>] [-R<range>] [-b<base>]\n"
"    [-n<num-request>] [-p<test-period>] [-d<drop-time>] [-D<max-drop>]\n"
"    [-l<local-addr|interface>] [-P<preload>] [-a<aggressivity>]\n"
"    [-L<local-port>] [-s<seed>] [-i] [-B] [-c] [-1]\n"
"    [-T<template-file>] [-X<xid-offset>] [-O<random-offset]\n"
"    [-E<time-offset>] [-S<srvid-offset>] [-I<ip-offset>]\n"
"    [-x<diagnostic-selector>] [-w<wrapped>] [server]\n"
"\f\n"
"The [server] argument is the name/address of the DHCP server to\n"
"contact.  For DHCPv4 operation, exchanges are initiated by\n"
"transmitting a DHCP DISCOVER to this address.\n"
"\n"
"For DHCPv6 operation, exchanges are initiated by transmitting a DHCP\n"
"SOLICIT to this address.  In the DHCPv6 case, the special name 'all'\n"
"can be used to refer to All_DHCP_Relay_Agents_and_Servers (the\n"
"multicast address FF02::1:2), or the special name 'servers' to refer\n"
"to All_DHCP_Servers (the multicast address FF05::1:3).  The [server]\n"
"argument is optional only in the case that -l is used to specify an\n"
"interface, in which case [server] defaults to 'all'.\n"
"\n"
"The default is to perform a single 4-way exchange, effectively pinging\n"
"the server.\n"
"The -r option is used to set up a performance test, without\n"
"it exchanges are initiated as fast as possible.\n"
"\n"
"Options:\n"
"-1: Take the server-ID option from the first received message.\n"
"-4: DHCPv4 operation (default). This is incompatible with the -6 option.\n"
"-6: DHCPv6 operation. This is incompatible with the -4 option.\n"
"-a<aggressivity>: When the target sending rate is not yet reached,\n"
"    control how many exchanges are initiated before the next pause.\n"
"-b<base>: The base MAC, DUID, IP, etc, used to simulate different\n"
"    clients.  This can be specified multiple times, each instance is\n"
"    in the <type>=<value> form, for instance:\n"
"    (and default) MAC=00:0c:01:02:03:04.\n"
"-d<drop-time>: Specify the time after which a request is treated as\n"
"    having been lost.  The value is given in seconds and may contain a\n"
"    fractional component.  The default is 1 second.\n"
"-E<time-offset>: Offset of the (DHCPv4) secs field / (DHCPv6)\n"
"    elapsed-time option in the (second/request) template.\n"
"    The value 0 disables it.\n"
"-h: Print this help.\n"
"-i: Do only the initial part of an exchange: DO or SA, depending on\n"
"    whether -6 is given.\n"
"-I<ip-offset>: Offset of the (DHCPv4) IP address in the requested-IP\n"
"    option / (DHCPv6) IA_NA option in the (second/request) template.\n"
"-l<local-addr|interface>: For DHCPv4 operation, specify the local\n"
"    hostname/address to use when communicating with the server.  By\n"
"    default, the interface address through which traffic would\n"
"    normally be routed to the server is used.\n"
"    For DHCPv6 operation, specify the name of the network interface\n"
"    via which exchanges are initiated.\n"
"-L<local-port>: Specify the local port to use\n"
"    (the value 0 means to use the default).\n"
"-O<random-offset>: Offset of the last octet to randomize in the template.\n"
"-P<preload>: Initiate first <preload> exchanges back to back at startup.\n"
"-r<rate>: Initiate <rate> DORA/SARR (or if -i is given, DO/SA)\n"
"    exchanges per second.  A periodic report is generated showing the\n"
"    number of exchanges which were not completed, as well as the\n"
"    average response latency.  The program continues until\n"
"    interrupted, at which point a final report is generated.\n"
"-R<range>: Specify how many different clients are used. With 1\n"
"    (the default), all requests seem to come from the same client.\n"
"-s<seed>: Specify the seed for randomization, making it repeatable.\n"
"-S<srvid-offset>: Offset of the server-ID option in the\n"
"    (second/request) template.\n"
"-T<template-file>: The name of a file containing the template to use\n"
"    as a stream of hexadecimal digits.\n"
"-v: Report the version number of this program.\n"
"-w<wrapped>: Command to call with start/stop at the beginning/end of\n"
"    the program.\n"
"-x<diagnostic-selector>: Include extended diagnostics in the output.\n"
"    <diagnostic-selector> is a string of single-keywords specifying\n"
"    the operations for which verbose output is desired.  The selector\n"
"    keyletters are:\n"
"   * 'a': print the decoded command line arguments\n"
"   * 'e': print the exit reason\n"
"   * 'i': print rate processing details\n"
"   * 'r': print randomization details\n"
"   * 's': print first server-id\n"
"   * 't': when finished, print timers of all successful exchanges\n"
"   * 'T': when finished, print templates\n"
"-X<xid-offset>: Transaction ID (aka. xid) offset in the template.\n"
"\n"
"DHCPv4 only options:\n"
"-B: Force broadcast handling.\n"
"\n"
"DHCPv6 only options:\n"
"-c: Add a rapid commit option (exchanges will be SA).\n"
"\n"
"The remaining options are used only in conjunction with -r:\n"
"\n"
"-D<max-drop>: Abort the test if more than <max-drop> requests have\n"
"    been dropped.  Use -D0 to abort if even a single request has been\n"
"    dropped.  If <max-drop> includes the suffix '%', it specifies a\n"
"    maximum percentage of requests that may be dropped before abort.\n"
"    In this case, testing of the threshold begins after 10 requests\n"
"    have been expected to be received.\n"
"-n<num-request>: Initiate <num-request> transactions.  No report is\n"
"    generated until all transactions have been initiated/waited-for,\n"
"    after which a report is generated and the program terminates.\n"
"-p<test-period>: Send requests for the given test period, which is\n"
"    specified in the same manner as -d.  This can be used as an\n"
"    alternative to -n, or both options can be given, in which case the\n"
"    testing is completed when either limit is reached.\n"
"-t<report>: Delay in seconds between two periodic reports.\n"
"\n"
"Errors:\n"
"- tooshort: received a too short message\n"
"- orphans: received a message which doesn't match an exchange\n"
"   (duplicate, late or not related)\n"
"- locallimit: reached to local system limits when sending a message.\n"
"\n"
"Exit status:\n"
"The exit status is:\n"
"0 on complete success.\n"
"1 for a general error.\n"
"2 if an error is found in the command line arguments.\n"
"3 if there are no general failures in operation, but one or more\n"
"  exchanges are not successfully completed.\n");
}

/*
 * main function / entry point
 */

int
main(const int argc, char * const argv[])
{
	int opt, flags = 0, ret, i;
	long long r;
	char *pc;
	extern char *optarg;
	extern int optind;

#define OPTIONS	"hv46r:t:R:b:n:p:d:D:l:P:a:L:s:iBc1T:X:O:E:S:I:x:w:"

	/* decode options */
	while ((opt = getopt(argc, argv, OPTIONS)) != -1)
	switch (opt) {
	case 'h':
		usage();
		exit(0);

	case 'v':
		version();
		exit(0);

	case '4':
		if (ipversion == 6) {
			fprintf(stderr, "IP version already set to 6\n");
			usage();
			exit(2);
		}
		ipversion = 4;
		break;

	case '6':
		if (ipversion == 4) {
			fprintf(stderr, "IP version already set to 4\n");
			usage();
			exit(2);
		}
		ipversion = 6;
		break;

	case 'r':
		rate = atoi(optarg);
		if (rate <= 0) {
			fprintf(stderr, "rate must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 't':
		report = atoi(optarg);
		if (report <= 0) {
			fprintf(stderr, "report must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'R':
		r = atoll(optarg);
		if (r < 0) {
			fprintf(stderr,
				"range must not be a negative integer\n");
			usage();
			exit(2);
		}
		range = (uint32_t) r;
		if ((range != 0) && (range != UINT32_MAX)) {
			uint32_t s = range + 1;
			uint64_t b = UINT32_MAX + 1, m;

			m = (b / s) * s;
			if (m == b)
				maxrandom = 0;
			else
				maxrandom = (uint32_t) m;
		}
		break;

	case 'b':
		if (basecnt > 3) {
			fprintf(stderr, "too many bases\n");
			usage();
			exit(2);
		}
		base[basecnt] = optarg;
		decodebase();
		basecnt++;
		break;

	case 'n':
		numreq[gotnumreq] = atoi(optarg);
		if (numreq[gotnumreq] <= 0) {
			fprintf(stderr,
				"num-request must be a positive integer\n");
			usage();
			exit(2);
		}
		gotnumreq = 1;
		break;

	case 'p':
		period = atoi(optarg);
		if (period <= 0) {
			fprintf(stderr,
				"test-period must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'd':
		losttime[gotlosttime] = atof(optarg);
		if (losttime[gotlosttime] <= 0.) {
			fprintf(stderr,
				"drop-time must be a positive number\n");
			usage();
			exit(2);
		}
		gotlosttime = 1;
		break;

	case 'D':
		pc = strchr(optarg, '%');
		if (pc != NULL) {
			*pc = '\0';
			maxpdrop[gotmaxdrop] = atof(optarg);
			if ((maxpdrop[gotmaxdrop] <= 0) ||
			    (maxpdrop[gotmaxdrop] >= 100)) {
				fprintf(stderr,
					"invalid drop-time percentage\n");
				usage();
				exit(2);
			}
			gotmaxdrop = 1;
			break;
		}
		maxdrop[gotmaxdrop] = atoi(optarg);
		if (maxdrop[gotmaxdrop] <= 0) {
			fprintf(stderr,
				"max-drop must be a positive integer\n");
			usage();
			exit(2);
		}
		gotmaxdrop = 1;
		break;

	case 'l':
		localname = optarg;
		break;

	case 'P':
		preload = atoi(optarg);
		if (preload < 0) {
			fprintf(stderr,
				"preload must not be a negative integer\n");
			usage();
			exit(2);
		}
		break;

	case 'a':
		aggressivity = atoi(optarg);
		if (aggressivity <= 0) {
			fprintf(stderr,
				"aggressivity must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'L':
		localport = atoi(optarg);
		if (localport < 0) {
			fprintf(stderr,
				"local-port must not be a negative integer\n");
			usage();
			exit(2);
		}
		if (localport > (int) UINT16_MAX) {
			fprintf(stderr,
				"local-port must be lower than %d\n",
				(int) UINT16_MAX);
			usage();
			exit(2);
		}
		break;

	case 's':
		seeded = 1;
		seed = (unsigned int) atol(optarg);
		break;

	case 'i':
		simple = 1;
		break;

	case 'B':
		isbroadcast = 1;
		break;

	case 'c':
		rapidcommit = 1;
		break;

	case '1':
		usefirst = 1;
		break;

	case 'T':
		if (templatefile[0] != NULL) {
			if (templatefile[1] != NULL) {
				fprintf(stderr,
					"template-files are already set\n");
				usage();
				exit(2);
			}
			templatefile[1] = optarg;
		} else
			templatefile[0] = optarg;
		break;

	case 'X':
		if (xidoffset[0] >= 0)
			i = 1;
		else
			i = 0;
		xidoffset[i] = atoi(optarg);
		if (xidoffset[i] <= 0) {
			fprintf(stderr,
				"xid-offset must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'O':
		if (rndoffset[0] >= 0)
			i = 1;
		else
			i = 0;
		rndoffset[i] = atoi(optarg);
		if (rndoffset[i] < 3) {
			fprintf(stderr,
				"random-offset must be greater than 3\n");
			usage();
			exit(2);
		}
		break;

	case 'E':
		elpoffset = atoi(optarg);
		if (elpoffset < 0) {
			fprintf(stderr,
				"time-offset must not be a "
				"negative integer\n");
			usage();
			exit(2);
		}
		break;

	case 'S':
		sidoffset = atoi(optarg);
		if (sidoffset <= 0) {
			fprintf(stderr,
				"srvid-offset must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'I':
		ripoffset = atoi(optarg);
		if (ripoffset <= 0) {
			fprintf(stderr,
				"ip-offset must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'x':
		diags = optarg;
		break;

	case 'w':
		wrapped = optarg;
		break;

	default:
		usage();
		exit(2);
	}

	/* adjust some global variables */
	if (ipversion == 0)
		ipversion = 4;
	if (templatefile[1] != NULL) {
		if (xidoffset[1] < 0)
			xidoffset[1] = xidoffset[0];
		if (rndoffset[1] < 0)
			rndoffset[1] = rndoffset[0];
	}

	/* when required, print the internal view of the command line */
	if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
		printf("IPv%d", ipversion);
		if (simple != 0) {
			if (ipversion == 4)
				printf(" DO only");
			else
				printf(" SA only");
		}
		if (rate != 0)
			printf(" rate=%d", rate);
		if (report != 0)
			printf(" report=%d", report);
		if (range != 0) {
			if (strchr(diags, 'r') != NULL)
				printf(" range=0..%d [0x%x]",
				       range,
				       (unsigned int) maxrandom);
			else
				printf(" range=0..%d", range);
		}
		if (basecnt != 0)
			for (i = 0; i < basecnt; i++)
				printf(" base[%d]='%s'", i, base[i]);
		if (gotnumreq != 0)
			printf(" num-request=%d,%d", numreq[0], numreq[1]);
		if (period != 0)
			printf(" test-period=%d", period);
		printf(" drop-time=%g,%g", losttime[0], losttime[1]);
		if ((maxdrop[0] != 0) || (maxdrop[1] != 0))
			printf(" max-drop=%d,%d", maxdrop[0], maxdrop[1]);
		if ((maxpdrop[0] != 0.) || (maxpdrop[1] != 0.))
			printf(" max-drop=%2.2f%%,%2.2f%%",
			       maxpdrop[0], maxpdrop[1]);
		if (preload != 0)
			printf(" preload=%d", preload);
		printf(" aggressivity=%d", aggressivity);
		if (localport != 0)
			printf(" local-port=%d", localport);
		if (seeded)
			printf(" seed=%u", seed);
		if (isbroadcast != 0)
			printf(" broadcast");
		if (rapidcommit != 0)
			printf(" rapid-commit");
		if (usefirst != 0)
			printf(" use-first");
		if ((templatefile[0] != NULL) && (templatefile[1] == NULL))
			printf(" template-file='%s'", templatefile[0]);
		else if (templatefile[1] != NULL)
			printf(" template-file='%s','%s'",
			       templatefile[0], templatefile[1]);
		if ((xidoffset[0] >= 0) && (xidoffset[1] < 0))
			printf(" xid-offset=%d", xidoffset[0]);
		else if (xidoffset[1] >= 0)
			printf(" xid-offset=%d,%d",
			       xidoffset[0], xidoffset[1]);
		if ((rndoffset[0] >= 0) && (rndoffset[1] < 0))
			printf(" xid-offset=%d", rndoffset[0]);
		else if (rndoffset[1] >= 0)
			printf(" xid-offset=%d,%d",
			       rndoffset[0], rndoffset[1]);
		if (elpoffset >= 0)
			printf(" time-offset=%d", elpoffset);
		if (sidoffset >= 0)
			printf(" srvid-offset=%d", sidoffset);
		if (ripoffset >= 0)
			printf(" ip-offset=%d", ripoffset);
		printf(" diagnotic-selectors='%s'", diags);
		if (wrapped != NULL)
			printf(" wrapped='%s'", wrapped);
		printf("\n");
	}

	/* check DHCPv4 only options */
	if ((ipversion != 4) && (isbroadcast != 0)) {
		fprintf(stderr, "-b is not compatible with IPv6 (-6)\n");
		usage();
		exit(2);
	}

	/* check DHCPv6 only options */
	if ((ipversion != 6) && (rapidcommit != 0)) {
		fprintf(stderr, "-6 (IPv6) must be set to use -c\n");
		usage();
		exit(2);
	}

	/* check 4-packet (aka not simple) mode options */
	if ((simple != 0) && (numreq[1] != 0)) {
		fprintf(stderr,
			"second -n<num-request> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (losttime[1] != 1.)) {
		fprintf(stderr,
			"second -d<drop-time> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) &&
	    ((maxdrop[1] != 0) || (maxpdrop[1] != 0.))) {
		fprintf(stderr,
			"second -D<max-drop> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (usefirst != 0)) {
		fprintf(stderr,
			"-1 is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (templatefile[1] != NULL)) {
		fprintf(stderr,
			"second -T<template-file> is not "
			"compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (xidoffset[1] >= 0)) {
		fprintf(stderr,
			"second -X<xid-offset> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (rndoffset[1] >= 0)) {
		fprintf(stderr,
			"second -O<random-offset is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (elpoffset >= 0)) {
		fprintf(stderr,
			"-E<time-offset> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (sidoffset >= 0)) {
		fprintf(stderr,
			"-S<srvid-offset> is not compatible with -i\n");
		usage();
		exit(2);
	}
	if ((simple != 0) && (ripoffset >= 0)) {
		fprintf(stderr,
			"-I<ip-offset> is not compatible with -i\n");
		usage();
		exit(2);
	}


	/* check simple mode options */
	if ((simple == 0) && (rapidcommit != 0)) {
		fprintf(stderr, "-i must be set to use -c\n");
		usage();
		exit(2);
	}

	/* check rate '-r' options */
	if ((rate == 0) && (report != 0)) {
		fprintf(stderr,
			"-r<rate> must be set to use -t<report>\n");
		usage();
		exit(2);
	}
	if ((rate == 0) && ((numreq[0] != 0) || (numreq[1] != 0))) {
		fprintf(stderr,
			"-r<rate> must be set to use -n<num-request>\n");
		usage();
		exit(2);
	}
	if ((rate == 0) && (period != 0)) {
		fprintf(stderr,
			"-r<rate> must be set to use -p<test-period>\n");
		usage();
		exit(2);
	}
	if ((rate == 0) &&
	    ((maxdrop[0] != 0) || (maxdrop[1] != 0) ||
	     (maxpdrop[0] != 0.) || (maxpdrop[1] != 0.))) {
		fprintf(stderr,
			"-r<rate> must be set to use -D<max-drop>\n");
		usage();
		exit(2);
	}

	/* check (first) template file options */
	if ((templatefile[0] == NULL) && (xidoffset[0] >= 0)) {
		fprintf(stderr,
			"-T<template-file> must be set to "
			"use -X<xid-offset>\n");
		usage();
		exit(2);
	}
	if ((templatefile[0] == NULL) && (rndoffset[0] >= 0)) {
		fprintf(stderr,
			"-T<template-file> must be set to "
			"use -O<random-offset>\n");
		usage();
		exit(2);
	}

	/* check (second) template file options */
	if ((templatefile[1] == NULL) && (elpoffset >= 0)) {
		fprintf(stderr,
			"second/request -T<template-file> must be set to "
			"use -E<time-offset>\n");
		usage();
		exit(2);
	}
	if ((templatefile[1] == NULL) && (sidoffset >= 0)) {
		fprintf(stderr,
			"second/request -T<template-file> must be set to "
			"use -S<srvid-offset>\n");
		usage();
		exit(2);
	}
	if ((templatefile[1] == NULL) && (ripoffset >= 0)) {
		fprintf(stderr,
			"second/request -T<template-file> must be set to "
			"use -I<ip-offset>\n");
		usage();
		exit(2);
	}

	/* check various template file(s) and other condition(s) options */
	if ((templatefile[0] != NULL) && (range > 0) && (rndoffset[0] < 0)) {
		fprintf(stderr,
			"-O<random-offset> must be set when "
			"-T<template-file> and -R<range> are used\n");
		usage();
		exit(2);
	}
	if ((templatefile[1] != NULL) && (sidoffset < 0)) {
		fprintf(stderr,
			"-S<srvid-offset> must be set when second "
			"-T<template-file> is used\n");
		usage();
		exit(2);
	}
	if ((templatefile[1] != NULL) && (ripoffset < 0)) {
		fprintf(stderr,
			"-I<ip-offset> must be set when second "
			"-T<template-file> is used\n");
		usage();
		exit(2);
	}

	/* get the server argument */
	if (optind < argc - 1) {
		fprintf(stderr, "extra arguments?\n");
		usage();
		exit(2);
	}
	if (optind == argc - 1) {
		servername = argv[optind];
		/* decode special cases */
		if ((ipversion == 4) &&
		    (strcmp(servername, "all") == 0)) {
			flags = AI_NUMERICHOST;
			isbroadcast = 1;
			servername = "255.255.255.255";
		} else if ((ipversion == 6) &&
			   (strcmp(servername, "all") == 0)) {
			flags = AI_NUMERICHOST;
			servername = "FF02::1:2";
		} else if ((ipversion == 6) &&
			   (strcmp(servername, "servers") == 0)) {
			flags = AI_NUMERICHOST;
			servername = "FF05::1:3";
		}
	}

	/* handle the local '-l' address/interface */
	if (localname != NULL) {
		/* given */
		getlocaladdr();
		if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
			if (isinterface)
				printf("interface='%s'\n", localname);
			else
				printf("local-addr='%s'\n", localname);
		}
		/* get the not given server from it */
		if (servername == NULL) {
			if (isinterface && (ipversion == 4)) {
				flags = AI_NUMERICHOST;
				isbroadcast = 1;
				servername = "255.255.255.255";
			} else if (isinterface && (ipversion == 6)) {
				flags = AI_NUMERICHOST;
				servername = "FF02::1:2";
			} else {
				fprintf(stderr,
					"without an interface "
					"server is required\n");
				usage();
				exit(2);
			}
		}
	} else if (servername == NULL) {
		fprintf(stderr, "without an interface server is required\n");
		usage();
		exit(2);
	}
	/* get the server socket address */
	getserveraddr(flags);
	/* finish local/server socket address stuff and print it */
	if ((diags != NULL) && (strchr(diags, 'a') != NULL))
		printf("server='%s'\n", servername);
	if (localname == NULL)
		getlocal();
	if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
		char addr[NI_MAXHOST];

		ret = getnameinfo((struct sockaddr *) &localaddr,
				  sizeof(localaddr),
				  addr,
				  NI_MAXHOST,
				  NULL,
				  0,
				  NI_NUMERICHOST);
		if (ret != 0) {
			fprintf(stderr,
				"can't get the local address: %s\n",
				gai_strerror(ret));
			exit(1);
		}
		printf("local address='%s'\n", addr);
	}

	/* initialize exchange structures */
	inits();

	/* get the socket descriptor and template(s) */
	if (ipversion == 4) {
		getsock4();
		if (templatefile[0] == NULL)
			build_template_discover4();
		else
			get_template_discover4();
		if (simple == 0) {
			if (templatefile[1] == NULL)
				build_template_request4();
			else
				get_template_request4();
		}
	} else {
		getsock6();
		if (duid_prefix != NULL) {
			if (templatefile[0] == NULL)
				build_template_solicit6();
			else
				get_template_solicit6();
			if (simple == 0) {
				if (templatefile[1] == NULL)
					build_template_request6();
				else
					get_template_request6();
			}
		}
	}
	/* sanity check */
	if ((unsigned) sock > FD_SETSIZE) {
		fprintf(stderr, "socket descriptor (%d) too large?!\n", sock);
		exit(1);
	}
	/* make the socket descriptor not blocking */
	flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0) {
		perror("fcntl(F_GETFL)");
		exit(1);
	}
	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("fcntl(F_SETFL)");
		exit(1);
	}

	/* wrapped start */
	if (wrapped != NULL) {
		pid_t pid;

		(void) signal(SIGCHLD, reapchild);
		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		} else if (pid == 0)
			(void) execlp(wrapped, "start", (char *) NULL);
	}

	/* boot is done! */
	if (clock_gettime(CLOCK_REALTIME, &boot) < 0) {
		perror("clock_gettime(boot)");
		exit(1);
	}

	/* compute the next intermediate reporting date */
	if (report != 0) {
		dreport.tv_sec = boot.tv_sec + report;
		dreport.tv_nsec = boot.tv_nsec;
	}

	/* compute the DUID (the current date is needed) */
	if ((ipversion == 6) && (duid_prefix == NULL)) {
		uint32_t curdate;

		duid_length = 14;
		duid_prefix = (uint8_t *) malloc(duid_length);
		if (duid_prefix == NULL) {
			perror("malloc(duid)");
			exit(1);
		}
		duid_prefix[0] = DHCP6_DUID_LLT >> 8;
		duid_prefix[1] = DHCP6_DUID_LLT;
		duid_prefix[2] = DHCP_HTYPE_ETHER >> 8;
		duid_prefix[3] = DHCP_HTYPE_ETHER;
		curdate = htonl(boot.tv_sec - DHCP6_DUID_EPOCH);
		memcpy(duid_prefix + 4, &curdate, 4);
		memcpy(duid_prefix + 8, mac_prefix, 6);
		/* the DUID is in template(s) */
		if (templatefile[0] == NULL)
			build_template_solicit6();
		else
			get_template_solicit6();
		if (simple == 0) {
			if (templatefile[1] == NULL)
				build_template_request6();
			else
				get_template_request6();
		}
	}
		
	/* seed the random generator */
	if (seeded == 0)
		seed = (unsigned int) (boot.tv_sec + boot.tv_nsec);
	srandom(seed);

	/* preload the server with at least one packet */
	compsend = preload + 1;
	for (i = 0; i <= preload; i++) {
		if (ipversion == 4)
			ret = send4();
		else
			ret = send6();
		if (ret < 0) {
			/* failure at the first packet is fatal */
			if (i == 0) {
				fprintf(stderr,
					"initial send failed: %s\n",
					strerror(-ret));
				exit(1);
			}
			if ((errno == EAGAIN) ||
			    (errno == EWOULDBLOCK) ||
			    (errno == ENOBUFS) ||
			    (errno == ENOMEM))
				locallimit++;
			fprintf(stderr, "preload send: %s\n", strerror(-ret));
			break;
		}
	}

	/* required only before the interrupted flag check */
	(void) signal(SIGINT, interrupt);

	/* main loop */
	for (;;) {
		struct timespec now, ts;
		fd_set rfds;

		/* immediate loop exit conditions */
		if (interrupted) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("interrupted\n");
			break;
		}
		if (fatal) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("got a fatal error\n");
			break;
		}

		/* get the date and use it */
		if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
			perror("clock_gettime(now)");
			fatal = 1;
			continue;
		}
		if ((period != 0) &&
		    ((boot.tv_sec + period < now.tv_sec) ||
		     ((boot.tv_sec + period == now.tv_sec) &&
		      (boot.tv_nsec < now.tv_nsec)))) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached test-period\n");
			break;
		}
		if ((report != 0) &&
		    ((dreport.tv_sec < now.tv_sec) ||
		     ((dreport.tv_sec == now.tv_sec) &&
		      (dreport.tv_nsec < now.tv_nsec))))
			reporting();

		/* compute the delay for the next send */
		due = last;
		if (rate == 1)
			due.tv_sec += 1;
		else if (rate != 0)
			due.tv_nsec += 1010000000 / rate;
		else
			due.tv_nsec += 1;
		while (due.tv_nsec >= 1000000000) {
			due.tv_sec += 1;
			due.tv_nsec -= 1000000000;
		}
		ts = due;
		ts.tv_sec -= now.tv_sec;
		ts.tv_nsec -= now.tv_nsec;
		while (ts.tv_nsec < 0) {
			ts.tv_sec -= 1;
			ts.tv_nsec += 1000000000;
		}
		/* the send was already due? */
		if (ts.tv_sec < 0) {
			ts.tv_sec = ts.tv_nsec = 0;
			latesent++;
		}

		/* pselect() */
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);
		ret = pselect(sock + 1, &rfds, NULL, NULL, &ts, NULL);
		if (ret < 0) {
			if (errno == EINTR)
				continue;
			perror("pselect");
			fatal = 1;
			continue;
		}

		/* packet(s) to receive */
		while (ret == 1) {
			if (ipversion == 4)
				receive4();
			else
				receive6();
			if (recv(sock, ibuf, sizeof(ibuf), MSG_PEEK) <= 0)
				ret = 0;
			else
				multrcvd++;
		}
		if (fatal)
			continue;

		/* check receive loop exit conditions */
		if ((numreq[0] != 0) && ((int) xscount0 >= numreq[0])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached num-request0\n");
			break;
		}
		if ((numreq[1] != 0) && ((int) xscount2 >= numreq[1])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached num-request2\n");
			break;
		}
		if ((maxdrop[0] != 0) &&
		    ((int) (xscount0 - xrcount0) > maxdrop[0])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop%s (absolute)\n",
				       simple != 0 ? "" : "0");
			break;
		}
		if ((maxdrop[1] != 0) &&
		    ((int) (xscount2 - xrcount2) > maxdrop[1])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop2 (absolute)\n");
			break;
		}
		if ((maxpdrop[0] != 0.) &&
		    (xscount0 > 10) &&
		    (((100. * (xscount0 - xrcount0)) / xscount0)
			> maxpdrop[0])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop%s (percent)\n",
				       simple != 0 ? "" : "0");
			break;
		}
		if ((maxpdrop[1] != 0.) &&
		    (xscount2 > 10) &&
		    (((100. * (xscount2 - xrcount2)) / xscount2)
			> maxpdrop[1])) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop2 (percent)\n");
			break;
		}

		/* compute how many packets to send */
		if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
			perror("clock_gettime(now2)");
			fatal = 1;
			continue;
		}
		if ((now.tv_sec > due.tv_sec) ||
		    ((now.tv_sec == due.tv_sec) &&
		     (now.tv_nsec >= due.tv_nsec))) {
			double tosend;

			if (rate != 0) {
				tosend = (now.tv_nsec - due.tv_nsec) / 1e9;
				tosend += now.tv_sec - due.tv_sec;
				tosend *= rate;
				tosend += 1;
				if (tosend > (double) aggressivity)
					i = aggressivity;
				else
					i = (int) tosend;
			} else
				i = aggressivity;
			compsend += i;
			/* send packets */
			for (;;) {
				if (ipversion == 4)
					ret = send4();
				else
					ret = send6();
				if (ret < 0) {
					if ((errno == EAGAIN) ||
					    (errno == EWOULDBLOCK) ||
					    (errno == ENOBUFS) ||
					    (errno == ENOMEM))
						locallimit++;
					fprintf(stderr,
						"send: %s\n", strerror(-ret));
					break;
				}
				i--;
				if (i == 0)
					break;
				/* check for late packets to receive */
				if (recv(sock, ibuf, sizeof(ibuf),
					 MSG_PEEK) > 0) {
					latercvd++;
					if (ipversion == 4)
						receive4();
					else
						receive6();
				}
			}
		} else
			/* there was no packet to send */
			shortwait++;
	}

	/* after main loop: finished */
	if (clock_gettime(CLOCK_REALTIME, &finished) < 0)
		perror("clock_gettime(finished)");

	/* wrapped stop */
	if (wrapped != NULL) {
		pid_t pid;

		pid = fork();
		if (pid == 0)
			(void) execlp(wrapped, "stop", (char *) NULL);
	}

	/* main statictics */
	if (xscount2 == 0)
		printf("sent: %llu, received: %llu (drops: %lld)\n",
		       (unsigned long long) xscount0,
		       (unsigned long long) xrcount0,
		       (long long) (xscount0 - xrcount0));
	else
		printf("sent: %llu/%llu, received: %llu/%llu "
		       "(drops: %lld/%lld)\n",
		       (unsigned long long) xscount0,
		       (unsigned long long) xscount2,
		       (unsigned long long) xrcount0,
		       (unsigned long long) xrcount2,
		       (long long) (xscount0 - xrcount0),
		       (long long) (xscount2 - xrcount2));
	printf("tooshort: %llu, orphans: %llu, local limits: %llu\n",
	       (unsigned long long) tooshort,
	       (unsigned long long) orphans,
	       (unsigned long long) locallimit);

	/* print the rate */
	if (finished.tv_sec != 0) {
		double dall, erate;

		dall = (finished.tv_nsec - boot.tv_nsec) / 1e9;
		dall += finished.tv_sec - boot.tv_sec;
		erate = xrcount0 / dall;
		if (rate != 0)
			printf("rate: %f (expected %d)\n", erate, rate);
		else
			printf("rate: %f\n", erate);
	}

	/* rate processing instrumentation */
	if ((diags != NULL) && (strchr(diags, 'i') != NULL)) {
		printf("latesent: %llu, compsend: %llu, shortwait: %llu\n"
		       "multrcvd: %llu, latercvd: %llu, collected:%llu/%llu\n",
		       (unsigned long long) latesent,
		       (unsigned long long) compsend,
		       (unsigned long long) shortwait,
		       (unsigned long long) multrcvd,
		       (unsigned long long) latercvd,
		       (unsigned long long) collected[0],
		       (unsigned long long) collected[1]);
	}

	/* round-time trip statistics */
	if (xrcount2 != 0) {
		double avg0, avg2, stddev0, stddev2;
		
		avg0 = dsum0 / xrcount0;
		avg2 = dsum2 / xrcount2;
		stddev0 = sqrt(dsumsq0 / xrcount0 - avg0 * avg0);
		stddev2 = sqrt(dsumsq2 / xrcount2 - avg2 * avg2);
		printf("RTT0: min/avg/max/stddev:  %.3f/%.3f/%.3f/%.3f ms\n",
		       dmin0 * 1e3, avg0 * 1e3, dmax0 * 1e3, stddev0 * 1e3);
		printf("RTT2: min/avg/max/stddev:  %.3f/%.3f/%.3f/%.3f ms\n",
		       dmin2 * 1e3, avg2 * 1e3, dmax2 * 1e3, stddev2 * 1e3);
	} else if (xrcount0 != 0) {
		double avg, stddev;
		
		avg = dsum0 / xrcount0;
		stddev = sqrt(dsumsq0 / xrcount0 - avg * avg);
		printf("RTT%s: min/avg/max/stddev:  %.3f/%.3f/%.3f/%.3f ms\n",
		       simple != 0 ? "" : "0",
		       dmin0 * 1e3, avg * 1e3, dmax0 * 1e3, stddev * 1e3);
	}

	/* (first) server-ID option content */
	if ((diags != NULL) && (strchr(diags, 's') != NULL) &&
	    !ISC_TAILQ_EMPTY(&xrcvd0)) {
		struct exchange *x;
		size_t n;

		printf("server-id: ");
		x = ISC_TAILQ_FIRST(&xrcvd0);
		if (ipversion == 4)
			n = 2;
		else
			n = 4;
		for (; n < x->sidlen; n++)
			printf("%02hhx", x->sid[n]);
		printf("\n");
	}

	/* all time-stamps */
	if ((diags != NULL) && (strchr(diags, 't') != NULL) &&
	    !ISC_TAILQ_EMPTY(&xrcvd0)) {
		struct exchange *x;

		printf("\n\n");
		ISC_TAILQ_FOREACH(x, &xrcvd0, gchain)
			printf("%ld.%09ld %ld.%09ld\n",
			       (long) x->ts0.tv_sec, x->ts0.tv_nsec,
			       (long) x->ts1.tv_sec, x->ts1.tv_nsec);

	}
	if ((diags != NULL) && (strchr(diags, 't') != NULL) &&
	    !ISC_TAILQ_EMPTY(&xrcvd2)) {
		struct exchange *x;

		printf("--\n");
		ISC_TAILQ_FOREACH(x, &xrcvd2, gchain)
			printf("%ld.%09ld %ld.%09ld %ld.%09ld %ld.%09ld\n",
			       (long) x->ts0.tv_sec, x->ts0.tv_nsec,
			       (long) x->ts1.tv_sec, x->ts1.tv_nsec,
			       (long) x->ts2.tv_sec, x->ts2.tv_nsec,
			       (long) x->ts3.tv_sec, x->ts3.tv_nsec);

	}
	if ((diags != NULL) && (strchr(diags, 't') != NULL) &&
	    !ISC_TAILQ_EMPTY(&xrcvd0))
		printf("\n\n");

	/* template(s) */
	if ((diags != NULL) && (strchr(diags, 'T') != NULL)) {
		size_t n;

		if (ipversion == 4) {
			printf("length = %zu\n", length_discover4);
			printf("xid offset = %d\n", DHCP_OFF_XID);
			printf("xid length = 4\n");
			printf("random offset = %zu\n", random_discover4);
			printf("content:\n");
			for (n = 0; n < length_discover4; n++) {
				printf("%s%02hhx",
				       (n & 15) == 0 ? "" : " ",
				       template_discover4[n]);
				if ((n & 15) == 15)
					printf("\n");
			}
			if ((n & 15) != 15)
				printf("\n");
			if (simple != 0)
				goto doneT;
			printf("--\n");
			printf("length = %zu\n", length_request4);
			printf("xid offset = %d\n", DHCP_OFF_XID);
			printf("xid length = 4\n");
			printf("random offset = %zu\n", random_request4);
			if (elapsed_request4 > 0)
				printf("secs offset = %zu\n",
				       elapsed_request4);
			printf("server-id offset = %zu\n", serverid_request4);
			printf("server-id length = %d\n", DHCP_OPTLEN_SRVID);
			printf("content:\n");
			printf("requested-ip-address offset = %zu\n",
			       reqaddr_request4);
			printf("requested-ip-address length = %d\n", 4);
			for (n = 0; n < length_request4; n++) {
				printf("%s%02hhx",
				       (n & 15) == 0 ? "" : " ",
				       template_request4[n]);
				if ((n & 15) == 15)
					printf("\n");
			}
			printf("\n");
		} else {
			printf("length = %zu\n", length_solicit6);
			printf("xid offset = %d\n", DHCP6_OFF_XID);
			printf("xid length = 3\n");
			printf("random offset = %zu\n", random_solicit6);
			for (n = 0; n < length_solicit6; n++) {
				printf("%s%02hhx",
				       (n & 15) == 0 ? "" : " ",
				       template_solicit6[n]);
				if ((n & 15) == 15)
					printf("\n");
			}
			if ((n & 15) != 15)
				printf("\n");
			if (simple != 0)
				goto doneT;
			printf("--\n");
			printf("length = %zu\n", length_request6);
			printf("xid offset = %d\n", DHCP_OFF_XID);
			printf("xid length = 4\n");
			printf("random offset = %zu\n", random_request6);
			if (elapsed_request6 > 0)
				printf("secs offset = %zu\n",
				       elapsed_request6);
			printf("server-id offset = %zu\n", serverid_request6);
			printf("content:\n");
			printf("requested-ip-address offset = %zu\n",
			       reqaddr_request6);
			for (n = 0; n < length_request6; n++) {
				printf("%s%02hhx",
				       (n & 15) == 0 ? "" : " ",
				       template_request6[n]);
				if ((n & 15) == 15)
					printf("\n");
			}
			printf("\n");
		}
	}
    doneT:

	/* compute the exit code (and exit) */
	if (fatal)
		exit(1);
	else if ((xscount0 == xrcount0) && (xscount2 == xrcount2))
		exit(0);
	else
		exit(3);
}
