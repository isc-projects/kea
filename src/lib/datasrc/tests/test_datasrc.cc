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

#include <config.h>

#include <cassert>

#include <algorithm>

#include <dns/tests/unittest_util.h>
#include <datasrc/tests/test_datasrc.h>

#include <datasrc/data_source.h>

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
namespace datasrc {

namespace {

// This is a mock data source for testing.  It can contain multiple zones.
// The content of each zone should be configured in the form of RRData{}.
// Each RRData element is a tuple of char strings, representing
// "name, RRtype, RDATA".  For simplicity we use the same single TTL for
// RRs (TEST_TTL) defined below.
// Multiple RRs of the same pair of (name, RRtype) can be defined, but
// they must not be interleaved with other types of pair.  For example,
// This is okay:
// {"example.com", "AAAA", "2001:db8::1"},
// {"example.com", "AAAA", "2001:db8::2"},
// ...
// but this is invalid:
// {"example.com", "AAAA", "2001:db8::1"},
// {"example.com", "A", "192.0.2.1"},
// {"example.com", "AAAA", "2001:db8::2"},
// ...
// If an RRset is associated with an RRSIG, the RRSIG must immediately follow
// the RRset to be signed.  Multiple RRSIGs can follow the RRset.  RRSIG
// records will always be attached to the most recent non-RRSIG RRset;
// consequently, the first RR listed must not be an RRSIG record.
//
// Names are sorted internally, and don't have to be sorted in the data.
//
// A zone is defined in the form of ZoneData{}, which contains:
// zone name (character string)
// RRclass (character string)
// A pointer to in-zone RRs in the form of RRData{}
// A pointer to glue RRs in the form of RRData{}
// Glues can be omitted, in which case a convenient constant "empty_records"
// can be specified.

// For simplicity we use the same single TTL for all test RRs.
const uint32_t TEST_TTL = 3600;

struct RRData {
    const char* const name;
    const char* const rrtype;
    const char* const rdata;
};

struct ZoneData {
    const char* const zone_name;
    const char* const rrclass;
    const struct RRData* records;
    const struct RRData* glue_records;
};

//
// zone data for example.com
//
const struct RRData example_com_records[] = {
    // example.com
    {"example.com", "NS", "dns01.example.com"},
    {"example.com", "NS", "dns02.example.com"},
    {"example.com", "NS", "dns03.example.com"},
    {"example.com", "RRSIG", "NS 5 2 3600 20100322084538 20100220084538 33495 example.com. ClcrfjkQZUY5L6ZlCkU3cJHzcrEGrofKSVeeoeZ+w6yeEowFNVXs2YBo3tom53DiCrdD9rs3feVSLGW5rjsz/O6lDuomgQG+EVSnWa7GTIPBXj1BmDXXp3XxeldYmhf4UzaN5BA+RUA5E8NChNKuNNof76j2S9tilfN/kvpy4fw="},
    {"example.com", "SOA", "master.example.com. admin.example.com. 1234 3600 1800 2419200 7200"},
    {"example.com", "RRSIG", "SOA 5 2 3600 20100322084538 20100220084538 33495 example.com.  KUun66Qaw36osk2BJS6U1fAy3PPDkNo2QK4meGNbDBY8q8b+f2o+IXJ14YCvssGl1ORW0CcLnDRxssnk8V/Svmj5iFhO+8HC2hnVBdi2zewvdVtwRb+lWwKN7pkXXwuy6g1t9WCd/j5FCc/wgxqtZUTPb6XgZcnHrORDMOTqLs4="},
    {"example.com", "NSEC", "cname-ext.example.com. NS SOA MX RRSIG NSEC DNSKEY"},
    {"example.com", "RRSIG", "NSEC 5 2 7200 20100322084538 20100220084538 33495 example.com. KxuVaPPKNPJzr/q+cJPiNlkHVTQK0LVsgTbSqruXQc25lAd0wn5oKUtxL1bEAchHkfA8eLzcYCj2ZqqAv9OJubw53mfskTad7UHs4Uj2RTrIsNGMCiZGgOpvNb9JcWpQtoyXVT1uNse+Qsbeir0eyeYIufUynFU041jtNrlJMio="},
    {"example.com", "DNSKEY", "257 3 5 AwEAAe5WFbxdCPq2jZrZhlMj7oJdff3W7syJtbvzg62tRx0gkoCDoBI9DPjlOQG0UAbj+xUV4HQZJStJaZ+fHU5AwVNT+bBZdtV+NujSikhdTHb4FYLg2b3Cx9NyJvAVukHp/91HnWuG4T36CzAFrfPwsHIrBz9BsaIQ21VRkcmj7DswfI/iDGd8j6bqiODyNZYQ+ZrLmF0KIJ2yPN3iO6Zq23TaOrVTjB7d1a/h31ODfiHAxFHrkY3t3D5JR9Nsl/7fdRmSznwtcSDgLXBoFEYmw6p86AcvRyoYNcL1SXjaKVLG5jyU3UR+LcGZT5t/0xGfoIK/aKwENrsjcKZZj660b1M="},
    {"example.com", "DNSKEY", "256 3 5 AwEAAcOUBllYc1hf7ND9uDy+Yz1BF3sI0m4qNGV7WcTD0WEiuV7IjXgHE36fCmS9QsUxSSOVo1I/FMxI2PJVqTYHkXFBS7AzLGsQYMU7UjBZSotBJ6Imt5pXMu+lEDNy8TOUzG3xm7g0qcbWYF6qCEfvZoBtAqi5Rk7Mlrqs8agxYyMx"},
    {"example.com", "RRSIG", "DNSKEY 5 2 3600 20100416210049 20100317210049 4456 example.com. 37FC0rcwOZVarTMjft0BMbvv8hbJU7OHNsvO7R1q6OgsLTj7QGMX3sC42JGbwUrYI/OwnZblNcv1eim0g0jX5k+sVr2OJsEubngRjVqLo54qV8rBC14tLk9PGKxxjQG0IBJU866uHxzXYBO2a1r2g93/qyTtrT7iPLu/2Ce1WRKMBPK0yf4nW2usFU/PXesXFWpZ7HLGZL73/NWv8wcezBDuU0B2PlHLjSu7k6poq6JWDC02o5SYnEBwsJ5Chi+3/NZmzKTiNP7g0H4t6QhunkEXxL3z0617mwwQt00ypXsNunnPy4Ub5Kllk1SKJl8ZkEDKkJtSvuXJhcAZsLyMQw=="},
    {"example.com", "RRSIG", "DNSKEY 5 2 3600 20100416210049 20100317210049 33495 example.com. h3OM5r3roBsgnEQk9fcjTg5L7p3yDptDpVzDN/lgjqpaWxtlz5LsulBH3YzwYyXzT7pG7L0/qT6dcuRECc/rniECviWvmJMJZzEAMry0Of/pk/8ekuGTxABpqwAoCwM5as30sc0cfMJTS7umpJVDA4lRB2zoKGefWnJ3+pREDiY="},

    // dns01.example.com
    {"dns01.example.com", "A", "192.0.2.1"},
    {"dns01.example.com", "RRSIG", "A 5 3 3600 20100322084538 20100220084538 33495 example.com. NIawlZLk8WZAjNux7oQM2mslfW52OZFFkWt++7FHu2SU98XqEeKfCMnpgtWe5T8Nr9cS8df901iEOJoWQzGTEaHYUBtEhsSjBVn7mKp3fz6473a2xxy75SUKZ0rxjNXSZ8Q5rnFmkX0HTH2Sg51mtjH6aC2pfheQnA2t193BnSg="},
    {"dns01.example.com", "NSEC", "dns02.example.com. A RRSIG NSEC"},
    {"dns01.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. EkyeshmMNP9xiAz6mDFDIwksTdmkF9zsFzLuVKAgK6eUk7St6tp5PSvjA8nWol0vdvvz4LK85a4ffTFEiNRyvWeYP2vOhEkyDcrwuCd8Vc3jh/8Sm1Js+nX7hJStrZGFvp2TWPpt9nKH5p3MxXvTb/YVurnue0xSeFAE17O3+I0="},

    // dns02.example.com
    {"dns02.example.com", "A", "192.0.2.2"},
    {"dns02.example.com", "RRSIG", "A 5 3 3600 20100322084538 20100220084538 33495 example.com. XJtVMbUIRE0mk6Hn/Nx6k36jaxaBDPK2/IYB6vCQjJETz6gW4T6q/H/eY9/Lsw5iYPFhoBRDxT4XFj575t98kELXnJe1WhuMbRPlOhyOjxkLECaUne/sbFPOtbGFx9ohuojI0RgxxZiCFaO8wJuv6nfPuzmlLajWS6z9NZeOMIk="},
    {"dns02.example.com", "NSEC", "dns03.example.com. A RRSIG NSEC"},
    {"dns02.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. imBNTMB3sPU4kblcaAH6V7lCVt5xgtAybi3DA/SbLEulLaV2NE6vcoEn/AieaM4mOJicQnUDj/H+1hSEhzxU2tRM8zfVlvztxQWn6eh7ZR4mKfNDSvRUGU9ykhpwMyC7wjOt1j5bcSA/OTnLRAilslnJyOM4bSaxVEFo8YPjncY="},

    // dns03.example.com
    {"dns03.example.com", "A", "192.0.2.3"},
    {"dns03.example.com", "RRSIG", "A 5 3 3600 20100322084538 20100220084538 33495 example.com. Ubrcm1H+F6m8khle7P9zU8eO+Jtuj+1Vx1MM5KAkmZPJwQe9uTcoCpQa6DXOGG9kajDTnNN1Be1gkZuJDTZJG4SmJLXLbNY3RDnxpGmWta3qs/VgDq78/YM8ropt1/s7YKyrCfGE2ff+FUB0mLObiG01ZV2gu5HJzgE7SEWLEiI="},
    {"dns03.example.com", "NSEC", "foo.example.com. A RRSIG NSEC"},
    {"dns03.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com.  nn829Xw5CJFnPHwI9WHeT5epQv+odtCkHnjlPFGoPTLOyiks+041UmMqtq3uiSp4d2meMSe9UuDvoROT0L6NTtQQvVqiDhTn0irTFw1uw7fO8ZTG7eyu6Ypfz0+HvfbNvd4kMoD2OTgADRXPVsCTwK+PBOIIG9YTEQfl8pCqW5g="},

    // www.example.com
    {"www.example.com", "A", "192.0.2.1"},
    {"www.example.com", "RRSIG", "A 5 3 3600 20100322084538 20100220084538 33495 example.com. qyFyyV/mE8x4pdhudr5iycwhDsva31MzwO1kBR+bDKvzJg8mN8KxlPZrOlNNUhd3YRXQVwieMyxOTWRPXoxrNEDkNwimXkfe3rrHY7ibV9eNS4OIBUjb44VjCNr9CmQSzfuQ2yxO2r+YIuPYHRCjieD4xh6t9ay4IaCN/tDAJ+Q="},
    {"www.example.com", "NSEC", "example.com. A RRSIG NSEC"},
    {"www.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. ZLZlSVBa2oe4U+7SZASnypP2VkI5gg1/1cVGqYUvfYNIUkcVMWDgn7DZCfpmo+2vdlV/4VhAc+sjDd+X+e57XGnW8+lqZHvG6NMMhmSGmeATD3D+8lEJJGo0dxoN4rHJQyp/eT2S4nChz+D/ze+YRagYxGF7pXm9zcrw3kKZGTs="},

    // *.wild.example.com
    {"*.wild.example.com", "A", "192.0.2.2"},
    {"*.wild.example.com", "RRSIG", "A 5 3 3600 20100322084538 20100220084538 33495 example.com. FdO+UWONgtLKFxUzzygGunw67F9y8SzsP7yOLEYVJclRR8X3Ii62L0gtQHq2y0TcKsXttRsD6XY+tM5P/pgXlTNi7Bk4Fgb0PIDPjOsfT4DrS80kWn0YbinM/4/FA1j5ru5sTTboOY5UGhvDnoA9ogNuQQYb2/3wkoH0PrA2Q/0="},
    {"*.wild.example.com", "NSEC", "*.wild2.example.com. A RRSIG NSEC"},
    {"*.wild.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. OoGYslRj4xjZnBuzgOqsrvkDAHWycmQzbUxCRmgWnCbXiobJK7/ynONH3jm8G3vGlU0lwpHkhNs6cUK+6Nu8W49X3MT0Xksl/brroLcXYLi3vfxnYUNMMpXdeFl6WNNfoJRo90F/f/TWXAClRrDS29qiG3G1PEJZikIxZsZ0tyM="},

    // *.wild2.example.com
    {"*.wild2.example.com", "CNAME", "www.example.com"},
    {"*.wild2.example.com", "RRSIG", "CNAME 5 3 3600 20100410212307 20100311212307 33495 example.com. pGHtGdRBi4GKFSKszi6SsKvuBLDX8dFhZubU0tMojQ9SJuiFNF+WtxvdAYuUaoWP/9VLUaYmiw5u7JnzmR84DiXZPEs6DtD+UJdOZhaS7V7RTpE+tMOfVQBLpUnRWYtlTTmiBpFquzf3DdIxgUFhEPEuJJyp3LFRxJObCaq9 nvI="},
    {"*.wild2.example.com", "NSEC", "*.wild3.example.com. CNAME RRSIG NSEC"},
    {"*.wild2.example.com", "RRSIG", "NSEC 5 3 7200 20100410212307 20100311212307 33495 example.com. EuSzh6or8mbvwru2H7fyYeMpW6J8YZ528rabU38V/lMN0TdamghIuCneAvSNaZgwk2MSN1bWpZqB2kAipaM/ZI9/piLlTvVjjOQ8pjk0auwCEqT7Z7Qng3E92O9yVzO+WHT9QZn/fR6t60392In4IvcBGjZyjzQk8njIwbui xGA="},

    // *.wild3.example.com -- a wildcard record with a lame CNAME
    {"*.wild3.example.com", "CNAME", "spork.example.com"},
    {"*.wild3.example.com", "RRSIG", "CNAME 5 3 3600 20100410212307 20100311212307 33495 example.com. pGHtGdRBi4GKFSKszi6SsKvuBLDX8dFhZubU0tMojQ9SJuiFNF+WtxvdAYuUaoWP/9VLUaYmiw5u7JnzmR84DiXZPEs6DtD+UJdOZhaS7V7RTpE+tMOfVQBLpUnRWYtlTTmiBpFquzf3DdIxgUFhEPEuJJyp3LFRxJObCaq9 nvI="},
    {"*.wild3.example.com", "NSEC", "www.example.com. CNAME RRSIG NSEC"},
    {"*.wild3.example.com", "RRSIG", "NSEC 5 3 7200 20100410212307 20100311212307 33495 example.com. EuSzh6or8mbvwru2H7fyYeMpW6J8YZ528rabU38V/lMN0TdamghIuCneAvSNaZgwk2MSN1bWpZqB2kAipaM/ZI9/piLlTvVjjOQ8pjk0auwCEqT7Z7Qng3E92O9yVzO+WHT9QZn/fR6t60392In4IvcBGjZyjzQk8njIwbui xGA="},

    // foo.example.com
    {"foo.example.com", "CNAME", "cnametest.flame.org"},
    {"foo.example.com", "RRSIG", "CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. DSqkLnsh0gCeCPVW/Q8viy9GNP+KHmFGfWqyVG1S6koBtGN/VQQ16M4PHZ9Zssmf/JcDVJNIhAChHPE2WJiaPCNGTprsaUshf1Q2vMPVnkrJKgDY8SVRYMptmT8eaT0gGri4KhqRoFpMT5OYfesybwDgfhFSQQAh6ps3bIUsy4o="},
    {"foo.example.com", "NSEC", "mail.example.com. CNAME RRSIG NSEC"},
    {"foo.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. RTQwlSqui6StUYye1KCSOEr1d3irndWFqHBpwP7g7n+w8EDXJ8I7lYgwzHvlQt6BLAxe5fUDi7ct8M5hXvsm7FoWPZ5wXH+2/eJUCYxIw4vezKMkMwBP6M/YkJ2CMqY8DppYf60QaLDONQAr7AcK/naSyioeI5h6eaoVitUDMso="},

    // cname-int.example.com
    {"cname-int.example.com", "CNAME", "www.example.com."},
    {"cname-int.example.com", "RRSIG", "CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. U1wjt0XY9xjTwvUmWSUcfLGMhCjfX2ylWfHrycy50x2oxcK9z94E1ejen9wDTIEBSGYgi6wpZ8RK0+02N1DWTGpDqNXd7aFRfDrWQJ/q/XJHDx0vlcmhkWhrT82LBfKxkrptOzchuSo/c0mpK+mpiIMc1VOwY+yuQ2ALfcD6EHw="},
    {"cname-int.example.com", "NSEC", "dname.example.com. CNAME RRSIG NSEC"},
    {"cname-int.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. rbV+gaxfrsoha59NOLF4EFyWQ+GuFCVK/8D77x1atan3HNlXBlZ1smgudKTaJ3CtlobIDt0MEdPxY1yn2Tskw/5mlP1PWf8oaP3BwGSQdn4gLI8+sMpNOPFEdXpxqxngm2F6/7fqniL1QuSAQBEdO+5UiCAgnncPmAsSJg3u1zg="},

    // cname-ext.example.com
    {"cname-ext.example.com", "CNAME", "www.sql1.example.com"},
    {"cname-ext.example.com", "RRSIG", "CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. bGPIuZilyygvTThK4BrdECuaBcnZUgW/0d09iN2CrNjckchQl3dtbnMNirFsVs9hShDSldRNlQpiAVMpnPgXHhReNum7jmX6yqIH6s8GKIo91zr3VL/ramlezie5w4MilDHrxXLK2pb8IHmP+ZHivQ2EtdYQZgETWBWxr5FDfwk="},
    {"cname-ext.example.com", "NSEC", "cname-int.example.com. CNAME RRSIG NSEC"},
    {"cname-ext.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. inWsFwSDWG7TakjwbUTzTRpXz0WifelA5Kn3ABk6BVirIPmd+yQoNj2QZBDFAQwhnLPlNws2Oo4vgMsBMyx1Fv5eHgMUuCN3DUDaLlzlPtUb42CjOUa+jZBeTV/Hd7WZrirluASE1QFDprLdSSqoPPfAKvN3pORtW7y580dMOIM="},

    // dname.example.com
    {"dname.example.com", "DNAME", "sql1.example.com."},
    {"dname.example.com", "RRSIG", "DNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. ae8U47oaiwWdurkSyzcsCAF6DxBqjukizwF7K7U6lQVMtfoUE14oiAqfj1fjH8YLDOO/Hd1twrd/u0vgjnI1Gg32YTi7cYOzwE912SV1u2B/y0awaQKWPBwOW0aI7vxelt1vMUF81xosiQD04gOIdDBTqbHKcDxum87iWbhk4Ug="},
    {"dname.example.com", "NSEC", "dns01.example.com. DNAME RRSIG NSEC"},
    {"dname.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. c21Fff2D8vBrLzohBnUeflkaRdUAnUxAFGp+UQ0miACDCMOFBlCS9v9g/2+orOnKfd3l4vyz55C310t8JXgXb119ofaZWj2zkdUe+X8Bax+sMS0Y5K/sUhSNvbJbozr9UYPdvjSVBiWgh3s9fsb+etKq9uFukAzGU/FuGYpO0r0="},

    // subzone.example.com
    {"subzone.example.com", "NS", "ns1.subzone.example.com"},
    {"subzone.example.com", "NS", "ns2.subzone.example.com"},
    {"subzone.example.com", "NSEC", "*.wild.example.com. NS DS RRSIG NSEC"},
    {"subzone.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. Oe2kgIhsLtPJ4+lDZDxznV8/vEVoXKOBFN9lwWyebaKa19BaSXlQ+YVejmulmKDDjEucMvEfuItfn6w7bnU+DzOLk5D1lJCjwDlKz8u3xOAx16TiuQn4bgQAOiFtBQygmGGqO3BVpX+jxsmw7eH3emofy8uUqr/C4aopnwuf28g="},
    {"subzone.example.com", "DS", "33313 5 1 0FDD7A2C11AA7F55D50FBF9B7EDDA2322C541A8D"},
    {"subzone.example.com", "DS", "33313 5 2 00B99B7006F496D135B01AB17EDB469B4BE9E1973884DEA757BC4E3015A8C3AB"},
    {"subzone.example.com", "RRSIG", "DS 5 3 3600 20100322084538 20100220084538 33495 example.com. dIqZKvpkJN1l92SOiWgJh3KbjErIN+EfojMsm4pEdV5xQdZwj6DNNEu6Kw4rRwdvrZIu0TyqPr3jSJb7o6R7vZgZzmLfVV/ojQah7rwuYHCFcfyZ4JyK2311fMhRR1QAvMsdcjdyA1XC140Cm6AnL3cH5rh/KUks/0ec3Ca7GNQ="},

    // subset of child zone: sql1
    {"sql1.example.com", "NS", "dns01.example.com"},
    {"sql1.example.com", "NS", "dns02.example.com"},
    {"sql1.example.com", "NS", "dns03.example.com"},

    {"sql1.example.com", "DS", "33313 5 1 0FDD7A2C11AA7F55D50FBF9B7EDDA2322C541A8D"},
    {"sql1.example.com", "DS", "33313 5 2 00B99B7006F496D135B01AB17EDB469B4BE9E1973884DEA757BC4E3015A8C3AB"},
    {"sql1.example.com", "RRSIG", "DS 5 3 3600 20100322084538 20100220084538 33495 example.com. dIqZKvpkJN1l92SOiWgJh3KbjErIN+EfojMsm4pEdV5xQdZwj6DNNEu6Kw4rRwdvrZIu0TyqPr3jSJb7o6R7vZgZzmLfVV/ojQah7rwuYHCFcfyZ4JyK2311fMhRR1QAvMsdcjdyA1XC140Cm6AnL3cH5rh/KUks/0ec3Ca7GNQ="},
    {"sql1.example.com", "NSEC", "subzone.example.com. NS DS RRSIG NSEC"},
    {"sql1.example.com", "RRSIG", "NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. k9FRdFyk/cPdkmmaoZbGZPpzIzfbFWQ3QCHd2qhJa0xAXaEOT/GBL6aFqx9SlunDu2wgES+To5fWPZGi4NzWpp6c5t27rnATN/oCEQ/UYIJKmWbqrXdst0Ps5boznk7suK2Y+km31KxaIf3fDd/T3kZCVsR0aWKRRRatPb7GfLw="},

    {NULL, NULL, NULL}
};
const struct RRData example_com_glue_records[] = {
    {"ns1.subzone.example.com", "A", "192.0.2.1"},
    {"ns2.subzone.example.com", "A", "192.0.2.2"},
    {NULL, NULL, NULL}
};

//
// zone data for sql1.example.com
//
const struct RRData sql1_example_com_records[] = {
    {"sql1.example.com", "NS", "dns01.example.com"},
    {"sql1.example.com", "NS", "dns02.example.com"},
    {"sql1.example.com", "NS", "dns03.example.com"},
    {"sql1.example.com", "RRSIG", "NS 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. 0CL8noy0NSgoWwuKd+Dc6vyIIw2BrAEBx0IJzcSB6GlB25x/zjEd6AJG0be13HN6jOaTX8iWTuCVrEYuXg76V+M4EvTZHjEScj0az74TrDv4Vdo459paGKCX9B8NLJW1mW4fzZrrXQ8jmBEZeS91Q5rJrO+UKJEuUz3LYdTPvao="},
    {"sql1.example.com", "SOA", "master.example.com. admin.example.com. 678 3600 1800 2419200 7200"},
    {"sql1.example.com", "RRSIG", "SOA 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. oakulfyljL/RAKgCKXEZ3KsG8BJj5WG4JK4moWFB6c9OKem6jIk8hKP2XlUVXFuOYJlRdIM4KicmR2GAK+5jJp6z5ShssstYTXo3QosVm6oCKumuFeLFHzcjfqP1D+F9NsvHldJIBnS/4ebPkmR5OENyCZXQF5HmN2awIj4CLjE="},
    {"sql1.example.com", "NSEC", "www.sql1.example.com. NS SOA RRSIG NSEC DNSKEY"},
    {"sql1.example.com", "RRSIG", "NSEC 5 3 7200 20100322084536 20100220084536 12447 sql1.example.com. v71CgdTYccCiTqfRcn6HsvISQa8ruvUfCKtpwym0RW/G27xlZn8otj2IMtWwkLxti8Rqqu+PTViLaOIbeVfHBcqzAd7U59cAOYoq3ODZx6auiE3C23HAKqUavKcP7Esaajm1cbcWy6Kyie4CAZc8M7EeKxgkXMKJGqBQzF+/FOo="},

    // www.sql1.example.com
    {"www.sql1.example.com", "A", "192.0.2.2"},
    {"www.sql1.example.com", "RRSIG", "A 5 4 3600 20100322084536 20100220084536 12447 sql1.example.com. DNdVKxB3oBsB14NPoV9WG14Y/g4zMcIXLYnFjj9vRZRZJpAvbTEipiXlayuhOxnqU827OipETQyeULZmLsqIQ1wK4Fgf+9b5aJ8D85/o4wBka00X4hZ3MwDPRb4mjuogwBTBg5NRpNSzUfbkPGiav08BFwgg+Efm9veSB05arS0="},
    {"www.sql1.example.com", "NSEC", "sql1.example.com. A RRSIG NSEC"},
    {"www.sql1.example.com", "RRSIG", "NSEC 5 4 7200 20100322084536 20100220084536 12447 sql1.example.com. cJMJhDx/ND7/9j3zhyXe+6eaSsU7ByYpXhJzbe+OhjFgH0VasQXq7o1QB3I293UZ+yhkjgXap+9QtPlraaNaYyTyOMQ42OoxSefJpYz9CME/FI2tsUfyrCnLFxYRNet7sMS0q+hLqxRayuEHDFDp72hHPGLJQ8a7jq4SrIonT50="},

    {NULL, NULL, NULL}
};

//
// zone data for loop.example
//
const struct RRData loop_example_records[] = {
    {"loop.example", "SOA", "master.loop.example admin.loop.example. "
     "1234 3600 1800 2419200 7200"},
    {"loop.example", "NS", "ns.loop.example"},
    {"one.loop.example", "CNAME", "two.loop.example"},
    {"two.loop.example", "CNAME", "one.loop.example"},
    {NULL, NULL, NULL}
};

//
// zone data for nons.example
//
const struct RRData nons_example_records[] = {
    {"nons.example", "SOA", "master.nons.example admin.nons.example. "
     "1234 3600 1800 2419200 7200"},
    {"www.nons.example", "A", "192.0.2.1"},
    {"ns.nons.example", "A", "192.0.2.2"},
    {NULL, NULL, NULL}
};

//
// zone data for nons-dname.example
//
const struct RRData nonsdname_example_records[] = {
    {"nons-dname.example", "SOA", "master.nons-dname.example "
     "admin.nons-dname.example. 1234 3600 1800 2419200 7200"},
    {"nons-dname.example", "DNAME", "example.org"},
    {"www.nons-dname.example", "A", "192.0.2.1"},
    {"ns.nons-dname.example", "A", "192.0.2.2"},
    {NULL, NULL, NULL}
};

//
// zone data for nosoa.example
//
const struct RRData nosoa_example_records[] = {
    {"nosoa.example", "NS", "ns.nosoa.example"},
    {"www.nosoa.example", "A", "192.0.2.1"},
    {"ns.nosoa.example", "A", "192.0.2.2"},
    {NULL, NULL, NULL}
};

//
// empty data set, for convenience.
//
const struct RRData empty_records[] = {
    {NULL, NULL, NULL}
};

//
// test zones
//
const struct ZoneData zone_data[] = {
    { "example.com", "IN", example_com_records, example_com_glue_records },
    { "sql1.example.com", "IN", sql1_example_com_records, empty_records },
    { "loop.example", "IN", loop_example_records, empty_records },
    { "nons.example", "IN", nons_example_records, empty_records },
    { "nons-dname.example", "IN", nonsdname_example_records, empty_records },
    { "nosoa.example", "IN", nosoa_example_records, empty_records }
};
const size_t NUM_ZONES = sizeof(zone_data) / sizeof(zone_data[0]);

struct Zone {
    Zone(const char* const name, const char* const class_txt) :
        zone_name(Name(name)), rrclass(class_txt)
    {}
    Name zone_name;
    RRClass rrclass;
    vector<Name> names;
    vector<RRsetPtr> rrsets;
};
vector<Zone> zones;
}

DataSrc::Result
TestDataSrc::init(isc::data::ConstElementPtr config UNUSED_PARAM) {
    return (init());
}

void
buildZone(Zone& zone, const RRData* records, const bool is_glue) {
    RRsetPtr prev_rrset;
    for (int i = 0; records[i].name != NULL; ++i) {
        Name name(records[i].name);
        RRType rrtype(records[i].rrtype);
        RRsetPtr rrset;
        bool new_name = false;

        if (!prev_rrset || prev_rrset->getName() != name) {
            if (!is_glue) {
                zone.names.push_back(name);
            }
            new_name = true;
        }

        if (new_name || prev_rrset->getType() != rrtype) {
            rrset = RRsetPtr(new RRset(name, zone.rrclass, rrtype,
                                       RRTTL(TEST_TTL)));
            if (rrtype != RRType::RRSIG()) {
                zone.rrsets.push_back(rrset);
            }
        } else {
            rrset = prev_rrset;
        }
        rrset->addRdata(createRdata(rrtype, zone.rrclass, records[i].rdata));
        if (rrtype == RRType::RRSIG()) {
            prev_rrset->addRRsig(rrset);
        } else {
            prev_rrset = rrset;
        }
    }
}

DataSrc::Result
TestDataSrc::init() {
    if (initialized) {
        return (SUCCESS);
    }

    if (zones.empty()) {
        for (int i = 0; i < NUM_ZONES; ++i) {
            Zone zone(zone_data[i].zone_name, zone_data[i].rrclass);
            buildZone(zone, zone_data[i].records, false);
            buildZone(zone, zone_data[i].glue_records, true);
            sort(zone.names.begin(), zone.names.end());
            zones.push_back(zone);
        }
    }

    initialized = true;
    return (SUCCESS);
}

void
TestDataSrc::findClosestEnclosure(DataSrcMatch& match) const {
    const Name& qname = match.getName();

    if (match.getClass() != getClass() && match.getClass() != RRClass::ANY()) {
        return;
    }

    vector<Zone>::const_iterator it;
    vector<Zone>::const_iterator best_it = zones.end();
    unsigned int best_common_labels = 0;
    for (it = zones.begin(); it != zones.end(); ++it) {
        const NameComparisonResult cmp = qname.compare(it->zone_name);
        const NameComparisonResult::NameRelation reln = cmp.getRelation();

        if ((reln == NameComparisonResult::EQUAL ||
             reln == NameComparisonResult::SUBDOMAIN) &&
            cmp.getCommonLabels() > best_common_labels) {
            best_it = it;
            best_common_labels = cmp.getCommonLabels();
        }
    }

    if (best_it != zones.end()) {
        match.update(*this, best_it->zone_name);
    }
}

struct ZoneNameMatch : public unary_function<Name, bool> {
    ZoneNameMatch(const Name& name) : name_(name) {}
    bool operator()(const Zone& zone) const {
        return (zone.zone_name == name_);
    }
    const Name& name_;
};

// XXX: the main data source module can override the returned RRset.
// That's bad and should be fixed (Trac #254), but for now we work around it.
RRsetPtr
copyRRset(RRsetPtr const source) {
    RRsetPtr rrset = RRsetPtr(new RRset(source->getName(), source->getClass(),
                                        source->getType(), source->getTTL()));
    RdataIteratorPtr it = source->getRdataIterator();
    for (it->first(); !it->isLast(); it->next()) {
        rrset->addRdata(it->getCurrent());
    }
    if (source->getRRsig()) {
        rrset->addRRsig(copyRRset(source->getRRsig()));
    }

    return (rrset);
}

class TestDataSrc::RRsetMatch {
public:
    struct MatchResult {
        MatchResult(const bool name_found, const bool has_delegation) :
            name_found_(name_found), has_delegation_(has_delegation)
        {}
        bool name_found_;
        bool has_delegation_;
    };
    RRsetMatch(const Name& name, const RRType& rrtype, const Mode mode,
               RRsetList& target, uint32_t& flags) :
        name_(name), rrtype_(rrtype), mode_(mode), target_(target),
        flags_(flags), name_found_(false), has_delegation_(false)
    {}
    void operator()(const RRsetPtr& rrset) {
        if (rrset->getName() != name_) {
            return;
        }
        name_found_ = true;

        if (rrset->getType() == RRType::NS() ||
            rrset->getType() == RRType::DNAME()) {
            has_delegation_ = true;
        }

        if (mode_ == DELEGATION) {
            if (rrset->getType() == RRType::NS() ||
                rrset->getType() == RRType::DNAME() ||
                rrset->getType() == RRType::DS()) {
                target_.addRRset(copyRRset(rrset));
            }
        } else if (mode_ == ADDRESS) {
            if (rrset->getType() == RRType::A() ||
                rrset->getType() == RRType::AAAA()) {
                target_.addRRset(copyRRset(rrset));
            }
        } else {
            if (rrtype_ == RRType::NSEC() &&
                rrset->getType() == RRType::CNAME()) {
                // XXX: ignore CNAME if the qtype is NSEC.
                // tricky, but necessary.
                return;
            }
            if (rrtype_ == RRType::ANY() || rrtype_ == rrset->getType() ||
                rrset->getType() == RRType::CNAME() ||
                rrset->getType() == RRType::DNAME()) {
                target_.addRRset(copyRRset(rrset));
                if (rrset->getType() == RRType::CNAME()) {
                    flags_ |= CNAME_FOUND;
                }
                if (rrset->getType() == RRType::DNAME()) {
                    flags_ |= REFERRAL;
                }
            }
        }
        
    }
    MatchResult getResult() { return (MatchResult(name_found_,
                                                  has_delegation_)); }
    const Name& name_;
    const RRType& rrtype_;
    const Mode mode_;
    RRsetList& target_;
    uint32_t& flags_;
    bool name_found_;
    bool has_delegation_;
};

void
TestDataSrc::findRecords(const Name& name, const RRType& rdtype,
                         RRsetList& target, const Name* zonename,
                         const Mode mode, uint32_t& flags) const
{
    flags = 0;

    assert(zonename != NULL);

    vector<Zone>::const_iterator zone = find_if(zones.begin(), zones.end(),
                                                ZoneNameMatch(*zonename));
    if (zone == zones.end()) {
        return;
    }

    const RRsetMatch::MatchResult match_result =
        for_each(zone->rrsets.begin(), zone->rrsets.end(),
                 RRsetMatch(name, rdtype, mode, target, flags)).getResult();
    if (match_result.has_delegation_) {
        flags |= REFERRAL;
    }
    if (target.size() == 0) {
        if (match_result.name_found_) {
            flags |= TYPE_NOT_FOUND;
        } else {
            flags |= NAME_NOT_FOUND;
        }
    }
}

DataSrc::Result
TestDataSrc::findRRset(const Name& qname,
                       const RRClass& qclass,
                       const RRType& qtype,
                       RRsetList& target,
                       uint32_t& flags,
                       const Name* zonename) const
{
    if (qclass != getClass() && qclass != RRClass::ANY()) {
        return (ERROR);
    }

    findRecords(qname, qtype, target, zonename, NORMAL, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findExactRRset(const Name& qname,
                            const RRClass& qclass,
                            const RRType& qtype,
                            RRsetList& target,
                            uint32_t& flags,
                            const Name* zonename) const
{
    if (qclass != getClass() && qclass != RRClass::ANY()) {
        return (ERROR);
    }

    findRecords(qname, qtype, target, zonename, NORMAL, flags);
    // Ignore referrals in this case
    flags &= ~REFERRAL;

    // CNAMEs don't count in this case
    if ((flags & CNAME_FOUND) != 0) {
        flags &= ~CNAME_FOUND;
        flags |= TYPE_NOT_FOUND;
    }

    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findAddrs(const Name& qname,
                       const RRClass& qclass,
                       RRsetList& target,
                       uint32_t& flags,
                       const Name* zonename) const
{
    if (qclass != getClass() && qclass != RRClass::ANY()) {
        return (ERROR);
    }

    findRecords(qname, RRType::ANY(), target, zonename, ADDRESS, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findReferral(const Name& qname,
                          const RRClass& qclass,
                          RRsetList& target,
                          uint32_t& flags,
                          const Name* zonename) const
{
    if (qclass != getClass() && qclass != RRClass::ANY()) {
        return (ERROR);
    }

    findRecords(qname, RRType::ANY(), target, zonename, DELEGATION, flags);
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findPreviousName(const Name& qname,
                              Name& target,
                              const Name* zonename) const
{
    assert(zonename != NULL);

    vector<Zone>::const_iterator zone = find_if(zones.begin(), zones.end(),
                                                ZoneNameMatch(*zonename));
    if (zone == zones.end()) {
        return (ERROR);
    }

    if (zone->names.empty()) {
        return (ERROR);
    }

    // if found, next_name >= qname.
    vector<Name>::const_iterator next_name =
        lower_bound(zone->names.begin(), zone->names.end(), qname);
    if (next_name == zone->names.end()) {
        // if no such name was found, the previous name is the last name.
        target = zone->names.back();
    } else if (*next_name == qname) {
        target = *next_name;
    } else if (next_name == zone->names.begin()) {
        // if qname < first_name, the "previous name" is the last name.
        target = zone->names.back();
    } else {
        // otherwise, qname and next_name share the same previous name.
        target = *(next_name - 1);
    }
    return (SUCCESS);
}

DataSrc::Result
TestDataSrc::findCoveringNSEC3(const Name& zonename UNUSED_PARAM,
                               string& hash UNUSED_PARAM,
                               RRsetList& target UNUSED_PARAM) const
{
    return (NOT_IMPLEMENTED);
}

}
}
