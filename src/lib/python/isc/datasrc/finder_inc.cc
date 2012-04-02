namespace {
const char* const ZoneFinder_doc = "\
The base class to search a zone for RRsets.\n\
\n\
The ZoneFinder class is a wrapper for the c++ base class for representing an\n\
object that performs DNS lookups in a specific zone accessible via a\n\
data source. In general, different types of data sources (in-memory,\n\
database-based, etc) define their own derived c++ classes of ZoneFinder,\n\
implementing ways to retrieve the required data through the common\n\
interfaces declared in the base class. Each concrete ZoneFinder object\n\
is therefore (conceptually) associated with a specific zone of one\n\
specific data source instance.\n\
\n\
The origin name and the RR class of the associated zone are available\n\
via the get_origin() and get_class() methods, respectively.\n\
\n\
The most important method of this class is find(), which performs the\n\
lookup for a given domain and type. See the description of the method\n\
for details.\n\
\n\
It's not clear whether we should request that a zone finder form a\n\
\"transaction\", that is, whether to ensure the finder is not\n\
susceptible to changes made by someone else than the creator of the\n\
finder. If we don't request that, for example, two different lookup\n\
results for the same name and type can be different if other threads\n\
or programs make updates to the zone between the lookups. We should\n\
revisit this point as we gain more experiences.\n\
\n\
";

const char* const ZoneFinder_getOrigin_doc = "\
get_origin() -> isc.dns.Name\n\
\n\
Return the origin name of the zone.\n\
\n\
";

const char* const ZoneFinder_getClass_doc = "\
get_class() -> isc.dns.RRClass\n\
\n\
Return the RR class of the zone.\n\
\n\
";

// Main changes from the C++ doxygen version:
// - Return type: use tuple instead of the dedicated FindResult type
// - NULL->None
// - exceptions
const char* const ZoneFinder_find_doc = "\
find(name, type, options=FIND_DEFAULT) -> (integer, RRset, integer)\n\
\n\
Search the zone for a given pair of domain name and RR type.\n\
\n\
Each derived version of this method searches the underlying backend\n\
for the data that best matches the given name and type. This method is\n\
expected to be \"intelligent\", and identifies the best possible\n\
answer for the search key. Specifically,\n\
\n\
- If the search name belongs under a zone cut, it returns the code of\n\
  DELEGATION and the NS RRset at the zone cut.\n\
- If there is no matching name, it returns the code of NXDOMAIN.\n\
- If there is a matching name but no RRset of the search type, it\n\
  returns the code of NXRRSET. This case includes the search name\n\
  matches an empty node of the zone.\n\
- If there is a CNAME RR of the searched name but there is no RR of\n\
  the searched type of the name (so this type is different from\n\
  CNAME), it returns the code of CNAME and that CNAME RR. Note that if\n\
  the searched RR type is CNAME, it is considered a successful match,\n\
  and the code of SUCCESS will be returned.\n\
- If the search name matches a delegation point of DNAME, it returns\n\
  the code of DNAME and that DNAME RR.\n\
\n\
No RRset will be returned in the NXDOMAIN and NXRRSET cases (the\n\
second element of the tuple will be None), unless DNSSEC data are\n\
required. See below for the cases with DNSSEC.\n\
\n\
The third element of the returned tuple provides supplemental\n\
information about the search result in the form of a bitmask (called\n\
\"flags\"). Such information may be useful for the caller if the\n\
caller wants to collect additional DNSSEC proofs based on the search\n\
result.\n\
\n\
The options parameter specifies customized behavior of the search.\n\
Their semantics is as follows (they are or bit-field):\n\
\n\
- FIND_GLUE_OK Allow search under a zone cut. By default the search\n\
  will stop once it encounters a zone cut. If this option is specified\n\
  it remembers information about the highest zone cut and continues\n\
  the search until it finds an exact match for the given name or it\n\
  detects there is no exact match. If an exact match is found, RRsets\n\
  for that name are searched just like the normal case; otherwise, if\n\
  the search has encountered a zone cut, DELEGATION with the\n\
  information of the highest zone cut will be returned.\n\
- FIND_DNSSEC Request that DNSSEC data (like NSEC, RRSIGs) are\n\
  returned with the answer. It is allowed for the data source to\n\
  include them even when not requested.\n\
- NO_WILDCARD Do not try wildcard matching. This option is of no use\n\
  for normal lookups; it's intended to be used to get a DNSSEC proof\n\
  of the non existence of any matching wildcard or non existence of an\n\
  exact match when a wildcard match is found.\n\
\n\
Name is expected to be included in the zone, that is, it\n\
should be equal to or a subdomain of the zone origin. Otherwise an\n\
OutOfZoneFind exception is raised.\n\
\n\
Note: For this reason it's probably better to throw an exception than\n\
returning NXDOMAIN. This point should be revisited in a near future\n\
version. In any case applications shouldn't call this method for an\n\
out-of-zone name.\n\
\n\
DNSSEC considerations: The result when DNSSEC data are required can be\n\
very complicated, especially if it involves negative result or\n\
wildcard match. Specifically, if an application calls this method for\n\
DNS query processing with DNSSEC data, and if the search result code\n\
is either NXDOMAIN or NXRRRSET, and/or RESULT_WILDCARD\n\
flag is set in the returned flags value,\n\
then the application will need to find additional NSEC or NSEC3\n\
records for supplemental proofs. This method helps the application for\n\
such post search processing.\n\
\n\
First, it tells the application whether the zone is signed with NSEC\n\
or NSEC3 via the RESULT_NSEC_SIGNED and RESULT_NSEC3_SIGNED flags\n\
in the returned flags value. Any sanely signed zone\n\
should be signed with either (and only one) of these two types of RRs;\n\
however, the application should expect that the zone could be broken\n\
and these methods could both return false. But this method should\n\
ensure that not both of these methods return true.\n\
\n\
In case it's signed with NSEC3, there is no further information\n\
returned from this method.\n\
\n\
In case it's signed with NSEC, this method will possibly return a\n\
related NSEC RRset in the second element of the tuple. What kind of\n\
NSEC is returned depends on the result code (NXDOMAIN or NXRRSET) and\n\
on whether it's a wildcard match:\n\
\n\
- In case of NXDOMAIN, the returned NSEC covers the queried domain\n\
  that proves that the query name does not exist in the zone. Note\n\
  that this does not necessarily prove it doesn't even match a\n\
  wildcard (even if the result of NXDOMAIN can only happen when\n\
  there's no matching wildcard either). It is caller's responsibility\n\
  to provide a proof that there is no matching wildcard if that proof\n\
  is necessary.\n\
- In case of NXRRSET, we need to consider the following cases\n\
  referring to Section 3.1.3 of RFC4035:\n\
\n\
1. (Normal) no data: there is a matching non-wildcard name with a\n\
   different RR type. This is the \"No Data\" case of the RFC.\n\
2. (Normal) empty non terminal: there is no matching (exact or\n\
   wildcard) name, but there is a subdomain with an RR of the query\n\
   name. This is one case of \"Name Error\" of the RFC.\n\
3. Wildcard empty non terminal: similar to 2, but the empty name is\n\
   a wildcard, and matches the query name by wildcard expansion. This\n\
   is a special case of \"Name Error\" of the RFC.\n\
4. Wildcard no data: there is no exact match name, but there is a\n\
   wildcard name that matches the query name with a different type of RR.\n\
   This is the \"Wildcard No Data\" case of the RFC.\n\
\n\
In case 1, find() returns NSEC of the matching name.\n\
\n\
In case 2, find() will return NSEC for the interval where the empty\n\
nonterminal lives. The end of the interval is the subdomain causing\n\
existence of the empty nonterminal (if there's sub.x.example.com, and\n\
no record in x.example.com, then x.example.com exists implicitly - is\n\
the empty nonterminal and sub.x.example.com is the subdomain causing\n\
it). Note that this NSEC proves not only the existence of empty non\n\
terminal name but also the non existence of possibly matching wildcard\n\
name, because there can be no better wildcard match than the exact\n\
matching empty name.\n\
\n\
In case 3, find() will return NSEC for the interval where the wildcard\n\
empty nonterminal lives. Cases 2 and 3 are especially complicated and\n\
confusing. See the examples below.\n\
\n\
In case 4, find() will return NSEC of the matching wildcard name.\n\
\n\
Examples: if zone \"example.com\" has the following record:\n\
\n\
a.example.com. NSEC a.b.example.com.\n\
\n\
a call to  find() for \"b.example.com.\" with the FIND_DNSSEC option\n\
will result in NXRRSET, and this NSEC will be returned.\n\
Likewise, if zone \"example.org\" has the following record,\n\
\n\
a.example.org. NSEC x.*.b.example.org.\n\
\n\
a call to  find() for \"y.b.example.org\" with FIND_DNSSEC will\n\
result in NXRRSET and this NSEC;  RESULT_WILDCARD bit is set in the\n\
returned flags.\n\
\n\
This method raises an isc.datasrc.Error exception if there is an\n\
internal error in the datasource.\n\
\n\
Parameters:\n\
  name       The domain name to be searched for.\n\
  type       The RR type to be searched for.\n\
  options    The search options.\n\
\n\
Return Value(s): A tuple of a result code (integer), an RRset object\n\
and flags bitmask (integer).\n\
";

const char* const ZoneFinder_findAll_doc = "\
find_all(isc.dns.Name, options=FIND_DEFAULT) ->\n\
   (integer, RRset, integer) | (integer, [RRset], integer)\
\n\
Finds all RRsets in the given name.\n\
\n\
This function works almost exactly in the same way as the find one.\n\
The only difference is, when the lookup is successful (eg. the code is\n\
SUCCESS), all the RRsets residing in the named node are returned in the\n\
second element of the returned tuple. All\n\
the other (unsuccessful) cases are handled the same, including\n\
returning delegations, NSEC/NSEC3 availability and NSEC proofs,\n\
wildcard information etc. The options parameter works the same way and\n\
it should conform to the same exception restrictions.\n\
\n\
Parameters:\n\
  name       The domain name to be searched for.\n\
  options    The search options.\n\
\n\
Return Value(s): A tuple of a result code (integer), an either\n\
RRset object or a list of RRsets, and flags (integer).\n\
In the second element a single RRset is returned for cases where the\n\
result is some kind of delegation, CNAME or similar; in other cases\n\
a list of RRsets is returned, containing all the results.\n\
";

const char* const ZoneFinder_find_previous_name_doc = "\
find_previous_name(isc.dns.Name) -> isc.dns.Name\n\
\n\
Gets the previous name in the DNSSEC order. This can be used\n\
to find the correct NSEC records for proving nonexistence\n\
of domains.\n\
\n\
This method does not include under-zone-cut data (glue data).\n\
\n\
Raises isc.datasrc.NotImplemented in case the data source backend\n\
doesn't support DNSSEC or there is no previous in the zone (NSEC\n\
records might be missing in the DB, the queried name is less or\n\
equal to the apex).\n\
\n\
Raises isc.datasrc.Error for low-level or internal datasource errors\n\
(like broken connection to database, wrong data living there).\n\
";
} // unnamed namespace
