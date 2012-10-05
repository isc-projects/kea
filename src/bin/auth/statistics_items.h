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

struct CounterTypeTree {
    const char* const name;
    const struct CounterTypeTree* const sub_tree;
    const int counter_id;
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
const struct CounterTypeTree QRCounterRequest[] = {
    { "v4",         NULL,   QR_REQUEST_IPV4       },
    { "v6",         NULL,   QR_REQUEST_IPV6       },
    { "edns0",      NULL,   QR_REQUEST_EDNS0      },
    { "badednsver", NULL,   QR_REQUEST_BADEDNSVER },
    { "tsig",       NULL,   QR_REQUEST_TSIG       },
    { "sig0",       NULL,   QR_REQUEST_SIG0       },
    { "badsig",     NULL,   QR_REQUEST_BADSIG     },
    { "udp",        NULL,   QR_REQUEST_UDP        },
    { "tcp",        NULL,   QR_REQUEST_TCP        },
    { "dnssec_ok",  NULL,   QR_REQUEST_DNSSEC_OK  },
    { NULL,         NULL,   -1                    }
};
const struct CounterTypeTree QRCounterOpcode[] = {
    { "query",  NULL,   QR_OPCODE_QUERY  },
    { "iquery", NULL,   QR_OPCODE_IQUERY },
    { "status", NULL,   QR_OPCODE_STATUS },
    { "notify", NULL,   QR_OPCODE_NOTIFY },
    { "update", NULL,   QR_OPCODE_UPDATE },
    { "other",  NULL,   QR_OPCODE_OTHER  },
    { NULL,     NULL,   -1               }
};
const struct CounterTypeTree QRCounterQtype[] = {
    { "a",          NULL,   QR_QTYPE_A,         },
    { "ns",         NULL,   QR_QTYPE_NS         },
    { "md",         NULL,   QR_QTYPE_MD         },
    { "mf",         NULL,   QR_QTYPE_MF         },
    { "cname",      NULL,   QR_QTYPE_CNAME      },
    { "soa",        NULL,   QR_QTYPE_SOA        },
    { "mb",         NULL,   QR_QTYPE_MB         },
    { "mg",         NULL,   QR_QTYPE_MG         },
    { "mr",         NULL,   QR_QTYPE_MR         },
    { "null",       NULL,   QR_QTYPE_NULL       },
    { "wks",        NULL,   QR_QTYPE_WKS        },
    { "ptr",        NULL,   QR_QTYPE_PTR        },
    { "hinfo",      NULL,   QR_QTYPE_HINFO      },
    { "minfo",      NULL,   QR_QTYPE_MINFO      },
    { "mx",         NULL,   QR_QTYPE_MX         },
    { "txt",        NULL,   QR_QTYPE_TXT        },
    { "rp",         NULL,   QR_QTYPE_RP         },
    { "afsdb",      NULL,   QR_QTYPE_AFSDB      },
    { "x25",        NULL,   QR_QTYPE_X25        },
    { "isdn",       NULL,   QR_QTYPE_ISDN       },
    { "rt",         NULL,   QR_QTYPE_RT         },
    { "nsap",       NULL,   QR_QTYPE_NSAP       },
    { "nsap-ptr",   NULL,   QR_QTYPE_NSAP_PTR   },
    { "sig",        NULL,   QR_QTYPE_SIG        },
    { "key",        NULL,   QR_QTYPE_KEY        },
    { "px",         NULL,   QR_QTYPE_PX         },
    { "gpos",       NULL,   QR_QTYPE_GPOS       },
    { "aaaa",       NULL,   QR_QTYPE_AAAA       },
    { "loc",        NULL,   QR_QTYPE_LOC        },
    { "nxt",        NULL,   QR_QTYPE_NXT        },
    { "eid",        NULL,   QR_QTYPE_EID        },
    { "nimloc",     NULL,   QR_QTYPE_NIMLOC     },
    { "srv",        NULL,   QR_QTYPE_SRV        },
    { "atma",       NULL,   QR_QTYPE_ATMA       },
    { "naptr",      NULL,   QR_QTYPE_NAPTR      },
    { "kx",         NULL,   QR_QTYPE_KX         },
    { "cert",       NULL,   QR_QTYPE_CERT       },
    { "a6",         NULL,   QR_QTYPE_A6         },
    { "dname",      NULL,   QR_QTYPE_DNAME      },
    { "sink",       NULL,   QR_QTYPE_SINK       },
    { "opt",        NULL,   QR_QTYPE_OPT        },
    { "apl",        NULL,   QR_QTYPE_APL        },
    { "ds",         NULL,   QR_QTYPE_DS         },
    { "sshfp",      NULL,   QR_QTYPE_SSHFP      },
    { "ipseckey",   NULL,   QR_QTYPE_IPSECKEY   },
    { "rrsig",      NULL,   QR_QTYPE_RRSIG      },
    { "nsec",       NULL,   QR_QTYPE_NSEC       },
    { "dnskey",     NULL,   QR_QTYPE_DNSKEY     },
    { "dhcid",      NULL,   QR_QTYPE_DHCID      },
    { "nsec3",      NULL,   QR_QTYPE_NSEC3      },
    { "nsec3param", NULL,   QR_QTYPE_NSEC3PARAM },
    { "hip",        NULL,   QR_QTYPE_HIP        },
    { "ninfo",      NULL,   QR_QTYPE_NINFO      },
    { "rkey",       NULL,   QR_QTYPE_RKEY       },
    { "talink",     NULL,   QR_QTYPE_TALINK     },
    { "spf",        NULL,   QR_QTYPE_SPF        },
    { "uinfo",      NULL,   QR_QTYPE_UINFO      },
    { "uid",        NULL,   QR_QTYPE_UID        },
    { "gid",        NULL,   QR_QTYPE_GID        },
    { "unspec",     NULL,   QR_QTYPE_UNSPEC     },
    { "tkey",       NULL,   QR_QTYPE_TKEY       },
    { "tsig",       NULL,   QR_QTYPE_TSIG       },
    { "ixfr",       NULL,   QR_QTYPE_IXFR       },
    { "axfr",       NULL,   QR_QTYPE_AXFR       },
    { "mailb",      NULL,   QR_QTYPE_MAILB      },
    { "maila",      NULL,   QR_QTYPE_MAILA      },
    { "uri",        NULL,   QR_QTYPE_URI        },
    { "caa",        NULL,   QR_QTYPE_CAA        },
    { "ta",         NULL,   QR_QTYPE_TA         },
    { "dlv",        NULL,   QR_QTYPE_DLV        },
    { "other",      NULL,   QR_QTYPE_OTHER      },
    { NULL,         NULL,   -1                  }
};
const struct CounterTypeTree QRCounterResponse[] = {
    { "truncated",  NULL,   QR_RESPONSE_TRUNCATED },
    { "edns0",      NULL,   QR_RESPONSE_EDNS0     },
    { "tsig",       NULL,   QR_RESPONSE_TSIG      },
    { "sig0",       NULL,   QR_RESPONSE_SIG0      },
    { NULL,         NULL,   -1                    }
};
const struct CounterTypeTree QRCounterRcode[] = {
    { "noerror",    NULL,   QR_RCODE_NOERROR    },
    { "formerr",    NULL,   QR_RCODE_FORMERR    },
    { "servfail",   NULL,   QR_RCODE_SERVFAIL   },
    { "nxdomain",   NULL,   QR_RCODE_NXDOMAIN   },
    { "notimp",     NULL,   QR_RCODE_NOTIMP     },
    { "refused",    NULL,   QR_RCODE_REFUSED    },
    { "yxdomain",   NULL,   QR_RCODE_YXDOMAIN   },
    { "yxrrset",    NULL,   QR_RCODE_YXRRSET    },
    { "nxrrset",    NULL,   QR_RCODE_NXRRSET    },
    { "notauth",    NULL,   QR_RCODE_NOTAUTH    },
    { "notzone",    NULL,   QR_RCODE_NOTZONE    },
    { "badsigvers", NULL,   QR_RCODE_BADSIGVERS },
    { "badkey",     NULL,   QR_RCODE_BADKEY     },
    { "badtime",    NULL,   QR_RCODE_BADTIME    },
    { "badmode",    NULL,   QR_RCODE_BADMODE    },
    { "badname",    NULL,   QR_RCODE_BADNAME    },
    { "badalg",     NULL,   QR_RCODE_BADALG     },
    { "badtrunc",   NULL,   QR_RCODE_BADTRUNC   },
    { "other",      NULL,   QR_RCODE_OTHER      },
    { NULL,         NULL,   -1 }
};
const struct CounterTypeTree QRCounterTree[] = {
    { "request",        QRCounterRequest,   -1              },
    { "opcode",         QRCounterOpcode,    -1              },
    { "qtype",          QRCounterQtype,     -1              },
    { "responses",      NULL,               QR_RESPONSE     },
    { "response",       QRCounterResponse,  -1              },
    { "qrysuccess",     NULL,               QR_QRYSUCCESS   },
    { "qryauthans",     NULL,               QR_QRYAUTHANS   },
    { "qrynoauthans",   NULL,               QR_QRYNOAUTHANS },
    { "qryreferral",    NULL,               QR_QRYREFERRAL  },
    { "qrynxrrset",     NULL,               QR_QRYNXRRSET   },
    { "authqryrej",     NULL,               QR_QRYREJECT    },
    { "rcode",          QRCounterRcode,     -1              },
    { NULL,             NULL,               -1              }
};

const int QROpCodeToQRCounterType[16] = {
    QR_OPCODE_QUERY,
    QR_OPCODE_IQUERY,
    QR_OPCODE_STATUS,
    QR_OPCODE_OTHER,
    QR_OPCODE_NOTIFY,
    QR_OPCODE_UPDATE,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER,
    QR_OPCODE_OTHER
};
const int QRQTypeToQRCounterType[258] = {
    QR_QTYPE_OTHER,
    QR_QTYPE_A,
    QR_QTYPE_NS,
    QR_QTYPE_MD,
    QR_QTYPE_MF,
    QR_QTYPE_CNAME,
    QR_QTYPE_SOA,
    QR_QTYPE_MB,
    QR_QTYPE_MG,
    QR_QTYPE_MR,
    QR_QTYPE_NULL,
    QR_QTYPE_WKS,
    QR_QTYPE_PTR,
    QR_QTYPE_HINFO,
    QR_QTYPE_MINFO,
    QR_QTYPE_MX,
    QR_QTYPE_TXT,
    QR_QTYPE_RP,
    QR_QTYPE_AFSDB,
    QR_QTYPE_X25,
    QR_QTYPE_ISDN,
    QR_QTYPE_RT,
    QR_QTYPE_NSAP,
    QR_QTYPE_NSAP_PTR,
    QR_QTYPE_SIG,
    QR_QTYPE_KEY,
    QR_QTYPE_PX,
    QR_QTYPE_GPOS,
    QR_QTYPE_AAAA,
    QR_QTYPE_LOC,
    QR_QTYPE_NXT,
    QR_QTYPE_EID,
    QR_QTYPE_NIMLOC,
    QR_QTYPE_SRV,
    QR_QTYPE_ATMA,
    QR_QTYPE_NAPTR,
    QR_QTYPE_KX,
    QR_QTYPE_CERT,
    QR_QTYPE_A6,
    QR_QTYPE_DNAME,
    QR_QTYPE_SINK,
    QR_QTYPE_OPT,
    QR_QTYPE_APL,
    QR_QTYPE_DS,
    QR_QTYPE_SSHFP,
    QR_QTYPE_IPSECKEY,
    QR_QTYPE_RRSIG,
    QR_QTYPE_NSEC,
    QR_QTYPE_DNSKEY,
    QR_QTYPE_DHCID,
    QR_QTYPE_NSEC3,
    QR_QTYPE_NSEC3PARAM,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_HIP,
    QR_QTYPE_NINFO,
    QR_QTYPE_RKEY,
    QR_QTYPE_TALINK,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_SPF,
    QR_QTYPE_UINFO,
    QR_QTYPE_UID,
    QR_QTYPE_GID,
    QR_QTYPE_UNSPEC,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_OTHER,
    QR_QTYPE_TKEY,
    QR_QTYPE_TSIG,
    QR_QTYPE_IXFR,
    QR_QTYPE_AXFR,
    QR_QTYPE_MAILB,
    QR_QTYPE_MAILA,
    QR_QTYPE_OTHER,
    QR_QTYPE_URI,
    QR_QTYPE_CAA
};
const int QRRCodeToQRCounterType[23] = {
    QR_RCODE_NOERROR,
    QR_RCODE_FORMERR,
    QR_RCODE_SERVFAIL,
    QR_RCODE_NXDOMAIN,
    QR_RCODE_NOTIMP,
    QR_RCODE_REFUSED,
    QR_RCODE_YXDOMAIN,
    QR_RCODE_YXRRSET,
    QR_RCODE_NXRRSET,
    QR_RCODE_NOTAUTH,
    QR_RCODE_NOTZONE,
    QR_RCODE_OTHER,
    QR_RCODE_OTHER,
    QR_RCODE_OTHER,
    QR_RCODE_OTHER,
    QR_RCODE_OTHER,
    QR_RCODE_BADSIGVERS,
    QR_RCODE_BADKEY,
    QR_RCODE_BADTIME,
    QR_RCODE_BADMODE,
    QR_RCODE_BADNAME,
    QR_RCODE_BADALG,
    QR_RCODE_BADTRUNC
};

} // anonymous namespace

#endif // __STATISTICS_ITEMS_H

// Local Variables:
// mode: c++
// End:
