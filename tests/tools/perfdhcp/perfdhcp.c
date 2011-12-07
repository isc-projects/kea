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

/* DHCPv4 defines */

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

/* DHCPv6 defines */

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

/* tail queue macros */

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

/* exchanges */

struct exchange {				/* per exchange structure */
	ISC_TAILQ_ENTRY(exchange) gchain;	/* global chaining */
	ISC_TAILQ_ENTRY(exchange) hchain;	/* hash table chaining */
	uint64_t order;				/* number of this exchange */
	uint32_t xid;				/* transaction ID */
	uint32_t rnd;				/* random part */
	struct timespec ts0, ts1;		/* timespecs */
};
struct exchange *xnext;				/* next to be received */
ISC_TAILQ_HEAD(xlist, exchange);		/* exchange list */
struct xlist xsent, xrcvd;			/* sent and received lists */
uint64_t xscount, xrcount;			/* exchange counters */
caddr_t exchanges;				/* hash table */
uint32_t hashsize;				/* hash table size */
uint64_t tooshort, orphans, locallimit;		/* error counters */
double dmin = 999999999.;			/* minimum delay */
double dmax = 0.;				/* maximum delay */
double dsum = 0.;				/* delay sum */
double dsumsq = 0.;				/* square delay sum */

int ipversion = 0;			/* IP version */
int simple;				/* DO/SA in place of DORR/SARR */
int rate;				/* rate in exchange per second */
int report;				/* delay between two reports */
uint32_t range;				/* randomization range */
uint32_t maxrandom;			/* maximum random value */
int basecnt;				/* base count */
char *base[4];				/* bases */
int numreq;				/* number of exchange */
int period;				/* test period */
double losttime = 1.0;			/* time after a request is lost  */
int maxdrop;				/* maximum number of lost requests */
int maxpdrop;				/* maximum percentage */
char *localname;			/* local address or interface */
int isinterface;			/* interface vs local address */
int preload;				/* preload exchanges */
int aggressivity = 1;			/* back to back exchanges */
int seeded;				/* is a seed provided */
unsigned int seed;			/* randomization seed */
int isbroadcast;			/* use broadcast */
int rapidcommit;			/* add rapid commit option */
char *diags;				/* diagnostic selectors */
char *templatefile;			/* template file name */
int xidoffset = -1, rndoffset = -1;	/* template offsets */
char *servername;			/* server */

struct sockaddr_storage localaddr;
struct sockaddr_storage serveraddr;

int sock;
int interrupted, fatal;

uint8_t obuf[4096], ibuf[4096];
char tbuf[8200];

struct timespec boot, last, due, dreport, finished;

uint8_t mac_prefix[6] = { 0x00, 0x0c, 0x01, 0x02, 0x03, 0x04 };
uint8_t *duid_prefix;
int duid_length;

uint8_t dhcp_cookie[4] = { 0x63, 0x82, 0x53, 0x63 };
size_t length_discover4;
uint8_t template_discover4[4096];
size_t xid_discover4;
size_t random_discover4;
size_t length_solicit6;
uint8_t template_solicit6[4096];
size_t xid_solicit6;
size_t random_solicit6;

void
inits(void)
{
	struct xlist *bucket;
	caddr_t p;
	size_t len, i;

	ISC_TAILQ_INIT(&xsent);
	ISC_TAILQ_INIT(&xrcvd);

	/// compute hashsize
	hashsize = 1024;
	len = sizeof(*bucket) * hashsize;
	exchanges = malloc(len);
	if (exchanges == NULL) {
		perror("malloc(exchanges)");
		exit(1);
	}
	for (i = 0, p = exchanges; i < hashsize; i++, p += sizeof(*bucket)) {
		bucket = (struct xlist *) p;
		ISC_TAILQ_INIT(bucket);
	}
}

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

void
getsock4(void)
{
	int ret;

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

void
build_template_discover4(void)
{
	uint8_t *p = template_discover4;

	length_discover4 = BOOTP_MIN_LEN;
	xid_discover4 = DHCP_OFF_XID;
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
	random_discover4 = DHCP_OFF_CHADDR + 6;
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
	*p++ = DHCP_OPT_END;
}

void
get_template_discover4(void)
{
	uint8_t *p = template_discover4;
	int fd, cc, i, j;

	fd = open(templatefile, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile, strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile, strerror(errno));
		exit(1);
	}
	if (cc < 100) {
		fprintf(stderr, "file '%s' too short\n", templatefile);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile);
		exit(2);
	}
	if (tbuf[cc - 1] == '\n') {
		tbuf[cc - 1] = '\0';
		cc--;
	}
	j = 0;
	for (i = 0; i < cc; i++) {
		if (isspace((int) tbuf[i]))
			continue;
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile);
			exit(2);
		}
		tbuf[j] = tbuf[i];
		j++;
	}
	cc = j;
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile);
		exit(2);
	}
	length_discover4 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset >= 0)
		xid_discover4 = (size_t) xidoffset;
	else
		xid_discover4 = DHCP_OFF_XID;
	if (xid_discover4 + 4 > length_discover4) {
		fprintf(stderr,
			"xid (at %zu) outside the template (length %zu)?\n",
			xid_discover4, length_discover4);
		exit(2);
	}
	if (rndoffset >= 0)
		random_discover4 = (size_t) rndoffset;
	else
		random_discover4 = 0;
	if (random_discover4 > length_discover4) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_discover4, length_discover4);
		exit(2);
	}
}

int
send4(void)
{
	struct exchange *x;
	struct xlist *bucket;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL) {
		locallimit++;
		return -ENOMEM;
	}

	memset(x, 0, sizeof(*x));
	x->order = xscount++;
	hash = x->xid = (uint32_t) random();

	ISC_TAILQ_INSERT_TAIL(&xsent, x, gchain);
	hash &= hashsize - 1;
	bucket = (struct xlist *) (exchanges + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	memcpy(obuf, template_discover4, length_discover4);
	/* xid */
	memcpy(obuf + xid_discover4, &x->xid, 4);
	/* random */
	x->rnd = randomize(random_discover4, x->xid);
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

void
receive4(void)
{
	struct exchange *x, *t;
	struct xlist *bucket;
	struct timespec now;
	ssize_t cc;
	uint32_t xid, hash;
	int checklost;
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
	if (cc < BOOTP_MIN_LEN) {
		tooshort++;
		return;
	}
	if (ibuf[DHCP_OFF_OPCODE] != BOOTP_OP_REPLY)
		return;
	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		perror("clock_gettime(receive)");
		fatal = 1;
		return;
	}
	memcpy(&xid, ibuf + DHCP_OFF_XID, 4);
	hash = xid & (hashsize - 1);
	bucket = (struct xlist *) (exchanges + hash * sizeof(*bucket));
	if ((xnext != NULL) && (xnext->xid == xid)) {
		x = xnext;
		goto found;
	}
	if (rate != 0)
		checklost = 3;
	ISC_TAILQ_FOREACH_SAFE(x, bucket, hchain, t) {
		double waited;

		if (x->xid == xid)
			goto found;
		if (checklost <= 0)
			continue;
		waited = now.tv_sec - x->ts0.tv_sec;
		waited += (now.tv_nsec - x->ts0.tv_nsec) / 1e9;
		if (waited < losttime) {
			checklost = 0;
			continue;
		}
		checklost--;
		ISC_TAILQ_REMOVE(bucket, x, hchain);
		ISC_TAILQ_REMOVE(&xsent, x, gchain);
		free(x);
	}
	orphans++;
	return;

    found:
	xrcount++;
	x->ts1 = now;
	delta = x->ts1.tv_sec - x->ts0.tv_sec;
	delta += (x->ts1.tv_nsec - x->ts0.tv_nsec) / 1e9;
	if (delta < dmin)
		dmin = delta;
	if (delta > dmax)
		dmax = delta;
	dsum += delta;
	dsumsq += delta * delta;
	xnext = ISC_TAILQ_NEXT(x, gchain);
	ISC_TAILQ_REMOVE(bucket, x, hchain);
	ISC_TAILQ_REMOVE(&xsent, x, gchain);
	ISC_TAILQ_INSERT_TAIL(&xrcvd, x, gchain);
}

void
getsock6(void)
{
	struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) &serveraddr;
	int ret;

	sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
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

void
get_template_solicit6(void)
{
	uint8_t *p = template_solicit6;
	int fd, cc, i;

	fd = open(templatefile, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open(%s): %s\n",
			templatefile, strerror(errno));
		exit(2);
	}
	cc = read(fd, tbuf, sizeof(tbuf));
	(void) close(fd);
	if (cc < 0) {
		fprintf(stderr, "read(%s): %s\n",
			templatefile, strerror(errno));
		exit(1);
	}
	if (cc < 10) {
		fprintf(stderr, "file '%s' too short\n", templatefile);
		exit(2);
	}
	if (cc > 8193) {
		fprintf(stderr,"file '%s' too large\n", templatefile);
		exit(2);
	}
	if (tbuf[cc - 1] == '\n') {
		tbuf[cc - 1] = '\0';
		cc--;
	}
	if ((cc & 1) != 0) {
		fprintf(stderr,
			"odd number of hexadecimal digits in file '%s'\n",
			templatefile);
		exit(2);
	}
	for (i = 0; i < cc; i++)
		if (!isxdigit((int) tbuf[i])) {
			fprintf(stderr,
				"illegal char[%d]='%c' in file '%s'\n",
				i, (int) tbuf[i], templatefile);
			exit(2);
		}
	length_solicit6 = cc >> 1;
	for (i = 0; i < cc; i += 2)
		(void) sscanf(tbuf + i, "%02hhx", &p[i >> 1]);
	if (xidoffset >= 0)
		xid_solicit6 = (size_t) xidoffset;
	else
		xid_solicit6 = DHCP6_OFF_XID;
	if (xid_solicit6 + 3 > length_solicit6) {
		fprintf(stderr,
			"xid (at %zu) is outside the template (length %zu)?\n",
			xid_solicit6, length_solicit6);
		exit(2);
	}
	if (rndoffset >= 0)
		random_solicit6 = (size_t) rndoffset;
	else
		random_solicit6 = 0;
	if (random_solicit6 > length_solicit6) {
		fprintf(stderr,
			"random (at %zu) outside the template (length %zu)?\n",
			random_solicit6, length_solicit6);
		exit(2);
	}
}

int
send6(void)
{
	struct exchange *x;
	struct xlist *bucket;
	uint32_t hash;
	ssize_t ret;

	x = (struct exchange *) malloc(sizeof(*x));
	if (x == NULL) {
		locallimit++;
		return -ENOMEM;
	}

	memset(x, 0, sizeof(*x));
	x->order = xscount++;
	hash = x->xid = (uint32_t) random() & 0x00ffffff;

	ISC_TAILQ_INSERT_TAIL(&xsent, x, gchain);
	hash &= hashsize - 1;
	bucket = (struct xlist *) (exchanges + hash * sizeof(*bucket));
	ISC_TAILQ_INSERT_TAIL(bucket, x, hchain);

	memcpy(obuf, template_solicit6, length_solicit6);
	/* xid */
	obuf[xid_solicit6] = x->xid >> 16;
	obuf[xid_solicit6 + 1] = x->xid >> 8;
	obuf[xid_solicit6 + 2] = x->xid;
	/* random */
	x->rnd = randomize(random_solicit6, x->xid);

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

void
receive6(void)
{
	struct exchange *x, *t;
	struct xlist *bucket;
	struct timespec now;
	ssize_t cc;
	uint32_t xid, hash;
	int checklost;
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
	if (cc < 22) {
		tooshort++;
		return;
	}
	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		perror("clock_gettime(receive)");
		fatal = 1;
		return;
	}
	xid = ibuf[DHCP6_OFF_XID] << 16;
	xid |= ibuf[DHCP6_OFF_XID + 1] << 8;
	xid |= ibuf[DHCP6_OFF_XID + 2];
	hash = xid & (hashsize - 1);
	bucket = (struct xlist *) (exchanges + hash * sizeof(*bucket));
	if ((xnext != NULL) && (xnext->xid == xid)) {
		x = xnext;
		goto found;
	}
	if (rate != 0)
		checklost = 3;
	ISC_TAILQ_FOREACH_SAFE(x, bucket, hchain, t) {
		double waited;

		if (x->xid == xid)
			goto found;
		if (checklost <= 0)
			continue;
		waited = now.tv_sec - x->ts0.tv_sec;
		waited += (now.tv_nsec - x->ts0.tv_nsec) / 1e9;
		if (waited < losttime) {
			checklost = 0;
			continue;
		}
		checklost--;
		ISC_TAILQ_REMOVE(bucket, x, hchain);
		ISC_TAILQ_REMOVE(&xsent, x, gchain);
		free(x);
	}
	orphans++;
	return;

    found:
	xrcount++;
	x->ts1 = now;
	delta = x->ts1.tv_sec - x->ts0.tv_sec;
	delta += (x->ts1.tv_nsec - x->ts0.tv_nsec) / 1e9;
	if (delta < dmin)
		dmin = delta;
	if (delta > dmax)
		dmax = delta;
	dsum += delta;
	dsumsq += delta * delta;
	xnext = ISC_TAILQ_NEXT(x, gchain);
	ISC_TAILQ_REMOVE(bucket, x, hchain);
	ISC_TAILQ_REMOVE(&xsent, x, gchain);
	ISC_TAILQ_INSERT_TAIL(&xrcvd, x, gchain);
}

void
decodebase(void)
{
	char *b0 = base[basecnt];

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
	fprintf(stderr, "not yet supported base '%s'\n", b0);
	exit(2);
}
			   
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
		if (ipversion == 4)
			((struct sockaddr_in *) ss)->sin_port = htons(67);
		else
			((struct sockaddr_in6 *) ss)->sin6_port = htons(546);
		return;
	}
	fprintf(stderr, "can't find interface %s\n", name);
	exit(1);
}

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
	if (ipversion == 4)
		((struct sockaddr_in *) &localaddr)->sin_port = htons(67);
	else
		((struct sockaddr_in6 *) &localaddr)->sin6_port = htons(546);
}

void
reporting(void)
{
	dreport.tv_sec += report;

	printf("sent: %llu, received: %llu (drops: %lld)",
	       (unsigned long long) xscount - 1,
	       (unsigned long long) xrcount,
	       (long long) (xscount - xrcount - 1));
	if (!ISC_TAILQ_EMPTY(&xrcvd)) {
		double avg;

		avg = dsum / xrcount;
		printf(" average: %.3f ms", avg * 1e3);
	}
	printf("\n");
}

void
interrupt(int sig)
{
	sig = sig;
	interrupted = 1;
}

void
version(void)
{
	fprintf(stderr, "version 0.01\n");
}

void
usage(void)
{
	fprintf(stderr, "%s",
"perfdhcp [-hv] [-4|-6] [-r<rate>] [-t<report>] [-R<range>] [-b<base>]\n"
"    [-n<num-request>] [-p<test-period>] [-d<drop-time>] [-D<max-drop>]\n"
"    [-l<local-addr|interface>] [-P<preload>] [-a<aggressivity>]\n"
"    [-s<seed>] [-i] [-B] [-c] [-x<diagnostic-selector>]\n"
"    [-T<template-file>] [-X<xid-offset>] [-O<random-offset] [server]\n"
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
"-h: Print this help.\n"
"-i: Do only the initial part of an exchange: DO or SA, depending on\n"
"    whether -6 is given.\n"
"-l<local-addr|interface>: For DHCPv4 operation, specify the local\n"
"    hostname/address to use when communicating with the server.  By\n"
"    default, the interface address through which traffic would\n"
"    normally be routed to the server is used.\n"
"    For DHCPv6 operation, specify the name of the network interface\n"
"    via which exchanges are initiated.\n"
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
"-T<template-file>: The name of a file containing the template to use\n"
"    as a stream of hexadecimal digits.\n"
"-v: Report the version number of this program.\n"
"-x<diagnostic-selector>: Include extended diagnostics in the output.\n"
"    <diagnostic-selector> is a string of single-keywords specifying\n"
"    the operations for which verbose output is desired.  The selector\n"
"    keyletters are:\n"
"   * 'a': print the decoded command line arguments\n"
"   * 'e': print the exit reason\n"
"   * 'r': print randomization details\n"
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
"Exit status:\n"
"The exit status is:\n"
"0 on complete success.\n"
"1 for a general error.\n"
"2 if an error is found in the command line arguments.\n"
"3 if there are no general failures in operation, but one or more\n"
"  exchanges are not successfully completed.\n");
}

int
main(const int argc, char * const argv[])
{
	int opt, flags, ret, i;
	long long r;
	char *pc;
	extern char *optarg;
	extern int optind;

#define OPTIONS	"hv46r:t:R:b:n:p:d:D:l:P:a:s:iBcx:T:X:O:"

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
		numreq = atoi(optarg);
		if (numreq <= 0) {
			fprintf(stderr,
				"num-request must be a positive integer\n");
			usage();
			exit(2);
		}
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
		losttime = atof(optarg);
		if (losttime <= 0.) {
			fprintf(stderr,
				"drop-time must be a positive number\n");
			usage();
			exit(2);
		}
		break;

	case 'D':
		pc = strchr(optarg, '%');
		if (pc != NULL) {
			*pc = '\0';
			maxpdrop = atoi(optarg);
			if ((maxpdrop <= 0) || (maxpdrop >= 100)) {
				fprintf(stderr,
					"invalid drop-time percentage\n");
				usage();
				exit(2);
			}
			break;
		}
		maxdrop = atoi(optarg);
		if (maxdrop < 0) {
			fprintf(stderr,
				"max-drop must not be a negative integer\n");
			usage();
			exit(2);
		}
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

	case 'x':
		diags = optarg;
		break;

	case 'T':
		if (templatefile != NULL) {
			fprintf(stderr,
				"<template-file> was already set to '%s'\n",
				templatefile);
			usage();
			exit(2);
		}
		templatefile = optarg;
		break;

	case 'X':
		xidoffset = atoi(optarg);
		if (xidoffset <= 0) {
			fprintf(stderr,
				"xid-offset must be a positive integer\n");
			usage();
			exit(2);
		}
		break;

	case 'O':
		rndoffset = atoi(optarg);
		if (rndoffset < 3) {
			fprintf(stderr,
				"random-offset must be greater than 3\n");
			usage();
			exit(2);
		}
		break;

	default:
		usage();
		exit(2);
	}

	if (simple == 0) {
		fprintf(stderr,
			"only the simple mode is currently supported:"
			" please use -i\n");
		usage();
		exit(2);
	}

	if (ipversion == 0)
		ipversion = 4;

	if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
		printf("IPv%d", ipversion);
		if (simple) {
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
		if (numreq != 0)
			printf(" num-request=%d", numreq);
		if (period != 0)
			printf(" test-period=%d", period);
		printf(" drop-time=%g", losttime);
		if (maxdrop >= 0)
			printf(" max-drop=%d", maxdrop);
		if (maxpdrop != 0)
			printf(" max-drop=%d%%", maxpdrop);
		if (preload != 0)
			printf(" preload=%d", preload);
		printf(" aggressivity=%d", aggressivity);
		if (seeded)
			printf(" seed=%u", seed);
		if (isbroadcast != 0)
			printf(" broadcast");
		if (rapidcommit != 0)
			printf(" rapid-commit");
		printf(" diagnotic-selectors='%s'", diags);
		if (templatefile != NULL)
			printf(" template-file='%s'", templatefile);
		if (xidoffset >= 0)
			printf(" xid-offset=%d", xidoffset);
		if (rndoffset >= 0)
			printf(" random-offset=%d", rndoffset);
		printf("\n");
	}

	if ((ipversion != 4) && (isbroadcast != 0)) {
		fprintf(stderr, "-b is not compatible with IPv6 (-6)\n");
		usage();
		exit(2);
	}

	if ((ipversion != 6) && (rapidcommit != 0)) {
		fprintf(stderr, "-6 (IPv6) must be set to use -c\n");
		usage();
		exit(2);
	}

	if ((simple == 0) && (rapidcommit != 0)) {
		fprintf(stderr, "-i must be set to use -c\n");
		usage();
		exit(2);
	}

	if ((rate == 0) && (report != 0)) {
		fprintf(stderr,
			"-r<rate> must be set to use -t<report>\n");
		usage();
		exit(2);
	}
	if ((rate == 0) && (numreq != 0)) {
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
	if ((rate == 0) && ((maxdrop != 0) || (maxpdrop != 0))) {
		fprintf(stderr,
			"-r<rate> must be set to use -D<max-drop>\n");
		usage();
		exit(2);
	}

	if ((templatefile == NULL) && (xidoffset >= 0)) {
		fprintf(stderr,
			"-T<template-file> must be set to "
			"use -X<xid-offset>\n");
		usage();
		exit(2);
	}
	if ((templatefile == NULL) && (rndoffset >= 0)) {
		fprintf(stderr,
			"-T<template-file> must be set to "
			"use -O<random-offset>\n");
		usage();
		exit(2);
	}
	if ((templatefile != NULL) && (range > 0) && (rndoffset < 0)) {
		fprintf(stderr,
			"-o<random-offset> must be set when "
			"-T<template-file> and -R<range> are used\n");
		usage();
		exit(2);
	}

	if (optind < argc - 1) {
		fprintf(stderr, "extra arguments?\n");
		usage();
		exit(2);
	}
	if (optind == argc - 1) {
		servername = argv[optind];
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

	if (localname != NULL) {
		getlocaladdr();
		if ((diags != NULL) && (strchr(diags, 'a') != NULL)) {
			if (isinterface)
				printf("interface='%s'\n", localname);
			else
				printf("local-addr='%s'\n", localname);
		}
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
	getserveraddr(flags);
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

	inits();

	if (ipversion == 4) {
		getsock4();
		if (templatefile == NULL)
			build_template_discover4();
		else
			get_template_discover4();
	} else {
		getsock6();
		if (duid_prefix != NULL) {
			if (templatefile == NULL)
				build_template_solicit6();
			else
				get_template_solicit6();
		}
	}
	if ((unsigned) sock > FD_SETSIZE) {
		fprintf(stderr, "socket descriptor (%d) too large?!\n", sock);
		exit(1);
	}
	flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0) {
		perror("fcntl(F_GETFL)");
		exit(1);
	}
	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("fcntl(F_SETFL)");
		exit(1);
	}

	if (clock_gettime(CLOCK_REALTIME, &boot) < 0) {
		perror("clock_gettime(boot)");
		exit(1);
	}

	if (report != 0) {
		dreport.tv_sec = boot.tv_sec + report;
		dreport.tv_nsec = boot.tv_nsec;
	}

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
		if (templatefile == NULL)
			build_template_solicit6();
		else
			get_template_solicit6();
	}
		
	if (seeded == 0)
		seed = (unsigned int) (boot.tv_sec + boot.tv_nsec);
	srandom(seed);

	for (i = 0; i <= preload; i++) {
		if (ipversion == 4)
			ret = send4();
		else
			ret = send6();
		if (ret < 0) {
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

	(void) signal(SIGINT, interrupt);

	for (;;) {
		struct timespec now, ts;
		fd_set rfds;

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
		if (ts.tv_sec < 0)
			ts.tv_sec = ts.tv_nsec = 0;
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
		if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
			perror("clock_gettime(now2)");
			fatal = 1;
			continue;
		}
		if (ret == 1) {
			if (ipversion == 4)
				receive4();
			else
				receive6();
		}
		if (fatal)
			continue;
		if ((numreq != 0) && ((int) xscount >= numreq)) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached num-request\n");
			break;
		}
		if ((maxdrop != 0) && ((int) (xscount - xrcount) > maxdrop)) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop (absolute)\n");
			break;
		}
		if ((maxpdrop != 0) &&
		    (xscount > 10) &&
		    ((int) (100 * (xscount - xrcount) / xscount) > maxpdrop)) {
			if ((diags != NULL) && (strchr(diags, 'e') != NULL))
				printf("reached max-drop (percent)\n");
			break;
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
				if (recv(sock, ibuf, sizeof(ibuf),
					 MSG_PEEK) > 0) {
					if (ipversion == 4)
						receive4();
					else
						receive6();
				}
			}
		}
	}

	if (clock_gettime(CLOCK_REALTIME, &finished) < 0)
		perror("clock_gettime(finished)");

	printf("sent: %llu, received: %llu (drops: %lld)\n",
	       (unsigned long long) xscount,
	       (unsigned long long) xrcount,
	       (long long) (xscount - xrcount));
	printf("tooshort: %llu, orphans: %llu, local limits: %llu\n",
	       (unsigned long long) tooshort,
	       (unsigned long long) orphans,
	       (unsigned long long) locallimit);

	if (finished.tv_sec != 0) {
		double dall, erate;

		dall = (finished.tv_nsec - boot.tv_nsec) / 1e9;
		dall += finished.tv_sec - boot.tv_sec;
		erate = xrcount / dall;
		if (rate != 0)
			printf("rate: %f (expected %d)\n", erate, rate);
		else
			printf("rate: %f\n", erate);
	}

	if (!ISC_TAILQ_EMPTY(&xrcvd)) {
		double avg, stddev;
		
		avg = dsum / xrcount;
		stddev = sqrt(dsumsq / xrcount - avg * avg);
		printf("RTT: min/avg/max/stddef:  %.3f/%.3f/%.3f/%.3f ms\n",
		       dmin * 1e3, avg * 1e3, dmax * 1e3, stddev * 1e3);
	}

	if ((diags != NULL) && (strchr(diags, 't') != NULL) &&
	    !ISC_TAILQ_EMPTY(&xrcvd)) {
		struct exchange *x;

		printf("\n\n");
		ISC_TAILQ_FOREACH(x, &xrcvd, gchain)
			printf("%ld.%09ld %ld.%09ld\n",
			       (long) x->ts0.tv_sec, x->ts0.tv_nsec,
			       (long) x->ts1.tv_sec, x->ts1.tv_nsec);
	}

	if ((diags != NULL) && (strchr(diags, 'T') != NULL)) {
		size_t n;

		if (ipversion == 4) {
			printf("length = %zu\n", length_discover4);
			printf("xid offset = %d\n", DHCP_OFF_XID);
			printf("xid length = 4\n");
			printf("random offset = %zu\n", random_discover4);
			printf("content:\n");
			for (n = 0; n < length_discover4; n++)
				printf("%02hhu", template_discover4[n]);
			printf("\n");
		} else {
			printf("length = %zu\n", length_solicit6);
			printf("xid offset = %d\n", DHCP6_OFF_XID);
			printf("xid length = 3\n");
			printf("random offset = %zu\n", random_solicit6);
			for (n = 0; n < length_solicit6; n++)
				printf("%02hhu", template_solicit6[n]);
			printf("\n");
		}
	}

	if (fatal)
		exit(1);
	else if (xscount == xrcount)
		exit(0);
	else
		exit(3);
}
