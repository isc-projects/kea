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
    QR_OPCODE_QUERY,    // Opcode =  0: Query
    QR_OPCODE_IQUERY,   // Opcode =  1: Iquery
    QR_OPCODE_STATUS,   // Opcode =  2: STATUS
    QR_OPCODE_OTHER,    // Opcode =  3: (Unassigned)
    QR_OPCODE_NOTIFY,   // Opcode =  4: Notify
    QR_OPCODE_UPDATE,   // Opcode =  5: Update
    QR_OPCODE_OTHER,    // Opcode =  6: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode =  7: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode =  8: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode =  9: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode = 10: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode = 11: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode = 12: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode = 13: (Unassigned)
    QR_OPCODE_OTHER,    // Opcode = 14: (Unassigned)
    QR_OPCODE_OTHER     // Opcode = 15: (Unassigned)
};
const int QRQTypeToQRCounterType[258] = {
    QR_QTYPE_OTHER,         // RRtype =   0: special use
    QR_QTYPE_A,             // RRtype =   1: A
    QR_QTYPE_NS,            // RRtype =   2: NS
    QR_QTYPE_MD,            // RRtype =   3: MD
    QR_QTYPE_MF,            // RRtype =   4: MF
    QR_QTYPE_CNAME,         // RRtype =   5: CNAME
    QR_QTYPE_SOA,           // RRtype =   6: SOA
    QR_QTYPE_MB,            // RRtype =   7: MB
    QR_QTYPE_MG,            // RRtype =   8: MG
    QR_QTYPE_MR,            // RRtype =   9: MR
    QR_QTYPE_NULL,          // RRtype =  10: NULL
    QR_QTYPE_WKS,           // RRtype =  11: WKS
    QR_QTYPE_PTR,           // RRtype =  12: PTR
    QR_QTYPE_HINFO,         // RRtype =  13: HINFO
    QR_QTYPE_MINFO,         // RRtype =  14: MINFO
    QR_QTYPE_MX,            // RRtype =  15: MX
    QR_QTYPE_TXT,           // RRtype =  16: TXT
    QR_QTYPE_RP,            // RRtype =  17: RP
    QR_QTYPE_AFSDB,         // RRtype =  18: AFSDB
    QR_QTYPE_X25,           // RRtype =  19: X25
    QR_QTYPE_ISDN,          // RRtype =  20: ISDN
    QR_QTYPE_RT,            // RRtype =  21: RT
    QR_QTYPE_NSAP,          // RRtype =  22: NSAP
    QR_QTYPE_NSAP_PTR,      // RRtype =  23: NSAP-PTR
    QR_QTYPE_SIG,           // RRtype =  24: SIG
    QR_QTYPE_KEY,           // RRtype =  25: KEY
    QR_QTYPE_PX,            // RRtype =  26: PX
    QR_QTYPE_GPOS,          // RRtype =  27: GPOS
    QR_QTYPE_AAAA,          // RRtype =  28: AAAA
    QR_QTYPE_LOC,           // RRtype =  29: LOC
    QR_QTYPE_NXT,           // RRtype =  30: NXT
    QR_QTYPE_EID,           // RRtype =  31: EID        
    QR_QTYPE_NIMLOC,        // RRtype =  32: NIMLOC     
    QR_QTYPE_SRV,           // RRtype =  33: SRV        
    QR_QTYPE_ATMA,          // RRtype =  34: ATMA       
    QR_QTYPE_NAPTR,         // RRtype =  35: NAPTR      
    QR_QTYPE_KX,            // RRtype =  36: KX         
    QR_QTYPE_CERT,          // RRtype =  37: CERT       
    QR_QTYPE_A6,            // RRtype =  38: A6         
    QR_QTYPE_DNAME,         // RRtype =  39: DNAME      
    QR_QTYPE_SINK,          // RRtype =  40: SINK       
    QR_QTYPE_OPT,           // RRtype =  41: OPT        
    QR_QTYPE_APL,           // RRtype =  42: APL        
    QR_QTYPE_DS,            // RRtype =  43: DS         
    QR_QTYPE_SSHFP,         // RRtype =  44: SSHFP      
    QR_QTYPE_IPSECKEY,      // RRtype =  45: IPSECKEY   
    QR_QTYPE_RRSIG,         // RRtype =  46: RRSIG      
    QR_QTYPE_NSEC,          // RRtype =  47: NSEC       
    QR_QTYPE_DNSKEY,        // RRtype =  48: DNSKEY     
    QR_QTYPE_DHCID,         // RRtype =  49: DHCID      
    QR_QTYPE_NSEC3,         // RRtype =  50: NSEC3      
    QR_QTYPE_NSEC3PARAM,    // RRtype =  51: NSEC3PARAM 
    QR_QTYPE_OTHER,         // RRtype =  52: TLSA
    QR_QTYPE_OTHER,         // RRtype =  53: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  54: (Unassigned)
    QR_QTYPE_HIP,           // RRtype =  55: HIP
    QR_QTYPE_NINFO,         // RRtype =  56: NINFO
    QR_QTYPE_RKEY,          // RRtype =  57: RKEY
    QR_QTYPE_TALINK,        // RRtype =  58: TALINK
    QR_QTYPE_OTHER,         // RRtype =  59: CDS
    QR_QTYPE_OTHER,         // RRtype =  60: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  61: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  62: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  63: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  64: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  65: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  66: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  67: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  68: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  69: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  70: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  71: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  72: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  73: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  74: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  75: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  76: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  77: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  78: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  79: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  80: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  81: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  82: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  83: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  84: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  85: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  86: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  87: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  88: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  89: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  90: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  91: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  92: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  93: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  94: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  95: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  96: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  97: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype =  98: (Unassigned)
    QR_QTYPE_SPF,           // RRtype =  99: SPF
    QR_QTYPE_UINFO,         // RRtype = 100: UINFO
    QR_QTYPE_UID,           // RRtype = 101: UID
    QR_QTYPE_GID,           // RRtype = 102: GID
    QR_QTYPE_UNSPEC,        // RRtype = 103: UNSPEC
    QR_QTYPE_OTHER,         // RRtype = 104: NID
    QR_QTYPE_OTHER,         // RRtype = 105: L32
    QR_QTYPE_OTHER,         // RRtype = 106: L64
    QR_QTYPE_OTHER,         // RRtype = 107: LP 
    QR_QTYPE_OTHER,         // RRtype = 108: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 109: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 110: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 111: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 112: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 113: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 114: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 115: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 116: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 117: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 118: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 119: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 120: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 121: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 122: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 123: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 124: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 125: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 126: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 127: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 128: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 129: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 130: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 131: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 132: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 133: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 134: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 135: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 136: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 137: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 138: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 139: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 140: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 141: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 142: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 143: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 144: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 145: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 146: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 147: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 148: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 149: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 150: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 151: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 152: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 153: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 154: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 155: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 156: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 157: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 158: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 159: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 160: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 161: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 162: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 163: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 164: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 165: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 166: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 167: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 168: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 169: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 170: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 171: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 172: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 173: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 174: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 175: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 176: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 177: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 178: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 179: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 180: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 181: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 182: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 183: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 184: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 185: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 186: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 187: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 188: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 189: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 190: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 191: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 192: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 193: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 194: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 195: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 196: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 197: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 198: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 199: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 200: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 201: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 202: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 203: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 204: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 205: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 206: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 207: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 208: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 209: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 210: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 211: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 212: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 213: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 214: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 215: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 216: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 217: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 218: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 219: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 220: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 221: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 222: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 223: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 224: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 225: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 226: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 227: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 228: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 229: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 230: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 231: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 232: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 233: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 234: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 235: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 236: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 237: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 238: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 239: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 240: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 241: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 242: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 243: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 244: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 245: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 246: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 247: (Unassigned)
    QR_QTYPE_OTHER,         // RRtype = 248: (Unassigned)
    QR_QTYPE_TKEY,          // RRtype = 249: TKEY
    QR_QTYPE_TSIG,          // RRtype = 250: TSIG
    QR_QTYPE_IXFR,          // RRtype = 251: IXFR
    QR_QTYPE_AXFR,          // RRtype = 252: AXFR
    QR_QTYPE_MAILB,         // RRtype = 253: MAILB
    QR_QTYPE_MAILA,         // RRtype = 254: MAILA
    QR_QTYPE_OTHER,         // RRtype = 255: for All records
    QR_QTYPE_URI,           // RRtype = 256: URI
    QR_QTYPE_CAA            // RRtype = 257: CAA
};
const int QRRCodeToQRCounterType[23] = {
    QR_RCODE_NOERROR,       // Rcode =  0: NoError
    QR_RCODE_FORMERR,       // Rcode =  1: FormErr
    QR_RCODE_SERVFAIL,      // Rcode =  2: ServFail
    QR_RCODE_NXDOMAIN,      // Rcode =  3: NXDomain
    QR_RCODE_NOTIMP,        // Rcode =  4: NotImp
    QR_RCODE_REFUSED,       // Rcode =  5: Refused
    QR_RCODE_YXDOMAIN,      // Rcode =  6: YXDomain
    QR_RCODE_YXRRSET,       // Rcode =  7: YXRRSet
    QR_RCODE_NXRRSET,       // Rcode =  8: NXRRSet
    QR_RCODE_NOTAUTH,       // Rcode =  9: NotAuth
    QR_RCODE_NOTZONE,       // Rcode = 10: NotZone
    QR_RCODE_OTHER,         // Rcode = 11: (Unassigned)
    QR_RCODE_OTHER,         // Rcode = 12: (Unassigned)
    QR_RCODE_OTHER,         // Rcode = 13: (Unassigned)
    QR_RCODE_OTHER,         // Rcode = 14: (Unassigned)
    QR_RCODE_OTHER,         // Rcode = 15: (Unassigned)
    QR_RCODE_BADSIGVERS,    // Rcode = 16: BADVERS, BADSIG
    QR_RCODE_BADKEY,        // Rcode = 17: BADKEY
    QR_RCODE_BADTIME,       // Rcode = 18: BADTIME
    QR_RCODE_BADMODE,       // Rcode = 19: BADMODE
    QR_RCODE_BADNAME,       // Rcode = 20: BADNAME
    QR_RCODE_BADALG,        // Rcode = 21: BADALG
    QR_RCODE_BADTRUNC       // Rcode = 22: BADTRUNC
};

} // anonymous namespace

#endif // __STATISTICS_ITEMS_H

// Local Variables:
// mode: c++
// End:
