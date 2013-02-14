// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

namespace {

const char* const ZoneIterator_doc = "\
Read-only iterator to a zone.\n\
\n\
You can get an instance of the ZoneIterator from\n\
DataSourceClient.get_iterator() method. The actual concrete\n\
c++ implementation will be different depending on the actual data source\n\
used. This is the abstract interface.\n\
\n\
There's no way to start iterating from the beginning again or return.\n\
\n\
The ZoneIterator is a python iterator, and can be iterated over directly.\n\
";

const char* const ZoneIterator_getNextRRset_doc = "\
get_next_rrset() -> isc.dns.RRset\n\
\n\
Get next RRset from the zone.\n\
\n\
This returns the next RRset in the zone.\n\
\n\
Any special order is not guaranteed.\n\
\n\
While this can potentially throw anything (including standard\n\
allocation errors), it should be rare.\n\
\n\
Pointer to the next RRset or None pointer when the iteration gets to\n\
the end of the zone.\n\
\n\
Raises an isc.datasrc.Error exception if it is called again after returning\n\
None\n\
";

// Modifications:
//  - ConstRRset->RRset
//  - NULL->None
//  - removed notes about derived classes (which doesn't apply for python)
const char* const ZoneIterator_getSOA_doc = "\
get_soa() -> isc.dns.RRset\n\
\n\
Return the SOA record of the zone in the iterator context.\n\
\n\
This method returns the zone's SOA record (if any, and a valid zone\n\
should have it) in the form of an RRset object. This SOA is identical\n\
to that (again, if any) contained in the sequence of RRsets returned\n\
by the iterator. In that sense this method is redundant, but is\n\
provided as a convenient utility for the application of the iterator;\n\
the application may need to know the SOA serial or the SOA RR itself\n\
for the purpose of protocol handling or skipping the expensive\n\
iteration processing.\n\
\n\
If the zone doesn't have an SOA (which is broken, but some data source\n\
may allow that situation), this method returns None. Also, in the\n\
normal and valid case, the SOA should have exactly one RDATA, but this\n\
API does not guarantee it as some data source may accept such an\n\
abnormal condition. It's up to the caller whether to check the number\n\
of RDATA and how to react to the unexpected case.\n\
\n\
Exceptions:\n\
  None\n\
\n\
Return Value(s): An SOA RRset object that would be\n\
returned from the iteration. It will be None if the zone doesn't have\n\
an SOA.\n\
";
} // unnamed namespace
