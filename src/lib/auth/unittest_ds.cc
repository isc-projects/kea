// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <cassert>

#include "unittest_util.h"
#include "unittest_ds.h"
#include "data_source.h"

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <iostream>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

namespace {
const Name example("example.com");
const Name sql1("sql1.example.com");
const Name www_sql1("www.sql1.example.com");
const Name www("www.example.com");
const Name foo("foo.example.com");
const Name dns01("dns01.example.com");
const Name dns02("dns02.example.com");
const Name dns03("dns03.example.com");
const Name cnameint("cname-int.example.com");
const Name cnameext("cname-ext.example.com");
const Name dname("dname.example.com");
const Name wild("*.wild.example.com");
const Name subzone("subzone.example.com");
const Name loop1("loop1.example.com");
const Name loop2("loop2.example.com");

RRsetPtr example_ns;
RRsetPtr example_soa;
RRsetPtr example_nsec;
RRsetPtr www_a;
RRsetPtr www_nsec;
RRsetPtr foo_cname;
RRsetPtr foo_nsec;
RRsetPtr cnameint_cname;
RRsetPtr cnameint_nsec;
RRsetPtr cnameext_cname;
RRsetPtr cnameext_nsec;
RRsetPtr dns01_a;
RRsetPtr dns01_nsec;
RRsetPtr dns02_a;
RRsetPtr dns02_nsec;
RRsetPtr dns03_a;
RRsetPtr dns03_nsec;
RRsetPtr wild_a;
RRsetPtr wild_nsec;
RRsetPtr dname_dname;
RRsetPtr dname_nsec;
RRsetPtr sql1_ns;
RRsetPtr sql1_soa;
RRsetPtr sql1_nsec;
RRsetPtr sql1_ds;
RRsetPtr sql1_ds_nsec;
RRsetPtr www_sql1_a;
RRsetPtr www_sql1_nsec;
RRsetPtr subzone_ns;
RRsetPtr subzone_nsec;
RRsetPtr subzone_glue1;
RRsetPtr subzone_glue2;
RRsetPtr subzone_ds;
RRsetPtr loop1_cname;
RRsetPtr loop2_cname;
}

TestDataSrc::TestDataSrc() {
    RRset* rp;
    RRsetPtr rrsig;

    // example.com
    example_ns = RRsetPtr(new RRset(example, RRClass::IN(),
                                    RRType::NS(), RRTTL(3600)));
    example_ns->addRdata(generic::NS(dns01));
    example_ns->addRdata(generic::NS(dns02));
    example_ns->addRdata(generic::NS(dns03));

    rp = new RRset(example, RRClass::IN(), RRType::RRSIG(), RRTTL(3600));
    rrsig = RRsetPtr(rp);
    rrsig->addRdata(generic::RRSIG("NS 5 2 3600 20100322084538 20100220084538 33495 example.com. ClcrfjkQZUY5L6ZlCkU3cJHzcrEGrofKSVeeoeZ+w6yeEowFNVXs2YBo3tom53DiCrdD9rs3feVSLGW5rjsz/O6lDuomgQG+EVSnWa7GTIPBXj1BmDXXp3XxeldYmhf4UzaN5BA+RUA5E8NChNKuNNof76j2S9tilfN/kvpy4fw="));
    example_ns->addRRsig(rrsig);

    example_soa = RRsetPtr(new RRset(example, RRClass::IN(),
                                    RRType::SOA(), RRTTL(3600)));
    example_soa->addRdata(generic::SOA("master.example.com. admin.example.com. 1234 3600 1800 2419200 7200"));

    rrsig = RRsetPtr(new RRset(example, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("SOA 5 2 3600 20100322084538 20100220084538 33495 example.com.  KUun66Qaw36osk2BJS6U1fAy3PPDkNo2QK4meGNbDBY8q8b+f2o+IXJ14YCvssGl1ORW0CcLnDRxssnk8V/Svmj5iFhO+8HC2hnVBdi2zewvdVtwRb+lWwKN7pkXXwuy6g1t9WCd/j5FCc/wgxqtZUTPb6XgZcnHrORDMOTqLs4="));
    example_soa->addRRsig(rrsig);

    example_nsec = RRsetPtr(new RRset(example, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    example_nsec->addRdata(generic::NSEC("cname-ext.example.com. NS SOA MX RRSIG NSEC DNSKEY"));
    rrsig = RRsetPtr(new RRset(example, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 2 7200 20100322084538 20100220084538 33495 example.com. KxuVaPPKNPJzr/q+cJPiNlkHVTQK0LVsgTbSqruXQc25lAd0wn5oKUtxL1bEAchHkfA8eLzcYCj2ZqqAv9OJubw53mfskTad7UHs4Uj2RTrIsNGMCiZGgOpvNb9JcWpQtoyXVT1uNse+Qsbeir0eyeYIufUynFU041jtNrlJMio="));
    example_nsec->addRRsig(rrsig);

    // sql1.example.com
    sql1_ns = RRsetPtr(new RRset(sql1, RRClass::IN(),
                                 RRType::NS(), RRTTL(3600)));
    sql1_ns->addRdata(generic::NS(dns01));
    sql1_ns->addRdata(generic::NS(dns02));
    sql1_ns->addRdata(generic::NS(dns03));

    rrsig = RRsetPtr(new RRset(sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NS 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. 0CL8noy0NSgoWwuKd+Dc6vyIIw2BrAEBx0IJzcSB6GlB25x/zjEd6AJG0be13HN6jOaTX8iWTuCVrEYuXg76V+M4EvTZHjEScj0az74TrDv4Vdo459paGKCX9B8NLJW1mW4fzZrrXQ8jmBEZeS91Q5rJrO+UKJEuUz3LYdTPvao="));
    sql1_ns->addRRsig(rrsig);

    sql1_soa = RRsetPtr(new RRset(sql1, RRClass::IN(),
                                 RRType::SOA(), RRTTL(3600)));
    sql1_soa->addRdata(generic::SOA("master.example.com. admin.example.com. 678 3600 1800 2419200 7200"));

    rrsig = RRsetPtr(new RRset(sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("SOA 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. oakulfyljL/RAKgCKXEZ3KsG8BJj5WG4JK4moWFB6c9OKem6jIk8hKP2XlUVXFuOYJlRdIM4KicmR2GAK+5jJp6z5ShssstYTXo3QosVm6oCKumuFeLFHzcjfqP1D+F9NsvHldJIBnS/4ebPkmR5OENyCZXQF5HmN2awIj4CLjE="));
    sql1_soa->addRRsig(rrsig);

    sql1_nsec = RRsetPtr(new RRset(sql1, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    sql1_nsec->addRdata(generic::NSEC("www.sql1.example.com. NS SOA RRSIG NSEC DNSKEY"));
    rrsig = RRsetPtr(new RRset(sql1, RRClass::IN(), RRType::RRSIG(), RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084536 20100220084536 12447 sql1.example.com. v71CgdTYccCiTqfRcn6HsvISQa8ruvUfCKtpwym0RW/G27xlZn8otj2IMtWwkLxti8Rqqu+PTViLaOIbeVfHBcqzAd7U59cAOYoq3ODZx6auiE3C23HAKqUavKcP7Esaajm1cbcWy6Kyie4CAZc8M7EeKxgkXMKJGqBQzF+/FOo="));
    sql1_nsec->addRRsig(rrsig);
    sql1_ds = RRsetPtr(new RRset(sql1, RRClass::IN(),
                                 RRType::DS(), RRTTL(3600)));
    sql1_ds->addRdata(generic::DS("33313 5 1 0FDD7A2C11AA7F55D50FBF9B7EDDA2322C541A8D"));
    sql1_ds->addRdata(generic::DS("33313 5 2 00B99B7006F496D135B01AB17EDB469B4BE9E1973884DEA757BC4E3015A8C3AB"));

    rrsig = RRsetPtr(new RRset(sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("DS 5 3 3600 20100322084538 20100220084538 33495 example.com. dIqZKvpkJN1l92SOiWgJh3KbjErIN+EfojMsm4pEdV5xQdZwj6DNNEu6Kw4rRwdvrZIu0TyqPr3jSJb7o6R7vZgZzmLfVV/ojQah7rwuYHCFcfyZ4JyK2311fMhRR1QAvMsdcjdyA1XC140Cm6AnL3cH5rh/KUks/0ec3Ca7GNQ="));
    sql1_ds->addRRsig(rrsig);


    sql1_ds_nsec = RRsetPtr(new RRset(sql1, RRClass::IN(),
                                   RRType::NSEC(), RRTTL(3600)));
    sql1_ds_nsec->addRdata(generic::NSEC("subzone.example.com. NS DS RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. k9FRdFyk/cPdkmmaoZbGZPpzIzfbFWQ3QCHd2qhJa0xAXaEOT/GBL6aFqx9SlunDu2wgES+To5fWPZGi4NzWpp6c5t27rnATN/oCEQ/UYIJKmWbqrXdst0Ps5boznk7suK2Y+km31KxaIf3fDd/T3kZCVsR0aWKRRRatPb7GfLw="));
    sql1_ds_nsec->addRRsig(rrsig);

    // www.sql1.example.com
    www_sql1_a = RRsetPtr(new RRset(www_sql1,
                                    RRClass::IN(), RRType::A(),
                                    RRTTL(3600)));
    www_sql1_a->addRdata(in::A("192.168.2.2"));

    rrsig = RRsetPtr(new RRset(www_sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 4 3600 20100322084536 20100220084536 12447 sql1.example.com. DNdVKxB3oBsB14NPoV9WG14Y/g4zMcIXLYnFjj9vRZRZJpAvbTEipiXlayuhOxnqU827OipETQyeULZmLsqIQ1wK4Fgf+9b5aJ8D85/o4wBka00X4hZ3MwDPRb4mjuogwBTBg5NRpNSzUfbkPGiav08BFwgg+Efm9veSB05arS0="));
    www_sql1_a->addRRsig(rrsig);

    www_sql1_nsec = RRsetPtr(new RRset(www_sql1,
                                       RRClass::IN(), RRType::NSEC(),
                                       RRTTL(3600)));
    www_sql1_nsec->addRdata(generic::NSEC("sql1.example.com. A RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(www_sql1, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 4 7200 20100322084536 20100220084536 12447 sql1.example.com. cJMJhDx/ND7/9j3zhyXe+6eaSsU7ByYpXhJzbe+OhjFgH0VasQXq7o1QB3I293UZ+yhkjgXap+9QtPlraaNaYyTyOMQ42OoxSefJpYz9CME/FI2tsUfyrCnLFxYRNet7sMS0q+hLqxRayuEHDFDp72hHPGLJQ8a7jq4SrIonT50="));
    www_sql1_nsec->addRRsig(rrsig);

    // dns01.example.com
    dns01_a = RRsetPtr(new RRset(dns01,
                                         RRClass::IN(), RRType::A(),
                                         RRTTL(3600)));
    dns01_a->addRdata(in::A("192.168.2.1"));

    rrsig = RRsetPtr(new RRset(dns01, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20100322084538 20100220084538 33495 example.com. NIawlZLk8WZAjNux7oQM2mslfW52OZFFkWt++7FHu2SU98XqEeKfCMnpgtWe5T8Nr9cS8df901iEOJoWQzGTEaHYUBtEhsSjBVn7mKp3fz6473a2xxy75SUKZ0rxjNXSZ8Q5rnFmkX0HTH2Sg51mtjH6aC2pfheQnA2t193BnSg="));
    dns01_a->addRRsig(rrsig);

    dns01_nsec = RRsetPtr(new RRset(dns01, RRClass::IN(), RRType::NSEC(), RRTTL(3600)));
    dns01_nsec->addRdata(generic::NSEC("dns02.example.com. A RRSIG NSEC"));

    rrsig = RRsetPtr(new RRset(dns01, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. EkyeshmMNP9xiAz6mDFDIwksTdmkF9zsFzLuVKAgK6eUk7St6tp5PSvjA8nWol0vdvvz4LK85a4ffTFEiNRyvWeYP2vOhEkyDcrwuCd8Vc3jh/8Sm1Js+nX7hJStrZGFvp2TWPpt9nKH5p3MxXvTb/YVurnue0xSeFAE17O3+I0="));
    dns01_nsec->addRRsig(rrsig);

    // dns02.example.com
    dns02_a = RRsetPtr(new RRset(dns02, RRClass::IN(), RRType::A(), RRTTL(3600)));
    dns02_a->addRdata(in::A("192.168.2.2"));

    rrsig = RRsetPtr(new RRset(dns02, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20100322084538 20100220084538 33495 example.com. XJtVMbUIRE0mk6Hn/Nx6k36jaxaBDPK2/IYB6vCQjJETz6gW4T6q/H/eY9/Lsw5iYPFhoBRDxT4XFj575t98kELXnJe1WhuMbRPlOhyOjxkLECaUne/sbFPOtbGFx9ohuojI0RgxxZiCFaO8wJuv6nfPuzmlLajWS6z9NZeOMIk="));
    dns02_a->addRRsig(rrsig);

    dns02_nsec = RRsetPtr(new RRset(dns02, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    dns02_nsec->addRdata(generic::NSEC("dns03.example.com. A RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(dns02, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));

    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. imBNTMB3sPU4kblcaAH6V7lCVt5xgtAybi3DA/SbLEulLaV2NE6vcoEn/AieaM4mOJicQnUDj/H+1hSEhzxU2tRM8zfVlvztxQWn6eh7ZR4mKfNDSvRUGU9ykhpwMyC7wjOt1j5bcSA/OTnLRAilslnJyOM4bSaxVEFo8YPjncY="));
    dns02_nsec->addRRsig(rrsig);

    // dns03.example.com
    dns03_a = RRsetPtr(new RRset(dns03,
                                         RRClass::IN(), RRType::A(),
                                         RRTTL(3600)));
    dns03_a->addRdata(in::A("192.168.2.3"));

    rrsig = RRsetPtr(new RRset(dns03, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20100322084538 20100220084538 33495 example.com. Ubrcm1H+F6m8khle7P9zU8eO+Jtuj+1Vx1MM5KAkmZPJwQe9uTcoCpQa6DXOGG9kajDTnNN1Be1gkZuJDTZJG4SmJLXLbNY3RDnxpGmWta3qs/VgDq78/YM8ropt1/s7YKyrCfGE2ff+FUB0mLObiG01ZV2gu5HJzgE7SEWLEiI="));
    dns03_a->addRRsig(rrsig);

    dns03_nsec = RRsetPtr(new RRset(dns03, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    dns03_nsec->addRdata(generic::NSEC("foo.example.com. A RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(dns03, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));

    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com.  nn829Xw5CJFnPHwI9WHeT5epQv+odtCkHnjlPFGoPTLOyiks+041UmMqtq3uiSp4d2meMSe9UuDvoROT0L6NTtQQvVqiDhTn0irTFw1uw7fO8ZTG7eyu6Ypfz0+HvfbNvd4kMoD2OTgADRXPVsCTwK+PBOIIG9YTEQfl8pCqW5g="));
    dns03_nsec->addRRsig(rrsig);

    // www.example.com
    www_a = RRsetPtr(new RRset(www, RRClass::IN(), RRType::A(),
                                       RRTTL(3600)));
    www_a->addRdata(in::A("192.168.1.1"));

    rrsig = RRsetPtr(new RRset(www, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20100322084538 20100220084538 33495 example.com. qyFyyV/mE8x4pdhudr5iycwhDsva31MzwO1kBR+bDKvzJg8mN8KxlPZrOlNNUhd3YRXQVwieMyxOTWRPXoxrNEDkNwimXkfe3rrHY7ibV9eNS4OIBUjb44VjCNr9CmQSzfuQ2yxO2r+YIuPYHRCjieD4xh6t9ay4IaCN/tDAJ+Q="));
    www_a->addRRsig(rrsig);

    www_nsec = RRsetPtr(new RRset(www, RRClass::IN(),
                                  RRType::NSEC(), RRTTL(3600)));
    www_nsec->addRdata(generic::NSEC("example.com. A RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(www, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. ZLZlSVBa2oe4U+7SZASnypP2VkI5gg1/1cVGqYUvfYNIUkcVMWDgn7DZCfpmo+2vdlV/4VhAc+sjDd+X+e57XGnW8+lqZHvG6NMMhmSGmeATD3D+8lEJJGo0dxoN4rHJQyp/eT2S4nChz+D/ze+YRagYxGF7pXm9zcrw3kKZGTs="));
    www_nsec->addRRsig(rrsig);

    // *.wild.example.com
    wild_a = RRsetPtr(new RRset(wild, RRClass::IN(), RRType::A(),
                                        RRTTL(3600)));
    wild_a->addRdata(in::A("192.168.3.2"));

    rrsig = RRsetPtr(new RRset(wild, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20100322084538 20100220084538 33495 example.com. FdO+UWONgtLKFxUzzygGunw67F9y8SzsP7yOLEYVJclRR8X3Ii62L0gtQHq2y0TcKsXttRsD6XY+tM5P/pgXlTNi7Bk4Fgb0PIDPjOsfT4DrS80kWn0YbinM/4/FA1j5ru5sTTboOY5UGhvDnoA9ogNuQQYb2/3wkoH0PrA2Q/0="));
    wild_a->addRRsig(rrsig);

    wild_nsec = RRsetPtr(new RRset(wild, RRClass::IN(),
                                   RRType::NSEC(), RRTTL(3600)));
    wild_nsec->addRdata(generic::NSEC("www.example.com. A RRSIG NSEC"));

    rrsig = RRsetPtr(new RRset(wild, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));

    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. OoGYslRj4xjZnBuzgOqsrvkDAHWycmQzbUxCRmgWnCbXiobJK7/ynONH3jm8G3vGlU0lwpHkhNs6cUK+6Nu8W49X3MT0Xksl/brroLcXYLi3vfxnYUNMMpXdeFl6WNNfoJRo90F/f/TWXAClRrDS29qiG3G1PEJZikIxZsZ0tyM="));
    wild_nsec->addRRsig(rrsig);

    // foo.example.com
    foo_cname = RRsetPtr(new RRset(foo, RRClass::IN(), RRType::CNAME(),
                                           RRTTL(3600)));
    foo_cname->addRdata(generic::CNAME("cnametest.flame.org"));

    rrsig = RRsetPtr(new RRset(foo, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. DSqkLnsh0gCeCPVW/Q8viy9GNP+KHmFGfWqyVG1S6koBtGN/VQQ16M4PHZ9Zssmf/JcDVJNIhAChHPE2WJiaPCNGTprsaUshf1Q2vMPVnkrJKgDY8SVRYMptmT8eaT0gGri4KhqRoFpMT5OYfesybwDgfhFSQQAh6ps3bIUsy4o="));
    foo_cname->addRRsig(rrsig);

    foo_nsec = RRsetPtr(new RRset(foo, RRClass::IN(),
                                  RRType::NSEC(), RRTTL(3600)));
    foo_nsec->addRdata(generic::NSEC("mail.example.com. CNAME RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(foo, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. RTQwlSqui6StUYye1KCSOEr1d3irndWFqHBpwP7g7n+w8EDXJ8I7lYgwzHvlQt6BLAxe5fUDi7ct8M5hXvsm7FoWPZ5wXH+2/eJUCYxIw4vezKMkMwBP6M/YkJ2CMqY8DppYf60QaLDONQAr7AcK/naSyioeI5h6eaoVitUDMso="));
    foo_nsec->addRRsig(rrsig);

    // cname-int.example.com
    cnameint_cname = RRsetPtr(new RRset(cnameint, RRClass::IN(),
                                        RRType::CNAME(), RRTTL(3600)));
    cnameint_cname->addRdata(generic::CNAME("www.example.com"));

    rrsig = RRsetPtr(new RRset(cnameint, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. U1wjt0XY9xjTwvUmWSUcfLGMhCjfX2ylWfHrycy50x2oxcK9z94E1ejen9wDTIEBSGYgi6wpZ8RK0+02N1DWTGpDqNXd7aFRfDrWQJ/q/XJHDx0vlcmhkWhrT82LBfKxkrptOzchuSo/c0mpK+mpiIMc1VOwY+yuQ2ALfcD6EHw="));
    cnameint_cname->addRRsig(rrsig);

    cnameint_nsec = RRsetPtr(new RRset(cnameint, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    cnameint_nsec->addRdata(generic::NSEC("dname.example.com. CNAME RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(cnameint, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. rbV+gaxfrsoha59NOLF4EFyWQ+GuFCVK/8D77x1atan3HNlXBlZ1smgudKTaJ3CtlobIDt0MEdPxY1yn2Tskw/5mlP1PWf8oaP3BwGSQdn4gLI8+sMpNOPFEdXpxqxngm2F6/7fqniL1QuSAQBEdO+5UiCAgnncPmAsSJg3u1zg="));
    cnameint_nsec->addRRsig(rrsig);

    // cname-ext.example.com
    cnameext_cname = RRsetPtr(new RRset(cnameext, RRClass::IN(),
                                        RRType::CNAME(), RRTTL(3600)));
    cnameext_cname->addRdata(generic::CNAME("www.sql1.example.com"));

    rrsig = RRsetPtr(new RRset(cnameext, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. bGPIuZilyygvTThK4BrdECuaBcnZUgW/0d09iN2CrNjckchQl3dtbnMNirFsVs9hShDSldRNlQpiAVMpnPgXHhReNum7jmX6yqIH6s8GKIo91zr3VL/ramlezie5w4MilDHrxXLK2pb8IHmP+ZHivQ2EtdYQZgETWBWxr5FDfwk="));
    cnameext_cname->addRRsig(rrsig);

    cnameext_nsec = RRsetPtr(new RRset(cnameext, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    cnameext_nsec->addRdata(generic::NSEC("cname-int.example.com. CNAME RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(cnameext, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. inWsFwSDWG7TakjwbUTzTRpXz0WifelA5Kn3ABk6BVirIPmd+yQoNj2QZBDFAQwhnLPlNws2Oo4vgMsBMyx1Fv5eHgMUuCN3DUDaLlzlPtUb42CjOUa+jZBeTV/Hd7WZrirluASE1QFDprLdSSqoPPfAKvN3pORtW7y580dMOIM="));
    cnameext_nsec->addRRsig(rrsig);

    // dname.example.com
    dname_dname = RRsetPtr(new RRset(dname, RRClass::IN(), RRType::DNAME(),
                               RRTTL(3600)));
    dname_dname->addRdata(generic::DNAME("sql1.example.com."));

    rrsig = RRsetPtr(new RRset(dname, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("DNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. ae8U47oaiwWdurkSyzcsCAF6DxBqjukizwF7K7U6lQVMtfoUE14oiAqfj1fjH8YLDOO/Hd1twrd/u0vgjnI1Gg32YTi7cYOzwE912SV1u2B/y0awaQKWPBwOW0aI7vxelt1vMUF81xosiQD04gOIdDBTqbHKcDxum87iWbhk4Ug="));
    dname_dname->addRRsig(rrsig);

    dname_nsec = RRsetPtr(new RRset(dname, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    dname_nsec->addRdata(generic::NSEC("dns01.example.com. DNAME RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(dname, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. c21Fff2D8vBrLzohBnUeflkaRdUAnUxAFGp+UQ0miACDCMOFBlCS9v9g/2+orOnKfd3l4vyz55C310t8JXgXb119ofaZWj2zkdUe+X8Bax+sMS0Y5K/sUhSNvbJbozr9UYPdvjSVBiWgh3s9fsb+etKq9uFukAzGU/FuGYpO0r0="));
    dname_nsec->addRRsig(rrsig);

    // subzone.example.com
    subzone_ns = RRsetPtr(new RRset(subzone, RRClass::IN(), RRType::NS(),
                                    RRTTL(3600)));
    subzone_ns->addRdata(generic::NS(Name("ns1.subzone.example.com")));
    subzone_ns->addRdata(generic::NS(Name("ns2.subzone.example.com")));

    subzone_ds = RRsetPtr(new RRset(subzone, RRClass::IN(), RRType::DS(),
                                    RRTTL(3600)));

    subzone_glue1 = RRsetPtr(new RRset(Name("ns1.subzone.example.com"),
                                    RRClass::IN(), RRType::A(),
                                    RRTTL(3600)));
    subzone_glue1->addRdata(in::A("192.168.3.1"));
    subzone_glue2 = RRsetPtr(new RRset(Name("ns2.subzone.example.com"),
                                    RRClass::IN(), RRType::A(),
                                    RRTTL(3600)));
    subzone_glue2->addRdata(in::A("192.168.3.2"));

    subzone_ds = RRsetPtr(new RRset(subzone, RRClass::IN(), RRType::DS(),
                                    RRTTL(3600)));

    subzone_ds->addRdata(generic::DS("33313 5 1 0FDD7A2C11AA7F55D50FBF9B7EDDA2322C541A8D"));
    subzone_ds->addRdata(generic::DS("33313 5 2 00B99B7006F496D135B01AB17EDB469B4BE9E1973884DEA757BC4E3015A8C3AB"));

    rrsig = RRsetPtr(new RRset(subzone, RRClass::IN(), RRType::RRSIG(),
                               RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("DS 5 3 3600 20100322084538 20100220084538 33495 example.com. dIqZKvpkJN1l92SOiWgJh3KbjErIN+EfojMsm4pEdV5xQdZwj6DNNEu6Kw4rRwdvrZIu0TyqPr3jSJb7o6R7vZgZzmLfVV/ojQah7rwuYHCFcfyZ4JyK2311fMhRR1QAvMsdcjdyA1XC140Cm6AnL3cH5rh/KUks/0ec3Ca7GNQ="));
    subzone_ds->addRRsig(rrsig);

    subzone_nsec = RRsetPtr(new RRset(subzone, RRClass::IN(),
                                      RRType::NSEC(), RRTTL(3600)));
    subzone_nsec->addRdata(generic::NSEC("*.wild.example.com. NS DS RRSIG NSEC"));
    rrsig = RRsetPtr(new RRset(subzone, RRClass::IN(), RRType::RRSIG(), RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG("NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. Oe2kgIhsLtPJ4+lDZDxznV8/vEVoXKOBFN9lwWyebaKa19BaSXlQ+YVejmulmKDDjEucMvEfuItfn6w7bnU+DzOLk5D1lJCjwDlKz8u3xOAx16TiuQn4bgQAOiFtBQygmGGqO3BVpX+jxsmw7eH3emofy8uUqr/C4aopnwuf28g="));
    subzone_nsec->addRRsig(rrsig);

    loop1_cname = RRsetPtr(new RRset(loop1, RRClass::IN(), RRType::CNAME(),
                                     RRTTL(3600)));
    loop1_cname->addRdata(generic::CNAME(loop2));
    loop2_cname = RRsetPtr(new RRset(loop2, RRClass::IN(), RRType::CNAME(),
                                     RRTTL(3600)));
    loop2_cname->addRdata(generic::CNAME(loop1));
}

void
TestDataSrc::findClosestEnclosure(NameMatch& match) const {
    const Name& qname = match.qname();
    NameComparisonResult::NameRelation cmp;

    cmp = qname.compare(sql1).getRelation();
    if (cmp == NameComparisonResult::EQUAL ||
          cmp == NameComparisonResult::SUBDOMAIN) {
        match.update(*this, sql1);
        return;
    }

    cmp = qname.compare(example).getRelation();
    if (cmp == NameComparisonResult::EQUAL ||
          cmp == NameComparisonResult::SUBDOMAIN) {
        match.update(*this, example);
        return;
    }

}

void
TestDataSrc::findRecords(const Name& name, const RRType& rdtype,
                         RRsetList& target, const Name* zonename, const Mode mode,
                         uint32_t& flags) const
{
    const bool any = (rdtype == RRType::ANY());
    flags = 0;

    assert(zonename != NULL);
    if (*zonename == sql1) {
        if (name == sql1 && mode == DELEGATION) {
            target.addRRset(sql1_ns);
            flags |= REFERRAL;
        } else if (name == sql1) {
            if (any) {
                target.addRRset(sql1_ns);
                target.addRRset(sql1_nsec);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NS()) {
                target.addRRset(sql1_ns);
                flags |= REFERRAL;
            } else if (rdtype == RRType::SOA()) {
                target.addRRset(sql1_soa);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(sql1_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == www_sql1) {
            if (any) {
                target.addRRset(www_sql1_a);
                target.addRRset(www_sql1_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(www_sql1_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(www_sql1_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else {
            flags |= NAME_NOT_FOUND;
        }
    } else {
        if (name == example && mode == DELEGATION) {
            target.addRRset(example_ns);
            flags |= REFERRAL;
        } else if (name == example) {
            if (any) {
                target.addRRset(example_ns);
                target.addRRset(example_soa);
                target.addRRset(example_nsec);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NS()) {
                target.addRRset(example_ns);
                flags |= REFERRAL;
            } else if (rdtype == RRType::SOA()) {
                target.addRRset(example_soa);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(example_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == sql1 && mode == DELEGATION) {
            target.addRRset(sql1_ns);
            target.addRRset(sql1_ds);
            target.addRRset(sql1_ds_nsec);
            flags |= REFERRAL;
        } else if (name == sql1) {
            if (any) {
                target.addRRset(sql1_ns);
                target.addRRset(sql1_ds);
                target.addRRset(sql1_ds_nsec);
                flags |= REFERRAL;
            } else if (rdtype == RRType::DS()) {
                target.addRRset(sql1_ds);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NS()) {
                target.addRRset(sql1_ns);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(sql1_ds_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == subzone && mode == DELEGATION) {
            target.addRRset(subzone_ns);
            target.addRRset(subzone_ds);
            flags |= REFERRAL;
        } else if (name == subzone) {
            if (any) {
                target.addRRset(subzone_ns);
                target.addRRset(subzone_nsec);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NS()) {
                target.addRRset(subzone_ns);
                flags |= REFERRAL;
            } else if (rdtype == RRType::DS()) {
                target.addRRset(subzone_ds);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(subzone_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == dns01 && mode == ADDRESS) {
            target.addRRset(dns01_a);
        } else if (name == dns01) {
            if (any) {
                target.addRRset(dns01_a);
                target.addRRset(dns01_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(dns01_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(dns01_nsec);
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == dns02 && mode == ADDRESS) {
            target.addRRset(dns02_a);
        } else if (name == dns02) {
            if (any) {
                target.addRRset(dns02_a);
                target.addRRset(dns02_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(dns02_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(dns02_nsec);
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == dns03 && mode == ADDRESS) {
            target.addRRset(dns03_a);
        } else if (name == dns03) {
            if (any) {
                target.addRRset(dns03_a);
                target.addRRset(dns03_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(dns03_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(dns03_nsec);
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == wild) {
            if (any) {
                target.addRRset(wild_a);
                target.addRRset(wild_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(wild_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(wild_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == www) {
            if (any) {
                target.addRRset(www_a);
                target.addRRset(www_nsec);
            } else if (rdtype == RRType::A()) {
                target.addRRset(www_a);
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(www_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == foo) {
            if (rdtype == RRType::NSEC()) {
                target.addRRset(foo_nsec);
            } else {
                target.addRRset(foo_cname);
                if (rdtype != RRType::CNAME()) {
                    flags |= CNAME_FOUND;
                }
            }
        } else if (name == cnameint) {
            if (rdtype == RRType::NSEC()) {
                target.addRRset(cnameint_nsec);
            } else {
                target.addRRset(cnameint_cname);
                if (rdtype != RRType::CNAME()) {
                    flags |= CNAME_FOUND;
                }
            }
        } else if (name == cnameext) {
            if (rdtype == RRType::NSEC()) {
                target.addRRset(cnameext_nsec);
            } else {
                target.addRRset(cnameext_cname);
                if (rdtype != RRType::CNAME()) {
                    flags |= CNAME_FOUND;
                }
            }
        } else if (name == dname) {
            if (any) {
                target.addRRset(dname_dname);
                target.addRRset(dname_nsec);
                flags |= REFERRAL;
            } else if (rdtype == RRType::DNAME()) {
                target.addRRset(dname_dname);
                flags |= REFERRAL;
            } else if (rdtype == RRType::NSEC()) {
                target.addRRset(dns01_nsec);
                flags |= REFERRAL;
            } else {
                flags |= TYPE_NOT_FOUND;
            }
        } else if (name == Name("ns1.subzone.example.com") && mode == ADDRESS) {
            target.addRRset(subzone_glue1);
        } else if (name == Name("ns2.subzone.example.com") && mode == ADDRESS) {
            target.addRRset(subzone_glue2);
        } else if (name == loop1) {
            target.addRRset(loop1_cname);
            if (rdtype != RRType::CNAME()) {
                flags |= CNAME_FOUND;
            }
        } else if (name == loop2) {
            target.addRRset(loop1_cname);
            if (rdtype != RRType::CNAME()) {
                flags |= CNAME_FOUND;
            }
        } else {
            flags |= NAME_NOT_FOUND;
        }
    }
    return;
}

DataSrc::Result
TestDataSrc::findRRset(const Query& q,
                       const Name& qname,
                       const RRClass& qclass,
                       const RRType& qtype,
                       RRsetList& target,
                       uint32_t& flags,
                       const Name* zonename) const
{
    findRecords(qname, qtype, target, zonename, NORMAL, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findExactRRset(const Query& q,
                            const Name& qname,
                            const RRClass& qclass,
                            const RRType& qtype,
                            RRsetList& target,
                            uint32_t& flags,
                            const Name* zonename) const
{
    findRecords(qname, qtype, target, zonename, NORMAL, flags);
    // Ignore referrals in this case
    flags &= ~REFERRAL;

    // CNAMEs don't count in this case
    if (flags & CNAME_FOUND) {
        flags &= ~CNAME_FOUND;
        flags |= TYPE_NOT_FOUND;
    }

    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findAddrs(const Query& q,
                        const Name& qname,
                        const RRClass& qclass,
                        RRsetList& target,
                        uint32_t& flags,
                        const Name* zonename) const
{
    findRecords(qname, RRType::ANY(), target, zonename, ADDRESS, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findReferral(const Query& q,
                          const Name& qname,
                          const RRClass& qclass,
                          RRsetList& target,
                          uint32_t& flags,
                          const Name* zonename) const
{
    findRecords(qname, RRType::ANY(), target, zonename, DELEGATION, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findPreviousName(const Query& q,
                              const Name& qname,
                              Name& target,
                              const Name* zonename) const
{
    assert(zonename != NULL);

    if (*zonename == example) {
        if (qname >= example || qname < cnameext) {
            target = example;
        } else if (qname < cnameint) {
            target = cnameext;
        } else if (qname < dname) {
            target = cnameint;
        } else if (qname < dns01) {
            target = dname;
        } else if (qname < dns02) {
            target = dns01;
        } else if (qname < dns03) {
            target = dns02;
        } else if (qname < foo) {
            target = dns03;
        } else if (qname < sql1) {
            target = foo;
        } else if (qname < subzone) {
            target = sql1;
        } else if (qname < www) {
            target = subzone;
        } else if (qname < wild) {
            target = www;
        } else {
            target = wild;
        }
    } else {
        if (qname >= sql1 || qname < www_sql1) {
            target = sql1;
        } else {
            target = www_sql1;
        }
    }
    return (SUCCESS);
}

}
}
