// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __STATISTICS_ITEMS_H
#define __STATISTICS_ITEMS_H 1

/// This file defines a set of statistics items in Auth module for internal
/// use. This file is intended to be included in statistics.cc.

namespace {

// enum for socket statistics
enum SocketCounterType {
    // Socket statistics
    SOCKET_IPV4_UDP_BINDFAIL,        ///< IPv4 UDP sockets bind failures
    SOCKET_IPV4_UDP_CLOSE,           ///< IPv4 UDP sockets closed
    SOCKET_IPV4_UDP_CONN,            ///< IPv4 UDP connections established successfully
    SOCKET_IPV4_UDP_CONNFAIL,        ///< IPv4 UDP sockets connection failures
    SOCKET_IPV4_UDP_OPEN,            ///< IPv4 UDP sockets opened successfully
    SOCKET_IPV4_UDP_OPENFAIL,        ///< IPv4 UDP sockets open failures
    SOCKET_IPV4_UDP_RECVERR,         ///< IPv4 UDP sockets receive errors
    SOCKET_IPV4_UDP_SENDERR,         ///< IPv4 UDP sockets send errors
    SOCKET_IPV4_TCP_ACCEPT,          ///< IPv4 TCP incoming connections successfully accepted
    SOCKET_IPV4_TCP_ACCEPTFAIL,      ///< IPv4 TCP incoming accept failures
    SOCKET_IPV4_TCP_BINDFAIL,        ///< IPv4 TCP sockets bind failures
    SOCKET_IPV4_TCP_CLOSE,           ///< IPv4 TCP sockets closed
    SOCKET_IPV4_TCP_CONN,            ///< IPv4 TCP connections established successfully
    SOCKET_IPV4_TCP_CONNFAIL,        ///< IPv4 TCP sockets connection failures
    SOCKET_IPV4_TCP_OPEN,            ///< IPv4 TCP sockets opened successfully
    SOCKET_IPV4_TCP_OPENFAIL,        ///< IPv4 TCP sockets open failures
    SOCKET_IPV4_TCP_RECVERR,         ///< IPv4 TCP sockets receive errors
    SOCKET_IPV4_TCP_SENDERR,         ///< IPv4 TCP sockets send errors
    SOCKET_IPV6_UDP_BINDFAIL,        ///< IPv6 UDP sockets bind failures
    SOCKET_IPV6_UDP_CLOSE,           ///< IPv6 UDP sockets closed
    SOCKET_IPV6_UDP_CONN,            ///< IPv6 UDP connections established successfully
    SOCKET_IPV6_UDP_CONNFAIL,        ///< IPv6 UDP sockets connection failures
    SOCKET_IPV6_UDP_OPEN,            ///< IPv6 UDP sockets opened successfully
    SOCKET_IPV6_UDP_OPENFAIL,        ///< IPv6 UDP sockets open failures
    SOCKET_IPV6_UDP_RECVERR,         ///< IPv6 UDP sockets receive errors
    SOCKET_IPV6_UDP_SENDERR,         ///< IPv6 UDP sockets send errors
    SOCKET_IPV6_TCP_ACCEPT,          ///< IPv6 TCP incoming connections successfully accepted
    SOCKET_IPV6_TCP_ACCEPTFAIL,      ///< IPv6 TCP incoming accept failures
    SOCKET_IPV6_TCP_BINDFAIL,        ///< IPv6 TCP sockets bind failures
    SOCKET_IPV6_TCP_CLOSE,           ///< IPv6 TCP sockets closed
    SOCKET_IPV6_TCP_CONN,            ///< IPv6 TCP connections established successfully
    SOCKET_IPV6_TCP_CONNFAIL,        ///< IPv6 TCP sockets connection failures
    SOCKET_IPV6_TCP_OPEN,            ///< IPv6 TCP sockets opened successfully
    SOCKET_IPV6_TCP_OPENFAIL,        ///< IPv6 TCP sockets open failures
    SOCKET_IPV6_TCP_RECVERR,         ///< IPv6 TCP sockets receive errors
    SOCKET_IPV6_TCP_SENDERR,         ///< IPv6 TCP sockets send errors
    SOCKET_UNIXDOMAIN_ACCEPT,        ///< Unix Domain sockets incoming connections successfully accepted
    SOCKET_UNIXDOMAIN_ACCEPTFAIL,    ///< Unix Domain sockets incoming accept failures
    SOCKET_UNIXDOMAIN_BINDFAIL,      ///< Unix Domain sockets bind failures
    SOCKET_UNIXDOMAIN_CLOSE,         ///< Unix Domain sockets closed
    SOCKET_UNIXDOMAIN_CONN,          ///< Unix Domain connections established successfully
    SOCKET_UNIXDOMAIN_CONNFAIL,      ///< Unix Domain sockets connection failures
    SOCKET_UNIXDOMAIN_OPEN,          ///< Unix Domain sockets opened successfully
    SOCKET_UNIXDOMAIN_OPENFAIL,      ///< Unix Domain sockets open failures
    SOCKET_UNIXDOMAIN_RECVERR,       ///< Unix Domain sockets receive errors
    SOCKET_UNIXDOMAIN_SENDERR,       ///< Unix Domain sockets send errors
    SOCKET_COUNTER_TYPES             ///< The number of defined counters
};
// item names for socket statistics
const char* const SocketCounterItemName[SOCKET_COUNTER_TYPES] = {
    "ipv4.udp.bindfail",
    "ipv4.udp.close",
    "ipv4.udp.conn",
    "ipv4.udp.connfail",
    "ipv4.udp.open",
    "ipv4.udp.openfail",
    "ipv4.udp.recverr",
    "ipv4.udp.senderr",
    "ipv4.tcp.accept",
    "ipv4.tcp.acceptfail",
    "ipv4.tcp.bindfail",
    "ipv4.tcp.close",
    "ipv4.tcp.conn",
    "ipv4.tcp.connfail",
    "ipv4.tcp.open",
    "ipv4.tcp.openfail",
    "ipv4.tcp.recverr",
    "ipv4.tcp.senderr",
    "ipv6.udp.bindfail",
    "ipv6.udp.close",
    "ipv6.udp.conn",
    "ipv6.udp.connfail",
    "ipv6.udp.open",
    "ipv6.udp.openfail",
    "ipv6.udp.recverr",
    "ipv6.udp.senderr",
    "ipv6.tcp.accept",
    "ipv6.tcp.acceptfail",
    "ipv6.tcp.bindfail",
    "ipv6.tcp.close",
    "ipv6.tcp.conn",
    "ipv6.tcp.connfail",
    "ipv6.tcp.open",
    "ipv6.tcp.openfail",
    "ipv6.tcp.recverr",
    "ipv6.tcp.senderr",
    "unixdomain.accept",
    "unixdomain.acceptfail",
    "unixdomain.bindfail",
    "unixdomain.close",
    "unixdomain.conn",
    "unixdomain.connfail",
    "unixdomain.open",
    "unixdomain.openfail",
    "unixdomain.recverr",
    "unixdomain.senderr"
};

// enum for query/response counters
enum QRCounterType {
    // Request Attributes
    QR_REQUEST_IPV4,        ///< Number of IPv4 requests received
    QR_REQUEST_IPV6,        ///< Number of IPv6 requests received
    QR_REQUEST_EDNS0,       ///< Number of requests with EDNS(0) received
    QR_REQUEST_BADEDNSVER,  ///< Number of requests with unsupported EDNS version received
    QR_REQUEST_TSIG,        ///< Number of requests with TSIG received
    QR_REQUEST_SIG0,        ///< Number of requests with SIG(0) received; not implemented in BIND 10
    QR_REQUEST_BADSIG,      ///< Number of requests with invalid TSIG or SIG(0) signature received
    QR_REQUEST_UDP,         ///< Number of UDP requests received
    QR_REQUEST_TCP,         ///< Number of TCP requests received
    QR_REQUEST_DNSSEC_OK,   ///< Number of requests with DO bit
    // Request Opcodes
    QR_OPCODE_QUERY,        ///< Number of Opcode=QUERY requests received
    QR_OPCODE_IQUERY,       ///< Number of Opcode=IQUERY requests received
    QR_OPCODE_STATUS,       ///< Number of Opcode=STATUS requests received
    QR_OPCODE_NOTIFY,       ///< Number of Opcode=NOTIFY requests received
    QR_OPCODE_UPDATE,       ///< Number of Opcode=UPDATE requests received
    QR_OPCODE_OTHER,        ///< Number of requests in other OpCode received
    // Query Types
    QR_QTYPE_A,             ///< Number of QTYPE = A queries received
    QR_QTYPE_NS,            ///< Number of QTYPE = NS queries received
    QR_QTYPE_MD,            ///< Number of QTYPE = MD queries received
    QR_QTYPE_MF,            ///< Number of QTYPE = MF queries received
    QR_QTYPE_CNAME,         ///< Number of QTYPE = CNAME queries received
    QR_QTYPE_SOA,           ///< Number of QTYPE = SOA queries received
    QR_QTYPE_MB,            ///< Number of QTYPE = MB queries received
    QR_QTYPE_MG,            ///< Number of QTYPE = MG queries received
    QR_QTYPE_MR,            ///< Number of QTYPE = MR queries received
    QR_QTYPE_NULL,          ///< Number of QTYPE = NULL queries received
    QR_QTYPE_WKS,           ///< Number of QTYPE = WKS queries received
    QR_QTYPE_PTR,           ///< Number of QTYPE = PTR queries received
    QR_QTYPE_HINFO,         ///< Number of QTYPE = HINFO queries received
    QR_QTYPE_MINFO,         ///< Number of QTYPE = MINFO queries received
    QR_QTYPE_MX,            ///< Number of QTYPE = MX queries received
    QR_QTYPE_TXT,           ///< Number of QTYPE = TXT queries received
    QR_QTYPE_RP,            ///< Number of QTYPE = RP queries received
    QR_QTYPE_AFSDB,         ///< Number of QTYPE = AFSDB queries received
    QR_QTYPE_X25,           ///< Number of QTYPE = X25 queries received
    QR_QTYPE_ISDN,          ///< Number of QTYPE = ISDN queries received
    QR_QTYPE_RT,            ///< Number of QTYPE = RT queries received
    QR_QTYPE_NSAP,          ///< Number of QTYPE = NSAP queries received
    QR_QTYPE_NSAP_PTR,      ///< Number of QTYPE = NSAP-PTR queries received
    QR_QTYPE_SIG,           ///< Number of QTYPE = SIG queries received
    QR_QTYPE_KEY,           ///< Number of QTYPE = KEY queries received
    QR_QTYPE_PX,            ///< Number of QTYPE = PX queries received
    QR_QTYPE_GPOS,          ///< Number of QTYPE = GPOS queries received
    QR_QTYPE_AAAA,          ///< Number of QTYPE = AAAA queries received
    QR_QTYPE_LOC,           ///< Number of QTYPE = LOC queries received
    QR_QTYPE_NXT,           ///< Number of QTYPE = NXT queries received
    QR_QTYPE_EID,           ///< Number of QTYPE = EID queries received
    QR_QTYPE_NIMLOC,        ///< Number of QTYPE = NIMLOC queries received
    QR_QTYPE_SRV,           ///< Number of QTYPE = SRV queries received
    QR_QTYPE_ATMA,          ///< Number of QTYPE = ATMA queries received
    QR_QTYPE_NAPTR,         ///< Number of QTYPE = NAPTR queries received
    QR_QTYPE_KX,            ///< Number of QTYPE = KX queries received
    QR_QTYPE_CERT,          ///< Number of QTYPE = CERT queries received
    QR_QTYPE_A6,            ///< Number of QTYPE = A6 queries received
    QR_QTYPE_DNAME,         ///< Number of QTYPE = DNAME queries received
    QR_QTYPE_SINK,          ///< Number of QTYPE = SINK queries received
    QR_QTYPE_OPT,           ///< Number of QTYPE = OPT queries received
    QR_QTYPE_APL,           ///< Number of QTYPE = APL queries received
    QR_QTYPE_DS,            ///< Number of QTYPE = DS queries received
    QR_QTYPE_SSHFP,         ///< Number of QTYPE = SSHFP queries received
    QR_QTYPE_IPSECKEY,      ///< Number of QTYPE = IPSECKEY queries received
    QR_QTYPE_RRSIG,         ///< Number of QTYPE = RRSIG queries received
    QR_QTYPE_NSEC,          ///< Number of QTYPE = NSEC queries received
    QR_QTYPE_DNSKEY,        ///< Number of QTYPE = DNSKEY queries received
    QR_QTYPE_DHCID,         ///< Number of QTYPE = DHCID queries received
    QR_QTYPE_NSEC3,         ///< Number of QTYPE = NSEC3 queries received
    QR_QTYPE_NSEC3PARAM,    ///< Number of QTYPE = NSEC3PARAM queries received
    QR_QTYPE_HIP,           ///< Number of QTYPE = HIP queries received
    QR_QTYPE_NINFO,         ///< Number of QTYPE = NINFO queries received
    QR_QTYPE_RKEY,          ///< Number of QTYPE = RKEY queries received
    QR_QTYPE_TALINK,        ///< Number of QTYPE = TALINK queries received
    QR_QTYPE_SPF,           ///< Number of QTYPE = SPF queries received
    QR_QTYPE_UINFO,         ///< Number of QTYPE = UINFO queries received
    QR_QTYPE_UID,           ///< Number of QTYPE = UID queries received
    QR_QTYPE_GID,           ///< Number of QTYPE = GID queries received
    QR_QTYPE_UNSPEC,        ///< Number of QTYPE = UNSPEC queries received
    QR_QTYPE_TKEY,          ///< Number of QTYPE = TKEY queries received
    QR_QTYPE_TSIG,          ///< Number of QTYPE = TSIG queries received
    QR_QTYPE_IXFR,          ///< Number of QTYPE = IXFR queries received
    QR_QTYPE_AXFR,          ///< Number of QTYPE = AXFR queries received
    QR_QTYPE_MAILB,         ///< Number of QTYPE = MAILB queries received
    QR_QTYPE_MAILA,         ///< Number of QTYPE = MAILA queries received
    QR_QTYPE_URI,           ///< Number of QTYPE = URI queries received
    QR_QTYPE_CAA,           ///< Number of QTYPE = CAA queries received
    QR_QTYPE_TA,            ///< Number of QTYPE = TA queries received
    QR_QTYPE_DLV,           ///< Number of QTYPE = DLV queries received
    QR_QTYPE_OTHER,         ///< Number of queries in other QTYPE received
    // Respose Attributes
    QR_RESPONSE,            ///< Number of responses sent
    QR_RESPONSE_TRUNCATED,  ///< Number of truncated responses sent
    QR_RESPONSE_EDNS0,      ///< Number of responses with EDNS0; not implemented in BIND 10
    QR_RESPONSE_TSIG,       ///< Number of responses with TSIG
    QR_RESPONSE_SIG0,       ///< Number of responses with SIG(0); not implemented in BIND 10
    QR_QRYSUCCESS,          ///< Number of queries resulted in rcode = NOERROR and answer RR >= 1
    QR_QRYAUTHANS,          ///< Number of queries resulted in authoritative answer
    QR_QRYNOAUTHANS,        ///< Number of queries resulted in non-authoritative answer
    QR_QRYREFERRAL,         ///< Number of queries resulted in referral answer
    QR_QRYNXRRSET,          ///< Number of queries resulted in NOERROR but answer RR == 0
    QR_QRYREJECT,           ///< Number of queries rejected
    // Response Rcodes
    QR_RCODE_NOERROR,       ///< Number of queries resulted in RCODE = 0 (NoError)
    QR_RCODE_FORMERR,       ///< Number of queries resulted in RCODE = 1 (FormErr)
    QR_RCODE_SERVFAIL,      ///< Number of queries resulted in RCODE = 2 (ServFail)
    QR_RCODE_NXDOMAIN,      ///< Number of queries resulted in RCODE = 3 (NXDomain)
    QR_RCODE_NOTIMP,        ///< Number of queries resulted in RCODE = 4 (NotImp)
    QR_RCODE_REFUSED,       ///< Number of queries resulted in RCODE = 5 (Refused)
    QR_RCODE_YXDOMAIN,      ///< Number of queries resulted in RCODE = 6 (YXDomain)
    QR_RCODE_YXRRSET,       ///< Number of queries resulted in RCODE = 7 (YXRRSet)
    QR_RCODE_NXRRSET,       ///< Number of queries resulted in RCODE = 8 (NXRRSet)
    QR_RCODE_NOTAUTH,       ///< Number of queries resulted in RCODE = 9 (NotAuth)
    QR_RCODE_NOTZONE,       ///< Number of queries resulted in RCODE = 10 (NotZone)
    QR_RCODE_BADSIGVERS,    ///< Number of queries resulted in RCODE = 16 (BADVERS, BADSIG)
    QR_RCODE_BADKEY,        ///< Number of queries resulted in RCODE = 17 (BADKEY)
    QR_RCODE_BADTIME,       ///< Number of queries resulted in RCODE = 18 (BADTIME)
    QR_RCODE_BADMODE,       ///< Number of queries resulted in RCODE = 19 (BADMODE)
    QR_RCODE_BADNAME,       ///< Number of queries resulted in RCODE = 20 (BADNAME)
    QR_RCODE_BADALG,        ///< Number of queries resulted in RCODE = 21 (BADALG)
    QR_RCODE_BADTRUNC,      ///< Number of queries resulted in RCODE = 22 (BADTRUNC)
    QR_RCODE_OTHER,         ///< Number of queries resulted in other RCODEs
    // End of counter types
    QR_COUNTER_TYPES  ///< The number of defined counters
};
// item names for query/response counters
const char* const QRCounterItemName[QR_COUNTER_TYPES] = {
    "request.v4",
    "request.v6",
    "request.edns0",
    "request.badednsver",
    "request.tsig",
    "request.sig0",
    "request.badsig",
    "request.udp",
    "request.tcp",
    "request.dnssec_ok",
    "opcode.query",
    "opcode.iquery",
    "opcode.status",
    "opcode.notify",
    "opcode.update",
    "opcode.other",
    "qtype.a",
    "qtype.ns",
    "qtype.md",
    "qtype.mf",
    "qtype.cname",
    "qtype.soa",
    "qtype.mb",
    "qtype.mg",
    "qtype.mr",
    "qtype.null",
    "qtype.wks",
    "qtype.ptr",
    "qtype.hinfo",
    "qtype.minfo",
    "qtype.mx",
    "qtype.txt",
    "qtype.rp",
    "qtype.afsdb",
    "qtype.x25",
    "qtype.isdn",
    "qtype.rt",
    "qtype.nsap",
    "qtype.nsap-ptr",
    "qtype.sig",
    "qtype.key",
    "qtype.px",
    "qtype.gpos",
    "qtype.aaaa",
    "qtype.loc",
    "qtype.nxt",
    "qtype.eid",
    "qtype.nimloc",
    "qtype.srv",
    "qtype.atma",
    "qtype.naptr",
    "qtype.kx",
    "qtype.cert",
    "qtype.a6",
    "qtype.dname",
    "qtype.sink",
    "qtype.opt",
    "qtype.apl",
    "qtype.ds",
    "qtype.sshfp",
    "qtype.ipseckey",
    "qtype.rrsig",
    "qtype.nsec",
    "qtype.dnskey",
    "qtype.dhcid",
    "qtype.nsec3",
    "qtype.nsec3param",
    "qtype.hip",
    "qtype.ninfo",
    "qtype.rkey",
    "qtype.talink",
    "qtype.spf",
    "qtype.uinfo",
    "qtype.uid",
    "qtype.gid",
    "qtype.unspec",
    "qtype.tkey",
    "qtype.tsig",
    "qtype.ixfr",
    "qtype.axfr",
    "qtype.mailb",
    "qtype.maila",
    "qtype.uri",
    "qtype.caa",
    "qtype.ta",
    "qtype.dlv",
    "qtype.other",
    "response",
    "response.truncated",
    "response.edns0",
    "response.tsig",
    "response.sig0",
    "qrysuccess",
    "qryauthans",
    "qrynoauthans",
    "qryreferral",
    "qrynxrrset",
    "authqryrej",
    "rcode.noerror",
    "rcode.formerr",
    "rcode.servfail",
    "rcode.nxdomain",
    "rcode.notimp",
    "rcode.refused",
    "rcode.yxdomain",
    "rcode.yxrrset",
    "rcode.nxrrset",
    "rcode.notauth",
    "rcode.notzone",
    "rcode.badsigvers",
    "rcode.badkey",
    "rcode.badtime",
    "rcode.badmode",
    "rcode.badname",
    "rcode.badalg",
    "rcode.badtrunc",
    "rcode.other"
};

} // anonymous namespace

#endif // __STATISTICS_ITEMS_H

// Local Variables:
// mode: c++
// End:
